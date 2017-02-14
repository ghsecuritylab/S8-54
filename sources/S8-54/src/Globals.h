#pragma once


#include "FPGA/FPGAtypes.h"
#include "Panel/Controls.h"
#include "Settings/SettingsTypes.h"

#include <stm32f4xx_hal.h>

#include <stm32f4xx_hal_hcd.h>
#include <stm32f4xx_hal_pcd.h>
#include <stm32f4xx_hal_dma.h>
#include <stm32f4xx_hal_spi.h>
#include <stm32f4xx_hal_adc.h>
#include <stm32f4xx_hal_dac.h>


#include <usbd_def.h>
#include <usbh_def.h>


extern USBH_HandleTypeDef handleUSBH;
extern HCD_HandleTypeDef handleHCD;
extern SPI_HandleTypeDef handleSPI;
extern DMA_HandleTypeDef handleDMA_RAM;
extern ADC_HandleTypeDef handleADC;
extern DAC_HandleTypeDef handleDAC;


typedef struct
{
    // FPGA
    uint FPGAneedAutoFind           : 1;    // ���� 1, �� ����� ����� ������
    uint FPGAtemporaryPause         : 1;
    uint FPGAinProcessingOfRead     : 1;
    uint FPGAcanReadData            : 1;
    uint FPGAcritiacalSituation     : 1;
    uint FPGAfirstAfterWrite        : 1;    // ������������ � ������ �������������. ����� ������ ������ ��������� � ������� ����� �� ������������ 
                                            // ������ ��������� ������ � ���, ������ ��� ��� �������� � ������ ������

    uint cursorInDirs               : 1;    // ���� 1, �� ����� ��������� ���������� �� ���������
    uint needRedrawFileManager      : 2;    // ���� 1, �� ����-�������� ��������� � ������ �����������
                                            // ���� 2, �� ������������ ������ ��������
                                            // ���� 3, �� ������������ ������ �����

    uint alreadyLoadSettings        : 1;    // ��� ���������� ����� ��� ����, ����� ��������� ������ ������ ������ �������� ��-�� �������������
                                            // ��������� ������� (��� ����������� �� ����� ����������� ��������� ������ ������ �� ������ ����������
                                            // ������� �������� �������, ��� ��������� �������� ��������� ���������).
    uint showHelpHints              : 1;    // ���� 1, �� ��� ������� ������ ������ ���������� � ������ ��������� ��������� � � ����������

    uint showDebugMenu              : 1;
    
    uint tuneTime                   : 1;    // ���� 1, �� ����� �������� �������� ����� ������� �������� ��������� �������� �������

    int topMeasures                 : 9;    // ���� ������� ������ ���������. ��� �������� ����� ��� ����������� ������ ��������� �� ����� - ����� ��� ������ �� �����������

    uint disablePower               : 1;    // ���� 1, �� ����� ��������� �������
    uint temporaryShowStrNavi       : 1;    // ������� ����, ��� ����� �������� ���������� ������ ��������� ����
    uint needSetOrientation         : 1;    // ��� ��������� ���������� �������
    uint cableEthIsConnected        : 1;    // 1, ���� ��������� ������ LAN

    uint panelControlReceive        : 1;    // ���� 1, �� ������ �������� �������
    uint needToMountFlash           : 1;    // ������������� � 1 �������� ��������, ��� ������������ ������. ���� � �����������.

    uint soundIsBeep                : 1;    // ��������������� � 1, ����� ��� ��������������� �����. ����� ��� ��������� ������� - ����� ��������, ����� ���������� ����
} BitField;

extern volatile BitField gBF;               // ��������� ������� volatile, ������ ��� ����� ��� ��������� ����������� �������� �� ����� ����������. ��������,
                                            // ��� ������� � ���������� soundIsBeep (����� ��������� ������� � ����� ���������� ��������, ����� ��� ����������
                                            // ������� ��� ��������� (������� ��������� ���������� �� ����������, ���� �����))

#define RETURN_TO_MAIN_MENU     0
#define RETURN_TO_LAST_MEM      1
#define RETURN_TO_INT_MEM       2
#define RETURN_TO_DISABLE_MENU  3


typedef struct 
{
    int16   currentNumLatestSignal;                 // ������� ����� ���������� ������� � ������ ������ - ���������
    int8    currentNumIntSignal;                    // ������� ����� �������, ����������� � ����
    uint    alwaysShowMemIntSignal                      : 1;    // ���� 1, �� ���������� ������ ��������� � ������ "�����. ��" ������
    uint    runningFPGAbeforeSmallButtons   : 1;    // ����� ����������� ���������� � ���, �������� �� ���� ����� ��������� � ����� ������ � �������
    uint    exitFromIntToLast               : 1;    // ���� 1, �� �������� �� �������� ���������� ������ ����� �� ����������, � � ���� ���������
    uint    exitFromModeSetNameTo           : 2;    // ���� ������������ �� ���� ��������� ����� ��� ���������� : 0 - � �������� ����, 1 - � ���� ���������, 2 - � ���� ����� ��, 3 - � ������� ���� � ����������� ����
    uint    needForSaveToFlashDrive         : 1;    // ���� 1, �� ����� ��������� ����� ��������� �� ������.
} GMemory;

#define ALWAYS_SHOW_MEM_INT_SIGNAL (gMemory.alwaysShowMemIntSignal == 1)

extern GMemory gMemory;


typedef enum
{
    StateCalibration_None,
    StateCalibration_ADCinProgress,
    StateCalibration_RShiftAstart,
    StateCalibration_RShiftAinProgress,
    StateCalibration_RShiftBstart,
    StateCalibration_RShiftBinProgress,
    StateCalibration_ErrorCalibrationA,
    StateCalibration_ErrorCalibrationB
} StateCalibration;

typedef enum
{
    StateWorkFPGA_Stop,                 // ���� - �� ���������� ����������� ����������.
    StateWorkFPGA_Wait,                 // ��� ����������� ��������������.
    StateWorkFPGA_Work,                 // ��� ������.
    StateWorkFPGA_Pause                 // ��� ���������, ����� �������� ������������� ������, ��������, ��� ������ ������ ��� ��� ������ �������� ���������.
} StateWorkFPGA;


typedef struct
{
    bool needCalibration;				// ������������� � true �������� ��������, ��� ���������� ���������� ����������.
    StateWorkFPGA stateWorkBeforeCalibration;
    StateCalibration stateCalibration;  // ������� ��������� ����������. ������������ � �������� ����������.
} StateFPGA;

typedef struct
{
    uint timeMS;    // ����� � ������������� �� ������ �������. �.�. ��������� ����������� �� ����� ���������� ������ � ���������, �� timeMS == 0 ��������, ��� ������ ������ � ������ ���������� ������ ��� �� ������
    uint hours : 5;
    uint minutes : 6;
    uint seconds : 6;
    uint year : 7;
    uint month : 4;
    uint day : 5;
} PackedTime;

typedef struct
{
    uint16      rShift[2];
    uint16      trigLev[2];
    uint8*      addrData;               // ����� ������ �� ������� ���
    uint8       range[2];               // ������� �� ���������� ����� �������.
    int16       tShift;                 // �������� �� �������
    uint        tBase           : 5;    // ������� �� �������
    uint        enableChB       : 1;    // ������� �� ����� B
    uint        indexLength     : 3;    // ������� ���� � ������ (��� ���������� ������� ��������� ���� � ��� ���� ������, ��� �����)
    uint        modeCoupleA     : 2;    // ����� ������ �� �����
    uint        modeCoupleB     : 2;
    uint        peackDet        : 2;    // ������� �� ������� ��������
    uint        enableChA       : 1;    // ������� �� ����� A
    uint        inverseChA      : 1;
    uint        inverseChB      : 1;
    uint        multiplierA     : 1;
    uint        multiplierB     : 1;
    PackedTime  time;
} DataSettings;

int NumBytesInChannel(DataSettings *ds);    // ���������� ���������� ���� �� �����
int NumBytesInData(DataSettings *ds);       // ���������� ���������� ���� � ����� �������
int NumPointsInChannel(DataSettings *ds);   // ���������� ���������� ����� �� �����

// ���������� 0, ���� ����� ��������
uint8 *AddressChannel(DataSettings *ds, Channel ch);

extern const char *gStringForHint;          // ������ ���������, ������� ���� �������� � ������ ����������� ������ ���������.
extern void* gItemHint;                     // Item, ��������� ��� �������� ����� �������� � ������ ����������� ������ ���������.

void SetItemForHint(void *item);

extern StateFPGA gStateFPGA; 

extern uint8        *gDataA;            // ��������� �� ������ ������� ������, ������� ���� �������� �� ������
extern uint8        *gDataB;            // ��������� �� ������ ������� ������, ������� ���� �������� �� ������
extern DataSettings *gDSet;             // ��������� �� ��������� �������� ��������

extern DataSettings *gDSmemInt;         //--
extern uint8        *gDataAmemInt;      // | ����� ������ �� ����, ������� ������ ���������� �� �����
extern uint8        *gDataBmemInt;      //-/

extern DataSettings *gDSmemLast;        //--
extern uint8        *gDataAmemLast;     // | ����� ������ �� ���, ������� ������ ���������� �� �����
extern uint8        *gDataBmemLast;     //-/

#define NUM_DATAS 999
extern DataSettings gDatas[NUM_DATAS];                  // ������������ ������ � DataStorage
extern uint8 gDataAve[NumChannels][FPGA_MAX_POINTS];    // ������������ ������ � DataStorage

extern int gAddNStop;

extern void *extraMEM;      // ��� ����������� ���������. ������������ ��� ��������� ������ ����������, ������� �� ����� �� ����� ��������� ���������,
                            // �� ����� ������ ��� � ����� �������. ����� �������������� � ������� ������ malloc() ���������� ����������� ����������
                            // ������, ������� ����� ������������� ������ free()

#define MALLOC_EXTRAMEM(NameStruct, name)   extraMEM = malloc(sizeof(NameStruct));    \
                                            NameStruct *name = (NameStruct*)extraMEM
#define ACCESS_EXTRAMEM(NameStruct, name)   NameStruct *name = (NameStruct*)extraMEM
#define FREE_EXTRAMEM()                     free(extraMEM)
