// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Settings.h"
#include "SettingsDisplay.h"
#include "Utils/Math.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int sDisplay_NumSignalsInS(void)
{
    return Tables_ENUMtoENumSignalsInSec(NUM_SIGNALS_IN_SEC);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void sDisplay_SetNumSignalsInS(int numSignalsInS)
{
    NUM_SIGNALS_IN_SEC = Tables_ENumSignalsInSecToENUM(numSignalsInS);
}
 

//----------------------------------------------------------------------------------------------------------------------------------------------------
int sDisplay_NumPointSmoothing(void)
{
    if(MODE_EMS && (SMOOTHING < NumSmooth_4points))
    {
        return 4;
    }

    int retValue = 0;
    if (SMOOTHINENABLED_DS)
    {
        retValue = SMOOTHING + 1; //-V2006
    }

    if (IN_RANDOM_MODE)
    {
        int numRand = 0;
        if (NRST_NUM_SMOOTH_FOR_RAND > 1)
        {
            numRand = NRST_NUM_SMOOTH_FOR_RAND;
        }

        LIMIT_BELOW(retValue, numRand);
    }


    return retValue;
}


//---------------------------------------------------------------------------------------------------------------------------------------------------
int sDisplay_NumAverage(void)
{
    if (MODE_EMS && (ENUM_AVE < ENumAverages_8))
    {
        return 8;
    }

    return (NUM_AVE);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void sDisplay_PointsOnDisplay(int *firstPoint, int *lastPoint)
{
    *firstPoint = SHIFT_IN_MEMORY;
    if (SET_PEAKDET_EN)
    {
        *firstPoint /= 2;
    }
    *lastPoint = *firstPoint + 281;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int sDisplay_ShiftInMemoryInPoints(void)
{
    if (SET_PEAKDET_DIS)
    {
        return SHIFT_IN_MEMORY;
    }
    return SHIFT_IN_MEMORY / 2;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int sDisplay_TimeMenuAutoHide(void)
{
    static const int times[] =
    {
        0, 5, 10, 15, 30, 60
    };
    return times[MENU_AUTO_HIDE] * 1000;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
bool sDisplay_IsSeparate(void)
{
    return FUNC_MODE_DRAW_SEPARATE || FFT_ENABLED;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void sDisplay_SetBrightness(int16 brightness)
{
    BRIGHTNESS_DISPLAY = brightness;
    Painter_SetBrightnessDisplay(brightness);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
ModeAveraging sDisplay_GetModeAveraging(void)
{
    if (IN_RANDOM_MODE)
    {
        return Averaging_Accurately;
    }
    return MODE_AVERAGING;
}
