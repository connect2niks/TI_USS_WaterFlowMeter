#ifndef _USSSWLIBCOMMONTIMER_H_
#define _USSSWLIBCOMMONTIMER_H_

//#############################################################################
//
//! \file   ussSwLib.h
//!
//! \brief  Contains all USS SW Library enums, structs, macros, function and
//!			global variables defintions
//!         
//
//  Group:          MSP
//  Target Device:  Banshee
//
//  (C) Copyright 2019, Texas Instruments, Inc.
//#############################################################################
// TI Release: USSLib_02_40_00_00 
// Release Date: February 22, 2020
//#############################################################################


//*****************************************************************************
// includes
//*****************************************************************************
#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include "ussSwLib.h"

//*****************************************************************************
//! \addtogroup ussSwLib 
//! @{
//*****************************************************************************

#ifdef __cplusplus

extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************


//*****************************************************************************
// typedefs
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************


//*****************************************************************************
// the function prototypes
//*****************************************************************************
extern void commonTimerGenerateLowPowerDelay(
		USS_SW_Library_configuration *config,
		uint16_t delay, USS_low_power_mode_option lpmMode);

extern void commonClearCCFlagStart(USS_SW_Library_configuration *config,
                                   uint16_t compareControlReg);

extern void commonTimerConfigureTick(
        USS_SW_Library_configuration *config);

extern void commonTimerConfigureDelay(
		USS_SW_Library_configuration *config,
		uint16_t compareRegister,
		uint16_t delay);

extern void commonTimerStart(USS_SW_Library_configuration *config);

extern void commonTimerStop(USS_SW_Library_configuration *config);

extern void commonTimerEnableInterrupt(
		USS_SW_Library_configuration *config,
		uint16_t compareControlReg);

extern void commonTimerDisableInterrupt(
		USS_SW_Library_configuration *config,
		uint16_t);

extern bool commonTimerPollInterruptFlag(
		USS_SW_Library_configuration *config);

extern void commonTimerClear(USS_SW_Library_configuration *config);

extern inline bool commonTimerConfigureTimer(
		USS_SW_Library_configuration *config);
		
extern void commonTimerConfigurePeriodMeasurement(USS_SW_Library_configuration *config,
        uint16_t delay1, uint16_t delay2);

extern void commonTimerPeriodMeasurementClear(USS_SW_Library_configuration *config);

extern void commonTimerPeriodMeasurementEnableInterrupts(USS_SW_Library_configuration *config);

extern void commonTimerPeriodMeasurementDisableInterrupts(USS_SW_Library_configuration *config);

extern void commonTimerPeriodMeasurementStart(USS_SW_Library_configuration *config);

extern void commonTimerPeriodMeasurementWaitEvent1(USS_SW_Library_configuration *config,
                                             USS_low_power_mode_option lpmMode);

extern void commonTimerPeriodMeasurementWaitEvent2(USS_SW_Library_configuration *config,
                                             USS_low_power_mode_option lpmMode);

extern bool commonTimerWaitTickEvent(USS_SW_Library_configuration *config,
                                     USS_low_power_mode_option lpmMode);

#ifdef __cplusplus
}
#endif // extern "C"

#ifdef __cplusplus
}
#endif // extern "C"
//@}  // ingroup

#endif // end of  _USSSWLIBCOMMONTIMER_H_ definition
