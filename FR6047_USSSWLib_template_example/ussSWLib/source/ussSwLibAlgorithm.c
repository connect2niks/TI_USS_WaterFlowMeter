//*****************************************************************************
// ussSwLibAlgorithm.c
//
// TI Release: USSLib_02_40_00_00
// Release Date: __LIB_RELEASE_DATE__
//
//*****************************************************************************
#include "ussSwLib.h"
#include "USS_Config/USS_userConfig.h"

USS_message_code USS_runAlgorithms(USS_SW_Library_configuration *config,
        USS_Algorithms_Results *results)
{
    USS_message_code code;
    USS_Algorithms_Results_fixed_point fixedResults;

    // Run Fixed Point Algorithms
    code = USS_runAlgorithmsFixedPoint(config, &fixedResults);

#if (USS_ALG_ENABLE_ESTIMATE_TEMPERATURE == true)
    if(config->algorithmsConfig->temperatureCalcOption == USS_Alg_temperature_Calculation_Option_enabled)
    {
        // Compute Temperature
        USS_computeTemperature(config, &fixedResults);
    }
#endif

#if (USS_ALG_ENABLE_ESTIMATE_TEMPERATURE == false && \
    USS_ALG_VFR_CALIB_MODE == USS_ALG_VFR_CALIB_OPTION_FLOW_TEMPERATURE)
#warning \
    "External Temperature Input required. Please modify USS_setTemperature below with valid temperature parameter."
    // External Temperature Input, change 10.0f with valid temperature
    USS_setTemperature(10.0f, &fixedResults);
#endif

    // Calibrate the Volume Flow Rate
    USS_calibrateVolumeFlowRate(config, &fixedResults);

    // Convert fixed results to float
    USS_getResultsInFloat(&fixedResults, results);

#if (USS_VFR_LARGE_PIPE_ADDL_SF_ENABLE)
    // Scale the volume flow rate
    USS_scaleVolumeFlowRate(config, results);
#endif

    return code;
}










