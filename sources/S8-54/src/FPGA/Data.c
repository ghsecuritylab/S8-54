#include "Data.h"
#include "Globals.h"
#include "Hardware/FLASH.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static DataSettings *pDSmemInt = 0;     // | ����� ������ �� ����, ������� ������ ���������� �� �����
static uint8* dataChanMemInt[2];        //-/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Data_GetFromIntMemory(void)
{
    FLASH_GetData(gMemory.currentNumIntSignal, &pDSmemInt, &dataChanMemInt[A], &dataChanMemInt[B]);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
DataSettings* Data_DSMemInt(void)
{
    return pDSmemInt;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
DataSettings** Data_pDSMemInt(void)
{
    return &pDSmemInt;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
uint8* Data_ChMemInt(Channel ch)
{
    return dataChanMemInt[ch];
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
uint8** Data_pChMemInt(Channel ch)
{
    return &(dataChanMemInt[ch]);
}
