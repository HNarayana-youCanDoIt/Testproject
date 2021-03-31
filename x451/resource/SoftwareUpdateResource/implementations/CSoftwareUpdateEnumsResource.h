/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CSoftwareUpdateEnumsResource.h
* @ingroup      HMIComponent
* @author       Nishant Khandagale
* CSoftwareUpdateEnumsResource, Enum for SoftwareUpdateHandler
*/

#ifndef CSOFTWAREUPDATEENUMSRESOURCE_H
#define CSOFTWAREUPDATEENUMSRESOURCE_H

#include <string>
using namespace std;

/**
 * Enum for different software update availability states
 */
enum ESoftwareUpdateAvailability
{
    UPDATE_READY_TO_DOWNLOAD = 0,
    UPDATE_READY_TO_INSTALL = 1,
    NW_NOT_IN_UPDATABLE_MODE = 2,
    NO_UPDATE_AVAILABLE = 3,
    UPDATE_ALREADY_IN_PROGRESS = 4,
    UPDATE_NOT_REQUIRED = 5,
    UPDATE_PACKAGE_CORRUPTED = 6,
    UPDATE_PACKAGE_INVALID = 7,
    UPDATE_PACKAGE_VALIDATION_FAILED = 8,
    UPDATE_SOURCE_MISSING = 9,
    SERVER_CONNECT_FAILED = 10,
    NO_NETWORK_CONNECTIVITY = 11
};

/**
 * Enum for different software update ERROR CODE states
 */
enum ESoftwareUpdateError
{
    PACKAGE_VALIDATION_FAILED = 0,
    PACKAGE_DOWNLOAD_FAILED = 1,
    PACKAGE_INSTALLATION_FAILED = 2,
    SERVER_SESSION_ERROR = 3,
    SERVER_CONNECTION_NOT_AVAILABLE = 4,
    MSD_DISCONNECTED = 5,
    MSD_INVALID = 6,
    PRECONDITION_CHECK_FAILED = 7,
    INVALID_SEQUENCE = 8,
    POST_INSTALL_VERIFICATION_FAILED = 9,
    SOFTWARE_UP_TO_DATE = 10,
    UNKNOWN_ERROR = 11,
    NO_NW_CONNECTIVITY = 12
};

/**
 * Enum for canceling update in progress
 */
enum ESoftwareUpdateCancelType
{
     DECLINE_INSTALL=0,
     CANCEL_INSTALL=1
};

/**
 * Enum for different software update sources
 */
enum ESoftwareUpdateSource
{
    UPDATE_SOURCE_MSD = 0,
    UPDATE_SOURCE_OTA = 1,
    UPDATE_SOURCE_VEHICLE_NETWORK = 2,
    UPDATE_SOURCE_UNKNOWN = 3
};

enum versionMismatchType{
    NO_VERSION_MISMATCH = 0,
    DISPLAY_VERSION_MISMATCH = 1,
    BUTTON_PANEL_VERSION_MISMATCH = 2,
    BP_DM_VERSION_MISMATCH = 3
};

struct SPackageDetails
{
       SPackageDetails() :
           eSource(UPDATE_SOURCE_UNKNOWN),
           strPackageName(""),
           strVersion(""),
           uiPackageSize(0)
       {
       }

       ESoftwareUpdateSource eSource ;
       string strPackageName;
       string strVersion ;
       uint32_t uiPackageSize ;
};

struct SUpdateSearchResult
{
    SUpdateSearchResult():
        _packageDetails(),
        _updateAvailability(NO_UPDATE_AVAILABLE)
    {

    }

    SPackageDetails _packageDetails;
    ESoftwareUpdateAvailability _updateAvailability;

};

#endif // CSOFTWAREUPDATEENUMSRESOURCE_H
