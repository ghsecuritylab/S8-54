// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Log.h"
#include "Ethernet/Ethernet.h"
#include "FlashDrive/FlashDrive.h"
#include "FPGA/Data.h"
#include "FPGA/FPGA.h"
#include "Hardware/Timer.h"
#include "Menu/Menu.h"
#include "Panel/Panel.h"
#include "VCP/VCP.h"


/// \todo �� ���� c ���� ������ �������� TODO("message")
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
    Log_EnableLoggerUSB(true);
    main3();
    VCP_Init();
    Settings_Load(false);
    FPGA_Init();
    FPGA_OnPressStartStop();
    Display_Init();
    Ethernet_Init();
    Menu_Init();
    
    while(1)
    {
        Timer_StartMultiMeasurement();  // ����� ������� ��� ������ ������������ ��������� ���������� � ������� ����� �������� �����.
        Ethernet_Update(0);
        FDrive_Update();
        FPGA_Update();                  // ��������� ���������� �����.
        Panel_Update();
        Menu_UpdateInput();             // ��������� ��������� ����
        Display_Update();               // ������ �����.
        Disable_IfNessessary();
    }
}
