/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CPopupManagerSM.h
* @ingroup      HMIComponent
* @author       Rahul Madan
* CPopupManagerSM  Class to implement Popup SCT Interface
*/
#ifndef CPOPUPMANAGERSM_H
#define CPOPUPMANAGERSM_H

#include "HMIIncludes.h"
class CPopupPropertyHandler;

/**
 * @class The CPopupManagerSM class
 * @brief Class to implement PopupManager SCT Interface (TML_HMI_SM::SCI_Popup_OCB)
 */
class CPopupManagerSM : public TML_HMI_SM::SCI_Popup_OCB
{
public:
    CPopupManagerSM();
    ~CPopupManagerSM();

public:
    /**
     * @brief enterNoNotification : SCT callback method called when NoNotification state is entered
     * @param void
     * @return void
     */
    void enterNoNotification() override;

    /**
     * @brief exitNoNotification : SCT callback method called when NoNotification state is exited
     * @param void
     * @return void
     */
    void exitNoNotification() override;

    /**
     * @brief enterNotificationActive : SCT callback method called when NotificationActive state is entered
     * @param void
     * @return void
     */
    void enterNotificationActive() override;

    /**
     * @brief exitNotificationActive : SCT callback method called when NotificationActive state is exited
     * @param void
     * @return void
     */
    void exitNotificationActive() override;

    /**
     * @brief handleNotificationPriority : SCT callback method called when Notification is in NotificationActive State and evShowNotification event is raised
     * @param void
     * @return void
     */
    void handleNotificationPriority() override;

    /**
     * @brief enterNoPopup : SCT callback method called when NoPopup state is entered
     * @param void
     * @return void
     */
    void enterNoPopup() override;

    /**
     * @brief exitNoPopup : SCT callback method called when NoPopup state is exited
     * @param void
     * @return void
     */
    void exitNoPopup() override;

    /**
     * @brief enterPopupActive : SCT callback method called when PopupActive state is entered
     * @param void
     * @return void
     */
    void enterPopupActive() override;

    /**
     * @brief exitPopupActive : SCT callback method called when PopupActive state is exited
     * @param void
     * @return void
     */
    void exitPopupActive() override;

    /**
     * @brief handlePopupPriority : SCT callback method called when Popup is in PopupActive State and evShowPopup event is raised
     * @param void
     * @return void
     */
    void handlePopupPriority() override;

    /**
     * @brief isPopupAllowed : SCT method called to check if currently displayed Popup is allowed over active HMI state(context)
     * @param void
     * @return bool - true if ePopupId's applicable context array contains current active state(context) of HMI, else false
     */
    virtual bool isPopupAllowed() override;

    /**
     * @brief isNotificationAllowed : SCT method called to check if currently displayed notification is allowed over active HMI state(context)
     * @param void
     * @return bool - true if ePopupId's applicable context array contains current active state(context) of HMI, else false
     */
    virtual bool isNotificationAllowed() override;

    /**
     * @brief checkPopupContext : SCT method called to check currently displayed popup's context.
     * @param void
     * @return void
     */
    virtual void checkPopupContext() override;

private:
    /** Instance of class CPopupPropertHandler **/
    CPopupPropertyHandler* m_pPopupPropertyHandler;
};

#endif // CPOPUPMANAGERSM_H
