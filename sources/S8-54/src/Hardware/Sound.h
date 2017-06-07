#pragma once
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Hardware
 *  @{
 *  @defgroup Sound
 *  @brief ������ �� �������� ���������
 *  @{
 */


typedef enum
{
    TypeWave_Sine,
    TypeWave_Meandr,
    TypeWave_Triangle
} TypeWave;


void Sound_Init(void);
/// ���� ������� �� ������.
void Sound_ButtonPress(void);
/// ������� ������� ���� ����������� ������ ������ ���� ����� ���� ������������ ���� ������� ������.
void Sound_ButtonRelease(void);

void Sound_GovernorChangedValue(void);

void Sound_RegulatorShiftRotate(void);

void Sound_RegulatorSwitchRotate(void);

void Sound_WarnBeepBad(void);

void Sound_WarnBeepGood(void);
/// ��� ������� ���� �������� ����� �������/��������� ����. ���� ����������� � ����.
void Sound_WaitCompletion(void);

/** @}  @}
 */
