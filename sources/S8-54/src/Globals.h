#pragma once
#include "Data/DataSettings.h"
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


/** @defgroup Globals
 *  @brief ��������� ���������
 *  @{
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define RETURN_TO_MAIN_MENU     0
#define RETURN_TO_LAST_MEM      1
#define RETURN_TO_INT_MEM       2
#define RETURN_TO_DISABLE_MENU  3

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern USBH_HandleTypeDef handleUSBH;
extern HCD_HandleTypeDef handleHCD;
extern SPI_HandleTypeDef handleSPI;
extern DMA_HandleTypeDef handleDMA_RAM;
extern ADC_HandleTypeDef handleADC;
extern DAC_HandleTypeDef handleDAC;

#define NEED_DISABLE_POWER      (gBF.disablePower)
#define FPGA_NEED_AUTO_FIND     (gBF.FPGAneedAutoFind)

#define FPGA_IN_PROCESS_OF_READ (gBF.FPGAinProcessingOfRead)
#define FPGA_FIRST_AFTER_WRITE  (gBF.FPGAfirstAfterWrite)

#define FM_CURSOR_IN_DIRS       (gBF.cursorInDirs)
#define FM_NEED_REDRAW          (gBF.needRedrawFileManager)
#define FM_REDRAW_FULL          1
#define FM_REDRAW_FOLDERS       2
#define FM_REDRAW_FILES         3

#define NUM_DRAWING_SIGNALS     (gBF.numDrawingSignals)
/// � ���� ��� ������� �� ������ ������ ���������� � ������� ��������� ���������� � � ����������
#define HINT_MODE_ENABLE        (gBF.showHelpHints)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    uint numDrawingSignals          : 9;    ///< \brief ���������� ������������ ��������. ������������ ��� ����, ����� ����������, ����� �� ������� 
                                            ///<        ������� � ������ ����������
    uint FPGAneedAutoFind           : 1;    ///< ���� 1, �� ����� ����� ������.
    uint FPGAinProcessingOfRead     : 1;
    uint FPGAfirstAfterWrite        : 1;    ///< \brief ������������ � ������ �������������. ����� ������ ������ ��������� � ������� ����� �� 
                                            ///<        ������������ ������ ��������� ������ � ���, ������ ��� ��� �������� � ������ ������.
    uint cursorInDirs               : 1;    ///< ���� 1, �� ����� ��������� ���������� �� ���������.
    uint needRedrawFileManager      : 2;    ///< @brief ���� 1, �� ����-�������� ��������� � ������ �����������.
                                            ///< ���� 2, �� ������������ ������ ��������.
                                            ///< ���� 3, �� ������������ ������ �����.
    uint alreadyLoadSettings        : 1;    ///< @brief ��� ���������� ����� ��� ����, ����� ��������� ������ ������ ������ �������� ��-�� 
                                            ///< ������������� ��������� ������� (��� ����������� �� ����� ����������� ��������� ������ ������ �� 
                                            ///< ������ ���������� ������� �������� �������, ��� ��������� �������� ��������� ���������).
    uint showHelpHints              : 1;    ///< ���� 1, �� ��� ������� ������ ������ ���������� � ������ ��������� ��������� � � ����������.
    uint showDebugMenu              : 1;
    uint tuneTime                   : 1;    ///< ���� 1, �� ����� �������� �������� ����� ������� �������� ��������� �������� �������.
    int topMeasures                 : 9;    ///< \brief ���� ������� ������ ���������. ��� �������� ����� ��� ����������� ������ ��������� �� ����� - 
                                            ///<        ����� ��� ������ �� �����������.
    uint disablePower               : 1;    ///< ���� 1, �� ����� ��������� �������.
    uint temporaryShowStrNavi       : 1;    ///< ������� ����, ��� ����� �������� ���������� ������ ��������� ����.
    uint needSetOrientation         : 1;    ///< ��� ��������� ���������� �������.
    uint cableEthIsConnected        : 1;    ///< 1, ���� ��������� ������ LAN.
    uint panelControlReceive        : 1;    ///< ���� 1, �� ������ �������� �������.
    uint needToMountFlash           : 1;    ///< ������������� � 1 �������� ��������, ��� ������������ ������. ���� � �����������.
    uint consoleInPause             : 1;    ///< ���� 1, �� ������� ��������� � ������ �����.
    uint needStopAfterReadFrameP2P  : 1;    ///< ���� 1, �� ����� ���������� ���������� ������ ����� ���������� ����� �� �����.
    uint needFinishDraw             : 1;    ///< ���� 1, �� ����� ���������� ��������� ��������� � ������� �� ����� ��, ��� ��� ����������.
} BitField;

extern volatile BitField gBF;   ///< @brief ��������� ������� volatile, ������ ��� ����� ��� ��������� ����������� �������� �� ����� ����������. 
                                ///< ��������, ��� ������� � ���������� soundIsBeep (����� ��������� ������� � ����� ���������� ��������, ����� ��� 
                                ///< ���������� ������� ��� ��������� (������� ��������� ���������� �� ����������, ���� �����)).

#define NEED_FINISH_DRAW        (gBF.needFinishDraw)

#define NUM_RAM_SIGNAL          (gMemory.currentNumRAMSignal)
#define NUM_ROM_SIGNAL          (gMemory.currentNumROMSignal)
#define ALWAYS_SHOW_ROM_SIGNAL  (gMemory.alwaysShowROMSignal)
#define RUN_FPGA_BEFORE_SB      (gMemory.runningFPGAbeforeSmallButtons)
#define EXIT_FROM_ROM_TO_RAM    (gMemory.exitFromROMtoRAM)
#define EXIT_FROM_SETNAME_TO    (gMemory.exitFromModeSetNameTo)
#define NEED_SAVE_TO_FLASHDRIVE (gMemory.needForSaveToFlashDrive)

#define RECORDING_TO_RAM        (gMemory.recordSaveToRAM == 1)  ///< 
#define RECORDING_TO_EXT        (gMemory.recordSaveToRAM == 0)
#define SET_RECORDING_TO_RAM    (gMemory.recordSaveToRAM = 1)
#define SET_RECORDING_TO_EXT    (gMemory.recordSaveToRAM = 0)

typedef struct 
{
    int16 currentNumRAMSignal;                  ///< ������� ����� ���������� ������� � ������ ������ - ���������.
    int8 currentNumROMSignal;                   ///< ������� ����� �������, ����������� � ����.
    uint alwaysShowROMSignal            : 1;    ///< ���� 1, �� ���������� ������ ��������� � ������ "�����. ��" ������.
    uint runningFPGAbeforeSmallButtons  : 1;    ///< ����� ����������� ���������� � ���, �������� �� ���� ����� ��������� � ����� ������ � �������.
    uint exitFromROMtoRAM               : 1;    ///< ���� 1, �� �������� �� �������� ���������� ������ ����� �� ����������, � � ���� ���������.
    uint exitFromModeSetNameTo          : 2;    ///< \brief ���� ������������ �� ���� ��������� ����� ��� ���������� : 0 - � �������� ����, 1 - 
                                                ///< � ���� ���������, 2 - � ���� ����� ��, 3 - � ������� ���� � ����������� ����.
    uint needForSaveToFlashDrive        : 1;    ///< ���� 1, �� ����� ��������� ����� ��������� �� ������.
    uint recordSaveToRAM                : 1;    ///< ���� 1, �� ������ ������ ������������ ���������� � RAM, ����� - �� ������
} GMemory;



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
    StateWorkFPGA_Stop,     ///< ���� - �� ���������� ����������� ����������.
    StateWorkFPGA_Wait,     ///< ��� ����������� ��������������.
    StateWorkFPGA_Work,     ///< ��� ������.
    StateWorkFPGA_Pause     ///< ��� ���������, ����� �������� ������������� ������, ��������, ��� ������ ������ ��� ��� ������ �������� ���������.
} StateWorkFPGA;


typedef struct
{
    bool needCalibration;                       ///< ������������� � true �������� ��������, ��� ���������� ���������� ����������.
    StateWorkFPGA stateWorkBeforeCalibration;
    StateCalibration stateCalibration;          ///< ������� ��������� ����������. ������������ � �������� ����������.
} StateFPGA;

extern const char *gStringForHint;              ///< ������ ���������, ������� ���� �������� � ������ ����������� ������ ���������.
extern void *gItemHint;                         ///< Item, ��������� ��� �������� ����� �������� � ������ ����������� ������ ���������.

void SetItemForHint(void *item);

extern StateFPGA gStateFPGA; 

extern GMemory gMemory;

#define MALLOC_EXTRAMEM(NameStruct, name)   extraMEM = malloc(sizeof(NameStruct));    \
                                            NameStruct *name = (NameStruct*)extraMEM
#define ACCESS_EXTRAMEM(NameStruct, name)   NameStruct *name = (NameStruct*)extraMEM
#define FREE_EXTRAMEM()                     free(extraMEM);

/** @}
 */
