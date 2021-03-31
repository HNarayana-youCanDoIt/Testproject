/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CDeviceModeHandlerResourceEnums.h
 * @ingroup       HMIComponent
 * @author        Vishal Chaudhary
 * @brief         Contain all the enums that shall be used by device mode
 *                handler resource data structures or by
 *                CDeviceModeHandlerResourceImpl class.
 */

#ifndef CDEVICEMODEHANDLERRESOURCEENUMS_H
#define CDEVICEMODEHANDLERRESOURCEENUMS_H

/*!
 * @enum    EDeviceType
 * @brief   This enum shall hold the values of device type connected to HU.
 */
enum EDeviceType{
    DEVICE_TYPE_USB_MSD,
    DEVICE_TYPE_IPHONE,
    DEVICE_TYPE_ANDROID_PHONE,
    DEVICE_TYPE_UNKNOWN,
};

/*!
 * @enum    EModeName
 * @brief   This enum is for Mode supported by device.
 */
enum EModeName{
    MODE_NAME_USB_NONE,
    MODE_NAME_USB_MSD,
    MODE_NAME_USB_IPHONE_IPOD,
    MODE_NAME_USB_IPHONE_CARPLAY,
    MODE_NAME_USB_IPHONE_CARLIFE,
    MODE_NAME_USB_IPHONE_SAL,
    MODE_NAME_USB_ANDROID_MTP,
    MODE_NAME_USB_ANDROID_ANDROIDAUTO,
    MODE_NAME_USB_ANDROID_CARLIFE,
    MODE_NAME_USB_ANDROID_SAL,
    MODE_NAME_WIFI_IPHONE_CARPLAY,
    MODE_NAME_WIFI_ANDROID_ANDROIDAUTO,
};

/*!
 * @enum    EModeStatus
 * @brief   This enum is for Mode status.
 */
enum EModeStatus{
    MODE_STATUS_UNKNOWN = -1,
    MODE_STATUS_CAPABLE,
    MODE_STATUS_ACTIVATING,
    MODE_STATUS_ACTIVE,
    MODE_STATUS_ERROR,
    MODE_STATUS_DEACTIVATING,
};

/*!
 * @enum    EErrorStatus
 * @brief   This enum is for error status.
 */
enum EErrorStatus{
    ERROR_STATUS_UNKNOWN,
};

#endif // CDEVICEMODEHANDLERRESOURCEENUMS_H
