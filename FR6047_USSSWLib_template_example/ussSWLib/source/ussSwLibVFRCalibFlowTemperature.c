//*****************************************************************************
// ussSwLibVFRCalibFlowTemperature.c
//
// TI Release: USSLib_02_40_00_00
// Release Date: __LIB_RELEASE_DATE__
//
//*****************************************************************************
#include "ussSwLib.h"
#include "USS_Config/USS_userConfig.h"

USS_message_code USS_calculateVolumeFlowRate(USS_SW_Library_configuration *config,
                                                USS_Algorithms_Results_fixed_point *results)
{
    int32_t iq16TempSum;
    int32_t iq16TempMpy;
    int32_t iq16M0;
    int32_t iq16M1;
    int32_t iq16M2;
    int32_t iq16M3;
    int32_t iq16VolumeFlowRate;
    int32_t iq16Temperature;
    uint8_t row,col,numFlows;
    uint16_t mcIdx;

    // Initialize local variables
    row = config->algorithmsConfig->calibObject.flowTempCalibObject->rowNum;
    col = config->algorithmsConfig->calibObject.flowTempCalibObject->colNum;
    numFlows = config->algorithmsConfig->calibObject.flowTempCalibObject->numOfFlows;
    mcIdx = col + (row*(numFlows-1));
    iq16Temperature = results->iq16Temperature;
    iq16VolumeFlowRate = results->iq16VolumeFlowRate;
    results->iq16VolumeFlowRateNoCalib = iq16VolumeFlowRate;

    iq16M0 = config->algorithmsConfig->calibObject.flowTempCalibObject->pQuadMeterConstants[mcIdx].iq16M0;
    iq16M1 = config->algorithmsConfig->calibObject.flowTempCalibObject->pQuadMeterConstants[mcIdx].iq16M1;
    iq16M2 = config->algorithmsConfig->calibObject.flowTempCalibObject->pQuadMeterConstants[mcIdx].iq16M2;
    iq16M3 = config->algorithmsConfig->calibObject.flowTempCalibObject->pQuadMeterConstants[mcIdx].iq16M3;

    iq16TempMpy = _IQ16mpy(iq16M3, iq16VolumeFlowRate);
    iq16TempMpy = _IQ16mpy(iq16TempMpy, iq16Temperature);

    iq16TempSum = iq16M0 + _IQ16mpy(iq16M1, iq16VolumeFlowRate);
    iq16TempSum = iq16TempSum + _IQ16mpy(iq16M2, iq16Temperature);
    iq16TempSum = iq16TempSum + iq16TempMpy;

    results->iq16VolumeFlowRate = iq16TempSum;

    return USS_message_code_no_error;
}

int32_t USS_getFlow(uint8_t col, uint8_t row, uint8_t numFlows,
                       USS_Algorithms_Quad_Point *pQuadPoints)
{
    uint16_t index;

    index = (uint16_t) col + ((uint16_t) row * (uint16_t) numFlows);
    return pQuadPoints[index].iq16Flow;
}

int32_t USS_getTemp(uint8_t col, uint8_t row, uint8_t numFlows,
                       USS_Algorithms_Quad_Point *pQuadPoints)
{
    uint16_t index;

    index = (uint16_t) col + ((uint16_t) row * (uint16_t) numFlows);
    return pQuadPoints[index].iq16Temp;
}

USS_message_code USS_isPtInside(USS_SW_Library_configuration *config,
                                   int8_t row,
                                   int8_t col,
                                   USS_Algorithms_Results_fixed_point *results)
{
    uint8_t numFlows,numTemps;
    USS_Algorithms_Quad_Point *pQuadPt;
    int32_t iq16VolumeFlowRate;
    int32_t iq16pFlow[4];
    int32_t iq16pTemp[4];
    uint8_t inside;
    int32_t iq16Flow1;
    int32_t iq16Flow2;
    int32_t iq16Temp1;
    int32_t iq16Temp2;

    int32_t iq16DeltaFlow;
    int32_t iq16Temperature;
    int32_t iq10TemperatureEst;
    int32_t iq10TemperatureDx;

    uint8_t idx;

    // Initialize local variables
    numFlows = config->algorithmsConfig->calibObject.flowTempCalibObject->numOfFlows;
    numTemps = config->algorithmsConfig->calibObject.flowTempCalibObject->numOfTemps;
    pQuadPt = config->algorithmsConfig->calibObject.flowTempCalibObject->pQuadPoints;
    iq16VolumeFlowRate = results->iq16VolumeFlowRate;
    iq16Temperature = results->iq16Temperature;
    inside = 0;

    // Increment search quadrilateral count
    config->algorithmsConfig->calibObject.flowTempCalibObject->searchQuadCount++;

    // Check for invalid coordinates
    if (row < 0 || col < 0 || row >= (numTemps-1) || col >= (numFlows-1))
    {
        return USS_message_code_Calibration_VFR_pt_outside_quadrilateral;
    }

    //    x1y1 ---- x2y2
    //     |          |
    //     |          |
    //     |          |
    //    x0y0 ---- x3y3

    iq16pFlow[0] = USS_getFlow(col,row+1,numFlows,pQuadPt);
    iq16pTemp[0] = USS_getTemp(col,row+1,numFlows,pQuadPt);
    iq16pFlow[1] = USS_getFlow(col,row,numFlows,pQuadPt);
    iq16pTemp[1] = USS_getTemp(col,row,numFlows,pQuadPt);
    iq16pFlow[2] = USS_getFlow(col+1,row,numFlows,pQuadPt);
    iq16pTemp[2] = USS_getTemp(col+1,row,numFlows,pQuadPt);
    iq16pFlow[3] = USS_getFlow(col+1,row+1,numFlows,pQuadPt);
    iq16pTemp[3] = USS_getTemp(col+1,row+1,numFlows,pQuadPt);

    iq16Flow1 = iq16pFlow[3];
    iq16Temp1 = iq16pTemp[3];

    for (idx=0;idx<4;idx++)
    {
        iq16Flow2 = iq16pFlow[idx];
        iq16Temp2 = iq16pTemp[idx];

        if( ((iq16Flow1 <= iq16VolumeFlowRate) && (iq16VolumeFlowRate <= iq16Flow2)) ||
             ((iq16Flow2 <= iq16VolumeFlowRate) && (iq16VolumeFlowRate <= iq16Flow1)))
        {
            iq16DeltaFlow = iq16Flow2 - iq16Flow1;
            iq10TemperatureEst = _IQ16mpy(((iq16Temp2-iq16Temp1)>>6),(iq16VolumeFlowRate-iq16Flow1));
            iq10TemperatureEst = iq10TemperatureEst + _IQ16mpy(iq16Temp1>>6,iq16DeltaFlow);

            // OVERFLOW WARNING: The product between temperature x delta between neighbor flow rates / 64 is limited to 32k
            iq10TemperatureDx = _IQ16mpy(iq16Temperature>>6, iq16DeltaFlow);

            if ( ((iq16VolumeFlowRate < iq16Flow1) || (iq16VolumeFlowRate < iq16Flow2))
                    && ( ((iq10TemperatureDx < iq10TemperatureEst) && (iq16DeltaFlow > 0)) ||
                          ((iq10TemperatureDx > iq10TemperatureEst) && (iq16DeltaFlow < 0))))
            {
                // Toggle the inside bit
                inside ^= 0x01;
            }
            else if((iq16Temperature >= iq16Temp1 || iq16Temperature >= iq16Temp2) &&
                    (iq16Temperature <= iq16Temp1 || iq16Temperature <= iq16Temp2) &&
                    (iq10TemperatureEst == iq10TemperatureDx))
            {
                // The point is on the line
                inside = 0x01;
                break;
            }
        }

        iq16Flow1 = iq16Flow2;
        iq16Temp1 = iq16Temp2;
    }

    if (inside == 0)
    {
        return USS_message_code_Calibration_VFR_pt_outside_quadrilateral;
    }
    else
    {
        return USS_message_code_Calibration_VFR_pt_inside_quadrilateral;
    }
}

USS_message_code USS_initialSearchQuad(USS_SW_Library_configuration *config,
                                          USS_Algorithms_Results_fixed_point *results)
{
    int32_t iq16VolumeFlowRate;
    int32_t iq16Temperature;
    int32_t iq16Temp1;
    int32_t iq16Temp2;
    uint8_t row,col,numFlows,numTemps,idx;
    USS_Algorithms_Quad_Point *pQuadPt;

    // Initialize local variables
    numFlows = config->algorithmsConfig->calibObject.flowTempCalibObject->numOfFlows;
    numTemps = config->algorithmsConfig->calibObject.flowTempCalibObject->numOfTemps;
    pQuadPt = config->algorithmsConfig->calibObject.flowTempCalibObject->pQuadPoints;
    iq16VolumeFlowRate = results->iq16VolumeFlowRate;
    iq16Temperature = results->iq16Temperature;
    col = 0;
    row = 0;

    // Find initial column

    // Check if the flow is below the lowest flow in the first row (highest temperature)
    if (iq16VolumeFlowRate < USS_getFlow(col,row,numFlows,pQuadPt))
    {
        col = 0;
    }
    // Check if the flow is above the highest flow in the first row (highest temperature)
    else if(iq16VolumeFlowRate >= USS_getFlow(numFlows-1,row,numFlows,pQuadPt))
    {
        col = numFlows-2;
    }
    else
    {
        // Find a flow that is in between 2 consecutive flows
        for(idx=0;idx<(numFlows-1);idx++)
        {
            iq16Temp1 = USS_getFlow(idx,row,numFlows,pQuadPt);
            iq16Temp2 = USS_getFlow(idx+1,row,numFlows,pQuadPt);

            if ((iq16VolumeFlowRate >= iq16Temp1) &&
                (iq16VolumeFlowRate < iq16Temp2))
            {
                col = idx;
                break;
            }
        }
    }

    // Find initial row

    // Check if the temp is above the highest temp in the found column
    if (iq16Temperature > USS_getTemp(col,row,numFlows,pQuadPt))
    {
        row = 0;
    }
    // Check if the temp is below the lowest temperature in the found column
    else if(iq16Temperature <= USS_getTemp(col,numTemps-1,numFlows,pQuadPt))
    {
        row = numTemps-2;
    }
    else
    {
        // Find a temperature that is in between 2 consecutive temps
        for(idx=0;idx<(numTemps-1);idx++)
        {
            iq16Temp1 = USS_getTemp(col,idx,numFlows,pQuadPt);
            iq16Temp2 = USS_getTemp(col,idx+1,numFlows,pQuadPt);

            if ((iq16Temperature <= iq16Temp1) &&
                    (iq16Temperature > iq16Temp2))
            {
                row = idx;
                break;
            }
        }
    }

    // Save the row and column
    config->algorithmsConfig->calibObject.flowTempCalibObject->rowNum = row;
    config->algorithmsConfig->calibObject.flowTempCalibObject->colNum = col;

    return USS_message_code_no_error;
}

USS_message_code USS_searchNeighborQuad(USS_SW_Library_configuration *config,
                                           USS_Algorithms_Results_fixed_point *results)
{
    USS_message_code code;
    int32_t iq16VolumeFlowRate;
    int32_t iq16Temperature;
    USS_Algorithms_Quad_Point *pQuadPt;
    int32_t iq16pFlow[4];
    int32_t iq16pTemp[4];
    int8_t row;
    int8_t col;
    uint8_t numFlows;

    // Initialize local variables
    iq16VolumeFlowRate = results->iq16VolumeFlowRate;
    iq16Temperature = results->iq16Temperature;
    numFlows = config->algorithmsConfig->calibObject.flowTempCalibObject->numOfFlows;
    pQuadPt = config->algorithmsConfig->calibObject.flowTempCalibObject->pQuadPoints;
    row = config->algorithmsConfig->calibObject.flowTempCalibObject->rowNum;
    col = config->algorithmsConfig->calibObject.flowTempCalibObject->colNum;

    //    x1y1 ---- x2y2
    //     |          |
    //     |          |
    //     |          |
    //    x0y0 ---- x3y3

    iq16pFlow[0] = USS_getFlow(col,row+1,numFlows,pQuadPt);
    iq16pTemp[0] = USS_getTemp(col,row+1,numFlows,pQuadPt);
    iq16pFlow[1] = USS_getFlow(col,row,numFlows,pQuadPt);
    iq16pTemp[1] = USS_getTemp(col,row,numFlows,pQuadPt);
    iq16pFlow[2] = USS_getFlow(col+1,row,numFlows,pQuadPt);
    iq16pTemp[2] = USS_getTemp(col+1,row,numFlows,pQuadPt);
    iq16pFlow[3] = USS_getFlow(col+1,row+1,numFlows,pQuadPt);
    iq16pTemp[3] = USS_getTemp(col+1,row+1,numFlows,pQuadPt);

    // Initialize code to inside
    code = USS_message_code_Calibration_VFR_pt_inside_quadrilateral;

    // Check if point is to the right
    if ( (iq16VolumeFlowRate > iq16pFlow[2]) ||
            (iq16VolumeFlowRate > iq16pFlow[3]))
    {
        //  If true, discard top left, left and bottom left
        if ( (iq16Temperature > iq16pTemp[1]) ||
                    (iq16Temperature > iq16pTemp[2]))
        {
            // If true, discard bottom and bottom right

            // Check right
            if (USS_isPtInside(config,row,col+1,results) == USS_message_code_Calibration_VFR_pt_inside_quadrilateral)
            {
                col = col + 1;
            }
            // Check top right
            else if (USS_isPtInside(config,row-1,col+1,results) == USS_message_code_Calibration_VFR_pt_inside_quadrilateral)
            {
                col = col + 1;
                row = row - 1;
            }
            // Check top
            else if (USS_isPtInside(config,row-1,col,results) == USS_message_code_Calibration_VFR_pt_inside_quadrilateral)
            {
                row = row - 1;
            }
            else
            {
                // If all 3 quadrants returned false, then the point is outside
                code = USS_message_code_Calibration_VFR_pt_outside_quadrilateral;
            }
        }
        else
        {
            // If false, discard top and top right

            // Check right
            if (USS_isPtInside(config,row,col+1,results) == USS_message_code_Calibration_VFR_pt_inside_quadrilateral)
            {
                col = col + 1;
            }
            // Check bottom right
            else if (USS_isPtInside(config,row+1,col+1,results) == USS_message_code_Calibration_VFR_pt_inside_quadrilateral)
            {
                col = col + 1;
                row = row + 1;
            }
            // Check bottom
            else if (USS_isPtInside(config,row+1,col,results) == USS_message_code_Calibration_VFR_pt_inside_quadrilateral)
            {
                row = row + 1;
            }
            else
            {
                // If all 3 quadrants returned false, then the point is outside
                code = USS_message_code_Calibration_VFR_pt_outside_quadrilateral;
            }
        }
    }
    else
    {
        // If false, discards top right, right and bottom right

        if ( (iq16Temperature > iq16pTemp[1]) ||
                    (iq16Temperature > iq16pTemp[2]))
        {
            // If true, discard bottom and bottom left

            // Check left
            if (USS_isPtInside(config,row,col-1,results) == USS_message_code_Calibration_VFR_pt_inside_quadrilateral)
            {
                col = col - 1;
            }
            // Check top left
            else if (USS_isPtInside(config,row-1,col-1,results) == USS_message_code_Calibration_VFR_pt_inside_quadrilateral)
            {
                col = col - 1;
                row = row - 1;
            }
            // Check top
            else if (USS_isPtInside(config,row-1,col,results) == USS_message_code_Calibration_VFR_pt_inside_quadrilateral)
            {
                row = row - 1;
            }
            else
            {
                // If all 3 quadrants returned false, then the point is outside
                code = USS_message_code_Calibration_VFR_pt_outside_quadrilateral;
            }
        }
        else
        {
            // If false, discard top and top left

            // Check left
            if (USS_isPtInside(config,row,col-1,results) == USS_message_code_Calibration_VFR_pt_inside_quadrilateral)
            {
                col = col - 1;
            }
            // Check bottom left
            else if (USS_isPtInside(config,row+1,col-1,results) == USS_message_code_Calibration_VFR_pt_inside_quadrilateral)
            {
                col = col - 1;
                row = row + 1;
            }
            // Check bottom
            else if (USS_isPtInside(config,row+1,col,results) == USS_message_code_Calibration_VFR_pt_inside_quadrilateral)
            {
                row = row + 1;
            }
            else
            {
                // If all 3 quadrants returned false, then the point is outside
                code = USS_message_code_Calibration_VFR_pt_outside_quadrilateral;
            }
        }
    }

    // Save the row and column
    config->algorithmsConfig->calibObject.flowTempCalibObject->rowNum = row;
    config->algorithmsConfig->calibObject.flowTempCalibObject->colNum = col;

    return code;
}

USS_message_code USS_calibrateVFRFlowTemperature(
        USS_SW_Library_configuration *config,
        USS_Algorithms_Results_fixed_point *results)
{
    USS_message_code code;

    // Initialize search quadrilateral count to 0
    config->algorithmsConfig->calibObject.flowTempCalibObject->searchQuadCount = 0;

    // Check state of statemachine to find correct quadrilateral
    switch(config->algorithmsConfig->calibObject.flowTempCalibObject->state)
    {
    case USS_Alg_volume_flow_Calibration_state_track:
        // Check if point is inside
        code = USS_isPtInside(config,
                              config->algorithmsConfig->calibObject.flowTempCalibObject->rowNum,
                              config->algorithmsConfig->calibObject.flowTempCalibObject->colNum,
                              results);
        // if point is still inside quadrilateral exit switch case
        if(code == USS_message_code_Calibration_VFR_pt_inside_quadrilateral)
        {
            break;
        }
        else
        {
            // If point is outside then check neighbors
            code = USS_searchNeighborQuad(config,results);
            // if point is inside a neighbor quadrilateral exit switch case
            if(code == USS_message_code_Calibration_VFR_pt_inside_quadrilateral)
            {
                break;
            }
            else
            {
                // Start search again
                config->algorithmsConfig->calibObject.flowTempCalibObject->state = USS_Alg_volume_flow_Calibration_state_search;
            }
        }
    case USS_Alg_volume_flow_Calibration_state_search:
        USS_initialSearchQuad(config,results);
        // Check if point is inside the initially found quadrilateral based on row/column
        code = USS_isPtInside(config,
                                 config->algorithmsConfig->calibObject.flowTempCalibObject->rowNum,
                                 config->algorithmsConfig->calibObject.flowTempCalibObject->colNum,
                                 results);
        if(code == USS_message_code_Calibration_VFR_pt_inside_quadrilateral)
        {
            config->algorithmsConfig->calibObject.flowTempCalibObject->state = USS_Alg_volume_flow_Calibration_state_track;
            break;
        }

        // If point is outside then check neighbors
        code = USS_searchNeighborQuad(config,results);
        // if point is inside a neighbor quadrilateral, then switch state machine to track state
        if(code == USS_message_code_Calibration_VFR_pt_inside_quadrilateral)
        {
            config->algorithmsConfig->calibObject.flowTempCalibObject->state = USS_Alg_volume_flow_Calibration_state_track;
        }
        else
        {
            // Add 10 to searchQuadCount when the point is outside all the searched quadrilaterals
            config->algorithmsConfig->calibObject.flowTempCalibObject->searchQuadCount += 10;
        }

        break;
    default:
        break;
    }

    // Calculate updated volume flow rate using m0-m3 coefficients
    USS_calculateVolumeFlowRate(config,results);

    return USS_message_code_valid_results;
}







