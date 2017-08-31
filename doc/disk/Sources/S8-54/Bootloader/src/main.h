#pragma once

#include "defines.h"

#include <stm32f4xx_hal.h>
#include <ff.h>


typedef unsigned int uint;

// Key configuration
#define KEY_START_ADDRESS   (uint)0x0
#define KEY_PAGE_NUMBER     20
#define KEY_VALUE           0xAAAA5555

// Flash configuration
#define MAIN_PROGRAM_START_ADDRESS  (uint)0x8020000
#define MAIN_PROGRAM_PAGE_NUMBER    21
#define NUM_OF_PAGES                256
#define FLASH_PAGE_SIZE             2048

#define TIME_WAIT   1000    // ����� ������ ��������


typedef enum
{
    State_Start,
    State_Mount,            // ������������ ������

    State_WrongFlash,       // ������ ����, �� ��������� ������
    State_RequestAction,    // ��� ������ - ���������� ��� ���
    State_NotFile,          // ���� ���� �������������, �� ���������� �� �� ����
    State_Upgrade,          // ������� ��������
    State_Ok                // ���������� ������ ���������
} State;

typedef enum
{
    StateDisk_Idle,
    StateDisk_Start
} StateDisk;

typedef struct
{
    bool isRun;
    float value;
    float direction;
    uint timePrev;
} Display;

typedef struct
{
    FATFS USBDISKFatFS;
    char USBDISKPath[4];
    StateDisk state;
    FIL file;
    int connection;
    int active;
} FDrive;

typedef struct
{
    FDrive drive;
    Display display;
    float percentUpdate;
    State state;
} MainStruct;


// ������ ��������� ������������ �� ���� ������� ��������� ��� ���������� ������� ���
// ������ ��� �� ������ ���� �������� � ������� malloc � ������ ��������� � ���������� � ������ �������� �� �������� ���������
extern MainStruct *ms;
