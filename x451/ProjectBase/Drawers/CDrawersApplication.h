/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CDrawersApplication.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* This file is having the declaration for CDrawersApplication class of Drawers.
*/

#ifndef CDRAWERAPPLICATION_H
#define CDRAWERAPPLICATION_H

#include <QObject>
#include "HMIIncludes.h"
#include "CDrawersEnums.h"
#include "CHVACEnums.h"

class CDrawersSM;
class CDrawersAdaptor;

/**
 * @class CDrawersApplication
 * @brief The CDrawersApplication class of Drawers, This class provides basic application
 *  functionalities to drawers, like qml debug logging and raiseEvent function
 *  to raise StateMachine events.
 */
class CDrawersApplication : public CBaseApplication
{
    Q_OBJECT

public:
    CDrawersApplication(QQuickItem* pParent = nullptr);

    ~CDrawersApplication();

    /**
     * @brief onCreated - Function is called when the QML is loaded successfully
     * @param pRootObject - provides the created qml object as the root Object
     * @return	void.
     */
    void onCreated(QQuickItem* pRootObject);

    /**
     * @brief raiseSMEvent - Function is called from the QML file to raise an event on the State machine
     * Based on which there might be a screen transition or internal state change
     * @param name - The name of the domain/module
     * @param data - The name of the event/state we want the SM to be transitioned into
     * @return	void.
     */
    void raiseSMEvent(const QString & name,const QVariant & data);

private:
    /**
     * @brief raiseSMEventFromShortcutDrawer - Function is called from raiseSMEvent when raiseSMEvent is
     *        called with name "ShortcutDrawer", Basically It handles all events raise, which HMI needs
     *        to raise from Shortcut drawer to change the states in state machine. Like: When Home button
     *        pressed from Shortcut drawer, Hmi needs to change the state to Home State.
     * @param const CDrawersEnums::EShortcutDrawerButtonID &eShortcutDrawerButtonID: ButtonID on which
     *        click HMI needs to take action.
     * @return	void.
     */
    void raiseSMEventFromShortcutDrawer(const CDrawersEnums::EShortcutDrawerButtonID &eShortcutDrawerButtonID);

    /**
     * @brief raiseSMEventFromQADDrawer - Function is called from raiseSMEvent when raiseSMEvent is
     *        called with name "QadDrawer", Basically It handles all events raise, which HMI needs
     *        to raise from QAD drawer to change the states in state machine. Like: When Active
     *        Entertainment info button pressed from QAD Maximized drawer, HMI needs to change the
     *        state to BT Paired Device List State.
     * @param const CDrawersEnums::EQadDrawerButtonID &eQadDrawerButtonID: ButtonID on which
     *        click HMI needs to take action.
     * @return	void.
     */
    void raiseSMEventFromQADDrawer(const CDrawersEnums::EQadDrawerButtonID &eQadDrawerButtonID);

    /**
     * @brief raiseSMEventFromSourceDrawer - Function is called from
     *        raiseSMEvent when raiseSMEvent is called with name
     *        "SourceDrawer", Basically It handles all events raise,
     *        which HMI needs to raise from Source drawer to change the states
     *        in state machine. Like: When user clicks on close button of Source
     *        Drawer HMI needs to raise state machine event to minimize Source
     *        Drawer.
     * @param const CDrawersEnums::ESourceDrawerButtonID &eSourceDrawerButtonID:
     *        ButtonID on which click HMI needs to take action.
     * @return	void.
     */
    void raiseSMEventFromSourceDrawer(const CDrawersEnums::ESourceDrawerButtonID &eSourceDrawerButtonID);

    /**
     * @brief raiseCommonSMEventsForDrawers - Function is called from raiseSMEvent
     *        when raiseSMEvent is called with name "Drawer",
     *        Basically it handles all events raised for general drawer
     *        behaviour for all drawers, like resetting Drawer's close Timer
     *        for currently Maximized drawer
     * @param eCommonEvent - The value indicates the SCT event to be
     *         raised
     * @return void
     */
    void raiseCommonSMEventsForDrawers(CDrawersEnums::ECommonEventsForDrawers eCommonEvent);

    /**
     * @brief connectSignals: This function is used to connect signals of
     *        another, adaptors if required. Currently connecting only HVAC
     *        Adaptor's signals.
     */
    void connectSignals();

    /**
     * @brief disconnectSignals: This function is used to disconnect signals of
     *        another, adaptors if required. Currently disconnecting only HVAC
     *        Adaptor's signals.
     */
    void disconnectSignals();

    /**
     * @brief   isHvacOverlayCanBeShown: This function decides can HMI show the HVAC Notification Overlay.
     * @param   void.
     * @return  true: if HVAC Notification overlay can be shown, otherwise false.
     */
    bool isHvacOverlayCanBeShown();

    /**
     * @brief   getNotificationType: Internal method to get HVAC notification type from HVAC param.
     * @param   eHVACParam: Type of HVAC param.
     * @return  Type of the HVAC notification.
     */
    CDrawersEnums::ENotificationTypes getNotificationType(CHVACEnums::EHVACParamEnums eHVACParam);

    /**
     * @brief   displayHVACNotificationOverlay: Internal method to display HVAC notification overlay.
     * @param   eHVACNotificationType: Type of HVAC notification overlay to be displayed.
     * @return  void.
     */
    void displayHVACNotificationOverlay(CDrawersEnums::ENotificationTypes eHVACNotificationType);

    /**
     * @brief   displayCtrlPanelModeOverlay: Internal method to display control panel mode overlay.
     * @param   void.
     * @return  void.
     */
    void displayCtrlPanelModeOverlay();

public slots:
    /**
     * @brief Slot to be connected to PopupManager's signal sigPopupResult to handle Popup events
     * @param ePopupId - Id of the Popup
     * @param EPopupPriority - Result of the Popup(Displayed, Closed or Ignored)
     */
    void sltPopupResult(CPopupEnum::EPopupID ePopupId, CPopupEnum::EPopupResult ePopupResult, QString strAdditionalInfo);

    /**
     * @brief   sltCcmUserInterventionParamChanged: Slot to show HVAC overlay on CCM param is changed.
     * @param   iHuCcmParam: The CCM parameter which has been changed.
     * @return  void.
     */
    void sltCcmUserInterventionParamChanged(int iHuCcmParam);

private:
    CDrawersSM* m_pDrawersSM;
};

#endif // CDRAWERAPPLICATION_H
