//*****************************************************************************
// ussSwLibISR.c
//
// TI Release: USSLib_02_40_00_00
// Release Date: __LIB_RELEASE_DATE__
//
//*****************************************************************************
#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include "common/USSGenericRegDef.h"
#include "ussSwLib.h"
#include "USS_Lib_HAL.h"


volatile uint32_t USSSWLIB_USS_interrupt_status;


void USS_registerSDHSInterruptCallback(USS_SDHS_Interrupt interruptNum,
		void function(void))
{
	switch (interruptNum)
	{
		case USS_SDHS_Interrupt_OVF:
			USSSWLIB_SDHS_OVF_callback = function;
			break;
		case USS_SDHS_Interrupt_ACQDONE:
			USSSWLIB_SDHS_ACQDONE_callback = function;
			break;
		case USS_SDHS_Interrupt_SSTRG:
			USSSWLIB_SDHS_SSTRG_callback = function;
			break;
		case USS_SDHS_Interrupt_DTRDY:
			USSSWLIB_SDHS_DTRDY_callback = function;
			break;
		case USS_SDHS_Interrupt_WINHI:
			USSSWLIB_SDHS_WINHI_callback = function;
			break;
		case USS_SDHS_Interrupt_WINLO:
			USSSWLIB_SDHS_WINLO_callback = function;
			break;
		default: break;
	}
}

void USS_unregisterSDHSInterruptCallback(USS_SDHS_Interrupt interruptNum)
{
	switch (interruptNum)
	{
		case USS_SDHS_Interrupt_OVF:
			USSSWLIB_SDHS_OVF_callback = 0;
			break;
		case USS_SDHS_Interrupt_ACQDONE:
			USSSWLIB_SDHS_ACQDONE_callback = 0;
			break;
		case USS_SDHS_Interrupt_SSTRG:
			USSSWLIB_SDHS_SSTRG_callback = 0;
			break;
		case USS_SDHS_Interrupt_DTRDY:
			USSSWLIB_SDHS_DTRDY_callback = 0;
			break;
		case USS_SDHS_Interrupt_WINHI:
			USSSWLIB_SDHS_WINHI_callback = 0;
			break;
		case USS_SDHS_Interrupt_WINLO:
			USSSWLIB_SDHS_WINLO_callback = 0;
			break;
		default: break;
	}
}

void USS_registerSAPHInterruptCallback(USS_SAPH_Interrupt interruptNum,
		void function(void))
{
	switch (interruptNum)
	{
		case USS_SAPH_Interrupt_DATAERR:
			USSSWLIB_SAPH_DATAERR_callback = function;
			break;
		case USS_SAPH_Interrupt_TMFTO:
		    USSSWLIB_SAPH_TMFTO_callback = function;
			break;
		case USS_SAPH_Interrupt_SEQDN:
			USSSWLIB_SAPH_SEQDN_callback = function;
			break;
		case USS_SAPH_Interrupt_PNGDN:
			USSSWLIB_SAPH_PNGDN_callback = function;
			break;
		default: break;
	}
}

// Unregister callback functions for ESI interrupt
void USS_unregisterSAPHInterruptCallback(USS_SAPH_Interrupt interruptNum)
{
	switch (interruptNum)
	{
		case USS_SAPH_Interrupt_DATAERR:
			USSSWLIB_SAPH_DATAERR_callback = 0;
			break;
		case USS_SAPH_Interrupt_TMFTO:
		    USSSWLIB_SAPH_TMFTO_callback = 0;
			break;
		case USS_SAPH_Interrupt_SEQDN:
			USSSWLIB_SAPH_SEQDN_callback = 0;
			break;
		case USS_SAPH_Interrupt_PNGDN:
			USSSWLIB_SAPH_PNGDN_callback = 0;
			break;
		default: break;
	}
}

void USS_registerUUPSInterruptCallback(USS_UUPS_Interrupt interruptNum,
		void function(void))
{
	switch (interruptNum)
	{
		case USS_UUPS_Interrupt_PREQIG :
			USSSWLIB_UUPS_PREQIG_callback = function;
			break;
		case USS_UUPS_Interrupt_PTMOUT :
			USSSWLIB_UUPS_PTMOUT_callback = function;
			break;
		case USS_UUPS_Interrupt_STPBYDB :
			USSSWLIB_UUPS_STPBYDB_callback = function;
			break;
		default: break;
	}
}

void USS_unregisterUUPSInterruptCallback(USS_UUPS_Interrupt interruptNum)
{
	switch (interruptNum)
	{
		case USS_UUPS_Interrupt_PREQIG:
			USSSWLIB_UUPS_PREQIG_callback = 0;
			break;
		case USS_UUPS_Interrupt_PTMOUT:
			USSSWLIB_UUPS_PTMOUT_callback = 0;
			break;
		case USS_UUPS_Interrupt_STPBYDB:
			USSSWLIB_UUPS_STPBYDB_callback = 0;
			break;
		default: break;
	}

}

void USS_registerHSPLLInterruptCallback(USS_HSPLL_Interrupt interruptNum,
		void function(void))
{
	switch (interruptNum)
	{
		case USS_HSPLL_Interrupt_PLLUNLOCK:
			USSSWLIB_HSPLL_PLLunlock_callback = function;
			break;
		default: break;
	}
}

void USS_unregisterHSPLLInterruptCallback(
		USS_HSPLL_Interrupt interruptNum)
{
	switch (interruptNum)
	{
		case USS_HSPLL_Interrupt_PLLUNLOCK:
			USSSWLIB_HSPLL_PLLunlock_callback = 0;
			break;
		default: break;
	}
}
