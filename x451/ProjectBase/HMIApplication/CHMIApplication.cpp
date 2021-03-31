/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CHMIApplication.h
* @ingroup      HMI Framework
* @author       Mohit Rajani
* @brief Main hmi class which creates the resources, adaptor, Qt windows and the state machine
*/

#include "CHMIApplication.h"
#include "Persistency/CPersistencyAdaptor.h"

#include "MediaOff/CMediaOffApplication.h"
#include "Tuner/CTunerApplication.h"
#include "Home/CHomeApplication.h"
#include "EnggMenu/CEnggApplication.h"
#include "Startup/CStartupAnim.h"
#include "Media/CMediaApplication.h"
#include "Setup/CSetupApplication.h"
#include "CDrawersApplication.h"
#include "CAndroidAutoApplication.h"
#include "SoftwareUpdate/CSoftwareUpdateApplication.h"
#include "VersionManager/CVersionManagerApplication.h"
#include "Diagnostic/CDiagnosticApplication.h"
#include "HardKey/CHardkeyEventHandler.h"
#include "Phone/CPhoneApplication.h"
#include "HVAC/CHVACApplication.h"
#include "CHMIApplicationSM.h"
#include <stdio.h>
#include <iostream>
#include <thread>
#include "HMIIncludes.h"
#include <QQuickView>
#include "CPowerModeAdaptor.h"
#include "CDisplayManagerAdaptor.h"
#include "CAppleCarPlayApplication.h"
#include "CParkAssistApplication.h"
#include "CVoiceAlertsEventHandler.h"
#include "CVRApplication.h"
#include "LayerManager/CLayerManagerApplication.h"
#include "CParkAssistAdaptor.h"
#include "CVariantControlApplication.h"
#include "CDateAndTimeAdaptor.h"
#include "CIntrospectionApplication.h"
#include "CICCastAdaptor.h"
#include "CAudioApplication.h"
#include "CRCAApplication.h"
#include "CMaskedMouseArea.h"
#include "CDynamicMaskedMouseArea.h"
#include "DriveNext/CDriveNextApplication.h"
#include "Doodle/CDoodleApplication.h"
#include "CW3WApplication.h"
#include "CSoundDemoApplication.h"

using namespace std;
#ifndef PLATFORM_WIN32
#include <systemd/sd-daemon.h>
#endif

#if !defined(PLATFORM_WIN32) && !defined(PLATFORM_LINUX_X86)
#include <NanoMsgService/CHMINanoMsgService.h>
#include <NanoMsgService/NanoMsg.h>
#endif

const qint32 HMI_SURFACE_ID = 20;
const qint32 VOICE_ALERT_NOTIFICATION_SURFACE_ID = 21;
const qint32 VOL_NOTIFICATION_SURFACE_ID = 22;
const QString HMI_CONFIG_FILE("/opt/hmi/HMI_CONFIG.ini");

CHMIApplication::CHMIApplication(QQuickItem* parent)
    :CBaseApplication(parent),
      rootObject(nullptr),
      m_pRootWindow(nullptr),
      m_pNotificationWindow(nullptr),
      m_pVoiceAlertWindow(nullptr),
      m_pHMIAppSM(nullptr),
#if !defined(PLATFORM_WIN32) && !defined(PLATFORM_LINUX_X86)
      m_pHMINanoMsgServiceThread(nullptr),
#endif
#ifdef USE_WAYLAND_IVI
      m_pWaylandIVICtrl(nullptr),
#endif
      m_pPopupManager(nullptr),
      m_bIsAnimationPlaying(true)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CHMIApplication::CHMIApplication");
    m_pHMIAppSM = new CHMIApplicationSM(*this);
    CHMIMain::getSM()->setSCI_Ui_OCB(m_pHMIAppSM);
    mfw.setContextProperty("cppUIBase", this);
    CMaskedMouseArea::registerMaskedMouseAreaToQML();
    CDynamicMaskedMouseArea::registerDynamicMaskedMouseAreaToQML();
    CHMIApplicationEnums::registerHMIApplicationEnumsToQML();
}

CHMIApplication::~CHMIApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CHMIApplication::~CHMIApplication");
    if (m_pHMIAppSM)
        delete m_pHMIAppSM;
#ifdef USE_WAYLAND_IVI
    if (m_pWaylandIVICtrl)
        delete m_pWaylandIVICtrl;
#endif

#if !defined(PLATFORM_WIN32) && !defined(PLATFORM_LINUX_X86)
    if(m_pHMINanoMsgServiceThread)
    {
        m_pHMINanoMsgServiceThread->quit();
        m_pHMINanoMsgServiceThread->wait();
    }
#endif
    if (m_pNotificationWindow)
        delete m_pNotificationWindow;

    m_pNotificationWindow = nullptr;

    if (m_pVoiceAlertWindow)
        delete m_pVoiceAlertWindow;

    m_pVoiceAlertWindow = nullptr;
}

void CHMIApplication::initHMIWindow()
{
    // Creating the window got the main HMI screens
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CHMIApplication::initHmi");

    //Read all the window dimensions from config file
    readAllWindowDimensionsFromConfig();

    //Create main HMI window
    createRootWindow();

    createNotificationWindow();

    createVoiceAlertWindow();

#ifdef USE_WAYLAND_IVI
    if (nullptr == m_pWaylandIVICtrl)
    {
        m_pWaylandIVICtrl = new WaylandIVIController();

        m_pWaylandIVICtrl->waylandLayerSetup(m_pRootWindow, static_cast<t_ilm_surface>(HMI_SURFACE_ID));
        m_pWaylandIVICtrl->waylandLayerSetup(m_pNotificationWindow, static_cast<t_ilm_surface>(VOL_NOTIFICATION_SURFACE_ID));
        m_pWaylandIVICtrl->waylandLayerSetup(m_pVoiceAlertWindow, static_cast<t_ilm_surface>(VOICE_ALERT_NOTIFICATION_SURFACE_ID));
    }
#endif

    if (nullptr == m_pPopupManager)
    {
        m_pPopupManager = CPopupManager::getInstance();
        mfw.setContextProperty("PopupManager", m_pPopupManager);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MAIN, "%s: m_pPopupManager is NULL.", __FUNCTION__);
    }

#if !defined(PLATFORM_WIN32) && !defined(PLATFORM_LINUX_X86)
    startNanoMsgServiceThread();
#endif
    //Create instances of all the applications
    createHMIApplications();

    // The load happens here since we are dependent on the various hmi applications to be instanciated
    // load the main hmi screen container
    loadMainAppScreen("qrc:/QML/Common/UI.qml");

    loadNotificationScreen("qrc:/QML/Common/HBNotificationOverlayUI.qml");

    loadVoiceAlertScreen("qrc:/QML/Drawers/HeaderStatusBar/HeaderNotificationContainerComponent.qml");
}

void CHMIApplication::readAllWindowDimensionsFromConfig()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s", __FUNCTION__);

#if defined(PLATFORM_WIN32) && defined(PLATFORM_LINUX_X86)
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Harman", "HMI_CONFIG");
#else
    QSettings settings(HMI_CONFIG_FILE, QSettings::IniFormat);
#endif
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s HMI config file path: %s", __FUNCTION__, settings.fileName().toStdString().data());
    //Check if file exits otherwise use the default set in structure
    if (QFile::exists(settings.fileName()))
    {
        // Get variant info based on it select the group to read the value from
        CVariantControlEnum::EVIP_DID eVIP_DID = CVariantControlAdaptor::getInstance()->eolVIP_DID();
        if (CVariantControlEnum::VIP_DID_HU_HIGH_X445 == eVIP_DID)
        {
            settings.beginGroup("X445");
        }
        else if ((CVariantControlEnum::VIP_DID_HU_HIGH_X451 == eVIP_DID) ||
                 (CVariantControlEnum::VIP_DID_HU_NEXON_EV_HIGH == eVIP_DID))
        {
            settings.beginGroup("X451");
        }
        else if (CVariantControlEnum::VIP_DID_HU_NEXON_LEVEL_B_VAVE == eVIP_DID
                 || CVariantControlEnum::VIP_DID_HU_NEXON_MCE == eVIP_DID)
        {
            settings.beginGroup("X104VAVE");
        }
        else
        {
            settings.beginGroup("X445");
        }

        mSWindowDimensions.mRootWindowWidth = settings.value("ROOT_WINDOW_WIDTH", DEFAULT_SCREEN_WIDTH).toInt();
        mSWindowDimensions.mRootWindowHeight = settings.value("ROOT_WINDOW_HEIGHT", DEFAULT_SCREEN_HEIGHT).toInt();
        mSWindowDimensions.mRootWindowX = settings.value("ROOT_WINDOW_X", 0).toInt();
        mSWindowDimensions.mRootWindowY = settings.value("ROOT_WINDOW_Y", 0).toInt();

        mSWindowDimensions.mNotificationWindowWidth = settings.value("NOTIFICATION_WINDOW_WIDTH", 560).toInt();
        mSWindowDimensions.mNotificationWindowHeight = settings.value("NOTIFICATION_WINDOW_HEIGHT", 92).toInt();
        mSWindowDimensions.mNotificationWindowX = settings.value("NOTIFICATION_WINDOW_X", 120).toInt();
        mSWindowDimensions.mNotificationWindowY = settings.value("NOTIFICATION_WINDOW_Y", 390).toInt();

        mSWindowDimensions.mVoiceAlertWindowWidth = settings.value("VOICE_ALERT_WINDOW_WIDTH", 800).toInt();;
        mSWindowDimensions.mVoiceAlertWindowHeight = settings.value("VOICE_ALERT_WINDOW_HEIGHT", 50).toInt();;
        mSWindowDimensions.mVoiceAlertWindowX = settings.value("VOICE_ALERT_WINDOW_X", 200).toInt();;
        mSWindowDimensions.mVoiceAlertWindowY = settings.value("VOICE_ALERT_WINDOW_Y", 0).toInt();;

        settings.endGroup();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s file %s does not exist", __FUNCTION__, settings.fileName().toStdString().data());
    }
}

void CHMIApplication::createRootWindow()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s", __FUNCTION__);

    m_pRootWindow = new QQuickWindow();
    m_pRootWindow->setWidth(mSWindowDimensions.mRootWindowWidth);
    m_pRootWindow->setHeight(mSWindowDimensions.mRootWindowHeight);
    m_pRootWindow->setX(mSWindowDimensions.mRootWindowX);
    m_pRootWindow->setY(mSWindowDimensions.mRootWindowY);
#ifndef PLATFORM_WIN32
    m_pRootWindow->setFlags(Qt::FramelessWindowHint);
#endif
    m_pRootWindow->setColor(Qt::transparent);
    m_pRootWindow->show();
    m_pRootWindow->create();
    m_pRootWindow->setTitle("X451-HMI");
    mParent = m_pRootWindow->contentItem();
    mfw.setRootObject(mParent);
}

void CHMIApplication::createNotificationWindow()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s", __FUNCTION__);
    m_pNotificationWindow = new QQuickWindow();
    m_pNotificationWindow->setWidth(mSWindowDimensions.mNotificationWindowWidth);
    m_pNotificationWindow->setHeight(mSWindowDimensions.mNotificationWindowHeight);
    m_pNotificationWindow->setX(mSWindowDimensions.mNotificationWindowX);
    m_pNotificationWindow->setY(mSWindowDimensions.mNotificationWindowY);
    m_pNotificationWindow->setColor(Qt::transparent);
    /* The notification window is used only for output (displaying notifications) and does not take input
        * hence setting flag
       */
    m_pNotificationWindow->setFlag(Qt::Window);
    m_pNotificationWindow->setFlags(Qt::WindowTransparentForInput);
    m_pNotificationWindow->setTitle("X451-HMI-Notification");
#ifndef PLATFORM_WIN32
    m_pNotificationWindow->setFlags(Qt::FramelessWindowHint);
#endif
    m_pNotificationWindow->show();
    m_pNotificationWindow->create();
    // Calling setMask before creating the window has no effect hence making the call here
    m_pNotificationWindow->setMask(QRegion(mSWindowDimensions.mNotificationWindowX, mSWindowDimensions.mNotificationWindowY,
                                           mSWindowDimensions.mNotificationWindowWidth, mSWindowDimensions.mNotificationWindowHeight));
    mfw.setNotificationRootObject(m_pNotificationWindow->contentItem());
}

void CHMIApplication::createVoiceAlertWindow()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s", __FUNCTION__);

    m_pVoiceAlertWindow = new QQuickWindow();
    m_pVoiceAlertWindow->setWidth(mSWindowDimensions.mVoiceAlertWindowWidth);
    m_pVoiceAlertWindow->setHeight(mSWindowDimensions.mVoiceAlertWindowHeight);
    m_pVoiceAlertWindow->setX(mSWindowDimensions.mVoiceAlertWindowX);
    m_pVoiceAlertWindow->setY(mSWindowDimensions.mVoiceAlertWindowY);
    m_pVoiceAlertWindow->setColor(Qt::transparent);
    m_pVoiceAlertWindow->setFlag(Qt::Window);
    /*
     * The Voice Alert window is used only for output (displaying notifications) and does not take input
     * hence setting flag
     */
    m_pVoiceAlertWindow->setFlags(Qt::WindowTransparentForInput);
    m_pVoiceAlertWindow->setTitle("X451-HMI-VOICE-ALERT");
#ifndef PLATFORM_WIN32
    m_pVoiceAlertWindow->setFlags(Qt::FramelessWindowHint);
#endif
    m_pVoiceAlertWindow->show();
    m_pVoiceAlertWindow->create();
    // Calling setMask before creating the window has no effect hence making the call here
    m_pVoiceAlertWindow->setMask(QRegion(mSWindowDimensions.mVoiceAlertWindowX, mSWindowDimensions.mVoiceAlertWindowY,
                                         mSWindowDimensions.mVoiceAlertWindowWidth, mSWindowDimensions.mVoiceAlertWindowHeight));
    mfw.setVoiceAlertRootObject(m_pVoiceAlertWindow->contentItem());
}

void CHMIApplication::createHMIApplications()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CHMIApplication::onCreated");

    /*
     * Creating the VariantControlApplication first since if would provide the EOL parameters to the various
     * applications and also state machine. Hence needs to be created before the state machine so that we can
     * provide it the various DID's
     */
    new CVariantControlApplication();

    //Instantiate common HMI components here
    new CHardkeyEventHandler();

    new CVoiceAlertsEventHandler();
    CVoiceAlertsAdaptor::getInstance();

    CPersistencyAdaptor::getInstance(); //Persistency service flow

    new CParkAssistApplication();

    CPowerModeAdaptor::getInstance();
    CDateAndTimeAdaptor::getInstance();
    CDisplayManagerAdaptor::getInstance();
    CICCastAdaptor::getInstance();
    new CAudioApplication();
    //end

    //Instantiate HMI applications here
    new CStartupAnim();
    new CMediaOffApplication();
    new CTunerApplication();
    new CMediaApplication();
    new CPhoneApplication();
    new CDriveNextApplication();
    new CW3WApplication();
    new CDoodleApplication();
    new CHomeApplication();
    new CSetupApplication();
    new CDrawersApplication();
    new CSoftwareUpdateApplication();
    new CAndroidAutoApplication();
    new CAppleCarPlayApplication();
    new CVRApplication();
    new CRCAApplication();

    new CIntrospectionApplication();
    // This is not an CBaseApplication derived class. Acts just as a creator class for the adaptor and eventHandler
    new CHVACApplication();
    new CVersionManagerApplication();
    new CDiagnosticApplication();
    new CLayerManagerApplication();
    new CEnggApplication();
    new CSoundDemoApplication();

    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CHMIApplication::onCreated");

    connect(CAudioAdaptor::getInstance(),&CAudioAdaptor::sigUpdateAudioPluginProxyAvailability,this, &CHMIApplication::sltUpdateAudioPluginProxyAvailability);

    connect(&mfw,SIGNAL(sigBeginScreenLoading()),this, SLOT(sltScreenAboutToLoad()));

#ifndef PLATFORM_WIN32
    sd_notify(0,"READY=1");
#endif
}

#if !defined(PLATFORM_WIN32) && !defined(PLATFORM_LINUX_X86)

void CHMIApplication::startNanoMsgServiceThread()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s",__FUNCTION__);
    m_pHMINanoMsgServiceThread = new CHMINanoMsgService();
    connect(m_pHMINanoMsgServiceThread, &CHMINanoMsgService::sigProcessNanoMsg, this, &CHMIApplication::sltProcessNanoMsg,Qt::QueuedConnection);
    connect(m_pHMINanoMsgServiceThread, &CHMINanoMsgService::finished, m_pHMINanoMsgServiceThread, &QObject::deleteLater);
    m_pHMINanoMsgServiceThread->start();
}

void CHMIApplication::sltProcessNanoMsg(int iNanoMsg)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, nano msg: %d",__FUNCTION__, iNanoMsg);
    ENanoMsgId eACKMsg = ENANOMSG_INVALID;
    // Logic to handle the various nano msg
    switch(iNanoMsg)
    {
    case ENANOMSG_REV_ENGAGE:
    case ENANOMSG_REV_DISENGAGE:
        // inform PDC of reverse gear status and send ACK
        eACKMsg = static_cast<ENanoMsgId>(CParkAssistAdaptor::getInstance()->updateReverseGearInfo(iNanoMsg));
        break;
    case ENANOMSG_HMI_ANMIATION_STARTED:
        // Animation is playing, send ACK
        //Set audioOff state ON
        m_bIsAnimationPlaying = true;
        CAudioAdaptor::getInstance()->setAudioOff(true);
        eACKMsg = ENANOMSG_HMI_ANMIATION_STARTED_ACK;
        break;
    case ENANOMSG_HMI_ANMIATION_STOPPED:
        // Animation has stopped, send ACK
        //Set audioOff state OFF
        m_bIsAnimationPlaying = false;
        CAudioAdaptor::getInstance()->setAudioOff(false);
        eACKMsg = ENANOMSG_HMI_ANMIATION_STOPPED_ACK;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s, %d nano message not handled", __FUNCTION__, iNanoMsg);
    }
    if (ENANOMSG_INVALID != eACKMsg)
    {
        int iReturn = SendNanoMessage(CHMINanoMsgService::getNanoMsgSocketID(), eACKMsg);
        if (-1 == iReturn)
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_MAIN, "%s: Nano Msg hand shake failed.", __FUNCTION__);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s: Nano Msg hand shake successful, message sent",__FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s: eACKMsg receveid as -1",__FUNCTION__);
    }
}

#endif

void CHMIApplication::sltUpdateAudioPluginProxyAvailability(bool bAvailability)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s bAvailability: %d, AnimationPlaying: %d ", __FUNCTION__, bAvailability, m_bIsAnimationPlaying);
    // If audio proxy has become available and startup animation is not playing call setAudioOff(off)
    if ((true == bAvailability) && (false == m_bIsAnimationPlaying))
    {
        //Set audioOff state OFF
        CAudioAdaptor::getInstance()->setAudioOff(false);
    }
}

void CHMIApplication::sltScreenAboutToLoad()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s",__FUNCTION__);
    emit sigScreenAboutToLoad();
}

void CHMIApplication::onCreated(QQuickItem *rootObject)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, __FUNCTION__);
    mfw.setRootObject(rootObject);
}

void CHMIApplication::initHmi()
{
    //Need to use singleShot timer due to the SM limitation of calling 2 runcycles one after another
    QTimer::singleShot(10,this,SLOT(updatePowerModeToSM()));

    /* This method will be invoked when system enters into early wake up state.
     * In reduced CAN mode HMI will always be switched to transparent screen.
    */
    LOG_WARNING(Log::e_LOG_CONTEXT_MAIN,"%s loading ScnTransparent.qml", __FUNCTION__);
    loadScreen("qrc:/QML/Common/ScnTransparent.qml");

    CPopupManager::getInstance()->closeAllPopups();
}

void CHMIApplication::updatePowerModeToSM()
{
#ifdef PLATFORM_LINUX_X86
    // These changes are so that the simulation works on linux desktop
    CPowerModeAdaptor::getInstance().powerModeChanged(CPowerModeEnums::VPM_ACTIVE);
#else

    if(true == CParkAssistAdaptor::getInstance()->reverseGearStatus())
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MAIN,"%s Entering early PDC mode", __FUNCTION__);
        /* Feeding the latest powermode to the state machine. */
        CHMIMain::getSM()->getSCI_Nsm()->set_currentPowerMode(CPowerModeAdaptor::getInstance().getPowerModeStatus());
        CHMIMain::getSM()->raise_evPdcActivated();
    }
    else
    {
        //This is to change "Early wake state" in State machine based on current power mode
        CPowerModeAdaptor::getInstance().powerModeChanged(CPowerModeAdaptor::getInstance().getPowerModeStatus());
    }
#endif
}

void CHMIApplication::loadScreen(QString qmlFilePath)
{
    CBaseApplication::loadScreen(qmlFilePath);
}

void CHMIApplication::raiseSMEvent(const QString &name, const QVariant &data)
{
    Q_UNUSED(data);
    // Generic back handling from screens
    if (name == "back")
    {
        mfw.doBack();
    }
    else if (name == "Home")
    {
        CHMIMain::getSM()->raise_evHomeActivated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s, Unhandled value: name:%s, data:%s", __FUNCTION__, name.toStdString().c_str(), data.toString().toStdString().c_str());
    }
}

int CHMIApplication::getListTopItemIndex()
{
    return mfw.getListTopItemIndex();
}

void CHMIApplication::updateTopIndex(int iTopIndex)
{
    mfw.updateTopIndex(iTopIndex);
}

QString CHMIApplication::invTruncateText(QString strText, int iTruncateLength, QString strAppendedAtEnd)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s, strText:%s, iTruncateLength:%d", __FUNCTION__, strText.toStdString().c_str(), iTruncateLength);
    QString strTruncatedString = "";
    if (iTruncateLength <= strAppendedAtEnd.length())
    {
        strTruncatedString = strText;
        LOG_WARNING(Log::e_LOG_CONTEXT_MAIN,"%s, iTruncateLength too small", __FUNCTION__);
    }
    else if (strText.length() > iTruncateLength)
    {
        strTruncatedString = strText.left(iTruncateLength - strAppendedAtEnd.length()) + strAppendedAtEnd;
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s, strTruncatedString:%s", __FUNCTION__, strTruncatedString.toStdString().c_str());
    }
    else
    {
        strTruncatedString = strText;
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s, No need to truncate as strText length not big enough", __FUNCTION__);
    }
    return strTruncatedString;
}
