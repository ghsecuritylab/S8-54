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
class Menu
{
public:
    /// �������������
    void Init(void);
    /// ������� ������ ���������� � ������� �����.
    void UpdateInput(void);
    /// ������� ��������� ��������� ������� ������ (����� 0.5 ���.).
    void ShortPressureButton(PanelButton button);
    /// ������� ��������� �������� ������� ������ (����� 0.5 ���.).
    void LongPressureButton(PanelButton button);
    /// ������� ����������, ����� ������ ��������� �� �������� � ������� ���������.
    void PressButton(PanelButton button);
    /// ������� ����������, ����� ������ ��������� �� �������� � ������� ���������.
    void ReleaseButton(PanelButton button);
    /// ������� ���������� � ������ ������� ��������.
    void PressReg(PanelRegulator reg);
    /// ������� ��������� �������� ����� ��������� ������.
    void RotateRegSetRight(void);
    /// ������� ��������� �������� ����� ��������� �����.
    void RotateRegSetLeft(void);
    /// ���������� ����� ��������������� �������� ���� � ������������ � �����������.
    void SetAutoHide(bool active);
    /// ���������� ����� ������ ����, ������������ ��� ������� � ������ ������ �������.
    void *ItemUnderKey(void);
    /// ���������� ���� � �������� ������ ���� � ��������� ����, ������� � ������ �� �����.
    char *StringNavigation(char buffer[100]);

    void Show(bool show);

    void OpenItemTime(void);
    /// ������� �������� �������� ����������� ������ ��������� ����, ���� ������ �����������.
    void TemporaryEnableStrNavi(void);
    /// ���������� ��� ������� ����� Menu_UpdateInput().
    void RunAfterUpdate(pFuncVV func);
};


extern Menu menu;


/** @}
 */
