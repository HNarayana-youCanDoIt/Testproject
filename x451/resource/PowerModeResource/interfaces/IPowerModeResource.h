/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         IPowerMode.h
* @ingroup      HMIComponent
* @author       Prashantkumar Raut
* IPowerModeResource, an interface for Power Mode Resource Implementaion in HMI.
*/

#ifndef IPOWERMODERESOURCE_H
#define IPOWERMODERESOURCE_H

#include <string>
#include <QString>
#include <QObject>
#include <QVariant>
#include "v2/org/genivi/NodeStateManager/NodeStateTypes.hpp"

using namespace v2::org::genivi::NodeStateManager;

/**
 * @interface IPowerModeResource
 * @brief     This interface provides functionality that would be implemented to interact
 *            with PowerMode presctrl and also to provide data to PowerMode Adaptor Layer
 */
class IPowerModeResource
{
public:
    virtual ~IPowerModeResource() {}

    /*********************************************************
             Request Methods
     *********************************************************/

    /**
     * @brief getNodeState async method to get the current node State information
     * @param void
     * @return void
     */
    virtual void getNodeState() = 0;

    /**
     * @brief setOneHourExpiryStateInactive: This method sets the one hour expiry state to in-active.
     * @param void.
     * @return void.
     */
    virtual void setOneHourExpiryStateInactive() = 0;

private:
    /*********************************************************
             CallBack Methods
     *********************************************************/
    /**
     * @brief CallBack method to get enum int value of power mode
     * @param m_mode - power mode string
     * @return void
     */
    virtual void onVehiclePowerMode(std::string m_mode) = 0;

    /**
     * @brief onGetNodeStateEvent getnodestate event callback
     * @param nsmNodeState
     * @return void
     */
    virtual void onGetNodeStateEvent(NodeStateTypes::NsmNodeState nsmNodeState) = 0;

    /**
     * @brief onGetSessionStateCb: This is a callback method to the getSessionStateChangedEvent.
     * @param Sessionname: Name of the session is received here, ex: "OneHourModeExpiry".
     *        seat: Type of seat is received here, NsmSeat_Driver etc.
     *        sessionState: The state of the session is received here, active or not.
     * @return void.
     */
    virtual void onGetSessionStateCb(const std::string &Sessionname, const NodeStateTypes::NsmSeat& seat, const NodeStateTypes::NsmSessionState& sessionState) = 0;

    /**
     * @brief setSessionStateAsyncCallback: This is a callback method to the SetSessionStateAsync.
     * @param status: callstatus holding the API call status.
     *        nsmErrorStatus: OK or error.
     * @return void.
     */
    virtual void onSetSessionStateAsyncCb(const CommonAPI::CallStatus& status, const NodeStateTypes::NsmErrorStatus& nsmErrorStatus) = 0;

};
#endif // IPOWERMODERESOURCE_H



