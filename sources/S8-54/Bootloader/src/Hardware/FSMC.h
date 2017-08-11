 #pragma once


#include "defines.h"


#define ADDR_BANK           0x60000000

#define ADDR_CDISPLAY               ((uint8 *)(ADDR_BANK + 0x080000))    // ����� 8-������ ��������������� �������������� �����
#define ADDR_FPGA                   ((uint8 *)(ADDR_BANK + 0x300000))    // ����� 16-������ ���������������� ��������������� �����
#define ADDR_RAM                    ((uint8 *)(ADDR_BANK + 0x200000))    // ����� 16-������ ���������������� ��������������� �����


typedef enum
{
    ModeFSMC_None,
    ModeFSMC_Display,
    ModeFSMC_FPGA,
    ModeFSMC_RAM
} ModeFSMC;


void FSMC_Init(void);

void FSMC_SetMode(ModeFSMC mode);

// ������� ������������ ��� ��������� � ���� �� ���������� - ���� ������/������ ���������� �� ����� �������������, ��������� ������
bool FSMC_InSetStateMode(void);

// ������� ������������ � ���� � ����������. ������������� �������, ������� ����� ���� ��������� ����� ��������� ������ �� ����
void FSMC_SetFuncitonAfterSetMode(pFuncBV func);
void FSMC_RemoveFunctionAfterSetMode(void);

// DEPTRECATED ��������������� �����, ������� ��� ���������� ����� ������� FSMC_SetMode()
void FSMC_RestoreMode(void);
    
ModeFSMC FSMC_GetMode(void);

#define FSMC_READ(address) (*(address))
#define FSMC_WRITE(address, data) (*(address) = data)

#define FSMC_SET_MODE(mode)                     \
    ModeFSMC modePrev = FSMC_GetMode();         \
    bool needRestoreMode = mode != modePrev;    \
    if(needRestoreMode)                         \
    {                                           \
        FSMC_SetMode(mode);                     \
    }

#define FSMC_RESTORE_MODE()                     \
    if(needRestoreMode)                         \
    {                                           \
        FSMC_SetMode(modePrev);                 \
    }
