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
#include <msp430.h>
#include "main.h"

USS_Algorithms_Results algorithms_Results;

static void checkCode(USS_message_code code, USS_message_code expectedCode);
static void handlePllUnlockEvent(void);
static void disableApplicationInterrupts(void);
static void enableApplicationInterrupts(void);

#if APPLICATION_ENABLE_UART_DEBUG
static void uartTxByte(char string);
static void uartTxHexByte(uint8_t Data);
static uint8_t nibbleToHex(uint8_t nibble);
static void uartTxUSSResult(uint8_t delimiter, float *data);
#endif

int main(void)
{
#if (APPLICATION_ENABLE_CHANNEL_SWAP == true)
    uint16_t appSwapInterval = APPLICATION_CHANNEL_SWAP_INTERVAL;
#endif

#if (APPLICATION_ENABLE_ABSTOF_DTOF_OFFSET_CALIBRATION == true)
    USS_dTof_absTof_offset_results abstoFDtofTestResults;
    USS_dTof_absTof_offset_test_config abstoFDtofTestConfig =
    {
         .numOfTestIterations        = APPLICATION_ABSTOF_DTOF_OFFSET_UPDATE_INTERVAL,
         .isUseLPMCapture            = APPLICATION_ABSTOF_DTOF_OFFSET_LPM_CAPTURE,
         .isCalculateUpsAbsTofOffset = APPLICATION_ABSTOF_DTOF_OFFSET_CALC_UPS_ABSTOF,
         .isCalculateDnsAbsTofOffset = APPLICATION_ABSTOF_DTOF_OFFSET_CALC_DNS_ABSTOF,
         .isCalculateDToFOffset      = APPLICATION_ABSTOF_DTOF_OFFSET_CALC_DTOF,
    };
#endif

    volatile USS_message_code code;
    USS_Algorithms_Results algResults;
    USS_calibration_hspll_results testResults;


    // Register PLL unlock event
    USS_registerHSPLLInterruptCallback(USS_HSPLL_Interrupt_PLLUNLOCK,
                                       &handlePllUnlockEvent);

    code = USS_configureUltrasonicMeasurement(&gUssSWConfig);
    checkCode(code, USS_message_code_no_error);

#if((USS_ALG_ABS_TOF_COMPUTATION_MODE == USS_ALG_ABS_TOF_COMPUTATION_MODE_LOBE_WIDE) || \
    (USS_ALG_ABS_TOF_COMPUTATION_MODE == USS_ALG_ABS_TOF_COMPUTATION_MODE_HILBERT_WIDE))
    // Reference binary pattern are only needed by
    // USS_Alg_AbsToF_Calculation_Option_lobeWide and
    // USS_Alg_AbsToF_Calculation_Option_hilbertWide AbsToF computation options
    if((USS_Alg_AbsToF_Calculation_Option_lobeWide ==
            gUssSWConfig.algorithmsConfig->absToFOption)
       || (USS_Alg_AbsToF_Calculation_Option_hilbertWide ==
               gUssSWConfig.algorithmsConfig->absToFOption))
    {
#if defined(__MSP430_HAS_SAPH_A__)
        if(USS_measurement_pulse_generation_mode_multi_tone ==
                gUssSWConfig.measurementConfig->pulseConfig->pulseGenMode)
        {
            code = USS_generateMultiToneBinaryPattern(&gUssSWConfig);
            checkCode(code, USS_message_code_no_error);
        }
#endif
        if(USS_measurement_pulse_generation_mode_multi_tone !=
                gUssSWConfig.measurementConfig->pulseConfig->pulseGenMode)
        {
            code = USS_generateMonoDualToneBinaryPattern(&gUssSWConfig);
            checkCode(code, USS_message_code_no_error);
        }
    }

#if (APPLICATION_ENABLE_BINARY_PATTERN_SIZE_SCALING == true)
    gUssSWConfig.algorithmsConfig->binaryPatternLength =
            (gUssSWConfig.captureConfig->sampleSize / APPLICATION_BINARY_PATTERN_SCALE_FACTOR);
#endif

#endif


    // Application must ensure no application level interrupts occur while
    // verifying HSPLL Frequency
    disableApplicationInterrupts();

    code = USS_verifyHSPLLFrequency(&gUssSWConfig, &testResults);

    // Application can re-enable interrupts after HSPLL verification
    enableApplicationInterrupts();

    checkCode(code, USS_message_code_no_error);

    gUssSWConfig.algorithmsConfig->clockRelativeError = _IQ27div((int32_t)(testResults.actualTestCount -
            testResults.expectedResult),testResults.expectedResult);

    code = USS_initAlgorithms(&gUssSWConfig);
    checkCode(code, USS_message_code_no_error);

#if (APPLICATION_ENABLE_SIGNAL_GAIN_CALIBRATION == true)
    code = USS_calibrateSignalGain(&gUssSWConfig);
    checkCode(code, USS_message_code_Signal_Gain_Calibration_successful);
#endif

#if (APPLICATION_ENABLE_ABSTOF_DTOF_OFFSET_CALIBRATION == true)
    code = USS_calculateOffsets(&gUssSWConfig, &abstoFDtofTestResults,
                                &abstoFDtofTestConfig);
    checkCode(code, USS_message_code_no_error);

    code = USS_updateAdditionalCaptureDelay(&gUssSWConfig,
          ((abstoFDtofTestResults.upsAbsToFOffset + abstoFDtofTestResults.dnsAbsToFOffset) /2.0f) -
          APPLICATION_ABSTOF_REFERENCE);
    checkCode(code, USS_message_code_no_error);

    code = USS_updateDtoFOffset(&gUssSWConfig, (-1.0f *abstoFDtofTestResults.dToFOffset));
    checkCode(code, USS_message_code_no_error);

#endif

    // Set the background timer period to 1 second
    USS_configAppTimerPeriod(&gUssSWConfig, gUssSWConfig.systemConfig->measurementPeriod);

    while(1)
    {

        code = USS_startLowPowerUltrasonicCapture(&gUssSWConfig);
        checkCode(code, USS_message_code_no_error);

        code = USS_runAlgorithms(&gUssSWConfig,&algResults);
        checkCode(code, USS_message_code_valid_results);

#if (APPLICATION_ENABLE_CHANNEL_SWAP == true)
        if(appSwapInterval == 0)
        {
            code = USS_swapCaptureChannels(&gUssSWConfig);
            code = USS_swapAlgorithmsCaptureBuffers(&gUssSWConfig);

            appSwapInterval = APPLICATION_CHANNEL_SWAP_INTERVAL;
        }else{
            appSwapInterval--;
        }
#endif

#if APPLICATION_ENABLE_UART_DEBUG
        uartTxUSSResult(APPLICATION_UART_ABSTOF_UPS_DELIM,&algResults.totalTOF_UPS);
        uartTxUSSResult(APPLICATION_UART_ABSTOF_DNS_DELIM,&algResults.totalTOF_DNS);
        uartTxUSSResult(APPLICATION_UART_DTOF_DELIM,&algResults.deltaTOF);
        uartTxUSSResult(APPLICATION_UART_VFR_DELIM,&algResults.volumeFlowRate);
#endif
        // Wait for timer to elapse
        USS_waitForAppTimerElapse(&gUssSWConfig,USS_low_power_mode_option_low_power_mode_3);
    }
}

#if APPLICATION_ENABLE_UART_DEBUG

void uartTxByte(char string)
{
    while(!(UCA1IFG & UCTXIFG));
    UCA1TXBUF = string;
}

void uartTxHexByte(uint8_t Data)
{
    uartTxByte(nibbleToHex(Data >> 4));
    uartTxByte(nibbleToHex(Data & 0x0F));
}

uint8_t nibbleToHex(uint8_t nibble)
{
    uint8_t ret = nibble;
    if(nibble < 10)
    {
        ret += '0';
    }
    else
    {
        ret += 'A' - 10;
    }

    return(ret);
}

void uartTxUSSResult(uint8_t delimiter, float *data)
{
    uint8_t *ptr;

    // Send delimiter
    uartTxByte(delimiter);
    // Send comma
    uartTxByte(',');

    ptr = (uint8_t *) data;

    // Send float values
    uartTxHexByte(ptr[3]);
    uartTxHexByte(ptr[2]);
    uartTxHexByte(ptr[1]);
    uartTxHexByte(ptr[0]);

    // Send new line return
    uartTxByte('\n');
    uartTxByte('\r');
}

#endif

void handlePllUnlockEvent(void)
{
    // If USS PLL unlock event is detected rest USS Module and reconfigure
    // measurement
    USS_resetUSSModule(&gUssSWConfig, true);
}


// This is a place holder for the application to disable interrupts which might
// be triggered during HSPLL verification
void disableApplicationInterrupts(void){

}

// This is a place holder for the application to enable interrupts once
// HSPLL verification has completed
void enableApplicationInterrupts(void){

}

void checkCode(USS_message_code code, USS_message_code expectedCode)
{
    if(code != expectedCode)
    {
        // Trap code
        while(1);
    }
}
