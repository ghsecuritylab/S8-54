#pragma once

char*   FloatFract2String(float value, bool alwaysSign, char bufferOut[20]);

char*   Float2String                            //  ����������� value ���� float � ��������� ������.
                                                //  @attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ������������ ����.
                                                //  @retval ��������� �� ������ � ������.
                    (float value,               //  ��������.
                    bool alwaysSign,            //  ���� ���������� � true, ����� ������ ������ ����� ����, ���� ���������� � false, ������ ���� ����� �������������.
                    int numDigits,              //  ����� �������� ��������.
                    char bufferOut[20]
                    );                         
char*   Bin2String                              //  ����������� value � ��������� ������. ��� ���� ��������� ��� 8 ��������.
                                                //  @attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ����������� ����.
                    (uint8 value,
                    char buffer[9]);
char*   Bin2String16                            // ����������� value � ��������� ������
                                                // @attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ����������� ����.
                    (uint16 value,
                    char buffer[19]);
char*   Hex8toString                            // ����������� value � ��������� ������ � ����������������� ����.
                                                // @attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ����������� ����.
                    (uint8 value,
                    char buffer[3],
                    bool upper);
char*   Hex16toString(uint16 value, char buffer[5], bool upper);
char*   Int2String                              // ����������� value � ��������� ������.
                                                // @attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ����������� ����.
                    (int value,                 // ��������.
                    bool alwaysSign,            // ���� ���������� � true, ���� ����� ���������� ������.
                    int numMinFields,           // ����������� ����� ���������� ���������. ���� ��� ������ ����� ������� �� ���������, ������ ����������� ������.
                    char buffer[20]
                    );
bool    String2Int(char *str, int *value);
char*   Voltage2String                          // ����������� voltage ����� � ��������� ������.
                                                // @attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ������������ ����.
                        (float voltage,         // �������� ���������� � �������.
                        bool alwaysSign,        // ���� ����������� � true, ���� ��������� ������.
                        char buffer[20]
                        );


// ����������� time ������ � ��������� ������.
// time - ����� � ��������. ����� ���� �������������.
char*   Time2String(float time, bool alwaysSign, char buffer[20]);

// ����������� time ������ � ��������� ������
// time - ����� � ��������. ����� ���� �������������
// numDigits - ���������� ���� � ������
char*   Time2StringAccuracy(float time, bool alwaysSign, char buffer[20], int numDigits);

// ����������� freq ���� � ��������� ������.
char*   Freq2String(float freq, bool, char bufferOut[20]);

// ����������� freq ���� � ��������� ������. ��� ���� ����� ���������� ���� � ������ ����� numDigits
char*   Freq2StringAccuracy(float freq, char bufferOut[20], int numDigits);

char*   Phase2String(float phase, bool, char bufferOut[20]);    // ����������� ������� � ������.

char*   Float2Db(float value, int numDigits, char bufferOut[20]);   // ����������� �������� � ��������� ������.

bool    IntInRange                              // ���������� true, ���� value ������ � �������� [min; max].
                   (int value,                  // ����������� ��������.
                   int min,                     // ������ ������� ���������.
                   int max                      // ������� ������� ���������.
                   );

int     BCD2Int(uint bcd);

float   MaxFloat(float val1, float val2, float val3);                   // ���������� ������������ �������� �� ���.
int8    CircleIncreaseInt8(int8 *val, int8 min, int8 max);              // ����������� �������� �� ������ val �� 1. �����, ���� ��������� ��������� max, ������������ ��� � min.
int16   CircleIncreaseInt16(int16 *val, int16 min, int16 max);
int8    CircleDecreaseInt8(int8 *val, int8 min, int8 max);              // �������� �������� �� ������ val �� 1. �����, ���� ��������� ������ min, ������������ ��� max.
int16   CircleDecreaseInt16(int16 *val, int16 min, int16 max);
int     CircleIncreaseInt(int *val, int min, int max);
int     CircleDecreaseInt(int *val, int min, int max);
float   CircleAddFloat(float *val, float delta, float min, float max);  // ����������� �������� �� ������ val �� delta. �����, ���� ��������� ������ max, ������������ ��� min.
float   CircleSubFloat(float *val, float delta, float min, float max);  // ��������� �������� �� ������ val �� delta. �����, ���� ��������� ������ min, ������������ ��� masx.
void    AddLimitationFloat                                              // ��������� � �������� �� ������ val delta. ���� ��������� �� ����������� � �������� [min; max], ����������.
                            (float *val,                                // �� ����� ������ �������� ��������.
                            float delta,                                // � ��� ������.
                            float min,                                  // ������ ������� ���������.
                            float max                                   // ������� ������� ���������.
                            );
void    SwapInt(int *value0, int *value1);                      // ���������� ������� ���������� ������ �� ������� value0 � value1.
void    SortInt(int *value0, int *value1);                      // ��������� ���������� value0 � value1 � ������� �����������.
char    GetSymbolForGovernor(int value);                        // ���������� ����������� ����������, ��������������� ��� �������� ���������.
void    EmptyFuncVV(void);                                      // �������-��������. ������ �� ������.
void    EmptyFuncVI(int);
void    EmptyFuncVpV(void *);                                   // �������-��������. ������ �� ������.
void    EmptyFuncVII(int, int);                                 // �������-��������. ������ �� ������.
void    EmptyFuncpVII(void *, int, int);                        // �������-��������. ������ �� ������.
void    EmptyFuncVI16(int16);                                   // �������-��������. ������ �� ������.
void    EmptyFuncVB(bool);                                      // �������-��������. ������ �� ������.
char*   IntToStrCat(char *_buffer, int _value);
