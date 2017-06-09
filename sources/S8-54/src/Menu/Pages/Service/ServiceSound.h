#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page mspSound;


// ������ - ���� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Governor mgServiceSoundVolume =
{
    Item_Governor, &mspSound, 0,
    {
        "���������", "Volume",
        "��������� ��������� �����",
        "Set the volume"
    },
    &SOUND_VOLUME, 0, 100, EmptyFuncVV
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
const Choice mcServiceSoundEnable =
{
    Item_Choice, &mspSound, 0,
    {
        "����", "Sound",
        "���������/���������� �����",
        "Inclusion/switching off of a sound"
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&SOUND_ENABLED
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
const Page mspSound =
{
    Item_Page, &pService, 0,
    {
        "����", "SOUND",
        "� ���� ���� ����� ��������� ��������� �����",
        "In this menu, you can adjust the volume"
    },
    Page_ServiceSound,
    {
        (void*)&mcServiceSoundEnable,
        (void*)&mgServiceSoundVolume
    }

};
