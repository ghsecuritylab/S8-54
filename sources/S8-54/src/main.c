#include "Display/Colors.h"
#include "Log.h"
#include "Ethernet/Ethernet.h"
#include "FlashDrive/FlashDrive.h"
#include "FPGA/FPGA.h"
#include "Hardware/Hardware.h"
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    Log_EnableLoggerUSB(true);
    //main3();
    Hardware_Init();
    vcp.Init();
    Settings_Load(false);
    FPGA_Init();
    FPGA_OnPressStartStop();
    display.Init();
    Ethernet_Init();
    menu.Init();

    while(1)
    {
        LOG_WRITE("%d", sizeof(Color));
        Timer_StartMultiMeasurement();  // ����� ������� ��� ������ ������������ ��������� ���������� � ������� ����� �������� �����.
        Ethernet_Update(0);             // ������������ LAN
        FDrive_Update();                // ������������ ������
        FPGA_Update();                  // ��������� ���������� �����.
        panel.Update();                 // ������������ ������
        menu.UpdateInput();             // ��������� ��������� ����
        display.Update();               // ������ �����.
        panel.DisableIfNessessary();    // ���������, ���� ����������
    }
}
