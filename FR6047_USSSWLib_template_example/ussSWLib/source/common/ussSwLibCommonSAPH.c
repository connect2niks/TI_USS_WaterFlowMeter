//*****************************************************************************
// ussSwLibCommon.c
//
// TI Release: USSLib_02_40_00_00
// Release Date: __LIB_RELEASE_DATE__
//
//*****************************************************************************
#include "ussSwLibCommonSAPH.h"
#include "USS_Config/USS_userConfig.h"

/*
 * Multi-tone definition
 */


#define E_HPER_STATE                                           0
#define E_LPER_STATE                                           1
#define X_HPER_STATE                                           2
#define X_LPER_STATE                                           3
#define TOTAL_NUM_OF_STATES                                    4

#if defined(__MSP430_HAS_SAPH_A__) && (USS_PULSE_MODE == USS_PULSE_MODE_MULTI_TONE)
static USS_message_code privatePadMultiToneConfig(USS_SW_Library_configuration *config,
                               USS_Pulse_Multitone_Configuration* multConf);

static uint16_t privatePadPulses(uint16_t minPulseCount,
        uint16_t numOfTrillcycles, uint16_t * pNumOfPulsArray,
        uint16_t * pPulsLPerArray, uint16_t * pPulsHPerArray);
#endif

/*******************************************************************************
 * IMPORTANT: All of theese functions assume that SAPH registers are unlocked
 *******************************************************************************/
USS_message_code commonConfigurePPGDutyCyle(
		USS_SW_Library_configuration *config,
		USS_measurement_pulse_generation_mode mode)
{
    USS_message_code code;
    uint64_t temp;
    uint32_t hspllFreq;
#if ((USS_PULSE_MODE == USS_PULSE_MODE_SINGLE_TONE) || \
    (USS_PULSE_MODE == USS_PULSE_MODE_DUAL_TONE))
    uint16_t lper;
#endif
    uint16_t per, hper;
#if defined(__MSP430_HAS_SAPH_A__) && (USS_PULSE_MODE == USS_PULSE_MODE_DUAL_TONE)
    uint16_t xper, xlper, xhper;
#endif
    USS_Pulse_Single_Dual_Tone_Configuration *sDTConf;

    code = USS_message_code_no_error;


    sDTConf = (USS_Pulse_Single_Dual_Tone_Configuration *)config->measurementConfig->pulseConfig->pToneConfig;

    hspllFreq = commonGetHSPLLFreqInHz(config);

    temp = (uint64_t)((uint64_t)hspllFreq * (uint64_t)(100));
    temp <<= 4;
    temp /= (uint64_t)(config->measurementConfig->pulseConfig->F1Frequency);

    per = (uint16_t)(temp / 1600);

    temp = ((temp >> 4)% 100);

    if(temp>50)
    {
        per++;
    }

    temp = (uint64_t)((uint64_t)hspllFreq * (uint64_t)sDTConf->F1DutyCycle);
    temp <<= 4;
    temp /= (uint64_t)(config->measurementConfig->pulseConfig->F1Frequency);

    hper = (uint16_t)(temp / 1600);

    temp = ((temp >> 4)% 100);

    if(temp>50)
    {
        hper++;
    }

#if ((USS_PULSE_MODE == USS_PULSE_MODE_SINGLE_TONE) || \
    (USS_PULSE_MODE == USS_PULSE_MODE_DUAL_TONE))
    lper = per - hper;
#endif

#if (USS_PULSE_MODE == USS_PULSE_MODE_SINGLE_TONE)
    if(USS_measurement_pulse_generation_mode_single_tone == mode)
    {
        if((hper > 255) || (lper > 255))
        {
            // PPG cannot generate the selected frequency
            code = USS_message_code_SAPH_invalid_pulse_configuration_error;
        }else
        {

        // Start PPG Configuration
        GENERIC_SAPH_PGC = ((sDTConf->numOfF1Cycles) |
                    ((config->measurementConfig->pulseConfig->numOfStopPulses) << 8));
#if defined(__MSP430_HAS_SAPH_A__)
        GENERIC_SAPH_XPGCTL = (ETY_0 | XMOD_0);
#endif
        GENERIC_SAPH_LP_E_PULS = lper;
        GENERIC_SAPH_HP_E_PULS = hper;

        code = USS_message_code_no_error;
        }
    }
#endif
#if defined(__MSP430_HAS_SAPH_A__) && (USS_PULSE_MODE == USS_PULSE_MODE_DUAL_TONE)
    //If generation mode is dual tone configure xpulse low phase and high phase
    if(USS_measurement_pulse_generation_mode_dual_tone == mode)
    {

        temp = (uint64_t)((uint64_t)hspllFreq * (uint64_t)(100));
        temp <<= 4;
        temp /= (uint64_t)(config->measurementConfig->pulseConfig->F2Frequency);

        xper = (uint16_t)(temp / 1600);

        temp = ((temp >> 4)% 100);

        if(temp>50)
        {
            xper++;
        }

        temp = (uint64_t)((uint64_t)hspllFreq * (uint64_t)sDTConf->F2DutyCycle);
        temp <<= 4;
        temp /= (uint64_t)(config->measurementConfig->pulseConfig->F2Frequency);

        xhper = (uint16_t)(temp / 1600);

        temp = ((temp >> 4)% 100);

        if(temp>50)
        {
            xhper++;
        }

        xlper = xper - xhper;


        if((hper > 255) || (lper > 255) || (xhper > 255) || (xlper > 255))
        {
            // PPG cannot generate the selected frequency
            code = USS_message_code_SAPH_invalid_pulse_configuration_error;
        }else
        {
        // In dual tone sequence in Pause-xpulses-epulse-pause
        GENERIC_SAPH_PGC = ((sDTConf->numOfF1Cycles) |
                ((config->measurementConfig->pulseConfig->numOfStopPulses) << 8));
        GENERIC_SAPH_XPGCTL = (ETY_0 | XMOD_2 | sDTConf->numOfF2Cycles);
        GENERIC_SAPH_LP_E_PULS = xlper;
        GENERIC_SAPH_HP_E_PULS = xhper;
        GENERIC_SAPH_LP_X_PULS = lper;
        GENERIC_SAPH_HP_X_PULS = hper;

        code = USS_message_code_no_error;

        }
    }
#endif

    return code;
}



USS_message_code commonConfigurePPGForManualMode(
		USS_SW_Library_configuration *config, USS_test_channel pPGChannel)
{
	USS_message_code code;

	if(UUPSCTL & USS_BUSY)
	{
		return USS_message_code_USS_ongoing_active_conversion_error;
	}


	code = USS_updateHSPLLConfiguration(config);

	if(code != USS_message_code_no_error)
	{
	    return code;
	}

    code = USS_updateSAPHConfiguration(config);

    if(code != USS_message_code_no_error)
    {
        return code;
    }

	//  Disable Acquisition Sequencer
	UUPSCTL &= ~(ASQEN);

	// Prepare SAPH module for manual trigger

    // Unlock SAPH registers
    GENERIC_SAPH_KEY = KEY;

    // Configure Channel selection which PPG acts on
    if(USS_test_channel_1 == pPGChannel)
    {
      GENERIC_SAPH_PGCTL = (TRSEL_0| PPGCHSEL_1 | PGSEL_0);
    }else
    {
      GENERIC_SAPH_PGCTL = (TRSEL_0| PPGCHSEL_0 | PGSEL_0);
    }

    // Finish PPG configuration
    GENERIC_SAPH_PGCTL |= (PPGEN);

    // Lock SAPH registers
    GENERIC_SAPH_KEY = 0;

    // Confirm HSPLL is locked
    code = commonPrepareForUSSPowerUp(config);
    if(USS_message_code_no_error != code)
    {
      return code;
    }

    code = commonPowerUpUSS(config);
    if(USS_message_code_no_error != code)
    {
      return code;
    }

    // Wait until USS module is in READY state
    while((UUPSCTL & UPSTATE_3) != UPSTATE_3);

	return code;
}

USS_message_code commonValidateSAPHconfigruation(
		USS_SW_Library_configuration *config)
{
	volatile int32_t temp;
	USS_silicon_version version;
	USS_silicon_variant variant;


	if((config->measurementConfig->startPPGCount < 2))
	{
		return USS_message_code_SAPH_time_startPPGCount_error;
	}

    version = commonDetermineSiliconVersion();
    variant = commonDetermineVariant();

    if(((variant != USS_silicon_version_variant_FR6047) ||
            ((variant == USS_silicon_version_variant_FR6047) &&
                    version != USS_silicon_version_A))  &&
            (config->measurementConfig->ulpBiasDelay !=
                    USS_measurement_ULP_bias_delay_no_delay))
    {
        if((config->measurementConfig->startPGAandINBiasCount != 0))
        {
            return USS_message_code_SAPH_time_startPGAandINBiasCount_error;
        }
    }else
    {
        if((config->measurementConfig->startPGAandINBiasCount <2))
        {
            return USS_message_code_SAPH_time_startPGAandINBiasCount_error;
        }
    }

	if((config->measurementConfig->turnOnADCCount < 2))
	{
		return USS_message_code_SAPH_time_turnOnADCCount_error;
	}

	if((config->measurementConfig->startADCsamplingCount < 2))
	{
		return USS_message_code_SAPH_time_startADCsamplingCount_error;
	}

	if((config->measurementConfig->restartCaptureCount < 2))
	{
		return USS_message_code_SAPH_time_restartCaptureCount_error;
	}

	if((config->measurementConfig->captureTimeOutCount < 2))
	{
		return USS_message_code_SAPH_time_captureTimeOutCount_error;
	}

	//Check to make sure user doesn't ARM SDHS before 40 usec after TStart
	// (TM1 - TStart) > 40 usec

	// Divide plloutput freq since TimeMark1 is in 16 ASQ clock periods

	switch(config->pllConfiguration->pllOutputFreq)
		{
			case USS_HSPLL_output_clk_freq_80_MHz:
				temp = (80000000);
				break;
			case USS_HSPLL_output_clk_freq_79_MHz:
				temp = (79000000);
				break;
			case USS_HSPLL_output_clk_freq_78_MHz:
				temp = (78000000);
				break;
			case USS_HSPLL_output_clk_freq_77_MHz:
				temp = (77000000);
				break;
			case USS_HSPLL_output_clk_freq_76_MHz:
				temp = (76000000);
				break;
			case USS_HSPLL_output_clk_freq_75_MHz:
				temp = (75000000);
				break;
			case USS_HSPLL_output_clk_freq_74_MHz:
				temp = (74000000);
				break;
			case USS_HSPLL_output_clk_freq_73_MHz:
				temp = (73000000);
				break;
			case USS_HSPLL_output_clk_freq_72_MHz:
				temp = (72000000);
				break;
			case USS_HSPLL_output_clk_freq_71_MHz:
				temp = (71000000);
				break;
			case USS_HSPLL_output_clk_freq_70_MHz:
				temp = (70000000);
				break;
			case USS_HSPLL_output_clk_freq_69_MHz:
				temp = (69000000);
				break;
			case USS_HSPLL_output_clk_freq_68_MHz:
				temp = (68000000);
				break;
			default:
				return USS_message_code_HSPLL_pllOutputFreq_inHz_error;
		}

	// Make sure F1 frequency is within min/max limit
	if((temp/config->measurementConfig->pulseConfig->F1Frequency) > 510)
	{
	    return USS_message_code_SAPH_invalid_pulse_configuration_error;
	}

	// Make sure F2 Frequency is within min max limit if user has selected
	// dual or multi-tone pulse
	if(config->measurementConfig->pulseConfig->pulseGenMode !=
	        USS_measurement_pulse_generation_mode_single_tone)
	{
        if((temp/config->measurementConfig->pulseConfig->F2Frequency) > 510)
        {
            return USS_message_code_SAPH_invalid_pulse_configuration_error;
        }
	}


	// Determine time from TMB to TMD mark based on hspll frequency and
	// TMD = TMB has to be at least 31.5 usec
	temp = ((temp>>4)/(config->measurementConfig->startADCsamplingCount - config->measurementConfig->turnOnADCCount));

	if(temp > 31746)
	{
		return USS_message_code_SAPH_time_turnOnADCCount_error;
	}


	// Determine if user has passed a valid biasImpedance selection
	switch (config->measurementConfig->biasImpedance) {
        case USS_measurement_bias_impedance_200_Ohms:
        case USS_measurement_bias_impedance_600_Ohms:
        case USS_measurement_bias_impedance_1200_Ohms:
        case USS_measurement_bias_impedance_2800_Ohms:
            break;
        default:
            return USS_message_code_SAPH_invalid_bias_impedance_error;
    }

	if(USS_measurement_pulse_generation_mode_multi_tone ==
	        config->measurementConfig->pulseConfig->pulseGenMode)
	{
	    USS_Pulse_Multitone_Configuration *pToneConfig = (USS_Pulse_Multitone_Configuration*) config->measurementConfig->pulseConfig->pToneConfig;
	    // Check numOFthril is an even number
	    if(pToneConfig->origNumOfThrillCycles > 20)
	    {
	        return USS_message_code_SAPH_numOfExcitationPulses_error;
	    }
	}else{

	    USS_Pulse_Single_Dual_Tone_Configuration *pToneConfig = (USS_Pulse_Single_Dual_Tone_Configuration*) config->measurementConfig->pulseConfig->pToneConfig;
        if(pToneConfig->numOfF1Cycles > 127)
        {
            return USS_message_code_SAPH_numOfExcitationPulses_error;
        }

        if(pToneConfig->F1DutyCycle >99)
        {
            return USS_message_code_SAPH_pulseLowPhasePeriod_error;
        }

        if(pToneConfig->F1DutyCycle < 1)
        {
            return USS_message_code_SAPH_pulseHighPhasePeriod_error;
        }

	    if(USS_measurement_pulse_generation_mode_dual_tone ==
	            config->measurementConfig->pulseConfig->pulseGenMode)
	    {
	        if(pToneConfig->numOfF2Cycles > 127)
	        {
	            return USS_message_code_SAPH_numOfExcitationPulses_error;
	        }

	        if(pToneConfig->F2DutyCycle >99)
	        {
	            return USS_message_code_SAPH_pulseLowPhasePeriod_error;
	        }

	        if(pToneConfig->F2DutyCycle < 1)
	        {
	            return USS_message_code_SAPH_pulseHighPhasePeriod_error;
	        }
	    }
	}

    // Determine if user has passed a valid muxChargePumpMode
    switch (config->measurementConfig->muxChargePumpMode) {
        case USS_measurement_mux_charge_pump_always_on:
        case USS_measurement_mux_charge_pump_always_off:
            break;
        default:
            return USS_message_code_SAPH_invalid_rx_charge_pump_mode_error;
    }

    if(config->measurementConfig->pulseConfig->numOfStopPulses >
	        USS_SAPH_MAX_STOP_PULSES){
        return USS_message_code_SAPH_numOfStopPulses_error;
    }


	return USS_message_code_no_error;

}

#if defined(__MSP430_HAS_SAPH_A__) && (USS_PULSE_MODE == USS_PULSE_MODE_MULTI_TONE)
USS_message_code commonConfigureMultiTone(USS_SW_Library_configuration *config)
{

    USS_Pulse_Multitone_Configuration* multConf;
    int32_t i,f1Freq,f2Freq,pulseCenterFreq, pulseBandwidth;
    uint32_t fSinInc, pPGFreq;
    _iq30 iq30Btemp;
    _iq23 iq23B;
    _iq18 iq18FIncrease;
    _iq12 iq12PulseDurFreq, iq12pPGCycles;
    _iq10 iq10FIncreased;
    uint16_t *pCurrArray;
    int16_t dmaCycles, xCycles,eCycles, stopAddr,pPGCycles;
    uint8_t ehperIndex, elperIndex, xhperIndex, xlperIndex,currentState;
    int8_t currentValue, previousValue;

    multConf =
            (USS_Pulse_Multitone_Configuration*) config->measurementConfig->pulseConfig->pToneConfig;


    // Note: It is assumed that f1Freq<f2Freq
    f1Freq = (int32_t)config->measurementConfig->pulseConfig->F1Frequency;
    f2Freq = (int32_t)config->measurementConfig->pulseConfig->F2Frequency;

    // Calculate the excitation pulse bandwidth
    pulseBandwidth = (f2Freq -f1Freq);


    if(pulseBandwidth < 0)
    {
        pulseBandwidth *= -1;
    }

    // In multi-tone pulse generation mode the PPG prescaler is always enabled.
    // Therefore,
    //
    // pPGFreq = HSPLL_Frequency / 4
    //
    // Note: The maximum update rate for x-pulses and e-pulses is 480 KHz
    pPGFreq = (commonGetHSPLLFreqInHz(config));

    // Calculate PPG period
    //
    // pPGPeriod = 1/pPGFreq
    //
    //pPGPeriod = ((float)(1.0)/(float)(pPGFreq));
    // Determine pulse center frequency
    // pulseCenterFreq = (f2 - f1) / 2;
    pulseCenterFreq = ((f2Freq + f1Freq) >> 1);

    // Calculate pulseDuration in seconds
    //
    // pulseDuration = numberOfPulses/pulseCenterFreq
    //

    iq12PulseDurFreq = _IQ12div(pulseCenterFreq,(multConf->origNumOfThrillCycles << 1));


    // Determine number of PPG cycles needed to calculate generate excitation
    // sequence
    //
    //  pPGCycles = pPGFreq * pulseDuration;
    //
    iq12pPGCycles =  _IQ24div(pPGFreq, iq12PulseDurFreq);


    // Multi-tone excitation frequency will be calculated in the following using
    // the following formula
    //
    // x(t) = sin(2*pi*f(t)*t);
    //
    // Where f(t) = f1 +((pulseBandwidth/(2*pulseDuration))*t)
    //
    // and 0<=t<=(pulseDuration-ppgPeriod) in increments of ppgPeriod
    //

    // The following constants are used to allow fixed point calculations for
    // multi-tone generation calculation

    // f(t) is calculated in iq12 format and is simplified as follows
    //
    // iq12f(t) = iq12f1 + (iq12FIncrease * t)
    //
    iq18FIncrease =  _IQ30div(pulseBandwidth, iq12pPGCycles);
    iq18FIncrease >>=1;

    // fSinInc = ppgFreq / (2*pi)
    switch(config->pllConfiguration->pllOutputFreq)
    {
    case USS_HSPLL_output_clk_freq_80_MHz:
        fSinInc =12732395;
        break;
    case USS_HSPLL_output_clk_freq_79_MHz:
        fSinInc =12573240;
            break;
    case USS_HSPLL_output_clk_freq_78_MHz:
        fSinInc =12414085;
            break;
    case USS_HSPLL_output_clk_freq_77_MHz:
        fSinInc =12254930;
            break;
    case USS_HSPLL_output_clk_freq_76_MHz:
        fSinInc =12095775;
            break;
    case USS_HSPLL_output_clk_freq_75_MHz:
        fSinInc =11936620;
            break;
    case USS_HSPLL_output_clk_freq_74_MHz:
        fSinInc =11777465;
            break;
    case USS_HSPLL_output_clk_freq_73_MHz:
        fSinInc =11618310;
            break;
    case USS_HSPLL_output_clk_freq_72_MHz:
        fSinInc =11459155;
            break;
    case USS_HSPLL_output_clk_freq_71_MHz:
        fSinInc =11300000;
            break;
    case USS_HSPLL_output_clk_freq_70_MHz:
        fSinInc =11140846;
            break;
    case USS_HSPLL_output_clk_freq_69_MHz:
        fSinInc =10981691;
            break;
    default:
        fSinInc =10822536;
            break;
    };

    // The number of e-pulses and x-pulses hper and lper counts are calculated
    // using the following state machine
    //
    //    ->  X_HPER_STATE --> X_LPER_STATE --> E_HPER_STATE -->E_LPER_STATE -
    //   |--------------------------------------------------------------------|
    //
    // Transitions to next state occurs when x(t) transitions from a positive
    // value to a negative value and vice versa.


    // The following section initializes the state machine variables
    // Initial values:
    //
    // previousValue = 1
    // currentState = X_HPER_STATE
    // all ehper,elper,xhper,xlper indices set to 0
    // i is used to indicate the multiple of ppgPeriod
    // pCurrArray pint to current x/e-pulse hper/lper array

    previousValue = 1;
    currentState = X_HPER_STATE;
    ehperIndex = elperIndex = xhperIndex = xlperIndex = 0;
    i=0;
    pCurrArray = (multConf->pXPulsHPerArray + xhperIndex);
    *(pCurrArray)=0;
    multConf->pNumOfXPulsArray[xhperIndex] =1;
    multConf->pNumOfEPulsArray[ehperIndex] =1;

    pPGCycles = _IQ12int(iq12pPGCycles);

    // Enter iteration loop
    for(i=0;i<pPGCycles;i++)
    {
        // calculate iq12f base on current iteration value
        float fIncreased = (_IQ18toF(iq18FIncrease) * (float)i);
        iq10FIncreased = _IQ10(f1Freq) + _IQ10(fIncreased);
        // calculate value of B in iq23 format
        //
        // B = 2*pi*f(t)*t
        //
        // B = fIncreased*(i/fSinInc);
        iq30Btemp = _IQ30div(i,fSinInc);
        // Maximum number of pulses 40
        iq23B = _IQ17mpy(iq10FIncreased,iq30Btemp);

        // Determine if x(t)>= 0 and assing comparisson result to currentValue
        currentValue = ((_IQ23sin(iq23B) >= 0) ? 1 : -1);

        // If current value is not the same as previous value then,
        // 1.- Increase ehper/elper/xhper/xlper index based on current state
        // 2.- Update pCurrArray to next array
        // 3.- Clear current values in array
        // 4.- Increase current State
        if(currentValue != previousValue)
        {
            switch (currentState)
            {
                case E_HPER_STATE:
                    ehperIndex++;
                    pCurrArray = (multConf->pEPulsLPerArray + elperIndex);
                    break;
                case E_LPER_STATE:
                    elperIndex++;
                    pCurrArray =(multConf->pXPulsHPerArray + xhperIndex);
                    multConf->pNumOfXPulsArray[xhperIndex] = 1;
                    break;
                case X_HPER_STATE:
                    xhperIndex++;
                    pCurrArray = (multConf->pXPulsLPerArray + xlperIndex);
                    break;
                case X_LPER_STATE:
                    xlperIndex++;
                    pCurrArray = (multConf->pEPulsHPerArray + ehperIndex);
                    multConf->pNumOfEPulsArray[ehperIndex] = 1;
                    break;
                default:
                    break;
            }
            // Clear any previous array value
            *(pCurrArray)=0;
            // Go to the next state
            ++currentState;
            currentState = ((currentState)%(TOTAL_NUM_OF_STATES));
        }

        // Increase xhper/xlper/ehper/elper count
        *(pCurrArray)+=1;

        // Save previous value in current value
        previousValue = currentValue;
    }


    privatePadMultiToneConfig(config, multConf);



 /*
  * Configure e-pulses and x-pulses RAM memory
  */

    eCycles = (multConf->numOfTrillcycles);
    xCycles = (multConf->numOfTrillcycles) -1;
    dmaCycles = eCycles + xCycles;
    stopAddr = (xCycles)*6+3;

    /*******************************************************************************
     * Configure DMA2 and DMA3 for multitone generation
     ******************************************************************************/
    // DMA2 and DMA3 triggered by SAPH PPG,
    // Note: DMA2 has higher priority
    DMACTL1 = DMA2TSEL_27 | DMA3TSEL_27;

    // DMA2 initial configuration
    // Repeated block transfer, increase source address, increase dst address
    DMA2CTL = 0x5000 | DMASRCINCR | DMADSTINCR;
    // Write new SA and DA to registers, new addresses are loaded
    // when DMAEN 0->1 or when transfer ends
    __data20_write_long((uintptr_t)&DMA2SA,
                        (uint32_t)&multConf->pRAMPulseConfigArray[0]);
    __data20_write_short((uintptr_t)&DMA2DA,
                        (uintptr_t)&GENERIC_SAPH_PGC);
    // configure DMA transfer size (3 registers per block)
    DMA2SZ = 0x0003;
    // Enable DMA2
    DMA2CTL |= DMAEN;
    // Write new SA and DA to registers, new addresses are loaded when
    // DMAEN 0->1 or when transfer ends
    __data20_write_short((uintptr_t)&DMA2SA,
                        (uintptr_t)(&multConf->pRAMPulseConfigArray[3]));

    __data20_write_short((uintptr_t)&DMA2DA,
                        (uintptr_t)&GENERIC_SAPH_XPGCTL);

    // DMA3 initial configuration
    // Repeated block transfer, increase source address, increase dst address
    DMA3CTL = 0x5000 | DMASRCINCR | DMADSTINCR;
    // Write new SA
    __data20_write_short((uintptr_t)&DMA3SA,
                        (uintptr_t)&multConf->pRAMDMAConfigArray[0]);
    // Destination Address for DMA3 is Start Address of DMA2
    __data20_write_long((uintptr_t)&DMA3DA,
                        (uintptr_t)&DMA2SA);

    // configure DMA transfer size (9 registers per block)
    DMA3SZ = 0x0009;
    // Enable DMA2
    DMA3CTL |= (DMAEN);
    // Write new SA and DA to registers, new addresses are loaded when
    // DMAEN 0->1 or when transfer ends
    __data20_write_long((uintptr_t)&DMA3SA,
                        (uintptr_t)(&multConf->pRAMDMAConfigArray[9]));


    // Setup RAM
    // RAM to be transfered to DMA2 and DMA3 configuration registers
    for(i=0;i<dmaCycles+1;i++){
        // DMA2SA
        __data20_write_long((uintptr_t) &multConf->pRAMDMAConfigArray[i*9],
                           (uint32_t)multConf->pRAMPulseConfigArray+((i+2)*6));

        // DMA2DA
        __data20_write_long((uintptr_t) &multConf->pRAMDMAConfigArray[2+i*9],
                           (uint32_t)&GENERIC_SAPH_PGC);

        // DMA2SZ
        __data20_write_long((uintptr_t) &multConf->pRAMDMAConfigArray[4+i*9],
                           (uint32_t)3);
        // dummy and DMA3CTL
        __data20_write_long((uintptr_t) &multConf->pRAMDMAConfigArray[6+i*9],
                           (uint32_t)(0x5000|DMASRCINCR|DMADSTINCR|DMAEN)<<16);

        // DMA3SA
        __data20_write_short((uintptr_t)&multConf->pRAMDMAConfigArray[8+i*9],
                             (uintptr_t)&multConf->pRAMDMAConfigArray[(i+2)*9]);

    }

    // Alternate SAPHPGC and  SAPHXPGCTL address for DMA2DA
    for(i=0;i<xCycles+1;i++)
    {
        __data20_write_short((uintptr_t)&multConf->pRAMDMAConfigArray[11+(i*18)],
                             (uintptr_t)&GENERIC_SAPH_XPGCTL);
    }

    // RAM to be transfered to generate e-pulses
    for(i=0;i<eCycles;i++){
        // SAPHPGC
        __data20_write_short((uintptr_t)&multConf->pRAMPulseConfigArray[i*6],
                             (uintptr_t)multConf->pNumOfEPulsArray[i]);
        // SAPHLPGPER
        __data20_write_short((uintptr_t)&multConf->pRAMPulseConfigArray[1+i*6],
                                     (uintptr_t)multConf->pEPulsLPerArray[i]);
        // SAPHHPGPER
        __data20_write_short((uintptr_t)&multConf->pRAMPulseConfigArray[2+i*6],
                                     (uintptr_t)multConf->pEPulsHPerArray[i]);
    }

    // RAM to be transfered to generate x-pulses
    for(i=0;i<xCycles;i++){
        // SAPHXPGCTL
        // DMA_Event enabled + dual tone loop mode
        // selected (XMOD_3) + numOfXPulses
        __data20_write_short((uintptr_t)&multConf->pRAMPulseConfigArray[3+i*6],
                             (uintptr_t)(ETY_1 | XMOD_3|(multConf->pNumOfXPulsArray[i+1])));

       // SAPHAXLPGPER
       __data20_write_short((uintptr_t)&multConf->pRAMPulseConfigArray[4+i*6],
                                    (uintptr_t)multConf->pXPulsLPerArray[i+1]);

       // SAPHAXHPGPER
       __data20_write_short((uintptr_t)&multConf->pRAMPulseConfigArray[5+i*6],
                                    (uintptr_t)multConf->pXPulsHPerArray[i+1]);
    }



    // Determine if user has selected an additional end of sequence
    if(multConf->pEOFSeqConfig->numOfTrillcycles > 0)
    {

        int16_t xtraEPulses, xtraXPulses, xtraDMACycles, xtraStopAddr;

        xtraEPulses   = multConf->pEOFSeqConfig->numOfTrillcycles;
        xtraXPulses   = xtraEPulses;
        xtraDMACycles = xtraEPulses + xtraXPulses;
        xtraStopAddr  = (xtraXPulses)*6;


        for(i=dmaCycles;i<(dmaCycles+xtraDMACycles+1);i++){
            // DMA2SA
            __data20_write_long((uintptr_t) &multConf->pRAMDMAConfigArray[i*9],
                               (uint32_t)multConf->pRAMPulseConfigArray+((i+2)*6));

            // DMA2DA
            __data20_write_long((uintptr_t) &multConf->pRAMDMAConfigArray[2+i*9],
                               (uint32_t)&GENERIC_SAPH_PGC);

            // DMA2SZ
            __data20_write_long((uintptr_t) &multConf->pRAMDMAConfigArray[4+i*9],
                               (uint32_t)3);
            // dummy and DMA3CTL
            __data20_write_long((uintptr_t) &multConf->pRAMDMAConfigArray[6+i*9],
                               (uint32_t)(0x5000|DMASRCINCR|DMADSTINCR|DMAEN)<<16);

            // DMA3SA
            __data20_write_short((uintptr_t)&multConf->pRAMDMAConfigArray[8+i*9],
                                 (uintptr_t)&multConf->pRAMDMAConfigArray[(i+2)*9]);

        }

        // Alternate SAPHPGC and  SAPHXPGCTL address for DMA2DA
        for(i=xCycles;i<(xCycles+xtraXPulses+1);i++){
            __data20_write_short((uintptr_t)&multConf->pRAMDMAConfigArray[11+(i*18)],
                                 (uintptr_t)&GENERIC_SAPH_XPGCTL);
        }

        uint8_t loop=0;
        // RAM to be transfered to generate x-pulses
        for(i=xCycles;i<(xtraXPulses+xCycles);i++){
            // SAPHXPGCTL
            // DMA_Event enabled + dual tone loop mode
            // selected (XMOD_3) + numOfXPulses

            __data20_write_short((uintptr_t)&multConf->pRAMPulseConfigArray[3+i*6],
                                 (uintptr_t)(ETY_1 | XMOD_3|(multConf->pEOFSeqConfig->pNumOfXPulsArray[loop])));

           // SAPHAXLPGPER
           __data20_write_short((uintptr_t)&multConf->pRAMPulseConfigArray[4+i*6],
                                        (uintptr_t)multConf->pEOFSeqConfig->pXPulsLPerArray[loop]);

           // SAPHAXHPGPER
           __data20_write_short((uintptr_t)&multConf->pRAMPulseConfigArray[5+i*6],
                                        (uintptr_t)multConf->pEOFSeqConfig->pXPulsLPerArray[loop]);

           loop++;
        }

        loop =0;
        // RAM to be transfered to generate e-pulses
        for(i=eCycles;i<(xtraEPulses+eCycles);i++){
            // SAPHPGC
            __data20_write_short((uintptr_t)&multConf->pRAMPulseConfigArray[i*6],
                                 (uintptr_t)multConf->pEOFSeqConfig->pNumOfEPulsArray[loop]);
            // SAPHLPGPER
            __data20_write_short((uintptr_t)&multConf->pRAMPulseConfigArray[1+i*6],
								 (uintptr_t)multConf->pEOFSeqConfig->pEPulsLPerArray[loop]);
            // SAPHHPGPER
            __data20_write_short((uintptr_t)&multConf->pRAMPulseConfigArray[2+i*6],
                                 (uintptr_t)multConf->pEOFSeqConfig->pEPulsHPerArray[loop]);
            loop++;
        }

        // Reconfigure X-pulse to initial configuration
        __data20_write_short((uintptr_t)&multConf->pRAMDMAConfigArray[8+((dmaCycles+xtraDMACycles)*9)],
                                     (uintptr_t)&multConf->pRAMDMAConfigArray[0]);

        // Configure stop pulses
        __data20_write_short((uintptr_t)&multConf->pRAMPulseConfigArray[stopAddr + xtraStopAddr -3],
                (__data20_read_short((uintptr_t)&multConf->pRAMPulseConfigArray[stopAddr + xtraStopAddr -3])) |
                (config->measurementConfig->pulseConfig->numOfStopPulses) << 8);

        // Stop
        // XMOD 2
        __data20_write_short((uintptr_t)&multConf->pRAMPulseConfigArray[stopAddr + xtraStopAddr],
                             (uintptr_t)(ETY_1 | XMOD_2|(multConf->pNumOfXPulsArray[xCycles + 1])));

        __data20_write_short((uintptr_t)&multConf->pRAMPulseConfigArray[stopAddr + xtraStopAddr +1],
                                     (uintptr_t)(multConf->pXPulsLPerArray[0]));

        __data20_write_short((uintptr_t)&multConf->pRAMPulseConfigArray[stopAddr + xtraStopAddr +2],
                                     (uintptr_t)(multConf->pXPulsHPerArray[0]));

    }else
    {
        // Reconfigure X-pulse to initial configuration
        __data20_write_short((uintptr_t)&multConf->pRAMDMAConfigArray[8+(dmaCycles*9)],
                                     (uintptr_t)&multConf->pRAMDMAConfigArray[0]);

        // Configure stop pulses
        __data20_write_short((uintptr_t)&multConf->pRAMPulseConfigArray[stopAddr -3],
                (__data20_read_short((uintptr_t)&multConf->pRAMPulseConfigArray[stopAddr -3])) |
                (config->measurementConfig->pulseConfig->numOfStopPulses) << 8);

        // Stop
        // XMOD 2
        __data20_write_short((uintptr_t)&multConf->pRAMPulseConfigArray[stopAddr ],
                             (uintptr_t)(ETY_1 | XMOD_2|(multConf->pNumOfXPulsArray[xCycles + 1])));

        __data20_write_short((uintptr_t)&multConf->pRAMPulseConfigArray[stopAddr + 1],
                                     (uintptr_t)(multConf->pXPulsLPerArray[0]));

        __data20_write_short((uintptr_t)&multConf->pRAMPulseConfigArray[stopAddr + 2],
                                     (uintptr_t)(multConf->pXPulsHPerArray[0]));


    }

    return USS_message_code_no_error;
}

#define USS_COMMON_SAPH_MAX_UPDATE_RATE_IN_HZ               (420000)
USS_message_code privatePadMultiToneConfig(USS_SW_Library_configuration *config,
                               USS_Pulse_Multitone_Configuration* multConf)
{
    uint32_t hspllFreqInHz;
    uint16_t minPulseCount;
    uint16_t numOfXThrillPulseReq;
    uint16_t numOfEThrillPulseReq;


    // Determine minimum pulse count based on HSPLL frequency
    hspllFreqInHz = commonGetHSPLLFreqInHz(config);

    minPulseCount = (hspllFreqInHz + (USS_COMMON_SAPH_MAX_UPDATE_RATE_IN_HZ-1))/(USS_COMMON_SAPH_MAX_UPDATE_RATE_IN_HZ);

    // Pad x-pulses
    numOfXThrillPulseReq = privatePadPulses(minPulseCount,
                     multConf->origNumOfThrillCycles,
                     multConf->pNumOfXPulsArray,
                     multConf->pXPulsHPerArray,
                     multConf->pXPulsLPerArray);
    // Pad e-pulses
    numOfEThrillPulseReq = privatePadPulses(minPulseCount,
                     multConf->origNumOfThrillCycles,
                     multConf->pNumOfEPulsArray,
                     multConf->pEPulsHPerArray,
                     multConf->pEPulsLPerArray);

    // Check if numOfXThrillPulseReq  is greater than numOfEThrillPulseReq
    if(numOfXThrillPulseReq > numOfEThrillPulseReq){
        // Add extra e-pulse to make e-pulses and x-pulses arrays of equal
        // length
        multConf->pNumOfEPulsArray[numOfXThrillPulseReq-1] = 1;
        multConf->pEPulsHPerArray[numOfXThrillPulseReq-1] =
                multConf->pXPulsHPerArray[numOfXThrillPulseReq-1];
        multConf->pEPulsLPerArray[numOfXThrillPulseReq-1] =
                        multConf->pXPulsLPerArray[numOfXThrillPulseReq-1];
    }



    // Reconfigure the new number of thrill cycles required for x-pulses
    multConf->numOfTrillcycles =  numOfXThrillPulseReq;

    return USS_message_code_no_error;


}


uint16_t privatePadPulses(uint16_t minPulseCount,
                                  uint16_t numOfTrillcycles,
                                  uint16_t * pNumOfPulsArray,
                                  uint16_t * pPulsLPerArray,
                                  uint16_t * pPulsHPerArray)
{
    uint16_t pulseCount, totalPulseCount, pulseIndex, u16temp, origConfigOffset,
            i;

    pulseCount = pulseIndex = origConfigOffset = totalPulseCount = 0;

    // Assume initial calculation is valid, if this is not true the loop will
    // fix it.
    u16temp = 1;
    // Loop through calculated ePulse and xpulse count to determine pulses
    // which need to be "padded"
    for (i = 0; i < (numOfTrillcycles); i++)
    {
        // Check if sequence needs to be padded or cleared
        if (origConfigOffset >= (numOfTrillcycles))
        {
            pNumOfPulsArray[i] = 0;
            pPulsHPerArray[i] = 0;
            pPulsLPerArray[i]  = 0;
        }
        else
        {
            pulseCount = (pPulsHPerArray[origConfigOffset]
                    + pPulsLPerArray[origConfigOffset]);

            if (pulseCount < minPulseCount)
            {
                // round up integer division
                u16temp = (minPulseCount + (pulseCount - 1)) / pulseCount;


                if (totalPulseCount <= numOfTrillcycles)
                {
                    pNumOfPulsArray[pulseIndex] = u16temp;
                    pPulsHPerArray[pulseIndex] =
                            pPulsHPerArray[origConfigOffset];
                    pPulsLPerArray[pulseIndex] =
                            pPulsLPerArray[origConfigOffset];

                }
                else
                {
                    pNumOfPulsArray[pulseIndex] = 0;
                    pPulsHPerArray[pulseIndex] = 0;
                    pPulsLPerArray[pulseIndex] = 0;
                }
            }

            totalPulseCount += u16temp;

            pulseIndex++;
            origConfigOffset += u16temp;
        }
    }

    return (pulseIndex);
}

#endif
