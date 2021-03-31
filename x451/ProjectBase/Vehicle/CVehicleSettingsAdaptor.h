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
 * This class is to handle Vehicle functionality.
 */

#ifndef CVehicleSettingsAdaptor_H
#define CVehicleSettingsAdaptor_H

#include "QObject"
#include "logging.h"
#include "CFramework.h"
#include "Vehicle/CVehicleEnums.h"
#include "implementations/CVehicleResourceImpl.h"
#include "CPopupManager.h"

//! @category FORWARD DECLERATIONS
class CVehicleResourceImpl;

/**
 * @brief The CVehicleSettingsAdaptor class: This class contains methods to handle vehicle related functionality
 *          like vehicle auto relock, approach lamps etc.
 */
class CVehicleSettingsAdaptor : public QObject
{
    Q_OBJECT

    // to get current appraoch lamps value
    Q_PROPERTY(int approachLamps     READ approachLamps    WRITE setAppraochLamps    NOTIFY sigAppraochLampsChanged)

    // to get current vehicle auto relock
    Q_PROPERTY(bool vehicleAutoRelock     READ vehicleAutoRelock    WRITE setVehicleAutoRelock    NOTIFY sigVehicleAutoRelockChanged)

    // to get bcm presence status
    Q_PROPERTY(bool bCmPresence     READ bCmPresence  NOTIFY sigBCMPresenceChanged)

    //to get vehicle speed value
    Q_PROPERTY(float fVehicleSpeed     READ fVehicleSpeed   NOTIFY sigVehicleSpeedChanged)
	
	/** To get SpeedLockOut status */
    Q_PROPERTY(bool speedLockOutStatus READ speedLockOutStatus NOTIFY sigSpeedLockOutStatusChanged)


    //to get ambient light mode
    Q_PROPERTY(CVehicleEnums::EAmbientLightMode ambientLightMode     READ ambientLightMode   NOTIFY sigAmbientLightModeChanged)

    //to get ambient light posible illumination level
    Q_PROPERTY(int ambLightIllumLevel  READ ambLightIllumLevel   NOTIFY sigAmbLightIllumLevelChanged)

    //to get ambient light mode presence on HU
    Q_PROPERTY(bool ambientLightModeIlluOnHu  READ ambientLightModeIlluOnHu   NOTIFY sigAmbientLightModeIlluOnHuChanged)

    //to get ambient light selected illumination level
    Q_PROPERTY(int ambSelIlluminationLevel  READ ambSelIlluminationLevel  WRITE setAmbLightIlluSelLevelValue NOTIFY sigAmbLightIlluSelLevelChanged)

    //to get park lamp status
    Q_PROPERTY(int parkLampStatus  READ parkLampStatus   NOTIFY sigParkLampStatusChanged)

    //to get vehicle auto relock presence status
    Q_PROPERTY(bool vehicleAutoRelockPresence  READ vehicleAutoRelockPresence   NOTIFY sigVehiAutoRelockPresenceChanged)

    //to get approach lamps presence status
    Q_PROPERTY(bool appraochLampsPresence  READ appraochLampsPresence   NOTIFY sigAppraochLampsPresenceChanged)

    //to get Bcm Ucs state
    Q_PROPERTY(bool bcmUcsState  READ bcmUcsState   NOTIFY sigBcmUcsStateChanged)

    //to get ambient light available status
    Q_PROPERTY(bool bAmbientLightAvailableStatus  READ bAmbientLightAvailableStatus   NOTIFY sigAmbientLightAvailableStatusChanged)

    //to get bcm drl presence status
    Q_PROPERTY(bool bcmDrlFeature  READ bcmDrlFeature   NOTIFY sigBcmDrlFeaturePresenceStatusChanged)

    //to get bcm drl selection status
    Q_PROPERTY(bool bcmDrlSelectionStatus  READ bcmDrlSelectionStatus   NOTIFY sigBcmDrlSelectionStatusChanged)

    //Property to get enable status of ambient light component
    Q_PROPERTY(bool ambLightEnableStatus READ ambLightEnableStatus NOTIFY sigAmbLightEnableStatusChanged)

public:
    ~CVehicleSettingsAdaptor();

    /**
    * @brief	This function get the instance of adaptor class.
    * @param	void.
    * @return   pointer
    */
    static CVehicleSettingsAdaptor *getInstance();

public:

    /**
     * @brief   invSetAmbLightEnableStatus: Method to enable/disable ambient light component.
     * @param   bIsEnable: True to enable ambient light, False to disable it.
     * @return  void.
     */
    Q_INVOKABLE void invSetAmbLightEnableStatus(bool bIsEnable);

    /**
    * @brief	This function will return approach lamps.
    * @param	void.
    * @return	approachLamps: approach lamps value.
    */
    int approachLamps();

    /**
    * @brief	This function will set appraoch lamps value.
    * @param	iApproachLamps: iApproachLamps will set approach lamps value.
    * @return	void
    */
    void setAppraochLamps(int iApproachLamps);

    /**
    * @brief	This function will return approach lamps.
    * @param	void.
    * @return	vehicleAutoRelock: vehicle auto relock status.
    */
    bool vehicleAutoRelock();

    /**
    * @brief	This function will set auto relock status.
    * @param	bAutoRelockStatus: bAutoRelockStatus will set vehicle auto relock.
    * @return	void
    */
    void setVehicleAutoRelock(bool bAutoRelockStatus);


    /**
     * @brief bAmbientLightAvailableStatus : This function will return ambient light available status
     * @param void.
     * @return  m_bAmbientLightAvailableStatus: ambient light available status.
     */
    bool bAmbientLightAvailableStatus() {return m_bAmbientLightAvailableStatus;}

    /**
     * @brief setAmbientLightAvailableStatus : This function will set ambient light available status.
     * @param bAmbientLightAvailableStatus : bAmbientLightAvailableStatus will hold ambient light available status.
     * @return void.
     */
    void setAmbientLightAvailableStatus(bool bAmbientLightAvailableStatus);


    /**
     * @brief bCmPresence : This function will return bcm presence
     * @param void.
     * @return  bCmPresence: bcm presence status.
     */
    bool bCmPresence() {return m_bBCmPresence;}

    /**
     * @brief setBCMPresence : This function will set BCm Presence status.
     * @param bBCmPresence : bBCmPresence will hold BCM status.
     * @return void.
     */
    void setBCMPresence(bool bBCmPresence);


    /**
     * @brief fVehicleSpeed : This function will return vehicle speed
     * @param void.
     * @return m_fVehicleSpeed : m_fVehicleSpeed will hold vehicle speed.
     */
    float fVehicleSpeed() {return m_fVehicleSpeed;}
    /**
     * @brief setVehicleSpeed : This function will set vehicle speed.
     * @param fVehicleSpeed : fVehicleSpeed will hold vehicle speed value.
     * @return void.
     */
    void setVehicleSpeed(float fVehicleSpeed);
	
    /**
     * @brief  speedLockOutStatus: This function will return speed lockout status.
     * @param  void.
     * @return bool: speed lockout status.
     */
    bool speedLockOutStatus() { return m_bSpeedLockOutStatus;}

    /**
     * @brief  setSpeedLockOutStatus: This function will set speed lockout status.
     * @param  bSpeedLockOutStatus: Holds speed lockout status.
     * @return void.
     */
    void setSpeedLockOutStatus(bool bSpeedLockOutStatus);

    /**
     * @brief bcmDrlSelectionStatus : This function will return the bcm drl selection state.
     * @param   void.
     * @return bcmDrlSelectionStatus : holds the bcm drl selection status.
     */
    bool bcmDrlSelectionStatus() { return m_bBcmDrlSelectionStatus; }

    /**
     * @brief   ambLightEnableStatus : Method to get the ambient light enable status.
     * @param   void.
     * @return  m_bAmbLightEnableStatus : TRUE if ambient light component is enabled, FALSE if disabled.
     */
    bool ambLightEnableStatus() { return m_bAmbLightEnableStatus; }

    /**
     * @brief updateBcmDrlSelectionState : This function will set drl status.
     * @param bDrlStatus : holds the Enable state of drl, If drl is enabled then true else false.
     * @return  void.
     */
    void updateBcmDrlSelectionState(bool bDrlStatus);

    /**
     * @brief bcmDrlFeature : This function will get the bcm drl feature presence state.
     * @param void.
     * @return bcmDrlFeature : bcm drl feature presence status
     */
    bool bcmDrlFeature() {return m_bBcmDrlFeatureStatus;}

    /**
     * @brief UpdateBcmDrlFeaturePresenceStatus :function will update about the drl feature whether it is enabled/disabled in system.
     * @param bIsDrlFeatureEnabled: value of the DRL feature presence.
     * @return void.
     */
    void UpdateBcmDrlFeaturePresenceStatus(bool bIsDrlFeatureEnabled);


    /**
     * @brief ambientLightMode : This function will return ambient light mode.
     * @param  void.
     * @return m_eAmbientLightMode : m_eAmbientLightMode will hold ambient light mode.
     */
    CVehicleEnums::EAmbientLightMode ambientLightMode() {return m_eAmbientLightMode;}

    /**
     * @brief setAmbLightMode : This function will set ambient light mode.
     * @param eAmbLightMode : eAmbLightMode will hold ambient light mode.
     * @return  void.
     */
    void setAmbLightMode(CVehicleEnums::EAmbientLightMode eAmbLightMode);

    /**
     * @brief ambLightIllumLevel : This function used to get the ambient light illumination level.
     * @param  void.
     * @return ambLightIllumLevel : ambLightIllumLevel will hold ambient light illumination level.
     */
    int ambLightIllumLevel() {return m_iAmbLightIllumLevel;}

    /**
     * @brief setAmbLightIllumLevel : This function will set ambient light illumination levels.
     * @param iAmbLightIllumLevel : iAmbLightIllumLevel will hold ambient light illumination levels.
     * @return  void.
     */
    void setAmbLightIllumLevel(int iAmbLightIllumLevel);

    /**
     * @brief ambientLightIllumOnHu : This function will return ambient light availability on HU status.
     * @param void.
     * @return ambientLightModeIlluOnHu: ambientLightModeIlluOnHu will hold ambinet light mode availability on HU.
     */
    bool ambientLightModeIlluOnHu() { return m_bAmbientLightModeIlluOnHu;}
    /**
     * @brief setAmbLightIllumOnHu : This function will set ambient light mode illumination on HU status.
     * @param bAmbientLightModeIlluOnHu : bAmbLightIllumOnHu will hold the ambient light illumination on HU status.
     * @return void.
     */
    void setAmbientLightModeIlluOnHu(bool bAmbientLightModeIlluOnHu);

    /**
     * @brief ambSellluminationLevel : This function used to get the ambient light illumination level.
     * @param  void.
     * @return ambLightIllumLevel : ambLightIllumLevel will hold ambient light illumination level.
     */
    int ambSelIlluminationLevel() { return m_iAmbSelIlluLevel; }

    /**
     * @brief setAmbLightIllumLevel : This function will set ambient light selected illumination level.
     * @param iAmbLightIllumLevel : iAmbLightIllumLevel will hold ambient light illumination level.
     * @return  void.
     */
    void setAmbLightIlluSelLevelValue(int iAmbSelIlluLevel);

    /**
     * @brief updateAmbLightSelIllumLevelResponseRecv: This function will set the response of
     *        setAmbLightIllumLevel() function. The value is used
     *        for debounce logic, When user made changes using slider, the
     *        resouce's api must only be called, if previous request resonsed
     *        recieved.
     */
    void updateAmbLightSelIllumLevelResponseRecv();

    /**
     * @brief parkLampStatus : This function will return park lamp status.
     * @param   void.
     * @return  parkLampStatus. parkLampStatus will hold park lamp status
     */
    bool parkLampStatus() {return m_bParkLampStatus;}

    /**
     * @brief setParkLampStatus : This function will set park lamp status.
     * @param bParkLampStatus : bParkLampStatus will hold park lamp status.
     * @return  void.
     */
    void setParkLampStatus(bool bParkLampStatus);

    /**
     * @brief vehicleAutoRelockPresence : This function will return true if vehicle auto relock is available
     * @param   void.
     * @return vehicleAutoRelockPresence : true if present else false.
     */
    bool vehicleAutoRelockPresence() {return m_bVehiAutoRelockPresence;}
    /**
     * @brief setVehicleAutoRelockPresence : This function will set vehicle auto relock presence in vehicle
     * @param   bVehiAutoRelockPresence : bVehiAutoRelockPresence status will hold true if present, else false
     * @return  void.
     */
    void setVehicleAutoRelockPresence(bool bVehiAutoRelockPresence);

    /**
     * @brief appraochLampsPresence : This function will return true if approach lamps is available
     * @param   void.
     * @return  appraochLampsPresence : appraochLampsPresence status will hold true if present, else false
     */
    bool appraochLampsPresence() {return m_bAppraochLampsPresence;}
    /**
     * @brief setAppraochLampsPresence : This function will set approach lamps presence in vehicle.
     * @param bAppraochLampsPresence    : bAppraochLampsPresence status will hold true if present, else false
     * @return  void.
     */
    void setAppraochLampsPresence(bool bAppraochLampsPresence);

    /**
     * @brief bcmUcsState : This function will return true if Bcm Ucs state is enabled else false
     * @param void.
     * @return bcmUcsState : bcmUcsState will hold bcm Ucs state.
     */
    bool bcmUcsState() {return m_bBcmUcsState;}
    /**
     * @brief setBcmUcsState : This function will set Bcm Ucs state in vehicle.
     * @param bBcmUcsState : bBcmUcsState will be true if enabled else false.
     * @return  void.
     */
    void setBcmUcsState(bool bBcmUcsState);

    /**
    * @brief	updateAmbientLightAvailability : This function will update ambient lights availability status
    * @param	void.
    * @return	void.
    */
    void updateAmbientLightAvailability();

    /**
     * @brief updateAntitheftFeaturePresenceStatus: function will update about the Antitheft feature whether it is enabled/disabled in system.
     * @param bIsAntitheftFeatureEnabled: value of the Antitheft feature presence.
     * @return void.
     */
    void updateAntitheftFeaturePresenceStatus(bool bIsAntitheftFeatureEnabled);

    /**
     * @brief updateBCmAntitheftKeyConfirmationValue:  function will update about the Antitheft key confirmation status whether it is true/false in system.
     * @param bIsAntitheftKeyConfirmed: Key confirmation status.
     * @return void.
     */
    void updateBCmAntitheftKeyConfirmationValue(bool bIsAntitheftKeyConfirmed);

    /**
     * @brief  updateVehicleSettingChangeError: This function updates Vehicle Setting can not be changed.
     * @param  None.
     * @return void.
     */
    void updateVehicleSettingChangeError();

    /**
     * @brief   invSetAmbIlluminationSelUserInitaited: Method to be invoked from QML whenever user start/stop changing the slider
     *          value of ambient light illumination level.
     * @param   bUserInitated: flag to maintain whether the ambient light value changes has been initated by user
     *          or not. TRUE if user starts chaging the value and FALSE if user stops changing the value.
     * @return  void.
     */
    Q_INVOKABLE void invSetAmbIlluminationSelUserInitaited(bool bUserInitated);

public:
    /**
    * @brief	This function is called from qml to set Approach lamps value.
    * @param	iAppraochLamps: AppraochLamps will hold appraochLamps value which has set from qml.
    * @return	void
    */
    Q_INVOKABLE void setApproachLampsAttribute(int iApproachLampsIndex);

    /**
    * @brief	This function is called from qml to set vehicle auto relock value.
    * @param	bAutoRelock: AutoRelock will hold vehicle auto relock status which has set from qml.
    * @return	void
    */
    Q_INVOKABLE void setVehicleAutoRelockAttribute(bool bAutoRelock);

    /**
     * @brief setAmbLightModeAttribute : This funtion is called from qml to set ambient light mode.
     * @param iAmbLightMode : iAmbLightMode will hold ambient light mode status which has set from qml.
     * @return  void.
     */
    Q_INVOKABLE void setAmbLightModeAttribute(int iAmbLightMode);

    /**
     * @brief setAmbLightillumLevelAttribute : This funtion is called from qml to set ambient light illumination level.
     * @param iAmbLightillumLevel : iAmbLightillumLevel will hold ambient light illumination level which has set from qml.
     * @return  void.
     */
    Q_INVOKABLE void setAmbLightillumLevelAttribute(int iAmbLightillumLevel);

    /**
     * @brief   invSetAmbLightIllumLevel: Method shall be invoked from qml to set
     *          the ambient light illumination level on iluumination slider bar release.
     *          The value should be requested to service only if the last received illumination
     *          level value is different than requested illumination value otherwise
     *          only the qml shall be updated with the last received value.
     * @param   iAmbLightIllumLevel: Ambient light illumination level to be requested.
     * @return  void.
     */
    Q_INVOKABLE void invSetAmbLightIllumLevel(int iAmbLightIllumLevel);

    /**
     * @brief setBcmDrlSelectionAttribute : This function is called from qml to set drl mode.
     * @param bValue : This variable holds the drl mode which has set from qml.
     * @return  void.
     */
    Q_INVOKABLE void setBcmDrlSelectionAttribute(bool bValue);

public slots:

    /**
     * @brief sltPopupResult: Slot to catch popup results signal dispatched by popup manager.
     * @param ePopupId: Popup id for which the reslut has been dispatched.
     * @param ePopupResult: Type of result being dispatched.
     * @param strAdditionalInfo: Addtional information dispatched required to know the reason of the result if required.
     */
    void sltPopupResult(CPopupEnum::EPopupID ePopupId, CPopupEnum::EPopupResult ePopupResult, QString strAdditionalInfo);

signals:
    /**
    * @brief	This signal will emit approach lamps value whenever appraoch lamps value gets changed.
    * @param	void.
    * @return	void
    */
    void sigAppraochLampsChanged();

    /**
    * @brief	This signal will emit vehicle auto relock status whenever vehicle auto relock status gets changed.
    * @param	void.
    * @return	void
    */
    void sigVehicleAutoRelockChanged();

    /**
     * @brief sigBCMPresenceChanged : This signal will emit BCM presence status whenever BCm presence gets changed.
     * @param void.
     * @return void
     */
    void sigBCMPresenceChanged();

    /**
     * @brief sigVehicleSpeedChanged : This signal will emit vehicle speed value whenever vehicle speed gets changed.
     * @param void.
     * @return void
     */
    void sigVehicleSpeedChanged();
	
    /**
     * @brief  sigSpeedLockOutStatusChanged : This signal will emit whenever speed lockout status gets changed.
     * @param  void.
     * @return void
     */
    void sigSpeedLockOutStatusChanged();


    /**
     * @brief sigAmbientLightModeChanged : This signal will emit ambient light mode value whenever ambient mode gets changed.
     * @param   void.
     * @return  void.
     */
    void sigAmbientLightModeChanged();

    /**
     * @brief sigAmbLightIllumLevelChanged : This signal will emit ambient light illumination level
     *        whenever ambient light illumination level gets changed.
     * @param   void.
     * @return  void.
     */
    void sigAmbLightIllumLevelChanged();

    /**
     * @brief sigAmbLightIllumOnHuChanged :  This signal will emit ambient light  mode availability on HU
     *        whenever ambient mode on HU gets changed.
     * @param   void.
     * @return  void.
     */
    void sigAmbientLightModeIlluOnHuChanged();

    /**
     * @brief sigAmbLightIlluSelLevelChanged : This signal will emit ambient light selected illumination level on Hu
     *        whenever ambient light selected illumination level gets changed.
     * @param   void.
     * @return  void.
     */
    void sigAmbLightIlluSelLevelChanged();


    /**
     * @brief sigParkLampStatusChanged :  This signal will emit park lamp status
     *        whenever park lamp status gets changed.
     * @param   void.
     * @return  void.
     */
    void sigParkLampStatusChanged();

    /**
     * @brief sigVehiAutoRelockPresenceChanged : This signal will emit vehicle auto relock presence status
     *        whenever vehicle auto relock status gets changed.
     * @param   void.
     * @return  void.
     */
    void sigVehiAutoRelockPresenceChanged();

    /**
     * @brief sigAppraochLampsPresenceChanged : This signal will emit approach lamps presence status
     *        whenever approach lamps status gets changed.
     * @param   void.
     * @return  void.
     */
    void sigAppraochLampsPresenceChanged();

    /**
     * @brief sigAmbientLightAvailableStatusChanged : This signal will emit ambient light available status
     *        whenever ambient light available status gets changed.
     * @param   void.
     * @return  void.
     */
    void sigAmbientLightAvailableStatusChanged();

    /**
     * @brief sigBcmUcsStateChanged : This signal will emit Bcm Ucs state whenvever Bcm Ucs state gets changed.
     * @param   void.
     * @return  void.
     */
    void sigBcmUcsStateChanged();

    /**
     * @brief sigBcmDrlSelectionStatusChanged : This signal will emit drl status
     *        whenever drl status gets changed.
     * @param   void.
     * @return  void.
     */
    void sigBcmDrlSelectionStatusChanged();

    /**
     * @brief   sigAmbLightEnableStatusChanged : Signal shall be dispatched whenever ambient light enable status is changed.
     * @param   void.
     * @return  void.
     */
    void sigAmbLightEnableStatusChanged();

    /**
     * @brief sigBcmDrlFeaturePresenceStatusChanged : This signal will emit drl presence
     *        whenever drl presence status gets changed.
     * @param   void.
     * @return  void.
     */
    void sigBcmDrlFeaturePresenceStatusChanged();

private:
    /**
     * @brief CVehicleSettingsAdaptor class Constructor
     * @param pParent
     * @return void
     */
    explicit CVehicleSettingsAdaptor(QObject *parent = nullptr);

    /* Instance of class CAudioAdaptor */
    static CVehicleSettingsAdaptor* m_pVehicleAdaptor;

    /* Instance of class IParkAssistResource */
    IVehicleResource* m_pVehicleResource;

    /* This variable holds the vehicle approach lamps value*/
    int m_iApproachLamps;

    /* This variable holds the vehicle auto relock value*/
    bool m_bVehicleAutoRelock;

    /**
     * @brief m_bBCmPresence : This variable holds the BCm presence status
     */
    bool m_bBCmPresence;

    /**
     * @brief m_fVehicleSpeed : This variable holds vehicle speed value
     */
    float m_fVehicleSpeed;

    /**
     * @brief m_iAmbientLightMode : This variable holds ambient light mode
     */
    CVehicleEnums::EAmbientLightMode m_eAmbientLightMode;

    /**
     * @brief m_iAmbLightIllumLevel : This varibale holds ambient light illumination levels.
     */
    int m_iAmbLightIllumLevel;

    /**
     * @brief m_bAmbientLightIlluOnHu : This variable holds ambient light mode illumination on HU presence status.
     */
    bool m_bAmbientLightModeIlluOnHu;

    /**
     * @brief m_iAmbSelIlluLevel : This variable holds ambient light mode Selected illumination level on HU.
     */
    int m_iAmbSelIlluLevel;

    //! Variable shall hold last amibient light illumination level received from service.
    int m_iLastAmbLightIllumLevel;

    /**
     * @brief m_bParkLampStatus : This variable holds the park lamp status.
     */
    bool m_bParkLampStatus;

    /* This variable holds the mapping of delay timer index & delay timer values values */
    QMap<CVehicleEnums::EVehicleApproachLampsIndex,CVehicleEnums::EVehicleApproachLampsValues> m_mapApproachLamps;
	
	/** This variable holds the speed lockout status value */
    bool m_bSpeedLockOutStatus;

    /** This variable holds the vehicle auto relock presence status*/
    bool m_bVehiAutoRelockPresence;

    /** This variable holds the approach lamps presence status*/
    bool m_bAppraochLampsPresence;

    /** This variable holds the ambient light available status*/
    bool m_bAmbientLightAvailableStatus;

    /** This variable holds the Bcm Ucs state*/
    bool m_bBcmUcsState;

    /**
     * @brief m_bBcmAntitheftFeatureStatus: This Variable store the value for the Antitheft feature enabled/disabled in system.
     */
    bool m_bBcmAntitheftFeatureStatus;

    /**
     * @brief m_bBCmAntitheftKeyConfirmationStatus: This Variable store the value for the Antitheft key confirmation in system.
     */
    bool m_bBCmAntitheftKeyConfirmationStatus;

    /**
     * @brief m_bBcmDrlSelectionStatus : This variable store the value of day light running status
     */
    bool m_bBcmDrlSelectionStatus;

    //! Variable to hold enable status of ambient light component.
    bool m_bAmbLightEnableStatus;

    /**
     * @brief m_bBcmDrlFeatureStatus : This variable store the value for the DRL feature enabled/disabled in system.
     */
    bool m_bBcmDrlFeatureStatus;

    /**
     * @brief m_bIsAmbLightSelIlluLevelRespRecv : This variable holds the ambient light illumination level selected value response status.
     */
    bool m_bIsAmbLightSelIlluLevelRespRecv;

    /**
     * @brief m_iAmbLightIllumReqValue : This variable used to hold the requested value for ambient light intensity.
     */
    int m_iAmbLightIllumReqValue;

    /**
     * @brief m_bIsAmbIlluminationSelUserInitaited : Flag to maintain whether ambient light illumination changes are user initated or not.
     */
    bool m_bIsAmbIlluminationSelUserInitaited;
};

#endif // CVehicleSettingsAdaptor_H
