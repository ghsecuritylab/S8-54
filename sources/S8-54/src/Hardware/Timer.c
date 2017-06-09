// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Timer.h"
#include "Log.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    pFuncVV func;       // ������� �������
    uint dTms;          // ������ ������������, ��
    uint timeFirstMS;   // ����� ������� ������������
    uint timeNextMS;    // ����� ���������� ������������. ���� == 0xffffffff, �� ������ ���������
    bool repeat;        // ���� true, ����� �����������, ���� �� ����� ������� ������� Timer_Disable()
} TimerStruct;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static TimerStruct timers[NumTimers];
static TIM_HandleTypeDef handleTIM3;
static uint timeStartLogging = 0;
static uint timePrevPoint = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#undef TIME_NEXT
#define TIME_NEXT(type) (timers[type].timeNextMS)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void StartTIM(uint timeStop);    // ������� �����, ������� ����������� � timeStop ��
static void StopTIM(void);
static uint NearestTime(void);          // ���������� ����� ������������ ���������� �������, ���� 0, ���� �������� ���
static void TuneTIM(TypeTimer2 type);   // ��������� ������� �� ������


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Timer_IsRun(TypeTimer2 type)
{
    return TIME_NEXT(type) != MAX_UINT;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_Init(void)
{
    for(uint i = 0; i < NumTimers; i++)
    {
        timers[i].timeNextMS = MAX_UINT;
    }

    __HAL_RCC_TIM2_CLK_ENABLE();    // ��� �����
    __HAL_RCC_TIM3_CLK_ENABLE();    // ��� ��������
    __HAL_RCC_TIM5_CLK_ENABLE();    // ��� �����������

    HAL_NVIC_EnableIRQ(TIM3_IRQn);
    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 1);

    handleTIM3.Instance = TIM3;
    handleTIM3.Init.Prescaler = 54000 - 1;
    handleTIM3.Init.CounterMode = TIM_COUNTERMODE_UP;
    handleTIM3.Init.Period = 1;
    handleTIM3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    TIM_HandleTypeDef handleTIM2;
    handleTIM2.Instance = TIM2;
    handleTIM2.Init.Prescaler = 0;
    handleTIM2.Init.CounterMode = TIM_COUNTERMODE_UP;
    handleTIM2.Init.Period = (uint)-1;
    handleTIM2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Base_Init(&handleTIM2);
    HAL_TIM_Base_Start(&handleTIM2);

    TIM_HandleTypeDef handleTIM5;
    handleTIM5.Instance = TIM5;
    handleTIM5.Init.Prescaler = 44999;
    handleTIM5.Init.CounterMode = TIM_COUNTERMODE_UP;
    handleTIM5.Init.Period = (uint) -1;
    handleTIM5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Base_Init(&handleTIM5);
    HAL_TIM_Base_Start(&handleTIM5);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&handleTIM3);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_Set(TypeTimer2 type, pFuncVV func, uint dTms)
{
    TimerStruct *timer = &timers[type];
    timer->func = func;
    timer->dTms = dTms;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_SetAndStartOnce(TypeTimer2 type, pFuncVV func, uint dTms)
{
    Timer_Set(type, func, dTms);
    Timer_StartOnce(type);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_SetAndEnable(TypeTimer2 type, pFuncVV func, uint dTms)
{
    Timer_Set(type, func, dTms);
    Timer_Enable(type);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_StartOnce(TypeTimer2 type)
{
    timers[type].repeat = false;
    TuneTIM(type);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_Enable(TypeTimer2 type)
{
    timers[type].repeat = true;
    TuneTIM(type);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
static void TuneTIM(TypeTimer2 type)
{
    TimerStruct *timer = &timers[type];
    timer->timeFirstMS = gTimeMS;

    uint timeNearest = NearestTime();

    uint timeNext = timer->timeFirstMS + timer->dTms;
    timer->timeNextMS = timeNext;

    if(timeNext < timeNearest)      // ���� ������ ������ ��������� ������ ��������
    {
        StartTIM(timeNext);         // �� ������� ������ �� ���� �����
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_Disable(TypeTimer2 type)
{
    timers[type].timeNextMS = MAX_UINT;
    timers[type].repeat = false;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
static uint NearestTime(void)
{
    uint time = MAX_UINT;

    for(uint type = 0; type < NumTimers; type++)
    {
        if(TIME_NEXT(type) < time)
        {
            time = TIME_NEXT(type);
        }
    }
    
    return time;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
static void StartTIM(uint timeStopMS)
{
    StopTIM();

    if(timeStopMS == MAX_UINT)
    {
        return;
    }

    uint dT = timeStopMS - gTimeMS;

    handleTIM3.Init.Period = (dT * 2) - 1;      // 10 ������������� 0.1��. �.�. ���� ��� ����� 1��, ����� �������� (100 - 1)

    HAL_TIM_Base_Init(&handleTIM3);
    HAL_TIM_Base_Start_IT(&handleTIM3);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    uint time = gTimeMS;
    uint nearestTime = NearestTime();

    if (nearestTime > time)
    {
        return;
    }

    StopTIM();

    for (uint type = 0; type < NumTimers; type++)
    {
        if (TIME_NEXT(type) <= time)            // ���� ������ ����� ������������
        {
            TimerStruct *timer = &timers[type];
            timer->func();
            if (timer->repeat)
            {
                timer->timeNextMS += timer->dTms;
            }
            else
            {
                timer->timeNextMS = MAX_UINT;
            }
        }
    }

    StartTIM(NearestTime());
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
static void StopTIM(void)
{
    HAL_TIM_Base_Stop_IT(&handleTIM3);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_PauseOnTime(uint timeMS)
{
    uint time = gTimeMS;
    while (gTimeMS - time < timeMS)
    {
    };
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_PauseOnTicks(uint numTicks)
{
    uint startTicks = gTimerTics;
    while (gTimerTics - startTicks < numTicks)
    {
    };
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_StartMultiMeasurement(void)
{
    TIM2->CR1 &= (uint)~TIM_CR1_CEN;
    TIM2->CNT = 0;
    TIM2->CR1 |= TIM_CR1_CEN;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_StartLogging(void)
{
    timeStartLogging = gTimerTics;
    timePrevPoint = timeStartLogging;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
uint Timer_LogPointUS(char *name)
{
    uint interval = gTimerTics - timePrevPoint;
    timePrevPoint = gTimerTics;
    LOG_WRITE("%s %.2f us", name, interval / 120.0f);
    return interval;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
uint Timer_LogPointMS(char *name)
{
    uint interval = gTimerTics - timePrevPoint;
    timePrevPoint = gTimerTics;
    LOG_WRITE("%s %.2f ms", name, interval / 120e3);
    return interval;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#undef TIME_NEXT
