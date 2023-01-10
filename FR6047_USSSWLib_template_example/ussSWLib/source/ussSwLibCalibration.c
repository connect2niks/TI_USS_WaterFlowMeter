//*****************************************************************************
// ussSwLibCalibration.c
//
// TI Release: USSLib_02_40_00_00
// Release Date: __LIB_RELEASE_DATE__
//
//*****************************************************************************
#include "ussSwLibCalibration.h"


#ifdef USS_CALIBRATE_SIGNAL_GAIN_TEST

int16_t ussMaxSignal[AGC_LOOP_MAX_ITERATIONS];

#endif

// Contains pairs of (USS Capture Gain setting,the corresponding dB value)
const float gUSSGainLookUp[AGC_GAIN_TABLE_SIZE]=
{
	17,-6.5,
	18,-5.5,
	19,-4.6,
	20,-4.1,
	21,-3.3,
	22,-2.3,
	23,-1.4,
	24,-0.8,
	25,0.1,
	26,1,
	27,1.9,
	28,2.6,
	29,3.5,
	30,4.4,
	31,5.2,
	32,6,
	33,6.8,
	34,7.7,
	35,8.7,
	36,9,
	37,9.8,
	38,10.7,
	39,11.7,
	40,12.2,
	41,13,
	42,13.9,
	43,14.9,
	44,15.5,
	45,16.3,
	46,17.2,
	47,18.2,
	48,18.8,
	49,19.6,
	50,20.5,
	51,21.5,
	52,22,
	53,22.8,
	54,23.6,
	55,24.6,
	56,25,
	57,25.8,
	58,26.7,
	59,27.7,
	60,28.1,
	61,28.9,
	62,29.9,
	63,30.8
};

// Output of PLL
USS_message_code USS_verifyHSPLLFrequency(
		USS_SW_Library_configuration *config,
		USS_calibration_hspll_results *testResults)
{
	USS_message_code code;
	int32_t timeout;
	int32_t minPass, maxPass;
	uint64_t temp;
	int64_t count = 0;
	uint32_t count1, count2;
	int16_t i;


	//  Disable Acquisition Sequencer
	UUPSCTL &= ~(ASQEN);

	// Prepare USS to be powered on
	code = commonPrepareForUSSPowerUp(config);

	if(USS_message_code_no_error != code)
	{
		return code;
	}

	// Power Up USS
	code = commonPowerUpUSS(config);

	if(USS_message_code_no_error != code)
	{
		return code;
	}

	GENERIC_SAPH_KEY = KEY;

	GENERIC_SAPH_ASCTL0 &= ~(ASQTEN);
	// Stop and Clear SAPH timer
	GENERIC_SAPH_TBCTL |= (TSTOP | TCLR);

	// Clear HSPLLUNLOCK flag before running the test
	HSPLLICR |= (PLLUNLOCK);

	// Set a timeout of approximate 900 msec (while loop takes 9 cycles approx)
	timeout = (int32_t)((float)(config->systemConfig->mCLKFrequency)*(float)0.1);
	while(((UUPSCTL & UPSTATE_3) != UPSTATE_3) && (timeout-- > 0));

	// Make sure USS Power up did not timed out
	if(timeout > 0)
	{
        // Clear SAPH Timer
        GENERIC_SAPH_TBCTL |= (TCLR | TSTOP);

        // Start period measurement timer
        commonTimerPeriodMeasurementStart(config);

        for(i = (1 << RESONATOR_CALIB_ITERATION_COUNT) -1; i>=0; i--)
        {
            // Start SAPH Timer
            GENERIC_SAPH_TBCTL |= (TSTART);

            // Configure timer to measure period between Event 1 at count = 4
            // and Event #2 at count = 554
            commonTimerConfigurePeriodMeasurement(config,
              RESONATOR_CALIB_MONITORING_ACLK_MIN_COUNT,
              RESONATOR_CALIB_MONITORING_ACLK_MIN_COUNT + RESONATOR_CALIB_MONITORING_ACLK);

            // Wait for first event
            commonTimerPeriodMeasurementWaitEvent1(config,
                                                   USS_low_power_mode_option_low_power_mode_0);
            count1 = ((((uint32_t)(GENERIC_SAPH_ATIMHI))<< 16) + (uint32_t)GENERIC_SAPH_ATIMLO);

            // Wait for second event
            commonTimerPeriodMeasurementWaitEvent2(config,
                                                   USS_low_power_mode_option_low_power_mode_0);
            count2 = ((((uint32_t)(GENERIC_SAPH_ATIMHI))<< 16) + (uint32_t)GENERIC_SAPH_ATIMLO);

            // Stop SAPH Timer
            GENERIC_SAPH_TBCTL |= (TSTOP |TCLR);

            // Save SAPH Timer count as the timer count difference between
            // count2 and count1
            count +=  (count2 - count1);
        }

        // Disable Event 1 and Event 2 Interrupts
        commonTimerPeriodMeasurementDisableInterrupts(config);

        GENERIC_SAPH_ASCTL0 |= (ASQTEN);
        // Lock SAPH registers
        GENERIC_SAPH_KEY = 0;
        //  Enable Acquisition Sequencer
        UUPSCTL |= (ASQEN);

        //Check if PLL unlocked during the test
        if((HSPLLRIS & PLLUNLOCK) == PLLUNLOCK)
        {
            code = USS_message_code_HSPLL_pll_unlock_error;
        }else
        {
            // Turn off USS module
            UUPSCTL |= (USSPWRDN);

            // Set a timeout of approximate 900 msec (while loop takes 9 cycles
            // approximately)
            timeout = (int32_t)((float)(config->systemConfig->mCLKFrequency)*(float)0.1);
            while(((UUPSCTL & UPSTATE_3)!=UPSTATE_0) && (timeout-- > 0));

            if(timeout < 0)
            {
                code = USS_message_code_UUPS_power_down_error;
            }
        }

        // Turn off USSXT after test
        HSPLLUSSXTLCTL &= ~(USSXTEN);

        switch((uint16_t)(config->pllConfiguration->pllOutputFreq))
        {
            case USS_HSPLL_output_clk_freq_68_MHz:
                temp = PLL_68_MHZ_TEMP_CONST;
                break;
            case USS_HSPLL_output_clk_freq_69_MHz:
                temp = PLL_69_MHZ_TEMP_CONST;
                break;
            case USS_HSPLL_output_clk_freq_70_MHz:
                temp = PLL_70_MHZ_TEMP_CONST;
                break;
            case USS_HSPLL_output_clk_freq_71_MHz:
                temp = PLL_71_MHZ_TEMP_CONST;
                break;
            case USS_HSPLL_output_clk_freq_72_MHz:
                temp = PLL_72_MHZ_TEMP_CONST;
                break;
            case USS_HSPLL_output_clk_freq_73_MHz:
                temp = PLL_73_MHZ_TEMP_CONST;
                break;
            case USS_HSPLL_output_clk_freq_74_MHz:
                temp = PLL_74_MHZ_TEMP_CONST;
                break;
            case USS_HSPLL_output_clk_freq_75_MHz:
                temp = PLL_75_MHZ_TEMP_CONST;
                break;
            case USS_HSPLL_output_clk_freq_76_MHz:
                temp = PLL_76_MHZ_TEMP_CONST;
                break;
            case USS_HSPLL_output_clk_freq_77_MHz:
                temp = PLL_77_MHZ_TEMP_CONST;
                break;
            case USS_HSPLL_output_clk_freq_78_MHz:
                temp = PLL_78_MHZ_TEMP_CONST;
                break;
            case USS_HSPLL_output_clk_freq_79_MHz:
                temp = PLL_79_MHZ_TEMP_CONST;
                break;
            case USS_HSPLL_output_clk_freq_80_MHz:
                temp = PLL_80_MHZ_TEMP_CONST;
                break;
            default:
                __no_operation();
                break;
        }

        temp = (temp>>19);

        testResults->expectedResult = temp;

        minPass = (testResults->expectedResult) -
                (config->pllConfiguration->hspllTolerance);

        maxPass = (testResults->expectedResult) +
                (config->pllConfiguration->hspllTolerance);

        // Average SAPH counts. Divide by 2^(RESONATOR_CALIB_ITERATION_COUNT)
        count >>= (RESONATOR_CALIB_ITERATION_COUNT);

        testResults->actualTestCount = count;
        testResults->difference = testResults->expectedResult - count;

        commonSDHSRestoreSDHSDTCA(config);

        if((count > minPass) && (count < maxPass))
        {
            code = USS_message_code_no_error;
        }else
        {
            code= USS_message_code_HSPLL_verification_expected_count_error;
        }


	}else
	{
	    code = USS_message_code_UUPS_power_up_error;
	}



	return code;

}

float USS_findAGCIndex(int8_t leftIndex, int8_t rightIndex, float tempGain)
{
	float leftValue,rightValue;
	float gainDifference;
	float tempGainDifference;
	// Initialize to Invalid Index
	float returnGainIndex=-1;
	int8_t medIndex;

	// Read Left most Value
	leftValue = gUSSGainLookUp[(leftIndex<<1)+1];
	// Read Right most Value
	rightValue = gUSSGainLookUp[(rightIndex<<1)+1];

	// Check if tempGain is less than smallest dB Gain
	if(leftValue > tempGain)
	{
		returnGainIndex = gUSSGainLookUp[leftIndex<<1];
	}
	// Check if tempGain is greater than largest dB Gain
	else if(rightValue < tempGain)
	{
		returnGainIndex = gUSSGainLookUp[rightIndex<<1];
	}

	while(returnGainIndex == -1 && leftIndex <= rightIndex)
	{
		// Find the Medium Value
		medIndex = leftIndex + ((rightIndex-leftIndex)>>1);

		gainDifference = tempGain-gUSSGainLookUp[(medIndex << 1)+1];

		// Find absolute value of the difference
		if(gainDifference < 0)
		{
			gainDifference = -1 * gainDifference;
		}

		// Check if the difference is less than AGC_MIN_DIFFERENCE
		if(gainDifference < AGC_MIN_DIFFERENCE)
		{
			// Check if medIndex is at the lowest index
			if(medIndex == 0)
			{
				// Return first value
				returnGainIndex = gUSSGainLookUp[0];
			}
			else
			{
				// Get the difference for the value below medIndex
				tempGainDifference = tempGain-gUSSGainLookUp[(medIndex << 1)-1];

				// Find absolute value of the difference
				if(tempGainDifference < 0)
				{
					tempGainDifference = -1 * tempGainDifference;
				}

				// Check which difference is smaller
				if(tempGainDifference < gainDifference)
				{
					// Return previous Gain Value in the lookup table
					returnGainIndex = gUSSGainLookUp[(medIndex << 1)-2];
				}
				else
				{
					// Get the difference for the value above medIndex
					tempGainDifference = gUSSGainLookUp[(medIndex << 1)+3]-tempGain;

					// Check which difference is smaller
					if(tempGainDifference < gainDifference)
					{
						returnGainIndex = gUSSGainLookUp[(medIndex << 1)+2];
					}
					else
					{
						// Return current Gain Value in the lookup table
						returnGainIndex = gUSSGainLookUp[medIndex << 1];
					}
				}
			}
		}
		// Check if tempGain is less than mid value, then ignore the right
		else if(gUSSGainLookUp[(medIndex << 1)+1] > tempGain)
		{
			rightIndex=medIndex-1;
		}
		// Then tempGain is greater than mid value, then ignore the left
		else
		{
			leftIndex=medIndex+1;
		}
	}

	return returnGainIndex;
}

USS_message_code USS_calibrateSignalGain(USS_SW_Library_configuration *config)
{
	uint8_t agcLoopMaxIterations = AGC_LOOP_MAX_ITERATIONS;
	uint8_t agcLoopSetting = AGC_LOOP_SETTLING;
	uint8_t agcLoopTimeOutCount=0, agcSettlingCount=0;
	USS_Capture_Gain_Range agcTempGain = (USS_Capture_Gain_Range) 0,currentGainConfig;
	// Initialize agcPrevGain to invalid value initially
	USS_Capture_Gain_Range agcPrevGain = (USS_Capture_Gain_Range) 0;
	int16_t maxMeasurementValue,minMeasurementValue;
	uint8_t agcGainIndex;
	float agcTempGainValue;
	uint16_t i;
	int16_t *pUPS,*pDNS;

#ifdef USS_CALIBRATE_SIGNAL_GAIN_TEST
	uint8_t maxSigIdx=0;
#endif

	pUPS = USS_getUPSPtr(config);
	pDNS = USS_getDNSPtr(config);

	// Save current SDHS configuration in case something goes wrong
	currentGainConfig = config->captureConfig->gainRange;

	while(agcLoopMaxIterations > agcLoopTimeOutCount)
	{
		if(agcPrevGain == (USS_Capture_Gain_Range) 0)
		{
			agcPrevGain = ADC_MINIMUM_GAIN_SETTING;
			config->captureConfig->gainRange = ADC_MINIMUM_GAIN_SETTING;

		}else
		{
			config->captureConfig->gainRange = agcPrevGain;
		}

		USS_updateSDHSConfiguration(config);

		USS_startLowPowerUltrasonicCapture(config);

		// Initialize maximum and minimum based on first reading of the UPS
		maxMeasurementValue = pUPS[0];
		minMeasurementValue = pUPS[0];

		// Find maximum and minimum for UPS and DNS
		for(i=0;i<(config->captureConfig->sampleSize);i++)
		{
			// Check if UPS[i] value is greater than current max value
			if(pUPS[i]> maxMeasurementValue)
			{
				maxMeasurementValue = pUPS[i];
			}
			// Check if UPS[i] value is less than current min value
			else if(pUPS[i]< minMeasurementValue)
			{
				minMeasurementValue = pUPS[i];
			}

			// Check if DNS[i] value is greater than current max value
			if(pDNS[i] > maxMeasurementValue)
			{
				maxMeasurementValue = pDNS[i] ;
			}
			// Check if DNS[i] value is less than current min value
			else if(pDNS[i]  < minMeasurementValue)
			{
				minMeasurementValue = pDNS[i] ;
			}
		}

		// Find absolute value of maximum and minimum for UPS and DNS
		if(maxMeasurementValue < 0)
		{
			maxMeasurementValue = -1 * maxMeasurementValue;
		}
		if(minMeasurementValue < 0)
		{
			minMeasurementValue = -1 * minMeasurementValue;
		}

        // Get peak-to-peak amplitude /2 instead of absolute max/min to remove DC offset
        maxMeasurementValue = (maxMeasurementValue + minMeasurementValue)/2;

#ifdef USS_CALIBRATE_SIGNAL_GAIN_TEST
		maxMeasurementValue = ussMaxSignal[maxSigIdx++];
#endif

		// Set SDHS PGA gain to the closest gain value agcTempGain,
		// Where agcTempGain= [Gprev + 20*log10(ADCnom/ maxsig)]
		// 		 agcTempGain= [Gprev + 20*log10(ADCnom) - 20*log10(maxsig)]

		// Find the Gprev index in lookup table
		agcGainIndex = (((uint8_t) agcPrevGain - AGC_INDEX_OFFSET)<<1)+1;

		agcTempGainValue = (float) gUSSGainLookUp[agcGainIndex] + (float) config->captureConfig->agcConstant;

		agcTempGainValue -= (float) ((float)20*log10f((float)maxMeasurementValue));

		// Perform a binary search on the based on the gUSSGainLookUp Table
		// Sets the agcTempGain value
		agcTempGain = (USS_Capture_Gain_Range) USS_findAGCIndex(0,46,agcTempGainValue);

		if(agcTempGain == agcPrevGain)
		{
			agcSettlingCount++;

			if(agcSettlingCount == agcLoopSetting)
			{
				USS_updateSAPHConfiguration(config);
				return USS_message_code_Signal_Gain_Calibration_successful;
			}
		}else
		{
			agcPrevGain = agcTempGain;
			agcSettlingCount = 0;
		}

		agcLoopTimeOutCount++;
	}

	config->captureConfig->gainRange = currentGainConfig;
	USS_updateSDHSConfiguration(config);
	USS_updateSAPHConfiguration(config);

	if(agcSettlingCount == 0)
	{
		return USS_message_code_Signal_Gain_Calibration_timeout;
	}
	else
	{
		return USS_message_code_Signal_Gain_Calibration_settling;
	}
}

USS_message_code USS_estimateDCoffset(USS_SW_Library_configuration *config,
                                      USS_dcOffEst_Calc_Mode mode)
{
	USS_message_code code;
	int16_t i;
	int32_t	upsSum, dnsSum;
	int16_t *pUpsValue, *pDnsValue;

	// Determine if user has selected to trigger a new UPS/DNS capture

	switch (mode) {
    // Determine if user has selected to trigger a new UPS/DNS capture
        case USS_dcOffEst_Calc_Mode_trigger_UPS_DNS_capture_controlled_by_ASQ:
            // Capture UPS and DNS with current USS configuration in LPM0
            // controlled via ASQ
            code = USS_startUltrasonicMeasurement(config,
                    USS_capture_power_mode_low_power_mode_0);
            break;
        case USS_dcOffEst_Calc_Mode_trigger_UPS_DNS_capture_using_LPM_capture:
            // Capture UPS and DNS with current USS configuration using SW
            // controlled flow going to LPM3 mode between captures.
            code = USS_startLowPowerUltrasonicCapture(config);
            break;
        default:
            code = USS_message_code_no_error;
            break;
    }

	if(USS_message_code_no_error == code)
	{
		// Obtain pointers to UPS and DNS excluding capture padding
		pUpsValue = USS_getUPSPtr(config);
		pDnsValue = USS_getDNSPtr(config);

		// Clear ups and dns SUM
		upsSum = 0;
		dnsSum = 0;

		// Add UPS and DNS captures based on configuration sample size
		for(i=config->captureConfig->sampleSize; i>0; i--)
		{
			upsSum+=(*pUpsValue++);
			dnsSum+=(*pDnsValue++);
		}

		// Store calibrated DC offset in configuration structures
		config->algorithmsConfig->calibratedDCOffsetDNS =
				(dnsSum/config->captureConfig->sampleSize);
		config->algorithmsConfig->calibratedDCOffsetUPS =
				(upsSum/config->captureConfig->sampleSize);

	}

	return code;
}

USS_message_code USS_calculateOffsets(USS_SW_Library_configuration *config,
                          USS_dTof_absTof_offset_results *testResults,
                          USS_dTof_absTof_offset_test_config *testConfig)
{
    USS_message_code code;
    USS_Algorithms_Results algResults;
    uint16_t iterations;
    bool isLPMCapture;
    bool iscalcAbstofUPS;
    bool iscalcAbstofDNS;
    bool iscalcDToF;
    float upsAbsAcc;
    float dnsAbsAcc;
    float dtofAcc;


    iterations      = testConfig->numOfTestIterations;
    isLPMCapture    = testConfig->isUseLPMCapture;
    iscalcAbstofUPS = testConfig->isCalculateUpsAbsTofOffset;
    iscalcAbstofDNS = testConfig->isCalculateDnsAbsTofOffset;
    iscalcDToF      = testConfig->isCalculateDToFOffset;


    // Validate test configuration
    if (iterations > ABSTOF_DTOF_MAX_ITERATIONS){
        return USS_message_code_Calibration_Offset_invalid_configuration;
    }

    if(((config->measurementConfig->sequenceSelection == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH1) ||
       (config->measurementConfig->sequenceSelection == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH0)) == false){
        return USS_message_code_Calibration_Offset_invalid_configuration;
    }

    upsAbsAcc = 0.0f;
    dnsAbsAcc = 0.0f;
    dtofAcc   = 0.0f;

    // Start Offset estimation
    for(iterations = testConfig->numOfTestIterations + 1; iterations > 0; iterations--){
        if(true == isLPMCapture){
            code = USS_startLowPowerUltrasonicCapture(config);
        }else{
            code = USS_startUltrasonicMeasurement(config,USS_capture_power_mode_low_power_mode_0);
        }

        if(code == USS_message_code_no_error)
        {
            code = USS_runAlgorithms(config, &algResults);

            if(code == USS_message_code_valid_results){
                if(true == iscalcAbstofUPS){
                    upsAbsAcc += algResults.totalTOF_UPS;
                }
                if(true == iscalcAbstofDNS){
                    dnsAbsAcc += algResults.totalTOF_DNS;
                }
                if(true == iscalcDToF){
                    dtofAcc   += algResults.deltaTOF;
                }
            }else{
                break;
            }
        }else{
            break;
        }
    }

    if(code == USS_message_code_valid_results)
    {
        if(true == iscalcAbstofUPS){
            testResults->upsAbsToFOffset =  (upsAbsAcc /
                    (float)(testConfig->numOfTestIterations + 1));
        }else{
            testResults->upsAbsToFOffset = 0.0f;
        }
        if(true == iscalcAbstofDNS){
            testResults->dnsAbsToFOffset = (dnsAbsAcc
                    / (float) (testConfig->numOfTestIterations + 1));
        }
        else
        {
            testResults->dnsAbsToFOffset = 0.0f;
        }
        if(true == iscalcDToF){
            testResults->dToFOffset = (dtofAcc
                    / (float) (testConfig->numOfTestIterations + 1));
        }
        else
        {
            testResults->dToFOffset = 0.0f;
        }
        code = USS_message_code_no_error;
    }else{
        testResults->upsAbsToFOffset = 0.0f;
        testResults->dnsAbsToFOffset = 0.0f;
        testResults->dToFOffset = 0.0f;
    }

    return code;
}











