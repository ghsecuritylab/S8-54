#pragma once

int     sDebug_GetSizeFontForConsole(void);            // ���������� ������ ������, ������� ����� �������� ��������� � �������.
//bool    sDebug_IsShowReg_RShiftA(void);
bool    sDebug_IsShowReg_RShift1(void);
bool    sDebug_IsShowReg_TrigLev(void);
bool    sDebug_IsShowReg_Range(Channel ch);
bool    sDebug_IsShowReg_TrigParam(void);
bool    sDebug_IsShowReg_ChanParam(Channel ch);
bool    sDebug_IsShowReg_TShift(void);
bool    sDebug_IsShowReg_TBase(void);
float   GetStretchADC(Channel ch);
void    SetStretchADC(Channel ch, float kStretch);
