#pragma once
#include "defines.h"
#include "FPGA/FPGAtypes.h"
#include "Globals.h"
#include "Panel/Controls.h"
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @defgroup FPGA
 *  @brief ������ � ��������
 *  @{
 */

extern uint16 gPost;
extern int16 gPred;
#define FPGA_IN_STATE_STOP (fpgaStateWork == StateWorkFPGA_Stop)
#define FPGA_IN_STATE_WORK (fpgaStateWork == StateWorkFPGA_Work)
#define FPGA_IN_STATE_WAIT (fpgaStateWork == StateWorkFPGA_Wait)
extern StateWorkFPGA fpgaStateWork;
extern int gAddNStop;
extern bool gFPGAisCalibrateAddRshift;

#define FPGA_IS_RUNNING FPGA_IsRunning()

/// �������������
void FPGA_Init(void);
/// ���������� ���������� ����������� �������� � �������
void FPGA_SetENumSignalsInSec(int numSigInSec);
/// ������� ������ ���������� ������ ����
void FPGA_Update(void);
/// ��������� ���� ����� ����������
void FPGA_OnPressStartStop(void);
/// ������ �������� ����� ����������
void FPGA_Start(void);

void FPGA_WriteStartToHardware(void);
/// ��������� ������� ����� ����������
void FPGA_Stop(bool pause);
/// ����� ������ ��� ��������� �����-�� ��������. ��������, ��� ��������� ����� ����� (������-�����) ���� �� �������, �� ����� ��������� �����������
void FPGA_Reset(void);
/// ���������� true, ���� ������ ��������� �� � �������� ����� ����������
bool FPGA_IsRunning(void);
/// ������� ������. ����� ��� ������ �������������, ��� ���������� ������� ����� �� �������� ���������������
void FPGA_ClearData(void);
/// ���������� ���������� ���������, �� ������� ����� �������������� ������ � ������ �������������
void FPGA_SetNumberMeasuresForGates(int number);
/// ������������� ��������� �������������
void FPGA_SwitchingTrig(void);
/// ���������� ��������� ����� ����� ��������� ����� - ����� ��������� ������ ������������� �� ��������� �����
void FPGA_TemporaryPause(void);

/// ����� � ���������� ������� ������������� �� ���������� ���������� �������
void FPGA_FindAndSetTrigLevel(void);
/// ��������� ��������� � ���������� ����� �� ���������� ��������� SSettings
void FPGA_LoadSettings(void);
/// ���������� ����� ������ �� �����
void FPGA_SetModeCouple(Channel ch, ModeCouple modeCoupe);
/// ���������� ������� �� ����������
void FPGA_SetRange(Channel ch, Range range);
/// ��������� ������� �� ����������
bool FPGA_RangeIncrease(Channel ch);
/// ��������� ������� �� ����������
bool FPGA_RangeDecrease(Channel ch);
/// ���������� ������� �� �������
void FPGA_SetTBase(TBase tBase);
/// ��������� ������� �� �������
void FPGA_TBaseDecrease(void);
/// ��������� ������� �� �������
void FPGA_TBaseIncrease(void);
/// ���������� ������������� �������� �� ����������
void FPGA_SetRShift(Channel ch, uint16 rShift);
/// ���������� ������������� �������� �� �������
void FPGA_SetTShift(int tShift);

/// ���������� ���������� �������� �� ������� ��� ������ �������������. � ������ �������� ��� �������� ������ ���� ������
void FPGA_SetDeltaTShift(int16 shift);
/// ��������/��������� ����� �������� ���������
void FPGA_SetPeackDetMode(PeakDetMode peackDetMode);
/// ��������/��������� ����������.
void FPGA_SetCalibratorMode(CalibratorMode calibratorMode);

void FPGA_EnableRecorderMode(bool enable);
/// ���������� ������������� ������� �������������
void FPGA_SetTrigLev(TrigSource ch, uint16 trigLev);
/// ���������� �������� �������������
void FPGA_SetTrigSource(TrigSource trigSource);
/// ���������� ���������� �������������
void FPGA_SetTrigPolarity(TrigPolarity polarity);
/// ���������� ����� ����� �������������
void FPGA_SetTrigInput(TrigInput trigInput);

void FPGA_SetResistance(Channel ch, Resistance resistance);

void FPGA_SetTPos(TPos tPos);

void FPGA_SetBandwidth(Channel ch);
/// ������� ������ ����� ��� ���������� ������. ���������� �� �������� ����������
void FPGA_ReadPoint(void);
/// ���������� ������������� �������� �� ������� � ��������� ����, ��������� ��� ������ �� �����
const char *FPGA_GetTShiftString(int16 tShiftRel, char buffer[20]);

typedef enum
{
    RecordFPGA,
    RecordAnalog,
    RecordDAC
} TypeRecord;

#define CS1 ((uint16 *)0)
#define CS2 ((uint16 *)1)
#define CS3 ((uint16 *)2)
#define CS4 ((uint16 *)3)

#define dacRShiftA ((uint16 *)0)
#define dacRShiftB ((uint16 *)1)
#define dacTrigLev ((uint16 *)2)


void FPGA_Write(TypeRecord type, uint16 *address, uint data, bool restart);

/** @}
 */
