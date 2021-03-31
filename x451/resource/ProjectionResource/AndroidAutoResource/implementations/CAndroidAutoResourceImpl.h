/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CAndroidAutoResourceImpl.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* CAndroidAutoResourceImpl, Resource Implementation for AndroidAuto.
*/
#ifndef CANDROIDAUTORESOURCEIMPL_H
#define CANDROIDAUTORESOURCEIMPL_H

#include "interfaces/IAndroidAutoResource.h"

/**
  * @category FORWAD_DECLARATION
  */
class CAndroidAutoEventProvider;

/**
 * @class   CAndroidAutoResourceImpl
 * @brief   This class shall implement AndroidAuto Resource intreface
 */
class CAndroidAutoResourceImpl: public IAndroidAutoResource
{
public:
    /*!
     * @brief   Destructor of CAndroidAutoResourceImpl
     * @param   void.
     * @return  void.
     */
    virtual ~CAndroidAutoResourceImpl();
    /**
     * @brief   Method to get the instance of CAndroidAutoEventProvider
     * @param   void
     * @return  CAndroidAutoEventProvider*
     */
    CAndroidAutoEventProvider* getAndroidAutoEventProvider();

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
    void requestProjection() override;

    /**
     * @brief   requestNative: Function to request the Native
     *          screen. Basically to stop the AndroidAuto projection. This
     *          function calls the AndroidAuto press's requestNative
     *          function.
     * @param   void.
     * @return  void
     */
    void requestNative() override;

    /**
     * @brief   reportKeyEvent: This function is used to report key press events
     *          to AndroidAuto plugin.
     * @param   uiKeyCode: KeyCode which needs to report.
     * @param   uiKeyState: KeyState, like press, release, longPress,
     *          longRelease.
     * @return  void.
     */
    void reportKeyEvent(const uint32_t &uiKeyCode, const uint32_t &uiKeyState) override;

    /**
     * @brief   toggleAapMediaAsync: This method is used to toggle the state of
     *          AndroidAuto media, it will toggle the state from play to pause
     *          and vice-versa.
     * @param   void.
     * @return  void.
     */
    void toggleAapMediaAsync() override;

    /**
     * @brief   pauseAapMediaAsync: This function will be used to pause the
     *          playing song for AndroidAuto Media.
     * @param   void.
     * @return  void.
     */
    void pauseAapMediaAsync() override;

    /**
     * @brief   playAapMediaAsync: This function will be used to play the
     *          song (which is in pause state) for AndroidAuto Media.
     * @param   void.
     * @return  void.
     */
    void playAapMediaAsync() override;

    /**
     * @brief   aapMediaNextAsync: This function is used to play Next Song,
     *          using SoftKey or touch next button available on Native HMI screen.
     * @param   void.
     * @return  void.
     */
    void aapMediaNextAsync() override;

    /**
     * @brief   aapMediaPreviousAsync: This function is used to play Previous
     *          Song, using SoftKey or touch previous button available on
     *          screen.
     * @param   void.
     * @return  void.
     */
    void aapMediaPreviousAsync() override;

    /**
     * @brief   aapShowAaMediaAsync: This function is used to launch the Android
     *          Auto music screen, Whenever required.
     * @param   void.
     * @return  void.
     */
    void aapShowAaMediaAsync() override;

    /**
     * @brief   getAAMediaMetaData: This method is used to get the Android Auto
     *          Media Meta Data.
     * @param   void.
     * @return  const SAAMediaMetaData&: Android Auto Media Meta Data.
     */
    const SAAMediaMetaData& getAAMediaMetaData() const
    {
        return m_objAAMediaMetaData;
    }

    /**
     * @brief   getAASessionDetails: This method is used to get the Android Auto
     *          session details.
     * @param   void.
     * @return  const SAASessionDetails&: Android Auto session details.
     */
    const SAASessionDetails& getAASessionDetails() override
    {
        return m_objAASessionDetails;
    }

    /**
     * @brief   getAANavigationNextTurnInfo: This method is used to get the Android Auto
     *          Navigation Next Turn info.
     * @param   void.
     * @return  const SAANaviNextTurnInfo&: Android Auto Navigation Next Turn details.
     */
    const SAANaviNextTurnInfo& getAANavigationNextTurnInfo() override
    {
        return m_objSAANaviNextTurnInfo;
    }

    /**
     * @brief   getAANavigationNextTurnDistInfo: This method is used to get the Android Auto
     *          Navigation Next Turn Distance info.
     * @param   void.
     * @return  const SAANaviNextTurnDistInfo&: Android Auto Navigation Next Turn Distance Info.
     */
    const SAANaviNextTurnDistInfo& getAANavigationNextTurnDistInfo() override
    {
        return m_objSAANaviNextTurnDistInfo;
    }

private:
    /**
    * @brief	CAndroidAutoResourceImpl::CAndroidAutoResourceImpl private
    *           constructor for class CAndroidAutoResourceImpl.
    * @param	void
    * @return	NA.
    **/
    CAndroidAutoResourceImpl();

    /*********************************************************//**
     *  @category   INTERNAL METHODS
     *********************************************************/
    /**
     * @brief Method to subscribe CallBack methods to events provided by
     *        AndroidAutoProxy
     * @param void
     * @return void
     */
    void subscribe();

    /**
     * @brief Method to subscribe CallBack methods to events provided by
     *        AndroidAutoPluginProxy
     * @param void
     * @return void
     */
    void subscribeAAPlugin();

    /*********************************************************//**
     *  @category   CALLBACK METHODS
     *********************************************************/

    /*!
     * @brief   Callback to get notified about the avalability status of the
     *          AndroidAuto proxy.
     * @param   eAvailabilityStatus - Status of AndroidAuto proxy whether available or not.
     * @return  void.
     */
    void androidAutoSeriveStatusCb(AvailabilityStatus eAvailabilityStatus) override;

    /*!
     * @brief   Callback to get notified about the avalability status of the
     *          AndroidAutoPlugin proxy.
     * @param   eAvailabilityStatus - Status of AndroidAuto proxy whether available or not.
     * @return  void.
     */
    void androidAutoPluginSeriveStatusCb(AvailabilityStatus eAvailabilityStatus) override;

    /**
     * @brief onFirstConnectionCb: This callBack function will be hit when any AA
     *        phone is connected for first time to HU. HMI will show the first
     *        run popup on this.
     * @param ucFirstRunParam: This will come as 1 if HMI needs to show first
     *        run popup, else 0
     * @return  void.
     */
    void onFirstConnectionCb(uint8_t ucFirstRunParam) override;

    /**
     * @brief onFunctionOwnerCb: This callBack function will be hit when function
     *        owner of any function like: screen, speech, audio and navigation
     *        gets changed, durin Android Auto session.
     * @param objSHuFunctions: Object of structure HuFunctions, which contains all
     *        function owner's details.
     * @return  void.
     */
    void onFunctionOwnerCb(
            const TataAndroidAutoPresPlugin::HuFunctions &objSHuFunctions) override;

    /**
     * @brief   onScreenOwnerCb: This callBack function will be hit when screen
     *          Owner Changes. Native ==> Projection or Projection ==> Native.
     *
     * @param   ownerType: ScreenOwner type: Phone or Native HMI
     * @return  void.
     */
    void onScreenOwnerCb(
            const TataAndroidAutoPresPlugin::OwnerType &ownerType) override;

    /**
     * @brief   onGetNavStatusTypeAttributeCb: This callBack function will be
     *          hit when Android Auto Navigation gets Activated or Deactivated.
     *
     * @param   navigationStatus: Navigation status active or not.
     * @return  void.
     */
    void onGetNavStatusTypeAttributeCb(
            const pprestypes::navigationStatusType &naviStatus) override;

    /**
     * @brief   onPlaybackStatusAttributeCb: This function called, Whenever
     *          PlaybackStatusAttribute gets changed.
     * @param   objsMediaPlaybackStatusUpdate: Object of
     *          sMediaPlaybackStatusUpdate, Which contains playState and all
     *          other info of Aandroid Auto Media.
     * @return  void.
     */
    void onPlaybackStatusAttributeCb(
            const pprestypes::sMediaPlaybackStatusUpdate
            &objsMediaPlaybackStatusUpdate) override;

    /**
     * @brief   onMetadataAttributeCb: This function is called whenever
     *          MetadataAttribute gets change. This attribute is for AA Media's
     *          meta data.
     * @param   objsMetaDataUpdate: Object of sMetaDataUpdate structure. This
     *          structure contains AA Media's Meta data info like songName,
     *          albumName, artistName,songAlbumArt, playlist, time, songRating.
     * @return  void.
     */
    void onMetadataAttributeCb(
            const pprestypes::sMetaDataUpdate &objsMetaDataUpdate) override;

    /**
     * @brief   onGetSessionAttributeCb: This function is called whenever
     *          SessionAttribute gets change. This attribute is for AA session
     *          details like Device name, bt address etc..
     * @param   objsSessionDetails: Object of sSessionDetails structure. This
     *          structure contains AA session details: devName, btAddres,
     *          usbSerialNo, isConnected, transport, status, remoteUI.
     * @return  void.
     */
    void onGetSessionAttributeCb( const pprestypes::sSessionDetails &objsSessionDetails ) override;

    /**
     * @brief   onNavTurnInfoAttributeCb: This function is called whenever
     *          TurnInfoAttribute gets change. This attribute is for AA Navigation
     *          Turn Info: like Turn side, road name etc..
     * @param   objsNaviNextTurnInfo: Object of sNaviNextTurnInfo structure.
     * @return  void.
     */
    virtual void onNavTurnInfoAttributeCb( const pprestypes::sNaviNextTurnInfo &objsNaviNextTurnInfo ) override;

    /**
     * @brief   onNavTurnDistInfoAttributeCb: This function is called whenever
     *          NavTurnDistInfoAttribute gets change. This attribute is for AA
     *          Navigatio Turn Distance Info.
     * @param   objsNaviNextTurnDistInfo: Object of sNaviNextTurnDistInfo structure.
     * @return  void.
     */
    virtual void onNavTurnDistInfoAttributeCb( const pprestypes::sNaviNextTurnDistInfo &objsNaviNextTurnDistInfo ) override;

    /**
     * @brief   onSpeechOwnerCb: This callBack function will be hit when voice activation
     *          Owner Changes between: No Voice Activation ==> Native ==> Projection.
     *
     * @param   ownerType: SpeechOwner type. No Voice Activation, Phone or Native HMI
     * @return  void.
     */
    void onSpeechOwnerCb(
            const TataAndroidAutoPresPlugin::OwnerType &ownerType) override;

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
     * @brief Pointer of CAndroidAutoEventProvider class to
     * emit signals to the AndroidAuto application layer.
     */
    CAndroidAutoEventProvider* m_pAndroidAutoEventProvider;

    /*!
     * @brief Instance of aaprescontrolsProxy class to communicate with
     * bt press control layer.
     */
    CAPIClientAbstraction<aaprescontrolsProxy> m_objAndroidAutoProxy;

    /*!
     * @brief Instance of TataAndroidAutoPresPluginProxy class to communicate with
     * bt AAPlugin layer.
     */
    CAPIClientAbstraction<TataAndroidAutoPresPluginProxy> m_objAndroidAutoPluginProxy;

    /*!
     * @brief Variable to hold the status of Android Auto proxy, It is available
     *        or not.
     */
    bool m_bIsAndroidAutoProxyAvailable;

    /*!
     * @brief Variable to hold the status of Android Auto Plugin proxy, It is
     *        available or not.
     */
    bool m_bIsAndroidAutoPluginProxyAvailable;

    /**
     * @brief m_objAAMediaMetaData: The Object of structure SAAMediaMetaData,
     *        Which contains Android Auto Media Meta data.
     */
    SAAMediaMetaData m_objAAMediaMetaData;

    /**
     * @brief m_objAASessionDetails: The Object of structure SAASessionDetails,
     *        Which contains Android Auto session details.
     */
    SAASessionDetails m_objAASessionDetails;

    /**
     * @brief m_objSAANaviNextTurnInfo: The Object of structure SAANaviNextTurnInfo.
     */
    SAANaviNextTurnInfo m_objSAANaviNextTurnInfo;

    /**
     * @brief m_objSAANaviNextTurnDistInfo: The Object of structure SAANaviNextTurnDistInfo.
     */
    SAANaviNextTurnDistInfo m_objSAANaviNextTurnDistInfo;

};

#endif // CANDROIDAUTORESOURCEIMPL_H
