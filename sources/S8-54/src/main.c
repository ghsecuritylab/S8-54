// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "defines.h"
#include "FPGA/Data.h"
#include "FPGA/DataStorage.h"
#include "Settings/Settings.h"
#include "Hardware/FSMC.h"
#include "Hardware/Timer.h"
#include "Hardware/FLASH.h"
#include "Log.h"
#include "Panel/Panel.h"
#include "VCP/VCP.h"
#include "FPGA/FPGA.h"
#include "Ethernet/Ethernet.h"
#include "Menu/Menu.h"
#include "Utils/ProcessingSignal.h"
#include "Menu/Pages/PageCursors.h"
#include "FlashDrive/FlashDrive.h"


// �� ���� c ���� ������ �������� TODO("message")
#define STRINGIZE_2( _ ) #_
#define STRINGIZE( _ ) STRINGIZE_2( _ )
#define TODO(msg) __pragma(message(__FILE__ "(" STRINGIZE(__LINE__) ") : TODO: " msg))


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern void main3(void);

#define TICS ((gTimerTics - time) / 120.0f)

static void ProcessingSignal(void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void Disable_IfNessessary(void)
{
    if (gBF.disablePower == 1)
    {
        Settings_Save();
        Log_DisconnectLoggerUSB();
        Panel_TransmitData(0x04);
        volatile bool run = true;
        while (run)
        {
        };
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void)
{
    /*
    ��������� ������������ �� ������ 0x08020000
    ������� �������� ���������� ������ ���� �������� �� ������ 0x08020000. ��� �������� ���� ������ � system_stm32xx.c ������ #define VECT_TAB_OFFSET 0x08020000
    ����� ������� ��������� �� ������ 0x08020004 (��� ����� ����������� ���������� ������)
    �� ��������� �� ���� �� ����������, �������������� �� ������ 0x08000000
    */

    Log_EnableLoggerUSB(true);
    main3();
    VCP_Init();
    Settings_Load(false);
    FPGA_Init();
    FPGA_OnPressStartStop();
    Display_Init();
    Ethernet_Init();
    Menu_Init();

    volatile bool run = true;
    while(run)
    {
        Timer_StartMultiMeasurement();      // ����� ������� ��� ������ ������������ ��������� ���������� � ������� ����� �������� �����.
        Ethernet_Update(0);
        FDrive_Update();
        FPGA_Update();                      // ��������� ���������� �����.
        ProcessingSignal();
        Panel_Update();
        Menu_UpdateInput();                 // ��������� ��������� ����
        Display_Update();                   // ������ �����.
        Disable_IfNessessary();
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void ProcessingSignal(void)
{
    uint8 **dataA = &gDataA;
    uint8 **dataB = &gDataB;
    DataSettings **ds = &gDSet;

    if (DS_NumElementsInStorage() == 0)
    {
        *dataA = 0;
        *dataB = 0;
        *ds = 0;
        return;
    }

    int first = 0;
    int last = 0;
    sDisplay_PointsOnDisplay(&first, &last);
    if (WORK_DIRECT)
    {
        if (IN_P2P_MODE         &&                  // ��������� � ������ ����������� ������
            START_MODE_WAIT     &&                  // � ������ ������ �������������
            DS_NumElementsWithCurrentSettings() > 1 // � � ��������� ��� ���� ��������� ������� � ������ �����������
            )
        {
            DS_GetDataFromEnd_RAM(1, &gDSet, (uint16**)&gDataA, (uint16**)&gDataB);
        }
        else
        {
            DS_GetDataFromEnd_RAM(0, &gDSet, (uint16**)&gDataA, (uint16**)&gDataB);
        }

        if (sDisplay_NumAverage() != 1 || IN_RANDOM_MODE)
        {
            ModeFSMC mode = FSMC_GetMode();
            FSMC_SetMode(ModeFSMC_RAM);
            gDataA = DS_GetAverageData(A);
            gDataB = DS_GetAverageData(B);
            FSMC_SetMode(mode);
        }
    }
    else if (WORK_LAST)
    {
        dataA = &gDataAmemLast;
        dataB = &gDataBmemLast;
        ds = &gDSmemLast;
        DS_GetDataFromEnd_RAM(gMemory.currentNumLatestSignal, &gDSmemLast, (uint16**)&gDataAmemLast, (uint16**)&gDataBmemLast);
    }
    else if (WORK_INT)
    {
        dataA = Data_pChMemInt(A);
        dataB = Data_pChMemInt(B);
        ds = Data_pDSMemInt();
        Data_GetFromIntMemory();
    }

    if (WORK_INT)
    { 
        if (SHOW_IN_INT_BOTH || SHOW_IN_INT_DIRECT)
        {
            Processing_SetSignal(gDataA, gDataB, gDSet, first, last);
        }
    }
    else
    {
        Processing_SetSignal(*dataA, *dataB, *ds, first, last);
    }

    CursorsUpdate();    // � ������, ���� ��������� � ������ ��������� ���������, ��������� �� ���������, ���� �����.
}
