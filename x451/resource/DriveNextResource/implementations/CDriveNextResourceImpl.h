/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CDriveNextResourceImpl.h
 * @ingroup       HMIComponent
 * @author        Nandkishor Lokhande
 * CDriveNextResourceImpl, Resource Implementation for DriveNext.
 */

#ifndef CDRIVENEXTRESOURCEIMPL_H
#define CDRIVENEXTRESOURCEIMPL_H

#include "interfaces/IDriveNextResource.h"
#include "CDriveNextEventProvider.h"
#include <capi/CAPIClientAbstraction.hpp>

using namespace std;
using namespace v0::com::harman::drivepro;

/*!
 * @class   CDriveNextResourceImpl
 * @brief   This class provides methods to communicate with the DriveNextPresCtrl proxy directly
 *          which are inherited from IDriveNextResource interface.
 */
class CDriveNextResourceImpl : public IDriveNextResource
{
public:

    /*****  DriveNext Resource Methods  ****************************/

    /**
    * @brief    ~CDriveNextResourceImpl: destructor for CDriveNextResourceImpl.
    * @param    NA.
    * @return   NA.
    */
    virtual ~CDriveNextResourceImpl();

    /**
    * @brief    getEventProvider: getter method to get DriveNext event provider object.
    * @param    void.
    * @return   CDriveNextEventProvider object pointer.
    */
    CDriveNextEventProvider* getEventProvider();

public:

    /*****  DriveNext Proxy API's  ****************************/

    /**
    * @brief    subscribeSignalsAsync: This function subscribes signals provided in vectSignalTypes
    * @param    vector<EDriveNextSignalTypes> vectSignalTypes: list of signal types.
    * @return   void.
    */
    void subscribeSignalsAsync(const vector<EDriveNextSignalTypes> &vectSignalTypes) override;

    /**
    * @brief    unSubscribeSignalsAsync: This function unSubscribes signals provided in vectSignalTypes
    * @param    vector<EDriveNextSignalTypes> vectSignalTypes: list of signal types.
    * @return   void.
    */
    void unSubscribeSignalsAsync(const vector<EDriveNextSignalTypes> &vectSignalTypes) override;

    /**
    * @brief    getSignaListValueFromProxy: This function requests latest values for subscribed signals with DriveNext proxy
    * @param    void.
    * @return   void.
    */
    void getSignaListValueFromProxy() override;

    /**
    * @brief    getMaxRatingFromProxy: This function requests latest value for max score rating with DriveNext proxy
    * @param    void.
    * @return   void.
    */
    void getMaxRatingFromProxy() override;

    /**
    * @brief    getSignalValuesMap: This function gives signal values map
    * @param    void.
    * @return   map<EDriveNextSignalTypes, SSignalDataStructure> map for signals types and there data.
    */
    map<EDriveNextSignalTypes, SSignalDataStructure> getSignalValuesMap() override;

    /**
    * @brief    onSignalValuesMapUpdate: This function is used to get signal value map update callback
    * @param    driveProTypeCollection::signalListValueMap signal value map.
    * @return   void.
    */
    void onSignalValuesMapUpdate(driveProTypeCollection::signalListValueMap mapSignalValues) override;

    /**
     * @brief getResetAvailabilityStatus: method to get Reset Option Availability Status
     * @param void
     * @return bool true when Reset Option availabile otherwise false
     */
    bool getResetAvailabilityStatus() override;

    /**
    * @brief    resetTripAsync: This function is to reset trip data.
    * @param    EDriveNextTripType trip to reset.
    * @return   void.
    */
    void resetTripAsync(EDriveNextTripType eTripType) override;

    /**
    * @brief    updateLibFileAsync: This function is to update Lib file.
    * @param    void.
    * @return   void.
    */
    void updateLibFileAsync() override;

    /**
    * @brief    updateConfigFileAsync: This function is to update config file.
    * @param    void.
    * @return   void.
    */
    void updateConfigFileAsync() override;

    /**
    * @brief    extractDPLogsAsync: This function is to extract Logs.
    * @param    void.
    * @return   void.
    */
    void extractDPLogsAsync() override;

    /**
    * @brief    setTripLoggingAsync: This function is to set trip logging.
    * @param    EDriveNextTripType trip to log.
    * @return   void.
    */
    void setTripLoggingAsync(EDriveNextTripType eTripType) override;

    /**
    * @brief    getServiceScalingFactors: This function is to gets service scaling factor vlaues.
    * @param    void.
    * @return   void.
    */
    void getServiceScalingFactors() override;

    /**
    * @brief    getServiceScalingFactorsAsync: This function is to request service scaling factor vlaues.
    * @param    void.
    * @return   void.
    */
    void getServiceScalingFactorsAsync() override;

    /**
    * @brief    getScoreScalingFactor: This function is to get score scaling factor vlaue.
    * @param    void.
    * @return   double score scaling factor value.
    */
    double getScoreScalingFactor() override;

    /**
    * @brief    getTripLogging: This function is to get trip logging.
    * @param    void.
    * @return   EDriveNextTripType trip to log.
    */
    EDriveNextTripType getTripLogging() override;

    /**
    * @brief    setDpLogLevelAsync: This function is to set log level.
    * @param    EDriveNextLogLevel log level.
    * @return   void.
    */
    void setDpLogLevelAsync(EDriveNextLogLevel eLogLevel) override;

    /**
    * @brief    getDpLogLevel: This function is to get Log level.
    * @param    void.
    * @return   EDriveNextLogLevel log level.
    */
    EDriveNextLogLevel getDpLogLevel() override;

    /**
    * @brief    setDpLoggingTypeAsync: This function is to set logging type.
    * @param    EDriveNextLoggingType logging type.
    * @return   void.
    */
    void setDpLoggingTypeAsync(EDriveNextLoggingType eLoggingType) override;

    /**
    * @brief    getDpLoggingType: This function is to get logging type.
    * @param    void.
    * @return   EDriveNextLoggingType logging type.
    */
    EDriveNextLoggingType getDpLoggingType() override;

    /**
     * @brief getProxyAvailabilityStatus: method to get getProxy Availability Status
     * @param void
     * @return bool true when proxy availabile otherwise false
     */
    bool getProxyAvailabilityStatus() override;

    /**
     * @brief getDNConfigVersion: method to get DriveNext Config version
     * @param void
     * @return string DriveNext Config version
     */
    string getDNConfigVersion() override;

    /**
     * @brief getDNLibVersion: method to get DriveNext Lib version
     * @param void
     * @return string DriveNext Lib version
     */
    string getDNLibVersion()override;

    /**
     * @brief getDistanceUnitInfo: method to get DriveNext distance unit information
     * @param void
     * @return SDistanceUnitInfo distance unit information
     */
    SDistanceUnitInfo getDistanceUnitInfo() override;

    /**
     * @brief getFuelUnitInfo: method to get DriveNext fuel unit information
     * @param void
     * @return SFuelUnitInfo fuel unit information
     */
    SFuelUnitInfo getFuelUnitInfo() override;

    /**
     * @brief getScoreMaxRatingInfo: method to get DriveNext score max rating information
     * @param void
     * @return SSignalDataStructure score max rating information
     */
    SSignalDataStructure getScoreMaxRatingInfo() override;

private:

    /*****  CALL BACK METHODS  ****************************/

    /**
     * @brief driveNextProxyStatusCb: CallBack method to get notified about the availability status of DriveNext Proxy
     * @param eStatus: status of DriveNext proxy whether available or not
     * @return void
     */
    void driveNextProxyStatusCb(CommonAPI::AvailabilityStatus eStatus) override;

    /**
    * @brief    subscribeSignalsAsyncCb: This function gives callback status for subscribe signals.
    * @param    CommonAPI::CallStatus request status.
    * @param    driveProTypeCollection::eReturnStatus Method call return status.
    * @param    driveProTypeCollection::signalArray arrSignalList: list of signal types.
    * @return   void.
    */
    void subscribeSignalsAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus, driveProTypeCollection::signalArray arrSignalList) override;

    /**
    * @brief    unSubscribeSignalsAsyncCb: This function gives callback status for unSubscribe signals.
    * @param    CommonAPI::CallStatus request status.
    * @param    driveProTypeCollection::eReturnStatus Method call return status.
    * @param    driveProTypeCollection::signalArray arrSignalList: list of signal types.
    * @return   void.
    */
    void unSubscribeSignalsAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus, driveProTypeCollection::signalArray arrSignalList) override;

    /**
     * @brief driveNextResetAvailabilityStatusCb: CallBack method to get notified about the availability status of DriveNext Reset Option
     * @param bStatus: true when DriveNext Reset Option available otherwise false
     * @return void
     */
    void driveNextResetAvailabilityStatusCb(bool bStatus) override;

    /**
    * @brief    onTripResetRequestCb: This function is to get the Trip Reset request status Information.
    * @param    objTripResetStatus: Trip Reset request status Information.
    * @return   void.
    */
    void onTripResetRequestCb(driveProTypeCollection::sTripResetStatus objTripResetStatus) override;

    /**
    * @brief    onVersionInfoAttributeCb: This function is to get the Version Information.
    * @param    objVersionInfo: Version information.
    * @return   void.
    */
    void onVersionInfoAttributeCb(driveProTypeCollection::sDpVersionInfo objVersionInfo) override;

    /**
    * @brief    onResetAllOptionEnabledAttributeCb: This function is to get the boolean value whether the reset all option is enabled or not.
    * @param    bIsResetAllOptionEnabled: whether reset all option is enabled or not.
    * @return   void.
    */
    void onResetAllOptionEnabledAttributeCb(bool bIsResetAllOptionEnabled) override;

    /**
    * @brief    onEfficiencyInfoAttributeCb: This function is to get the effciency Information.
    * @param    effciencyInfo: efficiency information.
    * @return   void.
    */
    void onEfficiencyInfoAttributeCb(driveProTypeCollection::sEffciencyInfo objEffciencyInfo) override;

    /**
    * @brief    onDrivingInfoAttributeCb: This function is to get the Driving Information.
    * @param    objDrivingInfo: driving information.
    * @return   void.
    */
    void onDrivingInfoAttributeCb(driveProTypeCollection::sDrivingInfo objDrivingInfo) override;

    /**
    * @brief    onSafetyInfoAttributeCb: This function is to get the Safety Information.
    * @param    objSafetyInfo: safety information.
    * @return   void.
    */
    void onSafetyInfoAttributeCb(driveProTypeCollection::sSafetyInfo objSafetyInfo) override;

    /**
    * @brief    onDistUnitAttributeChanged: This function is to get the Distance Unit Information.
    * @param    objDistUnitInfo: distance unit information.
    * @return   void.
    */
    void onDistUnitAttributeChanged(driveProTypeCollection::sDistUnit objDistUnitInfo) override;

    /**
    * @brief    onFuelUnitAttributeChanged: This function is to get the Fuel Unit Information.
    * @param    objFuelUnitInfo: fuel unit information.
    * @return   void.
    */
    void onFuelUnitAttributeChanged(driveProTypeCollection::sFuelUnit objFuelUnitInfo) override;

    /**
    * @brief    resetTripAsyncCb: This function is to get resetTripAsync request status.
    * @param    CommonAPI::CallStatus request status
    * @param    driveProTypeCollection::eReturnStatus Method call return status
    * @param    driveProTypeCollection::eTripType requested trip type
    * @return   void.
    */
    void resetTripAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus, driveProTypeCollection::eTripType eTripType) override;

    /**
    * @brief    updateLibFileAsyncCb: This function is to get updateLibFileAsync request status.
    * @param    CommonAPI::CallStatus request status
    * @param    driveProTypeCollection::eReturnStatus Method call return status
    * @return   void.
    */
    void updateLibFileAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus) override;

    /**
    * @brief    updateConfigFileAsyncCb: This function is to get updateConfigFileAsync request status.
    * @param    CommonAPI::CallStatus request status
    * @param    driveProTypeCollection::eReturnStatus Method call return status
    * @return   void.
    */
    void updateConfigFileAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus) override;

    /**
    * @brief    extractDPLogsAsyncCb: This function is to get extractDPLogsAsync request status.
    * @param    CommonAPI::CallStatus request status
    * @param    driveProTypeCollection::eReturnStatus Method call return status
    * @return   void.
    */
    void extractDPLogsAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus) override;

    /**
    * @brief    getServiceScalingFactorsAsyncCb: This function is to get callback service scaling factor vlaue.
    * @param    CommonAPI::CallStatus request status
    * @param    double scaling factor value
    * @return   void.
    */
    void getServiceScalingFactorsAsyncCb(const CommonAPI::CallStatus &eStatus, const double &uiScalingFactor) override;

    /**
    * @brief    setTripLoggingAsyncCb: This function is to get setTripLoggingAsync request status.
    * @param    CommonAPI::CallStatus request status
    * @param    driveProTypeCollection::eReturnStatus Method call return status
    * @param    driveProTypeCollection::eTripType requested trip type
    * @return   void.
    */
    void setTripLoggingAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus, driveProTypeCollection::eTripType eTripType) override;

    /**
    * @brief    setDpLogLevelAsyncCb: This function is to get setDpLogLevelAsync request status.
    * @param    CommonAPI::CallStatus request status
    * @param    driveProTypeCollection::eReturnStatus Method call return status
    * @param    uint32_t requested log level value
    * @return   void.
    */
    void setDpLogLevelAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus, uint32_t uiLogLevel) override;

    /**
    * @brief    setDpLoggingTypeAsyncCb: This function is to get setDpLoggingTypeAsync request status.
    * @param    CommonAPI::CallStatus request status
    * @param    driveProTypeCollection::eReturnStatus Method call return status
    * @param    driveProTypeCollection::eLoggingType requested logging type
    * @return   void.
    */
    void setDpLoggingTypeAsyncCb(CommonAPI::CallStatus eStatus, driveProTypeCollection::eReturnStatus eReturnStatus, driveProTypeCollection::eLoggingType eLoggingType) override;

private:
    /*****  DriveNext Internal Methods  ****************************/

    /**
    * @brief    resetSignalDataMap: This function used to reset m_mapSignalValues
    * @param    void.
    * @return   void.
    */
    void resetSignalDataMap();

    /**
    * @brief    getServiceAttributeValues: This function used to get service attribute values
    * @param    void.
    * @return   void.
    */
    void getServiceAttributeValues();

    /**
    * @brief    subscribeDriveNextProxy: method to subscribe DriveNext Service.
    * @param    void.
    * @return   void.
    */
    void subscribeDriveNextProxy();

    /**
    * @brief    unSubscribeDriveNextProxy: method to un-subscribe DriveNext Service.
    * @param    void.
    * @return   void.
    */
    void unSubscribeDriveNextProxy();

    /**
    * @brief    CDriveNextResourceImpl: constructor for CDriveNextResourceImpl.
    * @param    void.
    * @return   NA.
    */
    CDriveNextResourceImpl();

private:
    /**
    * @brief ResourceFactory: Adding ResourceFactory class as friend class so that
    * ResourceFactory shall be able to create the instance of this class.
    */
    friend class ResourceFactory;

    /* Create an instance of the CDriveNextEventProvider to emit signals to the upper layer **/
    CDriveNextEventProvider* m_pEventProvider;

    /* DriveNextServiceProxy class object to call DriveNext proxy methods **/
    CAPIClientAbstraction<drivepropresProxy> m_objDriveNextProxy;

    /**
     * This variable holds the mapping of trip type and the efficeincy information
     */
    map<EDriveNextTripType, SEffciencyInfo> m_mapEffciencyInfo;

    /**
     * This variable holds the mapping of trip type and the driving information
     */
    map<EDriveNextTripType, SDrivingInfo> m_mapDrivingInfo;

    /**
     * This variable holds the mapping of trip type and the safety information
     */
    map<EDriveNextTripType, SSafetyInfo> m_mapSafetyInfo;

    /**
     * This variable holds the status of proxy availability
     */
    bool m_bProxyAvailability;

    /**
     * This variable holds the status of Reset Option availability
     */
    bool m_bResetAvailability;

    /**
     * This variable holds the values of version information
     */
    driveProTypeCollection::sDpVersionInfo m_objVersionInfo;

    /**
     * This variable holds the Score Scaling Factor value
     */
    double m_dScoreScalingFactor;

    /**
     * This variable holds the distance unit information
     */
    SDistanceUnitInfo m_objDistanceUnitInfo;

    /**
     * This variable holds the fuel unit information
     */
    SFuelUnitInfo m_objFuelUnitInfo;

    /**
     * This variable holds the score max rating value information
     */
    SSignalDataStructure m_objScoreMaxRating;

    /**
     * This variable holds the mapping of data and signal types
     */
    map<EDriveNextSignalTypes, SSignalDataStructure> m_mapSignalValues;
};

#endif // CDRIVENEXTRESOURCEIMPL_H
