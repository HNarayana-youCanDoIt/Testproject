/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDriveNextAdaptor.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDriveNextAdaptor, an Adaptor for DriveNext module,
 * CDriveNextAdaptor is class used to communicate with qml, resources of DriveNext module.
 */

#ifndef CDRIVENEXTADAPTOR_H
#define CDRIVENEXTADAPTOR_H

#include <QObject>
#include <QString>
#include "logging.h"
#include "CFramework.h"
#include "CDriveNextTripsModel.h"
#include "CDriveNextEnum.h"
#include "CDriveNextTripData.h"

//! @category FORWARD DECLERATIONS
class CDriveNextResourceImpl;

/**
 * @brief CDriveNextAdaptor, an Adaptor for DriveNext module,
 * It is class used to communicate with qml, resources of DriveNext module.
 */
class CDriveNextAdaptor : public QObject
{
    Q_OBJECT
    //________________________________________________________________________________________________
    // Properties //

    /* To get the DriveNext proxy presence status */
    Q_PROPERTY(bool driveNextPresence READ driveNextPresence NOTIFY sigDriveNextPresenceChanged)

    /* To get the DriveNext reset option presence status */
    Q_PROPERTY(bool driveNextResetPresence READ driveNextResetPresence NOTIFY sigDriveNextResetPresenceChanged)

    /* To get the DriveNext score proxy scale */
    Q_PROPERTY(double scoreProxyScale READ scoreProxyScale NOTIFY sigScoreProxyScaleChanged)

    /* To get the DriveNext lib file update process status */
    Q_PROPERTY(bool updatingLibFile READ updatingLibFile NOTIFY sigUpdatingLibFileChanged)

    /* To get the DriveNext config file update process status */
    Q_PROPERTY(bool updatingConfigFile READ updatingConfigFile NOTIFY sigUpdatingConfigFileChanged)

    /* To get the DriveNext exporting Logs process status */
    Q_PROPERTY(bool exportingLogs READ exportingLogs NOTIFY sigExportingLogsChanged)

    /* To get the DriveNext Lib Version */
    Q_PROPERTY(QString libVersion READ libVersion NOTIFY sigLibVersionChanged)

    /* To get the DriveNext Config Version */
    Q_PROPERTY(QString configVersion READ configVersion NOTIFY sigConfigVersionChanged)

    /* To get the DriveNext trip selected for logging */
    Q_PROPERTY(CDriveNextEnum::EDNTripType logTripType READ logTripType NOTIFY sigLogTripTypeChanged)

    /* To get the DriveNext trip selected for logging update process status */
    Q_PROPERTY(bool updatingLogTripType READ updatingLogTripType NOTIFY sigUpdatingLogTripTypeChanged)

    /* To get the DriveNext log level selected for logging */
    Q_PROPERTY(CDriveNextEnum::EDNLogLevel logLevel READ logLevel NOTIFY sigLogLevelChanged)

    /* To get the DriveNext log level update process status */
    Q_PROPERTY(bool updatingLogLevel READ updatingLogLevel NOTIFY sigUpdatingLogLevelChanged)

    /* To get the DriveNext log location selected for logging */
    Q_PROPERTY(CDriveNextEnum::EDNLoggingType loggingLocation READ loggingLocation NOTIFY sigLoggingLocationChanged)

    /* To get the DriveNext log location update process status */
    Q_PROPERTY(bool updatingLoggingLocation READ updatingLoggingLocation NOTIFY sigUpdatingLoggingLocationChanged)

    /* To get the DriveNext trip reset process status */
    Q_PROPERTY(bool resetTripStatus READ resetTripStatus NOTIFY sigResetTripStatusChanged)

    /* To get the selected DriveNext Trip index */
    Q_PROPERTY(int currentTripIndex READ currentTripIndex WRITE setCurrentTripIndex NOTIFY sigCurrentTripIndexChanged)

    /* To get the selected DriveNext Trip Performance index */
    Q_PROPERTY(int currentPerformanceIndex READ currentPerformanceIndex WRITE setCurrentPerformanceIndex NOTIFY sigCurrentPerformanceIndexChanged)

    /* To get the DriveNext Trips data */
    Q_PROPERTY(QList<QObject*> tripsData READ tripsData NOTIFY sigTripsDataChanged)

    /* To get the DriveNext signals data */
    Q_PROPERTY(QList<QObject*> signalsData READ signalsData NOTIFY sigSignalsDataChanged)

    /* To get the DriveNext trips model */
    Q_PROPERTY(QAbstractListModel* driveNextTripsModel READ driveNextTripsModel CONSTANT)
    //________________________________________________________________________________________________
public:
    /**
    * @brief	CDriveNextAdaptor::CDriveNextAdaptor constructor for class CDriveNextAdaptor.
    * @param	QObject.
    * @return	NA.
    **/
    CDriveNextAdaptor(QObject *parent = nullptr);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::~CDriveNextAdaptor is destructor of class CDriveNextAdaptor
    * @param	NA.
    * @return	NA.
    **/
    ~CDriveNextAdaptor();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::driveNextPresence is method to get value for "driveNextPresence" property.
    * @param	void.
    * @return	bool TRUE if drive next is present, FALSE otherwise.
    **/
    bool driveNextPresence();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::driveNextResetPresence is method to get value for "driveNextResetPresence" property.
    * @param	void.
    * @return	bool TRUE if drive next reset option is present, FALSE otherwise.
    **/
    bool driveNextResetPresence();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::scoreProxyScale is method to get value for "scoreProxyScale" property.
    * @param	void.
    * @return	double Score Scaling Factor.
    **/
    double scoreProxyScale();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::getDistanceUnitInfo is a method to get distance unit info.
    * @param	void.
    * @return	SDistanceUnitInfo distance unit info.
    **/
    SDistanceUnitInfo getDistanceUnitInfo();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::getFuelUnitInfo is a method to get fuel unit info.
    * @param	void.
    * @return	SFuelUnitInfo fuel unit info.
    **/
    SFuelUnitInfo getFuelUnitInfo();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::updatingLibFile is method to get value for "updatingLibFile" property.
    * @param	void.
    * @return	bool TRUE if config update is in progress, FALSE otherwise.
    **/
    bool updatingLibFile();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::updatingConfigFile is method to get value for "updatingConfigFile" property.
    * @param	void.
    * @return	bool TRUE if config update is in progress, FALSE otherwise.
    **/
    bool updatingConfigFile();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::exportingLogs is method to get value for "exportingLogs" property.
    * @param	void.
    * @return	bool TRUE if config update is in progress, FALSE otherwise.
    **/
    bool exportingLogs();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::libVersion is method to get value for "libVersion" property.
    * @param	void.
    * @return	QString current lib version.
    **/
    QString libVersion();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::configVersion is method to get value for "configVersion" property.
    * @param	void.
    * @return	QString current config version.
    **/
    QString configVersion();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::logTripType is method to get value for "logTripType" property.
    * @param	void.
    * @return	CDriveNextEnum::EDNTripType current Log Trip Type.
    **/
    CDriveNextEnum::EDNTripType logTripType();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::updatingLogTripType  is method to get value for "updatingLogTripType" property.
    * @param	void.
    * @return	bool true when updating LogTripType otherwise false.
    **/
    bool updatingLogTripType();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::logLevel is method to get value for "logLevel" property.
    * @param	void.
    * @return	CDriveNextEnum::EDNLogLevel current Log Level.
    **/
    CDriveNextEnum::EDNLogLevel logLevel();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::updatingLogLevel is method to get value for "updatingLogLevel" property.
    * @param	void.
    * @return	bool true when updating LogLevel otherwise false.
    **/
    bool updatingLogLevel();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::loggingLocation  is method to get value for "loggingLocation" property.
    * @param	void.
    * @return	CDriveNextEnum::EDNLoggingType current logging Location.
    **/
    CDriveNextEnum::EDNLoggingType loggingLocation();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::updatingLoggingLocation  is method to get value for "updatingLoggingLocation" property.
    * @param	void.
    * @return	bool true when updating LoggingLocation otherwise false.
    **/
    bool updatingLoggingLocation();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::resetTripStatus  is method to get value for "resetTripStatus" property.
    * @param	void.
    * @return	bool true when reseting trip otherwise false.
    **/
    bool resetTripStatus();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::currentTripIndex  is method to get value for "currentTripIndex" property.
    * @param	void.
    * @return	int current index selected from "tripsData" list.
    **/
    int currentTripIndex();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::currentTripType  is method gives current trip type.
    * @param	void.
    * @return	CDriveNextEnum::EDNTripType current type.
    **/
    CDriveNextEnum::EDNTripType currentTripType();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::currentPerformanceIndex  is method to get value for "currentPerformanceIndex" property.
    * @param	void.
    * @return	int current index selected from "Trip Performance Button".
    **/
    int currentPerformanceIndex();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::tripsData  is method to get value for "tripsData" property.
    * @param	void.
    * @return	list for CDriveNextTripData class.
    **/
    QList<QObject*> tripsData();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::signalsData  is method to get value for "signalsData" property.
    * @param	void.
    * @return	list for CDDriveNextDataElement class.
    **/
    QList<QObject*> signalsData();
    //________________________________________________________________________________________________
    /**
     * @brief dnMainScreenGeneralSignalsList: This function is to MainScreen General Signals list.
     * @param void
     * @return std::vector<EDriveNextSignalTypes> list for engg screen data
     */
    const std::vector<EDriveNextSignalTypes>& dnMainScreenGeneralSignalsList();
    //________________________________________________________________________________________________
    /**
     * @brief dnMainScreenCurrentTripSignalsList: This function is to MainScreen CurrentTrip Signal list.
     * @param void
     * @return std::vector<EDriveNextSignalTypes> list for engg screen data
     */
    const std::vector<EDriveNextSignalTypes>& dnMainScreenCurrentTripSignalsList();
    //________________________________________________________________________________________________
    /**
     * @brief dnMainScreenTripASignalsList: This function is to MainScreen TripA Signals list.
     * @param void
     * @return std::vector<EDriveNextSignalTypes> list for engg screen data
     */
    const std::vector<EDriveNextSignalTypes>& dnMainScreenTripASignalsList();
    //________________________________________________________________________________________________
    /**
     * @brief dnMainScreenTripBSignalsList: This function is to MainScreen TripB Signals list.
     * @param void
     * @return std::vector<EDriveNextSignalTypes> list for engg screen data
     */
    const std::vector<EDriveNextSignalTypes>& dnMainScreenTripBSignalsList();
    //________________________________________________________________________________________________
    /**
     * @brief dnMainScreenOverallTripSignalsList: This function is to MainScreen Overall Trip list.
     * @param void
     * @return std::vector<EDriveNextSignalTypes> list for engg screen data
     */
    const std::vector<EDriveNextSignalTypes>& dnMainScreenOverallTripSignalsList();
    //________________________________________________________________________________________________
    /**
     * @brief dnMainScreenBestTripSignalsList: This function is to MainScreen BestTrip Signals list.
     * @param void
     * @return std::vector<EDriveNextSignalTypes> list for engg screen data
     */
    const std::vector<EDriveNextSignalTypes>& dnMainScreenBestTripSignalsList();
    //________________________________________________________________________________________________
    /**
     * @brief dnMainScreenLastTripSignalsList: This function is to MainScreen LastTrip Signals list.
     * @param void
     * @return std::vector<EDriveNextSignalTypes> list for engg screen data
     */
    const std::vector<EDriveNextSignalTypes>& dnMainScreenLastTripSignalsList();
    //________________________________________________________________________________________________
    /**
     * @brief enggDataEfficiencyList: This function is to get engg data Efficiency list.
     * @param void
     * @return std::vector<EDriveNextSignalTypes> list for engg screen data
     */
    const std::vector<EDriveNextSignalTypes>& enggDataEfficiencyList();
    //________________________________________________________________________________________________
    /**
     * @brief enggDataBrakingList: This function is to get engg data Braking list.
     * @param void
     * @return std::vector<EDriveNextSignalTypes> list for engg screen data
     */
    const std::vector<EDriveNextSignalTypes>& enggDataBrakingList();
    //________________________________________________________________________________________________
    /**
     * @brief enggDataAccelerationList: This function is to get engg data Acceleration list.
     * @param void
     * @return std::vector<EDriveNextSignalTypes> list for engg screen data
     */
    const std::vector<EDriveNextSignalTypes>& enggDataAccelerationList();
    //________________________________________________________________________________________________
    /**
     * @brief enggDataGearShiftList: This function is to get engg data GearShift list.
     * @param void
     * @return std::vector<EDriveNextSignalTypes> list for engg screen data
     */
    const std::vector<EDriveNextSignalTypes>& enggDataGearShiftList();
    //________________________________________________________________________________________________
    /**
     * @brief enggDataGenericList: This function is to get engg data Generic list.
     * @param void
     * @return std::vector<EDriveNextSignalTypes> list for engg screen data
     */
    const std::vector<EDriveNextSignalTypes>& enggDataGenericList();
    //________________________________________________________________________________________________
    /**
     * @brief enggDataSafetyList: This function is to get engg data Safety list.
     * @param void
     * @return std::vector<EDriveNextSignalTypes> list for engg screen data
     */
    const std::vector<EDriveNextSignalTypes>& enggDataSafetyList();
    //________________________________________________________________________________________________
    /**
     * @brief driveNextTripsModel: This function is to get drive next trips model.
     * @param void
     * @return QAbstractListModel*
     */
    QAbstractListModel *driveNextTripsModel();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::onScalingFactorsChanged is a method to update DriveNext Scaling Factors.
    * @param	void.
    * @return	void.
    **/
    void onScalingFactorsChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::onDistanceUnitChanged is a method to update DriveNext distance unit info.
    * @param	void.
    * @return	void.
    **/
    void onDistanceUnitChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::onFuelUnitChanged is a method to update DriveNext fuel unit info.
    * @param	void.
    * @return	void.
    **/
    void onFuelUnitChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::onScoreMaxRatingUpdated is a method to update DriveNext score max rating info.
    * @param	void.
    * @return	void.
    **/
    void onScoreMaxRatingUpdated();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::onVersionUpdated is a method to update DriveNext version info.
    * @param	void.
    * @return	void.
    **/
    void onVersionUpdated();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::setDriveNextPresence is a method to update driveNextPresence value.
    * @param	bool TRUE if drive next is present, FALSE otherwise.
    * @return	void.
    **/
    void setDriveNextPresence(bool bValue);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::setDriveNextResetPresence is a method to set driveNextResetPresence value.
    * @param	bool TRUE if drive next reset option is present, FALSE otherwise.
    * @return	void.
    **/
    void setDriveNextResetPresence(bool bValue);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::updateDriveNextResetPresenceChanged is a method to update driveNextResetPresence value.
    * @param	void.
    * @return	void.
    **/
    void  updateDriveNextResetPresenceChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::setScoreScalingFactor is a method to update Score Scaling Factor value.
    * @param	double Score Scaling Factor.
    * @return	void.
    **/
    void setScoreScalingFactor(double dValue);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::setScoreProxyScale is a method to update scoreProxyScale value.
    * @param	double Score Proxy Scale.
    * @return	void.
    **/
    void setScoreProxyScale(double dValue);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::setDistanceUnitInfo is a method to update distance unit info.
    * @param	SDistanceUnitInfo distance unit info.
    * @return	void.
    **/
    void setDistanceUnitInfo(SDistanceUnitInfo info);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::setFuelUnitInfo is a method to update fuel unit info.
    * @param	SFuelUnitInfo fuel unit info.
    * @return	void.
    **/
    void setFuelUnitInfo(SFuelUnitInfo info);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::updateSignalValues is method to update signal values.
    * @param    QList<int> qlistUpdatedSignalTypes list of updated signal types
    * @return   void.
    **/
    void updateSignalValues(QList<int> qlistUpdatedSignalTypes);
    //________________________________________________________________________________________________
    /**
    * @brief    updateLibFileEnded method called by CDriveNextEventHandler
    * to handle UpdateLibFileAsync request call back
    * @param    bool is call successful.
    * @return   void.
    */
    void updateLibFileEnded(bool bStatus);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::setUpdatingLibFile is a method to change Lib file updating status.
    * @param	bool true when Lib update is in progress otherwise false
    * @return	void.
    **/
    void setUpdatingLibFile(bool bValue);
    //________________________________________________________________________________________________
    /**
    * @brief    updateConfigFileEnded method called by CDriveNextEventHandler
    * to handle UpdateConfigFileAsync request call back
    * @param    bool is call successful.
    * @return   void.
    */
    void updateConfigFileEnded(bool bStatus);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::setUpdatingConfigFile is a method to change Config File updating status.
    * @param	bool true when Config File update is in progress otherwise false
    * @return	void.
    **/
    void setUpdatingConfigFile(bool bValue);
    //________________________________________________________________________________________________
    /**
    * @brief    exportingLogsEnded method called by CDriveNextEventHandler
    * to handle extractDPLogsAsync request call back
    * @param    bool is call successful.
    * @return   void.
    */
    void exportingLogsEnded(bool bStatus);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::setExportingLogs is a method to change Exporting logs status.
    * @param	bool true when Exporting logs is in progress otherwise false
    * @return	void.
    **/
    void setExportingLogs(bool bValue);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::setLibVersion is a method to update Lib version value.
    * @param	QString updated Lib Version
    * @return	void.
    **/
    void setLibVersion(QString strLibVersion);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::setConfigVersion is a method to update Config version value.
    * @param	QString updated Config Version
    * @return	void.
    **/
    void setConfigVersion(QString strConfigVersion);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::setLogTripType is a method to update current trip type for Logging.
    * @param	CDriveNextEnum::EDNTripType current trip type for Logging.
    * @return	void.
    **/
    void setLogTripType(CDriveNextEnum::EDNTripType eValue);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::setUpdatingLogTripType is a method change Trip type for Logging updating status.
    * @param	bool true when trip type for Logging change in progress otherwise false
    * @return	void.
    **/
    void setUpdatingLogTripType(bool bValue);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::setLogLevel is a method to update current log level for Logging.
    * @param	CDriveNextEnum::EDNLogLevel current log level for Logging.
    * @return	void.
    **/
    void setLogLevel(CDriveNextEnum::EDNLogLevel eValue);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::setUpdatingLogLevel is a method change log level for Logging updating status.
    * @param	bool true when log level for Logging change in progress otherwise false
    * @return	void.
    **/
    void setUpdatingLogLevel(bool bValue);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::setLoggingLocation is a method to update current logging location.
    * @param	CDriveNextEnum::EDNLoggingType current logging location for Logging.
    * @return	void.
    **/
    void setLoggingLocation(CDriveNextEnum::EDNLoggingType eValue);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::setUpdatingLoggingLocation is a method change logging location updating status.
    * @param	bool true when logging location for Logging change in progress otherwise false
    * @return	void.
    **/
    void setUpdatingLoggingLocation(bool bValue);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::updateLibFile is a method start DriveNext Lib file update flow
    * @param	void.
    * @return	void.
    **/
    void updateLibFile();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::updateConfigFile is a method start DriveNext Configure file update flow
    * @param	void.
    * @return	void.
    **/
    void updateConfigFile();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::exportLogs is a method start DriveNext export log flow
    * @param	void.
    * @return	void.
    **/
    void exportLogs();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::updateLogTripType is a method to update Trip for logging
    * @param	CDriveNextEnum::EDNTripType new logging trip type.
    * @return	void.
    **/
    void updateLogTripType(CDriveNextEnum::EDNTripType eTripType);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::updateLogLevel is a method to update log level for logging
    * @param	CDriveNextEnum::EDNLogLevel new logging level type.
    * @return	void.
    **/
    void updateLogLevel(CDriveNextEnum::EDNLogLevel eLogLevel);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::updateLoggingLocation is a method to update log location for logging
    * @param	CDriveNextEnum::EDNLoggingType new logging location type.
    * @return	void.
    **/
    void updateLoggingLocation(CDriveNextEnum::EDNLoggingType eLoggingType);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::tryResetDriveNextTrip is a method to start reset trip flow,
    * It is Q_INVOKABLE to allow direct call from qml code.
    * @param	CDriveNextEnum::EDNTripType trip type to reset.
    * @return	void.
    **/
    Q_INVOKABLE void tryResetDriveNextTrip(CDriveNextEnum::EDNTripType eType);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::resetDriveNextTrip is a method to reset trip information,
    * It is Q_INVOKABLE to allow direct call from qml code.
    * @param	CDriveNextEnum::EDNTripType trip type to reset.
    * @return	void.
    **/
    Q_INVOKABLE void resetDriveNextTrip(CDriveNextEnum::EDNTripType eType);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::getScoreRange is a method to get score range,
    * It is Q_INVOKABLE to allow direct call from qml code.
    * @param	void.
    * @return	score range.
    **/
    Q_INVOKABLE double getScoreRange();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::setResetTripStatus is a method to set reseting trip status
    * @param	bool true when reseting trip otherwise false.
    * @return	void.
    **/
    void setResetTripStatus(bool bValue);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::resetTripEnded is a callback method to catch reset trip request result
    * @param	bool true when reset trip success otherwise false.
    * @param	CDriveNextEnum::EDNTripType trip type to reset.
    * @return	void.
    **/
    void resetTripEnded(bool bStatus, CDriveNextEnum::EDNTripType eType);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::setCurrentTripIndex is a method to update current selected trip index
    * @param	int current selected trip index
    * @return	void.
    **/
    void setCurrentTripIndex(int iIndex);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::setCurrentPerformanceIndex is a method to update current selected Performance Index
    * @param	int current selected trip index
    * @return	void.
    **/
    void setCurrentPerformanceIndex(int iIndex);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::subscribeDNMainScreenGeneralSignals is a method to subscribe MainScreen General signals.
    * @param	bool true for subscribe, false for unsubscribe signals list.
    * @return	void.
    **/
    void subscribeDNMainScreenGeneralSignals(bool bSubscribe);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::subscribeDNMainScreenCurrentTripSignals is a method to subscribe MainScreen CurrentTrip signals.
    * @param	bool true for subscribe, false for unsubscribe signals list.
    * @return	void.
    **/
    void subscribeDNMainScreenCurrentTripSignals(bool bSubscribe);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::subscribeDNMainScreenTripASignals is a method to subscribe MainScreen TripA signals.
    * @param	bool true for subscribe, false for unsubscribe signals list.
    * @return	void.
    **/
    void subscribeDNMainScreenTripASignals(bool bSubscribe);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::subscribeDNMainScreenTripBSignals is a method to subscribe MainScreen TripB signals.
    * @param	bool true for subscribe, false for unsubscribe signals list.
    * @return	void.
    **/
    void subscribeDNMainScreenTripBSignals(bool bSubscribe);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::subscribeDNMainScreenOverallTripSignals is a method to subscribe MainScreen OverallTrip signals.
    * @param	bool true for subscribe, false for unsubscribe signals list.
    * @return	void.
    **/
    void subscribeDNMainScreenOverallTripSignals(bool bSubscribe);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::subscribeDNMainScreenBestTripSignals is a method to subscribe MainScreen BestTrip signals.
    * @param	bool true for subscribe, false for unsubscribe signals list.
    * @return	void.
    **/
    void subscribeDNMainScreenBestTripSignals(bool bSubscribe);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::subscribeDNMainScreenLastTripSignals is a method to subscribe MainScreen LastTrip signals.
    * @param	bool true for subscribe, false for unsubscribe signals list.
    * @return	void.
    **/
    void subscribeDNMainScreenLastTripSignals(bool bSubscribe);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::subscribeEnggEfficiencyList is a method to subscribe engg Efficiency signals.
    * @param	bool true for subscribe, false for unsubscribe signals list.
    * @return	void.
    **/
    void subscribeEnggEfficiencyList(bool bSubscribe);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::subscribeEnggBrakingList is a method to subscribe engg Braking signals.
    * @param	bool true for subscribe, false for unsubscribe signals list.
    * @return	void.
    **/
    void subscribeEnggBrakingList(bool bSubscribe);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::subscribeEnggAccelerationList is a method to subscribe engg Acceleration signals.
    * @param	bool true for subscribe, false for unsubscribe signals list.
    * @return	void.
    **/
    void subscribeEnggAccelerationList(bool bSubscribe);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::subscribeEnggGearShiftList is a method to subscribe engg GearShift signals.
    * @param	bool true for subscribe, false for unsubscribe signals list.
    * @return	void.
    **/
    void subscribeEnggGearShiftList(bool bSubscribe);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::subscribeEnggGenericList is a method to subscribe engg Generic signals.
    * @param	bool true for subscribe, false for unsubscribe signals list.
    * @return	void.
    **/
    void subscribeEnggGenericList(bool bSubscribe);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::subscribeEnggSafetyList is a method to subscribe engg Safety signals.
    * @param	bool true for subscribe, false for unsubscribe signals list.
    * @return	void.
    **/
    void subscribeEnggSafetyList(bool bSubscribe);
signals:
    /**
    * @brief	CDriveNextAdaptor::sigDriveNextPresenceChanged is QML signal for "driveNextPresence" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigDriveNextPresenceChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::sigDriveNextResetPresenceChanged is QML signal for "driveNextResetPresence" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigDriveNextResetPresenceChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::sigScoreProxyScaleChanged is QML signal for "scoreProxyScale" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigScoreProxyScaleChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::sigUpdatingLibFileChanged is QML signal for "updatingLibFile" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigUpdatingLibFileChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::sigUpdatingConfigFileChanged is QML signal for "updatingConfigFile" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigUpdatingConfigFileChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::sigExportingLogsChanged is QML signal for "exportingLogs" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigExportingLogsChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::sigLibVersionChanged is QML signal for "libVersion" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigLibVersionChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::sigConfigVersionChanged is QML signal for "configVersion" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigConfigVersionChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::sigLogTripTypeChanged is QML signal for "logTripType" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigLogTripTypeChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::sigUpdatingLogTripTypeChanged is QML signal for "updatingLogTripType" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigUpdatingLogTripTypeChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::sigLogLevelChanged is QML signal for "logLevel" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigLogLevelChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::sigUpdatingLogLevelChanged is QML signal for "updatingLogLevel" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigUpdatingLogLevelChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::sigLoggingLocationChanged is QML signal for "loggingLocation" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigLoggingLocationChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::sigUpdatingLoggingLocationChanged is QML signal for "updatingLoggingLocation" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigUpdatingLoggingLocationChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::sigUpdatingLoggingLocationChanged is QML signal for "resetTripStatus" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigResetTripStatusChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::sigCurrentTripIndexChanged is QML signal for "currentTripIndex" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigCurrentTripIndexChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::sigCurrentTripIndexChanged is QML signal for "currentPerformanceIndex" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigCurrentPerformanceIndexChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::sigTripsDataChanged is QML signal for "tripsData" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigTripsDataChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::sigSignalsDataChanged is QML signal for "signalsData" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigSignalsDataChanged();
    //________________________________________________________________________________________________
public slots:

    /**
     * @brief   sltPowerModeChanged: is slot for power mode status change
     * @param   void
     * @return  void
     */
    void sltPowerModeChanged();
    //________________________________________________________________________________________________
private:

    /**
    * @brief	CDriveNextAdaptor::validateDriveNextSignalTypes method to validate proxy signal types with HMI signals.
    * @param	void.
    * @return	bool true when all proxy signal types match with HMI signals.
    **/
    bool validateDriveNextSignalTypes();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::initDriveNextTripsData is function to init trips list.
    * @param	void.
    * @return	void.
    **/
    void initDriveNextTripsData();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::resetDriveNextTripsData is function to reset trips list.
    * @param	void.
    * @return	void.
    **/
    void resetDriveNextTripsData();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::initDriveNextSignalsData is function to init signals data list.
    * @param	void.
    * @return	void.
    **/
    void initDriveNextSignalsData();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::resetDriveNextSignalsData is function to reset signals data list.
    * @param	void.
    * @return	void.
    **/
    void resetDriveNextSignalsData();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::initDriveNextData is function to init DriveNext data list.
    * @param	void.
    * @return	void.
    **/
    void initDriveNextData();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::resetDriveNextData is function to reset DriveNext data list.
    * @param	void.
    * @return	void.
    **/
    void resetDriveNextData();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::initVectDNMainScreenGeneralSignals is function to init DN MainScreen General Signals.
    * @param	void.
    * @return	void.
    **/
    void initVectDNMainScreenGeneralSignals();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::initVectDNMainScreenCurrentTripSignals is function to init DN MainScreen CurrentTrip Signals.
    * @param	void.
    * @return	void.
    **/
    void initVectDNMainScreenCurrentTripSignals();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::initVectDNMainScreenTripASignals is function to init DN MainScreen TripA Signals.
    * @param	void.
    * @return	void.
    **/
    void initVectDNMainScreenTripASignals();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::initVectDNMainScreenTripBSignals is function to init DN MainScreen TripB Signals.
    * @param	void.
    * @return	void.
    **/
    void initVectDNMainScreenTripBSignals();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::initVectDNMainScreenOverallTripSignals is function to init DN MainScreen OverallTrip Signals.
    * @param	void.
    * @return	void.
    **/
    void initVectDNMainScreenOverallTripSignals();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::initVectDNMainScreenBestTripSignals is function to init DN MainScreen BestTrip Signals.
    * @param	void.
    * @return	void.
    **/
    void initVectDNMainScreenBestTripSignals();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::initVectDNMainScreenLastTripSignals is function to init DN MainScreen LastTrip Signals.
    * @param	void.
    * @return	void.
    **/
    void initVectDNMainScreenLastTripSignals();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::initVectEnggDataEfficiencySignals is function to init EnggData Efficiency Signals.
    * @param	void.
    * @return	void.
    **/
    void initVectEnggDataEfficiencySignals();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::initVectDNMainScreenGeneralSignals is function to init DN MainScreen General Signals.
    * @param	void.
    * @return	void.
    **/
    void initVectEnggDataBrakingSignals();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::initVectEnggDataAccelerationSignals is function to init EnggData Acceleration Signals.
    * @param	void.
    * @return	void.
    **/
    void initVectEnggDataAccelerationSignals();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::initVectEnggDataGearShiftSignals is function to init EnggData GearShift Signals.
    * @param	void.
    * @return	void.
    **/
    void initVectEnggDataGearShiftSignals();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::initVectEnggDataGenericSignals is function to init EnggData Generic Signals.
    * @param	void.
    * @return	void.
    **/
    void initVectEnggDataGenericSignals();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::initVectEnggDataSafetySignals is function to init EnggData Safety Signals.
    * @param	void.
    * @return	void.
    **/
    void initVectEnggDataSafetySignals();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::initDriveNextProperties is function to init all Q properties with latest values.
    * @param	void.
    * @return	void.
    **/
    void initDriveNextProperties();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextAdaptor::setValueToSignals is method to set value to signal list in required format.
    * @param	EDriveNextSignalTypes signal type to update.
    * @param	SSignalDataStructure signal data to update.
    * @return	void.
    **/
    void setValueToSignals( EDriveNextSignalTypes eSignalType, SSignalDataStructure signalData);
    //________________________________________________________________________________________________

private:

    /*!
     * @brief m_bDriveNextPresence : Variable to hold value for "driveNextPresence" property
     */
    bool m_bDriveNextPresence;

    /*!
     * @brief m_bDriveNextResetPresence : Variable to hold value for "driveNextResetPresence" property
     */
    bool m_bDriveNextResetPresence;

    /*!
     * @brief m_dScoreScalingFactor : Variable to hold value for Score Scaling Factor
     */
    double m_dScoreScalingFactor;

    /*!
     * @brief m_dScoreProxyScale : Variable to hold value for "scoreProxyScale" property
     */
    double m_dScoreProxyScale;

    /*!
     * @brief m_objDistanceUnitInfo : Variable to hold distance unit information
     */
    SDistanceUnitInfo m_objDistanceUnitInfo;

    /*!
     * @brief m_objFuelUnitInfo : Variable to hold fuel unit information
     */
    SFuelUnitInfo m_objFuelUnitInfo;

    /*!
     * @brief m_pDriveNextTripsModel : Pointer of CDriveNextTripsModel class.
     */
    CDriveNextTripsModel* m_pDriveNextTripsModel;

    /*!
     * @brief m_bUpdatingLibgFile : Variable to hold lib file updating status.
     */
    bool m_bUpdatingLibgFile;

    /*!
     * @brief m_bUpdatingConfigFile : Variable to hold config file updating status.
     */
    bool m_bUpdatingConfigFile;

    /*!
     * @brief m_bExportingLogs : Variable to hold exporting logs status.
     */
    bool m_bExportingLogs;

    /*!
     * @brief m_strLibVersion : Variable to hold Lib file version.
     */
    QString m_strLibVersion;

    /*!
     * @brief m_strConfigVersion : Variable to hold config file version.
     */
    QString m_strConfigVersion;

    /*!
     * @brief m_eDpLoggingLevel : Variable to hold current log level.
     */
    CDriveNextEnum::EDNLogLevel m_eDpLoggingLevel;

    /*!
     * @brief m_eDpLoggingType : Variable to hold current logging type.
     */
    CDriveNextEnum::EDNLoggingType m_eDpLoggingType;

    /*!
     * @brief m_eDpLoggingTrip : Variable to hold current log trip type.
     */
    CDriveNextEnum::EDNTripType m_eDpLoggingTrip;

    /*!
     * @brief m_bUpdatingDpLoggingLevel : Variable to hold Updating log level status.
     */
    bool m_bUpdatingDpLoggingLevel;

    /*!
     * @brief m_bUpdatingDpLoggingType : Variable to hold Updating logging type status.
     */
    bool m_bUpdatingDpLoggingType;

    /*!
     * @brief m_bUpdatingDpLoggingTrip : Variable to hold Updating log trip type status.
     */
    bool m_bUpdatingDpLoggingTrip;

    /*!
     * @brief m_bResetTripStatus : Variable to hold reseting trip status.
     */
    bool m_bResetTripStatus;

    /*!
     * @brief m_iCurrentTripIndex : Variable to hold current index selected from trips list.
     */
    int m_iCurrentTripIndex;

    /*!
     * @brief m_iCurrentPerformanceIndex : Variable to hold current index selected from performance breakup buttons.
     */
    int m_iCurrentPerformanceIndex;

    /*!
     * @brief m_lTripsData : list CDriveNextTripData class to hold different trips data.
     */
    QList<QObject*>  m_lTripsData;

    /*!
     * @brief m_lSignalsData : list of CDDriveNextDataElement class to hold different signals data.
     */
    QList<QObject*>  m_lSignalsData;

    /*!
     * @brief m_vectDNMainScreenGeneralSignals : vector to hold list of DN MainScreen General signals.
     */
    std::vector<EDriveNextSignalTypes> m_vectDNMainScreenGeneralSignals;

    /*!
     * @brief m_vectDNMainScreenGeneralSignals : vector to hold list of DN MainScreen Current Trip signals.
     */
    std::vector<EDriveNextSignalTypes> m_vectDNMainScreenCurrentTripSignals;

    /*!
     * @brief m_vectDNMainScreenGeneralSignals : vector to hold list of DN MainScreen Trip A signals.
     */
    std::vector<EDriveNextSignalTypes> m_vectDNMainScreenTripASignals;

    /*!
     * @brief m_vectDNMainScreenGeneralSignals : vector to hold list of DN MainScreen Trip B signals.
     */
    std::vector<EDriveNextSignalTypes> m_vectDNMainScreenTripBSignals;

    /*!
     * @brief m_vectDNMainScreenGeneralSignals : vector to hold list of DN MainScreen Overall Trip signals.
     */
    std::vector<EDriveNextSignalTypes> m_vectDNMainScreenOverallTripSignals;

    /*!
     * @brief m_vectDNMainScreenGeneralSignals : vector to hold list of DN MainScreen Best Trip signals.
     */
    std::vector<EDriveNextSignalTypes> m_vectDNMainScreenBestTripSignals;

    /*!
     * @brief m_vectDNMainScreenGeneralSignals : vector to hold list of DN MainScreen LastTrip signals.
     */
    std::vector<EDriveNextSignalTypes> m_vectDNMainScreenLastTripSignals;

    /*!
     * @brief m_vectEnggDataEfficiencySignals : vector to hold list of engg data Efficiency signals.
     */
    std::vector<EDriveNextSignalTypes> m_vectEnggDataEfficiencySignals;

    /*!
     * @brief m_vectEnggDataBrakingSignals : vector to hold list of engg data Braking signals.
     */
    std::vector<EDriveNextSignalTypes> m_vectEnggDataBrakingSignals;

    /*!
     * @brief m_vectEnggDataAccelerationSignals : vector to hold list of engg data Acceleration signals.
     */
    std::vector<EDriveNextSignalTypes> m_vectEnggDataAccelerationSignals;

    /*!
     * @brief m_vectEnggDataGearShiftSignals : vector to hold list of engg data GearShift signals.
     */
    std::vector<EDriveNextSignalTypes> m_vectEnggDataGearShiftSignals;

    /*!
     * @brief m_vectEnggDataGenericSignals : vector to hold list of engg data Generic signals.
     */
    std::vector<EDriveNextSignalTypes> m_vectEnggDataGenericSignals;

    /*!
     * @brief m_vectEnggDataSafetySignals : vector to hold list of engg data Safety signals.
     */
    std::vector<EDriveNextSignalTypes> m_vectEnggDataSafetySignals;

    /*!
     * @brief m_pDriveNextResource : Pointer of CDriveNextResourceImpl class to communicate with
     * DriveNext resource layer.
     */
    CDriveNextResourceImpl* m_pDriveNextResource;
};
#endif // CDRIVENEXTADAPTOR_H
