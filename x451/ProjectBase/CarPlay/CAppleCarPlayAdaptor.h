/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CAppleCarPlayAdaptor.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* This file is having the definition for Adaptor class of AppleCarPlay,
* This is used by QML files to get the information needs to show on view.
*/

#ifndef CAPPLECARPLAYADAPTOR_H
#define CAPPLECARPLAYADAPTOR_H

#include "logging.h"
#include "CHMIMain.h"
#include "CAppleCarPlayEnums.h"
#include "HardkeyResource/implementations/CHardkeyEnums.h"

/* Below private static const string identifiers to be used as contant string laterals in requestCarPlayProjection() param*/
const string CP_URL_MAPS = "maps:"; // URL without start and end double quotes i.e. "maps:"
const string CP_URL_MOBILEPHONE = "mobilephone:"; // URL without start and end double quotes i.e. "mobilephone:"
const string CP_URL_MUSIC = "music:"; // URL without start and end double quotes i.e. "music:"
const string CP_URL_NOWPLAYING = "nowplaying:"; // URL without start and end double quotes i.e. "nowplaying:"

/**
 * @category: Forward declaration.
 */
class CAppleCarPlayResourceImpl;

/**
 * @class CAppleCarPlayAdaptor
 * @brief The CAppleCarPlayAdaptor class of AppleCarPlay, This is used by QML
 * files to get the information needs to show on view.
 */

class CAppleCarPlayAdaptor : public QObject
{
    Q_OBJECT

    /*
     * Property for AppleCarPlay connection status, true if connected else false.
     */
    Q_PROPERTY(bool appleCarPlayConnectionStatus READ appleCarPlayConnectionStatus NOTIFY sigAppleCarPlayConnectionStatusChanged)

    /**
     * @brief Property for AppleCarPlay projection status, true if projected else false.
     */
    Q_PROPERTY(bool appleCarPlayProjectionStatus READ appleCarPlayProjectionStatus NOTIFY sigAppleCarPlayProjectionStatusChanged)

    /**
     * @brief Q_Property for CarPlay Media song Title.
     */
    Q_PROPERTY( QString cpMediaSongTitle READ cpMediaSongTitle NOTIFY sigCPMediaSongTitleChanged)

    /**
     * @brief Q_Property for CarPlay Media song Artist.
     */
    Q_PROPERTY( QString cpMediaSongArtist READ cpMediaSongArtist  NOTIFY sigCPMediaSongArtistChanged)

    /**
     * @brief Property for Connected AppleCarPlay Device Name.
     */
    Q_PROPERTY(QString appleCarPlayDeviceName READ appleCarPlayDeviceName NOTIFY sigAppleCarPlayDeviceNameChanged)

    /**
     * @brief Property for smart fan status, true if smart fan is enabled else false.
     */
    Q_PROPERTY(bool smartFanState READ smartFanState NOTIFY sigSmartFanStateChanged)

public:
    /**
    * @brief	CAppleCarPlayAdaptor::getInstance is static method used to get
    *           instance of singleton class CAppleCarPlayAdaptor
    * @param	void.
    * @return	CAppleCarPlayAdaptor pointer.
    **/
    static CAppleCarPlayAdaptor * getInstance();

    /**
    * @brief	CAppleCarPlayAdaptor::setAppleCarPlayConnectionStatus is setter
    *           function of appleCarPlayConnectionStatus property.
    * @param	const bool bAppleCarPlayConnectionStatus: AppleCarPlay connection status,
    *           true if connected else false.
    * @return	void.
    **/
    void setAppleCarPlayConnectionStatus(const bool bAppleCarPlayConnectionStatus);

    /**
    * @brief	CAppleCarPlayAdaptor::setAppleCarPlayProjectionStatus is setter
    *           function of appleCarPlayProjectionStatus property.
    * @param	const bool bAppleCarPlayConnectionStatus: AppleCarPlay projection status,
    *           true if projected else false.
    * @return	void.
    **/
    void setAppleCarPlayProjectionStatus(const bool bAppleCarPlayProjectionStatus);

    /**
    * @brief	CAppleCarPlayAdaptor::setAppleCarPlayPhoneStatus is setter
    *           function of appleCarPlayPhoneStatus property.
    * @param	const bool bAppleCarPlayPhoneStatus: AppleCarPlay phone status,
    *           true if phone(active call/ incoming call) is active else false.
    * @return	void.
    **/
    void setAppleCarPlayPhoneStatus(const bool bAppleCarPlayPhoneStatus);

    /**
    * @brief	CAppleCarPlayAdaptor::getAppleCarPlayPhoneStatus is getter
    *           function of appleCarPlayPhoneStatus property.
    * @param	void.
    * @return	bool m_bAppleCarPlayPhoneStatus: Apple Car Play active phone status.
    **/
    bool getAppleCarPlayPhoneStatus() { return m_bAppleCarPlayPhoneStatus; }

    /**
    * @brief	CAppleCarPlayAdaptor::setCarPlaySiriStatus is setter
    *           function of carPlaySiriStatus property.
    * @param	const bool bCarPlaySiriStatus: CarPlay Siri status,
    *           true if Siri is active else false.
    * @return	void.
    **/
    void setCarPlaySiriStatus(const bool bCarPlaySiriStatus);

    /**
    * @brief	CAppleCarPlayAdaptor::carPlaySiriStatus is getter
    *           function of carPlaySiriStatus property.
    * @param	void.
    * @return	bool m_bCarPlaySiriStatus: Car Play Siri status.
    **/
    bool carPlaySiriStatus() { return m_bCarPlaySiriStatus; }

    /**
    * @brief	CAppleCarPlayAdaptor::setAppleCarPlayDeviceName is setter
    *           function of appleCarPlayDeviceName property.
    * @param	strAppleCarPlayDeviceName: AppleCarPlay DeviceName.
    * @return	void.
    **/
    void setAppleCarPlayDeviceName(const QString &strAppleCarPlayDeviceName);

    /**
    * @brief	CAppleCarPlayAdaptor::setAppleCarPlayRemoteUIStatus is setter
    *           function of appleCarPlayRemoteUIStatus property.
    * @param	bAppleCarPlayRemoteUIStatus: AppleCarPlay Remote UI Status.
    * @return	void.
    **/
    void setAppleCarPlayRemoteUIStatus(bool bAppleCarPlayRemoteUIStatus);

    /**
    * @brief	CAppleCarPlayAdaptor::appleCarPlayConnectionStatus is getter
    *           function of appleCarPlayConnectionStatus property.
    * @param	void.
    * @return	const bool &m_bAppleCarPlayConnectionStatus: AppleCarPlay
    *           connection status, true if connected else false.
    **/
    bool appleCarPlayConnectionStatus() const { return m_bAppleCarPlayConnectionStatus; }

    /**
    * @brief	CAppleCarPlayAdaptor::appleCarPlayProjectionStatus is getter
    *           function of appleCarPlayProjectionnStatus property.
    * @param	void.
    * @return	m_bAppleCarPlayProjectionStatus: AppleCarPlay
    *           projection status, true if projected else false.
    **/
    bool appleCarPlayProjectionStatus() const { return m_bAppleCarPlayProjectionStatus; }

    /**
     * @brief   cpMediaSongTitle: Getter for cpMediaSongTitle property.
     * @param void.
     * @return  Currently playing song title.
     */
    const QString& cpMediaSongTitle()
    {
        return m_strCPMediaSongTitle;
    }

    /**
     * @brief setCPMediaSongTitle: setter function for currently playing song
     *        title for CarPlay Media.
     * @param strCPMediaSongTitle: currently playing song title for CarPlay
     *        Media.
     * @return void.
     */
    void setCPMediaSongTitle(const QString &strCPMediaSongTitle);

    /**
     * @brief   cpMediaSongArtist: Getter for cpMediaSongArtist property.
     * @param void.
     * @return  Currently playing song title.
     */
    const QString& cpMediaSongArtist()
    {
        return m_strCPMediaSongArtist;
    }

    /**
     * @brief setCPMediaSongArtist: setter function for currently playing song's
     *        artist name for CarPlay Media.
     * @param strCPMediaSongArtist: currently playing song's artist name for
     *        CarPlay Media.
     * @return void.
     */
    void setCPMediaSongArtist(const QString &strCPMediaSongArtist);

    /**
    * @brief	CAppleCarPlayAdaptor::appleCarPlayDeviceName is getter
    *           function of appleCarPlayDeviceName property.
    * @param	void.
    * @return	m_strAppleCarPlayDeviceName: Connected AppleCarPlay DeviceName.
    **/
    QString appleCarPlayDeviceName() const { return m_strAppleCarPlayDeviceName; }

    /**
    * @brief    CAppleCarPlayAdaptor::handleHardKeys Funtion to handle hardkey
    *           as per AppleCarPlay specifications.
    * @param    eKey: The key on which the action is triggered.
    * @param    eKeyState: State of the key on which the action is triggered.
    * @return   true if an action was taken false otherwise.
    */
    bool handleHardKeys(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState);

    /**
     * @brief   updateCPNowPlayingInfo: This function is used to update CarPlay
     *  Media Meta Data.
     * @param   void.
     * @return  void.
     */
    void updateCPNowPlayingInfo();

    /**
     * @brief smartFanState : This method is used to get the smart fan state.
     * @param  void.
     * @return smartFanState : holds true if smart fan enabled else false
     */
    bool smartFanState()  const { return m_bSmartFanState;}
    /**
     * @brief  updateSmartFanState: This method contains the call status of smart fan,
     *          if status is true requested value is updated to model & persistence.
     * @param  bValue: Smart fan state, value holds the Enable state of Fan,
     *                 like If smart Fan is enabled then true else false.
     * @return void.
     */
    void updateSmartFanState(bool bValue);

    /**
     * @brief updateCPProxyStatus: This method contains the CP proxy status, if CP proxy is available,
     *           this method reads the smart fan state from persistence and requests the CP proxy to set the same.
     * @param bCPProxyStatus: CP proxy status, true - available, false - not available.
     * @return void.
     */
    void updateCPProxyStatus(bool bCPProxyStatus);

    /**
    * @brief    CAppleCarPlayAdaptor::requestNative is Q_INVOKABLE, Which
    *           will be called, When user wants to go to Native screen. Like:
    *           When user pressed Home hadkey to go to Native HMI screen.
    * @param    void.
    * @return   void
    */
    Q_INVOKABLE void requestNative();

    /**
    * @brief    CAppleCarPlayAdaptor::launchAppleCarPlay is Q_INVOKABLE, Which
    *           will be called, When user wants to go to AppleCarPlay screen.
    *           Like: When user pressed AppleCarPlay icon on Home screen.
     * @param   appURL : URL identifier of the desired CarPlay UI application to launch:
     *          Blank String: last active CarPlay screen will be shown (by default Native)
     *          "maps:" - Carplay Maps application will be shown
     *          "mobilephone:" - CarPlay Phone application will be shown
     *          "music:" - CarPlay Music application will be shown
     *          "nowplaying:" - CarPlay Now Playing screen will be shown
     *          "tel:xxx-xxx-xxxx" - CarPlay Phone application will be shown and a phone call with desired number will be placed..
    * @return   void
    */
    Q_INVOKABLE void launchAppleCarPlay(const string &appURL = "");

    /**
     * @brief   showCPMusicScreen: This function is used to launch Car Play
     *          music screen, Whenever required to show.
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void showCPMusicScreen();

    /**
     * @brief   setIsCPSwitchable: This function is used to set the status
     *          of m_bIsCPSwitchable value.
     * @param   bIsCPSwitchable: This will be true, Whenever HMI needs
     *          to change the mode from CarPlay to  Native HMI and from
     *          Native HMI to CarPlay. (Basically this is used in case of
     *          source Toggle, When CarPlay is connected.)
     * @return  void.
     */
    Q_INVOKABLE void setIsCPSwitchable(bool bIsCPSwitchable);

    /**
     * @brief  setSmartFanState: This method is called from qml, when user clicks "Smart Fan" option.
     *          This method reads the smart fan state from persistence and requests the CP proxy to set the opposite state.
     * @param  void.
     * @return void.
     */
    Q_INVOKABLE void setSmartFanState();

signals:

    /**
    * @brief	CAppleCarPlayAdaptor::sigAppleCarPlayConnectionStatusChanged is
    *           a notify signal to notify appleCarPlayConnectionStatus property
    *           changes to qml
    * @param	bAppleCarPlayConnectionStatus: AppleCarPlay connection status,
    *           true if connected else false.
    * @return	void.
    **/
    void sigAppleCarPlayConnectionStatusChanged(bool bAppleCarPlayConnectionStatus);

    /**
    * @brief	CAppleCarPlayAdaptor::sigAppleCarPlayProjectionStatusChanged is
    *           a notify signal to notify appleCarPlayProjectionStatus property
    *           changes to qml
    * @param	bAppleCarPlayProjectionStatus: AppleCarPlay projection status,
    *           true if projected else false.
    * @return	void.
    **/
    void sigAppleCarPlayProjectionStatusChanged(bool bAppleCarPlayProjectionStatus);

    /**
     * @brief sigCPMediaSongTitleChanged: signal to notify the changes in
     *        cpMediaSongTitle property
     * @param	void.
     * @return	void.
     **/
    void sigCPMediaSongTitleChanged();

    /**
     * @brief sigCPMediaSongArtistChanged: signal to notify the changes in
     *        cpMediaSongArtist property
     * @param	void.
     * @return	void.
     **/
    void sigCPMediaSongArtistChanged();

    /**
    * @brief	CAppleCarPlayAdaptor::sigAppleCarPlayDeviceNameChanged is
    *           a notify signal to notify appleCarPlayDeviceName property
    *           changes to qml
    * @param	void.
    * @return	void.
    **/
    void sigAppleCarPlayDeviceNameChanged();

    /**
     * @brief  sigSmartFanStateChanged: This signal gets emitted on SmartFan status updated.
     * @param  bSmartFanState: true - smart fan ctive, false - not active.
     * @return void.
     */
    void sigSmartFanStateChanged(bool bSmartFanState);

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
     *          This slot calls resource api to launch Car Play music screen,
     *          if source SRC_CARPLAY_MEDIA is gets Activated.
     * @param   void.
     * @return  void.
     */
    void slotActiveEntSourceChanged();

    /**
     * @brief   slotBroadcastUserInteractionDetected: This function is called Whenever,
     *          Framework broadcasts any User Interaction Detected (i.e. touch/HK)
     *          In this case HMI has to inform CarPlay Service about this by calling requestNative() api
     * @param   void.
     * @return  void.
     */
    void slotBroadcastUserInteractionDetected();

private:
    /*!
     * @brief   Destructor of CAppleCarPlayAdaptor
     * @param   void.
     * @return  void.
     */
    ~CAppleCarPlayAdaptor();

    /**
    * @brief	CAppleCarPlayAdaptor::CAppleCarPlayAdaptor private constructor
    *           for singleton
    *           class CAppleCarPlayAdaptor.
    * @param	QObject parent.
    * @return	NA.
    **/
    explicit CAppleCarPlayAdaptor(QObject *pParent = nullptr);

    /**
    * @brief	CAppleCarPlayAdaptor::isAppleCarPlayResourceReady is to check
    *           that the AppleCarPlay resource is not NULL.
    * @param	void.
    * @return	Returns true if resource is not NULL else false.
    **/
    bool isAppleCarPlayResourceReady();

    /**
    * @brief    CAppleCarPlayAdaptor::requestCarPlayProjection is a private
    *           function, which is called to request AppleCarPlay service to
    *           start AppleCarPlay projection.
     * @param   appURL : URL identifier of the desired CarPlay UI application to launch:
     *          Blank String: CarPlay native screen will be shown
     *          "maps:" - Carplay Maps application will be shown
     *          "mobilephone:" - CarPlay Phone application will be shown
     *          "music:" - CarPlay Music application will be shown
     *          "nowplaying:" - CarPlay Now Playing screen will be shown
     *          "tel:xxx-xxx-xxxx" - CarPlay Phone application will be shown and a phone call with desired number will be placed..
    * @return   void
    */
    void requestCarPlayProjection(const string &appURL = "");

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
     *          default values. If CarPlay disconneted.
     * @param   void.
     * @return  void.
     */
    void resetData();

    /**************************************************//**
    * @category PROPERTIES
    ******************************************************/

    /*!
     * @brief Singolton Instance pointer for CAppleCarPlayAdaptor
     */
    static CAppleCarPlayAdaptor *m_pAppleCarPlayAdaptor;

    /*!
     * @brief Instance of IAppleCarPlayResource
     */
    CAppleCarPlayResourceImpl *m_pAppleCarPlayResource;

    /*!
     * @brief Variable to hold the AppleCarPlay connection status.
     */
    bool m_bAppleCarPlayConnectionStatus;

    /*!
     * @brief Variable to hold the AppleCarPlay projection status.
     */
    bool m_bAppleCarPlayProjectionStatus;

    /*!
     * @brief Variable to hold the AppleCarPlay phone status.
     */
    bool m_bAppleCarPlayPhoneStatus;

    /**
     * @brief m_strCPMediaSongTitle: Currently playing song title.
     */
    QString m_strCPMediaSongTitle;

    /**
     * @brief m_strCPMediaSongArtist: Currently playing song Artist.
     */
    QString m_strCPMediaSongArtist;

    /*!
     * @brief Variable to hold the AppleCarPlay Device Name.
     */
    QString m_strAppleCarPlayDeviceName;

    /**
     * @brief m_bIsCPSwitchable: Variable to hold the value can HMI
     *        switch to Car Play music screen and Car Play to Native HMI
     *        Active source Screen. ( Basically this is used in case of toggle
     *        source.)
     */
    bool m_bIsCPSwitchable;

    /**
     * @brief m_bAppleCarPlayRemoteUIStatus: Variable to hold the value of RemoteUI
     *        to check if CP is going to auto launch or not
     *        ( Basically this is used in case of showing CP connection popup
     *        source.)
     */
    bool m_bAppleCarPlayRemoteUIStatus;

    /**
     * @brief m_bSmartFanState: To hold the status of Smart Fan.
    */
    bool m_bSmartFanState;

    /*!
     * @brief Variable to hold the CarPlay Siri status.
     */
    bool m_bCarPlaySiriStatus;

    /**
     * @brief DEVICE_NAME_LENGTH_LIMIT: This variable holds the Device Name length limit.
     */
    const int DEVICE_NAME_LENGTH_LIMIT;
};

#endif // CAPPLECARPLAYADAPTOR_H
