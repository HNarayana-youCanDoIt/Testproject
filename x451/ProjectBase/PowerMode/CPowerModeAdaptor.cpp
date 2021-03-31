/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CPowerModeAdaptor.cpp
 * @ingroup         HMIComponent
 * @author          Prashantkumar Raut
 * CPowerModeAdaptor an adaptor for PowerMode module which is used
 * to communicate with the power mode resource layer, QML layer and state machine
 */

#include "CPowerModeAdaptor.h"
#include "CPowerModeEventHandler.h"
#include "CHMIMain.h"
#include "PowerModeResource/implementations/CPowerModeResourceImpl.h"
#include <ResourceFactory.hpp>
#include <Audio/CAudioAdaptor.h>
#include <CarPlay/CAppleCarPlayAdaptor.h>
#include <AndroidAuto/CAndroidAutoAdaptor.h>
#include "CDoodleApplication.h"
#include "CDoodleAdaptor.h"

CPowerModeAdaptor* CPowerModeAdaptor::m_pPowerModeAdaptor = nullptr;

CPowerModeAdaptor &CPowerModeAdaptor::getInstance()
{
    if (nullptr == m_pPowerModeAdaptor)
    {
        m_pPowerModeAdaptor = new CPowerModeAdaptor();
    }
    return *m_pPowerModeAdaptor;
}

CPowerModeAdaptor::CPowerModeAdaptor(QObject *parent) : QObject(parent)//, m_ePowerModeStatus(CPowerModeEnums::VPM_UNKNOWN)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,__FUNCTION__);
    CPowerModeEnums::registerPowerEnumsToQML();
    m_pPowerModeEventHandler = new CPowerModeEventHandler(this);
    CPowerModeResourceImpl* powerModeResource = static_cast<CPowerModeResourceImpl*>(ResourceFactory::getPowerModeResource());
    if (powerModeResource)
    {
        m_ePowerModeStatus = convertPMStrToEnum(QString::fromStdString(powerModeResource->getCurrentPowerMode()));
        m_eNSMNodeState = CPowerModeEnums::NsmNodeState_NotSet;
        m_bOneHourModeExpiryState = false;
        powerModeResource->getNodeState();
        CHMIMain::getSM()->getSCI_Nsm()->set_currentPowerMode(m_ePowerModeStatus);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,"powerModeResource null");
    }
    CFramework::getFramework().setContextProperty("cppPowerModeAdaptor",this);
}

CPowerModeAdaptor::~CPowerModeAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,__FUNCTION__);
    if(m_pPowerModeAdaptor)
    {
        delete m_pPowerModeAdaptor;
        m_pPowerModeAdaptor = nullptr;
    }

    if (m_pPowerModeEventHandler)
    {
        delete m_pPowerModeEventHandler;
        m_pPowerModeEventHandler = nullptr;
    }
}

CPowerModeEnums::eVehiclePowerModes CPowerModeAdaptor::convertPMStrToEnum(QString m_mode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,"%s: mode received is: %s", __FUNCTION__, m_mode.toStdString().c_str());
    CPowerModeEnums::eVehiclePowerModes ePMValue = CPowerModeEnums::VPM_UNKNOWN;
    if("VPM_SWITCH_OFF" == m_mode)
    {
        ePMValue =  CPowerModeEnums::VPM_SWITCH_OFF;
    }
    else if("VPM_EARLY_WAKEUP" == m_mode)
    {
        ePMValue =  CPowerModeEnums::VPM_EARLY_WAKEUP;
    }
    else if("VPM_MEDIA_OFF" == m_mode)
    {
        ePMValue =  CPowerModeEnums::VPM_MEDIA_OFF;
    }
    else if("VPM_ACTIVE" == m_mode)
    {
        ePMValue =  CPowerModeEnums::VPM_ACTIVE;
    }
    else if("VPM_ONE_HOUR" == m_mode)
    {
        ePMValue =  CPowerModeEnums::VPM_ONE_HOUR;
    }
    else
    {
        //do nothing
    }

    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,"%s: power mode value is: %d", __FUNCTION__, ePMValue);
    return ePMValue;
}

void CPowerModeAdaptor::sltPowerModeEvent(QString m_mode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,"%s : ver : %s ", __FUNCTION__,m_mode.toStdString().c_str() );

    powerModeChanged(convertPMStrToEnum(m_mode));
}

void CPowerModeAdaptor::sltNSMNodeStateEvent(int iNsmNodeState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,"%s : ver : %d ", __FUNCTION__, iNsmNodeState);
    m_eNSMNodeState = static_cast<CPowerModeEnums::eNSMNodeStates>(iNsmNodeState);
}

void CPowerModeAdaptor::powerModeChanged(CPowerModeEnums::eVehiclePowerModes ePowerMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE, "%s: ePowerMode: %d", __FUNCTION__, static_cast<int> (ePowerMode));

    if(CDoodleApplication::getDoodleAdaptor())
    {
        CDoodleApplication::getDoodleAdaptor()->setForceShowDoodleOnScreen(false);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRAWERS, "%s: CDoodleAdaptor object not available", __FUNCTION__);
    }

    /*
     * If Previous powerMode is Media Off then we have to stay in MediaOff screen
     * for at least 400 mili seconds. This is done becuase of the below issue.
     * AA/CP screen ===> Do MediaOff ==> Home Screen seen ==> AA/Cp screen seen.
     * But we have to switch directly to AA/CP screen after comeout of mediaOff.
     */
    //Todo: Ideally this should be handled within the state machine
    if (CPowerModeEnums::VPM_MEDIA_OFF == m_ePowerModeStatus && ((true == CAppleCarPlayAdaptor::getInstance()->appleCarPlayConnectionStatus()) ||
                                                                 (true == CAndroidAutoAdaptor::getInstance()->androidAutoConnectionStatus())))
    {
        m_ePowerModeStatus = ePowerMode;
        QTimer::singleShot(400, this, SLOT(sltUpdatePowerMode()));
    }
    else
    {
        m_ePowerModeStatus = ePowerMode;
        sltUpdatePowerMode();
    }
}

void CPowerModeAdaptor::sltUpdatePowerMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE, "%s: ePowerMode: %d", __FUNCTION__, static_cast<int> (m_ePowerModeStatus));

    CHMIMain::getSM()->getSCI_Nsm()->set_currentPowerMode(static_cast<int> (m_ePowerModeStatus));
    CHMIMain::getSM()->getSCI_Nsm()->raise_evPowerModeChanged(static_cast<int> (m_ePowerModeStatus));

    if (CPowerModeEnums::VPM_EARLY_WAKEUP == m_ePowerModeStatus)
    {
        /** If one hour mode expiry status is true, make it false */
        if(true == m_bOneHourModeExpiryState)
        {
            setOneHourExpiryStateInactive();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE, "%s: In else, m_bOneHourModeExpiryState is: %d", __FUNCTION__, m_bOneHourModeExpiryState);
        }
    }

    /*Note: Here we are handling this case to check power mode state and one hour mode expiry to close the one hour mode expiry poup */
    if((CPowerModeEnums::VPM_ACTIVE == m_ePowerModeStatus) && (m_bOneHourModeExpiryState))
    {
        setOneHourExpiryStateInactive();
        CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_POWERMODE_ONE_HOUR_MODE_EXPIRY);
        CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_SETUP_FACTORY_RESET_IGNITION_ON_STATUS);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE, "%s: ", __FUNCTION__);
    }

    emit sigPowerModeChanged();
}

CPowerModeEnums::eVehiclePowerModes CPowerModeAdaptor::getPowerModeStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,"%s: power mode status is: %d", __FUNCTION__, m_ePowerModeStatus);

    return m_ePowerModeStatus;
}

CPowerModeEnums::eNSMNodeStates CPowerModeAdaptor::getNSMNodeState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,"%s, nsm node state: %d",__FUNCTION__, m_eNSMNodeState);
    return m_eNSMNodeState;
}

void CPowerModeAdaptor::updateOneHourExpiryState(bool bOneHourExpiryState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE, "%s: one hour mode expiry state: %d", __FUNCTION__, bOneHourExpiryState);

    if(m_bOneHourModeExpiryState != bOneHourExpiryState)
    {
        m_bOneHourModeExpiryState = bOneHourExpiryState;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE, "%s: one hour mode expiry state is same as previous: %d", __FUNCTION__, bOneHourExpiryState);
    }

    if(true == m_bOneHourModeExpiryState)
    {
        CAudioAdaptor::getInstance()->playBeep(CAudioEnums::BEEP_TYPE_CONFIRM);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_POWERMODE_ONE_HOUR_MODE_EXPIRY);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE, "%s: In else, One hour expiry state is: %d", __FUNCTION__, m_bOneHourModeExpiryState);
    }
}

void CPowerModeAdaptor::setOneHourExpiryStateInactive()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE, "%s", __FUNCTION__);

    CPowerModeResourceImpl* pPowerModeResource = static_cast<CPowerModeResourceImpl*>(ResourceFactory::getPowerModeResource());
    if(pPowerModeResource)
    {
        m_bOneHourModeExpiryState = false;
        pPowerModeResource->setOneHourExpiryStateInactive();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_POWER_MODE, "%s: pPowerModeResource is null", __FUNCTION__);
    }
}
