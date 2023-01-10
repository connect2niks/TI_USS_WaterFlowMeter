/* --COPYRIGHT--,BSD
 * Copyright (C) 2019 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * --/COPYRIGHT--*/
/*******************************************************************************
 *
 *  system_pre_init.c - system_pre_init.c
 *
 ******************************************************************************/

/*
 * The function _system_pre_init it called by the start-up code before
 * "main" is called, and before data segment initialization is
 * performed.
 *
 * This is a template file, modify to perform any initialization that
 * should take place early.
 *
 * The return value of this function controls if data segment
 * initialization should take place. If 0 is returned, it is bypassed.
 *
 * For the MSP430 microcontroller family, please consider disabling
 * the watchdog timer here, as it could time-out during the data
 * segment initialization.
 */

#include <intrinsics.h>
#include <stdint.h>
#include "msp430.h"
#include "main.h"

#ifdef __TI_COMPILER_VERSION__
int _system_pre_init(void)
#elif __IAR_SYSTEMS_ICC__
int __low_level_init(void)
#elif __GNUC__
extern int system_pre_init(void) __attribute__((constructor));
int system_pre_init(void)
#else
#error Compiler not supported!
#endif
{
    /* Insert your low-level initializations here */

    /* Disable Watchdog timer to prevent reset during */
    /* int32_t variable initialization sequences. */
    // Stop WDT
    WDTCTL = WDTPW + WDTHOLD;

    /*
     * Configure CS module
     * MCLK  = 16 MHz from DCOCLK
     * SMCLK = 8MHz from DCOCLK
     * ACLK  = LFXTCLK expected to have a 32.768 KHz
     */
	// Unlock CS registers
	CSCTL0_H = CSKEY >> 8;
#if (USS_PULSE_MODE == 2)
    // Set DCO to 16MHz
    CSCTL1 = DCORSEL | DCOFSEL_4;
    // Configure wait states to be able to use 16 MHz MCLK
    FRCTL0 = (FRCTLPW | NWAITS_2);
    // Configure clock dividers all dividers
    CSCTL3 = (DIVA__1 | DIVS__2 | DIVM__1);
#else
    // Set DCO to 8MHz
    CSCTL1 = DCORSEL | DCOFSEL_3;
    // Configure clock dividers all dividers
    CSCTL3 = (DIVA__1 | DIVS__1 | DIVM__1);
#endif
    // Set SMCLK = MCLK = DCO, ACLK = LFXTCLK
    CSCTL2 = SELA__LFXTCLK | SELS__DCOCLK | SELM__DCOCLK;
	CSCTL4 |= (LFXTDRIVE_3);
	CSCTL4 &= ~(LFXTOFF);
	CSCTL0_H = 0;

	// GPIO Configuration
	PAOUT = 0;
	PADIR = 0xFFFF;

	PBOUT = 0;
	PBDIR = 0xFFFF;

	PCOUT = 0;
	PCDIR = 0xFFFF;

	PDOUT = 0;
	PDDIR = 0xFFFF;

    PEOUT = 0;
    PEDIR = 0xFFFF;

#if APPLICATION_ENABLE_UART_DEBUG
	// GPIO Configuration for UART mode
    P1SEL0 |= (BIT2 | BIT3);
    P1SEL1 &= ~(BIT2 | BIT3);

    // Configure USCI_A0 for UART mode, 8-bit data, 1 stop bit
    UCA1CTLW0 = UCSWRST;                    // Put eUSCI in reset
    UCA1CTLW0 |= UCSSEL__SMCLK;             // CLK = SMCLK

    // For BRCLK = SMCLK = 8MHz, and Baud rate = 115200 (See UG)
    UCA1BRW = 4;
    // UCBRSx (bits 7-4) = 0x55, UCBRFx (bits 3-1) = 5, UCOS16 (bit 0) = 1
    UCA1MCTLW = 0x5551;

    UCA1CTLW0 &= ~UCSWRST;                 // release from reset
#endif

    /*
     * Configure LFXT GPIO pins and start
     */
	PJSEL0 |= BIT4 | BIT5;

	// Disable the GPIO power-on default high-impedance mode to activate
	// previously configured port settings
	PM5CTL0 &= ~LOCKLPM5;


    /*==================================*/
    /* Choose if segment initialization */
    /* should be done or not.           */
    /* Return: 0 to omit initialization */
    /* 1 to run initialization          */
    /*==================================*/
    return(1);
}
