#include "Timer2.h"
#include "Timer.h"


typedef struct
{
    pFuncVV func;       // ������� �������
    uint dTms;          // ������ ������������, ��
    uint timeFirstMS;   // ����� ������� ������������
    uint timeNextMS;    // ����� ���������� ������������. ���� == 0xffffffff, �� ������ ���������
    bool repeat;        // ���� true, ����� �����������, ���� �� ����� ������� ������� Timer2_Disable()
} TimerStruct;


static TimerStruct timers[NumTimers];


#undef TIME_NEXT
#define TIME_NEXT(type) (timers[type].timeNextMS)


static void StartTIM(uint timeStop);    // ������� �����, ������� ����������� � timeStop ��
static void StopTIM(void);
static uint NearestTime(void);          // ���������� ����� ������������ ���������� �������, ���� 0, ���� �������� ���
static void TuneTIM(TypeTimer2 type);   // ��������� ������� �� ������
static void HandlerTIM(void);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Timer2_Init(void)
{
    for(uint i = 0; i < NumTimers; i++)
    {
        timers[i].timeNextMS = 0xffffffff;
    }
}


//---------------------------------------------------------------------------------------------------------------------------------------------------
void Timer2_Set(TypeTimer2 type, pFuncVV func, uint dTms)
{
    TimerStruct *timer = &timers[type];
    timer->func = func;
    timer->dTms = dTms;
}


//---------------------------------------------------------------------------------------------------------------------------------------------------
void Timer2_SetAndStartOne(TypeTimer2 type, pFuncVV func, uint dTms)
{
    Timer2_Set(type, func, dTms);
    Timer2_StartOnce(type);
}


//---------------------------------------------------------------------------------------------------------------------------------------------------
void Timer2_SetAndEnable(TypeTimer2 type, pFuncVV func, uint dTms)
{
    Timer2_Set(type, func, dTms);
    Timer2_Enable(type);
}


//---------------------------------------------------------------------------------------------------------------------------------------------------
void Timer2_StartOnce(TypeTimer2 type)
{
    timers[type].repeat = false;
    TuneTIM(type);
}


//---------------------------------------------------------------------------------------------------------------------------------------------------
void Timer2_Enable(TypeTimer2 type)
{
    timers[type].repeat = true;
    TuneTIM(type);
}


//---------------------------------------------------------------------------------------------------------------------------------------------------
static void TuneTIM(TypeTimer2 type)
{
    TimerStruct *timer = &timers[type];
    timer->timeFirstMS = gTimerMS;

    uint timeNext = timer->timeFirstMS + timer->dTms;
    timer->timeNextMS = timeNext;

    uint timeNearest = NearestTime();

    if(timeNext < timeNearest)      // ���� ������ ������ ��������� ������ ��������
    {
        StartTIM(timeNext);         // �� ������� ������ �� ���� �����
    }
}


//---------------------------------------------------------------------------------------------------------------------------------------------------
void Timer2_Disable(TypeTimer2 type)
{
    timers[type].timeNextMS = 0;
}


//---------------------------------------------------------------------------------------------------------------------------------------------------
static uint NearestTime(void)
{
    uint time = 0xffffffff;

    for(uint type = 0; type < NumTimers; type++)
    {
        if(TIME_NEXT(type) < time)
        {
            time = TIME_NEXT(type);
        }
    }
    
    return time;
}


//---------------------------------------------------------------------------------------------------------------------------------------------------
static void StartTIM(uint timeStop)
{
    StopTIM();

    if(timeStop == 0xffffffff)
    {
        return;
    }
}


//---------------------------------------------------------------------------------------------------------------------------------------------------
static void StopTIM(void)
{

}


//---------------------------------------------------------------------------------------------------------------------------------------------------
static void HandlerTIM(void)
{
    uint time = gTimerMS;

    for(uint type = 0; type < NumTimers; type++)
    {
        if(TIME_NEXT(type) <= time)            // ���� ������ ����� ������������
        {
            TimerStruct *timer = &timers[type];
            if(timer->repeat)
            {
                timer->timeNextMS += timer->dTms;
            }
            else
            {
                timer->timeNextMS = 0;                
            }
        }
    }

    StartTIM(NearestTime());
}


#undef TIME_NEXT
