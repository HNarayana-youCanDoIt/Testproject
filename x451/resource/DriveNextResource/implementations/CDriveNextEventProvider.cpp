/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CDriveNextEventProvider.cpp
 * @ingroup       HMIComponent
 * @author        Nandkishor Lokhande
 * CDriveNextEventProvider, This class propagates service signals to application layer.
 */

#include "logging.h"
#include "CDriveNextEventProvider.h"

CDriveNextEventProvider::CDriveNextEventProvider(QObject *pParent) :
    QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
}

CDriveNextEventProvider::~CDriveNextEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
}

void CDriveNextEventProvider::onProxyStatusChanged(bool bAvailable)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bAvailable %d", __FUNCTION__, bAvailable);
    emit sigProxyStatusChanged(bAvailable);
}

void CDriveNextEventProvider::onResetAvailabilityStatusChanged(bool bAvailable)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bAvailable %d", __FUNCTION__, bAvailable);
    emit sigResetAvailabilityStatusChanged();
}

void CDriveNextEventProvider::onSignalValuesUpdated(list<int> listUpdatedSignalTypes)
{
    //LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s listUpdatedSignalTypes.Size:%zd", __FUNCTION__, listUpdatedSignalTypes.size());
    QList<int> qlistUpdatedSignalTypes;
    for (list<int>::iterator it = listUpdatedSignalTypes.begin(); it != listUpdatedSignalTypes.end(); ++it)
    {
        qlistUpdatedSignalTypes.push_back(*it);
    }
    emit sigSignalValuesChanged(qlistUpdatedSignalTypes);
}

void CDriveNextEventProvider::onScoreMaxRatingUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    emit sigScoreMaxRatingUpdated();
}

void CDriveNextEventProvider::onVersionInfoChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    emit sigVersionUpdated();
}

void CDriveNextEventProvider::onResetTripAsyncCb(bool bStatus, EDriveNextTripType eTripType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bStatus %d, eTripType %d", __FUNCTION__, bStatus, static_cast<int>(eTripType));
    emit sigResetTripAsyncCb(bStatus, static_cast<int>(eTripType));
}

void CDriveNextEventProvider::onUpdateConfigFileAsyncCb(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bStatus %d", __FUNCTION__, bStatus);
    emit sigUpdateConfigFileAsyncCb(bStatus);
}

void CDriveNextEventProvider::onUpdateLibFileAsyncCb(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bStatus %d", __FUNCTION__, bStatus);
    emit sigUpdateLibFileAsyncCb(bStatus);
}

void CDriveNextEventProvider::onExtractDPLogsAsyncCb(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bStatus %d", __FUNCTION__, bStatus);
    emit sigExtractDPLogsAsyncCb(bStatus);
}

void CDriveNextEventProvider::onScalingFactorsChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    emit sigScalingFactorsChanged();
}

void CDriveNextEventProvider::onSetTripLoggingAsyncCb(bool bStatus, EDriveNextTripType eTripType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bStatus %d, eTripType %d", __FUNCTION__, bStatus, static_cast<int>(eTripType));
    emit sigSetTripLoggingAsyncCb(bStatus, static_cast<int>(eTripType));
}

void CDriveNextEventProvider::onTripLoggingChanged(EDriveNextTripType eTripType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eTripType %d", __FUNCTION__, static_cast<int>(eTripType));
    emit sigTripLoggingChanged(static_cast<int>(eTripType));
}

void CDriveNextEventProvider::onSetDpLogLevelAsyncCb(bool bStatus, EDriveNextLogLevel eLogLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bStatus %d, eLogLevel %d", __FUNCTION__, bStatus, static_cast<int>(eLogLevel));
    emit sigSetDpLogLevelAsyncCb(bStatus, static_cast<int>(eLogLevel));
}

void CDriveNextEventProvider::onDpLogLevelChanged(EDriveNextLogLevel eLogLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eLogLevel %d", __FUNCTION__, static_cast<int>(eLogLevel));
    emit sigDpLogLevelChanged(static_cast<int>(eLogLevel));
}

void CDriveNextEventProvider::onSetDpLoggingTypeAsyncCb(bool bStatus, EDriveNextLoggingType eLoggingType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bStatus %d, eLoggingType %d", __FUNCTION__, bStatus, static_cast<int>(eLoggingType));
    emit sigSetDpLoggingTypeAsyncCb(bStatus, static_cast<int>(eLoggingType));
}

void CDriveNextEventProvider::onDpLoggingTypeChanged(EDriveNextLoggingType eLoggingType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eLoggingType %d", __FUNCTION__, static_cast<int>(eLoggingType));
    emit sigDpLoggingTypeChanged(static_cast<int>(eLoggingType));
}

void CDriveNextEventProvider::onDistanceUnitInfoChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    emit sigDistanceUnitInfoChanged();
}

void CDriveNextEventProvider::onFuelUnitInfoChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    emit sigFuelUnitInfoChanged();
}
