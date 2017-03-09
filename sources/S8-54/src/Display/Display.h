﻿#pragma once
#include "DisplayTypes.h"
#include "Settings/SettingsTypes.h"
#include "Tables.h"
#include "Painter.h"

/*
    При поточечном режиме вывода текущие точки берутся из DS_GetData(0),
    а последний полный сигнал из DS_GetData(1);
*/


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void    Display_Init(void);
void    Display_Update(void);
void    Display_RotateRShift(Channel ch);
void    Display_RotateTrigLev(void);
void    Display_Redraw(void);
void    Display_EnableTrigLabel(bool enable);
void    Display_SetAddDrawFunction(pFuncVV func);
pFuncVV Display_GetAddDrawFunction(void);
void    Display_RemoveAddDrawFunction(void);
void    Display_Clear(void);
void    Display_ShiftScreen(int delta);
void    Display_ChangedRShiftMarkers(bool active);
void    Display_AddStringToIndicating(const char *string);
void    Display_OneStringUp(void);
void    Display_OneStringDown(void);
void    Display_SetPauseForConsole(bool pause);
void    Display_SetOrientation(DisplayOrientation orientation);
void    Display_DrawConsole(void);                              // Вывести сообщеия отладочной консоли
void    Display_SetDrawMode(DrawMode mode, pFuncVV func);       // Установить функцию и режим отрисовки экрана. Возможны три варианта
                                                                // 1. DrawMode_Hand - в этом случае будет вызываться функция func(), определяемая пользователем, с частотой 25 раз в секунду.
                                                                // Используется в случаях, когда не выполняется главный цикл
                                                                // 2. DrawMode_Auto и func == 0 - в этом случае будет выполняться функция Display_Update() в главном цикле
                                                                // 3. DrawMode_Auto и func != 0 - в этом случае будет выполняться функция func(), определяемая пользователем, но в теле
                                                                // главного цикла, будучи вызываемой из Display_Update() вместо Display_Update()

typedef enum
{
    LimitChan1_Volts,
    LimitChan2_Volts,
    LimitSweep_Time,
    EnabledPeakDet,
    LimitChan1_RShift,
    LimitChan2_RShift,
    LimitSweep_Level,
    LimitSweep_TShift,
    TooSmallSweepForPeakDet,
    TooFastScanForRecorder,
    FileIsSaved,
    SignalIsSaved,
    SignalIsDeleted,
    MenuDebugEnabled,
    MovingData,
    TimeNotSet,
    SignalNotFound,
    SetTPosToLeft,
    VerySmallMeasures,
    NeedRebootDevice,
    ImpossibleEnableMathFunction,
    ImpossibleEnableFFT,
    WrongFileSystem,
    WrongModePeackDet,
    DisableChannel2,
    TooLongMemory,
    NoPeakDet32k,
    NoPeakDet16k,
    Warn50Ohms,
    WarnNeedForFlashDrive,
    Warning_NumWarnings
} Warning;

void Display_ClearFromWarnings(void);
void Display_ShowWarning(Warning warning);

// Группа функций для вывода сообщения о занятом приборе
void Display_FuncOnWaitStart(char *textRu, char *textEn);
void Display_FuncOnWaitStop(void);
