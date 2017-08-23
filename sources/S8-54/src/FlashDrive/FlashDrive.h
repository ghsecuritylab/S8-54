#pragma once
#include <ff.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @defgroup FlashDrive
 *  @brief ������ � �������
 *  @{
 */

#define SIZE_FLASH_TEMP_BUFFER 512
typedef struct
{
    uint8 tempBuffer[SIZE_FLASH_TEMP_BUFFER];
    int sizeData;
    FIL fileObj;
    char name[255];
} StructForWrite;

typedef struct
{
    char nameDir[_MAX_LFN + 1];
    char lfn[(_MAX_LFN + 1)];
    FILINFO fno;
    DIR dir;
} StructForReadDir;


void FDrive_Init(void);

void FDrive_Update(void);

void FDrive_Mount(void);

bool FDrive_IsConnected(void);

void FDrive_GetNumDirsAndFiles(const char *fullPath, int *numDirs, int *numFiles);

bool FDrive_GetNameDir(const char *fuulPath, int numDir, char *nameDirOut, StructForReadDir *sfrd);

bool FDrive_GetNextNameDir(char *nameDirOut, StructForReadDir *sfrd);

void FDrive_CloseCurrentDir(StructForReadDir *sfrd);

bool FDrive_GetNameFile(const char *fullPath, int numFile, char *nameFileOut, StructForReadDir *sfrd);

bool FDrive_GetNextNameFile(char *nameFileOut, StructForReadDir *sfrd);

bool FDrive_OpenNewFileForWrite(const char *fullPathToFile, StructForWrite *structForWrite); // ������� ������� ���� ��� ������. ���� ����� ���� ��� ����������, ����� ���, ������� ����� ������� ����� � ������� ���

bool FDrive_WriteToFile(uint8 *data, int sizeData, StructForWrite *structForWrite);

bool FDrive_CloseFile(StructForWrite *structForWrite);

bool FDrive_AppendStringToFile(const char *string);

#define FDRIVE_IS_CONNECTED (FDrive_IsConnected())

/** @}
 */
