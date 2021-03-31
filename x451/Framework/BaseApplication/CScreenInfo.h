/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CScreenInfo.h
* @ingroup      HMI Framework
* @author       Mohit Rajani
* @brief Class stores the map<QString, int> of screens and their corresponding screen timeouts
*/

#ifndef SCREENINFO_H
#define SCREENINFO_H

#include <QMap>
/**
 * Header contains all the screens within the project and their respective timeouts
*/
namespace uiFwk {

const int iGenericScreenTimeout = 10000;
const int iNoScreenTimeout = -1;
struct SScreenTimeoutInfo
{
    //!Data to hold timeout value of screen timer.
    int     m_iScreenTimeout;
    //!Flag to maintain the default timeout rule for screen.
    bool    m_bTimeoutRuleDefault;
    SScreenTimeoutInfo(bool bTimeoutRuleDefault = true, int iScreenTimeout = iGenericScreenTimeout)
    {
        m_iScreenTimeout        = iScreenTimeout;
        m_bTimeoutRuleDefault   = bTimeoutRuleDefault;
    }
};

    QMap<QString, SScreenTimeoutInfo> screenInfoTimeoutMap = {
        //Home
        {"ScnHomeUpdateShortcuts.qml"	, SScreenTimeoutInfo() },
        {"ScnConfigureFavKey.qml"       , SScreenTimeoutInfo() },

        //Media
        {"MediaAuxGainScreen.qml"		, SScreenTimeoutInfo() },
        {"MediaBrowseCategory.qml"      , SScreenTimeoutInfo() },
        {"MediaBrowseScreen.qml"        , SScreenTimeoutInfo() },

        //Tuner
        {"TunerOptionScreen.qml"        , SScreenTimeoutInfo() }
    };
}
#endif // SCREENINFO_H
