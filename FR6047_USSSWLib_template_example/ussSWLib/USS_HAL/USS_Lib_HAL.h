/* --COPYRIGHT--,TI
 *MSP Source and Object Code Software License Agreement
 *
 *
 **IMPORTANT - PLEASE CAREFULLY READ THE FOLLOWING LICENSE AGREEMENT, WHICH IS LEGALLY BINDING.  AFTER YOU READ IT, YOU WILL BE ASKED WHETHER YOU ACCEPT AND AGREE TO ITS TERMS.  DO NOT CLICK  "I ACCEPT" UNLESS: (1) YOU WILL USE THE LICENSED MATERIALS FOR YOUR OWN BENEFIT AND PERSONALLY ACCEPT, AGREE TO AND INTEND TO BE BOUND BY THESE TERMS; OR (2) YOU ARE AUTHORIZED TO, AND INTEND TO BE BOUND BY, THESE TERMS ON BEHALF OF YOUR COMPANY.
 *
 *
 **Important - Read carefully: This Source and Object Code Software License Agreement ("Agreement") is a legal agreement between you and Texas Instruments Incorporated ("TI").  In this Agreement "you" means you personally if you will exercise the rights granted for your own benefit, but it means your company (or you on behalf of your company) if you will exercise the rights granted for your company's benefit.  The "Licensed Materials" subject to this Agreement include the software programs and any associated electronic documentation (in each case, in whole or in part) that accompany this Agreement, are set forth in the applicable software manifest and you access "on-line", as well as any updates or upgrades to such software programs or documentation, if any, provided to you at TI's sole discretion.  The Licensed Materials are specifically designed and licensed for use solely and exclusively with MSP microcontroller devices manufactured by or for TI ("TI Devices").  By installing, copying or otherwise using the Licensed Materials you agree to abide by the provisions set forth herein.  This Agreement is displayed for you to read prior to using the Licensed Materials.  If you choose not to accept or agree with these provisions, do not download or install the Licensed Materials.
 *
 **Note Regarding Possible Access to Other Licensed Materials:  The Licensed Materials may be bundled with software and associated electronic documentation, if any, licensed under terms other than the terms of this Agreement (in whole or in part, "Other Licensed Materials"), including, for example Open Source Software and/or TI-owned or third party Proprietary Software licensed under such other terms.  "Open Source Software" means any software licensed under terms requiring that (A) other software ("Proprietary Software") incorporated, combined or distributed with such software or developed using such software: (i) be disclosed or distributed in source code form; or (ii) otherwise be licensed on terms inconsistent with the terms of this Agreement, including but not limited to permitting use of the Proprietary Software on or with devices other than TI Devices, or (B) require the owner of Proprietary Software to license any of its patents to users of the Open Source Software and/or Proprietary Software incorporated, combined or distributed with such Open Source Software or developed using such Open Source Software.
 *
 **If by accepting this Agreement, you gain access to Other Licensed Materials, they will be listed in the applicable software manifest.  Your use of the Other Licensed Materials is subject to the applicable other licensing terms acknowledgements and disclaimers as specified in the applicable software manifest and/or identified or included with the Other Licensed Materials in the software bundle.  For clarification, this Agreement does not limit your rights under, or grant you rights that supersede, the terms of any applicable Other Licensed Materials license agreement.  If any of the Other Licensed Materials is Open Source Software that has been provided to you in object code only under terms that obligate TI to provide to you or show you where you can access the source code versions of such Open Source Software, TI will provide to you, or show you where you can access, such source code if you contact TI at Texas Instruments Incorporated, 12500 TI Boulevard, Mail Station 8638, Dallas, Texas 75243, Attention: Contracts Manager, Embedded Processing.  In the event you choose not to accept or agree with the terms in any applicable Other Licensed Materials license agreement, you must terminate this Agreement.
 *
 **1.    License Grant and Use Restrictions.
 *
 **a.    Licensed Materials License Grant.  Subject to the terms of this Agreement, TI hereby grants to you a limited, non-transferable, non-exclusive, non-assignable, non-sublicensable, fully paid-up and royalty-free license to:
 *
 *            i.    Limited Source Code License:  make copies, prepare derivative works, display internally and use internally the Licensed Materials provided to you in source code for the sole purpose of developing object and executable versions of such Licensed Materials, or any derivative thereof, that execute solely and exclusively on TI Devices, for end use in Licensee Products, and maintaining and supporting such Licensed Materials, or any derivative thereof, and Licensee Products.  For purposes of this Agreement, "Licensee Product" means a product that consists of both hardware, including one or more TI Devices, and software components, including only executable versions of the Licensed Materials that execute solely and exclusively on such TI Devices.
 *
 *            ii.    Object Code Evaluation, Testing and Use License:  make copies, display internally, distribute internally and use internally the Licensed Materials in object code for the sole purposes of evaluating and testing the Licensed Materials and designing and developing Licensee Products, and maintaining and supporting the Licensee Products;
 *
 *            iii.    Demonstration License:  demonstrate to third parties the Licensed Materials executing solely and exclusively on TI Devices as they are used in Licensee Products, provided that such Licensed Materials are demonstrated in object or executable versions only and
 *
 *        iv.    Production and Distribution License:  make, use, import, export and otherwise distribute the Licensed Materials as part of a Licensee Product, provided that such Licensee Products include only embedded executable copies of such Licensed Materials that execute solely and exclusively on TI Devices.
 *
 *    b.    Contractors.  The licenses granted to you hereunder shall include your on-site and off-site contractors (either an individual or entity), while such contractors are performing work for or providing services to you, provided that such contractors have executed work-for-hire agreements with you containing applicable terms and conditions consistent with the terms and conditions set forth in this Agreement and provided further that you shall be liable to TI for any breach by your contractors of this Agreement to the same extent as you would be if you had breached the Agreement yourself.
 *
 *    c.    No Other License.  Nothing in this Agreement shall be construed as a license to any intellectual property rights of TI other than those rights embodied in the Licensed Materials provided to you by TI.  EXCEPT AS PROVIDED HEREIN, NO OTHER LICENSE, EXPRESS OR IMPLIED, BY ESTOPPEL OR OTHERWISE, TO ANY OTHER TI INTELLECTUAL PROPERTY RIGHTS IS GRANTED HEREIN.
 *
 *    d.    Covenant not to Sue.  During the term of this Agreement, you agree not to assert a claim against TI or its licensees that the Licensed Materials infringe your intellectual property rights.
 *
 *    e.    Restrictions.  You shall maintain the source code versions of the Licensed Materials under password control protection and shall not disclose such source code versions of the Licensed Materials, to any person other than your employees and contractors whose job performance requires access.  You shall not use the Licensed Materials with a processing device other than a TI Device, and you agree that any such unauthorized use of the Licensed Materials is a material breach of this Agreement.  You shall not use the Licensed Materials for the purpose of analyzing or proving infringement of any of your patents by either TI or TI's customers.  Except as expressly provided in this Agreement, you shall not copy, publish, disclose, display, provide, transfer or make available the Licensed Materials to any third party and you shall not sublicense, transfer, or assign the Licensed Materials or your rights under this Agreement to any third party.  You shall not mortgage, pledge or encumber the Licensed Materials in any way.  You may use the Licensed Materials with Open Source Software or with software developed using Open Source Software tools provided you do not incorporate, combine or distribute the Licensed Materials in a manner that subjects the Licensed Materials to any license obligations or any other intellectual property related terms of any license governing such Open Source Software.
 *
 *    f.    Termination.  This Agreement is effective on the date the Licensed Materials are delivered to you together with this Agreement and will remain in full force and effect until terminated.  You may terminate this Agreement at any time by written notice to TI.  Without prejudice to any other rights, if you fail to comply with the terms of this Agreement or you are acquired, TI may terminate your right to use the Licensed Materials upon written notice to you.  Upon termination of this Agreement, you will destroy any and all copies of the Licensed Materials in your possession, custody or control and provide to TI a written statement signed by your authorized representative certifying such destruction. Except for Sections 1(a), 1(b) and 1(d), all provisions of this Agreement shall survive termination of this Agreement.
 *
 **2.    Licensed Materials Ownership.  The Licensed Materials are licensed, not sold to you, and can only be used in accordance with the terms of this Agreement.  Subject to the licenses granted to you pursuant to this Agreement, TI and its licensors own and shall continue to own all right, title and interest in and to the Licensed Materials, including all copies thereof.  You agree that all fixes, modifications and improvements to the Licensed Materials conceived of or made by TI that are based, either in whole or in part, on your feedback, suggestions or recommendations are the exclusive property of TI and all right, title and interest in and to such fixes, modifications or improvements to the Licensed Materials will vest solely in TI.  Moreover, you acknowledge and agree that when your independently developed software or hardware components are combined, in whole or in part, with the Licensed Materials, your right to use the combined work that includes the Licensed Materials remains subject to the terms and conditions of this Agreement.
 *
 **3.    Intellectual Property Rights.
 *
 *    a.    The Licensed Materials contain copyrighted material, trade secrets and other proprietary information of TI and its licensors and are protected by copyright laws, international copyright treaties, and trade secret laws, as well as other intellectual property laws.  To protect TI's and its licensors' rights in the Licensed Materials, you agree, except as specifically permitted by statute by a provision that cannot be waived by contract, not to "unlock", decompile, reverse engineer, disassemble or otherwise translate to a human-perceivable form any portions of the Licensed Materials provided to you in object code format only, nor permit any person or entity to do so.  You shall not remove, alter, cover, or obscure any confidentiality, trade secret, trade mark, patent, copyright or other proprietary notice or other identifying marks or designs from any component of the Licensed Materials and you shall reproduce and include in all copies of the Licensed Materials the copyright notice(s) and proprietary legend(s) of TI and its licensors as they appear in the Licensed Materials.  TI reserves all rights not specifically granted under this Agreement.
 *
 *    b.    Certain Licensed Materials may be based on industry recognized standards or software programs published by industry recognized standards bodies and certain third parties may claim to own patents, copyrights, and other intellectual property rights that cover implementation of those standards.  You acknowledge and agree that this Agreement does not convey a license to any such third party patents, copyrights, and other intellectual property rights and that you are solely responsible for any patent, copyright, or other intellectual property right claim that relates to your use or distribution of the Licensed Materials or your use or distribution of your products that include or incorporate the Licensed Materials.  Moreover, you acknowledge that you are responsible for any fees or royalties that may be payable to any third party based on such third party's interests in the Licensed Materials or any intellectual property rights that cover implementation of any industry recognized standard, any software program published by any industry recognized standards bodies or any other proprietary technology.
 *
 **4.    Confidential Information.  You acknowledge and agree that the Licensed Materials contain trade secrets and other confidential information of TI and its licensors.  You agree to use the Licensed Materials solely within the scope of the licenses set forth herein, to maintain the Licensed Materials in strict confidence, to use at least the same procedures and degree of care that you use to prevent disclosure of your own confidential information of like importance but in no instance less than reasonable care, and to prevent disclosure of the Licensed Materials to any third party, except as may be necessary and required in connection with your rights and obligations hereunder; provided, however, that you may not provide the Licensed Materials to any business organization or group within your company or to customers or contractors that design or manufacture semiconductors unless TI gives written consent.  You agree to obtain executed confidentiality agreements with your employees and contractors having access to the Licensed Materials and to diligently take steps to enforce such agreements in this respect.  TI may disclose your contact information to TI's licensors.
 *
 **5.    Warranties and Limitations.  THE LICENSED MATERIALS ARE PROVIDED "AS IS".  FURTHERMORE, YOU ACKNOWLEDGE AND AGREE THAT THE LICENSED MATERIALS HAVE NOT BEEN TESTED OR CERTIFIED BY ANY GOVERNMENT AGENCY OR INDUSTRY REGULATORY ORGANIZATION OR ANY OTHER THIRD PARTY ORGANIZATION.  YOU AGREE THAT PRIOR TO USING, INCORPORATING OR DISTRIBUTING THE LICENSED MATERIALS IN OR WITH ANY COMMERCIAL PRODUCT THAT YOU WILL THOROUGHLY TEST THE PRODUCT AND THE FUNCTIONALITY OF THE LICENSED MATERIALS IN OR WITH THAT PRODUCT AND BE SOLELY RESPONSIBLE FOR ANY PROBLEMS OR FAILURES.
 *
 **TI AND ITS LICENSORS MAKE NO WARRANTY OR REPRESENTATION, EITHER EXPRESS, IMPLIED OR STATUTORY, REGARDING THE LICENSED MATERIALS, INCLUDING BUT NOT LIMITED TO ANY IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT OF ANY THIRD PARTY PATENTS, COPYRIGHTS, TRADE SECRETS OR OTHER INTELLECTUAL PROPERTY RIGHTS.  YOU AGREE TO USE YOUR INDEPENDENT JUDGMENT IN DEVELOPING YOUR PRODUCTS.  NOTHING CONTAINED IN THIS AGREEMENT WILL BE CONSTRUED AS A WARRANTY OR REPRESENTATION BY TI TO MAINTAIN PRODUCTION OF ANY TI SEMICONDUCTOR DEVICE OR OTHER HARDWARE OR SOFTWARE WITH WHICH THE LICENSED MATERIALS MAY BE USED.
 *
 **IN NO EVENT SHALL TI OR ITS LICENSORS, BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL, PUNITIVE OR CONSEQUENTIAL DAMAGES, HOWEVER CAUSED, ON ANY THEORY OF LIABILITY, IN CONNECTION WITH OR ARISING OUT OF THIS AGREEMENT OR THE USE OF THE LICENSED MATERIALS REGARDLESS OF WHETHER TI HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  EXCLUDED DAMAGES INCLUDE, BUT ARE NOT LIMITED TO, COST OF REMOVAL OR REINSTALLATION, OUTSIDE COMPUTER TIME, LABOR COSTS, LOSS OF DATA, LOSS OF GOODWILL, LOSS OF PROFITS, LOSS OF SAVINGS, OR LOSS OF USE OR INTERRUPTION OF BUSINESS.  IN NO EVENT WILL TI'S OR ITS LICENSORS' AGGREGATE LIABILITY UNDER THIS AGREEMENT OR ARISING OUT OF YOUR USE OF THE LICENSED MATERIALS EXCEED FIVE HUNDRED U.S. DOLLARS (US$500).
 *
 *    Because some jurisdictions do not allow the exclusion or limitation of incidental or consequential damages or limitation on how long an implied warranty lasts, the above limitations or exclusions may not apply to you.
 *
 **6.    Indemnification Disclaimer.  YOU ACKNOWLEDGE AND AGREE THAT TI SHALL NOT BE LIABLE FOR AND SHALL NOT DEFEND OR INDEMNIFY YOU AGAINST ANY THIRD PARTY INFRINGEMENT CLAIM THAT RELATES TO OR IS BASED ON YOUR MANUFACTURE, USE, OR DISTRIBUTION OF THE LICENSED MATERIALS OR YOUR MANUFACTURE, USE, OFFER FOR SALE, SALE, IMPORTATION OR DISTRIBUTION OF YOUR PRODUCTS THAT INCLUDE OR INCORPORATE THE LICENSED MATERIALS.
 *
 **7.    No Technical Support.  TI and its licensors are under no obligation to install, maintain or support the Licensed Materials.
 *
 **8.    Notices.  All notices to TI hereunder shall be delivered to Texas Instruments Incorporated, 12500 TI Boulevard, Mail Station 8638, Dallas, Texas 75243, Attention: Contracts Manager - Embedded Processing, with a copy to Texas Instruments Incorporated, 13588 N. Central Expressway, Mail Station 3999, Dallas, Texas 75243, Attention: Law Department - Embedded Processing.  All notices shall be deemed served when received by TI.
 *
 **9.    Export Control.  The Licensed Materials are subject to export control under the U.S. Commerce Department's Export Administration Regulations ("EAR").  Unless prior authorization is obtained from the U.S. Commerce Department, neither you nor your subsidiaries shall export, re-export, or release, directly or indirectly (including, without limitation, by permitting the Licensed Materials to be downloaded), any technology, software, or software source code, received from TI, or export, directly or indirectly, any direct product of such technology, software, or software source code, to any person, destination or country to which the export, re-export, or release of the technology, software, or software source code, or direct product is prohibited by the EAR.  You represent and warrant that you (i) are not located in, or under the control of, a national or resident of Cuba, Iran, North Korea, Sudan and Syria or any other country subject to a U.S. goods embargo; (ii) are not on the U.S. Treasury Department's List of Specially Designated Nationals or the U.S. Commerce Department's Denied Persons List or Entity List; and (iii) will not use the Licensed Materials or transfer the Licensed Materials for use in any military, nuclear, chemical or biological weapons, or missile technology end-uses.  Any software export classification made by TI shall not be construed as a representation or warranty regarding the proper export classification for such software or whether an export license or other documentation is required for the exportation of such software.
 *
 **10.    Governing Law and Severability; Waiver.  This Agreement will be governed by and interpreted in accordance with the laws of the State of Texas, without reference to conflict of laws principles.  If for any reason a court of competent jurisdiction finds any provision of the Agreement to be unenforceable, that provision will be enforced to the maximum extent possible to effectuate the intent of the parties, and the remainder of the Agreement shall continue in full force and effect.  This Agreement shall not be governed by the United Nations Convention on Contracts for the International Sale of Goods, or by the Uniform Computer Information Transactions Act (UCITA).  The parties agree that non-exclusive jurisdiction for any dispute arising out of or relating to this Agreement lies within the courts located in the State of Texas.  Notwithstanding the foregoing, any judgment may be enforced in any United States or foreign court, and either party may seek injunctive relief in any United States or foreign court.  Failure by TI to enforce any provision of this Agreement shall not be deemed a waiver of future enforcement of that or any other provision in this Agreement or any other agreement that may be in place between the parties.
 *
 **11.    PRC Provisions.  If you are located in the People's Republic of China ("PRC") or if the Licensed Materials will be sent to the PRC, the following provisions shall apply:
 *
 *    a.    Registration Requirements.  You shall be solely responsible for performing all acts and obtaining all approvals that may be required in connection with this Agreement by the government of the PRC, including but not limited to registering pursuant to, and otherwise complying with, the PRC Measures on the Administration of Software Products, Management Regulations on Technology Import-Export, and Technology Import and Export Contract Registration Management Rules.  Upon receipt of such approvals from the government authorities, you shall forward evidence of all such approvals to TI for its records.  In the event that you fail to obtain any such approval or registration, you shall be solely responsible for any and all losses, damages or costs resulting therefrom, and shall indemnify TI for all such losses, damages or costs.
 *
 **b.    Governing Language.  This Agreement is written and executed in the English language and shall be authoritative and controlling, whether or not translated into a language other than English to comply with law or for reference purposes.  If a translation of this Agreement is required for any purpose, including but not limited to registration of the Agreement pursuant to any governmental laws, regulations or rules, you shall be solely responsible for creating such translation.
 *
 **12.    Contingencies.    TI shall not be in breach of this Agreement and shall not be liable for any non-performance or delay in performance if such non-performance or delay is due to a force majeure event or other circumstances beyond TI's reasonable control.
 *
 **13.        Entire Agreement.  This is the entire agreement between you and TI and this Agreement supersedes any prior agreement between the parties related to the subject matter of this Agreement.  Notwithstanding the foregoing, any signed and effective software license agreement relating to the subject matter hereof and stating expressly that such agreement shall control regardless of any subsequent click-wrap, shrink-wrap or web-wrap, shall supersede the terms of this Agreement.  No amendment or modification of this Agreement will be effective unless in writing and signed by a duly authorized representative of TI.  You hereby warrant and represent that you have obtained all authorizations and other applicable consents required empowering you to enter into this Agreement.
 *
 *
 *
 * --/COPYRIGHT--*/

#ifndef USS_HAL_USS_LIB_HAL_H_
#define USS_HAL_USS_LIB_HAL_H_

#include <msp430.h>
#include "ussSwLib.h"


//! \brief Selects the desired power mode while USS capture is done, API will
//! remain in this mode until capture is done.
//!
typedef enum _USSLIB_HAL_capture_mode_
{
    USSLIB_HAL_capture_mode_ups = 0,
    USSLIB_HAL_capture_mode_dns,
} USSLIB_HAL_capture_mode;


#if ((__EVM430_ID__ == 0x43) && (defined(__AFE_EXT_3v3__) || defined(__AFE_EXT_5v0__)))
#define USSSWLIB_ENABLE_EXTERNAL_CIRCUITRY_CONTROL                      true
#else
#define USSSWLIB_ENABLE_EXTERNAL_CIRCUITRY_CONTROL                      false
#endif

#define ENABLE_USS_LIB_BENCHMARK                                        false

#define USSSWLIB_TIMER_BASE_ADDRESS                              (TIMER_A1_BASE)


#if (USSSWLIB_ENABLE_EXTERNAL_CIRCUITRY_CONTROL == true)
#if ((__EVM430_ID__ == 0x43) && (defined(__AFE_EXT_3v3__) || defined(__AFE_EXT_5v0__)))
/******************************************************************************
 * External Circuitry Control signals
 ******************************************************************************/
#define USSSWLIB_HAL_RXEN_TIMER_BASE_ADDRESS                    (TIMER_A0_BASE)

#if(USSSWLIB_HAL_RXEN_TIMER_BASE_ADDRESS == TIMER_A0_BASE)
// Defines for RxEn control lines
// RxEn -> P6.7
#define USSSWLIB_HAL_AFE_RXEN_PORT                                  P6OUT
#define USSSWLIB_HAL_AFE_RXEN_PORT_DIR                              P6DIR
#define USSSWLIB_HAL_AFE_RXEN_PIN                                    BIT7
#else
#error "Define RxEn GPIO configurations"
// Defines for RxEn control lines
// RxEn -> Px.y
#define USSSWLIB_HAL_AFE_RXEN_PORT                                  PxOUT
#define USSSWLIB_HAL_AFE_RXEN_PORT_DIR                              PxDIR
#define USSSWLIB_HAL_AFE_RXEN_PORT_SEL0                             PxSEL0
#define USSSWLIB_HAL_AFE_RXEN_PORT_SEL1                             PxSEL1
#define USSSWLIB_HAL_AFE_RXEN_PIN                                    BITy
#endif

// Defines for RxSel1 and RxSel2 control lines
// RxSel1 -> P3.6
// RxSel2 -> P3.7
#define USSSWLIB_HAL_AFE_RX_SELx_PORT                              P3OUT
#define USSSWLIB_HAL_AFE_RX_SELx_PORT_DIR                          P3DIR
#define USSSWLIB_HAL_AFE_RX_SEL1_PIN                               BIT6
#define USSSWLIB_HAL_AFE_RX_SEL2_PIN                               BIT7

// Defines for RxPwr control lines
// RxPwr -> P2.2
#define USSSWLIB_HAL_AFE_RXPWR_PORT                                  P2OUT
#define USSSWLIB_HAL_AFE_RXPWR_PORT_DIR                              P2DIR
#define USSSWLIB_HAL_AFE_RXPWR_PIN                                   BIT2

#if (__EVM430_VER__ == 0x20)
// Defines for TxPwr control lines
// TxPwr -> P1.0
#define USSSWLIB_HAL_AFE_TXPWR_PORT                                  P1OUT
#define USSSWLIB_HAL_AFE_TXPWR_PORT_DIR                              P1DIR
#define USSSWLIB_HAL_AFE_TXPWR_PIN                                   BIT0

#if defined(__AFE_EXT_5v0__)
// Defines for Tx5VEn control line
// Tx5VEn -> P1.1
#define USSSWLIB_HAL_AFE_TX5VEN_PORT                                  P1OUT
#define USSSWLIB_HAL_AFE_TX5VEN_PORT_DIR                              P1DIR
#define USSSWLIB_HAL_AFE_TX5VEN_PIN                                   BIT1

#warning "Please confirm jumpers JP1 and JP2 are properly configured before \
    using EVM in 5V mode. "
#endif

#endif

#if ENABLE_USS_LIB_BENCHMARK
#warning "Benchmarking has been enabled. Make sure Benchmark pin doesn't\
 conflict with board configuration"
#define USSSWLIB_HAL_BENCHMARK_PORT                                  P1OUT
#define USSSWLIB_HAL_BENCHMARK_PORT_DIR                              P1DIR
#define USSSWLIB_HAL_BENCHMARK_PIN                                   BIT5
#endif
#else
#error "USSLib HAL external circuitry control not supported or defined for EVM configuration"
#endif  // (__EVM430_ID__ == 0x43) && (defined(__AFE_EXT_3v3__) || defined(__AFE_EXT_5v0__)))

#if(USSSWLIB_HAL_RXEN_TIMER_BASE_ADDRESS == USSSWLIB_TIMER_BASE_ADDRESS)
#error "USSSWLIB_HAL_RXEN_TIMER_BASE_ADDRESS cannot be the same base address\
as USSSWLIB_TIMER_BASE_ADDRESS"
#endif

#if (USSSWLIB_HAL_RXEN_TIMER_BASE_ADDRESS == TIMER_A0_BASE)
#define USSLIB_HAL_TIMER_RXEN_CCR0_VECTOR         (TIMER0_A0_VECTOR)
#define USSLIB_HAL_TIMER_RXEN_CCR1_VECTOR         (TIMER0_A1_VECTOR)
#elif (USSSWLIB_HAL_RXEN_TIMER_BASE_ADDRESS==TIMER_A1_BASE)
#define USSLIB_HAL_TIMER_RXEN_CCR0_VECTOR         (TIMER1_A0_VECTOR)
#define USSLIB_HAL_TIMER_RXEN_CCR1_VECTOR         (TIMER1_A1_VECTOR)
#elif (USSSWLIB_HAL_RXEN_TIMER_BASE_ADDRESS==TIMER_A2_BASE)
#define USSLIB_HAL_TIMER_RXEN_CCR0_VECTOR         (TIMER2_A0_VECTOR)
#define USSLIB_HAL_TIMER_RXEN_CCR1_VECTOR         (TIMER2_A1_VECTOR)
#elif (USSSWLIB_HAL_RXEN_TIMER_BASE_ADDRESS==TIMER_A3_BASE)
#define USSLIB_HAL_TIMER_RXEN_CCR0_VECTOR         (TIMER3_A0_VECTOR)
#define USSLIB_HAL_TIMER_RXEN_CCR1_VECTOR         (TIMER3_A1_VECTOR)
#elif (USSSWLIB_HAL_RXEN_TIMER_BASE_ADDRESS==TIMER_A4_BASE)
#define USSLIB_HAL_TIMER_RXEN_CCR0_VECTOR         (TIMER4_A0_VECTOR)
#define USSLIB_HAL_TIMER_RXEN_CCR1_VECTOR         (TIMER4_A1_VECTOR)
#else
#error INVALID_TIMER_SELECTION
#endif

#endif  // (USSSWLIB_ENABLE_EXTERNAL_CIRCUITRY_CONTROL == true)

#if(USSSWLIB_ENABLE_EXTERNAL_CIRCUITRY_CONTROL == true)
#if (__EVM430_ID__ == 0x47)
#error "USSLib HAL external circuitry control not supported or defined for EVM configuration"
#endif
#endif // USSSWLIB_ENABLE_EXTERNAL_CIRCUITRY_CONTROL




//******************************************************************************
// Defines LEA_START_ADDRESS for MSP430FR6047 and MSP430FR60430 device variant
// For MSP430FR6047 device variants LEA START address is 0x2C00
// For MSP430FR6043 device variants LEA START address is 0x4000
//
// Please refer the device specific datasheet for more details regarding
// the device memory organization
//
//******************************************************************************
#if defined (__MSP430FR6043__) || defined (__MSP430FR60431__)   ||     \
      defined (__MSP430FR6041__) || defined (__MSP430FR50431__) ||     \
      defined (__MSP430FR50431__) || defined (__MSP430FR5043__) ||     \
      defined (__MSP430FR5041__)
#define USS_HAL_LEA_START_ADDRESS                       (0x4000)
#elif defined (__MSP430FR6005__) || defined (__MSP430FR6007__)    ||   \
     defined (__MSP430FR6035__) || defined (__MSP430FR6037__)     ||   \
     defined (__MSP430FR60371__) || defined (__MSP430FR6045__)    ||   \
     defined (__MSP430FR6047__) || defined (__MSP430FR60471__)
#define USS_HAL_LEA_START_ADDRESS                       (0x2C00)
#else
#error "Device not supported"
#endif


#if (USSSWLIB_TIMER_BASE_ADDRESS==TIMER_A0_BASE)
#define USSLIB_HAL_TIMER_CCR0_VECTOR         (TIMER0_A0_VECTOR)
#define USSLIB_HAL_TIMER_CCR1_VECTOR         (TIMER0_A1_VECTOR)
#elif (USSSWLIB_TIMER_BASE_ADDRESS==TIMER_A1_BASE)
#define USSLIB_HAL_TIMER_CCR0_VECTOR         (TIMER1_A0_VECTOR)
#define USSLIB_HAL_TIMER_CCR1_VECTOR         (TIMER1_A1_VECTOR)
#elif (USSSWLIB_TIMER_BASE_ADDRESS==TIMER_A2_BASE)
#define USSLIB_HAL_TIMER_CCR0_VECTOR         (TIMER2_A0_VECTOR)
#define USSLIB_HAL_TIMER_CCR1_VECTOR         (TIMER2_A1_VECTOR)
#elif (USSSWLIB_TIMER_BASE_ADDRESS==TIMER_A3_BASE)
#define USSLIB_HAL_TIMER_CCR0_VECTOR         (TIMER3_A0_VECTOR)
#define USSLIB_HAL_TIMER_CCR1_VECTOR         (TIMER3_A1_VECTOR)
#elif (USSSWLIB_TIMER_BASE_ADDRESS==TIMER_A4_BASE)
#define USSLIB_HAL_TIMER_CCR0_VECTOR         (TIMER4_A0_VECTOR)
#define USSLIB_HAL_TIMER_CCR1_VECTOR         (TIMER4_A1_VECTOR)
#else
#error INVALID_TIMER_SELECTION
#endif


#if defined(__TI_COMPILER_VERSION__)
#define _PRAGMA(x) _Pragma (#x)
#define USS_HAL_LEA_DATA(var,align) _PRAGMA(DATA_SECTION(var,".leaRAM"))\
                                    _PRAGMA(DATA_ALIGN(var,(align)))

#define USS_TONE_CONFIG_DATA(var) _PRAGMA(DATA_SECTION(var,".ram_thrill"))

#elif defined(__IAR_SYSTEMS_ICC__)
#define _PRAGMA(x) _Pragma (#x)
#define USS_HAL_LEA_DATA(var,align) _PRAGMA(location="LEARAM")\
                                _PRAGMA(data_alignment=align)

#define USS_TONE_CONFIG_DATA(var) _PRAGMA(location="RAM_THRILL")

#elif defined(__GNUC__)
#define USS_HAL_LEA_DATA(var,align) __attribute__((section(".leaRAM")))\
                                __attribute__((aligned(align)))

#define USS_TONE_CONFIG_DATA(var) __attribute__((section("ram_thrill")))
#else
#define USS_HAL_LEA_DATA(var,align)
#endif

extern volatile uint16_t USS_LEA_IFG;

//! \brief Contains function callback pointer for USS SAPH DATAERR
//!
extern void (*USSSWLIB_SAPH_DATAERR_callback)(void);
//! \brief Contains function callback pointer for USS SAPH TMFTO
//!
extern void (*USSSWLIB_SAPH_TMFTO_callback)(void);
//! \brief Contains function callback pointer for USS SAPH SEQDN
//!
extern void (*USSSWLIB_SAPH_SEQDN_callback)(void);
//! \brief Contains function callback pointer for USS SAPH PNGDN
//!
extern void (*USSSWLIB_SAPH_PNGDN_callback)(void);
//! \brief Contains function callback pointer for USS UUPS PREQIG
//!
extern void (*USSSWLIB_UUPS_PREQIG_callback)(void);
//! \brief Contains function callback pointer for USS UUPS_PTMOUT
//!
extern void (*USSSWLIB_UUPS_PTMOUT_callback)(void);
//! \brief Contains function callback pointer for USS UUPS_STPBYDB
//!
extern void (*USSSWLIB_UUPS_STPBYDB_callback)(void);
//! \brief Contains function callback pointer for USS HSPLL_UNLOCK
//!
extern void (*USSSWLIB_HSPLL_PLLunlock_callback)(void);
//! \brief Contains function callback pointer for USS_SDHS_OVF
//!
extern void (*USSSWLIB_SDHS_OVF_callback)(void);
//! \brief Contains function callback pointer for USS_SDHS_OVINLVL
//!
extern void (*USSSWLIB_SDHS_ACQDONE_callback)(void);
//! \brief Contains function callback pointer for USS_SDHS_SSTRG
//!
extern void (*USSSWLIB_SDHS_SSTRG_callback)(void);
//! \brief Contains function callback pointer for USS_SDHS_DTRDY
//!
extern void (*USSSWLIB_SDHS_DTRDY_callback)(void);
//! \brief Contains function callback pointer for USS_SDHS_WINHI
//!
extern void (*USSSWLIB_SDHS_WINHI_callback)(void);
//! \brief Contains function callback pointer for USS_SDHS_WINLO
//!
extern void (*USSSWLIB_SDHS_WINLO_callback)(void);


#if(USSSWLIB_ENABLE_EXTERNAL_CIRCUITRY_CONTROL == true)
//! \brief function to initialize GPIOs used by USS Library
//!
extern void USSLIB_HAL_initGPIO(void);

//! \brief function to configure capture gpios
//!
extern void USSLIB_HAL_configGPIOForCapture(USSLIB_HAL_capture_mode mode);

//! \brief function to configure Timer used to control RxEn AFE pin state
//!
extern void USSLIB_HAL_configureRxEnTimer(uint16_t ASQTimerCounts,
                                          uint16_t RxEnTimerCounts);

//! \brief function to start Timer used to control RxEn AFE pin state
//!
extern void USSLIB_HAL_startRxEnTimer(void);

//! \brief function to configure GPIOs after acquisition
extern void USSLIB_HAL_configGPIOAfterCapture(void);

#endif

#endif /* USS_HAL_USS_LIB_HAL_H_ */

