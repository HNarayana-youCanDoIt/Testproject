/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CBaseApplication.cpp
* @ingroup      HMI Framework
* @author       Mohit Rajani
* @brief Main base class for all the HMI applications.
*/

#include "CBaseApplication.h"
#include "CFramework.h"
#include "logging.h"
#include "Framework/ThemeManager/CThemeManager.h"

CBaseApplication::CBaseApplication(QQuickItem* pParent):
    mParent(pParent)
  , mfw(CFramework::getFramework())
  , mThemeMgr(CThemeManager::getThemeManager())
{

}

void CBaseApplication::qmlLog(QString strLog)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"QML_LOG: %s", strLog.toUtf8().data());
}

void CBaseApplication::sltPopupResult(CPopupEnum::EPopupID ePopupId, CPopupEnum::EPopupResult ePopupResult, QString strAdditionalInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, __FUNCTION__);
    //Do Nothing
    Q_UNUSED(ePopupId);
    Q_UNUSED(ePopupResult);
    Q_UNUSED(strAdditionalInfo);
}

void CBaseApplication::loadScreen(QString qmlFilePath)
{
    bool retVal = false;
    CScreen* screen = mfw.getQMLScreen(qmlFilePath,NULL);


    if ((screen) && (screen->component()))
    {
        mfw.addScreenToStack(screen->screenName());
        retVal = QMetaObject::invokeMethod(mfw.getRootObject(), "loadComponent", Q_ARG(QVariant, QVariant::fromValue(screen->component()))
                                           ,Q_ARG(QVariant,QVariant::fromValue(screen->screenName())));
        if (!retVal)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"loadScreen: invokeMethod failed retVal %d", retVal);
        }

        // Start the screen timer
        mfw.startScreenTimer(screen->screenName());
    }
}

void CBaseApplication::loadDrawers(const QString &strQmlFilePath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s", __FUNCTION__);

    bool bRetVal = false;
    CScreen* pScreen = mfw.getQMLScreen(strQmlFilePath,NULL);
    if ((pScreen) && (pScreen->component()))
    {
        bRetVal = QMetaObject::invokeMethod(mfw.getRootObject(), "loadDrawersComponent",
                                           Q_ARG(QVariant, QVariant::fromValue(pScreen->component())) , Q_ARG(QVariant,QVariant::fromValue(pScreen->screenName())));
        if (!bRetVal)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"loadDrawers: invokeMethod failed retVal %d", bRetVal);
        }
    }
}

bool CBaseApplication::loadKeypadOverlay(const QString &strQmlFilePath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s: strQmlFilePath is: %s", __FUNCTION__, strQmlFilePath.toStdString().c_str());

    bool bRetVal = false;
    CScreen* pScreen = mfw.getQMLScreen(strQmlFilePath, NULL);
    if ((pScreen) && (pScreen->component()))
    {
        bRetVal = QMetaObject::invokeMethod(mfw.getRootObject(), "loadKeypadOverlay",
                                           Q_ARG(QVariant, QVariant::fromValue(pScreen->component())) , Q_ARG(QVariant,QVariant::fromValue(pScreen->screenName())));
    }
    return bRetVal;
}

bool CBaseApplication::unloadKeypadOverlay()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s", __FUNCTION__);
    return QMetaObject::invokeMethod(mfw.getRootObject(), "unloadKeypadOverlay");
}

bool CBaseApplication::loadVROverlay(const QString &strQmlFilePath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s: strQmlFilePath is: %s", __FUNCTION__, strQmlFilePath.toStdString().c_str());

    bool bRetVal = false;
    CScreen* pScreen = mfw.getQMLScreen(strQmlFilePath, NULL);
    if ((pScreen) && (pScreen->component()))
    {
        bRetVal = QMetaObject::invokeMethod(mfw.getRootObject(), "loadVROverlay",
                                           Q_ARG(QVariant, QVariant::fromValue(pScreen->component())));
    }
    return bRetVal;
}

bool CBaseApplication::unloadVROverlay()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s", __FUNCTION__);
    return QMetaObject::invokeMethod(mfw.getRootObject(), "unloadVROverlay");
}

void CBaseApplication::loadMainAppScreen(const QString &qmlFilePath)
{
    CScreen* screen = mfw.getQMLScreen(qmlFilePath,NULL);
    if ((screen) && (screen->component()))
    {
        QQuickItem* object = static_cast<QQuickItem*>(screen->component()->create());
        object->setParentItem(mfw.getRootObject());
        onCreated(object);
    }
}

void CBaseApplication::loadNotificationScreen(const QString &strQmlFilePath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s", __FUNCTION__);

    CScreen* pScreen = mfw.getQMLScreen(strQmlFilePath,NULL);
    if ((pScreen) && (pScreen->component()))
    {
        QQuickItem* pObject = static_cast<QQuickItem*>(pScreen->component()->create());
        pObject->setParentItem(mfw.getNotificationRootObject());
        mfw.setNotificationRootObject(pObject);
    }
}

void CBaseApplication::loadVoiceAlertScreen(const QString &strQmlFilePath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s: strQmlFilePath: %s", __FUNCTION__, strQmlFilePath.toStdString().c_str());

    CScreen* pScreen = mfw.getQMLScreen(strQmlFilePath,NULL);

    if ((pScreen) && (pScreen->component()))
    {
        QQuickItem* pObject = static_cast<QQuickItem*>(pScreen->component()->create());
        pObject->setParentItem(mfw.getVoiceAlertRootObject());
        mfw.setVoiceAlertRootObject(pObject);
    }
}
void CBaseApplication::unloadScreen(const QString &qmlFilePath)
{
    Q_UNUSED(qmlFilePath);
}

void CBaseApplication::raiseSMEvent(const QString &name, const QVariant &data)
{
    Q_UNUSED(name);
    Q_UNUSED(data);
}
