#pragma once
#include "defines.h"
#include "Panel/Controls.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @defgroup Menu
 *  @{
 *  @defgroup Pages
 *  @{
 *  @}
 */

#define MENU_IS_SHOWN (set.menu_IsShown)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// �������������
void Menu_Init(void);
/// ������� ������ ���������� � ������� �����.
void Menu_UpdateInput(void);
/// ������� ��������� ��������� ������� ������ (����� 0.5 ���.).
void Menu_ShortPressureButton(PanelButton button);
/// ������� ��������� �������� ������� ������ (����� 0.5 ���.).
void Menu_LongPressureButton(PanelButton button);
/// ������� ����������, ����� ������ ��������� �� �������� � ������� ���������.
void Menu_PressButton(PanelButton button);
/// ������� ����������, ����� ������ ��������� �� �������� � ������� ���������.
void Menu_ReleaseButton(PanelButton button);
/// ������� ���������� � ������ ������� ��������.
void Menu_PressReg(PanelRegulator reg);
/// ������� ��������� �������� ����� ��������� ������.
void Menu_RotateRegSetRight(void);
/// ������� ��������� �������� ����� ��������� �����.
void Menu_RotateRegSetLeft(void);
/// ���������� ����� ��������������� �������� ���� � ������������ � �����������.
void Menu_SetAutoHide(bool active);
/// ���������� ����� ������ ����, ������������ ��� ������� � ������ ������ �������.
void *Menu_ItemUnderKey(void);
/// ���������� ���� � �������� ������ ���� � ��������� ����, ������� � ������ �� �����.
char *Menu_StringNavigation(char buffer[100]);

void Menu_Show(bool show);
     
void Menu_OpenItemTime(void);
/// ������� �������� �������� ����������� ������ ��������� ����, ���� ������ �����������.
void Menu_TemporaryEnableStrNavi(void);
/// ���������� ��� ������� ����� Menu_UpdateInput().
void Menu_RunAfterUpdate(pFuncVV func);

/** @}
 */
