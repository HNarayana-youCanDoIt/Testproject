/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CPopupManager.h
* @ingroup      HMIComponent
* @author       Rahul Madan
* CPopupManager Class definition which shall be used by all the HMI Modules to
*               show, close and request any inforrmation about the Popups
*/

#ifndef CPOPUPMANAGER_H
#define CPOPUPMANAGER_H

#include <QObject>
#include <QVector>
#include "logging.h"
#include "CPopupEnum.h"
#include "CPopupPropertyHandler.h"
#include "CHardKeyEnum.h"


class CPopupManagerSM;

/**
 * @class CPopupManager
 * @brief Class definition which shall be used by all the HMI Modules to
 *        show, close and request any inforrmation about the Popups
 */
class CPopupManager : public QObject
{
    Q_OBJECT

    /** Properties */

    /** Property hold the Popup Result */
    Q_PROPERTY(CPopupEnum::EPopupResult ePopupResult READ ePopupResult WRITE setPopupResult NOTIFY sigPopupResultChanged)

    /** Property hold the visibility state of notification popup */
    Q_PROPERTY(bool bNotificationVisible READ getBNotificationVisible WRITE setBNotificationVisible NOTIFY sigNotificationVisibilityChanged)

public:
    /**
     * @brief getInstance : To get the only instance of CPopupManager
     * @param void
     * @return CPopupManager&
     */
    static CPopupManager* getInstance();
    ~CPopupManager();

    /**
     * @brief showPopup : Method to be invoked by HMI modules to show popup
     * @param CPopupEnum::EPopupID ePopupId - ID of the popup to be shown
     * @return void
     */
    Q_INVOKABLE void showPopup(CPopupEnum::EPopupID ePopupId);

    /**
     * @brief closePopup : Method to be invoked by HMI modules to close popup
     *        Popup will get closed only after it's min. timeout through this popup.
     *        Modules should generally call this Method only
     * @param CPopupEnum::EPopupID ePopupId - ID of the popup to be closed
     * @return void
     */
    Q_INVOKABLE void closePopup(CPopupEnum::EPopupID ePopupId);

    /**
     * @brief isPopupAlive : Method to be invoked by HMI modules to check if any Popup is displayed over screen
     * @param void
     * @return bool - true if any popup is displayed over the screen, else false
     */
    Q_INVOKABLE bool isPopupAlive();

    /**
     * @brief invResetPopupTimer Method to be invoked by HMI modules to reset the currently displayed popups's timer
     * @param void
     * @return void
     */
    Q_INVOKABLE void invResetPopupTimer();

    /**
     * @brief isNotificationAlive : Method to be invoked by HMI modules to check if any Notification is displayed over screen
     * @param void
     * @return bool - true if any notification is displayed over the screen, else false
     */
    Q_INVOKABLE bool isNotificationAlive();

    /**
     * @brief closeAllPopups : Method to be invoked by HMI modules to close all the popups
     *        This method shall be called while entering modes like - ReducedCAN Power mode
     * @param void
     * @return void
     */
    Q_INVOKABLE void closeAllPopups();

    /**
     * @brief forceClosePopup : Method to be invoked by HMI modules to force close popup
     *        Through this method popup will be closed irrespective of it's min. timeout
     *        This method should be called in very specific cases only like -
     *        * On Popup Button Press*
     *        *On source change* etc.
     * @param CPopupEnum::EPopupID ePopupId - ID of the popup to be force closed
     * @return void
     */
    Q_INVOKABLE void forceClosePopup(const CPopupEnum::EPopupID ePopupId);

    /**
    * @brief handleHardKeys : Funtion to handle hardkey as per media specifications.
    * @param eKey the key on which the action is triggered.
    * @param eState state of the key on which the action is triggered.
    * @return  true if an action was taken false otherwise.
    */
    bool handleHardKeys(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState);

    /**
    * @brief handleRotary : Funtion to handle rotary on popups.
    * @param eKey the key on which the action is triggered.
    * @param eState state of the key on which the action is triggered.
    * @return void
    */
    void handleRotary(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState);

    /**
     * @brief showPendingNotification : Method to show pending Notification Popups
     *        This method shows the Notification popups that are currently present in the pending popups list
     * @param void
     * @return void
     */
    void showPendingNotification();

    /**
     * @brief showPendingPopup : Method to show pending Popups
     *        This method shows the Notification popups that are currently present in the pending popups list
     * @param void
     * @return void
     */
    void showPendingPopup();

    /**
     * @brief isPopupAllowed : Method to check if requested popup/notification is allowed to be displayed over active state(context) of HMI
     * @param CPopupEnum::ePopupID ePopupId - popup requested to be displayed
     * @return bool - true if ePopupId's applicable context array contains current active state(context) of HMI, else false
     */
    bool isPopupAllowed(CPopupEnum::EPopupID ePopupId);

    /**
     * @brief isPopupAllowed : Method to check if requested popup/notification is allowed to be displayed over active state(context) of HMI
     * @param CPopupEnum::ePopupID ePopupId - popup requested to be displayed
     * @return bool - true if ePopupId's applicable context array contains current active state(context) of HMI, else false
     */
    void checkPopupContext();

    /**
     * @brief closeOnTouch : Q_INVOKABLE Method to close popup on Touch Event outside the popup
     * @param void
     * @return void
     */
    Q_INVOKABLE void closeOnTouch();

    /**
     * @brief closeOnHardKey : Q_INVOKABLE Method to close popup on hardkey press.
     * @param void
     * @return void
     */
    Q_INVOKABLE void closeOnHardKey();

    /**
     * @brief getCurrentDisplayedPopup : Method to get value of mCurrentDisplayedPopup(which is the Id of the Popup currently being displayed on the screen)
     * @param void
     * @return CPopupEnum::EPopupID - current value of mCurrentDisplayedPopup
     */
    inline CPopupEnum::EPopupID getCurrentDisplayedPopup() { return m_eCurrentDisplayedPopup;}

    /**
     * @brief getCurrentDisplayedNotification : Method to get value of the Id of the Notification currently being displayed on the screen
     * @param void
     * @return CPopupEnum::EPopupID - current value of m_eCurrentDisplayedNotification
     */
    inline CPopupEnum::EPopupID getCurrentDisplayedNotification() { return m_eCurrentDisplayedNotification;}

    /**
     * @brief   invSetHKHandledStatus: Method to set the status of HK handling by the popup. This method shall be
     *          invoked by the popup to indicate whether it has handled the HK completely of partial handling
     *          is done by the popup and partial handling should be done by the screen.
     * @param   bHKHandledStatus: TRUE if HK is completely handled by the popup, FALSE if the partial handling
     *          is done by the popup and screen needs to do partial handling.
     * @return  void.
     */
    Q_INVOKABLE void invSetHKHandledStatus(bool bHKHandledStatus) { m_bIsHKHandledCompletely = bHKHandledStatus; }

    /**
     * @brief setPopupResult : Method to set Popup result
     * @param ePopupresult : Popup result
     * @return void
     */
    void setPopupResult(CPopupEnum::EPopupResult ePopupresult);

    /**
     * @brief setPopupResult : Method to get Popup result
     * @param void
     * @return m_ePopupresult : Popup result
     */
    CPopupEnum::EPopupResult ePopupResult(){ return m_ePopupResult; }

    /**
     * @brief getBNotificationVisible: To get the state of notification visibility
     * @param void
     * @return true if notification is visible else false
     */
    bool getBNotificationVisible() const;

    /**
     * @brief setBNotificationVisible: To set the state of notification visibility
     * @param bNotificationVisible: current state of notification's visibility
     * @return void
     */
    Q_INVOKABLE void setBNotificationVisible(bool bNotificationVisible);

signals:

    /**
     * @brief sigShowNotificationPopup : Signal to be emitted when notification popup needs to be display
     * @param QString strNotificationQmlFilePath - Path of QML file to be unloaded
     * @return void
     */
    void sigShowNotificationPopup(const QString &strNotificationQmlFilePath, const QVariant &strNotificationQmlFileName, CPopupEnum::EPopupID ePopupId = CPopupEnum::EN_POPUPID_UNKNOWN);

    /**
     * @brief sigCloseNotificationPopup : Signal to be emitted when notification popup needs to be closed
     * @param void
     * @return void
     */
    void sigCloseNotificationPopup();

    /**
     * @brief sigEnterNoPopupState : Signal to emitted when popup is closed and Popup SCT enters NoPopup state
     * @param void
     * @return void
     */
    void sigEnterNoPopupState();

    /**
     * @brief sigEnterNoNotificationState : Signal to emitted when popup is closed and Popup SCT enters NoNotification state
     * @param void
     * @return void
     */
    void sigEnterNoNotificationState();

    /**
     * @brief sigPopupResult - Signal to be emitted whenever a popup is displayed, closed or Ignored
     * @param ePopupId - Id of the Popup
     * @param ePopupResult - Result of the Popup(Displayed, Closed or Ignored)
     * @param strAdditionalInfo : Additional info for popup
     * @return void
     */
    void sigPopupResult(CPopupEnum::EPopupID ePopupId,CPopupEnum::EPopupResult ePopupResult, QString strAdditionalInfo = "");

    /**
     * @brief sigProcessHKOnPopup - Signal to be emitted whenever a popup needs to process the HK and close on HK for that
     *        popup is FALSE
     * @param iKey - the key on which the action is triggered.
     * @param iKeyState - state of the key on which the action is triggered.
     * @return void.
     */
    void sigProcessHKOnPopup(int iKey, int iKeyState);

    /**
     * @brief sigRotaryUpdatePopup - Signal to be emitted whenever popup is on display and
     *                               user rotates menu rotary
     * @param iKey - the key on which the action is triggered.
     * @param iKeyState - state of the key on which the action is triggered.
     * @return void.
     */
    void sigRotaryUpdatePopup(int iKey, int iKeyState);

    /**
     * @brief sigRotaryPressedPopup - Signal to be emitted whenever popup is on display and
     *                               user pressed menu rotary
     * @param iKey - the key on which the action is triggered.
     * @param iKeyState - state of the key on which the action is triggered.
     * @return void.
     */
    void sigRotaryPressedPopup(int iKey, int iKeyState);

    /**
     * @brief sigPopupResultChanged - Signal to be emitted whenever ePopupResult updates
     * @param void
     * @return void.
     */
    void sigPopupResultChanged();

    /**
     * @brief sigNotificationVisibilityChanged - Signal to be emitted whenver the notification is displayed or hidden
     * @param void
     * @return void
     */
    void sigNotificationVisibilityChanged();

public slots:

    /**
     * @brief sltEnterNoPopupState : slot for sigEnterNoPopupState signal will invoke show pending popup method
     * @param void
     * @return void
     */
    void sltEnterNoPopupState();

    /**
     * @brief sltEnterNoNotificationState : slot for sigEnterNoNotificationState signal will invoke show pending notification method
     * @param void
     * @return void
     */
    void sltEnterNoNotificationState();

private:
    /**
     * @brief CPopupManager : class Constructor
     * @param void
     * @return void
     */
    CPopupManager();

    /**
     * @brief isExist : Method to check if a popup Id already exists in the pending popup list(m_lPendingPopups)
     * @param eId- ID of the popup to be checked
     * @return bool- True if ID already exists in the pending popup list
     *         False if ID does not exist in the pending popup list
     */
    bool isExist(CPopupEnum::EPopupID ePopupId);

    /**
     * @brief enqueuePopup : Method to enqueue popup in the pending popups queue
     * @param CPopupEnum::EPopupID ePopupId : Id of the popup to be enqued
     * @return void
     */
    void enqueuePopup(CPopupEnum::EPopupID ePopupId);

    /**
     * @brief dequeuePopup : Method that dequeues the first element of the queue and returns it's eId
     * @param void
     * @return CPopupEnum::EPopupID - Id of the popup dequeued
     */
    CPopupEnum::EPopupID dequeuePopup();

    /**
     * @brief loadPopup : Method called to load the Popup qml files
     * @param CPopupEnum::EPopupID ePopupId - ID of the popup to be loaded
     * @return void
     */
    void loadPopup(const CPopupEnum::EPopupID ePopupId);

    /**
     * @brief unloadPopup : This method is used to unload the Popup qml files
     * @param CPopupEnum::EPopupID ePopupId - ID of the popup to be unloaded
     * @return void
     */
    void unloadPopup(CPopupEnum::EPopupID ePopupId);

    /**
     * @brief handlePriority : Method to be called to handle the priority of the currently requested popup.
     *        On the basis of it's priority and  currently displayed popup, new popup is either enqueued, shown over the old popup or ignored.
     * @param ePopupId- Id of the currently requested popup
     * @return void
     */
    void handlePriority(CPopupEnum::EPopupID ePopupId);

    /**
     * @brief handlePopupsWithNoTimeOut : Method to handle popups having no time out value
     * @param CPopupEnum::EPopupID ePopupId - New popup to be shown
     * @return void
     */
    void handlePopupsWithNoTimeOut(CPopupEnum::EPopupID ePopupId);

    /**
     * @brief setCurrentRequestedPopup : Method to set value of mCurrentRequestedPopup(which is the Id of the Popup currently requested by a HMI module to display it on the screen)
     * @param CPopupEnum::EPopupID eId - Value to be set as mCurrentRequestedPopup
     * @return void
     */
    void setCurrentRequestedPopup(CPopupEnum::EPopupID ePopupId);

    /**
     * @brief getCurrentRequestedPopup : Method to get value of mCurrentRequestedPopup(which is the Id of the Popup currently requested by a HMI module to display it on the screen)
     * @param void
     * @return CPopupEnum::EPopupID - current value of mCurrentRequestedPopup
     */
    inline CPopupEnum::EPopupID getCurrentRequestedPopup() { return m_eCurrentRequestedPopup;}

    /**
     * @brief setCurrentRequestedNotification : Method to set value of mCurrentRequestedNotification(which is the Id of the Notification currently requested by a HMI module to display it on the screen)
     * @param CPopupEnum::EPopupID eId - Value to be set as mCurrentRequestedNotification
     * @return void
     */
    void setCurrentRequestedNotification(CPopupEnum::EPopupID ePopupId);

    /**
     * @brief getCurrentRequestedNotification : Method to get value of the Id of the Notification Popup currently requested by a HMI module to display it on the screen
     * @param void
     * @return CPopupEnum::EPopupID - current value of m_eCurrentRequestedNotification
     */
    inline CPopupEnum::EPopupID getCurrentRequestedNotification() { return m_eCurrentRequestedNotification;}

    /**
     * @brief setCurrentDisplayedPopup : Method to set value of mCurrentDisplayedPopup(which is the Id of the Popup currently being displayed on the screen)
     * @param CPopupEnum::EPopupID eId - Value to be set as mCurrentDisplayedPopup
     * @return void
     */
    void setCurrentDisplayedPopup(CPopupEnum::EPopupID ePopupId);

    /**
     * @brief setCurrentDisplayedNotification : Method to set value of the Id of the Notification currently being displayed on the screen
     * @param CPopupEnum::EPopupID ePopupId - Value to be set as m_eCurrentDisplayedNotification
     * @return void
     */
    inline void setCurrentDisplayedNotification(CPopupEnum::EPopupID ePopupId) {m_eCurrentDisplayedNotification = ePopupId;}
    /**
     * @brief broadcastPopupResult  : Method to broadcast popup result when popup gets displayed, ignored or closed
     * @param ePopupId : popup Id
     * @param ePopupresult : Popup result
     * @param strAdditionalInfo : Additional info for popup
     * @return void
     */
    void broadcastPopupResult(CPopupEnum::EPopupID ePopupId, CPopupEnum::EPopupResult ePopupresult, QString strAdditionalInfo = "");

    /**
     * @brief getPopupQueuingStatus - Method to get the status of m_bStartPopupQueueing
     * @param void
     * @return bool - current status of m_bStartPopupQueueing
     */
    bool getPopupQueuingStatus(){return m_bStartPopupQueueing;}

    /**
     * @brief setStartPopupQueueing - Method to set the status of m_bStartPopupQueueing
     * @param bStartPopupQueuing - value to be set as m_bStartPopupQueueing
     * @return void
     */
    void setStartPopupQueueing(bool bStartPopupQueuing);


private:
    /**
     * @brief Instance of Class CPopupManager
     */
    static CPopupManager* m_pInstance;
    /**
     * Instance of class CPopupPropertHandler
     */
    CPopupPropertyHandler* m_pPopupProperty;

    //ToDo: m_lPendingPopupList should be of CPopupEnum::EPopupID type not CPopupPropertyHandler::CPopupProperties
    /**
     * std::list implemented as Priority queue to store all the pending popups which are sorted on the basis of priority of popup
     */
    std::list<CPopupPropertyHandler::CPopupProperties> m_lPendingPopups;

    //ToDo: m_lPendingNotification should be of CPopupEnum::EPopupID type not CPopupPropertyHandler::CPopupProperties
    /**
     * std::list implemented as Priority queue to store all the pending notification which are sorted on the basis of priority of notification
     */
    std::list<CPopupPropertyHandler::CPopupProperties> m_lPendingNotification;

    /**
     * @brief comparePriority is a predicate that compares the priority of popups and returns bool value
     */
    struct comparePriority{
        bool operator()(const CPopupPropertyHandler::CPopupProperties &lhs,const CPopupPropertyHandler::CPopupProperties &rhs ) const
        {
            return lhs.m_ePriority < rhs.m_ePriority;
        }
    };

    /** Instance of class CPopupManagerSM */
    CPopupManagerSM* m_pPopupManagerSM;

    /** This will hold the id of current requested Popup */
    CPopupEnum::EPopupID m_eCurrentRequestedPopup;

    /** This will hold the id of current requested Notification Popup */
    CPopupEnum::EPopupID m_eCurrentRequestedNotification;

    /** This will hold the id of current displayed Popup */
    CPopupEnum::EPopupID m_eCurrentDisplayedPopup;

    /** This will hold the id of current displayed Notification Popup */
    CPopupEnum::EPopupID m_eCurrentDisplayedNotification;

    /**
     * @brief Making CPopupManagerSM a friend class of CPopupManager so that
     * CPopupManagerSM class can access private members and methods of CPopupManager
     */
    friend class CPopupManagerSM;

    //! Flag to decide whether the HK is handled completely by the popup or not.
    bool    m_bIsHKHandledCompletely;

    /**
     * @brief m_ePopupResult variable to store popup result.
     */
    CPopupEnum::EPopupResult    m_ePopupResult;

    /**
     * @brief m_eNotificationResult variable to store notification result.
     */
    CPopupEnum::EPopupResult    m_eNotificationResult;

    /**
     * @brief m_eHardKeyHandled variable to store hadr key on which action is performed.
     */
    CHardKeyEnum::EHardKeys     m_eHardKeyHandled;

    /**
     * This Property will store whether the current HMI state allows only queuing of popups
     */
    bool m_bStartPopupQueueing;

    /**
     * @brief m_bNotificationVisible: Stores the state of visibility of notification in header status bar.
     */
    bool m_bNotificationVisible;
};

#endif // CPOPUPMANAGER_H
