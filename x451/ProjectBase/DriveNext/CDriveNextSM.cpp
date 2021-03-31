/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDriveNextSM.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDriveNextSM, a State machine handler for DriveNext module,
 * CDriveNextSM inherits SCI_DriveNext_OCB to handle state-machine events.
 */

#include "HMIIncludes.h"

#include "CDriveNextApplication.h"
#include "CDriveNextAdaptor.h"
#include "CDriveNextSM.h"
#include "CDriveNextEventHandler.h"

///////////////////////////////////////////////////////////////////////////////
// CDriveNextSM related functions
///////////////////////////////////////////////////////////////////////////////
CDriveNextSM::CDriveNextSM(CDriveNextApplication& DriveNextApp):
    mDriveNextApp(DriveNextApp)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    CHMIMain::getSM()->setSCI_DriveNext_OCB(this);
}
//____________________________________________________________________________
CDriveNextSM::~CDriveNextSM()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
}

///////////////////////////////////////////////////////////////////////////////
// StateMachine related functions
///////////////////////////////////////////////////////////////////////////////

void CDriveNextSM::enterDriveNext()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    mDriveNextApp.getDriveNextAdaptor()->subscribeDNMainScreenGeneralSignals(true);
}

void CDriveNextSM::exitDriveNext()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    mDriveNextApp.getDriveNextAdaptor()->setCurrentTripIndex(0);
    mDriveNextApp.getDriveNextAdaptor()->setCurrentPerformanceIndex(0);
    mDriveNextApp.getDriveNextAdaptor()->subscribeDNMainScreenGeneralSignals(false);
}

void CDriveNextSM::enterDriveNextTripsScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    mDriveNextApp.loadScreen("qrc:/QML/DriveNext/ScnDriveNextTripsScreen.qml");
}

void CDriveNextSM::exitDriveNextTripsScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
}

void CDriveNextSM::enterDriveNextPerformanceBreakup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    mDriveNextApp.loadScreen("qrc:/QML/DriveNext/ScnDriveNextPerformanceBreakupScreen.qml");
    switch(mDriveNextApp.getDriveNextAdaptor()->currentTripType())
    {
    case CDriveNextEnum::EDNTripType::DRIVENEXT_CURRENT_TRIP:
    {
        mDriveNextApp.getDriveNextAdaptor()->subscribeDNMainScreenCurrentTripSignals(true);
    }
        break;
    case CDriveNextEnum::EDNTripType::DRIVENEXT_TRIP_A:
    {
        mDriveNextApp.getDriveNextAdaptor()->subscribeDNMainScreenTripASignals(true);
    }
        break;
    case CDriveNextEnum::EDNTripType::DRIVENEXT_TRIP_B:
    {
        mDriveNextApp.getDriveNextAdaptor()->subscribeDNMainScreenTripBSignals(true);
    }
        break;
    case CDriveNextEnum::EDNTripType::DRIVENEXT_OVERALL_TRIP:
    {
        mDriveNextApp.getDriveNextAdaptor()->subscribeDNMainScreenOverallTripSignals(true);
    }
        break;
    case CDriveNextEnum::EDNTripType::DRIVENEXT_BEST_TRIP:
    {
        mDriveNextApp.getDriveNextAdaptor()->subscribeDNMainScreenBestTripSignals(true);
    }
        break;
    case CDriveNextEnum::EDNTripType::DRIVENEXT_LAST_TRIP:
    {
        mDriveNextApp.getDriveNextAdaptor()->subscribeDNMainScreenLastTripSignals(true);
    }
        break;
    default :
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Unhandled Trip Type", __FUNCTION__);
    }
        break;
    }
}

void CDriveNextSM::exitDriveNextPerformanceBreakup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    switch(mDriveNextApp.getDriveNextAdaptor()->currentTripType())
    {
    case CDriveNextEnum::EDNTripType::DRIVENEXT_CURRENT_TRIP:
    {
        mDriveNextApp.getDriveNextAdaptor()->subscribeDNMainScreenCurrentTripSignals(false);
    }
        break;
    case CDriveNextEnum::EDNTripType::DRIVENEXT_TRIP_A:
    {
        mDriveNextApp.getDriveNextAdaptor()->subscribeDNMainScreenTripASignals(false);
    }
        break;
    case CDriveNextEnum::EDNTripType::DRIVENEXT_TRIP_B:
    {
        mDriveNextApp.getDriveNextAdaptor()->subscribeDNMainScreenTripBSignals(false);
    }
        break;
    case CDriveNextEnum::EDNTripType::DRIVENEXT_OVERALL_TRIP:
    {
        mDriveNextApp.getDriveNextAdaptor()->subscribeDNMainScreenOverallTripSignals(false);
    }
        break;
    case CDriveNextEnum::EDNTripType::DRIVENEXT_BEST_TRIP:
    {
        mDriveNextApp.getDriveNextAdaptor()->subscribeDNMainScreenBestTripSignals(false);
    }
        break;
    case CDriveNextEnum::EDNTripType::DRIVENEXT_LAST_TRIP:
    {
        mDriveNextApp.getDriveNextAdaptor()->subscribeDNMainScreenLastTripSignals(false);
    }
        break;
    default :
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Unhandled Trip Type", __FUNCTION__);
    }
        break;
    }
}
