/* --COPYRIGHT--,TI
   *MSP Source and Object Code Software License Agreement
 *
 *
 ***IMPORTANT - PLEASE CAREFULLY READ THE FOLLOWING LICENSE AGREEMENT, WHICH IS LEGALLY BINDING.  AFTER YOU READ IT, YOU WILL BE ASKED WHETHER YOU ACCEPT AND AGREE TO ITS TERMS.  DO NOT CLICK  "I ACCEPT" UNLESS: (1) YOU WILL USE THE LICENSED MATERIALS FOR YOUR OWN BENEFIT AND PERSONALLY ACCEPT, AGREE TO AND INTEND TO BE BOUND BY THESE TERMS; OR (2) YOU ARE AUTHORIZED TO, AND INTEND TO BE BOUND BY, THESE TERMS ON BEHALF OF YOUR COMPANY.
 *
 *
 ***Important - Read carefully: This Source and Object Code Software License Agreement ("Agreement") is a legal agreement between you and Texas Instruments Incorporated ("TI").  In this Agreement "you" means you personally if you will exercise the rights granted for your own benefit, but it means your company (or you on behalf of your company) if you will exercise the rights granted for your company's benefit.  The "Licensed Materials" subject to this Agreement include the software programs and any associated electronic documentation (in each case, in whole or in part) that accompany this Agreement, are set forth in the applicable software manifest and you access "on-line", as well as any updates or upgrades to such software programs or documentation, if any, provided to you at TI's sole discretion.  The Licensed Materials are specifically designed and licensed for use solely and exclusively with MSP microcontroller devices manufactured by or for TI ("TI Devices").  By installing, copying or otherwise using the Licensed Materials you agree to abide by the provisions set forth herein.  This Agreement is displayed for you to read prior to using the Licensed Materials.  If you choose not to accept or agree with these provisions, do not download or install the Licensed Materials.
 *
 ***Note Regarding Possible Access to Other Licensed Materials:  The Licensed Materials may be bundled with software and associated electronic documentation, if any, licensed under terms other than the terms of this Agreement (in whole or in part, "Other Licensed Materials"), including, for example Open Source Software and/or TI-owned or third party Proprietary Software licensed under such other terms.  "Open Source Software" means any software licensed under terms requiring that (A) other software ("Proprietary Software") incorporated, combined or distributed with such software or developed using such software: (i) be disclosed or distributed in source code form; or (ii) otherwise be licensed on terms inconsistent with the terms of this Agreement, including but not limited to permitting use of the Proprietary Software on or with devices other than TI Devices, or (B) require the owner of Proprietary Software to license any of its patents to users of the Open Source Software and/or Proprietary Software incorporated, combined or distributed with such Open Source Software or developed using such Open Source Software.
 *
 ***If by accepting this Agreement, you gain access to Other Licensed Materials, they will be listed in the applicable software manifest.  Your use of the Other Licensed Materials is subject to the applicable other licensing terms acknowledgements and disclaimers as specified in the applicable software manifest and/or identified or included with the Other Licensed Materials in the software bundle.  For clarification, this Agreement does not limit your rights under, or grant you rights that supersede, the terms of any applicable Other Licensed Materials license agreement.  If any of the Other Licensed Materials is Open Source Software that has been provided to you in object code only under terms that obligate TI to provide to you or show you where you can access the source code versions of such Open Source Software, TI will provide to you, or show you where you can access, such source code if you contact TI at Texas Instruments Incorporated, 12500 TI Boulevard, Mail Station 8638, Dallas, Texas 75243, Attention: Contracts Manager, Embedded Processing.  In the event you choose not to accept or agree with the terms in any applicable Other Licensed Materials license agreement, you must terminate this Agreement.
 *
 ***1.    License Grant and Use Restrictions.
 *
 ***a.    Licensed Materials License Grant.  Subject to the terms of this Agreement, TI hereby grants to you a limited, non-transferable, non-exclusive, non-assignable, non-sublicensable, fully paid-up and royalty-free license to:
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
 ***2.    Licensed Materials Ownership.  The Licensed Materials are licensed, not sold to you, and can only be used in accordance with the terms of this Agreement.  Subject to the licenses granted to you pursuant to this Agreement, TI and its licensors own and shall continue to own all right, title and interest in and to the Licensed Materials, including all copies thereof.  You agree that all fixes, modifications and improvements to the Licensed Materials conceived of or made by TI that are based, either in whole or in part, on your feedback, suggestions or recommendations are the exclusive property of TI and all right, title and interest in and to such fixes, modifications or improvements to the Licensed Materials will vest solely in TI.  Moreover, you acknowledge and agree that when your independently developed software or hardware components are combined, in whole or in part, with the Licensed Materials, your right to use the combined work that includes the Licensed Materials remains subject to the terms and conditions of this Agreement.
 *
 ***3.    Intellectual Property Rights.
 *
 *    a.    The Licensed Materials contain copyrighted material, trade secrets and other proprietary information of TI and its licensors and are protected by copyright laws, international copyright treaties, and trade secret laws, as well as other intellectual property laws.  To protect TI's and its licensors' rights in the Licensed Materials, you agree, except as specifically permitted by statute by a provision that cannot be waived by contract, not to "unlock", decompile, reverse engineer, disassemble or otherwise translate to a human-perceivable form any portions of the Licensed Materials provided to you in object code format only, nor permit any person or entity to do so.  You shall not remove, alter, cover, or obscure any confidentiality, trade secret, trade mark, patent, copyright or other proprietary notice or other identifying marks or designs from any component of the Licensed Materials and you shall reproduce and include in all copies of the Licensed Materials the copyright notice(s) and proprietary legend(s) of TI and its licensors as they appear in the Licensed Materials.  TI reserves all rights not specifically granted under this Agreement.
 *
 *    b.    Certain Licensed Materials may be based on industry recognized standards or software programs published by industry recognized standards bodies and certain third parties may claim to own patents, copyrights, and other intellectual property rights that cover implementation of those standards.  You acknowledge and agree that this Agreement does not convey a license to any such third party patents, copyrights, and other intellectual property rights and that you are solely responsible for any patent, copyright, or other intellectual property right claim that relates to your use or distribution of the Licensed Materials or your use or distribution of your products that include or incorporate the Licensed Materials.  Moreover, you acknowledge that you are responsible for any fees or royalties that may be payable to any third party based on such third party's interests in the Licensed Materials or any intellectual property rights that cover implementation of any industry recognized standard, any software program published by any industry recognized standards bodies or any other proprietary technology.
 *
 ***4.    Confidential Information.  You acknowledge and agree that the Licensed Materials contain trade secrets and other confidential information of TI and its licensors.  You agree to use the Licensed Materials solely within the scope of the licenses set forth herein, to maintain the Licensed Materials in strict confidence, to use at least the same procedures and degree of care that you use to prevent disclosure of your own confidential information of like importance but in no instance less than reasonable care, and to prevent disclosure of the Licensed Materials to any third party, except as may be necessary and required in connection with your rights and obligations hereunder; provided, however, that you may not provide the Licensed Materials to any business organization or group within your company or to customers or contractors that design or manufacture semiconductors unless TI gives written consent.  You agree to obtain executed confidentiality agreements with your employees and contractors having access to the Licensed Materials and to diligently take steps to enforce such agreements in this respect.  TI may disclose your contact information to TI's licensors.
 *
 ***5.    Warranties and Limitations.  THE LICENSED MATERIALS ARE PROVIDED "AS IS".  FURTHERMORE, YOU ACKNOWLEDGE AND AGREE THAT THE LICENSED MATERIALS HAVE NOT BEEN TESTED OR CERTIFIED BY ANY GOVERNMENT AGENCY OR INDUSTRY REGULATORY ORGANIZATION OR ANY OTHER THIRD PARTY ORGANIZATION.  YOU AGREE THAT PRIOR TO USING, INCORPORATING OR DISTRIBUTING THE LICENSED MATERIALS IN OR WITH ANY COMMERCIAL PRODUCT THAT YOU WILL THOROUGHLY TEST THE PRODUCT AND THE FUNCTIONALITY OF THE LICENSED MATERIALS IN OR WITH THAT PRODUCT AND BE SOLELY RESPONSIBLE FOR ANY PROBLEMS OR FAILURES.
 *
 ***TI AND ITS LICENSORS MAKE NO WARRANTY OR REPRESENTATION, EITHER EXPRESS, IMPLIED OR STATUTORY, REGARDING THE LICENSED MATERIALS, INCLUDING BUT NOT LIMITED TO ANY IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT OF ANY THIRD PARTY PATENTS, COPYRIGHTS, TRADE SECRETS OR OTHER INTELLECTUAL PROPERTY RIGHTS.  YOU AGREE TO USE YOUR INDEPENDENT JUDGMENT IN DEVELOPING YOUR PRODUCTS.  NOTHING CONTAINED IN THIS AGREEMENT WILL BE CONSTRUED AS A WARRANTY OR REPRESENTATION BY TI TO MAINTAIN PRODUCTION OF ANY TI SEMICONDUCTOR DEVICE OR OTHER HARDWARE OR SOFTWARE WITH WHICH THE LICENSED MATERIALS MAY BE USED.
 *
 ***IN NO EVENT SHALL TI OR ITS LICENSORS, BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL, PUNITIVE OR CONSEQUENTIAL DAMAGES, HOWEVER CAUSED, ON ANY THEORY OF LIABILITY, IN CONNECTION WITH OR ARISING OUT OF THIS AGREEMENT OR THE USE OF THE LICENSED MATERIALS REGARDLESS OF WHETHER TI HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  EXCLUDED DAMAGES INCLUDE, BUT ARE NOT LIMITED TO, COST OF REMOVAL OR REINSTALLATION, OUTSIDE COMPUTER TIME, LABOR COSTS, LOSS OF DATA, LOSS OF GOODWILL, LOSS OF PROFITS, LOSS OF SAVINGS, OR LOSS OF USE OR INTERRUPTION OF BUSINESS.  IN NO EVENT WILL TI'S OR ITS LICENSORS' AGGREGATE LIABILITY UNDER THIS AGREEMENT OR ARISING OUT OF YOUR USE OF THE LICENSED MATERIALS EXCEED FIVE HUNDRED U.S. DOLLARS (US$500).
 *
 *    Because some jurisdictions do not allow the exclusion or limitation of incidental or consequential damages or limitation on how long an implied warranty lasts, the above limitations or exclusions may not apply to you.
 *
 ***6.    Indemnification Disclaimer.  YOU ACKNOWLEDGE AND AGREE THAT TI SHALL NOT BE LIABLE FOR AND SHALL NOT DEFEND OR INDEMNIFY YOU AGAINST ANY THIRD PARTY INFRINGEMENT CLAIM THAT RELATES TO OR IS BASED ON YOUR MANUFACTURE, USE, OR DISTRIBUTION OF THE LICENSED MATERIALS OR YOUR MANUFACTURE, USE, OFFER FOR SALE, SALE, IMPORTATION OR DISTRIBUTION OF YOUR PRODUCTS THAT INCLUDE OR INCORPORATE THE LICENSED MATERIALS.
 *
 ***7.    No Technical Support.  TI and its licensors are under no obligation to install, maintain or support the Licensed Materials.
 *
 ***8.    Notices.  All notices to TI hereunder shall be delivered to Texas Instruments Incorporated, 12500 TI Boulevard, Mail Station 8638, Dallas, Texas 75243, Attention: Contracts Manager - Embedded Processing, with a copy to Texas Instruments Incorporated, 13588 N. Central Expressway, Mail Station 3999, Dallas, Texas 75243, Attention: Law Department - Embedded Processing.  All notices shall be deemed served when received by TI.
 *
 ***9.    Export Control.  The Licensed Materials are subject to export control under the U.S. Commerce Department's Export Administration Regulations ("EAR").  Unless prior authorization is obtained from the U.S. Commerce Department, neither you nor your subsidiaries shall export, re-export, or release, directly or indirectly (including, without limitation, by permitting the Licensed Materials to be downloaded), any technology, software, or software source code, received from TI, or export, directly or indirectly, any direct product of such technology, software, or software source code, to any person, destination or country to which the export, re-export, or release of the technology, software, or software source code, or direct product is prohibited by the EAR.  You represent and warrant that you (i) are not located in, or under the control of, a national or resident of Cuba, Iran, North Korea, Sudan and Syria or any other country subject to a U.S. goods embargo; (ii) are not on the U.S. Treasury Department's List of Specially Designated Nationals or the U.S. Commerce Department's Denied Persons List or Entity List; and (iii) will not use the Licensed Materials or transfer the Licensed Materials for use in any military, nuclear, chemical or biological weapons, or missile technology end-uses.  Any software export classification made by TI shall not be construed as a representation or warranty regarding the proper export classification for such software or whether an export license or other documentation is required for the exportation of such software.
 *
 ***10.    Governing Law and Severability; Waiver.  This Agreement will be governed by and interpreted in accordance with the laws of the State of Texas, without reference to conflict of laws principles.  If for any reason a court of competent jurisdiction finds any provision of the Agreement to be unenforceable, that provision will be enforced to the maximum extent possible to effectuate the intent of the parties, and the remainder of the Agreement shall continue in full force and effect.  This Agreement shall not be governed by the United Nations Convention on Contracts for the International Sale of Goods, or by the Uniform Computer Information Transactions Act (UCITA).  The parties agree that non-exclusive jurisdiction for any dispute arising out of or relating to this Agreement lies within the courts located in the State of Texas.  Notwithstanding the foregoing, any judgment may be enforced in any United States or foreign court, and either party may seek injunctive relief in any United States or foreign court.  Failure by TI to enforce any provision of this Agreement shall not be deemed a waiver of future enforcement of that or any other provision in this Agreement or any other agreement that may be in place between the parties.
 *
 ***11.    PRC Provisions.  If you are located in the People's Republic of China ("PRC") or if the Licensed Materials will be sent to the PRC, the following provisions shall apply:
 *
 *    a.    Registration Requirements.  You shall be solely responsible for performing all acts and obtaining all approvals that may be required in connection with this Agreement by the government of the PRC, including but not limited to registering pursuant to, and otherwise complying with, the PRC Measures on the Administration of Software Products, Management Regulations on Technology Import-Export, and Technology Import and Export Contract Registration Management Rules.  Upon receipt of such approvals from the government authorities, you shall forward evidence of all such approvals to TI for its records.  In the event that you fail to obtain any such approval or registration, you shall be solely responsible for any and all losses, damages or costs resulting therefrom, and shall indemnify TI for all such losses, damages or costs.
 *
 ***b.    Governing Language.  This Agreement is written and executed in the English language and shall be authoritative and controlling, whether or not translated into a language other than English to comply with law or for reference purposes.  If a translation of this Agreement is required for any purpose, including but not limited to registration of the Agreement pursuant to any governmental laws, regulations or rules, you shall be solely responsible for creating such translation.
 *
 ***12.    Contingencies.    TI shall not be in breach of this Agreement and shall not be liable for any non-performance or delay in performance if such non-performance or delay is due to a force majeure event or other circumstances beyond TI's reasonable control.
 *
 ***13.        Entire Agreement.  This is the entire agreement between you and TI and this Agreement supersedes any prior agreement between the parties related to the subject matter of this Agreement.  Notwithstanding the foregoing, any signed and effective software license agreement relating to the subject matter hereof and stating expressly that such agreement shall control regardless of any subsequent click-wrap, shrink-wrap or web-wrap, shall supersede the terms of this Agreement.  No amendment or modification of this Agreement will be effective unless in writing and signed by a duly authorized representative of TI.  You hereby warrant and represent that you have obtained all authorizations and other applicable consents required empowering you to enter into this Agreement.
 *
 *
 *
 * --/COPYRIGHT--*/
#ifndef _USERCONFIG_H_
#define _USERCONFIG_H_

//#############################################################################
//
//! \file   ussSwLib_userConfig.h
//!
//! \brief  USS SW Library configuration file
//!
//
//  Group:          MSP
//  Target Device:  MSP430FR604x
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
#include "IQmathLib.h"
#include "ussSwLibCalibration.h"

//*****************************************************************************
//! \addtogroup ussSwLib_userConfig
//! @{
//*****************************************************************************

#ifdef __cplusplus

extern "C"
{
#endif

 /*******************************************************************************
 * The following macros allows user to select tone generation type
 * *****************************************************************************/
 #define USS_PULSE_MODE_SINGLE_TONE                                  0
 #define USS_PULSE_MODE_DUAL_TONE                                    1
 #define USS_PULSE_MODE_MULTI_TONE                                   2

/*******************************************************************************
 * The following macros allows user to select default
 * Absolute time of flight computation option
 * To switch between computation option update
 * USS_ALG_ABS_TOF_COMPUTATION_MODE macro with the desired computation option
 ******************************************************************************/
 #define USS_ALG_ABS_TOF_COMPUTATION_MODE_LOBE                      0
 #define USS_ALG_ABS_TOF_COMPUTATION_MODE_HILBERT                   1
 #define USS_ALG_ABS_TOF_COMPUTATION_MODE_LOBE_WIDE                 2
 #define USS_ALG_ABS_TOF_COMPUTATION_MODE_HILBERT_WIDE              3


/*******************************************************************************
 * The following macros allows user to select default
 * DtoF computation option
 * To switch between computation option update
 * USS_ALG_DTOF_COMPUTATION_MODE macro with the desired computation
 * option
 ******************************************************************************/
 #define USS_ALG_DTOF_COMPUTATION_OPTION_WATER                       0
 #define USS_ALG_DTOF_COMPUTATION_OPTION_ESTIMATE                    1

 /*******************************************************************************
  * The following macros allows user to select default
  * DToF estimate windowing options
  * To switch between computation option update
  * USS_ALG_DTOF_WINDOWING_MODE macro with the desired computation option
  * when USS_ALG_DTOF_COMPUTATION_MODE = USS_ALG_DTOF_COMPUTATION_OPTION_ESTIMATE
  ******************************************************************************/
  #define USS_ALG_DTOF_EST_WINDOW_OPTION_DISABLED                        0
  #define USS_ALG_DTOF_EST_WINDOW_OPTION_ESTIMATE                        1
  #define USS_ALG_DTOF_EST_WINDOW_OPTION_DYNAMIC                         2
  #define USS_ALG_DTOF_EST_WINDOW_OPTION_STATIC                          3

 /*******************************************************************************
  * The following macros allows user to select default
  * DToF estimate windowing options
  * To switch between computation option update
  * USS_ALG_DTOF_WINDOWING_MODE macro with the desired computation option
  * when USS_ALG_DTOF_COMPUTATION_MODE = USS_ALG_DTOF_COMPUTATION_OPTION_WATER
  ******************************************************************************/
  #define USS_ALG_DTOF_WATER_WINDOW_OPTION_DISABLED                      0
  #define USS_ALG_DTOF_WATER_WINDOW_OPTION_ENABLED                       1

 /*******************************************************************************
  * The following macros allows user to select default
  * volume flow calibration options
  * To switch between computation option update
  * USS_ALG_VFR_CALIB_MODE macro with the desired computation option
  ******************************************************************************/
  #define USS_ALG_VFR_CALIB_OPTION_DISABLED                          0
  #define USS_ALG_VFR_CALIB_OPTION_FLOW                              1
  #define USS_ALG_VFR_CALIB_OPTION_FLOW_TEMPERATURE                  2

/*******************************************************************************
 * The following macros allows user to select default
 * Volume computation option
 * To switch between computation option update
 * USS_ALG_VOLUME_RATE_COMPUTATION_MODE macro with the desired computation
 * option
 ******************************************************************************/
#define USS_ALG_VOLUME_RATE_COMPUTATION_OPTION_WATER                0
#define USS_ALG_VOLUME_RATE_COMPUTATION_OPTION_GENERIC              1
#define USS_ALG_VOLUME_RATE_COMPUTATION_OPTION_GAS                  USS_ALG_VOLUME_RATE_COMPUTATION_OPTION_GENERIC

//******************************************************************************
// defines
//******************************************************************************

 /*******************************************************************************
  * USS PULSE GENERATION CONFIGURATION
  *
  * The following parameters configures the ultrasonic pulse generation
  *
  ******************************************************************************/
#ifndef USS_PULSE_MODE
 #define USS_PULSE_MODE                   USS_PULSE_MODE_MULTI_TONE
#endif

 #if (USS_PULSE_MODE == USS_PULSE_MODE_SINGLE_TONE)
 #define USS_NUM_OF_EXCITATION_PULSES_F1    20
 #define USS_F1_FREQ                        1000000
 #define USS_PULSE_DUTYPERCENT_F1           50
 #define USS_NUM_OF_EXCITATION_PULSES       USS_NUM_OF_EXCITATION_PULSES_F1
 #elif defined(__MSP430_HAS_SAPH_A__)
 #if (USS_PULSE_MODE == USS_PULSE_MODE_DUAL_TONE)
 #define USS_NUM_OF_EXCITATION_PULSES_F1    12
 #define USS_F1_FREQ                        170000
 #define USS_PULSE_DUTYPERCENT_F1           50
 #define USS_NUM_OF_EXCITATION_PULSES_F2    12
 #define USS_F2_FREQ                        240000
 #define USS_PULSE_DUTYPERCENT_F2           50
 #define USS_NUM_OF_EXCITATION_PULSES       (USS_NUM_OF_EXCITATION_PULSES_F1 + USS_NUM_OF_EXCITATION_PULSES_F2)
 #elif (USS_PULSE_MODE == USS_PULSE_MODE_MULTI_TONE)
 #define USS_F1_FREQ                        170000
 #define USS_F2_FREQ                        240000
 #define USS_NUM_OF_TRILL_PULSES            12
 #define USS_NUM_OF_EXCITATION_PULSES       ((2*(USS_NUM_OF_TRILL_PULSES + USS_NUM_OF_ADDTL_TRILL_PULSES)))
 #endif
 #endif

 #if (USS_PULSE_MODE == USS_PULSE_MODE_MULTI_TONE)
 #define USS_NUM_OF_ADDTL_TRILL_PULSES                 0
 #endif

 #define USS_ADDTL_BIN_PATTERN_SIZE                    0
 #define USS_NUM_OF_STOP_PULSES                        0



/*******************************************************************************
 * LIBRARY MEMORY OPTIMIZATION CONFIGURATION
 *
 * The following parameters allows to user to reduce capture buffer size and
 * temporary LEA and FRAM buffers.
 *
 ******************************************************************************/
#if defined(__MSP430_HAS_SAPH_A__)
#define USS_SW_LIB_APP_MAX_CAPTURE_SIZE                          500
#if (USS_PULSE_MODE == USS_PULSE_MODE_MULTI_TONE)
#define USS_NUM_OF_MAX_TRILL_PULSES                              20
#define USS_NUM_OF_MAX_ADDTL_TRILL_PULSES                        10
#endif
#else
#define USS_SW_LIB_APP_MAX_CAPTURE_SIZE                          330
#endif
#define USS_SW_LIB_APP_MAX_FILTER_LENGTH                         20
#define USS_SW_LIB_APP_MAX_FILTER_OPTIONS                        5
#define USS_SW_LIB_APP_MAX_HILBERT_FILTER_OPTIONS                2
#define USS_SW_LIB_APP_MAX_HILBERT_FILTER_LENGTH                 12
#if (USS_PULSE_MODE == USS_PULSE_MODE_MULTI_TONE)
#define USS_BINARY_ARRAY_MAX_SIZE                                400
#else
#define USS_BINARY_ARRAY_MAX_SIZE                                200
#endif

/*******************************************************************************
 * LIBRARY CAPTURE ACCUMULATION CONFIGURATION
 *
 * The following parameters allows to enable/disable capture accumulation
 * options. WARNING: Enabling accumulation will increase LEA RAM requirements
 *
 * USS_SW_LIB_ENABLE_ACCUMULATION valid options:
 * -true
 * -false
 *
 * USS_ALG_DTOF_INTERVAL valid options:
 *  -USS_dtof_volume_flow_calculation_interval_1 (default)
 *  -USS_dtof_volume_flow_calculation_interval_2
 *  -USS_dtof_volume_flow_calculation_interval_4
 *  -USS_dtof_volume_flow_calculation_interval_8
 *
 * The following definitions are used to initialize the following library
 * parameter:
 * -USS_Capture_Configuration.isCapAccumulationEnabled
 * -USS_Algorithms_User_Configuration.dtofVolInterval
*******************************************************************************/
#define USS_SW_LIB_ENABLE_ACCUMULATION    false
#if (USS_SW_LIB_ENABLE_ACCUMULATION == false)
#define USS_ALG_DTOF_INTERVAL USS_dtof_volume_flow_calculation_interval_1
#else
#warning "Update to desired calculation interval"
#define USS_ALG_DTOF_INTERVAL USS_dtof_volume_flow_calculation_interval_4
#endif

/*******************************************************************************
 * LIBRARY CLOCK DEFINITION
 *
 * IMPORTANT: The following defines only specify MCLK and LFXT frequencies at
 * which the application is configured to run. The library DOES NOT configure
 * MCLK, SMCLK or LFXT.
 *
 * This parameter are also using in the derived parameter section to calculate
 * HSPLL counts and LFXT counts.
 *
 * USS_MCLK_FREQ_IN_HZ valid options:
 * - Valid device specific MCLK frequency options
 *
 * USS_LFXT_FREQ_IN_HZ valid options:
 * - Valid device specific MCLK frequency options
 *
 * USS_SYS_MEASUREMENT_PERIOD (in LFXT cycles) valid range:
 * -min: 655 (20 milliseconds)
 * -max: 65535 (2 seconds)
 *
 ******************************************************************************/
#if (USS_PULSE_MODE == USS_PULSE_MODE_MULTI_TONE)
#define USS_MCLK_FREQ_IN_HZ               16000000
#else
#define USS_MCLK_FREQ_IN_HZ               8000000
#endif
#define USS_SMCLK_FREQ_IN_HZ               8000000
#define USS_LFXT_FREQ_IN_HZ                  32768
#define USS_SYS_MEASUREMENT_PERIOD           32768

/*******************************************************************************
 * LIBRARY DIAGNOSTIC CONFIGURATION
 *
 * The following configuration allows the application to obtain additional debug
 * message codes during the application process.
 *
 * USS_DIAGNOSTIC_MODE valid options:
 * - USS_diagnostics_mode_2 (default)
 * - USS_diagnostics_mode_0
 *
*******************************************************************************/
#define USS_DIAGNOSTIC_MODE            USS_diagnostics_mode_2

/*******************************************************************************
 * LIBRARY METER CONFIGURATION
 *
 * The following configuration allows the application to configure meter
 * specific parameter
 *
 * USS_ACOUSTIC_LENGTH (Acoustic length in us at room temperature)
 * USS_VOLUME_SCALE_FACTOR
 *
 *
*******************************************************************************/
#define USS_ACOUSTIC_LENGTH                          70
#if (USS_PULSE_MODE != USS_PULSE_MODE_SINGLE_TONE)
#define USS_VOLUME_SCALE_FACTOR                      61.00f
#else
#define USS_VOLUME_SCALE_FACTOR                      1.2742e7f
#endif
 // The following #define must be set to 1.0f or larger
#define USS_VFR_LARGE_PIPE_ADDL_SF                                      1.000000f
// The following #define must be :
// Set to false if USS_VFR_LARGE_PIPE_ADDL_SF == 1.0f
// Set to true if USS_VFR_LARGE_PIPE_ADDL_SF > 1.0f)
#define USS_VFR_LARGE_PIPE_ADDL_SF_ENABLE                               false

/*******************************************************************************
 * LIBRARY BASIC ULTRASONIC FIRING/CAPTURE CONFIGURATION
 *
 * The library basic configuration section has been split in the following
 * sections:
 *
 * -USS FREQUENCY CONFIGURATION PARAMETERS
 * -USS CAPTURE SEQUENCE CONFIGURATION
 * -USS PULSE GENERATION CONFIGURATION
 * -USS CALIBRATION CONFIGURATION
 *
*******************************************************************************/

/*******************************************************************************
 * USS FREQUENCY CONFIGURATION PARAMETERS
 *
 * USS_HSPLL_FREQ_IN_MHZ valid parameters:
 * - 80 (default), 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68
 *
 * USS_HSPLL_INPUT_CLK_TYPE valid parameters:
 * - USS_HSPLL_input_clock_type_ceramic_resonator (default)
 * - USS_HSPLL_input_clock_type_crystal
 *
 * USS_OVER_SAMPLE_RATE valid parameters:
 * -10
 * -20 (default)
 * -40
 * -80
 * -160
 *
 * USS_PLL_XTAL_IN_MHZ valid parameters:
 * -USS_HSPLL_input_clock_freq_8_MHz
 * -USS_HSPLL_input_clock_freq_4_MHz
 *
 * USS_OUTPUT_PLL_XTAL valid parameters:
 * -false (default)
 * -true
 *
 *****************************************************************************/
#define USS_HSPLL_FREQ_IN_MHZ                  80
#define USS_HSPLL_INPUT_CLK_TYPE               USS_HSPLL_input_clock_type_ceramic_resonator
#if (USS_PULSE_MODE == USS_PULSE_MODE_SINGLE_TONE)
#define USS_SDHS_OVER_SAMPLE_RATE              20
#else
#define USS_SDHS_OVER_SAMPLE_RATE              80
#endif
#define USS_PLL_XTAL_IN_MHZ                    USS_HSPLL_input_clock_freq_8_MHz
#define USS_OUTPUT_PLL_XTAL                    false
#define USS_HSPLL_TOLERANCE_PERCENT            0.5

/*******************************************************************************
 * USS CAPTURE SEQUENCE CONFIGURATION
 *
 * USS_SEQUENCE_SELECTION valid parameters:
 * - USS_CAPTURE_SEQUENCE_SELECTION_CH0
 * - USS_CAPTURE_SEQUENCE_SELECTION_CH1
 * - USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH0
 * - USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH1 (default)
 * - USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH0
 * - USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH1
 *
 * USS_CAPTURE_DURATION_USEC vaild range:
 * -min: 1 usec
 * -max: Varies depending on USS_SW_LIB_APP_MAX_CAPTURE_SIZE,
 *       USS_SDHS_OVER_SAMPLE_RATE and USS_HSPLL_FREQ_IN_MHZ
 *
 * For further details regarding min and max values for the following parameter
 * please refer the USS Library API Guide.
 * USS_GAIN_RANGE
 * USS_START_CAPTURE_SEC
 * USS_ADC_SAMP_COUNT_SEC
 * USS_RESTART_CAP_COUNT_SEC
 *
 ******************************************************************************/
#define USS_SEQUENCE_SELECTION                            USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH1
#if (USS_PULSE_MODE == USS_PULSE_MODE_SINGLE_TONE)
#define USS_CAPTURE_DURATION_USEC                         40
#define USS_GAIN_RANGE                                    USS_Capture_Gain_Range_1_0
#define USS_START_CAPTURE_SEC                             500000e-9f
#define USS_ADC_SAMP_COUNT_SEC                            532000e-9f
#else
#define USS_CAPTURE_DURATION_USEC                         300
#define USS_GAIN_RANGE                                    USS_Capture_Gain_Range_0_1
#define USS_START_CAPTURE_SEC                             200000e-9f
#define USS_ADC_SAMP_COUNT_SEC                            370000e-9f
#endif
#define USS_RESTART_CAP_COUNT_SEC                         3000e-6f

#if (USSSWLIB_ENABLE_EXTERNAL_CIRCUITRY_CONTROL == true)
#define USS_MEASUREMENT_TURN_ON_EXTERNAL_AMP_SEC          10000e-9f
#define USS_MEASUREMENT_ASQTRIGGER_DELAY_SEC              100e-6f
#endif



/*******************************************************************************
 * USS CALIBRATION CONFIGURATION
 *
 * The following parameters configures the ultrasonic:
 * -Automatic Gain Calibration Constant
 *
 * For further details regarding the following parameter please refer the USS
 * Library API Guide.
 * USS_AGC_CONSTANT
 * USS_ALG_CALIBRATED_UPS_DC_OFFSET
 * USS_ALG_CALIBRATED_DNS_DC_OFFSET
 *
 ******************************************************************************/
#define USS_AGC_CONSTANT                              60
#define USS_ALG_CALIBRATED_UPS_DC_OFFSET              0
#define USS_ALG_CALIBRATED_DNS_DC_OFFSET              0


/*******************************************************************************
 * LIBRARY BASIC ALGORITHM CONFIGURATION
 ******************************************************************************/
#if (USS_PULSE_MODE != USS_PULSE_MODE_SINGLE_TONE)
#define USS_ALG_ABS_TOF_COMPUTATION_MODE              USS_ALG_ABS_TOF_COMPUTATION_MODE_HILBERT_WIDE
#else
#define USS_ALG_ABS_TOF_COMPUTATION_MODE              USS_ALG_ABS_TOF_COMPUTATION_MODE_LOBE
#endif

#define USS_ALG_DTOF_COMPUTATION_MODE                 USS_ALG_DTOF_COMPUTATION_OPTION_ESTIMATE
#if (USS_PULSE_MODE != USS_PULSE_MODE_SINGLE_TONE)
#define USS_ALG_VOLUME_RATE_COMPUTATION_MODE          USS_ALG_VOLUME_RATE_COMPUTATION_OPTION_GAS
#else
#define USS_ALG_VOLUME_RATE_COMPUTATION_MODE          USS_ALG_VOLUME_RATE_COMPUTATION_OPTION_WATER
#endif


#define USS_ALG_ABS_TOF_INTERVAL                      1
#if (USS_PULSE_MODE != USS_PULSE_MODE_SINGLE_TONE)
#define USS_ALG_DTOF_WINDOWING_MODE                  USS_ALG_DTOF_EST_WINDOW_OPTION_DISABLED
#else
#if (USS_ALG_DTOF_COMPUTATION_MODE == USS_ALG_DTOF_COMPUTATION_OPTION_WATER)
#define USS_ALG_DTOF_WINDOWING_MODE                  USS_ALG_DTOF_WATER_WINDOW_OPTION_ENABLED
#elif (USS_ALG_DTOF_COMPUTATION_MODE == USS_ALG_DTOF_COMPUTATION_OPTION_ESTIMATE)
#define USS_ALG_DTOF_WINDOWING_MODE                  USS_ALG_DTOF_EST_WINDOW_OPTION_ESTIMATE
#endif
#endif
#define USS_ALG_FILT_IS_FILTER_ENABLED                false
#define USS_ENABLE_ABSTOF_LOBE_OFFSET_CORRECTION      false
#define USS_ALG_VFR_CALIB_MODE                        USS_ALG_VFR_CALIB_OPTION_DISABLED
#define USS_ALG_ENABLE_ESTIMATE_TEMPERATURE           false
#define USS_ALG_ADC_ADDITIONAL_CAP_DLY                0.0e-6
#define USS_ALG_DCOFFSET                              0.0e-12
#define USS_ALG_CLOCK_RELATIVERROR                    _IQ27(0.0)
#define USS_ALG_ABS_TOF_HILB_USE_CUSTOM_COEFF         false

#if(USS_ALG_DTOF_WINDOWING_MODE != USS_ALG_DTOF_EST_WINDOW_OPTION_DISABLED)
#define USS_ALG_WIN_START_INDEX_BACK_OFF_NUM_CYCLES   2
#define USS_ALG_WIN_TRAP_RAMP_NUM_CYCLES              4
#define USS_ALG_WIN_NUM_CYCLES_DELTA                  3
#define USS_ALG_WIN_PEAK_INDEX_2_EDGES_NUM_CYLES      0
#define USS_ALG_WIN_NUM_CYCLES                        (USS_NUM_OF_EXCITATION_PULSES + \
                                                       USS_ALG_WIN_NUM_CYCLES_DELTA)
#endif
/*******************************************************************************
 * LIBRARY ADVANCED ALGORITHM CONFIGURATION
 * For more information regarding the following parameter please refer to the
 * USS API Library Guide
 ******************************************************************************/
#if (USS_ALG_ABS_TOF_COMPUTATION_MODE == USS_ALG_ABS_TOF_COMPUTATION_MODE_LOBE)
#define USS_ALG_RATIO_OF_TRACK_LOBE                         0.11111
#define USS_ALG_NUM_PULS_BEFORE_THRSH                       1
#define USS_ALG_SEARCH_LOBE_SAMP                            1
#define USS_ALG_MAX_RATIO_PEAK_2_PEAK_VAR                   0.2
#define USS_ALG_CORR_VAL_THRSH_CHK_FACT                     0.05
#define USS_ALG_SIGN_VAL_THRSH_CHK                          100
#elif (USS_ALG_ABS_TOF_COMPUTATION_MODE == USS_ALG_ABS_TOF_COMPUTATION_MODE_HILBERT)
#define USS_ALG_ABS_TOF_SEARCH_RANGE                        3
#define USS_ALG_ABS_TOF_POS_SEARCH_RANGE                    USS_ALG_ABS_TOF_SEARCH_RANGE
#define USS_ALG_ABS_TOF_NEG_SEARCH_RANGE                    -(USS_NUM_OF_EXCITATION_PULSES + USS_ALG_ABS_TOF_SEARCH_RANGE)
#define USS_ALG_ABS_TOF_HILB_CROSS_THRESHOLD                20
#define USS_ALG_CORR_VAL_THRSH_CHK_FACT                     0.05
#define USS_ALG_SIGN_VAL_THRSH_CHK                          100
#elif (USS_ALG_ABS_TOF_COMPUTATION_MODE == USS_ALG_ABS_TOF_COMPUTATION_MODE_LOBE_WIDE)
#define USS_ALG_ABS_TOF_SEARCH_RANGE                        3
#define USS_ALG_ABS_TOF_POS_SEARCH_RANGE                    USS_ALG_ABS_TOF_SEARCH_RANGE
#define USS_ALG_ABS_TOF_NEG_SEARCH_RANGE                    -(USS_NUM_OF_EXCITATION_PULSES + USS_ALG_ABS_TOF_SEARCH_RANGE)
#define USS_ALG_RATIO_OF_TRACK_LOBE                         0.5
#define USS_ALG_MAX_RATIO_PEAK_2_PEAK_VAR                   0.5
#elif (USS_ALG_ABS_TOF_COMPUTATION_MODE == USS_ALG_ABS_TOF_COMPUTATION_MODE_HILBERT_WIDE)
#define USS_ALG_ABS_TOF_HILB_CROSS_THRESHOLD                50
#define USS_ALG_ABS_TOF_SEARCH_RANGE                        8
#define USS_ALG_ABS_TOF_POS_SEARCH_RANGE                    USS_ALG_ABS_TOF_SEARCH_RANGE
#define USS_ALG_ABS_TOF_NEG_SEARCH_RANGE                    -(USS_NUM_OF_EXCITATION_PULSES + USS_ALG_ABS_TOF_SEARCH_RANGE)
#else
#error "Invalid Absolute ToF Algorithm Option"
#endif


#if (USS_ALG_DTOF_COMPUTATION_MODE == USS_ALG_DTOF_COMPUTATION_OPTION_WATER)
#define USS_ALG_NUM_CYCLES_SEARCH_CORR            2
#define USS_ALG_HIGH_FLOW_OPTION                  (USS_highFlow_option_disabled)
#define USS_ALG_CYCLESLIPTHRESHOLD                1.1
#define USS_ALG_THRESHOLDX1X3                     2000000
#elif (USS_ALG_DTOF_COMPUTATION_MODE == USS_ALG_DTOF_COMPUTATION_OPTION_ESTIMATE)
#define USS_ALG_MAX_SAMPLE_SHIFT                  20
#define USS_ALG_THRESHOLDX1X3                     2000000
#else
#error "Invalid Delta ToF Algorithm Option"
#endif


/*******************************************************************************
* LIBRARY ALGORITHM BAND-PASS AND HILBERT COEFFICIENT
******************************************************************************/

#define USS_SW_LIB_APP_FILTER_COEFFICIENTS                         \
    {                                                              \
        /*  USS_filterCoeffs_3400000Hz   */                        \
        {    0xFEEA, 0xFFDA, 0xF4E6, 0xFBA5,                       \
             0xFFBB, 0x03BC, 0x155D, 0xDE0E,                       \
             0xF5A0, 0x2E9C, 0xF5A0, 0xDE0E,                       \
             0x155D, 0x03BC, 0xFFBB, 0xFBA5,                       \
             0xF4E6, 0xFFDA, 0xFEEA, 0x0000                        \
        },                                                         \
        /*  USS_filterCoeffs_3600000Hz   */                        \
        {    0x002B, 0xFF01, 0xF563, 0x050D,                       \
             0xFE4C, 0x0F1B, 0x0FDC, 0xE05C,                       \
             0xFAC9, 0x302A, 0xFAC9, 0xE05C,                       \
             0x0FDC, 0x0F1B, 0xFE4C, 0x050D,                       \
             0xF563, 0xFF01, 0x002B, 0x0000                        \
        },                                                         \
        /*  USS_filterCoeffs_3800000Hz   */                        \
        {    0x0120, 0xFAD8, 0xFA10, 0x06E7,                       \
             0xFE1E, 0x14A0, 0x0848, 0xE00B,                       \
             0xFE43, 0x2DAF, 0xFE43, 0xE00B,                       \
             0x0848, 0x14A0, 0xFE1E, 0x06E7,                       \
             0xFA10, 0xFAD8, 0x0120, 0x0000                        \
        },                                                         \
        /*  USS_filterCoeffs_4000000Hz   */                        \
        {    0x0000, 0xF68E, 0x0000, 0x037C,                       \
             0x0000, 0x1714, 0x0000, 0xE229,                       \
             0x0000, 0x2D64, 0x0000, 0xE229,                       \
             0x0000, 0x1714, 0x0000, 0x037C,                       \
             0x0000, 0xF68E, 0x0000, 0x0000                        \
        },                                                         \
        /*  USS_filterCoeffs_Custom   */                           \
        {0},                                                       \
    };

#define USS_SW_LIB_APP_HILB_FILTER_COEFFICIENTS                    \
    {                                                              \
        /*  Predefined Hilbert transform coefficients   */         \
        {  0xFD84, 0x0000, 0xF11F, 0x0000,                         \
           0xB38F, 0x0000, 0x4C71, 0x0000,                         \
           0x0EE1, 0x0000, 0x027C, 0x0000                          \
        },                                                         \
        /*  USS Hilbert Coeffs Custom   */                         \
        {0},                                                       \
    };

/*******************************************************************************
 * LIBRARY ADVANCED ULTRASONIC FIRING/CAPTURE CONFIGURATION
 *
 * For more information regarding the following parameter please refer to the
 * USS API Library Guide
 ******************************************************************************/
#define USS_EOF_SEQUENCE_SELECTION          USS_measurement_end_of_sequence_state_power_off
#define USS_CH0_DRIVE_STRENGHT              USS_measurement_drive_strength_pre_trimmed_drive
#define USS_CH1_DRIVE_STRENGHT              USS_measurement_drive_strength_pre_trimmed_drive
#define USS_PAUSE_STATE                     USS_measurement_pause_state_low
#define USS_PULSE_POLARITY                  USS_measurement_pulse_polarity_excitation_starts_on_high_pulse
#if (USS_PULSE_MODE == USS_PULSE_MODE_SINGLE_TONE)
#define USS_PGA_IN_BIAS_COUNT_SEC           5e-6
#define USS_TURN_ON_ADC_COUNT_SEC           5e-6
#else
#define USS_PGA_IN_BIAS_COUNT_SEC           200000e-9
#define USS_TURN_ON_ADC_COUNT_SEC           20000e-9
#endif
#define USS_TIME_OUT_COUNT_SEC              3000e-6
#define USS_HSPLL_USSXTAL_SETTLING_USEC     120
#define USS_ENABLE_UUPSPREQIGINTERRUPT      false
#define USS_ENABLE_SAPH_PING_TRANSMIT       false
#define USS_ENABLE_WINDOW_HI_COMP           false
#define USS_ENABLE_WINDOW_LO_COMP           false
#define USS_WINDOW_HIGH_THRESHOLD           (1040)
#define USS_WINDOW_LOW_THRESHOLD            (-1040)
#define USS_TRIGGER_CONFIG                  USS_Triger_Configuration_Software_Trigger
#define USS_ULP_BIAS_DELAY                  USS_measurement_ULP_bias_delay_no_delay
#define USS_BIAS_IMPEDANCE                  USS_measurement_bias_impedance_2800_Ohms
#define USS_MUX_CHARGE_PUMP_MODE            USS_measurement_mux_charge_pump_always_off

/******************************************************************************
* LIBRARY DERIVED PARAMETER SECTION
*
* The following section performs additional library configuration based on the
* parameter selection above.
*
* It is highly recommended to not modify the following sections
*
******************************************************************************/
#if (USS_PULSE_MODE == USS_PULSE_MODE_SINGLE_TONE)
#define USS_NUM_OF_EXCITATION_PULSES       USS_NUM_OF_EXCITATION_PULSES_F1
#elif defined(__MSP430_HAS_SAPH_A__)
#if (USS_PULSE_MODE == USS_PULSE_MODE_DUAL_TONE)
#define USS_NUM_OF_EXCITATION_PULSES       (USS_NUM_OF_EXCITATION_PULSES_F1 + USS_NUM_OF_EXCITATION_PULSES_F2)
#elif (USS_PULSE_MODE == USS_PULSE_MODE_MULTI_TONE)
#define USS_NUM_OF_EXCITATION_PULSES       ((2*(USS_NUM_OF_TRILL_PULSES + USS_NUM_OF_ADDTL_TRILL_PULSES)))
#endif
#endif


#if (USS_ALG_ABS_TOF_COMPUTATION_MODE == USS_ALG_ABS_TOF_COMPUTATION_MODE_LOBE)
#define USS_ALG_ABS_TOF_COMPUTATION (USS_Alg_AbsToF_Calculation_Option_lobe)
#elif (USS_ALG_ABS_TOF_COMPUTATION_MODE == USS_ALG_ABS_TOF_COMPUTATION_MODE_HILBERT)
#define USS_ALG_ABS_TOF_COMPUTATION (USS_Alg_AbsToF_Calculation_Option_hilbert)
#elif (USS_ALG_ABS_TOF_COMPUTATION_MODE == USS_ALG_ABS_TOF_COMPUTATION_MODE_LOBE_WIDE)
#define USS_ALG_ABS_TOF_COMPUTATION (USS_Alg_AbsToF_Calculation_Option_lobeWide)
#elif (USS_ALG_ABS_TOF_COMPUTATION_MODE == USS_ALG_ABS_TOF_COMPUTATION_MODE_HILBERT_WIDE)
#define USS_ALG_ABS_TOF_COMPUTATION ( \
        USS_Alg_AbsToF_Calculation_Option_hilbertWide)
#else
#error "Invalid Abs ToF computation option"
#endif


#if (USS_ALG_DTOF_COMPUTATION_MODE == USS_ALG_DTOF_COMPUTATION_OPTION_WATER)
#define USS_ALG_DELTA_TOF_COMPUTATION_OPTION  (USS_Alg_dToF_Calculation_Option_water)
#elif (USS_ALG_DTOF_COMPUTATION_MODE == USS_ALG_DTOF_COMPUTATION_OPTION_ESTIMATE)
#define USS_ALG_DELTA_TOF_COMPUTATION_OPTION  (USS_Alg_dToF_Calculation_Option_estimate)
#else
#error "Invalid Delta ToF computation option"
#endif


#if (USS_ALG_VOLUME_RATE_COMPUTATION_MODE == USS_ALG_VOLUME_RATE_COMPUTATION_OPTION_WATER)
#define USS_ALG_VOLUME_RATE_COMPUTATION_OPTION (USS_Alg_volume_flow_Calculation_Option_water)
#elif (USS_ALG_VOLUME_RATE_COMPUTATION_MODE == USS_ALG_VOLUME_RATE_COMPUTATION_OPTION_GENERIC)
#define USS_ALG_VOLUME_RATE_COMPUTATION_OPTION (USS_Alg_volume_flow_Calculation_Option_generic)
#else
#error "Invalid volume flow rate computation option"
#endif

#define USS_ALG_IS_INIT_ALGORITHMS                          false

#if (USS_PULSE_MODE > 2)
#error \
    "Pulse mode not supported. Please modify USS_PULSE_MODE to a valid configuration."
#endif

#if defined(__MSP430_HAS_SAPH_A__)
#if (USS_NUM_OF_ADDTL_TRILL_PULSES > 0)
#warning \
    "User must provide additional pulse configuration by defining xtraepulse, xtraxpulse, xtraxhper, xtraxlper, xtrahper, xtralper in variables in USS_userConfig.c"
#if (USS_ADDTL_BIN_PATTERN_SIZE == 0)
#error "USS_ADDTL_BIN_PATTERN_SIZE cannot be set to 0 when USS_NUM_OF_ADDTL_TRILL_PULSES > 0"
#endif
#elif (USS_NUM_OF_ADDTL_TRILL_PULSES < 0)
#error "Invalid number of USS_NUM_OF_ADDTL_TRILL_PULSES"
#endif
#endif

#if (USS_HSPLL_FREQ_IN_MHZ == 80)
#define    USS_HSPLL_FREQ    USS_HSPLL_output_clk_freq_80_MHz
#define USS_PLL_FREQ                80e6
#elif (USS_HSPLL_FREQ_IN_MHZ == 79)
#define    USS_HSPLL_FREQ    USS_HSPLL_output_clk_freq_79_MHz
#define USS_PLL_FREQ                79e6
#elif (USS_HSPLL_FREQ_IN_MHZ == 78)
#define    USS_HSPLL_FREQ    USS_HSPLL_output_clk_freq_78_MHz
#define USS_PLL_FREQ                78e6
#elif (USS_HSPLL_FREQ_IN_MHZ == 77)
#define    USS_HSPLL_FREQ    USS_HSPLL_output_clk_freq_77_MHz
#define USS_PLL_FREQ                77e6
#elif (USS_HSPLL_FREQ_IN_MHZ == 76)
#define    USS_HSPLL_FREQ    USS_HSPLL_output_clk_freq_76_MHz
#define USS_PLL_FREQ                76e6
#elif (USS_HSPLL_FREQ_IN_MHZ == 75)
#define    USS_HSPLL_FREQ    USS_HSPLL_output_clk_freq_75_MHz
#define USS_PLL_FREQ                75e6
#elif (USS_HSPLL_FREQ_IN_MHZ == 74)
#define    USS_HSPLL_FREQ    USS_HSPLL_output_clk_freq_74_MHz
#define USS_PLL_FREQ                74e6
#elif (USS_HSPLL_FREQ_IN_MHZ == 73)
#define    USS_HSPLL_FREQ    USS_HSPLL_output_clk_freq_73_MHz
#define USS_PLL_FREQ                73e6
#elif (USS_HSPLL_FREQ_IN_MHZ == 72)
#define    USS_HSPLL_FREQ    USS_HSPLL_output_clk_freq_72_MHz
#define USS_PLL_FREQ                72e6
#elif (USS_HSPLL_FREQ_IN_MHZ == 71)
#define    USS_HSPLL_FREQ    USS_HSPLL_output_clk_freq_71_MHz
#define USS_PLL_FREQ                71e6
#elif (USS_HSPLL_FREQ_IN_MHZ == 70)
#define    USS_HSPLL_FREQ    USS_HSPLL_output_clk_freq_70_MHz
#define USS_PLL_FREQ                70e6
#elif (USS_HSPLL_FREQ_IN_MHZ == 69)
#define    USS_HSPLL_FREQ    USS_HSPLL_output_clk_freq_69_MHz
#define USS_PLL_FREQ                69e6
#elif (USS_HSPLL_FREQ_IN_MHZ == 68)
#define    USS_HSPLL_FREQ    USS_HSPLL_output_clk_freq_68_MHz
#define USS_PLL_FREQ                68e6
#else
#define    USS_HSPLL_FREQ    USS_HSPLL_output_clk_freq_80_MHz
#define USS_PLL_FREQ                80e6
#endif

#define USS_START_PPG_COUNT    ((USS_PLL_FREQ * USS_START_CAPTURE_SEC) / 16)
#define USS_TURN_ON_ADC_COUNT  ((USS_PLL_FREQ * USS_TURN_ON_ADC_COUNT_SEC) / 16)
#define USS_PGA_IN_BIAS_COUNT  ((USS_PLL_FREQ * USS_PGA_IN_BIAS_COUNT_SEC) / 16)
#define USS_ADC_SAMP_COUNT     ((USS_PLL_FREQ * USS_ADC_SAMP_COUNT_SEC) / 16)
#define USS_RESTART_CAP_COUNT  ((USS_PLL_FREQ * USS_RESTART_CAP_COUNT_SEC / \
                                 16) / 16)
#define USS_TIME_OUT_COUNT     ((USS_PLL_FREQ * USS_TIME_OUT_COUNT_SEC / \
                                 4) / 16)
#define USS_LOW_POWER_RESTART_CAP_COUNT (USS_LFXT_FREQ_IN_HZ * \
                                         USS_RESTART_CAP_COUNT_SEC)

#define USS_HSPLL_TEMP         ((USS_PLL_FREQ) / 1600)
#define USS_HSPLL_TEMP2        ((USS_HSPLL_TEMP) * (USS_HSPLL_TOLERANCE_PERCENT))
#define USS_HSPLL_TOLERANCE    (USS_HSPLL_TEMP2*RESONATOR_CALIB_MONITORING_ACLK/(USS_LFXT_FREQ_IN_HZ))

// Macros used to place variables in LEA RAM memory section
#if defined(__TI_COMPILER_VERSION__)
#define _PRAGMA(x) _Pragma (# x)
#define USS_LEA_DATA(var,align) _PRAGMA(DATA_SECTION(var,".leaRAM")) \
    _PRAGMA(DATA_ALIGN(var,(align)))
#elif defined(__IAR_SYSTEMS_ICC__)
#define _PRAGMA(x) _Pragma (# x)
#define USS_LEA_DATA(var,align) _PRAGMA(location = "LEARAM") \
    _PRAGMA(data_alignment = align)
#elif defined(__GNUC__)
#define USS_LEA_DATA(var,align) __attribute__((section(".leaRAM"))) \
    __attribute__((aligned(align)))
#else
#define USS_LEA_DATA(var,align)
#endif

// This section of the header checks if the application maximum capture size
// is below the supported USS SW library capture size

#if (USS_SW_LIB_ENABLE_ACCUMULATION == true)
#if (USS_SW_LIB_APP_MAX_CAPTURE_SIZE > 372)
#error \
    "USS_SW_LIB_APP_MAX_CAPTURE_SIZE in USS_userConfig.h file must be less than 372"
#else
#define USS_SW_LIB_APP_MAX_ACC_BLOCK  (2 * USS_SW_LIB_APP_MAX_CAPTURE_SIZE)
#endif
#else
#if (USS_SW_LIB_APP_MAX_CAPTURE_SIZE > 620)
#error \
    "USS_SW_LIB_APP_MAX_CAPTURE_SIZE in USS_userConfig.h file must be less than 620"
#else
#define USS_SW_LIB_APP_MAX_ACC_BLOCK                 0
#endif
#endif

#define ROUND_UP(N, S) ((((N) + (S) - 1) / (S)) * (S))
#define TEMP_SETL     (USS_HSPLL_USSXTAL_SETTLING_USEC * USS_LFXT_FREQ_IN_HZ)
#define USS_HSPLL_USSXTAL_SETTLING_COUNT_TEMP ROUND_UP((TEMP_SETL/100000),10)
#define USS_HSPLL_USSXTAL_SETTLING_COUNT (USS_HSPLL_USSXTAL_SETTLING_COUNT_TEMP \
                                          / 10)

#define DIV_ROUND(N, D) (((N) + ((D)/2)) / (D))

#if(USS_ALG_DTOF_WINDOWING_MODE != USS_ALG_DTOF_EST_WINDOW_OPTION_DISABLED)

#if (USS_ALG_DTOF_COMPUTATION_MODE == USS_ALG_DTOF_COMPUTATION_OPTION_WATER)
#define USS_SW_LIB_APP_MAX_WINDOW_RAMP_SIZE (USS_SW_LIB_APP_MAX_CAPTURE_SIZE + USS_SW_LIB_APP_MAX_FILTER_LENGTH)
#elif (USS_ALG_DTOF_COMPUTATION_MODE == USS_ALG_DTOF_COMPUTATION_OPTION_ESTIMATE)
#define WINDOW_RAMP_TEMP_NUMERATOR (USS_ALG_WIN_TRAP_RAMP_NUM_CYCLES * USS_PLL_FREQ)
#define WINDOW_RAMP_TEMP_DENOMINATOR (USS_F1_FREQ  * USS_SDHS_OVER_SAMPLE_RATE)
#define USS_SW_LIB_APP_MAX_WINDOW_RAMP_TMP DIV_ROUND(WINDOW_RAMP_TEMP_NUMERATOR,WINDOW_RAMP_TEMP_DENOMINATOR)
#define USS_SW_LIB_APP_MAX_WINDOW_RAMP_SIZE ((int)USS_SW_LIB_APP_MAX_WINDOW_RAMP_TMP + 2)
#endif

#endif

#if (USS_ALG_FILT_IS_FILTER_ENABLED == true)
#if (USS_SDHS_OVER_SAMPLE_RATE == 20)
#if (USS_HSPLL_FREQ_IN_MHZ == 80)
#define USS_ALG_FILT_OPTION                                             3
#elif (USS_HSPLL_FREQ_IN_MHZ == 76)
#define USS_ALG_FILT_OPTION                                             2
#elif (USS_HSPLL_FREQ_IN_MHZ == 72)
#define USS_ALG_FILT_OPTION                                             1
#elif (USS_HSPLL_FREQ_IN_MHZ == 68)
#define USS_ALG_FILT_OPTION                                             0
#else
#warning "No predefined band-pass filter is available for the selected USS_OVER_SAMPLE_RATE and USS_HSPLL_FREQ frequency. User is responsible of defining USS_filterCoeffs_Custom entry below"
#define USS_ALG_FILT_OPTION                                             4
#endif
#else
#warning "No predefined band-pass filter is available for the selected USS_OVER_SAMPLE_RATE and USS_HSPLL_FREQ frequency. User is responsible of defining USS_filterCoeffs_Custom entry below"
#define USS_ALG_FILT_OPTION                                             4
#endif
#endif

#if (USS_ALG_ABS_TOF_HILB_USE_CUSTOM_COEFF == false)
#define USS_HILB_ALG_FILT_OPTION                                        0
#else
#warning \
    "Detected custom hilbert coefficient configuration. Please confirm USS_filterCoeffs_Custom has a valid coefficient configuration"
#define USS_HILB_ALG_FILT_OPTION                                        1
#endif

#if (USS_SDHS_OVER_SAMPLE_RATE == 10)
#define USS_OVER_SAMPLE_RATE \
    USS_Capture_Over_Sample_Rate_10
#elif (USS_SDHS_OVER_SAMPLE_RATE == 20)
#define USS_OVER_SAMPLE_RATE \
    USS_Capture_Over_Sample_Rate_20
#elif (USS_SDHS_OVER_SAMPLE_RATE == 40)
#define USS_OVER_SAMPLE_RATE \
    USS_Capture_Over_Sample_Rate_40
#elif (USS_SDHS_OVER_SAMPLE_RATE == 80)
#define USS_OVER_SAMPLE_RATE \
    USS_Capture_Over_Sample_Rate_80
#elif (USS_SDHS_OVER_SAMPLE_RATE == 160)
#define USS_OVER_SAMPLE_RATE \
    USS_Capture_Over_Sample_Rate_160
#else
#error "Invalid USS_SDHS_OVER_SAMPLE_RATE configuration"
#endif

#define USS_USER_CONFIG_NUMBER_OF_SAMPLES_PER_CAPTURE    \
  ((USS_CAPTURE_DURATION_USEC*USS_HSPLL_FREQ_IN_MHZ)/USS_SDHS_OVER_SAMPLE_RATE)

#if (USS_USER_CONFIG_NUMBER_OF_SAMPLES_PER_CAPTURE > \
     USS_SW_LIB_APP_MAX_CAPTURE_SIZE)
#error \
    "USS_USER_CONFIG_NUMBER_OF_SAMPLES_PER_CAPTURE exceeds USS_SW_LIB_APP_MAX_CAPTURE_SIZE"
#endif

#if (USS_PULSE_MODE != USS_PULSE_MODE_SINGLE_TONE)
#ifdef __MSP430_HAS_SAPH__
#error \
    "Dual or Multi-Tone configuration is not supported on MSP430 devices without SAPH_A module"
#endif
#endif

#if (USSSWLIB_ENABLE_EXTERNAL_CIRCUITRY_CONTROL == true)
#define USS_MEASUREMENT_TURN_ON_EXTERNAL_AMP_COUNT  (USS_SMCLK_FREQ_IN_HZ * \
                                                     USS_MEASUREMENT_TURN_ON_EXTERNAL_AMP_SEC)


#define USS_MEASUREMENT_ASQTRIGGER_DELAY_CYCLES       \
                    (USS_MEASUREMENT_ASQTRIGGER_DELAY_SEC*USS_SMCLK_FREQ_IN_HZ)
#endif


#define USS_Alg_dToF_Calculation_Option_water               1
#define USS_Alg_dToF_Calculation_Option_estimate            0
#define USS_highFlow_option_disabled                        0
#define USS_highFlow_option_version1                        1
#define USS_highFlow_option_version2                        2


#if (USS_ALG_DELTA_TOF_COMPUTATION_OPTION == USS_Alg_dToF_Calculation_Option_water)
#if (USS_ALG_HIGH_FLOW_OPTION != USS_highFlow_option_disabled)
#warning "USS_highFlow_option_version1 and USS_highFlow_option_version2 are \
discourage for new development. It is highly recommended to switch to \
USS_ALG_DELTA_TOF_COMPUTATION_OPTION = USS_Alg_dToF_Calculation_Option_estimate.\
When using USS_Alg_dToF_Calculation_Option_estimate, USS_ALG_HIGH_FLOW_OPTION \
is a don't care."
#endif
#endif


//******************************************************************************

//*****************************************************************************
// typedefs
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************
//! \brief global ultrasonic library configuration
//!
extern USS_SW_Library_configuration gUssSWConfig;
extern USS_Pulse_Single_Dual_Tone_Configuration singDualToneConfig;
extern USS_Pulse_Multitone_Configuration multiToneConfig;
extern USS_Pulse_Additional_End_of_Sequence_Configuration ussEndOfSeq;
//*****************************************************************************
// the function prototypes
//*****************************************************************************

#ifdef __cplusplus
}
#endif // extern "C"
//@}  // ingroup

#endif // end of  _USERCONFIG_H_ definition
