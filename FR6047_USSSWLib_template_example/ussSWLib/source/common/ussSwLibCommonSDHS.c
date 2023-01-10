//*****************************************************************************
// ussSwLibCommon.c
//
// TI Release: USSLib_02_40_00_00
// Release Date: __LIB_RELEASE_DATE__
//
//*****************************************************************************
#include "ussSwLibCommonSDHS.h"

USS_message_code commonValidateSDHSconfigruation(
		USS_SW_Library_configuration *config)
{

	// Check if sample size is within the valid range (1)
	if(true == ((config->captureConfig->sampleSize < 1)))
	{
		return USS_message_code_SDHS_sample_size_error;
	}

	// Check window threshold configuration
	// 1.-) Check if user enabled window threshold option otherwise skip check
	// 2.-) Check that that threshold value are valid based on output bit
	//      resolution
	if(true == ((config->captureConfig->enableWindowHiComp)))
	{
		if((config->captureConfig->windowHighThreshold < -2048) ||
		   (config->captureConfig->windowHighThreshold > 2047))
		{
			return USS_message_code_SDHS_threshold_error;
		}
	}

	if(true == ((config->captureConfig->enableWindowLoComp)))
	{
		if((config->captureConfig->windowLowThreshold < -2048) ||
		   (config->captureConfig->windowLowThreshold > 2047))
		{
			return USS_message_code_SDHS_threshold_error;
		}
	}

	if(true ==
	  ((config->captureConfig->enableWindowHiComp) &&
			  (config->captureConfig->windowLowThreshold)))
	{
		if((config->captureConfig->windowHighThreshold <
					config->captureConfig->windowLowThreshold))
		{
			return USS_message_code_SDHS_threshold_error;
		}
	}

	if ((config->captureConfig->sampleSize > config->captureConfig->maxCapture)) {
		return USS_message_code_SDHS_max_size_error;
	}


	//Check if HSPLL frequency is within (68MHz and 80MHz)
	if((config->pllConfiguration->pllOutputFreq >
		USS_HSPLL_output_clk_freq_68_MHz))
	{
		return USS_message_code_HSPLL_pllXtalFreq_inHz_error;
	}

	return USS_message_code_no_error;
}

void commonSDHSRestoreSDHSDTCA(
		USS_SW_Library_configuration *config)
{
	SDHSCTL4 &= ~(SDHSON);
	// Unlock SDHS registers
	SDHSCTL3 &= ~(TRIGEN);
	//Restore SDHSDTCDA address
	SDHSDTCDA = (((uint32_t)(&config->captureConfig->pCapturesBuffer[config->algorithmsConfig->filterLength << 1]) - USS_HAL_LEA_START_ADDRESS)>>1);
	// Lock SDHS registers
	SDHSCTL3 |= (TRIGEN);

}


void commonSDHSConfigModOpt(USS_SW_Library_configuration *config)
{
	switch (config->pllConfiguration->pllOutputFreq)
	{
		case USS_HSPLL_output_clk_freq_80_MHz:
		case USS_HSPLL_output_clk_freq_79_MHz:
		case USS_HSPLL_output_clk_freq_78_MHz:
		case USS_HSPLL_output_clk_freq_77_MHz:
			SDHSCTL7 = MODOPTI3 + MODOPTI2;
			break;
		case USS_HSPLL_output_clk_freq_76_MHz:
		case USS_HSPLL_output_clk_freq_75_MHz:
		case USS_HSPLL_output_clk_freq_74_MHz:
			SDHSCTL7 = MODOPTI3 + MODOPTI2 + MODOPTI0;
			break;
		case USS_HSPLL_output_clk_freq_73_MHz:
		case USS_HSPLL_output_clk_freq_72_MHz:
		case USS_HSPLL_output_clk_freq_71_MHz:
			SDHSCTL7 = MODOPTI3 + MODOPTI2 + MODOPTI1;
			break;
		default:
			SDHSCTL7 = MODOPTI3 + MODOPTI2 + MODOPTI1 + MODOPTI0;
			break;
	}
}
