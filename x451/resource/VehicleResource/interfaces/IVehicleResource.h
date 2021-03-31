/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          IVehicleResource.h
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 *  IVehicleResource, an interface for Audio Resource Implementaion in HMI.
 */

#ifndef IVEHICLERESOURCE_H
#define IVEHICLERESOURCE_H

#include <capi/CAPIClientAbstraction.hpp>
#include "v0/com/harman/dcif/VehicleSettingsPresCtrl.hpp"
#include "v0/com/harman/dcif/VehicleSettingsPresCtrlProxy.hpp"
#include "v0/com/harman/dcif/VehicleSettingsPresCtrlProxyBase.hpp"
#include "v0/com/harman/dcif/VehicleSettingsTypeCollection.hpp"

using namespace std;
using namespace v0::com::harman::dcif;

/*!
 * @interface IVehicleResource
 * @brief This interfaces provides abstract methods to communicate with the
 * VehiclePresCtrl proxy directly which shall be implemented by resource
 * implementation class.
 */

class IVehicleResource
{
public:
    virtual ~IVehicleResource(){}

    /*****  Request METHODS  ****************************/

    /**
    * @brief	This pure virtual function is to set appraoch lamps, API call to be made with this method.
    * @param    iApproachLampsValue: iApproachLampsValue is integer holding the approach lamps value set from vehicle adaptor.
    * @return	void.
    */
    virtual void setApproachLamps(int16_t iApproachLampsValue) = 0;

    /**
    * @brief	This pure virtual function is to set vehicle auto relock, API call to be made with this method.
    * @param    bVehicleAutoRelock: bVehicleAutoRelock is bool holding the vehicle auto relock state set from vehicle adaptor.
    * @return	void.
    */
    virtual void setVehicleAutoRelock(bool bVehicleAutoRelock) = 0;

    /**
    * @brief	This pure virtual function is to get vehicle auto relock status on start up, API call to be made with this method.
    * @param    void.
    * @return	void.
    */
    virtual void getVehicleAutoRelockValue() = 0;

    /**
    * @brief	This pure virtual function is to get approach lamps value on start up, API call to be made with this method.
    * @param    void.
    * @return	void.
    */
    virtual void getApproachLampValue() = 0;

    /**
     * @brief setAmbLightMode This pure virtual function is to set ambient light mode, API call to be made with this method.
     * @param iAmbLightMode : iAmbLightMode is integer holding the ambient light mode value set from vehicle adaptor.
     * @return  void.
     */
    virtual void setAmbLightMode(int16_t iAmbLightMode) = 0;

    /**
     * @brief setAmbLightIllumLevel This pure virtual function is to set ambient light illumination level, API call to be made with this method.
     * @param iAmbLightIllumLevel : iAmbLightMode is integer holding the ambient light illumination level value set from vehicle adaptor.
     * @return  void.
     */
    virtual void setAmbLightIllumLevel(int16_t iAmbLightIllumLevel) = 0;

    /**
    * @brief    setBcmDrlSelectionState : This pure virtual function is to set day light running lamp, API call to be made with this method.
    * @param    bDrlActiveStatus: true if needs to enable otherwise false.
    * @return	void.
    */
    virtual void setBcmDrlSelectionState(bool bDrlActiveStatus) = 0;

    /*****  CALL BACK METHODS  ****************************/

    /**
    * @brief	This function is call back method to get approach lamp value, response from vehicleserviceproxy received here.
    * @param    iApproachLampValue: iApproachLampValue holding the vehicle approach lamp on response.
    * @return	void.
    */
    virtual void onApproachLampValueCb(int16_t iApproachLampValue) = 0;

    /**
    * @brief	This function is call back method to get approach lamp value, response from vehicleserviceproxy received here.
    * @param    bAutoRelockStatus: bAutoRelockStatus holding the vehicle auto relock status on response.
    * @return	void.
    */
    virtual void onVehicleAutoRelockValueCb(bool bAutoRelockStatus) = 0;

    /**
    * @brief	This function is call back method to get vehicle auto relock callback status, response from vehicleserviceproxy received here.
    * @param    status: status holding the call back status.
    * @param    eValueType: return status.
    * @return	void.
    */
    virtual void setVehicleAutoRelockAsyncCbResp(const CallStatus &callStatus, VehicleSettingsTypeCollection::retStatus_enum eReturnValue) = 0;

    /**
    * @brief	This function is call back method to get approach lamps callback status, response from vehicleserviceproxy received here.
    * @param    status: status holding the call back status.
    * @param    eValueType: return status.
    * @return	void.
    */
    virtual void setApproachLampsAsyncCbResp(const CallStatus &callStatus, VehicleSettingsTypeCollection::retStatus_enum eReturnValue) = 0;

    /**
     * @brief onBCmPresenceAttributeCb : This function is call back method to get BCM presence status, response from vehicleserviceproxy received here.
     * @param bBCmPresence: return true on BCM presence else false
     * @return void
     */
    virtual void onBCmPresenceAttributeCb(bool bBCmPresence) = 0;

    /**
     * @brief onVehicleSpeedAttributeCb : This function is call back method to get vehicle speed value, response from vehicleserviceproxy received here.
     * @param fVehicleSpeed: fVehicleSpeed holding the vehicle speed on response.
     * @return void.
     */
    virtual void onVehicleSpeedAttributeCb(float fVehicleSpeed) = 0;

    /**
     * @brief onAmbLightModeAttributeCb : This function is call back method to get ambient light mode levels value, response from vehicleserviceproxy received here.
     * @param   iAmbLightMode : iAmbLightMode holding the ambient light mode on response.
     * @return  void.
     */
    virtual void onAmbLightModeAttributeCb(int16_t iAmbLightMode) = 0;

    /**
     * @brief onAmbLightIllumPossibleLevelsCb : This function is call back method to get ambient light possible illumination levels value, response from vehicleserviceproxy received here.
     * @param iAmbLightIllumPossibleLevels : holding the ambient light possible(range) illumination levels.
     *  @return void.
     */
    virtual void onAmbLightIllumPossibleLevelsCb(int16_t iAmbLightIllumPossibleLevels) = 0;

    /**
     * @brief onAmbientLightIllumSelLevelOnHuCb : This function is call back method to get ambient light illumination level value, response from vehicleserviceproxy received here.
     * @param iAmbSelIlluLevel : holding the current level of ambient light illumination.
     *  @return void.
     */
    virtual void onAmbientLightIllumSelLevelOnHuCb(int16_t iAmbSelIlluLevel) = 0;

    /**
     * @brief onAmbLightIllumSelLevelAsyncCbResp : This function is call back method to get ambient light illumination selected level value,
     *                   response from vehicleserviceproxy received here.
     * @param callStatus : status holding the API call status.
     * @param VehicleSettingsTypeCollection::retStatus_enum : holds the value of ambient light illumination selected level.
     */
    virtual void onAmbLightIllumSelLevelAsyncCbResp(const CallStatus &callStatus, VehicleSettingsTypeCollection::retStatus_enum eReturnValue) = 0;

    /**
     * @brief onAmbientLightModeIlluOnHuCb : This function is call back method to get ambient light mode illumination value, response from vehicleserviceproxy received here.
     * @param bAmbientLightMode : bAmbientLightMode holding the ambient light mode illumination value on response.
     * @return void.
     */
    virtual void onAmbientLightModeIlluOnHuCb(bool bAmbientLightModeIlluOnHu) = 0;

    /**
     * @brief onParkLampStatusCb : This function is call back method to get park lamp status value also this is to listen on attribute change
     *                               response from vehicleserviceproxy received here.
     * @param bParkLampStatus : bParkLampStatus holding the park lamp status on response.
     * @return  void.
     */
    virtual void onParkLampStatusCb(bool bParkLampStatus) = 0;

    /**
     * @brief getBCMPresenceAsyncCb : This function is call back method to get bcm presence status, repsonse from vehicleserviceproxy received here.
     * @param status : status holding the call back status.
     * @param bBCmPresence : bcm Presence status
     */
    virtual void getBCMPresenceAsyncCb(const CallStatus &status, bool bBCmPresence) = 0;

    /**
     * @brief onAmbLightModeAsyncCbResp : Callback to get notified about ambient light mode.
     * @param callStatus : status holding the API call status.
     * @param VehicleSettingsTypeCollection::retStatus_enum : holds the value of ambient light mode.
     */
    virtual void onAmbLightModeAsyncCbResp(const CallStatus &callStatus, VehicleSettingsTypeCollection::retStatus_enum eReturnValue) = 0;

    /**
     * @brief onAmbLightIllumPossibleLevelAsyncCbResp : This function is call back method to get ambient light illumination levels value,
     *                   response from vehicleserviceproxy received here.
     * @param callStatus : status holding the API call status.
     * @param VehicleSettingsTypeCollection::retStatus_enum : holds the value of ambient light illumination level.
     */
    virtual void onAmbLightIllumPossibleLevelAsyncCbResp(const CallStatus &callStatus, VehicleSettingsTypeCollection::retStatus_enum eReturnValue) = 0;

    /**
     * @brief   onSpeedLockOutEventCb: This is a callback method to the change event of getSpeedLockOutEvent.
     * @param   bSpeedLockOutStatus: holds speed lockOut status.
     * @return  void.
     */
    virtual void onSpeedLockOutEventCb(bool bSpeedLockOutStatus) = 0;


    /**
     * @brief onAntitheftFeaturePresenceAttributeCb: Call back function with the response whether the feature is enabled/disabled in system.
     * @param bIsAntitheftFeatureEnabled: value of the Antitheft feature presence.
     * @return void.
     */
    virtual void onAntitheftFeaturePresenceAttributeCb(bool bIsAntitheftFeatureEnabled) = 0;

    /**
     * @brief onBCmAntitheftKeyConfirmationValueCb: Call back function with the response whether the keyconfirmation has been verified or not in system.
     * @param iAntitheftKeyConfirmationValue: Key confirmation status.
     * @return void.
     */
    virtual void onBCmAntitheftKeyConfirmationValueCb(int iAntitheftKeyConfirmationValue) = 0;

    /**
     * @brief getBCmAntitheftFeaturePresenceValue: This function returns the value for Antitheft feature in a system.
     * @param void.
     * @return value of Anti theft feature.
     */
    virtual bool getBCmAntitheftFeaturePresenceValue() = 0;

    /**
     * @brief getBCmAntitheftKeyConfirmationValue: This function returns the value for Antitheft key confirmation in a system.
     * @param void.
     * @return value of Anti theft key confirmation.
     */
    virtual bool getBCmAntitheftKeyConfirmationValue() = 0;

    /**
     * @brief getAmbSelIlluminationLevel : This function returns the value of ambient light selected illumination level.
     * @param   void.
     * @return value of ambient light illumination level.
     */
    virtual int getAmbSelIlluminationLevel() = 0;

    /**
     * @brief getBcmDrlSelectionState : This function returns the value of bcm drl selection state.
     * @param   void.
     * @return  value of bcm drl selection status.
     */
    virtual bool getBcmDrlSelectionState() = 0;

    /**
    * @brief	onBcmDrlSelectionStateValueCb : This function is call back method to get drl value, response from vehicleserviceproxy received here.
    * @param    bDrlMode: bAutoRelockStatus holding the drl mode value on response.
    * @return	void.
    */
    virtual void onBcmDrlSelectionStateValueCb(bool bDrlMode) = 0;

    /**
     * @brief getBcmDrlFeaturePresenceStatus : This function returns the value of bcm drl feature presence state.
     * @param   void.
     * @return  value of bcm drl feature presence status.
     */
    virtual bool getBcmDrlFeaturePresenceStatus() = 0;

    /**
     * @brief onBcmDrlFeaturePresence : This function returns the value for DRL feature in a system.
     * @param  bIsDrlFeatureEnabled: value of the DRL feature presence.
     * @return  void
     */
    virtual void onBcmDrlFeaturePresenceAtrributeCb(bool bIsDrlFeatureEnabled) = 0;

    /**
     * @brief onBcmDrlActiveSignalValAsyncCbResp : This function is call back method to get bcm drl selection value,
     *                   response from vehicleserviceproxy received here.
     * @param callStatus : status holding the API call status.
     * @param VehicleSettingsTypeCollection::retStatus_enum : holds the value of bcm drl selection state value.
     */
    virtual void onBcmDrlActiveSignalValAsyncCbResp(const CallStatus &callStatus, VehicleSettingsTypeCollection::retStatus_enum eReturnValue) = 0;

    /**
     * @brief setAmbLightIllumLevelCb : This function is call back method to get the ambient light selected illumination level response status
     *                          recieved from vehicleserviceproxy.
     * @param eCallStatus : status holding the API call status.
     * @param eReturnValue : holds the error status.
     */
    virtual void setAmbLightIllumLevelAsyncCb(const CommonAPI::CallStatus& eCallStatus, VehicleSettingsTypeCollection::retStatus_enum eErrorStatus) = 0;
};

#endif // IVEHICLERESOURCE_H
