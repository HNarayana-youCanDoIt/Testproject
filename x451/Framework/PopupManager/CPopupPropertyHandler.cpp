/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CPopupPropertyHandler.cpp
* @ingroup      HMIComponent
* @author       Rahul Madan
* CPopupPropertyHandler Class implementation which shall contain all the basic info
*                       about all the popups with their properties
*                       and create a map with Popup Ids as keys and Properties as value
*/

#include "CPopupPropertyHandler.h"

//ToDo : No need of this context, shall be removed in next PR.
const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecInvalidContext =
                                                                                            {CPopupEnum::EN_HMI_EARLY_WAKEUP_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_SAL_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_STARTUP_ANIMATION_CONTEXT};

const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecCommonContext =
                                                                                            {CPopupEnum::EN_HMI_HOME_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_MEDIA_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_MEDIA_OFF_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_ENGG_MENU_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_TUNER_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_PHONE_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_SETUP_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_SOFTWARE_UPDATE_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_VR_PICKLIST_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_VR_HELP_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_DRIVE_NEXT_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_PHONE_SETUP_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_W3W_CONTEXT,
                                                                                             CPopupEnum::HMI_SOUNDDEMO_CONTEXT};

const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecCommonContextWithCall =
                                                                                            {CPopupEnum::EN_HMI_HOME_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_MEDIA_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_MEDIA_OFF_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_ENGG_MENU_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_TUNER_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_PHONE_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_SETUP_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_SOFTWARE_UPDATE_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_VR_PICKLIST_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_VR_HELP_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_PHONE_CALL_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_DRIVE_NEXT_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_PHONE_SETUP_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_W3W_CONTEXT,
                                                                                             CPopupEnum::HMI_SOUNDDEMO_CONTEXT};

const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecVRContext =
                                                                                            {CPopupEnum::EN_HMI_HOME_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_MEDIA_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_VR_HELP_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_VR_PICKLIST_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_ENGG_MENU_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_TUNER_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_PHONE_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_SETUP_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_SOFTWARE_UPDATE_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_DRIVE_NEXT_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_PHONE_SETUP_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_W3W_CONTEXT,
                                                                                             CPopupEnum::HMI_SOUNDDEMO_CONTEXT};

const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecDisplayOffPopupContext =
                                                                                            {CPopupEnum::EN_HMI_HOME_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_MEDIA_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_MEDIA_OFF_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_ENGG_MENU_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_TUNER_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_PHONE_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_SETUP_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_VR_PICKLIST_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_VR_HELP_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_SOFTWARE_UPDATE_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_DRIVE_NEXT_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_PHONE_SETUP_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_W3W_CONTEXT,
                                                                                             CPopupEnum::HMI_SOUNDDEMO_CONTEXT};


const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecIncomingCallPopupContext =
                                                                                            {CPopupEnum::EN_HMI_HOME_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_MEDIA_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_MEDIA_OFF_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_ENGG_MENU_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_TUNER_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_PHONE_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_SETUP_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_PHONE_CALL_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_VR_HELP_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_VR_PICKLIST_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_SOFTWARE_UPDATE_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_DRIVE_NEXT_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_PHONE_SETUP_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_W3W_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_DOODLE_SETUP_CONTEXT,
                                                                                             CPopupEnum::HMI_SOUNDDEMO_CONTEXT};

const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecVoiceAlertPopupContext =
                                                                                            {CPopupEnum::EN_HMI_HOME_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_MEDIA_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_MEDIA_OFF_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_ENGG_MENU_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_TUNER_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_PHONE_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_SETUP_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_PHONE_CALL_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_VR_HELP_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_VR_PICKLIST_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_ANDROID_AUTO_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_APPLE_CARPLAY_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_DRIVE_NEXT_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_PHONE_SETUP_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_W3W_CONTEXT,
                                                                                             CPopupEnum::HMI_SOUNDDEMO_CONTEXT};

const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecTunerContext =
                                                                                            {CPopupEnum::EN_HMI_TUNER_CONTEXT};

const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecHomeContext =
                                                                                            {CPopupEnum::EN_HMI_HOME_CONTEXT};

const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecMediaContext =
                                                                                            {CPopupEnum::EN_HMI_MEDIA_CONTEXT};

const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecMediaOffContext =
                                                                                            {CPopupEnum::EN_HMI_MEDIA_OFF_CONTEXT};

const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecPhoneContext =
                                                                                            {CPopupEnum::EN_HMI_PHONE_CONTEXT};

const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecPhoneCallContext =
                                                                                            {CPopupEnum::EN_HMI_PHONE_CALL_CONTEXT};

const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecSetupContext =
                                                                                            {CPopupEnum::EN_HMI_SETUP_CONTEXT,
                                                                                             CPopupEnum::EN_HMI_PHONE_SETUP_CONTEXT};

const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecEnggMenuContext =
                                                                                            {CPopupEnum::EN_HMI_ENGG_MENU_CONTEXT};

const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecSoftwareUpdateContext =
                                                                                            {CPopupEnum::EN_HMI_SOFTWARE_UPDATE_CONTEXT};

const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecPDCRVCContext =
                                                                                            {CPopupEnum::EN_HMI_PDC_RVC_CONTEXT};

const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecSetupAndHomeContext =
                                                                                            {CPopupEnum::EN_HMI_HOME_CONTEXT, CPopupEnum::EN_HMI_SETUP_CONTEXT};

const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecDriveNextContext =
                                                                                            {CPopupEnum::EN_HMI_DRIVE_NEXT_CONTEXT};

const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecDriveNextSetupContext =
                                                                                            {CPopupEnum::EN_HMI_DRIVE_NEXT_CONTEXT, CPopupEnum::EN_HMI_SETUP_CONTEXT};

const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecPhoneSetupContext =
                                                                                            {CPopupEnum::EN_HMI_PHONE_SETUP_CONTEXT};

const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecW3WContext =
                                                                                            {CPopupEnum::EN_HMI_W3W_CONTEXT};

const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecDoodleStickerContext =
                                                                                            {CPopupEnum::EN_HMI_HOME_CONTEXT, CPopupEnum::EN_HMI_MEDIA_OFF_CONTEXT};

const QVector<CPopupEnum::EPopupApplicableContext> CPopupPropertyHandler::CPopupProperties::m_vecDoodleSetupContext =
                                                                                            {CPopupEnum::EN_HMI_DOODLE_SETUP_CONTEXT};


/*******************************************************************
                Methods related to class CPopupProperties
*******************************************************************/
CPopupPropertyHandler::CPopupProperties::CPopupProperties()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s",__FUNCTION__);
    m_eId = CPopupEnum::EN_POPUPID_UNKNOWN;
    m_sQmlFilePath = "";
    m_ePriority = CPopupEnum::EN_POPUP_PRIORITY_NONE;
    m_bCloseOnHK = false;
    m_bCloseOnTouch = false;
    m_bCloseOnSupersede = false;
    m_bEnqueue = false;
    m_ePopupZone = CPopupEnum::EN_POPUP_ZONE_NONE;
    m_iMinTimeout = 0;
    m_iMaxTimeout = 0;
    m_vecApplicableContext = {CPopupEnum::EN_HMI_INVALID_CONTEXT};
}

//[RM] : Please initialize variables in initializer list.
CPopupPropertyHandler::CPopupProperties::CPopupProperties(CPopupEnum::EPopupID eId, const QString& sQmlFilePath, CPopupEnum::EPopupPriority ePriority, CPopupEnum::EPopupZone ePopupZone, bool bCloseOnSupersede, bool bCloseOnTouch, bool bCloseOnHK, int iMinTimeout, int iMaxTimeout, const QVector<CPopupEnum::EPopupApplicableContext> &vecApplicableContext, bool bEnqueue , bool bResetPopupTimer)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s", __FUNCTION__);
    m_eId = eId;
    m_sQmlFilePath = sQmlFilePath;
    m_ePriority = ePriority;
    m_bCloseOnHK = bCloseOnHK;
    m_bCloseOnTouch = bCloseOnTouch;
    m_bCloseOnSupersede = bCloseOnSupersede;
    m_bEnqueue = bEnqueue;
    m_ePopupZone = ePopupZone;
    m_iMinTimeout = iMinTimeout;
    m_iMaxTimeout = iMaxTimeout;
    m_vecApplicableContext = vecApplicableContext;
    m_bResetPopupTimer = bResetPopupTimer;
}
void CPopupPropertyHandler::CPopupProperties::reset()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s", __FUNCTION__);
    m_eId = CPopupEnum::EN_POPUPID_UNKNOWN;
    m_sQmlFilePath = "";
    m_ePriority = CPopupEnum::EN_POPUP_PRIORITY_NONE;
    m_bCloseOnHK = false;
    m_bCloseOnTouch = false;
    m_bCloseOnSupersede = false;
    m_bEnqueue = false;
    m_ePopupZone = CPopupEnum::EN_POPUP_ZONE_NONE;
    m_iMinTimeout = 0;
    m_iMaxTimeout = 0;
    m_vecApplicableContext = {CPopupEnum::EN_HMI_INVALID_CONTEXT};
    m_bResetPopupTimer = false;
}

void CPopupPropertyHandler::CPopupProperties::setProperties(CPopupEnum::EPopupID eId, const QString& sQmlFilePath, CPopupEnum::EPopupPriority ePriority, CPopupEnum::EPopupZone ePopupZone, bool bCloseOnSupersede, bool bCloseOnTouch, bool bCloseOnHK, int iMinTimeout, int iMaxTimeout, const QVector<CPopupEnum::EPopupApplicableContext> &vecApplicableContext, bool bEnqueue, bool bResetPopupTimer)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, "%s", __FUNCTION__);
    m_eId = eId;
    m_sQmlFilePath = sQmlFilePath;
    m_ePriority = ePriority;
    m_ePopupZone = ePopupZone;
    m_bCloseOnSupersede = bCloseOnSupersede;
    m_bCloseOnTouch = bCloseOnTouch;
    m_bCloseOnHK = bCloseOnHK;
    m_iMinTimeout = iMinTimeout;
    m_iMaxTimeout = iMaxTimeout;
    m_bEnqueue = bEnqueue;
    m_vecApplicableContext = vecApplicableContext;
    m_bResetPopupTimer = bResetPopupTimer;
}

/*******************************************************************
                Methods related to class CPopupPropertyHandler
*******************************************************************/
CPopupPropertyHandler::CPopupPropertyHandler()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s", __FUNCTION__);
    createPopupPropertyMap();
}

CPopupPropertyHandler::~CPopupPropertyHandler()
{

}

void CPopupPropertyHandler::createPopupPropertyMap()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s", __FUNCTION__);
    /*
     * NOTE: Always call reset() to set all properties for pProp to Default before calling setProperties() with properties for a new Popup
     */
    CPopupProperties objPopupProperties;
    /****************************
     * Media Popups
    ****************************/
    // USBInserted Popup
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_USB_CONNECTED, "qrc:/QML/Media/Popup/USBInsertedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_USB_CONNECTED,objPopupProperties);

    // USB Removed Popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_USB_DISCONNECTED, "qrc:/QML/Media/Popup/USBRemovedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_USB_DISCONNECTED,objPopupProperties);

    // IPOD Inserted Popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_IPOD_CONNECTED, "qrc:/QML/Media/Popup/IpodConnectedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_IPOD_CONNECTED,objPopupProperties);

    // IPOD Removed Popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_IPOD_DISCONNECTED, "qrc:/QML/Media/Popup/IpodDisconnectedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_IPOD_DISCONNECTED,objPopupProperties);

    //fixMe : Not available in popupList
    // BT Inserted Popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_BTAUDIO_CONNECTED, "qrc:/QML/Media/Popup/BTConnectedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_BTAUDIO_CONNECTED,objPopupProperties);

    //fixMe : Not available in popupList
    // BT Removed Popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_BTAUDIO_DISCONNECTED, "qrc:/QML/Media/Popup/BTDisconnectedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_BTAUDIO_DISCONNECTED,objPopupProperties);

    // AUX Inserted Popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_AUX_CONNECTED, "qrc:/QML/Media/Popup/AuxConnectedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_AUX_CONNECTED,objPopupProperties);

    // AUX Removed Popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_AUX_DISCONNECTED, "qrc:/QML/Media/Popup/AuxDisconnectedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_AUX_DISCONNECTED,objPopupProperties);

    //fixMe : Not available in popupList
    // Empty category popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_MEDIA_EMPTY_CATEGORY,"qrc:/QML/Media/Popup/EmptyCategorySelectedPopup.qml",CPopupEnum::EN_POPUP_PRIORITY_SIX, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3, CPopupProperties::m_vecMediaContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_MEDIA_EMPTY_CATEGORY,objPopupProperties);

    // Empty category popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_MEDIA_EMPTY_DEVICE_CONNECTED,"qrc:/QML/Media/Popup/EmptyUSBConnectedPopup.qml",CPopupEnum::EN_POPUP_PRIORITY_SIX, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_MEDIA_EMPTY_DEVICE_CONNECTED,objPopupProperties);

    // USB Device Error popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_USB_DEVICE_ERROR_CONNECTED,"qrc:/QML/Media/Popup/USBDeviceErrorPopup.qml",CPopupEnum::EN_POPUP_PRIORITY_SIX, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_USB_DEVICE_ERROR_CONNECTED,objPopupProperties);

    //fixMe : Not available in popupList
    // USB Only Video confirmation popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_USB_ONLY_VIDEO_CONFIRMATION,"qrc:/QML/Media/Popup/MediaVideoConfirmationPopup.qml",CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, false, true, true, 2, 5, CPopupProperties::m_vecCommonContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_USB_ONLY_VIDEO_CONFIRMATION,objPopupProperties);

    //fixMe : Not available in popupList
    // USB Only Image confirmation popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_USB_ONLY_IMAGE_CONFIRMATION,"qrc:/QML/Media/Popup/MediaImageConfirmationPopup.qml",CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, false, true, true, 2, 5, CPopupProperties::m_vecCommonContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_USB_ONLY_IMAGE_CONFIRMATION,objPopupProperties);

    // USB - Speed lockout - Video
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_USB_SPEED_LOCKOUT_VIDEO,"qrc:/QML/Media/Popup/SpeedLockoutVideoPopup.qml",CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5);
    fillPopupInfo(CPopupEnum::EN_POPUPID_USB_SPEED_LOCKOUT_VIDEO,objPopupProperties);

    // USB - Speed lockout - Images
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_USB_SPEED_LOCKOUT_IMAGES,"qrc:/QML/Media/Popup/SpeedLockoutImagePopup.qml",CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5);
    fillPopupInfo(CPopupEnum::EN_POPUPID_USB_SPEED_LOCKOUT_IMAGES,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_USB_CORRUPT_VIDEO,"qrc:/QML/Media/Popup/CorruptVideoPopup.qml",CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5, CPopupProperties::m_vecCommonContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_USB_CORRUPT_VIDEO,objPopupProperties);

    /****************************
     * Software Update Popups
    ****************************/
    // Update Image Not Found Popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_IMAGE_NOT_FOUND, "qrc:/QML/SoftwareDownload/UpdateImageNotFound.qml", CPopupEnum::EN_POPUP_PRIORITY_ONE, CPopupEnum::EN_POPUP_ZONE_FOUR, false, false, false, 2, 3, CPopupProperties::m_vecSoftwareUpdateContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_IMAGE_NOT_FOUND,objPopupProperties);

    // Ign ON during SW Update
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_TURN_IGN_OFF, "qrc:/QML/SoftwareDownload/TurnIgnOffPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_ONE, CPopupEnum::EN_POPUP_ZONE_FOUR, false, false, false, 2, 3, CPopupProperties::m_vecSoftwareUpdateContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_TURN_IGN_OFF,objPopupProperties);

    // Low Battery Popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_LOW_BATTERY,"qrc:/QML/SoftwareDownload/LowBatteryPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_ONE, CPopupEnum::EN_POPUP_ZONE_FOUR, false, false, false, 2, 3, CPopupProperties::m_vecSoftwareUpdateContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_LOW_BATTERY,objPopupProperties);

    // No USB connected popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_NO_USB_CONNECTED, "qrc:/QML/SoftwareDownload/NoUSBConnected.qml", CPopupEnum::EN_POPUP_PRIORITY_ONE, CPopupEnum::EN_POPUP_ZONE_FOUR, false, false, false, 2, 3, CPopupProperties::m_vecSoftwareUpdateContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_NO_USB_CONNECTED,objPopupProperties);

    //fixMe : Not available in popupList
    // Update Image Confirmation Popup on selecting file is ISO List screen
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_IMAGE_CONFIRMATION, "qrc:/QML/SoftwareDownload/ISOFileConfirmation.qml", CPopupEnum::EN_POPUP_PRIORITY_ONE, CPopupEnum::EN_POPUP_ZONE_FOUR, false, false, false, 0, -1, CPopupProperties::m_vecSoftwareUpdateContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_IMAGE_CONFIRMATION,objPopupProperties);

    // Package Validation Failed Popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PACKAGE_VALIDATION_FAILED, "qrc:/QML/SoftwareDownload/UpdatePackageValidationFailedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_ONE, CPopupEnum::EN_POPUP_ZONE_FOUR,false,false,false,2,3,CPopupProperties::m_vecSoftwareUpdateContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PACKAGE_VALIDATION_FAILED, objPopupProperties);

    // Package Validation in Progress Popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_VALIDATION_IN_PROGRESS, "qrc:/QML/SoftwareDownload/ValidationInProgressPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_ONE, CPopupEnum::EN_POPUP_ZONE_FOUR, false, false, false, 210, 211, CPopupProperties::m_vecSoftwareUpdateContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_VALIDATION_IN_PROGRESS, objPopupProperties);

    // Package USB Disconnected Popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_MSD_DISCONNECTED, "qrc:/QML/SoftwareDownload/USBDisconnectedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_ONE, CPopupEnum::EN_POPUP_ZONE_FOUR, false, false, false, 2, 3, CPopupProperties::m_vecSoftwareUpdateContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_MSD_DISCONNECTED,objPopupProperties);

    // VERSION MISMATCH Popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_VERSION_MISMATCH, "qrc:/QML/SoftwareDownload/VersionMismatchPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_ONE, CPopupEnum::EN_POPUP_ZONE_FOUR, false, false, false, -1, -1, CPopupProperties::m_vecCommonContextWithCall, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_VERSION_MISMATCH,objPopupProperties);

    /****************************
     * Home Popups
    ****************************/
    //Home shortcut remove/replace popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_HOME_EDIT_SHORTCUT, "qrc:/QML/Home/RemoveReplaceShortcutPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5, CPopupProperties::m_vecHomeContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_HOME_EDIT_SHORTCUT,objPopupProperties);

    /****************************
     * Audio Presets Popup
     ***************************/
    //fixMe : Not available in popupList
    //Audio presets list popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_AUDIO_PRESETS_LIST, "qrc:/QML/Setup/AudioPresetsListPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, false, true, true, 0, -1, CPopupProperties::m_vecSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_AUDIO_PRESETS_LIST,objPopupProperties);

    /****************************
     * Phone Setup Popups
    ****************************/
    //Device limit reached popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SETUP_DEVICE_LIMIT_REACHED,"qrc:/QML/PhoneSetup/DeviceLimitReachedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SETUP_DEVICE_LIMIT_REACHED, objPopupProperties);

    //Turn on bluetooth visibility popup
    //FixMe:Max timeout not mentioned in popupList document, by default maxTimeOut : 3sec
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SETUP_TURN_ON_BLUETOOTH,"qrc:/QML/PhoneSetup/TurnOnBluetoothPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3, CPopupProperties::m_vecPhoneSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SETUP_TURN_ON_BLUETOOTH, objPopupProperties);

    //Bt devices not found popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SETUP_BT_DEVICES_NOT_FOUND,"qrc:/QML/PhoneSetup/BtDevicesNotFoundPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3, CPopupProperties::m_vecPhoneSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SETUP_BT_DEVICES_NOT_FOUND, objPopupProperties);

    //Previous device disconnection popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SETUP_PREVIOUS_DEVICE_DISCONNECTION,"qrc:/QML/PhoneSetup/PreviousDeviceDisconnectionPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5, CPopupProperties::m_vecPhoneSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SETUP_PREVIOUS_DEVICE_DISCONNECTION, objPopupProperties);

    //Passkey popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SETUP_PASSKEY,"qrc:/QML/PhoneSetup/PassKeyPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, false, false, false, 1, -1, CPopupProperties::m_vecPhoneSetupContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SETUP_PASSKEY, objPopupProperties);

    //External pairing request popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SETUP_EXTERNAL_PAIRING_REQUEST,"qrc:/QML/PhoneSetup/ExternalPairingRequestPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, false, false, true, 2, 10);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SETUP_EXTERNAL_PAIRING_REQUEST, objPopupProperties);

    //Determining bluetooth services popup
    //Popup timeout not mentioned
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SETUP_DETERMINING_BT_SERVICES,"qrc:/QML/PhoneSetup/DeterminingBtServicesPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_FOUR, false, false, false, 1, 300, CPopupProperties::m_vecPhoneSetupContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SETUP_DETERMINING_BT_SERVICES, objPopupProperties);

    //Connecting popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTING,"qrc:/QML/PhoneSetup/ConnectingPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_FOUR, false, false, false, 1, 300, CPopupProperties::m_vecPhoneSetupContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTING, objPopupProperties);

    //Connected popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTED,"qrc:/QML/PhoneSetup/ConnectedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTED, objPopupProperties);

    //Connection failed popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTION_FAILED,"qrc:/QML/PhoneSetup/ConnectionFailedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTION_FAILED, objPopupProperties);

    //Disconnecting popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SETUP_DISCONNECTING,"qrc:/QML/PhoneSetup/DisconnectingPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_FOUR, false, false, false, 1, 300, CPopupProperties::m_vecPhoneSetupContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SETUP_DISCONNECTING, objPopupProperties);

    //Disconnected popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SETUP_DISCONNECTED,"qrc:/QML/PhoneSetup/DisconnectedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3, CPopupProperties::m_vecCommonContextWithCall);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SETUP_DISCONNECTED, objPopupProperties);

    //Delete device confirmation popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_DEVICE_CONFIRMATION,"qrc:/QML/PhoneSetup/DeleteDeviceConfirmationPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5, CPopupProperties::m_vecPhoneSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_DEVICE_CONFIRMATION, objPopupProperties);

    //Deleting device popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETING_DEVICE,"qrc:/QML/PhoneSetup/DeletingDevicePopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_FOUR, false, false, false, 1, 300, CPopupProperties::m_vecPhoneSetupContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETING_DEVICE, objPopupProperties);

    //Delete device success popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_DEVICE_SUCCESS,"qrc:/QML/PhoneSetup/DeleteDeviceSuccessPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3, CPopupProperties::m_vecSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_DEVICE_SUCCESS, objPopupProperties);

    //Delete device failed popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_DEVICE_FAILED,"qrc:/QML/PhoneSetup/DeleteDeviceFailedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3, CPopupProperties::m_vecSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_DEVICE_FAILED, objPopupProperties);

    //Delete all devices confirmation popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_ALL_DEVICES_CONFIRMATION,"qrc:/QML/PhoneSetup/DeleteAllDevicesConfirmationPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5, CPopupProperties::m_vecPhoneSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_ALL_DEVICES_CONFIRMATION, objPopupProperties);

    //Deleting all devices popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETING_ALL_DEVICES,"qrc:/QML/PhoneSetup/DeletingAllDevicesPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_FOUR, false, false, false, 1, 300, CPopupProperties::m_vecPhoneSetupContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETING_ALL_DEVICES, objPopupProperties);

    //Delete all devices success popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_ALL_DEVICES_SUCCESS,"qrc:/QML/PhoneSetup/DeleteAllDevicesSuccessPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3, CPopupProperties::m_vecSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_ALL_DEVICES_SUCCESS, objPopupProperties);

    //Delete all devices failed popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_ALL_DEVICES_FAILED,"qrc:/QML/PhoneSetup/DeleteAllDeviceFailedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3, CPopupProperties::m_vecSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_ALL_DEVICES_FAILED, objPopupProperties);

    //Only a2dp profile connected popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SETUP_ONLY_A2DP_CONNECTED,"qrc:/QML/PhoneSetup/A2DPConnectedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SETUP_ONLY_A2DP_CONNECTED, objPopupProperties);

    //Device battery low popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SETUP_DEVICE_BATTERY_LOW,"qrc:/QML/PhoneSetup/DeviceBatteryLowPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SETUP_DEVICE_BATTERY_LOW, objPopupProperties);

    /****************************
     * Android Auto Popups
    ****************************/
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_AA_FIRST_RUN, "qrc:/QML/AndroidAuto/AAFirstRunPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SIX, CPopupEnum::EN_POPUP_ZONE_FOUR, true, false, true, 2, 5, CPopupProperties::m_vecCommonContext, true, false);
    fillPopupInfo(CPopupEnum::EN_POPUPID_AA_FIRST_RUN, objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PROJECTION_ERROR, "qrc:/QML/AndroidAuto/ProjectionErrorPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SIX, CPopupEnum::EN_POPUP_ZONE_FOUR, true, false, true, 2, 5, CPopupProperties::m_vecCommonContext, true, false);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PROJECTION_ERROR, objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_AA_SESSION_CLOSED, "qrc:/QML/AndroidAuto/AASessionClosedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_AA_SESSION_CLOSED, objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS, "qrc:/QML/AndroidAuto/AANavigationDetailsPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SIX, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5, CPopupProperties::m_vecCommonContext, false, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS, objPopupProperties);

    //fixMe : Not available in popupList
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_AA_CONNECT_YOUR_PHONE, "qrc:/QML/AndroidAuto/AAConnectYourPhonePopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SIX, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5);
    fillPopupInfo(CPopupEnum::EN_POPUPID_AA_CONNECT_YOUR_PHONE, objPopupProperties);

    //fixMe : Not available in popupList
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_AA_MAX_DEVICES_PAIRED, "qrc:/QML/AndroidAuto/AAMaxDevicePairedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_AA_MAX_DEVICES_PAIRED, objPopupProperties);

    /****************************
     * Phone Call Popups
    ****************************/
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_INCOMING_CALL_POPUP,"qrc:/QML/PhoneCall/IncomingCallPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_TWO, CPopupEnum::EN_POPUP_ZONE_FOUR, false, false, false, -1, -1, CPopupProperties::m_vecIncomingCallPopupContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_INCOMING_CALL_POPUP, objPopupProperties);

    //No network available popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_NO_NETWORK_AVAILABLE,"qrc:/QML/PhoneCall/NoNetworkAvailablePopup.qml", CPopupEnum::EN_POPUP_PRIORITY_THREE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_NO_NETWORK_AVAILABLE, objPopupProperties);

    //Display OFF confirmation popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DISPLAY_OFF_CONFIRMATION, "qrc:/QML/Drawers/QadDrawer/DisplayOffConfirmationPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3, CPopupProperties::m_vecDisplayOffPopupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DISPLAY_OFF_CONFIRMATION,objPopupProperties);

    //Display OFF Transparent popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DISPLAY_OFF_TRANSPARENT, "qrc:/QML/Drawers/QadDrawer/DisplayOffTransparentPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_EIGHT, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 0, -1);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DISPLAY_OFF_TRANSPARENT, objPopupProperties);

    //PDC Low Priority Call popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_LOW_PRIORITY_CALL_POPUP, "qrc:/QML/PhoneCall/LowPriorityCallPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_TWO, CPopupEnum::EN_POPUP_ZONE_FOUR, false, false, false, -1, -1, CPopupProperties::m_vecPDCRVCContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_LOW_PRIORITY_CALL_POPUP, objPopupProperties);

    /****************************
     * Phone SMS Popups
    ****************************/
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_INCOMING_SMS_POPUP,"qrc:/QML/PhoneSMS/PhoneIncomingSMS.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, true, false, false, 2, 10);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_INCOMING_SMS_POPUP, objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SMS_READING_POPUP,"qrc:/QML/PhoneSMS/PhoneSMSReading.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, true, false, false, 2, -1);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SMS_READING_POPUP, objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SMS_READING_COMPLETE_POPUP, "qrc:/QML/PhoneSMS/PhoneSMSReadingComplete.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SMS_READING_COMPLETE_POPUP,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SENDING_SMS, "qrc:/QML/PhoneSMS/SendingSmsPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_THREE, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 5);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SENDING_SMS, objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_SMS_SENT, "qrc:/QML/PhoneSMS/SmsSentPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_THREE, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_SMS_SENT, objPopupProperties);

    //PDC Low Priority Sms Popup
    //ToDo: This willbe modified as per latest popuplist document
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_LOW_PRIORITY_SMS_POPUP, "qrc:/QML/PhoneSMS/LowPrioritySmsPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, true, false, false, 2, 10, CPopupProperties::m_vecPDCRVCContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_LOW_PRIORITY_SMS_POPUP,objPopupProperties);


    /****************************
     * Setup Factory Reset Popups
    ****************************/

    //Confirmation for factory reset popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_SETUP_FACTORY_RESET_CONFIRMATION_STATUS,"qrc:/QML/Setup/PopUp/FactoryResetConfirmationPopUp.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR,true, true, true, 2, 5, CPopupProperties::m_vecSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_SETUP_FACTORY_RESET_CONFIRMATION_STATUS, objPopupProperties);

    //Ignition On for factory reset popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_SETUP_FACTORY_RESET_IGNITION_ON_STATUS,"qrc:/QML/Setup/PopUp/FactoryResetIgnitionOnPopUp.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR,true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_SETUP_FACTORY_RESET_IGNITION_ON_STATUS, objPopupProperties);

    //Waiting for factory reset popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_SETUP_FACTORY_RESET_WAITING_STATUS,"qrc:/QML/Setup/PopUp/FactoryResetWaitingPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_ONE, CPopupEnum::EN_POPUP_ZONE_FOUR,false, false, false, 2, -1, CPopupProperties::m_vecSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_SETUP_FACTORY_RESET_WAITING_STATUS, objPopupProperties);

    //Successful  factory reset popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_SETUP_FACTORY_RESET_SUCCESSFUL_STATUS,"qrc:/QML/Setup/PopUp/FactoryResetSuccessfullPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR,false, false, false, 0, -1);
    fillPopupInfo(CPopupEnum::EN_POPUPID_SETUP_FACTORY_RESET_SUCCESSFUL_STATUS, objPopupProperties);

    //Factory reset disabled popup due to Speed Lockout
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_SETUP_FACTORY_RESET_DISABLE,"qrc:/QML/Setup/PopUp/FactoryResetDisabledPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, false, false, false, 2, 3, CPopupProperties::m_vecSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_SETUP_FACTORY_RESET_DISABLE, objPopupProperties);

    /****************************
     * Setup Theme Activated Popups
    ****************************/

    //Theme Activated confirmation popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_SETUP_THEME_ACTIVATED_SUCCESSFUL_STATUS, "qrc:/QML/Setup/PopUp/ThemeActivatedSuccessfullPopUp.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR,true, true, true, 2, 3, CPopupProperties::m_vecSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_SETUP_THEME_ACTIVATED_SUCCESSFUL_STATUS, objPopupProperties);

    //Vehicle settings cannot be updated popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_SETUP_VEHICLE_SETTING_CANNOT_UPDATE_POPUP, "qrc:/QML/Setup/PopUp/VehicleSettingCanNotBeUpdatedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR,true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_SETUP_VEHICLE_SETTING_CANNOT_UPDATE_POPUP, objPopupProperties);

    //Park lamp turn on popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_SETUP_PARK_LAMP_TURN_ON_STATUS, "qrc:/QML/Setup/PopUp/ParkLampTurnOnPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR,true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_SETUP_PARK_LAMP_TURN_ON_STATUS, objPopupProperties);

    //Climate turn on popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_SETUP_CLIMATE_TURN_ON_STATUS, "qrc:/QML/Setup/PopUp/ClimateTurnOnPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR,true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_SETUP_CLIMATE_TURN_ON_STATUS, objPopupProperties);

    /****************************
     * Apple CarPlay Popups
     ****************************/
    /*
     * FixMe - Need to ensure the priority and other details once this popup
     * is updated in the popup list doc.
     */
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_APPLE_CARPLAY_SESSION_CLOSED,"qrc:/QML/AppleCarPlay/AppleCarPlaySessionClosedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_APPLE_CARPLAY_SESSION_CLOSED, objPopupProperties);

    //fixMe : Not available in popupList
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_APPLE_CARPLAY_CONNECTION,"qrc:/QML/AppleCarPlay/AppleCarPlayConnectionPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, false, false, 2, 5);
    fillPopupInfo(CPopupEnum::EN_POPUPID_APPLE_CARPLAY_CONNECTION, objPopupProperties);

    //fixMe : Not available in popupList
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_APPLE_CARPLAY_CONNECT_YOUR_PHONE,"qrc:/QML/AppleCarPlay/AppleCarPlayConnectYourPhonePopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SIX, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5);
    fillPopupInfo(CPopupEnum::EN_POPUPID_APPLE_CARPLAY_CONNECT_YOUR_PHONE, objPopupProperties);

    /****************************
     * Phone Browse Popups
    ****************************/
    // TODO: Need to update all the phone browse popup
    //Favorite added information popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_BROWSE_FAVORITE_ADDED,"qrc:/QML/PhoneBrowse/FavoriteAddedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_BROWSE_FAVORITE_ADDED, objPopupProperties);

    //Favorite removed information popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_BROWSE_FAVORITE_REMOVED,"qrc:/QML/PhoneBrowse/FavoriteRemovedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_BROWSE_FAVORITE_REMOVED, objPopupProperties);

    //Favorite remove confirmation popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_BROWSE_FAVORITE_REMOVE_CONFIRMATION,"qrc:/QML/PhoneBrowse/RemoveFavoriteConfirmationPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5, CPopupProperties::m_vecPhoneContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_BROWSE_FAVORITE_REMOVE_CONFIRMATION, objPopupProperties);

    //Favorite list full popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_BROWSE_FAVORITE_LIST_FULL,"qrc:/QML/PhoneBrowse/FavoriteListFullPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3, CPopupProperties::m_vecPhoneContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_BROWSE_FAVORITE_LIST_FULL, objPopupProperties);

    //Add favorite failed
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_BROWSE_ADD_FAVORITE_FAILED,"qrc:/QML/PhoneBrowse/AddFavoriteFailedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_BROWSE_ADD_FAVORITE_FAILED, objPopupProperties);

    //Remove favorite failed
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_PHONE_BROWSE_REMOVE_FAVORITE_FAILED,"qrc:/QML/PhoneBrowse/RemoveFavoriteFailedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_PHONE_BROWSE_REMOVE_FAVORITE_FAILED, objPopupProperties);

    // Voice Alert Notifications
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_VOICE_ALERT_NOTIFICATION,"qrc:/QML/VoiceAlert/VoiceAlertsNotification.qml",CPopupEnum::EN_POPUP_PRIORITY_FOUR, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 0, -1, CPopupProperties::m_vecVoiceAlertPopupContext, true, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_VOICE_ALERT_NOTIFICATION,objPopupProperties);

    /****************************
     * Tuner Popups
    ****************************/

    // No valid station found after autostore popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_NO_VALID_STATION_FOUND_POPUP, "qrc:/QML/Tuner/NoValidStationFoundPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SIX, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3, CPopupProperties::m_vecTunerContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_NO_VALID_STATION_FOUND_POPUP, objPopupProperties);

    // Tuner Antenna not connected
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_TUNER_ANTENNA_NOT_CONNECTED_POPUP, "qrc:/QML/Tuner/AntennaNotConnectedNotification.qml", CPopupEnum::EN_POPUP_PRIORITY_SIX, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_TUNER_ANTENNA_NOT_CONNECTED_POPUP, objPopupProperties);

    /****************************
     * One Hour Mode Popups
    ****************************/

    // One hour mode entry popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_ONE_HOUR_MODE_ENTRY_POPUP,"qrc:/QML/StartupAnim/OneHourModeEntryPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_ONE_HOUR_MODE_ENTRY_POPUP, objPopupProperties);

    /****************************
     * VR Popups
    ****************************/
    // Mic Not available popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_MIC_NOT_AVAILABLE_POPUP,"qrc:/QML/VoiceRecognition/MicNotAvailablePopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3, CPopupProperties::m_vecIncomingCallPopupContext);
    fillPopupInfo(CPopupEnum::EN_MIC_NOT_AVAILABLE_POPUP, objPopupProperties);

    //Vr not available popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_VR_NOT_AVAILABLE_POPUP,"qrc:/QML/VoiceRecognition/VRNotAvailablePopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_VR_NOT_AVAILABLE_POPUP, objPopupProperties);

    /****************************
     * PowerMode Popups
     ****************************/
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_POWERMODE_ONE_HOUR_MODE_EXPIRY, "qrc:/QML/Setup/PopUp/OneHourModeExpiryPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, false, false, false, 2, -1);
    fillPopupInfo(CPopupEnum::EN_POPUPID_POWERMODE_ONE_HOUR_MODE_EXPIRY, objPopupProperties);

    /****************************
     * RCA Popups
    ****************************/
    //RCA aux gain
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_RCA_AUX_GAIN, "qrc:/QML/RCA/RCAAuxGainPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3, CPopupProperties::m_vecCommonContext, false, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_RCA_AUX_GAIN,objPopupProperties);

    //RCA audio preset
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_RCA_AUDIO_PRESET, "qrc:/QML/RCA/RCAAudioPresetPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3, CPopupProperties::m_vecCommonContext, false, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_RCA_AUDIO_PRESET,objPopupProperties);

    //RCA BMT
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_RCA_BMT, "qrc:/QML/RCA/RCABMTPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3, CPopupProperties::m_vecCommonContext, false, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_RCA_BMT,objPopupProperties);

    //RCA Balance fader
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_RCA_BALANCE_FADER, "qrc:/QML/RCA/RCABalanceAndFaderPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SEVEN, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3, CPopupProperties::m_vecCommonContext, false, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_RCA_BALANCE_FADER,objPopupProperties);


    /****************************
     * EnggMenu Popups
     ****************************/

    // USB Not Connected for Debug logs extract
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_ENGGMENU_USB_NOT_CONNECTED, "qrc:/QML/Engg/Popup/USBNotConnectedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SIX, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_ENGGMENU_USB_NOT_CONNECTED, objPopupProperties);

    // USB device full for Debug logs extract
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_ENGGMENU_USB_DEVICE_FULL, "qrc:/QML/Engg/Popup/USBDeviceFullPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SIX, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_ENGGMENU_USB_DEVICE_FULL, objPopupProperties);

    //Logging not enabled for Debug Logs extract
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_ENGGMENU_LOGGING_NOT_ENABLED, "qrc:/QML/Engg/Popup/LoggingNotEnabledPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_SIX, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_ENGGMENU_LOGGING_NOT_ENABLED, objPopupProperties);

    /****************************
     * Vehicle Popups
     ****************************/

    //Popup when antithef key Combination status gets failed.S
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_VEHICLE_ANTITHEFT_AUTHENTICATION_FAILED_POPUP, "qrc:/QML/Setup/PopUp/AntitheftKeyCombinationFailedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, false, false, false, 2, -1);
    fillPopupInfo(CPopupEnum::EN_POPUPID_VEHICLE_ANTITHEFT_AUTHENTICATION_FAILED_POPUP, objPopupProperties);

    /****************************
     * Phone Bt VR Popup
    ****************************/
    // Bt VR Not available popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_BT_VR_NOT_AVAILABLE_POPUP,"qrc:/QML/VoiceRecognition/BtVRNotAvailablePopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_BT_VR_NOT_AVAILABLE_POPUP, objPopupProperties);

    /****************************
     * DriveNext Popup
    ****************************/
    // DriveNext File Update Failed popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DN_FILE_UPDATE_FAILED,"qrc:/QML/DriveNext/Popups/DnFileUpdateFailedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DN_FILE_UPDATE_FAILED, objPopupProperties);

    // DriveNext File Update Success popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DN_FILE_UPDATE_SUCCESS,"qrc:/QML/DriveNext/Popups/DnFileUpdateSuccessPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DN_FILE_UPDATE_SUCCESS, objPopupProperties);

    // DriveNext Can Not Reset popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DN_CAN_NOT_RESET,"qrc:/QML/DriveNext/Popups/DnCanNotResetPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3, CPopupProperties::m_vecDriveNextSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DN_CAN_NOT_RESET, objPopupProperties);

    // DriveNext Reset All Confirmation popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DN_RESET_ALL_CONFIRMATION,"qrc:/QML/DriveNext/Popups/DnResetAllConfirmationPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5, CPopupProperties::m_vecDriveNextSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DN_RESET_ALL_CONFIRMATION, objPopupProperties);

    // DriveNext Reset All Failed popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DN_RESET_ALL_FAILED,"qrc:/QML/DriveNext/Popups/DnResetAllFailedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DN_RESET_ALL_FAILED, objPopupProperties);

    // DriveNext Reset All Success popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DN_RESET_ALL_SUCCESS,"qrc:/QML/DriveNext/Popups/DnResetAllSuccessPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DN_RESET_ALL_SUCCESS, objPopupProperties);

    // DriveNext Reset Trip A Confirmation popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DN_RESET_TRIP_A_CONFIRMATION,"qrc:/QML/DriveNext/Popups/DnResetTripAConfirmationPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5, CPopupProperties::m_vecDriveNextContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DN_RESET_TRIP_A_CONFIRMATION, objPopupProperties);

    // DriveNext Reset Trip B Confirmation popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DN_RESET_TRIP_B_CONFIRMATION,"qrc:/QML/DriveNext/Popups/DnResetTripBConfirmationPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5, CPopupProperties::m_vecDriveNextContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DN_RESET_TRIP_B_CONFIRMATION, objPopupProperties);

    // DriveNext Reset Trip Failed popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DN_RESET_TRIP_FAILED,"qrc:/QML/DriveNext/Popups/DnResetTripFailedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DN_RESET_TRIP_FAILED, objPopupProperties);

    // DriveNext Reset Trip Success popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DN_RESET_TRIP_SUCCESS,"qrc:/QML/DriveNext/Popups/DnResetTripSuccessPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DN_RESET_TRIP_SUCCESS, objPopupProperties);

    /****************************
     * W3W Popups
    ****************************/

    // Share Address Popup
    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_W3W_SHARE_ADDRESS, "qrc:/QML/W3W/W3WPopups/W3WShareAddressPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5, CPopupProperties::m_vecW3WContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_W3W_SHARE_ADDRESS,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_W3W_ADDRESS_SHARED, "qrc:/QML/W3W/W3WPopups/W3WAddressSharedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3, CPopupProperties::m_vecW3WContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_W3W_ADDRESS_SHARED,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_W3W_SET_FAVORITE, "qrc:/QML/W3W/W3WPopups/W3WSetFavoritePopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5, CPopupProperties::m_vecW3WContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_W3W_SET_FAVORITE,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_W3W_FAVORITE_SAVED, "qrc:/QML/W3W/W3WPopups/W3WFavoriteSavedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3, CPopupProperties::m_vecW3WContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_W3W_FAVORITE_SAVED,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_W3W_AA_CP_NOT_CONNECTED, "qrc:/QML/W3W/W3WPopups/W3WAddressAACPNotConnected.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5, CPopupProperties::m_vecCommonContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_W3W_AA_CP_NOT_CONNECTED,objPopupProperties);
	
	objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_W3W_CONNECTNEXT_NOT_CONNECTED, "qrc:/QML/W3W/W3WPopups/W3WAddressConnectNextNotConnected.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5, CPopupProperties::m_vecW3WContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_W3W_CONNECTNEXT_NOT_CONNECTED,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_W3W_DELETE_FAVORITE, "qrc:/QML/W3W/W3WPopups/W3WDeleteFavoritePopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5, CPopupProperties::m_vecW3WContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_W3W_DELETE_FAVORITE,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_W3W_DELETE_RECENT, "qrc:/QML/W3W/W3WPopups/W3WDeleteRecentPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5, CPopupProperties::m_vecW3WContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_W3W_DELETE_RECENT,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_W3W_ADDRESS_DELETED, "qrc:/QML/W3W/W3WPopups/W3WAddressDeletedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3, CPopupProperties::m_vecW3WContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_W3W_ADDRESS_DELETED,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_W3W_FAVORITE_MAX_LIMIT, "qrc:/QML/W3W/W3WPopups/W3WFavoriteMaxLimitPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3, CPopupProperties::m_vecW3WContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_W3W_FAVORITE_MAX_LIMIT,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_W3W_FAVORITE_ALREADY_SAVED, "qrc:/QML/W3W/W3WPopups/W3WFavoriteAlreadySavedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3, CPopupProperties::m_vecW3WContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_W3W_FAVORITE_ALREADY_SAVED,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_W3W_INVALID_ADDRESS, "qrc:/QML/W3W/W3WPopups/W3WInvalidAddressPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3, CPopupProperties::m_vecCommonContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_W3W_INVALID_ADDRESS,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_W3W_HFP_NOT_CONNECTED, "qrc:/QML/W3W/W3WPopups/W3WHFPNotConnectedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3, CPopupProperties::m_vecW3WContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_W3W_HFP_NOT_CONNECTED,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_W3W_SMS_NOT_SUPPORTED, "qrc:/QML/W3W/W3WPopups/W3WSMSNotSupportedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3, CPopupProperties::m_vecW3WContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_W3W_SMS_NOT_SUPPORTED,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_W3W_ALLOW_AUTOLAUNCH_AA, "qrc:/QML/W3W/W3WPopups/W3WAllowAutoLaunchAAPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5, CPopupProperties::m_vecCommonContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_W3W_ALLOW_AUTOLAUNCH_AA,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_W3W_ALLOW_AUTOLAUNCH_CP, "qrc:/QML/W3W/W3WPopups/W3WAllowAutoLaunchCPPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5, CPopupProperties::m_vecCommonContext, true);
    fillPopupInfo(CPopupEnum::EN_POPUPID_W3W_ALLOW_AUTOLAUNCH_CP,objPopupProperties);


    /****************************
     * Doodle Popups
    ****************************/

    objPopupProperties.reset();
    //bCloseOnHK is not in use for this popup As while doodle sticker is on screen HardKEys events handled by DoodleAdaptor.
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DOODLE_MYSTICKER_ICON, "qrc:/QML/Doodle/DoodleSubElements/DoodleMyStickerIcon.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, false, -1, -1, CPopupProperties::m_vecDoodleStickerContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DOODLE_MYSTICKER_ICON,objPopupProperties);

    objPopupProperties.reset();
    //bCloseOnHK is not in use for this popup As while doodle sticker is on screen HardKEys events handled by DoodleAdaptor.
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DOODLE_MYSTICKER_ICON_PREVIEW, "qrc:/QML/Doodle/DoodleSubElements/DoodleMyStickerIconPreview.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, -1, -1, CPopupProperties::m_vecDoodleSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DOODLE_MYSTICKER_ICON_PREVIEW,objPopupProperties);

    objPopupProperties.reset();
    //bCloseOnHK is not in use for this popup As while doodle sticker is on screen HardKEys events handled by DoodleAdaptor.
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DOODLE_STARTUP_IMAGE_PREVIEW, "qrc:/QML/Doodle/DoodleSubElements/DoodleStartupImagePreview.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, -1, -1, CPopupProperties::m_vecDoodleSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DOODLE_STARTUP_IMAGE_PREVIEW,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DOODLE_MYSTICKER_ACTIVATED, "qrc:/QML/Doodle/DoodlePopups/DoodleMyStickerActivatedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3, CPopupProperties::m_vecDoodleSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DOODLE_MYSTICKER_ACTIVATED,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DOODLE_MYSTICKER_CLEAR_POPUP, "qrc:/QML/Doodle/DoodlePopups/DoodleMyStickerClearPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5, CPopupProperties::m_vecDoodleSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DOODLE_MYSTICKER_CLEAR_POPUP,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DOODLE_MYSTICKER_NOT_CONFIGURED, "qrc:/QML/Doodle/DoodlePopups/DoodleMyStickerNotConfiguredPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3, CPopupProperties::m_vecDoodleSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DOODLE_MYSTICKER_NOT_CONFIGURED,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DOODLE_MYSTICKER_UPDATE, "qrc:/QML/Doodle/DoodlePopups/DoodleMyStickerUpdatedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3, CPopupProperties::m_vecDoodleSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DOODLE_MYSTICKER_UPDATE,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DOODLE_STARTUPIMAGE_ACTIVATED, "qrc:/QML/Doodle/DoodlePopups/DoodleStartupImageActivatedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3, CPopupProperties::m_vecDoodleSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DOODLE_STARTUPIMAGE_ACTIVATED,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DOODLE_STARTUPIMAGE_CLEAR_POPUP, "qrc:/QML/Doodle/DoodlePopups/DoodleStartupImageClearPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 5, CPopupProperties::m_vecDoodleSetupContext);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DOODLE_STARTUPIMAGE_CLEAR_POPUP,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DOODLE_STARTUPIMAGE_NOT_CONFIGURED, "qrc:/QML/Doodle/DoodlePopups/DoodleStartupImageNotConfiguredPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_FOUR, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DOODLE_STARTUPIMAGE_NOT_CONFIGURED,objPopupProperties);

    objPopupProperties.reset();
    objPopupProperties.setProperties(CPopupEnum::EN_POPUPID_DOODLE_STARTUPIMAGE_UPDATE, "qrc:/QML/Doodle/DoodlePopups/DoodleStartupImageUpdatedPopup.qml", CPopupEnum::EN_POPUP_PRIORITY_FIVE, CPopupEnum::EN_POPUP_ZONE_TWO, true, true, true, 2, 3);
    fillPopupInfo(CPopupEnum::EN_POPUPID_DOODLE_STARTUPIMAGE_UPDATE,objPopupProperties);
}

void CPopupPropertyHandler::fillPopupInfo(CPopupEnum::EPopupID eID, CPopupProperties pProp )
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s : %d",__FUNCTION__,eID);
    m_mapPopupGroup.insert(eID, pProp);
}

QMap<int, CPopupPropertyHandler::CPopupProperties> CPopupPropertyHandler::getPopupMap()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s", __FUNCTION__);
    return m_mapPopupGroup;
}
