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

#define MARKER_HORIZONTAL(ch, num)  (markerHor[ch][num] - MIN_VALUE)
#define MARKER_VERTICAL(ch, num)    (markerVert[ch][num])

extern int markerHor[NumChannels][2];
extern int markerVert[NumChannels][2];


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
