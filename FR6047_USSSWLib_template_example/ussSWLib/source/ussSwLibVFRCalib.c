//*****************************************************************************
// ussSwLibVFRCalib.c
//
// TI Release: USSLib_02_40_00_00
// Release Date: __LIB_RELEASE_DATE__
//
//*****************************************************************************
#include "ussSwLib.h"
#include "USS_Config/USS_userConfig.h"

USS_message_code USS_calibrateVolumeFlowRate(
        USS_SW_Library_configuration *config,
        USS_Algorithms_Results_fixed_point *results)
{
    USS_message_code code = USS_message_code_no_error;

#if (USS_ALG_VFR_CALIB_MODE == USS_ALG_VFR_CALIB_OPTION_FLOW)
    if(config->algorithmsConfig->volumeCalibrationOption == \
            USS_Alg_volume_flow_Calibration_Option_flow)
    {
        code = USS_calibrateVFRFlow(config,results);
    }
#endif
#if (USS_ALG_VFR_CALIB_MODE == USS_ALG_VFR_CALIB_OPTION_FLOW_TEMPERATURE)
    if(config->algorithmsConfig->volumeCalibrationOption == \
            USS_Alg_volume_flow_Calibration_Option_flow_temperature)
    {
        code = USS_calibrateVFRFlowTemperature(config,results);
    }
#endif

    return code;
}

USS_message_code USS_scaleVolumeFlowRate(
        USS_SW_Library_configuration *config,
        USS_Algorithms_Results *results)
{
    float tempVolumeFlowRate;
    float addlScaleFactor;

    // Initialize local variables
    tempVolumeFlowRate = results->volumeFlowRate;
    addlScaleFactor = config->meterConfig->volumeAddlScaleFactor;

    // Scale volume flow rate by the additional scale factor
    results->volumeFlowRate = (tempVolumeFlowRate*addlScaleFactor);

    // Check if volume flow calibration is enabled
    if(config->algorithmsConfig->volumeCalibrationOption !=
            USS_Alg_volume_flow_Calibration_Option_disabled)
    {
        tempVolumeFlowRate = results->volumeFlowRateNoCalib;
        results->volumeFlowRateNoCalib = (tempVolumeFlowRate*addlScaleFactor);
    }
    else {
        results->volumeFlowRateNoCalib = results->volumeFlowRate;
    }

    return USS_message_code_no_error;
}
