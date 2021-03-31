/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          IDisplayManagerResource.h
 * @ingroup       HMIComponent
 * @author        Vishal Chaudhary
 * @brief         This file contains IDisplayManagerResource interface that
 *                provides abstract methods to communicate with the
 *                DisplayManager proxy directly which shall be implemented by
 *                resource implementation class.
 */

#ifndef DISPLAYMANAGERRESOURCE_H
#define DISPLAYMANAGERRESOURCE_H

//!Include the headers related to DisplayManagerPresCtrl
#include "v0/com/harman/dcif/CDisplayMgrPresCtrlProxy.hpp"
#include "v0/com/harman/dcif/DisplayMgrEventTypes.hpp"

using namespace std;
using namespace v0::com::harman::dcif;

/*!
 * @interface IDisplayManagerResource
 * @brief This interfaces provides abstract methods to communicate with the
 * DisplayManager proxy directly which shall be implemented by resource
 * implementation class.
 */
class IDisplayManagerResource
{
public:
    virtual ~IDisplayManagerResource(){}

    /********************************************//**
     * @category REQUEST METHODS
     ************************************************/
    /**
     * @brief setDisplayOnOffFeatureAsyncReq: Request function to set Display
     *        ON/OFF. This function call Display Manager pres's
     *        setDisplayOnOffFeatureAsync() function.
     * @param bDisplayStatus: true if Display needs to ON, else false.
     * @return void.
     */
    virtual void setDisplayOnOffFeatureAsyncReq(bool bDisplayStatus)  = 0;

    /**
     * @brief setDisplayBrightnessLevelAsyncReq: function to set brightness
     *        level.
     * @param iBrightnessLevel: bright ness level needs to set.
     */
    virtual void setDisplayBrightnessLevelAsyncReq(int16_t iBrightnessLevel)  = 0;


    /**
     * @brief setButtonPanelBrightnessLevelAsyncReq: function to set brightness
     *        level.
     * @param iBrightnessLevel: bright ness level needs to set.
     */
    virtual void setButtonPanelBrightnessLevelAsyncReq(int16_t iBrightnessLevel)  = 0;


    /**
     * @brief getDisplayBrightnessLevelAsyncReq: funnction to get the
     *        brightness level.
     * @param void.
     * @return void.
     */
    virtual void getDisplayBrightnessLevelAsyncReq() = 0;

    /**
     * @brief getButtonPanelBrightnessLevelAsyncReq: funnction to get the
     *        brightness level.
     * @param void.
     * @return void.
     */
    virtual void getButtonPanelBrightnessLevelAsyncReq() = 0;

private:
    /********************************************//**
     * @category CALLBACK METHODS
     ************************************************/

    /*!
     * @brief   Callback to get notified about the avalability status of the DisplayManager proxy.
     * @param   eStatus - status of DisplayManager proxy whether available or not.
     * @return  void.
     */
    virtual void displayManagerStatusCb(CommonAPI::AvailabilityStatus eStatus) = 0;

    /**
     * @brief   onDisplayOnOffFeatureStatusCb: This callback will be called whenever
     *          DisplayOnOffFeatureStatusAttribute gets changed in display manager press.
     * @param   iDisplayOnOffFeatureStatus: Display OnOffFeature Status, 1 if enabled, else 0.
     * @return  void.
     */
    virtual void onDisplayOnOffFeatureStatusCb(int32_t iDisplayOnOffFeatureStatus) = 0;

    /**
     * @brief   onNightModeStatusCb: This callback will be called whenever
     *          NightModeStatusAttribute gets changed in display manager press.
     * @param   iNightModeStatus: night mode status 0 - disabled , 1 -
     *          enabled
     * @return  void.
     */
    virtual void onNightModeStatusCb(int32_t iNightModeStatus) = 0;



    /********************************************//**
     * @category RESPONSE CALLBACK METHODS
     ************************************************/

    /**
      * @brief setDisplayOnOffFeatureAsyncCb: Call back function of
      *        setDisplayOnOffFeatureAsync() function.
      * @param eCallStatus: call status
      * @param eErrorStatus: error status
      */
     virtual void setDisplayOnOffFeatureAsyncCb(const CommonAPI::CallStatus& eCallStatus, const DisplayMgrEventTypes::DmErrorStatus& eErrorStatus) = 0;

    /**
      * @brief setDisplayBrightnessLevelAsyncCb: Call back function of
      *        setDisplayBrightnessLevelAsync() function.
      * @param eCallStatus: call status
      * @param eErrorStatus: error status
      */
     virtual void setDisplayBrightnessLevelAsyncCb(const CommonAPI::CallStatus& eCallStatus, const DisplayMgrEventTypes::DmErrorStatus& eErrorStatus) = 0;

    /**
      * @brief setButtonPanelBrightnessLevelAsyncCb: Call back function of
      *        setButtonPanelBrightnessLevelAsync() function.
      * @param eCallStatus: call status
      * @param eErrorStatus: error status
      */
     virtual void setButtonPanelBrightnessLevelAsyncCb(const CommonAPI::CallStatus& eCallStatus, const DisplayMgrEventTypes::DmErrorStatus& eErrorStatus) = 0;


    /**
      * @brief getDisplayBrightnessLevelAsyncCb: Call back function of
      *        getDisplayBrightnessLevelAsync() function.
      * @param eCallStatus: call status
      * @param iBrightnessLevel: bright ness level.
      * @param eErrorStatus: error status.
      */
     virtual void getDisplayBrightnessLevelAsyncCb(const CommonAPI::CallStatus& eCallStatus, const int16_t& iBrightnessLevel, const DisplayMgrEventTypes::DmErrorStatus& eErrorStatus) = 0;

    /**
      * @brief getButtonPanelBrightnessLevelAsyncCb: Call back function of
      *        getButtonPanelBrightnessLevelAsync() function.
      * @param eCallStatus: call status
      * @param iBrightnessLevel: bright ness level.
      * @param eErrorStatus: error status.
      */
     virtual void getButtonPanelBrightnessLevelAsyncCb(const CommonAPI::CallStatus& eCallStatus, const int16_t& iBrightnessLevel, const DisplayMgrEventTypes::DmErrorStatus& eErrorStatus) = 0;


};
#endif // DISPLAYMANAGERRESOURCE_H
