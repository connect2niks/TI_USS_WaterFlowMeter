//*****************************************************************************
// ussSwLibCommon.c
//
// TI Release: USSLib_02_40_00_00
// Release Date: __LIB_RELEASE_DATE__
//
//*****************************************************************************
#include "ussSwLibCommonHSPLL.h"



USS_message_code commonValidateHSPLLconfiguration(
		USS_SW_Library_configuration *config)
{
	// Check if desired HSPLL Output frequency is between [68MHz and 80MHz]
	if((config->pllConfiguration->pllOutputFreq > USS_HSPLL_output_clk_freq_68_MHz))
	{
		return USS_message_code_HSPLL_pllOutputFreq_inHz_error;
	}


    // Check if HSPLL input frequency is between [4MHz and 8MHz]
	switch(config->pllConfiguration->ussXtalFreq)
	{
	case USS_HSPLL_input_clock_freq_4_MHz:
	case USS_HSPLL_input_clock_freq_8_MHz:
	    break;
	default:
        return USS_message_code_HSPLL_pllXtalFreq_inHz_error;
	}

	if((config->pllConfiguration->ussXTALsettlingCount == 0))
	{
		return USS_message_code_HSPLL_invalid_settling_count_error;
	}

	return USS_message_code_no_error;
}

void commonStabilizeOscillator(USS_SW_Library_configuration *config)
{

	commonTimerGenerateLowPowerDelay(config,
			config->pllConfiguration->ussXTALsettlingCount,
			USS_low_power_mode_option_low_power_mode_3);


}

uint32_t commonGetHSPLLFreqInHz(USS_SW_Library_configuration *config) {
	switch (config->pllConfiguration->pllOutputFreq) {
	case USS_HSPLL_output_clk_freq_80_MHz:
		return 80000000;
	case USS_HSPLL_output_clk_freq_79_MHz:
		return 79000000;
	case USS_HSPLL_output_clk_freq_78_MHz:
		return 78000000;
	case USS_HSPLL_output_clk_freq_77_MHz:
		return 77000000;
	case USS_HSPLL_output_clk_freq_76_MHz:
		return 76000000;
	case USS_HSPLL_output_clk_freq_75_MHz:
		return 75000000;
	case USS_HSPLL_output_clk_freq_74_MHz:
		return 74000000;
	case USS_HSPLL_output_clk_freq_73_MHz:
		return 73000000;
	case USS_HSPLL_output_clk_freq_72_MHz:
		return 72000000;
	case USS_HSPLL_output_clk_freq_71_MHz:
		return 71000000;
	case USS_HSPLL_output_clk_freq_70_MHz:
		return 70000000;
	case USS_HSPLL_output_clk_freq_69_MHz:
		return 69000000;
	case USS_HSPLL_output_clk_freq_68_MHz:
		return 68000000;
	default:
		return 80000000;
	}
}
