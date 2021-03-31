/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
***************************************************************
*/
/**
* @file         IVoiceAlerts.h
* @ingroup       HMIComponent
* @author        Guru Alingal
* IVoiceAlerts will have the declarations required for functions and attributes
* in voice alerts service to communicate with HMI.
*/

#ifndef IVOICEALERTS_H
#define IVOICEALERTS_H

#include <v1/com/harman/VoiceAlert/VoiceAlertType.hpp>
#include <v0/com/harman/VoiceAlert/VoiceAlertServiceProxy.hpp>

using namespace std;
using namespace v1::com::harman::VoiceAlert;
using namespace v0::com::harman::VoiceAlert;

class IVoiceAlerts
{
public:
    /** The base class of IVoiceAlerts */
    virtual ~IVoiceAlerts() {}

    /**
     * @brief getVoiceAlertPresence - Method used to read the presence of voice
     *        alert fetaure.
     * @param void
     * @returns int voice alert presence
     */
     virtual int getVoiceAlertPresence() = 0;

    /**
     * @brief activateVoiceAlerts - Method used to activate/deactivate voice alerts.
     * @param iState - 1 to enable, 0 to disable voice alerts.
     * @return void
     */
    //virtual void activateVoiceAlerts(int iState) = 0;

    /**
     * @brief getCurrentVoiceAlert- Get the current active voice alert.
     * @param void
     * @return active voice alert
     */
    virtual int getCurrentVoiceAlert() = 0;

    /**
     * @brief getCurrentMceVoiceAlert- Get the current active voice alert for Mce.
     * @param void
     * @return active mce voice alert
     */
    virtual int getCurrentMceVoiceAlert() = 0;

    /**
     * @brief getCurrentState - To get the current state of voice alerts.
     * @param void
     * @return current state of voice alert. Possibe states can be received,
     *         queued, in process, delivered, error, aborted etc.
     */
    virtual int getCurrentState() = 0;

    /**
     * @brief getHMISelectionState - To get the current state of HMI selection
     *        displaying voice alerts.
     * @param void
     * @return current state of HMI selection.
     */
    virtual int getHMISelectionState() = 0;

    /**
     * @brief setVoiceAlertSelection - To set the voice alert selection, API call to
     *          be made with this method.
     * @param bVoiceAlertSelection : bVoiceAlertSelection is holding the Voice alert selection status.
     * @return void.
     */
    virtual void setVoiceAlertSelection(bool bVoiceAlertSelection) = 0;

};
#endif
