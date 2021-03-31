/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CParkAssistAdaptor.cpp
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * This class is to handle Park Assist functionality.
 */

#include "CParkAssistAdaptor.h"
#include "ResourceFactory.hpp"
#include "StateMachine_TML_HMI_SM.h"
#include "CHMIMain.h"
#include "CPhoneAdaptor.h"
#include "ParkAssistResource/implementations/CParkAssistResourceImpl.h"
#include "CMediaAdaptor.h"
#include "CVariantControlAdaptor.h"
#include "CVRAdaptor.h"

#if !defined(PLATFORM_WIN32) && !defined(PLATFORM_LINUX_X86)
#include "NanoMsgService/CHMINanoMsgEnums.h"
#endif

float CParkAssistAdaptor::RVC_BUFFER_VALUE = 0.01f;

CParkAssistAdaptor* CParkAssistAdaptor::m_pParkAssistAdaptor = nullptr;

CParkAssistAdaptor::CParkAssistAdaptor(QObject *parent):
    QObject(parent),
    m_pParkAssistResource(ResourceFactory::getParkAssistResource()),
    m_iParkAssistVolume(-1),
    m_iParkAssistDelayTimer(-1),
    m_iParkAssistRearTone(-1),
    m_bReverseGearStatus(false),
    m_eParkAssistVariantType(CParkAssistEnum::PARK_ASSIST_VARIANT_DEFAULT),
    m_strPdcRvcFaultMessage("Check Surroundings For Safety!"),
    m_eRvcOverlayType(CParkAssistEnum::RVC_OVERLAY_DEFAULT),
    m_eRvcOverlayDirection(CParkAssistEnum::RVC_OVERLAY_DEFAULT_DIRECTION),
    m_dRvcOverlayAngle(0),
    m_bParkAssistProxyStatus(false),
    m_bIsPdcRvcActivatedFromHmi(false),
    m_eRvcZone(CParkAssistEnum::RVC_ZONE_DEFAULT),
    m_iPdcLeftSensorState(CParkAssistEnum::PDC_LEFT_ZONE_NO_OBSTACLE),
    m_iPdcMidLeftSensorState(CParkAssistEnum::PDC_MID_LEFT_ZONE_NO_OBSTACLE),
    m_iPdcMidRightSensorState(CParkAssistEnum::PDC_MID_RIGHT_ZONE_NO_OBSTACLE),
    m_iPdcRightSensorState(CParkAssistEnum::PDC_RIGHT_ZONE_NO_OBSTACLE),
    m_strParkAssistHeaderState(PDC_RVC_HEADER_STATE_FAULT_MESSAGE),
    m_bPdcPresence(false),
    m_iRvcOverlayCurrentImgIndex(RVC_OVERLAY_MID_IMAGE_INDEX),
    m_strRvcDistanceVaryImagePath(""),
    m_bIsAlertIconAvailable(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,__FUNCTION__);
    CFramework::getFramework().setContextProperty("cppParkAssistAdaptor", this);
    CParkAssistEnum::registerParkAssistEnumsToQML();

    //Function to set RVC related configuration values based on VIP DID
    setRVCConfigurationValues();
    RVC_ZONE_IMAGE_COUNT = (RVC_RED_IMAGE_COUNT + RVC_YELLOW_IMAGE_COUNT + RVC_GREEN_IMAGE_COUNT);
    RVC_RED_STEP    = (RVC_YELLOW_START - RVC_RED_START) / (float)RVC_RED_IMAGE_COUNT;
    RVC_YELLOW_STEP = (RVC_GREEN_START  - RVC_YELLOW_START) / (float)RVC_YELLOW_IMAGE_COUNT;
    RVC_GREEN_STEP  = (RVC_TOTAL_RANGE  - RVC_GREEN_START) / (float)RVC_GREEN_IMAGE_COUNT;

    // Filling the park assist delay timer indexe's & vaule's map
    m_mapParkAssistDelayTimer.clear();
    m_mapParkAssistDelayTimer.insert(CParkAssistEnum::PARK_ASSIST_DELAY_TIMER_ZERO_INDEX, CParkAssistEnum::PARK_ASSIST_DELAY_TIMER_ZERO_INDEX_VALUE);
    m_mapParkAssistDelayTimer.insert(CParkAssistEnum::PARK_ASSIST_DELAY_TIMER_ONE_INDEX, CParkAssistEnum::PARK_ASSIST_DELAY_TIMER_ONE_INDEX_VALUE);
    m_mapParkAssistDelayTimer.insert(CParkAssistEnum::PARK_ASSIST_DELAY_TIMER_TWO_INDEX, CParkAssistEnum::PARK_ASSIST_DELAY_TIMER_TWO_INDEX_VALUE);

    fillPdcFaultsMap();
    fillRvcFaultsMap();
    fillPdcRvcFaultsMap();
    fillRvcOverlayLeftImagesMap();
    fillRvcOverlayRightImagesMap();
    fillRvcDistanceVaryImagesMap();
    updateOverlayCurrentImagePath();
    if(m_pParkAssistResource)
    {
        setReverseGearStatus(m_pParkAssistResource->getRevGearStatus(), m_pParkAssistResource->getActivationStatus());
        setParkAssistVariant(static_cast<CParkAssistEnum::EParkAssistVariantType>(m_pParkAssistResource->getVariantType()));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: m_pParkAssistResource is NULL", __FUNCTION__);
    }
}

CParkAssistAdaptor::~CParkAssistAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,__FUNCTION__);

    if(m_pParkAssistAdaptor)
    {
        delete m_pParkAssistAdaptor;
        m_pParkAssistAdaptor = nullptr;
    }
    m_mapParkAssistDelayTimer.clear();
}

CParkAssistAdaptor *CParkAssistAdaptor::getInstance()
{
    if(nullptr == m_pParkAssistAdaptor)
    {
        m_pParkAssistAdaptor = new CParkAssistAdaptor();
    }
    return m_pParkAssistAdaptor;
}

void CParkAssistAdaptor::setRVCConfigurationValues()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s", __FUNCTION__);
    CVariantControlEnum::EVIP_DID eVIP_DID = CVariantControlAdaptor::getInstance()->eolVIP_DID();
    if ((CVariantControlEnum::VIP_DID_HU_NEXON_LEVEL_B_VAVE == eVIP_DID)
            || (CVariantControlEnum::VIP_DID_HU_NEXON_EV_HIGH == eVIP_DID)
            || (CVariantControlEnum::VIP_DID_HU_NEXON_MCE == eVIP_DID))
    {
        RVC_OVERLAY_IMAGE_COUNT = 29;
        switch(CVariantControlAdaptor::getInstance()->getESensorCount())
        {
        case CVariantControlEnum::EN_TWO_SENSORS:
        {
            RVC_TOTAL_RANGE = 120;
            RVC_GREEN_START = 80;
            RVC_YELLOW_START = 40;
            RVC_RED_START = 0;
            RVC_RED_IMAGE_COUNT = 9;
            RVC_YELLOW_IMAGE_COUNT = 9;
            RVC_GREEN_IMAGE_COUNT = 6;
        }
            break;

        case CVariantControlEnum::EN_FOUR_SENSORS:
        {
            /** RED ZONE RANGE(0 - 50), YELLOW ZONE RANGE(51 - 100), GREEN ZONE RANGE(101 - 150) */
            RVC_TOTAL_RANGE = 150;
            RVC_GREEN_START = 100;
            RVC_YELLOW_START = 50;
            RVC_RED_START = 0;
            RVC_RED_IMAGE_COUNT = 15;
            RVC_YELLOW_IMAGE_COUNT = 8;
            RVC_GREEN_IMAGE_COUNT = 6;
        }
            break;

        default:
            break;
        }
    }
    else if(CVariantControlEnum::VIP_DID_HU_HIGH_X451 == eVIP_DID)
    {
        // TATA_X451 specific code
        /** RED ZONE RANGE(0 - 40), YELLOW ZONE RANGE(41 - 80), GREEN ZONE RANGE(81 - 125) */
        RVC_TOTAL_RANGE = 125;
        RVC_GREEN_START = 80;
        RVC_YELLOW_START = 40;
        RVC_RED_START = 0;
        RVC_RED_IMAGE_COUNT = 18;
        RVC_YELLOW_IMAGE_COUNT = 6;
        RVC_GREEN_IMAGE_COUNT = 5;
        RVC_OVERLAY_IMAGE_COUNT = 13;
    }
    else if(CVariantControlEnum::VIP_DID_HU_HIGH_X445 == eVIP_DID)
    {
        // TATA_X445 specific code
        /** RED ZONE RANGE(0 - 40), YELLOW ZONE RANGE(41 - 80), GREEN ZONE RANGE(81 - 125) */
        RVC_TOTAL_RANGE = 125;
        RVC_GREEN_START = 80;
        RVC_YELLOW_START = 40;
        RVC_RED_START = 0;
        RVC_RED_IMAGE_COUNT = 18;
        RVC_YELLOW_IMAGE_COUNT = 6;
        RVC_GREEN_IMAGE_COUNT = 5;
        RVC_OVERLAY_IMAGE_COUNT = 13;
    }
    else
    {
        //Default is TATA_X445 specific code
        /** RED ZONE RANGE(0 - 40), YELLOW ZONE RANGE(41 - 80), GREEN ZONE RANGE(81 - 125) */
        RVC_TOTAL_RANGE = 125;
        RVC_GREEN_START = 80;
        RVC_YELLOW_START = 40;
        RVC_RED_START = 0;
        RVC_RED_IMAGE_COUNT = 18;
        RVC_YELLOW_IMAGE_COUNT = 6;
        RVC_GREEN_IMAGE_COUNT = 5;
        RVC_OVERLAY_IMAGE_COUNT = 13;
    }
}

void CParkAssistAdaptor::fillPdcFaultsMap()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, __FUNCTION__);

    m_mapPdcFault.clear();
    m_mapPdcFault.insert(CParkAssistEnum::PDC_FAULT_NO_FAULT, CParkAssistData("Check Surroundings For Safety!", false));
    m_mapPdcFault.insert(CParkAssistEnum::PDC_FAULT_CRITICAL_FAULT, CParkAssistData("Park Assist System Faulty, Please Check.", true));
    m_mapPdcFault.insert(CParkAssistEnum::PDC_FAULT_MINOR_FAULT, CParkAssistData("Park Assist System Faulty, Please Check.", true));
    m_mapPdcFault.insert(CParkAssistEnum::PDC_FAULT_TRAILER_CONNECTED, CParkAssistData("Trailer Connected, Drive Carefully!", true));
    m_mapPdcFault.insert(CParkAssistEnum::PDC_FAULT_VEHICLE_SPEED_TOO_HIGH, CParkAssistData("Vehicle Speed Too High, Drive Slowly!", true));
    m_mapPdcFault.insert(CParkAssistEnum::PDC_FAULT_TOO_MUCH_NOISY_ENVIRONMENT, CParkAssistData("Park Assist Information Not Available!", true));
    m_mapPdcFault.insert(CParkAssistEnum::PDC_FAULT_TAILGATE_OPEN, CParkAssistData("Tail Gate Open, Please Close!", true));
    m_mapPdcFault.insert(CParkAssistEnum::PDC_FAULT_PARK_BRAKE_ENGAGED, CParkAssistData("Park Brake Engaged, Please Release!", true));
}

void CParkAssistAdaptor::fillRvcFaultsMap()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, __FUNCTION__);

    m_mapRvcFault.clear();
    m_mapRvcFault.insert(CParkAssistEnum::RVC_FAULT_NO_FAULT, CParkAssistData("Check Surroundings For Safety!", false));
    m_mapRvcFault.insert(CParkAssistEnum::RVC_FAULT_TAILGATE_OPEN, CParkAssistData("Tail Gate Open, Please Close!", true));
    m_mapRvcFault.insert(CParkAssistEnum::RVC_FAULT_RVC_VIDEO_STG, CParkAssistData("Park Assist System Not Available!", false));
    /** No message only gibberish video in this case */
    m_mapRvcFault.insert(CParkAssistEnum::RVC_FAULT_RVC_VIDEO_SIGNAL_FAULT, CParkAssistData("", false));
}

void CParkAssistAdaptor::fillPdcRvcFaultsMap()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, __FUNCTION__);

    m_mapPdcRvcFault.clear();
    m_mapPdcRvcFault.insert(CParkAssistEnum::PDC_RVC_FAULT_NO_FAULT, CParkAssistData("Check Surroundings For Safety!", false));
    /** gibberish video with distance information from PDC in this case */
    m_mapPdcRvcFault.insert(CParkAssistEnum::PDC_RVC_FAULT_PDC_OK_RVC_VIDEO_FAULT, CParkAssistData("", false));

    m_mapPdcRvcFault.insert(CParkAssistEnum::PDC_RVC_FAULT_PDC_CRITICAL_FAULT_RVC_VIDEO_FAULT, CParkAssistData("Park Assist System Faulty, Please Check.", true));
    m_mapPdcRvcFault.insert(CParkAssistEnum::PDC_RVC_FAULT_PDC_NOISY_ENV_RVC_VIDEO_FAULT, CParkAssistData("Park Assist Information Not Available!", true));
    m_mapPdcRvcFault.insert(CParkAssistEnum::PDC_RVC_FAULT_PDC_TRAILER_CONNECTED_RVC_VIDEO_FAULT, CParkAssistData("Trailer Connected, Drive Carefully!", true));
    m_mapPdcRvcFault.insert(CParkAssistEnum::PDC_RVC_FAULT_PDC_OVERSPEED_RVC_VIDEO_FAULT, CParkAssistData("Vehicle Speed Too High, Drive Slowly!", true));

    m_mapPdcRvcFault.insert(CParkAssistEnum::PDC_RVC_FAULT_PDC_MINOR_FAULT_RVC_VIDEO_FAULT, CParkAssistData("Park Assist System Faulty, Please Check.", true));
    m_mapPdcRvcFault.insert(CParkAssistEnum::PDC_RVC_FAULT_PDC_TAILGATE_OPEN_RVC_VIDEO_FAULT, CParkAssistData("Tail Gate Open, Please Close!", true));
    m_mapPdcRvcFault.insert(CParkAssistEnum::PDC_RVC_FAULT_PDC_PARK_BRAKE_RVC_VIDEO_FAULT, CParkAssistData("Park Brake Engaged, Please Release!", true));

    m_mapPdcRvcFault.insert(CParkAssistEnum::PDC_RVC_FAULT_PDC_CRITICAL_FAULT_RVC_OK, CParkAssistData("Park Assist System Faulty, Please Check.", true));
    m_mapPdcRvcFault.insert(CParkAssistEnum::PDC_RVC_FAULT_PDC_NOISY_ENV_RVC_OK, CParkAssistData("Park Assist Information Not Available!", true));
    m_mapPdcRvcFault.insert(CParkAssistEnum::PDC_RVC_FAULT_PDC_TRAILER_RVC_OK, CParkAssistData("Trailer Connected, Drive Carefully!", true));
    m_mapPdcRvcFault.insert(CParkAssistEnum::PDC_RVC_FAULT_PDC_OVERSPEED_RVC_OK, CParkAssistData("Vehicle Speed Too High, Drive Slowly!", true));

    m_mapPdcRvcFault.insert(CParkAssistEnum::PDC_RVC_FAULT_PDC_TAILGATE_RVC_OK, CParkAssistData("Tail Gate Open, Please Close!", true));
    m_mapPdcRvcFault.insert(CParkAssistEnum::PDC_RVC_FAULT_PDC_PARK_BRAKE_RVC_OK, CParkAssistData("Park Brake Engaged, Please Release!", true));
    //FixMe: This case is not mentioned in popup list document of 3rd April 18, please check and modify the message if needed
    m_mapPdcRvcFault.insert(CParkAssistEnum::PDC_RVC_FAULT_PDC_MINOR_FAULT_RVC_OK, CParkAssistData("Park Assist System Faulty, Please Check.", true));
}

void CParkAssistAdaptor::fillRvcOverlayLeftImagesMap()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s", __FUNCTION__);

    m_mapRvcOverlayLeftImage.clear();
    QString strVariant = "";

    CVariantControlEnum::EVIP_DID eVIP_DID = CVariantControlAdaptor::getInstance()->eolVIP_DID();
    if ((CVariantControlEnum::VIP_DID_HU_NEXON_LEVEL_B_VAVE == eVIP_DID)
            || (CVariantControlEnum::VIP_DID_HU_NEXON_EV_HIGH == eVIP_DID)
            || (CVariantControlEnum::VIP_DID_HU_NEXON_MCE == eVIP_DID))
    {
        // For TATA_X104_High_VAVE Left Overlay Images.
        strVariant = "qrc:/image/ParkAssist/RVC/Overlays/X104_High_VAVE/X104_High_VAVE_RVC_PDC_lines_RCL_v13_18-2-19_";
    }
    else if (CVariantControlEnum::VIP_DID_HU_HIGH_X451 == eVIP_DID)
    {
        // For X451 Left Overlay Images.
        strVariant = "qrc:/image/ParkAssist/RVC/Overlays/X451_High/X4_PDC_lines_LR_v8_5-9-19_";
    }
    else if (CVariantControlEnum::VIP_DID_HU_HIGH_X445 == eVIP_DID)
    {
        // For TATA_X445 Left Overlay Images.
        strVariant = "qrc:/image/ParkAssist/RVC/Overlays/X451_High/X4_PDC_lines_LR_v8_5-9-19_";
    }
    else
    {
        //Default is TATA_X445 Left Overlay Images.
        strVariant = "qrc:/image/ParkAssist/RVC/Overlays/X451_High/X4_PDC_lines_LR_v8_5-9-19_";
    }

    for (int iIndex = 1 ; iIndex <= RVC_OVERLAY_IMAGE_COUNT; iIndex++)
    {
        int iImgImdex = (RVC_OVERLAY_IMAGE_COUNT - iIndex);
        QString strIndex = QString::number(iImgImdex).rightJustified(3, '0');
        QString strImagePath = strVariant + strIndex + ".png";
        m_mapRvcOverlayLeftImage.insert(iIndex, strImagePath);
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s, Index: %d, Path:%s", __FUNCTION__, iIndex, strImagePath.toStdString().c_str());
    }
}

void CParkAssistAdaptor::fillRvcOverlayRightImagesMap()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s", __FUNCTION__);

    m_mapRvcOverlayRightImage.clear();
    QString strVariant = "";

    CVariantControlEnum::EVIP_DID eVIP_DID = CVariantControlAdaptor::getInstance()->eolVIP_DID();
    if ((CVariantControlEnum::VIP_DID_HU_NEXON_LEVEL_B_VAVE == eVIP_DID)
            || (CVariantControlEnum::VIP_DID_HU_NEXON_EV_HIGH == eVIP_DID)
            || (CVariantControlEnum::VIP_DID_HU_NEXON_MCE == eVIP_DID))
    {
        // For TATA_X104_High_VAVE Right Overlay Image Path.
        strVariant = "qrc:/image/ParkAssist/RVC/Overlays/X104_High_VAVE/X104_High_VAVE_RVC_PDC_lines_RCL_v13_18-2-19_";
    }
    else if (CVariantControlEnum::VIP_DID_HU_HIGH_X451 == eVIP_DID)
    {
        // For X451 Left Overlay Images.
        strVariant = "qrc:/image/ParkAssist/RVC/Overlays/X451_High/X4_PDC_lines_LR_v8_5-9-19_";
    }
    else if (CVariantControlEnum::VIP_DID_HU_HIGH_X445 == eVIP_DID)
    {
        // For TATA_X445 Left Overlay Images.
        strVariant = "qrc:/image/ParkAssist/RVC/Overlays/X451_High/X4_PDC_lines_LR_v8_5-9-19_";
    }
    else
    {
        // Default is TATA_X445 Right Overlay Image Path.
        strVariant = "qrc:/image/ParkAssist/RVC/Overlays/X451_High/X4_PDC_lines_LR_v8_5-9-19_";
    }

    for (int iIndex = 1 ; iIndex <= RVC_OVERLAY_IMAGE_COUNT ; iIndex++)
    {
        int iImgImdex = (RVC_OVERLAY_IMAGE_COUNT + iIndex);
        QString strIndex = QString::number(iImgImdex).rightJustified(3, '0');
        QString strImagePath = strVariant + strIndex + ".png";
        m_mapRvcOverlayRightImage.insert(iIndex, strImagePath);
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s, Index: %d, Path:%s", __FUNCTION__, iIndex, strImagePath.toStdString().c_str());
    }
}

void CParkAssistAdaptor::fillRvcDistanceVaryImagesMap()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s", __FUNCTION__);

    m_mapRvcDistanceUImages.clear();
    QString strVariant = "";

    CVariantControlEnum::EVIP_DID eVIP_DID = CVariantControlAdaptor::getInstance()->eolVIP_DID();
    if ((CVariantControlEnum::VIP_DID_HU_NEXON_LEVEL_B_VAVE == eVIP_DID)
            || (CVariantControlEnum::VIP_DID_HU_NEXON_EV_HIGH == eVIP_DID)
            || (CVariantControlEnum::VIP_DID_HU_NEXON_MCE == eVIP_DID))
    {
        switch(CVariantControlAdaptor::getInstance()->getESensorCount())
        {
        case CVariantControlEnum::EN_TWO_SENSORS:
        {
            strVariant = "qrc:/image/ParkAssist/RVC/Zones/X104_VAVE/2_Sensors/Nexon_2Sensor_RVC_Zone_";
        }
            break;

        case CVariantControlEnum::EN_FOUR_SENSORS:
        {
            strVariant = "qrc:/image/ParkAssist/RVC/Zones/X104_VAVE/4_Sensors/X104_High_VAVE_RVC_PDC_CL_GYR_v13_18-2-19_";
        }
            break;

        default:
            //do not do anything
            break;
        }
    }
    else if (CVariantControlEnum::VIP_DID_HU_HIGH_X451 == eVIP_DID)
    {
        // For TATA_X451 Zone Images.
        strVariant = "qrc:/image/ParkAssist/RVC/Zones/X451/X4_PDC_Center_lines_v7_5-9-18_";
    }
    else if (CVariantControlEnum::VIP_DID_HU_HIGH_X445 == eVIP_DID)
	{
        // For TATA_X445 Zone Images.
        strVariant = "qrc:/image/ParkAssist/RVC/Zones/X451/X4_PDC_Center_lines_v7_5-9-18_";
	}
    else
    {
        //Deafult is TATA_X445 Zone Images.
        strVariant = "qrc:/image/ParkAssist/RVC/Zones/X451/X4_PDC_Center_lines_v7_5-9-18_";
    }


    for (int iIndex = 1 ; iIndex <= RVC_ZONE_IMAGE_COUNT ; iIndex++)
    {
        int iImgImdex = (iIndex - 1);
        QString strIndex = QString::number(iImgImdex).rightJustified(3, '0');
        QString strImagePath = strVariant + strIndex + ".png";
        m_mapRvcDistanceUImages.insert(iIndex, strImagePath);
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s, Index: %d, Path:%s", __FUNCTION__, iIndex, strImagePath.toStdString().c_str());
    }
}

/* get, set methods - start */

int CParkAssistAdaptor::parkAssistVolume()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s: park assist volume :%d", __FUNCTION__, m_iParkAssistVolume);

    return m_iParkAssistVolume;
}

void CParkAssistAdaptor::setParkAssistVolume(int iParkAssistVolume)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s set - park assist volume :%d", __FUNCTION__, iParkAssistVolume);

    if(iParkAssistVolume != m_iParkAssistVolume)
    {
        m_iParkAssistVolume = iParkAssistVolume;
        emit sigParkAssistVolumeChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s Values are same", __FUNCTION__);
    }
}

int CParkAssistAdaptor::parkAssistDelayTimer()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s: park assist delay timer :%d", __FUNCTION__, m_iParkAssistDelayTimer);

    /* Passing the value to the map so that we can get key,
        if value is not found in the map it returns PARK_ASSIST_DELAY_TIMER_DEFAULT_INDEX */
    return m_mapParkAssistDelayTimer.key(static_cast<CParkAssistEnum::EParkAssistDelayTimerValues>(m_iParkAssistDelayTimer),
                                         CParkAssistEnum::PARK_ASSIST_DELAY_TIMER_DEFAULT_INDEX);
}

void CParkAssistAdaptor::setParkAssistDelayTimer(int iParkAssistDelayTimer)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s set - park assist delay timer :%d", __FUNCTION__, iParkAssistDelayTimer);

    /** Can sends default value 1 on every cycle instead of 0 */
    if(PARK_ASSIST_DELAY_TIMER_VALUE_ONE == iParkAssistDelayTimer)
    {
        iParkAssistDelayTimer = PARK_ASSIST_DELAY_TIMER_VALUE_ZERO;
    }
    else
    {
        //Do nothing
    }

    m_iParkAssistDelayTimer = iParkAssistDelayTimer;
    emit sigParkAssistDelayTimerChanged();
}

int CParkAssistAdaptor::parkAssistRearTone()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s: park assist tone :%d", __FUNCTION__, m_iParkAssistRearTone);

    return m_iParkAssistRearTone;
}

void CParkAssistAdaptor::setParkAssistRearTone(int iParkAssistRearTone)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s set - park assist rear tone :%d", __FUNCTION__, iParkAssistRearTone);

    if(iParkAssistRearTone != m_iParkAssistRearTone)
    {
        m_iParkAssistRearTone = iParkAssistRearTone;
        emit sigParkAssistRearToneChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s Values are same", __FUNCTION__);
    }
}

bool CParkAssistAdaptor::reverseGearStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: reverse gear status: %d", __FUNCTION__, m_bReverseGearStatus);

    return ResourceFactory::getParkAssistResource()->getRevGearStatus();
}

void CParkAssistAdaptor::setReverseGearStatus(bool bReverseGearStatus, bool bActivationStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Reverse gear status: %d, Activation status from HMI: %d",
             __FUNCTION__, bReverseGearStatus, bActivationStatus);

    m_bReverseGearStatus = bReverseGearStatus;          /** Reverse gear status */
    setStatusPdcRvcActivatedFromHmi(bActivationStatus); /** Activation status from HMI */

    if(true == pdcRvcScreenStatus())
    {
        if(!(CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_PDC_active_pdc_region_UI_PDC)))
        {
            CHMIMain::getSM()->raise_evPdcActivated();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: PDC-RVC screen is already shown", __FUNCTION__);
        }
    }
    else
    {
        CHMIMain::getSM()->raise_evPdcDeactivated();
    }

    emit sigReverseGearStatusChanged();
}

CParkAssistEnum::EParkAssistVariantType CParkAssistAdaptor::parkAssistVariant()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: park assist variant: %d", __FUNCTION__, m_eParkAssistVariantType);

    return m_eParkAssistVariantType;
}

void CParkAssistAdaptor::setParkAssistVariant(CParkAssistEnum::EParkAssistVariantType eParkAssistVariantType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: park assist variant: %d", __FUNCTION__, eParkAssistVariantType);

    if(eParkAssistVariantType != m_eParkAssistVariantType)
    {
        m_eParkAssistVariantType = eParkAssistVariantType;
        emit sigParkAssistVariantChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Park assist variant is same as previous", __FUNCTION__);
    }
}

int CParkAssistAdaptor::pdcScreenLeftSensorState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: PDC left sensor state: %d", __FUNCTION__, m_iPdcLeftSensorState);

    return m_iPdcLeftSensorState;
}

int CParkAssistAdaptor::pdcScreenMidLeftSensorState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: PDC mid left sensor state: %d", __FUNCTION__, m_iPdcMidLeftSensorState);

    return m_iPdcMidLeftSensorState;
}

int CParkAssistAdaptor::pdcScreenMidRightSensorState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: PDC mid right sensor state: %d", __FUNCTION__, m_iPdcMidRightSensorState);

    return m_iPdcMidRightSensorState;
}

int CParkAssistAdaptor::pdcScreenRightSensorState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: PDC right sensor state: %d", __FUNCTION__, m_iPdcRightSensorState);

    return m_iPdcRightSensorState;
}

void CParkAssistAdaptor::setPdcScreenSensorState(int iPdcSensorState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: PDC sensor state from service: %d", __FUNCTION__, iPdcSensorState);

    /** Logic to extract PDC sensor's state */
    m_iPdcMidRightSensorState = (iPdcSensorState & 0XFF);
    m_iPdcRightSensorState = ((iPdcSensorState & 0XFF00) >> 8);
    m_iPdcMidLeftSensorState = ((iPdcSensorState & 0XFF0000) >> 16);
    m_iPdcLeftSensorState = ((iPdcSensorState & 0XFF000000) >> 24);

    if(CVariantControlEnum::EN_TWO_SENSORS == CVariantControlAdaptor::getInstance()->getESensorCount())
    {
        m_iPdcMidRightSensorState = m_iPdcRightSensorState;
        m_iPdcMidLeftSensorState = m_iPdcLeftSensorState;
    }
    else
    {
        //No change required for 4 sensors. 3 sensors is not a valid requirement.
    }

    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: PDC sensor state-HMI: LH: %d, MLH: %d, MRH: %d, RH: %d",
             __FUNCTION__, m_iPdcLeftSensorState, m_iPdcMidLeftSensorState, m_iPdcMidRightSensorState, m_iPdcRightSensorState);

    emit sigPdcSensorStateChanged();
}

int CParkAssistAdaptor::rvcScreenSensorState()
{
    return m_eRvcZone;
}

void CParkAssistAdaptor::setRvcScreenSensorState(int iRvcSensorState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC sensor zone state: %d", __FUNCTION__, iRvcSensorState);
    int iRvcObstacleImageIndex = 0;
    float fZoneIndex = 0.0f;
    float fImageIndex = 0.0f;

    /** The logic used here is, zone is found based on the distance information from obstacle
        In that zone, image index is calculated based on the range of that particular zone and count of images in that particular zone
        Finally iRvcObstacleImageIndex is calculated based on total image count. */

    if (iRvcSensorState > RVC_TOTAL_RANGE)  /** RVC_ZONE_DEFAULT */
    {
        /** Obstacle distance is beyond 150, hide all zones */
        m_eRvcZone = CParkAssistEnum::RVC_ZONE_DEFAULT;
    }
    else if (iRvcSensorState > RVC_GREEN_START) /** RVC_ZONE_GREEN */
    {
        m_eRvcZone = CParkAssistEnum::RVC_ZONE_GREEN;
        fZoneIndex = (iRvcSensorState - RVC_GREEN_START) / RVC_GREEN_STEP;
        fImageIndex = (RVC_GREEN_IMAGE_COUNT + RVC_BUFFER_VALUE) - fZoneIndex;
        iRvcObstacleImageIndex = qCeil(fImageIndex);
    }
    else if (iRvcSensorState > RVC_YELLOW_START)    /** RVC_ZONE_YELLOW */
    {
        m_eRvcZone = CParkAssistEnum::RVC_ZONE_YELLOW;
        fZoneIndex = (iRvcSensorState - RVC_YELLOW_START) / RVC_YELLOW_STEP;
        fImageIndex = (RVC_GREEN_IMAGE_COUNT + RVC_YELLOW_IMAGE_COUNT + RVC_BUFFER_VALUE) - fZoneIndex;
        iRvcObstacleImageIndex = qCeil(fImageIndex);
    }
    else    /** RVC_ZONE_RED */
    {
        m_eRvcZone = CParkAssistEnum::RVC_ZONE_RED;
        fZoneIndex = (iRvcSensorState - RVC_RED_START) / RVC_RED_STEP;
        fImageIndex = (RVC_GREEN_IMAGE_COUNT + RVC_YELLOW_IMAGE_COUNT + RVC_RED_IMAGE_COUNT + RVC_BUFFER_VALUE) - fZoneIndex;
        iRvcObstacleImageIndex = qCeil(fImageIndex);
    }

    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC obstacle image index: %d", __FUNCTION__, iRvcObstacleImageIndex);

    if(CParkAssistEnum::RVC_ZONE_DEFAULT != m_eRvcZone)
    {
        if(m_mapRvcDistanceUImages.contains(iRvcObstacleImageIndex))
        {
            m_strRvcDistanceVaryImagePath = m_mapRvcDistanceUImages[iRvcObstacleImageIndex];
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Map doesn't contains index: %d", __FUNCTION__, iRvcObstacleImageIndex);
            /**
             * If iRvcObstacleImageIndex is greater than max image count then set m_strRvcDistanceVaryImagePath
             * to the last image of RvcDistanceUImages map.
             */
            if(iRvcObstacleImageIndex > RVC_ZONE_IMAGE_COUNT)
            {
                int iMaxObstacleImgIndex = RVC_ZONE_IMAGE_COUNT;
                m_strRvcDistanceVaryImagePath = m_mapRvcDistanceUImages[iMaxObstacleImgIndex];
            }
            else
            {
                //do not do anything
            }
        }

        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: m_strRvcDistanceVaryImagePath is: %s", __FUNCTION__, m_strRvcDistanceVaryImagePath.toStdString().c_str());
    }
    else
    {
        m_strRvcDistanceVaryImagePath = "";
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Obstacle distance is beyond 150, hide all zones: %d", __FUNCTION__, iRvcSensorState);
    }

    emit sigRvcSensorStateChanged();
}

QString CParkAssistAdaptor::rvcDistanceVaryImagePath()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: rvcDistanceVaryImagePath: %s", __FUNCTION__, m_strRvcDistanceVaryImagePath.toStdString().c_str());
    return m_strRvcDistanceVaryImagePath;
}
QString CParkAssistAdaptor::pdcRvcFaultMessage()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Fault message: %s", __FUNCTION__, m_strPdcRvcFaultMessage.toStdString().c_str());

    return m_strPdcRvcFaultMessage;
}

void CParkAssistAdaptor::setPdcFault(CParkAssistEnum::EPdcFaults ePdcFault)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: PDC fault: %d", __FUNCTION__, ePdcFault);

    if (CParkAssistEnum::PARK_ASSIST_VARIANT_PDC == parkAssistVariant())
    {
        if(m_mapPdcFault.contains(ePdcFault))
        {
            m_strPdcRvcFaultMessage = m_mapPdcFault[ePdcFault].pdcRvcFaultMessage();
            m_bIsAlertIconAvailable = m_mapPdcFault[ePdcFault].isAlertIconAvailable();
            emit sigPdcRvcFaultChanged();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST,"%s - m_mapPdcFault doesn't contains: %d", __FUNCTION__, ePdcFault);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s - Fault:%d, not for PARK_ASSIST_VARIANT_PDC", __FUNCTION__, ePdcFault);
    }
}

void CParkAssistAdaptor::setRvcFault(CParkAssistEnum::ERvcFaults eRvcFault)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC fault: %d", __FUNCTION__, eRvcFault);

    if (CParkAssistEnum::PARK_ASSIST_VARIANT_RVC == parkAssistVariant())
    {
        if(m_mapRvcFault.contains(eRvcFault))
        {
            m_strPdcRvcFaultMessage = m_mapRvcFault[eRvcFault].pdcRvcFaultMessage();
            m_bIsAlertIconAvailable = m_mapRvcFault[eRvcFault].isAlertIconAvailable();
            emit sigPdcRvcFaultChanged();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST,"%s - m_mapRvcFault doesn't contains: %d", __FUNCTION__, eRvcFault);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s - Fault:%d, not for PARK_ASSIST_VARIANT_RVC", __FUNCTION__, eRvcFault);
    }
}

void CParkAssistAdaptor::setPdcRvcFault(CParkAssistEnum::EPdcRvcFaults ePdcRvcFault)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: PDC+RVC fault: %d", __FUNCTION__, ePdcRvcFault);

    if (CParkAssistEnum::PARK_ASSIST_VARIANT_PDC_RVC == parkAssistVariant())
    {
        if(m_mapPdcRvcFault.contains(ePdcRvcFault))
        {
            m_strPdcRvcFaultMessage = m_mapPdcRvcFault[ePdcRvcFault].pdcRvcFaultMessage();
            m_bIsAlertIconAvailable = m_mapPdcRvcFault[ePdcRvcFault].isAlertIconAvailable();
            emit sigPdcRvcFaultChanged();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST,"%s - m_mapPdcRvcFault doesn't contains: %d", __FUNCTION__, ePdcRvcFault);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s - Fault:%d, not for PARK_ASSIST_VARIANT_PDC_RVC", __FUNCTION__, ePdcRvcFault);
    }
}

CParkAssistEnum::ERvcOverlays CParkAssistAdaptor::rvcOverlayType()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC overlay type: %d", __FUNCTION__, m_eRvcOverlayType);

    return m_eRvcOverlayType;
}

void CParkAssistAdaptor::setRvcOverlayType(CParkAssistEnum::ERvcOverlays eRvcOverlayType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC overlay type: %d", __FUNCTION__, eRvcOverlayType);

    if(eRvcOverlayType != m_eRvcOverlayType)
    {
        m_eRvcOverlayType = eRvcOverlayType;
        emit sigRvcOverlayTypeChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC overlay is same as previous", __FUNCTION__);
    }
}

CParkAssistEnum::ERvcOverlayDirection CParkAssistAdaptor::rvcOverlayDirection()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC overlay direction: %d", __FUNCTION__, m_eRvcOverlayDirection);

    return m_eRvcOverlayDirection;
}

void CParkAssistAdaptor::setRvcOverlayDirection(CParkAssistEnum::ERvcOverlayDirection eRvcOverlayDirection)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC overlay direction: %d", __FUNCTION__, eRvcOverlayDirection);

    m_eRvcOverlayDirection = eRvcOverlayDirection;
    setRvcOverlayAngle(m_dRvcOverlayAngle);
    emit sigRvcOverlayDirectionChanged();
}

double CParkAssistAdaptor::rvcOverlayAngle()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC overlay angle: %f", __FUNCTION__, m_dRvcOverlayAngle);

    return m_dRvcOverlayAngle;
}

QString CParkAssistAdaptor::rvcOverlayCurrentImagePath()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC overlay image path: %s ", __FUNCTION__, m_strRvcOverlayCurrentImgPath.toStdString().c_str());

    return m_strRvcOverlayCurrentImgPath;
}

void CParkAssistAdaptor::setRvcOverlayAngle(double dRvcOverlayAngle)
{
    m_dRvcOverlayAngle = dRvcOverlayAngle;
    m_iRvcOverlayCurrentImgIndex = calculateCurrentImageIndex(m_dRvcOverlayAngle);

    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC overlay angle: %f, image index: %d, direction: %d",
             __FUNCTION__, dRvcOverlayAngle, m_iRvcOverlayCurrentImgIndex, m_eRvcOverlayDirection);

    if(RVC_OVERLAY_MID_IMAGE_INDEX == m_iRvcOverlayCurrentImgIndex)
    {
        updateOverlayCurrentImagePath();
    }
    else
    {
        if(CParkAssistEnum::RVC_OVERLAY_CLOCKWISE_DIRECTION == m_eRvcOverlayDirection)
        {
            if(m_mapRvcOverlayRightImage.contains(m_iRvcOverlayCurrentImgIndex))
            {
                m_strRvcOverlayCurrentImgPath = m_mapRvcOverlayRightImage[m_iRvcOverlayCurrentImgIndex];
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC right image map doesn't contains index: %d", __FUNCTION__, m_iRvcOverlayCurrentImgIndex);
            }
        }
        else    /** RVC_OVERLAY_COUNTER_CLOCKWISE_DIRECTION */
        {
            if(m_mapRvcOverlayLeftImage.contains(m_iRvcOverlayCurrentImgIndex))
            {
                m_strRvcOverlayCurrentImgPath = m_mapRvcOverlayLeftImage[m_iRvcOverlayCurrentImgIndex];
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC left image map doesn't contains index: %d", __FUNCTION__, m_iRvcOverlayCurrentImgIndex);
            }
        }
    }

    emit sigRvcOverlayAngleChanged();
}

int CParkAssistAdaptor::calculateCurrentImageIndex(double dRvcOverlayAngle)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC overlay angle: %f", __FUNCTION__, dRvcOverlayAngle);
    return (qRound(dRvcOverlayAngle) * RVC_OVERLAY_IMAGE_COUNT) / RVC_OVERLAY_MAX_ANGLE;
}

bool CParkAssistAdaptor::getParkAssistProxyStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Park assist status: %d", __FUNCTION__, m_bParkAssistProxyStatus);

    return m_bParkAssistProxyStatus;
}

void CParkAssistAdaptor::setParkAssistProxyStatus(bool bParkAssistProxyStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Park assist status: %d", __FUNCTION__, bParkAssistProxyStatus);

    if(bParkAssistProxyStatus != m_bParkAssistProxyStatus)
    {
        m_bParkAssistProxyStatus = bParkAssistProxyStatus;
        emit sigParkAssistProxyStatusChanged(bParkAssistProxyStatus);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Park assist proxy status is same as previous", __FUNCTION__);
    }
}

bool CParkAssistAdaptor::isPdcRvcActivatedFromHmi()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: isPdcRvcActivatedFromHmi: %d", __FUNCTION__, m_bIsPdcRvcActivatedFromHmi);

    return m_bIsPdcRvcActivatedFromHmi;
}

void CParkAssistAdaptor::setStatusPdcRvcActivatedFromHmi(bool bStatusActivatedFromHmi)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: isPdcRvcActivatedFromHmi: %d", __FUNCTION__, bStatusActivatedFromHmi);

    if(bStatusActivatedFromHmi != m_bIsPdcRvcActivatedFromHmi)
    {
        m_bIsPdcRvcActivatedFromHmi = bStatusActivatedFromHmi;
        emit sigPdcRvcActivatedFromHmiChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: isPdcRvcActivatedFromHmi status is same as previous", __FUNCTION__);
    }
}

QString CParkAssistAdaptor::parkAssistHeaderState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: park assist header: %s", __FUNCTION__, m_strParkAssistHeaderState.toStdString().c_str());

    return m_strParkAssistHeaderState;
}

void CParkAssistAdaptor::setParkAssistHeaderState(const QString& sHeaderState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: park assist header: %s", __FUNCTION__, sHeaderState.toStdString().c_str());

    if(sHeaderState != m_strParkAssistHeaderState)
    {
        m_strParkAssistHeaderState = sHeaderState;
        emit sigParkAssistHeaderStateChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: m_strParkAssistHeaderState status is same as previous", __FUNCTION__);
    }
}

bool CParkAssistAdaptor::pdcRvcScreenStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: ReverseGearStatus: %d, ActivationStatusFromHMI: %d",
             __FUNCTION__, m_bReverseGearStatus, m_bIsPdcRvcActivatedFromHmi);

    return (m_bReverseGearStatus || m_bIsPdcRvcActivatedFromHmi);
}

bool CParkAssistAdaptor::pdcRvcProxyStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s: park assist poxy status: %d", __FUNCTION__, m_bParkAssistProxyStatus);
    return m_bParkAssistProxyStatus;
}

void CParkAssistAdaptor::setPdcPresence(bool bPdcPresence)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: PDC Presence: %d", __FUNCTION__, bPdcPresence);

    if(bPdcPresence != m_bPdcPresence)
    {
        m_bPdcPresence = bPdcPresence;
        emit sigPdcPresenceChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s:m_bPdcPresence status is same as previous", __FUNCTION__);
    }
}

void CParkAssistAdaptor::setPdcSettingsStatus(bool bPdcSettingsErrorStatus, int iErrorId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Pdc Settings error status : %d, Error Id : %d ", __FUNCTION__, bPdcSettingsErrorStatus, iErrorId);

    if(bPdcSettingsErrorStatus)
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_SETUP_VEHICLE_SETTING_CANNOT_UPDATE_POPUP);
    }
    else
    {
        //Do Nothing
        CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_SETUP_VEHICLE_SETTING_CANNOT_UPDATE_POPUP);
    }
}

bool CParkAssistAdaptor::isAlertIconAvailable()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: m_bIsAlertIconAvailable: %d", __FUNCTION__, m_bIsAlertIconAvailable);

    return m_bIsAlertIconAvailable;
}

void CParkAssistAdaptor::updateOverlayCurrentImagePath()
{
    CVariantControlEnum::EVIP_DID eVIP_DID = CVariantControlAdaptor::getInstance()->eolVIP_DID();
    if ((CVariantControlEnum::VIP_DID_HU_NEXON_LEVEL_B_VAVE == eVIP_DID)
        || (CVariantControlEnum::VIP_DID_HU_NEXON_EV_HIGH == eVIP_DID)
        || (CVariantControlEnum::VIP_DID_HU_NEXON_MCE == eVIP_DID))
    {
        // TATA_X104_High_VAVE specific code
        m_strRvcOverlayCurrentImgPath = "qrc:/image/ParkAssist/RVC/Overlays/X104_High_VAVE/X104_High_VAVE_RVC_PDC_lines_RCL_v13_18-2-19_029_Center.png";
    }
    else if (CVariantControlEnum::VIP_DID_HU_HIGH_X451 == eVIP_DID)
    {
        // TATA_X451 specific code
        m_strRvcOverlayCurrentImgPath = "qrc:/image/ParkAssist/RVC/Overlays/X451_High/X4_PDC_lines_LR_v8_5-9-19_013.png";
    }
    else if (CVariantControlEnum::VIP_DID_HU_HIGH_X445 == eVIP_DID)
    {
        // TATA_X445 specific code
        m_strRvcOverlayCurrentImgPath = "qrc:/image/ParkAssist/RVC/Overlays/X451_High/X4_PDC_lines_LR_v8_5-9-19_013.png";
    }
    else
    {
        // Default is TATA_X445 specific code
        m_strRvcOverlayCurrentImgPath = "qrc:/image/ParkAssist/RVC/Overlays/X451_High/X4_PDC_lines_LR_v8_5-9-19_013.png";
    }

    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: m_strRvcOverlayCurrentImgPath: %s ", __FUNCTION__, m_strRvcOverlayCurrentImgPath.toStdString().c_str());

}

/* get, set methods - end */

/* ParkAssist resource implementor methods - start */

void CParkAssistAdaptor::setHmiNotificationAttribute(bool bHmiUpStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s: park assist hmi status: %d", __FUNCTION__, bHmiUpStatus);

    if(m_pParkAssistResource)
    {
        m_pParkAssistResource->setHmiNotificationAttribute(bHmiUpStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST,"%s, m_pParkAssistResource is NULL", __FUNCTION__);
    }
}

void CParkAssistAdaptor::setParkAssistDelayTimerAttribute(int iParkAssistDelayTimerIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s: park assist delay timer: %d", __FUNCTION__, iParkAssistDelayTimerIndex);

    CParkAssistEnum::EParkAssistDelayTimer eParkAssistDelayTimer = static_cast<CParkAssistEnum::EParkAssistDelayTimer>(iParkAssistDelayTimerIndex);
    if(m_mapParkAssistDelayTimer.contains(eParkAssistDelayTimer))
    {
        if(m_pParkAssistResource)
        {
            m_pParkAssistResource->setParkAssistDelayTimer(m_mapParkAssistDelayTimer[eParkAssistDelayTimer]);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST,"%s, m_pParkAssistResource is NULL", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST,"%s - m_mapParkAssistDelayTimer doesn't contains :%d", __FUNCTION__, iParkAssistDelayTimerIndex);
    }
}

void CParkAssistAdaptor::setParkAssistRearToneAttribute(int iParkAssistToneIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s: park assist tone: %d", __FUNCTION__, iParkAssistToneIndex);

    CParkAssistEnum::EPDcRearTones eParkAssistTone = static_cast<CParkAssistEnum::EPDcRearTones>(iParkAssistToneIndex);

    if(m_pParkAssistResource)
    {
        m_pParkAssistResource->setParkAssistRearTone(eParkAssistTone);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST,"%s, m_pParkAssistResource is NULL", __FUNCTION__);
    }
}

void CParkAssistAdaptor::activatePdcRvc(bool bShowPdcRvcScreen)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: bShowPdcRvcScreen: %d", __FUNCTION__, bShowPdcRvcScreen);

    if(m_pParkAssistResource)
    {
        if(bShowPdcRvcScreen)
        {
            m_pParkAssistResource->setReverseGearStatusAttribute(true);
        }
        else
        {
            m_pParkAssistResource->setReverseGearStatusAttribute(false);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: m_pParkAssistResource is NULL", __FUNCTION__);
    }
}

bool CParkAssistAdaptor::handleHardKeys(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: key is: %d, key state is: %d", __FUNCTION__, eKey, eKeyState);
    bool bReturn = false;

    if(CHardKeyEnum::KEYCODEHK_BACK == eKey)
    {
        activatePdcRvc(false);
        bReturn = true;
    }
    else
    {
        //Do Nothing
    }
    return bReturn;
}

int CParkAssistAdaptor::updateReverseGearInfo(int iRevGearStatus)
{
    int iRetValue = -1;
    CParkAssistResourceImpl *pCParkAssistResourceImpl = dynamic_cast<CParkAssistResourceImpl*>(m_pParkAssistResource);

#if !defined(PLATFORM_WIN32) && !defined(PLATFORM_LINUX_X86)
    if (ENANOMSG_REV_ENGAGE == iRevGearStatus)
    {
        //Hide Native VR Overlay whenever reverse gear gets engaged
        CVRAdaptor::getInstance()->showHideVROverlay(false);

        //Hide BT VR overlay whenever reverse gear gets engaged
        CPhoneAdaptor::getInstance()->showHidePhoneBtVROverlay(false);
    }
#endif

    if(pCParkAssistResourceImpl)
    {
        iRetValue = pCParkAssistResourceImpl->updateReverseGearInfo(iRevGearStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: pCParkAssistResourceImpl is NULL", __FUNCTION__);
    }
    return iRetValue;
}
/* ParkAssist resource implementor methods - end */

void CParkAssistAdaptor::updateRvcState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s", __FUNCTION__);
    /** The delay is introduced to have a smooth transition from fb0 to fb1 */
    QTimer::singleShot(200, this, SLOT(sltNotifyParkAssistDeactivation()));
}

void CParkAssistAdaptor::sltNotifyParkAssistDeactivation()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s", __FUNCTION__);
    //Setting rvcstate to media for showing video surface if video was playing
    CMediaAdaptor::getInstance().updateRvcState(false);
}
