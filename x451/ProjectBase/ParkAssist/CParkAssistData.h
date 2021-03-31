/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CParkAssistData.h
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * This class is to store the Park Assist data like fault messages & alert icons visibility.
 */

#ifndef CPARKASSISTDATA_H
#define CPARKASSISTDATA_H

#include "QString"

/**
 * @brief The CParkAssistData class: This class is to store the Park Assist data like fault messages & alert icons visibility.
 */
class CParkAssistData
{
public:

    CParkAssistData();
    ~CParkAssistData();

    /**
     * @brief CParkAssistData: To initialise the members of park assist data class.
     * @param strPdcRvcFaultMessage: contains fault message to be shown.
     * @param bAlertIconVisibility: contains alert icon available status, true - available, false - not available.
     */
    CParkAssistData(QString strPdcRvcFaultMessage, bool bAlertIconVisibility);

    /**
     * @brief  isAlertIconAvailable: Returns the status of Alert icon, true - available, false - not available.
     * @param  void.
     * @return bool: Alert icon available status.
     */
    bool isAlertIconAvailable();

    /**
     * @brief	pdcRvcFaultMessage: Returns the fault message of the PDC-RVC system.
     * @param	void.
     * @return	returns the fault message of the PDC-RVC system.
     */
    QString pdcRvcFaultMessage();

private:

    /** This variable holds the alert icon available status, true - available, false - not available */
    bool m_bIsAlertIconAvailable;

    /** This variable holds PDC-RVC fault message */
    QString m_strPdcRvcFaultMessage;

};

#endif // CPARKASSISTDATA_H
