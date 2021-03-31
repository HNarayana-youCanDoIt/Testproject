/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CTunerEventHandler.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Balyan
 * CTunerEventHandler, The class listens for the signals raised by the resource layer provider class
 * It has the implementation of the corresponding slots
**/

#include "CTunerEventHandler.h"
#include <CHMIMain.h>
#include "CTunerAdaptor.h"
#include "Tuner/implementations/CTunerResourceImpl.h"
//#include "Tuner/interfaces/ITunerTypes.h"
#include <ResourceFactory.hpp>

CTunerEventHandler::CTunerEventHandler(QObject *parent):
    QObject(parent)
{
    connectSignals();
}

CTunerEventHandler::~CTunerEventHandler()
{

}

void CTunerEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    CTunerResourceImpl* TunerResource = static_cast<CTunerResourceImpl*>(ResourceFactory::getTunerResource());
    if (TunerResource)
    {
        /** make the signal and slot connection */
        CTunerEventProvider* pTunerEventProvider = TunerResource->getTunerDataEventProvider();
        if(pTunerEventProvider)
        {
            connect(pTunerEventProvider, SIGNAL(sigUpdateFrequency(uint)), this, SLOT(sltUpdateFrequency(uint)));
            connect(pTunerEventProvider, SIGNAL(sigUpdateSeekType(uint)), this, SLOT(sltUpdateSeekType(uint)));
            connect(pTunerEventProvider, SIGNAL(sigUpdateBand(int)), this, SLOT(sltUpdateBand(int)));
            connect(pTunerEventProvider, SIGNAL(sigManualSeekStatus()), this, SLOT(sltManualSeekStatus()));
            connect(pTunerEventProvider, SIGNAL(sigUpdateStationName(const string &)), this, SLOT(sltUpdateStationName(const string &)));
            connect(pTunerEventProvider, SIGNAL(sigPresetListResponseReceived()), this, SLOT(sltUpdatePresetList()));
            connect(pTunerEventProvider, SIGNAL(sigActivePresetResponseReceived()), this, SLOT(sltActivePresetResponseReceived()));
            connect(pTunerEventProvider, SIGNAL(sigUpdateFieldStrength(int)), this, SLOT(sltUpdateFieldStrength(int)));
            connect(pTunerEventProvider, SIGNAL(sigValidStationFoundUpdated(bool)), this, SLOT(sltValidStationFoundUpdated(bool)));
            connect(pTunerEventProvider, SIGNAL(sigUpdateTagId(uint)), this, SLOT(sltTagIdUpdated(uint)));
            connect(pTunerEventProvider, SIGNAL(sigUpdateMultipath(unsigned char)), this, SLOT(sltUpdateMultipath(unsigned char)));
            connect(pTunerEventProvider, SIGNAL(sigIntrospectionProxyAvailable()), this, SLOT(sltIntrospectionProxyAvailable()));
            connect(pTunerEventProvider, SIGNAL(sigUpdateTunerStatus(bool)), this, SLOT(sltUpdateTunerStatus(bool)));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_TUNER,"pTunerEventProvider is null");
        }

    }

    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_TUNER,"Resource returns as null from Resource Factory");
    }

}

void CTunerEventHandler::sltUpdateSeekType(uint uiSeekState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, uiSeekState: %d",__FUNCTION__,uiSeekState);
    CTunerAdaptor::getInstance()->seekUpdate(static_cast<CTunerEnums::ETunerSeekType>(uiSeekState));
}

void CTunerEventHandler::sltUpdateFrequency(uint uiFrequency)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    CTunerAdaptor::getInstance()->frequencyUpdate(uiFrequency);
}

void CTunerEventHandler::sltUpdateBand(int iBand)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    CTunerEnums::ETunerBand eband = static_cast<CTunerEnums::ETunerBand>(iBand);
    CTunerAdaptor::getInstance()->bandUpdate(eband);
}

void CTunerEventHandler::sltManualSeekStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    CTunerAdaptor::getInstance()->setManualSeekStatus(false);
}

void CTunerEventHandler::sltUpdateStationName(const string &objStrStationName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    CTunerAdaptor::getInstance()->setStationName(QString::fromStdString(objStrStationName));
}

void CTunerEventHandler::sltUpdatePresetList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    CTunerAdaptor::getInstance()->setPresetList();

}

void CTunerEventHandler::sltActivePresetResponseReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
}

void CTunerEventHandler::sltUpdateFieldStrength(int iFieldStrength)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    CTunerAdaptor::getInstance()->setFieldStrength(iFieldStrength);
}

void CTunerEventHandler::sltTagIdUpdated(uint uiTagId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    CTunerAdaptor::getInstance()->setTagId(uiTagId);
}

void CTunerEventHandler::sltValidStationFoundUpdated(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    CTunerAdaptor::getInstance()->setAutoStoreCompleteSuccessStatus(bStatus);
}

void CTunerEventHandler::sltUpdateMultipath(unsigned char ucMultipath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s", __FUNCTION__);
    if(CTunerAdaptor::getInstance())
    {
        CTunerAdaptor::getInstance()->setMultipath(ucMultipath);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, TunerAdaptor Instance is NULL", __FUNCTION__);
    }
}

void CTunerEventHandler::sltIntrospectionProxyAvailable()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s", __FUNCTION__);
    if(CTunerAdaptor::getInstance())
    {
        CTunerAdaptor::getInstance()->introspectionProxyAvailable();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, TunerAdaptor Instance is NULL", __FUNCTION__);
    }
}

void CTunerEventHandler::sltUpdateTunerStatus(bool bIsTunerAvailable)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    CTunerAdaptor::getInstance()->setTunerAvailabilityStatus(bIsTunerAvailable);
}
