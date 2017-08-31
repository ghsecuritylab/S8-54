﻿#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Hardware
 *  @{
 *  @defgroup Timer
 *  @brief Разные таймеры
 *  @{
 */

typedef enum
{
    kPressKey,                  ///< Нужно устанавливать, когда приходит нажатие клавиши.
    kShowLevelRShiftA,          ///< Нужно устанавливать, когда изменяется положение ручки смещения канала 1.
    kShowLevelRShiftB,          ///< Нужно устанавливать, когда изменяется положение ручки смещения канала 2.
    kShowLevelTrigLev,          ///< Нужно устанавливать, когда изменяется положение ручки уровня синхронизации
    kENumSignalsInSec,           ///< Для установки количества считываний сигнала в секунду.
    kFlashDisplay,              ///< Таймер для мерцающих участков экрана чёрно-белого дисплея.
    kShowMessages,              ///< Таймер для засекания время показа информационных и предупреждающих сообщений.
    kMenuAutoHide,              ///< Таймер для отсчёта времени скрывания меню.
    kRShiftMarkersAutoHide,     ///< Таймер для отсчёта времени скрывания дополнительных боковых меток.
    kUSB,                       ///< Вспомогательный, для общих нужд.
    kStopSound,                 ///< Выключить звук
    kTemporaryPauseFPGA,        ///< Временная пауза для фиксации сигнала на экране после поворота ручек
    kStrNaviAutoHide,           ///< Прятать строку навигации меню
    kTimerStartP2P,             ///< Таймер для запуска следующего цикла поточечного чтения
    kTimerDisplay,              ///< Таймер на ручную отрисовку экрана
    NumTimers
} TypeTimer2;


void Timer_Init(void);
/// Назначает таймеру timer функцию и время срабатывания
void Timer_Set(TypeTimer2 type, pFuncVV func, uint dTms);

void Timer_SetAndStartOnce(TypeTimer2 type, pFuncVV func, uint dTms);

void Timer_SetAndEnable(TypeTimer2 type, pFuncVV func, uint dTms);

void Timer_StartOnce(TypeTimer2 type);

void Timer_Enable(TypeTimer2 type);

void Timer_Disable(TypeTimer2 type);

bool Timer_IsRun(TypeTimer2 type);

void Timer_PauseOnTime(uint timeMS);

void Timer_PauseOnTicks(uint numTicks);
/// Запускает счётчик для измерения малых отрезков времени
void Timer_StartMultiMeasurement(void);
/// Устанавливает стартовую точку логгирования. Далее вызовы Timer_LogPoint засекают временные интервалы от это точки
void Timer_StartLogging(void);

uint Timer_LogPointUS(char *name);

uint Timer_LogPointMS(char *name);


/// @brief Количество тиков, прошедших с момента последнего вызова функции Timer_StartMultiMeasurement(). Не более (1 << 32)
/// В одной секунде 120.000.000 тиков для С8-53 и 90.000.000 тиков для С8-54.
/// Максимальный отрезок времени, который можно отсчитать с её помощью - 35 сек.
#define gTimerTics (TIM2->CNT)
#define gTimerUS (TIM2->CNT / 90)
    
#define gTimeMS HAL_GetTick()

/** @}  @}
 */
