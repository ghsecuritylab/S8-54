#pragma once


#include "Panel/Controls.h"


void    Menu_Draw(void);                        // ���������� ����.
void*   ItemUnderButton(PanelButton button);    // ���������� ����� �������� ����, ���������������� ������ button.
bool    IsPressed(void* item);                  // ���������� true, ���� ������, ��������������� �������� ���� item, ��������� � ������� ���������.
bool    IsShade(void* item);                    // ���������� true, ���� ������� ���� item ������ (��������� �� �� ����� ������� ����. ��� �������, ��� ��������, ��� ������� �������������� ������� ���� ����� Choice ��� Governor.
