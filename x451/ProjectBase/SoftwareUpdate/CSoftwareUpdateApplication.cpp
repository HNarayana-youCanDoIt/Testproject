/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CSoftwareUpdateApplication.cpp
 * @ingroup         HMIComponent
 * @author          Nishant Khandagale
 * CSoftwareUpdateApplication, an Application for Software Update module,
 * CSoftwareUpdateApplication act as mediator between QML and Statemachine.
 */

#include "CSoftwareUpdateApplication.h"
#include "CSoftwareUpdateSM.h"
#include "CSoftwareUpdateAdaptor.h"
#include "CSoftwareUpdateEventHandler.h"

CSoftwareUpdateApplication::CSoftwareUpdateApplication(QQuickItem* parent):CBaseApplication(parent),
    m_pSoftwareUpdateSM(new CSoftwareUpdateSM(*this)),
    m_pSoftwareUpdateAdaptor(CSoftwareUpdateAdaptor::getInstance()),
    m_pSoftwareUpdateEventHandler(new CSoftwareUpdateEventHandler())
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s", __FUNCTION__);
    CHMIMain::getSM()->setSCI_SoftwareUpdate_OCB(m_pSoftwareUpdateSM);
    mfw.setContextProperty("cppSoftwareUpdateApp",this);
}

CSoftwareUpdateApplication::~CSoftwareUpdateApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s", __FUNCTION__);
    if (m_pSoftwareUpdateSM)
    {
        delete m_pSoftwareUpdateSM;
    }
    if (m_pSoftwareUpdateEventHandler)
    {
        delete m_pSoftwareUpdateEventHandler;
    }
}

void CSoftwareUpdateApplication::onCreated(QQuickItem *rootObject)
{
    Q_UNUSED(rootObject);
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s", __FUNCTION__);
}

void CSoftwareUpdateApplication::loadScreen(QString qmlFilePath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    CBaseApplication::loadScreen(qmlFilePath);
}

void CSoftwareUpdateApplication::raiseSMEvent(const QString &name, const QVariant &data)
{
    Q_UNUSED(name)
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s name:%s data:%s", __FUNCTION__, name.toStdString().c_str(), data.toString().toStdString().c_str());

    if(ISO_STRING == data)
    {
        CHMIMain::getSM()->getSCI_SoftwareUpdate()->raise_evSoftwareSelectActivated();
    }
    else if(BACK_STRING == data)
    {
        CHMIMain::getSM()->raise_evBackPressed();
    }
    else if(HOME_STRING == data)
    {
        CHMIMain::getSM()->raise_evHomeActivated();
    }
    else if(ENGG_MENU_STRING == data)
    {
        CHMIMain::getSM()->raise_evEnggMenuActivated();
    }
    else if(USB_DISCONNECT_STRING == data)
    {
        //Check for Software Update state through Setup State.
        if(CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_Setup_setup_region_SoftwareUpdate_swupdate_region_SoftwareSelectScreen))
        {
            CHMIMain::getSM()->raise_evBackPressed();
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE, "%s - Request to raise SM event not handled",__FUNCTION__);
    }
}
