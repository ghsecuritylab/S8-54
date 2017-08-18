#pragma once
#include "defines.h"
#include "Settings/SettingsTypes.h"


/** @defgroup DataBuffer
 *  @{
 */


extern uint8 *dataIN[NumChannels];      ///< ��������� ������ ������� ������.
extern uint8 *dataOUT[NumChannels];     ///< ������ � ������ ������� ������.

#define IN_A    dataIN[A]
#define IN_B    dataIN[B]
#define OUT_A   dataOUT[A]
#define OUT_B   dataOUT[B]


/** @}
 */
