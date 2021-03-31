/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CTunerApplication.h
 * @ingroup       HMIComponent
 * @author        Rahul Balyan
 * CTunerApplication,  This is an Application class for tuner module which communicates with project framework.
 * It also load tuner module's QML.
 **/

#ifndef CTUNERAPPLICATION_H
#define CTUNERAPPLICATION_H

#include <QObject>
#include "HMIIncludes.h"
#include "StateMachine_TML_HMI_SM.h"

/**
 * @brief The CTunerApplication class
 * This is an Application class for tuner module which communicates with project framework.
 * It also load tuner module's QML.
**/

class CTunerAdaptor;
class CTunerSM;
class CTunerEventHandler;

class CTunerApplication : public CBaseApplication
{
public:
    CTunerApplication(QQuickItem* parent = nullptr);

    ~CTunerApplication();

    /**
     * @brief onCreated - Function is called when the QML is loaded successfully
     * @param rootObject - provides the created qml object as the root Object
     */
    virtual void onCreated(QQuickItem* rootObject);

    /**
     * @brief raiseSMEvent - Function is called from the QML file to raise an event on the State machine
     * Based on which there might be a screen transition or internal state change
     * @param name - The name of the domain/module
     * @param data - The name of the event/state we want the SM to be transitioned into
     */
    void raiseSMEvent(const QString & name,const QVariant & data);

    /**
     * @brief loadScreen - Function is called to load the provide qml file onto the QQuickWindow
     * @param qmlFilePath - provide qml file path
     */
    void loadScreen(QString qmlFilePath);

private:

    // This pointer variable of CTunerAdaptor class will be used to communicate with tuner adaptor.
    CTunerAdaptor *m_pTunerAdaptor;

    // this pointer variable of CTunerSM class will be used to communicate with tuner state machine class.
    CTunerSM *m_pTunerSM;

    // This pointer variable of CTunerEventHandler class will be used to communicate with tuner event handler.
    CTunerEventHandler *m_pTunerEventHandler;

};



#endif // CTUNERAPPLICATION_H
