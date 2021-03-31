/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CMediaEventProvider.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* @brief        File to contain all the Structure Data that shall be used by
*               CAndroidAutoResourceImpl Class
*/
#ifndef CANDROIDAUTORESOURCEDATA_H
#define CANDROIDAUTORESOURCEDATA_H

#include <string>

using namespace std;

/**
 * @struct SAAMediaMetaData
 * @brief This structure holds the data AAMediaMetaData
 */
struct SAAMediaMetaData
{
    SAAMediaMetaData()
        :m_strSongName("")
        ,m_strAlbumName("")
        ,m_strArtistName("")
        ,m_strSongAlbumArt("")
        ,m_strPlaylist("")
        ,m_uiTime(0)
        ,m_iSongRating(-1)
    {

    }
    string m_strSongName;
    string m_strAlbumName;
    string m_strArtistName;
    string m_strSongAlbumArt;
    string m_strPlaylist;
    unsigned int m_uiTime;
    int m_iSongRating;
};

/**
 * @struct SAASessionDetails
 * @brief This structure holds the Android Auto session details.
 */
struct SAASessionDetails
{
    SAASessionDetails()
        :m_strDeviceName("")
        ,m_strBtAddress("")
        ,m_strUSBSerialNo("")
        ,m_bIsConnected(false)
        ,m_iTransportType(0)
        ,m_iSessionStatus(0)
        ,m_bRemoteUi(false)
    {

    }
    string m_strDeviceName;
    string m_strBtAddress;
    string m_strUSBSerialNo;
    bool m_bIsConnected;
    int m_iTransportType;
    int m_iSessionStatus;
    bool m_bRemoteUi;
};

/**
 * @struct SAANaviNextTurnInfo
 * @brief This structure holds the Android Auto Navigation's Next Turn Information.
 */
struct SAANaviNextTurnInfo
{
    SAANaviNextTurnInfo()
        :m_strRoadName("")
        ,m_iNextTurnSide(3) // 3 is used as unspecified turn type
        ,m_iNextTurnEvent(0) // 0 is unknown
        ,m_strImage("")
        ,m_iTurnAngle(-1)
        ,m_iTurnNumber(-1)
    {

    }
    string m_strRoadName;
    int m_iNextTurnSide;
    int m_iNextTurnEvent;
    string m_strImage;
    int m_iTurnAngle;
    int m_iTurnNumber;
};

/**
 * @struct SAANaviNextTurnDistInfo
 * @brief This structure holds the Android Auto Navigation's Next Turn Distance Information.
 */
struct SAANaviNextTurnDistInfo
{
    SAANaviNextTurnDistInfo()
        :m_iDistance(-1)
        ,m_iTimeDuration(-1)
        ,m_iDisplayDistance(-1)
        ,m_iDistanceUnit(-1)
    {

    }
    int m_iDistance;
    int m_iTimeDuration;
    int m_iDisplayDistance;
    int m_iDistanceUnit;
};

#endif // CANDROIDAUTORESOURCEDATA_H
