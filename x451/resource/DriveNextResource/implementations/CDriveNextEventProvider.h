/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CDriveNextEventProvider.h
 * @ingroup       HMIComponent
 * @author        Nandkishor Lokhande
 * CDriveNextEventProvider, This class propagates service signals to application layer.
 */

#ifndef CDRIVENEXTEVENTPROVIDER_H
#define CDRIVENEXTEVENTPROVIDER_H

#include <QObject>
#include <string>
using namespace std;

#include "CDriveNextResourceData.h"

/*!
 * @class   CDriveNextEventProvider
 * @brief   This class provides signals to catch service events
 *          which can be used by application layer.
 */
class CDriveNextEventProvider : public QObject
{
    Q_OBJECT

public:

    /**
    * @brief    constructor for CDriveNextEventProvider.
    * @param    QObject pointer to link object with creator object.
    * @return   NA.
    */
    CDriveNextEventProvider(QObject* pParent = 0);

    /**
    * @brief    destructor for CDriveNextEventProvider.
    * @param    NA.
    * @return   NA.
    */
    ~CDriveNextEventProvider();

public:
    /*
     * Methods to call from service resource implementation class to propogate events to above layer
     */

    /**
    * @brief    onProxyStatusChanged method gets call from service resource implementation class
    * when DriveNext Proxy Status Changes
    * @param    bool true when DriveNext Proxy available otherwise false
    * @return   void.
    */
    void onProxyStatusChanged(bool bAvailable);

    /**
    * @brief    onResetAvailabilityStatusChanged method gets call from service resource implementation class
    * when DriveNext Reset Option Availability Status Changes
    * @param    bool true when DriveNext Reset Option available otherwise false
    * @return   void.
    */
    void onResetAvailabilityStatusChanged(bool bAvailable);

    /**
    * @brief    onSignalValuesUpdated method gets call from service resource implementation class
    * when DriveNext signal values gets updated
    * @param    list<int> listUpdatedSignalTypes list of updated signal types
    * @return   void.
    */
    void onSignalValuesUpdated(list<int> listUpdatedSignalTypes);

    /**
    * @brief    onScoreMaxRatingUpdated method gets call from service resource implementation class
    * when DriveNext score max rating values gets updated
    * @param    void.
    * @return   void.
    */
    void onScoreMaxRatingUpdated();

    /**
    * @brief    onVersionInfoChanged method gets call from service resource implementation class
    * when DriveNext Version info Changes
    * @param    void.
    * @return   void.
    */
    void onVersionInfoChanged();

    /**
    * @brief    onResetTripAsyncCb method gets call from service resource implementation class
    * when ResetTripAsync request call back hits
    * @param    bool is call successful.
    * @param    EDriveNextTripType reseted trip type.
    * @return   void.
    */
    void onResetTripAsyncCb(bool bStatus, EDriveNextTripType eTripType);

    /**
    * @brief    onUpdateConfigFileAsyncCb method gets call from service resource implementation class
    * when UpdateConfigFileAsync request call back hits
    * @param    bool is call successful.
    * @return   void.
    */
    void onUpdateConfigFileAsyncCb(bool bStatus);

    /**
    * @brief    onUpdateLibFileAsyncCb method gets call from service resource implementation class
    * when UpdateLibFileAsync request call back hits
    * @param    bool is call successful.
    * @return   void.
    */
    void onUpdateLibFileAsyncCb(bool bStatus);

    /**
    * @brief    onExtractDPLogsAsyncCb method gets call from service resource implementation class
    * when ExtractDPLogsAsync request call back hits
    * @param    bool is call successful.
    * @return   void.
    */
    void onExtractDPLogsAsyncCb(bool bStatus);

    /**
    * @brief    onScalingFactorsChanged method gets call from service resource implementation class
    * when Scaling Factor value changes
    * @param    void.
    * @return   void.
    */
    void onScalingFactorsChanged();

    /**
    * @brief    onSetTripLoggingAsyncCb method gets call from service resource implementation class
    * when SetTripLoggingAsync request call back hits
    * @param    bool is call successful.
    * @param    EDriveNextTripType updated trip type for logging
    * @return   void.
    */
    void onSetTripLoggingAsyncCb(bool bStatus, EDriveNextTripType eTripType);

    /**
    * @brief    onTripLoggingChanged method gets call from service resource implementation class
    * when TripLogging value gets change
    * @param    EDriveNextTripType updated trip type for logging
    * @return   void.
    */
    void onTripLoggingChanged(EDriveNextTripType eTripType);

    /**
    * @brief    onSetDpLogLevelAsyncCb method gets call from service resource implementation class
    * when SetDpLogLevelAsync request call back hits
    * @param    bool is call successful.
    * @param    EDriveNextLogLevel updated log level for logging
    * @return   void.
    */
    void onSetDpLogLevelAsyncCb(bool bStatus, EDriveNextLogLevel eLogLevel);

    /**
    * @brief    onDpLogLevelChanged method gets call from service resource implementation class
    * when DpLogLevel value gets change
    * @param    EDriveNextLogLevel updated log level for logging
    * @return   void.
    */
    void onDpLogLevelChanged(EDriveNextLogLevel eLogLevel);

    /**
    * @brief    onSetDpLoggingTypeAsyncCb method gets call from service resource implementation class
    * when SetDpLoggingType request call back hits
    * @param    bool is call successful.
    * @param    EDriveNextLoggingType updated logging location for logging
    * @return   void.
    */
    void onSetDpLoggingTypeAsyncCb(bool bStatus, EDriveNextLoggingType eLoggingType);

    /**
    * @brief    onDpLoggingTypeChanged method gets call from service resource implementation class
    * when DpLoggingType value gets change
    * @param    EDriveNextLoggingType updated logging location for logging
    * @return   void.
    */
    void onDpLoggingTypeChanged(EDriveNextLoggingType eLoggingType);

    /**
    * @brief    onDistanceUnitInfoChanged method gets call from service resource implementation class
    * when dinstance unit information gets change
    * @param    void.
    * @return   void.
    */
    void onDistanceUnitInfoChanged();

    /**
    * @brief    onFuelUnitInfoChanged method gets call from service resource implementation class
    * when fuel unit information gets change
    * @param    void.
    * @return   void.
    */
    void onFuelUnitInfoChanged();

signals:
    /*
     * Signals to listen by HMI module to handle respective events
     */

    /**
    * @brief    sigProxyStatusChanged signal listen by HMI modules
    * to handle Proxy availability status
    * @param    bool true when DriveNext Proxy available otherwise false
    * @return   void.
    */
    void sigProxyStatusChanged(bool bAvailable);

    /**
    * @brief    sigResetAvailabilityStatusChanged signal listen by HMI modules
    * to handle Reset option availability status
    * @param    void.
    * @return   void.
    */
    void sigResetAvailabilityStatusChanged();

    /**
    * @brief    sigSignalValuesChanged signal listen by HMI modules
    * to handle updated signal values
    * @param    QList<int> qlistUpdatedSignalTypes list of Updated Signal types
    * @return   void.
    */
    void sigSignalValuesChanged(QList<int> qlistUpdatedSignalTypes);

    /**
    * @brief    sigScoreMaxRatingUpdated signal listen by HMI modules
    * to handle updated score max rating info
    * @param    void.
    * @return   void.
    */
    void sigScoreMaxRatingUpdated();

    /**
    * @brief    sigVersionUpdated signal listen by HMI modules
    * to handle changes in version info
    * @param    void.
    * @return   void.
    */
    void sigVersionUpdated();

    /**
    * @brief    sigResetTripAsyncCb signal listen by HMI modules
    * to handle ResetTripAsync request call back
    * @param    bool is call successful.
    * @param    int EDriveNextTripType reseted trip type.
    * @return   void.
    */
    void sigResetTripAsyncCb(bool bStatus, int iTripType);

    /**
    * @brief    sigUpdateConfigFileAsyncCb signal listen by HMI modules
    * to handle UpdateConfigFileAsync request call back
    * @param    bool is call successful.
    * @return   void.
    */
    void sigUpdateConfigFileAsyncCb(bool bStatus);

    /**
    * @brief    sigUpdateLibFileAsyncCb signal listen by HMI modules
    * to handle UpdateLibFileAsync request call back
    * @param    bool is call successful.
    * @return   void.
    */
    void sigUpdateLibFileAsyncCb(bool bStatus);

    /**
    * @brief    sigExtractDPLogsAsyncCb signal listen by HMI modules
    * to handle ExtractDPLogsAsync request call back
    * @param    bool is call successful.
    * @return   void.
    */
    void sigExtractDPLogsAsyncCb(bool bStatus);

    /**
    * @brief    sigScalingFactorsChanged signal listen by HMI modules
    * to handle score scaling favtor value
    * @param    void.
    * @return   void.
    */
    void sigScalingFactorsChanged();

    /**
    * @brief    sigSetTripLoggingAsyncCb signal listen by HMI modules
    * to handle SetTripLoggingAsync request call back
    * @param    bool is call successful.
    * @param    int EDriveNextTripType updated trip type for logging
    * @return   void.
    */
    void sigSetTripLoggingAsyncCb(bool bStatus, int iTripType);

    /**
    * @brief    sigTripLoggingChanged signal listen by HMI modules
    * to handle TripLogging value change
    * @param    int EDriveNextTripType updated trip type for logging
    * @return   void.
    */
    void sigTripLoggingChanged(int iTripType);

    /**
    * @brief    sigSetDpLogLevelAsyncCb signal listen by HMI modules
    * to handle SetDpLogLevelAsync request call back
    * @param    bool is call successful.
    * @param    int EDriveNextLogLevel updated log level for logging
    * @return   void.
    */
    void sigSetDpLogLevelAsyncCb(bool bStatus, int iLogLevel);

    /**
    * @brief    sigDpLogLevelChanged signal listen by HMI modules
    * to handle DpLogLevel value change
    * @param    int EDriveNextLogLevel updated log level for logging
    * @return   void.
    */
    void sigDpLogLevelChanged(int iLogLevel);

    /**
    * @brief    sigSetDpLoggingTypeAsyncCb signal listen by HMI modules
    * to handle SetDpLoggingType request call back
    * @param    bool is call successful.
    * @param    int EDriveNextLoggingType updated logging location for logging
    * @return   void.
    */
    void sigSetDpLoggingTypeAsyncCb(bool bStatus, int iLoggingType);

    /**
    * @brief    sigDpLoggingTypeChanged signal listen by HMI modules
    * to handle DpLoggingType value change
    * @param    int EDriveNextLoggingType updated logging location for logging
    * @return   void.
    */
    void sigDpLoggingTypeChanged(int iLoggingType);

    /**
    * @brief    sigDistanceUnitInfoChanged signal listen by HMI modules
    * to handle distance unit information change
    * @param    void.
    * @return   void.
    */
    void sigDistanceUnitInfoChanged();

    /**
    * @brief    sigFuelUnitInfoChanged signal listen by HMI modules
    * to handle fuel unit information change
    * @param    void.
    * @return   void.
    */
    void sigFuelUnitInfoChanged();
};

#endif // CDRIVENEXTEVENTPROVIDER_H
