/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CVRApplication.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain implementation of all the methods declared in
 *                CVRApplication class
 */

#include "CVRApplication.h"
#include "CVRSM.h"
#include "CVRAdaptor.h"
#include "CVREventHandler.h"
#include "logging.h"
#include "CAppleCarPlayAdaptor.h"
#include "CAndroidAutoAdaptor.h"

CVRApplication::CVRApplication(QQuickItem *pParent)
    : CBaseApplication(pParent),
      m_pVREventHandler(new CVREventHandler(this)),
      m_pVRSm(new CVRSM(*this))
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    mfw.setContextProperty("cppVRApp", this);
    connect(CVRAdaptor::getInstance(), SIGNAL(sigShowHideVROverlay(bool)), this, SLOT(sltShowHideVROverlay(bool)), Qt::DirectConnection);
}

CVRApplication::~CVRApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);

    if(m_pVREventHandler)
    {
        delete m_pVREventHandler;
        m_pVREventHandler = nullptr;
    }

    if(m_pVRSm)
    {
        delete m_pVRSm;
        m_pVRSm = nullptr;
    }
}

void CVRApplication::onCreated(QQuickItem* pRootObject)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    Q_UNUSED(pRootObject);
}

void CVRApplication::loadScreen(QString strQmlFilePath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: qml file path is - %s", __FUNCTION__, strQmlFilePath.toStdString().c_str());
    CBaseApplication::loadScreen(strQmlFilePath);
}

void CVRApplication::raiseSMEvent(const QString& strName, const QVariant& objData)
{
    Q_UNUSED(objData);
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: name is: %s", __FUNCTION__, strName.toStdString().c_str());

    if(strName.compare("VRHelpCommand") == 0)
    {
        CHMIMain::getSM()->getSCI_Vr()->raise_evVRHelpDetail();
    }
    else if(strName.compare("VRHelpCategory") == 0)
    {
        /* In case VR is launched on Projection screen, and VR Help is selected,
         * then Projection screen should not come to focus on VR cancel */
        CAppleCarPlayAdaptor::getInstance()->requestNative();
        CAndroidAutoAdaptor::getInstance()->requestNative();

        CHMIMain::getSM()->raise_evVRHelpActivated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR,"%s: Invalid name received", __FUNCTION__);
    }
}

void CVRApplication::sltShowHideVROverlay(bool bShowVROverLay)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: bShowVROverLay is: %d", __FUNCTION__, bShowVROverLay);
    if(bShowVROverLay)
    {
        if(loadVROverlay("qrc:/QML/VoiceRecognition/VRAnimPopup.qml"))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: VR overlay loaded", __FUNCTION__);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: Unable to load VR overlay", __FUNCTION__);
        }
    }
    else
    {
        if(unloadVROverlay())
        {
            LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: VR overlay unloaded", __FUNCTION__);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: Unable to unload VR overlay", __FUNCTION__);
        }
    }
}
