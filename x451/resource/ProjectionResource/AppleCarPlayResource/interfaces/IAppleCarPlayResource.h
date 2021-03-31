/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         IAppleCarPlayResource.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* IAppleCarPlayResource, an interface for AppleCarPlay Resource Implementaion in
* HMI.
*/

#ifndef IAPPLECARPLAYRESOURCE_H
#define IAPPLECARPLAYRESOURCE_H

#include <string>
#include "implementations/CAppleCarPlayResourceData.h"
#include "capi/CAPIClientAbstraction.hpp"

//!Include the headers related to AppleCarPlayPresCtrl
#include "v3/com/harman/pres/cpprescontrolsProxy.hpp"
#include "v1/com/harman/pres/pprestypes.hpp"
#include "v0/com/harman/carplaypres/TataCarPlayPresPluginProxy.hpp"

using namespace v3::com::harman::pres;
using namespace v2::com::harman::pres;
using namespace v1::com::harman::pres;
using namespace v0::com::harman::carplaypres;
using namespace std;

/**
 * @interface IAppleCarPlayResource
 * @brief     This interface provides functionality that would be implemented to
 *            interact with AppleCarPlay presctrl and also to provide data to
 *            AppleCarPlay Adaptor Layer
 */
class IAppleCarPlayResource
{
public:
    virtual ~IAppleCarPlayResource() {}

    /********************************************
     * @category REQUEST METHODS
     ************************************************/

    /**
     * @brief   requestProjection: Function to request the AppleCarPlay
     *          projection screen. Basically to launch the AppleCarPlay screen.
     *          This function calls the AppleCarPlay press's requestProjection
     *          function.
     * @param   appURL : URL identifier of the desired CarPlay UI application to launch:
     *          Blank String: CarPlay native screen will be shown
     *          "maps:" - Carplay Maps application will be shown
     *          "mobilephone:" - CarPlay Phone application will be shown
     *          "music:" - CarPlay Music application will be shown
     *          "nowplaying:" - CarPlay Now Playing screen will be shown
     *          "tel:xxx-xxx-xxxx" - CarPlay Phone application will be shown and a phone call with desired number will be placed..
     * @return  void
     */
    virtual void requestProjection(const string &appURL) = 0;

    /**
     * @brief   requestNative: Function to request the Native
     *          screen. Basically to stop the AppleCarPlay projection.
     * @param   void.
     * @return  void
     */
    virtual void requestNative() = 0;

    /**
     * @brief   reportKeyEvent: This function is used to report key press events to
     *          CarPlay plugin.
     * @param   uiKeyCode: KeyCode which needs to report.
     * @param   uiKeyState: KeyState, like press, release, longPress, longRelease.
     * @return  void
     */
    virtual void reportKeyEvent(const uint32_t &uiKeyCode, const uint32_t &uiKeyState) = 0;

    /********************************************
     * @category GETTER METHODS
     ************************************************/

    /**
     * @brief   getNowPlayingData: This method is used to get the CarPlay
     *          Media Meta Data.
     * @param   void.
     * @return  const CarPlayNowPlayingInfo&: CarPlay Media Meta Data.
     */
    virtual const CarPlayNowPlayingInfo& getNowPlayingData() = 0;

    /**
     * @brief  setSmartFanState: This method is called from upper layer to send smart fan state request to CP resource.
     * @param  bSmartFanState: State of smart fan to be requested true / false.
     * @return void.
     */
    virtual void setSmartFanState(bool bSmartFanState) = 0;

    /**
     * @brief  onSetSmartFanStateAsyncCb: This is a callback method to the setSmartFanstateAsync.
     * @param  status: Status of the API call, success or not.
     * @return void.
     */
    virtual void onSetSmartFanStateAsyncCb(const CallStatus &status, bool bValue) = 0;

private:

    /********************************************
     * @category CALLBACK METHODS
     ************************************************/

    /*!
     * @brief   Callback to get notified about the avalability status of the
     *          AppleCarPlay proxy.
     * @param   eAvailabilityStatus - Status of AppleCarPlay proxy whether
     *          available or not.
     * @return  void.
     */
    virtual void appleCarPlaySeriveStatusCb(AvailabilityStatus eAvailabilityStatus) = 0;

    /*!
     * @brief   Callback to get notified about the avalability status of the
     *          TataAppleCarPlayPlugin proxy.
     * @param   eAvailabilityStatus - Status of TataAppleCarPlayPlugin proxy whether
     *          available or not.
     * @return  void.
     */
    virtual void appleCarPlayPluginSeriveStatusCb(AvailabilityStatus eAvailabilityStatus) = 0;

    /*!
     * @brief   Callback to get notified about the session details from
     *          AppleCarPlay proxy.
     * @param   sSessionDetails - Object of pprestypes::sSessionDetails
     * @return  void.
     */
    virtual void onSessionAttributeDetailsCb(pprestypes::sSessionDetails sSessionDetails) = 0;

    /*!
     * @brief   Callback to get notified about the connected device details from
     *          AppleCarPlay proxy.
     * @param   vectSDeviceDetails - Object of vector<pprestypes::sDevDetails>
     * @return  void.
     */
    virtual void onDeviceDetailsCb(const vector<pprestypes::sDevDetails> &vectSDeviceDetails) = 0;

    /**
     * @brief   onScreenOwnerCb: This callBack function will be hit when screen
     *          Owner Changes. Native ==> Projection or Projection ==> Native.
     *
     * @param   ownerType: ScreenOwner type: Projection or Native HMI
     * @return  void.
     */
    virtual void onScreenOwnerCb(const TataCarPlayPresPlugin::OwnerType &ownerType) = 0;

    /**
     * @brief   onPhoneOwnerCb: This callBack function will be hit when phone
     *          Owner Changes. for CarPlay active call, it updates the attribute
     *          to value 1
     * @param   ownerType: PhoneOwner type: Phone or Native HMI
     * @return  void.
     */
    virtual void onPhoneOwnerCb(const TataCarPlayPresPlugin::OwnerType &ownerType) = 0;

    /**
     * @brief   onNowPlayingDataAttributeCb: This function is called whenever
     *          NowPlayingAttribute gets change. This attribute is for CP Media's
     *          meta data.
     * @param   objsNowPlayingInfo: Object of sPluginNowPlayingInfo structure. This
     *          structure contains CP Media's Meta data info like title and artist
     * @return  void.
     */
    virtual void onNowPlayingDataAttributeCb(const TataCarPlayPresPlugin::sPluginNowPlayingInfo &objsNowPlayingInfo) = 0;

    /**
     * @brief   onSpeechOwnerCb: This callBack function will be hit when Voice activation
     *          Owner Changes between: No Voice Activation ==> Native ==> Projection.
     *
     * @param   ownerType: SpeechOwner type: No Voice Activation, Phone or Native HMI
     * @return  void.
     */
    virtual void onSpeechOwnerCb(const TataCarPlayPresPlugin::OwnerType &ownerType) = 0;


    /********************************************
     * @category RESPONSE CALLBACK METHODS
     ************************************************/
};

#endif // IAPPLECARPLAYRESOURCE_H
