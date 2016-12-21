#pragma once


typedef enum
{
    ExcessValues        // ���������� �������� ���������� �������� � "����������", "����������", "��� ����"
} WarningWithNumber;


NumSignalsInSec Tables_NumSignalsInSecToENUM(int numSignalsInSec);
int             Tables_ENUMtoNumSignalsInSec(NumSignalsInSec numSignalsInSec);
const char*     Tables_GetTBaseString(TBase tBase);
const char*     Tables_GetTBaseStringEN(TBase tBase);
const char*     Tables_RangeNameFromValue(Range range);
int             Tables_GetNumChannel(Channel chan);     // ���������� ����� ������ �� 1 �� 2
