/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDriveNextAdaptor.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDriveNextAdaptor, an Adaptor for DriveNext module,
 * CDriveNextAdaptor is class used to communicate with qml, resources of DriveNext module.
 */

#include "ResourceFactory.hpp"
#include "HMIIncludes.h"

#include "CDriveNextApplication.h"
#include "CDriveNextAdaptor.h"
#include "CDriveNextSM.h"
#include "CDriveNextEventHandler.h"
#include "CDriveNextEnum.h"
#include "CDDriveNextDataElement.h"
#include "CSetupAdaptor.h"
#include "CDDriveNextSignalInformation.h"

#include "implementations/CDriveNextResourceImpl.h"
#include "implementations/CDriveNextModerator.h"

///////////////////////////////////////////////////////////////////////////////
// Adaptor related functions
///////////////////////////////////////////////////////////////////////////////
CDriveNextAdaptor::CDriveNextAdaptor(QObject *parent) :
    QObject(parent),
    m_bDriveNextPresence(false),
    m_bDriveNextResetPresence(false),
    m_dScoreScalingFactor(0),
    m_dScoreProxyScale(0),
    m_bUpdatingLibgFile(false),
    m_bUpdatingConfigFile(false),
    m_bExportingLogs(false),
    m_strLibVersion(""),
    m_strConfigVersion(""),
    m_eDpLoggingLevel(CDriveNextEnum::EDNLogLevel::DRIVENEXT_LOG_LEVEL_UNKNOWN),
    m_eDpLoggingType(CDriveNextEnum::EDNLoggingType::DRIVENEXT_LOG_TYPE_UNKNOWN),
    m_eDpLoggingTrip(CDriveNextEnum::EDNTripType::DRIVENEXT_TRIP_UNKNOWN),
    m_bUpdatingDpLoggingLevel(false),
    m_bUpdatingDpLoggingType(false),
    m_bUpdatingDpLoggingTrip(false),
    m_bResetTripStatus(false),
    m_iCurrentTripIndex(0),
    m_iCurrentPerformanceIndex(0),
    m_pDriveNextResource(dynamic_cast<CDriveNextResourceImpl*>(ResourceFactory::getDriveNextResource()))
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    CFramework::getFramework().setContextProperty("cppDriveNextAdaptor",this);
    CDriveNextEnum::registerDriveNextEnumsToQML();
    CDDriveNextDataElement::resetUnitScaleMap();
    m_pDriveNextTripsModel = new CDriveNextTripsModel(this);

    CDDriveNextSignalInformation::initSignalsData();

    if (CDriveNextModerator::validateDNProxyEnumValue() && validateDriveNextSignalTypes())
    {
        initDriveNextSignalsData();
        initDriveNextData();
    }
    else
    {
        LOG_ERROR(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Proxy signal types not matching with HMI signals", __FUNCTION__);
    }
    initDriveNextTripsData();

    setDriveNextPresence(m_pDriveNextResource->getProxyAvailabilityStatus());

    connect(&CPowerModeAdaptor::getInstance(), SIGNAL(sigPowerModeChanged()), this, SLOT(sltPowerModeChanged()), Qt::QueuedConnection);
}
//____________________________________________________________________________
CDriveNextAdaptor::~CDriveNextAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);

    resetDriveNextSignalsData();
    resetDriveNextData();
    resetDriveNextTripsData();

    if(m_pDriveNextTripsModel)
    {
        delete m_pDriveNextTripsModel;
        m_pDriveNextTripsModel = nullptr;
    }

    CDDriveNextSignalInformation::resetSignalsData();

    disconnect(&CPowerModeAdaptor::getInstance(), SIGNAL(sigPowerModeChanged()), this, SLOT(sltPowerModeChanged()));
}
//____________________________________________________________________________
void CDriveNextAdaptor::initDriveNextProperties()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    if(m_pDriveNextResource)
    {
        setDriveNextPresence(m_pDriveNextResource->getProxyAvailabilityStatus());
        updateDriveNextResetPresenceChanged();
        setLibVersion(QString::fromStdString(m_pDriveNextResource->getDNLibVersion()));
        setConfigVersion(QString::fromStdString(m_pDriveNextResource->getDNConfigVersion()));

        setLogTripType(static_cast<CDriveNextEnum::EDNTripType>(m_pDriveNextResource->getTripLogging()));
        setLogLevel(static_cast<CDriveNextEnum::EDNLogLevel>(m_pDriveNextResource->getDpLogLevel()));
        setLoggingLocation(static_cast<CDriveNextEnum::EDNLoggingType>(m_pDriveNextResource->getDpLoggingType()));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
    }
}
//____________________________________________________________________________
bool CDriveNextAdaptor::validateDriveNextSignalTypes()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    bool bStatus = true;
    for (int i = static_cast<int>(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_FUELECOINSTRATING); i < static_cast<int>(EDriveNextSignalTypes::DRIVENEXT_SIG_TOTAL_COUNT); i++)
    {
        if (CDDriveNextSignalInformation::getSignalData(i).m_eSignalType != static_cast<EDriveNextSignalTypes>(i))
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: Incorrect SIGNALS DATA INFO for EDriveNextSignalTypes value:%d", __FUNCTION__, i);
            bStatus = false;
        }
    }
    return bStatus;
}
//____________________________________________________________________________
void CDriveNextAdaptor::initDriveNextTripsData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    resetDriveNextTripsData();
    // initialize trips in list
    ////FixMe need to update data as per service trip data values
    m_lTripsData.append(new CDriveNextTripData(CDriveNextEnum::EDNTripType::DRIVENEXT_CURRENT_TRIP));
    m_lTripsData.append(new CDriveNextTripData(CDriveNextEnum::EDNTripType::DRIVENEXT_TRIP_A));
    m_lTripsData.append(new CDriveNextTripData(CDriveNextEnum::EDNTripType::DRIVENEXT_TRIP_B));
    m_lTripsData.append(new CDriveNextTripData(CDriveNextEnum::EDNTripType::DRIVENEXT_OVERALL_TRIP));
    m_lTripsData.append(new CDriveNextTripData(CDriveNextEnum::EDNTripType::DRIVENEXT_BEST_TRIP));
    m_lTripsData.append(new CDriveNextTripData(CDriveNextEnum::EDNTripType::DRIVENEXT_LAST_TRIP));
}
//____________________________________________________________________________
void CDriveNextAdaptor::resetDriveNextTripsData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    setCurrentTripIndex(0);
    qDeleteAll(m_lTripsData.begin(), m_lTripsData.end());
    m_lTripsData.clear();
}
//____________________________________________________________________________
void CDriveNextAdaptor::initDriveNextSignalsData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);

    resetDriveNextSignalsData();
    for (int i = 0; i < EDriveNextSignalTypes::DRIVENEXT_SIG_TOTAL_COUNT; i++)
    {
        m_lSignalsData.append(new CDDriveNextDataElement());
        ((CDDriveNextDataElement*)m_lSignalsData[i])->setSignalType(static_cast<EDriveNextSignalTypes>(i));
        ((CDDriveNextDataElement*)m_lSignalsData[i])->setDnTitle(CDDriveNextSignalInformation::getSignalData(i).m_DNInfo.m_strTitle);
        ((CDDriveNextDataElement*)m_lSignalsData[i])->setEnggTitle(CDDriveNextSignalInformation::getSignalData(i).m_EnggInfo.m_strTitle);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::resetDriveNextSignalsData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    qDeleteAll(m_lSignalsData.begin(), m_lSignalsData.end());
    m_lSignalsData.clear();
}
//____________________________________________________________________________
void CDriveNextAdaptor::initDriveNextData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    resetDriveNextData();
}
//____________________________________________________________________________
void CDriveNextAdaptor::resetDriveNextData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);

    m_vectDNMainScreenGeneralSignals.clear();
    m_vectDNMainScreenCurrentTripSignals.clear();
    m_vectDNMainScreenTripASignals.clear();
    m_vectDNMainScreenTripBSignals.clear();
    m_vectDNMainScreenOverallTripSignals.clear();
    m_vectDNMainScreenBestTripSignals.clear();
    m_vectDNMainScreenLastTripSignals.clear();

    m_vectEnggDataEfficiencySignals.clear();
    m_vectEnggDataBrakingSignals.clear();
    m_vectEnggDataAccelerationSignals.clear();
    m_vectEnggDataGearShiftSignals.clear();
    m_vectEnggDataGenericSignals.clear();
    m_vectEnggDataSafetySignals.clear();
}
//____________________________________________________________________________
void CDriveNextAdaptor::initVectDNMainScreenGeneralSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    m_vectDNMainScreenGeneralSignals.clear();

    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_OVERALLCUMURATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_FUELECOCUMRATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DRIVECUMURATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SAFETYCUMRATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGFUELECO);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TRIPDIST);

    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_OVERALLCUMURATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_FUELECOCUMRATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DRIVECUMURATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SAFETYCUMRATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGFUELECO);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TRIPDIST);

    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_OVERALLCUMURATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_FUELECOCUMRATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DRIVECUMURATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SAFETYCUMRATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGFUELECO);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TRIPDIST);

    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_OVERALLCUMURATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_FUELECOCUMRATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DRIVECUMURATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SAFETYCUMRATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGFUELECO);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TRIPDIST);

    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_OVERALLCUMURATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_FUELECOCUMRATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DRIVECUMURATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SAFETYCUMRATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGFUELECO);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TRIPDIST);

    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_OVERALLCUMURATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_FUELECOCUMRATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DRIVECUMURATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SAFETYCUMRATING);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGFUELECO);
    m_vectDNMainScreenGeneralSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TRIPDIST);
}
//____________________________________________________________________________
void CDriveNextAdaptor::initVectDNMainScreenCurrentTripSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    m_vectDNMainScreenCurrentTripSignals.clear();

    m_vectDNMainScreenCurrentTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TRIPDURATION);
    m_vectDNMainScreenCurrentTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_IDLETIME);
    m_vectDNMainScreenCurrentTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGSPEED);

    m_vectDNMainScreenCurrentTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOPSPEED);
    m_vectDNMainScreenCurrentTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMECORRECTGEARPER);
    m_vectDNMainScreenCurrentTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESNOPER);
    m_vectDNMainScreenCurrentTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_MOSTTIMEGEAR);

    m_vectDNMainScreenCurrentTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_PERTIMEWITHSEATBELT);
    m_vectDNMainScreenCurrentTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEHIGHSPEEDPER);
    m_vectDNMainScreenCurrentTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCHARSHCOUNT);
    m_vectDNMainScreenCurrentTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_HARSHBRK);
}
//____________________________________________________________________________
void CDriveNextAdaptor::initVectDNMainScreenTripASignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    m_vectDNMainScreenTripASignals.clear();

    m_vectDNMainScreenTripASignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TRIPDURATION);
    m_vectDNMainScreenTripASignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_IDLETIME);
    m_vectDNMainScreenTripASignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGSPEED);

    m_vectDNMainScreenTripASignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOPSPEED);
    m_vectDNMainScreenTripASignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIMECORRECTGEARPER);
    m_vectDNMainScreenTripASignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCPEDALPRESNOPER);
    m_vectDNMainScreenTripASignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_MOSTTIMEGEAR);

    m_vectDNMainScreenTripASignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_PERTIMEWITHSEATBELT);
    m_vectDNMainScreenTripASignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIMEHIGHSPEEDPER);
    m_vectDNMainScreenTripASignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCHARSHCOUNT);
    m_vectDNMainScreenTripASignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_HARSHBRK);
}
//____________________________________________________________________________
void CDriveNextAdaptor::initVectDNMainScreenTripBSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    m_vectDNMainScreenTripBSignals.clear();
    m_vectDNMainScreenTripBSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TRIPDURATION);
    m_vectDNMainScreenTripBSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_IDLETIME);
    m_vectDNMainScreenTripBSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGSPEED);

    m_vectDNMainScreenTripBSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOPSPEED);
    m_vectDNMainScreenTripBSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIMECORRECTGEARPER);
    m_vectDNMainScreenTripBSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCPEDALPRESNOPER);
    m_vectDNMainScreenTripBSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_MOSTTIMEGEAR);

    m_vectDNMainScreenTripBSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_PERTIMEWITHSEATBELT);
    m_vectDNMainScreenTripBSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIMEHIGHSPEEDPER);
    m_vectDNMainScreenTripBSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCHARSHCOUNT);
    m_vectDNMainScreenTripBSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_HARSHBRK);
}
//____________________________________________________________________________
void CDriveNextAdaptor::initVectDNMainScreenOverallTripSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    m_vectDNMainScreenOverallTripSignals.clear();
    m_vectDNMainScreenOverallTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TRIPDURATION);
    m_vectDNMainScreenOverallTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_IDLETIME);
    m_vectDNMainScreenOverallTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGSPEED);

    m_vectDNMainScreenOverallTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOPSPEED);
    m_vectDNMainScreenOverallTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIMECORRECTGEARPER);
    m_vectDNMainScreenOverallTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCPEDALPRESNOPER);
    m_vectDNMainScreenOverallTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_MOSTTIMEGEAR);

    m_vectDNMainScreenOverallTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_PERTIMEWITHSEATBELT);
    m_vectDNMainScreenOverallTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIMEHIGHSPEEDPER);
    m_vectDNMainScreenOverallTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCHARSHCOUNT);
    m_vectDNMainScreenOverallTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_HARSHBRK);
}
//____________________________________________________________________________
void CDriveNextAdaptor::initVectDNMainScreenBestTripSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    m_vectDNMainScreenBestTripSignals.clear();
    m_vectDNMainScreenBestTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TRIPDURATION);
    m_vectDNMainScreenBestTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_IDLETIME);
    m_vectDNMainScreenBestTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGSPEED);

    m_vectDNMainScreenBestTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOPSPEED);
    m_vectDNMainScreenBestTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIMECORRECTGEARPER);
    m_vectDNMainScreenBestTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCPEDALPRESNOPER);
    m_vectDNMainScreenBestTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_MOSTTIMEGEAR);

    m_vectDNMainScreenBestTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_PERTIMEWITHSEATBELT);
    m_vectDNMainScreenBestTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIMEHIGHSPEEDPER);
    m_vectDNMainScreenBestTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCHARSHCOUNT);
    m_vectDNMainScreenBestTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_HARSHBRK);
}
//____________________________________________________________________________
void CDriveNextAdaptor::initVectDNMainScreenLastTripSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    m_vectDNMainScreenLastTripSignals.clear();
    m_vectDNMainScreenLastTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TRIPDURATION);
    m_vectDNMainScreenLastTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_IDLETIME);
    m_vectDNMainScreenLastTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGSPEED);

    m_vectDNMainScreenLastTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOPSPEED);
    m_vectDNMainScreenLastTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIMECORRECTGEARPER);
    m_vectDNMainScreenLastTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCPEDALPRESNOPER);
    m_vectDNMainScreenLastTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_MOSTTIMEGEAR);

    m_vectDNMainScreenLastTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_PERTIMEWITHSEATBELT);
    m_vectDNMainScreenLastTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIMEHIGHSPEEDPER);
    m_vectDNMainScreenLastTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCHARSHCOUNT);
    m_vectDNMainScreenLastTripSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_HARSHBRK);
}
//____________________________________________________________________________
void CDriveNextAdaptor::initVectEnggDataEfficiencySignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    m_vectEnggDataEfficiencySignals.clear();
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_FUELECOINSTRATING);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_FUELECOCUMRATING);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIME_ENGINEIDLE);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_IDLETIME);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_IDLETIMEPER);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALFUELIDLE);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIME_RPMEFFINFO);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDIST);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMEAMBER);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMEAMBERPER);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMEGREEN);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMEGREENPER);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMERED);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMEREDPER);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTAMBER);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTAMBERPER);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTGREEN);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTGREENPER);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTRED);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTREDPER);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGENG_RPM);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIME_ACON);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AC_ONTIME);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AC_ONTIMEPER);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIME_CLT_ACC);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_CLT_ACCTIME);
    m_vectEnggDataEfficiencySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_CLT_ACCTIMEPER);
}
//____________________________________________________________________________
void CDriveNextAdaptor::initVectEnggDataBrakingSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    m_vectEnggDataBrakingSignals.clear();
    m_vectEnggDataBrakingSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_BRKINSTRATING);
    m_vectEnggDataBrakingSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCLN);
    m_vectEnggDataBrakingSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NOOFBRKCYCLE);
    m_vectEnggDataBrakingSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_BRKCUMRATING);
    m_vectEnggDataBrakingSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALBRK);
    m_vectEnggDataBrakingSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NORMALBRK);
    m_vectEnggDataBrakingSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NORMALBRKPER);
    m_vectEnggDataBrakingSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_MODERATEBRK);
    m_vectEnggDataBrakingSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_MODERATEBRKPER);
    m_vectEnggDataBrakingSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_HEAVYBRK);
    m_vectEnggDataBrakingSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_HEAVYBRKPER);
    m_vectEnggDataBrakingSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_PANICBRK);
    m_vectEnggDataBrakingSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_PANICBRKPER);
    m_vectEnggDataBrakingSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_HARSHBRK);
    m_vectEnggDataBrakingSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_HARSHBRKPER);
    m_vectEnggDataBrakingSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGBRKCOUNT);
    m_vectEnggDataBrakingSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ODODISTPERTRIP_BRAKING);
}
//____________________________________________________________________________
void CDriveNextAdaptor::initVectEnggDataAccelerationSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    m_vectEnggDataAccelerationSignals.clear();
    m_vectEnggDataAccelerationSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCINSTRATING);
    m_vectEnggDataAccelerationSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCCUMRATING);
    m_vectEnggDataAccelerationSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTRAVELTIME);
    m_vectEnggDataAccelerationSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALACCPEDALPRESSTIME);
    m_vectEnggDataAccelerationSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE1);
    m_vectEnggDataAccelerationSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE1PER);
    m_vectEnggDataAccelerationSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE2);
    m_vectEnggDataAccelerationSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE2PER);
    m_vectEnggDataAccelerationSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE3);
    m_vectEnggDataAccelerationSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE3PER);
    m_vectEnggDataAccelerationSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE4);
    m_vectEnggDataAccelerationSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE4PER);
    m_vectEnggDataAccelerationSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSNO);
    m_vectEnggDataAccelerationSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESNOPER);
    m_vectEnggDataAccelerationSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGACCPEDALPOS);
    m_vectEnggDataAccelerationSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCHARSHCOUNT);
}
//____________________________________________________________________________
void CDriveNextAdaptor::initVectEnggDataGearShiftSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    m_vectEnggDataGearShiftSignals.clear();
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_VEHICLE_TXMNVARIANT);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_GSINSTRATING);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_GSCUMRATING);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTVALIDGEAR_GEARSHIFT);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEVALIDGEAR_GEARSHIFT);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR1);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR1);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR1PER);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR1PER);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR2);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR2);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR2PER);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR2PER);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR3);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR3);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR3PER);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR3PER);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR4);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR4);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR4PER);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR4PER);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR5);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR5);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR5PER);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR5PER);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR6);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR6);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR6PER);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR6PER);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_MOSTTIMEGEAR);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTVALIDGEAR);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTWRONGGEAR);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTDOWNINDI);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTUPINDI);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGDISTWRONGINDI);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGDISTDOWNINDI);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGDISTUPINDI);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTWRONGGEARPER);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTDOWNINDIPER);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTUPINDIPER);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEVALIDGEAR);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEWRONGGEAR);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEDOWNINDI);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEUPINDI);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEWRONGGEARPER);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEDOWNINDIPER);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEUPINDIPER);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALCOUNTWRONGGEAR);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALCOUNTDOWNINDI);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALCOUNTUPINDI);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALCOUNTDOWNINDIPER);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALCOUNTUPINDIPER);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGCOUNTUPINDI);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGCOUNTDOWNINDI);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMECORRECTGEARPER);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGGEARSHIFT);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NOOFGEARSHIFT);
    m_vectEnggDataGearShiftSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ODODISTPERTRIP);
}
//____________________________________________________________________________
void CDriveNextAdaptor::initVectEnggDataGenericSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    m_vectEnggDataGenericSignals.clear();
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOPSPEED);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DRIVEINSTRATING);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DRIVECUMURATING);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND1TIME);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND1TIMEPER);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND2TIME);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND2TIMEPER);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND3TIME);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND3TIMEPER);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND4TIME);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND4TIMEPER);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TRIPDIST);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TRIPDIST);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TRIPDIST);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TRIPDIST);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TRIPDURATION);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TRIPDURATION);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TRIPDURATION);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TRIPDURATION);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGSPEED);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGSPEED);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGSPEED);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGSPEED);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGFUELECO);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGFUELECO);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGFUELECO);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGFUELECO);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_OVERALLINSTRATING);
    m_vectEnggDataGenericSignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_OVERALLCUMURATING);
}
//____________________________________________________________________________
void CDriveNextAdaptor::initVectEnggDataSafetySignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    m_vectEnggDataSafetySignals.clear();
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_PERTIMEWITHOUTSEATBELT);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_PERTIMEWITHSEATBELT);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SEATBELTFACTOR);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NOOFTIMEWITHOUTSEATBELT);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NOOFTIMEWITHSEATBELT);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NOOFTIMEWITHOUTSEATBELTPER);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DOORCLOSETIMEPER);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DOOROPENTIMEPER);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEHIGHSPEEDCLTBRKPRESSEDPER);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEHIGHSPEEDPER);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SRSFACTOR);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TEABREAKFACTOR);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TRLFACTOR);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TLLFACTOR);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TBLFACTOR);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TFLFACTOR);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TPLFACTOR);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TRVLFACTOR);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_BRKFLDFACTOR);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_OILPRFACTOR);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_WIFFACTOR);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_VEHICLEHEALTH);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SAFETYINSTRATING);
    m_vectEnggDataSafetySignals.push_back(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SAFETYCUMRATING);
}
//____________________________________________________________________________
bool CDriveNextAdaptor::driveNextPresence()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_bDriveNextPresence %d", __FUNCTION__, m_bDriveNextPresence);
    return m_bDriveNextPresence;
}
//____________________________________________________________________________
bool CDriveNextAdaptor::driveNextResetPresence()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_bDriveNextResetPresence %d", __FUNCTION__, m_bDriveNextResetPresence);
    return m_bDriveNextResetPresence;
}
//____________________________________________________________________________
double CDriveNextAdaptor::scoreProxyScale()
{
    return m_dScoreProxyScale;
}
//____________________________________________________________________________
bool CDriveNextAdaptor::updatingLibFile()
{
    return m_bUpdatingLibgFile;
}
//____________________________________________________________________________
bool CDriveNextAdaptor::updatingConfigFile()
{
    return m_bUpdatingConfigFile;
}
//____________________________________________________________________________
bool CDriveNextAdaptor::exportingLogs()
{
    return m_bExportingLogs;
}
//____________________________________________________________________________
QString CDriveNextAdaptor::libVersion()
{
    return m_strLibVersion;
}
//____________________________________________________________________________
QString CDriveNextAdaptor::configVersion()
{
    return m_strConfigVersion;
}
//____________________________________________________________________________
CDriveNextEnum::EDNTripType CDriveNextAdaptor::logTripType()
{
    return m_eDpLoggingTrip;
}
//____________________________________________________________________________
bool CDriveNextAdaptor::updatingLogTripType()
{
    return m_bUpdatingDpLoggingTrip;
}
//____________________________________________________________________________
CDriveNextEnum::EDNLogLevel CDriveNextAdaptor::logLevel()
{
    return m_eDpLoggingLevel;
}
//____________________________________________________________________________
bool CDriveNextAdaptor::updatingLogLevel()
{
    return m_bUpdatingDpLoggingLevel;
}
//____________________________________________________________________________
CDriveNextEnum::EDNLoggingType CDriveNextAdaptor::loggingLocation()
{
    return m_eDpLoggingType;
}
//____________________________________________________________________________
bool CDriveNextAdaptor::updatingLoggingLocation()
{
    return m_bUpdatingDpLoggingType;
}
//____________________________________________________________________________
bool CDriveNextAdaptor::resetTripStatus()
{
    return m_bResetTripStatus;
}
//____________________________________________________________________________
int CDriveNextAdaptor::currentTripIndex()
{
    return m_iCurrentTripIndex;
}
//____________________________________________________________________________
CDriveNextEnum::EDNTripType CDriveNextAdaptor::currentTripType()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s currentTripIndex %d", __FUNCTION__, currentTripIndex());
    return m_pDriveNextTripsModel->getElementAt(currentTripIndex()).m_eTripType;
}
//____________________________________________________________________________
int CDriveNextAdaptor::currentPerformanceIndex()
{
    return m_iCurrentPerformanceIndex;
}
//____________________________________________________________________________
QList<QObject*> CDriveNextAdaptor::tripsData()
{
    return m_lTripsData;
}
//____________________________________________________________________________
QList<QObject *> CDriveNextAdaptor::signalsData()
{
    return m_lSignalsData;
}
//____________________________________________________________________________
const std::vector<EDriveNextSignalTypes>& CDriveNextAdaptor::dnMainScreenGeneralSignalsList()
{
    if (m_vectDNMainScreenGeneralSignals.size() == 0)
    {
        initVectDNMainScreenGeneralSignals();
    }
    return m_vectDNMainScreenGeneralSignals;
}
//____________________________________________________________________________
const std::vector<EDriveNextSignalTypes>& CDriveNextAdaptor::dnMainScreenCurrentTripSignalsList()
{
    if (m_vectDNMainScreenCurrentTripSignals.size() == 0)
    {
        initVectDNMainScreenCurrentTripSignals();
    }
    return m_vectDNMainScreenCurrentTripSignals;
}
//____________________________________________________________________________
const std::vector<EDriveNextSignalTypes>& CDriveNextAdaptor::dnMainScreenTripASignalsList()
{
    if (m_vectDNMainScreenTripASignals.size() == 0)
    {
        initVectDNMainScreenTripASignals();
    }
    return m_vectDNMainScreenTripASignals;
}
//____________________________________________________________________________
const std::vector<EDriveNextSignalTypes>& CDriveNextAdaptor::dnMainScreenTripBSignalsList()
{
    if (m_vectDNMainScreenTripBSignals.size() == 0)
    {
        initVectDNMainScreenTripBSignals();
    }
    return m_vectDNMainScreenTripBSignals;
}
//____________________________________________________________________________
const std::vector<EDriveNextSignalTypes>& CDriveNextAdaptor::dnMainScreenOverallTripSignalsList()
{
    if (m_vectDNMainScreenOverallTripSignals.size() == 0)
    {
        initVectDNMainScreenOverallTripSignals();
    }
    return m_vectDNMainScreenOverallTripSignals;
}
//____________________________________________________________________________
const std::vector<EDriveNextSignalTypes>& CDriveNextAdaptor::dnMainScreenBestTripSignalsList()
{
    if (m_vectDNMainScreenBestTripSignals.size() == 0)
    {
        initVectDNMainScreenBestTripSignals();
    }
    return m_vectDNMainScreenBestTripSignals;
}
//____________________________________________________________________________
const std::vector<EDriveNextSignalTypes>& CDriveNextAdaptor::dnMainScreenLastTripSignalsList()
{
    if (m_vectDNMainScreenLastTripSignals.size() == 0)
    {
        initVectDNMainScreenLastTripSignals();
    }
    return m_vectDNMainScreenLastTripSignals;
}
//____________________________________________________________________________
const std::vector<EDriveNextSignalTypes>& CDriveNextAdaptor::enggDataEfficiencyList()
{
    if (m_vectEnggDataEfficiencySignals.size() == 0)
    {
        initVectEnggDataEfficiencySignals();
    }
    return m_vectEnggDataEfficiencySignals;
}
//____________________________________________________________________________
const std::vector<EDriveNextSignalTypes>& CDriveNextAdaptor::enggDataBrakingList()
{
    if (m_vectEnggDataBrakingSignals.size() == 0)
    {
        initVectEnggDataBrakingSignals();
    }
    return m_vectEnggDataBrakingSignals;
}
//____________________________________________________________________________
const std::vector<EDriveNextSignalTypes>& CDriveNextAdaptor::enggDataAccelerationList()
{
    if (m_vectEnggDataAccelerationSignals.size() == 0)
    {
        initVectEnggDataAccelerationSignals();
    }
    return m_vectEnggDataAccelerationSignals;
}
//____________________________________________________________________________
const std::vector<EDriveNextSignalTypes>& CDriveNextAdaptor::enggDataGearShiftList()
{
    if (m_vectEnggDataGearShiftSignals.size() == 0)
    {
        initVectEnggDataGearShiftSignals();
    }
    return m_vectEnggDataGearShiftSignals;
}
//____________________________________________________________________________
const std::vector<EDriveNextSignalTypes>& CDriveNextAdaptor::enggDataGenericList()
{
    if (m_vectEnggDataGenericSignals.size() == 0)
    {
        initVectEnggDataGenericSignals();
    }
    return m_vectEnggDataGenericSignals;
}
//____________________________________________________________________________
const std::vector<EDriveNextSignalTypes>& CDriveNextAdaptor::enggDataSafetyList()
{
    if (m_vectEnggDataSafetySignals.size() == 0)
    {
        initVectEnggDataSafetySignals();
    }
    return m_vectEnggDataSafetySignals;
}
//____________________________________________________________________________
QAbstractListModel *CDriveNextAdaptor::driveNextTripsModel()
{
    return m_pDriveNextTripsModel;
}
//____________________________________________________________________________
void CDriveNextAdaptor::setDriveNextPresence(bool bValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, bValue=%d", __FUNCTION__, bValue);
    if(bValue != m_bDriveNextPresence)
    {
        m_bDriveNextPresence = bValue;
        if (m_bDriveNextPresence)
        {
            initDriveNextProperties();
        }
        else
        {
            /**
             * @brief When drive next proxy not available, HMI need to get out to home screen from:
             * 1.DriveNext Trips screen
             * 2.DriveNext Setup Screen
             * 3.DriveNext Engg Screen
             * Using State machine states active status to determine weather HMI is in DriveNext screens or not.
             */
            if ((CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_DriveNext)) ||
                    (CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_Setup_setup_region_DriveNextSetup)) ||
                    (CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_EnggMenu_engg_region_DriveNext)))
            {
                LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, Moving Out from DriveNext screen", __FUNCTION__);
                CHMIMain::getSM()->raise_evHomeActivated();
            }
            else
            {
                //Do Nothing!
            }
        }
        emit sigDriveNextPresenceChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, m_bDriveNextPresence not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::onScalingFactorsChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);

}
//____________________________________________________________________________
void CDriveNextAdaptor::onDistanceUnitChanged()
{
    if(m_pDriveNextResource)
    {
        setDistanceUnitInfo(m_pDriveNextResource->getDistanceUnitInfo());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::onFuelUnitChanged()
{
    if(m_pDriveNextResource)
    {
        setFuelUnitInfo(m_pDriveNextResource->getFuelUnitInfo());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::onScoreMaxRatingUpdated()
{
    if(m_pDriveNextResource)
    {
        SSignalDataStructure info = m_pDriveNextResource->getScoreMaxRatingInfo();
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s value:%lf, error:%d", __FUNCTION__, info.getValue(), static_cast<int>(info.getErrorType()));
        setScoreProxyScale(info.getValue());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::onVersionUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    if(m_pDriveNextResource)
    {
        setLibVersion(QString::fromStdString(m_pDriveNextResource->getDNLibVersion()));
        setConfigVersion(QString::fromStdString(m_pDriveNextResource->getDNConfigVersion()));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::setDriveNextResetPresence(bool bValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, bValue=%d", __FUNCTION__, bValue);
    if(bValue != m_bDriveNextResetPresence)
    {
        m_bDriveNextResetPresence = bValue;

        if (!m_bDriveNextResetPresence)
        {
            CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_DN_RESET_ALL_CONFIRMATION);
            CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_DN_RESET_TRIP_A_CONFIRMATION);
            CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_DN_RESET_TRIP_B_CONFIRMATION);
        }
        else
        {
            //Do Nothing!
        }

        emit sigDriveNextResetPresenceChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, m_bDriveNextResetPresence not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::updateDriveNextResetPresenceChanged()
{
    bool bRPMStatus = m_pDriveNextResource && m_pDriveNextResource->getResetAvailabilityStatus();
    bool bPowerModeStatus = (CPowerModeEnums::eVehiclePowerModes::VPM_ACTIVE == CPowerModeAdaptor::getInstance().getPowerModeStatus());

    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, bRPMStatus:%d, bPowerModeStatus:%d", __FUNCTION__, bRPMStatus, bPowerModeStatus);

    setDriveNextResetPresence(bRPMStatus && bPowerModeStatus);
}
//____________________________________________________________________________
void CDriveNextAdaptor::setScoreScalingFactor(double dValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, dValue=%lf", __FUNCTION__, dValue);
    m_dScoreScalingFactor = dValue;
    CDDriveNextDataElement::updateScaleFactor(CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE, m_dScoreScalingFactor);
}
//____________________________________________________________________________
void CDriveNextAdaptor::setScoreProxyScale(double dValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, dValue=%lf", __FUNCTION__, dValue);
    if ( m_dScoreProxyScale != dValue)
    {
        m_dScoreProxyScale = dValue;
        emit sigScoreProxyScaleChanged();
    }
    else
    {
        //Do Nothing
    }

    if (m_dScoreProxyScale > 0)
    {
        setScoreScalingFactor(getScoreRange()/m_dScoreProxyScale);
    }
    else
    {
        setScoreScalingFactor(0);
    }
}
//____________________________________________________________________________
SDistanceUnitInfo CDriveNextAdaptor::getDistanceUnitInfo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, m_eUnitType:%d, m_dUnitScale:%lf", __FUNCTION__, static_cast<int>(m_objDistanceUnitInfo.m_eUnitType), m_objDistanceUnitInfo.m_dUnitScale);
    return m_objDistanceUnitInfo;
}
//____________________________________________________________________________
SFuelUnitInfo CDriveNextAdaptor::getFuelUnitInfo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, m_eUnitType:%d, m_dUnitScale:%lf", __FUNCTION__, static_cast<int>(m_objFuelUnitInfo.m_eUnitType), m_objFuelUnitInfo.m_dUnitScale);
    return m_objFuelUnitInfo;
}
//____________________________________________________________________________
void CDriveNextAdaptor::setDistanceUnitInfo(SDistanceUnitInfo info)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, m_eUnitType:%d, m_dUnitScale:%lf", __FUNCTION__, static_cast<int>(info.m_eUnitType), info.m_dUnitScale);
    m_objDistanceUnitInfo = info;

    //Fix Me need to handle scale factor for changed units
    double dScalingFactorMtrPerSecSq = 1.0;//m_objDistanceUnitInfo.m_dUnitScale;
    double dScalingFactorKm = 1.0;//m_objDistanceUnitInfo.m_dUnitScale;
    double dScalingFactorKmPerHr = 1.0;//m_objDistanceUnitInfo.m_dUnitScale;

    CDDriveNextDataElement::updateScaleFactor(CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_MTR_PER_SEC_SQR, dScalingFactorMtrPerSecSq);
    CDDriveNextDataElement::updateScaleFactor(CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM, dScalingFactorKm);
    CDDriveNextDataElement::updateScaleFactor(CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM_PER_HR, dScalingFactorKmPerHr);
}
//____________________________________________________________________________
void CDriveNextAdaptor::setFuelUnitInfo(SFuelUnitInfo info)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, m_eUnitType:%d, m_dUnitScale:%lf", __FUNCTION__, static_cast<int>(info.m_eUnitType), info.m_dUnitScale);
    m_objFuelUnitInfo = info;

    //Fix Me need to handle scale factor for changed units
    double dScalingFactorMiliLtr = 1.0;//m_objFuelUnitInfo.m_dUnitScale;;
    double dScalingFactorKmPerLtr = 1.0;//m_objFuelUnitInfo.m_dUnitScale;;

    CDDriveNextDataElement::updateScaleFactor(CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_MILI_LTR, dScalingFactorMiliLtr);
    CDDriveNextDataElement::updateScaleFactor(CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM_PER_LITRE, dScalingFactorKmPerLtr);
    CDDriveNextDataElement::updateScaleFactor(CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM_PER_LTR, dScalingFactorKmPerLtr);
}
//____________________________________________________________________________
void CDriveNextAdaptor::updateSignalValues(QList<int> qlistUpdatedSignalTypes)
{
    //LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s qlistUpdatedSignalTypes.Size %d", __FUNCTION__, qlistUpdatedSignalTypes.size());
    if(m_pDriveNextResource)
    {
        for (int index = 0; index < qlistUpdatedSignalTypes.size(); index++)
        {
            int iSignalType = qlistUpdatedSignalTypes[index];

            EDriveNextSignalTypes eSignalType = static_cast<EDriveNextSignalTypes>(iSignalType);
            SSignalDataStructure signalData = m_pDriveNextResource->getSignalValuesMap().at(eSignalType);

            setValueToSignals(eSignalType, signalData);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::updateLibFileEnded(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bStatus %d", __FUNCTION__, bStatus);
    setUpdatingLibFile(false);
    if (bStatus)
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_DN_FILE_UPDATE_SUCCESS);
    }
    else
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_DN_FILE_UPDATE_FAILED);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::setUpdatingLibFile(bool bValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bValue %d", __FUNCTION__, bValue);
    if (m_bUpdatingLibgFile != bValue)
    {
        m_bUpdatingLibgFile = bValue;
        emit sigUpdatingLibFileChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_bUpdatingLibgFile value not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::updateConfigFileEnded(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bStatus %d", __FUNCTION__, bStatus);
    setUpdatingConfigFile(false);
    if (bStatus)
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_DN_FILE_UPDATE_SUCCESS);
    }
    else
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_DN_FILE_UPDATE_FAILED);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::setUpdatingConfigFile(bool bValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bValue %d", __FUNCTION__, bValue);
    if (m_bUpdatingConfigFile != bValue)
    {
        m_bUpdatingConfigFile = bValue;
        emit sigUpdatingConfigFileChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_bUpdatingConfigFile value not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::exportingLogsEnded(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bStatus %d", __FUNCTION__, bStatus);
    setExportingLogs(false);
}
//____________________________________________________________________________
void CDriveNextAdaptor::setExportingLogs(bool bValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bValue %d", __FUNCTION__, bValue);
    if (m_bExportingLogs != bValue)
    {
        m_bExportingLogs = bValue;
        emit sigExportingLogsChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_bExportingLogs value not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::setLibVersion(QString sLibVersion)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, sLibVersion=%s", __FUNCTION__, sLibVersion.toStdString().data());
    if(sLibVersion != m_strLibVersion)
    {
        m_strLibVersion = sLibVersion;
        emit sigLibVersionChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, m_strLibVersion not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::setConfigVersion(QString strConfigVersion)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, strConfigVersion=%s", __FUNCTION__, strConfigVersion.toStdString().data());
    if(strConfigVersion != m_strConfigVersion)
    {
        m_strConfigVersion = strConfigVersion;
        emit sigConfigVersionChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, m_strConfigVersion not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::setLogTripType(CDriveNextEnum::EDNTripType eValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eValue %d", __FUNCTION__, static_cast<int>(eValue));
    if(eValue != m_eDpLoggingTrip)
    {
        m_eDpLoggingTrip = eValue;
        emit sigLogTripTypeChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, m_eDpLoggingTrip not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::setUpdatingLogTripType(bool bValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bValue %d", __FUNCTION__, bValue);
    if(bValue != m_bUpdatingDpLoggingTrip)
    {
        m_bUpdatingDpLoggingTrip = bValue;
        emit sigUpdatingLogTripTypeChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, m_bUpdatingDpLoggingTrip not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::setLogLevel(CDriveNextEnum::EDNLogLevel eValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eValue %d", __FUNCTION__, static_cast<int>(eValue));
    if(eValue != m_eDpLoggingLevel)
    {
        m_eDpLoggingLevel = eValue;
        emit sigLogLevelChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, m_eDpLoggingLevel not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::setUpdatingLogLevel(bool bValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bValue %d", __FUNCTION__, bValue);
    if(bValue != m_bUpdatingDpLoggingLevel)
    {
        m_bUpdatingDpLoggingLevel = bValue;
        emit sigUpdatingLogLevelChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, m_bUpdatingDpLoggingLevel not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::setLoggingLocation(CDriveNextEnum::EDNLoggingType eValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eValue %d", __FUNCTION__, static_cast<int>(eValue));
    if(eValue != m_eDpLoggingType)
    {
        m_eDpLoggingType = eValue;
        emit sigLoggingLocationChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, m_eDpLoggingType not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::setUpdatingLoggingLocation(bool bValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bValue %d", __FUNCTION__, bValue);
    if(bValue != m_bUpdatingDpLoggingType)
    {
        m_bUpdatingDpLoggingType = bValue;
        emit sigUpdatingLoggingLocationChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, m_bUpdatingDpLoggingType not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::updateLibFile()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    if (!updatingLibFile())
    {
        if(driveNextPresence() && m_pDriveNextResource)
        {
            setUpdatingLibFile(true);
            m_pDriveNextResource->updateLibFileAsync();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, update Config File already in progress", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::updateConfigFile()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    if (!updatingConfigFile())
    {
        if(driveNextPresence() && m_pDriveNextResource)
        {
            setUpdatingConfigFile(true);
            m_pDriveNextResource->updateConfigFileAsync();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, update Config File already in progress", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::exportLogs()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    if (!exportingLogs())
    {
        if(driveNextPresence() && m_pDriveNextResource)
        {
            setExportingLogs(true);
            m_pDriveNextResource->extractDPLogsAsync();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, update Config File already in progress", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::updateLogTripType(CDriveNextEnum::EDNTripType eTripType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eTripType %d", __FUNCTION__, static_cast<int>(eTripType));
    if (!updatingLogTripType())
    {
        if(driveNextPresence() && m_pDriveNextResource)
        {
            setUpdatingLogTripType(true);
            m_pDriveNextResource->setTripLoggingAsync(static_cast<EDriveNextTripType>(eTripType));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, another updating is in progress", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::updateLogLevel(CDriveNextEnum::EDNLogLevel eLogLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eLogLevel %d", __FUNCTION__, static_cast<int>(eLogLevel));
    if (!updatingLogLevel())
    {
        if(driveNextPresence() && m_pDriveNextResource)
        {
            setUpdatingLogLevel(true);
            m_pDriveNextResource->setDpLogLevelAsync(static_cast<EDriveNextLogLevel>(eLogLevel));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, another updating is in progress", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::updateLoggingLocation(CDriveNextEnum::EDNLoggingType eLoggingType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eLoggingType %d", __FUNCTION__, static_cast<int>(eLoggingType));
    if (!updatingLoggingLocation())
    {
        if(driveNextPresence() && m_pDriveNextResource)
        {
            setUpdatingLoggingLocation(true);
            m_pDriveNextResource->setDpLoggingTypeAsync(static_cast<EDriveNextLoggingType>(eLoggingType));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, another updating is in progress", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::tryResetDriveNextTrip(CDriveNextEnum::EDNTripType eType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eType %d", __FUNCTION__, static_cast<int>(eType));
    if (driveNextResetPresence())
    {
        switch(eType)
        {
        case CDriveNextEnum::EDNTripType::DRIVENEXT_TRIP_A:
        {
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_DN_RESET_TRIP_A_CONFIRMATION);
        }
            break;
        case CDriveNextEnum::EDNTripType::DRIVENEXT_TRIP_B:
        {
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_DN_RESET_TRIP_B_CONFIRMATION);
        }
            break;
        case CDriveNextEnum::EDNTripType::DRIVENEXT_ALL_TRIP:
        {
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_DN_RESET_ALL_CONFIRMATION);
        }
            break;
        case CDriveNextEnum::EDNTripType::DRIVENEXT_OVERALL_TRIP:
        case CDriveNextEnum::EDNTripType::DRIVENEXT_CURRENT_TRIP:
        case CDriveNextEnum::EDNTripType::DRIVENEXT_LAST_TRIP:
        case CDriveNextEnum::EDNTripType::DRIVENEXT_BEST_TRIP:
        case CDriveNextEnum::EDNTripType::DRIVENEXT_TRIP_UNKNOWN:
        default:
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: Unhandled eType %d", __FUNCTION__, static_cast<int>(eType));
        }
            break;
        }
    }
    else
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_DN_CAN_NOT_RESET);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::resetDriveNextTrip(CDriveNextEnum::EDNTripType eType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eType %d", __FUNCTION__, static_cast<int>(eType));
    if (!resetTripStatus())
    {
        if(driveNextPresence() && m_pDriveNextResource)
        {
            setResetTripStatus(true);
            m_pDriveNextResource->resetTripAsync(static_cast<EDriveNextTripType>(eType));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, another trip reset is in progress", __FUNCTION__);
    }
}
//____________________________________________________________________________
double CDriveNextAdaptor::getScoreRange()
{
    return CDDriveNextSignalInformation::SCORE_RANGE;
}
//____________________________________________________________________________
void CDriveNextAdaptor::setResetTripStatus(bool bValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bValue %d", __FUNCTION__, bValue);
    if(bValue != m_bResetTripStatus)
    {
        m_bResetTripStatus = bValue;
        emit sigResetTripStatusChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, m_bResetTripStatus not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::resetTripEnded(bool bStatus, CDriveNextEnum::EDNTripType eType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bStatus %d eType %d", __FUNCTION__, bStatus, static_cast<int>(eType));
    if (CDriveNextEnum::EDNTripType::DRIVENEXT_ALL_TRIP == eType)
    {
        CPopupEnum::EPopupID eOnScreenPopupId = CPopupManager::getInstance()->getCurrentDisplayedPopup();
        if ((CPopupEnum::EPopupID::EN_POPUPID_SETUP_FACTORY_RESET_WAITING_STATUS != eOnScreenPopupId) && (CPopupEnum::EPopupID::EN_POPUPID_SETUP_FACTORY_RESET_SUCCESSFUL_STATUS != eOnScreenPopupId))
        {
            if (bStatus)
            {
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_DN_RESET_ALL_SUCCESS);
            }
            else
            {
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_DN_RESET_ALL_FAILED);
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s FACTORY_RESET in process with eOnScreenPopupId:%d, ignoring drivenext popups", __FUNCTION__, static_cast<int>(eOnScreenPopupId));
        }
    }
    else
    {
        if (bStatus)
        {
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_DN_RESET_TRIP_SUCCESS);
        }
        else
        {
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_DN_RESET_TRIP_FAILED);
        }
    }
    setResetTripStatus(false);
}
//____________________________________________________________________________
void CDriveNextAdaptor::setCurrentTripIndex(int iIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s iIndex %d", __FUNCTION__, iIndex);
    if (iIndex != m_iCurrentTripIndex)
    {
        m_iCurrentTripIndex = iIndex;
        emit sigCurrentTripIndexChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, no change in value", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::setCurrentPerformanceIndex(int iIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s iIndex %d", __FUNCTION__, iIndex);
    if (iIndex != m_iCurrentPerformanceIndex)
    {
        m_iCurrentPerformanceIndex = iIndex;
        emit sigCurrentPerformanceIndexChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, no change in value", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::subscribeDNMainScreenGeneralSignals(bool bSubscribe)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bSubscribe:%d", __FUNCTION__, bSubscribe);

    if(driveNextPresence() && m_pDriveNextResource)
    {
        if (bSubscribe)
        {
            m_pDriveNextResource->subscribeSignalsAsync(dnMainScreenGeneralSignalsList());
        }
        else
        {
            m_pDriveNextResource->unSubscribeSignalsAsync(dnMainScreenGeneralSignalsList());
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::subscribeDNMainScreenCurrentTripSignals(bool bSubscribe)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bSubscribe:%d", __FUNCTION__, bSubscribe);

    if(driveNextPresence() && m_pDriveNextResource)
    {
        if (bSubscribe)
        {
            m_pDriveNextResource->subscribeSignalsAsync(dnMainScreenCurrentTripSignalsList());
        }
        else
        {
            m_pDriveNextResource->unSubscribeSignalsAsync(dnMainScreenCurrentTripSignalsList());
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::subscribeDNMainScreenTripASignals(bool bSubscribe)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bSubscribe:%d", __FUNCTION__, bSubscribe);

    if(driveNextPresence() && m_pDriveNextResource)
    {
        if (bSubscribe)
        {
            m_pDriveNextResource->subscribeSignalsAsync(dnMainScreenTripASignalsList());
        }
        else
        {
            m_pDriveNextResource->unSubscribeSignalsAsync(dnMainScreenTripASignalsList());
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::subscribeDNMainScreenTripBSignals(bool bSubscribe)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bSubscribe:%d", __FUNCTION__, bSubscribe);

    if(driveNextPresence() && m_pDriveNextResource)
    {
        if (bSubscribe)
        {
            m_pDriveNextResource->subscribeSignalsAsync(dnMainScreenTripBSignalsList());
        }
        else
        {
            m_pDriveNextResource->unSubscribeSignalsAsync(dnMainScreenTripBSignalsList());
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::subscribeDNMainScreenOverallTripSignals(bool bSubscribe)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bSubscribe:%d", __FUNCTION__, bSubscribe);

    if(driveNextPresence() && m_pDriveNextResource)
    {
        if (bSubscribe)
        {
            m_pDriveNextResource->subscribeSignalsAsync(dnMainScreenOverallTripSignalsList());
        }
        else
        {
            m_pDriveNextResource->unSubscribeSignalsAsync(dnMainScreenOverallTripSignalsList());
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::subscribeDNMainScreenBestTripSignals(bool bSubscribe)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bSubscribe:%d", __FUNCTION__, bSubscribe);

    if(driveNextPresence() && m_pDriveNextResource)
    {
        if (bSubscribe)
        {
            m_pDriveNextResource->subscribeSignalsAsync(dnMainScreenBestTripSignalsList());
        }
        else
        {
            m_pDriveNextResource->unSubscribeSignalsAsync(dnMainScreenBestTripSignalsList());
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::subscribeDNMainScreenLastTripSignals(bool bSubscribe)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bSubscribe:%d", __FUNCTION__, bSubscribe);

    if(driveNextPresence() && m_pDriveNextResource)
    {
        if (bSubscribe)
        {
            m_pDriveNextResource->subscribeSignalsAsync(dnMainScreenLastTripSignalsList());
        }
        else
        {
            m_pDriveNextResource->unSubscribeSignalsAsync(dnMainScreenLastTripSignalsList());
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
    }
}
//____________________________________________________________________________

void CDriveNextAdaptor::subscribeEnggEfficiencyList(bool bSubscribe)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bSubscribe:%d", __FUNCTION__, bSubscribe);

    if(driveNextPresence() && m_pDriveNextResource)
    {
        if (bSubscribe)
        {
            m_pDriveNextResource->subscribeSignalsAsync(enggDataEfficiencyList());
        }
        else
        {
            m_pDriveNextResource->unSubscribeSignalsAsync(enggDataEfficiencyList());
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::subscribeEnggBrakingList(bool bSubscribe)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bSubscribe:%d", __FUNCTION__, bSubscribe);

    if(driveNextPresence() && m_pDriveNextResource)
    {
        if (bSubscribe)
        {
            m_pDriveNextResource->subscribeSignalsAsync(enggDataBrakingList());
        }
        else
        {
            m_pDriveNextResource->unSubscribeSignalsAsync(enggDataBrakingList());
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::subscribeEnggAccelerationList(bool bSubscribe)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bSubscribe:%d", __FUNCTION__, bSubscribe);

    if(driveNextPresence() && m_pDriveNextResource)
    {
        if (bSubscribe)
        {
            m_pDriveNextResource->subscribeSignalsAsync(enggDataAccelerationList());
        }
        else
        {
            m_pDriveNextResource->unSubscribeSignalsAsync(enggDataAccelerationList());
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::subscribeEnggGearShiftList(bool bSubscribe)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bSubscribe:%d", __FUNCTION__, bSubscribe);

    if(driveNextPresence() && m_pDriveNextResource)
    {
        if (bSubscribe)
        {
            m_pDriveNextResource->subscribeSignalsAsync(enggDataGearShiftList());
        }
        else
        {
            m_pDriveNextResource->unSubscribeSignalsAsync(enggDataGearShiftList());
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::subscribeEnggGenericList(bool bSubscribe)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bSubscribe:%d", __FUNCTION__, bSubscribe);

    if(driveNextPresence() && m_pDriveNextResource)
    {
        if (bSubscribe)
        {
            m_pDriveNextResource->subscribeSignalsAsync(enggDataGenericList());
        }
        else
        {
            m_pDriveNextResource->unSubscribeSignalsAsync(enggDataGenericList());
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::subscribeEnggSafetyList(bool bSubscribe)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s bSubscribe:%d", __FUNCTION__, bSubscribe);

    if(driveNextPresence() && m_pDriveNextResource)
    {
        if (bSubscribe)
        {
            m_pDriveNextResource->subscribeSignalsAsync(enggDataSafetyList());
        }
        else
        {
            m_pDriveNextResource->unSubscribeSignalsAsync(enggDataSafetyList());
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s: DriveNext resource object not created", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDriveNextAdaptor::sltPowerModeChanged()
{
    updateDriveNextResetPresenceChanged();
}
//____________________________________________________________________________
void CDriveNextAdaptor::setValueToSignals( EDriveNextSignalTypes eSignalType, SSignalDataStructure signalData)
{
    int iSignalType = static_cast<int>(eSignalType);
    //LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eSignalType:%d signalDataValue:%lf", __FUNCTION__, iSignalType, signalData.getValue());

    if (m_lSignalsData.size() > iSignalType)
    {
        ((CDDriveNextDataElement*)m_lSignalsData[iSignalType])->setSignalData(signalData.getValue(), static_cast<CDriveNextEnum::EDNSignalErrorTypes>(signalData.getErrorType()));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s undefined format for iSignalType:%d", __FUNCTION__, iSignalType);
    }
}
//____________________________________________________________________________
