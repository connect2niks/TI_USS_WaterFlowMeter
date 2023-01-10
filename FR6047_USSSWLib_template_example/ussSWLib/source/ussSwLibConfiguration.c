//*****************************************************************************
// ussSwLibConfigurationUpdate.c
//
// TI Release: USSLib_02_40_00_00
// Release Date: __LIB_RELEASE_DATE__
//
//*****************************************************************************
#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include "ussSwLib.h"
#include "USS_Lib_HAL.h"
#include "common/ussSwLibCommonSAPH.h"
#include "common/ussSwLibCommonSDHS.h"
#include "common/ussSwLibCommonHSPLL.h"
#include "common/ussSwLibCommonUSS.h"
#include "common/USSGenericRegDef.h"
#include "USS_Config/USS_userConfig.h"

USS_message_code USS_updateSDHSConfiguration(USS_SW_Library_configuration *config)
{
	USS_message_code code;

	//
	// Validate SDHS parameter and HSPLL Output frequency if
	// USS_diagnostics_mode_2 is selected
	//
	if(USS_diagnostics_mode_2 == config->systemConfig->diagMode)
	{
		code = commonValidateSDHSconfigruation(config);

		if(USS_message_code_no_error != code)
		{
			return code;
		}
	}

	// Check if no active conversion is in progress
	if(UUPSCTL & USS_BUSY)
	{
		return USS_message_code_SDHS_update_error_ongoing_conversion;
	}


	// Unlock SDHS register for configuration
	SDHSCTL3 &= ~(TRIGEN);

	// Configure SDHS.CTL0, SDHS.CTL1, SDHS.CTL2, SDHS.CTL6, SDHS.CTL7,
	// SDHS.WINHITH, SDHS.WINLOTH, SDHS.DTCSA  registers
	SDHSCTL0 = TRGSRC + SHIFT_0 + OBR_0 + DFMSEL_0 + DALGN_0 + + INTDLY_0 +
			AUTOSSDIS;
	SDHSCTL1 = config->captureConfig->overSampleRate;

	if((config->captureConfig->enableWindowHiComp ||
			config->captureConfig->enableWindowLoComp))
	{
		SDHSCTL2 = WINCMPEN + DTCOFF_0 +
				(config->captureConfig->sampleSize - 1);

		// Configure SDHS window comparator based on user selection
		SDHSWINHITH = config->captureConfig->windowHighThreshold;

		// Configure SDHS window comparator based on user selection
		SDHSWINLOTH = config->captureConfig->windowLowThreshold;

	}else
	{
		SDHSCTL2 = DTCOFF_0 +
						(config->captureConfig->sampleSize -1);
	}
	
	// Configure PGA Gain
	SDHSCTL6 = config->captureConfig->gainRange;
	
	// Configure SDHS Modulator Optimization
	commonSDHSConfigModOpt(config);

    // Reset SDHSCTL4 and SDHSCTL5 registers
    SDHSCTL4 = 0;
    SDHSCTL5 = 0;

    // Configure DTC destination offset address
	commonSDHSRestoreSDHSDTCA(config);


	return USS_message_code_no_error;
}

USS_message_code USS_updateHSPLLConfiguration(
		USS_SW_Library_configuration *config)
{
	uint16_t tempVar;
	USS_message_code code;

	// Validate HSPLL Configuration parameters if
	// USS_diagnostics_mode_2 is selected
	if(USS_diagnostics_mode_2 == config->systemConfig->diagMode)
	{
		code = commonValidateHSPLLconfiguration(config);

		if(USS_message_code_no_error != code)
		{
			return code;
		}
	}


	// Check if no active conversion is in progress
	if(UUPSCTL & USS_BUSY)
	{
		return USS_message_code_HSPLL_update_error_ongoing_conversion;
	}

	// Unlock SDHS register for configuration
	SDHSCTL3 &= ~(TRIGEN);

	// Configure SDHS Modulator Optimization
	commonSDHSConfigModOpt(config);

	// Lock SDHS register for configuration
	SDHSCTL3 |= (TRIGEN);


	// Calculate HSPLL Multiplier using the following formula
	//                       (pll_out_freq_in_Hz * 2)
	//		PLLM =  ___________________________   -1
	//                           pll_in_freq_in_Hz

    switch(config->pllConfiguration->pllOutputFreq)
    {
        case USS_HSPLL_output_clk_freq_80_MHz:
            tempVar = 80;
            break;
        case USS_HSPLL_output_clk_freq_79_MHz:
            tempVar = 79;
            break;
        case USS_HSPLL_output_clk_freq_78_MHz:
            tempVar = 78;
            break;
        case USS_HSPLL_output_clk_freq_77_MHz:
            tempVar = 77;
            break;
        case USS_HSPLL_output_clk_freq_76_MHz:
            tempVar = 76;
            break;
        case USS_HSPLL_output_clk_freq_75_MHz:
            tempVar = 75;
            break;
        case USS_HSPLL_output_clk_freq_74_MHz:
            tempVar = 74;
            break;
        case USS_HSPLL_output_clk_freq_73_MHz:
            tempVar = 73;
            break;
        case USS_HSPLL_output_clk_freq_72_MHz:
            tempVar = 72;
            break;
        case USS_HSPLL_output_clk_freq_71_MHz:
            tempVar = 71;
            break;
        case USS_HSPLL_output_clk_freq_70_MHz:
            tempVar = 70;
            break;
        case USS_HSPLL_output_clk_freq_69_MHz:
            tempVar = 69;
            break;
        case USS_HSPLL_output_clk_freq_68_MHz:
            tempVar = 68;
            break;
        default:
            return USS_message_code_HSPLL_pllOutputFreq_inHz_error;
    }

    switch(config->pllConfiguration->ussXtalFreq)
    {
    case USS_HSPLL_input_clock_freq_4_MHz:
        tempVar >>= 1;
        break;
    case USS_HSPLL_input_clock_freq_8_MHz:
        tempVar >>= 2;
        break;
    default:
        return USS_message_code_HSPLL_pllXtalFreq_inHz_error;
    }

    tempVar--;


	tempVar = (tempVar<<10);


	if(config->pllConfiguration->ussXtalFreq ==  USS_HSPLL_input_clock_freq_8_MHz)
	{
		HSPLLCTL = tempVar + PLLINFREQ;
	}else
	{
		HSPLLCTL = tempVar;
	}

	// Configure HSPLLPLLXTLCTL register based on HSPLL input frequency clock
	// type (crystal or ceramic resonator) and based on user selection to output
	// HSPLL clock

	if(true == config->pllConfiguration->outputPLLXtal)
	{
		HSPLLUSSXTLCTL = config->pllConfiguration->HSPLLInputCLKType;
	}else
	{
		HSPLLUSSXTLCTL = config->pllConfiguration->HSPLLInputCLKType + XTOUTOFF;
	}


	return USS_message_code_no_error;
}

USS_message_code USS_updateSAPHConfiguration(USS_SW_Library_configuration *config)
{
	USS_message_code code;
    USS_silicon_version version;
    USS_silicon_variant variant;

    code = USS_message_code_no_error;

	// Validate SAPH PPG Configuration parameters if
	if(USS_diagnostics_mode_2 == config->systemConfig->diagMode)
	{
		code = commonValidateSAPHconfigruation(config);

		if(USS_message_code_no_error != code)
		{
			return code;
		}
	}

	// Check if no active conversion is in progress
	if(UUPSCTL & USS_BUSY)
	{
		return USS_message_code_SAPH_update_error_ongoing_conversion;
	}

    version = commonDetermineSiliconVersion();
    variant = commonDetermineVariant();

	// Prepare acquisition sequencer and Programmable Pulse Generator (PPG)
	// for configuration
	GENERIC_SAPH_KEY = KEY;

    if((variant == USS_silicon_version_variant_FR6043) ||
            ((variant == USS_silicon_version_variant_FR6047) && (version != USS_silicon_version_A) &&
            (version != USS_silicon_version_not_supported)))
    {
        // Configure bias impedance generator

        // Unlock SAPH and SAPH trim registers
        // Unlock trim register to be able to modify SAPHMCNF register
        GENERIC_SAPH_TACTL |= (UNLOCK);

        // Clear currently configured bias impedance generator
        GENERIC_SAPH_MCNF &= ~(BIMP_3);
        switch (config->measurementConfig->biasImpedance) {
        case USS_measurement_bias_impedance_1200_Ohms:
            GENERIC_SAPH_MCNF |= (BIMP_2);
            break;
        case USS_measurement_bias_impedance_200_Ohms:
            GENERIC_SAPH_MCNF |= (BIMP_0);
            break;
        case USS_measurement_bias_impedance_600_Ohms:
            GENERIC_SAPH_MCNF |= (BIMP_1);
            break;
        case USS_measurement_bias_impedance_2800_Ohms:
            GENERIC_SAPH_MCNF |= (BIMP_3);
            break;
        }


        switch (config->measurementConfig->muxChargePumpMode) {
        case USS_measurement_mux_charge_pump_always_on:
            // Configure RX input multiplexer charge pump to be explicitly on
            // during whole during whole capture
            GENERIC_SAPH_MCNF |= (CPEO);
            break;
        case USS_measurement_mux_charge_pump_always_off:
            // Configure RX input multiplexer charge pump to be off during
            // capture
            GENERIC_SAPH_MCNF &= ~(CPEO);
            break;
        }

        // Lock trim register to avoid unwanted modifications
        GENERIC_SAPH_TACTL &= ~(UNLOCK);
    }

	GENERIC_SAPH_ASCTL0 &= ~(ASQTEN);
	GENERIC_SAPH_PGCTL &= ~(PPGEN);

	GENERIC_SAPH_OCTL1 = ((config->measurementConfig->ch1DriveStrength << 1) +
			(config->measurementConfig->ch0DriveStrength));

#if (USS_PULSE_MODE == USS_PULSE_MODE_SINGLE_TONE)
	if(config->measurementConfig->pulseConfig->pulseGenMode ==
	        USS_measurement_pulse_generation_mode_single_tone)
	{
        code = commonConfigurePPGDutyCyle(config,
                       config->measurementConfig->pulseConfig->pulseGenMode);

	}
#endif
#if defined(__MSP430_HAS_SAPH_A__) && (USS_PULSE_MODE == USS_PULSE_MODE_DUAL_TONE)
	if(config->measurementConfig->pulseConfig->pulseGenMode ==
            USS_measurement_pulse_generation_mode_dual_tone)
	{
	    code = commonConfigurePPGDutyCyle(config,
                       config->measurementConfig->pulseConfig->pulseGenMode);

	SAPHPGCTL = (TRSEL_1 + PGSEL_1);
	}
#endif
#if defined(__MSP430_HAS_SAPH_A__) && (USS_PULSE_MODE == USS_PULSE_MODE_MULTI_TONE)
        if(config->measurementConfig->pulseConfig->pulseGenMode ==
            USS_measurement_pulse_generation_mode_multi_tone)
	{

	    code = commonConfigureMultiTone(config);

	}
#endif

	if(USS_message_code_no_error == code)
	{
        GENERIC_SAPH_PGCTL |= (TRSEL_1 + PGSEL_1);

        // Configure USS CH0 and CH1 to be configured by the PPG
        GENERIC_SAPH_OSEL |= (PCH0SEL_1 | PCH1SEL_1);
        // PPG configuration done
        GENERIC_SAPH_PGCTL |= (PPGEN);

        // Configure SAPH Acquisition sequencer
        switch (config->measurementConfig->sequenceSelection)
        {
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH0)
        case USS_CAPTURE_SEQUENCE_SELECTION_CH0:
//            GENERIC_SAPH_ASCTL0 = TRIGSEL_1;
            // Configure Bias Control registers
            // Defaulting excitation bias to 0.4V Nominal
            // Enable CH0 TX voltage
            GENERIC_SAPH_BCTL = (ASQBSC_1 | EXCBIAS_2 | CH0EBSW | PGABSW);
            // Configure mux to select correct RX channel
            GENERIC_SAPH_ICTL0 = (DUMEN | MUXCTL | MUXSEL_1);
            break;
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH1)
        case USS_CAPTURE_SEQUENCE_SELECTION_CH1:
//            GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + ASQCHSEL_1;
            // Configure Bias Control registers
            // Defaulting excitation bias to 0.4V Nominal
            // Enable CH1 TX voltage
            GENERIC_SAPH_BCTL = (ASQBSC_1 | EXCBIAS_2 | CH1EBSW | PGABSW);
            // Configure mux to select correct RX channel
            GENERIC_SAPH_ICTL0 = (DUMEN | MUXCTL | MUXSEL_0);
            break;
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH0 || \
        USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH1)
        case USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH0:
        case USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH1:
//            GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + PNGCNT0;
            // Configure Bias Control registers
            // Defaulting excitation bias to 0.4V Nominal
            // Enable CH0 TX voltage
            GENERIC_SAPH_BCTL = (ASQBSC_1 | EXCBIAS_2 | CH0EBSW | PGABSW);
            // Configure mux to select correct RX channel
            GENERIC_SAPH_ICTL0 = (DUMEN | MUXCTL | MUXSEL_1);
            break;
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH1 || \
        USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH0)
        case USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH1:
        case USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH0:
//            GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + ASQCHSEL_1 + PNGCNT0;
            // Configure Bias Control registers
            // Defaulting excitation bias to 0.4V Nominal
            // Enable CH1 TX voltage
            GENERIC_SAPH_BCTL = (ASQBSC_1 | EXCBIAS_2 | CH1EBSW | PGABSW);
            // Configure mux to select correct RX channel
            GENERIC_SAPH_ICTL0 = (DUMEN | MUXCTL | MUXSEL_0);
            break;
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH0_CH0 || \
        USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH1_CH0)
        case USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH0_CH0:
        case USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH1_CH0:
//            GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + PNGCNT1;
            // Configure Bias Control registers
            // Defaulting excitation bias to 0.4V Nominal
            // Enable CH0 TX voltage
            GENERIC_SAPH_BCTL = (ASQBSC_1 | EXCBIAS_2 | CH0EBSW | PGABSW);
            // Configure mux to select correct RX channel
            GENERIC_SAPH_ICTL0 = (DUMEN | MUXCTL | MUXSEL_1);
            break;
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH1_CH1 || \
        USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH0_CH1)
        case USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH1_CH1:
        case USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH0_CH1:
//            GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + ASQCHSEL_1 + PNGCNT1;
            // Configure Bias Control registers
            // Defaulting excitation bias to 0.4V Nominal
            // Enable CH1 TX voltage
            GENERIC_SAPH_BCTL = (ASQBSC_1 | EXCBIAS_2 | CH1EBSW | PGABSW);
            // Configure mux to select correct RX channel
            GENERIC_SAPH_ICTL0 = (DUMEN | MUXCTL | MUXSEL_0);
            break;
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH0_CH0_CH0 || \
        USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH1_CH0_CH1)
        case USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH0_CH0_CH0:
        case USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH1_CH0_CH1:
//            GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + PNGCNT0 + PNGCNT1;
            // Configure Bias Control registers
            // Defaulting excitation bias to 0.4V Nominal
            // Enable CH0 TX voltage
            GENERIC_SAPH_BCTL = (ASQBSC_1 | EXCBIAS_2 | CH0EBSW | PGABSW);
            // Configure mux to select correct RX channel
            GENERIC_SAPH_ICTL0 = (DUMEN | MUXCTL | MUXSEL_1);
            break;
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH1_CH1_CH1 || \
        USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH0_CH1_CH0)
        case USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH1_CH1_CH1:
        case USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH0_CH1_CH0:
//            GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + ASQCHSEL_1 + PNGCNT0 + PNGCNT1;
            // Configure Bias Control registers
            // Defaulting excitation bias to 0.4V Nominal
            // Enable CH1 TX voltage
            GENERIC_SAPH_BCTL = (ASQBSC_1 | EXCBIAS_2 | CH1EBSW | PGABSW);
            // Configure mux to select correct RX channel
            GENERIC_SAPH_ICTL0 = (DUMEN | MUXCTL | MUXSEL_0);
            break;
#endif
        default:
            break;
        }

        // Configure SAPH Acquisition sequencer
        switch (config->measurementConfig->sequenceSelection) {
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH0 || \
        USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH1)
            case USS_CAPTURE_SEQUENCE_SELECTION_CH0:
                GENERIC_SAPH_ASCTL0 = TRIGSEL_1;
                break;
            case USS_CAPTURE_SEQUENCE_SELECTION_CH1:
                GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + ASQCHSEL_1;
                break;
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH0 || \
        USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH1)
            case USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH0:
            case USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH1:
                GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + PNGCNT0;
                break;
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH1 || \
        USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH0)
            case USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH1:
            case USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH0:
                GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + ASQCHSEL_1 + PNGCNT0;
                break;
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH0_CH0 || \
        USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH1_CH0)
            case USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH0_CH0:
            case USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH1_CH0:
                GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + PNGCNT1;
                break;
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH1_CH1 || \
        USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH0_CH1)
            case USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH1_CH1:
            case USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH0_CH1:
                GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + ASQCHSEL_1 + PNGCNT1;
                break;
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH0_CH0_CH0 || \
        USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH1_CH0_CH1)
            case USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH0_CH0_CH0:
            case USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH1_CH0_CH1:
                GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + PNGCNT0 + PNGCNT1;
                break;
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH1_CH1_CH1 || \
        USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH0_CH1_CH0)
            case USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH1_CH1_CH1:
            case USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH0_CH1_CH0:
                GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + ASQCHSEL_1 + PNGCNT0 + PNGCNT1;
                break;
#endif
            default:
                break;
        }

        switch (config->measurementConfig->sequenceSelection) {
            case USS_CAPTURE_SEQUENCE_SELECTION_CH0:
            case USS_CAPTURE_SEQUENCE_SELECTION_CH1:
            case USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH0:
            case USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH1:
            case USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH0_CH0:
            case USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH1_CH1:
            case USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH0_CH0_CH0:
            case USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH1_CH1_CH1:
                    GENERIC_SAPH_ASCTL1 = config->measurementConfig->eofSequenceState;
                break;
            default:
                    GENERIC_SAPH_ASCTL1 = (config->measurementConfig->eofSequenceState) +
                            CHTOG;
                break;
        }

        // Selects pulse polarity
        GENERIC_SAPH_APOL = config->measurementConfig->pulseConfig->pulsePolarity;

        // Select pause state
        if(USS_measurement_pause_state_high_impedance ==
                config->measurementConfig->pulseConfig->pauseState)
        {
            GENERIC_SAPH_APHIZ = 0x000F;
            GENERIC_SAPH_APLEV = 0;
        }else if(USS_measurement_pause_state_low ==
                config->measurementConfig->pulseConfig->pauseState)
        {
            GENERIC_SAPH_APHIZ = 0;
            GENERIC_SAPH_APLEV = 0;
        }else
        {
            GENERIC_SAPH_APHIZ = 0;
            GENERIC_SAPH_APLEV = 0x000F;
        }

        // Configure SAPH time marks
        GENERIC_SAPH_ATM_A = config->measurementConfig->startPPGCount;
        GENERIC_SAPH_ATM_B = config->measurementConfig->turnOnADCCount;
        GENERIC_SAPH_ATM_C = config->measurementConfig->startPGAandINBiasCount;
        GENERIC_SAPH_ATM_D = config->measurementConfig->startADCsamplingCount;
        GENERIC_SAPH_ATM_E = config->measurementConfig->restartCaptureCount;
        GENERIC_SAPH_ATM_F = config->measurementConfig->captureTimeOutCount;

        // Acquisition sequencer for configuration done
        GENERIC_SAPH_ASCTL0 |= (ASQTEN);

        // Lock SAPH registers
        GENERIC_SAPH_KEY = 0;

        commonUpdateUSSULPbiasDelay(config);

        return USS_message_code_no_error;
	}else
	{
	    return code;
	}
}

USS_message_code USS_updateUUPSConfiguration(USS_SW_Library_configuration *config)
{

	// Check if no active conversion is in progress
	if(UUPSCTL & USS_BUSY)
	{
		return USS_message_code_UUPS_update_error_ongoing_conversion;
	}

	// Configure trigger selection
	UUPSCTL = ASQEN + config->triggerConfig->triggerConfig;


	return USS_message_code_no_error;
}

USS_message_code USS_updateUSSInterruptsConfiguration(
		USS_SW_Library_configuration *config)
{
	// Check if no active conversion is in progress
	if(UUPSCTL & USS_BUSY)
	{
		return USS_message_code_interrupt_update_error_ongoing_conversion;
	}

	//
	if(config->interruptConfig->enableSAPHPingTransmitDoneInterrupt)
	{
		// Clear pending interrupts before enabling Ping Done interrupt
		GENERIC_SAPH_ICR |= (PNGDN);
		// Enable Ping Done interrupt
		GENERIC_SAPH_IMSC |= (PNGDN);
	}else
	{
		// Disable Ping Done interrupt
		GENERIC_SAPH_IMSC &= ~(PNGDN);
	}


	if(config->interruptConfig->enableUUPSPREQIGInterrupt)
	{
		// Clear pending power request ignored interrupt
		UUPSICR |= (PREQIG);
		// Enable power request ignored interrupt
		UUPSIMSC |= (PREQIG);
	}else
	{
		// Disable power request ignored interrupt
		UUPSIMSC &= ~(PREQIG);
	}

	USSSWLIB_USS_interrupt_status &= ~(USS_INTERRUPTS_MASK);

	return USS_message_code_no_error;
}

USS_message_code USS_resetUSSModule(
        USS_SW_Library_configuration *config, bool reconfigUSSModule)
{
    USS_silicon_version version;
    USS_silicon_variant variant;
    bool isResetModule;

    // Determine if function is available based on device variant and revision
    isResetModule = false;
    version = commonDetermineSiliconVersion();
    variant = commonDetermineVariant();

    if(variant == USS_silicon_version_variant_FR6047)
    {
        if(version != USS_silicon_version_A)
        {
            isResetModule = true;
        }
    }else
    {
        isResetModule = true;
    }

    // Reset moduel based on flag value
    if(true == isResetModule)
    {
        // Reset USS Module
        UUPSCTL |= (USSSWRST);

        // Release module from reset state
        UUPSCTL &= ~(USSSWRST);

        // Reconfigure module based on user selection
        if(true == reconfigUSSModule)
        {
           return USS_configureUltrasonicMeasurement(config);
        }

        return USS_message_code_no_error;
    }

    return USS_meesage_code_silicon_version_does_not_support_this_functionality;

}


