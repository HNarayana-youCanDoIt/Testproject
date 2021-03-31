/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CDeviceModeHandlerResourceData.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* @brief        File to contain all the Structure Data that shall be used by
*               CDeviceModeHandlerResourceImpl Class
*/
#ifndef CDEVICEMODEHANDLERRESOURCEDATA_H
#define CDEVICEMODEHANDLERRESOURCEDATA_H

#include <string>
#include <vector>
#include "CDeviceModeHandlerResourceResourceEnums.h"

using namespace std;

struct SModeInfo
{
    SModeInfo(): m_eModeName(MODE_NAME_USB_NONE),
                 m_eModeStatus(MODE_STATUS_UNKNOWN),
                 m_eErrorStatus(ERROR_STATUS_UNKNOWN)
    {

    }

    //! Data to hold ModeName
    EModeName       m_eModeName;
    //! Data to hold ModeStatus
    EModeStatus       m_eModeStatus;
    //! Data to hold value of ErrorStatus
    EErrorStatus m_eErrorStatus;
};

/*!
 * @struct  SDeviceInformation
 * @brief   This structure shall hold basic information of the device.
 */
struct SDeviceInformation
{
    SDeviceInformation(): m_uiDeviceID(0),
                   m_strDeviceName(""),
                   m_bHasUserPrefrence(false)
    {

    }
    //! Data to hold device ID
    uint8_t       m_uiDeviceID;
    //! Data to hold device name
    string       m_strDeviceName;
    //! Data to hold value of hasUserPreference
    bool m_bHasUserPrefrence;
    //! Data to hold value of connected device type
    EDeviceType m_eDeviceType;

    vector<SModeInfo> m_vectSModeInfo;
};

#endif // CDEVICEMODEHANDLERRESOURCEDATA_H
