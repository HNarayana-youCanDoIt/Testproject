/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CVehicleSettingsEventProvider.h
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * CVehicleSettingsEventProvider, Class to send signals to Setup Application layer on vehicle settings Resource events
 */

#ifndef CVehicleSettingsEventProvider_H
#define CVehicleSettingsEventProvider_H

#include <QObject>
#include "CVehicleEnums.h"
using namespace std;

class CVehicleSettingsEventProvider :  public QObject
{
    Q_OBJECT
public:
    CVehicleSettingsEventProvider(QObject* pParent = 0);
    ~CVehicleSettingsEventProvider();

signals:
    /**
    * @brief	This signal is emitted when appraoch lamps changed and
    *           consumed by the application layer.
    * @param	iAppraochLampsValue: apprach lamps value.
    * @return	void.
    */
    void sigUpdateApproachLampsValue(int iAppraochLampsValue);

    /**
    * @brief	This signal is emitted when vehicle auto relock changed and
    *           consumed by the application layer.
    * @param	bAutoRelockStatus: vehicle auto relock status.
    * @return	void.
    */
    void sigUpdateVehicleAutoRelockStatus(bool bAutoRelockStatus);

    /**
     * @brief sigUpdateBCMPresenceStatus : This signal is emitted when BCM presence changed and
     *           consumed by the application layer.
     * @param bBCmPresenceStatus: bcm presence status.
     * @return void.
     */
    void sigUpdateBCMPresenceStatus(bool bBCmPresenceStatus);

    /**
     * @brief sigUpdateVehicleSpeedValue : This signal is emitted when vehicle speed changed and
     *          consumed by the application layer.
     * @param fVehicleSpeed: vehicle speed value.
     * @return void.
     */
    void sigUpdateVehicleSpeedValue(float fVehicleSpeed);

    /**
     * @brief sigUpdateAmbLightModeValue : This signal is emitted when ambient light mode changed and
     *          consumed by the application layer.
     * @param iAmbLightMode : ambient light mode value.
     * @return  void.
     */
    void sigUpdateAmbLightModeValue(int iAmbLightMode);

    /**
     * @brief sigUpdateAmbLightIllumLevelValue : This signal is emitted when ambient light illumination levels
     *          changed and consumed by the application layer.
     * @param iAmbLightIllumPossibleLevels : ambient light illumination levels.
     * @return  void.
     */
    void sigUpdateAmbLightIllumLevelValue(int iAmbLightIllumPossibleLevels);

    /**
     * @brief sigUpdateParkLampStatus : This signal is emitted when park lamp status
     *          changed and consumed by the application layer.
     * @param bParkLampStatus : park lamp status
     * @return  void.
     */
    void sigUpdateParkLampStatus(bool bParkLampStatus);

    /**
     * @brief  sigUpdateSpeedLockOutStatus: This signal is emitted when speed lockout status is changed.
     * @param  bSpeedLockOutStatus: speed lockout status.
     * @return void.
     */
    void sigUpdateSpeedLockOutStatus(bool bSpeedLockOutStatus);

    /**
     * @brief sigUpdateAmbientLightModeIlluOnHuValue : This signal is emitted when ambient light mode illumination status is changed.
     * @param bAmbientLightModeIlluOnHu : ambient light mode illumination on HU status.
     * @return void.
     */
    void sigUpdateAmbientLightModeIlluOnHuValue(bool bAmbientLightModeIlluOnHu);

    /**
     * @brief sigUpdateVehiAutoRelockPresenceStatus : This signal is emitted when vehicle auto relock presence status is changed.
     * @param bVehiAutoRelockPresence : vehicle auto relock presence status.
     * @return  void.
     */
    void sigUpdateVehiAutoRelockPresenceStatus(bool bVehiAutoRelockPresence);

    /**
     * @brief sigUpdateApproachLampsPresenceStatus : This signal is emitted when approach lamps presence status is changed.
     * @param bApproachLampsPresence : appraoch lamps presence status.
     * @return void.
     */
    void sigUpdateApproachLampsPresenceStatus(bool bApproachLampsPresence);

    /**
     * @brief sigUpdateBcmUcsState : This signal is emitted when BCm Ucs state is changed.
     * @param bBcmUcsState : BcmUcs state.
     * @return  void.
     */
    void sigUpdateBcmUcsState(bool bBcmUcsState);

    /**
     * @brief sigUpdateAntitheftFeaturePresenceStatus: this signal is emitted when anti theft presence feature is updated.
     * @param bIsAntitheftFeatureEnabled: value of the Antitheft feature presence.
     * @return void.
     */
    void sigUpdateAntitheftFeaturePresenceStatus(bool bIsAntitheftFeatureEnabled) ;

    /**
     * @brief sigUpdateBCmAntitheftKeyConfirmationValue: this signal is emitted when anti theft key confirmation feature is updated.
     * @param bIsAntitheftKeyConfirmed: Key confirmation status.
     * @return void.
     */
    void sigUpdateBCmAntitheftKeyConfirmationValue(bool bIsAntitheftKeyConfirmed) ;

    /**
     * @brief  sigVehicleSettingChangeError : This signal is emitted when Vehicle Setting can not be changed.
     * @param  None.
     * @return void.
     */
    void sigVehicleSettingChangeError();

    /**
     * @brief  sigUpdateAmbLightIlluSelLevelValue : This signal is emitted when ambient light illumination level changed.
     * @param  iAmbSelIlluLevel : value of ambient light illumination level.
     * @return void.
     */
    void sigUpdateAmbLightIlluSelLevelValue(int iAmbSelIlluLevel);

    /**
     * @brief sigBcmDrlSelectionState : This signal is emitted when drl value is changed.
     * @param bDrlMode : value of day light running lamp value.
     * @return  void.
     */
    void sigBcmDrlSelectionState(bool bDrlMode);

    /**
     * @brief sigUpdateBcmDrlFeaturePresenceStatus : This signal is emitted when drl presence is changed.
     * @param bIsDrlFeatureEnabled : value of the DRL feature presence.
     * @return  void.
     */
    void sigUpdateBcmDrlFeaturePresenceStatus(bool bIsDrlFeatureEnabled);

    /**
     * @brief sigUpdateAmbLightSelIllumLevelResponse : This signal is emitted when ambient light selected
     * illumination level response is changed
     * @param   void.
     * @return  void.
     */
    void sigUpdateAmbLightSelIllumLevelResponse();

public:
    /**
    * @brief	This function is called from resource layer when appraoch lamp value has updated.
    * @param	iAppraochLamps: Appraoch lamp value.
    * @return	void.
    */
    void updateApproachLampsValue(qint16 iAppraochLamps);

    /**
    * @brief	This function is called from resource layer when vehicle auto relock status has updated.
    * @param	bAutoRelockStatus: auto relock status.
    * @return	void.
    */
    void updateVehicleAutoRelockStatus(bool bAutoRelockStatus);

    /**
     * @brief updateBCMPresenceStatus : This function is called from resource layer when BCM presence status has updated.
     * @param bBCmPresenceStatus: bcm Presence status
     * @return void.
     */
    void updateBCMPresenceStatus(bool bBCmPresenceStatus);

    /**
     * @brief updateVehiAutoRelockPresenceStatus : This function is called from resource layer when vehicle auto relock
     *         presence status has updated.
     * @param bVehiAutoRelockPresence : vehicle auto relock presence status.
     * @return  void.
     */
    void updateVehiAutoRelockPresenceStatus(bool bVehiAutoRelockPresence);

    /**
     * @brief updateVehicleSpeedValue : This function is called from resource layer when vehicle speed value has updated.
     * @param fVehicleSpeed : vehicle speed value
     * @return void.
     */
    void updateVehicleSpeedValue(float fVehicleSpeed);

    /**
     * @brief updateAmbLightModeValue : This function is called from resource layer when ambient Light mode value has updated.
     * @param iAmbLightMode : Ambient Light mode value.
     * @return void.
     */
    void updateAmbLightModeValue(int iAmbLightMode);

    /**
     * @brief updateAmbLightIllumLevelValue : This function is called from resource layer when ambient Light illumination
     *          levels value has updated.
     * @param iAmbLightIllumLevel : ambient light illumination possible levels.
     * @return void.
     */
    void updateAmbLightIllumLevelValue(int iAmbLightIllumLevel);

    /**
     * @brief updateAmbientLightModeIlluOnHuValue : This function is called from resource layer when ambient Light illumination
     *          mode on HU value has updated.
     * @param bAmbientLightModeIlluOnHu : ambient light mode illumination value.
     * @return void.
     */
    void updateAmbientLightModeIlluOnHuValue(bool bAmbientLightModeIlluOnHu);

    /**
     * @brief updateAmbLightIlluSelLevelOnHuValue : This function is called from resource layer when ambient Light illumination
     *          level on HU value has updated.
     * @param iAmbSelIlluLevel : ambient light mode illumination level.
     * @return void.
     */
    void updateAmbLightIlluSelLevelOnHuValue(int16_t iAmbSelIlluLevel);

    /**
     * @brief updateParkLampStatus : This function is called from resource layer when park lamp status has updated.
     * @param bParkLampStatus : park lamp status.
     * @return  void.
     */
    void updateParkLampStatus(bool bParkLampStatus);

    /**
     * @brief  updateSpeedLockOutStatus : This function is called from resource layer when speed lockout value has updated.
     * @param  bSpeedLockOutStatus: holds speed lockout status.
     * @return void.
     */
    void updateSpeedLockOutStatus(bool bSpeedLockOutStatus);

    /**
     * @brief updateApproachLampsPresenceStatus : This function is called from resource layer when approach lamps presence has updated.
     * @param bApproachLampsPresence : holds approach lamps presence status.
     * @return  void.
     */
    void updateApproachLampsPresenceStatus(bool bApproachLampsPresence);

    /**
     * @brief updateBcmUcsState : This function is called from resource layer when Bcm Ucs state has updated.
     * @param bBcmUcsState : holds the Bcm Ucs state.
     * @return  void.
     */
    void updateBcmUcsState(bool bBcmUcsState);

    /**
     * @brief updateAntitheftFeaturePresenceStatus: sends the signal with the anti theft presence state to application layer.
     * @param bIsAntitheftFeatureEnabled: value of the Antitheft feature presence.
     * @return void.
     */
    void updateAntitheftFeaturePresenceStatus(bool bIsAntitheftFeatureEnabled) ;

    /**
     * @brief updateBCmAntitheftKeyConfirmationValue: sends the signal with the anti theft ckey confirmation value to application layer.
     * @param bIsAntitheftKeyConfirmed: Key confirmation status.
     * @return void.
     */
    void updateBCmAntitheftKeyConfirmationValue(bool bIsAntitheftKeyConfirmed) ;

    /**
     * @brief  updateVehicleSettingChangeError: This function is called from resource layer when Vehicle Setting can not be change.
     * @param  None.
     * @return void.
     */
    void updateVehicleSettingChangeError();

    /**
     * @brief updateBcmDrlSelectionState: This function is called from resource layer when day light running lamp value updated.
     * @param  bDrlMode : value of drl mode.
     * @return  void.
     */
    void updateBcmDrlSelectionState(bool bDrlMode);

    /**
     * @brief updateBcmDrlFeaturePresenceStatus : sends the signal with the drl presence state to application layer.
     *  @param bIsDrlFeatureEnabled: value of the DRL feature presence.
     */
    void updateBcmDrlFeaturePresenceStatus(bool bIsDrlFeatureEnabled);

    /**
     * @brief updateAmbLightSelIllumLevelResponse : This function sends the signal when ambient light selected
     *  illumination level response status gets changed.
     * @param   void.
     * @return  void.
     */
    void updateAmbLightSelIllumLevelResponse();
};

#endif // CVehicleSettingsEventProvider_H
