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
* @author       Rahul Madan
* @brief        File to contain all the Structure Data that shall be used by CMediaResourceImpl Class
*/
#ifndef CMEDIARESOURCEDATA_H
#define CMEDIARESOURCEDATA_H

#include <string>

using namespace std;

/**
 * @struct NowPlayingInfo
 * @brief This structure shall hold the data for NowPlaying Track
 */
struct NowPlayingInfo
    {
        NowPlayingInfo()
            :strTitle("")
            ,strAlbum("")
            ,strArtist("")
            ,strFileName("")
            ,iFileID(-1)
            ,iMediaType(0) //unknown
        {

        }
        //This would hold Song Title
        std::string strTitle;

        //This would hold Song Album
        std::string strAlbum;

        //This would hold Song Artist
        std::string strArtist;

        //This would hold File name
        std::string strFileName;

        //This would hold ID of the Song being played
        int iFileID;

        //This would hold media type being played i.e. song or video
        int iMediaType;
    };

/**
 * @struct MediaBrowseData
 * @brief This structure shall hold the data for Media browse list
 */
struct MediaBrowseData
    {
        MediaBrowseData()
            :strValue("")
            ,iFileID(-1)
            ,iIndexID(-1)
            ,iMetadataType(0) //unknown
            ,bIsActive(false)
            ,iFSContentType(0)
        {

        }
        //This would hold the actual value of the browse item
        std::string strValue;

        //This would hold ID of the browse item
        int iFileID;

        //This would hold index ID of the browse item in teh current list
        int iIndexID;

        //This would hold metadata type of the browse item i.e. albums/artists/folders etc
        int iMetadataType;

        //This would hold a bool value indicating if current nowPlaying belongs to this item
        bool bIsActive;

        //This would hold file system content type reported by Media service for specific browse item
        int iFSContentType;
    };
/**
 * @struct SRemotePlayerSupport
 * @brief This structure shall hold the bool value for all Remote Player Capabilities
 */
struct SRemotePlayerSupport
{
    SRemotePlayerSupport()
    {
        bIsPlayPauseSupported = false;
        bIsNextPrevSupported = false;
        bIsFwdRwdSupported = false;
        bIsRepeatSupported = false;
        bIsRandomSupported = false;
        bIsBrowseSupported = false;
    }

    //This would hold bool value for Play/Pause feature support of current BT Device Connected for Media
    bool bIsPlayPauseSupported;

    //This would hold bool value for Next/Prev feature support of current BT Device Connected for Media
    bool bIsNextPrevSupported;

    //This would hold bool value for Repeat feature support of current BT Device Connected for Media
    bool bIsRepeatSupported;

    //This would hold bool value for Random feature support of current BT Device Connected for Media
    bool bIsRandomSupported;

    //This would hold bool value for Browse feature support of current BT Device Connected for Media
    bool bIsBrowseSupported;

    //This would hold bool value for fast forward/rewind support of current BT Device Connected for Media
    bool bIsFwdRwdSupported;
};

/**
 * @enum RemotePlayerCapabilities
 * @brief Enums for all the Remote Player Capabilities received from Media Service
 */
enum RemotePlayerCapabilities
{
    REMOTEPLAYERCAP_PLAY = 1,
    REMOTEPLAYERCAP_PAUSE = 2,
    REMOTEPLAYERCAP_NEXT = 4,
    REMOTEPLAYERCAP_PREVIOUS = 8,
    REMOTEPLAYERCAP_FASTFORWARD = 16,
    REMOTEPLAYERCAP_FASTREWIND = 32,
    REMOTEPLAYERCAP_REPEATOFF = 64,
    REMOTEPLAYERCAP_REPEATSINGLE = 128,
    REMOTEPLAYERCAP_REPEATALL = 256,
    REMOTEPLAYERCAP_SHUFFLE = 512,
    REMOTEPLAYERCAP_UNSHUFFLE = 1024,
    REMOTEPLAYERCAP_BROWSING = 2048
};

struct sVideoParameters
{
    /** This would hold video codec value */
    string strVideoCodec;
    /** This would hold video resolution: video height * video width */
    string strVideoResolution;
    /** This would hold video frame rate */
    string strVideoFrameRate;
    /** This would hold audio codec value in the video */
    string strAudioCodec;
    /** This would hold audio sampling rate in the video*/
    string strAudioSamplingRate;
};

#endif // CMEDIARESOURCEDATA_H
