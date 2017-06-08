// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "defines.h"
#include "FPGA/Data.h"
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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern void main3(void);

#define TICS ((gTimerTics - time) / 120.0f)

//static void ProcessingSignal(void);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


//----------------------------------------------------------------------------------------------------------------------------------------------------
int main(void)
{
    /*
    ��������� ������������ �� ������ 0x08020000
    ������� �������� ���������� ������ ���� �������� �� ������ 0x08020000. ��� �������� ���� ������ � system_stm32xx.c ������ #define 
    VECT_TAB_OFFSET 0x08020000.
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
        LOG_WRITE("%d %d", sizeof(DataSettings), sizeof(PackedTime));
        Ethernet_Update(0);
        FDrive_Update();
        FPGA_Update();                      // ��������� ���������� �����.
        Data_Load();
        //ProcessingSignal();
        Panel_Update();
        Menu_UpdateInput();                 // ��������� ��������� ����
        Display_Update();                   // ������ �����.
        Disable_IfNessessary();
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
void ProcessingSignal(void)
{
    uint8 **dataA = &DATA(A);
    uint8 **dataB = &DATA(B);
    DataSettings **ds = &DS;

    if (DS_NumElementsInStorage() == 0)
    {
        *dataA = 0;
        *dataB = 0;
        *ds = 0;
        return;
    }

    if (WORK_DIRECT)
    {
        if (IN_P2P_MODE         &&                  // ��������� � ������ ����������� ������
            START_MODE_WAIT     &&                  // � ������ ������ �������������
            DS_NumElementsWithCurrentSettings() > 1 // � � ��������� ��� ���� ��������� ������� � ������ �����������
            )
        {
            DS_GetDataFromEnd_RAM(1, &DS, (uint16**)&DATA(A), (uint16**)&DATA(B));
        }
        else
        {
            DS_GetDataFromEnd_RAM(0, &DS, (uint16**)&DATA(A), (uint16**)&DATA(B));
        }

        if (sDisplay_NumAverage() != 1 || IN_RANDOM_MODE)
        {
            ModeFSMC mode = FSMC_GetMode();
            FSMC_SetMode(ModeFSMC_RAM);
            Data_GetAverageFromDataStorage();
            FSMC_SetMode(mode);
        }
    }
    else if (WORK_LAST)
    {
        dataA = &DATA_LAST(A);
        dataB = &DATA_LAST(B);
        ds = &DS_LAST;
        DS_GetDataFromEnd_RAM(gMemory.currentNumLatestSignal, &DS_LAST, (uint16**)&DATA_LAST(A), (uint16**)&DATA_LAST(B));
    }
    else if (WORK_EEPROM)
    {
        dataA = &DATA_INT(A);
        dataB = &DATA_INT(B);
        ds = &DS_INT;
        Data_GetFromIntMemory();
    }

    int first = 0;
    int last = 0;
    sDisplay_PointsOnDisplay(&first, &last);

    if (WORK_EEPROM)
    { 
        if (SHOW_IN_INT_BOTH || SHOW_IN_INT_DIRECT)
        {
            Processing_SetSignal(DATA(A), DATA(B), DS, first, last);
        }
    }
    else
    {
        Processing_SetSignal(*dataA, *dataB, *ds, first, last);
    }

    CursorsUpdate();    // � ������, ���� ��������� � ������ ��������� ���������, ��������� �� ���������, ���� �����.
}
*/
