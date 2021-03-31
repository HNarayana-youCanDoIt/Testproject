/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDriveNextEventHandler.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDriveNextEventHandler, a Resource handler for DriveNext module,
 * CDriveNextEventHandler act as mediator between adaptor and resource manager.
 * The class listens for the signals raised by the resource layer provider class.
 * It has the implementation of the corresponding slots.
 */

#include <CHMIMain.h>
#include <ResourceFactory.hpp>

#include "CDriveNextApplication.h"
#include "CDriveNextAdaptor.h"
#include "CDriveNextSM.h"
#include "CDriveNextEventHandler.h"

#include "implementations/CDriveNextEventProvider.h"
#include "implementations/CDriveNextResourceImpl.h"

///////////////////////////////////////////////////////////////////////////////
// DataEventHandler related functions
///////////////////////////////////////////////////////////////////////////////
CDriveNextEventHandler::CDriveNextEventHandler(QObject *parent):
    QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    connectSignals();
}
//____________________________________________________________________________
CDriveNextEventHandler::~CDriveNextEventHandler()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    disconnectSignals();
}
//____________________________________________________________________________
void CDriveNextEventHandler::slotProxyStatusChanged(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bStatus %d", __FUNCTION__, bStatus);
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->setDriveNextPresence(bStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNextAdaptor not available", __FUNCTION__);
    }
}

void CDriveNextEventHandler::slotScalingFactorsChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->onScalingFactorsChanged();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNextAdaptor not available", __FUNCTION__);
    }
}

void CDriveNextEventHandler::slotDistanceUnitInfoChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->onDistanceUnitChanged();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNextAdaptor not available", __FUNCTION__);
    }
}

void CDriveNextEventHandler::slotFuelUnitInfoChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->onFuelUnitChanged();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNextAdaptor not available", __FUNCTION__);
    }
}

void CDriveNextEventHandler::slotResetAvailabilityStatusChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->updateDriveNextResetPresenceChanged();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNextAdaptor not available", __FUNCTION__);
    }
}

void CDriveNextEventHandler::slotSignalValuesChanged(QList<int> qlistUpdatedSignalTypes)
{
    //LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s qlistUpdatedSignalTypes.Size %d", __FUNCTION__, qlistUpdatedSignalTypes.size());
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->updateSignalValues(qlistUpdatedSignalTypes);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNextAdaptor not available", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextEventHandler::slotScoreMaxRatingUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->onScoreMaxRatingUpdated();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNextAdaptor not available", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextEventHandler::slotVersionUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->onVersionUpdated();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNextAdaptor not available", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextEventHandler::slotResetTripAsyncCb(bool bStatus, int iTripType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bStatus %d, iTripType %d", __FUNCTION__, bStatus, iTripType);
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->resetTripEnded(bStatus, static_cast<CDriveNextEnum::EDNTripType>(iTripType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNextAdaptor not available", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextEventHandler::slotUpdateLibFileAsyncCb(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bStatus %d", __FUNCTION__, bStatus);
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->updateLibFileEnded(bStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNextAdaptor not available", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextEventHandler::slotUpdateConfigFileAsyncCb(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bStatus %d", __FUNCTION__, bStatus);
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->updateConfigFileEnded(bStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNextAdaptor not available", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextEventHandler::slotExtractDPLogsAsyncCb(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bStatus %d", __FUNCTION__, bStatus);
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->exportingLogsEnded(bStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNextAdaptor not available", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextEventHandler::slotSetTripLoggingAsyncCb(bool bStatus, int iTripType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bStatus %d, iTripType %d", __FUNCTION__, bStatus, iTripType);
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        if (bStatus)
        {
            CDriveNextApplication::getDriveNextAdaptor()->setLogTripType(static_cast<CDriveNextEnum::EDNTripType>(iTripType));
        }else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Request failed", __FUNCTION__);
        }
        CDriveNextApplication::getDriveNextAdaptor()->setUpdatingLogTripType(false);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNextAdaptor not available", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextEventHandler::slotTripLoggingChanged(int iTripType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s iTripType %d", __FUNCTION__, iTripType);
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->setLogTripType(static_cast<CDriveNextEnum::EDNTripType>(iTripType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNextAdaptor not available", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextEventHandler::slotSetDpLogLevelAsyncCb(bool bStatus, int iLogLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bStatus %d, iLogLevel %d", __FUNCTION__, bStatus, iLogLevel);
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        if (bStatus)
        {
            CDriveNextApplication::getDriveNextAdaptor()->setLogLevel(static_cast<CDriveNextEnum::EDNLogLevel>(iLogLevel));
        }else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Request failed", __FUNCTION__);
        }
        CDriveNextApplication::getDriveNextAdaptor()->setUpdatingLogLevel(false);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNextAdaptor not available", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextEventHandler::slotDpLogLevelChanged(int iLogLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s iLogLevel %d", __FUNCTION__, iLogLevel);
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->setLogLevel(static_cast<CDriveNextEnum::EDNLogLevel>(iLogLevel));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNextAdaptor not available", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextEventHandler::slotSetDpLoggingTypeAsyncCb(bool bStatus, int iLoggingType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bStatus %d, iLoggingType %d", __FUNCTION__, bStatus, iLoggingType);
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        if (bStatus)
        {
            CDriveNextApplication::getDriveNextAdaptor()->setLoggingLocation(static_cast<CDriveNextEnum::EDNLoggingType>(iLoggingType));
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Request failed", __FUNCTION__);
        }
        CDriveNextApplication::getDriveNextAdaptor()->setUpdatingLoggingLocation(false);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNextAdaptor not available", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextEventHandler::slotDpLoggingTypeChanged(int iLoggingType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s iLoggingType %d", __FUNCTION__, iLoggingType);
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->setLoggingLocation(static_cast<CDriveNextEnum::EDNLoggingType>(iLoggingType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNextAdaptor not available", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    CDriveNextResourceImpl* pResource = dynamic_cast<CDriveNextResourceImpl*>(ResourceFactory::getDriveNextResource());
    if(pResource)
    {
        CDriveNextEventProvider * pEventProvider = pResource->getEventProvider();
        if(pEventProvider)
        {
            connect(pEventProvider, SIGNAL(sigProxyStatusChanged(bool)),this, SLOT(slotProxyStatusChanged(bool)), Qt::QueuedConnection);
            connect(pEventProvider, SIGNAL(sigScalingFactorsChanged()),this, SLOT(slotScalingFactorsChanged()), Qt::QueuedConnection);
            connect(pEventProvider, SIGNAL(sigDistanceUnitInfoChanged()),this, SLOT(slotDistanceUnitInfoChanged()), Qt::QueuedConnection);
            connect(pEventProvider, SIGNAL(sigFuelUnitInfoChanged()),this, SLOT(slotFuelUnitInfoChanged()), Qt::QueuedConnection);
            connect(pEventProvider, SIGNAL(sigResetAvailabilityStatusChanged()),this, SLOT(slotResetAvailabilityStatusChanged()), Qt::QueuedConnection);
            connect(pEventProvider, SIGNAL(sigSignalValuesChanged(QList<int>)),this, SLOT(slotSignalValuesChanged(QList<int>)), Qt::QueuedConnection);
            connect(pEventProvider, SIGNAL(sigScoreMaxRatingUpdated()),this, SLOT(slotScoreMaxRatingUpdated()), Qt::QueuedConnection);
            connect(pEventProvider, SIGNAL(sigVersionUpdated()),this, SLOT(slotVersionUpdated()), Qt::QueuedConnection);
            connect(pEventProvider, SIGNAL(sigResetTripAsyncCb(bool, int)),this, SLOT(slotResetTripAsyncCb(bool, int)), Qt::QueuedConnection);
            connect(pEventProvider, SIGNAL(sigUpdateLibFileAsyncCb(bool)),this, SLOT(slotUpdateLibFileAsyncCb(bool)), Qt::QueuedConnection);
            connect(pEventProvider, SIGNAL(sigUpdateConfigFileAsyncCb(bool)),this, SLOT(slotUpdateConfigFileAsyncCb(bool)), Qt::QueuedConnection);
            connect(pEventProvider, SIGNAL(sigExtractDPLogsAsyncCb(bool)),this, SLOT(slotExtractDPLogsAsyncCb(bool)), Qt::QueuedConnection);
            connect(pEventProvider, SIGNAL(sigSetTripLoggingAsyncCb(bool, int)),this, SLOT(slotSetTripLoggingAsyncCb(bool, int)), Qt::QueuedConnection);
            connect(pEventProvider, SIGNAL(sigTripLoggingChanged(int)),this, SLOT(slotTripLoggingChanged(int)), Qt::QueuedConnection);
            connect(pEventProvider, SIGNAL(sigSetDpLogLevelAsyncCb(bool, int)),this, SLOT(slotSetDpLogLevelAsyncCb(bool, int)), Qt::QueuedConnection);
            connect(pEventProvider, SIGNAL(sigDpLogLevelChanged(int)),this, SLOT(slotDpLogLevelChanged(int)), Qt::QueuedConnection);
            connect(pEventProvider, SIGNAL(sigSetDpLoggingTypeAsyncCb(bool, int)),this, SLOT(slotSetDpLoggingTypeAsyncCb(bool, int)), Qt::QueuedConnection);
            connect(pEventProvider, SIGNAL(sigDpLoggingTypeChanged(int)),this, SLOT(slotDpLoggingTypeChanged(int)), Qt::QueuedConnection);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: CDriveNextEventProvider is NULL", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext Resource is returned NULL from Resource Factory", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextEventHandler::disconnectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    CDriveNextResourceImpl* pResource = dynamic_cast<CDriveNextResourceImpl*>(ResourceFactory::getDriveNextResource());
    if(pResource)
    {
        CDriveNextEventProvider * pEventProvider = pResource->getEventProvider();
        if(pEventProvider)
        {
            disconnect(pEventProvider, SIGNAL(sigProxyStatusChanged(bool)),this, SLOT(slotProxyStatusChanged(bool)));
            disconnect(pEventProvider, SIGNAL(sigScalingFactorsChanged()),this, SLOT(slotScalingFactorsChanged()));
            disconnect(pEventProvider, SIGNAL(sigDistanceUnitInfoChanged()),this, SLOT(slotDistanceUnitInfoChanged()));
            disconnect(pEventProvider, SIGNAL(sigFuelUnitInfoChanged()),this, SLOT(slotFuelUnitInfoChanged()));
            disconnect(pEventProvider, SIGNAL(sigResetAvailabilityStatusChanged()),this, SLOT(slotResetAvailabilityStatusChanged()));
            disconnect(pEventProvider, SIGNAL(sigSignalValuesChanged(QList<int>)),this, SLOT(slotSignalValuesChanged(QList<int>)));
            disconnect(pEventProvider, SIGNAL(sigScoreMaxRatingUpdated()),this, SLOT(slotScoreMaxRatingUpdated()));
            disconnect(pEventProvider, SIGNAL(sigVersionUpdated()),this, SLOT(slotVersionUpdated()));
            disconnect(pEventProvider, SIGNAL(sigResetTripAsyncCb(bool, int)),this, SLOT(slotResetTripAsyncCb(bool, int)));
            disconnect(pEventProvider, SIGNAL(sigUpdateLibFileAsyncCb(bool)),this, SLOT(slotUpdateLibFileAsyncCb(bool)));
            disconnect(pEventProvider, SIGNAL(sigUpdateConfigFileAsyncCb(bool)),this, SLOT(slotUpdateConfigFileAsyncCb(bool)));
            disconnect(pEventProvider, SIGNAL(sigExtractDPLogsAsyncCb(bool)),this, SLOT(slotExtractDPLogsAsyncCb(bool)));
            disconnect(pEventProvider, SIGNAL(sigSetTripLoggingAsyncCb(bool, int)),this, SLOT(slotSetTripLoggingAsyncCb(bool, int)));
            disconnect(pEventProvider, SIGNAL(sigTripLoggingChanged(int)),this, SLOT(slotTripLoggingChanged(int)));
            disconnect(pEventProvider, SIGNAL(sigSetDpLogLevelAsyncCb(bool, int)),this, SLOT(slotSetDpLogLevelAsyncCb(bool, int)));
            disconnect(pEventProvider, SIGNAL(sigDpLogLevelChanged(int)),this, SLOT(slotDpLogLevelChanged(int)));
            disconnect(pEventProvider, SIGNAL(sigSetDpLoggingTypeAsyncCb(bool, int)),this, SLOT(slotSetDpLoggingTypeAsyncCb(bool, int)));
            disconnect(pEventProvider, SIGNAL(sigDpLoggingTypeChanged(int)),this, SLOT(slotDpLoggingTypeChanged(int)));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: CDriveNextEventProvider is NULL", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext Resource is returned NULL from Resource Factory", __FUNCTION__);
    }
}
