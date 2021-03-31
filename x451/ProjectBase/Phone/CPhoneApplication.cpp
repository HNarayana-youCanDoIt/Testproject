/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CPhoneApplication.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain implementation of all the methods declared in
 *                CPhoneApplication class
 */

#include "CPhoneApplication.h"
#include "CPhoneSM.h"
#include "CPhoneAdaptor.h"
#include "CPhoneEventHandler.h"
#include "CPopupManager.h"
#include "logging.h"

CPhoneApplication::CPhoneApplication(QQuickItem *pParent):
    CBaseApplication(pParent),
    m_pPhoneAdaptor(CPhoneAdaptor::getInstance()),
    m_pPhoneSM(new CPhoneSM(*this)),
    m_pPhoneEventHandler(new CPhoneEventHandler(this))
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    CHMIMain::getSM()->setSCI_Phone_OCB(m_pPhoneSM);
    mfw.setContextProperty("cppPhoneApp", this);
    CPhoneEnum::registerPhoneEnumsToQML();
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->initPhoneDataModels();
    }
    connectSignals();
}

CPhoneApplication::~CPhoneApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);

    if(m_pPhoneEventHandler)
    {
        delete m_pPhoneEventHandler;
        m_pPhoneEventHandler = NULL;
    }

    if(m_pPhoneSM)
    {
        delete m_pPhoneSM;
        m_pPhoneSM = NULL;
    }
}

/***********************************************************//**
 * @category    METHODS
 ***********************************************************/
void CPhoneApplication::onCreated(QQuickItem *rootObject)
{
    Q_UNUSED(rootObject);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,__FUNCTION__);
}

void CPhoneApplication::loadScreen(QString qmlFilePath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,__FUNCTION__);
    CBaseApplication::loadScreen(qmlFilePath);
}

void CPhoneApplication::raiseSMEvent(const QString & name,const QVariant & data)
{
    Q_UNUSED(data);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,__FUNCTION__);
    if(name.compare("PhoneSetupPopup") == 0)
    {
        // If pair a new device item is selected then we need to show popup otherwise raise event to switch state
        if(static_cast<CPhoneEnum::EPhoneSetupItems>(data.toInt()) == CPhoneEnum::PHONE_SETUP_PAIR_NEW_DEVICE)
        {
            if(m_pPhoneAdaptor && CPopupManager::getInstance())

            {
                m_pPhoneAdaptor->invSwitchToPairNewDevice();
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "Phone adaptor object or popup manager not created");
            }
        }
        else
        {
            raiseSMEventForPhoneSetup(static_cast<CPhoneEnum::EPhoneSetupItems>(data.toInt()));
        }
    }
    else if(name.compare("PhoneSetup") == 0)
    {
        raiseSMEventForPhoneSetup(static_cast<CPhoneEnum::EPhoneSetupItems>(data.toInt()));
    }
    else if(name.compare("ConferenceParticipant") == 0)
    {
        CHMIMain::getSM()->getSCI_Phone()->raise_evPhoneCallParticipantScreen();
    }
    else if(name.compare("PhoneBrowse") == 0)
    {
        raiseSMEventForPhoneBrowse(data.toInt());
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: data received from qml :%s", __FUNCTION__, name.toStdString().c_str());
    }
}

void CPhoneApplication::qmlLog(QString strLog)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"QML_LOG: %s", strLog.toUtf8().data());
}

void CPhoneApplication::sltPopupResult(CPopupEnum::EPopupID ePopupId, CPopupEnum::EPopupResult ePopupResult, QString strAdditionalInfo)
{
    Q_UNUSED(strAdditionalInfo);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s ePopupId: %d | ePopupResult: %d", __FUNCTION__,ePopupId,ePopupResult);
    switch(ePopupId)
    {
    case CPopupEnum::EPopupID::EN_POPUPID_PHONE_SETUP_TURN_ON_BLUETOOTH:
    {
        if(CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_TIMEOUT == ePopupResult)
        {
            CHMIMain::getSM()->getSCI_Setup()->raise_evBluetoothSetupActivated(CHMIMain::getSM()->get_sETUP_SCR_PAIR_NEW_DEVICE());
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Switching to pair new device screen", __FUNCTION__);
        }

    }
        break;

    case CPopupEnum::EPopupID::EN_POPUPID_PHONE_SETUP_DEVICE_LIMIT_REACHED:
    {
        if(CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_TIMEOUT == ePopupResult)
        {
            CHMIMain::getSM()->getSCI_Setup()->raise_evBluetoothSetupActivated(CHMIMain::getSM()->get_sETUP_SCR_PAIRED_DEVICES());
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Switching to paired devices screen", __FUNCTION__);
        }

    }
        break;

    case CPopupEnum::EPopupID::EN_POPUPID_PHONE_SETUP_BT_DEVICES_NOT_FOUND:
    {
        if(CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_TIMEOUT == ePopupResult)
        {
            CHMIMain::getSM()->getSCI_Setup()->raise_evBluetoothSetupActivated(CHMIMain::getSM()->getDefaultSCI()->get_sETUP_SCR_BT_NAMED_ENTRY());
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Switching to phone setup", __FUNCTION__);
        }

    }
        break;

    case CPopupEnum::EPopupID::EN_POPUPID_PHONE_SETUP_PREVIOUS_DEVICE_DISCONNECTION:
    case CPopupEnum::EPopupID::EN_POPUPID_PHONE_SETUP_DELETE_DEVICE_CONFIRMATION:
    {
        if((CPopupEnum::EN_POPUP_RESULT_DISPLAYED != ePopupResult) &&
           (CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS != ePopupResult)&&
           (CPopupEnum::EN_POPUP_RESULT_IGNORED != ePopupResult))
        {
            CPhoneAdaptor::getInstance()->invResetSelectedItemInfo();
        }

    }
        break;

    case CPopupEnum::EPopupID::EN_POPUPID_PHONE_BROWSE_FAVORITE_LIST_FULL:
    {
        if(CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_TIMEOUT == ePopupResult)
        {
            raiseSMEventForPhoneBrowse(CPhoneEnum::PHONE_BROWSE_TYPE_FAVORITES);
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Switching to favorite screen", __FUNCTION__);
        }

    }
        break;

    case CPopupEnum::EPopupID::EN_POPUPID_PHONE_INCOMING_SMS_POPUP:
    case CPopupEnum::EPopupID::EN_POPUPID_LOW_PRIORITY_SMS_POPUP:
    {
        if((CPopupEnum::EN_POPUP_RESULT_DISPLAYED != ePopupResult) && (CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_CONTEXT_CHANGE != ePopupResult))
        {
            if(CPhoneAdaptor::getInstance())
            {
                //Reset incoming sms popup state
                CPhoneAdaptor::getInstance()->resetIncomingSmsPopupState();
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor not available", __FUNCTION__);
            }
        }
        else
        {
            //do nothing
        }

        if((CPopupEnum::EN_POPUP_RESULT_DISPLAYED != ePopupResult))
        {
            CPhoneAdaptor::getInstance()->invSetLowPriorityPopupActiveStatus(false);
        }
    }
        break;

    case CPopupEnum::EPopupID::EN_POPUPID_PHONE_SENDING_SMS:
    {
        if(CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_TIMEOUT == ePopupResult)
        {
            if(CPhoneAdaptor::getInstance())
            {
                //Show sms sent popup
                CPhoneAdaptor::getInstance()->showSmsSentPopup();
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor not available", __FUNCTION__);
            }
        }

    }
        break;

    case CPopupEnum::EPopupID::EN_POPUPID_PHONE_SETUP_EXTERNAL_PAIRING_REQUEST:
    {
        if((CPopupEnum::EN_POPUP_RESULT_DISPLAYED != ePopupResult) &&
           (CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS != ePopupResult)&&
           (CPopupEnum::EN_POPUP_RESULT_IGNORED != ePopupResult))
        {
            CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EPopupID::EN_POPUPID_PHONE_SETUP_CONNECTING);
            CPhoneAdaptor::getInstance()->invBondingReply(false, true);
        }

    }
        break;

    case CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETING_ALL_DEVICES:
    {
        if((CPopupEnum::EN_POPUP_RESULT_DISPLAYED != ePopupResult) &&
           (CPopupEnum::EN_POPUP_RESULT_INVALID != ePopupResult)&&
           (CPopupEnum::EN_POPUP_RESULT_IGNORED != ePopupResult))
        {
            if(CPhoneAdaptor::getInstance()->getDeleteAllDevicesStatus())
            {
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_ALL_DEVICES_SUCCESS);
            }
            else
            {
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_ALL_DEVICES_FAILED);
            }
        }
        else
        {
            //do nothing
        }
    }
        break;

    case CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETING_DEVICE:
    {
        if((CPopupEnum::EN_POPUP_RESULT_DISPLAYED != ePopupResult) &&
           (CPopupEnum::EN_POPUP_RESULT_INVALID != ePopupResult)&&
           (CPopupEnum::EN_POPUP_RESULT_IGNORED != ePopupResult))
        {
            if(CPhoneAdaptor::getInstance()->getDeleteDeviceStatus())
            {
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_DEVICE_SUCCESS);
            }
            else
            {
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_DEVICE_FAILED);
            }
        }
        else
        {
            //do nothing
        }
    }
        break;

    case CPopupEnum::EN_POPUPID_PHONE_SETUP_DELETE_ALL_DEVICES_SUCCESS:
    {
        if((CPopupEnum::EN_POPUP_RESULT_DISPLAYED != ePopupResult) &&
           (CPopupEnum::EN_POPUP_RESULT_INVALID != ePopupResult))
        {
            CPhoneAdaptor::getInstance()->resetDeleteAllDevicesSelStatus();
        }
        else
        {
            //do nothing
        }
    }
        break;
		
	case CPopupEnum::EN_POPUPID_LOW_PRIORITY_CALL_POPUP:
    {
        if((CPopupEnum::EN_POPUP_RESULT_DISPLAYED != ePopupResult))
        {
            CPhoneAdaptor::getInstance()->invSetLowPriorityPopupActiveStatus(false);
        }
    }
        break;

    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Invalid popup id");
        break;
    }
}

void CPhoneApplication::sltShowHidePhoneBtVROverlay(bool bShowPhoneBtVROverLay)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: bShowPhoneBtVROverLay is: %d", __FUNCTION__, bShowPhoneBtVROverLay);
    if(bShowPhoneBtVROverLay)
    {
        if(loadVROverlay("qrc:/QML/VoiceRecognition/CPhoneBtVROverlay.qml"))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: Phone bt VR overlay loaded", __FUNCTION__);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: Unable to load phonr bt VR overlay", __FUNCTION__);
        }
    }
    else
    {
        if(unloadVROverlay())
        {
            LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: Phone bt VR overlay unloaded", __FUNCTION__);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: Unable to unload phone bt VR overlay", __FUNCTION__);
        }
    }
}


void CPhoneApplication::raiseSMEventForPhoneSetup(CPhoneEnum::EPhoneSetupItems ePhoneSetupIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    switch(ePhoneSetupIndex)
    {
    case CPhoneEnum::PHONE_SETUP_PAIR_NEW_DEVICE:
    {
        if(m_pPhoneAdaptor && m_pPhoneAdaptor->pairedDeviceListModel() && CPopupManager::getInstance())

        {
            /*
             * If paired devices count is grater than the supported paired device count then show popup that
             * device limit has reached otherwise switch to pair new device screen.
             */
            if(m_pPhoneAdaptor->isMaxDeviceLimitReached())
            {
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PHONE_SETUP_DEVICE_LIMIT_REACHED);
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Maximum paired devices limit reached", __FUNCTION__);
            }
            else
            {
                CHMIMain::getSM()->getSCI_Setup()->raise_evBluetoothSetupActivated(CHMIMain::getSM()->get_sETUP_SCR_PAIR_NEW_DEVICE());
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Switching to pair new device screen", __FUNCTION__);
            }
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object or popup manager not created", __FUNCTION__);
        }

    }
        break;

    case CPhoneEnum::PHONE_SETUP_PAIRED_DEVICES:
        CHMIMain::getSM()->getSCI_Setup()->raise_evBluetoothSetupActivated(CHMIMain::getSM()->get_sETUP_SCR_PAIRED_DEVICES());
        break;

    default:
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"wrong index: %d", ePhoneSetupIndex);
        break;
    }
    CHMIMain::getSM()->runCycle();
}

void CPhoneApplication::raiseSMEventForPhoneBrowse(int iPhoneBrowseType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    CHMIMain::getSM()->raise_evPhoneBrowseActivated(iPhoneBrowseType);
}

void CPhoneApplication::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    connect(CPopupManager::getInstance(),SIGNAL(sigPopupResult(CPopupEnum::EPopupID,CPopupEnum::EPopupResult, QString)),this,SLOT(sltPopupResult(CPopupEnum::EPopupID,CPopupEnum::EPopupResult, QString)));
    connect(CPhoneAdaptor::getInstance(), SIGNAL(sigShowHidePhoneBtVROverlay(bool)), this, SLOT(sltShowHidePhoneBtVROverlay(bool)));
}
