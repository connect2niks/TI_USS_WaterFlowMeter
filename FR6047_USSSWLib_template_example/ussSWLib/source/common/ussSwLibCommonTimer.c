//*****************************************************************************
// ussSwLibCommon.c
//
// TI Release: USSLib_02_40_00_00
// Release Date: __LIB_RELEASE_DATE__
//
//*****************************************************************************
#include "ussSwLibCommonTimer.h"

static void commonTimerWaitEvent(uint32_t flag, USS_low_power_mode_option lpmMode);

void commonTimerGenerateLowPowerDelay(
		USS_SW_Library_configuration *config,
		uint16_t delay,USS_low_power_mode_option lpmMode)
{
	// Save global interrupt status
	uint16_t gieStatus = ( __get_SR_register() & GIE);
	uint16_t compareControlReg = OFS_TAxCCTL1;
	uint16_t compareReg = OFS_TAxCCR1;

	commonTimerConfigureDelay(config,compareReg,delay);

	commonClearCCFlagStart(config,compareControlReg);

	commonTimerEnableInterrupt(config,compareControlReg);

	__disable_interrupt();
	while(false==(USSSWLIB_USS_interrupt_status & USS_TIMER_EXPIRED_EVENT1_INTERRUPT))
	{
		__bis_SR_register(lpmMode + GIE);
		__disable_interrupt();
	}

	commonClearCCFlagStart(config,compareControlReg);

	commonTimerDisableInterrupt(config,compareControlReg);

	USSSWLIB_USS_interrupt_status &= ~(USS_TIMER_EXPIRED_EVENT1_INTERRUPT);

	// Restore global interrupts status
	if(GIE == gieStatus)
	{
		__bis_SR_register(GIE);
	}
}

void commonTimerConfigureTick(
        USS_SW_Library_configuration *config)
{
    uint16_t compareControlReg = OFS_TAxCCTL0;
    uint16_t compareReg = OFS_TAxCCR0;

    commonTimerConfigureDelay(config,compareReg,config->systemConfig->measurementPeriod);
    commonClearCCFlagStart(config,compareControlReg);
    commonTimerEnableInterrupt(config,compareControlReg);

    // Clear expired interrupt flag
    USSSWLIB_USS_interrupt_status &= ~(USS_TIMER_EXPIRED_INTERRUPT);
}

void commonTimerConfigureDelay(USS_SW_Library_configuration *config,
        uint16_t compareRegister,
		uint16_t delay)
{
    HARDWAREWREG16(config->systemConfig->timerBaseAddress + OFS_TAxCTL) &= ~(MC__CONTINUOUS);
	HARDWAREWREG16(config->systemConfig->timerBaseAddress + compareRegister) =
	        HARDWAREWREG16(config->systemConfig->timerBaseAddress + OFS_TAxR) + delay;
	HARDWAREWREG16(config->systemConfig->timerBaseAddress + OFS_TAxCTL) |= MC__CONTINUOUS;
}

void commonTimerConfigurePeriodMeasurement(USS_SW_Library_configuration *config,
        uint16_t delay1, uint16_t delay2)
{
    commonTimerPeriodMeasurementClear(config);
    HARDWAREWREG16(config->systemConfig->timerBaseAddress + OFS_TAxCTL) &= ~(MC__CONTINUOUS);
    // CCR1 will be triggered on first event
    HARDWAREWREG16(config->systemConfig->timerBaseAddress + OFS_TAxCCR1) =
                HARDWAREWREG16(config->systemConfig->timerBaseAddress + OFS_TAxR) + delay1;
    // CCR2 will be a timeout for 2nd event
    HARDWAREWREG16(config->systemConfig->timerBaseAddress + OFS_TAxCCR2) =
                HARDWAREWREG16(config->systemConfig->timerBaseAddress + OFS_TAxR) + delay2;
    HARDWAREWREG16(config->systemConfig->timerBaseAddress + OFS_TAxCTL) |= MC__CONTINUOUS;
}

void commonTimerPeriodMeasurementClear(USS_SW_Library_configuration *config)
{
    USSSWLIB_USS_interrupt_status &= ~USS_TIMER_EXPIRED_EVENT1_INTERRUPT;
    USSSWLIB_USS_interrupt_status &= ~USS_TIMER_EXPIRED_EVENT2_INTERRUPT;
    HARDWAREWREG16(config->systemConfig->timerBaseAddress + OFS_TAxCCTL1) &= ~(CCIFG);
    HARDWAREWREG16(config->systemConfig->timerBaseAddress + OFS_TAxCCTL2) &= ~(CCIFG);
}

void commonTimerPeriodMeasurementEnableInterrupts(USS_SW_Library_configuration *config)
{
    HARDWAREWREG16(config->systemConfig->timerBaseAddress + OFS_TAxCCTL1) |= (CCIE);
    HARDWAREWREG16(config->systemConfig->timerBaseAddress + OFS_TAxCCTL2) |= (CCIE);
}

void commonTimerPeriodMeasurementDisableInterrupts(USS_SW_Library_configuration *config)
{
    HARDWAREWREG16(config->systemConfig->timerBaseAddress + OFS_TAxCCTL1) &= ~(CCIE);
    HARDWAREWREG16(config->systemConfig->timerBaseAddress + OFS_TAxCCTL2) &= ~(CCIE);
}

void commonTimerPeriodMeasurementStart(USS_SW_Library_configuration *config)
{
    commonTimerPeriodMeasurementClear(config);
    commonTimerPeriodMeasurementEnableInterrupts(config);
}

void commonTimerPeriodMeasurementWaitEvent1(USS_SW_Library_configuration *config,
                                             USS_low_power_mode_option lpmMode)
{
    commonTimerWaitEvent(USS_TIMER_EXPIRED_EVENT1_INTERRUPT, lpmMode);
}

void commonTimerPeriodMeasurementWaitEvent2(USS_SW_Library_configuration *config,
                                             USS_low_power_mode_option lpmMode)
{
    commonTimerWaitEvent(USS_TIMER_EXPIRED_EVENT2_INTERRUPT, lpmMode);

}

bool commonTimerWaitTickEvent(USS_SW_Library_configuration *config,
                              USS_low_power_mode_option lpmMode)
{
    bool overflowFlag = false;

    if(USSSWLIB_USS_interrupt_status & USS_TIMER_EXPIRED_INTERRUPT)
    {
        overflowFlag = true;
        USSSWLIB_USS_interrupt_status &= ~(USS_TIMER_EXPIRED_INTERRUPT);
    }
    else
    {
        commonTimerWaitEvent(USS_TIMER_EXPIRED_INTERRUPT,lpmMode);
    }

    return overflowFlag;
}

static void commonTimerWaitEvent(uint32_t flag,
                                 USS_low_power_mode_option lpmMode)
{
    // Save global interrupt status
    uint16_t gieStatus = ( __get_SR_register() & GIE);

    __disable_interrupt();
    while(false==(USSSWLIB_USS_interrupt_status & flag))
    {
        __bis_SR_register(lpmMode + GIE);
        __disable_interrupt();
    }

    USSSWLIB_USS_interrupt_status &= ~(flag);

    // Restore global interrupts status
    if(GIE == gieStatus)
    {
        __bis_SR_register(GIE);
    }
}

void commonClearCCFlagStart(USS_SW_Library_configuration *config,
                            uint16_t compareControlReg)
{
	HARDWAREWREG16(config->systemConfig->timerBaseAddress + compareControlReg) &= ~(CCIFG);
}

void commonTimerStart(USS_SW_Library_configuration *config)
{
	HARDWAREWREG16(config->systemConfig->timerBaseAddress + OFS_TAxCTL) |=
					(MC__CONTINUOUS | TACLR);
}

void commonTimerStop(USS_SW_Library_configuration *config)
{
	HARDWAREWREG16(config->systemConfig->timerBaseAddress + OFS_TAxCTL) &=
					~(MC__STOP);
}

void commonTimerClear(USS_SW_Library_configuration *config)
{
	HARDWAREWREG16(config->systemConfig->timerBaseAddress + OFS_TAxCTL) |=
						(TACLR);
}

void commonTimerEnableInterrupt(USS_SW_Library_configuration *config,
                                uint16_t compareControlReg)
{
	HARDWAREWREG16(config->systemConfig->timerBaseAddress + compareControlReg) |=
				(CCIE);
}

void commonTimerDisableInterrupt(USS_SW_Library_configuration *config,
                                 uint16_t compareControlReg)
{
	 HARDWAREWREG16(config->systemConfig->timerBaseAddress + compareControlReg) &=
				~(CCIE);
}

bool commonTimerPollInterruptFlag(USS_SW_Library_configuration *config)
{
	if(HARDWAREWREG16(config->systemConfig->timerBaseAddress + OFS_TAxCCTL1) &
			CCIFG)
	{
		return true;
	}

	return false;
}

bool commonTimerConfigureTimer(USS_SW_Library_configuration *config)
{

	// Configure Timer to be used for delays
	uint16_t baseAdress = config->systemConfig->timerBaseAddress;
	HARDWAREWREG16(baseAdress + OFS_TAxCTL) =
		(TASSEL__ACLK | ID__1 | MC__CONTINUOUS | TACLR);
	HARDWAREWREG16(baseAdress + OFS_TAxEX0) =
		(TAIDEX_0);
	HARDWAREWREG16(baseAdress + OFS_TAxCCTL1) =
			CCIE;

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
			commonTimerGenerateLowPowerDelay(config,4,
					USS_low_power_mode_option_low_power_mode_3);

			CSCTL5 &= ~LFXTOFFG;                // Clear XT1 fault flag
			SFRIFG1 &= ~OFIFG;

		}while ((SFRIFG1 & OFIFG));

	}
	CSCTL0_H = 0;

	return true;
}
