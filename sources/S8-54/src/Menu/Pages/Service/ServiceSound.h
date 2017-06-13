#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page ppSound;


// ������ - ���� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Governor mgServiceSoundVolume =
{
    Item_Governor, &ppSound, 0,
    {
        "���������", "Volume",
        "��������� ��������� �����",
        "Set the volume"
    },
    &SOUND_VOLUME, 0, 100
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
const Choice mcServiceSoundEnable =
{
    Item_Choice, &ppSound, 0,
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
const Page ppSound =
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
