#pragma once


#include "Decoder.h"


// ��������� ��������� ������� ������, ��������� ����������������� � �����������
// � start �������� ����� ������� ����� ������ �������, � end - ����� ���������� ����� ��������� �������, ��� ������� - 
// ������� ��������. ���� ����� ����� ���� ������� �������� ����������� ������ ������, � ����� ����� �������� � ���������
// ������ Section.
typedef struct
{
    uint16 start;
    uint16 end;
} Section;

#define NUM_SECTIONS (1024 * 8)

void DataBase_Init(Section sections[NUM_SECTIONS]);
void DataBase_GetData(uint16 address, OutStruct params[20]);
