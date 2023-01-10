//*****************************************************************************
// ussSwLibCommon.c
//
// TI Release: USSLib_02_40_00_00
// Release Date: __LIB_RELEASE_DATE__
//
//*****************************************************************************
#include "ussSwLibCommonUSS.h"
#include "ussSwLibCommonInterrupts.h"
#include "ussSwLibCommonHSPLL.h"
#include "ussSwLibCommonTimer.h"


USS_message_code commonPowerUpUSS(
		USS_SW_Library_configuration *config)
{
	if((UUPSCTL & UPSTATE_3))
	{
		if(UUPSCTL & USS_BUSY)
		{
			return USS_message_code_UUPS_power_up_error;
		}

	}

	// Turn on USS Power and PLL and start measurement
	UUPSCTL |= USSPWRUP;


	return USS_message_code_no_error;
}

USS_message_code commonPowerDownUSS(
		USS_SW_Library_configuration *config)
{
	if((UUPSCTL & UPSTATE_3) != UPSTATE_0)
	{
		// Turn off USS Power and PLL and start measurement
		while((UUPSCTL & UPSTATE_3) != UPSTATE_0)
		{
			UUPSCTL |= USSPWRDN;
		}
	}




	return USS_message_code_no_error;
}


USS_message_code commonPrepareForUSSPowerUp
	(USS_SW_Library_configuration *config)
{
    USS_message_code code;
    uint8_t maxRetry = 50;

    // Check if HSPLL oscillator is enabled
    if(false == (HSPLLUSSXTLCTL & USSXTEN))
    {
        HSPLLUSSXTLCTL |= USSXTEN;

        commonStabilizeOscillator(config);
    }

    // Check if oscillator is stable maxRetry
    while(maxRetry > 0)
    {
        // Check if HSPLL oscillator is stable
        if(false != (HSPLLUSSXTLCTL & OSCSTATE))
        {
            code = USS_message_code_no_error;
            break;
        }
        else
        {
            code = USS_message_code_USSXT_oscillator_not_stable_error;
        }

        maxRetry = maxRetry - 1;
    }

    // Check if there is no active conversion
    if((code == USS_message_code_no_error) && (UUPSCTL & USS_BUSY))
    {
        code =  USS_message_code_USS_ongoing_active_conversion_error;
    }

    return code;
}


USS_message_code commonIsconversionSuccessfull(
		USS_SW_Library_configuration *config)
{
	// Disable interrupts used during capture
	commonDisableCaptureInterrupts(config);


	// Determine if ultrasonic measurement was completed successfully
	if(((USSSWLIB_USS_interrupt_status & (USS_SAPH_SEQ_ACQ_DN_INTERRUPT | USS_SAPH_PING_DN_INTERRUPT)) == USS_SAPH_SEQ_ACQ_DN_INTERRUPT) ||
	   ((USSSWLIB_USS_interrupt_status & USS_SDHS_ACQDONE_INTERRUPT) == USS_SDHS_ACQDONE_INTERRUPT))
	{
		// Check if ISTOP flag was set during conversion
		if(SDHSRIS & ISTOP)
		{
			return USS_message_code_invalid_conversion_data;
		}else
		{
			return USS_message_code_no_error;
		}

		// If it is not a valid conversion then check what went wrong
	}else
	{
		// Determine if conversion was stopped by debugger
		if(USSSWLIB_USS_interrupt_status & USS_UUPS_STOPPED_BY_DEBUGGER)
		{
			return USS_message_code_error_conversion_stopped_by_debugger;
		}

		// Check Window Threshold interrupt
		// Only if user has enabled this feature
		if(config->captureConfig->enableWindowLoComp)
		{
			// Check if Window Low threshold has been reached during
			// conversion
			if(USSSWLIB_USS_interrupt_status & USS_SDHS_WINLO_INTERRUPT)
			{
				return USS_message_code_SDHS_window_low_threshold_reached;
			}
		}

		if(config->captureConfig->enableWindowHiComp)
		{
			// Check if Window High threshold has been reached during
			// conversion
			if(USSSWLIB_USS_interrupt_status & USS_SDHS_WINHI_INTERRUPT)
			{
				return USS_message_code_SDHS_window_high_threshold_reached;
			}

		}

		// Check if there was a USS Power Up Time Out
		if(USSSWLIB_USS_interrupt_status & USS_UUPS_PWR_UP_TM_OUT_INTERRUPT)
		{
			return USS_message_code_UUPS_power_up_time_out_error;
		}

		// Check if SAPH data error interrupt was fired
		if(USSSWLIB_USS_interrupt_status &
				USS_SAPH_DATA_ERR_ABORT_INTERRUPT)
		{
			return USS_message_code_data_error_abort;
		}

		// Check if SAPH Time Mark 4 timed out
		if(USSSWLIB_USS_interrupt_status & USS_SAPH_TMF_TM_OUT_INTERRUPT)
		{
			return USS_message_code_ASQ_time_out;
		}

		// Check if PLL was unlocked during conversion
		if(USSSWLIB_USS_interrupt_status & USS_HSPLL_PLL_UNLOCK_INTERRUPT)
		{
			return USS_message_code_HSPLL_pll_unlock_error;
		}

		// Check if Measurement was stopped
		if(USSSWLIB_USS_interrupt_status & USS_SAPH_SEQUENCE_STOPPED)
		{
			return USS_message_code_measurement_stopped;
		}

		// Code should not reach this point

	}
	// Code should not reach this point

	return USS_message_code_error_occurred;

}

void commonWaitForconversion(
		USS_capture_power_mode_option mode)
{

	uint16_t gieStatus = (__get_SR_register() & GIE);

	__disable_interrupt();

	// The following events will cause the API to exit low power mode
	//	- If SDHS is in manual mode: SDHS ACQDONE
	//	- If SDHS is controlled by ASQ: SAPH ACQ DN
	//	- If conversion is stopped
	//	- If conversion is interrupted by entering debug mode
	while(false ==
			((USSSWLIB_USS_interrupt_status & USS_SAPH_SEQ_ACQ_DN_INTERRUPT) ||
			(USSSWLIB_USS_interrupt_status & USS_SDHS_ACQDONE_INTERRUPT) ||
			(USSSWLIB_USS_interrupt_status & USS_SAPH_SEQUENCE_STOPPED)  ||
			(USSSWLIB_USS_interrupt_status & USS_UUPS_STOPPED_BY_DEBUGGER) ||
			(USSSWLIB_USS_interrupt_status & USS_HSPLL_PLL_UNLOCK_INTERRUPT) ||
			(USSSWLIB_USS_interrupt_status & USS_UUPS_PWR_UP_TM_OUT_INTERRUPT)))
	{
		if(USS_capture_power_mode_active != mode)
		{
			__bis_SR_register(mode);
			__disable_interrupt();
		}else
		{
			__enable_interrupt();
		}
	}


	if(gieStatus)
	{
		__enable_interrupt();
	}
}

USS_message_code commonUpdateUSSULPbiasDelay
    (USS_SW_Library_configuration *config)
{

    USS_silicon_version version;
    USS_silicon_variant variant;

    // Unlock SAPH and SAPH trim registers

    version = commonDetermineSiliconVersion();
    variant = commonDetermineVariant();

    if((variant == USS_silicon_version_variant_FR6043) ||
            ((variant == USS_silicon_version_variant_FR6047) && (version != USS_silicon_version_A) &&
            (version != USS_silicon_version_not_supported)))
    {
        GENERIC_SAPH_KEY = KEY;
        GENERIC_SAPH_TACTL |= (UNLOCK);
        // Configure ULP bias configuration
        UUPSCTL &= ~(LBHDEL_3);
        switch (config->measurementConfig->ulpBiasDelay)
        {
            case USS_measurement_ULP_bias_delay_200_usec:
                GENERIC_SAPH_MCNF |= (LPBE);
                UUPSCTL |= (LBHDEL_2);
                break;
            case USS_measurement_ULP_bias_delay_100_usec:
                GENERIC_SAPH_MCNF |= (LPBE);
                UUPSCTL |= (LBHDEL_1);
                break;
            case USS_measurement_ULP_bias_delay_300_usec:
                GENERIC_SAPH_MCNF |= (LPBE);
                UUPSCTL |= (LBHDEL_3);
                break;
            default:
                // Default is no ULP delay
                GENERIC_SAPH_MCNF &= ~(LPBE);
                UUPSCTL |= (LBHDEL_0);
                break;
        }

        // Lock SAPH registers and lock trim registers
        GENERIC_SAPH_TACTL &= ~(UNLOCK);
        GENERIC_SAPH_KEY = 0;
    }


    return USS_message_code_no_error;
}


USS_silicon_version commonDetermineSiliconVersion(void)
{
// Hardware device ID location
#define DEVICE_HW_ID  *((uint8_t *)0x1A06)

    uint8_t devID = DEVICE_HW_ID;

    switch (devID) {
        case 0x10:
            return USS_silicon_version_A;
        case 0x20:
            return USS_silicon_version_B;
    }

    return USS_silicon_version_not_supported;
}

USS_silicon_variant commonDetermineVariant(void)
{
    // Device ID location
#define DEVICE_ID  *((uint16_t *)0x1A04)

    uint16_t devID = DEVICE_ID;

    if(devID == 0x832E || devID == 0x832F)
    {
        return USS_silicon_version_variant_FR6047;
    }
    else if(((devID & 0x8300) == 0x8300) && (devID != 0x8300))
    {
        return USS_silicon_version_variant_FR6043;
    }else if(((devID & 0x8200) == 0x8200) || (devID == 0x8300))
    {
        return USS_silicon_version_variant_FR6047;
    }

    return USS_silicon_version_variant_not_supported;
}

void commonTurnOffHSPLLXTAL(void)
{
    // Check if HSPLL oscillator is enabled
    if(true == (HSPLLUSSXTLCTL & USSXTEN))
    {
        HSPLLUSSXTLCTL &= ~USSXTEN;
    }
}

