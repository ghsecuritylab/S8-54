#include "defines.h"
#include "Timer.h"
#include "Log.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const TIM_HandleTypeDef handleTIM6 =
{
    TIM6,
    {
        179,
        TIM_COUNTERMODE_UP,     // Init.CounterMode
        500,                    // Init.Period
        TIM_CLOCKDIVISION_DIV1  // Init.ClockDivision
    }
};

static void (*f[TypeTimerSize])(void) = {0};
static uint reactionTimeMS[TypeTimerSize] = {0};
static int timePrevExecuteMS[TypeTimerSize] = {0};
static bool isRun[TypeTimerSize] = {false};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Timer_Init(void)
{
#ifndef _MS_VS
    __TIM6_CLK_ENABLE();        // ��� ������� �����������
    __TIM2_CLK_ENABLE();        // ��� �����
    __TIM5_CLK_ENABLE();
#endif

    HAL_TIM_Base_Init((TIM_HandleTypeDef*)&handleTIM6);

    HAL_TIM_Base_Start_IT((TIM_HandleTypeDef*)&handleTIM6);

    TIM_HandleTypeDef handleTIM2 =
    {
        TIM2,
        {
            0,
            TIM_COUNTERMODE_UP,
            0xffffffff,
            TIM_CLOCKDIVISION_DIV1
        }
    };

    HAL_TIM_Base_Init((TIM_HandleTypeDef*)&handleTIM2);

    HAL_TIM_Base_Start((TIM_HandleTypeDef*)&handleTIM2);

    TIM_HandleTypeDef handleTIM5 =
    {
        TIM5,
        {
            44999,             // WARN ��� � �� ����������, ��� ��������� ������ �� 1��. ��� 44999 ������ ����� - 2��.
            TIM_COUNTERMODE_UP,
            0xffffffff,
            TIM_CLOCKDIVISION_DIV1
        }
    };

    HAL_TIM_Base_Init((TIM_HandleTypeDef*)&handleTIM5);

    HAL_TIM_Base_Start((TIM_HandleTypeDef*)&handleTIM5);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_PauseOnTicks(uint numTicks)
{
    uint startTicks = gTimerTics;
    while (gTimerTics - startTicks < numTicks) {};
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_PauseOnTime(uint timeMS)
{
    uint time = gTimerMS;
    while(gTimerMS - time < timeMS) {};
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_StartMultiMeasurement(void)
{
    TIM2->CR1 &= (uint)~TIM_CR1_CEN;
    TIM2->CNT = 0;
    TIM2->CR1 |= TIM_CR1_CEN; 
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static uint timeStartLogging = 0;
static uint timePrevPoint = 0;


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_StartLogging(void)
{
    timeStartLogging = gTimerTics;
    timePrevPoint = timeStartLogging;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
uint Timer_LogPointUS(char *name)
{
    uint interval = gTimerTics - timePrevPoint;
    timePrevPoint = gTimerTics;
    LOG_WRITE("%s %.2f us", name, interval / 120.0f);
    return interval;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
uint Timer_LogPointMS(char *name)
{
    uint interval = gTimerTics - timePrevPoint;
    timePrevPoint = gTimerTics;
    LOG_WRITE("%s %.2f ms", name, interval / 120e3);
    return interval;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_Enable(TypeTimer type, int timeInMS, void(*eF)(void))
{
    f[type] = eF;
    reactionTimeMS[type] = timeInMS;
    timePrevExecuteMS[type] = gTimerMS;
    isRun[type] = true;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_Disable(TypeTimer type)
{
    isRun[type] = false;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_Pause(TypeTimer type)
{
    isRun[type] = false;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_Continue(TypeTimer type)
{
    isRun[type] = true;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
bool Timer_IsRun(TypeTimer type)
{
    return isRun[type];
};


//------------------------------------------------------------------------------------------------------------------------------------------------------
static void Timer_Update(void)
{
    uint curTimeMS = gTimerMS;

    for(int num = 0; num < TypeTimerSize; num++)
    {
        if(isRun[num])
        {
            uint delta = curTimeMS - timePrevExecuteMS[num];
            if(delta >= reactionTimeMS[num])
            {
                f[num]();
                timePrevExecuteMS[num] = curTimeMS;
            }
            
        }
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void TIM6_DAC_IRQHandler(void)
{
    if (__HAL_TIM_GET_FLAG(&handleTIM6, TIM_FLAG_UPDATE) == SET && __HAL_TIM_GET_ITSTATUS(&handleTIM6, TIM_IT_UPDATE))
    {
        Timer_Update();
        __HAL_TIM_CLEAR_FLAG(&handleTIM6, TIM_FLAG_UPDATE);
        __HAL_TIM_CLEAR_IT(&handleTIM6, TIM_IT_UPDATE);
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------------------------------------------------------------------------------
void PersonalTimer_Start(TypePersonalTimer type, uint timeMS, bool repeat, pFuncVV func)
{

}

//---------------------------------------------------------------------------------------------------------------------------------------------------
void PersonalTimer_Stop(TypePersonalTimer type)
{

}

//---------------------------------------------------------------------------------------------------------------------------------------------------
void TIM2_IRQHandler(void)
{

}
