#pragma once


float       sCursors_GetCursPosU(Channel ch, int numCur);                         // �������� ������� ������� ����������.
bool        sCursors_NecessaryDrawCursors(void);                                    // ���������� true,���� ����� �������� �������.
const char* sCursors_GetCursVoltage(Channel source, int numCur, char buffer[20]);   // �������� ������ ������� ����������.
const char* sCursors_GetCursorTime(Channel source, int numCur, char buffer[20]);    // �������� ������ ������� �������.
const char* sCursors_GetCursorPercentsU(Channel source, char buffer[20]);           // �������� ������ ��������� �������� ����������.
const char* sCursors_GetCursorPercentsT(Channel source, char buffer[20]);           // �������� ������ ��������� �������� �������.
