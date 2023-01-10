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
//#############################################################################
//
//! \file   USS_userConfig.c
//!
//! \brief  This file contains USS SW Library configuration
//!
//
//  Group:          MSP
//  Target Device:  MSP430FR6047
//
//  (C) Copyright 2019, Texas Instruments, Inc.
//#############################################################################
// TI Release: USSLib_02_40_00_00
// Release Date: February 22, 2020
//#############################################################################
#include "USS_userConfig.h"
#if (USS_ENABLE_ABSTOF_LOBE_OFFSET_CORRECTION == true)
#include <USS_Config/USS_intrplCorrLUT.h>
#endif
#if (USS_ALG_VFR_CALIB_MODE==USS_ALG_VFR_CALIB_OPTION_FLOW)
#include <USS_Config/USS_meterVFRCalibFlow.h>
#endif
#if (USS_ALG_VFR_CALIB_MODE==USS_ALG_VFR_CALIB_OPTION_FLOW_TEMPERATURE)
#include <USS_Config/USS_meterVFRCalibFlowTemperature.h>
#endif
#if(USS_ALG_ENABLE_ESTIMATE_TEMPERATURE == true)
#include <USS_Config/USS_temperatureLUT.h>
#endif

#if defined(__TI_COMPILER_VERSION__)
#if (USS_ALG_FILT_IS_FILTER_ENABLED == true)
#pragma PERSISTENT(gUSSFilterCoeffs)
#endif
#if defined(USS_ALG_FILT_IS_FILTER_ENABLED)
#pragma PERSISTENT(gUSSHilbertCoeffs)
#endif
#pragma PERSISTENT(gNVMemBlock)
#if (USS_PULSE_MODE != USS_PULSE_MODE_SINGLE_TONE)
#pragma PERSISTENT(epulse)
#pragma PERSISTENT(hper)
#pragma PERSISTENT(lper)
#pragma PERSISTENT(ussEndOfSeq)
#pragma PERSISTENT(multiToneConfig)
#pragma PERSISTENT(xpulse)
#pragma PERSISTENT(xhper)
#pragma PERSISTENT(xlper)
#if (USS_NUM_OF_ADDTL_TRILL_PULSES > 0)
#pragma PERSISTENT(xtraepulse)
#pragma PERSISTENT(xtraxpulse)
#pragma PERSISTENT(xtraxhper)
#pragma PERSISTENT(xtraxlper)
#pragma PERSISTENT(xtrahper)
#pragma PERSISTENT(xtralper)
#endif
#endif

#pragma PERSISTENT(ussSystemConfig)
#pragma PERSISTENT(ussMeterConfig)
#pragma PERSISTENT(singDualToneConfig)
#pragma PERSISTENT(ussPulseConfig)
#pragma PERSISTENT(ussMeasurementConfig)
#pragma PERSISTENT(ussPLLConfig)
#pragma PERSISTENT(ussInterruptConfig)
#pragma PERSISTENT(ussCaptureConfig)
#pragma PERSISTENT(ussTriggerConfig)
#pragma PERSISTENT(ussAlgConfig)
#pragma PERSISTENT(gUssSWConfig)
#if (USS_ALG_VFR_CALIB_MODE==USS_ALG_VFR_CALIB_OPTION_FLOW)
#pragma PERSISTENT(ussAlgorithmMeterConstCalib)
#pragma PERSISTENT(ussAlgorithmVolumeFlowObj)
#elif (USS_ALG_VFR_CALIB_MODE==USS_ALG_VFR_CALIB_OPTION_FLOW_TEMPERATURE)
#pragma PERSISTENT(ussAlgorithmQuadPoints)
#pragma PERSISTENT(ussAlgorithmQuadMeterConstant)
#pragma PERSISTENT(ussAlgorithmVolumeFlowTemperatureObj)
#endif
#if(USS_ALG_ENABLE_ESTIMATE_TEMPERATURE == true)
#pragma PERSISTENT(ussAlgorithmTemperatureCalcObj)
#endif
#define __persistent
#define __no_init
#elif defined (__IAR_SYSTEMS_ICC__)
#else
#error Compiler not supported!
#endif


#if (USS_ALG_VFR_CALIB_MODE==USS_ALG_VFR_CALIB_OPTION_FLOW)
__persistent USS_Algorithms_Flow_Meter_Constant
       ussAlgorithmMeterConstCalib[USS_METER_VFR_CALIB_FLOW_RANGES] =
               USS_METER_VFR_CALIB_FLOW_DATA;
__persistent USS_Alg_volume_Flow_Calib_Object
        ussAlgorithmVolumeFlowObj =
        {
         .numOfRanges = USS_METER_VFR_CALIB_FLOW_RANGES,
         .pMeterConfiguration = &ussAlgorithmMeterConstCalib[0],
        };
#elif (USS_ALG_VFR_CALIB_MODE==USS_ALG_VFR_CALIB_OPTION_FLOW_TEMPERATURE)
__persistent USS_Algorithms_Quad_Point
       ussAlgorithmQuadPoints[USS_METER_VFR_CALIB_FLOW_TEMPERATURE_POINT_LENGTH] =
               USS_METER_VFR_CALIB_FLOW_TEMPERATURE_QUAD_POINTS;
__persistent USS_Algorithms_Quad_Meter_Constant
       ussAlgorithmQuadMeterConstant[USS_METER_VFR_CALIB_FLOW_TEMPERATURE_MC_LENGTH] =
               USS_METER_VFR_CALIB_FLOW_TEMPERATURE_METER_CONSTANTS;

__persistent USS_Alg_volume_Flow_Temperature_Calib_Object
        ussAlgorithmVolumeFlowTemperatureObj =
        {
         .numOfFlows = USS_METER_VFR_CALIB_FLOW_TEMPERATURE_NUM_FLOW,
         .numOfTemps = USS_METER_VFR_CALIB_FLOW_TEMPERATURE_NUM_TEMP,
         .pQuadPoints = &ussAlgorithmQuadPoints[0],
         .pQuadMeterConstants = &ussAlgorithmQuadMeterConstant[0],
        };
#endif

#if(USS_ALG_ENABLE_ESTIMATE_TEMPERATURE == true)

const int32_t ussTempCalc[USS_TEMPERATURE_LUT_LENGTH][3]=
        USS_TEMPERATURE_LUT_VALUES;

__persistent USS_Alg_temperature_Calculation_Object
       ussAlgorithmTemperatureCalcObj =
       {
        .tempLUTLength = USS_TEMPERATURE_LUT_LENGTH,
        .pTempLUT = &ussTempCalc[0],
        .iq24transducerConstant = _IQ24(USS_TEMPERATURE_LUT_TRANSDUCER_CONST),
       };
#endif




#if (USS_ENABLE_ABSTOF_LOBE_OFFSET_CORRECTION == true)
const int16_t gUSSAbsToFLUT[USS_INTRPL_CORR_LUT_RES][2]=
        USS_INTRPL_CORR_LUT_VALUES;
#endif


// LEA and FRAM memory buffers
USS_HAL_LEA_DATA(gUSSLEATempMemBlock, 4)
__no_init int16_t gUSSLEATempMemBlock[2 * (USS_SW_LIB_APP_MAX_CAPTURE_SIZE +
                            USS_SW_LIB_APP_MAX_FILTER_LENGTH)];

#if(USS_ALG_DTOF_WINDOWING_MODE != USS_ALG_DTOF_EST_WINDOW_OPTION_DISABLED)
USS_HAL_LEA_DATA(gUSSLEARAMReservedBlock1, 4)
__no_init int16_t gUSSLEARAMReservedBlock1[USS_SW_LIB_APP_MAX_WINDOW_RAMP_SIZE];
#endif

USS_HAL_LEA_DATA(gUSSLEARAMReservedBlock2, 4)
__no_init int16_t gUSSLEARAMReservedBlock2[USS_SW_LIB_APP_MAX_CAPTURE_SIZE +
                                           USS_SW_LIB_APP_MAX_HILBERT_FILTER_LENGTH];

__persistent int32_t gNVMemBlock[(USS_SW_LIB_APP_MAX_CAPTURE_SIZE * 2)]={0};


USS_HAL_LEA_DATA(gUSSBinaryPattern, 4)
__no_init int16_t gUSSBinaryPattern[USS_BINARY_ARRAY_MAX_SIZE];

#if USS_SW_LIB_APP_MAX_ACC_BLOCK
USS_HAL_LEA_DATA(gUSSLEARAMReservedAccMemBlock,4)
int16_t gUSSLEARAMReservedAccMemBlock[USS_SW_LIB_APP_MAX_ACC_BLOCK];
#endif

#if defined(USS_ALG_FILT_IS_FILTER_ENABLED)
// Filter Hilbert and Band Pass Coefficients
__persistent int16_t gUSSHilbertCoeffs[
    USS_SW_LIB_APP_MAX_HILBERT_FILTER_OPTIONS][
    USS_SW_LIB_APP_MAX_HILBERT_FILTER_LENGTH] =
    USS_SW_LIB_APP_HILB_FILTER_COEFFICIENTS;
#endif

#if (USS_ALG_FILT_IS_FILTER_ENABLED == true)
__persistent int16_t gUSSFilterCoeffs[USS_SW_LIB_APP_MAX_FILTER_OPTIONS][
    USS_SW_LIB_APP_MAX_FILTER_LENGTH] =
    USS_SW_LIB_APP_FILTER_COEFFICIENTS;
#endif

#if defined(__MSP430_HAS_SAPH_A__) && (USS_PULSE_MODE == USS_PULSE_MODE_MULTI_TONE)
USS_TONE_CONFIG_DATA(RAM_XE)
__no_init uint16_t RAM_XE[(USS_NUM_OF_MAX_TRILL_PULSES +
                 USS_NUM_OF_MAX_ADDTL_TRILL_PULSES) * 6];
USS_TONE_CONFIG_DATA(RAM_DMA_CONFIG)
__no_init uint16_t RAM_DMA_CONFIG[(USS_NUM_OF_MAX_TRILL_PULSES +
                         USS_NUM_OF_MAX_ADDTL_TRILL_PULSES) * 18];

__persistent uint16_t epulse[USS_NUM_OF_MAX_TRILL_PULSES] = {0};
__persistent uint16_t hper  [USS_NUM_OF_MAX_TRILL_PULSES] = {0};
__persistent uint16_t lper  [USS_NUM_OF_MAX_TRILL_PULSES] = {0};
__persistent uint16_t xpulse[USS_NUM_OF_MAX_TRILL_PULSES] = {0};
__persistent uint16_t xhper [USS_NUM_OF_MAX_TRILL_PULSES] = {0};
__persistent uint16_t xlper [USS_NUM_OF_MAX_TRILL_PULSES] = {0};

#if (USS_NUM_OF_ADDTL_TRILL_PULSES > 0)
__persistent uint16_t xtraepulse[USS_NUM_OF_ADDTL_TRILL_PULSES] = {0};
__persistent uint16_t xtraxpulse[USS_NUM_OF_ADDTL_TRILL_PULSES] = {0};
__persistent uint16_t xtraxhper [USS_NUM_OF_ADDTL_TRILL_PULSES] = {0};
__persistent uint16_t xtraxlper [USS_NUM_OF_ADDTL_TRILL_PULSES] = {0};
__persistent uint16_t xtrahper  [USS_NUM_OF_ADDTL_TRILL_PULSES] = {0};
__persistent uint16_t xtralper  [USS_NUM_OF_ADDTL_TRILL_PULSES] = {0};
__persistent int16_t additionalBinarySequence[USS_ADDTL_BIN_PATTERN_SIZE] = {0};
#endif
#endif

__persistent USS_System_Configuration ussSystemConfig = {
    .LFXTFrequency = USS_LFXT_FREQ_IN_HZ,
    .mCLKFrequency = USS_MCLK_FREQ_IN_HZ,
    .timerBaseAddress = USSSWLIB_TIMER_BASE_ADDRESS,
    .measurementPeriod = USS_SYS_MEASUREMENT_PERIOD,
    .diagMode = USS_DIAGNOSTIC_MODE,
};

__persistent USS_Meter_Configuration ussMeterConfig = {
    .acousticLength = USS_ACOUSTIC_LENGTH,
#if(USS_PULSE_MODE == USS_PULSE_MODE_SINGLE_TONE)
    .transducerFreq = USS_F1_FREQ,
#else
    .transducerFreq = ((USS_F1_FREQ + USS_F2_FREQ) / 2),
#endif
    .volumeScaleFactor = USS_VOLUME_SCALE_FACTOR,
    .volumeAddlScaleFactor = USS_VFR_LARGE_PIPE_ADDL_SF
};

#if defined(__MSP430_HAS_SAPH_A__) && (USS_PULSE_MODE == USS_PULSE_MODE_MULTI_TONE)
__persistent USS_Pulse_Additional_End_of_Sequence_Configuration ussEndOfSeq =
{
    .numOfTrillcycles = USS_NUM_OF_ADDTL_TRILL_PULSES,
#if (USS_NUM_OF_ADDTL_TRILL_PULSES > 0)
    .pNumOfEPulsArray = &xtraepulse[0],
    .pNumOfXPulsArray = &xtraxpulse[0],
    .pEPulsHPerArray = &xtrahper[0],
    .pEPulsLPerArray = &xtralper[0],
    .pXPulsHPerArray = &xtraxhper[0],
    .pXPulsLPerArray = &xtraxlper[0],
#endif
};

__persistent USS_Pulse_Multitone_Configuration multiToneConfig =
{
#if (USS_PULSE_MODE == USS_PULSE_MODE_MULTI_TONE)
    .origNumOfThrillCycles = USS_NUM_OF_TRILL_PULSES,
#endif
    .pNumOfEPulsArray = &epulse[0],
    .pNumOfXPulsArray = &xpulse[0],
    .pEPulsHPerArray = &hper[0],
    .pEPulsLPerArray = &lper[0],
    .pXPulsHPerArray = &xhper[0],
    .pXPulsLPerArray = &xlper[0],
    .pRAMPulseConfigArray = &RAM_XE[0],
    .pRAMDMAConfigArray = &RAM_DMA_CONFIG[0],
    .pEOFSeqConfig = &ussEndOfSeq,
};
#endif

__persistent USS_Pulse_Single_Dual_Tone_Configuration singDualToneConfig = {

#if ((USS_PULSE_MODE == USS_PULSE_MODE_SINGLE_TONE) ||    \
     (USS_PULSE_MODE == USS_PULSE_MODE_DUAL_TONE))
    .numOfF1Cycles = USS_NUM_OF_EXCITATION_PULSES_F1,
    .F1DutyCycle = (float) USS_PULSE_DUTYPERCENT_F1,
#if (USS_PULSE_MODE != USS_PULSE_MODE_SINGLE_TONE)
    .numOfF2Cycles = USS_NUM_OF_EXCITATION_PULSES_F2,
    .F2DutyCycle = (float) USS_PULSE_DUTYPERCENT_F2,
#else
    .numOfF2Cycles = 0,
    .F2DutyCycle   = 0,
#endif
#else
    .numOfF1Cycles = 0,
    .F1DutyCycle   = 0,
    .numOfF2Cycles = 0,
    .F2DutyCycle   = 0,
#endif

};

__persistent USS_Pulse_Configuration ussPulseConfig = {
    .pauseState = USS_PAUSE_STATE,
    .pulsePolarity = USS_PULSE_POLARITY,
    .F1Frequency = USS_F1_FREQ,
#ifdef USS_NUM_OF_STOP_PULSES
    .numOfStopPulses = USS_NUM_OF_STOP_PULSES,
#else
    .numOfStopPulses = 0,
#endif
#if (USS_PULSE_MODE != USS_PULSE_MODE_SINGLE_TONE)
    .F2Frequency = USS_F2_FREQ,
#endif


#if (USS_PULSE_MODE == USS_PULSE_MODE_SINGLE_TONE)
    .pulseGenMode = USS_measurement_pulse_generation_mode_single_tone,
    .pToneConfig = &singDualToneConfig,
#elif (USS_PULSE_MODE == USS_PULSE_MODE_DUAL_TONE)
    .pulseGenMode = USS_measurement_pulse_generation_mode_dual_tone,
    .pToneConfig = &singDualToneConfig,
#elif (USS_PULSE_MODE == USS_PULSE_MODE_MULTI_TONE)
    .pulseGenMode = USS_measurement_pulse_generation_mode_multi_tone,
    .pToneConfig = &multiToneConfig,
#endif
};

__persistent USS_Measurement_Configuration ussMeasurementConfig = {
    .ch0DriveStrength = USS_CH0_DRIVE_STRENGHT,
    .ch1DriveStrength = USS_CH1_DRIVE_STRENGHT,
    .sequenceSelection = USS_SEQUENCE_SELECTION,
    .eofSequenceState = USS_EOF_SEQUENCE_SELECTION,
    .pulseConfig = &ussPulseConfig,
    .startPPGCount = USS_START_PPG_COUNT,
    .turnOnADCCount = (uint_least16_t) USS_TURN_ON_ADC_COUNT,
    .startPGAandINBiasCount = USS_PGA_IN_BIAS_COUNT,
    .startADCsamplingCount = (uint16_t)USS_ADC_SAMP_COUNT,
    .restartCaptureCount = (uint_least16_t) USS_RESTART_CAP_COUNT,
    .captureTimeOutCount = USS_TIME_OUT_COUNT,
    .ulpBiasDelay = USS_ULP_BIAS_DELAY,
    .biasImpedance = USS_BIAS_IMPEDANCE,
    .muxChargePumpMode = USS_MUX_CHARGE_PUMP_MODE,
    .restartLowPowerCaptureCount =
        (uint_least16_t) USS_LOW_POWER_RESTART_CAP_COUNT,
#if (USSSWLIB_ENABLE_EXTERNAL_CIRCUITRY_CONTROL == true)
    .startRxEnCount = USS_MEASUREMENT_TURN_ON_EXTERNAL_AMP_COUNT,
#endif
};

__persistent USS_HSPLL_Configuration ussPLLConfig = {
    .ussXtalFreq = USS_PLL_XTAL_IN_MHZ,
    .pllOutputFreq = USS_HSPLL_FREQ,
    .outputPLLXtal = USS_OUTPUT_PLL_XTAL,
    .HSPLLInputCLKType = USS_HSPLL_INPUT_CLK_TYPE,
    .hspllTolerance = (uint16_t) USS_HSPLL_TOLERANCE,
    .ussXTALsettlingCount = USS_HSPLL_USSXTAL_SETTLING_COUNT,
};

__persistent USS_Interrupt_Configuration ussInterruptConfig = {
    .enableUUPSPREQIGInterrupt = USS_ENABLE_UUPSPREQIGINTERRUPT,
    .enableSAPHPingTransmitDoneInterrupt = USS_ENABLE_SAPH_PING_TRANSMIT
};

__persistent USS_Capture_Configuration ussCaptureConfig = {
    .overSampleRate = USS_OVER_SAMPLE_RATE,
    .sampleSize = USS_USER_CONFIG_NUMBER_OF_SAMPLES_PER_CAPTURE,
    .gainRange = USS_GAIN_RANGE,
    .enableWindowHiComp = USS_ENABLE_WINDOW_HI_COMP,
    .enableWindowLoComp = USS_ENABLE_WINDOW_LO_COMP,
    .windowHighThreshold = USS_WINDOW_HIGH_THRESHOLD,
    .windowLowThreshold = USS_WINDOW_LOW_THRESHOLD,
    .agcConstant = USS_AGC_CONSTANT,
    .pCapturesBuffer = &gUSSLEATempMemBlock[0],
    .maxCapture = (sizeof(gUSSLEATempMemBlock) / sizeof(int16_t)),
    .isCapAccumulationEnabled = USS_SW_LIB_ENABLE_ACCUMULATION,
#if USS_SW_LIB_APP_MAX_ACC_BLOCK
    .pAccCaptureBuffer = &gUSSLEARAMReservedAccMemBlock[0],
#endif
};

__persistent USS_Trigger_Configuration ussTriggerConfig = {
    .triggerConfig = USS_TRIGGER_CONFIG
};

__persistent USS_Algorithms_User_Configuration ussAlgConfig = {
    .absToFOption              = USS_ALG_ABS_TOF_COMPUTATION,
    .dtoFCalcOption            = (USS_Alg_dToF_Calculation_Option)USS_ALG_DELTA_TOF_COMPUTATION_OPTION,
    .volumeCalOption           = USS_ALG_VOLUME_RATE_COMPUTATION_OPTION,
    .clockRelativeError        = USS_ALG_CLOCK_RELATIVERROR,
    .absTOFInterval            = USS_ALG_ABS_TOF_INTERVAL,
    .dtofVolInterval           = USS_ALG_DTOF_INTERVAL,
    .calibratedDCOffsetUPS     = USS_ALG_CALIBRATED_UPS_DC_OFFSET,
    .calibratedDCOffsetDNS     = USS_ALG_CALIBRATED_DNS_DC_OFFSET,
    .ADCAdditionalCaptureDelay = USS_ALG_ADC_ADDITIONAL_CAP_DLY,
    .dcOffset                  = USS_ALG_DCOFFSET,
    .windowingMode             = USS_ALG_DTOF_WINDOWING_MODE,
#if(USS_ALG_DTOF_WINDOWING_MODE != USS_ALG_DTOF_EST_WINDOW_OPTION_DISABLED)
    .winStartIndexBackOffNumCycles = USS_ALG_WIN_START_INDEX_BACK_OFF_NUM_CYCLES,
    .winTrapzRampOverNumCycles     = USS_ALG_WIN_TRAP_RAMP_NUM_CYCLES,
    .winNumCycles                  = USS_ALG_WIN_NUM_CYCLES,
    .winPeakIndex2EdgeNumCycles    = USS_ALG_WIN_PEAK_INDEX_2_EDGES_NUM_CYLES,
#endif
    .enableFilter = USS_ALG_FILT_IS_FILTER_ENABLED,
#if(USS_ALG_FILT_IS_FILTER_ENABLED == true)
    .filterCoeffs = &gUSSFilterCoeffs[USS_ALG_FILT_OPTION][0],
    .filterLength = (sizeof(gUSSFilterCoeffs[USS_ALG_FILT_OPTION])
                     / sizeof(int16_t)),
#endif


#if defined(USS_ALG_SEARCH_LOBE_SAMP)
     .searchLobeSampleSteps = USS_ALG_SEARCH_LOBE_SAMP,
#else
     .searchLobeSampleSteps = 1,
#endif


#if defined(USS_ALG_NUM_PULS_BEFORE_THRSH)
     .numPulsesBeforeThreshold = USS_ALG_NUM_PULS_BEFORE_THRSH,
#else
     .numPulsesBeforeThreshold = 1,
#endif

#if defined(USS_ALG_RATIO_OF_TRACK_LOBE)
     .ratioOfTrackLobeToPeak = USS_ALG_RATIO_OF_TRACK_LOBE,
#else
     .ratioOfTrackLobeToPeak = 0.11111,
#endif
#if defined(USS_ALG_MAX_RATIO_PEAK_2_PEAK_VAR)
     .maxRatioPeak2PeakVariation = USS_ALG_MAX_RATIO_PEAK_2_PEAK_VAR,
#else
     .maxRatioPeak2PeakVariation = 0.2,
#endif
#if defined(USS_ALG_CORR_VAL_THRSH_CHK_FACT)
     .corrValueThresholdCheckFactor = USS_ALG_CORR_VAL_THRSH_CHK_FACT,
#else
     .corrValueThresholdCheckFactor = 0.05,
#endif
#if defined(USS_ALG_SIGN_VAL_THRSH_CHK)
     .signalValueThresholdCheck = USS_ALG_SIGN_VAL_THRSH_CHK,
#else
     .signalValueThresholdCheck = 100,
#endif
#if defined(USS_ALG_HIGH_FLOW_OPTION)
     .highFlowOption = (USS_highFlow_option)USS_ALG_HIGH_FLOW_OPTION,
#else
     .highFlowOption = (USS_highFlow_option)USS_highFlow_option_disabled,
#endif
#if defined(USS_ALG_CYCLESLIPTHRESHOLD)
     .cycleSlipThreshold = USS_ALG_CYCLESLIPTHRESHOLD,
#else
     .cycleSlipThreshold = 1.1,
#endif

#if defined(USS_ALG_THRESHOLDX1X3)
     .thresholdX1X3 = USS_ALG_THRESHOLDX1X3,
#else
     .thresholdX1X3 = 2000000,
#endif

#if defined(USS_ALG_MAX_SAMPLE_SHIFT)
    .maxSampleShift = USS_ALG_MAX_SAMPLE_SHIFT,
#else
#if ((USS_ALG_ABS_TOF_COMPUTATION_MODE == USS_ALG_ABS_TOF_COMPUTATION_MODE_LOBE_WIDE) || \
     (USS_ALG_ABS_TOF_COMPUTATION_MODE == USS_ALG_ABS_TOF_COMPUTATION_MODE_HILBERT_WIDE))
    .maxSampleShift = 20,
#else
    .maxSampleShift = 6,
#endif
#endif


#if defined(USS_ALG_NUM_CYCLES_SEARCH_CORR)
    .numCycleSearchCorrPeak = USS_ALG_NUM_CYCLES_SEARCH_CORR,
#else
    .numCycleSearchCorrPeak = 2,
#endif
    .pNvMemBuffer = &gNVMemBlock[0],
#if(USS_ALG_DTOF_WINDOWING_MODE != USS_ALG_DTOF_EST_WINDOW_OPTION_DISABLED)
    .pLEAMemBuffer1 = &gUSSLEARAMReservedBlock1[0],
#endif
    .pLEAMemBuffer2 = &gUSSLEARAMReservedBlock2[0],
    .hilbertTransformCoeffs = &gUSSHilbertCoeffs[USS_HILB_ALG_FILT_OPTION][0],
    .hilbertTransformCoeffsLength =
        (sizeof(gUSSHilbertCoeffs[USS_HILB_ALG_FILT_OPTION])
         / sizeof(int16_t)),
    .pBinaryPattern = &gUSSBinaryPattern[0],
    .maxBinaryPatternLenght = (sizeof(gUSSBinaryPattern) / sizeof(int16_t)),

#if(USS_NUM_OF_ADDTL_TRILL_PULSES>0)
    .pAdditionalBinaryPattern = &additionalBinarySequence[0],
#endif
#ifndef USS_ADDTL_BIN_PATTERN_SIZE
    .additionalPatternLength = 0,
#else
    .additionalPatternLength = USS_ADDTL_BIN_PATTERN_SIZE,
#endif

#if ((USS_ALG_ABS_TOF_COMPUTATION_MODE == USS_ALG_ABS_TOF_COMPUTATION_MODE_HILBERT) || \
     (USS_ALG_ABS_TOF_COMPUTATION_MODE == USS_ALG_ABS_TOF_COMPUTATION_MODE_HILBERT_WIDE) || \
     (USS_ALG_ABS_TOF_COMPUTATION_MODE == USS_ALG_ABS_TOF_COMPUTATION_MODE_LOBE_WIDE))
    .negSearchRange = USS_ALG_ABS_TOF_NEG_SEARCH_RANGE,
    .posSearchRange = USS_ALG_ABS_TOF_POS_SEARCH_RANGE,
#else
    .negSearchRange = -20,
    .posSearchRange = 2,
    .crossThreshold = 20,
#endif

#if ((USS_ALG_ABS_TOF_COMPUTATION_MODE == USS_ALG_ABS_TOF_COMPUTATION_MODE_HILBERT) || \
     (USS_ALG_ABS_TOF_COMPUTATION_MODE == USS_ALG_ABS_TOF_COMPUTATION_MODE_HILBERT_WIDE))
    .crossThreshold = USS_ALG_ABS_TOF_HILB_CROSS_THRESHOLD,
#else
    .crossThreshold = 20,
#endif


#if (defined(USS_ENABLE_ABSTOF_LOBE_OFFSET_CORRECTION) && (USS_ENABLE_ABSTOF_LOBE_OFFSET_CORRECTION == true))
    .pInterpCorrectionTablePtr   = gUSSAbsToFLUT,
    .interpCorrectionTableLenght = sizeof(gUSSAbsToFLUT)/(2*sizeof(int16_t)),
#else
    .pInterpCorrectionTablePtr = NULL,
    .interpCorrectionTableLenght = 0,
#endif

#if(USS_ALG_ENABLE_ESTIMATE_TEMPERATURE == true)
    .tempCalcObject = &ussAlgorithmTemperatureCalcObj,
    .temperatureCalcOption = USS_Alg_temperature_Calculation_Option_enabled,
#else
    .tempCalcObject = NULL,
    .temperatureCalcOption = USS_Alg_temperature_Calculation_Option_disabled,
#endif

#if (USS_ALG_VFR_CALIB_MODE==USS_ALG_VFR_CALIB_OPTION_FLOW)
    .volumeCalibrationOption = USS_Alg_volume_flow_Calibration_Option_flow,
    .calibObject.flowCalibObject = &ussAlgorithmVolumeFlowObj,
#elif (USS_ALG_VFR_CALIB_MODE==USS_ALG_VFR_CALIB_OPTION_FLOW_TEMPERATURE)
    .volumeCalibrationOption = USS_Alg_volume_flow_Calibration_Option_flow_temperature,
    .calibObject.flowTempCalibObject = &ussAlgorithmVolumeFlowTemperatureObj,
#else
    .volumeCalibrationOption = USS_Alg_volume_flow_Calibration_Option_disabled,
    .calibObject = NULL,
#endif
    .isInitAlgorithms = USS_ALG_IS_INIT_ALGORITHMS,
};

__persistent USS_SW_Library_configuration gUssSWConfig = {
    .systemConfig = &ussSystemConfig,
    .meterConfig = &ussMeterConfig,
    .measurementConfig = &ussMeasurementConfig,
    .pllConfiguration = &ussPLLConfig,
    .captureConfig = &ussCaptureConfig,
    .triggerConfig = &ussTriggerConfig,
    .interruptConfig = &ussInterruptConfig,
    .algorithmsConfig = &ussAlgConfig,
};

