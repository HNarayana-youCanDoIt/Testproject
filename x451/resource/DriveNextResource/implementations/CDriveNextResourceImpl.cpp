/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CDriveNextResourceImpl.cpp
 * @ingroup       HMIComponent
 * @author        Nandkishor Lokhande
 * CDriveNextResourceImpl, Resource Implementation for DriveNext.
 */

#include "CDriveNextResourceImpl.h"
#include <ResourceMaster.h>
#include "logging.h"
#include "ResourceDeploymentConfig.h"
#include "CDriveNextModerator.h"

#include <iomanip>
#include <sstream>

CDriveNextResourceImpl::CDriveNextResourceImpl():
    m_pEventProvider(new CDriveNextEventProvider()),
    m_objDriveNextProxy(ResourceDeploymentConfig::getConfig().m_DriveNext_Proxy.domain, ResourceDeploymentConfig::getConfig().m_DriveNext_Proxy.instance),
    m_bProxyAvailability(false),
    m_bResetAvailability(false),
    m_dScoreScalingFactor(0)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    subscribeDriveNextProxy();

    m_mapEffciencyInfo.clear();
    m_mapDrivingInfo.clear();
    m_mapSafetyInfo.clear();
    resetSignalDataMap();

    CDriveNextModerator::validateDNProxyEnumValue();
}

CDriveNextResourceImpl::~CDriveNextResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    unSubscribeDriveNextProxy();
}

void CDriveNextResourceImpl::resetSignalDataMap()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);

    m_mapSignalValues.clear();
    SSignalDataStructure signalData;
    for (int i = 0; i < EDriveNextSignalTypes::DRIVENEXT_SIG_TOTAL_COUNT; i++)
    {
        m_mapSignalValues[static_cast<EDriveNextSignalTypes>(i)] = signalData;
    }
}

CDriveNextEventProvider *CDriveNextResourceImpl::getEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    return m_pEventProvider;
}

void CDriveNextResourceImpl::subscribeSignalsAsync(const vector<EDriveNextSignalTypes> &vectSignalTypes)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, vectSignalTypes.Size:%zd", __FUNCTION__, vectSignalTypes.size());
    if (vectSignalTypes.size() > 0)
    {
        if (getProxyAvailabilityStatus())
        {
            driveProTypeCollection::signalArray arrSignalList;
            for (uint i = 0; i < vectSignalTypes.size(); i++)
            {
                LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, vectSignalTypes[i]:%d", __FUNCTION__, static_cast<int>(vectSignalTypes[i]));
                arrSignalList.push_back(CDriveNextModerator::convertToDNProxySignalEnumValue(vectSignalTypes[i]));
            }
            m_objDriveNextProxy->subscribeSignalsAsync(arrSignalList, std::bind(&CDriveNextResourceImpl::subscribeSignalsAsyncCb, this, _1, _2, _3));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Proxy not available", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s empty vectSignalTypes list provided", __FUNCTION__);
    }
}

void CDriveNextResourceImpl::subscribeSignalsAsyncCb(CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus, driveProTypeCollection::signalArray arrSignalList)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eStatus %d, eReturnStatus %d, arrSignalList size %zd", __FUNCTION__, static_cast<int>(eStatus), eReturnStatus.value_, arrSignalList.size());
#ifdef PLATFORM_WIN32
    if ((CallStatus::SUCCESS == eStatus) && (driveProTypeCollection::eReturnStatus::SUCCESS == eReturnStatus))
    {
        driveProTypeCollection::sValuesMap signalData;
        signalData.setErrorcode(driveProTypeCollection::eDpErrorCode::SUCCESS);
        signalData.setSigValue(0);

        driveProTypeCollection::signalListValueMap mapSignalValues;
        for (int i = 0; i < arrSignalList.size(); i++)
        {
            mapSignalValues[arrSignalList[i]] = signalData;
        }
        onSignalValuesMapUpdate(mapSignalValues);
    }
    else
    {
        //Do Nothing
    }
#endif
}

void CDriveNextResourceImpl::unSubscribeSignalsAsync(const vector<EDriveNextSignalTypes> &vectSignalTypes)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, vectSignalTypes.Size:%zd", __FUNCTION__, vectSignalTypes.size());
    if (vectSignalTypes.size() > 0)
    {
        if (getProxyAvailabilityStatus())
        {
            driveProTypeCollection::signalArray arrSignalList;
            for (uint i = 0; i < vectSignalTypes.size(); i++)
            {
                LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, vectSignalTypes[i]:%d", __FUNCTION__, static_cast<int>(vectSignalTypes[i]));
                arrSignalList.push_back(CDriveNextModerator::convertToDNProxySignalEnumValue(vectSignalTypes[i]));
            }
            m_objDriveNextProxy->unSubscribeSignalsAsync(arrSignalList, std::bind(&CDriveNextResourceImpl::unSubscribeSignalsAsyncCb, this, _1, _2, _3));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Proxy not available", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s empty vectSignalTypes list provided", __FUNCTION__);
    }
}

void CDriveNextResourceImpl::unSubscribeSignalsAsyncCb(CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus, driveProTypeCollection::signalArray arrSignalList)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eStatus %d, eReturnStatus %d, arrSignalList size %zd", __FUNCTION__, static_cast<int>(eStatus), eReturnStatus.value_, arrSignalList.size());
}

void CDriveNextResourceImpl::getSignaListValueFromProxy()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    if (getProxyAvailabilityStatus())
    {
        CommonAPI::CallStatus eStatus = CommonAPI::CallStatus::UNKNOWN;
        driveProTypeCollection::eReturnStatus eReturnStatus = driveProTypeCollection::eReturnStatus::FAILURE;

        m_objDriveNextProxy->getSignaListValue(eStatus, eReturnStatus);
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eStatus %d, eReturnStatus %d", __FUNCTION__, static_cast<int>(eStatus), eReturnStatus.value_);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Proxy not available", __FUNCTION__);
    }
}

void CDriveNextResourceImpl::getMaxRatingFromProxy()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    if (getProxyAvailabilityStatus())
    {
        CommonAPI::CallStatus eStatus = CommonAPI::CallStatus::UNKNOWN;
        driveProTypeCollection::eReturnStatus eReturnStatus = driveProTypeCollection::eReturnStatus::FAILURE;
        uint iMaxRating = 0;
        m_objDriveNextProxy->getMaxRating(eStatus, iMaxRating, eReturnStatus);

        if ((CommonAPI::CallStatus::SUCCESS == eStatus) && (driveProTypeCollection::eReturnStatus::SUCCESS == eReturnStatus))
        {
            m_objScoreMaxRating.setValue(iMaxRating);
            m_objScoreMaxRating.setErrorType(EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_SUCCESS);
            LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_objScoreMaxRating:%lf", __FUNCTION__, m_objScoreMaxRating.getValue());
        }
        else
        {
            m_objScoreMaxRating.setValue(0);
            m_objScoreMaxRating.setErrorType(EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_UNKNOWN);
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s CALL FAIL eStatus %d, eReturnStatus %d", __FUNCTION__, static_cast<int>(eStatus), eReturnStatus.value_);
        }

        if(m_pEventProvider)
        {
            m_pEventProvider->onScoreMaxRatingUpdated();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_pEventProvider not available", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Proxy not available", __FUNCTION__);
    }
}

map<EDriveNextSignalTypes, SSignalDataStructure> CDriveNextResourceImpl::getSignalValuesMap()
{
    //LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_mapSignalValues.Size:%zd", __FUNCTION__, m_mapSignalValues.size());
    return m_mapSignalValues;
}

void CDriveNextResourceImpl::onSignalValuesMapUpdate(driveProTypeCollection::signalListValueMap mapSignalValues)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s mapSignalValues.Size:%zd", __FUNCTION__, mapSignalValues.size());
    if (mapSignalValues.size() > 0)
    {
        list<int> listUpdatedSignalTypes;

        for (driveProTypeCollection::signalListValueMap::iterator it = mapSignalValues.begin(); it != mapSignalValues.end(); ++it)
        {
            driveProTypeCollection::eSignalNames eProxySignalType = it->first;
            driveProTypeCollection::sValuesMap sProxySignalData = it->second;
            SSignalDataStructure signalData;

            EDriveNextSignalTypes eSignalType = CDriveNextModerator::convertToDNHmiSignalEnumValue(static_cast<driveProTypeCollection::eSignalNames::Literal>(eProxySignalType.value_));
            signalData.setErrorType(CDriveNextModerator::convertDriveNextSignalErrorType(sProxySignalData.getErrorcode()));
            signalData.setValue(sProxySignalData.getSigValue());

            if (EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_SUCCESS != signalData.getErrorType())
            {
                LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eSignalType:%d dSignalValue:%lf dSignalErrorType:%d HMIErrorType:%d", __FUNCTION__, static_cast<int>(eSignalType), sProxySignalData.getSigValue(), static_cast<int>(sProxySignalData.getErrorcode()), static_cast<int>(signalData.getErrorType()));
            }
            else
            {
                //Do Nothing!
            }
            m_mapSignalValues[eSignalType] = signalData;
            listUpdatedSignalTypes.push_back(static_cast<int>(eSignalType));
        }

        if(m_pEventProvider)
        {
            m_pEventProvider->onSignalValuesUpdated(listUpdatedSignalTypes);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_pEventProvider not available", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s no signal data received", __FUNCTION__);
    }
}

void CDriveNextResourceImpl::driveNextProxyStatusCb(AvailabilityStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, DriveNext service status : %d", __FUNCTION__, static_cast<int>(eStatus));
    m_bProxyAvailability = (CommonAPI::AvailabilityStatus::AVAILABLE == eStatus);

    if(m_pEventProvider)
    {
        m_pEventProvider->onProxyStatusChanged(m_bProxyAvailability);
        if (getProxyAvailabilityStatus())
        {
            getServiceScalingFactors();
            getMaxRatingFromProxy();
            getServiceAttributeValues();
        }
        else
        {
            ////Do Nothing
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_pEventProvider not available", __FUNCTION__);
    }
}

bool CDriveNextResourceImpl::getProxyAvailabilityStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_bProxyAvailability %d", __FUNCTION__, m_bProxyAvailability);
    return m_bProxyAvailability;
}

void CDriveNextResourceImpl::driveNextResetAvailabilityStatusCb(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, DriveNext Engine RPM Running bStatus:%d", __FUNCTION__, bStatus);
    m_bResetAvailability = !bStatus;
    if(m_pEventProvider)
    {
        m_pEventProvider->onResetAvailabilityStatusChanged(m_bResetAvailability);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_pEventProvider not available", __FUNCTION__);
    }
}

bool CDriveNextResourceImpl::getResetAvailabilityStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_bResetAvailability %d", __FUNCTION__, m_bResetAvailability);
    return m_bResetAvailability;
}

void CDriveNextResourceImpl::onTripResetRequestCb(driveProTypeCollection::sTripResetStatus objTripResetStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s getTriptype:%d, getTripResetStatus:%d", __FUNCTION__, static_cast<int>(objTripResetStatus.getTriptype()), static_cast<int>(objTripResetStatus.getTripResetStatus()));
    if(m_pEventProvider)
    {
        m_pEventProvider->onResetTripAsyncCb((driveProTypeCollection::eReturnStatus::SUCCESS == objTripResetStatus.getTripResetStatus()), CDriveNextModerator::convertDriveNextTripType(objTripResetStatus.getTriptype()));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_pEventProvider not available", __FUNCTION__);
    }
}

void CDriveNextResourceImpl::onVersionInfoAttributeCb(driveProTypeCollection::sDpVersionInfo objVersionInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s getLibraryVersion %s, ConfigVersion %lf", __FUNCTION__, objVersionInfo.getLibraryVersion().c_str(), objVersionInfo.getConfigVersion());
    m_objVersionInfo = objVersionInfo;

    if(m_pEventProvider)
    {
        m_pEventProvider->onVersionInfoChanged();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_pEventProvider not available", __FUNCTION__);
    }
}

string CDriveNextResourceImpl::getDNLibVersion()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s DNLibVersion %s", __FUNCTION__, m_objVersionInfo.getLibraryVersion().c_str());
    return m_objVersionInfo.getLibraryVersion();
}

string CDriveNextResourceImpl::getDNConfigVersion()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s ConfigVersion %lf", __FUNCTION__, m_objVersionInfo.getConfigVersion());
    double dConfigVersion = m_objVersionInfo.getConfigVersion();
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << dConfigVersion;
    std::string strConfigVersion = stream.str();
    return strConfigVersion;
}

void CDriveNextResourceImpl::subscribeDriveNextProxy()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    SUBSCRIBE(m_objDriveNextProxy, getProxyStatusEvent(), &CDriveNextResourceImpl::driveNextProxyStatusCb, _1);

#ifndef PLATFORM_WIN32
    ////Fix Me this code not working on windows simulation, need to verify with driveNext proxy
    SUBSCRIBE(m_objDriveNextProxy, getBlueScreenDataUpdateEvent(), &CDriveNextResourceImpl::onSignalValuesMapUpdate, _1);
    SUBSCRIBE(m_objDriveNextProxy, getRpmEnableStatusUpdateEvent(), &CDriveNextResourceImpl::driveNextResetAvailabilityStatusCb, _1);
    SUBSCRIBE(m_objDriveNextProxy, getTripResetStatusEvent(), &CDriveNextResourceImpl::onTripResetRequestCb, _1);
#endif

    SUBSCRIBE(m_objDriveNextProxy, getS_DpVersionInfoAttribute().getChangedEvent(), &CDriveNextResourceImpl::onVersionInfoAttributeCb, _1);
    SUBSCRIBE(m_objDriveNextProxy, getResetAllOptionEnabledAttribute().getChangedEvent(), &CDriveNextResourceImpl::onResetAllOptionEnabledAttributeCb, _1);
    SUBSCRIBE(m_objDriveNextProxy, getS_EfficiencyInfoAttribute().getChangedEvent(), &CDriveNextResourceImpl::onEfficiencyInfoAttributeCb, _1);
    SUBSCRIBE(m_objDriveNextProxy, getS_DrivingInfoAttribute().getChangedEvent(), &CDriveNextResourceImpl::onDrivingInfoAttributeCb, _1);
    SUBSCRIBE(m_objDriveNextProxy, getS_SafetyInfoAttribute().getChangedEvent(), &CDriveNextResourceImpl::onSafetyInfoAttributeCb, _1);

    SUBSCRIBE(m_objDriveNextProxy, getS_DistUnitAttribute().getChangedEvent(), &CDriveNextResourceImpl::onDistUnitAttributeChanged, _1);
    SUBSCRIBE(m_objDriveNextProxy, getS_FuelUnitAttribute().getChangedEvent(), &CDriveNextResourceImpl::onFuelUnitAttributeChanged, _1);
}

void CDriveNextResourceImpl::unSubscribeDriveNextProxy()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
}

void CDriveNextResourceImpl::onResetAllOptionEnabledAttributeCb(bool bIsResetAllOptionEnabled)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s %d", __FUNCTION__, bIsResetAllOptionEnabled);
    //Todo: Need to implement the Reset All option enabled flow
}

void CDriveNextResourceImpl::onEfficiencyInfoAttributeCb(driveProTypeCollection::sEffciencyInfo objEffciencyInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);

    SEffciencyInfo objEffciencyInfoItem;

    objEffciencyInfoItem.eTripType = CDriveNextModerator::convertDriveNextTripType(objEffciencyInfo.getTripType());
    objEffciencyInfoItem.dFuelEcoInstRating = objEffciencyInfo.getFuelEcoInstRating();
    objEffciencyInfoItem.dFuelEcoCumulativeRating = objEffciencyInfo.getFuelEcoCumulativeRating();

    objEffciencyInfoItem.dEngineIdleTime = objEffciencyInfo.getEngineIdleTime();
    objEffciencyInfoItem.dAverageSpeed = objEffciencyInfo.getAverageSpeed();

    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "Trip Type : %d, Fuel Eco Inst Rating : %lf, Fuel Eco Cumulative Rating : %lf, Engine Idle Time : %lf, Average Speed : %lf",
             static_cast<int>(objEffciencyInfoItem.eTripType), objEffciencyInfoItem.dFuelEcoInstRating, objEffciencyInfoItem.dFuelEcoCumulativeRating,
             objEffciencyInfoItem.dEngineIdleTime, objEffciencyInfoItem.dAverageSpeed);

    objEffciencyInfoItem.setAverageFuelEconomy( CDriveNextModerator::convertDriveNextTripType(objEffciencyInfo.getS_averageFuelEconomy().getTripType()),
                                                objEffciencyInfo.getS_averageFuelEconomy().getAverageFuelEconomy() );

    objEffciencyInfoItem.setRpmBandInfo( objEffciencyInfo.getS_rpmBandInfo().getTotalTime(),
                                         objEffciencyInfo.getS_rpmBandInfo().getTotalDistance(),
                                         objEffciencyInfo.getS_rpmBandInfo().getEffRpmTimeAmber(),
                                         objEffciencyInfo.getS_rpmBandInfo().getEffRpmTimeAmberPer(),
                                         objEffciencyInfo.getS_rpmBandInfo().getEffRpmTimeGreen(),
                                         objEffciencyInfo.getS_rpmBandInfo().getEffRpmTimeGreenPer(),
                                         objEffciencyInfo.getS_rpmBandInfo().getEffRpmTimeRed(),
                                         objEffciencyInfo.getS_rpmBandInfo().getEffRpmTimeRedPer(),
                                         objEffciencyInfo.getS_rpmBandInfo().getEffRpmDistAmber(),
                                         objEffciencyInfo.getS_rpmBandInfo().getEffRpmDistAmberPer(),
                                         objEffciencyInfo.getS_rpmBandInfo().getEffRpmDistGreen(),
                                         objEffciencyInfo.getS_rpmBandInfo().getEffRpmDistGreenPer(),
                                         objEffciencyInfo.getS_rpmBandInfo().getEffRpmDistRed(),
                                         objEffciencyInfo.getS_rpmBandInfo().getEffRpmDistRedPer()
                                         );

    m_mapEffciencyInfo[objEffciencyInfoItem.eTripType] = objEffciencyInfoItem;

    //Todo: Need to inform the upper layer
}

void CDriveNextResourceImpl::onDrivingInfoAttributeCb(driveProTypeCollection::sDrivingInfo objDrivingInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);

    SDrivingInfo objDrivingInfoItem;

    objDrivingInfoItem.eTripType = CDriveNextModerator::convertDriveNextTripType(objDrivingInfo.getTripType());
    objDrivingInfoItem.dTopSpeed = objDrivingInfo.getTopSpeed();
    objDrivingInfoItem.dCorrectGearPerTime = objDrivingInfo.getCorrectGearPerTime();
    objDrivingInfoItem.dAverageAccPedalTravelPosition = objDrivingInfo.getAverageAccPedalTravelPosition();
    objDrivingInfoItem.dMostUsedGear = objDrivingInfo.getMostUsedGear();
    objDrivingInfoItem.dCumulativeRatingofAvgAcc = objDrivingInfo.getCumulativeRatingofAvgAcc();
    objDrivingInfoItem.dCumulativeRatingofAvgBrake = objDrivingInfo.getCumulativeRatingofAvgBrake();
    objDrivingInfoItem.dCumulativeRatingofAvgGear = objDrivingInfo.getCumulativeRatingofAvgGear();
    objDrivingInfoItem.dInstRatingofAvgAcc = objDrivingInfo.getInstRatingofAvgAcc();
    objDrivingInfoItem.dInstRatingofAvgBrake = objDrivingInfo.getInstRatingofAvgBrake();
    objDrivingInfoItem.dInstRatingofAvgGear = objDrivingInfo.getInstRatingofAvgGear();
    objDrivingInfoItem.dBrakingCountPer10Km = objDrivingInfo.getBrakingCountPer10Km();

    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "Trip Type : %d, TopSpeed : %lf, CorrectGearPerTime : %lf, AverageAccPedalTravelPosition : %lf, MostUsedGear : %lf",
             static_cast<int>(objDrivingInfoItem.eTripType), objDrivingInfoItem.dTopSpeed, objDrivingInfoItem.dCorrectGearPerTime,
             objDrivingInfoItem.dAverageAccPedalTravelPosition, objDrivingInfoItem.dMostUsedGear);

    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "CumulativeRatingofAvgAcc : %lf, CumulativeRatingofAvgBrake : %lf, CumulativeRatingofAvgGear : %lf, InstRatingofAvgAcc : %lf, dInstRatingofAvgBrake : %lf, InstRatingofAvgGear : %lf, dBrakingCountPer10Km : %lf",
             objDrivingInfoItem.dCumulativeRatingofAvgAcc, objDrivingInfoItem.dCumulativeRatingofAvgBrake, objDrivingInfoItem.dCumulativeRatingofAvgGear,
             objDrivingInfoItem.dInstRatingofAvgAcc, objDrivingInfoItem.dInstRatingofAvgBrake, objDrivingInfoItem.dInstRatingofAvgGear,
             objDrivingInfoItem.dBrakingCountPer10Km);

    objDrivingInfoItem.setDiffSpeedBandsPerTime(
                CDriveNextModerator::convertDriveNextTripType(objDrivingInfo.getDiffSpeedBandsPerTime().getTripType()),
                objDrivingInfo.getDiffSpeedBandsPerTime().getSpeedBand1TimePer(), objDrivingInfo.getDiffSpeedBandsPerTime().getSpeedBand2TimePer(),
                objDrivingInfo.getDiffSpeedBandsPerTime().getSpeedBand3TimePer(), objDrivingInfo.getDiffSpeedBandsPerTime().getSpeedBand4TimePer(),
                objDrivingInfo.getDiffSpeedBandsPerTime().getSpeedBand1Time(), objDrivingInfo.getDiffSpeedBandsPerTime().getSpeedBand2Time(),
                objDrivingInfo.getDiffSpeedBandsPerTime().getSpeedBand3Time(), objDrivingInfo.getDiffSpeedBandsPerTime().getSpeedBand4Time()
                );

    m_mapDrivingInfo[objDrivingInfoItem.eTripType] = objDrivingInfoItem;

    //Todo: Need to inform the upper layer
}

void CDriveNextResourceImpl::onSafetyInfoAttributeCb(driveProTypeCollection::sSafetyInfo objSafetyInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);

    SSafetyInfo objSafetyInfoItem;

    objSafetyInfoItem.dSafetyInstRating = objSafetyInfo.getSafetyInstRating();
    objSafetyInfoItem.dAverageSpeed = objSafetyInfo.getAverageSpeed();

    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "Safety Inst Rating : %lf, Average Speed : %lf",
             objSafetyInfoItem.dSafetyInstRating, objSafetyInfoItem.dAverageSpeed);

    objSafetyInfoItem.setSeatBeltPerTime( CDriveNextModerator::convertDriveNextTripType(objSafetyInfo.getS_seatBeltPerTime().getTripType()),
                                          objSafetyInfo.getS_seatBeltPerTime().getPerTimeWithoutSeatbelt(),
                                          objSafetyInfo.getS_seatBeltPerTime().getPerTimeWithSeatbelt(),
                                          objSafetyInfo.getS_seatBeltPerTime().getSeatBeltFactor() );

    objSafetyInfoItem.setBrakingTypeInfo( CDriveNextModerator::convertDriveNextTripType(objSafetyInfo.getS_breakingtypeInfo().getTripType()),
                                          objSafetyInfo.getS_breakingtypeInfo().getTotalBrk(),
                                          objSafetyInfo.getS_breakingtypeInfo().getNormalBrk(),
                                          objSafetyInfo.getS_breakingtypeInfo().getNormalBrkPer(),
                                          objSafetyInfo.getS_breakingtypeInfo().getModerateBrk(),
                                          objSafetyInfo.getS_breakingtypeInfo().getModerateBrkPer(),
                                          objSafetyInfo.getS_breakingtypeInfo().getHeavyBrk(),
                                          objSafetyInfo.getS_breakingtypeInfo().getHeavyBrkPer(),
                                          objSafetyInfo.getS_breakingtypeInfo().getPanicBrk(),
                                          objSafetyInfo.getS_breakingtypeInfo().getPanicBrkPer(),
                                          objSafetyInfo.getS_breakingtypeInfo().getHarshBrk(),
                                          objSafetyInfo.getS_breakingtypeInfo().getHarshBrkPer() );

    m_mapSafetyInfo[objSafetyInfoItem.sSeatBeltPerTime.eTripType] = objSafetyInfoItem;

    //Todo: Need to inform the upper layer
}

void CDriveNextResourceImpl::onDistUnitAttributeChanged(driveProTypeCollection::sDistUnit objDistUnitInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s EnumDistUnit:%d, ScalingFactor:%lf", __FUNCTION__, static_cast<int>(objDistUnitInfo.getEnumDistUnit()), objDistUnitInfo.getScalingFactor());
    m_objDistanceUnitInfo.m_eUnitType = CDriveNextModerator::convertDriveNextDistUnitType(objDistUnitInfo.getEnumDistUnit());

    if (m_objDistanceUnitInfo.m_eUnitType != EDriveNextDistanceUnitType::DRIVENEXT_DIST_TYPE_UNKNOWN)
    {
        m_objDistanceUnitInfo.m_dUnitScale = objDistUnitInfo.getScalingFactor();
    }
    else
    {
        m_objDistanceUnitInfo.m_dUnitScale = 0;
    }

    if(m_pEventProvider)
    {
        m_pEventProvider->onDistanceUnitInfoChanged();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_pEventProvider not available", __FUNCTION__);
    }
}

SDistanceUnitInfo CDriveNextResourceImpl::getDistanceUnitInfo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_eUnitType:%d, m_dUnitScale:%lf", __FUNCTION__, static_cast<int>(m_objDistanceUnitInfo.m_eUnitType), m_objDistanceUnitInfo.m_dUnitScale);
    return m_objDistanceUnitInfo;
}

void CDriveNextResourceImpl::onFuelUnitAttributeChanged(driveProTypeCollection::sFuelUnit objFuelUnitInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s EnumFuelUnit:%d, ScalingFactor:%lf", __FUNCTION__, static_cast<int>(objFuelUnitInfo.getEnumFuelUnit()), objFuelUnitInfo.getScalingFactor());
    m_objFuelUnitInfo.m_eUnitType = CDriveNextModerator::convertDriveNextFuelUnitType(objFuelUnitInfo.getEnumFuelUnit());

    if (m_objFuelUnitInfo.m_eUnitType != EDriveNextFuelUnitType::DRIVENEXT_FUEL_TYPE_UNKNOWN)
    {
        m_objFuelUnitInfo.m_dUnitScale = objFuelUnitInfo.getScalingFactor();
    }
    else
    {
        m_objFuelUnitInfo.m_dUnitScale = 0;
    }

    if(m_pEventProvider)
    {
        m_pEventProvider->onFuelUnitInfoChanged();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_pEventProvider not available", __FUNCTION__);
    }
}

SFuelUnitInfo CDriveNextResourceImpl::getFuelUnitInfo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_eUnitType:%d, m_dUnitScale:%lf", __FUNCTION__, static_cast<int>(m_objFuelUnitInfo.m_eUnitType), m_objFuelUnitInfo.m_dUnitScale);
    return m_objFuelUnitInfo;
}

SSignalDataStructure CDriveNextResourceImpl::getScoreMaxRatingInfo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s value:%lf, error:%d", __FUNCTION__, m_objScoreMaxRating.getValue(), static_cast<int>(m_objScoreMaxRating.getErrorType()));
    return m_objScoreMaxRating;
}

void CDriveNextResourceImpl::resetTripAsync(EDriveNextTripType eTripType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eTripType:%d", __FUNCTION__, static_cast<int>(eTripType));
    if (getProxyAvailabilityStatus())
    {
        driveProTypeCollection::eTripType eProxyTripType = driveProTypeCollection::eTripType::TRIP_A;
        if (CDriveNextModerator::convertDriveNextProxyTripType(eTripType, eProxyTripType))
        {
            m_objDriveNextProxy->resetTripAsync(eProxyTripType, std::bind(&CDriveNextResourceImpl::resetTripAsyncCb, this, _1, _2, _3));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eTripType:%d fail to convert in proxy trip type", __FUNCTION__, static_cast<int>(eTripType));
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Proxy not available", __FUNCTION__);
    }
}

void CDriveNextResourceImpl::resetTripAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus, driveProTypeCollection::eTripType eTripType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eStatus %d, eReturnStatus %d, eTripType %d", __FUNCTION__, static_cast<int>(eStatus), eReturnStatus.value_, static_cast<int>(eTripType));
    if(m_pEventProvider)
    {
#ifdef PLATFORM_WIN32
        m_pEventProvider->onResetTripAsyncCb(((CommonAPI::CallStatus::SUCCESS == eStatus) && (driveProTypeCollection::eReturnStatus::SUCCESS == eReturnStatus)), CDriveNextModerator::convertDriveNextTripType(eTripType));
#else
        if (CommonAPI::CallStatus::SUCCESS != eStatus)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Call Failed", __FUNCTION__);
            m_pEventProvider->onResetTripAsyncCb(false, CDriveNextModerator::convertDriveNextTripType(eTripType));
        }
        else
        {
            //Do Nothing
        }
#endif
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_pEventProvider not available", __FUNCTION__);
    }
}

void CDriveNextResourceImpl::updateLibFileAsync()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    if (getProxyAvailabilityStatus())
    {
        m_objDriveNextProxy->updateDpDynamicLibAsync(std::bind(&CDriveNextResourceImpl::updateLibFileAsyncCb, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Proxy not available", __FUNCTION__);
    }
}

void CDriveNextResourceImpl::updateLibFileAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eStatus %d, eReturnStatus %d", __FUNCTION__, static_cast<int>(eStatus), eReturnStatus.value_);
    if(m_pEventProvider)
    {
        m_pEventProvider->onUpdateLibFileAsyncCb((CommonAPI::CallStatus::SUCCESS == eStatus) && (driveProTypeCollection::eReturnStatus::SUCCESS == eReturnStatus));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_pEventProvider not available", __FUNCTION__);
    }
}

void CDriveNextResourceImpl::updateConfigFileAsync()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    if (getProxyAvailabilityStatus())
    {
        m_objDriveNextProxy->updateConfigFileAsync(std::bind(&CDriveNextResourceImpl::updateConfigFileAsyncCb, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Proxy not available", __FUNCTION__);
    }
}

void CDriveNextResourceImpl::updateConfigFileAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eStatus %d, eReturnStatus %d", __FUNCTION__, static_cast<int>(eStatus), eReturnStatus.value_);
    if(m_pEventProvider)
    {
        m_pEventProvider->onUpdateConfigFileAsyncCb((CommonAPI::CallStatus::SUCCESS == eStatus) && (driveProTypeCollection::eReturnStatus::SUCCESS == eReturnStatus));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_pEventProvider not available", __FUNCTION__);
    }
}

void CDriveNextResourceImpl::extractDPLogsAsync()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    if (getProxyAvailabilityStatus())
    {
        m_objDriveNextProxy->extractDPLogsAsync(std::bind(&CDriveNextResourceImpl::extractDPLogsAsyncCb, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Proxy not available", __FUNCTION__);
    }
}

void CDriveNextResourceImpl::extractDPLogsAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eStatus %d, eReturnStatus %d", __FUNCTION__, static_cast<int>(eStatus), eReturnStatus.value_);
    if(m_pEventProvider)
    {
        m_pEventProvider->onExtractDPLogsAsyncCb((CommonAPI::CallStatus::SUCCESS == eStatus) && (driveProTypeCollection::eReturnStatus::SUCCESS == eReturnStatus));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_pEventProvider not available", __FUNCTION__);
    }
}

void CDriveNextResourceImpl::setTripLoggingAsync(EDriveNextTripType eTripType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eTripType %d", __FUNCTION__, static_cast<int>(eTripType));
    if (getProxyAvailabilityStatus())
    {
        driveProTypeCollection::eTripType eProxyTripType = driveProTypeCollection::eTripType::TRIP_A;
        if (CDriveNextModerator::convertDriveNextProxyTripType(eTripType, eProxyTripType))
        {
            m_objDriveNextProxy->setTripLoggingAsync(eProxyTripType, std::bind(&CDriveNextResourceImpl::setTripLoggingAsyncCb, this, _1, _2, _3));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eTripType:%d fail to convert in proxy trip type", __FUNCTION__, static_cast<int>(eTripType));
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Proxy not available", __FUNCTION__);
    }
}

void CDriveNextResourceImpl::setTripLoggingAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus, driveProTypeCollection::eTripType eTripType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eStatus %d, eReturnStatus %d, eTripType %d", __FUNCTION__, static_cast<int>(eStatus), eReturnStatus.value_, static_cast<int>(eTripType));
    if(m_pEventProvider)
    {
        m_pEventProvider->onSetTripLoggingAsyncCb(((CommonAPI::CallStatus::SUCCESS == eStatus) && (driveProTypeCollection::eReturnStatus::SUCCESS == eReturnStatus)), CDriveNextModerator::convertDriveNextTripType(eTripType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_pEventProvider not available", __FUNCTION__);
    }
}

void CDriveNextResourceImpl::getServiceScalingFactors()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    if (getProxyAvailabilityStatus())
    {
        CommonAPI::CallStatus eStatus = CommonAPI::CallStatus::UNKNOWN;
        double dScalingFactor = 0;
        m_objDriveNextProxy->getScalingFactor(eStatus, dScalingFactor);
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eStatus %d, dScalingFactor %lf", __FUNCTION__, static_cast<int>(eStatus), dScalingFactor);
        getServiceScalingFactorsAsyncCb(eStatus, dScalingFactor);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Proxy not available", __FUNCTION__);
    }
}

void CDriveNextResourceImpl::getServiceScalingFactorsAsync()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    if (getProxyAvailabilityStatus())
    {
        m_objDriveNextProxy->getScalingFactorAsync(std::bind(&CDriveNextResourceImpl::getServiceScalingFactorsAsyncCb, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Proxy not available", __FUNCTION__);
    }
}

void CDriveNextResourceImpl::getServiceScalingFactorsAsyncCb(const CommonAPI::CallStatus& eStatus, const double &dScalingFactor)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eStatus %d, dScalingFactor %lf", __FUNCTION__, static_cast<int>(eStatus), dScalingFactor);
    if (CommonAPI::CallStatus::SUCCESS == eStatus)
    {
        if (dScalingFactor > 0)
        {
            m_dScoreScalingFactor = dScalingFactor;
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Invalid scale factor eStatus %d, dScalingFactor %lf", __FUNCTION__, static_cast<int>(eStatus), dScalingFactor);
            m_dScoreScalingFactor = 0;
        }

        if(m_pEventProvider)
        {
            m_pEventProvider->onScalingFactorsChanged();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_pEventProvider not available", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s getServiceScalingFactorsAsync failed eStatus %d", __FUNCTION__, static_cast<int>(eStatus));
    }
}

double CDriveNextResourceImpl::getScoreScalingFactor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, m_dScoreScalingFactor:%lf", __FUNCTION__,m_dScoreScalingFactor);
    return m_dScoreScalingFactor;
}

EDriveNextTripType CDriveNextResourceImpl::getTripLogging()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    EDriveNextTripType eHMITripType = EDriveNextTripType::DRIVENEXT_TRIP_UNKNOWN;
    if (getProxyAvailabilityStatus())
    {
        CommonAPI::CallStatus eStatus = CommonAPI::CallStatus::UNKNOWN;
        driveProTypeCollection::eReturnStatus eReturnStatus = driveProTypeCollection::eReturnStatus::FAILURE;
        driveProTypeCollection::eTripType eProxyTripType = driveProTypeCollection::eTripType::TRIP_A;

        m_objDriveNextProxy->getTripLogging(eStatus, eReturnStatus, eProxyTripType);
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eStatus %d, eReturnStatus %d, eProxyTripType %d", __FUNCTION__, static_cast<int>(eStatus), eReturnStatus.value_, static_cast<int>(eProxyTripType));

        eHMITripType = CDriveNextModerator::convertDriveNextTripType(eProxyTripType);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Proxy not available", __FUNCTION__);
    }
    return eHMITripType;
}

void CDriveNextResourceImpl::setDpLogLevelAsync(EDriveNextLogLevel eLogLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eLogLevel %d", __FUNCTION__, static_cast<int>(eLogLevel));
    if (getProxyAvailabilityStatus())
    {
        uint32_t iProxyLogLevel = 0;
        if (CDriveNextModerator::convertDriveNextProxyLogLevel(eLogLevel, iProxyLogLevel))
        {
            m_objDriveNextProxy->setDpLogLevelAsync(iProxyLogLevel, std::bind(&CDriveNextResourceImpl::setDpLogLevelAsyncCb, this, _1, _2, _3));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eLogLevel %d not handled", __FUNCTION__, static_cast<int>(eLogLevel));
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Proxy not available", __FUNCTION__);
    }
}

void CDriveNextResourceImpl::setDpLogLevelAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus, uint32_t uiLogLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eStatus %d, eReturnStatus %d, uiLogLevel %d", __FUNCTION__, static_cast<int>(eStatus), eReturnStatus.value_, uiLogLevel);
    if(m_pEventProvider)
    {
        m_pEventProvider->onSetDpLogLevelAsyncCb(((CommonAPI::CallStatus::SUCCESS == eStatus) && (driveProTypeCollection::eReturnStatus::SUCCESS == eReturnStatus)), CDriveNextModerator::convertDriveNextLogLevel(uiLogLevel));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_pEventProvider not available", __FUNCTION__);
    }
}

EDriveNextLogLevel CDriveNextResourceImpl::getDpLogLevel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    EDriveNextLogLevel eHMILogLevel = EDriveNextLogLevel::DRIVENEXT_LOG_LEVEL_UNKNOWN;
    if (getProxyAvailabilityStatus())
    {
        CommonAPI::CallStatus eStatus = CommonAPI::CallStatus::UNKNOWN;
        driveProTypeCollection::eReturnStatus eReturnStatus = driveProTypeCollection::eReturnStatus::FAILURE;
        uint32_t uiLogLevel = 0;

        m_objDriveNextProxy->getDpLogLevel(eStatus, eReturnStatus, uiLogLevel);
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eStatus %d, eReturnStatus %d, uiLogLevel %d", __FUNCTION__, static_cast<int>(eStatus), eReturnStatus.value_, uiLogLevel);

        eHMILogLevel = CDriveNextModerator::convertDriveNextLogLevel(uiLogLevel);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Proxy not available", __FUNCTION__);
    }
    return eHMILogLevel;
}

void CDriveNextResourceImpl::setDpLoggingTypeAsync(EDriveNextLoggingType eLoggingType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eLoggingType %d", __FUNCTION__, static_cast<int>(eLoggingType));
    if (getProxyAvailabilityStatus())
    {
        driveProTypeCollection::eLoggingType eProxtLoggingType = driveProTypeCollection::eLoggingType::LOGGING_INTERNAL;
        if (CDriveNextModerator::convertDriveNextProxyLoggingType(eLoggingType, eProxtLoggingType))
        {
            m_objDriveNextProxy->setDpLoggingTypeAsync(eProxtLoggingType, std::bind(&CDriveNextResourceImpl::setDpLoggingTypeAsyncCb, this, _1, _2, _3));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eLoggingType %d not handled", __FUNCTION__, static_cast<int>(eLoggingType));
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Proxy not available", __FUNCTION__);
    }
}

void CDriveNextResourceImpl::setDpLoggingTypeAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus, driveProTypeCollection::eLoggingType eLoggingType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eStatus %d, eReturnStatus %d, eLoggingType %d", __FUNCTION__, static_cast<int>(eStatus), eReturnStatus.value_, static_cast<int>(eLoggingType));
    if(m_pEventProvider)
    {
        m_pEventProvider->onSetDpLoggingTypeAsyncCb(((CommonAPI::CallStatus::SUCCESS == eStatus) && (driveProTypeCollection::eReturnStatus::SUCCESS == eReturnStatus)), CDriveNextModerator::convertDriveNextLoggingType(eLoggingType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_pEventProvider not available", __FUNCTION__);
    }
}

EDriveNextLoggingType CDriveNextResourceImpl::getDpLoggingType()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    EDriveNextLoggingType eHMILoggingType = EDriveNextLoggingType::DRIVENEXT_LOG_TYPE_UNKNOWN;
    if (getProxyAvailabilityStatus())
    {
        CommonAPI::CallStatus eStatus = CommonAPI::CallStatus::UNKNOWN;
        driveProTypeCollection::eReturnStatus eReturnStatus = driveProTypeCollection::eReturnStatus::FAILURE;
        driveProTypeCollection::eLoggingType eLoggingType = driveProTypeCollection::eLoggingType::LOGGING_INTERNAL;

        m_objDriveNextProxy->getDpLoggingType(eStatus, eReturnStatus, eLoggingType);
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eStatus %d, eReturnStatus %d, eLoggingType %d", __FUNCTION__, static_cast<int>(eStatus), eReturnStatus.value_, static_cast<int>(eLoggingType));

        eHMILoggingType = CDriveNextModerator::convertDriveNextLoggingType(eLoggingType);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Proxy not available", __FUNCTION__);
    }
    return eHMILoggingType;
}

void CDriveNextResourceImpl::getServiceAttributeValues()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    if (getProxyAvailabilityStatus())
    {
        ////Get Version Info Attribute value
        CommonAPI::CallStatus eStatus = CommonAPI::CallStatus::UNKNOWN;
        driveProTypeCollection::sDpVersionInfo objVersionInfo;
        m_objDriveNextProxy->getS_DpVersionInfoAttribute().getValue(eStatus, objVersionInfo);
        if (CommonAPI::CallStatus::SUCCESS == eStatus)
        {
            onVersionInfoAttributeCb(objVersionInfo);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s get VersionInfoAttribute failed eStatus %d", __FUNCTION__, static_cast<int>(eStatus));
        }

        ////Get all remaining attribute values here
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Proxy not available", __FUNCTION__);
    }
}
