/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CSoftwareUpdateApplication.h
 * @ingroup         HMIComponent
 * @author          Nishant Khandagale
 * CSoftwareUpdateApplication, an Application for Software Update module,
 * CSoftwareUpdateApplication act as mediator between QML and Statemachine.
 */

#ifndef CSOFTWAREUPDATEAPPLICATION_H
#define CSOFTWAREUPDATEAPPLICATION_H

#include <QObject>
#include "HMIIncludes.h"

class CSoftwareUpdateSM;
class CSoftwareUpdateAdaptor;
class CSoftwareUpdateEventHandler;

/**
 * @brief The CSoftwareUpdateApplication class: This class contains all the functionality related to Software Update module
 *          creates instances for CSoftwareUpdateEventHandler & CSoftwareUpdateSM and raises SM events
 */
class CSoftwareUpdateApplication : public CBaseApplication
{
public:
    /**
    * @brief	CSoftwareUpdateApplication - Constructor for application class CSoftwareUpdateApplication
    * @param	QQuickItem
    * @return	NA
    **/
    CSoftwareUpdateApplication(QQuickItem* parent = nullptr);

    /**
    * @brief	~CSoftwareUpdateApplication - Destructor for application class CSoftwareUpdateApplication
    * @param	NA
    * @return	NA
    **/
    ~CSoftwareUpdateApplication();

    /**
    * @brief	onCreated - Method is called when the QML is loaded successfully, this is CBaseApplication method
    * @param	QQuickItem
    * @return	void
    **/
    virtual void onCreated(QQuickItem* rootObject);

    /**
     * @brief   loadScreen - Method is called to load the provide qml file onto the QQuickWindow, this is CBaseApplication method
     * @param   qmlFilePath - provide qml file path
     * @return	void
     */
    virtual void loadScreen(QString qmlFilePath);

    /**
     * @brief   raiseSMEvent - Method is called from the QML file to raise an event on the State machine, this is CBaseApplication method
     * @param   name & data
     * @return	void.
     */
    virtual void raiseSMEvent(const QString & name,const QVariant & data);

private:
    /* Instance of CSoftwareUpdateSM class */
    CSoftwareUpdateSM* m_pSoftwareUpdateSM;
    /* Instance of CSoftwareUpdateAdaptor class */
    CSoftwareUpdateAdaptor* m_pSoftwareUpdateAdaptor;
    /* Instance of CSoftwareUpdateEventHandler class */
    CSoftwareUpdateEventHandler* m_pSoftwareUpdateEventHandler;

    /* string constant for SM event */
    const QString ISO_STRING = "ISO";
    /* string constant for SM event */
    const QString BACK_STRING = "Back";
    /* string constant for SM event */
    const QString HOME_STRING = "Home";
    /* string constant for SM event */
    const QString ENGG_MENU_STRING = "EnggMenu";
    /* string constant for SM event */
    const QString USB_DISCONNECT_STRING = "usbDisconnect";


};

#endif // CSOFTWAREUPDATEAPPLICATION_H
