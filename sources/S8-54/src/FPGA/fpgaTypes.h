﻿#pragma once
#include "Hardware/FSMC.h"
#include "Settings/SettingsTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup FPGA
 *  @{
 *  @defgroup FPGA_Types FPGA Types
 *  @{
 */

/// Минимальное значение смещения канала по напряжению, засылаемое в аналоговую часть. Соответствует смещению 10 клеток вниз от центральной линии
#define RShiftMin           100
/// Среднее значение смещения канала по напряжению, засылаемое в аналоговую часть. Соответствует расположению марера по центру экрана
#define RShiftZero          32500
/// Максимальное значение смещения канала по напряжению, засылаемое в аналоговую часть. Соответствует смещению 10 клеток вверх от центральной лиини
#define RShiftMax           64900
/// Сколько точек смещения в одной клетке
#define RSHIFT_IN_CELL (((RShiftMax) - (RShiftMin)) / 24)
/// На столько единиц нужно изменить значение смещения, чтобы маркер смещения по напряжению передвинулся на одну точку
#define STEP_RSHIFT ((RSHIFT_IN_CELL) / GRID_DELTA)
/// Минимальное значение уровня синхронизации, засылаемое в прибор
#define TrigLevMin  RShiftMin
/// Максимальное значечение уровня синхронизации, засылаемое в аналоговую часть
#define TrigLevMax  RShiftMax
/// Нулевое значение уровня синхронизации, засылаемое в прибор. Маркер синхронизации при этом находитися на одном уровне с маркером смещения по напряжению
#define TrigLevZero RShiftZero
/// Максимально значение задержки по времени относительно точки синхронизации, засылаемое в альтеру
#define TShiftMax   16000
/// Это значение входного сигнала, считанное с АЦП, соответствует центру сетки. Если значение == 0, значит, его нет. Это нужно для режимов рандомизатора и поточечного вывода p2p, а также для tShift ранее считанного сигнала
#define AVE_VALUE   128
/// Это значение входного сигнала, считанное с АЦП, соответствует нижней границе сетки (-5 клеток от центра). Если значение == 0, значит, его нет. Это нужно для режимов рандомизатора и поточечного вывода p2p, а также для tShift ранее считанного сигнала
#define MIN_VALUE   (AVE_VALUE - 125)
/// Это значение входного сигнала, считанное с АЦП, соответствует верхней границе сетки (+5 клеток от центра)
#define MAX_VALUE   (AVE_VALUE + 125)
/// Если значение == 0, значит, его нет. Это нужно для режимов рандомизатора и поточечного вывода p2p, а также для tShift ранее считанного сигнала
#define NONE_VALUE  0
/// Столько точек помещается на экране от верхней до нижней границы
#define POINTS_IN_SCREEN_VERT ((MAX_VALUE) - (MIN_VALUE))
/// Минимальный масштаб по времени, при котором возможно включение режима пикового детектора
#define MIN_TBASE_PEC_DEAT  TBase_500ns
/// С этого значения tBase должен включаться режим поточечного вывода
#define MIN_TBASE_P2P       TBase_50ms
/// Столько точек может записать прибор во внутреннюю память за одно измерение
#define FPGA_MAX_POINTS     16384

#define FPGA_MAX_POINTS_FOR_CALCULATE 900

#define WR_START        ((uint16 *)(ADDR_FPGA + (0x00 << 1)))    ///< Запуск цикла измерения. Для запуска нужно записать 1
#define WR_RAZV         ((uint16 *)(ADDR_FPGA + (0x01 << 1)))
#define WR_PRED         ((uint16 *)(ADDR_FPGA + (0x02 << 1)))
#define WR_POST         ((uint16 *)(ADDR_FPGA + (0x03 << 1)))
#define WR_TRIG         ((uint16 *)(ADDR_FPGA + (0x04 << 1)))
#define WR_UPR          ((uint16 *)(ADDR_FPGA + (0x05 << 1)))
#define UPR_BIT_PEACKDET            1   ///< пиковый детектор - 0/1 выкл/вкл
#define UPR_BIT_CALIBRATOR_AC_DC    2   ///< постоянное/переменное
#define UPR_BIT_CALIBRATOR_VOLTAGE  3   ///< 0/4В
#define UPR_BIT_RECORDER            4   ///< 0 - обычный режим, 1 - регистратор
#define WR_ADDR_NSTOP   ((uint16 *)(ADDR_FPGA + (0x06 << 1)))
#define WR_FL_RESET     ((uint16 *)(ADDR_FPGA + (0x08 << 1)))
#define WR_RESET        ((uint16 *)(ADDR_FPGA + (0x1f << 1)))

#define RD_ADC_A        ((uint16 *)(ADDR_FPGA + (0x00 << 1)))
#define RD_ADC_B        ((uint16 *)(ADDR_FPGA + (0x02 << 1)))

#define RD_ADDR_NSTOP   ((uint16 *)(ADDR_FPGA + (0x08 << 1)))
/*
    Алгоритм последовательного чтения каналов
    1. Считать RD_ADDR.
    2. Считать канал 1.
    3. Записать RD_ADDR в предзапуск в прямом виде.
    4. Записать в WR_ADDR любое число.
    5. Считать канал 2.

    Изменения для 32к 1-го канала
    в  расчёте предзапуска заменить 8192 на 16384
*/

#define WR_FREQ_METER_PARAMS    ((uint16 *)(ADDR_FPGA + (0x0a << 1)))

#define RD_FREQ_LOW             ((uint16 *)(ADDR_FPGA + (0x10 << 1)))
#define RD_FREQ_HI              ((uint16 *)(ADDR_FPGA + (0x18 << 1)))
#define RD_PERIOD_LOW           ((uint16 *)(ADDR_FPGA + (0x20 << 1)))
#define RD_PERIOD_HI            ((uint16 *)(ADDR_FPGA + (0x28 << 1)))

#define RD_FL                   ((uint16 *)(ADDR_FPGA + (0x30 << 1)))  
#define FL_DATA_READY       0   ///< 0 - данные готовы
#define FL_TRIG_READY       1   ///< 1 - наличие синхроимпульса
#define FL_PRED_READY       2   ///< 2 - окончание счета предзапуска
#define FL_POINT_READY      3   ///< 3 - признак того, что точка готова (в поточечном выводе)
#define FL_FREQ_READY       4   ///< 4 - можно считывать частоту
#define FL_PERIOD_READY     5   ///< 5 - можно считывать период
#define FL_LAST_RECOR       6   ///< 6 - признак последней записи - определяет, какой бит ставить первым
#define FL_OVERFLOW_FREQ    8   ///< 8 - признак переполнения счётчика частоты
#define FL_OVERFLOW_PERIOD  9   ///< 9 - признак переполнения счётчика периода


extern uint16 *addressesADC[NumChannels];
#define ADDRESS_READ(ch)    addressesADC[ch];


/** @}  @}
 */
