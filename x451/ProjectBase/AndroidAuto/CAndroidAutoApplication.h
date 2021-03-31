/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CAndroidAutoApplication.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* This file is having the declaration for CAndroidAutoApplication class of
* AndroidAuto.
*/

#ifndef CANDROIDAUTOAPPLICATION_H
#define CANDROIDAUTOAPPLICATION_H

#include <QObject>
#include "HMIIncludes.h"
#include "CAndroidAutoEnums.h"

class CAndroidAutoSM;
class CAndroidAutoAdaptor;
class CAndroidAutoEventHandler;

/**
 * @class CAndroidAutoApplication
 * @brief The CAndroidAutoApplication class of AndroidAuto, This class provides
 * basic application functionalities to AndroidAuto, like qml debug logging and
 * raiseEvent function to raise StateMachine events.
 */
class CAndroidAutoApplication : public CBaseApplication
{

public:
    /*!
     * @brief   Constructor of CAndroidAutoApplication
     * @param   pParent: parent class pointer.
     * @return  void.
     */
    CAndroidAutoApplication(QQuickItem* pParent = nullptr);

    /*!
     * @brief   Destructor of CAndroidAutoApplication
     * @param   void.
     * @return  void.
     */
    ~CAndroidAutoApplication();

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
     * @brief m_pAndroidAutoSM: Pointer of Android Auto SM class.
     */
    CAndroidAutoSM* m_pAndroidAutoSM;

    /**
     * @brief m_pAndroidAutoEventHandler: Pointer of CAndroidAutoEventHandler
     */
    CAndroidAutoEventHandler *m_pAndroidAutoEventHandler;
};

#endif // CANDROIDAUTOAPPLICATION_H
