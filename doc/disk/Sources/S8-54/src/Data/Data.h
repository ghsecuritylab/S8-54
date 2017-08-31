#pragma once
#include "Data/DataSettings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup FPGA
 *  @{
 *  @defgroup Data
 *  @{
 *  @defgroup Interface ���������
 *  @{
 */

#ifndef _INCLUDE_DATA_
#define EXTERN extern
#else
#define EXTERN
#endif

#define DS          pDS             ///< ��������� �� ��������� �������� ��������� �������.

EXTERN DataSettings *pDS;           ///< ��������� �� ��������� �������� ��������� �������. ���������� � ���� ������� ����� ������ DS.

#undef EXTERN
/** @defgroup GlobalData Global Data
 *  @brief ���������, ����������� ��� ������������� � ������ ������ �������
 *  @{
 */

#define TSHIFT_DS           (TSHIFT(DS))
#define TBASE_DS            (TBASE(DS))
#define INVERSE_DS(ch)      (INVERSE(DS, ch))
#define COUPLE_DS(ch)       (COUPLE(DS, ch))
#define DIVIDER_DS(ch)      (DIVIDER(DS, ch))
#define RANGE_DS(ch)        (RANGE(DS, ch))
#define RANGE_DS_A          (RANGE(DS, A))
#define RANGE_DS_B          (RANGE(DS, B))
#define ENABLED_DS(ch)      (ENABLED(DS, ch))
#define ENABLED_DS_A        (ENABLED(DS, A))
#define ENABLED_DS_B        (ENABLED(DS, B))
#define RSHIFT_DS(ch)       (RSHIFT(DS, ch))
#define RSHIFT_DS_A         (RSHIFT(DS, A))
#define RSHIFT_DS_B         (RSHIFT(DS, B))
#define PEAKDET_DS          (PEAKDET(DS))
#define TRIGLEV_DS(ch)      (TRIGLEV(DS))
#define ENUM_BYTES_DS       (ENUM_BYTES(DS))
#define BYTES_IN_CHANNEL_DS (BytesInChannel(DS))

#define TIME_TIME_DS        (TIME_TIME(DS))
#define TIME_DAY_DS         (TIME_DAY(DS))
#define TIME_HOURS_DS       (TIME_HOURS(DS))
#define TIME_MINUTES_DS     (TIME_MINUTES(DS))
#define TIME_SECONDS_DS     (TIME_SECONDS(DS))
#define TIME_MONTH_DS       (TIME_MONTH(DS))
#define TIME_YEAR_DS        (TIME_YEAR(DS))

/** @}
 */


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// � ���� ��������� ����� ��������� �����, �������������� ��� ������ �� �����
typedef struct
{
    uint8   data[NumChannels][281 * 2];     ///< ������ ����� �������. ����� � ��� ���� ������, ��� �� ������, ��� �������� ���������
    bool    needDraw[NumChannels];          ///< ���� true, �� ����� 1 ���� ��������
    int     posBreak;                       ///< ������� � ����������� �����, �� ������� ����� �������� ����� ������� ����������� ������
} StructDataDrawing;


/// \brief ������ ������ �� ���, fromEnd c ����� (fromEnd == 0 - ��������� ��������� ������) � ��������� ������� inA(B), outA(B), DS.
/// forMemoryWindow ����� ��� ����, ����� � ������ ������ �������� ������ ������� ��� ������ � ���� ������
void Data_ReadFromRAM(int fromEnd, StructDataDrawing *dataStruct, bool forMemoryWindow);
/// ������ ������ �� EPROM. ����� ������� - ��������� NUM_ROM_SIGNAL � ��������� ������� inA(B), outA(B), DS.
void Data_ReadFromROM(StructDataDrawing *dataStruct);
/// ������ ������, �������������� ������ �����
void Data_ReadMin(StructDataDrawing *dataStruct);
/// ������ ������, �������������� ������ ������
void Data_ReadMax(StructDataDrawing *dataStruct);


/** @}  @}  @}
 */
