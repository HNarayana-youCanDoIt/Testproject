/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CDiagnosticEventHandler.h
* @ingroup      HMIComponent
* @author       Manali Patil
* @class        CDiagnosticEventHandler: Class has the slots for all the Signals sent by CDiagnosticEventProvider
*                                   which informs Diagnostic Adaptor about Diagnostic Resource Events
*/

#ifndef CDIAGNOSTICEVENTHANDLER_H
#define CDIAGNOSTICEVENTHANDLER_H

#include <QObject>

class CDiagnosticAdaptor;

/**
 * @brief The CDiagnosticEventHandler class: This class is to handle Diagnostic events.
 *          Diagnostic resource event provider will emit signals and those will be handled here.
 */
class CDiagnosticEventHandler : public QObject
{
    Q_OBJECT
public:

    /**
    * @brief	CDiagnosticEventHandler - Constructor for event handler class CDiagnosticEventHandler
    * @param	pParent: Parent class pointer.
    * @return	void.
    **/
    explicit CDiagnosticEventHandler(QObject *pParent = nullptr);

    /**
    * @brief	~CDiagnosticEventHandler - Destructor for event handler class CDiagnosticEventHandler
    * @param	void.
    * @return	void.
    **/
    ~CDiagnosticEventHandler();

public slots:

    /**
    * @brief	This method will inform antenna connection status to Diagnostic adaptor .
    * @param    iAntennaConnectionStatus : Status of Antenna Connection.
    * @return	void
    */
    void sltUpdateAntennaConnectionStatus(int iAntennaConnectionStatus);

    /**
    * @brief	This method will inform swc connection status to Diagnostic adaptor .
    * @param    iSWCConnectionStatus: Status of SWC Connection.
    * @return	void
    */
    void sltUpdateSWCConnectionState(int iSWCConnectionStatus);

    /**
    * @brief	This method will inform mic connection status to Diagnostic adaptor .
    * @param    iMICConnectionStatus  : Status of MIC Connection.
    * @return	void
    */
    void sltUpdateMICConnectionStatus(int iMICConnectionStatus);

private:
    /**
    * @brief	This function will connect signals and slots
    * @param	void
    * @return	void
    */
    void connectSignals();
};

#endif // CDIAGNOSTICEVENTHANDLER_H
