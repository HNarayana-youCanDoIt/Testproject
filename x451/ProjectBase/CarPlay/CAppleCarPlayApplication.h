/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CAppleCarPlayApplication.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* This file is having the declaration for CAppleCarPlayApplication class of
* AppleCarPlay.
*/

#ifndef CAPPLECARPLAYAPPLICATION_H
#define CAPPLECARPLAYAPPLICATION_H

#include <QObject>
#include "HMIIncludes.h"
#include "CAppleCarPlayEnums.h"

class CAppleCarPlaySM;
class CAppleCarPlayAdaptor;
class CAppleCarPlayEventHandler;

/**
 * @class CAppleCarPlayApplication
 * @brief The CAppleCarPlayApplication class of AppleCarPlay, This class provides
 * basic application functionalities to AppleCarPlay, like qml debug logging and
 * raiseEvent function to raise StateMachine events.
 */
class CAppleCarPlayApplication : public CBaseApplication
{

public:
    /*!
     * @brief   Constructor of CAppleCarPlayApplication
     * @param   pParent: parent class pointer.
     * @return  void.
     */
    CAppleCarPlayApplication(QQuickItem* pParent = nullptr);

    /*!
     * @brief   Destructor of CAppleCarPlayApplication
     * @param   void.
     * @return  void.
     */
    ~CAppleCarPlayApplication();

    /**
     * @brief onCreated - Function is called when the QML is loaded successfully
     * @param pRootObject - provides the created qml object as the root Object
     * @return	void.
     */
    void onCreated(QQuickItem* pRootObject);

    /**
     * @brief raiseSMEvent - Function is called from the QML file to raise an event on the State machine
     * Based on which there might be a screen transition or internal state change
     * @param name - The name of the domain/module
     * @param data - The name of the event/state we want the SM to be transitioned into
     * @return	void.
     */
    void raiseSMEvent(const QString & name, const QVariant & data);

private:

private:
    /**
     * @brief m_pAppleCarPlaySM: Pointer of AppleCarPlay SM class.
     */
    CAppleCarPlaySM* m_pAppleCarPlaySM;

    /**
     * @brief m_pAppleCarPlayEventHandler: Pointer of CAppleCarPlayEventHandler
     */
    CAppleCarPlayEventHandler *m_pAppleCarPlayEventHandler;
};

#endif // CAPPLECARPLAYAPPLICATION_H
