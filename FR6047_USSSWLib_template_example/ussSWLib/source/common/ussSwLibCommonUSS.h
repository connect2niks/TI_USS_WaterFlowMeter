#ifndef _USSSWLIBCOMMONUSS_H_
#define _USSSWLIBCOMMONUSS_H_

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
#include "USS_Lib_HAL.h"
#include "ussSwLibCommonInterrupts.h"
#include "ussSwLibCommonHSPLL.h"
#include "ussSwLibCommonTimer.h"
#include "USSGenericRegDef.h"

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
//! \brief Used to specify the silicon version of FR6047 or FR6043 devices
//!
typedef enum _USS_silicon_version_
{
    USS_silicon_version_A,
    USS_silicon_version_B,
    USS_silicon_version_not_supported,
}USS_silicon_version;


//! \brief Used to identify FR6047 or FR6043 devices
//!
typedef enum _USS_silicon_variant_
{
    USS_silicon_version_variant_FR6047,
    USS_silicon_version_variant_FR6043,
    USS_silicon_version_variant_not_supported,
}USS_silicon_variant;


//*****************************************************************************
// defines
//*****************************************************************************
#define LEA_START_ADDRESS					    (0x2C00)
#define USS_ALGORITHMS_NUM_OF_SAMPLE_PADDING    (ALG_MAX_FILTER_LENGTH)


//*****************************************************************************
// typedefs
//*****************************************************************************


//*****************************************************************************
// globals
//*****************************************************************************



//*****************************************************************************
// the function prototypes
//*****************************************************************************
extern USS_message_code commonPowerUpUSS(
		USS_SW_Library_configuration *config);

extern USS_message_code commonPowerDownUSS(
		USS_SW_Library_configuration *config);

extern USS_message_code commonIsconversionSuccessfull(
		USS_SW_Library_configuration *config);

extern uint16_t commonDecodeSDHSDTCDAoffset(
		USS_SW_Library_configuration *config);

extern void commonWaitForconversion(
		USS_capture_power_mode_option mode);

extern USS_message_code commonPrepareForUSSPowerUp
	(USS_SW_Library_configuration *config);

extern USS_message_code commonUpdateUSSULPbiasDelay
    (USS_SW_Library_configuration *config);

extern USS_silicon_version commonDetermineSiliconVersion(void);

extern USS_silicon_variant commonDetermineVariant(void);

#ifdef __cplusplus
}
#endif // extern "C"
//@}  // ingroup

#endif // end of  _USSSWLIBUSS_H_ definition
