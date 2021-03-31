/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CSoftwareUpdateEventProvider.h
 * @ingroup       HMIComponent
 * @author        Nishant Khandagale
 * CSoftwareUpdateEventProvider, Class to send signals to Software Update Application layer on Software Update Resource events
 */

#ifndef CSOFTWAREUPDATEEVENTPROVIDER_H
#define CSOFTWAREUPDATEEVENTPROVIDER_H

#include <QObject>

/**
 * @brief The CSoftwareUpdateEventProvider class send signals to Software Update Application layer on Software Update Resource events
 */
class CSoftwareUpdateEventProvider: public QObject
{
    Q_OBJECT

public:
    /**
    * @brief	Constructor
    * @param	QObject*
    * @return	void
    */
    CSoftwareUpdateEventProvider(QObject* parent = 0);

    /**
    * @brief	Destructor
    * @param	void
    * @return	None
    */
    ~CSoftwareUpdateEventProvider();

signals:

    /**
    * @brief	This function is used to signal to application layer on availability of
    *           Software Update service
    * @param	bool swUpdateAvailability : Software Update service availability
    * @return	void
    */
    void sigSWUpdateAvailable(bool swUpdateAvailability);

    /**
    * @brief	This function is used to signal to application layer once response of Software Update request
    *           is recieved
    * @param	void
    * @return	void
    */
    void sigUpdateSoftware();

    /**
    * @brief	This function is used to signal to application layer on error of Software Update request
    * @param	type of error
    * @return	void
    */
    void sigUpdateError(uint type);

    /**
    * @brief	This function is used to signal to application layer on error of Software Update Availability request
    * @param	type of Update
    * @return	void
    */
    void sigUpdateSwAvailability(uint type);

public:

    /**
    * @brief	This function is called on response of Software update availability status
    *           and is consumed by the application layer
    * @param	bool swUpdateAvailability : Software Update Service availability
    * @return	void
    */
    void updateSwAvailabilityStatus(bool swUpdateAvailability);

    /**
    * @brief	This function is called on response of Software Update request and
    *           consumed by the application layer
    * @param	void
    * @return	void
    */
    void updateSoftware();

    /**
    * @brief	This function is called on error of Software Update request and
    *           consumed by the application layer
    * @param	uint type of error
    * @return	void
    */
    void updateError(uint type);

    /**
    * @brief	This function is called on availability error of Software Update request and
    *           consumed by the application layer
    * @param	uint type of update
    * @return	void
    */
    void updateSwAvailability(uint type);

};

#endif // CSOFTWAREUPDATEEVENTPROVIDER_H
