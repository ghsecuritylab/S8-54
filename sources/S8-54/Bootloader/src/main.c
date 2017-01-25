/*
*************** �������� ����� ****************************
*/


#ifdef WIN32

#define __STATIC_INLINE

#endif

#include "main.h"
#include "globals.h"
#include "FlashDrive/FlashDrive.h"
#include "Hardware/Hardware.h"
#include "Settings/Settings.h"
#include "Display/Painter.h"
#include "Display/Display.h"
#include "Hardware/Timer.h"
#include "Panel/Panel.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define FILE_NAME "S8-54.bin"

typedef void(*pFunction)(void);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint jumpAddress = 0;
pFunction JumpToApplication;
State state = State_Start;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Upgrade(void);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    HAL_Init();
    
//    /*
//    __disable_irq();
//    ������ ��������� �� �������� ���������
//    JumpToApplication = (pFunction)(*(__IO uint*)(MAIN_PROGRAM_START_ADDRESS + 4));
//    __set_MSP(*(__IO uint*)MAIN_PROGRAM_START_ADDRESS);
//    __enable_irq();
//    JumpToApplication();
//    */
    
    
    Hardware_Init();

    Settings_Load();
    
    Timer_PauseOnTime(250);
    
    Display_Init();

    state = State_Start;

    Timer_Enable(kTemp, 10, Display_Update);

    FDrive_Init();

    for(uint i = 0; i < 1000000; i++)
    {
        if(FDrive_Update())
        {
            break;
        }
    }

    if (state == State_Mount)   // ��� ��������, ��� ���� ������ �������������
    {
        if (FDrive_FileExist(FILE_NAME))
        {
            state = State_RequestAction;
            volatile PanelButton button = Panel_PressedButton();
            
            while(1)
            {
                button = Panel_PressedButton();
                if(button == B_F1 || button == B_F5)
                {
                    break;
                }
            }
            
            if (button == B_F5)
            {   
                state = State_Ok;
            }
            else
            {
                Upgrade();
            }
        }
        else
        {
            state = State_NotFile;
            //Timer_PauseOnTime(2000);
        }
    }
    else if (state == State_WrongFlash) // ���� �� ������� ��������������
    {
        Timer_PauseOnTime(5000);
    }

    state = State_Ok;

    Panel_DeInit();

    Timer_Disable(kTemp);

    while (Display_IsRun())
    {

    }

    Display_Update();
    
    HAL_DeInit();

    __disable_irq();
    // ������ ��������� �� �������� ���������
    JumpToApplication = (pFunction)(*(__IO uint*)(MAIN_PROGRAM_START_ADDRESS + 4));
    __set_MSP(*(__IO uint*)MAIN_PROGRAM_START_ADDRESS);
    __enable_irq();
    JumpToApplication();
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Upgrade(void)
{

}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void ResetKey(void)
{
    HAL_FLASH_Unlock();

    FLASH_EraseInitTypeDef flashITD =
    {
        TYPEERASE_SECTORS,
        KEY_START_ADDRESS,
        1,
        VOLTAGE_RANGE_3
    };

    uint error = 0;

    HAL_FLASHEx_Erase(&flashITD, &error);
    HAL_FLASH_Lock();
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
uint ReadKey(void)
{
    return *(uint*)KEY_START_ADDRESS;
}


/*
    �� ������ 0x08000000 ��������� ���������.
    ����� ������ �� ��������� ������� ������.
        ���� ������ ����:
            ��������� ������� ����� S8-54.bin. ���� ������� �������, ������� ��������� "�� USB-����� ���������� ������ ����������� �����������. ����������?"
            ���� ������ "��":
                1. ��������� �������:
                    5 - 0x08020000
                    6 - 0x08040000
                    7 - 0x08060000
                2. �� �� ����� ������������ ���������� ����� S8-54.bin
        ���� ������ �������������� �� �������:
            ������� ��������� "�� ������� �������������� ������. ���������, ��� �� ��� �������� ������� fat32"
    ����� ����������� ������� �� ������, ���������� � 0x0802004
*/
