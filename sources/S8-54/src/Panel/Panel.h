#pragma once 
#include "defines.h"
#include "Panel/Controls.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** \defgroup Panel 
 *  \brief ������ � ������� ����������
 *   @{
 */

/// ������������� ����������� �����������
void    Panel_Init(void);
/// ������� ����� �������� ������ ���� ��� ��������� ���������� � ������ ����� ������� ����������
void    Panel_Update(void);
/// ��������/��������� �������� ���������
void    Panel_EnableLEDRegSet(bool enable);
/// ��������/��������� �������� �����1
void    Panel_EnableLEDChannelA(bool enable);
/// ��������/��������� �������� �����2
void    Panel_EnableLEDChannelB(bool enable);
/// ��������/��������� �������� �����
void    Panel_EnableLEDTrig(bool enable);
/// �������� ������ � �� ����������
void    Panel_TransmitData(uint16 data);
/// �������� ������ ����������
/** ����� ������ ���������, �� ���������� ���� ���������� ��������� ���������� pressedButton */
void    Panel_Disable(void);
/// �������� ������ ����������
void    Panel_Enable(void);
/// ���������� ���������� �������
bool    Panel_ProcessingCommandFromPIC(uint16 command);
/// ���������� ��������� ������, �������������� ��� �������� � ������, �� ������
uint16  Panel_NextData(void);
/// �������� ������� �������
PanelButton   Panel_WaitPressingButton(void);

/**  @}
 */
