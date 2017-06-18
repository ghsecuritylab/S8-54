#pragma once
#include "defines.h"
#include "Settings/SettingsTypes.h"
#include "FPGA/fpgaTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Settings
 *  @{
 *  @defgroup DataSettings Data Settings
 *  @{
 */

typedef struct
{
    uint timeMS     : 32;   // ����� � ������������� �� ������ �������. �.�. ��������� ����������� �� ����� ���������� ������ � ���������, �� timeMS == 0 ��������, ��� ������ ������ � ������ ���������� ������ ��� �� ������
    uint hours      : 5;
    uint minutes    : 6;
    uint seconds    : 6;
    uint year       : 7;
    uint month      : 4;
    uint day        : 5;
} PackedTime;

typedef struct
{
    uint8*      addr;               // ����� ������ �� ������� ���
    uint16      rShift[2];
    uint16      trigLev[2];
    int16       tShift;             // �������� �� �������
    uint8       range[2];           // ������� �� ���������� ����� �������.
    uint        tBase       : 5;    // ������� �� �������
    uint        enableA     : 1;    // ������� �� ����� A
    uint        enableB     : 1;    // ������� �� ����� B
    uint        coupleA     : 2;    // ����� ������ �� �����
    uint        coupleB     : 2;
    uint        peackDet    : 2;    // ������� �� ������� ��������
    uint        inverseA    : 1;
    uint        inverseB    : 1;
    uint        multiplierA : 1;
    uint        multiplierB : 1;
    uint        indexLength : 3;    // ������� ���� � ������ (��� ���������� ������� ��������� ���� � ��� ���� ������, ��� �����)
    PackedTime  time;
} DataSettings;

#define ADDRESS_DATA(ds)        ((ds)->addr)

#define RSHIFT(ds, ch)          ((ds)->rShift[ch])
#define RSHIFT_A(ds)            (RSHIFT(ds, A))
#define RSHIFT_B(ds)            (RSHIFT(ds, B))

#define TRIGLEV(ds, ch)         ((ds)->trigLev[ch])
#define TRIGLEV_A(ds)           (TRIGLEV(ds, A))
#define TRIGLEV_B(ds)           (TRIGLEV(ds, B))

#define TSHIFT(ds)              ((ds)->tShift)

#define Lval_RANGE(ds, ch)      ((ds)->range[ch])
#define Lval_RANGE_A(ds)        (Lval_RANGE(ds, A))
#define Lval_RANGE_B(ds)        (Lval_RANGE(ds, B))
#define RANGE(ds, ch)           ((Range)Lval_RANGE(ds, ch))
#define RANGE_A(ds)             (RANGE(ds, A))
#define RANGE_B(ds)             (RANGE(ds, B))

#define Lval_TBASE(ds)          ((ds)->tBase)
#define TBASE(ds)               ((TBase)Lval_TBASE(ds))

#define Lval_ENABLED_A(ds)      ((ds)->enableA)
#define Lval_ENABLED_B(ds)      ((ds)->enableB)
#define Lval_ENABLED(ds, ch)    ((ch == A) ? Lval_ENABLED_A(ds) : Lval_ENABLED_B(ds))
#define ENABLED_A(ds)           ((bool)Lval_ENABLED_A(ds))
#define ENABLED_B(ds)           ((bool)Lval_ENABLED_B(ds))
#define ENABLED(ds, ch)         ((ch == A) ? ENABLED_A(ds) : ENABLED_B(ds))

#define Lval_COUPLE_A(ds)       ((ds)->coupleA)
#define Lval_COUPLE_B(ds)       ((ds)->coupleB)
#define COUPLE_A(ds)            ((ModeCouple)Lval_COUPLE_A(ds))
#define COUPLE_B(ds)            ((ModeCouple)Lval_COUPLE_B(ds))
#define COUPLE(ds, ch)          ((ch == A) ? COUPLE_A(ds) : COUPLE_B(ds))

#define Lval_PEACKDET(ds)       ((ds)->peackDet)
#define PEACKDET(ds)            ((PeackDetMode)Lval_PEACKDET(ds))

#define INVERSE_A(ds)           ((ds)->inverseA)
#define INVERSE_B(ds)           ((ds)->inverseB)
#define INVERSE(ds, ch)         ((ch == A) ? INVERSE_A(ds) : INVERSE_B(ds))

#define Lval_DIVIDER_A(ds)      ((ds)->multiplierA)
#define Lval_DIVIDER_B(ds)      ((ds)->multiplierB)

#define DIVIDER_A(ds)           ((Divider)Lval_DIVIDER_A(ds))
#define DIVIDER_B(ds)           ((Divider)Lval_DIVIDER_B(ds))
#define DIVIDER(ds, ch)         ((ch == A) ? DIVIDER_A(ds) : DIVIDER_B(ds))

#define INDEXLENGTH(ds)         ((ds)->indexLength)

#define TIME_TIME(ds)           ((ds)->time)
#define TIME_DAY(ds)            ((ds)->time.day)
#define TIME_HOURS(ds)          ((ds)->time.hours)
#define TIME_MINUTES(ds)        ((ds)->time.minutes)
#define TIME_SECONDS(ds)        ((ds)->time.seconds)
#define TIME_MONTH(ds)          ((ds)->time.month)
#define TIME_YEAR(ds)           ((ds)->time.year)
#define TIME_MS(ds)             ((ds)->time.timeMS)


int NumPointsInChannel(const DataSettings *ds);     // ���������� ���������� ����� �� �����

#define BYTES_IN_CHANNEL(ds) NumBytesInChannel(ds, false)
int NumBytesInChannel(DataSettings *ds, bool forCalculate);


// ���������� 0, ���� ����� ��������
uint8 *AddressChannel(DataSettings *ds, Channel ch);


typedef enum
{
    StateOSCI_Start,
    StateOSCI_DrawLoPart        // ����� ������� � ������ ����� ������
} StateOSCI;

extern StateOSCI gState;    // ��� �������� �������� ��������� ������� - ��������, ���� ������, ����� �� ������� �������� ������� ��� �� ������

#define NUM_DATAS 999
extern DataSettings gDatas[NUM_DATAS];                  // ������������ ������ � DataStorage
extern uint8 gDataAve[NumChannels][FPGA_MAX_POINTS];    // ������������ ������ � DataStorage

extern int gAddNStop;
extern void *extraMEM;      // ��� ����������� ���������. ������������ ��� ��������� ������ ����������, ������� �� ����� �� ����� ��������� ���������,
                            // �� ����� ������ ��� � ����� �������. ����� �������������� � ������� ������ malloc() ���������� ����������� ����������
                            // ������, ������� ����� ������������� ������ free()



#define INVERSE_CH(ch) GetInverse(ch)

bool GetInverse(Channel ch);

void DataSettings_Fill(DataSettings *ds);

bool DataSettings_IsEquals(const DataSettings *ds1, const DataSettings *ds2);

/** @}  @}
 */
