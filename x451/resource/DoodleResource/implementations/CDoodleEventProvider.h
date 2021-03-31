/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CDoodleEventProvider.h
 * @ingroup       HMIComponent
 * @author        Nandkishor Lokhande
 * CDoodleEventProvider, This class propagates service signals to application layer.
 */
//________________________________________________________________________________________________
#ifndef CDoodleEVENTPROVIDER_H
#define CDoodleEVENTPROVIDER_H

#include <QObject>
#include <string>
using namespace std;

#include "CDoodleResourceData.h"
#include "CDoodleResourceEnum.h"
//________________________________________________________________________________________________
/*!
 * @class   CDoodleEventProvider
 * @brief   This class provides signals to catch service events
 *          which can be used by application layer.
 */
class CDoodleEventProvider : public QObject
{
    Q_OBJECT

public:
    //// Methods specific for CDoodleEventProvider class

    /**
    * @brief    CDoodleEventProvider: constructor for CDoodleEventProvider class.
    * @param    QObject pointer to link object with creator object.
    * @return   NA.
    */
    CDoodleEventProvider(QObject* pParent = 0);
    //________________________________________________________________________________________________
    /**
    * @brief    ~CDoodleEventProvider: destructor for CDoodleEventProvider class.
    * @param    NA.
    * @return   NA.
    */
    ~CDoodleEventProvider();
    //________________________________________________________________________________________________

public:
    //// Methods to call from service resource implementation class to propagate events to above layer

    /**
    * @brief    onProxyStatusChanged method gets call from service resource implementation class
    * when Doodle Proxy Status Changes
    * @param    void
    * @return   void.
    */
    void onProxyStatusChanged();
    //________________________________________________________________________________________________

signals:
    //// Signals to listen by HMI module to handle respective events

    /**
    * @brief    sigProxyStatusChanged signal listen by HMI modules
    * to handle Proxy availability status
    * @param    void.
    * @return   void.
    */
    void sigProxyStatusChanged();
    //________________________________________________________________________________________________
};

#endif // CDRIVENEXTEVENTPROVIDER_H
