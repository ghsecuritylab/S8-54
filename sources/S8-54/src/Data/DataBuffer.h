#pragma once
#include "defines.h"
#include "Settings/SettingsTypes.h"


/** @defgroup DataBuffer
 *  @{
 */


extern uint8 *dataIN[NumChannels];      ///< ��������� ������ ������� ������.
extern uint8 *dataOUT[NumChannels];     ///< ������ � ������ ������� ������.

#define IN(ch)  (dataIN[ch])
#define IN_A    IN(A)
#define IN_B    IN(B)
#define OUT(ch) (dataOUT[ch])
#define OUT_A   OUT(A)
#define OUT_B   OUT(B)


extern void *extraMEM;      // ��� ����������� ���������. ������������ ��� ��������� ������ ����������, ������� �� ����� �� ����� ��������� ���������,
                            // �� ����� ������ ��� � ����� �������. ����� �������������� � ������� ������ malloc() ���������� ����������� ����������
                            // ������, ������� ����� ������������� ������ free()
#define MALLOC_EXTRAMEM(NameStruct, name)   extraMEM = malloc(sizeof(NameStruct));    \
                                            NameStruct *name = (NameStruct*)extraMEM
#define ACCESS_EXTRAMEM(NameStruct, name)   NameStruct *name = (NameStruct*)extraMEM
#define FREE_EXTRAMEM()                     free(extraMEM);


/** @}
 */
