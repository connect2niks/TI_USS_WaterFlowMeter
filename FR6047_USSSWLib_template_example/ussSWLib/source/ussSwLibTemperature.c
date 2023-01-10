//*****************************************************************************
// ussSwLibTemperature.c
//
// TI Release: USSLib_02_40_00_00
// Release Date: __LIB_RELEASE_DATE__
//
//*****************************************************************************
#include "ussSwLib.h"
#include "USS_Config/USS_userConfig.h"

int16_t USS_findTemperature(USS_Alg_temperature_Calculation_Object * tempObj,int16_t l, int16_t r, int32_t x)
{
    if (r >= l)
    {
        int16_t mid = l + (r - l) / 2;
        int32_t delta = tempObj->pTempLUT[mid][0] - x;

        if (delta == 0)
        {
            return mid;
        }

        if (delta > 0)
        {
            return USS_findTemperature(tempObj, l, mid - 1, x);
        }

        return USS_findTemperature(tempObj, mid + 1, r, x);
    }

    return (l-1);
}

int32_t USS_calculateVelocity(USS_SW_Library_configuration *config,
                                 USS_Algorithms_Results_fixed_point *results)
{
    int32_t iq16Velocity;
    int32_t iq12Temp;
    int32_t iq49Temp;
    int32_t iq40TotalTOFSum;
    int32_t iq40TotalTOF_UPS;
    int32_t iq40TotalTOF_DNS;
    int32_t iq24TransducerConst;

    // Initialize local variables
    iq40TotalTOF_UPS = results->iq40TotalTOF_UPS;
    iq40TotalTOF_DNS = results->iq40TotalTOF_DNS;
    iq24TransducerConst = config->algorithmsConfig->tempCalcObject->iq24transducerConstant;

    // Calculate velocity
    // v = (L/2)*( (1/UPS) + (1/DNS)) = (L/2)*( (UPS+DNS)/(UPS*DNS) )
    iq40TotalTOFSum = iq40TotalTOF_UPS + iq40TotalTOF_DNS;
    iq49Temp = (int32_t)(((int64_t)iq40TotalTOF_UPS * (int64_t)iq40TotalTOF_DNS) >> 31);
    //iq12Temp's range is 46,000 to 48,000
    iq12Temp = _IQ21div(iq40TotalTOFSum,iq49Temp);

    iq16Velocity = _IQ20mpy(iq24TransducerConst, iq12Temp);

    return iq16Velocity;
}

USS_message_code USS_computeTemperature(USS_SW_Library_configuration *config,
                                        USS_Algorithms_Results_fixed_point *results)
{
    int32_t iq16Velocity;
    int32_t iq16TempK;
    int32_t iq16TempK1;
    int32_t iq16TempSum;
    int32_t iq16VelocityK;
    int32_t iq16Constant;
    int16_t tempIdx;
    uint16_t tableLength;

    if(config->algorithmsConfig->tempCalcObject == NULL)
    {
        return USS_message_code_algorithm_error_temperature_object;
    }

    // Calculate velocity
    iq16Velocity = USS_calculateVelocity(config,results);

    // Initialize local variables
    tableLength = config->algorithmsConfig->tempCalcObject->tempLUTLength;

    // Check if velocity is below the minimum velocity
    if(iq16Velocity < config->algorithmsConfig->tempCalcObject->pTempLUT[0][0])
    {
        tempIdx = 0;
    }
    // Check if velocity is above the maximum velocity
    else if(iq16Velocity > config->algorithmsConfig->tempCalcObject->pTempLUT[tableLength-1][0])
    {
        tempIdx = tableLength - 2;
    }
    else
    {
        // Get Index for temperature value
        tempIdx = USS_findTemperature(config->algorithmsConfig->tempCalcObject,
                                         0,
                                         tableLength-1,
                                         iq16Velocity);

        if(tempIdx >= tableLength - 1)
        {
            tempIdx = tableLength - 2;
        }
    }

    iq16TempK = config->algorithmsConfig->tempCalcObject->pTempLUT[tempIdx][1];
    iq16TempK1 = config->algorithmsConfig->tempCalcObject->pTempLUT[tempIdx+1][1];
    iq16VelocityK = config->algorithmsConfig->tempCalcObject->pTempLUT[tempIdx][0];
    iq16Constant = config->algorithmsConfig->tempCalcObject->pTempLUT[tempIdx][2];

    // Use linear interpolation to calculate temperature
    iq16TempSum = _IQ16mpy((iq16TempK1-iq16TempK),(iq16Velocity-iq16VelocityK));
    iq16TempSum = _IQ16mpy(iq16TempSum,iq16Constant);
    iq16TempSum = iq16TempSum + iq16TempK;

    // Store the calculated temperature
    results->iq16Temperature = iq16TempSum;

    return USS_message_code_no_error;
}

USS_message_code USS_setTemperature(float temperature,
                                    USS_Algorithms_Results_fixed_point *results)
{
    results->iq16Temperature = _IQ16(temperature);

    return USS_message_code_no_error;
}

