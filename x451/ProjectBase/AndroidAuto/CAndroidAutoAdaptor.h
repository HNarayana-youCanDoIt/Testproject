/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CAndroidAutoAdaptor.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* This file is having the definition for Adaptor class of AndroidAuto,
* This is used by QML files to get the information needs to show on view.
*/

#ifndef CANDROIDAUTOADAPTOR_H
#define CANDROIDAUTOADAPTOR_H

#include "logging.h"
#include "CHMIMain.h"
#include "CAndroidAutoEnums.h"


/**
 * @category: Forward declaration.
 */
class CAndroidAutoResourceImpl;

/**
 * @class CAndroidAutoAdaptor
 * @brief The CAndroidAutoAdaptor class of AndroidAuto, This is used by QML
 * files to get the information needs to show on view.
 */
class CAndroidAutoAdaptor : public QObject
{
    Q_OBJECT

    /**
     * @brief Q_Property for android auto connection status, true if connected
     *        else false.
     */
    Q_PROPERTY(bool androidAutoConnectionStatus READ androidAutoConnectionStatus NOTIFY sigAndroidAutoConnectionStatusChanged)

    /**
     * @brief Q_Property for android auto bond req status, true if connected
     *        else false.
     */
    Q_PROPERTY(bool androidAutoBondReqStatus READ androidAutoBondReqStatus NOTIFY sigAndroidAutoBondReqStatusChanged)


    /**
     * @brief Q_Property for AndroidAuto projection status, true if
     *        projected else false.
     */
    Q_PROPERTY(bool androidAutoProjectionStatus READ androidAutoProjectionStatus NOTIFY sigAndroidAutoProjectionStatusChanged)

    /**
     * @brief Q_Property for AndroidAuto Media song Title.
     */
    Q_PROPERTY(QString aaMediaSongTitle READ aaMediaSongTitle NOTIFY sigAAMediaSongTitleChanged)

    /**
     * @brief Q_Property for AndroidAuto Media song Artist.
     */
    Q_PROPERTY(QString aaMediaSongArtist READ aaMediaSongArtist NOTIFY sigAAMediaSongArtistChanged)

    /**
     * @brief Q_Property for AndroidAuto Media play state.
     */
    Q_PROPERTY(CAndroidAutoEnums::EAAMediaPlayState aaMediaPlayState READ aaMediaPlayState NOTIFY sigAAMediaPlayStateChanged)

    /**
     * @brief Q_Property for OKGoogle (AndroidAuto Voice Recognition) status,
     *        true if active else false.
     */
    Q_PROPERTY(bool okGoogleStatus READ okGoogleStatus NOTIFY sigOKGoogleStatusChanged)

    /**
     * @brief Q_Property for Android Auto Navigation status, true if active else
     *        false.
     */
    Q_PROPERTY(bool aaNaviStatus READ aaNaviStatus NOTIFY sigAANaviStatusChanged)

    /**
     * @brief Q_Property for Android Auto Navigation popup title text.
     */
    Q_PROPERTY(QString aaNaviPopupTitle READ aaNaviPopupTitle NOTIFY sigAANaviPopupTitleChanged)

    /**
     * @brief Q_Property for Android Auto Navigation popup text.
     */
    Q_PROPERTY(QString aaNaviPopupText READ aaNaviPopupText NOTIFY sigAANaviPopupTextChanged)

    /**
     * @brief Q_Property for Android Auto Navigation popup Image source path.
     */
    Q_PROPERTY(QString aaNaviPopupImage READ aaNaviPopupImage NOTIFY sigAANaviPopupImageChanged)

    /**
     * @brief Q_Property for Android Auto Navigation Distance with unit text.
     */
    Q_PROPERTY(QString aaNaviDistance READ aaNaviDistance NOTIFY sigAANaviDistanceChanged)

public:
    /**
    * @brief	CAndroidAutoAdaptor::getInstance is static method used to get
    *           instance of singleton class CAndroidAutoAdaptor
    * @param	void.
    * @return	CAndroidAutoAdaptor pointer.
    **/
    static CAndroidAutoAdaptor * getInstance();

    /**
    * @brief	CAndroidAutoAdaptor::setAndroidAutoConnectionStatus is setter
    *           function of androidAutoConnectionStatus property.
    * @param	const bool bAAConnectionStatus: AndroidAuto connection status,
    *           true if connected else false.
    * @return	void.
    **/
    void setAndroidAutoConnectionStatus(const bool bAAConnectionStatus);

    /**
    * @brief	CAndroidAutoAdaptor::setAndroidAutoBondReqStatus is setter
    *           function of androidBondReqStatus property.
    * @param	const bool bAAConnectionStatus: AndroidAuto BondReq status,
    *           true if connected else false.
    * @return	void.
    **/
    void setAndroidAutoBondReqStatus(const bool bAABondReqStatus);


    /**
    * @brief	CAndroidAutoAdaptor::setAndroidAutoProjectionStatus is setter
    *           function of androidAutoProjectionStatus property.
    * @param	const bool &bAAProjectionStatus: AndroidAuto connection status,
    *           true if projected else false.
    * @return	void.
    **/
    void setAndroidAutoProjectionStatus(const bool bAAProjectionStatus);

    /**
    * @brief	CAndroidAutoAdaptor::androidAutoConnectionStatus is getter
    *           function of androidAutoConnectionStatus property.
    * @param	void.
    * @return	const bool &bAAConnectionStatus: AndroidAuto connection status,
    *           true if connected else false.
    **/
    bool androidAutoConnectionStatus() const
    {
        return m_bAndroidAutoConnectionStatus;
    }

    /**
    * @brief	CAndroidAutoAdaptor::androidAutoBondReqStatus is getter
    *           function of androidAutoBondReqStatus property.
    * @param	void.
    * @return	const bool &bAABondReqStatus: AndroidAuto BondReq status,
    *           true if connected else false.
    **/
    bool androidAutoBondReqStatus() const
    {
        return m_bAndroidAutoBondReqStatus;
    }

    /**
    * @brief	CAndroidAutoAdaptor::androidAutoProjectionStatus is getter
    *           function of androidAutoProjectionStatus property.
    * @param	void.
    * @return	m_bAndroidAutoProjectionStatus: AndroidAuto
    *           projection status, true if projected else false.
    **/
    bool androidAutoProjectionStatus() const
    {
        return m_bAndroidAutoProjectionStatus;
    }

    /**
     * @brief   aaMediaSongTitle: Getter for aaMediaSongTitle property.
     * @return  Currently playing song title.
     */
    const QString& aaMediaSongTitle()
    {
        return m_strAAMediaSongTitle;
    }

    /**
     * @brief setAAMediaSongTitle: setter function for currently playing song
     *        title for Android Auto Media.
     * @param strAAMediaSongTitle: currently playing song title for Android Auto
     *        Media.
     */
    void setAAMediaSongTitle(const QString &strAAMediaSongTitle);

    /**
     * @brief   aaMediaSongArtist: Getter for aaMediaSongArtist property.
     * @return  Currently playing song title.
     */
    const QString& aaMediaSongArtist()
    {
        return m_strAAMediaSongArtist;
    }

    /**
     * @brief setAAMediaSongArtist: setter function for currently playing song's
     *        artist name for Android Auto Media.
     * @param strAAMediaSongArtist: currently playing song's artist name for
     *        Android Auto Media.
     */
    void setAAMediaSongArtist(const QString &strAAMediaSongArtist);

    /**
     * @brief   aaMediaPlayState: Getter for AndroidAuto Media play state, true
     *          if playing else false.
     * @param   void.
     * @return  AndroidAuto Media play state.
     */
    CAndroidAutoEnums::EAAMediaPlayState aaMediaPlayState() const
    {
        return m_eAAMediaPlayState;
    }

    /**
     * @brief   setAAMediaPlayState: setter for aaMediaPlayState property.
     * @param   usAAMediaPlayState: AA media playState.
     * @return  void.
     */
    void setAAMediaPlayState(CAndroidAutoEnums::EAAMediaPlayState eAAMediaPlayState);

    /**
     * @brief   okGoogleStatus: Getter for OKGoogle status.
     * @param   void
     * @return  OKGoogleStatus: true if active, else false.
     */
    bool okGoogleStatus() const
    {
        return m_bOKGoogleStatus;
    }

    /**
     * @brief   setOKGoogleStatus: Setter for okGoogleStatus property.
     * @param   bOKGoogleStatus: OKGoogle Status, true if active, else false.
     * @return  void.
     */
    void setOKGoogleStatus(bool bOKGoogleStatus);

    /**
     * @brief   aaNaviStatus: Getter for Android Auto Navigation status.
     * @param   void
     * @return  m_bAANaviStatus: true if active, else false.
     */
    bool aaNaviStatus() const
    {
        return m_bAANaviStatus;
    }

    /**
     * @brief   setAANaviStatus: setter for aaNaviStatus property.
     * @param   bAANaviStatus: AA Navigation Status, true if active, else false.
     * @return  void.
     */
    void setAANaviStatus(bool bAANaviStatus);

    /**
     * @brief   aaNaviPopupTitle: Getter for property aaNaviPopupTitle.
     * @param   void.
     * @return  Android Auto Navigation popup Title.
     */
    QString aaNaviPopupTitle() const
    {
        return m_strAANaviPopupTitle;
    }

    /**
     * @brief   setAANaviPopupTitle: Setter for propert aaNaviPopupTitle.
     * @param   strAANaviPopupTitle: Popup Title needs to be updated.
     * @return  Void.
     */
    void setAANaviPopupTitle(const QString &strAANaviPopupTitle);

    /**
     * @brief   aaNaviPopupText: Getter for property aaNaviPopupText.
     * @param   void.
     * @return  Android Auto Navigation popup Text.
     */
    QString aaNaviPopupText() const
    {
        return m_strAANaviPopupText;
    }

    /**
     * @brief   setAANaviPopupText: Setter for propert aaNaviPopupText.
     * @param   strAANaviPopupText: Popup Text needs to be updated.
     * @return  Void.
     */
    void setAANaviPopupText(const QString &strAANaviPopupText);

    /**
     * @brief   aaNaviPopupImage: Getter for property aaNaviPopupImage.
     * @param   void.
     * @return  Android Auto Navigation popup Image Source.
     */
    QString aaNaviPopupImage() const
    {
        return m_strAANaviPopupImage;
    }

    /**
     * @brief   setAANaviPopupImage: Setter for propert aaNaviPopupImage.
     * @param   strAANaviPopupImage: Popup Image source needs to be updated.
     * @return  Void.
     */
    void setAANaviPopupImage(const QString &strAANaviPopupImage);


    /**
     * @brief   aaNaviPopupImage: Getter for property aaNaviPopupImage.
     * @param   void.
     * @return  Android Auto Navigation popup Image Source.
     */
    QString aaNaviDistance() const
    {
        return m_strAANaviDistance;
    }

    /**
     * @brief   setAANaviPopupImage: Setter for property aaNaviDistance.
     * @param   setAANaviDistance: Android Auto Navigation distance needs to be updated.
     * @return  Void.
     */
    void setAANaviDistance(const QString &strAANaviDistance);

    /**
    * @brief    CAndroidAutoAdaptor::handleHardKeys Funtion to handle hardkey
    *           as per AndroidAuto specifications.
    * @param    eKey: The key on which the action is triggered.
    * @param    eKeyState: State of the key on which the action is triggered.
    * @return   true if an action was taken false otherwise.
    */
    bool handleHardKeys(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState);

    /**
     * @brief   updateAAMediaMetaData: This function is used to update Android
     *          Auto Media Meta Data.
     * @param   void.
     * @return  void.
     */
    void updateAAMediaMetaData();

    /**
     * @brief   updateAASessionDetails: This function is used to update Android
     *          Auto session details.
     * @param   void.
     * @return  void.
     */
    void updateAASessionDetails();

    /**
     * @brief   updateAANavigationDetails: This function is used to update Android
     *          Auto Navigation Turn Event details.
     * @param   void.
     * @return  void.
     */
    void updateAANaviTurnEventDetails();

    /**
     * @brief   updateAANaviDistanceDetails: This function is used to update Android
     *          Auto Navigation Distance details.
     * @param   void.
     * @return  void.
     */
    void updateAANaviDistanceDetails();

    /**
     * @brief   getAATransientStateStatus: Method to get the transient state status.
     * @param   void.
     * @return  transient state status, TRUE if transition has happened from AA
     *          to PDC/RVC, FALSE otherwise.
     */
    bool getAATransientStateStatus() { return m_bAATransientStateStatus; }

    /**
     * @brief   setAATransientState: Method to be invoked to set the transient state.
     * @param   bTransientState: transient state status, shall be set to TRUE if the
     *          transition is from AA to PDC/RVC, FALSE otherwise.
     * @return  void.
     */
    void setAATransientState(bool bAATransientState) { m_bAATransientStateStatus = bAATransientState; }

    /**
    * @brief    CAndroidAutoAdaptor::requestNative is Q_INVOKABLE, Which
    *           will be called, When user wants to go to Native screen. Like:
    *           When user pressed Home hadkey to go to Native HMI screen.
    * @param    void.
    * @return   void
    */
    Q_INVOKABLE void requestNative();

    /**
    * @brief    CAndroidAutoAdaptor::launchAndroidAuto is Q_INVOKABLE, Which
    *           will be called, When user wants to go to AndroidAuto screen.
    *           Like: When user pressed AndroidAuto Icon on Home screen.
    * @param    void.
    * @return   void
    */
    Q_INVOKABLE void launchAndroidAuto();

    /**
    * @brief    CAndroidAutoAdaptor::next is Q_INVOKABLE, Which
    *           will be called, When user wants to play next song using
    *           interface present on HMI. Like: from QAD
    * @param    void.
    * @return   void
    */
    Q_INVOKABLE void next();

    /**
    * @brief    CAndroidAutoAdaptor::next is Q_INVOKABLE, Which
    *           will be called, When user wants to play previous song using
    *           interface present on HMI. Like: from QAD
    * @param    void.
    * @return   void
    */
    Q_INVOKABLE void prev();

    /**
    * @brief    CAndroidAutoAdaptor::togglePlayPause is Q_INVOKABLE, Which
    *           will be called, When user wants to toggle the play/Pause using
    *           interface present on HMI. Like: from QAD.
    *           If song is in playState QAD shows pause button, and on press of
    *           pause button QML calls this function to make it pause. same
    *           behaviour for play
    * @param    void.
    * @return   void
    */
    Q_INVOKABLE void togglePlayPause();

    /**
     * @brief   showAAMusicScreen: This function is used to launch AmdroidAuto
     *          music screen, Whenever required to show.
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void showAAMusicScreen();

    /**
     * @brief   setCanSwitchMode: This function is used to set the status
     *          of m_bCanSwitchMode value.
     * @param   bCanSwitchMode: This will be true, Whenever HMI needs
     *          to change the mode from AndroidAuto to  Native HMI and from
     *          Native HMI to Android Auto. (Basically this is used in case of
     *          source Toggle, When Android Auto is connected.)
     * @return  void.
     */
    Q_INVOKABLE void setCanSwitchMode(bool bCanSwitchMode);

signals:

    /**
    * @brief	CAndroidAutoAdaptor::sigAndroidAutoConnectionStatusChanged is a
    *           notify signal to notify androidAutoConnectionStatus property
    *           changes to qml
    * @param	void.
    * @return	void.
    **/
    void sigAndroidAutoConnectionStatusChanged(
            bool bAndroidAutoConnectionStatus
            );

    /**
    * @brief	CAndroidAutoAdaptor::sigAndroidAutoBondReqStatusChanged is a
    *           notify signal to notify androidAutoBondReqStatus property
    *           changes to qml
    * @param	void.
    * @return	void.
    **/
    void sigAndroidAutoBondReqStatusChanged(
            bool bAndroidAutoBondReqStatus
            );

    /**
    * @brief	CAndroidAutoAdaptor::sigAndroidAutoProjectionStatusChanged is a
    *           notify signal to notify androidAutoProjectionStatus property
    *           changes.
    * @param	void.
    * @return	void.
    **/
    void sigAndroidAutoProjectionStatusChanged(
            bool bAndroidAutoProjectionStatus
            );

    /**
     * @brief sigAAMediaSongTitleChanged: signal to notify the changes in
     *        aaMediaSongTitle property
     */
    void sigAAMediaSongTitleChanged();

    /**
     * @brief sigAAMediaSongArtistChanged: signal to notify the changes in
     *        aaMediaSongArtist property
     */
    void sigAAMediaSongArtistChanged();

    /**
     * @brief sigAAMediaPlayStateChanged: signal to notify the changes in
     *        aaMediaPlayState property.
     */
    void sigAAMediaPlayStateChanged();

    /**
     * @brief   sigOKGoogleStatusChanged: signal to notify the changes in
     *          okGoogleStatus property.
     * @param   void.
     * @return  void.
     */
    void sigOKGoogleStatusChanged();

    /**
     * @brief   sigAANaviStatusChanged: signal to notify the changes in
     *          aaNaviStatus property.
     * @param   void.
     * @return  void.
     */
    void sigAANaviStatusChanged();

    /**
     * @brief sigAANaviPopupTitleChanged: signal to notify the changes in
     *          aaNaviPopupTitle property.
     */
    void sigAANaviPopupTitleChanged();

    /**
     * @brief sigAANaviPopupTextChanged: signal to notify the changes in
     *          aaNaviPopupText property.
     */
    void sigAANaviPopupTextChanged();

    /**
     * @brief sigAANaviPopupImageChanged: signal to notify the changes in
     *          aaNaviPopupImage property.
     */
    void sigAANaviPopupImageChanged();

    /**
     * @brief sigAANaviDistanceChanged: signal to notify the changes in
     *          aaNaviDistance property.
     */
    void sigAANaviDistanceChanged();

public slots:

    /**
     * @brief   slotActiveAudioSourceListUpdated: Slot Which checks, What is the
     *          active Audio source.
     * @param   void.
     * @return  void.
     */
    void slotActiveAudioSourceListUpdated();

    /**
     * @brief   slotActiveEntSourceChanged: This function is called Whenever,
     *          Active Entertainment source gets changed. This is a slot function
     *          which is connected to sigActiveEntSrcChanged() of AudioAdaptor.
     *          This slot calls resource api to launch Android Auto music screen,
     *          if source SRC_GAL_MEDIA is gets Activated.
     * @param   void.
     * @return  void.
     */
    void slotActiveEntSourceChanged();

private:
    /*!
     * @brief   Destructor of CAndroidAutoAdaptor
     * @param   void.
     * @return  void.
     */
    ~CAndroidAutoAdaptor();

    /**
    * @brief	CAndroidAutoAdaptor::CAndroidAutoAdaptor private constructor for
    *           singleton class CAndroidAutoAdaptor.
    * @param	QObject parent.
    * @return	NA.
    **/
    explicit CAndroidAutoAdaptor(QObject *pParent = nullptr);

    /**
    * @brief	CAndroidAutoAdaptor::isAndroidAutoResourceReady is to check
    *           that the AndroidAuto resource is not NULL.
    * @param	void.
    * @return	Returns true if resource is not NULL else false.
    **/
    bool isAndroidAutoResourceReady();

    /**
    * @brief    CAndroidAutoAdaptor::requestAAProjection is a private function
    *           Which is called to make call to AA resource to launch Android
    *           Auto projection.
    * @param    void.
    * @return   void
    */
    void requestAAProjection();

    /**
     * @brief   connectSignals: This function connects the signals of another
     *          adaptors.
     * @param   void.
     * @return  void.
     */
    void connectSignals();

    /**
     * @brief   disconnectSignals: This function disConnects the signals of
     *          another adaptors.
     * @param   void.
     * @return  void.
     */
    void disconnectSignals();

    /**
     * @brief   reportKeyEventToResource: Function to report Keys to resource
     *          Layer.
     * @param   eKey: Key Code, Which is pressed.
     * @param   eKeyState: Key State of Pressed key.
     * @return  void.
     */
    void reportKeyEventToResource(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState);

    /**
     * @brief   resetData: This function is used to reset all local data to
     *          default values. If Android Auto disconneted.
     * @param   void.
     * @return  void.
     */
    void resetData();

    /**
     * @brief   goToNativeHome: This function is internal function used to go to
     *          Native HMI Home screen. This is called when AA connection gets
     *          disconnected or Projection gets deactivated or HMI requests
     *          native.
     * @param   void.
     * @return  void.
     */
    void goToNativeHome();

    /**************************************************//**
    * @category PROPERTIES
    ******************************************************/

    /*!
     * @brief Singolton Instance pointer for CAndroidAutoAdaptor
     */
    static CAndroidAutoAdaptor *m_pAndroidAutoAdaptor;

    /*!
     * @brief Instance of IAndroidAutoResource
     */
    CAndroidAutoResourceImpl *m_pAndroidAutoResource;

    /**
     * @brief m_pAudioResource: Audio Resource instances.
     */
    IAudioResource* m_pAudioResource;

    /*!
     * @brief Variable to hold the AndroidAuto connection status.
     */
    bool m_bAndroidAutoConnectionStatus;

    /*!
     * @brief Variable to hold the AndroidAuto bond req status.
     */
    bool m_bAndroidAutoBondReqStatus;

    /*!
     * @brief Variable to hold the AndroidAuto projection status.
     */
    bool m_bAndroidAutoProjectionStatus;

    /**
     * @brief m_strAAMediaSongTitle: Currently playing song title.
     */
    QString m_strAAMediaSongTitle;

    /**
     * @brief m_strAAMediaSongArtist: Currently playing song Artist.
     */
    QString m_strAAMediaSongArtist;

    /**
     * @brief m_eAAMediaPlayState: PlayState for AA Media
     */
    CAndroidAutoEnums::EAAMediaPlayState m_eAAMediaPlayState;

    /**
     * @brief m_bOKGoogleStatus: OK Google status: true if active else false.
     */
    bool m_bOKGoogleStatus;

    /**
     * @brief m_bAANaviStatus: Android Auto Navigation status: true if active
     *         else false.
     */
    bool m_bAANaviStatus;

    /**
     * @brief m_bCanSwitchMode: Variable to hold the value can HMI
     *        switch to Android Auto music screen and Android Auto to Native HMI
     *        Active source Screen. ( Basically this is used in case of toggle
     *        source.)
     */
    bool m_bCanSwitchMode;

	/**
     * @brief m_strAADeviceBtAddress: This variable stores the bt address of the
     *        connected Android Auto device.
     */
    QString m_strAADeviceBtAddress;

    /**
     * @brief   m_bAATransientStateStatus: Property to store the status of transient state,
     *          this flag shall be set to true when transition is from AA state to PDC/RVC
     *          state and shall be set to false when the transition is back to AA state from
     *          PDC/RVC state. This flag shall also be set to false it the AA device is
     *          disconnected(connectionStatus is received as false)
     */
    bool m_bAATransientStateStatus;

    /**
     * @brief m_strAANaviPopupTitle: This variable holds the Android Auto Navigation Popup Title.
     */
    QString m_strAANaviPopupTitle;

    /**
     * @brief m_strAANaviPopupText: This variable holds the Android Auto Navigation Popup Text.
     */
    QString m_strAANaviPopupText;

    /**
     * @brief m_strAANaviPopupImage: This variable holds the Android Auto Navigation Popup Image
     *        source, Which needs to be shown on AA Navigation popup.
     */
    QString m_strAANaviPopupImage;

    /**
     * @brief m_strAANaviDistance: This variable holds the Navigation distance
     *        with unit string.
     */
    QString m_strAANaviDistance;
};

#endif // CANDROIDAUTOADAPTOR_H
