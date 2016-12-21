#pragma once 


#include "defines.h"
#include "Controls.h"


void    Panel_Init(void);
void    Panel_DeInit(void);
void    Panel_Update(void);
void    Panel_TransmitData(uint16 data);            // �������� ������� � �� ������ ����������.
void    Panel_Disable(void);                        // � ���������� ������ ������ ���� ��������� ��������� ���������� pressedButton, �� �������� ������ ������� ��������.
void    Panel_Enable(void);
PanelButton   Panel_WaitPressingButton(void);       // ������� ������� �������.
bool    Panel_ProcessingCommandFromPIC(uint16 command);
uint16  Panel_NextData(void);
PanelButton  Panel_PressedButton(void);
