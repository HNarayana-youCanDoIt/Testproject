/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         IAndroidAutoResource.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* IAndroidAutoResource, an interface for AndroidAuto Resource Implementaion in
* HMI.
*/

#ifndef IANDROIDAUTORESOURCE_H
#define IANDROIDAUTORESOURCE_H

#include <string>
#include "capi/CAPIClientAbstraction.hpp"

//!Include the headers related to AndroidAutoPresCtrl
#include "v1/com/harman/pres/aaprescontrolsProxy.hpp"
#include "v0/com/harman/androidautopres/TataAndroidAutoPresPluginProxy.hpp"
#include "implementations/CAndroidAutoResourceData.h"


using namespace v1::com::harman::pres;
using namespace std;
using namespace v2::com::harman::pres;
using namespace v0::com::harman::androidautopres;

/**
 * @interface IAndroidAutoResource
 * @brief     This interface provides functionality that would be implemented to
 *            interact with AndroidAuto presctrl and also to provide data to
 *            AndroidAuto Adaptor Layer
 */
class IAndroidAutoResource
{
public:
    virtual ~IAndroidAutoResource() {}

    /********************************************//**
     * @category REQUEST METHODS
     ************************************************/

    /**
     * @brief   requestProjection: Function to request the Android Auto
     *          projection screen. Basically to launch the Android Auto screen.
     *          This function calls the AndroidAuto press's requestProjection
     *          function.
     * @param   void.
     * @return  void
     */
    virtual void requestProjection() = 0;

    /**
     * @brief   requestNative: Function to request the Native
     *          screen. Basically to stop the AndroidAuto projection.
     * @param   void.
     * @return  void
     */
    virtual void requestNative() = 0;

    /**
     * @brief   reportKeyEvent: This function is used to report key press events to
     *          AndroidAuto plugin.
     * @param   uiKeyCode: KeyCode which needs to report.
     * @param   uiKeyState: KeyState, like press, release, longPress, longRelease.
     */
    virtual void reportKeyEvent(const uint32_t &uiKeyCode, const uint32_t &uiKeyState) = 0;

    /**
     * @brief   toggleAapMediaAsync: This methdo is used to toggle the state of
     *          AndroidAuto media, Like If media is playing and user press on
     *          pause button then it will toggle that state from play to pause.
     * @param   void.
     * @return  void.
     */
    virtual void toggleAapMediaAsync() = 0;

    /**
     * @brief   pauseAapMediaAsync: This function will be used to pause the
     *          playing song for AndroidAuto Media.
     * @param   void.
     * @return  void.
     */
    virtual void pauseAapMediaAsync() = 0;

    /**
     * @brief   playAapMediaAsync: This function will be used to play the
     *          song (which is in pause state) for AndroidAuto Media.
     * @param   void.
     * @return  void.
     */
    virtual void playAapMediaAsync() = 0;

    /**
     * @brief   aapMediaNextAsync: This function is used to play Next Song,
     *          using SoftKey or touch next button available on Native HMI
     *          screen.
     * @param   void.
     * @return  void.
     */
    virtual void aapMediaNextAsync() = 0;

    /**
     * @brief   aapMediaPreviousAsync: This function is used to play Previous
     *          Song, using SoftKey or touch previous button available on Native
     *          HMI screen.
     * @param   void.
     * @return  void.
     */
    virtual void aapMediaPreviousAsync() = 0;

    /**
     * @brief   aapShowAaMediaAsync: This function is used to launch the Android
     *          Auto music screen, Whenever required.
     * @param   void.
     * @return  void.
     */
    virtual void aapShowAaMediaAsync() = 0;

    /**
     * @brief   getAASessionDetails: This method is used to get the Android Auto
     *          session details.
     * @param   void.
     * @return  const SAASessionDetails&: Android Auto session details.
     */
    virtual const SAASessionDetails& getAASessionDetails() = 0;

    /**
     * @brief   getAANavigationNextTurnInfo: This method is used to get the Android Auto
     *          Navigation Next Turn info.
     * @param   void.
     * @return  const SAANaviNextTurnInfo&: Android Auto Navigation Next Turn details.
     */
    virtual const SAANaviNextTurnInfo& getAANavigationNextTurnInfo() = 0;

    /**
     * @brief   getAANavigationNextTurnDistInfo: This method is used to get the Android Auto
     *          Navigation Next Turn info.
     * @param   void.
     * @return  const SAANaviNextTurnDistInfo&: Android Auto Navigation Next Turn details.
     */
    virtual const SAANaviNextTurnDistInfo& getAANavigationNextTurnDistInfo() = 0;

private:

    /********************************************//**
     * @category CALLBACK METHODS
     ************************************************/

    /*!
     * @brief   Callback to get notified about the avalability status of the
     *          AndroidAuto proxy.
     * @param   eAvailabilityStatus - Status of AndroidAuto proxy whether
     *          available or not.
     * @return  void.
     */
    virtual void androidAutoSeriveStatusCb(AvailabilityStatus eAvailabilityStatus) = 0;

    /*!
     * @brief   Callback to get notified about the avalability status of the
     *          AndroidAutoPlugin proxy.
     * @param   eAvailabilityStatus - Status of AndroidAuto proxy whether available or not.
     * @return  void.
     */
    virtual void androidAutoPluginSeriveStatusCb(AvailabilityStatus eAvailabilityStatus) = 0;

    /**
     * @brief   onFirstConnectionCb: This callBack function will be hit when any AA
     *          phone is connected for first time to HU.
     *
     * @param   ucFirstRunParam: This will come as 1 if HMI needs to show first
     *          run popup, else 0
     * @return  void.
     */
    virtual void onFirstConnectionCb(uint8_t ucFirstRunParam) = 0;

    /**
     * @brief onFunctionOwnerCb: This callBack function will be hit when function
     *        owner of any function like: screen, speech, audio and navigation
     *        gets changed, during Android Auto session.
     * @param objSHuFunctions: Object of structure HuFunctions, which contains all
     *        function owner's details.
     * @return  void.
     */
    virtual void onFunctionOwnerCb(
            const TataAndroidAutoPresPlugin::HuFunctions &objSHuFunctions) = 0;

    /**
     * @brief   onScreenOwnerCb: This callBack function will be hit when screen
     *          Owner Changes. Native ==> Projection or Projection ==> Native.
     *
     * @param   ownerType: ScreenOwner type. Phone or Native HMI
     * @return  void.
     */
    virtual void onScreenOwnerCb(
            const TataAndroidAutoPresPlugin::OwnerType &ownerType) = 0;

    /**
     * @brief   onGetNavStatusTypeAttributeCb: This callBack function will be
     *          hit when Android Auto Navigation gets Activated or Deactivated.
     *
     * @param   navigationStatus: Navigation status active or not.
     * @return  void.
     */
    virtual void onGetNavStatusTypeAttributeCb(
            const pprestypes::navigationStatusType &naviStatus) = 0;

    /**
     * @brief   onPlaybackStatusAttributeCb: This function called, Whenever
     *          PlaybackStatusAttribute gets changed.
     * @param   objsMediaPlaybackStatusUpdate: Object of
     *          sMediaPlaybackStatusUpdate, Which contains playState and all
     *          other info of Aandroid Auto Media.
     * @return  void.
     */
    virtual void onPlaybackStatusAttributeCb(
            const pprestypes::sMediaPlaybackStatusUpdate
            &objsMediaPlaybackStatusUpdate) = 0;

    /**
     * @brief   onMetadataAttributeCb: This function is called whenever
     *          MetadataAttribute gets change. This attribute is for AA Media's
     *          meta data.
     * @param   objsMetaDataUpdate: Object of sMetaDataUpdate structure. This
     *          structure contains AA Media's Meta data info like songName,
     *          albumName, artistName,songAlbumArt, playlist, time, songRating.
     * @return  void.
     */
    virtual void onMetadataAttributeCb(
            const pprestypes::sMetaDataUpdate &objsMetaDataUpdate) = 0;

    /**
     * @brief   onGetSessionAttributeCb: This function is called whenever
     *          SessionAttribute gets change. This attribute is for AA session
     *          details like Device name, bt address etc..
     * @param   objsSessionDetails: Object of sSessionDetails structure. This
     *          structure contains AA session details: devName, btAddres,
     *          usbSerialNo, isConnected, transport, status, remoteUI.
     * @return  void.
     */
    virtual void onGetSessionAttributeCb( const pprestypes::sSessionDetails &objsSessionDetails ) = 0;

    /**
     * @brief   onNavTurnInfoAttributeCb: This function is called whenever
     *          TurnInfoAttribute gets change. This attribute is for AA Navigation
     *          Turn Info: like Turn side, road name etc..
     * @param   objsNaviNextTurnInfo: Object of sNaviNextTurnInfo structure.
     * @return  void.
     */
    virtual void onNavTurnInfoAttributeCb( const pprestypes::sNaviNextTurnInfo &objsNaviNextTurnInfo ) = 0;

    /**
     * @brief   onNavTurnDistInfoAttributeCb: This function is called whenever
     *          NavTurnDistInfoAttribute gets change. This attribute is for AA
     *          Navigatio Turn Distance Info.
     * @param   objsNaviNextTurnDistInfo: Object of sNaviNextTurnDistInfo structure.
     * @return  void.
     */
    virtual void onNavTurnDistInfoAttributeCb( const pprestypes::sNaviNextTurnDistInfo &objsNaviNextTurnDistInfo ) = 0;

    /**
     * @brief   onSpeechOwnerCb: This callBack function will be hit when voice activation
     *          Owner Changes between: No Voice Activation ==> Native ==> Projection.
     *
     * @param   ownerType: SpeechOwner type. No Voice Activation, Phone or Native HMI
     * @return  void.
     */
    virtual void onSpeechOwnerCb(
            const TataAndroidAutoPresPlugin::OwnerType &ownerType) = 0;

    /********************************************//**
     * @category RESPONSE CALLBACK METHODS
     ************************************************/
};

#endif // IANDROIDAUTORESOURCE_H
