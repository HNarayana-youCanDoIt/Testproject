/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CSoftwareUpdateSM.cpp
 * @ingroup         HMIComponent
 * @author          Gaurav Garg
 * CSoftwareUpdateSM, a State machine handler for Software Update module,
 * CSoftwareUpdateSM inherits SCI_SoftwareUpdate_OCB to handle statemachine events.
 */

#include "HMIIncludes.h"
#include "CSoftwareUpdateSM.h"
#include "CHardkeyAdaptor.h"
#include "CSoftwareUpdateAdaptor.h"

CSoftwareUpdateSM::CSoftwareUpdateSM(CSoftwareUpdateApplication& softwareUpdateApp):mSoftwareUpdateApp(softwareUpdateApp)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s", __FUNCTION__);
}

CSoftwareUpdateSM::~CSoftwareUpdateSM()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s", __FUNCTION__);
}

void CSoftwareUpdateSM::enterSoftwareUpdateMain()
{
    CHardkeyAdaptor::getInstance()->setSWUpdateActiveState(true);
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s", __FUNCTION__);
    mSoftwareUpdateApp.loadScreen("qrc:/QML/SoftwareDownload/SoftwareDownload.qml");
}

void CSoftwareUpdateSM::exitSoftwareUpdateMain()
{
    CHardkeyAdaptor::getInstance()->setSWUpdateActiveState(false);
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s", __FUNCTION__);
}

void CSoftwareUpdateSM::enterSoftwareSelectMode()
{
    CHardkeyAdaptor::getInstance()->setSWUpdateActiveState(true);
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s", __FUNCTION__);
    mSoftwareUpdateApp.loadScreen("qrc:/QML/SoftwareDownload/ISOList.qml");
}

void CSoftwareUpdateSM::exitSoftwareSelectMode()
{
    CHardkeyAdaptor::getInstance()->setSWUpdateActiveState(false);
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s", __FUNCTION__);
    callDeclineOnSwUpdate();
}

void CSoftwareUpdateSM::enterSoftwareUpdate()
{
    CHardkeyAdaptor::getInstance()->setSWUpdateActiveState(true);
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s", __FUNCTION__);
}

void CSoftwareUpdateSM::exitSoftwareUpdate()
{
    CHardkeyAdaptor::getInstance()->setSWUpdateActiveState(false);
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s", __FUNCTION__);

#if !defined(TATA_X445)
    CFramework::getFramework().clearScreenHistoryStack();
#endif
}

void CSoftwareUpdateSM::callDeclineOnSwUpdate()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s", __FUNCTION__);
    CSoftwareUpdateAdaptor::getInstance()->cancelUpdateOnError(ESoftwareUpdateCancelType::DECLINE_INSTALL);
}
