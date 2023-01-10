//*****************************************************************************
// ussSwLibMeasurement.c
//
// TI Release: USSLib_02_40_00_00
// Release Date: __LIB_RELEASE_DATE__
//
//*****************************************************************************
#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include "ussSwLib.h"

#include "common/benchmarkussswLib.h"
#include "common/ussSwLibCommonUSS.h"
#include "common/ussSwLibCommonSDHS.h"
#include "common/ussSwLibCommonInterrupts.h"
#include "common/ussSwLibCommonTimer.h"
#include "common/USSGenericRegDef.h"
#include "USS_Lib_HAL.h"
#include "USS_Config/USS_userConfig.h"

#define USS_LOW_POWER_DELAY_MAX_RERTY		3

#if(USSSWLIB_ENABLE_EXTERNAL_CIRCUITRY_CONTROL == true)
static void USS_ACQDoneCallback(void);
#endif

USS_message_code USS_configureUltrasonicMeasurement(
		USS_SW_Library_configuration *config)
{
#if ENABLE_USS_LIB_BENCHMARK
	BENCHMARK_ENTRY_USS_LIB();
#endif

	USS_message_code messageCode;

#if(USSSWLIB_ENABLE_EXTERNAL_CIRCUITRY_CONTROL == true)
    USSLIB_HAL_initGPIO();
    USSLIB_HAL_configureRxEnTimer(USS_MEASUREMENT_ASQTRIGGER_DELAY_CYCLES,
                                  config->measurementConfig->startRxEnCount);
    USS_registerSAPHInterruptCallback(USS_SAPH_Interrupt_SEQDN,
                                      USS_ACQDoneCallback);
#endif


	// Configure USS modules
	messageCode = USS_updateUUPSConfiguration(config);
	if(USS_message_code_no_error != messageCode)
	{
		return messageCode;
	}
	messageCode = USS_updateHSPLLConfiguration(config);
	if(USS_message_code_no_error != messageCode)
	{
		return messageCode;
	}
	messageCode = USS_updateSAPHConfiguration(config);
	if(USS_message_code_no_error != messageCode)
	{
		return messageCode;
	}
	messageCode = USS_updateSDHSConfiguration(config);
	if(USS_message_code_no_error != messageCode)
	{
		return messageCode;
	}

	messageCode = USS_updateUSSInterruptsConfiguration(config);
	if(USS_message_code_no_error != messageCode)
	{
		return messageCode;
	}

	// Configure Timer for delay operations
	if(false == commonTimerConfigureTimer(config))
	{
		return USS_message_code_ACLK_settling_time_out;
	}

#if ENABLE_USS_LIB_BENCHMARK
	BENCH_EXIT_USS_LIB();
#endif

	return USS_message_code_no_error;
}


USS_message_code USS_startUltrasonicMeasurement(
		USS_SW_Library_configuration *config,
		USS_capture_power_mode_option mode)
{

#if ENABLE_USS_LIB_BENCHMARK
	BENCH_ENTRY_USS_LIB();
#endif

	USS_message_code code;
	// Check if USS is in ready state, if it is not ready go through USS
	// confirm HSPLL is stable otherwise stabilize HSPLL
	code = commonPrepareForUSSPowerUp(config);

	if(USS_message_code_no_error != code)
	{
		return code;
	}

#if ENABLE_USS_LIB_BENCHMARK
	BENCH_EXIT_USS_LIB();
#endif
#if ENABLE_USS_LIB_BENCHMARK
	BENCH_ENTRY_USS_LIB(&benchUSSLib.USS_start_ups);
#endif

	// Enable SAPH, HSPLL and UUPS interrupts
	USSSWLIB_USS_interrupt_status &= ~(USS_INTERRUPTS_MASK);

	// Clear any pending USS Interrupts
	commonClearUSSInterrupts();

	// enable USS interruputs
	commonEnableCaptureInterrupts(config);

	//Clear ISTOP bit before triggering capture
	SDHSICR |= (ISTOP);


	// Start capture if user is triggerring USS mesaurement via SW
	if(USS_Triger_Configuration_Software_Trigger ==
			config->triggerConfig->triggerConfig)
	{
		commonPowerUpUSS(config);


		// Wait for conversion to be done
		commonWaitForconversion(mode);

#if ENABLE_USS_LIB_BENCHMARK
		BENCH_EXIT_USS_LIB();
#endif

#if ENABLE_USS_LIB_BENCHMARK
		BENCH_ENTRY_USS_LIB(&benchUSSLib.USS_finish_ups);
#endif
		// Check for conversion result
		code = commonIsconversionSuccessfull(config);

		commonSDHSRestoreSDHSDTCA(config);

		// Disable USSXTAL if user requested to turn off USS module
		// otherwise PLL will be unlocked
		if(USS_measurement_end_of_sequence_state_power_off ==
				config->measurementConfig->eofSequenceState)
		{
			HSPLLUSSXTLCTL &= ~(USSXTEN);
		}

	}

#if ENABLE_USS_LIB_BENCHMARK
	BENCH_EXIT_USS_LIB();
#endif

	return code;
}


USS_message_code USS_stopUltrasonicMeasurement(
		USS_SW_Library_configuration *config,
		USS_stop_measurement_state stopMeasurementState)
{
	//Check if a conversion is active
	if(UUPSCTL & USS_BUSY)
	{
		// Check if SAPH SEQDN interrupt has not been triggered yet
		if(USSSWLIB_USS_interrupt_status & USS_SAPH_SEQ_ACQ_DN_INTERRUPT)
		{
			// Clear USS_SAPH_SEQ_ACQ_DN_INTERRUPT interrupt
			USSSWLIB_USS_interrupt_status &= ~(USS_SAPH_SEQ_ACQ_DN_INTERRUPT);

			// No need to stop sequence just power down USS based on
			// stopMeasurementState parameter
			if(USS_stop_measurement_turn_off_USS == stopMeasurementState)
			{
				UUPSCTL |= (USSPWRDN);
			}

		}else
		{
			// Clear TIMER interrupts and enable capture interrupts to make sure
			// SAPH SEQDN done interrupt gets triggered
			USSSWLIB_USS_interrupt_status &= ~(USS_TIMER_EXPIRED_EVENT1_INTERRUPT);

			commonEnableCaptureInterrupts(config);

			if(USS_stop_measurement_turn_off_USS == stopMeasurementState)
			{
				UUPSCTL |= (USSPWRDN);
			}else
			{
				UUPSCTL |= (USSSTOP);
			}

			// Wait until SAPH SEQDN occurs
			__disable_interrupt();
			while(USSSWLIB_USS_interrupt_status &
					USS_SAPH_SEQ_ACQ_DN_INTERRUPT)
			{
				__bis_SR_register(LPM1_bits + GIE);
				__disable_interrupt();
			}

			// Wait for at least 20 usec as specified in USS spec
			commonTimerGenerateLowPowerDelay(config,1,
					USS_low_power_mode_option_low_power_mode_1);
		}

		// Verify USS state is OFF or in READY/STANDBY state based on user selection
		if(USS_stop_measurement_turn_off_USS == stopMeasurementState)
		{
			// Check if USS state is OFF
			if((UUPSCTL & UPSTATE_3) != UPSTATE_0)
			{
				// If you get to this part of code something went really wrong.
				return USS_message_code_error_occurred;
			}
		}else
		{
			// Check if USS state is READY
			if((UUPSCTL & UPSTATE_3) != UPSTATE_3 )
			{
				// If you get to this part of code something went really wrong.
				return USS_message_code_error_occurred;
			}

			//Check that USS is no longer busy
			if(UUPSCTL & USS_BUSY)
			{
				// If you get to this part of code something went really
				// really wrong.
				return USS_message_code_error_occurred;
			}
		}
	}

	USSSWLIB_USS_interrupt_status |= USS_SAPH_SEQUENCE_STOPPED;

	// Measurement sequence was successfully stopped or no capture was active.
	return USS_message_code_no_error;
}

void USS_generateLPMDelay(
		USS_SW_Library_configuration *config,
		USS_low_power_mode_option lpmMode,
		uint16_t count)
{
	commonTimerGenerateLowPowerDelay(config,count,lpmMode);
}

void USS_configAppTimerPeriod(
        USS_SW_Library_configuration *config,
        uint16_t count)
{
    config->systemConfig->measurementPeriod = count;
    USSSWLIB_USS_measurementPeriod = count;
    commonTimerConfigureTick(config);
}

USS_message_code USS_waitForAppTimerElapse(
        USS_SW_Library_configuration *config,
        USS_low_power_mode_option lpmMode)
{
    USS_message_code code;
    bool overflowFlag;

    // Check if there was an overflow in the measurement period
    overflowFlag = commonTimerWaitTickEvent(config, lpmMode);

    if(overflowFlag)
    {
        code = USS_message_code_measurement_period_overflow;
    }
    else
    {
        code = USS_message_code_no_error;
    }
    return code;
}

USS_message_code USS_commonTriggerSingleCapture(USS_SW_Library_configuration *config,
												uint8_t captureChannel,
												uint16_t lowPowerDelay)
{

    USS_message_code code = USS_message_code_no_error;

#if defined(__MSP430_BASEADDRESS_SAPH_A__)
    USS_Pulse_Multitone_Configuration* multConf;
#endif

	// Unlock SAPH
	GENERIC_SAPH_KEY = KEY;

	// Turn on USSXTAL
	HSPLLUSSXTLCTL |= USSXTEN;

	// Enable SAPH, HSPLL and UUPS interrupts
	USSSWLIB_USS_interrupt_status &= ~(USS_INTERRUPTS_MASK);

	// Clear any pending USS Interrupts
	GENERIC_SAPH_ICR = (DATAERR | TMFTO | SEQDN | PNGDN);
	SDHSICR = (WINLO | WINHI | DTRDY | SSTRG | ACQDONE | OVF);
	UUPSICR = (PTMOUT | STPBYDB);
	HSPLLICR = (PLLUNLOCK);

	// enable USS interrupts
	commonEnableCaptureInterrupts(config);

	//Clear ISTOP bit before triggering capture
	SDHSICR |= (ISTOP);

	// Clear current sequence selection early bias switch selection
	GENERIC_SAPH_BCTL &= ~(CH1EBSW | CH0EBSW);
	// Clear current input multiplexer channel selection
	GENERIC_SAPH_ICTL0 &= ~(MUXSEL_15);

	// Configure SAPH for channel 0/1 single capture
	switch(captureChannel)
	{
	case USS_CAPTURE_SEQUENCE_SELECTION_CH0:
#if(USSSWLIB_ENABLE_EXTERNAL_CIRCUITRY_CONTROL == false)
	    GENERIC_SAPH_ASCTL0 = (TRIGSEL_1 | ASQTEN);
        GENERIC_SAPH_BCTL |= (CH0EBSW | PGABSW);
        GENERIC_SAPH_ICTL0 |= (MUXSEL_1);
#endif

#if (USSSWLIB_ENABLE_EXTERNAL_CIRCUITRY_CONTROL == true)
#if ((__EVM430_ID__ == 0x43) && (defined(__AFE_EXT_3v3__) || defined(__AFE_EXT_5v0__)))

        // CH0 TX , CH0 RX
        // ASQ is triggered in software
        GENERIC_SAPH_ASCTL0 = (TRIGSEL_0 + ASQTEN);
        GENERIC_SAPH_ASCTL1 |= (CHOWN);
        GENERIC_SAPH_BCTL &= ~(ASQBSC);
        GENERIC_SAPH_BCTL |= (PGABSW);
        // Select Rx Mux input channel_0
        GENERIC_SAPH_ICTL0 |= (MUXSEL_0);
        // Configure RX signal path
        USSLIB_HAL_configGPIOForCapture(USSLIB_HAL_capture_mode_ups);
#else
    #error "USS Lib Measurement not supported or defined for EVM configuration"
#endif // ((__EVM430_ID__ == 0x43) && (defined(__AFE_EXT_3v3__) || defined(__AFE_EXT_5v0__)))
#endif // (USSSWLIB_ENABLE_EXTERNAL_CIRCUITRY_CONTROL == true)
		break;
	case USS_CAPTURE_SEQUENCE_SELECTION_CH1:
#if(USSSWLIB_ENABLE_EXTERNAL_CIRCUITRY_CONTROL == false)
	    GENERIC_SAPH_ASCTL0 = (TRIGSEL_1 | ASQCHSEL_1 | ASQTEN);
        GENERIC_SAPH_BCTL |= (CH1EBSW | PGABSW);
#endif

#if (USSSWLIB_ENABLE_EXTERNAL_CIRCUITRY_CONTROL == true)
#if ( (__EVM430_ID__ == 0x43) && ((defined(__AFE_EXT_3v3__) || defined(__AFE_EXT_5v0__))) && \
      (__EVM430_VER__ == 0x20) )
        // CH0 TX , CH0 RX
        // ASQ is triggered in software
        GENERIC_SAPH_ASCTL0 = (TRIGSEL_0 | ASQTEN);
        GENERIC_SAPH_BCTL &= ~(ASQBSC);
        GENERIC_SAPH_BCTL |= (PGABSW);
        GENERIC_SAPH_ASCTL1 |= (CHOWN);
        // Select Rx Mux input channel_0
        GENERIC_SAPH_ICTL0 |= (MUXSEL_0);
        // Configure RX signal path
        USSLIB_HAL_configGPIOForCapture(USSLIB_HAL_capture_mode_dns);
#elif ( (__EVM430_ID__ == 0x43) && (defined(__AFE_EXT_3v3__)) && \
        (__EVM430_VER__ == 0x11) )
        // CH1 TX , CH0 RX
        // ASQ is triggered in software
        GENERIC_SAPH_ASCTL0 = (TRIGSEL_0 | ASQCHSEL_1 | ASQTEN);
        GENERIC_SAPH_BCTL &= ~(ASQBSC);
        GENERIC_SAPH_BCTL |= (PGABSW);
        GENERIC_SAPH_ASCTL1 &= ~(CHOWN);
        // Select Rx Mux input channel_1
        GENERIC_SAPH_ICTL0 |= (MUXCTL | MUXSEL1);
        // Configure RX signal path
        USSLIB_HAL_configGPIOForCapture(USSLIB_HAL_capture_mode_dns);
#else
    #error "USS Lib Measurement not supported or defined for EVM configuration"
#endif // ((__EVM430_ID__ == 0x43) && (defined(__AFE_EXT_3v3__)))
#endif // (USSSWLIB_ENABLE_EXTERNAL_CIRCUITRY_CONTROL == true)

		break;
	default:
		return USS_message_code_error_occurred;
	}


#if defined(__MSP430_BASEADDRESS_SAPH_A__)
	if(config->measurementConfig->pulseConfig->pulseGenMode ==
	        USS_measurement_pulse_generation_mode_multi_tone)
	{
	    multConf = (USS_Pulse_Multitone_Configuration*)config->measurementConfig->pulseConfig->pToneConfig;


/*******************************************************************************
 * Reconfigure DMA2 and DMA3 for multitone generation
 ******************************************************************************/

        // DMA2 initial configuration
        // Repeated block transfer, increase source address, increase dst address
        DMA2CTL = 0x5000|DMASRCINCR|DMADSTINCR;
        // Write new SA and DA to registers, new addresses are loaded
        // when DMAEN 0->1 or when transfer ends

        // Write new SA and DA to registers, new addresses are loaded
        // when DMAEN 0->1 or when transfer ends
        __data20_write_long((uintptr_t)&DMA2SA,
                            (uint32_t)&multConf->pRAMPulseConfigArray[0]);
        __data20_write_short((uintptr_t)&DMA2DA,
                            (uintptr_t)&GENERIC_SAPH_PGC);

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
        DMA3CTL = 0x5000|DMASRCINCR|DMADSTINCR;
        // Write new SA
        __data20_write_short((uintptr_t)&DMA3SA,
                            (uintptr_t)&multConf->pRAMDMAConfigArray[0]);
        // Enable DMA2
        DMA3CTL |= (DMAEN);
        // Write new SA and DA to registers, new addresses are loaded when
        // DMAEN 0->1 or when transfer ends
        __data20_write_long((uintptr_t)&DMA3SA,
                            (uintptr_t)(&multConf->pRAMDMAConfigArray[9]));


	    // Configuration PPG in MultiTone configuration
	    GENERIC_SAPH_PGC = ((*multConf->pNumOfEPulsArray) | (config->measurementConfig->pulseConfig->numOfStopPulses << 8));
	    GENERIC_SAPH_XPGCTL = (ETY_1 | XMOD_3 | (*multConf->pNumOfXPulsArray));
	    GENERIC_SAPH_LP_X_PULS = (*multConf->pXPulsLPerArray);
	    GENERIC_SAPH_HP_X_PULS = (*multConf->pXPulsHPerArray);


	}
#endif

	commonTimerGenerateLowPowerDelay(config,
			config->pllConfiguration->ussXTALsettlingCount,
			USS_low_power_mode_option_low_power_mode_3);

    // Turn on USS Power and PLL and start measurement
    UUPSCTL |= USSPWRUP;

#if(USSSWLIB_ENABLE_EXTERNAL_CIRCUITRY_CONTROL == true)
	USSLIB_HAL_startRxEnTimer();
#endif

	// Go to LPM 0 and wait for conversion to finish
	commonWaitForconversion(USS_capture_power_mode_low_power_mode_0);

#if(USSSWLIB_ENABLE_EXTERNAL_CIRCUITRY_CONTROL == true)
	USSLIB_HAL_configGPIOAfterCapture();
#endif

    // Check if error occurred
    code = commonIsconversionSuccessfull(config);
	if(code != USS_message_code_no_error)
	{
		return code;
	}

	// Power off USSXTAL
	HSPLLUSSXTLCTL &= ~USSXTEN;


	// Delay based on user input for LowPowerCaptureCount
	if(lowPowerDelay > 0)
	{
		commonTimerGenerateLowPowerDelay(config,
										lowPowerDelay,
										USS_low_power_mode_option_low_power_mode_3);
	}


	return USS_message_code_no_error;
}

USS_message_code USS_startLowPowerUltrasonicCapture(
		USS_SW_Library_configuration *config)
{
	USS_message_code code;
	//
	// Configure SAPH end of sequence to off state
	//

	// Unlock SAPH
	GENERIC_SAPH_KEY = KEY;

	// The ASQ sends a power down request to the
	// PSQ (Power Sequencer) when the OFF request is received.
	GENERIC_SAPH_ASCTL1 &= ~(STDBY);
	// OFF request is generated after sequence
	GENERIC_SAPH_ASCTL1 |= ESOFF;

	// Lock SAPH registers
	GENERIC_SAPH_KEY = 0;

#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH1)
	if(config->measurementConfig->sequenceSelection == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH1)
	{
		code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH0,config->measurementConfig->restartLowPowerCaptureCount);
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH1,0);
		}

		// Update SAPH Configuration
		GENERIC_SAPH_ASCTL1 = config->measurementConfig->eofSequenceState;
		GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + PNGCNT0;
	}
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH0)
	if(config->measurementConfig->sequenceSelection == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH0)
	{
		code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH1,config->measurementConfig->restartLowPowerCaptureCount);
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH0,0);
		}

		// Update SAPH Configuration
		GENERIC_SAPH_ASCTL1 = config->measurementConfig->eofSequenceState;
		GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + ASQCHSEL_1 + PNGCNT0;
	}
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH0)
	if(config->measurementConfig->sequenceSelection == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH0)
	{
		code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH0,config->measurementConfig->restartLowPowerCaptureCount);
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH0,0);
		}

		// Update SAPH Configuration
		GENERIC_SAPH_ASCTL1 = config->measurementConfig->eofSequenceState;
		GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + PNGCNT0;
	}
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH1)
	if(config->measurementConfig->sequenceSelection == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH1)
	{
		code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH1,config->measurementConfig->restartLowPowerCaptureCount);
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH1,0);
		}

		// Update SAPH Configuration
		GENERIC_SAPH_ASCTL1 = config->measurementConfig->eofSequenceState;
		GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + ASQCHSEL_1 + PNGCNT0;
	}
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH1_CH0)
	if(config->measurementConfig->sequenceSelection == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH1_CH0)
	{
		code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH0,config->measurementConfig->restartLowPowerCaptureCount);
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH1,config->measurementConfig->restartLowPowerCaptureCount);
		}
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH0,0);
		}

		// Update SAPH Configuration
		GENERIC_SAPH_ASCTL1 = config->measurementConfig->eofSequenceState;
		GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + PNGCNT1;
	}
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH0_CH1)
	if(config->measurementConfig->sequenceSelection == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH0_CH1)
	{
		code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH1,config->measurementConfig->restartLowPowerCaptureCount);
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH0,config->measurementConfig->restartLowPowerCaptureCount);
		}
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH1,0);
		}

		// Update SAPH Configuration
		GENERIC_SAPH_ASCTL1 = config->measurementConfig->eofSequenceState;
		GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + ASQCHSEL_1 + PNGCNT1;
	}
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH0_CH0)
	if(config->measurementConfig->sequenceSelection == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH0_CH0)
	{
		code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH0,config->measurementConfig->restartLowPowerCaptureCount);
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH0,config->measurementConfig->restartLowPowerCaptureCount);
		}
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH0,0);
		}

		// Update SAPH Configuration
		GENERIC_SAPH_ASCTL1 = config->measurementConfig->eofSequenceState;
		GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + PNGCNT1;
	}
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH1_CH1)
	if(config->measurementConfig->sequenceSelection == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH1_CH1)
	{
		code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH1,config->measurementConfig->restartLowPowerCaptureCount);
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH1,config->measurementConfig->restartLowPowerCaptureCount);
		}
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH1,0);
		}

		// Update SAPH Configuration
		GENERIC_SAPH_ASCTL1 = config->measurementConfig->eofSequenceState;
		GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + ASQCHSEL_1 + PNGCNT1;
	}
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH1_CH0_CH1)
	if(config->measurementConfig->sequenceSelection == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH1_CH0_CH1)
	{
		code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH0,config->measurementConfig->restartLowPowerCaptureCount);
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH1,config->measurementConfig->restartLowPowerCaptureCount);
		}
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH0,config->measurementConfig->restartLowPowerCaptureCount);
		}
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH1,0);
		}

		// Update SAPH Configuration
		GENERIC_SAPH_ASCTL1 = config->measurementConfig->eofSequenceState;
		GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + PNGCNT0 + PNGCNT1;
	}
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH0_CH1_CH0)
	if(config->measurementConfig->sequenceSelection == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH0_CH1_CH0)
	{
		code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH1,config->measurementConfig->restartLowPowerCaptureCount);
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH0,config->measurementConfig->restartLowPowerCaptureCount);
		}
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH1,config->measurementConfig->restartLowPowerCaptureCount);
		}
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH0,0);
		}

		// Update SAPH Configuration
		GENERIC_SAPH_ASCTL1 = config->measurementConfig->eofSequenceState;
		GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + ASQCHSEL_1 + PNGCNT0 + PNGCNT1;
	}
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH0_CH0_CH0)
	if(config->measurementConfig->sequenceSelection == USS_CAPTURE_SEQUENCE_SELECTION_CH0_CH0_CH0_CH0)
	{
		code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH0,config->measurementConfig->restartLowPowerCaptureCount);
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH0,config->measurementConfig->restartLowPowerCaptureCount);
		}
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH0,config->measurementConfig->restartLowPowerCaptureCount);
		}
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH0,0);
		}

		// Update SAPH Configuration
		GENERIC_SAPH_ASCTL1 = config->measurementConfig->eofSequenceState;
		GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + PNGCNT0 + PNGCNT1;
	}
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH1_CH1_CH1)
	if(config->measurementConfig->sequenceSelection == USS_CAPTURE_SEQUENCE_SELECTION_CH1_CH1_CH1_CH1)
	{
		code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH1,config->measurementConfig->restartLowPowerCaptureCount);
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH1,config->measurementConfig->restartLowPowerCaptureCount);
		}
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH1,config->measurementConfig->restartLowPowerCaptureCount);
		}
		if(code == USS_message_code_no_error)
		{
			code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH1,0);
		}

		// Update SAPH Configuration
		GENERIC_SAPH_ASCTL1 = config->measurementConfig->eofSequenceState;
		GENERIC_SAPH_ASCTL0 = TRIGSEL_1 + ASQCHSEL_1 + PNGCNT0 + PNGCNT1;
	}
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH0)
	if(config->measurementConfig->sequenceSelection == USS_CAPTURE_SEQUENCE_SELECTION_CH0)
	{
		code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH0,0);
	}
#endif
#if (USS_SEQUENCE_SELECTION == USS_CAPTURE_SEQUENCE_SELECTION_CH1)
	if(config->measurementConfig->sequenceSelection == USS_CAPTURE_SEQUENCE_SELECTION_CH1)
	{
		code = USS_commonTriggerSingleCapture(config,USS_CAPTURE_SEQUENCE_SELECTION_CH1,0);
	}
#endif
	else
	{
		GENERIC_SAPH_ASCTL1 = (config->measurementConfig->eofSequenceState) +
				CHTOG;
	}

	// Reset SDHSDTCDA address
	commonSDHSRestoreSDHSDTCA(config);

	return code;
}

#if(USSSWLIB_ENABLE_EXTERNAL_CIRCUITRY_CONTROL == true)
static void USS_ACQDoneCallback(void)
{
    // Power Down the UUPS after the acquisition is complete
    UUPSCTL |= USSPWRDN;
}
#endif
