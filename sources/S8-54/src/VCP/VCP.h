#pragma once


void    VCP_Init(void);
void    VCP_SendDataAsynch(uint8 *data, int size);
void    VCP_SendDataSynch(const uint8 *data, int size);
void    VCP_SendStringAsynch(char *data);               // ��������� ������ ��� ������������ ����
void    VCP_SendStringSynch(char *data);                // ��������� ������ ��� ������������ ����
void    VCP_SendFormatStringAsynch(char *format, ...);  // ��� ������ ��������� � ������������ ��������� \r\n
void    VCP_SendFormatStringSynch(char *format, ...);   // ��� ������ ��������� � ������������ ��������� \r\n
void    VCP_SendByte(uint8 data);
void    VCP_Flush(void);
