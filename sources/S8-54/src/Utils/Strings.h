#pragma once


typedef struct
{
    uint8*   address;
    int8    numSymbols;
} Word;


int GetNumWordsInString(const uint8 *string);                       // ���������� ���������� ���� � ������. ����������� - �������. ������ ������������� ������� 0x0d, 0x0a.
bool GetWord(const uint8 *string, Word *word, const int numWord);   // ��� ������� ����� ����������� � �������� �������� �����.
bool WordEqualZeroString(Word *word, char* string);
bool EqualsStrings(char *str1, char *str2, int size);
bool EqualsZeroStrings(char *str1, char *str2);
