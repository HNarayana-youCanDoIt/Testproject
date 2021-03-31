/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CAppleCarPlayResourceImpl.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* CAppleCarPlayResourceImpl, Resource Implementation for AppleCarPlay.
*/
#ifndef CAPPLECARPLAYRESOURCEIMPL_H
#define CAPPLECARPLAYRESOURCEIMPL_H

#include "interfaces/IAppleCarPlayResource.h"

class CAppleCarPlayEventProvider;

/**
 * @class CAppleCarPlayResourceImpl
 * @brief This class implements AppleCarPlay Resource intreface
 */
class CAppleCarPlayResourceImpl: public IAppleCarPlayResource
{
public:
    /*!
     * @brief   Destructor of CAppleCarPlayResourceImpl
     * @param   void.
     * @return  void.
     */
    virtual ~CAppleCarPlayResourceImpl();
    /**
     * @brief Method to get the instance of CAppleCarPlayEventProvider
     * @param void
     * @return CAppleCarPlayEventProvider*
     */
    CAppleCarPlayEventProvider* getAppleCarPlayEventProvider();

    /********************************************//**
     * @category REQUEST METHODS
     ************************************************/

    /**
     * @brief   requestProjection: Function to request the AppleCarPlay projection
     *          screen. Basically to launch the AppleCarPlay screen. This
     *          function calls the AppleCarPlay press's requestProjection
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
    void requestProjection(const string &appURL = "") override;

    /**
     * @brief   requestNative: Function to request the Native
     *          screen. Basically to stop the AppleCarPlay projection. This
     *          function calls the AppleCarPlay press's requestNative
     *          function.
     * @param   void.
     * @return  void
     */
    void requestNative() override;

    /**
     * @brief   reportKeyEvent: This function is used to report key press events
     *          to CarPlay plugin.
     * @param   uiKeyCode: KeyCode which needs to report.
     * @param   uiKeyState: KeyState, like press, release, longPress,
     *          longRelease.
     * @return  void.
     */
    void reportKeyEvent(const uint32_t &uiKeyCode, const uint32_t &uiKeyState) override;

    /**
     * @brief   getNowPlayingData: This method is used to get the CarPlay
     *          Media Meta Data.
     * @param   void.
     * @return  const CarPlayNowPlayingInfo&: CarPlay Media Meta Data.
     */
    virtual const CarPlayNowPlayingInfo& getNowPlayingData() override
    {
        return m_objNowPlayingInfo;
    }

    /**
     * @brief  setSmartFanState: This method is called from upper layer to send smart fan state request to CP resource.
     * @param  bSmartFanState: State of smart fan to be requested true / false.
     * @return void.
     */
    void setSmartFanState(bool bSmartFanState) override;

    /**
     * @brief  onSetSmartFanStateAsyncCb: This is a callback method to the setSmartFanstateAsync.
     * @param  status: Status of the API call, success or not.
     * @return void.
     */
    void onSetSmartFanStateAsyncCb(const CallStatus &status, bool bValue) override;

private:
    /**
    * @brief	CAppleCarPlayResourceImpl::CAppleCarPlayResourceImpl private
    *           constructor for class CAppleCarPlayResourceImpl.
    * @param	void
    * @return	NA.
    **/
    CAppleCarPlayResourceImpl();

    /*********************************************************//**
     *  @category   INTERNAL METHODS
     *********************************************************/
    /**
     * @brief Method to subscribe CallBack methods to events provided by
     *        AppleCarPlayProxy
     * @param void
     * @return void
     */
    void subscribe();

    /**
     * @brief Method to subscribe CallBack methods to events provided by
     *        CarPlayPluginProxy
     * @param void
     * @return void
     */
    void subscribeAppleCarPlayPlugin();

    /**
     * @brief  updateCPProxyStatus: This method updates the CP proxy status to upper layer.
     * @param  bCPProxyStatus: CP proxy status, true - available, false - not available.
     * @return void.
     */
    void updateCPProxyStatus(bool bCPProxyStatus);

    /*********************************************************//**
     *  @category   CALLBACK METHODS
     *********************************************************/

    /*!
     * @brief   Callback to get notified about the avalability status of the
     *          AppleCarPlay proxy.
     * @param   eAvailabilityStatus - Status of AppleCarPlay proxy whether
     *          available or not.
     * @return  void.
     */
    void appleCarPlaySeriveStatusCb(AvailabilityStatus eAvailabilityStatus) override;

    /*!
     * @brief   Callback to get notified about the avalability status of the
     *          TataAppleCarPlayPlugin proxy.
     * @param   eAvailabilityStatus - Status of TataAppleCarPlayPlugin proxy whether
     *          available or not.
     * @return  void.
     */
    void appleCarPlayPluginSeriveStatusCb(AvailabilityStatus eAvailabilityStatus) override;

    /*!
     * @brief   Callback to get notified about the session attribute details from
     *          AppleCarPlay proxy.
     * @param   sSessionDetails - Object of pprestypes::sSessionDetails
     * @return  void.
     */
    void onSessionAttributeDetailsCb(pprestypes::sSessionDetails sSessionDetails) override;

    /*!
     * @brief   Callback to get notified about the connected device details from
     *          AppleCarPlay proxy.
     * @param   vectSDeviceDetails - Object of vector<pprestypes::sDevDetails>
     * @return  void.
     */
    void onDeviceDetailsCb(const vector<pprestypes::sDevDetails> &vectSDeviceDetails) override;

    /**
     * @brief   onScreenOwnerCb: This callBack function will be hit when screen
     *          Owner Changes. Native ==> Projection or Projection ==> Native.
     *
     * @param   ownerType: ScreenOwner type: Phone or Native HMI
     * @return  void.
     */
    void onScreenOwnerCb(const TataCarPlayPresPlugin::OwnerType &ownerType) override;

    /**
     * @brief   onPhoneOwnerCb: This callBack function will be hit when phone
     *          Owner Changes. for CarPlay active call, it updates the attribute
     *          to value 1
     * @param   ownerType: ScreenOwner type: Phone or Native HMI
     * @return  void.
     */
    void onPhoneOwnerCb(const TataCarPlayPresPlugin::OwnerType &ownerType) override;

    /**
     * @brief   onNowPlayingDataAttributeCb: This function is called whenever
     *          NowPlayingAttribute gets change. This attribute is for CP Media's
     *          meta data.
     * @param   objsNowPlayingInfo: Object of sPluginNowPlayingInfo structure. This
     *          structure contains CP Media's Meta data info like title and artist
     * @return  void.
     */
    virtual void onNowPlayingDataAttributeCb(const TataCarPlayPresPlugin::sPluginNowPlayingInfo &objsNowPlayingInfo) override;

    /**
     * @brief   onSpeechOwnerCb: This callBack function will be hit when Voice activation
     *          Owner Changes between: No Voice Activation ==> Native ==> Projection.
     *
     * @param   ownerType: SpeechOwner type: No Voice Activation, Phone or Native HMI
     * @return  void.
     */
    void onSpeechOwnerCb(const TataCarPlayPresPlugin::OwnerType &ownerType) override;

    /*********************************************************//**
     *  @category   RESPONSE CALLBACK METHODS
     *********************************************************/

private:
    /**
     * @brief Adding ResourceFactory class as friend class so that
     * ResourceFactory shall be able to create the instance of this class.
     */
    friend class ResourceFactory;

    /*********************************************************//**
     *  @category   PROPERTIES
     *********************************************************/

    /*!
     * @brief Pointer of CAppleCarPlayEventProvider class to
     * emit signals to the AppleCarPlay application layer.
     */
    CAppleCarPlayEventProvider* m_pAppleCarPlayEventProvider;

    /*!
     * @brief Instance of aaprescontrolsProxy class to communicate with
     * bt press control layer.
     */
    CAPIClientAbstraction<cpprescontrolsProxy> m_objAppleCarPlayProxy;

    /*!
     * @brief Instance of TataCarPlayPresPluginProxy class to communicate with
     * CarPlayPlugin layer.
     */
    CAPIClientAbstraction<TataCarPlayPresPluginProxy> m_objAppleCarPlayPluginProxy;

    /*!
     * @brief Variable to hold the status of AppleCarPlay proxy, It is available
     *        or not.
     */
    bool m_bIsAppleCarPlayProxyAvailable;

    /*!
     * @brief Variable to hold the status of AppleCarPlay Plugin proxy, It is
     *        available or not.
     */
    bool m_bIsAppleCarPlayPluginProxyAvailable;

    /**
     * @brief m_objNowPlayingInfo: The Object of structure CarPlayNowPlayingInfo,
     *        Which contains CarPlay Media Now Playing info.
     */
    CarPlayNowPlayingInfo m_objNowPlayingInfo;

};

#endif // CAPPLECARPLAYRESOURCEIMPL_H
