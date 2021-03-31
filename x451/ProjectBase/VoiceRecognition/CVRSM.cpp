/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CVRSM.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain implementation of all the methods declared in
 *                CVRSM class
 */

#include "CVRApplication.h"
#include "CVRSM.h"
#include "logging.h"

CVRSM::CVRSM(CVRApplication &objVRApp)
    : m_objVRApp(objVRApp)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    CHMIMain::getSM()->setSCI_Vr_OCB(this);
}

CVRSM::~CVRSM()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
}

void CVRSM::enterVRPickList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    m_objVRApp.loadScreen("qrc:/QML/VoiceRecognition/PickListScreen.qml");
}

void CVRSM::exitVRPickList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    CFramework::getFramework().clearScreenHistoryStack();
}

void CVRSM::enterVRHelp()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
}

void CVRSM::exitVRHelp()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    CFramework::getFramework().clearScreenHistoryStack();
}

void CVRSM::enterVRHelpMain()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    m_objVRApp.loadScreen("qrc:/QML/VoiceRecognition/HelpCategoryListScreen.qml");
}

void CVRSM::exitVRHelpMain()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
}

void CVRSM::enterVRHelpDetail()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    m_objVRApp.loadScreen("qrc:/QML/VoiceRecognition/HelpCommandListScreen.qml");
}

void CVRSM::exitVRHelpDetail()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
}
