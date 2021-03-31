/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          IBtPluginResource.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains IBtPluginResource interface that provides abstract methods to communicate
 * with the BtPressPlugin proxy directly which shall be implemented by resource implementation class.
 */

#ifndef IBTPLUGINRESOURCE_H
#define IBTPLUGINRESOURCE_H

//!Include the headers related to BtPressPlugin
#include "v7/com/harman/btpres/BTPresTypes.hpp"
#include "v3/com/harman/btpresplugin/BtManagerExtProxy.hpp"

using namespace v3::com::harman::btpresplugin;
using namespace v7::com::harman::btpres;
using namespace v1::com::harman::UISpeechService;
using namespace std;

/*!
 * @interface IBtPluginResource
 */
class IBtPluginResource
{
public:
    virtual ~IBtPluginResource(){}

    /**
     * @brief   startTTSPlayAsyncReq - Method to inform bt press plugin to start TTS playback.
     * @param   uiPropmtId - set the source to start the TTS playback in mix mode or
     *                       non mix mode.
     * @param   strMessageText - Message to be played on TTS prompt.
     * @return  void.
     */
    virtual void startTTSPlayAsyncReq(uint32_t uiPropmtId, string strMessageText) = 0;

    /**
     * @brief   stopTTSPlayAsyncReq - Method to inform bt press plugin to stop TTS playback.
     * @param   uiPropmtId - set the source to start the TTS playback in mix mode or
     *                       non mix mode.
     * @return  void.
     */
    virtual void stopTTSPlayAsyncReq(uint32_t uiPropmtId) = 0;

protected:
    /**
     * @brief   btPluginStatusCb - Callback to get notified about the avalability status of the BtManagerExtProxy.
     * @param   eStatus - status of BtManagerExtProxy whether available or not.
     * @return  void.
     */
    virtual void btPluginStatusCb(CommonAPI::AvailabilityStatus eStatus) = 0;

    /**
     * @brief   ttsPlayStateCb - Callback to get notified about the current TTS playstate status.
     * @param   eTTSPlayState - current playstate of the TTS.
     * @return  void.
     */
    virtual void ttsPlayStateCb(UISSTypes::ePlayState eTTSPlayState) = 0;

    /**
     * @brief   startTTSPlayAsyncCb - Callback to get notified about startTTSPlayAsyncReq method response.
     * @param   eCallStatus - call status of the startTTSPlayAsyncReq method, whether success or not.
     * @param   eErrorType - type of the error received after invoking startTTSPlayAsyncReq method.
     * @return  void.
     */
    virtual void startTTSPlayAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /**
     * @brief   stopTTSPlayAsyncCb - Callback to get notified about stopTTSPlayAsyncReq method response.
     * @param   eCallStatus - call status of the stopTTSPlayAsyncReq method, whether success or not.
     * @param   eErrorType - type of the error received after invoking stopTTSPlayAsyncReq method.
     * @return  void.
     */
    virtual void stopTTSPlayAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;
};

#endif // IBTPLUGINRESOURCE_H
