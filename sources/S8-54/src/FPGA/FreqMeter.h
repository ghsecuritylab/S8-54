#pragma once


bool FreqMeter_Init(void);

void FreqMeter_Draw(int x, int y);

// �������� �������� ������� ��� ������ � ������ ����� ������
float FreqMeter_GetFreq(void);

// ������� ���������� �� FPGA
void FreqMeter_Update(uint16 flag);
