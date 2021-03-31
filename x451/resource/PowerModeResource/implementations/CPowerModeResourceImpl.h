/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CPowerModeResourceImpl.h
* @ingroup      HMIComponent
* @author       Prashantkumar Raut
* CPowerModeResourceImpl is the Resource Implementation for PowerMode.
*/

#ifndef CPOWERMODERESOURCEIMPL_H
#define CPOWERMODERESOURCEIMPL_H

#include <QVariant>
#include <memory>
#include "interfaces/IPowerModeResource.h"
#include "CPowerModeEventProvider.h"
//Header files related to PresCtrl
#include "v2/org/genivi/NodeStateManager/ConsumerProxy.hpp"
#include "v2/org/genivi/NodeStateManager/NodeStateTypes.hpp"
#include <CommonAPI/CommonAPI.hpp>

using namespace std;
using namespace v2::org::genivi::NodeStateManager;

/**
*   @brief The CPowerModeResourceImpl class
*   This class implements the CPowerModeResourceImpl interface.
*/
class CPowerModeResourceImpl: public IPowerModeResource
{
public:
    /**
    * @brief	CPowerModeResourceImpl::~CPowerModeResourceImpl is destructor of class CPowerModeResourceImpl
    * @param	NA.
    * @return	NA.
    **/
    virtual ~CPowerModeResourceImpl();

    /**
     * @brief Method to get the instance of CPowerModeEventProvider
     * @param void
     * @return CPowerModeEventProvider pointer
     */
    CPowerModeEventProvider* getPowerModeEventProvider();

    /**
     * @brief Method to get the power mode from the NSM service
     * @param string: value from power mode service
     * @return void
     */
    virtual void onVehiclePowerMode(std::string strMode) override;

    /**
     * @brief getNodeState async method to get the current node State information from NSM service
     * @param void
     * @return void
     */
    void getNodeState() override;

    /**
     * @brief onGetNodeStateEvent getnodestate event callback
     * @param nsmNodeState
     * @return void
     */
    void onGetNodeStateEvent(NodeStateTypes::NsmNodeState eNsmNodeState) override;

    /**
    * @brief	This function is to check the availability of NSM Manager proxy.
    * @param    enum: status will have API availability status.
    * @return	void.
    */
    void statusEventListnerNSMManager(CommonAPI::AvailabilityStatus status);

    /**
     * @brief asyncGetNodeStateCb callback method for the getNodeState call
     * @param const CommonAPI::CallStatus& : API call response status
     *        NodeStateTypes::NsmNodeState& : nsm node state
     *        NodeStateTypes::NsmErrorStatus& : error status
     * @return void
     */
    void asyncGetNodeStateCb(const CommonAPI::CallStatus& eStatus, const NodeStateTypes::NsmNodeState &eNsmNodeState, const NodeStateTypes::NsmErrorStatus &eErrorStatus);

    /**
     * @brief Method to subscribe CallBack methods to events provided by PowerModeProxy
     * @param void
     * @return void
     */
    void subscribe();

    /**
     * @brief getCurrentPowerMode provides the current power mode string
     * @return power mode string
     */
    std::string getCurrentPowerMode();

    /**
     * @brief getCurrentNSMNodeState provide current nsm node state
     * @return int provides the current nsm node state
     */
    int getCurrentNSMNodeState();

    /**
     * @brief onGetSessionStateCb: This is a callback method to the getSessionStateChangedEvent.
     * @param Sessionname: Name of the session is received here, ex: "OneHourModeExpiry".
     *        seat: Type of seat is received here, NsmSeat_Driver etc.
     *        sessionState: The state of the session is received here, active or not.
     * @return void.
     */

    void onGetSessionStateCb(const std::string &Sessionname, const NodeStateTypes::NsmSeat& seat, const NodeStateTypes::NsmSessionState& sessionState);

    /**
     * @brief setOneHourExpiryStateInactive: This method sets the one hour expiry state to in-active.
     * @param void.
     * @return void.
     */
    void setOneHourExpiryStateInactive();

    /**
     * @brief setSessionStateAsyncCallback: This is a callback method to the SetSessionStateAsync.
     * @param status: callstatus holding the API call status.
     *        nsmErrorStatus: OK or error.
     * @return void.
     */
    void onSetSessionStateAsyncCb(const CommonAPI::CallStatus& status, const NodeStateTypes::NsmErrorStatus& nsmErrorStatus);

private:

    const string ONE_HOUR_MODE_EXPIRY_SESSION = "OneHourModeExpiry";
    const string NSM_SESSION_OWNER = "NSMC";

private:
    /**
     * Adding ResourceFactory class as friend class so that
     */
    friend class ResourceFactory;

    /**
    * @brief	CPowerModeResourceImpl::CPowerModeResourceImpl private constructor for singleton class CPowerModeResourceImpl
    * @param	void
    * @return	void
    **/
    CPowerModeResourceImpl();

    /**
     * Create an instance of the CPowerModeEventProvider to emit signals to the upper layer
     */
    CPowerModeEventProvider* m_pPowerModeEventProvider;

    /**
     * PowerModeProxy class object to call PowerMode Proxy methods
     */
    std::shared_ptr<v2::org::genivi::NodeStateManager::ConsumerProxy<>> m_pPowerMode_Proxy;

    /**
     * a member variable maintaining the availability status of Node State Manager Service
     */
    bool m_bNSManagerAvailable;

    /**
     * a member variable maintaining the power mode string
     */
    std::string m_strPowerMode;

    /** stores the nsmNodeState */
    NodeStateTypes::NsmNodeState m_eNSMNodeState;

};

#endif // CPOWERMODERESOURCEI7MPL_H
