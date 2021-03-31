/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDriveNextEventHandler.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDriveNextEventHandler, a Resource handler for DriveNext module,
 * CDriveNextEventHandler act as mediator between adaptor and resource manager.
 * The class listens for the signals raised by the resource layer provider class.
 * It has the implementation of the corresponding slots.
 */

#ifndef CDRIVENEXTEVENTHANDLER_H
#define CDRIVENEXTEVENTHANDLER_H

#include <QObject>

/**
 * @brief CDriveNextEventHandler, a Resource handler for DriveNext module,
 * It act as mediator between adaptor and resource manager,
 * This listens signals raised by the resource layer provider class,
 * It has the implementation of the corresponding slots.
 */
class CDriveNextEventHandler: public QObject
{
    Q_OBJECT
public:
    /**
    * @brief	CDriveNextEventHandler::CDriveNextEventHandler constructor for data handler class CDriveNextEventHandler.
    * @param	QObject.
    * @return	NA.
    **/
    CDriveNextEventHandler(QObject* parent = 0);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextEventHandler::~CDriveNextEventHandler is destructor of data handler class CDriveNextEventHandler
    * @param	NA.
    * @return	NA.
    **/
    ~CDriveNextEventHandler();
    //________________________________________________________________________________________________
public slots:

    /**
    * @brief    slotProxyStatusChanged slot catch by HMI module
    * to handle Proxy availability status
    * @param    bool true when DriveNext Proxy available otherwise false
    * @return   void.
    */
    void slotProxyStatusChanged(bool bStatus);

    /**
    * @brief    slotScalingFactorsChanged slot catch by HMI module
    * to handle change in Scaling Factors
    * @param    void.
    * @return   void.
    */
    void slotScalingFactorsChanged();

    /**
    * @brief    slotDistanceUnitInfoChanged slot catch by HMI module
    * to handle change in distance unit information
    * @param    void.
    * @return   void.
    */
    void slotDistanceUnitInfoChanged();

    /**
    * @brief    slotFuelUnitInfoChanged slot catch by HMI module
    * to handle change in fuel unit information
    * @param    void.
    * @return   void.
    */
    void slotFuelUnitInfoChanged();

    /**
    * @brief    slotResetAvailabilityStatusChanged slot catch by HMI module
    * to handle Reset Option availability status
    * @param    void.
    * @return   void.
    */
    void slotResetAvailabilityStatusChanged();

    /**
    * @brief    slotSignalValuesChanged slot catch by HMI module
    * to handle updated signal values
    * @param    QList<int> qlistUpdatedSignalTypes list of updated signal types
    * @return   void.
    */
    void slotSignalValuesChanged(QList<int> qlistUpdatedSignalTypes);

    /**
    * @brief    slotScoreMaxRatingUpdated slot catch by HMI module
    * to handle changes in score max rating info
    * @param    void.
    * @return   void.
    */
    void slotScoreMaxRatingUpdated();

    /**
    * @brief    slotVersionUpdated slot catch by HMI module
    * to handle changes in version info
    * @param    void.
    * @return   void.
    */
    void slotVersionUpdated();

    /**
    * @brief    slotResetTripAsyncCb slot catch by HMI module
    * to handle ResetTripAsync request call back
    * @param    bool is call successful.
    * @param    int EDriveNextTripType reseted trip type.
    * @return   void.
    */
    void slotResetTripAsyncCb(bool bStatus, int iTripType);

    /**
    * @brief    slotUpdateLibFileAsyncCb slot catch by HMI module
    * to handle UpdateLibFileAsync request call back
    * @param    bool is call successful.
    * @return   void.
    */
    void slotUpdateLibFileAsyncCb(bool bStatus);

    /**
    * @brief    slotUpdateConfigFileAsyncCb slot catch by HMI module
    * to handle UpdateConfigFileAsync request call back
    * @param    bool is call successful.
    * @return   void.
    */
    void slotUpdateConfigFileAsyncCb(bool bStatus);

    /**
    * @brief    slotExtractDPLogsAsyncCb slot catch by HMI module
    * to handle ExtractDPLogsAsync request call back
    * @param    bool is call successful.
    * @return   void.
    */
    void slotExtractDPLogsAsyncCb(bool bStatus);

    /**
    * @brief    slotSetTripLoggingAsyncCb slot catch by HMI module
    * to handle SetTripLoggingAsync request call back
    * @param    bool is call successful.
    * @param    int EDriveNextTripType updated trip type for logging
    * @return   void.
    */
    void slotSetTripLoggingAsyncCb(bool bStatus, int iTripType);

    /**
    * @brief    slotTripLoggingChanged slot catch by HMI module
    * to handle TripLogging value change
    * @param    int EDriveNextTripType updated trip type for logging
    * @return   void.
    */
    void slotTripLoggingChanged(int iTripType);

    /**
    * @brief    slotSetDpLogLevelAsyncCb slot catch by HMI module
    * to handle SetDpLogLevelAsync request call back
    * @param    bool is call successful.
    * @param    int EDriveNextLogLevel updated log level for logging
    * @return   void.
    */
    void slotSetDpLogLevelAsyncCb(bool bStatus, int iLogLevel);

    /**
    * @brief    slotDpLogLevelChanged slot catch by HMI module
    * to handle DpLogLevel value change
    * @param    int EDriveNextLogLevel updated log level for logging
    * @return   void.
    */
    void slotDpLogLevelChanged(int iLogLevel);

    /**
    * @brief    slotSetDpLoggingTypeAsyncCb slot catch by HMI module
    * to handle SetDpLoggingType request call back
    * @param    bool is call successful.
    * @param    int EDriveNextLoggingType updated logging location for logging
    * @return   void.
    */
    void slotSetDpLoggingTypeAsyncCb(bool bStatus, int iLoggingType);

    /**
    * @brief    slotDpLoggingTypeChanged slot catch by HMI module
    * to handle DpLoggingType value change
    * @param    int EDriveNextLoggingType updated logging location for logging
    * @return   void.
    */
    void slotDpLoggingTypeChanged(int iLoggingType);
    //________________________________________________________________________________________________
private:
    /**
    * @brief	CDriveNextEventHandler::connectSignals used to create connection for class CDriveNextEventHandler
    * @param	void.
    * @return	void.
    **/
    void connectSignals();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextEventHandler::disconnectSignals used to release connection for class CDriveNextEventHandler
    * @param	void.
    * @return	void.
    **/
    void disconnectSignals();
    //________________________________________________________________________________________________
};
#endif // CDRIVENEXTEVENTHANDLER_H
