#pragma once

#include "defines.h"
#include "Hardware/FLASH.h"


typedef struct
{
    uint start;
    int end;
} Segment;          // ��������� ��� �������� ������� ���������� ����� ������������ ��������� ������


void Segments_Set(Segment segments[MAX_NUM_SAVED_WAVES + 2]);   // ���������� ������ ���������, � ������� ����� ��������
void Segments_Cut(uint start, uint end);                        // �������� ������� � ����� ���������
int  Segments_Num(void);
