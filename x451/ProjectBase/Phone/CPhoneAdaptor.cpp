/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CPhoneAdaptor.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain implementation of all the methods declared in
 *                CPhoneAdaptor class
 */

#include "CPhoneAdaptor.h"
#include "logging.h"
#include "ResourceFactory.hpp"
#include "CPhoneData.h"
#include "CPopupManager.h"
#include "CAndroidAutoAdaptor.h"
#include "CAppleCarPlayAdaptor.h"
#include "CAudioAdaptor.h"
#include "CPersistencyAdaptor.h"
#include "CDisplayManagerAdaptor.h"
#include "CParkAssistAdaptor.h"
#include "CDiagnosticAdaptor.h"
#include "CDiagnosticEnum.h"
#include "CVRAdaptor.h"
#include "interfaces/IBtPluginResource.h"

#include "implementations/CICCastResourceImpl.h"
#include "implementations/CPhonePIMDBResourceImpl.h"
#include "implementations/CPhoneCallManagerResourceImpl.h"
#include "implementations/CPhoneConnectionManagerResourceImpl.h"
#include "PhoneResource/CPhoneResourceEnums.h"

CPhoneAdaptor* CPhoneAdaptor::m_pPhoneAdaptor = NULL;

CPhoneAdaptor::CPhoneAdaptor(QObject *pParent) :
    QObject(pParent),
    m_objFramework(CFramework::getFramework()),
    /** Phone connection  related properties **/
    m_pPhConnMgrResource(dynamic_cast<CPhoneConnectionManagerResourceImpl*>(ResourceFactory::getPhoneConnectionManagerResource())),
    m_pDeviceSearchListModel(NULL),
    m_pPairedDeviceListModel(NULL),
    m_pPhoneSetupListModel(NULL),
    m_strPassKeyPin(""),
    m_strDisconnectedDeviceName(""),
    m_strDeletedDeviceName(""),
    m_bIsBluetoothEnabled(false),
    m_bDeviceSearchStatus(false),
    m_bBtVisibilityReqStatus(false),
    m_bHUDiscoverableStatus(false),
    m_strSelItemName(""),
    m_strSelItemBtAddr(""),
    m_bIsDeleteAllSelected(false),

    /** Connected device info **/
    m_strConnectedDeviceAddr(""),
    m_strConnectedDeviceName(""),
    m_eHFPConnectionStatus(CONNECTION_STATUS_DEFAULT),
    m_eA2DPConnectionStatus(CONNECTION_STATUS_DEFAULT),
    m_bIsHFPConnected(false),
    m_bIsA2DPConnected(false),
    m_bIsDeviceConnected(false),

    /** Phone call related properties **/
    m_pPhCallMgrResource(dynamic_cast<CPhoneCallManagerResourceImpl*>(ResourceFactory::getPhoneCallManagerResource())),
    m_ePhoneCallState(CPhoneEnum::PHONE_CALLSTATE_IDLE),
    m_bAcceptCallRequestStatus(false),
    m_bRejectCallRequestStatus(false),
    m_bSendSMSRequestStatus(false),
    m_bDialRequestStatus(false),
    m_bMergeCallsRequestStatus(false),
    m_bSwapCallRequestStatus(false),
    m_bResumeCallRequestStatus(false),
    m_bHoldCallRequestStatus(false),
    m_bEndCallRequestStatus(false),
    m_bIsHandsFreeMode(false),
    m_bIsNetworkAvailable(false),
    m_eSignalStrengthLevel(CPhoneEnum::SIGNAL_STRENGTH_UNAVAILABLE),
    m_eBatteryChargeLevel(CPhoneEnum::BATTERY_CHARGE_UNAVAILABLE),
    /** Phone pimdb related properties **/
    m_eCurrentPhoneBrowseScreen(CPhoneEnum::PHONE_BROWSE_TYPE_CALL_LOGS),
    m_pPhPimDbResource(dynamic_cast<CPhonePIMDBResourceImpl*>(ResourceFactory::getPhonePIMDBResource())),
    m_pCallLogListModel(new CCallLogListModel(this)),
    m_pFrequentlyDialedListModel(new CCallLogListModel(this)),
    m_pContactListModel(new CContactDetailListModel(this)),
    m_pContactDetailListModel(new CContactDetailListModel(this)),
    m_pFavoriteContactListModel(new CContactDetailListModel(this)),
    m_ePimDbCallListSyncState(CPhoneEnum::PHONE_DATA_READ_OFF),
    m_ePimDbContactListSyncState(CPhoneEnum::PHONE_DATA_READ_OFF),
    m_ePimDbContactDetailListSyncState(CPhoneEnum::PHONE_DATA_READ_OFF),
    m_ePimDbFavouriteListSyncState(CPhoneEnum::PHONE_DATA_READ_OFF),
    m_ePimDbFrequentlyDialedListSyncState(CPhoneEnum::PHONE_DATA_READ_OFF),
    m_ePhoneNetworkRegState(PHONE_NETWORK_REGSTATE_UNKNOWN),
    m_bIsInDTMFNumberPad(false),
    m_iCurrentMessageIndex(-1),
    m_strCurrentMessageText(""),
    m_bSMSAvailable(false),
    m_bIsSendingSMSAllowed(false),
    m_bIsFavoriteToggling(false),
    m_eTTSPlayState(CPhoneEnum::EN_PLAY_STATE_NOTPLAYING),
    m_bStartNewSmsReadout(false),
    m_bIsOldestConnDeviceDeletionRequested(false),
    m_iContactListCurrentTopIndex(0),
    m_bShowIncomingSmsPopup(false),
    m_bDeleteAllDevicesStatus(false),
    m_bDeleteDeviceStatus(false),
    m_bLPPhonePopupStatus(false),
    m_iPreviousPairedListCount(0),
    m_iCurrentPairedListCount(0),
    m_bPhoneBtVrModeStatus(false),
    m_bIsPhoneBtVROverlayVisible(false),
    m_bBtVrSupported(false),
    m_bApplePhoneConnected(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    qmlRegisterUncreatableType<CCallInfo>                ("com.harman.qml.CallInfo", 1, 0, "CallInfo",                  "Cannot create instance of CCallInfo in qml");
    qmlRegisterUncreatableType<CCallLogListModel>        ("com.harman.qml.PimDb",    1, 0, "CCallLogListModel",         "Cannot create instance of CCallLogListModel in qml");
    qmlRegisterUncreatableType<CContactDetailListModel>  ("com.harman.qml.PimDb",    1, 0, "CContactDetailListModel",   "Cannot create instance of CContactDetailListModel in qml");
    m_objFramework.setContextProperty("cppPhoneAdaptor", this);
    getPhoneResourceInfo();
    invResetUnreadMissedCallInfo();
    resetCallInfo();
    resetPimdbProperties();
    connect(CParkAssistAdaptor::getInstance(),      SIGNAL(sigReverseGearStatusChanged()),                  this, SLOT(sltReverseGearStatusChanged()), Qt::QueuedConnection);
    connect(CAudioAdaptor::getInstance(),           SIGNAL(sigSourceStateInfoUpdated(int,int)),             this, SLOT(sltSourceStateInfoUpdated(int, int)), Qt::QueuedConnection);
    connect(CAndroidAutoAdaptor::getInstance(),     SIGNAL(sigAndroidAutoConnectionStatusChanged(bool)),    this, SLOT(sltPrjPhConnectionStatus(bool)), Qt::QueuedConnection);
    connect(CAppleCarPlayAdaptor::getInstance(),    SIGNAL(sigAppleCarPlayConnectionStatusChanged(bool)),   this, SLOT(sltPrjPhConnectionStatus(bool)), Qt::QueuedConnection);
    connect(&m_objEndCallScreenTimer,               SIGNAL(timeout()),                                      this, SLOT(sltDeactivatePhoneCall()));
}

CPhoneAdaptor::~CPhoneAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if (m_pPhoneAdaptor)
    {
        delete m_pPhoneAdaptor;
        m_pPhoneAdaptor = NULL;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: phone adaptor instance already destroyed", __FUNCTION__);
    }

    if (m_pDeviceSearchListModel)
    {
        delete m_pDeviceSearchListModel;
        m_pDeviceSearchListModel = NULL;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: device search list model instance already destroyed", __FUNCTION__);
    }

    if (m_pPairedDeviceListModel)
    {
        delete m_pPairedDeviceListModel;
        m_pPairedDeviceListModel = NULL;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: paired device list model instance already destroyed", __FUNCTION__);
    }

    if(m_pPhoneSetupListModel)
    {
        delete m_pPhoneSetupListModel;
        m_pPhoneSetupListModel = NULL;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: phone setup list model instance already destroyed", __FUNCTION__);
    }

    if (m_pCallLogListModel)
    {
        delete m_pCallLogListModel;
        m_pCallLogListModel = NULL;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: call log list model instance already destroyed", __FUNCTION__);
    }

    if (m_pFrequentlyDialedListModel)
    {
        delete m_pFrequentlyDialedListModel;
        m_pFrequentlyDialedListModel = NULL;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: frequently dialed list model instance already destroyed", __FUNCTION__);
    }

    if (m_pContactListModel)
    {
        delete m_pContactListModel;
        m_pContactListModel = NULL;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: contact list model instance already destroyed", __FUNCTION__);
    }

    if (m_pContactDetailListModel)
    {
        delete m_pContactDetailListModel;
        m_pContactDetailListModel = NULL;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: contact detail list model instance already destroyed", __FUNCTION__);
    }

    if (m_pFavoriteContactListModel)
    {
        delete m_pFavoriteContactListModel;
        m_pFavoriteContactListModel = NULL;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: favorite list model instance already destroyed", __FUNCTION__);
    }
}

/************************************************************************//**
 * @category    METHODS
 ************************************************************************/
bool CPhoneAdaptor::getProjPhConnectionStatus()
{
    bool bStatus = ((CAndroidAutoAdaptor::getInstance()->androidAutoConnectionStatus()) ||
                    (CAppleCarPlayAdaptor::getInstance()->appleCarPlayConnectionStatus()));
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bStatus: %d:", __FUNCTION__, bStatus);
    return bStatus;
}

void CPhoneAdaptor::getPhoneResourceInfo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pPhConnMgrResource)
    {
        updateBluetoothStatus(m_pPhConnMgrResource->getBluetoothStatus());

    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: phone connection manager resource not available", __FUNCTION__);
    }

    updateBondedDeviceList();
    //updateConnectedDeviceList();
    updateBondingRequest();
    updateServiceConnectionStatus();
    callStateInfoUpdated();
    updateOperatorInfoList();
    updateRssiChargeInfo();
    updateHfFeatures();
    updateHfModeStatus();
}

CPhoneAdaptor* CPhoneAdaptor::getInstance()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if (!m_pPhoneAdaptor)
    {
        m_pPhoneAdaptor = new CPhoneAdaptor();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: phone adaptor instance already created", __FUNCTION__);
    }
    return m_pPhoneAdaptor;
}

void CPhoneAdaptor::initPhoneDataModels()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_pDeviceSearchListModel = new CDeviceSearchListModel(this);
    m_pPairedDeviceListModel = new CPairedDeviceListModel(this);
    m_pPhoneSetupListModel = new CPhoneSetupListModel(this);
}

void CPhoneAdaptor::reqPhoneBtVrActivation()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: m_bPhoneBtVrModeStatus: %d, m_strConnectedDeviceAddr: %sm pdcRvcStatus: %d, doesCallExist: %d",
             __FUNCTION__, m_bPhoneBtVrModeStatus, m_strConnectedDeviceAddr.toStdString().c_str(),
             CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus(), CPhoneAdaptor::getInstance()->doesCallExist());

    if((!CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus()) &&
        (!CPhoneAdaptor::getInstance()->doesCallExist()))
    {
        if(m_strConnectedDeviceAddr != "")
        {
            if(m_bBtVrSupported)
            {
                if(m_pPhCallMgrResource)
                {
                    m_pPhCallMgrResource->setPhoneBtVrModeAsyncReq(m_strConnectedDeviceAddr.toStdString(), true);
                }
                else
                {
                    LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone call manager resource object not created", __FUNCTION__);
                }
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bt vr is not supported by connected phone", __FUNCTION__);
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_BT_VR_NOT_AVAILABLE_POPUP);
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: no device is connected, switching to phone setup", __FUNCTION__);
            CHMIMain::getSM()->getSCI_Setup()->raise_evBluetoothSetupActivated(CHMIMain::getSM()->getDefaultSCI()->get_sETUP_SCR_BT_NAMED_ENTRY());
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: Reverse gear is engaged or call is active, not activating Bt VR", __FUNCTION__);
    }
}

void CPhoneAdaptor::invReqPhoneBtVrDeactivation()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: m_bPhoneBtVrModeStatus: %d, m_strConnectedDeviceAddr: %s", __FUNCTION__, m_bPhoneBtVrModeStatus, m_strConnectedDeviceAddr.toStdString().c_str());
    if(m_bPhoneBtVrModeStatus)
    {
        if(m_pPhCallMgrResource)
        {
            m_pPhCallMgrResource->setPhoneBtVrModeAsyncReq(m_strConnectedDeviceAddr.toStdString(), false);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone call manager resource object not created", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Phone bt vr is not active or no device is connected", __FUNCTION__);
    }
}

bool CPhoneAdaptor::isPhoneBtVROverlayVisible()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: m_bIsPhoneBtVROverlayVisible: %d", __FUNCTION__, m_bIsPhoneBtVROverlayVisible);
    return m_bIsPhoneBtVROverlayVisible;
}

bool CPhoneAdaptor::invHandleHardKeys(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: key is: %d, key state is: %d", __FUNCTION__, eKey, eKeyState);
    bool bRet = true;

    switch(eKey)
    {
    case CHardKeyEnum::KEYCODEHK_SEEKUP:
    case CHardKeyEnum::KEYCODEHK_SEEKDOWN:
    case CHardKeyEnum::KEYCODESWC_NEXT:
    case CHardKeyEnum::KEYCODESWC_PREV:
    {
        if(m_bShowIncomingSmsPopup)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: incoming sms, pass the control to module", __FUNCTION__);
            //screen should do the partial handling of HK, hence return false
            bRet = false;
        }
        else if(m_eTTSPlayState == CPhoneEnum::EN_PLAY_STATE_PLAYING)
        {
            //No action should be taken, hence return true
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: sms reading ongoing, do not take any action", __FUNCTION__);
        }
        else if(m_bPhoneBtVrModeStatus)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Phone bt vr is active, No action to be taken", __FUNCTION__);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: No action to be taken", __FUNCTION__);
        }
    }
        break;

    default:
    {
        if((CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState) ||
                (CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState))
        {
            switch(eKey)
            {
            case CHardKeyEnum::KEYCODEHK_PHONE:
            {
                if(isCallIncoming())
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: call is incoming, accept it", __FUNCTION__);
                    invAcceptIncomingCall();
                }
                else if(m_bShowIncomingSmsPopup)
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: incoming sms, activate readout", __FUNCTION__);
                    if((CParkAssistAdaptor::getInstance()) && (!CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus()))
                    {
                        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Reverse gear is disengaged", __FUNCTION__);
                        if(CPopupManager::getInstance())
                        {
                            CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_SMS_POPUP);
                        }
                        else
                        {
                            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Popup manager not available", __FUNCTION__);
                        }
                        invStartSmsReadout();
                    }
                    else
                    {
                        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Reverse gear is engaged", __FUNCTION__);
                    }
                }
                else if(m_eTTSPlayState == CPhoneEnum::EN_PLAY_STATE_PLAYING)
                {
                    invStopSmsReadout();
                    invSwitchToPhoneBrowse(CPhoneEnum::PHONE_BROWSE_TYPE_CALL_LOGS);
                }
                else if(!doesCallExist())
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: call does not exist, switch to phone call logs", __FUNCTION__);
                    invSwitchToPhoneBrowse(CPhoneEnum::PHONE_BROWSE_TYPE_CALL_LOGS);
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: No action to be taken", __FUNCTION__);
                }
            }
                break;

            case CHardKeyEnum::KEYCODESWC_ACCEPT_VR:
            {
                if(isCallIncoming())
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: call is incoming, accept it", __FUNCTION__);
                    invAcceptIncomingCall();
                }
                else if(m_bShowIncomingSmsPopup)
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: incoming sms, activate readout", __FUNCTION__);
                    if((CParkAssistAdaptor::getInstance()) && (!CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus()))
                    {
                        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Reverse gear is disengaged", __FUNCTION__);
                        CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_SMS_POPUP);
                        invStartSmsReadout();
                    }
                    else
                    {
                        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Reverse gear is engaged", __FUNCTION__);
                    }
                }
                else if(m_bPhoneBtVrModeStatus)
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: phone bt vr is active", __FUNCTION__);
                    if(m_bApplePhoneConnected)
                    {
                        if(CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState)
                        {
                            reqPhoneBtVrActivation();
                        }
                        else if(CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState)
                        {
                            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: iPhone connected, long press on PTT, deactivate phone bt vr", __FUNCTION__);
                            invReqPhoneBtVrDeactivation();
                        }
                        else
                        {
                            //do nothing
                        }
                    }
                    else
                    {
                        if(CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState)
                        {
                            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: android phone connected, short release on PTT, deactivate phone bt vr", __FUNCTION__);
                            invReqPhoneBtVrDeactivation();
                        }
                        else
                        {
                            //do nothing
                        }
                    }
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: No action to be taken", __FUNCTION__);
                }
            }
                break;

            case CHardKeyEnum::KEYCODESWC_REJECT_MUTE:
            {
                if(isCallIncoming())
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: call is incoming, reject it", __FUNCTION__);
                    invRejectIncomingCall();
                }
                else if(isCallActive())
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: call is active, end the call", __FUNCTION__);
                    invEndPhoneCall();
                }
                else if(m_bShowIncomingSmsPopup)
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: incoming sms, close the popup", __FUNCTION__);
                    if((CParkAssistAdaptor::getInstance()) && (!CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus()))
                    {
                        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Reverse gear is disengaged", __FUNCTION__);
                        if(CPopupManager::getInstance())
                        {
                            CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_SMS_POPUP);
                        }
                        else
                        {
                            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Popup manager not available", __FUNCTION__);
                        }
                    }
                    else
                    {
                        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Reverse gear is engaged", __FUNCTION__);
                    }
                }
                else if(m_eTTSPlayState == CPhoneEnum::EN_PLAY_STATE_PLAYING)
                {
                    invStopSmsReadout();
                }
                else if(m_bPhoneBtVrModeStatus)
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: deactivate phone bt vr", __FUNCTION__);
                    invReqPhoneBtVrDeactivation();
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: No action to be taken", __FUNCTION__);
                }
            }
                break;

            case CHardKeyEnum::KEYCODESWC_SOURCE:
            {
                if(m_bShowIncomingSmsPopup)
                {
                    if(CPopupManager::getInstance())
                    {
                        CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_SMS_POPUP);
                    }
                    else
                    {
                        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Popup manager not available", __FUNCTION__);
                    }
                    //screen should do the partial handling of HK, hence return false
                    bRet = false;
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: No action to be taken", __FUNCTION__);
                }

                if(m_eTTSPlayState == CPhoneEnum::EN_PLAY_STATE_PLAYING)
                {
                    invStopSmsReadout();
                    bRet = false;
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: No action to be taken", __FUNCTION__);
                }

                if(m_bPhoneBtVrModeStatus)
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: deactivate phone bt vr", __FUNCTION__);
                    invReqPhoneBtVrDeactivation();
                    //screen should do the partial handling of HK, hence return false
                    bRet = false;
                }
                else
                {
                    //do nothing
                }
            }
                break;

            case CHardKeyEnum::KEYCODEHK_HOME:
            case CHardKeyEnum::KEYCODEHK_FAVORITE:
            {
                if(m_bShowIncomingSmsPopup)
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: incoming sms, close popup", __FUNCTION__);
                    if((CParkAssistAdaptor::getInstance()) && (!CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus()))
                    {
                        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Reverse gear is disengaged", __FUNCTION__);
                        if(CPopupManager::getInstance())
                        {
                            CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_SMS_POPUP);
                        }
                        else
                        {
                            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Popup manager not available", __FUNCTION__);
                        }
                        //screen should do the partial handling of HK, hence return false
                        bRet = false;
                    }
                    else
                    {
                        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Reverse gear is engaged", __FUNCTION__);
                    }

                }
                else if(m_eTTSPlayState == CPhoneEnum::EN_PLAY_STATE_PLAYING)
                {
                    invStopSmsReadout();
                    bRet = false;
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: No action to be taken", __FUNCTION__);
                }
            }
                break;

            case CHardKeyEnum::KEYCODEHK_BACK:
            {
                if(CPopupEnum::EN_POPUPID_LOW_PRIORITY_CALL_POPUP == CPopupManager::getInstance()->getCurrentDisplayedPopup())
                {
                    bRet = false;
                }
                else if(CPopupEnum::EN_POPUPID_LOW_PRIORITY_SMS_POPUP == CPopupManager::getInstance()->getCurrentDisplayedPopup())
                {
                    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_LOW_PRIORITY_SMS_POPUP);
                    bRet = false;
                }
                else if(m_bShowIncomingSmsPopup)
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: incoming sms, close popup", __FUNCTION__);
                    if((CParkAssistAdaptor::getInstance()) && (!CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus()))
                    {
                        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Reverse gear is disengaged", __FUNCTION__);
                        if(CPopupManager::getInstance())
                        {
                            CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_SMS_POPUP);
                        }
                        else
                        {
                            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Popup manager not available", __FUNCTION__);
                        }
                    }
                    else
                    {
                        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Reverse gear is engaged", __FUNCTION__);
                    }
                }
                else if(m_eTTSPlayState == CPhoneEnum::EN_PLAY_STATE_PLAYING)
                {
                    invStopSmsReadout();
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: No action to be taken", __FUNCTION__);
                }
            }
                break;

            default:
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: key received is not handled", __FUNCTION__);
                break;
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: key state received is not handled", __FUNCTION__);
        }
    }
        break;
    }
    return bRet;
}

QString CPhoneAdaptor::invGetLastDialedNumber()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    QString lastDialedNumber = "";

    if(m_pPhPimDbResource)
    {
        int iSize = static_cast<int>(m_pPhPimDbResource->getCallLogList().size());
        if(iSize > 0)
        {
            for(int iIndex = 0 ; iIndex < iSize -1; iIndex++)
            {
                if(getCallType(m_pPhPimDbResource->getCallLogList().at(iIndex).m_iCallType) == CPhoneEnum::CALL_TYPE_OUTGOING)
                {
                    lastDialedNumber =  QString::fromStdString(m_pPhPimDbResource->getCallLogList().at(iIndex).m_strContactNumber);
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s---%s", __FUNCTION__, lastDialedNumber.toStdString().c_str());
                    break;
                }
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s list is empty , size is %d", __FUNCTION__, iSize);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, " %s PimDb resource object not created", __FUNCTION__);
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s---%s", __FUNCTION__, lastDialedNumber.toStdString().c_str());
    return lastDialedNumber;
}

int CPhoneAdaptor::invGetBrowseType(int iItemIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: item index: %d", __FUNCTION__, iItemIndex);
    int iItemType = -1;
    if((iItemIndex >= 0) && (iItemIndex < m_objPhoneBrowseTabBarModel.rowCount()))
    {
        iItemType = m_objPhoneBrowseTabBarModel.getBrowseType(iItemIndex);
    }
    else
    {
        //Do nothing
    }
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: browse item type: %d", __FUNCTION__, iItemType);
    return iItemType;
}

int CPhoneAdaptor::invGetBrowseItemIndex(int iPhoneBrowseType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: iPhoneBrowseType: %d", __FUNCTION__, iPhoneBrowseType);
    int iItemIndex = -1;
    if((iPhoneBrowseType > CPhoneEnum::PHONE_BROWSE_TYPE_UNKNOWN) && (iPhoneBrowseType < CPhoneEnum::PHONE_BROWSE_TYPE_CONTACT_DETAILS))
    {
        iItemIndex = m_objPhoneBrowseTabBarModel.getBrowseItemIndex(static_cast<CPhoneEnum::EPhoneBrowseType>(iPhoneBrowseType));
    }
    else
    {
        //Do nothing
    }
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: tab bar item index: %d", __FUNCTION__, iItemIndex);
    return iItemIndex;
}

bool CPhoneAdaptor::isCallActive()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    bool bRet = false;
    if((m_ePhoneCallState != CPhoneEnum::PHONE_CALLSTATE_INCOMING_CALL) &&
            (m_ePhoneCallState != CPhoneEnum::PHONE_CALLSTATE_ACTIVE_CALL_AND_INCOMING_CALL) &&
            (m_ePhoneCallState != CPhoneEnum::PHONE_CALLSTATE_HELD_CALL_AND_INCOMING_CALL) &&
            (m_ePhoneCallState != CPhoneEnum::PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_INCOMING_CALL) &&
            (m_ePhoneCallState != CPhoneEnum::PHONE_CALLSTATE_CONFERENCE_ONHOLD_AND_INCOMING_CALL) &&
            (m_ePhoneCallState != CPhoneEnum::PHONE_CALLSTATE_ALL_CALLS_TERMINATED) &&
            (m_ePhoneCallState != CPhoneEnum::PHONE_CALLSTATE_IDLE))
    {
        bRet = true;
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Call is active/outgoing");
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Call is not active/outgoing");
    }

    return bRet;
}

bool CPhoneAdaptor::isCallIncoming()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    bool bRet = false;
    if((m_ePhoneCallState == CPhoneEnum::PHONE_CALLSTATE_INCOMING_CALL) ||
            (m_ePhoneCallState == CPhoneEnum::PHONE_CALLSTATE_ACTIVE_CALL_AND_INCOMING_CALL) ||
            (m_ePhoneCallState == CPhoneEnum::PHONE_CALLSTATE_HELD_CALL_AND_INCOMING_CALL) ||
            (m_ePhoneCallState == CPhoneEnum::PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_INCOMING_CALL) ||
            (m_ePhoneCallState == CPhoneEnum::PHONE_CALLSTATE_CONFERENCE_ONHOLD_AND_INCOMING_CALL))
    {
        bRet = true;
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Call is incoming");
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Call is not incoming");
    }

    return bRet;
}

bool CPhoneAdaptor::doesCallExist()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    bool bRet = false;
    if(m_ePhoneCallState != CPhoneEnum::PHONE_CALLSTATE_IDLE)
    {
        bRet = true;
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, " %s Call exists, call state %d", __FUNCTION__, m_ePhoneCallState);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, " %s Call does not exist", __FUNCTION__);
    }

    return bRet;
}

bool CPhoneAdaptor::lowPriorityPopupActive()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    return m_bLPPhonePopupStatus;

}

void CPhoneAdaptor::switchToContactDetails(int iContactId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s",__FUNCTION__);
    invGetContactDetails(iContactId);
}

void CPhoneAdaptor::sltReverseGearStatusChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    takeActionForPhoneInterrupts();
}

void CPhoneAdaptor::sltSourceStateInfoUpdated(int iSourceId, int iSourceState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: source id is: %d, source state is: %d", __FUNCTION__, iSourceId, iSourceState);
    CAudioEnums::ESourceId eSourceId        = static_cast<CAudioEnums::ESourceId>(iSourceId);
    CAudioEnums::ESourceState eSourceState  = static_cast<CAudioEnums::ESourceState>(iSourceState);
    switch(eSourceId)
    {
    case CAudioEnums::EN_INT_SOURCE_TEL_RINGING:
    {
        switch(eSourceState)
        {
        case CAudioEnums::EN_SOURCE_STATE_CONNECTED:
            callStateInfoUpdated();
            break;

        case CAudioEnums::EN_SOURCE_STATE_DISCONNECTED:
        {
            if(m_ePhoneCallState == CPhoneEnum::PHONE_CALLSTATE_ALL_CALLS_TERMINATED)
            {
                ringtoneSourceDeactivated();
            }
        }
            break;

        default:
            break;
        }
    }
        break;

    case CAudioEnums::EN_INT_SOURCE_TEL_HANDSFREE:
    {
        switch(eSourceState)
        {
        case CAudioEnums::EN_SOURCE_STATE_CONNECTED:
            callStateInfoUpdated();
            break;

        case CAudioEnums::EN_SOURCE_STATE_DISCONNECTED:
        {
            if((m_ePhoneCallState == CPhoneEnum::PHONE_CALLSTATE_ALL_CALLS_TERMINATED) && (!m_objEndCallScreenTimer.isActive()))
            {
                if(CHMIMain::getSM()->getSCI_Phone()->get_bIsPhoneCallStateActivated())
                {
                    hfpSourceDeactivated();
                }
                else
                {
                    //HFP source deactivation received for first incoming call(incase of IPHONE and NEXUS 6p, HFP source is activated instead of ringtone source)
                    ringtoneSourceDeactivated();
                }
            }
            else
            {
                //end call screen timer is active that means hfp source deactivation is received before the timeout
            }
        }
            break;

        default:
            break;
        }
    }
        break;

    default:
        break;
    }
}

void CPhoneAdaptor::sltPrjPhConnectionStatus(bool bPrjPhConnectionState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bPrjPhConnectionState: %d", __FUNCTION__, bPrjPhConnectionState);

    updateBTItemEnableState();
}

void CPhoneAdaptor::sltDeactivatePhoneCall()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CAudioAdaptor::getInstance())
    {
        CAudioEnums::ESourceState eSourceState = CAudioAdaptor::getInstance()->getSourceState(CAudioEnums::EN_INT_SOURCE_TEL_HANDSFREE);
        if(eSourceState == CAudioEnums::EN_SOURCE_STATE_DISCONNECTED)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: HFP source is disconnected", __FUNCTION__);
            hfpSourceDeactivated();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: HFP source is connected", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Audio adaptor not available", __FUNCTION__);
    }
}

void CPhoneAdaptor::takeActionForPhoneInterrupts()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if((CParkAssistAdaptor::getInstance()) && (CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus()))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: reverse gear engaged", __FUNCTION__);
        if(doesCallExist())
        {
            if(m_ePhoneCallState != CPhoneEnum::PHONE_CALLSTATE_INCOMING_CALL)
            {
                CHMIMain::getSM()->getSCI_Phone()->set_bIsPhoneCallStateActivated(true);
            }
            updateCallInPdcRvc();
        }
        else if(m_bShowIncomingSmsPopup)
        {
            updateSmsInPdcRvc();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: call does not exist", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: reverse gear disengaged", __FUNCTION__);
        if(doesCallExist())
        {
            updateCallInNative();
        }
        else if(m_bShowIncomingSmsPopup)
        {
            updateSmsInNative();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: call does not exist", __FUNCTION__);
        }
    }
}

void CPhoneAdaptor::resetIncomingSmsPopupState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_bShowIncomingSmsPopup = false;
    ResourceFactory::getICCastResource()->setIcRenderSmsIndicationAsyncReq(false, "");
}

void CPhoneAdaptor::showSmsSentPopup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    CAudioAdaptor::getInstance()->playBeep(CAudioEnums::BEEP_TYPE_CONFIRM);
    CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SMS_SENT);
}

/************************************************************************//**
 * @category    BT CONNECTION METHODS
 ************************************************************************/
void CPhoneAdaptor::invClearDeviceSearchList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pDeviceSearchListModel)
    {
        m_pDeviceSearchListModel->removeRows();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Device list model object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::startDeviceSearch()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pPhConnMgrResource)
    {
        m_pPhConnMgrResource->startDeviceSearchAsyncReq();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone connection manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::invStopDeviceSearch()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pPhConnMgrResource)
    {
        m_pPhConnMgrResource->stopDeviceSearchAsyncReq();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone connection manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::updateBluetoothStatus(bool bBtStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "function is: %s , bluetooth status is: %d", __FUNCTION__, bBtStatus);
    if(bBtStatus != m_bIsBluetoothEnabled)
    {
        m_bIsBluetoothEnabled = bBtStatus;
        updateBTItemEnableState();
        emit sigBluetoothStatusUpdated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bluetooth status not changed", __FUNCTION__);
    }
}

void CPhoneAdaptor::updatePassKey(const string& strPassKey)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "function is: %s , passkey pin is: \'%s\'", __FUNCTION__, strPassKey.c_str());
    if(QString::fromStdString(strPassKey).compare(m_strPassKeyPin) != 0)
    {
        m_strPassKeyPin = QString::fromStdString(strPassKey);
        emit sigPassKeyPinUpdated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: passkey pin value not changed", __FUNCTION__);
    }
}

void CPhoneAdaptor::updateDeviceSearchStatus(bool bDeviceSearchStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "function is: %s , device search status is: %d", __FUNCTION__, bDeviceSearchStatus);
    if(bDeviceSearchStatus != m_bDeviceSearchStatus)
    {
        m_bDeviceSearchStatus = bDeviceSearchStatus;
        emit sigDeviceSearchStatus();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: device search status not changed", __FUNCTION__);
    }
}

void CPhoneAdaptor::updateHUDiscoverableStatus(bool bDiscoverableStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "function is: %s , discoverable status is: %d", __FUNCTION__, bDiscoverableStatus);
    if(m_pPhoneSetupListModel)
    {
        m_bHUDiscoverableStatus     = bDiscoverableStatus;
        /**
         * bt visisbility request status has been received from connection manager service,
         * hence change the enable state from true to false, as we are disabling/enabling the bluetooth visibility
         * option in the screen based on the enable state. If enable state is true(request has been sent) then the
         * bluetooth visibility option shall be disabled and vice versa.
         */
        setBtVisibilityReqStatus(false);
        m_pPhoneSetupListModel->setData(m_pPhoneSetupListModel->index(CPhoneEnum::PHONE_SETUP_BLUETOOTH_VISIBILITY, 0),
                                        !(getProjPhConnectionStatus()), CPhoneSetupListModel::PHONE_SETUP_ITEM_ENABLED_ROLE);
        m_pPhoneSetupListModel->setData(m_pPhoneSetupListModel->index(CPhoneEnum::PHONE_SETUP_BLUETOOTH_VISIBILITY, 0),
                                        m_bHUDiscoverableStatus, CPhoneSetupListModel::PHONE_SETUP_ITEM_CHECKED_ROLE);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: phone setup list model object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::updateDeviceSearchResult()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pPhConnMgrResource)
    {
        if(m_pDeviceSearchListModel)
        {
            vector<SSearchDeviceInfo> objNewList = m_pPhConnMgrResource->getDeviceSearchList();
            int iSize = static_cast<int>(objNewList.size());

            //! add newly found devices
            for(int iIndex = 0; iIndex < iSize; iIndex++)
            {
                bool bNewDeviceFound = true;
                CPhoneData::SDeviceInfo objNewDeviceInfo;

                objNewDeviceInfo.m_strName          = QString::fromStdString(objNewList.at(iIndex).m_strDeviceName);
                objNewDeviceInfo.m_strDeviceBtAddr  = QString::fromStdString(objNewList.at(iIndex).m_strDeviceBtAddr);

                for(int iIndex = 0, iSize = m_pDeviceSearchListModel->rowCount(); iIndex < iSize; iIndex++)
                {
                    QString strDeviceName = m_pDeviceSearchListModel->getNameFromIndex(iIndex);
                    QString strDeviceAddr = m_pDeviceSearchListModel->getAddrFromIndex(iIndex);

                    if ((objNewDeviceInfo.m_strDeviceBtAddr == strDeviceAddr) && (objNewDeviceInfo.m_strName  == strDeviceName))
                    {
                        bNewDeviceFound = false;
                        break;
                    }
                }
                if (bNewDeviceFound)
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: adding new device: NewDeviceName: %s, NewDeviceBTAddress: %s", __FUNCTION__,
                             objNewDeviceInfo.m_strName.toStdString().c_str(), objNewDeviceInfo.m_strDeviceBtAddr.toStdString().c_str());
                    m_pDeviceSearchListModel->insertRows(objNewDeviceInfo);
                }
            }

            //! remove old device if not in the new list
            bool bOldDeviceFound = false;
            do
            {
                for(int iIndex = 0, iOldeListSize = m_pDeviceSearchListModel->rowCount(); iIndex < iOldeListSize; iIndex++)
                {
                    bOldDeviceFound = false;
                    QString strDeviceName = m_pDeviceSearchListModel->getNameFromIndex(iIndex);
                    QString strDeviceAddr = m_pDeviceSearchListModel->getAddrFromIndex(iIndex);

                    int iNewListSize = static_cast<int>(objNewList.size());
                    for(int iNewIndex = 0; iNewIndex < iNewListSize; iNewIndex++)
                    {
                        QString strNewDeviceName = QString::fromStdString(objNewList.at(iNewIndex).m_strDeviceName);
                        QString strNewDeviceAddr = QString::fromStdString(objNewList.at(iNewIndex).m_strDeviceBtAddr);

                        if ((strNewDeviceAddr == strDeviceAddr) && (strNewDeviceName == strDeviceName))
                        {
                            bOldDeviceFound = true;
                            break;
                        }
                    }
                    if (!bOldDeviceFound)
                    {
                        m_pDeviceSearchListModel->removeRow(iIndex);
                        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s removing device name:%s, Addr:%s", __FUNCTION__, strDeviceName.toStdString().c_str(), strDeviceAddr.toStdString().c_str());
                        break;
                    }
                    bOldDeviceFound = false;
                }
            }
            while (bOldDeviceFound);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: device search list model object not created", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: connection manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::updateConnectedDeviceList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pPhConnMgrResource)
    {
        int iSize = static_cast<int>(m_pPhConnMgrResource->getConnectedDeviceList().size());
        //Currently only one device can be connected and hence not checking bt address and straight away asigning the values
        for(int iIndex = 0; iIndex < iSize; iIndex++)
        {
            if(m_pPhConnMgrResource->getConnectedDeviceList().at(iIndex).m_mapProfileInfoList.count(PROFILE_TYPE_HFPGW) > 0)
            {
                EConnectionStatus eHFPConnectionStatus = m_pPhConnMgrResource->getBondedDeviceList().at(iIndex).m_mapProfileInfoList.at(PROFILE_TYPE_HFPGW).m_eConnectionStatus;
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: HFP connection status is: %d", __FUNCTION__, eHFPConnectionStatus);
                setHFPConnectionStatusType(eHFPConnectionStatus);
            }
            else
            {
                //do nothing
            }

            if(m_pPhConnMgrResource->getConnectedDeviceList().at(iIndex).m_mapProfileInfoList.count(PROFILE_TYPE_A2DP) > 0)
            {
                EConnectionStatus eA2DPConnectionStatus = m_pPhConnMgrResource->getBondedDeviceList().at(iIndex).m_mapProfileInfoList.at(PROFILE_TYPE_A2DP).m_eConnectionStatus;
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: A2DP connection status is: %d", __FUNCTION__, eA2DPConnectionStatus);
                setA2DPConnectionStatusType(eA2DPConnectionStatus);
            }
            else
            {
                //do nothing
            }
        }
    }
}

void CPhoneAdaptor::resetDeleteAllDevicesSelStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_bIsDeleteAllSelected = false;
}

void CPhoneAdaptor::updateBondedDeviceList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    bool bConnectionStatus          = false;
    QString strConnectedDeviceName  = "";

    if(m_pPhConnMgrResource)
    {
        if(m_pPairedDeviceListModel)
        {
            int iSize = static_cast<int>(m_pPhConnMgrResource->getBondedDeviceList().size());


            //Show delete all success popup if delete all was selected and bonded device list is empty
            if(m_bIsDeleteAllSelected && (iSize == 0))
            {
                m_bDeleteAllDevicesStatus = true;
                //Close all connecting/diconnecting/connected/disconnected popups here if already displayed or in the queue
                closeAllPhoneBtPopups();
                //Close deleting all device popup
                CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETING_ALL_DEVICES);
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: delete all device is selected", __FUNCTION__);
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: delete all option is not selected", __FUNCTION__);
            }

            //Insert pair new device item in the list
            QList<CPhoneData::SPairedDeviceInfo>    listPairedDevices;
            CPhoneData::SPairedDeviceInfo objPairNewDeviceItem;
            objPairNewDeviceItem.m_eItemType = CPhoneEnum::ITEM_TYPE_LABEL_WITH_BUTTON;
            listPairedDevices.append(objPairNewDeviceItem);

            EConnectionStatus eHFPConnectionStatus  = CONNECTION_STATUS_DISCONNECTED;
            EConnectionStatus eA2DPConnectionStatus = CONNECTION_STATUS_DISCONNECTED;

            for(int iIndex = 0; iIndex < iSize; iIndex++)
            {
                CPhoneData::SPairedDeviceInfo objPairedDeviceInfo;
                QString strDeviceIndex                  = QString("Device") + QString::number(iIndex);
                objPairedDeviceInfo.m_strName           = QString::fromStdString(m_pPhConnMgrResource->getBondedDeviceList().at(iIndex).m_strDeviceName);
                objPairedDeviceInfo.m_strDeviceBtAddr   = QString::fromStdString(m_pPhConnMgrResource->getBondedDeviceList().at(iIndex).m_strDeviceBtAddr);
                objPairedDeviceInfo.m_eItemType         = CPhoneEnum::ITEM_TYPE_ICON_WITH_BUTTON;
                if((m_pPhConnMgrResource->getBondedDeviceList().at(iIndex).m_mapProfileInfoList.count(PROFILE_TYPE_HFPGW) > 0) &&
                        (m_pPhConnMgrResource->getBondedDeviceList().at(iIndex).m_mapProfileInfoList.at(PROFILE_TYPE_HFPGW).m_eConnectionStatus == CONNECTION_STATUS_CONNECTED))
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: PROFILE_TYPE_HFPGW is connected", __FUNCTION__);
                    objPairedDeviceInfo.m_bDeviceConnectionStatus   = true;
                    bConnectionStatus                               = true;
                    strConnectedDeviceName                          = objPairedDeviceInfo.m_strName;
                    eHFPConnectionStatus                            = CONNECTION_STATUS_CONNECTED;
                    if(m_strConnectedDeviceAddr.compare(objPairedDeviceInfo.m_strDeviceBtAddr) != 0)
                    {
                        //Open session for communication for receiving pimdb updates or requesting db data
                        m_pPhPimDbResource->openSessionAsyncReq(objPairedDeviceInfo.m_strDeviceBtAddr.toStdString());
                        m_strConnectedDeviceAddr = objPairedDeviceInfo.m_strDeviceBtAddr;
                        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: db session is not opened", __FUNCTION__);
                    }
                    else
                    {
                        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: db session already opened", __FUNCTION__);
                    }
                }
                else if((m_pPhConnMgrResource->getBondedDeviceList().at(iIndex).m_mapProfileInfoList.count(PROFILE_TYPE_A2DP) > 0) &&
                        (m_pPhConnMgrResource->getBondedDeviceList().at(iIndex).m_mapProfileInfoList.at(PROFILE_TYPE_A2DP).m_eConnectionStatus == CONNECTION_STATUS_CONNECTED))
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: PROFILE_TYPE_A2DP is connected", __FUNCTION__);
                    objPairedDeviceInfo.m_bDeviceConnectionStatus   = true;
                    bConnectionStatus                               = true;
                    strConnectedDeviceName                          = objPairedDeviceInfo.m_strName;
                    eA2DPConnectionStatus                           = CONNECTION_STATUS_CONNECTED;
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: profile type not handled for CONNECTION_STATUS_CONNECTED", __FUNCTION__);
                }

                if((m_pPhConnMgrResource->getBondedDeviceList().at(iIndex).m_mapProfileInfoList.count(PROFILE_TYPE_HFPGW) > 0) &&
                        (m_pPhConnMgrResource->getBondedDeviceList().at(iIndex).m_mapProfileInfoList.at(PROFILE_TYPE_HFPGW).m_eConnectionStatus == CONNECTION_STATUS_DISCONNECTED))
                {
                    if(m_strConnectedDeviceAddr.compare(objPairedDeviceInfo.m_strDeviceBtAddr) == 0)
                    {
                        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: connected device bt address matches with received bt address, reset hfp data", __FUNCTION__);
                        resetHFPData();
                    }
                    else
                    {
                        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: connected device bt address does not match with received bt address", __FUNCTION__);
                    }
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: profile type not handled for CONNECTION_STATUS_DISCONNECTED", __FUNCTION__);
                }

                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: , DeviceName: %s, DeviceBTAddress: %s, ItemType: %d",
                         strDeviceIndex.toStdString().c_str(),
                         objPairedDeviceInfo.m_strName.toStdString().c_str(),
                         objPairedDeviceInfo.m_strDeviceBtAddr.toStdString().c_str(),
                         objPairedDeviceInfo.m_eItemType);
                listPairedDevices.append(objPairedDeviceInfo);
            }
            setConnectedDeviceName(strConnectedDeviceName);
            setDeviceConnectionStatus(bConnectionStatus);
            setHFPConnectionStatusType(eHFPConnectionStatus);
            setA2DPConnectionStatusType(eA2DPConnectionStatus);

            //If paired device list contains atleast one paired device then add delete all option
            if(iSize > 1)
            {
                CPhoneData::SPairedDeviceInfo objPairedDeviceInfo;
                objPairedDeviceInfo.m_eItemType = CPhoneEnum::ITEM_TYPE_LABEL;
                listPairedDevices.append (objPairedDeviceInfo);
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: paired device list is not empty", __FUNCTION__);
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: paired device list is empty", __FUNCTION__);
            }
            m_iPreviousPairedListCount = m_iCurrentPairedListCount;
            m_pPairedDeviceListModel->removeRows();
            m_iCurrentPairedListCount = listPairedDevices.count();
            m_pPairedDeviceListModel->insertRows(listPairedDevices);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: paired device list model object not created", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: connection manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::updateBondingStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pPhConnMgrResource && CPopupManager::getInstance())
    {
        EPairingStatus ePairingStatus = m_pPhConnMgrResource->getDeviceBondingStatus().m_ePairingStatus;
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: PairingStatus is: %d",__FUNCTION__, ePairingStatus);
        switch(ePairingStatus)
        {
        case PAIRING_STATUS_SUCCESS:
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: pairing is success", __FUNCTION__);
            //Close all connecting/diconnecting/connected/disconnected popups here if already displayed or in the queue
            closeAllPhoneBtPopups();
            //Close passkey popup
            CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_PASSKEY);
            //Show determining bt services popup
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DETERMINING_BT_SERVICES);
            //Emit signal if pairing is successful
            emit sigExitPairNewDeviceScreen();
        }
            break;
        case PAIRING_STATUS_FAILURE:
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: pairing is failed", __FUNCTION__);
            //Close all connecting/diconnecting/connected/disconnected popups here if already displayed or in the queue
            closeAllPhoneBtPopups();
            //Close passkey popup
            CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_PASSKEY);
            //Close external passkey popup
            CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_EXTERNAL_PAIRING_REQUEST);
            //Show connection failed popup
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTION_FAILED);
            //Emit signal if pairing fails
            emit sigExitPairNewDeviceScreen();
        }
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: operation on pairing status received is not handled", __FUNCTION__);
            break;
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: connection manager resource object or popup manager object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::updateBondingRequest()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, " %s  bondReq %d ", __FUNCTION__, CAndroidAutoAdaptor::getInstance()->androidAutoBondReqStatus());

	//This condition handles the situation when android auto is connected and the mode status is ACTIVATING then pass key popup should not be displayed
    if (CAndroidAutoAdaptor::getInstance()->androidAutoConnectionStatus() ||
        true == (CAndroidAutoAdaptor::getInstance()->androidAutoBondReqStatus()))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "AndroidAuto is connected, No need to"
                                           " show, Pairing request and passkey"
                                           " popups.");
    }
    else if(m_pPhConnMgrResource && CPopupManager::getInstance() && m_pPairedDeviceListModel)

    {
        /*
         * If paired devices count is grater than the supported paired device count then show popup that
         * device limit has reached other wise proceed with pairing flow.
         */
        if(isMaxDeviceLimitReached())
        {
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DEVICE_LIMIT_REACHED);
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Maximum paired devices limit reached", __FUNCTION__);
        }
        else
        {
            updatePassKey(m_pPhConnMgrResource->getBondingRequest().m_strPasskey);
            if(m_strSelItemBtAddr.compare(QString::fromStdString(m_pPhConnMgrResource->getBondingRequest().m_strDeviceBtAddr)) == 0)
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: pairing initaited from HU", __FUNCTION__);
                //Show passkey popup for pairing initiated from HU
                invSetSelectedItemInfo(QString::fromStdString(m_pPhConnMgrResource->getBondingRequest().m_strDeviceName),
                                       QString::fromStdString(m_pPhConnMgrResource->getBondingRequest().m_strDeviceBtAddr));
                //Close connecting popup
                CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTING);
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_PASSKEY);
                invBondingReply(true, true);
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "external pairing requested");
                //External pairing request from remote phone
                invSetSelectedItemInfo(QString::fromStdString(m_pPhConnMgrResource->getBondingRequest().m_strDeviceName),
                                       QString::fromStdString(m_pPhConnMgrResource->getBondingRequest().m_strDeviceBtAddr));
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_EXTERNAL_PAIRING_REQUEST);
            }
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: connection manager resource object or popup manager object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::updateServiceConnectionStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pPhConnMgrResource && CPopupManager::getInstance())
    {
        ESupportedProfile _eSupportedProfile    = m_pPhConnMgrResource->getServiceConnectionStatus().m_eSupportedProfile;
        EConnectionStatus _eConnectionStatus    = m_pPhConnMgrResource->getServiceConnectionStatus().m_eConnectionStatus;
        QString strDeviceName                   = QString::fromStdString(m_pPhConnMgrResource->getServiceConnectionStatus().m_strDeviceName);
        QString strDeviceAddress                = QString::fromStdString(m_pPhConnMgrResource->getServiceConnectionStatus().m_strDeviceBtAddr);

        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: DeviceName : %s, DeviceAddress : %s, SupportedProfile : %d, ConnectionStatus : %d",
                 __FUNCTION__, strDeviceName.toStdString().c_str(), strDeviceAddress.toStdString().c_str(), _eSupportedProfile, _eConnectionStatus);

        if((_eSupportedProfile == PROFILE_TYPE_A2DP) || (_eSupportedProfile == PROFILE_TYPE_HFPGW))
        {
            if(_eSupportedProfile == PROFILE_TYPE_HFPGW)
            {
                setHFPConnectionStatusType(_eConnectionStatus);
            }
            else
            {
                setA2DPConnectionStatusType(_eConnectionStatus);
            }
            /*
             * connection status condition is checked to handle only connected,disconnected and connection_error scenarios,
             * as there are other connection states which are also received from service and currently we do not need to
             * handle them.
             */
            switch (_eConnectionStatus)
            {
            case CONNECTION_STATUS_CONNECTING:
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: CONNECTION_STATUS_CONNECTING", __FUNCTION__);
            }
                break;
            case CONNECTION_STATUS_CONNECTED:
            {
                //Both HFP and A2DP profile connected
                if((getHFPConnectionStatusType() == CONNECTION_STATUS_CONNECTED) && (getA2DPConnectionStatusType() == CONNECTION_STATUS_CONNECTED))
                {
                    //Close disconnecting popup
                    CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DISCONNECTING);

                    //Close connecting popup
                    CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTING);

                    /*
                     * Open the session for database queries whenever device is connected for hfp profile. It can happen
                     * that first a2dp connection is received and after that hfp connection is received, in that scenario
                     * this condition will be executed.
                     */
                    if(m_strConnectedDeviceAddr.compare(strDeviceAddress) != 0)
                    {
                        //Open session for communication for receiving pimdb updates or requesting db data
                        m_pPhPimDbResource->openSessionAsyncReq(strDeviceAddress.toStdString());
                        m_strConnectedDeviceAddr = strDeviceAddress;
                    }

                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Both HFP and A2DP profiles are connected");
                }
                //Only HFP profile connected
                else if(getHFPConnectionStatusType() == CONNECTION_STATUS_CONNECTED)
                {
                    setConnectedDeviceName(strDeviceName);
                    setDeviceConnectionStatus(true);
                    setDisconnectedDeviceName("");
                    if(m_strConnectedDeviceAddr.compare(strDeviceAddress) != 0)
                    {
                        //Open session for communication for receiving pimdb updates or requesting db data
                        m_pPhPimDbResource->openSessionAsyncReq(strDeviceAddress.toStdString());
                        m_strConnectedDeviceAddr = strDeviceAddress;
                    }
                    //Close connecting popup
                    CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTING);
                    //Close determining bluetooth services popup
                    CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DETERMINING_BT_SERVICES);
                    //Show device connected popup
                    CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTED);
                    //Emit signal if pairing/connection is successful
                    emit sigExitPairNewDeviceScreen();
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "HFP is connected");
                }
                //Only A2DP profile connected
                else if(getA2DPConnectionStatusType() == CONNECTION_STATUS_CONNECTED)
                {
                    setConnectedDeviceName(strDeviceName);
                    setDisconnectedDeviceName("");
                    setDeviceConnectionStatus(true);
                    //Close connecting popup
                    CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTING);
                    //Close determining bluetooth services popup
                    CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DETERMINING_BT_SERVICES);
                    //Show device connected popup
                    CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTED);
                    //Emit signal if pairing/connection is successful
                    emit sigExitPairNewDeviceScreen();
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "A2DP is connected");
                }
                else
                {
                    ////code part that should never trigger
                    LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s, %d, %d, If your reading this somthing is wrong with CONNECTION_STATUS_CONNECTED!", __FUNCTION__, getHFPConnectionStatusType(), getA2DPConnectionStatusType());
                }
            }
                break;
            case CONNECTION_STATUS_DISCONNECTING:
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: CONNECTION_STATUS_DISCONNECTING", __FUNCTION__);
            }
                break;
            case CONNECTION_STATUS_DISCONNECTED:
            {
                bool bDeviceDisconnected = false;
                if(_eSupportedProfile == PROFILE_TYPE_HFPGW)
                {
                    //Only HFP profile disconnected
                    if(getHFPConnectionStatusType() == CONNECTION_STATUS_DISCONNECTED)
                    {
                        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Only HFP is disconnected");                        

                        if((getA2DPConnectionStatusType() == CONNECTION_STATUS_DISCONNECTED) ||
                                (getA2DPConnectionStatusType() == CONNECTION_STATUS_CONNECTERROR) ||
                                (getA2DPConnectionStatusType() == CONNECTION_STATUS_NOT_SUPPORTED) ||
                                (getA2DPConnectionStatusType() == CONNECTION_STATUS_DEFAULT))
                        {
                            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "A2DP consider as disconnected : %d", getA2DPConnectionStatusType());
                            bDeviceDisconnected = true;
                        }
                    }
                }
                else if(getA2DPConnectionStatusType() == CONNECTION_STATUS_DISCONNECTED)
                {
                    //Only A2DP Disconnected
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Only A2DP is disconnected");

                    if((getHFPConnectionStatusType() == CONNECTION_STATUS_DISCONNECTED) ||
                            (getHFPConnectionStatusType() == CONNECTION_STATUS_CONNECTERROR) ||
                            (getHFPConnectionStatusType() == CONNECTION_STATUS_NOT_SUPPORTED) ||
                            (getHFPConnectionStatusType() == CONNECTION_STATUS_DEFAULT))
                    {
                        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "HFP consider as disconnected : %d", getHFPConnectionStatusType());
                        bDeviceDisconnected = true;
                    }
                }
                else
                {
                    //do nothing
                }

                if (bDeviceDisconnected)
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"[KPI_MARKER][HMI][ Bluetooth Disconnected]");
                    setConnectedDeviceName("");
                    setDisconnectedDeviceName(strDeviceName);
                    setDeviceConnectionStatus(false);
                    //Close disconnecting popup
                    CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DISCONNECTING);
                    //Show device disconnected popup only if AppleCarPlay connection status is false
                    if(!CAppleCarPlayAdaptor::getInstance()->appleCarPlayConnectionStatus())
                    {
                        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DISCONNECTED);
                    }
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Both HFP and A2DP profiles are disconnected");
                }
                else
                {
                    //do nothing
                }
            }
                break;
            case CONNECTION_STATUS_CONNECTERROR:
            {
                //Both HFP and A2DP profile connection error
                if((getHFPConnectionStatusType() == CONNECTION_STATUS_CONNECTERROR) && (getA2DPConnectionStatusType() == CONNECTION_STATUS_CONNECTERROR))
                {
                    setConnectedDeviceName("");
                    setDisconnectedDeviceName("");
                    setDeviceConnectionStatus(false);

                    //Close connecting popup
                    CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTING);
                    //Close determining bluetooth services popup
                    CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DETERMINING_BT_SERVICES);
                    //Show connection failed popup
                    CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTION_FAILED);

                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Both HFP and A2DP profiles connection errors");
                }
                //Only HFP profile connection error
                else if(getHFPConnectionStatusType() == CONNECTION_STATUS_CONNECTERROR)
                {
                    //Close disconnecting popup
                    CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DISCONNECTING);
                    //Reset all phone related information to default whenever there is connection error for hfp profile.
                    resetPhoneInformation();
                    //Reset sms details info
                    resetSMSDetails();
                    //Reset reading sms details
                    resetReadingSMSDetails();
                    //Reset pimdb related properties
                    resetPimdbProperties();
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Only HFP profile connection error");
                }
                //Only A2DP profile connection error
                else if(getA2DPConnectionStatusType() == CONNECTION_STATUS_CONNECTERROR)
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Only A2DP profile connection error");
                    //Close disconnecting popup
                    CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DISCONNECTING);
                }
                else
                {
                    ////code part that should never trigger
                    LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s, %d, %d, If your reading this somthing is wrong with CONNECTION_STATUS_CONNECTERROR!", __FUNCTION__, getHFPConnectionStatusType(), getA2DPConnectionStatusType());
                }
            }
                break;
            case CONNECTION_STATUS_NOT_SUPPORTED:
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: CONNECTION_STATUS_NOT_SUPPORTED", __FUNCTION__);
            }
                break;
            case CONNECTION_STATUS_DEFAULT:
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: CONNECTION_STATUS_DEFAULT", __FUNCTION__);
            }
                break;
            default:
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: connection status not handled", __FUNCTION__);
            }
                break;
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: connection status update for profiles other than HFP and A2DP", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: connection manager resource object or popup manager object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::updateDeviceDeletedStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    //If delete all device is not selected then only proceed further to delete device success popup
    if(!m_bIsDeleteAllSelected)
    {
        if(m_pPhConnMgrResource && CPopupManager::getInstance())
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Deleted device name: \'%s\'",m_pPhConnMgrResource->getDeviceDeleted().m_strDeviceName.c_str());
            m_bDeleteDeviceStatus = true;
            setDeletedDeviceName(QString::fromStdString(m_pPhConnMgrResource->getDeviceDeleted().m_strDeviceName));
            //close connecting/disconnecting/connected/disconnected bt popups if already displayed or in the queue
            closeAllPhoneBtPopups();
            //Close deleting device popup
            CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETING_DEVICE);
            //Reset selected device info
            invResetSelectedItemInfo();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: connection manager resource object or popup manager object not created", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: delete all option is selected", __FUNCTION__);
    }
}

void CPhoneAdaptor::updateSetDiscoverableModeMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                              EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: method call status: %d, method call error type: %d",
             __FUNCTION__, eMethodCallStatus, eMethodCallErrorType);
    if((eMethodCallStatus != METHOD_CALL_STATUS_SUCCESS) || (eMethodCallErrorType != METHOD_CALL_ERROR_TYPE_SUCCESS))
    {
        /**
         * set discoverable method call failed, hence change the request status from true to false, as we are
         * disabling/enabling the bluetooth visibility option in the screen based on the enable state. If enable
         * state is true(request has been sent) then the bluetooth visibility option shall be disabled and vice versa.
         */
        setBtVisibilityReqStatus(false);
        m_pPhoneSetupListModel->setData(m_pPhoneSetupListModel->index(CPhoneEnum::PHONE_SETUP_BLUETOOTH_VISIBILITY, 0),
                                        (!getProjPhConnectionStatus()), CPhoneSetupListModel::PHONE_SETUP_ITEM_ENABLED_ROLE);
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "set discoverable method call failed");
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "set discoverable method call success");
    }
}

void CPhoneAdaptor::updateStartDeviceSearchMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                            EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: method call status: %d, method call error type: %d",
             __FUNCTION__, eMethodCallStatus, eMethodCallErrorType);
}

void CPhoneAdaptor::updateStopDeviceSearchMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                           EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: method call status: %d, method call error type: %d",
             __FUNCTION__, eMethodCallStatus, eMethodCallErrorType);
}

void CPhoneAdaptor::updateStartAllServiceConnectionMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                    EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: method call status: %d, method call error type: %d",
             __FUNCTION__, eMethodCallStatus, eMethodCallErrorType);
    if((eMethodCallStatus != METHOD_CALL_STATUS_SUCCESS) || (eMethodCallErrorType != METHOD_CALL_ERROR_TYPE_SUCCESS))
    {
        CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTING);
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, start all service connection method call failed", __FUNCTION__);
        //Clear selected item info after getting the response
        invResetSelectedItemInfo();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, start all service connection method call success", __FUNCTION__);
    }
}

void CPhoneAdaptor::updateStartServiceConnectionMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                 EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: method call status: %d, method call error type: %d",
             __FUNCTION__, eMethodCallStatus, eMethodCallErrorType);
}

void CPhoneAdaptor::updateBondingReplyMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                       EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: method call status: %d, method call error type: %d",
             __FUNCTION__, eMethodCallStatus, eMethodCallErrorType);
    if((eMethodCallStatus != METHOD_CALL_STATUS_SUCCESS) || (eMethodCallErrorType != METHOD_CALL_ERROR_TYPE_SUCCESS))
    {
        CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTING);
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "bonding reply method call failed");
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "bonding reply method call success");
    }
}

void CPhoneAdaptor::updateDeleteDeviceMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                       EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: method call status: %d, method call error type: %d",
             __FUNCTION__, eMethodCallStatus, eMethodCallErrorType);
    if((eMethodCallStatus != METHOD_CALL_STATUS_SUCCESS) || (eMethodCallErrorType != METHOD_CALL_ERROR_TYPE_SUCCESS))
    {
        m_bDeleteDeviceStatus = false;
        //close connecting/disconnecting/connected/disconnected bt popups if already displayed or in the queue
        closeAllPhoneBtPopups();
        //Close deleting device popup
        CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETING_DEVICE);
        //Reset selected device info
        invResetSelectedItemInfo();
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Delete device method call status failed");
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Delete device method call status success");
    }
}

void CPhoneAdaptor::updateDeleteAllDevicesMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                           EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: method call status: %d, method call error type: %d",
             __FUNCTION__, eMethodCallStatus, eMethodCallErrorType);
    if((eMethodCallStatus != METHOD_CALL_STATUS_SUCCESS) || (eMethodCallErrorType != METHOD_CALL_ERROR_TYPE_SUCCESS))
    {
        resetDeleteAllDevicesSelStatus();
        m_bDeleteAllDevicesStatus = false;
        //Close all connecting/diconnecting/connected/disconnected popups here if already displayed or in the queue
        closeAllPhoneBtPopups();
        //Close deleting all device popup
        CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETING_ALL_DEVICES);

        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Delete all device method call status fail");
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Delete all device method call status success");
    }

}

void CPhoneAdaptor::updateStartAllServiceDisconnectionMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                       EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: method call status: %d, method call error type: %d",
             __FUNCTION__, eMethodCallStatus, eMethodCallErrorType);
    if((eMethodCallStatus != METHOD_CALL_STATUS_SUCCESS) || (eMethodCallErrorType != METHOD_CALL_ERROR_TYPE_SUCCESS))
    {
        CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DISCONNECTING);
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, start all service disconnection method call failed", __FUNCTION__);
        //Clear selected item info after getting the response
        invResetSelectedItemInfo();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, start all service disconnection method call success", __FUNCTION__);
    }
}

void CPhoneAdaptor::updateStartServiceDisconnectionMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                    EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: method call status: %d, method call error type: %d",
             __FUNCTION__, eMethodCallStatus, eMethodCallErrorType);
}

void CPhoneAdaptor::updateSetBluetoothStatusMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                             EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: method call status: %d, method call error type: %d",
             __FUNCTION__, eMethodCallStatus, eMethodCallErrorType);
}


/************************************************************************//**
 * @category    CONNECTION MANAGER RESOURCE LAYER METHODS
 * @brief       API's can be called directly from QML or from other
 *              Adaptor's
 ************************************************************************/

void CPhoneAdaptor::invSetDiscoverableMode(bool bEnable)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bEnable value is: %d", __FUNCTION__, bEnable);
    if(m_pPhConnMgrResource)
    {
        /**
         * bt visisbility request status has been sent to connection manager service, hence change the enable
         * state from false to true, as we are disabling/enabling the bluetooth visibility option in the screen
         * based on the enable state. If enable state is true(request has been sent) then the bluetooth visibility
         * option shall be disabled and vice versa.
         */
        setBtVisibilityReqStatus(true);
        m_pPhoneSetupListModel->setData(m_pPhoneSetupListModel->index(CPhoneEnum::PHONE_SETUP_BLUETOOTH_VISIBILITY, 0),
                                        false, CPhoneSetupListModel::PHONE_SETUP_ITEM_ENABLED_ROLE);
        m_pPhConnMgrResource->setDiscoverableModeAsyncReq(bEnable);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone connection manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::invStartAllServiceConnection(const QString strBtAddr)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: device bt address is: %s", __FUNCTION__, strBtAddr.toStdString().c_str());
    if(m_pPhConnMgrResource)
    {
        // Reset HFP and A2DP connection status
        setHFPConnectionStatusType(CONNECTION_STATUS_DEFAULT);
        setA2DPConnectionStatusType(CONNECTION_STATUS_DEFAULT);
        m_pPhConnMgrResource->startAllServiceConnectionAsyncReq(strBtAddr.toStdString());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone connection manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::invStartServiceConnection(const QString strBtAddr, bool bStartHFPConnection)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: device bt address is: %s, bStartHFPConnection: %d",
             __FUNCTION__, strBtAddr.toStdString().c_str(), bStartHFPConnection);
    if(m_pPhConnMgrResource)
    {
        ESupportedProfile eProfileType = PROFILE_TYPE_DEFAULT;
        if(bStartHFPConnection)
        {
            eProfileType = PROFILE_TYPE_HFPGW;
        }
        else
        {
            eProfileType = PROFILE_TYPE_A2DP;
        }
        m_pPhConnMgrResource->startServiceConnectionAsyncReq(strBtAddr.toStdString(), eProfileType);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone connection manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::invBondingReply(bool bAccepted, bool bSecureBonding)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: device bt address is: %s, pairing accepted: %d, secure bonding: %d",
             __FUNCTION__, selItemBtAddr().toStdString().c_str(), bAccepted, bSecureBonding);
    if(m_pPhConnMgrResource)
    {
        m_pPhConnMgrResource->bondingReplyAsyncReq(selItemBtAddr().toStdString(), bAccepted, bSecureBonding);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone connection manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::invDeleteDevice()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: device bt address is: %s",
             __FUNCTION__, selItemBtAddr().toStdString().c_str());
    if(m_pPhConnMgrResource)
    {
        m_pPhConnMgrResource->deleteDeviceAsyncReq(selItemBtAddr().toStdString());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone connection manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::invDeleteAllDevices()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pPhConnMgrResource)
    {
        m_bIsDeleteAllSelected = true;
        m_pPhConnMgrResource->deleteAllDevicesAsyncReq();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone connection manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::invStartAllServiceDisconnection(const QString strBtAddr)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: device bt address is: %s",
             __FUNCTION__, strBtAddr.toStdString().c_str());
    if(m_pPhConnMgrResource)
    {
        m_pPhConnMgrResource->startAllServiceDisconnectionAsyncReq(strBtAddr.toStdString());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone connection manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::invStartServiceDisconnection(const QString strBtAddr, bool bStartHFPDisconnection)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: device bt address is: %s, bStartHFPDisconnection: %d",
             __FUNCTION__, strBtAddr.toStdString().c_str(), bStartHFPDisconnection);
    if(m_pPhConnMgrResource)
    {
        ESupportedProfile eProfileType = PROFILE_TYPE_DEFAULT;
        if(bStartHFPDisconnection)
        {
            eProfileType = PROFILE_TYPE_HFPGW;
        }
        else
        {
            eProfileType = PROFILE_TYPE_A2DP;
        }
        m_pPhConnMgrResource->startServiceDisconnectionAsyncReq(strBtAddr.toStdString(), eProfileType);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone connection manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::invSetSelectedItemInfo(const QString strName, const QString strBtAddr)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: selected device name is: %s, selected device bt address is: %s",
             __FUNCTION__, strName.toStdString().c_str(), strBtAddr.toStdString().c_str());
    m_strSelItemName    = strName;
    m_strSelItemBtAddr  = strBtAddr;
}

void CPhoneAdaptor::invExternalPairingRejected()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    invResetSelectedItemInfo();
}

void CPhoneAdaptor::invSwitchToPhoneBrowse(CPhoneEnum::EPhoneBrowseType ePhoneBrowseType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_eHFPConnectionStatus == CONNECTION_STATUS_CONNECTED)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: switiching to phone browse, phone browse type is : %d", __FUNCTION__, ePhoneBrowseType);
        CHMIMain::getSM()->raise_evPhoneBrowseActivated(ePhoneBrowseType);
    }
    else
    {
        if(m_eA2DPConnectionStatus == CONNECTION_STATUS_CONNECTED)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Hfp profile is not connected. A2dp is connected", __FUNCTION__);
            if(CPopupManager::getInstance())
            {
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_ONLY_A2DP_CONNECTED);
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Popup manager not available", __FUNCTION__);
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: phone is not connected, switching to phone setup", __FUNCTION__);
            CHMIMain::getSM()->getSCI_Setup()->raise_evBluetoothSetupActivated(CHMIMain::getSM()->getDefaultSCI()->get_sETUP_SCR_BT_NAMED_ENTRY());
        }
    }
}

void CPhoneAdaptor::invSwitchToPairedDevices()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if((bluetoothStatus()) && (((CAndroidAutoAdaptor::getInstance()) && (!CAndroidAutoAdaptor::getInstance()->androidAutoConnectionStatus())) &&
                               ((CAppleCarPlayAdaptor::getInstance()) && (!CAppleCarPlayAdaptor::getInstance()->appleCarPlayConnectionStatus()))))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Bluetooth is enabled, Android auto and carplay is not connected: Switching to paired devices");
        CHMIMain::getSM()->getSCI_Setup()->raise_evBluetoothSetupActivated(CHMIMain::getSM()->getDefaultSCI()->get_sETUP_SCR_PAIRED_DEVICES_NAMED_ENTRY());
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Bluetooth is disabled or Android auto or carplay is connected: Switching to phone setup");
        CHMIMain::getSM()->getSCI_Setup()->raise_evBluetoothSetupActivated(CHMIMain::getSM()->getDefaultSCI()->get_sETUP_SCR_BT_NAMED_ENTRY());
    }
}

void CPhoneAdaptor::invSwitchToPairNewDevice()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    /*
     * If paired devices count is grater than the supported paired device count then show popup that
     * device limit has reached other wise show popup to turn on phone bluetooth visistibility.
     */
    if(m_pPhoneAdaptor->isMaxDeviceLimitReached())
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DEVICE_LIMIT_REACHED);
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Maximum paired devices limit reached", __FUNCTION__);
    }
    else
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_TURN_ON_BLUETOOTH);
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Showing popup turn on bluetooth", __FUNCTION__);
    }
}

/************************************************************************//**
 * @category    BT CONNECTION RELATED SETTERS
 ************************************************************************/
void CPhoneAdaptor::setConnectedDeviceName(const QString& strConnectedDeviceName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: connected device name is: %s",
             __FUNCTION__, strConnectedDeviceName.toStdString().c_str());
    if(strConnectedDeviceName.compare(m_strConnectedDeviceName) != 0)
    {
        m_strConnectedDeviceName = strConnectedDeviceName;
        emit sigConnectedDeviceNameUpdated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "connected device name not changed");
    }
}

void CPhoneAdaptor::setDeviceConnectionStatus(bool bDeviceConnectionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: device connection status is: %d", __FUNCTION__,
             bDeviceConnectionStatus);
    if(m_bIsDeviceConnected != bDeviceConnectionStatus)
    {
        m_bIsDeviceConnected = bDeviceConnectionStatus;
        emit sigDeviceConnectionUpdated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "device connection status not changed");
    }
}

void CPhoneAdaptor::setDisconnectedDeviceName(const QString& strDisonnectedDeviceName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: disconnected device name is: %s",
             __FUNCTION__, strDisonnectedDeviceName.toStdString().c_str());
    if(strDisonnectedDeviceName.compare(m_strDisconnectedDeviceName) != 0)
    {
        m_strDisconnectedDeviceName = strDisonnectedDeviceName;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "disconnected device name not changed");
    }
}

void CPhoneAdaptor::setDeletedDeviceName(const QString& strDeletedDeviceName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: deleted device name is: %s",
             __FUNCTION__, strDeletedDeviceName.toStdString().c_str());
    if(strDeletedDeviceName.compare(m_strDeletedDeviceName) != 0)
    {
        m_strDeletedDeviceName = strDeletedDeviceName;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "deleted device name not changed");
    }
}

void CPhoneAdaptor::setBtVisibilityReqStatus(bool bBtVisibilityReqStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bt visibility request status is: %d",
             __FUNCTION__, bBtVisibilityReqStatus);
    if(bBtVisibilityReqStatus != m_bBtVisibilityReqStatus)
    {
        m_bBtVisibilityReqStatus = bBtVisibilityReqStatus;
        emit sigBtVisibilityReqStatusUpdated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "bt visibility request status not changed");
    }
}


/************************************************************************//**
 * @category   PHONE CALL METHODS
 ************************************************************************/
void CPhoneAdaptor::callStateInfoUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pPhCallMgrResource && !m_pPhCallMgrResource->getCallStateInfoList().empty())
    {
        //Check whether the call state received is not PHONE_CALLSTATE_IDLE and source activated for bthfp or ringtone is received
        if(static_cast<CPhoneEnum::EPhoneCallState>(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_eHMICallState) != CPhoneEnum::PHONE_CALLSTATE_IDLE)
        {
            //Request display on
            CDisplayManagerAdaptor::getInstance()->reqDisplayOnOffFeature(false);
            /*
             * Update HMI call state property that shall be used by the QML. Currently we are getting the first index data
             * from the call state info list as we only support single device connection.
             */
            CPhoneEnum::EPhoneCallState ePhoneCallState = static_cast<CPhoneEnum::EPhoneCallState>(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_eHMICallState);

            if(ePhoneCallState != CPhoneEnum::PHONE_CALLSTATE_ALL_CALLS_TERMINATED)
            {
                CAudioEnums::ESourceState eHFPSourceState       = CAudioAdaptor::getInstance()->getSourceState(CAudioEnums::EN_INT_SOURCE_TEL_HANDSFREE);
                CAudioEnums::ESourceState eRingtoneSourceState  = CAudioAdaptor::getInstance()->getSourceState(CAudioEnums::EN_INT_SOURCE_TEL_RINGING);
                //If Ringtone source is activated then only show incoming call popup
                if((eRingtoneSourceState == CAudioEnums::EN_SOURCE_STATE_CONNECTED) && (ePhoneCallState == CPhoneEnum::PHONE_CALLSTATE_INCOMING_CALL))
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Ringtone source is connected", __FUNCTION__);
                    resetRequestStatusProperties();
                    showMicNotConnectedPopup();
                    updateIncomingCallInfo();
                    setPhoneCallState(ePhoneCallState);
                }
                //If HFP source is activated then only active call screen
                else if(eHFPSourceState == CAudioEnums::EN_SOURCE_STATE_CONNECTED)
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: HFP source is connected", __FUNCTION__);
                    /** Reset end call and dial request status to false whenever call state is received **/
                    setEndCallReqStatus(false);
                    setDialReqStatus(false);
                    showMicNotConnectedPopup();
                    //Load phone call screen based on call state
                    switch(ePhoneCallState)
                    {
                    //In case of Iphone and Nexus 6p, source HFP is activated for ringtone as the phone itself plays the ringtone(inband) and not the HU
                    case CPhoneEnum::PHONE_CALLSTATE_INCOMING_CALL:
                    {
                        resetRequestStatusProperties();
                        updateIncomingCallInfo();
                    }
                        break;
                    case CPhoneEnum::PHONE_CALLSTATE_ACTIVE_CALL_AND_INCOMING_CALL:
                    {
                        resetRequestStatusProperties();
                        updateSingleAndIncomingCallInfo(true);
                    }
                        break;
                    case CPhoneEnum::PHONE_CALLSTATE_HELD_CALL_AND_INCOMING_CALL:
                    {
                        resetRequestStatusProperties();
                        updateSingleAndIncomingCallInfo(false);
                    }
                        break;
                    case CPhoneEnum::PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_INCOMING_CALL:
                    {
                        resetRequestStatusProperties();
                        updateConferenceAndIncomingCallInfo(true);
                    }
                        break;
                    case CPhoneEnum::PHONE_CALLSTATE_CONFERENCE_ONHOLD_AND_INCOMING_CALL:
                    {
                        resetRequestStatusProperties();
                        updateConferenceAndIncomingCallInfo(false);
                    }
                        break;
                    case CPhoneEnum::PHONE_CALLSTATE_ACTIVE_CALL:
                        updateSingleCallInfo(true);                        
                        break;
                    case CPhoneEnum::PHONE_CALLSTATE_HELD_CALL:
                        updateSingleCallInfo(false);
                        break;
                    case CPhoneEnum::PHONE_CALLSTATE_ACTIVE_CALL_AND_HELD_CALL:
                        updateActiveAndHeldCallInfo();
                        break;
                    case CPhoneEnum::PHONE_CALLSTATE_ACTIVE_CALL_AND_CONFERENCE_ONHOLD:
                        updateSingleAndConferenceCallInfo(false);
                        break;
                    case CPhoneEnum::PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_HELD_CALL:
                        updateSingleAndConferenceCallInfo(true);
                        break;
                    case CPhoneEnum::PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE:
                        updateConferenceCallInfo(true);
                        break;
                    case CPhoneEnum::PHONE_CALLSTATE_CONFERENCE_ONHOLD:
                        updateConferenceCallInfo(false);
                        break;
                    case CPhoneEnum::PHONE_CALLSTATE_DIALING:
                        updateOutgoingCallInfo(true);
                        break;
                    case CPhoneEnum::PHONE_CALLSTATE_ALERTING:
                        updateOutgoingCallInfo(false);
                        break;
                    case CPhoneEnum::PHONE_CALLSTATE_ACTIVE_CALL_AND_DIALING:
                        updateSingleAndOutgoingCallInfo(true, true);
                        break;
                    case CPhoneEnum::PHONE_CALLSTATE_ACTIVE_CALL_AND_ALERTING:
                        updateSingleAndOutgoingCallInfo(true, false);
                        break;
                    case CPhoneEnum::PHONE_CALLSTATE_HELD_CALL_AND_DIALING:
                        updateSingleAndOutgoingCallInfo(false, true);
                        break;
                    case CPhoneEnum::PHONE_CALLSTATE_HELD_CALL_AND_ALERTING:
                        updateSingleAndOutgoingCallInfo(false, false);
                        break;
                    case CPhoneEnum::PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_DIALING:
                        updateConferenceAndOutgoingCallInfo(true, true);
                        break;
                    case CPhoneEnum::PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_ALERTING:
                        updateConferenceAndOutgoingCallInfo(true, false);
                        break;
                    case CPhoneEnum::PHONE_CALLSTATE_CONFERENCE_ONHOLD_AND_DIALING:
                        updateConferenceAndOutgoingCallInfo(false, true);
                        break;
                    case CPhoneEnum::PHONE_CALLSTATE_CONFERENCE_ONHOLD_AND_ALERTING:
                        updateConferenceAndOutgoingCallInfo(false, false);
                        break;
                    default:
                        break;
                    }
                    setPhoneCallState(ePhoneCallState);
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Neither Ringtone nor HFP source is active", __FUNCTION__);
                }
            }
            else
            {
                //HFP source activation is not checked to show end call screen beacuse without call active screen, call end screen should not be shown.
                if(CHMIMain::getSM()->getSCI_Phone()->get_bIsPhoneCallStateActivated())
                {
                    updateAllCallsTerminatedCallInfo();
                    setPhoneCallState(ePhoneCallState);
                }
                else
                {
                    if(CAudioAdaptor::getInstance())
                    {
                        CAudioEnums::ESourceState eRingtoneSourceState  = CAudioAdaptor::getInstance()->getSourceState(CAudioEnums::EN_INT_SOURCE_TEL_RINGING);
                        CAudioEnums::ESourceState eHfpSourceState       = CAudioAdaptor::getInstance()->getSourceState(CAudioEnums::EN_INT_SOURCE_TEL_HANDSFREE);
                        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: eRingtoneSourceState: %d, eHfpSourceState: %d", __FUNCTION__, eRingtoneSourceState, eHfpSourceState);
                        //In case of Iphone and Nexus 6p, source HFP is activated for ringtone as the phone itself plays the ringtone(inband) and not the HU
                        if((eRingtoneSourceState == CAudioEnums::EN_SOURCE_STATE_DISCONNECTED) ||
                                (eHfpSourceState == CAudioEnums::EN_SOURCE_STATE_DISCONNECTED))
                        {
                            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Ringing or hfp source is disconnected", __FUNCTION__);
                            ringtoneSourceDeactivated();
                        }
                        else if((eRingtoneSourceState != CAudioEnums::EN_SOURCE_STATE_UNKNOWN) ||
                                (eHfpSourceState != CAudioEnums::EN_SOURCE_STATE_UNKNOWN))
                        {
                            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Ringing or hfp source is not disconnected and not unknown", __FUNCTION__);
                            setPhoneCallState(ePhoneCallState);
                        }
                        else
                        {
                            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Ringing source is unknown", __FUNCTION__);
                        }
                    }
                    else
                    {
                        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Audio adaptor not available", __FUNCTION__);
                    }
                }
            }            
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone call manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::updateHfFeatures()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pPhCallMgrResource && !m_pPhCallMgrResource->getHfpSupportedFeatureList().empty() )
    {
        /*
         *  Currently we are getting the first index data from the network operator info list as
         *  we only support single device connection.
         */
        //Update the item in conference participant list based upon enhanced hangup feature
        bool bHangupEnhancedSupported = ((m_pPhCallMgrResource->getHfpSupportedFeatureList().at(0).m_mapSupportedFeatures.count(PHONE_FEATURE_HANGUP_ENH) > 0) &&
                                         (m_pPhCallMgrResource->getHfpSupportedFeatureList().at(0).m_mapSupportedFeatures.at(PHONE_FEATURE_HANGUP_ENH)));
        for(int iIndex = 0; iIndex < m_objConfParticipantsListModel.rowCount(); iIndex++)
        {
            m_objConfParticipantsListModel.updateConfParticipantListItem(iIndex, bHangupEnhancedSupported,
                                                                         CConfParticipantsListModel::END_PARTICIPANT_CALL_ROLE);
        }

        m_bBtVrSupported = ((m_pPhCallMgrResource->getHfpSupportedFeatureList().at(0).m_mapSupportedFeatures.count(PHONE_FEATURE_VR) > 0) &&
                            (m_pPhCallMgrResource->getHfpSupportedFeatureList().at(0).m_mapSupportedFeatures.at(PHONE_FEATURE_VR)));
        m_bApplePhoneConnected = ((m_pPhCallMgrResource->getHfpSupportedFeatureList().at(0).m_mapSupportedFeatures.count(PHONE_FEATURE_SIRI) > 0) &&
                             (m_pPhCallMgrResource->getHfpSupportedFeatureList().at(0).m_mapSupportedFeatures.at(PHONE_FEATURE_SIRI)));

        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: bHangupEnhancedSupported:%d, m_bBtVrSupported: %d, m_bApplePhoneConnected: %d",
                    __FUNCTION__, bHangupEnhancedSupported, m_bBtVrSupported, m_bApplePhoneConnected);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone call manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::updateOperatorInfoList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    /*
     *  Currently we are getting the first index data from the network operator info list as
     *  we only support single device connection.
     */

    if(m_pPhCallMgrResource && !m_pPhCallMgrResource->getNetworkOperatorInfoList().empty())
    {
        m_bIsNetworkAvailable = m_pPhCallMgrResource->getNetworkOperatorInfoList().at(0).m_bNetworkAvailability;
        m_ePhoneNetworkRegState= m_pPhCallMgrResource->getNetworkOperatorInfoList().at(0).m_ePhoneNetworkRegState;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone call manager resource object not created", __FUNCTION__);
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: m_bIsNetworkAvailable: %d, m_ePhoneNetworkRegState: %d",
             __FUNCTION__, m_bIsNetworkAvailable, m_ePhoneNetworkRegState);
}

void CPhoneAdaptor::updateRssiChargeInfo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pPhCallMgrResource && !m_pPhCallMgrResource->getSignalChargeInfoList().empty())
    {
        /*
         *  Currently we are getting the first index data from the signal charge info list as
         *  we only support single device connection.
         */
        ESignalLevel eSignalLevel =  NO_SIM_SIGNAL_LEVEL ;

        //if SIM card is not available the signal level will be sent invalid
        if(PHONE_NETWORK_REGSTATE_NOT_REGISTERED != m_ePhoneNetworkRegState)
        {
            eSignalLevel = m_pPhCallMgrResource->getSignalChargeInfoList().at(0).m_eSignalLevel;
        }

        setSignalStrength(eSignalLevel);
        setBatteryCharge(m_pPhCallMgrResource->getSignalChargeInfoList().at(0).m_eBatteryChargeLevel);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone call manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::updateHfModeStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    setHFModeReqStatus(false);
    if(m_pPhCallMgrResource && !m_pPhCallMgrResource->getHfModeStatusList().empty())
    {
        /*
         *  Currently we are getting the first index data from the hf mode status info list as
         *  we only support single device connection.
         */
        ECallAudioStatus eCallAudioStatus = m_pPhCallMgrResource->getHfModeStatusList().at(0).m_eCallAudioStatus;
        switch (eCallAudioStatus)
        {
        case CALL_AUDIOSTATUS_CONNECTED:
        {
            setHandsFreeModeStatus(true);
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, switched to handsfree mode 1", __FUNCTION__);
        }
            break;
        case CALL_AUDIOSTATUS_DISCONNECTED:
        {
            setHandsFreeModeStatus(false);
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, switched to private mode 0", __FUNCTION__);
        }
            break;
        default:
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s, HF toggle Fail with error:%d, using old status:%d", __FUNCTION__, eCallAudioStatus, handsFreeModeStatus());
        }
            break;
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone call manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::updateCallDuration()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pPhCallMgrResource && !m_pPhCallMgrResource->getCallDurationList().empty())
    {
        int iSize = static_cast<int>(m_pPhCallMgrResource->getCallDurationList().size());

        for(int iIndex = 0; iIndex < iSize; iIndex++)
        {
            int iCallId                  = m_pPhCallMgrResource->getCallDurationList().at(iIndex).m_iCallId;
            unsigned int uiCallDuration  = m_pPhCallMgrResource->getCallDurationList().at(iIndex).m_uiCallDuration;
            //Convert call duration received in time format
            QString strFormattedDuration = QDateTime::fromTime_t(uiCallDuration).toUTC().toString("hh:mm:ss");
            if(m_objFirstCallerInfo.invGetCallId() == iCallId)
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE," %s call id of first caller is: %d, setting call duration of first caller", __FUNCTION__, iCallId);
                m_objFirstCallerInfo.setCallDuration(strFormattedDuration);
            }
            else if(m_objSecondCallerInfo.invGetCallId() == iCallId)
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, " %s call id of second caller is: %d, setting call duration of second caller", __FUNCTION__, iCallId);
                m_objSecondCallerInfo.setCallDuration(strFormattedDuration);
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, " %s call id does not match", __FUNCTION__);
            }
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone call manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::updatePhoneBtVrModeStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(!CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus())
    {
        if(m_pPhCallMgrResource && !m_pPhCallMgrResource->getPhonebtVrModeStatusList().empty())
        {
            /*
             *  Currently we are getting the first index data from the phone bt vr mode status info list as
             *  we only support single device connection.
             */
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: m_strConnectedDeviceAddr: %s, deviceAddrreceived: %s, vrModeStatus: %d",
                     __FUNCTION__, m_strConnectedDeviceAddr.toStdString().c_str(), m_pPhCallMgrResource->getPhonebtVrModeStatusList().at(0).m_strDeviceBtAddr.c_str(),
                     m_pPhCallMgrResource->getPhonebtVrModeStatusList().at(0).m_bPhoneBtVrModeStatus);
            if(m_strConnectedDeviceAddr.toStdString() == m_pPhCallMgrResource->getPhonebtVrModeStatusList().at(0).m_strDeviceBtAddr)
            {
                m_bPhoneBtVrModeStatus = m_pPhCallMgrResource->getPhonebtVrModeStatusList().at(0).m_bPhoneBtVrModeStatus;
                showHidePhoneBtVROverlay(m_bPhoneBtVrModeStatus);
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: connected device bt address and received bt address does not match", __FUNCTION__);
            }
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone call manager resource object not created", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: reverse gear engaged, do not show bt vr overlay", __FUNCTION__);
    }
}

void CPhoneAdaptor::updateAcceptIncomingCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                  EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if((eMethodCallStatus != METHOD_CALL_STATUS_SUCCESS) || (eMethodCallErrorType != METHOD_CALL_ERROR_TYPE_SUCCESS))
    {
        setAcceptCallReqStatus(false);
    }
}

void CPhoneAdaptor::updateRejectIncomingCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                  EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if((eMethodCallStatus != METHOD_CALL_STATUS_SUCCESS) || (eMethodCallErrorType != METHOD_CALL_ERROR_TYPE_SUCCESS))
    {
        setRejectCallReqStatus(false);
    }
}

void CPhoneAdaptor::updateSendSMSAsyncMethodCallStatus(bool bIsSucessful)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, SMS status %d", __FUNCTION__, bIsSucessful);
    setSendSMSReqStatus(false);
}

void CPhoneAdaptor::updateDialAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                    EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if((eMethodCallStatus != METHOD_CALL_STATUS_SUCCESS) || (eMethodCallErrorType != METHOD_CALL_ERROR_TYPE_SUCCESS))
    {
        setDialReqStatus(false);
    }
}

void CPhoneAdaptor::updateConferenceCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                              EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if((eMethodCallStatus != METHOD_CALL_STATUS_SUCCESS) || (eMethodCallErrorType != METHOD_CALL_ERROR_TYPE_SUCCESS))
    {
        setMergeCallsReqStatus(false);
    }
}

void CPhoneAdaptor::updateSwapCallsAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                         EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if((eMethodCallStatus != METHOD_CALL_STATUS_SUCCESS) || (eMethodCallErrorType != METHOD_CALL_ERROR_TYPE_SUCCESS))
    {
        setSwapCallsReqStatus(false);
    }
}

void CPhoneAdaptor::updateResumeHeldCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                              EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if((eMethodCallStatus != METHOD_CALL_STATUS_SUCCESS) || (eMethodCallErrorType != METHOD_CALL_ERROR_TYPE_SUCCESS))
    {
        setResumeCallReqStatus(false);
    }
}

void CPhoneAdaptor::updateHoldActiveCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                              EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if((eMethodCallStatus != METHOD_CALL_STATUS_SUCCESS) || (eMethodCallErrorType != METHOD_CALL_ERROR_TYPE_SUCCESS))
    {
        setHoldCallReqStatus(false);
    }
}

void CPhoneAdaptor::updateEndCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                       EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if((eMethodCallStatus != METHOD_CALL_STATUS_SUCCESS) || (eMethodCallErrorType != METHOD_CALL_ERROR_TYPE_SUCCESS))
    {
        setEndCallReqStatus(false);
    }
}

void CPhoneAdaptor::updateEndActiveCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                             EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if((eMethodCallStatus != METHOD_CALL_STATUS_SUCCESS) || (eMethodCallErrorType != METHOD_CALL_ERROR_TYPE_SUCCESS))
    {
        setEndCallReqStatus(false);
    }
}

void CPhoneAdaptor::updateEndAllCallsAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                           EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if((eMethodCallStatus != METHOD_CALL_STATUS_SUCCESS) || (eMethodCallErrorType != METHOD_CALL_ERROR_TYPE_SUCCESS))
    {
        setEndCallReqStatus(false);
    }
}

void CPhoneAdaptor::updateSendDtmfToneAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                            EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    Q_UNUSED(eMethodCallStatus);
    Q_UNUSED(eMethodCallErrorType);
}

void CPhoneAdaptor::updateSetHfModeAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                         EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if((eMethodCallStatus != METHOD_CALL_STATUS_SUCCESS) || (eMethodCallErrorType != METHOD_CALL_ERROR_TYPE_SUCCESS))
    {
        setHFModeReqStatus(false);
    }
}

void CPhoneAdaptor::updateSetVRModeAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus, EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: eMethodCallStatus: %d, eMethodCallErrorType: %d", __FUNCTION__, eMethodCallStatus, eMethodCallErrorType);
    //Show popup(VR disabled) and activate native VR is error is received as METHOD_CALL_ERROR_TYPE_API_NOT_SUPPORTED
    if(eMethodCallErrorType == METHOD_CALL_ERROR_TYPE_API_NOT_SUPPORTED)
    {
        //TODO: Need to show popup that VR is not turned off
        CVRAdaptor::getInstance()->activateVRSession(CHardKeyEnum::HKEY_STATE_RELEASED);
    }
    else
    {
        //do nothing
    }
}

void CPhoneAdaptor::invUpdateSMSAlertNotification(int iItemId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: iItemId: %d", __FUNCTION__, iItemId);
    /** Writing SMSAlertNotification into persistency */
    CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_SETUP_SMS_NOTIFY_TYPE, iItemId);
    m_pPhoneSetupListModel->updateSmsAlertNotificationList ();
}

void CPhoneAdaptor::invUpdateConfigureAutoSms(int iItemId)
{

    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: iItemId: %d", __FUNCTION__, iItemId);
    /** Writing ConfigureAuto Sms selected option into persistency */
    CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_SETUP_SMS_CONFIGURE_SELECTION, iItemId);
    m_pPhoneSetupListModel->updateConfigAutoSmsList ();
}

void CPhoneAdaptor::invShowPopupNoDeviceFound()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if (m_ePhoneCallState == CPhoneEnum::PHONE_CALLSTATE_IDLE)
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_BT_DEVICES_NOT_FOUND);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, phone call is going on", __FUNCTION__);
        CHMIMain::getSM()->getSCI_Setup()->raise_evBluetoothSetupActivated(CHMIMain::getSM()->getDefaultSCI()->get_sETUP_SCR_BT_NAMED_ENTRY());
    }
}

/************************************************************************//**
 * @category    CALL MANAGER RESOURCE LAYER METHODS
 * @brief       API's can be called directly from QML or from other
 *              Adaptor's
 ************************************************************************/
void CPhoneAdaptor::invAcceptIncomingCall(bool bAcceptInHandsetMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bAcceptInHandsetMode is: %d", __FUNCTION__, bAcceptInHandsetMode);
    if(m_pPhCallMgrResource)
    {
        setAcceptCallReqStatus(true);
        m_pPhCallMgrResource->acceptIncomingCallAsyncReq(m_strConnectedDeviceAddr.toStdString(), bAcceptInHandsetMode);
        invToggleMicMute(CAudioAdaptor::getInstance()->micMuteStatus());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone call manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::invRejectIncomingCall()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pPhCallMgrResource)
    {
        setRejectCallReqStatus(true);
        m_pPhCallMgrResource->rejectIncomingCallAsyncReq(m_strConnectedDeviceAddr.toStdString());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone call manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::invRejectIncomingCallWithSMS()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if (m_pPhPimDbResource && (!sendSMSReqStatus()) && m_pPhoneSetupListModel)
    {
        setSendSMSReqStatus(true);
        if(CPopupManager::getInstance())
        {
            CAudioAdaptor::getInstance()->playBeep(CAudioEnums::BEEP_TYPE_CONFIRM);
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SENDING_SMS);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Popup manager not available", __FUNCTION__);
        }
        m_pPhPimDbResource->sendSMSAsyncReq(m_strConnectedDeviceAddr.toStdString(), m_objIncomingCallInfo.callerNumber().toStdString(), m_pPhoneSetupListModel->getConfiguredAutoSmsText().toStdString());
        invRejectIncomingCall();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone pimdb manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::sendSMS(const QString number, const QString SMSText)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if (m_pPhPimDbResource && (!sendSMSReqStatus()) && m_pPhoneSetupListModel)
    {
        if(m_strConnectedDeviceAddr != "")
        {
            setSendSMSReqStatus(true);
            m_pPhPimDbResource->sendSMSAsyncReq(m_strConnectedDeviceAddr.toStdString(), number.toStdString(), SMSText.toStdString());
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: no device connected", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone pimdb manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::invDial(QString strNumber, QString strName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: ,number to dial is: %s, contact name is: %s", __FUNCTION__,
             strNumber.toStdString().c_str(), strName.toStdString().c_str());
    if(m_bIsNetworkAvailable)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: network is available", __FUNCTION__);
        if(m_pPhCallMgrResource)
        {
            setDialReqStatus(true);
            m_pPhCallMgrResource->dialAsyncReq(m_strConnectedDeviceAddr.toStdString(), strNumber.toStdString(), strName.toStdString(),
                                               "", CONTACT_NUM_TELEPHONE_TYPE_DEFAULT);
            invToggleMicMute(CAudioAdaptor::getInstance()->micMuteStatus());
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone call manager resource object not created", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: network is not available", __FUNCTION__);
        //show popup that newtork is not available
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_NO_NETWORK_AVAILABLE);
    }
}

void CPhoneAdaptor::invConferenceCall()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pPhCallMgrResource)
    {
        setMergeCallsReqStatus(true);
        m_pPhCallMgrResource->conferenceCallAsyncReq(m_strConnectedDeviceAddr.toStdString());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone call manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::invSwapCalls()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pPhCallMgrResource)
    {
        setSwapCallsReqStatus(true);
        m_pPhCallMgrResource->swapCallsAsyncReq(m_strConnectedDeviceAddr.toStdString());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone call manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::invResumeHeldCall()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pPhCallMgrResource)
    {
        setResumeCallReqStatus(true);
        m_pPhCallMgrResource->resumeHeldCallAsyncReq(m_strConnectedDeviceAddr.toStdString());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone call manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::invHoldActiveCall()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pPhCallMgrResource)
    {
        setHoldCallReqStatus(true);
        m_pPhCallMgrResource->holdActiveCallAsyncReq(m_strConnectedDeviceAddr.toStdString());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone call manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::invToggleMicMute(bool bToggleMicMute)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bToggleMicMute is: %d", __FUNCTION__, bToggleMicMute);
    if(CAudioAdaptor::getInstance())
    {
        if(bToggleMicMute)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Toggle mic mute", __FUNCTION__);
            CAudioAdaptor::getInstance()->toggleMicMute();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Do not toggle mic mute", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Audio Adapter object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::invEndPhoneCall()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s , current phone call state : %d", __FUNCTION__, m_ePhoneCallState);

    switch(m_ePhoneCallState)
    {
    case CPhoneEnum::PHONE_CALLSTATE_ACTIVE_CALL:
    case CPhoneEnum::PHONE_CALLSTATE_ACTIVE_CALL_AND_HELD_CALL:
    case CPhoneEnum::PHONE_CALLSTATE_ACTIVE_CALL_AND_CONFERENCE_ONHOLD:
    case CPhoneEnum::PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_HELD_CALL:
        endActiveCall();
        break;
    case CPhoneEnum::PHONE_CALLSTATE_HELD_CALL:
    case CPhoneEnum::PHONE_CALLSTATE_DIALING:
    case CPhoneEnum::PHONE_CALLSTATE_ALERTING:
        invEndCall(firstCallerInfo()->invGetCallId());
        break;
    case CPhoneEnum::PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE:
    case CPhoneEnum::PHONE_CALLSTATE_CONFERENCE_ONHOLD:
        endAllCalls();
        break;
    case CPhoneEnum::PHONE_CALLSTATE_ACTIVE_CALL_AND_DIALING:
    case CPhoneEnum::PHONE_CALLSTATE_ACTIVE_CALL_AND_ALERTING:
    case CPhoneEnum::PHONE_CALLSTATE_HELD_CALL_AND_DIALING:
    case CPhoneEnum::PHONE_CALLSTATE_HELD_CALL_AND_ALERTING:
    case CPhoneEnum::PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_DIALING:
    case CPhoneEnum::PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_ALERTING:
    case CPhoneEnum::PHONE_CALLSTATE_CONFERENCE_ONHOLD_AND_DIALING:
    case CPhoneEnum::PHONE_CALLSTATE_CONFERENCE_ONHOLD_AND_ALERTING:
        invEndCall(secondCallerInfo()->invGetCallId());
        break;
    default:
        break;
    }
}

void CPhoneAdaptor::invEndCall(int iCallId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: iCallId is: %d", __FUNCTION__, iCallId);
    if(m_pPhCallMgrResource)
    {
        setEndCallReqStatus(true);
        m_pPhCallMgrResource->endCallAsyncReq(m_strConnectedDeviceAddr.toStdString(), iCallId);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone call manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::endActiveCall()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pPhCallMgrResource)
    {
        setEndCallReqStatus(true);
        m_pPhCallMgrResource->endActiveCallAsyncReq(m_strConnectedDeviceAddr.toStdString());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone call manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::endAllCalls()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pPhCallMgrResource)
    {
        setEndCallReqStatus(true);
        m_pPhCallMgrResource->endAllCallsAsyncReq(m_strConnectedDeviceAddr.toStdString());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone call manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::pimDbServiceAvailableStatusChanged(bool bPimDbServiceAvailableStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, bPimDbServiceAvailableStatus = %d", __FUNCTION__, bPimDbServiceAvailableStatus);
    if (!bPimDbServiceAvailableStatus)
    {
        LOG_ERROR(Log::e_LOG_CONTEXT_PHONE, "%s, !!! BT service CRASH, reseting phone adaptor data !!!!", __FUNCTION__);
        //Set bluetooth status as false so that pair new device, paired device, device visibility items can be disabled
        updateBluetoothStatus(false);
        resetPhoneAdaptor();
    }
    else
    {
        //Do Nothing
    }
}

void CPhoneAdaptor::invSendDtmfTone(const QString strDtmfTone)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: strDtmfTone is: %s", __FUNCTION__, strDtmfTone.toStdString().c_str());
    if(m_pPhCallMgrResource)
    {
        m_pPhCallMgrResource->sendDtmfToneAsyncReq(m_strConnectedDeviceAddr.toStdString(), strDtmfTone.toStdString());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone call manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::invSetHfMode(bool bHfMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bHfMode is: %d", __FUNCTION__, bHfMode);
    if(m_pPhCallMgrResource)
    {
        setHFModeReqStatus(true);
        m_pPhCallMgrResource->setHfModeAsyncReq(m_strConnectedDeviceAddr.toStdString(), bHfMode);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone call manager resource object not created", __FUNCTION__);
    }
}




/************************************************************************//**
 * @category    PHONE CALL PROPERTY RELATED SIGNALS
 ************************************************************************/
void CPhoneAdaptor::setAcceptCallReqStatus(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bStatus is: %d", __FUNCTION__, bStatus);
    if(m_bAcceptCallRequestStatus != bStatus)
    {
        m_bAcceptCallRequestStatus = bStatus;
        emit sigAcceptCallReqStatusUpdated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "value is unchanged");
    }
}

void CPhoneAdaptor::setRejectCallReqStatus(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bStatus is: %d", __FUNCTION__, bStatus);
    if(m_bRejectCallRequestStatus != bStatus)
    {
        m_bRejectCallRequestStatus = bStatus;
        emit sigRejectCallReqStatusUpdated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "value is unchanged");
    }
}

void CPhoneAdaptor::setSendSMSReqStatus(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bStatus is: %d", __FUNCTION__, bStatus);
    if(m_bSendSMSRequestStatus != bStatus)
    {
        m_bSendSMSRequestStatus = bStatus;
        emit sigSendSMSReqStatusUpdated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "value is unchanged");
    }
}

void CPhoneAdaptor::setDialReqStatus(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bStatus is: %d", __FUNCTION__, bStatus);
    if(m_bDialRequestStatus != bStatus)
    {
        m_bDialRequestStatus = bStatus;
        emit sigDialReqStatusUpdated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "value is unchanged");
    }
}

void CPhoneAdaptor::setMergeCallsReqStatus(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bStatus is: %d", __FUNCTION__, bStatus);
    if(m_bMergeCallsRequestStatus != bStatus)
    {
        m_bMergeCallsRequestStatus = bStatus;
        emit sigMergeCallsReqStatusUpdated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "value is unchanged");
    }
}

void CPhoneAdaptor::setSwapCallsReqStatus(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bStatus is: %d", __FUNCTION__, bStatus);
    if(m_bSwapCallRequestStatus != bStatus)
    {
        m_bSwapCallRequestStatus = bStatus;
        emit sigSwapCallsReqStatusUpdated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "value is unchanged");
    }
}

void CPhoneAdaptor::setResumeCallReqStatus(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bStatus is: %d", __FUNCTION__, bStatus);
    if(m_bResumeCallRequestStatus != bStatus)
    {
        m_bResumeCallRequestStatus = bStatus;
        emit sigResumeCallReqStatusUpdated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "value is unchanged");
    }
}

void CPhoneAdaptor::setHoldCallReqStatus(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bStatus is: %d", __FUNCTION__, bStatus);
    if(m_bHoldCallRequestStatus != bStatus)
    {
        m_bHoldCallRequestStatus = bStatus;
        emit sigHoldCallReqStatusUpdated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "value is unchanged");
    }
}

void CPhoneAdaptor::setEndCallReqStatus(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bStatus is: %d", __FUNCTION__, bStatus);
    if(m_bEndCallRequestStatus != bStatus)
    {
        m_bEndCallRequestStatus = bStatus;
        emit sigEndCallReqStatusUpdated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "value is unchanged");
    }
}

void CPhoneAdaptor::setHFModeReqStatus(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bStatus is: %d", __FUNCTION__, bStatus);
    if(m_bHFModeRequestStatus != bStatus)
    {
        m_bHFModeRequestStatus = bStatus;
        emit sigHFModeReqStatusUpdated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "value is unchanged");
    }
}

void CPhoneAdaptor::setHandsFreeModeStatus(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bStatus is: %d", __FUNCTION__, bStatus);
    if(m_bIsHandsFreeMode != bStatus)
    {
        m_bIsHandsFreeMode = bStatus;
        emit sigHandsFreeModeStatusUpdated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "value is unchanged");
    }
}
void CPhoneAdaptor::setSignalStrength(ESignalLevel eSignalStrength)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s eSignalStrength: %d",__FUNCTION__,eSignalStrength);
    CPhoneEnum::ESignalStrengthLevel eSignalStrengthLevel = CPhoneEnum::SIGNAL_STRENGTH_UNAVAILABLE;
    switch(eSignalStrength)
    {
    case NO_SIM_SIGNAL_LEVEL:
        eSignalStrengthLevel = CPhoneEnum::SIGNAL_STRENGTH_NO_SIM;
        break;
    case SIGNAL_LEVEL_0_PERCENT:
        eSignalStrengthLevel = CPhoneEnum::SIGNAL_STRENGTH_LEVEL_ZERO;
        break;
    case SIGNAL_LEVEL_10_PERCENT:
    case SIGNAL_LEVEL_20_PERCENT:
        eSignalStrengthLevel = CPhoneEnum::SIGNAL_STRENGTH_LEVEL_ONE;
        break;
    case SIGNAL_LEVEL_30_PERCENT:
    case SIGNAL_LEVEL_40_PERCENT:
        eSignalStrengthLevel = CPhoneEnum::SIGNAL_STRENGTH_LEVEL_TWO;
        break;
    case SIGNAL_LEVEL_50_PERCENT:
    case SIGNAL_LEVEL_60_PERCENT:
        eSignalStrengthLevel = CPhoneEnum::SIGNAL_STRENGTH_LEVEL_THREE;
        break;
    case SIGNAL_LEVEL_70_PERCENT:
    case SIGNAL_LEVEL_80_PERCENT:
        eSignalStrengthLevel = CPhoneEnum::SIGNAL_STRENGTH_LEVEL_FOUR;
        break;
    case SIGNAL_LEVEL_90_PERCENT:
    case SIGNAL_LEVEL_100_PERCENT:
        eSignalStrengthLevel = CPhoneEnum::SIGNAL_STRENGTH_LEVEL_FIVE;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "signal strength level not handled");
        break;
    }
    if(m_eSignalStrengthLevel != eSignalStrengthLevel)
    {
        m_eSignalStrengthLevel = eSignalStrengthLevel;
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, " %s m_eSignalStrengthLevel -- %d ", __FUNCTION__, m_eSignalStrengthLevel);
        emit sigSignalStrengthLevelUpdated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "value is unchanged");
    }
}
void CPhoneAdaptor::setBatteryCharge(EBatteryChargeLevel eBatteryCharge)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: eBatteryCharge is: %d", __FUNCTION__, eBatteryCharge);
    CPhoneEnum::EBatteryChargeLevel eBatteryChargeLevel = CPhoneEnum::BATTERY_CHARGE_UNAVAILABLE;
    switch(eBatteryCharge)
    {
    case BATTERY_CHARGE_LEVEL_0_PERCENT:
    {
        eBatteryChargeLevel = CPhoneEnum::BATTERY_CHARGE_LEVEL_ZERO;
        if(m_eBatteryChargeLevel != eBatteryChargeLevel)
        {
            //Show low battery popup and play beep
            if(CPopupManager::getInstance())
            {
                CAudioAdaptor::getInstance()->playBeep(CAudioEnums::BEEP_TYPE_CONFIRM);
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DEVICE_BATTERY_LOW);
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Popup manager not available", __FUNCTION__);
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: value is unchanged", __FUNCTION__);
        }
    }
        break;
    case BATTERY_CHARGE_LEVEL_20_PERCENT:
        eBatteryChargeLevel = CPhoneEnum::BATTERY_CHARGE_LEVEL_ONE;
        break;
    case BATTERY_CHARGE_LEVEL_40_PERCENT:
        eBatteryChargeLevel = CPhoneEnum::BATTERY_CHARGE_LEVEL_TWO;
        break;
    case BATTERY_CHARGE_LEVEL_60_PERCENT:
        eBatteryChargeLevel = CPhoneEnum::BATTERY_CHARGE_LEVEL_THREE;
        break;
    case BATTERY_CHARGE_LEVEL_80_PERCENT:
        eBatteryChargeLevel = CPhoneEnum::BATTERY_CHARGE_LEVEL_FOUR;
        break;
    case BATTERY_CHARGE_LEVEL_100_PERCENT:
        eBatteryChargeLevel = CPhoneEnum::BATTERY_CHARGE_LEVEL_FIVE;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: battery charge level not handled", __FUNCTION__);
        break;
    }
    if(m_eBatteryChargeLevel != eBatteryChargeLevel)
    {
        m_eBatteryChargeLevel = eBatteryChargeLevel;
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, " %s: m_eBatteryChargeLevel is: %d ", __FUNCTION__, m_eBatteryChargeLevel);
        emit sigBatteryChargeLevelUpdated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: value is unchanged", __FUNCTION__);
    }
}

void CPhoneAdaptor::setPhoneCallState(CPhoneEnum::EPhoneCallState ePhoneCallState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: ePhoneCallState is: %d",__FUNCTION__, ePhoneCallState);
    m_ePhoneCallState = ePhoneCallState;
    emit sigPhoneCallStateUpdated();
}

/************************************************************************//**
 * @category    PHONE CALL RELATED SETTERS
 ************************************************************************/
void CPhoneAdaptor::setIncomingCallInfo(uint8_t iCallId, const QString& strIncomingrCallerName, const QString& strIncomingCallerNumber,
                                        const QString& strIncomingCallerProfileImg, CPhoneEnum::ECallerState eIncomingCallerState, bool bShowOverlayImage)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: iCallId: %d, strIncomingrCallerName: %s, strIncomingCallerNumber: %s, strIncomingCallerProfileImg: %s, eIncomingCallerState: %d, bShowOverlayImage: %d",
             __FUNCTION__, iCallId, strIncomingrCallerName.toStdString().c_str(), strIncomingCallerNumber.toStdString().c_str(),
             strIncomingCallerProfileImg.toStdString().c_str(), eIncomingCallerState, bShowOverlayImage);
    m_objIncomingCallInfo.setCallId(iCallId);
    m_objIncomingCallInfo.setCallerName(strIncomingrCallerName);
    m_objIncomingCallInfo.setCallerNumber(strIncomingCallerNumber);
    m_objIncomingCallInfo.setCallerProfileImage(strIncomingCallerProfileImg, bShowOverlayImage, true);
    m_objIncomingCallInfo.setCallerState(eIncomingCallerState);
}

void CPhoneAdaptor::setFirstCallerInfo(uint8_t iCallId, const QString &strFirstCallerName, const QString &strFirstCallerNumber,
                                       const QString &strFirstCallerProfileImg, CPhoneEnum::ECallerState eFirstCallerState, bool bShowOverlayImage, bool bIsSingleCallActive)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: iCallId: %d, strFirstCallerName: %s, strFirstCallerNumber: %s, strFirstCallerProfileImg: %s, eFirstCallerState: %d, bShowOverlayImage: %d, bIsSingleCallActive: %d",
             __FUNCTION__, iCallId, strFirstCallerName.toStdString().c_str(), strFirstCallerNumber.toStdString().c_str(),
             strFirstCallerProfileImg.toStdString().c_str(), eFirstCallerState, bShowOverlayImage, bIsSingleCallActive);
    m_objFirstCallerInfo.setCallId(iCallId);
    m_objFirstCallerInfo.setCallerName(strFirstCallerName);
    m_objFirstCallerInfo.setCallerNumber(strFirstCallerNumber);
    m_objFirstCallerInfo.setCallerProfileImage(strFirstCallerProfileImg, bShowOverlayImage, bIsSingleCallActive);
    m_objFirstCallerInfo.setCallerState(eFirstCallerState);
}

void CPhoneAdaptor::setSecondCallerInfo(uint8_t iCallId, const QString &strSecondCallerName, const QString &strSecondCallerNumber,
                                        const QString &strSecondCallerProfileImg, CPhoneEnum::ECallerState eSecondCallerState, bool bShowOverlayImage, bool bIsSingleCallActive)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: iCallId: %d, strSecondCallerName: %s, strSecondCallerNumber: %s, strSecondCallerProfileImg: %s, eSecondCallerState: %d, bShowOverlayImage: %d, bIsSingleCallActive: %d",
             __FUNCTION__, iCallId, strSecondCallerName.toStdString().c_str(), strSecondCallerNumber.toStdString().c_str(),
             strSecondCallerProfileImg.toStdString().c_str(), eSecondCallerState, bShowOverlayImage, bIsSingleCallActive);
    m_objSecondCallerInfo.setCallId(iCallId);
    m_objSecondCallerInfo.setCallerName(strSecondCallerName);
    m_objSecondCallerInfo.setCallerNumber(strSecondCallerNumber);
    m_objSecondCallerInfo.setCallerProfileImage(strSecondCallerProfileImg, bShowOverlayImage, bIsSingleCallActive);
    m_objSecondCallerInfo.setCallerState(eSecondCallerState);
}

void CPhoneAdaptor::setFavoriteToggleInfo(QString strContactName, int iContactId, QString strContactNumber, int iContactType, int iFavoriteIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: strContactName: %s, iContactId: %d, strContactNumber: %s, iContactType: %d, iFavoriteIndex: %d",
             __FUNCTION__, strContactName.toStdString().c_str(), iContactId, strContactNumber.toStdString().c_str(), iContactType, iFavoriteIndex);
    m_objFavoriteTogglingInfo.m_strName     = strContactName;
    m_objFavoriteTogglingInfo.m_iContactID  = iContactId;
    m_objFavoriteTogglingInfo.m_strNumber   = strContactNumber;
    m_objFavoriteTogglingInfo.m_iType       = iContactType;
    m_objFavoriteTogglingInfo.m_iFavIndex   = iFavoriteIndex;
    m_objFavoriteTogglingInfo.m_bIsFavorite = (0 < iFavoriteIndex);

    setFavoriteToggling(true);
}

void CPhoneAdaptor::resetFavoriteToggleInfo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s",__FUNCTION__);
    m_objFavoriteTogglingInfo.clear();
    setFavoriteToggling(false);
}

void CPhoneAdaptor::setFavoriteToggling(const bool bIsToggling)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bIsToggling: %d",__FUNCTION__, bIsToggling);
    if (bIsToggling != m_bIsFavoriteToggling)
    {
        m_bIsFavoriteToggling = bIsToggling;
        sigIsFavoriteTogglingUpdated();
    }
}

/************************************************************************//**
 * @category   PHONE PIMDB METHODS
 ************************************************************************/
void CPhoneAdaptor::pimDbRemoveAsFavoriteOperationResult(bool bIsSuccess)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: fav removed result: %d", __FUNCTION__, bIsSuccess);
    if (m_pContactDetailListModel)
    {
        if (bIsSuccess)
        {
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_BROWSE_FAVORITE_REMOVED);
        }
        else
        {
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_BROWSE_REMOVE_FAVORITE_FAILED);
        }
        invGetContactDetails(m_pContactDetailListModel->getContactIdFromIndex(0));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "contact detail model object not created");
    }
    setFavoriteToggling(false);
}

void CPhoneAdaptor::setContactListCurrentTopIndex(int iValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: iValue: %d",__FUNCTION__, iValue);
    if (m_iContactListCurrentTopIndex != iValue)
    {
        m_iContactListCurrentTopIndex = iValue;
        emit sigContactListCurrentTopIndexUpdated();
    }
    else
    {
        //No change in value
    }
}

void CPhoneAdaptor::setIsSendingSMSAllowed(bool bIsSendingSMSAllowed)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bIsSendingSMSAllowed: %d",__FUNCTION__, bIsSendingSMSAllowed);
    if (m_bIsSendingSMSAllowed != bIsSendingSMSAllowed)
    {
        m_bIsSendingSMSAllowed = bIsSendingSMSAllowed;
        emit sigIsSendingSMSAllowedChanged();
    }
}

void CPhoneAdaptor::updateUnreadMissedCallStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pPhPimDbResource)
    {
        unsigned int uiMissedCallCount = m_pPhPimDbResource->getUnreadMissedCallData().m_uiMissedCallCount;
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: missed call count: %d", __FUNCTION__, uiMissedCallCount);
        /* Only update the unread missed call count to show it in QAD */
        incrementUnreadMissedCallCount(uiMissedCallCount);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "PimDb resource object not created");
    }
}

void CPhoneAdaptor::updateGetSmsSupportedFeature()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);

    if(m_pPhPimDbResource)
    {
        if(!m_pPhPimDbResource->getSmsSupportedFeatureList().empty())    {
            /*
         *  Currently we are getting the first index data from the network operator info list as
         *  we only support single device connection.
         */
            bool bSendSMSAllowed = m_pPhPimDbResource->getSmsSupportedFeatureList().at(0).m_bSendSupport;
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"bSendSMSAllowed : %d", bSendSMSAllowed);
            m_pPhPimDbResource->changeIsSendingSMSAllowed(bSendSMSAllowed);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone call manager resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::updateTTSPlayStateStatus(int iTTSPlayState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: tts play state status: %d", __FUNCTION__, iTTSPlayState);
    CPhoneEnum::ETTSPlayState eTTSPlayState = static_cast<CPhoneEnum::ETTSPlayState>(iTTSPlayState);

    if(m_eTTSPlayState != eTTSPlayState)
    {
        m_eTTSPlayState = eTTSPlayState;
        switch(m_eTTSPlayState)
        {
        case CPhoneEnum::EN_PLAY_STATE_PLAYSTART:
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SMS_READING_POPUP);
            break;

        case CPhoneEnum::EN_PLAY_STATE_PLAYEND:
        {
            CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_PHONE_SMS_READING_POPUP);
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SMS_READING_COMPLETE_POPUP);
        }
            break;

        case CPhoneEnum::EN_PLAY_STATE_ABORTED:
        {
            //Close sms reading popup if TTS play is aborted or error
            CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SMS_READING_POPUP);
            if(m_bStartNewSmsReadout)
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: start readout of new sms", __FUNCTION__);
                m_bStartNewSmsReadout = false;
                invStartSmsReadout();
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: start new sms readout is false", __FUNCTION__);
            }
        }
            break;

        default:
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: tts play state not handled", __FUNCTION__);
            break;
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: tts play state status updated, but values are same", __FUNCTION__);
    }
}

void CPhoneAdaptor::pimDbSetAsFavoriteOperationResult(bool bIsSuccess)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: fav add result: %d", __FUNCTION__, bIsSuccess);
    if (m_pContactDetailListModel)
    {
        if (bIsSuccess)
        {
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_BROWSE_FAVORITE_ADDED);
        }
        else
        {
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_BROWSE_ADD_FAVORITE_FAILED);
        }
        invGetContactDetails(m_pContactDetailListModel->getContactIdFromIndex(0));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "contact detail model object not created");
    }

    setFavoriteToggling(false);
}

void CPhoneAdaptor::changePimDbCallListSyncState(CPhoneEnum::EPhoneSyncStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: eStatus: %d", __FUNCTION__, eStatus);
    if (eStatus != m_ePimDbCallListSyncState)
    {
        m_ePimDbCallListSyncState = eStatus;
        emit sigPimDbCallListSyncUpdated();
    }
}

void CPhoneAdaptor::changePimDbContactListSyncState(CPhoneEnum::EPhoneSyncStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: eStatus: %d", __FUNCTION__, eStatus);
    if (eStatus != m_ePimDbContactListSyncState)
    {
        m_ePimDbContactListSyncState = eStatus;
        emit sigPimDbContactListSyncUpdated();
    }
}

void CPhoneAdaptor::changePimDbContactDetailSyncState(CPhoneEnum::EPhoneSyncStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: eStatus: %d", __FUNCTION__, eStatus);
    if (eStatus != m_ePimDbContactDetailListSyncState)
    {
        m_ePimDbContactDetailListSyncState = eStatus;
        emit sigPimDbContactDetailSyncUpdated();
    }
}

void CPhoneAdaptor::changePimDbFavouriteListSyncState(CPhoneEnum::EPhoneSyncStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: eStatus: %d", __FUNCTION__, eStatus);
    if (eStatus != m_ePimDbFavouriteListSyncState)
    {
        m_ePimDbFavouriteListSyncState = eStatus;
        emit sigPimDbFavouriteListSyncUpdated();
    }
}

void CPhoneAdaptor::changePimDbFrequentlyDialedListSyncState(CPhoneEnum::EPhoneSyncStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: eStatus: %d", __FUNCTION__, eStatus);
    if (eStatus != m_ePimDbFrequentlyDialedListSyncState)
    {
        m_ePimDbFrequentlyDialedListSyncState = eStatus;
        emit sigPimDbFrequentlyDialedListSyncUpdated();
    }
}

void CPhoneAdaptor::invChangeDTMFNumberPadStatus(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bStatus: %d", __FUNCTION__, bStatus);
    if(m_bIsInDTMFNumberPad != bStatus)
    {
        m_bIsInDTMFNumberPad = bStatus;
        emit sigDTMFNumberPadStatusUpdated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "DTMF number pad value unchanged");
    }
}

void CPhoneAdaptor::pimDbCallListUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);

    if(m_pPhPimDbResource)
    {
        if(m_pCallLogListModel)
        {
            m_pCallLogListModel->removeRows();
            int iSize = static_cast<int>(m_pPhPimDbResource->getCallLogList().size());
            for(int iIndex = 0; iIndex < iSize; iIndex++)
            {
                CPhoneData::SCallLogInfo objCallInfo;

                int index = m_pPhPimDbResource->getCallLogList().at(iIndex).m_iCallLogIndex;
                QString dateTime = QString::fromStdString(m_pPhPimDbResource->getCallLogList().at(iIndex).m_strCallStamp);
                QStringList dateTimeSplit = dateTime.split(", ");

                objCallInfo.m_iIndex = index;
                objCallInfo.m_strName = QString::fromStdString(m_pPhPimDbResource->getCallLogList().at(iIndex).m_strContactName);
                objCallInfo.m_strNumber = QString::fromStdString(m_pPhPimDbResource->getCallLogList().at(iIndex).m_strContactNumber);
                objCallInfo.m_iCallType = getCallType(m_pPhPimDbResource->getCallLogList().at(iIndex).m_iCallType);

                if (dateTimeSplit.length() == 2)
                {
                    objCallInfo.m_strTime = dateTimeSplit[1];
                    objCallInfo.m_strDate = dateTimeSplit[0];
                }
                else
                {
                    LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s invalid format date", dateTime.toStdString().c_str());
                }

                m_pCallLogListModel->insertRows(objCallInfo);
            }
            emit sigCallLogListModelUpdated();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "call log list model object not created");
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "PimDb resource object not created");
    }
}

void CPhoneAdaptor::pimDbContactListUpdated(unsigned short usStartIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: start index is: %d", __FUNCTION__, usStartIndex);

    if(m_pPhPimDbResource)
    {
        if(m_pContactListModel)
        {
            //Clear the list if start index is received as 0
            if(usStartIndex == 0)
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: start index is 0, clearing contact list model", __FUNCTION__);
                m_pContactListModel->removeRows();
                /**
                 * If current screen displayed is contact details screen and contact list is updated because of background sync
                 * then switch to contact screen else do nothing
                 */
                if(CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_ContactDetails))
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: contact details screen is displayed, do back", __FUNCTION__);
                    CFramework::getFramework().doBack();
                }
                else
                {
                    //do nothing
                }
            }

            int iSize = static_cast<int>(m_pPhPimDbResource->getContactList().size());
            for(int iIndex = 0; iIndex < iSize; iIndex++)
            {
                CPhoneData::SContactDetailInfo objContactInfo;

                objContactInfo.m_iIndex         = m_pPhPimDbResource->getContactList().at(iIndex).m_iContactIndex;
                objContactInfo.m_iContactID     = m_pPhPimDbResource->getContactList().at(iIndex).m_iContactID;
                objContactInfo.m_strName        = QString::fromStdString(m_pPhPimDbResource->getContactList().at(iIndex).m_strContactName);
                objContactInfo.m_strNumber      = QString::fromStdString(m_pPhPimDbResource->getContactList().at(iIndex).m_strContactNumber);
                objContactInfo.m_iType          = m_pPhPimDbResource->getContactList().at(iIndex).m_iContactType;
                objContactInfo.m_iFavIndex      = m_pPhPimDbResource->getContactList().at(iIndex).m_iFavIndex;
                objContactInfo.m_bIsFavorite    = (objContactInfo.m_iFavIndex > 0);

                m_pContactListModel->insertRows(objContactInfo);
            }
            emit sigContactListModelUpdated();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "contact list model object not created");
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "PimDb resource object not created");
    }
}

void CPhoneAdaptor::pimDbContactDetailListUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);

    if(m_pPhPimDbResource)
    {
        if(m_pContactDetailListModel)
        {
            invResetContactDetailList();

            int iSize = static_cast<int>(m_pPhPimDbResource->getContactDetailList().size());
            for(int iIndex = 0; iIndex < iSize; iIndex++)
            {
                CPhoneData::SContactDetailInfo objContactInfo;

                objContactInfo.m_iIndex         = m_pPhPimDbResource->getContactDetailList().at(iIndex).m_iContactIndex;
                objContactInfo.m_iContactID     = m_pPhPimDbResource->getContactDetailList().at(iIndex).m_iContactID;
                objContactInfo.m_strName        = QString::fromStdString(m_pPhPimDbResource->getContactDetailList().at(iIndex).m_strContactName);
                objContactInfo.m_strNumber      = QString::fromStdString(m_pPhPimDbResource->getContactDetailList().at(iIndex).m_strContactNumber);
                objContactInfo.m_iType          = m_pPhPimDbResource->getContactDetailList().at(iIndex).m_iContactType;
                objContactInfo.m_iFavIndex      = 0;//m_pPhPimDbResource->getContactDetailList().at(iIndex).m_iFavIndex;
                objContactInfo.m_bIsFavorite    = false;//(objContactInfo.m_iFavIndex > 0);

                m_pContactDetailListModel->insertRows(objContactInfo);
            }
            syncFavouriteListWithContactDetails();
            //Switch to contact details screen as the contact details data has been received.
            invSwitchToPhoneBrowse(CPhoneEnum::PHONE_BROWSE_TYPE_CONTACT_DETAILS);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "contact detail list model object not created");
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "PimDb resource object not created");
    }
}

void CPhoneAdaptor::pimDbFavouriteListUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);

    if(m_pPhPimDbResource)
    {
        if(m_pFavoriteContactListModel)
        {
            m_pFavoriteContactListModel->removeRows();
            int iSize = static_cast<int>(m_pPhPimDbResource->getFavouriteList().size());
            for(int iIndex = 0; iIndex < iSize; iIndex++)
            {
                CPhoneData::SContactDetailInfo objContactInfo;

                objContactInfo.m_iIndex         = m_pPhPimDbResource->getFavouriteList().at(iIndex).m_iContactIndex;
                objContactInfo.m_iContactID     = m_pPhPimDbResource->getFavouriteList().at(iIndex).m_iContactID;
                objContactInfo.m_strName        = QString::fromStdString(m_pPhPimDbResource->getFavouriteList().at(iIndex).m_strContactName);
                objContactInfo.m_strNumber      = QString::fromStdString(m_pPhPimDbResource->getFavouriteList().at(iIndex).m_strContactNumber);
                objContactInfo.m_iType          = m_pPhPimDbResource->getFavouriteList().at(iIndex).m_iContactType;
                objContactInfo.m_iFavIndex      = m_pPhPimDbResource->getFavouriteList().at(iIndex).m_iFavIndex;
                objContactInfo.m_bIsFavorite    = (objContactInfo.m_iFavIndex > 0);

                m_pFavoriteContactListModel->insertRows(objContactInfo);
            }
            syncFavouriteListWithContactDetails();
            emit sigFavoriteContactListModelUpdated();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "favorite list model object not created");
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "PimDb resource object not created");
    }

    if (m_pContactDetailListModel)
    {
        invGetContactDetails(m_pContactDetailListModel->getContactIdFromIndex(0));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "contact detail list model object not created");
    }
}

void CPhoneAdaptor::pimDbFrequentlyDialedListUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);

    if(m_pPhPimDbResource)
    {
        if(m_pFrequentlyDialedListModel)
        {
            m_pFrequentlyDialedListModel->removeRows();
            int iSize = static_cast<int>(m_pPhPimDbResource->getFrequentlyDialedList().size());
            for(int iIndex = 0; iIndex < iSize; iIndex++)
            {
                CPhoneData::SCallLogInfo objFrequentlyDialedInfo;

                int index = m_pPhPimDbResource->getFrequentlyDialedList().at(iIndex).m_iDialledNumIndex;
                QString dateTime = QString::fromStdString(m_pPhPimDbResource->getFrequentlyDialedList().at(iIndex).m_strCallStamp);
                QStringList dateTimeSplit = dateTime.split(", ");

                objFrequentlyDialedInfo.m_iIndex = index;
                objFrequentlyDialedInfo.m_strName = QString::fromStdString(m_pPhPimDbResource->getFrequentlyDialedList().at(iIndex).m_strContactName);
                objFrequentlyDialedInfo.m_strNumber = QString::fromStdString(m_pPhPimDbResource->getFrequentlyDialedList().at(iIndex).m_strContactNumber);
                objFrequentlyDialedInfo.m_iCallType = getCallType(m_pPhPimDbResource->getFrequentlyDialedList().at(iIndex).m_iCallType);

                if (dateTimeSplit.length() == 2)
                {
                    objFrequentlyDialedInfo.m_strTime = dateTimeSplit[1];
                    objFrequentlyDialedInfo.m_strDate = dateTimeSplit[0];
                }
                else
                {
                    LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: invalid format date: %s", __FUNCTION__, dateTime.toStdString().c_str());
                }

                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: iIndex: %d, strName: %s, strNumber: %s, iCallType: %d, strTime: %s, strDate: %s",
                         __FUNCTION__, objFrequentlyDialedInfo.m_iIndex, objFrequentlyDialedInfo.m_strName.toStdString().c_str(),
                         objFrequentlyDialedInfo.m_strNumber.toStdString().c_str(), objFrequentlyDialedInfo.m_iCallType,
                         objFrequentlyDialedInfo.m_strTime.toStdString().c_str(), objFrequentlyDialedInfo.m_strDate.toStdString().c_str());

                m_pFrequentlyDialedListModel->insertRows(objFrequentlyDialedInfo);
            }
            emit sigFrequentlyDialedListModelUpdated();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: frequently dialed list model object not created", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: PimDb resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::syncFavouriteListWithContactDetails()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);

    if(m_pPhPimDbResource)
    {
        if(m_pContactDetailListModel && m_pFavoriteContactListModel)
        {
            int iFavCount = m_pFavoriteContactListModel->rowCount();
            int iContactsCount = m_pContactDetailListModel->rowCount();

            if ((iFavCount > 0) && (iContactsCount > 0))
            {
                for (int i = 0; i < iFavCount; i++)
                {
                    if (m_pContactDetailListModel->getContactIdFromIndex(0) == m_pFavoriteContactListModel->getContactIdFromIndex(i))
                    {
                        for (int j = 0; j < iContactsCount; j++)
                        {
                            if (m_pFavoriteContactListModel->getNumberFromIndex(i) == m_pContactDetailListModel->getNumberFromIndex(j))
                            {
                                m_pContactDetailListModel->setFavoriteIndex(j, m_pFavoriteContactListModel->getFavoriteIndex(i));
                            }
                        }
                    }
                }
            }
        }
        emit sigContactDetailListModelUpdated();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "PimDb resource object not created");
    }
}

/************************************************************************//**
 * @category    PHONE PIMDB PROPERTY RELATED GETTERS
 ************************************************************************/
CPhoneEnum::EPhoneSyncStatus CPhoneAdaptor::pimDbCallListSyncStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    return m_ePimDbCallListSyncState;
}

CPhoneEnum::EPhoneSyncStatus CPhoneAdaptor::pimDbContactListSyncStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    return m_ePimDbContactListSyncState;
}

CPhoneEnum::EPhoneSyncStatus CPhoneAdaptor::pimDbContactDetailSyncStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    return m_ePimDbContactDetailListSyncState;
}

CPhoneEnum::EPhoneSyncStatus CPhoneAdaptor::pimDbFavouriteListSyncStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    return m_ePimDbFavouriteListSyncState;
}

CPhoneEnum::EPhoneSyncStatus CPhoneAdaptor::pimDbFrequentlyDialedListSyncStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    return m_ePimDbFrequentlyDialedListSyncState;
}

QString CPhoneAdaptor::smsSenderName()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    return QString::fromStdString(m_objMessageData.m_strName);
}

QString CPhoneAdaptor::smsSenderNumber()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    return QString::fromStdString(m_objMessageData.m_strNumber);
}

QString CPhoneAdaptor::smsData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    return QString::fromStdString(m_objMessageData.m_strBody);
}

QString CPhoneAdaptor::readingSMSSenderName()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    return QString::fromStdString(m_objReadingMessageData.m_strName);
}

QString CPhoneAdaptor::readingSMSSenderNumber()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    return QString::fromStdString(m_objReadingMessageData.m_strNumber);
}

QString CPhoneAdaptor::readingSMSData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    return QString::fromStdString(m_objReadingMessageData.m_strBody);
}

void CPhoneAdaptor::setSMSDetails(SMessageData &objSMSData)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: sender bt address: %s, sender name: %s, sender number: %s, message body: %s ", __FUNCTION__,
             objSMSData.m_strAddress.c_str(), objSMSData.m_strName.c_str(), objSMSData.m_strNumber.c_str(), objSMSData.m_strBody.c_str());
    m_objMessageData = objSMSData;
    sigSMSSenderNameChanged();
    sigSMSSenderNumberChanged();
    sigSMSDataChanged();
}

void CPhoneAdaptor::setReadingSMSDetails(SMessageData &objSmsData)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: sender bt address: %s, sender name: %s, sender number: %s, message body: %s ", __FUNCTION__,
             objSmsData.m_strAddress.c_str(), objSmsData.m_strName.c_str(), objSmsData.m_strNumber.c_str(), objSmsData.m_strBody.c_str());
    m_objReadingMessageData = objSmsData;
    sigReadingSMSSenderNameChanged();
    sigReadingSMSSenderNumberChanged();
    sigReadingSMSDataChanged();
}

void CPhoneAdaptor::resetSMSDetails()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_objMessageData.clear();

    sigSMSSenderNameChanged();
    sigSMSSenderNumberChanged();
    sigSMSDataChanged();
}

void CPhoneAdaptor::resetReadingSMSDetails()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_objReadingMessageData.clear();

    sigReadingSMSSenderNameChanged();
    sigReadingSMSSenderNumberChanged();
    sigReadingSMSDataChanged();
}

bool CPhoneAdaptor::isMaxDeviceLimitReached()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    //(m_pPairedDeviceListModel->rowCount() - 1) is checked as "Pair new device" item is also added in the list
    return ((m_pPairedDeviceListModel->rowCount() - 1) > CPhoneData::MAX_DEVICE_PAIRING_COUNT);
}

bool CPhoneAdaptor::isDeviceAlreadyPaired(const QString &strBtAddress)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    return (m_pPairedDeviceListModel->isDeviceAlreadyPaired(strBtAddress));
}

void CPhoneAdaptor::deleteOldestConnectedDevice()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);

    if(m_pPhConnMgrResource)
    {
        m_bIsOldestConnDeviceDeletionRequested = true;
        m_pPhConnMgrResource->getOldestConnectedDeviceAsyncReq();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: m_pPhConnMgrResource is NULL.", __FUNCTION__);
    }
}

void CPhoneAdaptor::updateOldestConnectedDeviceInfo(const QString &strDeviceName, const QString &strDeviceAddress)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Oldest Device Name: %s, Device Address: %s", __FUNCTION__,
             strDeviceName.toStdString().c_str(), strDeviceAddress.toStdString().c_str());
    if(m_pPhConnMgrResource && m_bIsOldestConnDeviceDeletionRequested)
    {
        m_pPhConnMgrResource->deleteDeviceAsyncReq(strDeviceAddress.toStdString());
        m_bIsOldestConnDeviceDeletionRequested = false;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: m_pPhConnMgrResource is NULL.", __FUNCTION__);
    }
}

void CPhoneAdaptor::newMessageNotification()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pPhPimDbResource)
    {
        if (CPopupEnum::EN_POPUPID_PHONE_INCOMING_SMS_POPUP == CPopupManager::getInstance()->getCurrentDisplayedPopup())
        {
            CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_SMS_POPUP);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, Incoming SMS popup is not alive", __FUNCTION__);
        }
        m_bShowIncomingSmsPopup = false;

        SMessageData objSmsData = m_pPhPimDbResource->getMessageData();
        string strSenderNameNum = (objSmsData.m_strName == "") ? objSmsData.m_strNumber : objSmsData.m_strName;
        setSMSDetails(objSmsData);

        if(m_pPhoneSetupListModel)
        {
            CPhoneEnum::ESmsAlertNotificationItemId eSmsAlertType = static_cast<CPhoneEnum::ESmsAlertNotificationItemId>(m_pPhoneSetupListModel->getSmsAlertType());
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: sms alert type is: %d", __FUNCTION__, eSmsAlertType);
            switch(eSmsAlertType)
            {
            case CPhoneEnum::NO_NOTIFICATION_ID:
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: no notification to be shown", __FUNCTION__);
            }
                break;
            case CPhoneEnum::NOTIFY_WITH_BEEP_AND_POPUP_ID:
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: play beep and show incoming sms popup", __FUNCTION__);
                CAudioAdaptor::getInstance()->playBeep(CAudioEnums::BEEP_TYPE_CONFIRM);
                ResourceFactory::getICCastResource()->setIcRenderSmsIndicationAsyncReq(true, strSenderNameNum);
                if((CParkAssistAdaptor::getInstance()) && (CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus()))
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: show low priority incoming sms popup", __FUNCTION__);
                    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_LOW_PRIORITY_SMS_POPUP);
                    CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_LOW_PRIORITY_SMS_POPUP);
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: show full incoming sms popup", __FUNCTION__);
                    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_SMS_POPUP);
                    CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_SMS_POPUP);
                }

                m_bShowIncomingSmsPopup = true;
            }
                break;
            case CPhoneEnum::NOTIFY_WITH_ONLY_POPUP_ID:
            {
                ResourceFactory::getICCastResource()->setIcRenderSmsIndicationAsyncReq(true, strSenderNameNum);
                if((CParkAssistAdaptor::getInstance()) && (CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus()))
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: show low priority incoming sms popup", __FUNCTION__);
                    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_LOW_PRIORITY_SMS_POPUP);
                    CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_LOW_PRIORITY_SMS_POPUP);
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: show full incoming sms popup", __FUNCTION__);
                    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_SMS_POPUP);
                    CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_SMS_POPUP);
                }

                m_bShowIncomingSmsPopup = true;
            }
                break;
            default:
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: sms alert type not handled", __FUNCTION__);
                break;
            }
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s, phone setup list model not available", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s, pimdb resource not available", __FUNCTION__);
    }
}

void CPhoneAdaptor::invResetContactDetailList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pContactDetailListModel)
    {
        m_pContactDetailListModel->removeRows();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "contact list model object not created");
    }
}

/************************************************************************//**
 * @category    PHONE PIMDB MANAGER RESOURCE LAYER METHODS
 ************************************************************************/
void CPhoneAdaptor::invGetContactDetails(int iContactId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: contact id: %d", __FUNCTION__, iContactId);
    if(m_pPhPimDbResource)
    {
        if (0 < iContactId)
        {
            m_pPhPimDbResource->getContactsByIDAsyncReq(0, iContactId);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s invalid iContactId passed : %d", __FUNCTION__, iContactId);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "PimDb resource object not created");
    }
}

void CPhoneAdaptor::invAddContactToFavorite(QString strContactName, int iContactId, QString strContactNumber, int iContactType, int iFavoriteIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: contact name: %s, contact id: %d, contact number: %s, contact type: %d, fav index: %d",
             __FUNCTION__, strContactName.toStdString().c_str(), iContactId, strContactNumber.toStdString().c_str(),
             iContactType, iFavoriteIndex);
    if(m_pPhPimDbResource)
    {
        if ((NULL == m_pFavoriteContactListModel) ||
                (m_pFavoriteContactListModel->rowCount() < CPhoneData::FAVORITE_CONTACTS_MAX_LIMIT))
        {
            setFavoriteToggleInfo(strContactName, iContactId, strContactNumber, iContactType, iFavoriteIndex);
            m_pPhPimDbResource->addContactToFavouriteListAsyncReq(m_objFavoriteTogglingInfo.m_iContactID, m_objFavoriteTogglingInfo.m_strNumber.toStdString(), m_objFavoriteTogglingInfo.m_iType);
        }
        else
        {
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_BROWSE_FAVORITE_LIST_FULL);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "PimDb resource object not created");
    }
}

void CPhoneAdaptor::invRemoveContactFromFavorite(QString strContactName, int iContactId, QString strContactNumber, int iContactType, int iFavoriteIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: contact name: %s, contact id: %d, contact number: %s, contact type: %d, fav index: %d",
             __FUNCTION__, strContactName.toStdString().c_str(), iContactId, strContactNumber.toStdString().c_str(),
             iContactType, iFavoriteIndex);
    setFavoriteToggleInfo(strContactName, iContactId, strContactNumber, iContactType, iFavoriteIndex);
    CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_BROWSE_FAVORITE_REMOVE_CONFIRMATION);
}

QString CPhoneAdaptor::invGetContactTypeText(int iContactType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: iContactType: %d", __FUNCTION__, iContactType);
    QString strContactType = "";
    switch (iContactType)
    {
    case EContactType::CONTACT_TYPE_MOBILE:
    {
        strContactType = "Mobile";
    }
        break;
    case EContactType::CONTACT_TYPE_HOME:
    {
        strContactType = "Home";
    }
        break;
    case EContactType::CONTACT_TYPE_WORK:
    {
        strContactType = "Work";
    }
        break;
    case EContactType::CONTACT_TYPE_OTHER:
    {
        strContactType = "Other";
    }
        break;
    default:
    {
        strContactType = "";
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "Contact Type %d NOT HANDLED", iContactType);
    }
        break;
    }
    LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "Contact type is: %s", strContactType.toStdString().c_str());
    return strContactType;
}

void CPhoneAdaptor::invRemoveFavorite(bool bRemoveFav)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: to be removed: %d", __FUNCTION__, bRemoveFav);
    if (bRemoveFav)
    {
        if(m_pPhPimDbResource)
        {
            m_pPhPimDbResource->deleteContactFromFavouriteListAsyncReq(m_objFavoriteTogglingInfo.m_iFavIndex);
        }
        else
        {
            resetFavoriteToggleInfo();
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "PimDb resource object not created");
        }
    }
    else
    {
        resetFavoriteToggleInfo();
    }
}

void CPhoneAdaptor::invResetUnreadMissedCallInfo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_uiUnreadMissedCallCount = 0;
    m_strPhoneNotificationText = tr("TEXT_QAD_NOTIFY_LABEL_NO_NEW_NOTIFICATIONS");
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: phone notification text - %s", __FUNCTION__, m_strPhoneNotificationText.toStdString().c_str());
}

void CPhoneAdaptor::invStartSmsReadout()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(ResourceFactory::getBtPluginResource() && (m_objMessageData.m_strBody != ""))
    {
        if(CPopupManager::getInstance())
        {
            if(m_eTTSPlayState == CPhoneEnum::EN_PLAY_STATE_PLAYING)
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: tts is in playing state", __FUNCTION__);
                invStopSmsReadout();
                m_bStartNewSmsReadout = true;
            }
            else
            {
                setReadingSMSDetails(m_objMessageData);
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: tts is not in playing state", __FUNCTION__);
                ResourceFactory::getBtPluginResource()->startTTSPlayAsyncReq(CPhoneData::SMS_READOUT_NON_MIX_MODE, m_objMessageData.m_strBody);
            }
            m_bShowIncomingSmsPopup = false;
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: popup manager object not created", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: BtPlugin resource object not created", __FUNCTION__);
    }
}

void CPhoneAdaptor::invStopSmsReadout()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(ResourceFactory::getBtPluginResource())
    {
        ResourceFactory::getBtPluginResource()->stopTTSPlayAsyncReq(CPhoneData::SMS_READOUT_NON_MIX_MODE);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: BtPlugin resource object not created", __FUNCTION__);
    }
}

QString CPhoneAdaptor::getKeyButtonDefaultImageCapital(int iKeyIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: iKeyIndex: %d", __FUNCTION__, iKeyIndex);
    QString strImagePath = "";

    switch(iKeyIndex)
    {
    case 1:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalQ_7in_n-assets/Set_Btn_Key_CapQ_7in_n.png";    break;
    case 2:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalW_7in_n-assets/Set_Btn_Key_CapW_7in_n.png";    break;
    case 3:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalE_7in_n-assets/Set_Btn_Key_CapE_7in_n.png";    break;
    case 4:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalR_7in_n-assets/Set_Btn_Key_CapR_7in_n.png";    break;
    case 5:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalT_7in_n-assets/Set_Btn_Key_CapitalT_n.png";    break;
    case 6:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalY_7in_n-assets/Set_Btn_Key_CapY_7in_n.png";    break;
    case 7:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalU_7in_n-assets/Set_Btn_Key_CapU_7in_n.png";    break;
    case 8:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KP_CapitalI_7in_n-assets/Set_Btn_KP_CapitalI_7in_n.png";     break;
    case 9:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalO_7in_n-assets/Set_Btn_Key_CapO_7in_n.png";    break;
    case 10: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalP_7in_n-assets/Set_Btn_Key_CapP_7in_n.png";    break;
    case 11: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalA_7in_n-assets/Set_Btn_Key_CapA_7in_n.png";    break;
    case 12: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalS_7in_n-assets/Set_Btn_Key_CapS_7in_n.png";    break;
    case 13: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalD_7in_n-assets/Set_Btn_Key_CapD_7in_n.png";    break;
    case 14: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalF_7in_n-assets/Set_Btn_Key_CapF_7in_n.png";    break;
    case 15: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalG_7in_n-assets/Set_Btn_Key_CapG_7in_n.png";    break;
    case 16: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalH_7in_n-assets/Set_Btn_Key_CapH_7in_n.png";    break;
    case 17: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalJ_7in_n-assets/Set_Btn_Key_CapJ_7in_n.png";    break;
    case 18: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalK_7in_n-assets/Set_Btn_Key_CapK_7in_n.png";    break;
    case 19: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalL_7in_n-assets/Set_Btn_Key_CapL_7in_n.png";    break;
    case 20: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalaA_7in_n-assets/Set_Btn_Key_CapaA_7in_n.png";  break;
    case 21: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalZ_7in_n-assets/Set_Btn_Key_CapZ_7in_n.png";    break;
    case 22: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalX_7in_n-assets/Set_Btn_Key_CapX_7in_n.png";    break;
    case 23: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalC_7in_n-assets/Set_Btn_Key_CapC_7in_n.png";    break;
    case 24: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalV_7in_n-assets/Set_Btn_Key_CapV_7in_n.png";    break;
    case 25: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitaB_7in_n-assets/Set_Btn_Key_CapB_7in_n.png";     break;
    case 26: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalN_7in_n-assets/Set_Btn_Key_CapN_7in_n.png";    break;
    case 27: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalM_7in_n-assets/Set_Btn_Key_CapM_7in_n.png";    break;
    case 28: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Capital,_7in_n-assets/_7in_n.png";                    break;
    case 29: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Capital._7in_n-assets/Set_Btn_Key_Cap._7in_n.png";    break;
    case 30: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Space_7in_n-assets/Set_Btn_Key_Space_7in_n.png";      break;
    case 31: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_123_7in_n-assets/Set_Btn_KeyPad_123_n.png";          break;

    default: LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: getKeyButtonDefaultImageCapital - default case, iKeyIndex: %d", __FUNCTION__, iKeyIndex); break;

    }
    return strImagePath;
}

QString CPhoneAdaptor::getKeyButtonDefaultImageSmall(int iKeyIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: iKeyIndex: %d", __FUNCTION__, iKeyIndex);
    QString strImagePath = "";

    switch(iKeyIndex)
    {
    case 1:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallQ_7in_n-assets/Set_Btn_Key_SmallQ_7in_n.png";    break;
    case 2:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallW_7in_n-assets/Set_Btn_Key_SmallW_7in_n.png";    break;
    case 3:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallE_7in_n-assets/Set_Btn_Key_SmallE_7in_n.png";    break;
    case 4:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallR_7in_n-assets/Set_Btn_Key_SmallR_7in_n.png";    break;
    case 5:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallT_7in_n-assets/Set_Btn_Key_SmallT_7in_n.png";    break;
    case 6:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallY_7in_n-assets/Set_Btn_Key_SmallY_7in_n.png";    break;
    case 7:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallU_7in_n-assets/Set_Btn_Key_SmallU_7in_n.png";    break;
    case 8:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallI_7in_n-assets/Set_Btn_Key_SmallI_7in_n.png";    break;
    case 9:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallO_7in_n-assets/Set_Btn_Key_SmallO_7in_n.png";    break;
    case 10: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallP_7in_n-assets/Set_Btn_Key_SmallP_7in_n.png";    break;
    case 11: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallA_7in_n-assets/Set_Btn_Key_SmallA_7in_n.png";    break;
    case 12: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallS_7in_n-assets/Set_Btn_Key_SmallS_7in_n.png";    break;
    case 13: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallD_7in_n-assets/Set_Btn_Key_SmallD_7in_n.png";    break;
    case 14: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallF_7in_n-assets/Set_Btn_Key_SmallF_7in_n.png";    break;
    case 15: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallG_7in_n-assets/Set_Btn_Key_SmallG_7in_n.png";    break;
    case 16: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallH_7in_n-assets/Set_Btn_Key_SmallH_7in_n.png";    break;
    case 17: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallJ_7in_n-assets/Set_Btn_Key_SmallJ_7in_n.png";    break;
    case 18: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallK_7in_n-assets/Set_Btn_Key_SmallK_7in_n.png";    break;
    case 19: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallL_7in_n-assets/Set_Btn_Key_SmallL_7in_n.png";    break;
    case 20: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalaA_7in_n-assets/Set_Btn_Key_CapaA_7in_n.png";  break;
    case 21: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallZ__7in_n-assets/Set_Btn_Key_SmallZ_7in_n.png";   break;
    case 22: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallX_7in_n-assets/Set_Btn_Key_SmallX_7in_n.png";    break;
    case 23: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallC_7in_n-assets/Set_Btn_Key_SmallC_7in_n.png";    break;
    case 24: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallV_7in_n-assets/Set_Btn_Key_SmallV_7in_n.png";    break;
    case 25: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallB_7in_n-assets/Set_Btn_Key_SmallB_7in_n.png";    break;
    case 26: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallN_7in_n-assets/Set_Btn_Key_SmallN_7in_n.png";    break;
    case 27: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallM_7in_n-assets/Set_Btn_Key_SmallM_7in_n.png";    break;
    case 28: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Capital,_7in_n-assets/_7in_n.png";                    break;
    case 29: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Capital._7in_n-assets/Set_Btn_Key_Cap._7in_n.png";    break;
    case 30: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Space_7in_n-assets/Set_Btn_Key_Space_7in_n.png";      break;
    case 31: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_123_7in_n-assets/Set_Btn_KeyPad_123_n.png";          break;

    default: LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: getKeyButtonDefaultImageSmall - default case, iKeyIndex: %d", __FUNCTION__, iKeyIndex); break;
    }
    return strImagePath;
}

QString CPhoneAdaptor::getKeyButtonDefaultImageNumeric(int iKeyIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: iKeyIndex: %d", __FUNCTION__, iKeyIndex);
    QString strImagePath = "";

    switch(iKeyIndex)
    {
    case 1:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_1_7in_n-assets/Set_Btn_Keypad_1_7in_n.png";                         break;
    case 2:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_2_7in_n-assets/Set_Btn_Keypad_2_7in_n.png";                         break;
    case 3:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_3_7in_n-assets/Set_Btn_Keypad_3_7in_n.png";                         break;
    case 4:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_4_7in_n-assets/Set_Btn_Keypad_4_7in_n.png";                         break;
    case 5:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_5_7in_n-assets/Set_Btn_Keypad_5_7in_n.png";                         break;
    case 6:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_6_7in_n-assets/Set_Btn_Key_6_7in_n.png";                            break;
    case 7:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_7_7in_n-assets/Set_Btn_Key_7_7in_n.png";                            break;
    case 8:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_8_7in_n-assets/Set_Btn_Keypad_8_7in_n.png";                         break;
    case 9:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_9_7in_n-assets/Set_Btn_Keypad_9_7in_n.png";                         break;
    case 10: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_0_7in_n-assets/Set_Btn_Keypad_0_7in_n.png";                         break;
    case 11: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_AtTheRate_7in_n-assets/Set_Btn_Keypad_AtTheRate_7in_n.png";         break;
    case 12: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Hash_7in_n-assets/Set_Btn_Keypad_Hash_7in_n.png";                   break;
    case 13: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Dollar_7in_n-assets/Set_Btn_Keypad_Dollar_7in_n.png";               break;
    case 14: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Percentage_7in_n-assets/Set_Btn_Keypad_Percentage_7in_n.png";       break;
    case 15: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_And_7in_n-assets/Set_Btn_Keypad_And_7in_n.png";                     break;
    case 16: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Minus_7in_n-assets/Set_Btn_Keypad_Minus_7in_n.png";                 break;
    case 17: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Plus_7in_n-assets/Plus_7in_n.png";                                  break;
    case 18: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Left_Bracket_7in_n-assets/Set_Btn_Keypad_Left_Bracket_7in_n.png";   break;
    case 19: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Right_Bracket_7in_n-assets/Set_Btn_Keypad_Right_Bracket_7in_n.png"; break;
    case 20: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_1_1_7in_n-assets/Set_Btn_KeyPad_1_1_7in_n.png";                     break;
    case 21: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Keystar_7in_n-assets/Set_Btn_Keypad_star_7in_n.png";                break;
    case 22: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Doubleqoutations_7in_n-assets/Set_Btn_Key_2qout_n.png";             break;
    case 23: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_singlequotation_7in_n-assets/Set_Btn_Key_1quotation_7in_n.png";     break;
    case 24: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Colon_7in_n-assets/Set_Btn_Keypad_Colon_7in_n.png";                 break;
    case 25: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Semicolon_7in_n-assets/Set_Btn_Key_Semicolon_7in_n.png";            break;
    case 26: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Exclaimation_7in_n-assets/Set_Btn_Keypad__Exclaimation_7in_n.png";  break;
    case 27: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Questionmark_7in_n-assets/Set_Btn_Key_Quest_7in_n.png";             break;
    case 28: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Capital,_7in_n-assets/_7in_n.png";                                  break;
    case 29: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Capital._7in_n-assets/Set_Btn_Key_Cap._7in_n.png";                  break;
    case 30: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Space_7in_n-assets/Set_Btn_Key_Space_7in_n.png";                    break;
    case 31: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_abc_7in_n-assets/Set_Btn_Key_abc_7in_n.png";                        break;

    default: LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: getKeyButtonDefaultImageNumeric - default case, iKeyIndex: %d", __FUNCTION__, iKeyIndex); break;
    }
    return strImagePath;
}

QString CPhoneAdaptor::getKeyButtonPressedImageCapital(int iKeyIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: iKeyIndex: %d", __FUNCTION__, iKeyIndex);
    QString strImagePath = "";

    switch(iKeyIndex)
    {
    case 1:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalQ_7in_n-assets/Set_Btn_Key_CapQ_7in_nf.png";   break;
    case 2:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalW_7in_n-assets/Set_Btn_Key_CapW_7in_nf.png";   break;
    case 3:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalE_7in_n-assets/Set_Btn_Key_CapE_7in_nf.png";   break;
    case 4:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalR_7in_n-assets/Set_Btn_Key_CapR_7in_nf.png";   break;
    case 5:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalT_7in_n-assets/Set_Btn_Key_CapitalT_nf.png";   break;
    case 6:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalY_7in_n-assets/Set_Btn_Key_CapY_7in_nf.png";   break;
    case 7:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalU_7in_n-assets/Set_Btn_Key_CapU_7in_nf.png";   break;
    case 8:  strImagePath =  "qrc:/image/KeyPad/Set_Btn_KP_CapitalI_7in_n-assets/Set_Btn_KP_CapitalI_7in_nf.png";   break;
    case 9:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalO_7in_n-assets/Set_Btn_Key_CapO_7in_nf.png";   break;
    case 10: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalP_7in_n-assets/Set_Btn_Key_CapP_7in_nf.png";   break;
    case 11: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalA_7in_n-assets/Set_Btn_Key_CapA_7in_nf.png";   break;
    case 12: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalS_7in_n-assets/Set_Btn_Key_CapS_7in_nf.png";   break;
    case 13: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalD_7in_n-assets/Set_Btn_Key_CapD_7in_nf.png";   break;
    case 14: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalF_7in_n-assets/Set_Btn_Key_CapF_7in_nf.png";   break;
    case 15: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalG_7in_n-assets/Set_Btn_Key_CapG_7in_nf.png";   break;
    case 16: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalH_7in_n-assets/Set_Btn_Key_CapH_7in_nf.png";   break;
    case 17: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalJ_7in_n-assets/Set_Btn_Key_CapJ_7in_nf.png";   break;
    case 18: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalK_7in_n-assets/Set_Btn_Key_CapK_7in_nf.png";   break;
    case 19: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalL_7in_n-assets/Set_Btn_Key_CapL_7in_nf.png";   break;
    case 20: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalaA_7in_n-assets/Set_Btn_Key_CapaA_7in_nf.png"; break;
    case 21: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalZ_7in_n-assets/Set_Btn_Key_CapZ_7in_nf.png";   break;
    case 22: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalX_7in_n-assets/Set_Btn_Key_CapX_7in_nf.png";   break;
    case 23: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalC_7in_n-assets/Set_Btn_Key_CapC_7in_nf.png";   break;
    case 24: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalV_7in_n-assets/Set_Btn_Key_CapV_7in_nf.png";   break;
    case 25: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitaB_7in_n-assets/Set_Btn_Key_CapB_7in_nf.png";    break;
    case 26: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalN_7in_n-assets/Set_Btn_Key_CapN_7in_nf.png";   break;
    case 27: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalM_7in_n-assets/Set_Btn_Key_CapM_7in_nf.png";   break;
    case 28: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Capital,_7in_n-assets/_7in_nf.png";                   break;
    case 29: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Capital._7in_n-assets/Set_Btn_Key_Cap._7in_nf.png";   break;
    case 30: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Space_7in_n-assets/Set_Btn_Key_Space_7in_nf.png";     break;
    case 31: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_123_7in_n-assets/Set_Btn_KeyPad_123_nf.png";         break;

    default: LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: getKeyButtonDefaultImageCapital - default case, iKeyIndex: %d", __FUNCTION__, iKeyIndex); break;

    }
    return strImagePath;
}

QString CPhoneAdaptor::getKeyButtonPressedImageSmall(int iKeyIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: iKeyIndex: %d", __FUNCTION__, iKeyIndex);
    QString strImagePath = "";

    switch(iKeyIndex)
    {
    case 1:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallQ_7in_n-assets/Set_Btn_Key_SmallQ_7in_nf.png";   break;
    case 2:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallW_7in_n-assets/Set_Btn_Key_SmallW_7in_nf.png";   break;
    case 3:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallE_7in_n-assets/Set_Btn_Key_SmallE_7in_nf.png";   break;
    case 4:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallR_7in_n-assets/Set_Btn_Key_SmallR_7in_nf.png";   break;
    case 5:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallT_7in_n-assets/Set_Btn_Key_SmallT_7in_nf.png";   break;
    case 6:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallY_7in_n-assets/Set_Btn_Key_SmallY_7in_nf.png";   break;
    case 7:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallU_7in_n-assets/Set_Btn_Key_SmallU_7in_nf.png";   break;
    case 8:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallI_7in_n-assets/Set_Btn_Key_SmallI_7in_nf.png";   break;
    case 9:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallO_7in_n-assets/Set_Btn_Key_SmallO_7in_nf.png";   break;
    case 10: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallP_7in_n-assets/Set_Btn_Key_SmallP_7in_nf.png";   break;
    case 11: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallA_7in_n-assets/Set_Btn_Key_SmallA_7in_nf.png";   break;
    case 12: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallS_7in_n-assets/Set_Btn_Key_SmallS_7in_nf.png";   break;
    case 13: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallD_7in_n-assets/Set_Btn_Key_SmallD_7in_nf.png";   break;
    case 14: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallF_7in_n-assets/Set_Btn_Key_SmallF_7in_nf.png";   break;
    case 15: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallG_7in_n-assets/Set_Btn_Key_SmallG_7in_nf.png";   break;
    case 16: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallH_7in_n-assets/Set_Btn_Key_SmallH_7in_nf.png";   break;
    case 17: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallJ_7in_n-assets/Set_Btn_Key_SmallJ_7in_nf.png";   break;
    case 18: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallK_7in_n-assets/Set_Btn_Key_SmallK_7in_nf.png";   break;
    case 19: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallL_7in_n-assets/Set_Btn_Key_SmallL_7in_nf.png";   break;
    case 20: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalaA_7in_n-assets/Set_Btn_Key_CapaA_7in_nf.png"; break;
    case 21: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallZ__7in_n-assets/Set_Btn_Key_SmallZ_7in_nf.png";  break;
    case 22: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallX_7in_n-assets/Set_Btn_Key_SmallX_7in_nf.png";   break;
    case 23: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallC_7in_n-assets/Set_Btn_Key_SmallC_7in_nf.png";   break;
    case 24: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallV_7in_n-assets/Set_Btn_Key_SmallV_7in_nf.png";   break;
    case 25: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallB_7in_n-assets/Set_Btn_Key_SmallB_7in_nf.png";   break;
    case 26: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallN_7in_n-assets/Set_Btn_Key_SmallN_7in_nf.png";   break;
    case 27: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallM_7in_n-assets/Set_Btn_Key_SmallM_7in_nf.png";   break;
    case 28: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Capital,_7in_n-assets/_7in_nf.png";                   break;
    case 29: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Capital._7in_n-assets/Set_Btn_Key_Cap._7in_nf.png";   break;
    case 30: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Space_7in_n-assets/Set_Btn_Key_Space_7in_nf.png";     break;
    case 31: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_123_7in_n-assets/Set_Btn_KeyPad_123_nf.png";         break;

    default: LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: getKeyButtonDefaultImageSmall - default case, iKeyIndex: %d", __FUNCTION__, iKeyIndex); break;
    }
    return strImagePath;
}

QString CPhoneAdaptor::getKeyButtonPressedImageNumeric(int iKeyIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: getKeyButtonPressedImageCapital - default case, iKeyIndex: %d", __FUNCTION__, iKeyIndex);

    QString strImagePath = "";

    switch(iKeyIndex)
    {
    case 1:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_1_7in_n-assets/Set_Btn_Keypad_1_7in_nf.png";                        break;
    case 2:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_2_7in_n-assets/Set_Btn_Keypad_2_7in_nf.png";                        break;
    case 3:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_3_7in_n-assets/Set_Btn_Keypad_3_7in_nf.png";                        break;
    case 4:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_4_7in_n-assets/Set_Btn_Keypad_4_7in_nf.png";                        break;
    case 5:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_5_7in_n-assets/Set_Btn_Keypad_5_7in_nf.png";                        break;
    case 6:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_6_7in_n-assets/Set_Btn_Key_6_7in_nf.png";                           break;
    case 7:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_7_7in_n-assets/Set_Btn_Key_7_7in_nf.png";                           break;
    case 8:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_8_7in_n-assets/Set_Btn_Keypad_8_7in_nf.png";                        break;
    case 9:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_9_7in_n-assets/Set_Btn_Keypad_9_7in_nf.png";                        break;
    case 10: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_0_7in_n-assets/Set_Btn_Keypad_0_7in_nf.png";                        break;
    case 11: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_AtTheRate_7in_n-assets/Set_Btn_Keypad_AtTheRate_7in_nf.png";        break;
    case 12: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Hash_7in_n-assets/Set_Btn_Keypad_Hash_7in_nf.png";                  break;
    case 13: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Dollar_7in_n-assets/Set_Btn_Keypad_Dollar_7in_nf.png";              break;
    case 14: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Percentage_7in_n-assets/Set_Btn_Keypad_Percentage_7in_nf.png";      break;
    case 15: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_And_7in_n-assets/Set_Btn_Keypad_And_7in_nf.png";                    break;
    case 16: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Minus_7in_n-assets/Set_Btn_Keypad_Minus_7in_nf.png";                break;
    case 17: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Plus_7in_n-assets/Plus_7in_nf.png";                                 break;
    case 18: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Left_Bracket_7in_n-assets/Set_Btn_Keypad_Left_Bracket_7in_nf.png";  break;
    case 19: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Right_Bracket_7in_n-assets/Set_Btn_Keypad_Right_Bracket_7in_nf.png";break;
    case 20: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_1_1_7in_n-assets/Set_Btn_KeyPad_1_1_7in_nf.png";                    break;
    case 21: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Keystar_7in_n-assets/Set_Btn_Keypad_star_7in_nf.png";               break;
    case 22: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Doubleqoutations_7in_n-assets/Set_Btn_Key_2qout_nf.png";            break;
    case 23: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_singlequotation_7in_n-assets/Set_Btn_Key_1quotation_7in_nf.png";    break;
    case 24: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Colon_7in_n-assets/Set_Btn_Keypad_Colon_7in_nf.png";                break;
    case 25: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Semicolon_7in_n-assets/Set_Btn_Key_Semicolon_7in_nf.png";           break;
    case 26: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Exclaimation_7in_n-assets/Set_Btn_Keypad__Exclaimation_7in_nf.png"; break;
    case 27: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Questionmark_7in_n-assets/Set_Btn_Key_Quest_7in_nf.png";            break;
    case 28: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Capital,_7in_n-assets/_7in_nf.png";                                 break;
    case 29: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Capital._7in_n-assets/Set_Btn_Key_Cap._7in_nf.png";                 break;
    case 30: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Space_7in_n-assets/Set_Btn_Key_Space_7in_nf.png";                   break;
    case 31: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_abc_7in_n-assets/Set_Btn_Key_abc_7in_nf.png";                       break;

    default: LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: getKeyButtonDefaultImageNumeric - default case, iKeyIndex: %d", __FUNCTION__, iKeyIndex); break;
    }
    return strImagePath;
}

QString CPhoneAdaptor::getKeyButtonDisabledImageCapital(int iKeyIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: iKeyIndex: %d", __FUNCTION__, iKeyIndex);
    QString strImagePath = "";

    switch(iKeyIndex)
    {
    case 1:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalQ_7in_n-assets/Set_Btn_Key_CapQ_7in_nd.png";    break;
    case 2:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalW_7in_n-assets/Set_Btn_Key_CapW_7in_nd.png";    break;
    case 3:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalE_7in_n-assets/Set_Btn_Key_CapE_7in_nd.png";    break;
    case 4:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalR_7in_n-assets/Set_Btn_Key_CapR_7in_nd.png";    break;
    case 5:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalT_7in_n-assets/Set_Btn_Key_CapitalT_nd.png";    break;
    case 6:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalY_7in_n-assets/Set_Btn_Key_CapY_7in_nd.png";    break;
    case 7:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalU_7in_n-assets/Set_Btn_Key_CapU_7in_nd.png";    break;
    case 8:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KP_CapitalI_7in_n-assets/Set_Btn_KP_CapitalI_7in_nd.png";     break;
    case 9:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalO_7in_n-assets/Set_Btn_Key_CapO_7in_nd.png";    break;
    case 10: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalP_7in_n-assets/Set_Btn_Key_CapP_7in_nd.png";    break;
    case 11: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalA_7in_n-assets/Set_Btn_Key_CapA_7in_nd.png";    break;
    case 12: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalS_7in_n-assets/Set_Btn_Key_CapS_7in_nd.png";    break;
    case 13: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalD_7in_n-assets/Set_Btn_Key_CapD_7in_nd.png";    break;
    case 14: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalF_7in_n-assets/Set_Btn_Key_CapF_7in_nd.png";    break;
    case 15: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalG_7in_n-assets/Set_Btn_Key_CapG_7in_nd.png";    break;
    case 16: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalH_7in_n-assets/Set_Btn_Key_CapH_7in_nd.png";    break;
    case 17: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalJ_7in_n-assets/Set_Btn_Key_CapJ_7in_nd.png";    break;
    case 18: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalK_7in_n-assets/Set_Btn_Key_CapK_7in_nd.png";    break;
    case 19: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalL_7in_n-assets/Set_Btn_Key_CapL_7in_nd.png";    break;
    case 20: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalaA_7in_n-assets/Set_Btn_Key_CapaA_7in_nd.png";  break;
    case 21: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalZ_7in_n-assets/Set_Btn_Key_CapZ_7in_nd.png";    break;
    case 22: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalX_7in_n-assets/Set_Btn_Key_CapX_7in_nd.png";    break;
    case 23: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalC_7in_n-assets/Set_Btn_Key_CapC_7in_nd.png";    break;
    case 24: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalV_7in_n-assets/Set_Btn_Key_CapV_7in_nd.png";    break;
    case 25: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitaB_7in_n-assets/Set_Btn_Key_CapB_7in_nd.png";     break;
    case 26: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalN_7in_n-assets/Set_Btn_Key_CapN_7in_nd.png";    break;
    case 27: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalM_7in_n-assets/Set_Btn_Key_CapM_7in_nd.png";    break;
    case 28: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Capital,_7in_n-assets/_7in_nd.png";                    break;
    case 29: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Capital._7in_n-assets/Set_Btn_Key_Cap._7in_nd.png";    break;
    case 30: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Space_7in_n-assets/Set_Btn_Key_Space_7in_nd.png";      break;
    case 31: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_123_7in_n-assets/Set_Btn_KeyPad_123_nd.png";          break;

    default: LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: getKeyButtonDefaultImageCapital - default case, iKeyIndex: %d", __FUNCTION__, iKeyIndex); break;

    }
    return strImagePath;
}

QString CPhoneAdaptor::getKeyButtonDisabledImageSmall(int iKeyIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: iKeyIndex: %d", __FUNCTION__, iKeyIndex);
    QString strImagePath = "";

    switch(iKeyIndex)
    {
    case 1:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallQ_7in_n-assets/Set_Btn_Key_SmallQ_7in_nd.png";    break;
    case 2:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallW_7in_n-assets/Set_Btn_Key_SmallW_7in_nd.png";    break;
    case 3:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallE_7in_n-assets/Set_Btn_Key_SmallE_7in_nd.png";    break;
    case 4:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallR_7in_n-assets/Set_Btn_Key_SmallR_7in_nd.png";    break;
    case 5:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallT_7in_n-assets/Set_Btn_Key_SmallT_7in_nd.png";    break;
    case 6:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallY_7in_n-assets/Set_Btn_Key_SmallY_7in_nd.png";    break;
    case 7:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallU_7in_n-assets/Set_Btn_Key_SmallU_7in_nd.png";    break;
    case 8:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallI_7in_n-assets/Set_Btn_Key_SmallI_7in_nd.png";    break;
    case 9:  strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallO_7in_n-assets/Set_Btn_Key_SmallO_7in_nd.png";    break;
    case 10: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallP_7in_n-assets/Set_Btn_Key_SmallP_7in_nd.png";    break;
    case 11: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallA_7in_n-assets/Set_Btn_Key_SmallA_7in_nd.png";    break;
    case 12: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallS_7in_n-assets/Set_Btn_Key_SmallS_7in_nd.png";    break;
    case 13: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallD_7in_n-assets/Set_Btn_Key_SmallD_7in_nd.png";    break;
    case 14: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallF_7in_n-assets/Set_Btn_Key_SmallF_7in_nd.png";    break;
    case 15: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallG_7in_n-assets/Set_Btn_Key_SmallG_7in_nd.png";    break;
    case 16: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallH_7in_n-assets/Set_Btn_Key_SmallH_7in_nd.png";    break;
    case 17: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallJ_7in_n-assets/Set_Btn_Key_SmallJ_7in_nd.png";    break;
    case 18: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallK_7in_n-assets/Set_Btn_Key_SmallK_7in_nd.png";    break;
    case 19: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallL_7in_n-assets/Set_Btn_Key_SmallL_7in_nd.png";    break;
    case 20: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_CapitalaA_7in_n-assets/Set_Btn_Key_CapaA_7in_nd.png";  break;
    case 21: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallZ__7in_n-assets/Set_Btn_Key_SmallZ_7in_nd.png";   break;
    case 22: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallX_7in_n-assets/Set_Btn_Key_SmallX_7in_nd.png";    break;
    case 23: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallC_7in_n-assets/Set_Btn_Key_SmallC_7in_nd.png";    break;
    case 24: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallV_7in_n-assets/Set_Btn_Key_SmallV_7in_nd.png";    break;
    case 25: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallB_7in_n-assets/Set_Btn_Key_SmallB_7in_nd.png";    break;
    case 26: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallN_7in_n-assets/Set_Btn_Key_SmallN_7in_nd.png";    break;
    case 27: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_SmallM_7in_n-assets/Set_Btn_Key_SmallM_7in_nd.png";    break;
    case 28: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Capital,_7in_n-assets/_7in_nd.png";                    break;
    case 29: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Capital._7in_n-assets/Set_Btn_Key_Cap._7in_nd.png";    break;
    case 30: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Space_7in_n-assets/Set_Btn_Key_Space_7in_nd.png";      break;
    case 31: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_123_7in_n-assets/Set_Btn_KeyPad_123_nd.png";          break;

    default: LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: getKeyButtonDefaultImageSmall - default case, iKeyIndex: %d", __FUNCTION__, iKeyIndex); break;
    }
    return strImagePath;
}

QString CPhoneAdaptor::getKeyButtonDisabledImageNumeric(int iKeyIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: iKeyIndex: %d", __FUNCTION__, iKeyIndex);
    QString strImagePath = "";

    switch(iKeyIndex)
    {
    case 1:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_1_7in_n-assets/Set_Btn_Keypad_1_7in_nd.png";                        break;
    case 2:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_2_7in_n-assets/Set_Btn_Keypad_2_7in_nd.png";                        break;
    case 3:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_3_7in_n-assets/Set_Btn_Keypad_3_7in_nd.png";                        break;
    case 4:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_4_7in_n-assets/Set_Btn_Keypad_4_7in_nd.png";                        break;
    case 5:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_5_7in_n-assets/Set_Btn_Keypad_5_7in_nd.png";                        break;
    case 6:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_6_7in_n-assets/Set_Btn_Key_6_7in_nd.png";                           break;
    case 7:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_7_7in_n-assets/Set_Btn_Key_7_7in_nd.png";                           break;
    case 8:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_8_7in_n-assets/Set_Btn_Keypad_8_7in_nd.png";                        break;
    case 9:  strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_9_7in_n-assets/Set_Btn_Keypad_9_7in_nd.png";                        break;
    case 10: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_0_7in_n-assets/Set_Btn_Keypad_0_7in_nd.png";                        break;
    case 11: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_AtTheRate_7in_n-assets/Set_Btn_Keypad_AtTheRate_7in_nd.png";        break;
    case 12: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Hash_7in_n-assets/Set_Btn_Keypad_Hash_7in_nd.png";                  break;
    case 13: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Dollar_7in_n-assets/Set_Btn_Keypad_Dollar_7in_nd.png";              break;
    case 14: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Percentage_7in_n-assets/Set_Btn_Keypad_Percentage_7in_nd.png";      break;
    case 15: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_And_7in_n-assets/Set_Btn_Keypad_And_7in_nd.png";                    break;
    case 16: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Minus_7in_n-assets/Set_Btn_Keypad_Minus_7in_nd.png" ;               break;
    case 17: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Plus_7in_n-assets/Plus_7in_nd.png";                                 break;
    case 18: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Left_Bracket_7in_n-assets/Set_Btn_Keypad_Left_Bracket_7in_nd.png";  break;
    case 19: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Right_Bracket_7in_n-assets/Set_Btn_Keypad_Right_Bracket_7in_nd.png";break;
    case 20: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_1_1_7in_n-assets/Set_Btn_KeyPad_1_1_7in_nd.png";                    break;
    case 21: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Keystar_7in_n-assets/Set_Btn_Keypad_star_7in_nd.png";               break;
    case 22: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Doubleqoutations_7in_n-assets/Set_Btn_Key_2qout_nd.png";            break;
    case 23: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_singlequotation_7in_n-assets/Set_Btn_Key_1quotation_7in_nd.png";    break;
    case 24: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Colon_7in_n-assets/Set_Btn_Keypad_Colon_7in_nd.png";                break;
    case 25: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Semicolon_7in_n-assets/Set_Btn_Key_Semicolon_7in_nd.png";           break;
    case 26: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Exclaimation_7in_n-assets/Set_Btn_Keypad__Exclaimation_7in_nd.png"; break;
    case 27: strImagePath = "qrc:/image/KeyPad/Set_Btn_Keypad_Questionmark_7in_n-assets/Set_Btn_Key_Quest_7in_nd.png";            break;
    case 28: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Capital,_7in_n-assets/_7in_nd.png";                                 break;
    case 29: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Capital._7in_n-assets/Set_Btn_Key_Cap._7in_nd.png";                 break;
    case 30: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_Space_7in_n-assets/Set_Btn_Key_Space_7in_nd.png";                   break;
    case 31: strImagePath = "qrc:/image/KeyPad/Set_Btn_KeyPad_abc_7in_n-assets/Set_Btn_Key_abc_7in_nd.png";                       break;

    default: LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: getKeyButtonDefaultImageNumeric - default case, iKeyIndex: %d", __FUNCTION__, iKeyIndex); break;
    }
    return strImagePath;
}

QChar CPhoneAdaptor::getClickedCharacter(CPhoneEnum::EKeyPadState eKeypadState, int iCharIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: eKeypadState: %d,  iCharIndex: %d", __FUNCTION__, static_cast<int> (eKeypadState), iCharIndex);

    if(((iCharIndex >= 0) && (iCharIndex < KEYPAD_CHAR_ARRAY_COLUMNS)) && ((static_cast<int> (eKeypadState) >= -1) && (static_cast<int> (eKeypadState) < 3)))
    {
        return m_aKeypadCharacters[static_cast<int> (eKeypadState)][iCharIndex];
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: Index of Out Bound ,iCharIndex: %d", __FUNCTION__, iCharIndex);
        return -1;
    }
}

void CPhoneAdaptor::saveButtonClicked(const QString &strMessage)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: Index: %d, Message: %s", __FUNCTION__, m_iCurrentMessageIndex, strMessage.toStdString().c_str());
    //FixMe: When read & write strings into persistency is done, write SMS content into persistency
    /** Updating the SMS content model data and updating corresponding lists containing message */
    m_pPhoneSetupListModel->updateConfigureMessageList(m_iCurrentMessageIndex, strMessage);
}

void CPhoneAdaptor::editButtonClicked(const QString &strMessage, int iIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: Index: %d, Message: %s", __FUNCTION__, iIndex, strMessage.toStdString().c_str());
    m_iCurrentMessageIndex = iIndex;
    if(m_strCurrentMessageText != strMessage)
    {
        m_strCurrentMessageText = strMessage;
        emit sigTextInputMessageChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, Message content not changed", __FUNCTION__);
    }
}

QString CPhoneAdaptor::textInputMessage()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s", __FUNCTION__);
    return m_strCurrentMessageText;
}

/************************************************************************//**
 * @category    INTERNAL METHODS
 ************************************************************************/
void CPhoneAdaptor::invResetSelectedItemInfo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s", __FUNCTION__);
    m_strSelItemBtAddr  = "";
    m_strSelItemName    = "";
}

void CPhoneAdaptor::invSetLowPriorityPopupActiveStatus(bool bLPPhonePopupStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: bLPPhonePopupStatus: %d ", __FUNCTION__, bLPPhonePopupStatus);
    if(m_bLPPhonePopupStatus != bLPPhonePopupStatus)
    {
        m_bLPPhonePopupStatus = bLPPhonePopupStatus;
        emit sigLowPriorityPopupActiveUpdated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Values are same for bLPPhonePopupStatus", __FUNCTION__);
    }

}

bool CPhoneAdaptor::selectContactDetailsCategory(const QString &strCategory)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: strCategory: %s ", __FUNCTION__, strCategory.toStdString().c_str());
    bool bRet = false;

    EContactType eContactType = EContactType::CONTACT_TYPE_DEFAULT;

    if(strCategory.toLower() == "mobile")
    {
        eContactType = EContactType::CONTACT_TYPE_MOBILE;
    }
    else if(strCategory.toLower() == "work")
    {
        eContactType = EContactType::CONTACT_TYPE_WORK;
    }
    else if(strCategory.toLower() == "home")
    {
        eContactType = EContactType::CONTACT_TYPE_HOME;
    }
    else if(strCategory.toLower() == "other")
    {
        eContactType = EContactType::CONTACT_TYPE_OTHER;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: Wrong contact details category passed", __FUNCTION__);
    }

    if(m_pContactDetailListModel)
    {
        for(int iIndex = 0; iIndex < m_pContactDetailListModel->rowCount(); iIndex++)
        {
            if(eContactType == static_cast<EContactType>(m_pContactDetailListModel->getContactTypeFromIndex(iIndex)))
            {
                emit sigHighlightContactCategory(iIndex);
                bRet = true;
                break;
            }
            else
            {
                //do nothing
            }
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "contact detail list model object not created");
    }

    return bRet;
}

void CPhoneAdaptor::closeAllPhoneBtPopups()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s", __FUNCTION__);
    if(CPopupManager::getInstance())
    {
        //force close all bt related connecting/disconnecting/connected/disconnected popups
        CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTING);
        CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTED);
        CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTION_FAILED);
        CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DISCONNECTING);
        CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DISCONNECTED);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "popup manager object not created");
    }
}

void CPhoneAdaptor::resetCallInfo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s", __FUNCTION__);
    m_objIncomingCallInfo.clear();
    m_objFirstCallerInfo.clear();
    m_objSecondCallerInfo.clear();
}

void CPhoneAdaptor::resetRequestStatusProperties()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s", __FUNCTION__);
    //reseting values using set function
    setAcceptCallReqStatus(false);
    setRejectCallReqStatus(false);
    setSendSMSReqStatus(false);
    setDialReqStatus(false);
    setMergeCallsReqStatus(false);
    setSwapCallsReqStatus(false);
    setResumeCallReqStatus(false);
    setHoldCallReqStatus(false);
    setEndCallReqStatus(false);
    setHFModeReqStatus(false);
}

void CPhoneAdaptor::resetPimdbProperties()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_pCallLogListModel)
        m_pCallLogListModel->removeRows();

    if(m_pFrequentlyDialedListModel)
        m_pFrequentlyDialedListModel->removeRows();

    if(m_pContactListModel)
        m_pContactListModel->removeRows();

    invResetContactDetailList();

    if(m_pFavoriteContactListModel)
        m_pFavoriteContactListModel->removeRows();

    m_ePimDbCallListSyncState               = CPhoneEnum::PHONE_DATA_READ_OFF;
    m_ePimDbContactListSyncState            = CPhoneEnum::PHONE_DATA_READ_OFF;
    m_ePimDbContactDetailListSyncState      = CPhoneEnum::PHONE_DATA_READ_OFF;
    m_ePimDbFavouriteListSyncState          = CPhoneEnum::PHONE_DATA_READ_OFF;
    m_ePimDbFrequentlyDialedListSyncState   = CPhoneEnum::PHONE_DATA_READ_OFF;
}

void CPhoneAdaptor::resetHFPData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    //raise event to switch to home screen
    CHMIMain::getSM()->getSCI_Phone()->raise_evHFPDisconnect();
    //abort sms readout
    invStopSmsReadout();
    //Close sms incoming popup
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_SMS_POPUP);
    //Close sms reading popup
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SMS_READING_POPUP);
    //Close sms reading complete popup
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SMS_READING_COMPLETE_POPUP);
    //Close low priority sms popup
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_LOW_PRIORITY_SMS_POPUP);
    //Reset phone information to default whenever device is disconnected for hfp profile
    resetPhoneInformation();
    //Reset sms details info
    resetSMSDetails();
    //Reset reading sms details
    resetReadingSMSDetails();
    //Reset pimdb related properties
    resetPimdbProperties();
    //Reset Phone BT VR mode status
    m_bPhoneBtVrModeStatus = false;
    //Hide Phone BT VR overlay
    showHidePhoneBtVROverlay(false);
}

void CPhoneAdaptor::resetPhoneInformation()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s", __FUNCTION__);
    m_strConnectedDeviceAddr    = "";
    m_bIsHandsFreeMode          = true;
    m_bIsNetworkAvailable       = false;
    m_bShowIncomingSmsPopup     = false;
    m_bBtVrSupported            = false;
    m_bApplePhoneConnected      = false;
    setBatteryCharge(BATTERY_CHARGE_LEVEL_INVALID);
    setSignalStrength(SIGNAL_LEVEL_INVALID);
    m_objConfParticipantsListModel.removeRows();
    invResetUnreadMissedCallInfo();
}

void CPhoneAdaptor::resetPhoneAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s", __FUNCTION__);
    resetPhoneConnectionData();
    resetPhoneCallData();
    resetPhonePimDbData();
    resetRequestStatusProperties();
}

void CPhoneAdaptor::resetPhoneConnectionData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s", __FUNCTION__);
    resetHFPData();
    invClearDeviceSearchList();
    updatePassKey("");
    setDisconnectedDeviceName("");
    setDeletedDeviceName("");
    updateDeviceSearchStatus(false);
    invResetSelectedItemInfo();
    setConnectedDeviceName("");
    setHFPConnectionStatusType(EConnectionStatus::CONNECTION_STATUS_DEFAULT);
    setA2DPConnectionStatusType(EConnectionStatus::CONNECTION_STATUS_DEFAULT);
    setDeviceConnectionStatus(false);

    if(m_pPairedDeviceListModel)
    {
        m_pPairedDeviceListModel->removeRows();
        //Reset the paired device List Count to 0 whenever the service crashes.
        m_iPreviousPairedListCount = 0;
        m_iCurrentPairedListCount = 0;
    }

    m_bIsDeleteAllSelected      = false;
    m_bDeleteAllDevicesStatus   = false;
    m_bDeleteDeviceStatus       = false;
    m_strConnectedDeviceAddr    = "";
    m_bHUDiscoverableStatus     = false;
    m_bBtVisibilityReqStatus    = false;

    //Fore close all phone connection manager proxy related popups
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DEVICE_LIMIT_REACHED);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_TURN_ON_BLUETOOTH);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_BT_DEVICES_NOT_FOUND);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_PREVIOUS_DEVICE_DISCONNECTION);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_PASSKEY);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_EXTERNAL_PAIRING_REQUEST);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_PAIRING_FAILED);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DETERMINING_BT_SERVICES);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTING);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTED);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_CONNECTION_FAILED);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DISCONNECTING);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DISCONNECTED);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_DEVICE_CONFIRMATION);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETING_DEVICE);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_DEVICE_SUCCESS);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_DEVICE_FAILED);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_ALL_DEVICES_CONFIRMATION);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETING_ALL_DEVICES);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_ALL_DEVICES_SUCCESS);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_ALL_DEVICES_FAILED);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_ONLY_A2DP_CONNECTED);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DEVICE_BATTERY_LOW);
}

void CPhoneAdaptor::resetPhoneCallData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s", __FUNCTION__);
    ringtoneSourceDeactivated();
    hfpSourceDeactivated();
    m_objEndCallScreenTimer.stop();
    m_ePhoneNetworkRegState = PHONE_NETWORK_REGSTATE_UNKNOWN;

    //Force close all call proxy related popups
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_CALL_POPUP);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_NO_NETWORK_AVAILABLE);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_LOW_PRIORITY_CALL_POPUP);
}

void CPhoneAdaptor::resetPhonePimDbData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s", __FUNCTION__);
    setIsSendingSMSAllowed(false);
    resetFavoriteToggleInfo();
    setContactListCurrentTopIndex(0);
    updateTTSPlayStateStatus(CPhoneEnum::EN_PLAY_STATE_NOTPLAYING);
    setCurrentPhoneBrowseScreen(CPhoneEnum::PHONE_BROWSE_TYPE_CALL_LOGS);
    invChangeDTMFNumberPadStatus(false);
    invSetLowPriorityPopupActiveStatus(false);

    m_iCurrentMessageIndex                  = -1;
    m_strCurrentMessageText                 = "";
    m_bSMSAvailable                         = false;
    m_bStartNewSmsReadout                   = false;
    m_bIsOldestConnDeviceDeletionRequested  = false;

    //Force close all pimdb proxy related popups
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_SMS_POPUP);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SMS_READING_POPUP);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SMS_READING_COMPLETE_POPUP);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_LOW_PRIORITY_SMS_POPUP);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SENDING_SMS);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_SMS_SENT);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_BROWSE_FAVORITE_ADDED);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_BROWSE_FAVORITE_REMOVED);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_BROWSE_FAVORITE_REMOVE_CONFIRMATION);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_BROWSE_FAVORITE_LIST_FULL);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_BROWSE_ADD_FAVORITE_FAILED);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_BROWSE_REMOVE_FAVORITE_FAILED);
}

const SCallStateInfo* CPhoneAdaptor::getCallInfo(const vector<SCallStateInfo>& vectCallStateInfo, ECallState eCallState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s", __FUNCTION__);
    const SCallStateInfo* pCallInfo = NULL;
    int iCallInfoListSize = static_cast<int>(vectCallStateInfo.size());
    for(int iIndex = 0; iIndex < iCallInfoListSize; iIndex++)
    {
        if(eCallState == vectCallStateInfo.at(iIndex).m_eCallState)
        {
            pCallInfo = &vectCallStateInfo.at(iIndex);
            break;
        }
    }
    return pCallInfo;
}

int CPhoneAdaptor::getConferenceParicipantsCount(const vector<SCallStateInfo>& vectCallStateInfo, ECallState eCallState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s", __FUNCTION__);
    int iCount = 0;
    if(m_pPhCallMgrResource)
    {
        int iCallInfoListSize = static_cast<int>(vectCallStateInfo.size());
        //Clear conference participant list model
        m_objConfParticipantsListModel.removeRows();
        bool bHangupEnhancedSupported  = false;
        if((!m_pPhCallMgrResource->getHfpSupportedFeatureList().empty()) && (m_pPhCallMgrResource->getHfpSupportedFeatureList().at(0).m_mapSupportedFeatures.count(PHONE_FEATURE_HANGUP_ENH) > 0))
        {
            bHangupEnhancedSupported = m_pPhCallMgrResource->getHfpSupportedFeatureList().at(0).m_mapSupportedFeatures.at(PHONE_FEATURE_HANGUP_ENH);
        }
        for(int iIndex = 0; iIndex < iCallInfoListSize; iIndex++)
        {
            if(eCallState == vectCallStateInfo.at(iIndex).m_eCallState)
            {
                iCount++;
                //Insert participant information in conference participant list
                CPhoneData::SConfParticipantInfo objConfParticipantInfo;
                QString strContactName = QString::fromStdString(vectCallStateInfo.at(iIndex).m_strContactName);
                objConfParticipantInfo.m_strName                = (strContactName.compare("") != 0) ?
                            strContactName :
                            QString::fromStdString(vectCallStateInfo.at(iIndex).m_strContactNumber);
                objConfParticipantInfo.m_iCalldId               = vectCallStateInfo.at(iIndex).m_iCallId;
                objConfParticipantInfo.m_bHangupEnhancedStatus  = bHangupEnhancedSupported;
                m_objConfParticipantsListModel.insertRows(objConfParticipantInfo);
            }
        }
    }
    return iCount;
}

int CPhoneAdaptor::getCallType(int iPimDbCallType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: iPimdbCallType: %d", __FUNCTION__, iPimDbCallType);

    int iCallType = CPhoneEnum::CALL_TYPE_UNKNOWN;

    switch (iPimDbCallType)
    {
    case BTPresTypes::eDatabaseType::DB_TYPE_MISSED_CALLSTACK:
    {
        iCallType = CPhoneEnum::CALL_TYPE_MISSED;
    }
        break;
    case BTPresTypes::eDatabaseType::DB_TYPE_DIALLED_CALLSTACK:
    {
        iCallType = CPhoneEnum::CALL_TYPE_OUTGOING;
    }
        break;
    case BTPresTypes::eDatabaseType::DB_TYPE_RECEIVED_CALLSTACK:
    {
        iCallType = CPhoneEnum::CALL_TYPE_INCOMING;
    }
        break;
    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "Call Type %d NOT HANDLED", iPimDbCallType);
    }
        break;
    }
    return iCallType;
}

QString CPhoneAdaptor::getContactTypeText(int iContactType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: iContactType: %d", __FUNCTION__, iContactType);
    QString strContactType = "";
    switch (iContactType)
    {
    case EContactType::CONTACT_TYPE_MOBILE:
    {
        strContactType = "Mobile";
    }
        break;
    case EContactType::CONTACT_TYPE_HOME:
    {
        strContactType = "Home";
    }
        break;
    case EContactType::CONTACT_TYPE_WORK:
    {
        strContactType = "Work";
    }
        break;
    case EContactType::CONTACT_TYPE_OTHER:
    {
        strContactType = "Other";
    }
        break;
    default:
    {
        strContactType = "";
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "Contact Type %d NOT HANDLED", iContactType);
    }
        break;
    }
    return strContactType;
}


void CPhoneAdaptor::setCurrentPhoneBrowseScreen(CPhoneEnum::EPhoneBrowseType eCurrentScreen)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: eCurrentScreen: %d", __FUNCTION__, static_cast<int>(eCurrentScreen));
    if(eCurrentScreen != m_eCurrentPhoneBrowseScreen)
    {
        m_eCurrentPhoneBrowseScreen = eCurrentScreen;
        emit sigCurrentPhoneBrowseScreenChanged();
    }
}
void CPhoneAdaptor::activateSMCallState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s", __FUNCTION__);
    CHMIMain::getSM()->raise_evPhoneCallActivated();
}

void CPhoneAdaptor::incrementUnreadMissedCallCount(unsigned int uiMissedCallCount)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: missed call count - %d", __FUNCTION__, uiMissedCallCount);
    m_uiUnreadMissedCallCount += uiMissedCallCount;
    if(m_uiUnreadMissedCallCount == 0)
    {
        m_strPhoneNotificationText = tr("TEXT_QAD_NOTIFY_LABEL_NO_NEW_NOTIFICATIONS");
    }
    else if(m_uiUnreadMissedCallCount == 1)
    {
        m_strPhoneNotificationText = tr("TEXT_QAD_NOTIFY_LABEL_MISSED_CALL");
    }
    else
    {
        m_strPhoneNotificationText = QString::number(m_uiUnreadMissedCallCount) + tr("TEXT_QAD_NOTIFY_LABEL_MISSED_CALLS");
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: phone notification text - %s", __FUNCTION__, m_strPhoneNotificationText.toStdString().c_str());
    emit sigPhoneNotificationTextChanged();
}

void CPhoneAdaptor::updateCallInPdcRvc()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_CALL_POPUP);
    CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_LOW_PRIORITY_CALL_POPUP);
}

void CPhoneAdaptor::updateCallInNative()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_LOW_PRIORITY_CALL_POPUP);
    if(isCallIncoming())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: call is incoming", __FUNCTION__);
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"[KPI_MARKER][HMI][ show incoming call indication on HMI]");
        if(m_ePhoneCallState == CPhoneEnum::PHONE_CALLSTATE_INCOMING_CALL)
        {
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_CALL_POPUP);
        }
        else
        {
            CHMIMain::getSM()->getSCI_Phone()->set_bIsPhoneCallStateActivated(true);
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_CALL_POPUP);
            activateSMCallState();
        }

    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: call is not incoming", __FUNCTION__);
        activateSMCallState();
    }
}

EConnectionStatus CPhoneAdaptor::getHFPConnectionStatusType()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    return m_eHFPConnectionStatus;
}

void CPhoneAdaptor::setHFPConnectionStatusType(EConnectionStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: eStatus: %d", __FUNCTION__, static_cast<int>(eStatus));
    CHMIMain::getInstance()->getSM()->getSCI_Phone()->set_bIsPhoneConnectedInHFP(eStatus == EConnectionStatus::CONNECTION_STATUS_CONNECTED);
    updateHFPConnectionStatus(eStatus == EConnectionStatus::CONNECTION_STATUS_CONNECTED);
    m_eHFPConnectionStatus = eStatus;
}

void CPhoneAdaptor::updateHFPConnectionStatus(bool bIsHfpConnected)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bIsHfpConnected: %d", __FUNCTION__, bIsHfpConnected);
    if(m_bIsHFPConnected != bIsHfpConnected)
    {
        m_bIsHFPConnected = bIsHfpConnected;
        emit sigHFPConnectionStatus();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: value of hfp connection status is unchanged", __FUNCTION__);
    }
}

EConnectionStatus CPhoneAdaptor::getA2DPConnectionStatusType()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    return m_eA2DPConnectionStatus;
}

void CPhoneAdaptor::setA2DPConnectionStatusType(EConnectionStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: eStatus: %d", __FUNCTION__, static_cast<int>(eStatus));
    CHMIMain::getInstance()->getSM()->getSCI_Phone()->set_bIsPhoneConnectedInA2DP(eStatus == EConnectionStatus::CONNECTION_STATUS_CONNECTED);
    m_bIsA2DPConnected = (eStatus == EConnectionStatus::CONNECTION_STATUS_CONNECTED);
    m_eA2DPConnectionStatus = eStatus;
}

void CPhoneAdaptor::updateSmsInPdcRvc()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPopupManager::getInstance())
    {
        CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_SMS_POPUP);
        m_bShowIncomingSmsPopup = true;
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_LOW_PRIORITY_SMS_POPUP);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: do not show incoming sms popup", __FUNCTION__);
    }
}

void CPhoneAdaptor::updateSmsInNative()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPopupManager::getInstance())
    {
        CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_LOW_PRIORITY_SMS_POPUP);
        m_bShowIncomingSmsPopup = true;
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_SMS_POPUP);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: do not show incoming sms popup", __FUNCTION__);
    }
}

void CPhoneAdaptor::ringtoneSourceDeactivated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_LOW_PRIORITY_CALL_POPUP);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_CALL_POPUP);
    //Clear the first caller info
    m_objIncomingCallInfo.clear();
    ResourceFactory::getICCastResource()->setIcRenderPhoneCallStateAsyncReq(EICRenderPhoneCallState::EN_ICRENDER_STATE_NO_PHONE_CALL, "", -1);
    //Reset the call state to default(idle state) after raising phone call deactivation
    setPhoneCallState(CPhoneEnum::PHONE_CALLSTATE_IDLE);
}

void CPhoneAdaptor::hfpSourceDeactivated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    CHMIMain::getSM()->getSCI_Phone()->set_bIsPhoneCallStateActivated(false);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_LOW_PRIORITY_CALL_POPUP);
    CHMIMain::getSM()->getDefaultSCI()->raise_evPhoneCallDeactivated();
    //Clear the first and second caller info
    m_objFirstCallerInfo.clear();
    m_objSecondCallerInfo.clear();
    ResourceFactory::getICCastResource()->setIcRenderPhoneCallStateAsyncReq(EICRenderPhoneCallState::EN_ICRENDER_STATE_NO_PHONE_CALL, "", -1);
    //Reset the call state to default(idle state) after raising phone call deactivation
    setPhoneCallState(CPhoneEnum::PHONE_CALLSTATE_IDLE);
}

void CPhoneAdaptor::updateIncomingCallInfo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    const SCallStateInfo* pCallInfo = getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_RINGING);
    if(pCallInfo)
    {
        //First caller is set as incoming call
        setIncomingCallInfo(pCallInfo->m_iCallId, QString::fromStdString(pCallInfo->m_strContactName),
                            QString::fromStdString(pCallInfo->m_strContactNumber),
                            QString::fromStdString(pCallInfo->m_strContactImageUrl),
                            CPhoneEnum::CALLER_INACTIVE);
        string strContactNameNum = (pCallInfo->m_strContactName == "") ? pCallInfo->m_strContactNumber : pCallInfo->m_strContactName;
        ResourceFactory::getICCastResource()->setIcRenderPhoneCallStateAsyncReq(EICRenderPhoneCallState::EN_ICRENDER_STATE_INCOMING_CALL,
                                                                                strContactNameNum, pCallInfo->m_iCallId);
    }
    //Clear first and second caller info
    m_objFirstCallerInfo.clear();
    m_objSecondCallerInfo.clear();
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"[KPI_MARKER][HMI][ show incoming call indication on HMI]");
    if((CParkAssistAdaptor::getInstance()) && (CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus()))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: reverse gear is engaged, show low priority call popup", __FUNCTION__);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_LOW_PRIORITY_CALL_POPUP);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: reverse gear is disengaged, show full call popup", __FUNCTION__);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_CALL_POPUP);
    }
}

void CPhoneAdaptor::updateSingleCallInfo(bool bIsCallActive)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bIsCallActive: %d", __FUNCTION__, bIsCallActive);
    //Close incoming call popup whenever new call state is received
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_CALL_POPUP);
    const SCallStateInfo* pCallInfo                 = NULL;
    CPhoneEnum::ECallerState eFirstCallerState      = CPhoneEnum::CALLER_UNAVAILABLE;
    EICRenderPhoneCallState eICRenderPhoneCallState = EICRenderPhoneCallState::EN_ICRENDER_STATE_INVALID_CALL_STATE;

    //First caller is set as active/held call
    if(bIsCallActive)
    {
        eFirstCallerState       = CPhoneEnum::CALLER_ACTIVE;
        pCallInfo               = getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_ACTIVE);
        eICRenderPhoneCallState = EICRenderPhoneCallState::EN_ICRENDER_STATE_ACTIVE_CALL;
    }
    else
    {
        eFirstCallerState       = CPhoneEnum::CALLER_ON_HOLD;
        pCallInfo               = getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_ON_HOLD);
        eICRenderPhoneCallState = EICRenderPhoneCallState::EN_ICRENDER_STATE_CALL_ONHOLD;
    }

    if(pCallInfo)
    {
        setFirstCallerInfo(pCallInfo->m_iCallId, QString::fromStdString(pCallInfo->m_strContactName),
                           QString::fromStdString(pCallInfo->m_strContactNumber),
                           QString::fromStdString(pCallInfo->m_strContactImageUrl),
                           eFirstCallerState, false, true);

        string strContactNameNum = (pCallInfo->m_strContactName == "") ? pCallInfo->m_strContactNumber : pCallInfo->m_strContactName;
        ResourceFactory::getICCastResource()->setIcRenderPhoneCallStateAsyncReq(eICRenderPhoneCallState, strContactNameNum, pCallInfo->m_iCallId);
    }
    //Clear second caller info
    m_objSecondCallerInfo.clear();
    showPhoneCallScreen();
}

void CPhoneAdaptor::updateConferenceCallInfo(bool bIsConferenceCallActive)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bIsConferenceCallActive: %d", __FUNCTION__, bIsConferenceCallActive);
    //Close incoming call popup whenever new call state is received
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_CALL_POPUP);
    const SCallStateInfo* pCallInfo                 = NULL;
    QString strConfParticipantCount                 = "";
    CPhoneEnum::ECallerState eFirstCallerState      = CPhoneEnum::CALLER_UNAVAILABLE;
    EICRenderPhoneCallState eICRenderPhoneCallState = EICRenderPhoneCallState::EN_ICRENDER_STATE_INVALID_CALL_STATE;
    //First caller is set to conference call
    if(bIsConferenceCallActive)
    {
        eFirstCallerState		= CPhoneEnum::CALLER_ACTIVE;
        pCallInfo				= getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_ACTIVE);
        strConfParticipantCount = QString::number(getConferenceParicipantsCount
                                                  (m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo,
                                                   CALL_STATE_ACTIVE));
        eICRenderPhoneCallState = EICRenderPhoneCallState::EN_ICRENDER_STATE_ACTIVE_CONF_CALL;
    }
    else
    {
        eFirstCallerState		= CPhoneEnum::CALLER_ON_HOLD;
        pCallInfo				= getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_ON_HOLD);
        strConfParticipantCount = QString::number(getConferenceParicipantsCount
                                                  (m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo,
                                                   CALL_STATE_ON_HOLD));
        eICRenderPhoneCallState = EICRenderPhoneCallState::EN_ICRENDER_STATE_CALL_ONHOLD;
    }
    if(pCallInfo)
    {
        setFirstCallerInfo(CPhoneData::CONFERENCE_CALL_ID, tr("TEXT_PHONE_CALL_CONFERENCE"), strConfParticipantCount + tr("TEXT_PHONE_CALL_PARTICIPANTS"), "", eFirstCallerState);
        ResourceFactory::getICCastResource()->setIcRenderPhoneCallStateAsyncReq(eICRenderPhoneCallState, "", CPhoneData::CONFERENCE_CALL_ID);
    }
    //Clear second caller info
    m_objSecondCallerInfo.clear();
    showPhoneCallScreen();
}

void CPhoneAdaptor::updateOutgoingCallInfo(bool bIsCallDialing)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bIsCallDialing: %d", __FUNCTION__, bIsCallDialing);
    //Close incoming call popup whenever new call state is received
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_CALL_POPUP);
    const SCallStateInfo* pCallInfo				= NULL;
    //First caller is set to dialing/alerting call
    if(bIsCallDialing)
    {
        pCallInfo = getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_DIALING);
    }
    else
    {
        pCallInfo = getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_ALERTING);
    }

    if(pCallInfo)
    {
        setFirstCallerInfo(pCallInfo->m_iCallId, QString::fromStdString(pCallInfo->m_strContactName),
                           QString::fromStdString(pCallInfo->m_strContactNumber),
                           QString::fromStdString(pCallInfo->m_strContactImageUrl),
                           CPhoneEnum::CALLER_INACTIVE, false, true);

        string strContactNameNum = (pCallInfo->m_strContactName == "") ? pCallInfo->m_strContactNumber : pCallInfo->m_strContactName;
        ResourceFactory::getICCastResource()->setIcRenderPhoneCallStateAsyncReq(EICRenderPhoneCallState::EN_ICRENDER_STATE_OUTGOING_CALL,
                                                                                strContactNameNum, pCallInfo->m_iCallId);
    }
    //Clear second caller info
    m_objSecondCallerInfo.clear();
    showPhoneCallScreen();
}

void CPhoneAdaptor::updateSingleAndIncomingCallInfo(bool bIsCallActive)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bIsCallActive: %d", __FUNCTION__, bIsCallActive);
    const SCallStateInfo* pCallInfo				= NULL;
    CPhoneEnum::ECallerState eFirstCallerState  = CPhoneEnum::CALLER_UNAVAILABLE;

    /* First caller is set to active/hold call and second caller is set to incoming call,
     * as in multi party case incoming call state will be received always after active/held call state.
     * Even if incoming call state is received before active call state i.e. sometimes in startup scenarios,
     * in HMI we will always consider first caller as active/held call and second caller as incoming call
     */
    if(bIsCallActive)
    {
        eFirstCallerState	= CPhoneEnum::CALLER_ACTIVE;
        pCallInfo			= getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_ACTIVE);
    }
    else
    {
        eFirstCallerState	= CPhoneEnum::CALLER_ON_HOLD;
        pCallInfo			= getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_ON_HOLD);
    }

    if(pCallInfo)
    {
        setFirstCallerInfo(pCallInfo->m_iCallId, QString::fromStdString(pCallInfo->m_strContactName),
                           QString::fromStdString(pCallInfo->m_strContactNumber),
                           QString::fromStdString(pCallInfo->m_strContactImageUrl), eFirstCallerState, false, true);
    }

    pCallInfo = getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_WAITING);
    if(pCallInfo)
    {
        setIncomingCallInfo(pCallInfo->m_iCallId, QString::fromStdString(pCallInfo->m_strContactName),
                            QString::fromStdString(pCallInfo->m_strContactNumber),
                            QString::fromStdString(pCallInfo->m_strContactImageUrl),
                            CPhoneEnum::CALLER_INACTIVE);

        string strContactNameNum = (pCallInfo->m_strContactName == "") ? pCallInfo->m_strContactNumber : pCallInfo->m_strContactName;
        ResourceFactory::getICCastResource()->setIcRenderPhoneCallStateAsyncReq(EICRenderPhoneCallState::EN_ICRENDER_STATE_INCOMING_CALL,
                                                                                strContactNameNum, pCallInfo->m_iCallId);
    }
    //Clear second caller info
    m_objSecondCallerInfo.clear();
    showCallScreenWithIncomingCallPopup();
}

void CPhoneAdaptor::updateConferenceAndIncomingCallInfo(bool bIsConferenceCallActive)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bIsConferenceCallActive: %d", __FUNCTION__, bIsConferenceCallActive);
    const SCallStateInfo* pCallInfo				= NULL;
    QString strConfParticipantCount				= "";
    CPhoneEnum::ECallerState eFirstCallerState  = CPhoneEnum::CALLER_UNAVAILABLE;

    /* First caller is set to conference call and second caller is set to incoming call,
     * as in multi party case incoming call state will be received always after conference call state.
     * Even if incoming call state is received before conference call state i.e. sometimes in startup scenarios,
     * in HMI we will always consider first caller as conference call and second caller as incoming call
     */
    if(bIsConferenceCallActive)
    {
        eFirstCallerState		= CPhoneEnum::CALLER_ACTIVE;
        pCallInfo				= getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_ACTIVE);
        strConfParticipantCount = QString::number(getConferenceParicipantsCount
                                                  (m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo,
                                                   CALL_STATE_ACTIVE));
    }
    else
    {
        eFirstCallerState		= CPhoneEnum::CALLER_ON_HOLD;
        pCallInfo				= getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_ON_HOLD);
        strConfParticipantCount = QString::number(getConferenceParicipantsCount
                                                  (m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo,
                                                   CALL_STATE_ON_HOLD));
    }

    if(pCallInfo)
    {
        setFirstCallerInfo(CPhoneData::CONFERENCE_CALL_ID, tr("TEXT_PHONE_CALL_CONFERENCE"), strConfParticipantCount + tr("TEXT_PHONE_CALL_PARTICIPANTS"), "", eFirstCallerState);
    }

    pCallInfo = getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_WAITING);
    if(pCallInfo)
    {
        setIncomingCallInfo(pCallInfo->m_iCallId, QString::fromStdString(pCallInfo->m_strContactName),
                            QString::fromStdString(pCallInfo->m_strContactNumber),
                            QString::fromStdString(pCallInfo->m_strContactImageUrl),
                            CPhoneEnum::CALLER_INACTIVE);

        string strContactNameNum = (pCallInfo->m_strContactName == "") ? pCallInfo->m_strContactNumber : pCallInfo->m_strContactName;
        ResourceFactory::getICCastResource()->setIcRenderPhoneCallStateAsyncReq(EICRenderPhoneCallState::EN_ICRENDER_STATE_INCOMING_CALL,
                                                                                strContactNameNum, pCallInfo->m_iCallId);
    }
    //Clear second caller info
    m_objSecondCallerInfo.clear();
    showCallScreenWithIncomingCallPopup();
}

void CPhoneAdaptor::updateActiveAndHeldCallInfo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    //Close incoming call popup whenever new call state is received
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_CALL_POPUP);

    int iOnGoingCallIndex           = getOnGoingCallIndex(m_pPhCallMgrResource->getCallStateInfoList(), 0);
    if (0 <= iOnGoingCallIndex)
    {
        const SCallStateInfo* pCallInfo = &m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo.at(iOnGoingCallIndex);
        string strContactNameNum        = "";
        int iCallId                     = -1;
        if(pCallInfo)
        {
            CPhoneEnum::ECallerState eFirstCallerState = CPhoneEnum::CALLER_UNAVAILABLE;
            if(pCallInfo->m_eCallState == CALL_STATE_ACTIVE)
            {
                eFirstCallerState = CPhoneEnum::CALLER_ACTIVE;
                iCallId           = pCallInfo->m_iCallId;
                strContactNameNum = (pCallInfo->m_strContactName == "") ? pCallInfo->m_strContactNumber : pCallInfo->m_strContactName;
            }
            else if(pCallInfo->m_eCallState == CALL_STATE_ON_HOLD)
            {
                eFirstCallerState = CPhoneEnum::CALLER_ON_HOLD;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: first caller: call state not handled", __FUNCTION__);
            }
            setFirstCallerInfo(pCallInfo->m_iCallId, QString::fromStdString(pCallInfo->m_strContactName),
                               QString::fromStdString(pCallInfo->m_strContactNumber),
                               QString::fromStdString(pCallInfo->m_strContactImageUrl),
                               eFirstCallerState);
        }

        iOnGoingCallIndex = getOnGoingCallIndex(m_pPhCallMgrResource->getCallStateInfoList(), (iOnGoingCallIndex + 1));
        if (0 <= iOnGoingCallIndex)
        {
            pCallInfo = &m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo.at(iOnGoingCallIndex);
            if(pCallInfo)
            {
                CPhoneEnum::ECallerState eSecondCallerState = CPhoneEnum::CALLER_UNAVAILABLE;
                if(pCallInfo->m_eCallState == CALL_STATE_ACTIVE)
                {
                    eSecondCallerState = CPhoneEnum::CALLER_ACTIVE;
                    iCallId            = pCallInfo->m_iCallId;
                    strContactNameNum  = (pCallInfo->m_strContactName == "") ? pCallInfo->m_strContactNumber : pCallInfo->m_strContactName;
                }
                else if(pCallInfo->m_eCallState == CALL_STATE_ON_HOLD)
                {
                    eSecondCallerState = CPhoneEnum::CALLER_ON_HOLD;
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: second caller: call state not handled", __FUNCTION__);
                }
                setSecondCallerInfo(pCallInfo->m_iCallId, QString::fromStdString(pCallInfo->m_strContactName),
                                    QString::fromStdString(pCallInfo->m_strContactNumber),
                                    QString::fromStdString(pCallInfo->m_strContactImageUrl),
                                    eSecondCallerState);
            }
            ResourceFactory::getICCastResource()->setIcRenderPhoneCallStateAsyncReq(EICRenderPhoneCallState::EN_ICRENDER_STATE_ACTIVE_CALL, strContactNameNum, iCallId);
            showPhoneCallScreen();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: second caller: Not found", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: first caller: Not found", __FUNCTION__);
    }
}

void CPhoneAdaptor::updateSingleAndConferenceCallInfo(bool bIsConferenceCallActive)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bIsConferenceCallActive: %d", __FUNCTION__, bIsConferenceCallActive);
    //Close incoming call popup whenever new call state is received
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_CALL_POPUP);
    const SCallStateInfo* pFirstCallInfo            = NULL;
    const SCallStateInfo* pSecondCallInfo           = NULL;
    QString strConfParticipantCount                 = "";
    CPhoneEnum::ECallerState eFirstCallerState      = CPhoneEnum::CALLER_UNAVAILABLE;
    CPhoneEnum::ECallerState eSecondCallerState     = CPhoneEnum::CALLER_UNAVAILABLE;
    string strContactNameNum                        = "";
    EICRenderPhoneCallState eICRenderPhoneCallState = EICRenderPhoneCallState::EN_ICRENDER_STATE_INVALID_CALL_STATE;
    int iCallId                                     = -1;

    /* First caller is set to conference call and second caller is set to active call,
     * as in multi party case active call state will be received always after conference call state.
     * Even if active call state is received before conference call state i.e. sometimes in startup scenarios,
     * in HMI we will always consider first caller as conference call and second caller as active call
     */
    //=======Update conference call and single call==========
    if(bIsConferenceCallActive)
    {
        //Set conference call information
        eFirstCallerState		= CPhoneEnum::CALLER_ACTIVE;
        pFirstCallInfo          = getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_ACTIVE);
        strConfParticipantCount = QString::number(getConferenceParicipantsCount
                                                  (m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo,
                                                   CALL_STATE_ACTIVE));
        eICRenderPhoneCallState = EICRenderPhoneCallState::EN_ICRENDER_STATE_ACTIVE_CONF_CALL;
        iCallId                 = CPhoneData::CONFERENCE_CALL_ID;

        //Set single call information
        eSecondCallerState	= CPhoneEnum::CALLER_ON_HOLD;
        pSecondCallInfo     = getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_ON_HOLD);


    }
    else
    {
        //Set conference call information
        eFirstCallerState		= CPhoneEnum::CALLER_ON_HOLD;
        pFirstCallInfo          = getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_ON_HOLD);
        strConfParticipantCount = QString::number(getConferenceParicipantsCount
                                                  (m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo,
                                                   CALL_STATE_ON_HOLD));

        //Set single call information
        eSecondCallerState      = CPhoneEnum::CALLER_ACTIVE;
        pSecondCallInfo			= getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_ACTIVE);
        eICRenderPhoneCallState = EICRenderPhoneCallState::EN_ICRENDER_STATE_ACTIVE_CALL;
        if(pSecondCallInfo)
        {
            strContactNameNum   = (pSecondCallInfo->m_strContactName == "") ? pSecondCallInfo->m_strContactNumber : pSecondCallInfo->m_strContactName;
            iCallId             = pSecondCallInfo->m_iCallId;
        }
        else
        {
            //do nothing
        }
    }

    if(pFirstCallInfo)
    {
        setFirstCallerInfo(CPhoneData::CONFERENCE_CALL_ID, strConfParticipantCount + tr("TEXT_PHONE_CALL_PARTICIPANTS"), "", "", eFirstCallerState);
    }

    if(pSecondCallInfo)
    {
        setSecondCallerInfo(pSecondCallInfo->m_iCallId, QString::fromStdString(pSecondCallInfo->m_strContactName),
                            QString::fromStdString(pSecondCallInfo->m_strContactNumber),
                            QString::fromStdString(pSecondCallInfo->m_strContactImageUrl),
                            eSecondCallerState);
    }
    ResourceFactory::getICCastResource()->setIcRenderPhoneCallStateAsyncReq(eICRenderPhoneCallState, strContactNameNum, iCallId);
    showPhoneCallScreen();
}

void CPhoneAdaptor::updateSingleAndOutgoingCallInfo(bool bIsSingleCallActive, bool bIsCallDialing)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bIsSingleCallActive: %d, bIsCallDialing: %d", __FUNCTION__, bIsSingleCallActive, bIsCallDialing);
    //Close incoming call popup whenever new call state is received
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_CALL_POPUP);
    const SCallStateInfo* pCallInfo				= NULL;
    CPhoneEnum::ECallerState eFirstCallerState  = CPhoneEnum::CALLER_UNAVAILABLE;

    /* First caller is set to active/held call and second caller is set to dialing/alerting call,
     * as in multi party case dialing/alerting call state will be received always after active call state.
     * Even if dialing call state is received before active call state i.e. sometimes in startup scenarios,
     * in HMI we will always consider first caller as active/held call and second caller as dialing/alerting call
     */
    //=======Update Single call==========
    if(bIsSingleCallActive)
    {
        eFirstCallerState	= CPhoneEnum::CALLER_ACTIVE;
        pCallInfo			= getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_ACTIVE);
    }
    else
    {
        eFirstCallerState	= CPhoneEnum::CALLER_ON_HOLD;
        pCallInfo			= getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_ON_HOLD);
    }
    if(pCallInfo)
    {
        setFirstCallerInfo(pCallInfo->m_iCallId, QString::fromStdString(pCallInfo->m_strContactName),
                           QString::fromStdString(pCallInfo->m_strContactNumber),
                           QString::fromStdString(pCallInfo->m_strContactImageUrl),
                           eFirstCallerState);
    }

    //=======Update Outgoing call==========
    if(bIsCallDialing)
    {
        pCallInfo = getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_DIALING);
    }
    else
    {
        pCallInfo = getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_ALERTING);
    }
    if(pCallInfo)
    {
        setSecondCallerInfo(pCallInfo->m_iCallId, QString::fromStdString(pCallInfo->m_strContactName),
                            QString::fromStdString(pCallInfo->m_strContactNumber),
                            QString::fromStdString(pCallInfo->m_strContactImageUrl),
                            CPhoneEnum::CALLER_INACTIVE);

        string strContactNameNum = (pCallInfo->m_strContactName == "") ? pCallInfo->m_strContactNumber : pCallInfo->m_strContactName;
        ResourceFactory::getICCastResource()->setIcRenderPhoneCallStateAsyncReq(EICRenderPhoneCallState::EN_ICRENDER_STATE_OUTGOING_CALL,
                                                                                strContactNameNum, pCallInfo->m_iCallId);
    }
    showPhoneCallScreen();
}

void CPhoneAdaptor::updateConferenceAndOutgoingCallInfo(bool bIsConferenceCallActive, bool bIsCallDialing)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bIsConferenceCallActive: %d, bIsCallDialing: %d", __FUNCTION__, bIsConferenceCallActive, bIsCallDialing);
    //Close incoming call popup whenever new call state is received
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_CALL_POPUP);
    const SCallStateInfo* pCallInfo				= NULL;
    QString strConfParticipantCount				= "";
    CPhoneEnum::ECallerState eFirstCallerState  = CPhoneEnum::CALLER_UNAVAILABLE;
    /* First caller is set to conference active/held call and second caller is set to dialing/alerting call,
     * as in multi party case dialing/alerting call state will be received always after conference call active/held state.
     * Even if dialing/alerting call state is received before conference call state i.e. sometimes in startup scenarios,
     * in HMI we will always consider first caller as conference active/held call and second caller as dialing/alerting call
     */
    //=======Update Conference call==========
    if(bIsConferenceCallActive)
    {
        eFirstCallerState		= CPhoneEnum::CALLER_ACTIVE;
        pCallInfo				= getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_ACTIVE);
        strConfParticipantCount = QString::number(getConferenceParicipantsCount
                                                  (m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo,
                                                   CALL_STATE_ACTIVE));
    }
    else
    {
        eFirstCallerState		= CPhoneEnum::CALLER_ON_HOLD;
        pCallInfo				= getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_ON_HOLD);
        strConfParticipantCount = QString::number(getConferenceParicipantsCount
                                                  (m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo,
                                                   CALL_STATE_ON_HOLD));
    }
    if(pCallInfo)
    {
        setFirstCallerInfo(CPhoneData::CONFERENCE_CALL_ID, strConfParticipantCount + tr("TEXT_PHONE_CALL_PARTICIPANTS"), "", "", eFirstCallerState);
    }

    //=======Update Outgoing call==========
    if(bIsCallDialing)
    {
        pCallInfo = getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_DIALING);
    }
    else
    {
        pCallInfo = getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_ALERTING);
    }
    if(pCallInfo)
    {
        setSecondCallerInfo(pCallInfo->m_iCallId, QString::fromStdString(pCallInfo->m_strContactName),
                            QString::fromStdString(pCallInfo->m_strContactNumber),
                            QString::fromStdString(pCallInfo->m_strContactImageUrl),
                            CPhoneEnum::CALLER_INACTIVE);
        string strContactNameNum = (pCallInfo->m_strContactName == "") ? pCallInfo->m_strContactNumber : pCallInfo->m_strContactName;
        ResourceFactory::getICCastResource()->setIcRenderPhoneCallStateAsyncReq(EICRenderPhoneCallState::EN_ICRENDER_STATE_OUTGOING_CALL,
                                                                                strContactNameNum, pCallInfo->m_iCallId);
    }
    showPhoneCallScreen();
}

void CPhoneAdaptor::updateAllCallsTerminatedCallInfo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    //Close incoming call popup whenever new call state is received
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_CALL_POPUP);
    const SCallStateInfo* pCallInfo				= NULL;
    string strContactNameNum                    = "";
    int iCallId                                 = -1;
    /*
     * If call state info list size is greater than 0 then the PHONE_CALLSTATE_ALL_CALLS_TERMINATED state is
     * received for conference call otherwise for single call.
     */
    /* TODO: This condition can fail in a scenario where we receive callstate as terminated or two calls
     * eventhough the calls where not in conference.
     * Scenario - If in multiparty calls, both the calls are ended as same time then HMI will receive call
     * state as terminated for both the calls and we will end up executing below flow. Need to take care
     */
    if(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo.size() > 1)
    {
        pCallInfo = getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_TERMINATED);
        QString strConfParticipantCount = QString::number(getConferenceParicipantsCount
                                                          (m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo,
                                                           CALL_STATE_TERMINATED));
        iCallId                         = CPhoneData::CONFERENCE_CALL_ID;
        if(pCallInfo)
        {
            setFirstCallerInfo(CPhoneData::CONFERENCE_CALL_ID, tr("TEXT_PHONE_CALL_CONFERENCE"), strConfParticipantCount + tr("TEXT_PHONE_CALL_PARTICIPANTS"), "", CPhoneEnum::CALLER_ACTIVE);
        }
    }
    else
    {
        pCallInfo = getCallInfo(m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo, CALL_STATE_TERMINATED);
        if(pCallInfo)
        {
            setFirstCallerInfo(pCallInfo->m_iCallId, QString::fromStdString(pCallInfo->m_strContactName),
                               QString::fromStdString(pCallInfo->m_strContactNumber),
                               QString::fromStdString(pCallInfo->m_strContactImageUrl),
                               CPhoneEnum::CALLER_ACTIVE, false, true);
            iCallId             = pCallInfo->m_iCallId;
            strContactNameNum   = (pCallInfo->m_strContactName == "") ? pCallInfo->m_strContactNumber : pCallInfo->m_strContactName;
        }
    }

    ResourceFactory::getICCastResource()->setIcRenderPhoneCallStateAsyncReq(EICRenderPhoneCallState::EN_ICRENDER_STATE_CALL_ENDED,
                                                                            strContactNameNum, iCallId);

    //Clear second caller info
    m_objSecondCallerInfo.clear();
    //Clear incoming caller info
    m_objIncomingCallInfo.clear();
    //Clear conference participant list model
    m_objConfParticipantsListModel.removeRows();
    //show call screen if not in call screen
    showPhoneCallScreen();
    //Start end call screen timer
    m_objEndCallScreenTimer.setSingleShot(true);
    m_objEndCallScreenTimer.start(600);
}

bool CPhoneAdaptor::showPhoneCallScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    bool bShowCallScreen = false;
    CHMIMain::getSM()->getSCI_Phone()->set_bIsPhoneCallStateActivated(true);

    if((CParkAssistAdaptor::getInstance()) && (CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus()))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: show low priority call popup", __FUNCTION__);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_LOW_PRIORITY_CALL_POPUP);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: activate phone call state", __FUNCTION__);
        activateSMCallState();
        bShowCallScreen = true;
    }
    return bShowCallScreen;
}

bool CPhoneAdaptor::showCallScreenWithIncomingCallPopup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    bool bShowCallScreenWithIncomingCallPopup = false;
    CHMIMain::getSM()->getSCI_Phone()->set_bIsPhoneCallStateActivated(true);

    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"[KPI_MARKER][HMI][ show incoming call indication on HMI]");
    if((CParkAssistAdaptor::getInstance()) && (CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus()))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: show low priority call popup", __FUNCTION__);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_LOW_PRIORITY_CALL_POPUP);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: show full call popup and activate phone call state", __FUNCTION__);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_INCOMING_CALL_POPUP);
        activateSMCallState();
        bShowCallScreenWithIncomingCallPopup = true;
    }
    return bShowCallScreenWithIncomingCallPopup;
}

bool CPhoneAdaptor::showMicNotConnectedPopup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    bool bRet = false;
    //Show mic not available popup, if mic is not connected
    if((CDiagnosticAdaptor::getInstance()) && (CDiagnosticAdaptor::getInstance()->micConnectionStatus() != CDiagnosticEnum::CONNECTED))
    {
        //Mic is not connected
        CAudioAdaptor::getInstance()->playBeep(CAudioEnums::BEEP_TYPE_CONFIRM);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_MIC_NOT_AVAILABLE_POPUP);
        bRet = true;
    }
    else
    {
        //Mic is connected
    }
    return bRet;
}

void CPhoneAdaptor::updateBTItemEnableState()
{
    bool bEnableState = ((!CAndroidAutoAdaptor::getInstance()->androidAutoConnectionStatus()) &&
                         (!CAppleCarPlayAdaptor::getInstance()->appleCarPlayConnectionStatus()) &&
                         (m_bIsBluetoothEnabled));
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: bEnableState: %d", __FUNCTION__, bEnableState);
    m_pPhoneSetupListModel->setData(m_pPhoneSetupListModel->index(CPhoneEnum::PHONE_SETUP_PAIR_NEW_DEVICE, 0),
                                    bEnableState, CPhoneSetupListModel::PHONE_SETUP_ITEM_ENABLED_ROLE);
    m_pPhoneSetupListModel->setData(m_pPhoneSetupListModel->index(CPhoneEnum::PHONE_SETUP_PAIRED_DEVICES, 0),
                                    bEnableState, CPhoneSetupListModel::PHONE_SETUP_ITEM_ENABLED_ROLE);
    m_pPhoneSetupListModel->setData(m_pPhoneSetupListModel->index(CPhoneEnum::PHONE_SETUP_BLUETOOTH_VISIBILITY, 0),
                                    bEnableState, CPhoneSetupListModel::PHONE_SETUP_ITEM_ENABLED_ROLE);
}

int CPhoneAdaptor::getOnGoingCallIndex(const vector<SCallStateInfoList> &callStateInfoList, int iIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s iIndex:%d", __FUNCTION__, iIndex);
    if ((0 <= iIndex) && (!callStateInfoList.empty()))
    {
        bool bOnGoingCallFound = false;
        int iCallStateInfSize = static_cast<int>(callStateInfoList.at(0).m_vectCallStateInfo.size());//cast the unsigned int to an int since it may store a -1 value
        while(iCallStateInfSize > iIndex)
        {
            const SCallStateInfo* pCallInfo = &m_pPhCallMgrResource->getCallStateInfoList().at(0).m_vectCallStateInfo.at(iIndex);
            if ((pCallInfo) && ((CALL_STATE_ACTIVE == pCallInfo->m_eCallState) || (CALL_STATE_ON_HOLD == pCallInfo->m_eCallState)))
            {
                bOnGoingCallFound = true;
                break;
            }
            else
            {
                iIndex++;
            }
        }

        if (!bOnGoingCallFound)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s Active / Hold call not found", __FUNCTION__);
            iIndex = -1;
        }
    }
    else
    {
        iIndex = -1;
    }
    return iIndex;
}

void CPhoneAdaptor::showHidePhoneBtVROverlay(bool bShowPhoneBtVROverLay)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: bShowPhoneBtVROverLay: %d", __FUNCTION__, bShowPhoneBtVROverLay);

    if (m_bIsPhoneBtVROverlayVisible != bShowPhoneBtVROverLay)
    {
        m_bIsPhoneBtVROverlayVisible = bShowPhoneBtVROverLay;
        emit sigShowHidePhoneBtVROverlay(bShowPhoneBtVROverLay);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: Values are same. So no Action", __FUNCTION__);
    }
}
