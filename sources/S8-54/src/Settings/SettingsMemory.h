﻿#pragma once
#include "Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Settings
 *  @{
 *  @defgroup SettingsMemory Settings Memory
 *  @{
 */

#define FILE_NAME_MASK          (set.mem_FileNameMask)
#define FILE_NAME               (set.mem_FileName)
#define INDEX_SYMBOL            (set.mem_IndexCurSymbolNameMask)
#define FLASH_AUTO_CONNECT      (set.mem_FlashAutoConnect)

#define FILE_NAMING_MODE        (set.mem_FileNamingMode)
#define FILE_NAMING_MODE_MASK   (FILE_NAMING_MODE == FileNamingMode_Mask)
#define FILE_NAMING_MODE_MANUAL (FILE_NAMING_MODE == FileNamingMode_Manually)

#define MODE_WORK               (set.mem_ModeWork)
#define MODE_WORK_DIR           (MODE_WORK == ModeWork_Dir)
#define MODE_WORK_RAM           (MODE_WORK == ModeWork_RAM)
#define MODE_WORK_ROM           (MODE_WORK == ModeWork_ROM)


#define SHOW_IN_INT             (set.mem_ModeShowIntMem)
#define SHOW_IN_INT_SAVED       (SHOW_IN_INT == ModeShowIntMem_Saved)
#define SHOW_IN_INT_DIRECT      (SHOW_IN_INT == ModeShowIntMem_Direct)
#define SHOW_IN_INT_BOTH        (SHOW_IN_INT == ModeShowIntMem_Both)

#define FPGA_NUM_POINTS         (set.mem_ENumPointsFPGA)
#define FPGA_NUM_POINTS_512     (FPGA_NUM_POINTS == FNP_512)
#define FPGA_NUM_POINTS_8k      (FPGA_NUM_POINTS == FNP_8k)
#define FPGA_NUM_POINTS_16k     (FPGA_NUM_POINTS == FNP_16k)
#define FPGA_NUM_POINTS_32k     (FPGA_NUM_POINTS == FNP_32k)

#define MODE_BTN_MEMORY         (set.mem_ModeBtnMemory)
#define MODE_BTN_MEMORY_MENU    (MODE_BTN_MEMORY == ModeBtnMemory_Menu)
#define MODE_BTN_MEMORY_SAVE    (MODE_BTN_MEMORY == ModeBtnMemory_Save)

#define MODE_SAVE               (set.mem_ModeSaveSignal)
#define MODE_SAVE_BMP           (MODE_SAVE == ModeSaveSignal_BMP)
#define MODE_SAVE_TXT           (MODE_SAVE == ModeSaveSignal_TXT)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int sMemory_NumPointsInChannel(void);

ENumPoinstFPGA NumPoints_2_FPGA_NUM_POINTS(int numPoints);

int FPGA_NUM_POINTS_2_NumPoints(ENumPoinstFPGA numPoints);

/** @}  @}
 */
