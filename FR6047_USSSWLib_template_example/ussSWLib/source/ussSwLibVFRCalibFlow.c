//*****************************************************************************
// ussSwLibVFRCalibFlow.c
//
// TI Release: USSLib_02_40_00_00
// Release Date: __LIB_RELEASE_DATE__
//
//*****************************************************************************
#include "ussSwLib.h"
#include "USS_Config/USS_userConfig.h"

int8_t USS_findMeterConstantRange(USS_Algorithms_Flow_Meter_Constant arr[],
                                     int8_t l, int8_t r, int32_t x)
{
    int32_t iq16minimumVFR;

    if (r >= l)
    {
        int mid = l + (r - l) / 2;

        iq16minimumVFR = arr[mid].iq16minimumVFR;

        if (iq16minimumVFR == x)
        {
            return mid;
        }
        else if (iq16minimumVFR > x)
        {
            return USS_findMeterConstantRange(arr, l, mid - 1, x);
        }
        else
        {
            return USS_findMeterConstantRange(arr, mid + 1, r, x);
        }
    }

    return (l-1);
}

USS_message_code USS_calibrateVFRFlow(
        USS_SW_Library_configuration *config,
        USS_Algorithms_Results_fixed_point *results)
{
    uint32_t iq16Volume;
    int32_t iq16TempMpy;
    USS_Alg_volume_Flow_Calib_Object * flowCalibObj;
    int8_t calibIdx;

    // Load local variables
    iq16Volume = results->iq16VolumeFlowRate;
    flowCalibObj = config->algorithmsConfig->calibObject.flowCalibObject;

    // Save the volume flow rate before applying calibration constants
    results->iq16VolumeFlowRateNoCalib = results->iq16VolumeFlowRate;

    // Find the calibration index
    calibIdx = USS_findMeterConstantRange(
            config->algorithmsConfig->calibObject.flowCalibObject->pMeterConfiguration, 0,
            config->algorithmsConfig->calibObject.flowCalibObject->numOfRanges-1, iq16Volume);

    if(calibIdx < 0)
    {
        calibIdx = 0;
    }

    // Multiple volume by slope
    iq16TempMpy = _IQ16mpy(iq16Volume, flowCalibObj->pMeterConfiguration[calibIdx].iq16Slope);
    // Add offset
    iq16Volume = iq16TempMpy + flowCalibObj->pMeterConfiguration[calibIdx].iq16Offset;

    results->iq16VolumeFlowRate = iq16Volume;

    return USS_message_code_valid_results;
}
