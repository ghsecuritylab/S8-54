#pragma once
#include "defines.h"
#include "Settings/SettingsTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup FPGA
 *  @{
 *  @defgroup FPGA_Extensions FPGA Extensions
 *  @brief �������������� ������� ������ � ��������
 *  @{
 */

/// ������ ������� ����������
void  FPGA_ProcedureCalibration(void);
/// �������� ��������� ������������
void  FPGA_BalanceChannel(Channel ch);
/// ������ �������� ������ �������
void  FPGA_AutoFind(void);

bool  FreqMeter_Init(void);

void  FreqMeter_Draw(int x, int y);
/// �������� �������� ������� ��� ������ � ������ ����� ������
float FreqMeter_GetFreq(void);
/// ������� ���������� �� FPGA
void  FreqMeter_Update(uint16 flag);

/** @}  @}
 */
