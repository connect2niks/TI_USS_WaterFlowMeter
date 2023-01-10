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
#ifndef USS_INTRPL_CORR_LUT_H_
#define USS_INTRPL_CORR_LUT_H_
//#############################################################################
//
//! \file   USS_intrplCorrLUT.h
//!
//! \brief  USS SW Library Absolute Time of Flight offset correction look-up
//!         table
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

#include "QmathLib.h"

#define USS_INTRPL_CORR_LUT_RES      (256)

#if USS_INTRPL_CORR_LUT_RES
//******************************************************************************
// The following Look-up table (LUT) was generated using the parameters below:
//
// Signal Sample Freq  = 4000 kHz
// Transducer Freq     = 1000 kHz
// Resolution          = 256
//
//******************************************************************************
#define USS_INTRPL_CORR_LUT_VALUES                                           \
{                                                                            \
    {_Q15(0.000000), _Q15(0.414214)},                                        \
    {_Q15(0.002842), _Q15(0.408700)},                                        \
    {_Q15(0.005689), _Q15(0.403209)},                                        \
    {_Q15(0.008541), _Q15(0.397739)},                                        \
    {_Q15(0.011398), _Q15(0.392292)},                                        \
    {_Q15(0.014260), _Q15(0.386867)},                                        \
    {_Q15(0.017126), _Q15(0.381466)},                                        \
    {_Q15(0.019997), _Q15(0.376087)},                                        \
    {_Q15(0.022871), _Q15(0.370732)},                                        \
    {_Q15(0.025750), _Q15(0.365401)},                                        \
    {_Q15(0.028633), _Q15(0.360093)},                                        \
    {_Q15(0.031519), _Q15(0.354810)},                                        \
    {_Q15(0.034408), _Q15(0.349551)},                                        \
    {_Q15(0.037300), _Q15(0.344318)},                                        \
    {_Q15(0.040195), _Q15(0.339109)},                                        \
    {_Q15(0.043092), _Q15(0.333926)},                                        \
    {_Q15(0.045992), _Q15(0.328768)},                                        \
    {_Q15(0.048893), _Q15(0.323637)},                                        \
    {_Q15(0.051796), _Q15(0.318532)},                                        \
    {_Q15(0.054701), _Q15(0.313453)},                                        \
    {_Q15(0.057607), _Q15(0.308401)},                                        \
    {_Q15(0.060513), _Q15(0.303377)},                                        \
    {_Q15(0.063420), _Q15(0.298380)},                                        \
    {_Q15(0.066327), _Q15(0.293411)},                                        \
    {_Q15(0.069234), _Q15(0.288471)},                                        \
    {_Q15(0.072140), _Q15(0.283558)},                                        \
    {_Q15(0.075046), _Q15(0.278675)},                                        \
    {_Q15(0.077950), _Q15(0.273821)},                                        \
    {_Q15(0.080853), _Q15(0.268996)},                                        \
    {_Q15(0.083754), _Q15(0.264202)},                                        \
    {_Q15(0.086652), _Q15(0.259437)},                                        \
    {_Q15(0.089548), _Q15(0.254703)},                                        \
    {_Q15(0.092441), _Q15(0.250000)},                                        \
    {_Q15(0.095331), _Q15(0.245328)},                                        \
    {_Q15(0.098217), _Q15(0.240688)},                                        \
    {_Q15(0.101098), _Q15(0.236080)},                                        \
    {_Q15(0.103975), _Q15(0.231504)},                                        \
    {_Q15(0.106847), _Q15(0.226961)},                                        \
    {_Q15(0.109713), _Q15(0.222450)},                                        \
    {_Q15(0.112573), _Q15(0.217974)},                                        \
    {_Q15(0.115427), _Q15(0.213530)},                                        \
    {_Q15(0.118274), _Q15(0.209122)},                                        \
    {_Q15(0.121114), _Q15(0.204747)},                                        \
    {_Q15(0.123945), _Q15(0.200408)},                                        \
    {_Q15(0.126769), _Q15(0.196104)},                                        \
    {_Q15(0.129583), _Q15(0.191835)},                                        \
    {_Q15(0.132389), _Q15(0.187603)},                                        \
    {_Q15(0.135184), _Q15(0.183407)},                                        \
    {_Q15(0.137969), _Q15(0.179248)},                                        \
    {_Q15(0.140743), _Q15(0.175126)},                                        \
    {_Q15(0.143506), _Q15(0.171041)},                                        \
    {_Q15(0.146257), _Q15(0.166995)},                                        \
    {_Q15(0.148995), _Q15(0.162987)},                                        \
    {_Q15(0.151721), _Q15(0.159018)},                                        \
    {_Q15(0.154432), _Q15(0.155088)},                                        \
    {_Q15(0.157130), _Q15(0.151198)},                                        \
    {_Q15(0.159812), _Q15(0.147347)},                                        \
    {_Q15(0.162480), _Q15(0.143538)},                                        \
    {_Q15(0.165131), _Q15(0.139769)},                                        \
    {_Q15(0.167766), _Q15(0.136041)},                                        \
    {_Q15(0.170383), _Q15(0.132354)},                                        \
    {_Q15(0.172983), _Q15(0.128710)},                                        \
    {_Q15(0.175564), _Q15(0.125109)},                                        \
    {_Q15(0.178126), _Q15(0.121550)},                                        \
    {_Q15(0.180669), _Q15(0.118034)},                                        \
    {_Q15(0.183191), _Q15(0.114562)},                                        \
    {_Q15(0.185692), _Q15(0.111134)},                                        \
    {_Q15(0.188172), _Q15(0.107751)},                                        \
    {_Q15(0.190629), _Q15(0.104412)},                                        \
    {_Q15(0.193064), _Q15(0.101119)},                                        \
    {_Q15(0.195474), _Q15(0.097872)},                                        \
    {_Q15(0.197861), _Q15(0.094670)},                                        \
    {_Q15(0.200222), _Q15(0.091516)},                                        \
    {_Q15(0.202558), _Q15(0.088408)},                                        \
    {_Q15(0.204868), _Q15(0.085347)},                                        \
    {_Q15(0.207151), _Q15(0.082334)},                                        \
    {_Q15(0.209406), _Q15(0.079370)},                                        \
    {_Q15(0.211632), _Q15(0.076454)},                                        \
    {_Q15(0.213830), _Q15(0.073586)},                                        \
    {_Q15(0.215998), _Q15(0.070769)},                                        \
    {_Q15(0.218136), _Q15(0.068000)},                                        \
    {_Q15(0.220243), _Q15(0.065282)},                                        \
    {_Q15(0.222318), _Q15(0.062615)},                                        \
    {_Q15(0.224360), _Q15(0.059998)},                                        \
    {_Q15(0.226370), _Q15(0.057433)},                                        \
    {_Q15(0.228346), _Q15(0.054919)},                                        \
    {_Q15(0.230287), _Q15(0.052457)},                                        \
    {_Q15(0.232193), _Q15(0.050048)},                                        \
    {_Q15(0.234064), _Q15(0.047691)},                                        \
    {_Q15(0.235898), _Q15(0.045387)},                                        \
    {_Q15(0.237695), _Q15(0.043137)},                                        \
    {_Q15(0.239455), _Q15(0.040941)},                                        \
    {_Q15(0.241176), _Q15(0.038798)},                                        \
    {_Q15(0.242859), _Q15(0.036710)},                                        \
    {_Q15(0.244502), _Q15(0.034677)},                                        \
    {_Q15(0.246104), _Q15(0.032699)},                                        \
    {_Q15(0.247666), _Q15(0.030776)},                                        \
    {_Q15(0.249187), _Q15(0.028910)},                                        \
    {_Q15(0.250665), _Q15(0.027099)},                                        \
    {_Q15(0.252101), _Q15(0.025344)},                                        \
    {_Q15(0.253495), _Q15(0.023646)},                                        \
    {_Q15(0.254844), _Q15(0.022005)},                                        \
    {_Q15(0.256149), _Q15(0.020421)},                                        \
    {_Q15(0.257410), _Q15(0.018895)},                                        \
    {_Q15(0.258626), _Q15(0.017426)},                                        \
    {_Q15(0.259796), _Q15(0.016016)},                                        \
    {_Q15(0.260920), _Q15(0.014663)},                                        \
    {_Q15(0.261997), _Q15(0.013369)},                                        \
    {_Q15(0.263027), _Q15(0.012133)},                                        \
    {_Q15(0.264010), _Q15(0.010957)},                                        \
    {_Q15(0.264945), _Q15(0.009839)},                                        \
    {_Q15(0.265831), _Q15(0.008781)},                                        \
    {_Q15(0.266670), _Q15(0.007782)},                                        \
    {_Q15(0.267459), _Q15(0.006843)},                                        \
    {_Q15(0.268198), _Q15(0.005964)},                                        \
    {_Q15(0.268889), _Q15(0.005144)},                                        \
    {_Q15(0.269529), _Q15(0.004385)},                                        \
    {_Q15(0.270119), _Q15(0.003686)},                                        \
    {_Q15(0.270659), _Q15(0.003047)},                                        \
    {_Q15(0.271148), _Q15(0.002469)},                                        \
    {_Q15(0.271586), _Q15(0.001951)},                                        \
    {_Q15(0.271973), _Q15(0.001494)},                                        \
    {_Q15(0.272308), _Q15(0.001098)},                                        \
    {_Q15(0.272593), _Q15(0.000763)},                                        \
    {_Q15(0.272825), _Q15(0.000488)},                                        \
    {_Q15(0.273006), _Q15(0.000275)},                                        \
    {_Q15(0.273136), _Q15(0.000122)},                                        \
    {_Q15(0.273214), _Q15(0.000031)},                                        \
    {_Q15(0.273214), _Q15(0.000000)},                                        \
    {_Q15(0.273214), _Q15(0.000031)},                                        \
    {_Q15(0.273136), _Q15(0.000122)},                                        \
    {_Q15(0.273006), _Q15(0.000275)},                                        \
    {_Q15(0.272825), _Q15(0.000488)},                                        \
    {_Q15(0.272593), _Q15(0.000763)},                                        \
    {_Q15(0.272308), _Q15(0.001098)},                                        \
    {_Q15(0.271973), _Q15(0.001494)},                                        \
    {_Q15(0.271586), _Q15(0.001951)},                                        \
    {_Q15(0.271148), _Q15(0.002469)},                                        \
    {_Q15(0.270659), _Q15(0.003047)},                                        \
    {_Q15(0.270119), _Q15(0.003686)},                                        \
    {_Q15(0.269529), _Q15(0.004385)},                                        \
    {_Q15(0.268889), _Q15(0.005144)},                                        \
    {_Q15(0.268198), _Q15(0.005964)},                                        \
    {_Q15(0.267459), _Q15(0.006843)},                                        \
    {_Q15(0.266670), _Q15(0.007782)},                                        \
    {_Q15(0.265831), _Q15(0.008781)},                                        \
    {_Q15(0.264945), _Q15(0.009839)},                                        \
    {_Q15(0.264010), _Q15(0.010957)},                                        \
    {_Q15(0.263027), _Q15(0.012133)},                                        \
    {_Q15(0.261997), _Q15(0.013369)},                                        \
    {_Q15(0.260920), _Q15(0.014663)},                                        \
    {_Q15(0.259796), _Q15(0.016016)},                                        \
    {_Q15(0.258626), _Q15(0.017426)},                                        \
    {_Q15(0.257410), _Q15(0.018895)},                                        \
    {_Q15(0.256149), _Q15(0.020421)},                                        \
    {_Q15(0.254844), _Q15(0.022005)},                                        \
    {_Q15(0.253495), _Q15(0.023646)},                                        \
    {_Q15(0.252101), _Q15(0.025344)},                                        \
    {_Q15(0.250665), _Q15(0.027099)},                                        \
    {_Q15(0.249187), _Q15(0.028910)},                                        \
    {_Q15(0.247666), _Q15(0.030776)},                                        \
    {_Q15(0.246104), _Q15(0.032699)},                                        \
    {_Q15(0.244502), _Q15(0.034677)},                                        \
    {_Q15(0.242859), _Q15(0.036710)},                                        \
    {_Q15(0.241176), _Q15(0.038798)},                                        \
    {_Q15(0.239455), _Q15(0.040941)},                                        \
    {_Q15(0.237695), _Q15(0.043137)},                                        \
    {_Q15(0.235898), _Q15(0.045387)},                                        \
    {_Q15(0.234064), _Q15(0.047691)},                                        \
    {_Q15(0.232193), _Q15(0.050048)},                                        \
    {_Q15(0.230287), _Q15(0.052457)},                                        \
    {_Q15(0.228346), _Q15(0.054919)},                                        \
    {_Q15(0.226370), _Q15(0.057433)},                                        \
    {_Q15(0.224360), _Q15(0.059998)},                                        \
    {_Q15(0.222318), _Q15(0.062615)},                                        \
    {_Q15(0.220243), _Q15(0.065282)},                                        \
    {_Q15(0.218136), _Q15(0.068000)},                                        \
    {_Q15(0.215998), _Q15(0.070769)},                                        \
    {_Q15(0.213830), _Q15(0.073586)},                                        \
    {_Q15(0.211632), _Q15(0.076454)},                                        \
    {_Q15(0.209406), _Q15(0.079370)},                                        \
    {_Q15(0.207151), _Q15(0.082334)},                                        \
    {_Q15(0.204868), _Q15(0.085347)},                                        \
    {_Q15(0.202558), _Q15(0.088408)},                                        \
    {_Q15(0.200222), _Q15(0.091516)},                                        \
    {_Q15(0.197861), _Q15(0.094670)},                                        \
    {_Q15(0.195474), _Q15(0.097872)},                                        \
    {_Q15(0.193064), _Q15(0.101119)},                                        \
    {_Q15(0.190629), _Q15(0.104412)},                                        \
    {_Q15(0.188172), _Q15(0.107751)},                                        \
    {_Q15(0.185692), _Q15(0.111134)},                                        \
    {_Q15(0.183191), _Q15(0.114562)},                                        \
    {_Q15(0.180669), _Q15(0.118034)},                                        \
    {_Q15(0.178126), _Q15(0.121550)},                                        \
    {_Q15(0.175564), _Q15(0.125109)},                                        \
    {_Q15(0.172983), _Q15(0.128710)},                                        \
    {_Q15(0.170383), _Q15(0.132354)},                                        \
    {_Q15(0.167766), _Q15(0.136041)},                                        \
    {_Q15(0.165131), _Q15(0.139769)},                                        \
    {_Q15(0.162480), _Q15(0.143538)},                                        \
    {_Q15(0.159812), _Q15(0.147347)},                                        \
    {_Q15(0.157130), _Q15(0.151198)},                                        \
    {_Q15(0.154432), _Q15(0.155088)},                                        \
    {_Q15(0.151721), _Q15(0.159018)},                                        \
    {_Q15(0.148995), _Q15(0.162987)},                                        \
    {_Q15(0.146257), _Q15(0.166995)},                                        \
    {_Q15(0.143506), _Q15(0.171041)},                                        \
    {_Q15(0.140743), _Q15(0.175126)},                                        \
    {_Q15(0.137969), _Q15(0.179248)},                                        \
    {_Q15(0.135184), _Q15(0.183407)},                                        \
    {_Q15(0.132389), _Q15(0.187603)},                                        \
    {_Q15(0.129583), _Q15(0.191835)},                                        \
    {_Q15(0.126769), _Q15(0.196104)},                                        \
    {_Q15(0.123945), _Q15(0.200408)},                                        \
    {_Q15(0.121114), _Q15(0.204747)},                                        \
    {_Q15(0.118274), _Q15(0.209122)},                                        \
    {_Q15(0.115427), _Q15(0.213530)},                                        \
    {_Q15(0.112573), _Q15(0.217974)},                                        \
    {_Q15(0.109713), _Q15(0.222450)},                                        \
    {_Q15(0.106847), _Q15(0.226961)},                                        \
    {_Q15(0.103975), _Q15(0.231504)},                                        \
    {_Q15(0.101098), _Q15(0.236080)},                                        \
    {_Q15(0.098217), _Q15(0.240688)},                                        \
    {_Q15(0.095331), _Q15(0.245328)},                                        \
    {_Q15(0.092441), _Q15(0.250000)},                                        \
    {_Q15(0.089548), _Q15(0.254703)},                                        \
    {_Q15(0.086652), _Q15(0.259437)},                                        \
    {_Q15(0.083754), _Q15(0.264202)},                                        \
    {_Q15(0.080853), _Q15(0.268996)},                                        \
    {_Q15(0.077950), _Q15(0.273821)},                                        \
    {_Q15(0.075046), _Q15(0.278675)},                                        \
    {_Q15(0.072140), _Q15(0.283558)},                                        \
    {_Q15(0.069234), _Q15(0.288471)},                                        \
    {_Q15(0.066327), _Q15(0.293411)},                                        \
    {_Q15(0.063420), _Q15(0.298380)},                                        \
    {_Q15(0.060513), _Q15(0.303377)},                                        \
    {_Q15(0.057607), _Q15(0.308401)},                                        \
    {_Q15(0.054701), _Q15(0.313453)},                                        \
    {_Q15(0.051796), _Q15(0.318532)},                                        \
    {_Q15(0.048893), _Q15(0.323637)},                                        \
    {_Q15(0.045992), _Q15(0.328768)},                                        \
    {_Q15(0.043092), _Q15(0.333926)},                                        \
    {_Q15(0.040195), _Q15(0.339109)},                                        \
    {_Q15(0.037300), _Q15(0.344318)},                                        \
    {_Q15(0.034408), _Q15(0.349551)},                                        \
    {_Q15(0.031519), _Q15(0.354810)},                                        \
    {_Q15(0.028633), _Q15(0.360093)},                                        \
    {_Q15(0.025750), _Q15(0.365401)},                                        \
    {_Q15(0.022871), _Q15(0.370732)},                                        \
    {_Q15(0.019997), _Q15(0.376087)},                                        \
    {_Q15(0.017126), _Q15(0.381466)},                                        \
    {_Q15(0.014260), _Q15(0.386867)},                                        \
    {_Q15(0.011398), _Q15(0.392292)},                                        \
    {_Q15(0.008541), _Q15(0.397739)},                                        \
    {_Q15(0.005689), _Q15(0.403209)},                                        \
    {_Q15(0.002842), _Q15(0.408700)}                                         \
}
#endif

#endif /* USS_INTRPL_CORR_LUT_H_ */
