//*****************************************************************************
// ussSwLibCommon.c
//
// TI Release: USSLib_02_40_00_00
// Release Date: __LIB_RELEASE_DATE__
//
//*****************************************************************************
#include "ussSwLibCommonInterrupts.h"

static void commonEnableCommonCaptureInterrupts(
		USS_SW_Library_configuration *config);

void commonEnableCaptureInterrupts(
		USS_SW_Library_configuration *config)
{
	// Enable interrupts
	commonEnableCommonCaptureInterrupts(config);
	GENERIC_SAPH_IMSC |= (DATAERR | TMFTO | SEQDN);
}

void commonEnableManualSDHSTriggerInterrupts(
		USS_SW_Library_configuration *config)
{
	// Enable interrupts
	commonEnableCommonCaptureInterrupts(config);
	SDHSIMSC |= (ACQDONE);

}

static void commonEnableCommonCaptureInterrupts(
		USS_SW_Library_configuration *config)
{
	// Enable interrupts
	UUPSIMSC |= (PTMOUT | STPBYDB);
	HSPLLIMSC |= (PLLUNLOCK);
	if(config->captureConfig->enableWindowHiComp)
	{
		SDHSIMSC |= (WINHI);
	}

	if(config->captureConfig->enableWindowLoComp)
	{
		SDHSIMSC |= (WINLO);
	}

}

void commonDisableCaptureInterrupts(
		USS_SW_Library_configuration *config)
{
	UUPSIMSC &= ~(PTMOUT | STPBYDB);
	GENERIC_SAPH_IMSC &= ~(DATAERR | TMFTO | SEQDN);
	HSPLLIMSC &= ~(PLLUNLOCK);
	if(config->captureConfig->enableWindowHiComp)
	{
		SDHSIMSC &= ~(WINHI);
	}

	if(config->captureConfig->enableWindowLoComp)
	{
		SDHSIMSC &= ~(WINLO);
	}

    SDHSIMSC &= ~(ACQDONE);

}

void commonClearUSSInterrupts(void)
{
	// Clear any pending interrupt flags
	USSSWLIB_USS_interrupt_status &= ~(
			USS_SAPH_DATA_ERR_ABORT_INTERRUPT | USS_SAPH_TMF_TM_OUT_INTERRUPT |
			USS_SAPH_SEQ_ACQ_DN_INTERRUPT     | USS_SAPH_PING_DN_INTERRUPT    |
			USS_SDHS_WINLO_INTERRUPT          | USS_SDHS_WINHI_INTERRUPT      |
			USS_SDHS_DTRDY_INTERRUPT          | USS_SDHS_SSTRG_INTERRUPT      |
			USS_SDHS_ACQDONE_INTERRUPT        | USS_SDHS_OVF_INTERRUPT        |
			USS_UUPS_PWR_UP_TM_OUT_INTERRUPT  | USS_HSPLL_PLL_UNLOCK_INTERRUPT|
			USS_UUPS_STOPPED_BY_DEBUGGER      | USS_SAPH_SEQUENCE_STOPPED     |
			USS_UUPS_PWR_REQ_IGN_INTERRUPT    | USS_SAPH_DMA_ACK_VIOLATION);

	// Clear any pending USS Interrupts
	GENERIC_SAPH_ICR = (DATAERR | TMFTO | SEQDN | PNGDN);
	SDHSICR = (WINLO | WINHI | DTRDY | SSTRG | ACQDONE | OVF);
	UUPSICR = (PTMOUT | STPBYDB);
	HSPLLICR = (PLLUNLOCK);
}
