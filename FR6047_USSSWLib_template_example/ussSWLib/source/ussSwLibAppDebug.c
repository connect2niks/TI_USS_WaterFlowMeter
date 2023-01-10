//*****************************************************************************
// ussSwLibAppDebug.c
//
// TI Release: USSLib_02_40_00_00
// Release Date: __LIB_RELEASE_DATE__
//
//*****************************************************************************
#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include "ussSwLib.h"
#include "common/USSGenericRegDef.h"
#include "common/ussSwLibCommonSAPH.h"
#include "common/ussSwLibCommonSDHS.h"
#include "common/ussSwLibCommonInterrupts.h"
#include "common/ussSwLibCommonUSS.h"


USS_message_code USS_testPPGconfiguration(USS_SW_Library_configuration *config,
		USS_test_channel pPGChannel)
{
	USS_message_code code;

	code = commonConfigurePPGForManualMode(config, pPGChannel);


	// Unlock SAPH registers
    GENERIC_SAPH_KEY = KEY;

	// Trigger PPG
	GENERIC_SAPH_PPGTRIG |= PPGTRIG;

	// Wait for excitation sequence to be done. Implemented using delay cycles
	// since PPGDN flag is not set during manual trigger.
	__delay_cycles(62000);

    commonPowerDownUSS(config);

    commonTurnOffHSPLLXTAL();

    // Reconfigure UUPS and SAPH modules
    code = USS_updateUUPSConfiguration(config);
    if(USS_message_code_no_error != code)
    {
        return code;
    }

    // Return to ASQ mode
    code = USS_updateSAPHConfiguration(config);
    if(USS_message_code_no_error != code)
    {
        return code;
    }

	return code;
}

USS_message_code USS_testSDHSconversion(
		USS_SW_Library_configuration *config, USS_test_channel SDHSChannel,
		USS_capture_power_mode_option mode)
{

	USS_message_code code;

	// Update SDHS configuration
	code = USS_updateSDHSConfiguration(config);

	if(USS_message_code_no_error != code)
	{
		return	code;
	}

	//  Disable Acquisition Sequencer
	UUPSCTL &= ~(ASQEN);

	// Unlock SDHS registers
	SDHSCTL3 &= ~(TRIGEN);

	// Configure SDHS for SDHSON bit to start sampling as well as power up
	// Sampling Size count and DTC are enabled by USS_updateSDHSConfiguration
	// API
	SDHSCTL0 &= ~(AUTOSSDIS | TRGSRC);

	// Unlock SAPH registers
	GENERIC_SAPH_KEY = KEY;

	// Configure MUX input SAPHICTL0 register
	// - Channel mulitplexer is controlled by register
	// - Configure MUX input channel
	GENERIC_SAPH_ICTL0 = DUMEN + SDHSChannel;

	// Configure SAPH to use nominal PGABIAS and configure BIAS switch to close
	GENERIC_SAPH_BCTL = PGABIAS_2 + PGABSW;

	// Lock SAPH registers
	GENERIC_SAPH_KEY = 0;

	
	// Check the oscillation fault flag if the flag is set then go to LPM3 mode
	// for 800 ms if there is fault in LFXT crystal then ACLK is being sourced by
	// LFMODCLK at ~37.5 KHz
	CSCTL0_H = CSKEY >> 8;
	CSCTL5 &= ~LFXTOFFG;                // Clear XT1 fault flag
	SFRIFG1 &= ~OFIFG;

	if(SFRIFG1 & OFIFG)
	{
		do
		{
			CSCTL5 &= ~LFXTOFFG;                // Clear XT1 fault flag
			SFRIFG1 &= ~OFIFG;

		}while ((SFRIFG1 & OFIFG));

	}
	CSCTL0_H = 0;

	// Lock SDHS registers
	SDHSCTL3 |= (TRIGEN);

	// Configures HSPLL
	USS_updateHSPLLConfiguration(config);

	// Confirm HSPLL is locked
	code = commonPrepareForUSSPowerUp(config);
	if(USS_message_code_no_error != code)
	{
		return code;
	}

	commonPowerUpUSS(config);

	// Configure SDHS interrupt and HSPLL interrupts
	commonClearUSSInterrupts();

	commonEnableManualSDHSTriggerInterrupts(config);

	// Wait until HSPLL is locked
	while((HSPLLCTL & PLL_LOCK)!= PLL_LOCK);

	// Trigger conversion and wait in user selected low power mode until
	// conversion is done
	SDHSCTL4 |= SDHSON;

	commonWaitForconversion(mode);

	code = commonIsconversionSuccessfull(config);

	// Reconfigure SDHSDTCDA
	commonSDHSRestoreSDHSDTCA(config);

	// Exit SDHS manual mode

	// Unlock SDHS registers
	SDHSCTL3 &= ~(TRIGEN);

	// Configure SDHS for SSTART bit to trigger sampling as well as power up
	// Sampling Size count and DTC are enabled by USS_updateSDHSConfiguration
	// API
	SDHSCTL0 &= ~(AUTOSSDIS);

	// Lock SDHS registers
	SDHSCTL3 |= (TRIGEN);

	// Unlock SAPH registers
	GENERIC_SAPH_KEY = KEY;

	// Configure MUX input SAPHICTL0 register
	// - Channel mulitplexer is controlled by register
	// - Configure MUX input channel
	GENERIC_SAPH_ICTL0 = (DUMEN_1 | MUXCTL_1) ;

	// Configure SAPH to be controlled by ASQ
	// Defaulting excitation bias to 0.4V Nominal
	GENERIC_SAPH_BCTL = (ASQBSC_1 | EXCBIAS_2) ;

	// Lock SAPH registers
	GENERIC_SAPH_KEY = 0;

	// Enable Acquisition Sequencer
	UUPSCTL |= (ASQEN_1);

	return code;
}

USS_message_code USS_startPPGToneGeneration(
		USS_SW_Library_configuration *config,
		USS_test_channel pPGChannel)
{
	USS_message_code code;

	code = USS_updateHSPLLConfiguration(config);

	if(USS_message_code_no_error != code)
	{
		return code;
	}

	// configure PPG Frequency and duty cycle
	commonConfigurePPGDutyCyle(config,
                      config->measurementConfig->pulseConfig->pulseGenMode);

	// Disable ASQ to make sure sequence is not triggered when
	// powering up the USS module
    UUPSCTL &= ~(ASQEN);

    // Unlock SAPH registers
    GENERIC_SAPH_KEY = KEY;

    // Configure Channel selection which PPG acts on
    if(USS_test_channel_1 == pPGChannel)
    {
      GENERIC_SAPH_PGCTL = (TRSEL_0| PPGCHSEL_1 | PGSEL_0);
    }else
    {
      GENERIC_SAPH_PGCTL = (TRSEL_0| PPGCHSEL_0 | PGSEL_0);
    }

    // Finish PPG configuration
    GENERIC_SAPH_PGCTL |= (PPGEN);

    // Confirm HSPLL is locked
    code = commonPrepareForUSSPowerUp(config);
    if(USS_message_code_no_error != code)
    {
      return code;
    }

    code = commonPowerUpUSS(config);
    if(USS_message_code_no_error != code)
    {
      return code;
    }

    // Wait until USS module is in READY state
    while((UUPSCTL & UPSTATE_3) != UPSTATE_3);

    // Start Tone generation
    GENERIC_SAPH_PGCTL |= (TONE);

    // Lock SAPH registers
    GENERIC_SAPH_KEY = 0;

	return code;
}

USS_message_code USS_stopPPGToneGeneration(
		USS_SW_Library_configuration *config)
{
	USS_message_code code;

	// Unlock SAPH registers
	GENERIC_SAPH_KEY = KEY;

	// Stop any active tone generation
	GENERIC_SAPH_PGCTL &= ~(TONE);

    // Lock SAPH registers
    GENERIC_SAPH_KEY = 0;

    commonPowerDownUSS(config);

    commonTurnOffHSPLLXTAL();

	code = USS_updateUUPSConfiguration(config);
    if(USS_message_code_no_error != code)
    {
        return code;
    }

	// Return to ASQ mode
	code = USS_updateSAPHConfiguration(config);
    if(USS_message_code_no_error != code)
    {
        return code;
    }

	return code;
}
