/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CDisplayManagerResourceImpl.h
 * @ingroup       HMIComponent
 * @author        Vishal Chaudhary
 * @brief         This file contains CDisplayManagerResourceImpl class that
 *                shall implement the DisplayManagerResource interface and is
 *                a mediator between lower layer(press control) and upper
 *                layer(application).
 */

#ifndef CDISPLAYMANAGERRESOURCEIMPL_H
#define CDISPLAYMANAGERRESOURCEIMPL_H

#include <capi/CAPIClientAbstraction.hpp>
#include "interfaces/IDisplayManagerResource.h"
#include "CDisplayManagerEventProvider.h"



/*!
 * @class CDisplayManagerResourceImpl
 * @brief This is a singleton class that shall implement the
 *        DisplayManagerResource interface and is a mediator between lower
 *        layer(press control) and upper layer(application).
 */

class CDisplayManagerResourceImpl: public IDisplayManagerResource
{

/********************************************//**
 * @category METHODS
 ************************************************/
public:
    virtual ~CDisplayManagerResourceImpl();

    /*!
     * @brief   Method to get the instance of CDisplayManagerDataEventProvider
     *          class.
     * @param   void.
     * @return  pointer to the object of CDisplayManagerDataEventProvider class.
     */
    CDisplayManagerEventProvider * getDisplayManagerEventProvider();

    /******************************************************//**
     * @category    REQUEST
     * @brief       Overide the DisplayManagerResource functions
     * that shall be used by the Phone adapter layer to propagate
     * the calls.
     *******************************************************/
    void setDisplayOnOffFeatureAsyncReq(bool bDisplayStatus) override;
    void setDisplayBrightnessLevelAsyncReq(int16_t uiBrightnessLevel) override;

    /**
     * @brief setButtonPanelBrightnessLevelAsyncReq: function to set brightness
     *        level.
     * @param iBrightnessLevel: bright ness level needs to set.
     */
    void setButtonPanelBrightnessLevelAsyncReq(int16_t iBrightnessLevel) override;
    void getDisplayBrightnessLevelAsyncReq() override;
    /**
     * @brief getButtonPanelBrightnessLevelAsyncReq: funnction to get the
     *        brightness level.
     * @param void.
     * @return void.
     */
    void getButtonPanelBrightnessLevelAsyncReq() override;

    /******************************************************//**
     * @category GETTERS
     *******************************************************/


private:
    /*!
     * @brief Adding ResourceFactory class as friend class so that
     * ResourceFactory shall be able to create the instance of this class.
     */
    friend class ResourceFactory;
    CDisplayManagerResourceImpl();

    /******************************************************//**
     * @category CALLBACK
     *******************************************************/
    void displayManagerStatusCb( CommonAPI::AvailabilityStatus eStatus ) override;
    void setDisplayOnOffFeatureAsyncCb(const CommonAPI::CallStatus& eCallStatus, const DisplayMgrEventTypes::DmErrorStatus& eErrorStatus) override;
    void setDisplayBrightnessLevelAsyncCb(const CommonAPI::CallStatus& eCallStatus, const DisplayMgrEventTypes::DmErrorStatus& eErrorStatus) override;
    void getDisplayBrightnessLevelAsyncCb(const CommonAPI::CallStatus& eCallStatus, const int16_t& iBrightnessLevel, const DisplayMgrEventTypes::DmErrorStatus& eErrorStatus) override;

    /**
      * @brief setButtonPanelBrightnessLevelAsyncCb: Call back function of
      *        setButtonPanelBrightnessLevelAsync() function.
      * @param eCallStatus: call status
      * @param eErrorStatus: error status
      */
    void setButtonPanelBrightnessLevelAsyncCb(const CommonAPI::CallStatus& eCallStatus, const DisplayMgrEventTypes::DmErrorStatus& eErrorStatus) override;

    /**
      * @brief getButtonPanelBrightnessLevelAsyncCb: Call back function of
      *        getButtonPanelBrightnessLevelAsync() function.
      * @param eCallStatus: call status
      * @param iBrightnessLevel: bright ness level.
      * @param eErrorStatus: error status.
      */
    void getButtonPanelBrightnessLevelAsyncCb(const CommonAPI::CallStatus& eCallStatus, const int16_t& iBrightnessLevel, const DisplayMgrEventTypes::DmErrorStatus& eErrorStatus) override;

    void onDisplayOnOffFeatureStatusCb(int32_t iDisplayOnOffFeatureStatus) override;
    void onNightModeStatusCb(int32_t iNightModeStatus) override;

    /********************************************//**
     * @category RESPONSE
     ************************************************/


    /******************************************************//**
     * @category INTERNAL METHODS
     *******************************************************/
    /*!
     * @brief   Internal method to subscribe all the callback methods.
     * @param   void.
     * @return  void.
     */
    void subscribeDisplayManagerCb();

/******************************************************//**
 * @category PROPERTIES
 *******************************************************/
private:

    /*!
     * @brief Pointer of CDisplayManagerDataEventProvider class to
     * emit signals to the DisplayManager application layer.
     */
    CDisplayManagerEventProvider    *m_pDisplayManagerEventProvider;

    /*!
     * @brief Instance of DisplayManagerProxy class to communicate with
     * Display Manager press control layer.
     */
    CAPIClientAbstraction<CDisplayMgrPresCtrlProxy> m_objDisplayManagerProxy;

    /**
     * @brief m_bIsDisplayManagerProxyAvailable: Flag to maintain connection
     *        manager proxy availability status
     */
    bool    m_bIsDisplayManagerProxyAvailable;
};

#endif // CDISPLAYMANAGERRESOURCEIMPL_H
