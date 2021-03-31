/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CSoftwareUpdateEventHandler.h
* @ingroup      HMIComponent
* @author       Nishant Khandagale
* @class        CSoftwareUpdateEventHandler: Class has the slots for all the Signals sent by CSoftwareUpdateEventHandler
*                                   which informs Software Update Adaptor about Software Update Resource Events
*/

#ifndef CSOFTWAREUPDATEEVENTHANDLER_H
#define CSOFTWAREUPDATEEVENTHANDLER_H

#include <QObject>
#include "Test/SoftwareUpdate/CSoftwareUpdateEventHandlerTest.h"

class CSoftwareUpdateAdaptor;

/**
 * @brief The CSoftwareUpdateEventHandler class: This class is to handle Software Update events.
 *          Software Update resource event provider will emit signals and those will be handled here.
 */
class CSoftwareUpdateEventHandler : public QObject
{
    Q_OBJECT
public:

    /**
    * @brief	CSoftwareUpdateEventHandler - Constructor for event handler class CSoftwareUpdateEventHandler
    * @param	QQuickItem
    * @return	NA
    **/
    explicit CSoftwareUpdateEventHandler(QObject *parent = nullptr);

    /**
    * @brief	~CSoftwareUpdateEventHandler - Destructor for event handler class CSoftwareUpdateEventHandler
    * @param	QQuickItem
    * @return	NA
    **/
    ~CSoftwareUpdateEventHandler();

    FRIEND_TEST(CSoftwareUpdateEventHandlerTest, coverage);


public slots:

    /**
    * @brief	This function will update software update Availibility status received from
    *           Software Update Resource layer.
    * @param	bool swUpdateAvailability : Software Update service availability
    * @return	void
    */
    void sltSWUpdateAvailable(bool swUpdateAvailability);

    /**
    * @brief	This function will update ISO List received from Software Update Resource layer.
    * @param	void
    * @return	void
    */
    void sltUpdateSoftware();

    /**
     * @brief	This function will show error messages recieved from Software Update Resource layer.
     * @param	uint type of error message
     * @return	void
     */
     void sltUpdateError(uint uiSwUpdateError);

     /**
      * @brief	This function will show availability update messages recieved from Software Update Resource layer.
      * @param	uint type of update message
      * @return	void
      */
      void sltUpdateSwAvailability(uint uiSwAvailabilityType);


private:
    /**
    * @brief	This function will connect signals and slots
    * @param	void
    * @return	void
    */
    void connectSignals();

    /* Pointer to CSoftwareUpdateAdaptor */
    CSoftwareUpdateAdaptor *m_pSoftwareUpdateAdaptor;
};

#endif // CSOFTWAREUPDATEEVENTHANDLER_H
