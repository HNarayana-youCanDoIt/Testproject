/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CDrawersAdaptor.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* This file is having the definition for Adaptor class of Drawers,
* This is used by QML files to get the information needs to show on view.
*/

#ifndef CDRAWERSADAPTOR_H
#define CDRAWERSADAPTOR_H

#include "logging.h"
#include "CHMIMain.h"
#include "CDrawersEnums.h"

// Drawers and Slide Bars States Strings, used in QML for state of drawers.

const QString  DRAWERS_STATE_HIDDEN_STRING = "Hidden";
const QString  DRAWERS_STATE_SHOW_WITH_ANIMATION_STRING = "ShowDrawersWithAnimation";
const QString  DRAWERS_STATE_SHOW_WITHOUT_ANIMATION_STRING = "ShowDrawersWithoutAnimation";
const QString  DRAWERS_STATE_HIDE_WITH_ANIMATION_STRING = "HideDrawersWithAnimation";
const QString  DRAWERS_STATE_HIDE_WITHOUT_ANIMATION_STRING = "HideDrawersWithoutAnimation";
const QString  DRAWERS_STATE_MINIMIZED_STRING = "Minimized";
const QString  DRAWERS_STATE_MAXIMIZED_STRING = "Maximized";
const QString  SLIDE_BARS_STATE_HIDDEN_STRING = "Hidden";
const QString  SHORTCUT_DRAWER_NAME_STRING = "ShortcutDrawer";
const QString  QAD_DRAWER_NAME_STRING = "QadDrawer";
const QString  SOURCE_DRAWER_NAME_STRING = "SourceDrawer";
const QString  DRAWERS_NAME_STRING = "Drawers";

/**
 * @class CDrawersAdaptor
 * @brief The CDrawersAdaptor class of Drawers, This is used by QML
 *        files to get the information needs to show on view.
 */
class CDrawersAdaptor : public QObject
{
    Q_OBJECT

    /*
     * Property for maximize minimize animation duration.
     */
    Q_PROPERTY(int drawersMaximizeMinimizeAnimationDuration
               READ drawersMaximizeMinimizeAnimationDuration
               NOTIFY sigDrawersMaximizeMinimizeAnimationDurationChanged)
    /*
     * Property for show hide animation duration.
     */
    Q_PROPERTY(int drawersShowHideAnimationDuration
               READ drawersShowHideAnimationDuration
               NOTIFY sigDrawersShowHideAnimationDurationChanged)

    /*
     * Drawer's property ==> "ShowDrawersWithAnimation",
     * "ShowDrawersWithoutAnimation", "HideDrawersWithAnimation",
     * "HideDrawersWithoutAnimation"
     */
    Q_PROPERTY(QString drawersState
               READ drawersState
               NOTIFY sigDrawersStateChanged)

    /*
     * Source Drawer's property
     */

    /*
     * Property for source Drawer State ==> "Minimize", "Maximaize".
     */
    Q_PROPERTY(QString srcDrawerState
               READ srcDrawerState
               NOTIFY sigSrcDrawerStateChanged)


    /*
     * Property for shortcut Drawer State ==> "Minimize", "Maximaize".
     */
    Q_PROPERTY(QString shortcutDrawerState
               READ shortcutDrawerState
               NOTIFY sigShortcutDrawerStateChanged)

    /*
     *  Setup Drawer's Property
     */

    /*
     * Property for Home Button State.
     */
    Q_PROPERTY(bool enableHomeButton
               READ enableHomeButton
               NOTIFY sigEnableHomeButtonChanged)

    /*
     * Property for Settings Button State.
     */
    Q_PROPERTY(bool enableSettingsButton
               READ enableSettingsButton
               NOTIFY sigEnableSettingsButtonChanged)


    /*
     * Hvac Drawer's property
     */
    /*
     * Property for HVAC Drawer State ==> "Minimize", "Maximaize", "Collapsed",
     * "Expanded".
     */
    Q_PROPERTY(QString hvacDrawerState
               READ hvacDrawerState
               NOTIFY sigHvacDrawerStateChanged)

    /*
     * QAD Drawer's property
     */
    /*
     * Property for QAD Drawer State ==> "Minimize", "Maximaize",
     * "Collapsed", "Expanded".
     */
    Q_PROPERTY(QString qadDrawerState
               READ qadDrawerState
               NOTIFY sigQadDrawerStateChanged)
	/*
     * Property for notification overlay state.
     */
    Q_PROPERTY(QString notificationOverlayState READ notificationOverlayState NOTIFY sigNotificationOverlayStateChanged)

    /*
     * Property for Current Active Notification Overlay type.
     */
    Q_PROPERTY(CDrawersEnums::ENotificationTypes activeNotification READ activeNotification WRITE setActiveNotification NOTIFY sigActiveNotificationChanged)

    /*
     * Property for bool variable m_bShowMuteStatus
     */
    Q_PROPERTY(bool showMuteStatus READ showMuteStatus NOTIFY sigShowMuteStateChanged)

    /*
     * Property to get Status Bar availability on screen.
     */
    Q_PROPERTY(bool allowStatusBarOnScreen READ allowStatusBarOnScreen NOTIFY sigAllowStatusBarOnScreenChanged)

public:
    /**
    * @brief	CDrawersAdaptor::getInstance is static method used to get
    *           instance of singleton class CDrawersAdaptor
    * @param	void.
    * @return	CDrawersAdaptor pointer.
    **/
    static CDrawersAdaptor * getInstance();

    /*
     * Drawer's public functions
     */
    /**
    * @brief	CDrawersAdaptor::drawersState is getter/read method for
    *           drawersState property
    * @param	void.
    * @return	QString.
    **/
    QString drawersState()  const
    {
        return m_strDrawersState;
    }

    /**
    * @brief	isDrawerMaximized: Method to be invoked to know whether the
    *           drawer(Shortcut or QAD) is maximized or not.
    * @param	void
    * @return	return whether the drawer is maximized(Shortcut or QAD) or not.
    *           TRUE - drawer is maximized, FALSE otherwise
    **/
    bool isDrawerMaximized();

    /**
    * @brief	CDrawersAdaptor::setDrawersState is setter method for
    *           drawersState property
    * @param	const QString &strDrawersState: Drawers state
    * @return	void.
    **/
    void setDrawersState(const QString &strDrawersState);

    /*
     * Source Drawer's public functions
     */

    /**
    * @brief	CDrawersAdaptor::srcDrawerState is getter/read method for
    *           srcDrawerState property
    * @param	void.
    * @return	QString.
    **/
    QString srcDrawerState()   const
    {
        return m_strSrcDrawerState;
    }

    /**
    * @brief	CDrawersAdaptor::setDrawersState is setter/write method for
    *           srcDrawerState property
    * @param	const QString &strSrcDrawerState: Source Drawer's State.
    * @return	void.
    **/
    void setSrcDrawerState(const QString &strSrcDrawerState);


    /**
    * @brief	CDrawersAdaptor::shortcutDrawerState is getter/read method for
    *           shortcutDrawerState property
    * @param	void.
    * @return	QString: current state of the shortcut drawer
    **/
    QString shortcutDrawerState()   const
    {
        return m_strShortcutDrawerState;
    }

    /**
    * @brief	CDrawersAdaptor::setShortcutDrawerState is setter/write method for
    *           shortcutDrawerState property
    * @param	const QString &strShortcutDrawerState: Shortcut Drawer's State.
    * @return	void.
    **/
    void setShortcutDrawerState(const QString &strShortcutDrawerState);

    /*
     *  Setup Drawer's public functions
     */
    /**
    * @brief	CDrawersAdaptor::enableHomeButton is getter/read method for
    *           enableHomeButton property
    * @param	void.
    * @return	bool.
    **/
    bool enableHomeButton() const
    {
        return m_bEnableHomeButton;
    }

    /**
    * @brief	CDrawersAdaptor::setEnableHomeButton is setter/write method for
    *           enableHomeButton property
    * @param	const bool &bEnableHomeButton: true if enable else false.
    * @return	void.
    **/
    void setEnableHomeButton(const bool &bEnableHomeButton);

    /**
    * @brief	CDrawersAdaptor::enableSettingsButton is getter/read method for
    *           enableSettingsButtonenableSettingsButton property
    * @param	void.
    * @return	bool: true if enable else false
    **/
    bool enableSettingsButton() const
    {
        return m_bEnableSettingsButton;
    }

    /**
    * @brief	CDrawersAdaptor::setEnableSettingsButton is setter/write method
    *           for enableSettingsButton property
    * @param	const bool &bEnableSettingsButton: true if enable else false
    * @return	void.
    **/
    void setEnableSettingsButton(const bool &bEnableSettingsButton);

    /*
     * Hvac Drawer's public functions
     */

    /**
    * @brief	CDrawersAdaptor::hvacDrawerState is getter/read method for
    *           hvacDrawerState property
    * @param	void.
    * @return	QString: HVAC Drawer's State.
    **/
    QString hvacDrawerState() const
    {
        return m_strHvacDrawerState;
    }

    /**
    * @brief	CDrawersAdaptor::setHvacDrawerState is setter/write method for
    *           srcDrawerState property
    * @param	const QString &strHvacDrawerState : HVAD Drawer's State.
    * @return	void.
    **/
    void setHvacDrawerState(const QString &strHvacDrawerState);

    /*
     * QAD Drawer's public functions
     */

    /**
    * @brief	CDrawersAdaptor::qadDrawerState is getter/read method for
    *           qadDrawerState property
    * @param	void.
    * @return	QString: qad Drawer's State
    **/
    QString qadDrawerState() const
    {
        return m_strQadDrawerState;
    }

    /**
    * @brief	CDrawersAdaptor::setQadDrawerState is setter/write method for
    *           qadDrawerState property
    * @param	const QString &strQadDrawerState: QAD Drawer's State
    * @return	void.
    **/
    void setQadDrawerState(const QString &strQadDrawerState);

    /**
    * @brief	CDrawersAdaptor::drawersMaximizeMinimizeAnimationDuration is
    *           getter/read method for drawersMaximizeMinimizeAnimationDuration
    *           property.
    * @param	void.
    * @return	int: Drawer's Maximize Minimize Animation Duration.
    **/
    int drawersMaximizeMinimizeAnimationDuration() const { return m_iDrawersMaximizeMinimizeAnimationDuration;}

    /**
    * @brief	CDrawersAdaptor::setDrawersMaximizeMinimizeAnimationDuration is
    *           setter/write method for drawersMaximizeMinimizeAnimationDuration
    *           property
    * @param	const int &iMaximizedMinimizedAnimationDuration: Drawer's
    *           Maximize Minimize Animation Duration.
    * @return	void.
    **/
    void setDrawersMaximizeMinimizeAnimationDuration(const int &iMaximizedMinimizedAnimationDuration);

    /**
    * @brief	CDrawersAdaptor::drawersShowHideAnimationDuration is getter/read
    *           method for drawersShowHideAnimationDuration property.
    * @param	void.
    * @return	int: Drawer's Show Hide Animation Duration.
    **/
    int drawersShowHideAnimationDuration() const { return m_iDrawersShowHideAnimationDuration;}

    /**
    * @brief	CDrawersAdaptor::setDrawersShowHideAnimationDuration is
    *           setter/write method for drawersShowHideAnimationDuration
    *           property.
    * @param	const int &iShowHideAnimationDuration: Drawer's Show Hide
    *           Animation Duration.
    * @return	void.
    **/
    void setDrawersShowHideAnimationDuration(const int &iShowHideAnimationDuration);

    /**
    * @brief    handleHardKeys Funtion to handle hardkey as per drawer specifications.
    * @param    eKey the key on which the action is triggered.
    * @param    eState state of the key on which the action is triggered.
    * @return   true if an action was taken false otherwise.
    */
    bool handleHardKeys(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState);

    /**
     * @brief closeDrawers - Function to close the drawers which are in maximized state.
     * @param void
     * @return true if a drawer is closed else false
     */
    bool closeDrawers();

    /**
     * @brief   setShowMuteStatus: This function is used to set the
     *          variable m_bShowMuteStatus, which is used to decide
     *          that the Mute/UnMute status needs to be shown on screen or not.
     * @param   bShowMuteStatus: true if Mute status needs to shown else false.
     * @return  void.
     */
    void setShowMuteStatus(bool bShowMuteStatus);

	/**
     * @brief   notificationOverlayState: getter function for property notificationOverlayState.
     * @param   void.
     * @return  notificationOverlayState.
     */
    QString notificationOverlayState() const
    {
        return m_strNotificationOverlayState;
    }

    /**
     * @brief   setNotificationOverlayState: Setter for property notificationOverlayState.
     * @param   strNotificationOverlayState: Notification overlay state.
     * @return  void.
     */
    void setNotificationOverlayState(const QString &strNotificationOverlayState);

    /**
     * @brief activeNotification
     * @return
     */
    CDrawersEnums::ENotificationTypes activeNotification() const
    {
        return m_eActiveNotification;
    }

    /**
     * @brief setActiveNotification
     * @param eActiveNotification
     */
    void setActiveNotification(CDrawersEnums::ENotificationTypes eActiveNotification);

    /**
    * @brief	CDrawersAdaptor::showMuteStatus is getter/read method for bShowMuteStatus property
    * @param	void.
    * @return	bool: Value indicating if Mute bar should be displayed or not.
    **/
    bool showMuteStatus() const { return m_bShowMuteStatus; }

    /**
    * @brief	CDrawersAdaptor::allowStatusBarOnScreen is getter/read method for allowStatusBarOnScreen property
    * @param	void.
    * @return	bool: TRUE when Status bar is allowed on screen otherwise FALSE.
    **/
    bool allowStatusBarOnScreen();

    /**
    * @brief	CDrawersAdaptor::setAllowStatusBarOnScreen is setter/write method for allowStatusBarOnScreen property
    * @param	bool: TRUE when Status bar is allowed on screen otherwise FALSE.
    * @return	void.
    **/
    void setAllowStatusBarOnScreen(bool bStatus);

signals:

    /**
    * @brief	CDrawersAdaptor::sigDrawersStateChanged is a notify signal
    *           to notify drawersState property changes to qml
    * @param	void.
    * @return	void.
    **/
    void sigDrawersStateChanged();

    /*
     *  Source Drawer's Signals
     */

    /**
    * @brief	CDrawersAdaptor::sigSrcDrawerStateChanged is a notify signal to
    *           notify SrcDrawerState property changes to qml.
    * @param	void.
    * @return	void.
    **/
    void sigSrcDrawerStateChanged();

    /**
    * @brief	CDrawersAdaptor::sigShortcutDrawerStateChanged is a notify
    *           signal to notify ShortcutDrawerState property changes to qml.
    * @param	void.
    * @return	void.
    **/
    void sigShortcutDrawerStateChanged();

    /*
     *  Setup Drawer's Signals
     */

    /**
    * @brief	CDrawersAdaptor::sigEnableHomeButtonChanged is a notify signal
    *           to notify enableHomeButton property changes to qml.
    * @param	void.
    * @return	void.
    **/
    void sigEnableHomeButtonChanged();

    /**
    * @brief	CDrawersAdaptor::sigEnableBackButtonChanged is a notify signal
    *           to notify enableBackButton property changes to qml.
    * @param	void.
    * @return	void.
    **/
    void sigEnableBackButtonChanged();

    /**
    * @brief	CDrawersAdaptor::sigEnableSettingsButtonChanged is a notify
    *           signal to notify enableSettingsButton property changes to qml.
    * @param	void.
    * @return	void.
    **/
    void sigEnableSettingsButtonChanged();

    /*
     *  Hvac Drawer's Signals
     */

    /**
    * @brief	CDrawersAdaptor::sigHvacDrawerStateChanged is a notify signal
    *           to notify hvacDrawerState property changes to qml.
    * @param	void.
    * @return	void.
    **/
    void sigHvacDrawerStateChanged();

    /*
     *  QAD Drawer's Signals
     */

    /**
    * @brief	CDrawersAdaptor::sigQadDrawerStateChanged is a notify signal to
    *           notify qadDrawerState property changes to qml.
    * @param	void.
    * @return	void.
    **/
    void sigQadDrawerStateChanged();

    /**
    * @brief	CDrawersAdaptor::sigDrawersMaximizeMinimizeAnimationDurationChanged
    *           is a notify signal to notify drawersMaximizeMinimizeAnimationDuration
    *           property changes to qml.
    * @param	void.
    * @return	void.
    **/
    void sigDrawersMaximizeMinimizeAnimationDurationChanged();

    /**
    * @brief	CDrawersAdaptor::sigDrawersShowHideAnimationDurationChanged is a
    *           notify signal to notify drawersShowHideAnimationDuration property
    *           changes to qml.
    * @param	void.
    * @return	void.
    **/
    void sigDrawersShowHideAnimationDurationChanged();

	/**
     * @brief   sigNotificationOverlayStateChanged: Signal to notify the change in notificationOverlayState
     *          property.
     * @param   void.
     * @return  void.
     */
    void sigNotificationOverlayStateChanged();

    /**
     * @brief sigActiveNotificationChanged: Signal to notify the change in activeNotification
     *        property.
     */
    void sigActiveNotificationChanged();

    /**
    * @brief	CDrawersAdaptor::setShowMuteStateChanged is used
    *           to notify m_bShowMuteStatus property changes to qml.
    **/
    void sigShowMuteStateChanged();

    /**
    * @brief    CDrawersAdaptor::sigAllowStatusBarOnScreenChanged signal to handle change events for allowStatusBarOnScreen property
    * @param void.
    * @return void.
    **/
    void sigAllowStatusBarOnScreenChanged();

    /**
     * @brief sigChangeMuteStatusOnScreenExit: This signal will emit to change the mute status when the exit of any required
     *        screen will be called.
     * @param void.
     * @return void.
     */
    void sigChangeMuteStatusOnScreenExit();

    /**
     * @brief   sigHideNotificationOverlay: This signal is used to hide the Notification Overlays.
     * @param   void.
     * @return  void.
     */
    void sigHideNotificationOverlay();

    /**
     * @brief sigDateTimeRefresh - Signal to Notify that m_objDateTimeTimer is timedout
     *        Using this Signal, Date and Time can be updated wherever needed.
     * @param void
     * @return void
     */
    void sigDateTimeRefresh();

private slots:
    /**
     * @brief sltMuteStatusChanged: This function is called whenever Mute status is changed.
     *        This slot function handles shows VolumeBar on MuteStatus change during
     *        AA/Carplay Projection
     * @param void
     * @return void
     */
    void sltMuteStatusChanged();

    /**
     * @brief sltNotificationLayerVisibilityState slot is called with the notification layer visibility state signal is emitted
     * @param bVisibilityState the current visibility state
     * @return void
     */
    void sltNotificationLayerVisibilityState(bool bVisibilityState);

    /**
     * @brief sltChangeMuteStatusOnScreenExit: slot to change the visibility status for Mute/Volume bar.
     * @param void.
     * @return void.
     */
    void sltChangeMuteStatusOnScreenExit();

    /**
     * @brief   sltHideNotificationOverlay: This function hides all the Notification Overlays (Volume and HVAC)
     * @param   void.
     * @return  void.
     */
    void sltHideNotificationOverlay();

    /**
     * @brief sltDateTimeTimeout - Method is called when m_objDateTimeTimer timeout signal is received
     * @param void
     * @return void
     */
    void sltDateTimeTimeout();

private:
    ~CDrawersAdaptor();

    /**
    * @brief	CDrawersAdaptor::CDrawersAdaptor private constructor for singleton
    *           class CDrawersAdaptor.
    * @param	QObject parent.
    * @return	NA.
    **/
    explicit CDrawersAdaptor(QObject *pParent = nullptr);

    /**
     * @brief   connectSignals: This function connects the signals of another
     *          adaptors.
     * @param   void.
     * @return  void.
     */
    void connectSignals();

    /**
     * @brief   disconnectSignals: This function disConnects the signals of
     *          another adaptors.
     * @param   void.
     * @return  void.
     */
    void disconnectSignals();

    /*
     * Singolton Instance pointer for CDrawersAdaptor
     */
    static CDrawersAdaptor *m_pDrawersAdaptor;

    /*
     *  This variable holds Drawer's state.
     *  The states an be ==> "ShowDrawersWithAnimation",
     *  "ShowDrawersWithoutAnimation", "HideDrawersWithAnimation",
     *  "HideDrawersWithoutAnimation"
     */
    QString m_strDrawersState;

    /*
     *  Source Drawer's Local Variables
     */

    /*
     * This variable holds the Source Drawer's State.
     */
    QString m_strSrcDrawerState;

    /*
     * This variable holds the Shortcut Drawer's State.
     */
    QString m_strShortcutDrawerState;

    /*
     *  Setup Drawer's Local Variables
     */

    /*
     * This variable holds the state of Home button.
     * true ==> If enable, else false
     */
    bool m_bEnableHomeButton;

    /*
     * This variable holds the state of Settings button.
     * true ==> If enable, else false
     */
    bool m_bEnableSettingsButton;


    /*
     *  Hvac Drawer's Local Variables
     */

    /*
     * This variable holds the HVAC Drawer's State.
     */
    QString m_strHvacDrawerState;


    /*
     *  Qad Drawer's Local Variables
     */

    /*
     * This variable holds the QAD Drawer's State.
     */
    QString m_strQadDrawerState;

    /*
     * Volume Bar's Local Variables.
     */

    /**
     * @brief m_iDrawersMaximizeMinimizeAnimationDuration: This variable holds
     *        the maximize minimize animation duration.
     */
    int m_iDrawersMaximizeMinimizeAnimationDuration;

    /**
     * @brief m_iDrawersShowHideAnimationDuration: This variable holds the show
     *        hide animation duration.
     */
    int m_iDrawersShowHideAnimationDuration;

    /**
     * @brief m_bShowMuteStatus: This variable is used to decide that
     * the Mute status needs to be show or not, like On Projection, video,
     * Picture viewer screen, we need to show both Mute and Unmute status. So
     * this variable is used to show the status. This variable needs to be set
     * true, If any state wants to show the Mute unmute status on it, and on exit
     * of that state, this needs to be reset as false.
     */
    bool m_bShowMuteStatus;

    /**
     * @brief m_bAllowStatusBarOnScreen: veriable to hold value for property allowStatusBarOnScreen.
     */
    bool m_bAllowStatusBarOnScreen;

    /**
     * @brief m_strNotificationOverlayState: Variable to hold the state (Show/Hide) of
     *        Notification overlay.
     */
    QString m_strNotificationOverlayState;

    /**
     * @brief m_eActiveNotification: This variable holds the active notification.
     */
    CDrawersEnums::ENotificationTypes m_eActiveNotification;

    /**
     * @brief m_objDateTimeTimer - Date and Time Timer object.
     *       The timer is used to update date and time in drawers and in Media Off screen
     */
    QTimer m_objDateTimeTimer;
};

#endif // CDRAWERSADAPTOR_H
