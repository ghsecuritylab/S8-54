#pragma once
#include "FPGA/FPGA.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page mspCalibrator;


// ������ - ���������� ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnChange_Calibrator(bool active)
{
    FPGA_SetCalibratorMode(CALIBRATOR_MODE);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool IsActive_Calibrator_Calibrate(void)
{
    return !(SET_CALIBR_MODE_A == CalibrationMode_Disable && CALIBR_MODE_B == CalibrationMode_Disable);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Calibrator_Calibrate(void)
{
    gStateFPGA.needCalibration = true;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcCalibrator =
{
    Item_Choice, &mspCalibrator, 0,
    {
        "����������",   "Calibrator",
        "����� ������ �����������",
        "Mode of operation of the calibrator"
    },
    {
        {"�����",       "DC"},
        {"+4V",         "+4V"},
        {"0V",          "0V"}
    },
    (int8*)&CALIBRATOR_MODE, OnChange_Calibrator
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const Button mbCalibrator_Calibrate =
{
    Item_Button, &mspCalibrator, IsActive_Calibrator_Calibrate,
    {
        "�����������", "Calibrate",
        "������ ��������� ����������",
        "Running the calibration procedure"
    },
    OnPress_Calibrator_Calibrate, EmptyFuncVII
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const Page mspCalibrator =
{
    Item_Page, &pService, 0,
    {
        "����������", "CALIBRATOR",
        "����������� ������������ � ���������� ������������",
        "Control of the calibrator and calibration of an oscillograph"
    },
    Page_ServiceCalibrator,
    {
        (void*)&mcCalibrator,           // ������ - ���������� - ����������
        (void*)&mbCalibrator_Calibrate  // ������ - ���������� - �����������
    }
};
