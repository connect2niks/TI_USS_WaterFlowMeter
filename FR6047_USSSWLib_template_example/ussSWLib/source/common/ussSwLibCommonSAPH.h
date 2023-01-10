#ifndef _USSSWLIBCOMMONSAPH_H_
#define _USSSWLIBCOMMONSAPH_H_

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
#include <math.h>
#include <intrinsics.h>
#include "ussSwLib.h"
#include "ussSwLibCommonUSS.h"
#include "USSGenericRegDef.h"
#include "IQmathLib.h"

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
#define USS_SAPH_MAX_MULTITONE_UPDATE_FREQ_IN_HZ                (420000)

#define USS_SAPH_MAX_STOP_PULSES                                (16)

//*****************************************************************************
// typedefs
//*****************************************************************************


//*****************************************************************************
// globals
//*****************************************************************************


//*****************************************************************************
// the function prototypes
//*****************************************************************************

extern USS_message_code commonConfigurePPGDutyCyle(
        USS_SW_Library_configuration *config,
        USS_measurement_pulse_generation_mode mode);

extern USS_message_code commonConfigurePPGForManualMode(
		USS_SW_Library_configuration *config, USS_test_channel pPGChannel);

extern USS_message_code commonValidateSAPHconfigruation(
		USS_SW_Library_configuration *config);

#ifdef __MSP430_HAS_SAPH_A__
extern USS_message_code commonConfigureMultiTone(USS_SW_Library_configuration *config);
#endif


#ifdef __cplusplus
}
#endif // extern "C"
//@}  // ingroup

#endif // end of  _USSSWLIBCOMMONSAPH_H_ definition
