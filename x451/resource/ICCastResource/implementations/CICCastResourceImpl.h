/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CICCastResourceImpl.h
* @ingroup      HMIComponent
* @author       Rahul Balyan
* IICCastResource, Resource Implementation for the IC Cast module. Implements the IICCastResource interface
*/

#ifndef CICCASTRESOURCEIMPL_H
#define CICCASTRESOURCEIMPL_H

#include "interfaces/IICCastResource.h"
#include "CICCastEventProvider.h"


class CICCastResourceImpl: public IICCastResource
{
public:
    virtual ~CICCastResourceImpl();

    /**
     * @brief getICCastEventProvider: Method to get the instance of the ICCast event provider
     * @param void
     * @return the pointer to the ICCast event provider
     */
    CICCastEventProvider* getICCastEventProvider();

    /**
     * @brief icCastProxyStatusCb: CallBack method to get notified about the availability status of IC cast Proxy
     * @param eStatus: status of IC cast proxy whether available or not
     * @return void
     */
    void icCastProxyStatusCb(CommonAPI::AvailabilityStatus eStatus) override;

    /**
     * @brief   setIcRenderPhoneCallStateAsyncReq: Method to be invoked by phone adaptor to notify ic cast service
     *          regarding call state received.
     * @param   ePhoneCallState: current phone call state that should be passed to ic render service.
     * @param   strContactNameNum: Caller contact name or number if contact name is not available.
     * @param   cCallId: call id of the call.
     * @return  void.
     */
    void setIcRenderPhoneCallStateAsyncReq(EICRenderPhoneCallState ePhoneCallState, const string& strContactNameNum, int8_t cCallId) override;

    /**
     * @brief   setIcRenderSmsIndicationAsyncReq: Method to be invoked by phone adaptor to notify ic cast service
     *          whenever incoming sms is shown/remove in HMI
     * @param   bSmsIndicationFlag: Flag to indicate whether incoming sms is shown or removed.
     * @param   strContactNameNum: Sms sender contact name or number if contact name is not available.
     * @return  void.
     */
    void setIcRenderSmsIndicationAsyncReq(bool bSmsIndicationFlag, const string& strContactNameNum) override;

    /*!
     * @brief   setIcRenderPhoneCallStateAsyncReqCb: Callback to get notified about setIcRenderPhoneCallStateAsync
     *          method response.
     * @param   eCallStatus   - call status of the setIcRenderPhoneCallStateAsync method, whether success or not.
     * @return  void.
     */
    void setIcRenderPhoneCallStateAsyncReqCb(const CommonAPI::CallStatus& eCallStatus);

    /*!
     * @brief   setIcRenderPhoneCallStateAsyncReqCb: Callback to get notified about setIcRenderSmsRxIndicationAsync
     *          method response.
     * @param   eCallStatus   - call status of the setIcRenderSmsRxIndicationAsync method, whether success or not.
     * @return  void.
     */
    void setIcRenderSmsIndicationAsyncReqCb(const CommonAPI::CallStatus& eCallStatus);

    /**
     * @brief setIcRenderCastAsyncReq: Function to on/off the given casting component.
     * @param int: Type of Component that needs to be on/Off
     * @param iICCastTypeEnum: TRUE- to activate the given feature FALSE- to deactivate the feature.
     */
    void setIcRenderCastAsyncReq(int iICCastTypeEnum, const bool bICCastStatus) override;

    /*!
     * @brief   setIcRenderCastAsyncReqCb: Callback to get notified about setIcRenderCastAsyncReq
     *          method response.
     * @param   eCallStatus   - call status of the setIcRenderCastAsyncReq method, whether success or not.
     * @return  void.
     */
    void setIcRenderCastAsyncReqCb(const CommonAPI::CallStatus& eCallStatus) override;

    /**
     * @brief isICCastProxyAvailable: returns the proxy availability.
     * @param void.
     * @return bool: TRUE- IF proxy is available. FALSE- if proxy is absent.
     */
    bool isICCastProxyAvailable() override { return m_bICCastProxyAvailable; }

    /**
     * @brief getIcRenderCastAsync: getter for the value for the given component of IC Cast.
     * @param iIcRenderCas: Enum of the component used for IC Cast.
     * @return void.
     */
    void getIcRenderCastAsync(int iIcRenderCastComponent) override;

    /**
     * @brief getIcRenderCastAsyncReqCb: getter callback  for the value for the given component of IC Cast.
     * @param eCallStatus::eIcRenderCas: callback status for the request.
     * @param bIcCastValue: IC cast value for which request was made.
     * @return void.
     */
    void getIcRenderCastAsyncReqCb(const CommonAPI::CallStatus& eCallStatus, bool bIcCastValue) override;

    /**
     * @brief getICCastValue: Getter for the latest value of IC Cast Value.
     * @param void.
     * @return bool: IC cast value for active/ inactive state.
     */
    bool getICCastValue() override { return m_bICCastValue; }

    /**
     * @brief setIcColorTheme Method gets invoked whenever there  is a change in theme type
     * @param   iCurrentThemeType: holds the value for Current Theme type.
     * @return  void
     */
    void setIcColorTheme(int iCurrentThemeType) override;

    /**
     * @brief setIcColorThemeCb: Callback Method for setIcColorThemeAsync.
     * @param eCallStatus   - call status of the setIcColorThemeCb method, whether success or not.
     * @return  void
     */
    void setIcColorThemeCb(const CommonAPI::CallStatus& eCallStatus) override;

private:
    CICCastResourceImpl();

    /**
     * @brief ResourceFactory: Adding ResourceFactory class as friend class so that
     * ResourceFactory shall be able to create the instance of this class.
     */
    friend class ResourceFactory;

    /**
     * @brief subscribeToICCastProxy: Method to subscribe CallBack methods to events provided by ICCast proxy
     * @param void
     * @return void
     */
    void subscribeToICCastProxy();

    /**
     * @brief   getICRenderCallState: Internal method to map IC Cast resource's phone call state enums to
     *          ICCast press's eIcRenderCallState enums. The mapped enums shall be used by the class itself.
     * @param   ePhoneCallState - IC Cast resource's phone call state enum value.
     * @return  ICCast press's eIcRenderCallState enum value.
     */
    IcRenderPresTypes::eIcRenderCallState getICRenderCallState(EICRenderPhoneCallState ePhoneCallState);

    /**
     * @brief m_pICCastEventProvider: Instance of CICCastEventProvider to propogate events to ICCast application layer
     */
    CICCastEventProvider* m_pICCastEventProvider;

    /**
     * @brief m_ICCastProxy: ICCastServiceProxy class object to call ICCast layer Proxy methods
     */
    CAPIClientAbstraction<IcRenderPresProxy> m_ICCastProxy;

    /**
     * @brief m_bICCastProxyAvailable: provides information whether the IC cast proxy is available or not
     */
    bool m_bICCastProxyAvailable;

    /**
     * @brief m_bICCastValue: This variable holds the latest requested ic cast value.
     */
    bool m_bICCastValue;
};

#endif // CICCASTRESOURCEIMPL_H
