/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CParkAssistAdaptor.h
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * This class is to handle ParkAssist functionality.
 */

#ifndef CPARKASSISTADAPTOR_H
#define CPARKASSISTADAPTOR_H

#include "QObject"
#include "logging.h"
#include "CFramework.h"
#include "ParkAssistResource/interfaces/IParkAssistResource.h"
#include "CParkAssistEnums.h"
#include "CHardKeyEnum.h"
#include "CParkAssistData.h"

/**
 * @brief The CParkAssistAdaptor class: This class contains methods to handle Park Assist related functionality
 *          like Park Assit tone, delay timer, tone volume etc.
 */
class CParkAssistAdaptor : public QObject
{
    /** Park assist screen header states */
    const QString PDC_RVC_HEADER_STATE_FAULT_MESSAGE = "Fault_Message_Header";

    Q_OBJECT

    // To get current parkAssistVolume value
    Q_PROPERTY(int parkAssistVolume READ parkAssistVolume NOTIFY sigParkAssistVolumeChanged)

    // To get current parkAssistDelayTimer value
    Q_PROPERTY(int parkAssistDelayTimer READ parkAssistDelayTimer NOTIFY sigParkAssistDelayTimerChanged)

    // To get current parkAssistRearTone value
    Q_PROPERTY(int parkAssistRearTone READ parkAssistRearTone NOTIFY sigParkAssistRearToneChanged)

    /** To get current status of reverse gear, engaged or disengaged */
    Q_PROPERTY(bool reverseGearStatus READ reverseGearStatus NOTIFY sigReverseGearStatusChanged)

    /** To get current park assist variant type */
    Q_PROPERTY(CParkAssistEnum::EParkAssistVariantType parkAssistVariant READ parkAssistVariant NOTIFY sigParkAssistVariantChanged)

    /** To get the current PDC screen left sensor state */
    Q_PROPERTY(int pdcScreenLeftSensorState READ pdcScreenLeftSensorState NOTIFY sigPdcSensorStateChanged)

    /** To get the current PDC screen mid left sensor state */
    Q_PROPERTY(int pdcScreenMidLeftSensorState READ pdcScreenMidLeftSensorState NOTIFY sigPdcSensorStateChanged)

    /** To get the current PDC screen mid right sensor state */
    Q_PROPERTY(int pdcScreenMidRightSensorState READ pdcScreenMidRightSensorState NOTIFY sigPdcSensorStateChanged)

    /** To get the current PDC screen right sensor state */
    Q_PROPERTY(int pdcScreenRightSensorState READ pdcScreenRightSensorState NOTIFY sigPdcSensorStateChanged)

    /** To get the current RVC screen sensor state */
    Q_PROPERTY(int rvcScreenSensorState READ rvcScreenSensorState NOTIFY sigRvcSensorStateChanged)

    /** To get the current fault message of PDC-RVC system */
    Q_PROPERTY(QString pdcRvcFaultMessage READ pdcRvcFaultMessage NOTIFY sigPdcRvcFaultChanged)

    /** To get the RVC overlay type, static or dynamic */
    Q_PROPERTY(CParkAssistEnum::ERvcOverlays rvcOverlayType READ rvcOverlayType NOTIFY sigRvcOverlayTypeChanged)

    /** To get the current steering wheel direction, clockwise or counter-clockwise */
    Q_PROPERTY(CParkAssistEnum::ERvcOverlayDirection rvcOverlayDirection READ rvcOverlayDirection NOTIFY sigRvcOverlayDirectionChanged)

    /** To get the current steering wheel angle */
    Q_PROPERTY(double rvcOverlayAngle READ rvcOverlayAngle NOTIFY sigRvcOverlayAngleChanged)


    /** To get the status of PDC-RVC screen, activated from HMI or not */
    Q_PROPERTY(bool isPdcRvcActivatedFromHmi READ isPdcRvcActivatedFromHmi NOTIFY sigPdcRvcActivatedFromHmiChanged)

    /** To get the status park assist header - fault message, call or SMS */
    Q_PROPERTY(QString parkAssistHeaderState READ parkAssistHeaderState NOTIFY sigParkAssistHeaderStateChanged)

    /** To get the current RVC overlay image path */
    Q_PROPERTY(QString rvcOverlayCurrentImagePath READ rvcOverlayCurrentImagePath NOTIFY sigRvcOverlayAngleChanged)

    /** To get status of PDC-RVC screen, active or in-active */
    Q_PROPERTY(bool pdcRvcScreenStatus READ pdcRvcScreenStatus NOTIFY sigReverseGearStatusChanged)

    /** To get the proxy status changes */
    Q_PROPERTY(bool pdcRvcProxyStatus READ pdcRvcProxyStatus NOTIFY sigParkAssistProxyStatusChanged)

    /** To get the pdc presence status*/
    Q_PROPERTY(bool pdcPresence READ pdcPresence NOTIFY sigPdcPresenceChanged)

    /** To get the RVC distance vary image path */
    Q_PROPERTY(QString rvcDistanceVaryImagePath READ rvcDistanceVaryImagePath NOTIFY sigRvcSensorStateChanged)

    /** To get the alert icon available status on park assist fault message header, true - available, false - not available */
    Q_PROPERTY(bool isAlertIconAvailable READ isAlertIconAvailable NOTIFY sigPdcRvcFaultChanged)

public:

    /**
    * @brief	Destructor of adaptor class.
    * @param	NA.
    * @return   NA.
    */
    ~CParkAssistAdaptor();

    /**
    * @brief	This function is to get the instance of park assist adaptor class.
    * @param	void.
    * @return   pointer
    */
    static CParkAssistAdaptor *getInstance();

    /**
    * @brief	This function will return park assist volume.
    * @param	void.
    * @return	int: park assist volume
    */
    int parkAssistVolume();

    /**
    * @brief	This function will set park assist volume.
    * @param	iParkAssistVolume: will update park assist volume to member variable.
    * @return	void
    */
    void setParkAssistVolume(int iParkAssistVolume);

    /**
    * @brief	This function will return park delay timer.
    * @param	void.
    * @return	int: park assist delay timer value
    */
    int parkAssistDelayTimer();

    /**
    * @brief	This function will set park assist delay timer value.
    * @param	iParkAssistDelayTimer: will update park assist delay timer to member variable.
    * @return	void
    */
    void setParkAssistDelayTimer(int iParkAssistDelayTimer);

    /**
    * @brief	This function will return park assist rear tone value.
    * @param	void.
    * @return	int: park assist rear tone value
    */
    int parkAssistRearTone();

    /**
    * @brief	This function will set park assist rear tone value.
    * @param	iParkAssistRearTone: will update park assist rear tone to member variable.
    * @return	void
    */
    void setParkAssistRearTone(int iParkAssistRearTone);

    /**
     * @brief	This function will return the status of reverse gear, engaged or dis-engaged
     * @param	void.
     * @return	bool: status of reverse gear, engaged or dis-engaged
     */
    bool reverseGearStatus();

    /**
    * @brief	setReverseGearStatus: This function will set the status of reverse gear, engaged or dis-engaged
    * @param	bool bReverseGearStatus: status of reverse gear, engaged or dis-engaged
    * @param	bool bActivationStatus: status of activation from HMI, true - show screen, false - hide screen
    * @return	void
    */
    void setReverseGearStatus(bool bReverseGearStatus, bool bActivationStatus);

    /**
     * @brief	This function will return the park assist variant
     * @param	void.
     * @return	CParkAssistEnum::EParkAssistVariantType: Variant type, PDC, RVC or PDC+RVC
     */
    CParkAssistEnum::EParkAssistVariantType parkAssistVariant();

    /**
     * @brief	This function will set the park assist variant
     * @param	CParkAssistEnum::EParkAssistVariantType: Variant type, PDC, RVC or PDC+RVC
     * @return	void
     */
    void setParkAssistVariant(CParkAssistEnum::EParkAssistVariantType eParkAssistVariantType);

    /**
     * @brief	This function will return the PDC screen sensor state of left zone
     * @param	void.
     * @return	int: Holds in which zone the obstacle is present
     */
    int pdcScreenLeftSensorState();

    /**
     * @brief	This function will return the PDC screen sensor state of mid left zone
     * @param	void.
     * @return	int: Holds in which zone the obstacle is present
     */
    int pdcScreenMidLeftSensorState();

    /**
     * @brief	This function will return the PDC screen sensor state of mid right zone
     * @param	void.
     * @return	int: Holds in which zone the obstacle is present
     */
    int pdcScreenMidRightSensorState();

    /**
     * @brief	This function will return the PDC screen sensor state of right zone
     * @param	void.
     * @return	int: Holds in which zone the obstacle is present
     */
    int pdcScreenRightSensorState();

    /**
     * @brief	This function will set the PDC screen sensor state
     * @param	int iPdcSensorState: Holds in which zone the obstacle is present
     * @return	void
     */
    void setPdcScreenSensorState(int iPdcSensorState);

    /**
     * @brief	This function will return the RVC screen sensor state
     * @param	void.
     * @return	int: Holds in which zone the obstacle is present
     */
    int rvcScreenSensorState();

    /**
     * @brief	This function will set the RVC screen sensor state
     * @param	int iRvcSensorState: Holds in which zone the obstacle is present
     * @return	void
     */
    void setRvcScreenSensorState(int iRvcSensorState);

    /**
     * @brief	This function will return the fault message of the PDC-RVC system.
     * @param	void.
     * @return	Current fault message of the PDC-RVC system.
     */
    QString pdcRvcFaultMessage();

    /**
     * @brief	This function will set the PDC fault
     * @param	CParkAssistEnum::EPdcFaults ePdcFault: Holds the PDC fault index, based on which corresponding fault message gets displayed
     * @return	void
     */
    void setPdcFault(CParkAssistEnum::EPdcFaults ePdcFault);

    /**
     * @brief	This function will set the RVC fault
     * @param	CParkAssistEnum::ERvcFaults eRvcFault: Holds the RVC fault index, based on which corresponding fault message gets displayed
     * @return	void
     */
    void setRvcFault(CParkAssistEnum::ERvcFaults eRvcFault);

    /**
     * @brief	This function will set the PDC+RVC fault
     * @param	CParkAssistEnum::EPdcRvcFaults ePdcRvcFault: Holds the PDC+RVC fault index, based on which corresponding fault message gets displayed
     * @return	void
     */
    void setPdcRvcFault(CParkAssistEnum::EPdcRvcFaults ePdcRvcFault);

    /**
     * @brief	This function will return the RVC overlay type
     * @param	void.
     * @return	CParkAssistEnum::ERvcOverlays: Static / Dynamic overlay
     */
    CParkAssistEnum::ERvcOverlays rvcOverlayType();

    /**
     * @brief	This function will set the RVC overlay type
     * @param	CParkAssistEnum::ERvcOverlays eRvcOverlayType: Current active overlay, Static / Dynamic
     * @return	void.
     */
    void setRvcOverlayType(CParkAssistEnum::ERvcOverlays eRvcOverlayType);

    /**
     * @brief	This function will return the RVC overlay direction
     * @param	void.
     * @return	CParkAssistEnum::ERvcOverlayDirection: clockwise / counter-clockwise direction
     */
    CParkAssistEnum::ERvcOverlayDirection rvcOverlayDirection();

    /**
     * @brief	This function will set the RVC overlay direction
     * @param	CParkAssistEnum::ERvcOverlayDirection eRvcOverlayDirection: clockwise / counter-clockwise direction
     * @return	void.
     */
    void setRvcOverlayDirection(CParkAssistEnum::ERvcOverlayDirection eRvcOverlayDirection);

    /**
     * @brief	This function will return the RVC overlay angle
     * @param	void.
     * @return	double: RVC overlay angle
     */
    double rvcOverlayAngle();

    /**
     * @brief	setRvcOverlayAngle: This function will set the RVC overlay angle, and assigns the overlay image path to m_strRvcOverlayCurrentImgPath.
     * @param	double dRvcOverlayAngle: RVC overlay angle
     * @return	void.
     */
    void setRvcOverlayAngle(double dRvcOverlayAngle);

    /**
     * @brief	This function will return the park assist proxy status, used to enable the park assist icon on home
     * @param	void.
     * @return	bool: park assist proxy status, available or not
     */
    bool getParkAssistProxyStatus();

    /**
     * @brief	This function will set the park assist proxy status, used to enable the park assist icon on home
     * @param	bool bParkAssistProxyStatus: park assist proxy status, available or not
     * @return	void.
     */
    void setParkAssistProxyStatus(bool bParkAssistProxyStatus);

    /**
     * @brief	This function will return the status of PDC_RVC screen, activated from HMI or not, used to show cancel button on PDC_RVC screen
     * @param	void.
     * @return	bool: park assist proxy status, available or not
     */
    bool isPdcRvcActivatedFromHmi();

    /**
     * @brief	This function will set the status of PDC_RVC screen, activated from HMI or not, used to show cancel button on PDC_RVC screen
     * @param	bool bStatusActivatedFromHmi: park assist proxy status, available or not
     * @return	void.
     */
    void setStatusPdcRvcActivatedFromHmi(bool bStatusActivatedFromHmi);

    /**
     * @brief	rvcOverlayCurrentImagePath: This function will return the overlay current image path.
     * @param	void.
     * @return	QString: Path of the image.
     */
    QString rvcOverlayCurrentImagePath();

    /**
     * @brief	pdcRvcScreenStatus: This function will return the status of PDC_RVC screen in HMI.
     * @param	void.
     * @return	bool: true - PDC_RVC screen active, false - PDC_RVC screen not active.
     */
    bool pdcRvcScreenStatus();

    /**
     * @brief	pdcRvcProxyStatus: This function will return the status of PDC_RVC proxy in HMI.
     * @param	void.
     * @return	bool: true - proxy available, false - proxy not available.
     */
    bool pdcRvcProxyStatus();

    /**
     * @brief	parkAssistHeaderState: This function will return the active park assist header type.
     * @param	void.
     * @return	QString: Park assist header type, fault message, call or SMS.
     */
    QString parkAssistHeaderState();

    /**
     * @brief	setParkAssistHeaderState: This function will set the state of active park assist header.
     * @param	const QString sHeaderState: Park assist header type, fault message, call or SMS.
     * @return	void.
     */
    void setParkAssistHeaderState(const QString& sHeaderState);

    /**
     * @brief pdcPresence : This function will return the pdc presence state.
     * @param   void.
     * @return  pdcPresence : pdc presence status holds true if present else false
     */
    bool pdcPresence() {return m_bPdcPresence;}
    /**
     * @brief setPdcPresence: This function will set the state of pdc presence.
     * @param   bPdcPresence : Pdc Presence status
     * @return  void.
     */
    void setPdcPresence(bool bPdcPresence);

    /**
     * @brief setPdcSettingsStatus : This function will set the pdc settings error status.
     * @param bErrorStatus : bErrorStatus holds true if pdc settings cannot be updated as bcm is not ready, else false.
     * @param iErrorId : holds the error id.
     * @return  void.
     */
    void setPdcSettingsStatus(bool bPdcSettingsErrorStatus, int iErrorId);

    /**
     * @brief setHmiNotificationAttribute this method sets the HMI notification attribute which informs the RVC/PDC the HMI is up
     * @brief NotificationAttribute this method sets the HMI notification attribute which informs the RVC/PDC the HMI is up
     * and running
     * @param status informing the HMI is up and running, should be true always
     */
    Q_INVOKABLE  void setHmiNotificationAttribute(bool bHmiUpStatus);

    /**
     * @brief  updateRvcState: This method gets invoked when PDC-RVC is de-activated, notifies media service de-activation is done .
     * @param  void.
     * @return void.
     */
    void updateRvcState();

    /**
     * @brief updateReverseGearInfo update the reverse gear status (internal function)
     * @param iRevGearStatus current reverse gear status
     * @return provide the ACK value
     */
    int updateReverseGearInfo(int iRevGearStatus);

    /**
     * @brief  rvcDistanceVaryImagePath: This method returns the path of the image to be shown
     *          on RVC screen based on obstacle distance from sensor.
     * @param  void.
     * @return QString: Path of the image.
     */
    QString rvcDistanceVaryImagePath();

    /**
    * @brief	This function will request park assist delay timer to LB.
    * @param	int iParkAssistDelayTimerIndex: contains park delay timer to be set.
    * @return	void
    */
    Q_INVOKABLE void setParkAssistDelayTimerAttribute(int iParkAssistDelayTimerIndex);

    /**
    * @brief	This function will request Park Assist tone to LB.
    * @param	int iParkAssistTone: contains park assist tone to be set.
    * @return	void
    */
    Q_INVOKABLE void setParkAssistRearToneAttribute(int iParkAssistToneIndex);

    /**
    * @brief	This function will request Park Assist service to activate / de-activate PDC-RVC screen
    *           On clicking Park Assist icon on Home screen, we need to display PDC-RVC screen
    *           On clicking cancel button on PDC-RVC screen, we need to remove PDC-RVC screen
    * @param	bool bShowPdcRvcScreen: contains true/false to activate or de-activate PDC-RVC screen
    * @return	void
    */
    Q_INVOKABLE void activatePdcRvc(bool bShowPdcRvcScreen);


    /**
    * @brief    CParkAssistAdaptor::handleHardKeys Funtion to handle hardkey
    *           as per Park Assist specifications.
    * @param    eKey: The key on which the action is triggered.
    * @param    eKeyState: State of the key on which the action is triggered.
    * @return   true if an action was taken false otherwise.
    */
    bool handleHardKeys(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState);


    /**
     * @brief  isAlertIconAvailable: Returns the status of Alert icon, true - available, false - not available.
     * @param  void.
     * @return bool: Alert icon available status.
     */
    bool isAlertIconAvailable();

    /**
     * @brief updateOverlayCurrentImagePath: updates the m_strRvcOverlayCurrentImgPath as per the project.
     * @param void.
     * @return void.
     */
    void updateOverlayCurrentImagePath();

signals:

    /**
    * @brief	This signal gets emitted on park assist volume change.
    * @param	void.
    * @return	void
    */
    void sigParkAssistVolumeChanged();

    /**
    * @brief	This signal gets emitted on park assist delay timer change.
    * @param	void.
    * @return	void
    */
    void sigParkAssistDelayTimerChanged();

    /**
    * @brief	This signal gets emitted on park assist rear tone change.
    * @param	void.
    * @return	void
    */
    void sigParkAssistRearToneChanged();

    /**
     * @brief	This signal gets emitted on reverse gear status change.
     * @param	void.
     * @return	void
     */
    void sigReverseGearStatusChanged();

    /**
     * @brief	This signal gets emitted on park assist variant change.
     * @param	void.
     * @return	void
     */
    void sigParkAssistVariantChanged();

    /**
     * @brief	This signal gets emitted on PDC screen sensor information change.
     * @param	void.
     * @return	void
     */
    void sigPdcSensorStateChanged();

    /**
     * @brief	This signal gets emitted on RVC screen sensor information change.
     * @param	void.
     * @return	void
     */
    void sigRvcSensorStateChanged();

    /**
     * @brief	This signal gets emitted on PDC-RVC fault state change.
     * @param	void.
     * @return	void
     */
    void sigPdcRvcFaultChanged();

    /**
     * @brief	This signal gets emitted on RVC overlay type change.
     * @param	void.
     * @return	void
     */
    void sigRvcOverlayTypeChanged();

    /**
     * @brief	This signal gets emitted on RVC overlay direction change.
     * @param	void.
     * @return	void
     */
    void sigRvcOverlayDirectionChanged();

    /**
     * @brief	This signal gets emitted on RVC overlay angle change.
     * @param	void.
     * @return	void
     */
    void sigRvcOverlayAngleChanged();

    /**
     * @brief	This signal gets emitted on Park assist proxy status change.
     * @param	bool bParkAssistProxyStatus : Park Assist proxy availibility status
     * @return	void
     */
    void sigParkAssistProxyStatusChanged(bool bParkAssistProxyStatus);

    /**
     * @brief	This signal gets emitted on when PDC-RVC is activated from HMI.
     * @param	void
     * @return	void
     */
    void sigPdcRvcActivatedFromHmiChanged();

    /**
     * @brief	This signal gets emitted on park assist header state change.
     * @param	void
     * @return	void
     */
    void sigParkAssistHeaderStateChanged();

    /**
     * @brief	This signal gets emitted on park assist variant change & reverse gear engaged status is true.
     * @param	void.
     * @return	void
     */
    void sigDisplayScreenPdcRvc();

    /**
     * @brief sigPdcPresence : This signal gets emitted on pdc presence state on change.
     * @param   void.
     * @return  void.
     */
    void sigPdcPresenceChanged();

private slots:

    /**
     * @brief  sltNotifyParkAssistDeactivation: This method notifies park assist de-activation to media service.
     * @param  void.
     * @return void.
     */
    void sltNotifyParkAssistDeactivation();

private:

    /**
     * @brief CParkAssistAdaptor class Constructor
     * @param pParent
     * @return NA
     */
    explicit CParkAssistAdaptor(QObject *parent = nullptr);

    /**
     * @brief   setRVCConfigurationValues, Function to set RVC related configuration values based on VIP DID
     * @param   void
     * @return  void
     */
    void setRVCConfigurationValues();

    /**
     * @brief  This method fills the PDC faults indexes & corresponding messages to a map
     * @param  void
     * @return void
     */
    void fillPdcFaultsMap();

    /**
     * @brief  This method fills the RVC faults indexes & corresponding messages to a map
     * @param  void
     * @return void
     */
    void fillRvcFaultsMap();

    /**
     * @brief  This method fills the PDC-RVC faults indexes & corresponding messages to a map
     * @param  void
     * @return void
     */
    void fillPdcRvcFaultsMap();

    /**
     * @brief  fillRvcOverlayLeftImagesMap: This method fills the overlay indexe's & corresponding left side overlay images to a map
     * @param  void
     * @return void
     */
    void fillRvcOverlayLeftImagesMap();

    /**
     * @brief  fillRvcOverlayRightImagesMap: This method fills the overlay indexe's & corresponding right side overlay images to a map
     * @param  void
     * @return void
     */
    void fillRvcOverlayRightImagesMap();

    /**
     * @brief  calculateCurrentImageIndex: This method returns the index of overlay image based on steering wheel angle.
     *          Index is calculated based on the max angle & image count.
     * @param  double dRvcOverlayAngle: Steering wheel angle.
     * @return int: Index of the overlay image to be shown.
     */
    int calculateCurrentImageIndex(double dRvcOverlayAngle);

    /**
     * @brief fillRvcDistanceVaryImagesMap: This method fills distance vary image indexe's & image paths to m_mapRvcDistanceUImages.
     * @param  void.
     * @return void.
     */
    void fillRvcDistanceVaryImagesMap();

public slots:


private:

    /** Instance of class CParkAssistAdaptor */
    static CParkAssistAdaptor* m_pParkAssistAdaptor;

    /** Instance of class IParkAssistResource */
    IParkAssistResource* m_pParkAssistResource;

    /** Variable holds park assist volume */
    int m_iParkAssistVolume;

    /** Variable holds park assist delay timer */
    int m_iParkAssistDelayTimer;

    /** Variable holds park assist rear tone */
    int m_iParkAssistRearTone;

    /** This variable holds the mapping of delay timer index & delay timer values */
    QMap<CParkAssistEnum::EParkAssistDelayTimer,CParkAssistEnum::EParkAssistDelayTimerValues> m_mapParkAssistDelayTimer;

    /** This variable holds status of reverse gear, true - engaged / false - disengaged */
    bool m_bReverseGearStatus;

    /** This variable holds park assist variant type */
    CParkAssistEnum::EParkAssistVariantType m_eParkAssistVariantType;

    /** This variable holds PDC-RVC fault message */
    QString m_strPdcRvcFaultMessage;

    /** This variable holds RVC overlay type, static or dynamic */
    CParkAssistEnum::ERvcOverlays m_eRvcOverlayType;

    /** This variable holds steering wheel direction, clockwise or counter-clockwise */
    CParkAssistEnum::ERvcOverlayDirection m_eRvcOverlayDirection;

    /** This variable holds steering wheel angle */
    double m_dRvcOverlayAngle;

    /** This variable holds park assist proxy status */
    bool m_bParkAssistProxyStatus;

    /** This variable holds park assist status, activated from HMI or not */
    bool m_bIsPdcRvcActivatedFromHmi;

    /** This variable holds current active zone of RVC screen */
    int m_eRvcZone;

    /** This variable holds current active left zone of PDC screen */
    int m_iPdcLeftSensorState;

    /** This variable holds current active mid left zone of PDC screen */
    int m_iPdcMidLeftSensorState;

    /** This variable holds current active mid right zone of PDC screen */
    int m_iPdcMidRightSensorState;

    /** This variable holds current active right zone of PDC screen */
    int m_iPdcRightSensorState;

    /** This variable holds the mapping of PDC fault codes, corresponding fault messages and alert icon availability status... */
    QMap<CParkAssistEnum::EPdcFaults, CParkAssistData> m_mapPdcFault;

    /** This variable holds the mapping of RVC fault codes, corresponding fault messages and alert icon availability status.. */
    QMap<CParkAssistEnum::ERvcFaults, CParkAssistData> m_mapRvcFault;

    /** This variable holds the mapping of PDC-RVC fault codes, corresponding fault messages and alert icon availability status.. */
    QMap<CParkAssistEnum::EPdcRvcFaults, CParkAssistData> m_mapPdcRvcFault;

    /** To get the status park assist header - fault message, call or SMS */
    QString m_strParkAssistHeaderState;

    /** This variable holds the pdc presence status */
    bool m_bPdcPresence;

    /** This variable holds the mapping of indexe's & corresponding left side overlay images path */
    QMap<int, QString> m_mapRvcOverlayLeftImage;

    /** This variable holds the mapping of indexe's & corresponding right side overlay images path */
    QMap<int, QString> m_mapRvcOverlayRightImage;

    /** This variable holds the index of current overlay image to be shown */
    int m_iRvcOverlayCurrentImgIndex;

    /** This variable holds the path of current overlay image to be shown */
    QString m_strRvcOverlayCurrentImgPath;

    /**
     * @brief m_mapRvcDistanceUImages: This variable holds the mapping of obstacle distance image index & corresponding image path
     */
    QMap<int, QString> m_mapRvcDistanceUImages;

    /**
     * @brief m_strRvcDistanceVaryImagePath: This variable holds the path of the obstacle distance image
     */
    QString m_strRvcDistanceVaryImagePath;

    /** This variable holds the alert icon availability status of current fault code.., true - available, false - not available */
    bool m_bIsAlertIconAvailable;

    /**
     * @brief m_iRvcOverlayImageCount: This will hold the image count value for overlay according to the project.
     */
    int m_iRvcOverlayImageCount;

    /**
     * @brief RVC_OVERLAY_MAX_ANGLE: Maximum Angle of RVC Overlay.
     */
    static const int RVC_OVERLAY_MAX_ANGLE = 530;

    /**
     * @brief RVC_OVERLAY_MID_IMAGE_INDEX: Middle Image index.
     */
    static const int RVC_OVERLAY_MID_IMAGE_INDEX = 0;

    /**
     * @brief RVC_TOTAL_RANGE: Total Zone Range for X451.
     */
    int RVC_TOTAL_RANGE;

    /**
     * @brief RVC_GREEN_START: Starting Range of Green Zone for X451.
     */
    int RVC_GREEN_START;

    /**
     * @brief RVC_YELLOW_START: Starting Range of Yellow Zone for X451.
     */
    int RVC_YELLOW_START;

    /**
     * @brief RVC_RED_START: Starting Range of Red Zone for X451.
     */
    int RVC_RED_START;

    /**
     * @brief RVC_RED_IMAGE_COUNT: Red Image Count for X451.
     */
    int RVC_RED_IMAGE_COUNT;

    /**
     * @brief RVC_YELLOW_IMAGE_COUNT: Yellow Image Count for X451.
     */
    int RVC_YELLOW_IMAGE_COUNT;

    /**
     * @brief RVC_GREEN_IMAGE_COUNT: Green Image Count for X451
     */
    int RVC_GREEN_IMAGE_COUNT;

    /**
     * @brief RVC_OVERLAY_IMAGE_COUNT: Total Overlay Image count of One Direction for X451.
     */
    int RVC_OVERLAY_IMAGE_COUNT;

    /**
     * @brief RVC_ZONE_IMAGE_COUNT: Total Zone Image Count.
     */
    int RVC_ZONE_IMAGE_COUNT = (RVC_RED_IMAGE_COUNT + RVC_YELLOW_IMAGE_COUNT + RVC_GREEN_IMAGE_COUNT);

    /**
     * @brief RVC_BUFFER_VALUE: Buffered Value.
     */
    static float RVC_BUFFER_VALUE;

    /**
     * @brief RVC_RED_STEP: Units by which the next/previous image should change for Red Zone.
     */
    float RVC_RED_STEP;

    /**
     * @brief RVC_YELLOW_STEP: Units by which the next/previous image should change for Yellow Zone.
     */
    float RVC_YELLOW_STEP;

    /**
     * @brief RVC_GREEN_STEP: Units by which the next/previous image should change for Green Zone.
     */
    float RVC_GREEN_STEP;

    /**
     * @brief PARK_ASSIST_DELAY_TIMER_VALUE_ZERO: Contant to Hold the value for Delay Timer 0.
     */
    static const int PARK_ASSIST_DELAY_TIMER_VALUE_ZERO = 0;

    /**
     * @brief PARK_ASSIST_DELAY_TIMER_VALUE_ONE: Contant to Hold the value for Delay Timer 1.
     */
    static const int PARK_ASSIST_DELAY_TIMER_VALUE_ONE = 1;
};

#endif // CPARKASSISTADAPTOR_H
