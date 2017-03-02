#pragma once


#include "defines.h"
#include "Panel/Controls.h"


#define COMMON_BEGIN_SB_EXIT  {"�����", "Exit"}, {"������ ��� ������ � ���������� ����", "Button to return to the previous menu" }, EmptyFuncBV


const void* PageForButton(PanelButton button);          // ���������� �������� ����, ������� ������ ����������� �� ������� ������ button.
bool IsMainPage(void *item);                            // ���������� true, ���� item - ����� ������� �������� ����.


void DrawMenuCursVoltage(int x, int y, bool top, bool bottom);
void CalculateConditions(int16 pos0, int16 pos1, CursCntrl cursCntrl, bool *cond0, bool *cond1);    // ������������ ������� ��������� ��� ����� ������ ���������� ������� ���������.
void DrawMenuCursTime(int x, int y, bool left, bool right);
void DrawSB_Exit(int x, int y);
