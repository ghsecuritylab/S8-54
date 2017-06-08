// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "defines.h"
#include "Globals.h"
#include "Log.h"
#include "Sound.h"
#include "Settings/Settings.h"
#include "Utils/Math.h"
#include "Hardware/Timer.h"
#include <stm32f437xx.h>
#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_tim.h>
#include <stm32f4xx_hal_dac.h>
#include <stm32f4xx_hal_gpio.h>
#include <stm32f4xx_hal_dma.h>
#include <stm32f4xx_hal_dma_ex.h>
#include <math.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define POINTS_IN_PERIOD_SOUND 10
static uint8 points[POINTS_IN_PERIOD_SOUND] = {0};
static float frequency = 0.0f;
static float amplitude = 0.0f;
static TypeWave typeWave = TypeWave_Sine;
static bool soundWarnIsBeep = false;
static bool buttonIsPressed = false;    ///< \brief ����� ����������� ���� ������� ������, ��������������� ���� ����, ����� �����, ����������� �� ���� 
                                        ///< ����������
static bool isBeep = false;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sound_Init(void)
{
    DAC_ChannelConfTypeDef config =
    {
        DAC_TRIGGER_T7_TRGO,
        DAC_OUTPUTBUFFER_ENABLE
    };

    HAL_DAC_DeInit(&handleDAC);

    HAL_DAC_Init(&handleDAC);

    HAL_DAC_ConfigChannel(&handleDAC, &config, DAC_CHANNEL_1);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
static void Stop(void)
{
    HAL_DAC_Stop_DMA(&handleDAC, DAC_CHANNEL_1);
    isBeep = false;
    soundWarnIsBeep = false;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void TIM7_Config(uint16 prescaler, uint16 period)
{
    static TIM_HandleTypeDef htim =
    {
        TIM7,
        {
            0,
            TIM_COUNTERMODE_UP,
        }
    };

    htim.Init.Prescaler = prescaler;
    htim.Init.Period = period;
    htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    HAL_TIM_Base_Init(&htim);

    TIM_MasterConfigTypeDef masterConfig =
    {
        TIM_TRGO_UPDATE,
        TIM_MASTERSLAVEMODE_DISABLE
    };

    HAL_TIMEx_MasterConfigSynchronization(&htim, &masterConfig);

    HAL_TIM_Base_Stop(&htim);
    HAL_TIM_Base_Start(&htim);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
uint16 CalculatePeriodForTIM(void)
{
#define MULTIPLIER_CALCPERFORTIM 30e6f

    return (uint16)(MULTIPLIER_CALCPERFORTIM / frequency / POINTS_IN_PERIOD_SOUND);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void CalculateSine(void)
{
    for(int i = 0; i < POINTS_IN_PERIOD_SOUND; i++)
    {
        float step = 2.0f * 3.1415926f / (POINTS_IN_PERIOD_SOUND - 1);
        float value = (sinf(i * step) + 1.0f) / 2.0f;
        float v = value * amplitude * 255.0f;
        points[i] = (uint8)v;
    }

    for (int i = 0; i < POINTS_IN_PERIOD_SOUND; i++)
    {
        if (i < POINTS_IN_PERIOD_SOUND / 2)
        {
            points[i] = 0;
        }
        else
        {
            points[i] = (uint8)(255.0f * amplitude);
        }
    }

    //LOG_WRITE("min = %d, max = %d", min, max);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void CalculateMeandr(void)
{
    for(int i = 0; i < POINTS_IN_PERIOD_SOUND / 2; i++)
    {
        points[i] = (uint8)(255.0f * amplitude);
    }
    for(int i = POINTS_IN_PERIOD_SOUND / 2; i < POINTS_IN_PERIOD_SOUND; i++)
    {
        points[i] = 0;
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void CalculateTriangle(void)
{
    float k = 255.0 / POINTS_IN_PERIOD_SOUND;
    for(int i = 0; i < POINTS_IN_PERIOD_SOUND; i++)
    {
        points[i] = (uint8)(k * (float)i * amplitude);
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void SetWave(void)
{
    TIM7_Config(0, CalculatePeriodForTIM());

    if(typeWave == TypeWave_Sine)
    {
        CalculateSine();
    }
    else if(typeWave == TypeWave_Meandr)
    {
        CalculateMeandr();
    }
    else if(typeWave == TypeWave_Triangle)
    {
        CalculateTriangle();
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
static void Sound_Beep(const TypeWave newTypeWave, const float newFreq, const float newAmpl, const int newDuration)
{
    if (soundWarnIsBeep)
    {
        return;
    }
    if (!SOUND_ENABLED)
    {
        return;
    }
    if (frequency != newFreq || amplitude != newAmpl || typeWave != newTypeWave) //-V550
    {
        frequency = newFreq;
        amplitude = newAmpl * SOUND_VOLUME / 100.0f;
        typeWave = newTypeWave;
        
        Stop();
        SetWave();
    }

    Stop();
    
    isBeep = true;
    
    HAL_DAC_Start_DMA(&handleDAC, DAC_CHANNEL_1, (uint32_t*)points, POINTS_IN_PERIOD_SOUND, DAC_ALIGN_8B_R);

    Timer_SetAndStartOnce(kStopSound, Stop, newDuration);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Sound_ButtonPress(void)
{
    Sound_Beep(TypeWave_Sine, 2000.0f, 0.75f, 50);
    buttonIsPressed = true;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Sound_ButtonRelease(void)
{
    if (buttonIsPressed)
    {
        Sound_Beep(TypeWave_Sine, 1000.0f, 0.5f, 50);
        buttonIsPressed = false;
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Sound_GovernorChangedValue(void)
{
    Sound_Beep(TypeWave_Sine, 1000.0f, 0.5f, 50);
    buttonIsPressed = false;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Sound_RegulatorShiftRotate(void)
{
    Sound_Beep(TypeWave_Sine, 1.0f, 0.2f, 3);
    buttonIsPressed = false;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Sound_RegulatorSwitchRotate(void)
{
    Sound_Beep(TypeWave_Sine, 500.0f, 0.5f, 75);
    buttonIsPressed = false;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Sound_WarnBeepBad(void)
{
    Sound_Beep(TypeWave_Meandr, 500.0f, 1.0f, 500);
    soundWarnIsBeep = true;
    buttonIsPressed = false;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Sound_WarnBeepGood(void)
{
    Sound_Beep(TypeWave_Triangle, 1000.0f, 1.0f, 500);
    buttonIsPressed = false;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Sound_WaitCompletion(void)
{
    while (isBeep)
    {

    };
}
