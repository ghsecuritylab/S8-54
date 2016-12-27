#include "SettingsTime.h"
#include "Settings.h"
#include "Log.h"
#include "Utils/Math.h"
#include "FPGA/FPGA.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sTime_SetTBase(TBase tBase)
{
    TBASE = tBase;
    //FPGA_ClearData();
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void sTime_SetTShift(int16 shift)
{
    TSHIFT = shift;
    //FPGA_ClearData();
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int sTime_TPosInBytes(void)
{
    static const int m[][2][3] =
    {
        {{0, 256, 510}, {0, 512, 1022}},
        {{0, 512, 1022}, {0, 1024, 2046}},
        {{0, 1024, 2046}, {0, 2048, 4094}},
        {{0, 2048, 4094}, {0, 4096, 8190}},
        {{0, 4096, 8190}, {0, 8192, 16382}},
        {{0, 8192, 16382}, {0, 8192, 16382}},
        {{0, 16384, 32766}, {0, 16384, 32766}}
    };
    return m[set.memory.fpgaNumPoints][PEACKDET][TPOS];
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int sTime_TPosInPoints(void)
{
    static const int m[][2][3] =
    {
        {{0, 256, 510}, {0, 256, 510}},
        {{0, 512, 1022}, {0, 512, 1022}},
        {{0, 1024, 2046}, {0, 1024, 2046}},
        {{0, 2048, 4094}, {0, 2048, 4094}},
        {{0, 4096, 8190}, {0, 4096, 8190}},
        {{0, 8192, 16382}, {0, 4096, 8190}},
        {{0, 16384, 32766}, {0, 8192, 16382}}
    };
    return m[set.memory.fpgaNumPoints][PEACKDET][TPOS];
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int sTime_TShiftInPoints(void)
{
    return PEACKDET_EN ? TSHIFT : (TSHIFT * 2); 
}

#define k 0

//------------------------------------------------------------------------------------------------------------------------------------------------------
int16 sTime_TShiftMin(void)
{
    static const int16 m[FPGA_NUM_POINTS_SIZE][3] =
    {
        {-256 + k,  -128 + k,  0 + k},  // 512
        {-512 + k , -256 + k,  0 + k},  // 1024
        {-1024 + k, -512 + k,  0 + k},  // 2048
        {-2048 + k, -1024 + k, 0 + k},  // 4096
        {-4096 + k, -2048 + k, 0 + k},  // 8192
        {-8192 + k, -4096 + k, 0 + k},  // 16384
        {-16384 + k, -8192 + k, 0 + k}  // 32758
    };

    FPGA_NUM_POINTS numPoints = set.memory.fpgaNumPoints;

    if (PEACKDET_DIS)
    {
        return m[numPoints][TPOS];
    }

    return m[numPoints][TPOS] * 2; // ��� �������� ��������� ��� �������� ������ ���� � ��� ���� ������
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int16 sTime_TShiftZero(void)
{
    return -sTime_TShiftMin();
}

#undef k
