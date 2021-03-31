/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         ITunerTypes.h
* @ingroup       HMIComponent
* @author        Manali Patil
* ITunerTypes includes enums of resource layer.
*/


#ifndef ITUNERTYPES_H
#define ITUNERTYPES_H

#include <string.h>

//ITunerTypes includes enums used for resource layer
namespace ITunerTypes
{

    /** enum for source Types */
    enum sourceType
    {
        SOURCE_UNDEF = 0,
        SOURCE_FM = 1,
        SOURCE_SW = 2,
        SOURCE_MW = 4,
        SOURCE_LW = 8,
        SOURCE_HD = 64
    };

    /** enum to identify the correspoding request */
    enum eRequestHandle
    {
        eHANDLE_DEFAULT = 0,
        eHANDLE_SEEK_AUTO = 1,
        eHANDLE_SEEK_STEP = 2,
        eHANDLE_SEEK_MANUAL = 3,
        eHANDLE_SEEK_OFF = 4,
        eHANDLE_SCAN = 5,
        eHANDLE_SELECT_PRESET_MANUAL = 6,
        eHANDLE_SELECT_PRESET_SWC = 7,
        eHANDLE_STORE_PRESET = 8,
        eHANDLE_SELECT_STATION = 9,
        eHANDLE_LIST_STATIONS = 10
    };

    /** enum for seek mode of station */
    enum StationSeekMode
    {
        SEEK_OFF,
        SEEK_MAN_UP,
        SEEK_MAN_DOWN,
        SEEK_AUTO_UP,
        SEEK_AUTO_DOWN,
        SEEK_ENDLESS_UP,
        SEEK_ENDLESS_DOWN,
        SEEK_SCAN_UP,
        SEEK_SCAN_SKIP_UP,
        SEEK_SCAN_DOWN,
        SEEK_SCAN_SKIP_DOWN,
        SEEK_FULL_AUTOSTORE,
        SEEK_FULL_BACKGROUND
    };
}
#endif // ITUNERTYPES_H
