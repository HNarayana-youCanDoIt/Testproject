/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CVehicleSettingsEventHandler.h
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * This class is to handle vehicle settings and vehicle events.
 */

#ifndef CVehicleSettingsEventHandler_H
#define CVehicleSettingsEventHandler_H

#include <QObject>
#include "CVehicleEnums.h"

/**
 * @brief The CVehicleSettingsEventHandler class: This class is to handle vehicle events.
 *          vehicle resource event provider will emit signals and those will be handled here.
 */
class CVehicleSettingsEventHandler : public QObject
{
    Q_OBJECT
public:
    CVehicleSettingsEventHandler(QObject* parent = 0);
    ~CVehicleSettingsEventHandler();

public slots:
    /**
    * @brief	This function will update approach lamps value received from vehicle Resource layer.
    * @param	iAppraochLampsValue: appraoch lamps value from vehicleProxyService.
    * @return	void
    */
    void sltUpdateApproachLampsValue(int iAppraochLampsValue);

    /**
    * @brief	This function will update auto relock status received from vehicle Resource layer.
    * @param	bAutoRelockStatus: auto relock status from vehicleProxyService.
    * @return	void
    */
    void sltUpdateVehicleAutoRelockStatus(bool bAutoRelockStatus);

    /**
     * @brief sltupdateBCMPresenceStatus : This function will update BCM presence status received from vehicle Resource layer.
     * @param bBCmPresence: BCm presence status from vehicleProxyService.
     * @return void.
     */
    void sltUpdateBCMPresenceStatus(bool bBCmPresence);

    /**
     * @brief sltUpdateVehicleSpeedValue : This function will update vehicle speed value received from vehicle Resource layer.
     * @param fVehicleSpeed: vehicle speed value from vehicleProxyService.
     * @return void.
     */
    void sltUpdateVehicleSpeedValue(float fVehicleSpeed);
	
    /**
     * @brief  sltUpdateVehicleSpeedValue : This function will update speed lockout status value received from vehicle Resource layer.
     * @param  bSpeedLockOutStatus: holds speed lockout status.
     * @return void.
     */
    void sltUpdateSpeedLockOutStatus(bool bSpeedLockOutStatus);

    /**
     * @brief sltUpdateAmbLightModeValue : This function will update ambient light mode value received from vehicle Resource layer.
     * @param iAmbLightMode : ambient light mode value from vehicleProxyService.
     * @return  void.
     */
    void sltUpdateAmbLightModeValue(int iAmbLightMode);

    /**
     * @brief sltUpdateAmbLightIllumLevelValue : This function will update ambient light illumination level
     *          value received from vehicle Resource layer.
     * @param iAmbLightIlluLevel : ambient light illumination level value from vehicleProxyService.
     * @return void.
     */
    void sltUpdateAmbLightIllumLevelValue(int iAmbLightIlluLevel);

    /**
     * @brief sltUpdateAmbientLightModeIlluOnHuStatus : This function will update ambient light illumination mode status
     *          value received from vehicle Resource layer.
     * @param bAmbientLightModeIlluOnHu : ambient light illumination mode on HU value from vehicleProxyService.
     * @return void.
     */
    void sltUpdateAmbientLightModeIlluOnHuStatus(bool bAmbientLightModeIlluOnHu);

    /**
     * @brief sltUpdateAmbLightIlluSelLevelValue : This function will update ambient light illumination level
     *          value received from vehicle Resource layer.
     * @param iAmbLightIlluLevel : ambient light illumination level value from vehicleProxyService.
     * @return void.
     */
    void sltUpdateAmbLightIlluSelLevelValue(int iAmbSelIlluLevel);

    /**
     * @brief sltUpdateParkLampStatus : This function will update park lamp status
     *          value received from vehicle Resource layer.
     * @param bParkLampStatus : park lamp status from vehicleProxyService.
     * @return  void.
     */
    void sltUpdateParkLampStatus(bool bParkLampStatus);

    /**
     * @brief sltUpdateVehiAutoRelockPresenceStatus : This function will update vehicle auto relock presence status
     * @param bVehiAutoRelockPresence : vehicle auto relock presence status
     * @return  void.
     */
    void sltUpdateVehiAutoRelockPresenceStatus(bool bVehiAutoRelockPresence);

    /**
     * @brief sltUpdateApproachLampsPresenceStatus : This function will update approach lamps presence status.
     * @param bApproachLampsPresence : approach lamps presence status
     * @return  void.
     */
    void sltUpdateApproachLampsPresenceStatus(bool bApproachLampsPresence);

    /**
     * @brief sltUpdateBcmUcsState : This function update the Bcm Ucs state.
     * @param bBcmUcsState : BcmUcs state will hold true if enabled else false.
     * @return  void.
     */
    void sltUpdateBcmUcsState(bool bBcmUcsState);  

    /**
     * @brief sltUpdateAntitheftFeaturePresenceStatus: function with the response whether the feature is enabled/disabled in system.
     * @param bIsAntitheftFeatureEnabled: value of the Antitheft feature presence.
     * @return void.
     */
    void sltUpdateAntitheftFeaturePresenceStatus(bool bIsAntitheftFeatureEnabled);

    /**
     * @brief sltUpdateBCmAntitheftKeyConfirmationValue: function with the response whether the keyconfirmation has been verified or not in system.
     * @param bIsAntitheftKeyConfirmed: Key confirmation status.
     * @return void.
     */
    void sltUpdateBCmAntitheftKeyConfirmationValue(bool bIsAntitheftKeyConfirmed);

    /**
     * @brief  sltVehicleSettingChangeError: This function update the Vehicle Setting change error.
     * @param  None.
     * @return void.
     */
    void sltVehicleSettingChangeError();

    /**
     * @brief sltBcmDrlSelectionState : This function updates the Drl mode.
     * @param bDrlMode : drl mode status from vehicleProxyService.
     */
    void sltBcmDrlSelectionState(bool bDrlMode);

    /**
     * @brief sltUpdateBcmDrlFeaturePresenceStatus: function with the response whether the feature is enabled/disabled in system.
     * @param bIsDrlFeatureEnabled: value of the drl feature presence.
     * @return void.
     */
    void sltUpdateBcmDrlFeaturePresenceStatus(bool bIsDrlFeatureEnabled);

    /**
     * @brief sltUpdateAmbLightSelIllumLevelResponse : This function will update the ambient light selected illumination
     *          level response status.
     * @param   void.
     * @return  void.
     */
    void sltUpdateAmbLightSelIllumLevelResponse();

private:
    /**
    * @brief	This function will connect signals and slots.
    * @param	void
    * @return	void
    */
    void connectSignals();

};

#endif // CVehicleSettingsEventHandler_H
