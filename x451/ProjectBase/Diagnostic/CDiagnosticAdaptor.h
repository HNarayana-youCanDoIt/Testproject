/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDiagnosticAdaptor.h
 * @ingroup         HMIComponent
 * @author          Manali Patil
 * CDiagnosticAdaptor, an Adaptor for Diagnostic module,
 * CDiagnosticAdaptor used to communicate between QML and Resource Layer.
 */

#ifndef CDIAGNOSTICADAPTOR_H
#define CDIAGNOSTICADAPTOR_H

#include <QObject>
#include <CDiagnosticEnum.h>

class IDiagnosticResource;

/**
 * @brief The CDiagnosticAdaptor class: This singleton class contains methods to handle Diagnostic related functionality
 */
class CDiagnosticAdaptor : public QObject
{
    Q_OBJECT

    //Properties
    /* To get antenna connection status information */
    Q_PROPERTY(CDiagnosticEnum::EConnectionStatus antennaConnectionStatus READ antennaConnectionStatus NOTIFY sigAntennaConnectionStatusChanged)

    /* To get swc connection status information */
    Q_PROPERTY(CDiagnosticEnum::EConnectionStatus swcConnectionStatus READ swcConnectionStatus NOTIFY sigSWCConnectionStatusChanged)

    /* To get mic connection status information */
    Q_PROPERTY(CDiagnosticEnum::EConnectionStatus micConnectionStatus READ micConnectionStatus NOTIFY sigMICConnectionStatusChanged)

public:
    /**
    * @brief	getInstance :This function get the instance of adaptor class.
    * @param	void
    * @return   pointer to CDiagnosticAdaptor
    */
    static CDiagnosticAdaptor* getInstance();

    /**
    * @brief	 ~CDiagnosticAdaptor: Destructor
    * @param	void
    * @return   None
    */
    ~CDiagnosticAdaptor();

    /**
     * @brief antennaConnectionStatus:  Method to get the value of m_eAntennaConnectionStatus
     * @param void
     * @return m_eAntennaConnectionStatus - Value of antenna connection status
     */
    CDiagnosticEnum::EConnectionStatus antennaConnectionStatus();

    /**
     * @brief swcConnectionStatus: Method to get the value of m_eSWCConnectionStatus
     * @param void
     * @return m_eSWCConnectionStatus - Value of swc connection status
     */
    CDiagnosticEnum::EConnectionStatus swcConnectionStatus();

    /**
     * @brief micConnectionStatus: Method to get the value of m_eMICConnectionStatus
     * @param void
     * @return m_eMICConnectionStatus - Value of mic connection status
     */
    CDiagnosticEnum::EConnectionStatus micConnectionStatus();

    /**
     * @brief setAntennaConnectionStatus: Method to set the connection status of antenna
     * @param eAntennaConnectionStatus - Value of antenna connection status from diagnostic service
     * @return void
     */
    void setAntennaConnectionStatus(CDiagnosticEnum::EConnectionStatus eAntennaConnectionStatus);

    /**
     * @brief setSWCConnectionStatus: Method to set the connection status of swc
     * @param eSWCConnectionStatus - Value of swc connection status from diagnostic service
     * @return void
     */
    void setSWCConnectionStatus(CDiagnosticEnum::EConnectionStatus eSWCConnectionStatus);

    /**
     * @brief setMICConnectionStatus: Method to set the connection status of mic
     * @param eMICConnectionStatus - Value of mic connection status from diagnostic service
     * @return void
     */
    void setMICConnectionStatus(CDiagnosticEnum::EConnectionStatus eMICConnectionStatus);


signals:

    /**
    * @brief	sigAntennaConnectionStatusChanged: This signal will emit antenna status information
    * @param	void
    * @return	void
    */
    void sigAntennaConnectionStatusChanged();

    /**
    * @brief	sigSWCConnectionStatusChanged: This signal will emit swc status information
    * @param	void
    * @return	void
    */
    void sigSWCConnectionStatusChanged();

    /**
    * @brief	sigMICConnectionStatusChanged: This signal will emit mic status information
    * @param	void
    * @return	void
    */
    void sigMICConnectionStatusChanged();

public slots:

private:
    /**
    * @brief	CDiagnosticAdaptor: Constructor
    * @param	QObject *parent : Parent class instance
    * @return   None
    */
    explicit CDiagnosticAdaptor(QObject *parent = nullptr);

    /* Static pointer for CDiagnosticAdaptor instance */
    static CDiagnosticAdaptor* m_pDiagnosticAdaptor;

    /* Pointer to IDiagnosticResource instance */
    IDiagnosticResource* m_pDiagnosticResource;

    /* This variable holds the antenna connection details */
    CDiagnosticEnum::EConnectionStatus m_eAntennaConnectionStatus;

    /* This variable holds the swc connection details */
    CDiagnosticEnum::EConnectionStatus m_eSWCConnectionStatus;

    /* This variable holds the mic connection details */
    CDiagnosticEnum::EConnectionStatus m_eMICConnectionStatus;
};

#endif // CDIAGNOSTICADAPTOR_H
