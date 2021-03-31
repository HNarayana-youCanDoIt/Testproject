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
* @brief        File to contain all the Structure Data that shall be used by CMediaResourceImpl Class
*/
#ifndef CAPPLECARPLAYRESOURCEDATA_H
#define CAPPLECARPLAYRESOURCEDATA_H

#include <string>

using namespace std;

/**
 * @struct CarPlayNowPlayingInfo
 * @brief This structure shall hold the data for NowPlaying Track for CarPlay
 */
struct CarPlayNowPlayingInfo
{
    CarPlayNowPlayingInfo()
        :mStrTitle("")
        ,mStrArtist("")
    {

    }
    //This would hold Song Title
    std::string mStrTitle;
    //This would hold Song Artist
    std::string mStrArtist;
};


#endif // CAPPLECARPLAYRESOURCEDATA_H
