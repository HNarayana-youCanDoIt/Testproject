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

#ifndef CHMIAPPLICATION_H
#define CHMIAPPLICATION_H

#include "HMIIncludes.h"
#include "CHMIApplicationEnums.h"

#ifdef USE_WAYLAND_IVI
#include "WaylandIVIController.h"
#endif

#if !defined(PLATFORM_WIN32) && !defined(PLATFORM_LINUX_X86)
class CHMINanoMsgService;
#endif

#define DEFAULT_SCREEN_WIDTH 800
#define DEFAULT_SCREEN_HEIGHT 480

class CHMIApplicationSM;
class CPopupManager;
using namespace std;

struct sHMIWindowDimensions
{
    sHMIWindowDimensions()
    {
        mRootWindowWidth = DEFAULT_SCREEN_WIDTH;
        mRootWindowHeight = DEFAULT_SCREEN_HEIGHT;
        mRootWindowX = mRootWindowY = 0;

        mNotificationWindowWidth = 560;
        mNotificationWindowHeight = 92;
        mNotificationWindowX = mNotificationWindowY = 0;

        mVoiceAlertWindowWidth = 800;
        mVoiceAlertWindowHeight = 50;
        mVoiceAlertWindowX = mVoiceAlertWindowY = 0;
    }
    // main window
    qint32 mRootWindowWidth;
    qint32 mRootWindowHeight;
    qint32 mRootWindowX;
    qint32 mRootWindowY;

    // notification window
    qint32 mNotificationWindowWidth;
    qint32 mNotificationWindowHeight;
    qint32 mNotificationWindowX;
    qint32 mNotificationWindowY;

    // voice alert window
    qint32 mVoiceAlertWindowWidth;
    qint32 mVoiceAlertWindowHeight;
    qint32 mVoiceAlertWindowX;
    qint32 mVoiceAlertWindowY;
};

/**
 * @brief The CHMIApplication class
 * Main class which creates the resources, adaptor, Qt windows and the state machine
 */
class CHMIApplication : public CBaseApplication
{
    Q_OBJECT
    Q_DISABLE_COPY(CHMIApplication)

    /*
     * Property to get Screen Aspect Ratio for current variant
     */
    Q_PROPERTY(double screenAspectRatio READ screenAspectRatio CONSTANT)

public :
    CHMIApplication(QQuickItem* parent);
    virtual ~CHMIApplication();

    /**
     * @brief initHMIWindow, creates the main hmi and notification windows, links with the LayerManager surface
     * creates the various HMI applications and loads the main UI and Notifcation qmls
     * @param void
     * @return void
     */
    void initHMIWindow();

    /**
     * @brief initHmi check the power mode and sends it to the state machine to start the welcome animation
     * @param void
     * @return void
     */
    void initHmi();

    /**
     * @brief getScreenWidth: Used to get Screen Width
     * @param void
     * @return int Screen Width.
     */
    int getScreenWidth() { return mSWindowDimensions.mRootWindowWidth; }

    /**
     * @brief getScreenHeight: Used to get Screen Height
     * @param void
     * @return int Screen Height.
     */
    int getScreenHeight(){ return mSWindowDimensions.mRootWindowHeight; }

public:
    /**
     * @brief onCreated - Function is called when the QML is loaded successfully
     * @param pRootObject - provides the created qml object as the root Object
     * @return void
     */
    virtual void onCreated(QQuickItem* pRootObject) override;

    /**
     * @brief loadScreen - Function is called to load the provide qml file onto the QQuickWindow
     * @param strQmlFilePath - provide qml file path
     * @return void
     */
    void loadScreen(QString strQmlFilePath) override;

    /**
     * @brief raiseSMEvent - Function is called from the QML file to raise an event on the State machine
     * Based on which there might be a screen transition or internal state change
     * @param strName - The name of the domain/module
     * @param varData - The name of the event/state we want the SM to be transitioned into
     */

    void raiseSMEvent(const QString & strName,const QVariant & varData) override;

    /**
     * @brief invTruncateText - Function is used to truncate given string with given length
     * @param strText - string to truncate
     * @param iTruncateLength - char length by which string needs to be truncated
     * @return QString - truncated string
     */
    Q_INVOKABLE QString invTruncateText(QString strText, int iTruncateLength = 20, QString strAppendedAtEnd = "...");

    /**
     * @brief getListTopItemIndex - Method called from GenericList.qml to get the index of item to displayed on top from screen history stack
     * @param void
     * @return int - index of item to be loaded on top of the list
     */
    Q_INVOKABLE int getListTopItemIndex();

    /**
     * @brief updateTopIndex - Method called from GenericList.qml to update the index of item currently displayed on top
     * @param int - Index of top item in the current list
     * @return void
     */
    Q_INVOKABLE void updateTopIndex(int iTopIndex);

    /**
    * @brief	This function will return Screen Aspect Ratio for current variant
    * @param	void.
    * @return	int: Screen Aspect Ratio for current variant
    */
    double screenAspectRatio()
    {
#if defined(PLATFORM_WIN32) || defined(PLATFORM_LINUX_X86)
        return 1.00;
#else
        return 0.93;
#endif
    }

signals:

    /**
     * @brief sigScreenAboutToLoad - Signal to be emitted from sltScreenAboutToLoad.
     * @param void
     * @return void
     */
    void sigScreenAboutToLoad();

public slots:
    /**
     * @brief updatePowerModeToSM function informs the update NSM state to the state machine
     * @param void
     * @return void
     */
    void updatePowerModeToSM();

#if !defined(PLATFORM_WIN32) && !defined(PLATFORM_LINUX_X86)
    /**
     * @brief sltProcessNanoMsg slot is called when we receive sigProcessNanoMsg from the nano msg service
     * @param iNanoMsg nano msg received from the client
     * @return void
     */
    void sltProcessNanoMsg(int iNanoMsg);
#endif

    /**
    * @brief	sltUpdateAudioPluginProxyAvailability This slot will update proxy availability data received from Audio Resource layer.
    * @param	bAvailablility: proxy availability true /false
    * @return	void
    */
    void sltUpdateAudioPluginProxyAvailability(bool bAvailability);

    /**
     * @brief sltScreenAboutToLoad - This slot will emit signal sigScreenAboutToLoad
     * @param void
     * @return void
     */
    void sltScreenAboutToLoad();


private:

    /**
     * @brief readAllWindowDimensionsFromConfig Read all the window dimensions from config file
     * @param void
     * @return void
     */
    void readAllWindowDimensionsFromConfig();

    /**
     * @brief createRootWindow function to create the main hmi window
     * @param void
     * @return void
     */
    void createRootWindow();

	
    /**
     * @brief createNotificationWindow: function to create the volume/hvac overlay notification window
     * @param void
     * @return void
     */
    void createNotificationWindow();

    /**
     * @brief createVoiceAlertWindow: function to create the Voice Alert overlay window
     * @param void
     * @return void
     */
    void createVoiceAlertWindow();

    /**
     * @brief createHMIApplications function to create the various hmi applications
     * @param void
     * @return void
     */
    void createHMIApplications();

#if !defined(PLATFORM_WIN32) && !defined(PLATFORM_LINUX_X86)
    /**
     * @brief startNanoMsgServiceThread Function starts the HMI nano message service thread
     * @param void
     * @return void
     */
    void startNanoMsgServiceThread();
#endif

private:

    QObject* rootObject;

    /** Pointer to the main hmi window */
    QQuickWindow* m_pRootWindow;
	
    /** Pointer to the volume/Hvac overlay notification window */
    QQuickWindow* m_pNotificationWindow;

    /** Pointer to the Voice Alert overlay window */
    QQuickWindow* m_pVoiceAlertWindow;

    /** pointer to the HMI state machine */
    CHMIApplicationSM* m_pHMIAppSM;

#if !defined(PLATFORM_WIN32) && !defined(PLATFORM_LINUX_X86)
    /** pointer to the hmi nano msg service */
    CHMINanoMsgService* m_pHMINanoMsgServiceThread;
#endif

#ifdef USE_WAYLAND_IVI
    WaylandIVIController* m_pWaylandIVICtrl;
#endif

    /** pointer to the Popup manager */
    CPopupManager* m_pPopupManager;

    /** Store information whether animation is playing or not */
    bool m_bIsAnimationPlaying;

    /** Struture for getting the window dimensions for the HMI windows based on variants */
    sHMIWindowDimensions mSWindowDimensions;
};

#endif // CHMIAPPLICATION_H
