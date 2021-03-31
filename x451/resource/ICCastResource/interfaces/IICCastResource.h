/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         IICCastResource.h
* @ingroup      HMIComponent
* @author       Rahul Balyan
* IICCastResource, an interface for the IC Cast Resource Implementaion in HMI.
*/

#ifndef IICCASTRESOURCE_H
#define IICCASTRESOURCE_H

#include <QObject>

#include "v0/com/harman/dcif/IcRenderPresTypes.hpp"
#include "v0/com/harman/dcif/IcRenderPresProxy.hpp"
#include <capi/CAPIClientAbstraction.hpp>
#include "implementations/CICCastEnum.h"

using namespace std;
using namespace v0::com::harman::dcif;

/**
 * @interface IICCastResource
 * @brief     This interface provides functionality that would be implemented to interact
 *            with ICCast service and also to provide data to ICCast Adaptor Layer
 */
class IICCastResource
{
public:
    virtual ~IICCastResource(){}

    /*****  CALL BACK METHODS  ****************************/

    /**
     * @brief icCastProxyStatusCb: CallBack method to get notified about the availability status of ICCast Proxy
     * @param eStatus: status of ICCast proxy whether available or not
     * @return void
     */
    virtual void icCastProxyStatusCb(CommonAPI::AvailabilityStatus eStatus) = 0;

    /**
     * @brief   setIcRenderPhoneCallStateAsyncReq: Method to be invoked by phone adaptor to notify ic cast service
     *          regarding call state received.
     * @param   ePhoneCallState: current phone call state that should be passed to ic render service.
     * @param   strContactNameNum: Caller contact name or number if contact name is not available.
     * @param   cCallId: call id of the call.
     * @return  void.
     */
    virtual void setIcRenderPhoneCallStateAsyncReq(EICRenderPhoneCallState ePhoneCallState, const string& strContactNameNum, int8_t cCallId) = 0;

    /**
     * @brief   setIcRenderSmsIndicationAsyncReq: Method to be invoked by phone adaptor to notify ic cast service
     *          whenever incoming sms is shown/remove in HMI
     * @param   bSmsIndicationFlag: Flag to indicate whether incoming sms is shown or removed.
     * @param   strContactNameNum: Sms sender contact name or number if contact name is not available.
     * @return  void.
     */
    virtual void setIcRenderSmsIndicationAsyncReq(bool bSmsIndicationFlag, const string& strContactNameNum) = 0;

    /**
     * @brief setIcRenderCastAsyncReq: Function to on/off the given casting component.
     * @param iICCastTypeEnum: Type of Component that needs to be on/Off
     * @param bICCastOnOffValue: TRUE- to activate the given feature FALSE- to deactivate the feature.
     */
    virtual void setIcRenderCastAsyncReq(int iICCastTypeEnum, const bool bICCastOnOffValue) = 0;

    /*!
     * @brief   setIcRenderCastAsyncReqCb: Callback to get notified about setIcRenderCastAsyncReq
     *          method response.
     * @param   eCallStatus   - call status of the setIcRenderCastAsyncReq method, whether success or not.
     * @return  void.
     */
    virtual void setIcRenderCastAsyncReqCb(const CommonAPI::CallStatus& eCallStatus) = 0;
    /**
     * @brief isICCastProxyAvailable: returns the proxy availability.
     * @param void.
     * @return bool: TRUE- IF proxy is available. FALSE- if proxy is absent.
     */
    virtual bool isICCastProxyAvailable() = 0;

    /**
     * @brief getIcRenderCastAsync: getter for the value for the given component of IC Cast.
     * @param iIcRenderCastComponent: Value of the component used for IC Cast.
     * @return void.
     */
    virtual void getIcRenderCastAsync(int iIcRenderCastComponent) =  0;

    /**
     * @brief getIcRenderCastAsyncReqCb: getter callback  for the value for the given component of IC Cast.
     * @param eCallStatus::eIcRenderCas: callback status for the request.
     * @param bIcCastValue: IC cast value for which request was made.
     * @return void.
     */
    virtual void getIcRenderCastAsyncReqCb(const CommonAPI::CallStatus& eCallStatus, bool bIcCastValue) = 0;

    /**
     * @brief getICCastValue: Getter for the latest value of IC Cast Value.
     * @param void.
     * @return bool: IC cast value for active/ inactive state.
     */
    virtual bool getICCastValue() = 0;

    /**
     * @brief setIcColorTheme Method gets invoked whenever there  is a change in theme type
     * @param   iCurrentThemeType: holds the value for Current Theme type.
     * @return  void
     */
    virtual void setIcColorTheme(int iCurrentThemeType) = 0;

    /**
     * @brief setIcColorThemeCb: Callback Method for setIcColorThemeAsync.
     * @param eCallStatus   - call status of the setIcColorThemeCb method, whether success or not.
     * @return  void
     */
    virtual void setIcColorThemeCb(const CommonAPI::CallStatus& eCallStatus) = 0;

};

#endif // IICCASTRESOURCE_H
