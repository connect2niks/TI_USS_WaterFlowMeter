#ifndef _USSSWLIBCOMMONHSPLL_H_
#define _USSSWLIBCOMMONHSPLL_H_

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
#include "ussSwLibCommonTimer.h"


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
extern USS_message_code commonValidateHSPLLconfiguration(
		USS_SW_Library_configuration *config);

extern void commonStabilizeOscillator(
		USS_SW_Library_configuration *config);

extern uint32_t commonGetHSPLLFreqInHz(USS_SW_Library_configuration *config);

extern void commonTurnOffHSPLLXTAL(void);

#ifdef __cplusplus
}
#endif // extern "C"
//@}  // ingroup

#endif // end of  _USSSWLIBHSPLL_H_ definition
