#pragma once
#include "Measures.h"
#include "defines.h"
#include "Data/DataStorage.h"
#include "FPGA/FPGAtypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Utils
 *  @{
 *  @defgroup ProcessingSignal
 *  @{
 */

#define MARKER_VOLTAGE(ch, num)  (markerVoltage[ch][num] - MIN_VALUE)
#define MARKER_TIME(ch, num)    (markerTime[ch][num])

extern int markerVoltage[NumChannels][2];
extern int markerTime[NumChannels][2];


/// \brief ���������� ������ ��� ���������. ������ ������� �� DS, inA, inB.
/// �������� ������, ��������������� ������� ����������� set, �������������� ����� � ������������ � outA, outB.
void Processing_SetData(bool needSmoothing);
/// �������� ������� ������� ����������, �������������� �������� ������� ������� posCurT
float Processing_GetCursU(Channel ch, float posCurT);
/// �������� ������� ������� �������, ��������������� �������� ������� ������� ���������� posCurU
float Processing_GetCursT(Channel ch, float posCurU, int numCur);
/// ���������������� ��������� ��������� ������ ������������� �������� sinX/X
void Processing_InterpolationSinX_X(uint8 *data, int numPoints, TBase tBase);
/// ���������� ������ ��������������� ���������
char* Processing_GetStringMeasure(Measure measure, Channel ch, char *buffer, int lenBuf);
/// ��������� ��� ���������
void Processing_CalculateMeasures(void);


/** @}  @}
 */
