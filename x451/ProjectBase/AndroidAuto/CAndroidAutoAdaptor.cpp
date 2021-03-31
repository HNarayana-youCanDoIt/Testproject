/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CAndroidAutoAdaptor.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* This file is having the definition of all functions of Adaptor class of
* AndroidAuto, This is used by QML files to get the information needs to show
* on view or any other adaptor, who needs any info related to AndroidAuto.
*/

#include "CAndroidAutoAdaptor.h"
#include "ResourceFactory.hpp"
#include "CPopupManager.h"
#include "CAudioAdaptor.h"
#include "AudioResource/interfaces/IAudioResource.h"
#include "ProjectionResource/AndroidAutoResource/implementations/CAndroidAutoResourceImpl.h"
#include "CPhoneAdaptor.h"
#include "CLayerManagerAdaptor.h"
#include "CDisplayManagerAdaptor.h"
#include "CDiagnosticAdaptor.h"
#include "CDiagnosticEnum.h"

CAndroidAutoAdaptor	*CAndroidAutoAdaptor::m_pAndroidAutoAdaptor	= nullptr;

CAndroidAutoAdaptor::CAndroidAutoAdaptor(QObject *pParent) : QObject(pParent),
    m_pAndroidAutoResource(dynamic_cast<CAndroidAutoResourceImpl*> (ResourceFactory::getAndroidAutoResource())),
    m_bAndroidAutoConnectionStatus(false),
    m_bAndroidAutoBondReqStatus(false),
    m_bAndroidAutoProjectionStatus(false),
    m_strAAMediaSongTitle(""),
    m_strAAMediaSongArtist(""),
    m_eAAMediaPlayState(CAndroidAutoEnums::EN_AA_MEDIA_PLAY_STATE_UNKNOWN),
    m_bOKGoogleStatus(false),
    m_bAANaviStatus(false),
    m_bCanSwitchMode(false),
    m_strAADeviceBtAddress(""),
    m_bAATransientStateStatus(false),
    m_strAANaviPopupTitle(""),
    m_strAANaviPopupText(""),
    m_strAANaviPopupImage(""),
    m_strAANaviDistance("")
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    CFramework::getFramework().setContextProperty("cppAndroidAutoAdaptor", this);
    CAndroidAutoEnums::registerAndroidAutoEnumsToQML();
    connectSignals();
}

bool CAndroidAutoAdaptor::handleHardKeys(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: eKey: %d, eKeyState: %d",
             __FUNCTION__, eKey, eKeyState);

    bool bReturn = false;

    if (m_bAndroidAutoConnectionStatus)
    {
        switch(eKey)
        {
        case CHardKeyEnum::KEYCODEHK_SOFTWARE_UPDATE:
        case CHardKeyEnum::KEYCODEHK_ENGGMENU:
        case CHardKeyEnum::KEYCODEHK_HOME:
        {
            requestNative();
            bReturn = true;
        }
            break;
        case CHardKeyEnum::KEYCODEHK_PHONE:
        case CHardKeyEnum::KEYCODEHK_SEEKDOWN:
        case CHardKeyEnum::KEYCODEHK_SEEKUP:
        case CHardKeyEnum::KEYCODESWC_DOWN:
        case CHardKeyEnum::KEYCODESWC_NEXT:
        case CHardKeyEnum::KEYCODESWC_PREV:
        case CHardKeyEnum::KEYCODESWC_UP:
        case CHardKeyEnum::KEYCODEHK_BACK:
        {
            reportKeyEventToResource( eKey, eKeyState );
            bReturn = true;
        }
            break;

        case CHardKeyEnum::KEYCODEHK_FAVORITE:
        {
            // If OK Google is Active then report key to AAPres to deactivate OK Google.
            if (m_bOKGoogleStatus)
            {
                reportKeyEventToResource( CHardKeyEnum::KEYCODESWC_SOURCE, eKeyState );
            }
            else
            {
                requestNative();
                bReturn = true;
            }
        }
            break;
        case CHardKeyEnum::KEYCODESWC_SOURCE:
        {
            // If OK Google is Active then report key to AAPres to deactivate OK Google.
            if (m_bOKGoogleStatus)
            {
                reportKeyEventToResource( CHardKeyEnum::KEYCODESWC_SOURCE, eKeyState );
            }
            else
            {
                //Do nothing.
            }
        }
            break;
        case CHardKeyEnum::KEYCODESWC_ACCEPT_VR:
        {
            if((CDiagnosticAdaptor::getInstance()) && (CDiagnosticAdaptor::getInstance()->micConnectionStatus() != CDiagnosticEnum::CONNECTED))
            {
                //Mic is not connected
                CAudioAdaptor::getInstance()->playBeep(CAudioEnums::BEEP_TYPE_CONFIRM);
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_MIC_NOT_AVAILABLE_POPUP);
            }
            else
            {
                //Mic is connected
            }
            reportKeyEventToResource( eKey, eKeyState );

            if( (!m_bOKGoogleStatus) && (CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState) )
            {
                /* To forward this event to start the Native VR, as per Native VR + Ok Google use case */
                bReturn = false;
            }
            else
            {
                bReturn = true;
            }
        }
            break;
        default:
            LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s Invalid data "
                                                       "received key: %d state:"
                                                       " %d ", __FUNCTION__,
                        eKey, eKeyState);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: "
                                                "m_bAndroidAutoConnectionStatus:"
                                                " %d ", __FUNCTION__,
                 m_bAndroidAutoConnectionStatus);
    }

    return bReturn;
}

void CAndroidAutoAdaptor::updateAAMediaMetaData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if ( m_pAndroidAutoResource )
    {
        const SAAMediaMetaData& objSAAMediaMetaData = m_pAndroidAutoResource->getAAMediaMetaData();
        setAAMediaSongTitle(objSAAMediaMetaData.m_strSongName.c_str());
        setAAMediaSongArtist(objSAAMediaMetaData.m_strArtistName.c_str());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "m_pAndroidAutoResource is NULL.");
    }
}

void CAndroidAutoAdaptor::updateAASessionDetails()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if ( m_pAndroidAutoResource )
    {
        const SAASessionDetails& objSAASessionDetails = m_pAndroidAutoResource->getAASessionDetails();
        m_strAADeviceBtAddress = objSAASessionDetails.m_strBtAddress.c_str();

        setAndroidAutoConnectionStatus((pprestypes::eSessionStatus::SESSION_ACTIVATED == objSAASessionDetails.m_iSessionStatus));

        if(pprestypes::eSessionStatus::SESSION_ERROR == objSAASessionDetails.m_iSessionStatus)
        {
            //ShowProjErrorPopup
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PROJECTION_ERROR);
        }

        /*
         * If Android Auto is connected, m_strAADeviceBtAddress is not empty, device is not already paired
         * and Max device limit reached, then HMI has to show Max device Limit reached popup and request bt
         * service to delete one device.
         */
        if (m_bAndroidAutoConnectionStatus && !m_strAADeviceBtAddress.isEmpty())
        {
            if ( !CPhoneAdaptor::getInstance()->isDeviceAlreadyPaired(m_strAADeviceBtAddress) &&
                 CPhoneAdaptor::getInstance()->isMaxDeviceLimitReached())
            {
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_MAX_DEVICES_PAIRED);
                CPhoneAdaptor::getInstance()->deleteOldestConnectedDevice();
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, :Max Device Limit not reached or device already paired.", __FUNCTION__);
            }
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "m_pAndroidAutoResource is NULL.");
    }
}

void CAndroidAutoAdaptor::updateAANaviTurnEventDetails()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    setAANaviPopupTitle("");
    setAANaviPopupText("");
    setAANaviPopupImage("");
    setAANaviDistance("");

    if ( m_pAndroidAutoResource && m_bAANaviStatus)
    {
        SAANaviNextTurnInfo objAANaviNextTurnInfo = m_pAndroidAutoResource->getAANavigationNextTurnInfo();

        switch(static_cast<CAndroidAutoEnums::EAANaviNextTurnEvent>(objAANaviNextTurnInfo.m_iNextTurnEvent))
        {
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_EVENT_DEPART:
        {
            setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
            setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_Depart_n.png");
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
        }
            break;
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_EVENT_DESTINATION:
        {
            setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
            setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_DestinationReached_n.png");
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
        }
            break;
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_EVENT_ENTER_AND_EXIT:
        {
            switch(static_cast<CAndroidAutoEnums::EAANaviRoundAboutTurnAngle> (objAANaviNextTurnInfo.m_iTurnAngle))
            {
            case CAndroidAutoEnums::EN_AA_ROUND_ABOUT_TURN_ANGLE_45:
            {
                setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
                setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_ArrowRoundabt1_n.png");
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
            }
                break;
            case CAndroidAutoEnums::EN_AA_ROUND_ABOUT_TURN_ANGLE_90:
            {
                setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
                setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_ArrowRoundabt2_n.png");
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
            }
                break;
            case CAndroidAutoEnums::EN_AA_ROUND_ABOUT_TURN_ANGLE_135:
            {
                setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
                setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_ArrowRoundabt3_n.png");
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
            }
                break;
            case CAndroidAutoEnums::EN_AA_ROUND_ABOUT_TURN_ANGLE_180:
            {
                setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
                setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_ArrowRoundabt4_n.png");
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
            }
                break;
            case CAndroidAutoEnums::EN_AA_ROUND_ABOUT_TURN_ANGLE_225:
            {
                setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
                setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_ArrowRoundabt5_n.png");
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
            }
                break;
            case CAndroidAutoEnums::EN_AA_ROUND_ABOUT_TURN_ANGLE_270:
            {
                setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
                setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_ArrowRoundabt6_n.png");
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
            }
                break;
            case CAndroidAutoEnums::EN_AA_ROUND_ABOUT_TURN_ANGLE_315:
            {
                setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
                setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_ArrowRoundabt7_n.png");
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
            }
                break;
            case CAndroidAutoEnums::EN_AA_ROUND_ABOUT_TURN_ANGLE_360:
            {
                setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
                setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_ArrowRoundabt8_n.png");
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
            }
                break;
            default:
            {
                CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
                LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "Navigation Round About number Not handled. Popup Closed.")
                }
                break;
            }
        }
            break;
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_EVENT_FERRY_BOAT:
        {
            setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
            setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_FerryBoat_n.png");
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
        }
            break;
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_EVENT_FERRY_TRAIN:
        {
            // Not Handling this for now.
        }
            break;
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_EVENT_FORK:
        {
            setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
            setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_Fork_n.png");
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
        }
            break;
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_EVENT_MERGE:
        {
            setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
            setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_Merge_n.png");
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
        }
            break;
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_EVENT_NAME_CHANGE:
        {
            // Not handling this for now.
        }
            break;
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_EVENT_ON_TURN:
        {
            if (CAndroidAutoEnums::EN_AA_NEXT_TURN_SIDE_TYPE_LEFT == objAANaviNextTurnInfo.m_iNextTurnSide)
            {
                setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
                setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_HighwayEnterleft_n.png");
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
            }
            else if (CAndroidAutoEnums::EN_AA_NEXT_TURN_SIDE_TYPE_RIGHT == objAANaviNextTurnInfo.m_iNextTurnSide)
            {
                setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
                setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_HighwayEnterright_n.png");
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
            }
            else
            {
                CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
                LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: SHARP TURN: Wrong side is recieved.", __FUNCTION__);
            }
        }
            break;
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_EVENT_ROUND_ABOUT_ENTER:
        {
            setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
            setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_RoundAboutEnter_n.png");
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
        }
            break;
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_EVENT_ROUND_ABOUT_EXIT:
        {
            setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
            setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_RoundAboutExit_n.png");
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
        }
            break;
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_EVENT_SHARP_TURN:
        {
            if (CAndroidAutoEnums::EN_AA_NEXT_TURN_SIDE_TYPE_LEFT == objAANaviNextTurnInfo.m_iNextTurnSide)
            {
                setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
                setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_LeftTurnSharp_n.png");
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
            }
            else if (CAndroidAutoEnums::EN_AA_NEXT_TURN_SIDE_TYPE_RIGHT == objAANaviNextTurnInfo.m_iNextTurnSide)
            {
                setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
                setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_RightTurnSharp_n.png");
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
            }
            else
            {
                CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
                LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: SHARP TURN: Wrong side is recieved.", __FUNCTION__);
            }
        }
            break;
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_EVENT_SLIGHT_TURN:
        {
            if (CAndroidAutoEnums::EN_AA_NEXT_TURN_SIDE_TYPE_LEFT == objAANaviNextTurnInfo.m_iNextTurnSide)
            {
                setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
                setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_BearLeft_n.png");
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
            }
            else if (CAndroidAutoEnums::EN_AA_NEXT_TURN_SIDE_TYPE_RIGHT == objAANaviNextTurnInfo.m_iNextTurnSide)
            {
                setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
                setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_BearRight_n.png");
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
            }
            else
            {
                CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
                LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: SLIGHT TURN: Wrong side is recieved.", __FUNCTION__);
            }
        }
            break;
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_EVENT_STRAIGHT:
        {
            setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
            setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_Striaght_n.png");
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
        }
            break;
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_EVENT_TURN:
        {
            if (CAndroidAutoEnums::EN_AA_NEXT_TURN_SIDE_TYPE_LEFT == objAANaviNextTurnInfo.m_iNextTurnSide)
            {
                setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
                setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_TurnLeft_n.png");
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
            }
            else if (CAndroidAutoEnums::EN_AA_NEXT_TURN_SIDE_TYPE_RIGHT == objAANaviNextTurnInfo.m_iNextTurnSide)
            {
                setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
                setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_Turnright_n.png");
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
            }
            else
            {
                CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
                LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: SLIGHT TURN: Wrong side is recieved.", __FUNCTION__);
            }
        }
            break;
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_EVENT_U_TURN:
        {
            setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
            setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_UTurn_n.png");
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
        }
            break;
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_EVENT_OFF_RAMP:
        {
            setAANaviPopupText(QString::fromStdString(objAANaviNextTurnInfo.m_strRoadName));
            setAANaviPopupImage("qrc:/image/AANavigation/Nav_Ico_7in_n-assets/Nav_Ico_HighwayExit_n.png");
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
        }
            break;
        default:
        {
            CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_AA_NAVIGATION_DETAILS);
            LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "Navigation Event type Not handled.")
            }
            break;
        }

    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "m_pAndroidAutoResource is NULL.");
    }

}

void CAndroidAutoAdaptor::updateAANaviDistanceDetails()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if ( m_pAndroidAutoResource )
    {
        SAANaviNextTurnDistInfo objAANaviNextTurnDistInfo = m_pAndroidAutoResource->getAANavigationNextTurnDistInfo();

        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: Distance Unit type: %d", __FUNCTION__, objAANaviNextTurnDistInfo.m_iDistanceUnit);

        QString strDisplayDistance = "";

        switch(static_cast<CAndroidAutoEnums::EAANaviNextTurnDistanceUnit> (objAANaviNextTurnDistInfo.m_iDistanceUnit))
        {
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_DISTANCE_UNIT_METERS:
            strDisplayDistance = QString::number(objAANaviNextTurnDistInfo.m_iDisplayDistance / 1000) + " m";
            break;
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_DISTANCE_UNIT_KILOMETERS_P1:
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_DISTANCE_UNIT_KILOMETERS:
            strDisplayDistance = QString::number(static_cast<float> (objAANaviNextTurnDistInfo.m_iDisplayDistance) / 1000) + " km";
            break;
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_DISTANCE_UNIT_MILES_P1:
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_DISTANCE_UNIT_MILES:
            strDisplayDistance = QString::number(objAANaviNextTurnDistInfo.m_iDisplayDistance / 1000) + " mi";
            break;
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_DISTANCE_UNIT_YARDS:
            strDisplayDistance =  QString::number(objAANaviNextTurnDistInfo.m_iDisplayDistance / 1000) + " yards";
            break;
        case CAndroidAutoEnums::EN_AA_NEXT_TURN_DISTANCE_UNIT_FEET:
            strDisplayDistance = QString::number(objAANaviNextTurnDistInfo.m_iDisplayDistance / 1000) + " feets";
            break;
        default:
            LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "Distance Unit type Not handled.")
                    break;
        }

        setAANaviDistance(strDisplayDistance);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAutoResource is NULL", __FUNCTION__);
    }
}

bool CAndroidAutoAdaptor::isAndroidAutoResourceReady()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    bool bReturnValue = false;

    if (NULL != m_pAndroidAutoResource)
    {
        bReturnValue = true;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAutoResource"
                                                   " is NULL", __FUNCTION__);
    }

    return bReturnValue;
}

void CAndroidAutoAdaptor::requestAAProjection()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if (m_pAndroidAutoResource)
    {
        m_pAndroidAutoResource->requestProjection();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAutoResource"
                                                   " is NULL", __FUNCTION__);
    }
}

void CAndroidAutoAdaptor::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    connect(CAudioAdaptor::getInstance(), SIGNAL(sigActiveAudioSourceListUpdated()),
            this, SLOT(slotActiveAudioSourceListUpdated()), Qt::QueuedConnection);
    connect(CAudioAdaptor::getInstance(), SIGNAL(sigActiveEntSrcChanged()),
            this, SLOT(slotActiveEntSourceChanged()), Qt::QueuedConnection);
}

void CAndroidAutoAdaptor::disconnectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    disconnect(CAudioAdaptor::getInstance(), SIGNAL(sigActiveAudioSourceListUpdated()),
               this, SLOT(slotActiveAudioSourceListUpdated()));
    disconnect(CAudioAdaptor::getInstance(), SIGNAL(sigActiveEntSrcChanged()),
               this, SLOT(slotActiveEntSourceChanged()));
}

void CAndroidAutoAdaptor::reportKeyEventToResource(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: eKey: %d, eKeyState: %d", __FUNCTION__, eKey, eKeyState);

    if (m_pAndroidAutoResource)
    {
        m_pAndroidAutoResource->reportKeyEvent(eKey, eKeyState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAutoResource is NULL", __FUNCTION__);
    }
}

void CAndroidAutoAdaptor::resetData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    setAndroidAutoProjectionStatus(false);
    setAAMediaPlayState(CAndroidAutoEnums::EN_AA_MEDIA_PLAY_STATE_UNKNOWN);
    setAAMediaSongArtist("");
    setAAMediaSongTitle("");
    setOKGoogleStatus(false);
    setAANaviStatus(false);
    setCanSwitchMode(false);
    setAATransientState(false);
    setAANaviPopupTitle("");
    setAANaviPopupText("");
    setAANaviPopupImage("");
    setAANaviDistance("");
}

void CAndroidAutoAdaptor::goToNativeHome()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if (CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_AndroidAuto))
    {
        CHMIMain::getSM()->raise_evHomeActivated();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : AndroidAuto "
                                                    "is not cative"
                                                    " state.",
                    __FUNCTION__);
    }
}

void CAndroidAutoAdaptor::requestNative()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if (m_pAndroidAutoResource)
    {
        m_pAndroidAutoResource->requestNative();
        goToNativeHome();

        // Calling layer manager adaptor to show/set the HMI surface as top surface
        CLayerManagerAdaptor::getInstance()->showScene(CLayerManagerEnums::SURFACE_HMI);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAutoResource"
                                                   " is NULL", __FUNCTION__);
    }
}

void CAndroidAutoAdaptor::launchAndroidAuto()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if ( !m_bAndroidAutoConnectionStatus )
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_CONNECT_YOUR_PHONE);
    }
    else if ( !m_bAndroidAutoProjectionStatus )
    {
        requestAAProjection();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: Android Auto is already"
                                                " projected.", __FUNCTION__);
    }
}

void CAndroidAutoAdaptor::next()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if (m_pAndroidAutoResource)
    {
        m_pAndroidAutoResource->aapMediaNextAsync();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAutoResource"
                                                   " is NULL", __FUNCTION__);
    }
}

void CAndroidAutoAdaptor::prev()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if (m_pAndroidAutoResource)
    {
        m_pAndroidAutoResource->aapMediaPreviousAsync();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAutoResource"
                                                   " is NULL", __FUNCTION__);
    }
}

void CAndroidAutoAdaptor::togglePlayPause()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if (m_pAndroidAutoResource)
    {
        m_pAndroidAutoResource->toggleAapMediaAsync();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAutoResource"
                                                   " is NULL", __FUNCTION__);
    }
}

void CAndroidAutoAdaptor::showAAMusicScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    /*
     * if canSwitchMode is true or Any Audio Screen is active, like FM, AM, Media
     * screen and AA Media gets activated. HMI should switch to AA Media screen.
     */
    if (m_pAndroidAutoResource && (m_bCanSwitchMode || CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_ActiveAudio)))
    {
        m_pAndroidAutoResource->aapShowAaMediaAsync();
        setCanSwitchMode(false);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAutoResource"
                                                   " is NULL", __FUNCTION__);
    }
}

void CAndroidAutoAdaptor::setCanSwitchMode(bool bCanSwitchMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: bCanSwitchMode: %d", __FUNCTION__, bCanSwitchMode);

    if ( ( m_bCanSwitchMode != bCanSwitchMode ) &&
         m_bAndroidAutoConnectionStatus )
    {
        m_bCanSwitchMode = bCanSwitchMode;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: Values are same.", __FUNCTION__);
    }
}

void CAndroidAutoAdaptor::slotActiveAudioSourceListUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
}

void CAndroidAutoAdaptor::slotActiveEntSourceChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if ( m_bAndroidAutoConnectionStatus &&
         (CAudioEnums::SRC_GAL_MEDIA ==
          CAudioAdaptor::getInstance()->activeEntSrc()) )
    {
        showAAMusicScreen();
    }
    else if ( m_bCanSwitchMode )
    {
        requestNative();
        setCanSwitchMode(false);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: Active Source is not "
                                                   "SRC_GAL_MEDIA", __FUNCTION__);
    }
}

CAndroidAutoAdaptor::~CAndroidAutoAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
}

CAndroidAutoAdaptor *CAndroidAutoAdaptor::getInstance()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if (!m_pAndroidAutoAdaptor)
    {
        m_pAndroidAutoAdaptor = new CAndroidAutoAdaptor();
    }
    else
    {
        // Do nothing.
    }

    return m_pAndroidAutoAdaptor;
}

void CAndroidAutoAdaptor::setAndroidAutoConnectionStatus(const bool bAAConnectionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : bAAConnectionStatus: %d",
             __FUNCTION__, bAAConnectionStatus);

    if (m_bAndroidAutoConnectionStatus != bAAConnectionStatus)
    {
        m_bAndroidAutoConnectionStatus = bAAConnectionStatus;
        emit sigAndroidAutoConnectionStatusChanged(m_bAndroidAutoConnectionStatus);

        /*
         * If Display is Off, Do display ON
         */
        CDisplayManagerAdaptor::getInstance()->reqDisplayOnOffFeature(false);

        if (!m_bAndroidAutoConnectionStatus)
        {
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_SESSION_CLOSED);
            goToNativeHome();
            resetData();
        }
        else
        {
            CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_AA_CONNECT_YOUR_PHONE);
            CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_AA_FIRST_RUN);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : Values are same.", __FUNCTION__);
    }
}

void CAndroidAutoAdaptor::setAndroidAutoBondReqStatus(const bool bAABondReqStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : bAABondReqStatus: %d",
             __FUNCTION__, bAABondReqStatus);
    if (m_bAndroidAutoBondReqStatus != bAABondReqStatus)
    {
        m_bAndroidAutoBondReqStatus = bAABondReqStatus;
        emit sigAndroidAutoBondReqStatusChanged(m_bAndroidAutoBondReqStatus);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : Values are same.", __FUNCTION__);
    }

}

void CAndroidAutoAdaptor::setAndroidAutoProjectionStatus(const bool bAAProjectionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : bAAProjectionStatus: %d",
             __FUNCTION__, bAAProjectionStatus);

    if (m_bAndroidAutoProjectionStatus != bAAProjectionStatus)
    {
        m_bAndroidAutoProjectionStatus = bAAProjectionStatus;

        CHMIMain::getSM()->getSCI_AndroidAuto()->set_bProjStatus(m_bAndroidAutoProjectionStatus);
        emit sigAndroidAutoProjectionStatusChanged(m_bAndroidAutoProjectionStatus);

        if (m_bAndroidAutoProjectionStatus)
        {
            /*
             * If Display is Off, Do display ON
             */
            CDisplayManagerAdaptor::getInstance()->reqDisplayOnOffFeature(false);

            /*
             * Raise evAndroidAutoActivated to activate AndroidAuto state
             * in state Machine.
             */
            CHMIMain::getSM()->raise_evAndroidAutoActivated();
        }
        else
        {
            goToNativeHome();

            /*
             * This is done here because, If we show popup on connection status,
             * that time the state/popup context remains as Android Auto (in AA
             * context this popup is not allowed to show), the popup
             * context changes only on entry of new state, So after raising the
             * event of projection status changed, HMI is showing the session
             * closed popup, if Android Auto connection status is false.
             */
            if (!m_bAndroidAutoConnectionStatus)
            {
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_SESSION_CLOSED);
            }
            else
            {
                // Do nothing.
            }
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : Values are same.",
                 __FUNCTION__);
    }
}

void CAndroidAutoAdaptor::setAAMediaSongTitle(const QString &strAAMediaSongTitle)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : strAAMediaSongTitle: %s",
             __FUNCTION__, strAAMediaSongTitle.toStdString().c_str());

    if (m_strAAMediaSongTitle != strAAMediaSongTitle)
    {
        m_strAAMediaSongTitle = strAAMediaSongTitle;
        emit sigAAMediaSongTitleChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : Values are same.",
                 __FUNCTION__);
    }
}

void CAndroidAutoAdaptor::setAAMediaSongArtist(const QString &strAAMediaSongArtist)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : strAAMediaSongArtist: %s",
             __FUNCTION__, strAAMediaSongArtist.toStdString().c_str());

    if (m_strAAMediaSongArtist != strAAMediaSongArtist)
    {
        m_strAAMediaSongArtist = strAAMediaSongArtist;
        emit sigAAMediaSongArtistChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : Values are same.",
                 __FUNCTION__);
    }
}

void CAndroidAutoAdaptor::setAAMediaPlayState(CAndroidAutoEnums::EAAMediaPlayState eAAMediaPlayState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : eAAMediaPlayState: %d",
             __FUNCTION__, eAAMediaPlayState);

    if (m_eAAMediaPlayState != eAAMediaPlayState)
    {
        m_eAAMediaPlayState = eAAMediaPlayState;
        emit sigAAMediaPlayStateChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : Values are same.",
                 __FUNCTION__);
    }
}

void CAndroidAutoAdaptor::setOKGoogleStatus(bool bOKGoogleStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : bOKGoogleStatus: %d",
             __FUNCTION__, bOKGoogleStatus);

    if (m_bOKGoogleStatus != bOKGoogleStatus)
    {
        m_bOKGoogleStatus = bOKGoogleStatus;
        emit sigOKGoogleStatusChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : Values are same.",
                 __FUNCTION__);
    }
}

void CAndroidAutoAdaptor::setAANaviStatus(bool bAANaviStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : bAANaviStatus: %d",
             __FUNCTION__, bAANaviStatus);

    if (m_bAANaviStatus != bAANaviStatus)
    {
        m_bAANaviStatus = bAANaviStatus;
        emit sigAANaviStatusChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : Values are same.",
                 __FUNCTION__);
    }
}

void CAndroidAutoAdaptor::setAANaviPopupTitle(const QString &strAANaviPopupTitle)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : strAANaviPopupTitle: %s",
             __FUNCTION__, strAANaviPopupTitle.toStdString().c_str());

    if (m_strAANaviPopupTitle != strAANaviPopupTitle)
    {
        m_strAANaviPopupTitle = strAANaviPopupTitle;
        emit sigAANaviPopupTitleChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : Values are same.", __FUNCTION__);
    }
}

void CAndroidAutoAdaptor::setAANaviPopupText(const QString &strAANaviPopupText)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : strAANaviPopupText: %s",
             __FUNCTION__, strAANaviPopupText.toStdString().c_str());

    if (m_strAANaviPopupText != strAANaviPopupText)
    {
        m_strAANaviPopupText = strAANaviPopupText;
        emit sigAANaviPopupTextChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : Values are same.", __FUNCTION__);
    }
}

void CAndroidAutoAdaptor::setAANaviPopupImage(const QString &strAANaviPopupImage)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : strAANaviPopupImage: %s",
             __FUNCTION__, strAANaviPopupImage.toStdString().c_str());

    if (m_strAANaviPopupImage != strAANaviPopupImage)
    {
        m_strAANaviPopupImage = strAANaviPopupImage;
        emit sigAANaviPopupImageChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : Values are same.", __FUNCTION__);
    }
}

void CAndroidAutoAdaptor::setAANaviDistance(const QString &strAANaviDistance)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : strAANaviDistance: %s",
             __FUNCTION__, strAANaviDistance.toStdString().c_str());

    if (m_strAANaviDistance != strAANaviDistance)
    {
        m_strAANaviDistance = strAANaviDistance;
        emit sigAANaviDistanceChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : Values are same.", __FUNCTION__);
    }
}
