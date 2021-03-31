/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          IDriveNextResource.h
 * @ingroup       HMIComponent
 * @author        Nandkishor Lokhande
 * CDriveNextResourceImpl, an interface for DriveNext Resource Implementation in HMI.
 */

#ifndef IDRIVENEXTRESOURCE_H
#define IDRIVENEXTRESOURCE_H

#include "v0/com/harman/drivepro/drivepropresProxy.hpp"
#include "../implementations/CDriveNextResourceData.h"

using namespace std;
using namespace v0::com::harman::drivepro;

/*!
 * @interface   IDriveNextResource
 * @brief       This interfaces provides abstract methods to communicate with the DriveNextPresCtrl proxy directly
 *              which shall be implemented by resource implementation class.
 */
class IDriveNextResource
{
public:

    /**
    * @brief    ~IDriveNextResource: destructor for IDriveNextResource.
    * @param    NA.
    * @return   NA.
    */
    virtual ~IDriveNextResource(){}

private:

    /***** FUNCTIONS TO MAKE PROXY METHOD CALL ****************************/

    /**
     * @brief driveNextProxyStatusCb: CallBack method to get notified about the availability status of DriveNext Proxy
     * @param eStatus: status of DriveNext proxy whether available or not
     * @return void
     */
    virtual void driveNextProxyStatusCb(CommonAPI::AvailabilityStatus eStatus) = 0;

    /**
     * @brief getProxyAvailabilityStatus: method to get getProxy Availability Status
     * @param void
     * @return bool true when proxy availabile otherwise false
     */
    virtual bool getProxyAvailabilityStatus() = 0;

    /**
    * @brief    subscribeSignalsAsync: This function subscribes signals provided in vectSignalTypes
    * @param    vector<EDriveNextSignalTypes> vectSignalTypes: list of signal types.
    * @return   void.
    */
    virtual void subscribeSignalsAsync(const vector<EDriveNextSignalTypes> &vectSignalTypes) = 0;

    /**
    * @brief    subscribeSignalsAsyncCb: This function gives callback status for subscribe signals.
    * @param    CommonAPI::CallStatus request status.
    * @param    driveProTypeCollection::eReturnStatus Method call return status.
    * @param    driveProTypeCollection::signalArray arrSignalList: list of signal types.
    * @return   void.
    */
    virtual void subscribeSignalsAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus, driveProTypeCollection::signalArray arrSignalList) = 0;

    /**
    * @brief    unSubscribeSignalsAsync: This function unSubscribes signals provided in vectSignalTypes.
    * @param    vector<EDriveNextSignalTypes> vectSignalTypes: list of signal types.
    * @return   void.
    */
    virtual void unSubscribeSignalsAsync(const vector<EDriveNextSignalTypes> &vectSignalTypes) = 0;

    /**
    * @brief    unSubscribeSignalsAsyncCb: This function gives callback status for unSubscribe signals.
    * @param    CommonAPI::CallStatus request status.
    * @param    driveProTypeCollection::eReturnStatus Method call return status.
    * @param    driveProTypeCollection::signalArray arrSignalList: list of signal types.
    * @return   void.
    */
    virtual void unSubscribeSignalsAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus, driveProTypeCollection::signalArray arrSignalList) = 0;

    /**
    * @brief    getSignaListValueFromProxy: This function requests latest values for subscribed signals with DriveNext proxy
    * @param    void.
    * @return   void.
    */
    virtual void getSignaListValueFromProxy() = 0;

    /**
    * @brief    getMaxRatingFromProxy: This function requests latest value for max score rating with DriveNext proxy
    * @param    void.
    * @return   void.
    */
    virtual void getMaxRatingFromProxy() = 0;

    /**
    * @brief    getSignalValuesMap: This function gives signal values map
    * @param    void.
    * @return   map<EDriveNextSignalTypes, SSignalDataStructure> map for signals types and there data.
    */
    virtual map<EDriveNextSignalTypes, SSignalDataStructure> getSignalValuesMap() = 0;

    /**
    * @brief    onSignalValuesMapUpdate: This function is used to get signal value map update callback
    * @param    driveProTypeCollection::signalListValueMap signal value map.
    * @return   void.
    */
    virtual void onSignalValuesMapUpdate(driveProTypeCollection::signalListValueMap mapSignalValues) = 0;

    /**
     * @brief driveNextResetAvailabilityStatusCb: CallBack method to get notified about the availability status of DriveNext Reset Option
     * @param bStatus: true when DriveNext Reset Option available otherwise false
     * @return void
     */
    virtual void driveNextResetAvailabilityStatusCb(bool bStatus) = 0;

    /**
     * @brief getResetAvailabilityStatus: method to get Reset Option Availability Status
     * @param void
     * @return bool true when Reset Option availabile otherwise false
     */
    virtual bool getResetAvailabilityStatus() = 0;

    /**
    * @brief    onTripResetRequestCb: This function is to get the Trip Reset request status Information.
    * @param    objTripResetStatus: Trip Reset request status Information.
    * @return   void.
    */
    virtual void onTripResetRequestCb(driveProTypeCollection::sTripResetStatus objTripResetStatus) = 0;

    /**
    * @brief    onVersionInfoAttributeCb: This function is to get the Version Information.
    * @param    objVersionInfo: Version information.
    * @return   void.
    */
    virtual void onVersionInfoAttributeCb(driveProTypeCollection::sDpVersionInfo objVersionInfo) = 0;

    /**
     * @brief getDNConfigVersion: method to get DriveNext Config version
     * @param void
     * @return string DriveNext Config version
     */
    virtual string getDNConfigVersion() = 0;

    /**
     * @brief getDNLibVersion: method to get DriveNext Lib version
     * @param void
     * @return string DriveNext Lib version
     */
    virtual string getDNLibVersion() = 0;

    /**
     * @brief getDistanceUnitInfo: method to get DriveNext distance unit information
     * @param void
     * @return SDistanceUnitInfo distance unit information
     */
    virtual SDistanceUnitInfo getDistanceUnitInfo() = 0;

    /**
     * @brief getFuelUnitInfo: method to get DriveNext fuel unit information
     * @param void
     * @return SFuelUnitInfo fuel unit information
     */
    virtual SFuelUnitInfo getFuelUnitInfo() = 0;

    /**
     * @brief getScoreMaxRatingInfo: method to get DriveNext score max rating information
     * @param void
     * @return SSignalDataStructure score max rating information
     */
    virtual SSignalDataStructure getScoreMaxRatingInfo() = 0;

    /**
    * @brief    onResetAllOptionEnabledAttributeCb: This function is to get the boolean value whether the reset all option is enabled or not.
    * @param    bIsResetAllOptionEnabled: whether reset all option is enabled or not.
    * @return   void.
    */
    virtual void onResetAllOptionEnabledAttributeCb(bool bIsResetAllOptionEnabled) = 0;

    /**
    * @brief    onEfficiencyInfoAttributeCb: This function is to get the effciency Information.
    * @param    objEffciencyInfo: efficiency information.
    * @return   void.
    */
    virtual void onEfficiencyInfoAttributeCb(driveProTypeCollection::sEffciencyInfo objEffciencyInfo) = 0;

    /**
    * @brief    onDrivingInfoAttributeCb: This function is to get the Driving Information.
    * @param    objDrivingInfo: driving information.
    * @return   void.
    */
    virtual void onDrivingInfoAttributeCb(driveProTypeCollection::sDrivingInfo objDrivingInfo) = 0;

    /**
    * @brief    onSafetyInfoAttributeCb: This function is to get the Safety Information.
    * @param    objSafetyInfo: safety information.
    * @return   void.
    */
    virtual void onSafetyInfoAttributeCb(driveProTypeCollection::sSafetyInfo objSafetyInfo) = 0;

    /**
    * @brief    onDistUnitAttributeChanged: This function is to get the Distance Unit Information.
    * @param    objDistUnitInfo: distance unit information.
    * @return   void.
    */
    virtual void onDistUnitAttributeChanged(driveProTypeCollection::sDistUnit objDistUnitInfo) = 0;

    /**
    * @brief    onFuelUnitAttributeChanged: This function is to get the Fuel Unit Information.
    * @param    objFuelUnitInfo: fuel unit information.
    * @return   void.
    */
    virtual void onFuelUnitAttributeChanged(driveProTypeCollection::sFuelUnit objFuelUnitInfo) = 0;

    /**
    * @brief    resetTripAsync: This function is to reset trip data.
    * @param    EDriveNextTripType trip to reset.
    * @return   void.
    */
    virtual void resetTripAsync(EDriveNextTripType eTripType) = 0;

    /**
    * @brief    resetTripAsyncCb: This function is to get resetTripAsync request status.
    * @param    CommonAPI::CallStatus request status
    * @param    driveProTypeCollection::eReturnStatus Method call return status
    * @param    driveProTypeCollection::eTripType requested trip type
    * @return   void.
    */
    virtual void resetTripAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus, driveProTypeCollection::eTripType eTripType) = 0;

    /**
    * @brief    updateLibFileAsync: This function is to update Lib file.
    * @param    void.
    * @return   void.
    */
    virtual void updateLibFileAsync() = 0;

    /**
    * @brief    updateLibFileAsyncCb: This function is to get updateLibFileAsync request status.
    * @param    CommonAPI::CallStatus request status
    * @param    driveProTypeCollection::eReturnStatus Method call return status
    * @return   void.
    */
    virtual void updateLibFileAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus) = 0;

    /**
    * @brief    updateConfigFileAsync: This function is to update config file.
    * @param    void.
    * @return   void.
    */
    virtual void updateConfigFileAsync() = 0;

    /**
    * @brief    updateConfigFileAsyncCb: This function is to get updateConfigFileAsync request status.
    * @param    CommonAPI::CallStatus request status
    * @param    driveProTypeCollection::eReturnStatus Method call return status
    * @return   void.
    */
    virtual void updateConfigFileAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus) = 0;

    /**
    * @brief    extractDPLogsAsync: This function is to extract Logs.
    * @param    void.
    * @return   void.
    */
    virtual void extractDPLogsAsync() = 0;

    /**
    * @brief    extractDPLogsAsyncCb: This function is to get extractDPLogsAsync request status.
    * @param    CommonAPI::CallStatus request status
    * @param    driveProTypeCollection::eReturnStatus Method call return status
    * @return   void.
    */
    virtual void extractDPLogsAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus) = 0;

    /**
    * @brief    setTripLoggingAsync: This function is to set trip logging.
    * @param    EDriveNextTripType trip to log.
    * @return   void.
    */
    virtual void setTripLoggingAsync(EDriveNextTripType eTripType) = 0;

    /**
    * @brief    setTripLoggingAsyncCb: This function is to get setTripLoggingAsync request status.
    * @param    CommonAPI::CallStatus request status
    * @param    driveProTypeCollection::eReturnStatus Method call return status
    * @param    driveProTypeCollection::eTripType requested trip type
    * @return   void.
    */
    virtual void setTripLoggingAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus, driveProTypeCollection::eTripType eTripType) = 0;

    /**
    * @brief    getServiceScalingFactors: This function is to gets service scaling factor vlaues.
    * @param    void.
    * @return   void.
    */
    virtual void getServiceScalingFactors() = 0;

    /**
    * @brief    getServiceScalingFactorsAsync: This function is to request service scaling factor vlaues.
    * @param    void.
    * @return   void.
    */
    virtual void getServiceScalingFactorsAsync() = 0;

    /**
    * @brief    getServiceScalingFactorsAsyncCb: This function is to get callback service scaling factor vlaue.
    * @param    CommonAPI::CallStatus request status
    * @param    double scaling factor value
    * @return   void.
    */
    virtual void getServiceScalingFactorsAsyncCb(const CommonAPI::CallStatus &eStatus, const double &uiScalingFactor) = 0;

    /**
    * @brief    getScoreScalingFactor: This function is to get score scaling factor vlaue.
    * @param    void.
    * @return   double score scaling factor value.
    */
    virtual double getScoreScalingFactor() = 0;

    /**
    * @brief    getTripLogging: This function is to get trip logging.
    * @param    void.
    * @return   EDriveNextTripType trip to log.
    */
    virtual EDriveNextTripType getTripLogging() = 0;

    /**
    * @brief    setDpLogLevelAsync: This function is to set log level.
    * @param    EDriveNextLogLevel log level.
    * @return   void.
    */
    virtual void setDpLogLevelAsync(EDriveNextLogLevel eLogLevel) = 0;

    /**
    * @brief    setDpLogLevelAsyncCb: This function is to get setDpLogLevelAsync request status.
    * @param    CommonAPI::CallStatus request status
    * @param    driveProTypeCollection::eReturnStatus Method call return status
    * @param    uint32_t requested log level value
    * @return   void.
    */
    virtual void setDpLogLevelAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus, uint32_t uiLogLevel) = 0;

    /**
    * @brief    getDpLogLevel: This function is to get Log level.
    * @param    void.
    * @return   EDriveNextLogLevel log level.
    */
    virtual EDriveNextLogLevel getDpLogLevel() = 0;

    /**
    * @brief    setDpLoggingTypeAsync: This function is to set logging type.
    * @param    EDriveNextLoggingType logging type.
    * @return   void.
    */
    virtual void setDpLoggingTypeAsync(EDriveNextLoggingType eLoggingType) = 0;

    /**
    * @brief    setDpLoggingTypeAsyncCb: This function is to get setDpLoggingTypeAsync request status.
    * @param    CommonAPI::CallStatus request status
    * @param    driveProTypeCollection::eReturnStatus Method call return status
    * @param    driveProTypeCollection::eLoggingType requested logging type
    * @return   void.
    */
    virtual void setDpLoggingTypeAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus, driveProTypeCollection::eLoggingType eLoggingType) = 0;

    /**
    * @brief    getDpLoggingType: This function is to get logging type.
    * @param    void.
    * @return   EDriveNextLoggingType logging type.
    */
    virtual EDriveNextLoggingType getDpLoggingType() = 0;
};

#endif // IDRIVENEXTRESOURCE_H
