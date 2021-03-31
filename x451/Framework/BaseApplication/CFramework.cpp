/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CFramework.cpp
* @ingroup      HMI Framework
* @author       Mohit Rajani
* @brief Class provides a way to register context properties, start/restart screen timers. Create and handle the qml screen components
*/

#include "CFramework.h"
#include "logging.h"
#include <QQmlContext>
#include <QQuickWindow>
#include <CHMIMain.h>
#include <QGuiApplication>
#include <CScreenInfo.h>

CFramework* CFramework::m_pFramework = nullptr;

CFramework::CFramework(QObject *pParent)
    :QObject(pParent),
      m_pRootObject(nullptr)
	, m_pNotificationRootObject(nullptr)
    , m_pVoiceAlertRootObject(nullptr)
    , m_strScreenName("")
    , m_bEnableUserInteractionDetection(false)
    , m_bIsBackPressed(false)
{
    m_objScreenTimer.setSingleShot(true);
    connect(&m_objScreenTimer,SIGNAL(timeout()),this, SLOT(sltScreenTimeout()));
    qGuiApp->installEventFilter(this);
}

CFramework::~CFramework()
{
    QMap<QString, CScreen*>::iterator screenIterator;
    for(screenIterator = m_mapScreens.begin(); screenIterator != m_mapScreens.end(); ++screenIterator)
    {
        delete screenIterator.value();
    }
    if (m_pFramework)
        delete m_pFramework;
    m_objScreenTimer.stop();
}

CFramework& CFramework::getFramework()
{
    if ( nullptr ==  m_pFramework )
    {
        m_pFramework = new CFramework;
    }
    return *m_pFramework;
}


void  CFramework::setContextProperty(const QString &strName, QObject *pValue)
{
    m_objEngine.rootContext()->setContextProperty(strName, pValue);
}

void CFramework::setContextProperty(const QString &name, const QVariant & value)
{
    m_objEngine.rootContext()->setContextProperty(name,value);
}

void CFramework::setRootObject(QQuickItem *pRootObject)
{
    m_pRootObject = pRootObject;
}

QQuickItem* CFramework::getRootObject()
{
    return m_pRootObject;
}

void CFramework::setNotificationRootObject(QQuickItem *pRootObject)
{
    m_pNotificationRootObject = pRootObject;
}

QQuickItem *CFramework::getNotificationRootObject()
{
    return m_pNotificationRootObject;
}

void CFramework::setVoiceAlertRootObject(QQuickItem *pRootObject)
{
    m_pVoiceAlertRootObject = pRootObject;
}

QQuickItem *CFramework::getVoiceAlertRootObject()
{
    return m_pVoiceAlertRootObject;
}

CScreen* CFramework::getQMLScreen(const QString &strQmlurl, QQuickItem* pParent)
{
    Q_UNUSED(pParent);
    //LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "Framework::getQMLScreen, url: %s",strQmlurl.toStdString().data());

    CScreen* pScreen = nullptr;

    QMap<QString, CScreen*>::const_iterator screenIterator = m_mapScreens.find(strQmlurl);

    if (screenIterator == m_mapScreens.end())
    {
        QQmlComponent* pNewComponent = new QQmlComponent(&m_objEngine, QUrl(strQmlurl));

        if (pNewComponent)
        {
            if(QQmlComponent::Ready == pNewComponent->status())
            {
                pScreen = new CScreen(strQmlurl, pNewComponent);

                if (pScreen)
                {
                    m_mapScreens.insert(strQmlurl, pScreen);
                    m_objEngine.setObjectOwnership(pNewComponent, QQmlEngine::CppOwnership);
                }
                else
                {
                    LOG_WARNING(Log::e_LOG_CONTEXT_MAIN, "%s: pScreen is NULL.", __FUNCTION__);
                }
            }
            else
            {
                if(QQmlComponent::Error == pNewComponent->status())
                {
                    LOG_ERROR(Log::e_LOG_CONTEXT_MAIN, "Framework::getQMLScreen Error loading componentroot");
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "Framework::getQMLScreen component not ready..!!");
                }

                QString strComponentErr;
                QDebug errStream(&strComponentErr);
                errStream << pNewComponent->errors();

                LOG_ERROR(Log::e_LOG_CONTEXT_MAIN, "Framework::getQMLScreen Error message: %s", strComponentErr.toStdString().data());
            }
        }
    }
    else
    {
        pScreen = screenIterator.value();
    }
    return pScreen;
}

void CFramework::startScreenTimer()
{
    //LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s: screen name: %s", __FUNCTION__, m_strScreenName.toStdString().c_str());
    QMap<QString, uiFwk::SScreenTimeoutInfo>::const_iterator it = uiFwk::screenInfoTimeoutMap.find(m_strScreenName);
    if ((it != uiFwk::screenInfoTimeoutMap.end()) && (uiFwk::iNoScreenTimeout != it.value().m_iScreenTimeout))
    {
        // if the timer is already running it will stop the timer and restart
        m_objScreenTimer.start(it.value().m_iScreenTimeout);
    }
    else
    {
        // Stopping screen timer if it is running for previous screen.
        if(m_objScreenTimer.isActive())
        {
            stopScreenTimer();
        }
    }
}

void CFramework::startScreenTimer(const QString &strScreenName)
{
    QMap<QString, uiFwk::SScreenTimeoutInfo>::const_iterator it = uiFwk::screenInfoTimeoutMap.find(strScreenName);
    //LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, timer for screen: %s", __FUNCTION__, strScreenName.toStdString().data());

    if ((it != uiFwk::screenInfoTimeoutMap.end()) && (uiFwk::iNoScreenTimeout != it.value().m_iScreenTimeout))
    {
        if(it.value().m_bTimeoutRuleDefault)
        {
            //LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, screen timeout handled by framework", __FUNCTION__);
            // if the timer is already running it will stop the timer and restart
            m_objScreenTimer.start(it.value().m_iScreenTimeout);
        }
        else
        {
            bool retVal = QMetaObject::invokeMethod(getRootObject(), "startScreenTimer");
            if (!retVal)
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_MAIN,"startScreenTimer: invokeMethod failed, retVal %d", retVal);
            }
        }
    }
    else
    {
        //LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, No screen found or timeout, hence no timer set for current screen",__FUNCTION__);
        // Stopping screen timer if it is running for previous screen.
        if(m_objScreenTimer.isActive())
        {
            stopScreenTimer();
        }
    }
}

void CFramework::sltScreenTimeout()
{
    //LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s",__FUNCTION__);
    m_strScreenName = "";
    doBack();
}

void CFramework::restartScreenTimer()
{
    //LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, screen: %s",__FUNCTION__, m_strScreenName.toStdString().data());
    startScreenTimer();
}

void CFramework::stopScreenTimer()
{
    //LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s",__FUNCTION__);
    m_objScreenTimer.stop();
}

bool CFramework::eventFilter(QObject *pQObject, QEvent *pQEvent)
{
    QEvent::Type eventType = pQEvent->type();
    if ((eventType == QEvent::TouchBegin) || (eventType == QEvent::TouchEnd) || (eventType == QEvent::TouchUpdate)
            || (eventType == QEvent::MouseMove))
    {
        // restart screen timer
        //LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, %s, event type: %d",__FUNCTION__, pQObject->objectName().toStdString().data(), static_cast<int>(eventType));
        restartScreenTimer();
        monitorUserInteraction();
    }
    else
    {
        // Do nothing
    }
    // standard event processing
    return QObject::eventFilter(pQObject, pQEvent);
}

void CFramework::setBEnableUserInteractionDetection(bool bEnableUserInteractionDetection)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s : %d",__FUNCTION__,bEnableUserInteractionDetection);
    m_bEnableUserInteractionDetection = bEnableUserInteractionDetection;
}

void CFramework::monitorUserInteraction()
{
    /**Below code is to broadcast for any type of User Interaction happenning i.e. Touch/HK/ScreeChange/Popups etc. */
    if(m_bEnableUserInteractionDetection)
    {
        emit sigBroadcastUserInteractionDetected();
        m_bEnableUserInteractionDetection = false;
    }
}

void CFramework::addScreenToStack(const QString &strScreenName)
{
    if(m_bIsBackPressed)
    {
        if(!m_screenHistoryStack.isEmpty())
        {
            m_screenHistoryStack.pop();
        }
    }
    //If back is not pressed, then push the new screen to the screen history stack and if back is not pressed then do nothing.
    else
    {
        /**
         * Emit signal to notify Generic list that a new screen is about to be loaded
         * Generic list would update the current top index of the currently loaded screen
         */
        emit sigBeginScreenLoading();

        SScreenData objScreenData;
        objScreenData.m_strScreenName = strScreenName;
        objScreenData.m_iTopIndex = 0;
        m_screenHistoryStack.push(objScreenData);
    }

    //Update the current screen variable
    m_strScreenName = strScreenName;

    setBackPressedStatus(false);
}

void CFramework::updateTopIndex(int iTopIndex)
{
    //Update the top index of current screen only when back button is not pressed
    if(!m_bIsBackPressed)
    {
        if(!m_screenHistoryStack.isEmpty())
        {
            SScreenData objScreen = m_screenHistoryStack.pop();
            objScreen.m_iTopIndex = iTopIndex;
            m_screenHistoryStack.push(objScreen);
        }
    }

}


int CFramework::getListTopItemIndex()
{
    int iReturnVal = 0;

    if(!m_screenHistoryStack.isEmpty())
    {
        SScreenData objScreen = m_screenHistoryStack.top();
        if(objScreen.m_strScreenName == m_strScreenName)
        {
            iReturnVal = objScreen.m_iTopIndex;
        }
    }

    return iReturnVal;
}

void CFramework::setBackPressedStatus(bool bIsBackPressed)
{
    m_bIsBackPressed = bIsBackPressed;
}

void CFramework::clearScreenHistoryStack()
{
    m_screenHistoryStack.clear();
    setBackPressedStatus(false);
}

void CFramework::doBack()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s ",__FUNCTION__);
    setBackPressedStatus(true);
    CHMIMain::getSM()->raise_evBackPressed();
}




