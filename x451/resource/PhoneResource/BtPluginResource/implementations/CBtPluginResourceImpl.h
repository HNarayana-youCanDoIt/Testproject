/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CBtPluginResourceImpl.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CBtPluginResourceImpl class that shall implement the
 * BtPluginResource interface and is a mediator between lower layer(press control)
 * and upper layer(adaptor).
 */

#ifndef CBTPLUGINRESOURCE_H
#define CBTPLUGINRESOURCE_H

#include <capi/CAPIClientAbstraction.hpp>
#include "interfaces/IBtPluginResource.h"
#include "CBtPluginEventProvider.h"
#include "PhoneResource/CPhoneResourceEnums.h"

/*!
 * @class CBtPluginResourceImpl - Derived from IBtPluginResource interface
 */
class CBtPluginResourceImpl: public IBtPluginResource
{    

/********************************************//**
 * @category METHODS
 ************************************************/
public:

    /**
     * @brief   getBtPluginEventProvider - Method to get the instance of CBtPluginEventProvider class.
     * @param   void.
     * @return  pointer to the object of CBtPluginEventProvider class.
     */
    CBtPluginEventProvider* getBtPluginEventProvider();

    /******************************************************//**
     * @category    REQUEST
     * @brief       Overide the BtPluginResource functions that shall
     * be used by the Phone adapter layer to propagate the calls.
     *******************************************************/
    /**
     * @brief   startTTSPlayAsyncReq - Method to inform bt press plugin to start TTS playback.
     * @param   uiPropmtId - set the source to start the TTS playback in mix mode or
     *                       non mix mode.
     * @param   strMessageText - Message to be played on TTS prompt.
     * @return  void.
     */
    void startTTSPlayAsyncReq(uint32_t uiPropmtId, string strMessageText) override;

    /**
     * @brief   stopTTSPlayAsyncReq - Method to inform bt press plugin to stop TTS playback.
     * @param   uiPropmtId - set the source to start the TTS playback in mix mode or
     *                       non mix mode.
     * @return  void.
     */
    void stopTTSPlayAsyncReq(uint32_t uiPropmtId) override;

private:
    /*!
     * @brief Adding ResourceFactory class as friend class so that
     * ResourceFactory shall be able to create the instance of this class.
     */
    friend class ResourceFactory;

    /**
     * @brief CBtPluginResourceImpl - Constructor of CBtPluginResourceImpl class
     */
    CBtPluginResourceImpl();

    /**
     * @brief ~CBtPluginResourceImpl - Destructor of CBtPluginResourceImpl class
     */
    virtual ~CBtPluginResourceImpl();

    /******************************************************//**
     * @category CALLBACK
     *******************************************************/
    /**
     * @brief   btPluginStatusCb - Callback to get notified about the avalability status of the BtManagerExtProxy.
     * @param   eStatus - status of BtManagerExtProxy whether available or not.
     * @return  void.
     */
    void btPluginStatusCb(CommonAPI::AvailabilityStatus eStatus) override;

    /**
     * @brief   ttsPlayStateCb - Callback to get notified about the current TTS playstate status.
     * @param   eTTSPlayState - current playstate of the TTS.
     * @return  void.
     */
    void ttsPlayStateCb(UISSTypes::ePlayState eTTSPlayState) override;

    /********************************************//**
     * @category RESPONSE
     ************************************************/
    /**
     * @brief   startTTSPlayAsyncCb - Callback to get notified about startTTSPlayAsyncReq method response.
     * @param   eCallStatus - call status of the startTTSPlayAsyncReq method, whether success or not.
     * @param   eErrorType - type of the error received after invoking startTTSPlayAsyncReq method.
     * @return  void.
     */
    void startTTSPlayAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;

    /**
     * @brief   stopTTSPlayAsyncCb - Callback to get notified about stopTTSPlayAsyncReq method response.
     * @param   eCallStatus - call status of the stopTTSPlayAsyncReq method, whether success or not.
     * @param   eErrorType - type of the error received after invoking stopTTSPlayAsyncReq method.
     * @return  void.
     */
    void stopTTSPlayAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;


    /******************************************************//**
     * @category INTERNAL METHODS
     *******************************************************/
    /**
     * @brief   subscribeBtPluginCb - Internal method to subscribe all the callback methods.
     * @param   void.
     * @return  void.
     */
    void subscribeBtPluginCb();

    /**
     * @brief   getMethodCallStatus - Internal method to map BTPress method call status enums to connection manager resource's method
     *          call status enums. The mapped enums shall be used by the phone application layer and the class itself.
     * @param   eCallStatus - BTPress method call status enum value.
     * @return  bt plugin resource's method call status enum.
     */
    EMethodCallStatus getMethodCallStatus(CallStatus eCallStatus);

    /**
     * @brief   getMethodCallErrorType - Internal method to map BTPress method call error type enums to connection manager resource's
     *          method call error type enums. The mapped enums shall be used by the phone application layer
     * @param   iErrorType - BTPress method call error type enum value.
     * @return  bt plugin resource's method call error type enum value.
     */
    EMethodCallErrorType getMethodCallErrorType(int iErrorType);


/******************************************************//**
 * @category PROPERTIES
 *******************************************************/
private:
    /**
     * @brief Pointer of CBtPluginEventProvider class to
     * emit signals to the phone adaptor layer.
     */
    CBtPluginEventProvider*                     m_pBtPluginEventProvider;
    /**
     * @brief Instance of BtManagerExtProxy class to communicate with
     * bt press plugin layer.
     */
    CAPIClientAbstraction<BtManagerExtProxy>    m_objBtPluginProxy;
    //! Flag to maintain bt plugin proxy availability status
    bool                                        m_bIsBtPluginProxyAvailable;
};

#endif // CBTPLUGINRESOURCE_H
