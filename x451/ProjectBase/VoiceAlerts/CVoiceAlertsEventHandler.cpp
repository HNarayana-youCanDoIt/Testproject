
/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
***************************************************************
*/
/**
* @file         CVoiceAlertsResImpl.h
* @ingroup       HMIComponent
* @author        Guru Alingal
* @brief CVoiceAlertsEventHandler class will be used to receive the data sent
* from voice alert resource layer and pass on the information to voice alert
* adaptor.
*/

#include<CVoiceAlertsEventHandler.h>
#include "CVariantControlAdaptor.h"

CVoiceAlertsEventHandler::CVoiceAlertsEventHandler(QObject *parent):
    QObject(parent)
{
    registerConnections();
}

CVoiceAlertsEventHandler::~CVoiceAlertsEventHandler()
{

}

void CVoiceAlertsEventHandler::registerConnections()
{
    CVoiceAlertsResImpl* pResImpl = dynamic_cast<CVoiceAlertsResImpl*>(ResourceFactory::getVoiceAlertResource());
    if(pResImpl)
    {
        CVoiceAlertsEventProvider* pEvtProvider = pResImpl->getEventProvider();

        if(pEvtProvider)
        {
            connect(pEvtProvider, SIGNAL(sigHuAlertState(int)), this, SLOT(sltHuAlertState(int)), Qt::QueuedConnection);
            connect(pEvtProvider, SIGNAL(sigHuAlertMceState(int)), this, SLOT(sltHuAlertMceState(int)), Qt::QueuedConnection);
            connect(pEvtProvider, SIGNAL(sigHuAlertStatus(int)), this, SLOT(sltHuAlertStatus(int)), Qt::QueuedConnection);
            connect(pEvtProvider, SIGNAL(sigHuAlertHMISelection(int)), this, SLOT(sltHuAlertHMISelection(int)), Qt::QueuedConnection);
            connect(pEvtProvider, SIGNAL(sigHuInfoFeaturePresence(int)), this, SLOT(sltHuInfoFeaturePresence(int)), Qt::QueuedConnection);
            connect(pEvtProvider, SIGNAL(sigCurDriveMode(int)), this, SLOT(sltCurDriveMode(int)), Qt::QueuedConnection);
        }
    }
}

void CVoiceAlertsEventHandler::sltVASStatus(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s, bStatus:%d", __FUNCTION__, bStatus);
}

void CVoiceAlertsEventHandler::sltHuAlertStatus(int iAlertStaus)
{
    CVoiceAlertsAdaptor::getInstance().setECurrAlertState(static_cast<CVoiceAlertsEnums::EVoiceAlertsState>(iAlertStaus));
}

void CVoiceAlertsEventHandler::sltHuInfoFeaturePresence(int iPresence)
{
    CVoiceAlertsAdaptor::getInstance().setVoiceAlertPresence(iPresence);
}

void CVoiceAlertsEventHandler::sltCurDriveMode(int iDriveMode)
{    
    CVariantControlEnum::EVIP_DID eVIP_DID = CVariantControlAdaptor::getInstance()->eolVIP_DID();
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s: iDriveMode: %d, eVIP_DID: %d", __FUNCTION__, iDriveMode, eVIP_DID);
    if (CVariantControlEnum::VIP_DID_HU_NEXON_LEVEL_B_VAVE == eVIP_DID || CVariantControlEnum::VIP_DID_HU_NEXON_MCE == eVIP_DID)
    {
        // TATA_X104_High_VAVE specific code
        CVoiceAlertsAdaptor::getInstance().driveModeUpdate(static_cast<CVoiceAlertsEnums::EDriveModes>(iDriveMode));
    }
    else
    {
        // For the other variant we do not do anything for now
    }
}

void CVoiceAlertsEventHandler::sltHuAlertHMISelection(int iHMISelection)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s: sltHuAlertHMISelection %d", __FUNCTION__, iHMISelection);
    CVoiceAlertsAdaptor::getInstance().setVoiceAlertSelection(iHMISelection);
}

void CVoiceAlertsEventHandler::sltHuAlertState(int iAlert)
{
    CVoiceAlertsAdaptor::getInstance().setECurrAlert(iAlert);
}

void CVoiceAlertsEventHandler::sltHuAlertMceState(int iMceAlert)
{
    CVoiceAlertsAdaptor::getInstance().setECurrMceAlert(iMceAlert);
}
