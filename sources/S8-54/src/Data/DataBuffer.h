#pragma once
#include "defines.h"
#include "Settings/SettingsTypes.h"


/** @defgroup DataBuffer
 *  @{
 */


extern uint8 *dataIN[NumChannels];      ///< ��������� ������ ������� ������.
extern uint8 *dataOUT[NumChannels];     ///< ������ � ������ ������� ������.

#define IN_A    dataIN[A]
#define IN_B    dataIN[B]
#define OUT_A   dataOUT[A]
#define OUT_B   dataOUT[B]


extern void *extraMEM;      // ��� ����������� ���������. ������������ ��� ��������� ������ ����������, ������� �� ����� �� ����� ��������� ���������,
                            // �� ����� ������ ��� � ����� �������. ����� �������������� � ������� ������ malloc() ���������� ����������� ����������
                            // ������, ������� ����� ������������� ������ free()
#define MALLOC_EXTRAMEM(NameStruct, name)   extraMEM = malloc(sizeof(NameStruct));    \
                                            NameStruct *name = (NameStruct*)extraMEM
#define ACCESS_EXTRAMEM(NameStruct, name)   NameStruct *name = (NameStruct*)extraMEM
#define FREE_EXTRAMEM()                     free(extraMEM);


/** @}
 */
