/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CIntrospectionApplication.h
* @ingroup      HMIComponent
* @author       Gaurav Garg
* CIntrospectionApplication, an Application for Introspection module,
* CIntrospectionApplication act as creator calls for the adaptor and event handler
*/

#ifndef CINTROSPECTIONAPPLICATION_H
#define CINTROSPECTIONAPPLICATION_H

#include <QObject>
#include "HMIIncludes.h"

class CIntrospectionAdaptor;
class CIntrospectionEventHandler;

/**
 * @brief The CIntrospectionApplication CIntrospectionApplication, an Application for Introspection module,
 * CIntrospectionApplication act as creator calls for the adaptor
 */
class CIntrospectionApplication: public QObject
{
public:
    CIntrospectionApplication(QObject* parent = nullptr);
    ~CIntrospectionApplication();

private:
    /** Stores the Introspection adaptor object instance */
    CIntrospectionAdaptor* m_pIntrospectionAdaptor;

    /** Stores the event handler object instance */
    CIntrospectionEventHandler* m_pIntrospectionEventHandler;

};

#endif // CINTROSPECTIONAPPLICATION_H
