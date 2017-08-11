#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
    ExcessValues        // ���������� �������� ���������� �������� � "����������", "����������", "��� ����"
} WarningWithNumber;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ENumSignalsInSec Tables_ENumSignalsInSecToENUM(int numSignalsInSec);

int Tables_ENUMtoENumSignalsInSec(ENumSignalsInSec numSignalsInSec);

const char *Tables_GetTBaseString(TBase tBase);

const char *Tables_GetTBaseStringEN(TBase tBase);

const char *Tables_RangeNameFromValue(Range range);
/// ���������� ����� ������ �� 1 �� 2.
int Tables_GetNumChannel(Channel ch);

extern const char * const symbolsAlphaBet[0x48];
/// ������� ������ �� ������� symbolsAlphaBet
void DrawStr(int index, int x, int y);
