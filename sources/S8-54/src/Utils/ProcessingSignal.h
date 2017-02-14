#pragma once


#include "Measures.h"
#include "defines.h"
#include "FPGA/FPGAtypes.h"
#include "FPGA/DataStorage.h"


void    Processing_SetSignal(uint8 *dataA, uint8 *dataB, DataSettings *ds, int firstPoint, int lastPoint);         // ���������� ������ ��� ���������.
void    Processing_GetData(uint8 **dataA, uint8 **dataB, DataSettings **ds);        // �������� ������ ����� �������������� �������.
float   Processing_GetCursU(Channel ch, float posCurT);                           // �������� ������� ������� ����������, �������������� �������� ������� ������� posCurT.
float   Processing_GetCursT(Channel ch, float posCurU, int numCur);               // �������� ������� ������� �������, ��������������� �������� ������� ������� ���������� posCurU.
void    Processing_InterpolationSinX_X(uint8 *data, int numPoints, TBase tBase);    // ���������������� ��������� ��������� ������ ������������� �������� sinX/X.
char*   Processing_GetStringMeasure(Measure measure, Channel ch, char *buffer, int lenBuf);// ���������� ������ ��������������� ���������.
void    Processing_CalculateMeasures(void);                                         // ��������� ��� ���������.
int     Processing_GetMarkerHorizontal(Channel ch, int numMarker);                // ���������� �������� ��������������� �������. ���� ERROR_VALUE_INT - ������ �������� �� �����.
int     Processing_GetMarkerVertical(Channel ch, int numMarker);                  // ���������� �������� ������������� �������. ���� ERROR_VALUE_INT - ������ �������� �� �����.
