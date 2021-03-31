/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CDiagnosticEventProvider.h
 * @ingroup       HMIComponent
 * @author        Manali Patil
 * CDiagnosticEventProvider, Class to send signals to Diagnostic Application layer on Diagnostic Resource events
 */

#ifndef CDIAGNOSTICEVENTPROVIDER_H
#define CDIAGNOSTICEVENTPROVIDER_H

#include <QObject>

/**
 * @brief The CDiagnosticEventProvider class send signals to Diagnostic Application layer on Diagnostic Resource events
 */
class CDiagnosticEventProvider: public QObject
{
    Q_OBJECT

public:
    /**
    * @brief	Constructor
    * @param	QObject*
    * @return	void
    */
    CDiagnosticEventProvider(QObject* pParent = 0);

    /**
    * @brief	Destructor
    * @param	void
    * @return	None
    */
    ~CDiagnosticEventProvider();

signals:

    /** @brief Signal to notify antenna connection status has been updated
    * @param iAntennaStatus : Status of Antenna Connection.
    * @return void
    */
    void sigUpdateAntennaConnectionStatus(int iAntennaStatus);

    /** @brief Signal to notify swc connection status has been updated
    * @param iSWCStatus: Status of SWC Connection.
    * @return void
    */
    void sigUpdateSWCConnectionState(int iSWCStatus);

    /** @brief Signal to notify mic connection status has been updated
    * @param iMICStatus  : Status of MIC Connection.
    * @return void
    */
    void sigUpdateMICConnectionStatus(int iMICStatus);

public:

    /**
    * @brief	updateAntennaConnectionStatus: update antenna connection status.
    * @param	iAntennaStatus : Status of Antenna Connection.
    * @return	void
    */
    void updateAntennaConnectionStatus(int iAntennaStatus);

    /**
    * @brief	updateSWCConnectionState: update swc connection status.
    * @param	iSWCStatus: Status of SWC Connection.
    * @return	void
    */
    void updateSWCConnectionState(int iSWCStatus);

    /**
    * @brief	updateMICConnectionStatus: update mic connection status.
    * @param	iMICStatus  : Status of MIC Connection.
    * @return	void
    */
    void updateMICConnectionStatus(int iMICStatus);

};

#endif // CDIAGNOSTICEVENTPROVIDER_H
