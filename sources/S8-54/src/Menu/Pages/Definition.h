#pragma once
#include "defines.h"
#include "Panel/Controls.h"
#include "Settings/SettingsTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char * const titleCommonBeginSBexit[] = { "�����", "Exit", "������ ��� ������ � ���������� ����", "Button to return to the previous menu" };

#define COMMON_BEGIN_SB_EXIT  titleCommonBeginSBexit


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ���������� �������� ����, ������� ������ ����������� �� ������� ������ button.
const void *PageForButton(PanelButton button);
/// ���������� true, ���� item - ����� ������� �������� ����.
bool IsMainPage(const void *item);
/// ������� ��������� ������ ������ �� ������ ������ ����.
void DrawSB_Exit(int x, int y);
/// ������������� ������� ��������� ������� ������ ������ �� ������ ������ ����.
void OnPressSB_Exit(void);
