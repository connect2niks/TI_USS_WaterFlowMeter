#ifndef _USSINTERNALREG_H_
#define _USSINTERNALREG_H_

#include <msp430.h>

#if defined(__MSP430_HAS_SAPH__)
#define __MSP430_BASEADDRESS_GENERIC_SAPH__          __MSP430_BASEADDRESS_SAPH__
#elif defined(__MSP430_BASEADDRESS_SAPH_A__)
#define __MSP430_BASEADDRESS_GENERIC_SAPH__          __MSP430_BASEADDRESS_SAPH_A__
#else
#error "SAPH module not supported by USS SW Library"
#endif

/* SAPHMCNF Control Bits */
#define LPBE                             (0x0800)        /* */
#define LPBE_0                           (0x0000)        /* For manual bias mode and regular ASQ bias mode. In this
                                                            configuration the user controls by the ASQBSW has full control
                                                            over the TxBias and RxBias switches. */
#define LPBE_1                           (0x0800)        /* Low power bias mode. In this mode the ASQ uses the CHxEBSW and
                                                            PGABSW as auxiliary values to achieve faster channel setting
                                                            on reactive input loads. The ASQ has full controls over the
                                                            bias switch multiplexer. */
#define CPEO                             (0x0100)        /* */
#define CPEO_0                           (0x0000)        /* Charge pump is turned on by SDHS and ASQ related requests
                                                            only. */
#define CPEO_1                           (0x0100)        /* Charge pump is turned on regardless of SDHS and ASQ related
                                                            charge pump requests. */
//#define BIMP                             (0x0000)        /* */
#define BIMP_0                           (0x0000)        /* 200 Ohms buffer impedance for RxBias and TxBias */
#define BIMP_1                           (0x0001)        /* 600 Ohms buffer impedance for RxBias and TxBias */
#define BIMP_2                           (0x0002)        /* 1200 Ohms buffer impedance for RxBias and TxBias (default) */
#define BIMP_3                           (0x0003)        /* 2800 Ohms buffer impedance for RxBias and TxBias */


#define LBHDEL_0                         (0x0000)        /* no additional delay */
#define LBHDEL_1                         (0x1000)        /* additional hold off delay of ~100us (512 REFCLKs) */
#define LBHDEL_1_H                       (0x0010)
#define LBHDEL_2                         (0x2000)        /* additional hold off delay of ~200us (1024 REFCLKs) */
#define LBHDEL_2_H                       (0x0020)
#define LBHDEL_3                         (0x3000)        /* additional hold off delay of ~300us (1536 REFCLKs) */
#define LBHDEL_3_H                       (0x0030)

#define USSSWRST                         (0x0080)        /* */
#define USSSWRST_L                       (0x0080)
#define USSSWRST_0                       (0x0000)        /* Disabled. USS (and sub modules) reset released for operation */
#define USSSWRST_1                       (0x0080)        /* Enabled. USS (and sub modules) logic held in reset state */
#define USSSWRST_1_L                     (0x0080)




#define GENERIC_SAPH_IIDX                                  (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0000))
#define GENERIC_SAPH_MIS                                   (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0002))
#define GENERIC_SAPH_RIS                                   (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0004))
#define GENERIC_SAPH_IMSC                                  (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0006))
#define GENERIC_SAPH_ICR                                   (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0008))
#define GENERIC_SAPH_ISR                                   (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x000A))
#define GENERIC_SAPH_DESCLO                                (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x000C))
#define GENERIC_SAPH_DESCHI                                (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x000E))
#define GENERIC_SAPH_KEY                                   (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0010))
#define GENERIC_SAPH_OCTL0                                 (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0012))
#define GENERIC_SAPH_OCTL1                                 (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0014))
#define GENERIC_SAPH_OSEL                                  (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0016))
#define GENERIC_SAPH_CH0PUT                                (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0020))
#define GENERIC_SAPH_CH0PDT                                (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0022))
#define GENERIC_SAPH_CH0TT                                 (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0024))
#define GENERIC_SAPH_CH1PUT                                (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0026))
#define GENERIC_SAPH_CH1PDT                                (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0028))
#define GENERIC_SAPH_CH1TT                                 (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x002A))
#define GENERIC_SAPH_MCNF                                  (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x002C))
#define GENERIC_SAPH_TACTL                                 (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x002E))
#define GENERIC_SAPH_ICTL0                                 (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0030))
#define GENERIC_SAPH_BCTL                                  (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0034))
#define GENERIC_SAPH_PGC                                   (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0040))
#define GENERIC_SAPH_LP_E_PULS                              (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0042))
#define GENERIC_SAPH_HP_E_PULS                              (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0044))
#define GENERIC_SAPH_PGCTL                                 (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0046))
#define GENERIC_SAPH_PPGTRIG                               (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0048))
#ifdef __MSP430_BASEADDRESS_SAPH_A__
#define GENERIC_SAPH_XPGCTL                                 (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x004A))
#define GENERIC_SAPH_LP_X_PULS                              (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x004C))
#define GENERIC_SAPH_HP_X_PULS                              (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x004E))
#endif
#define GENERIC_SAPH_ASCTL0                                (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0060))
#define GENERIC_SAPH_ASCTL1                                (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0062))
#define GENERIC_SAPH_ASQTRIG                               (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0064))
#define GENERIC_SAPH_APOL                                  (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0066))
#define GENERIC_SAPH_APLEV                                 (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0068))
#define GENERIC_SAPH_APHIZ                                 (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x006A))
#define GENERIC_SAPH_ATM_A                                 (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x006E))
#define GENERIC_SAPH_ATM_B                                 (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0070))
#define GENERIC_SAPH_ATM_C                                 (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0072))
#define GENERIC_SAPH_ATM_D                                 (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0074))
#define GENERIC_SAPH_ATM_E                                 (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0076))
#define GENERIC_SAPH_ATM_F                                 (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x0078))
#define GENERIC_SAPH_TBCTL                                 (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x007A))
#define GENERIC_SAPH_ATIMLO                                (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x007C))
#define GENERIC_SAPH_ATIMHI                                (*(int *)(__MSP430_BASEADDRESS_GENERIC_SAPH__ + 0x007E))



#endif
