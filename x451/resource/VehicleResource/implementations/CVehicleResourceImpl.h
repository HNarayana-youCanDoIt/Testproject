/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CVehicleResourceImpl.h
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * CVehicleResourceImpl, Resource Implementation for Audio.
 */

#ifndef CVEHICLERESOURCEIMPL_H
#define CVEHICLERESOURCEIMPL_H

#include "interfaces/IVehicleResource.h"
#include "CVehicleSettingsEventProvider.h"

using namespace std;
using namespace v0::com::harman::dcif;

/**
*   @brief The VehicleResourceImpl class
*   This class implements the VehicleResourceImpl interface.
*/

class CVehicleResourceImpl : public IVehicleResource
{

public:
    virtual ~CVehicleResourceImpl();

    CVehicleSettingsEventProvider* getVehicleEventProvider();

    /**
    * @brief	This function is to check the availability of audio settings proxy.
    * @param    eStatus: status will have API availability status.
    * @return	void.
    */
    void vehicleSettingsSeriveStatusCb(CommonAPI::AvailabilityStatus eStatus);


    /*****  Request METHODS  ****************************/
    void setApproachLamps(int16_t iApproachLampsValue) override;

    void setVehicleAutoRelock(bool bVehicleAutoRelock) override;

    void getVehicleAutoRelockValue() override;

    void setAmbLightMode(int16_t iAmbLightMode) override;

    void setAmbLightIllumLevel(int16_t iAmbLightIllumLevel) override;

    /**
     * @brief getBCMPresence : This method is used to get the bcm presence
     * @param   void.
     * @return  void.
     */
    void getBCMPresence();

    void getApproachLampValue() override;

    /**
     * @brief getAmbLightMode : This method is used to get the ambient light mode
     * @param   void.
     * @return  void.
     */
    void getAmbLightMode();

    /**
     * @brief getAmbLightIllumPossibleLevel : This method is used to get the ambient light illumination levels.
     * @param   void.
     * @return  void.
     */
    void getAmbLightIllumPossibleLevel();

    /**
     * @brief getAmbLightIllumSelLevel : This method is used to get the ambient light illumination selected level.
     * @param   void.
     * @return  void.
     */
    void getAmbLightIllumSelLevel();

    void setBcmDrlSelectionState(bool bDrlActiveStatus) override;

    /**
     * @brief getBcmDrlActiveSignalVal : This method is used to get the bcm drl selection value.
     * @param   void.
     * @return  void.
     */
    void getBcmDrlActiveSignalVal();

    /*****  CALL BACK METHODS  ****************************/
    void onApproachLampValueCb(int16_t iApproachLampValue) override;

    void onVehicleAutoRelockValueCb(bool bAutoRelockStatus) override;

    void setVehicleAutoRelockAsyncCbResp(const CallStatus &callStatus, VehicleSettingsTypeCollection::retStatus_enum eReturnValue) override;

    void setApproachLampsAsyncCbResp(const CallStatus &callStatus, VehicleSettingsTypeCollection::retStatus_enum eReturnValue) override;

    void onBCmPresenceAttributeCb(bool bBCmPresence) override;

    void onVehiAutoRelockPresenceAttributeCb(bool bVehiAutoRelockPresence);

    void onApproachLampsPresenceAttributeCb(bool bApproachLampsPresence);

    void onBcmUcsStateAttributeCb(bool bBcmUcsState);

    void onVehicleSpeedAttributeCb(float fVehicleSpeed) override;

    void onAmbLightModeAttributeCb(int16_t iAmbLightMode) override;

    void onAmbLightIllumPossibleLevelsCb(int16_t iAmbLightIllumPossibleLevels) override;

    void onAmbientLightModeIlluOnHuCb(bool bAmbientLightModeIlluOnHu) override;

    void onAmbientLightIllumSelLevelOnHuCb(int16_t iAmbSelIlluLevel) override;

    void onParkLampStatusCb(bool bParkLampStatus) override;

    void getBCMPresenceAsyncCb(const CallStatus &status, bool bBCmPresence) override;

    void onAmbLightModeAsyncCbResp(const CallStatus &callStatus, VehicleSettingsTypeCollection::retStatus_enum eReturnValue) override;

    void onAmbLightIllumPossibleLevelAsyncCbResp(const CallStatus &callStatus, VehicleSettingsTypeCollection::retStatus_enum eReturnValue) override;

    void onAmbLightIllumSelLevelAsyncCbResp(const CallStatus &callStatus, VehicleSettingsTypeCollection::retStatus_enum eReturnValue) override;

    void onBcmDrlActiveSignalValAsyncCbResp(const CallStatus &callStatus, VehicleSettingsTypeCollection::retStatus_enum eReturnValue) override;

    /**
     * @brief   onSpeedLockOutEventCb: This is a callback method to the change event of getSpeedLockOutEvent.
     * @param   bSpeedLockOutStatus: holds speed lockOut status.
     * @return  void.
     */
    void onSpeedLockOutEventCb(bool bSpeedLockOutStatus) override;

    /**
     * @brief onAntitheftFeaturePresenceAttributeCb: Call back function with the response whether the feature is enabled/disabled in system.
     * @param bIsAntitheftFeatureEnabled: value of the Antitheft feature presence.
     * @return void.
     */
    void onAntitheftFeaturePresenceAttributeCb(bool bIsAntitheftFeatureEnabled) override;

    /**
     * @brief onBCmAntitheftKeyConfirmationValueCb: Call back function with the response whether the keyconfirmation has been verified or not in system.
     * @param iAntitheftKeyConfirmationValue: Key confirmation status.
     * @return void.
     */
    void onBCmAntitheftKeyConfirmationValueCb(int iAntitheftKeyConfirmationValue) override;

    /**
     * @brief getBCmAntitheftFeaturePresenceValue: This function returns the value for Antitheft feature in a system.
     * @param void.
     * @return value of Anti theft feature.
     */
    bool getBCmAntitheftFeaturePresenceValue() override;

    /**
     * @brief getBCmAntitheftKeyConfirmationValue: This function returns the value for Antitheft key confirmation in a system.
     * @param void.
     * @return value of Anti theft key confirmation.
     */
    bool getBCmAntitheftKeyConfirmationValue() override;

    /**
     * @brief  onGetHuBcmRequestErrorEventCb: This is a callback method to getHuBCmRequestErrorEvent, notifies any error from BCM module.
     * @param  eBcmRequestStatus: BCM request status, success = 0 or failure = -1.
     * @return void.
     */
    void onGetHuBcmRequestErrorEventCb(VehicleSettingsTypeCollection::retStatus_enum eBcmRequestStatus);

    int getAmbSelIlluminationLevel() override;

    bool getBcmDrlSelectionState() override;

    void onBcmDrlSelectionStateValueCb(bool bDrlMode) override;

    bool getBcmDrlFeaturePresenceStatus() override;

    void onBcmDrlFeaturePresenceAtrributeCb(bool bIsDrlFeatureEnabled) override;

    void setAmbLightIllumLevelAsyncCb(const CommonAPI::CallStatus& eCallStatus, VehicleSettingsTypeCollection::retStatus_enum eErrorStatus) override;

private:
    friend class ResourceFactory;

    CVehicleResourceImpl();

    /**
    * @brief	This function is to subscribe the vehicle settings events
    *           provided by VehicleSettingsService proxy.
    * @param    void.
    * @return	void.
    */
    void subscribeVehicleSettingsProxy();

    /* Create an instance of the CVehicleSettingsEventProvider to emit signals to the upper layer **/
    CVehicleSettingsEventProvider* m_pVehicleEventProvider;

    /* VehicleSettingsServiceProxy class object to call vehicle proxy methods **/
    CAPIClientAbstraction<VehicleSettingsPresCtrlProxy> m_objVehicleServiceProxy;

    /* This variable holds the service availability status, TRUE if available else FALSE **/
    bool m_bVehicleSettingAvailable;

    /**
     * @brief m_bIsBCmAntitheftFeatureEnabled: This Variable store the value for the Antitheft feature enabled/disabled in system.
     */
    bool m_bIsBCmAntitheftFeatureEnabled;

    /**
     * @brief m_bIsBCmAntitheftKeyConfirmed: This Variable store the value for the Antitheft key confirmation in system.
     */
    bool m_bIsBCmAntitheftKeyConfirmed;

    /**
     * @brief m_iAmbSelIlluLevel: This Variable store the value ambient light illumination level.
     */
    int m_iAmbSelIlluLevel;

    /**
     * @brief m_bBcmDrlFeatureStatus : This variable stores the bcm drl feature presence status.
     */
    bool m_bBcmDrlFeatureStatus;

    /**
     * @brief m_bBcmDrlSelectionStatus : This variable stores the bcm drl selection status.
     */
    bool m_bBcmDrlSelectionStatus;

};

#endif // CVEHICLERESOURCEIMPL_H
