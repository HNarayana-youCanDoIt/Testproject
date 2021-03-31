
/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CIntrospectionEventHandler.h
* @ingroup      HMIComponent
* @author       Gaurav Garg
* CIntrospectionEventHandler: Class acts as the event handler for all the signals/events sent by CIntrospectionEventHandler
* which informs Introspection Adaptor about Introspection resource events
*/

#ifndef CINTROSPECTIONEVENTHANDLER_H
#define CINTROSPECTIONEVENTHANDLER_H

#include <QObject>

/**
 * @brief CIntrospectionEventHandler: Class acts as the event handler for all the signals/events sent by CIntrospectionEventHandler
* which informs Introspection Adaptor about Introspection resource events
*/
class CIntrospectionEventHandler : public QObject
{
    Q_OBJECT
public:

    explicit CIntrospectionEventHandler(QObject *parent = nullptr);

    ~CIntrospectionEventHandler();

public slots:

    /**
     * @brief sltGetIntrospectionData Method to inform Introspection adaptor that inspect screen data is required
     * @param iItemType The type of item - screen, drawer, popup
     * @param itemName The name of item that needs to be inspected
     * @return void
     */
    void sltGetIntrospectionData(int iItemType, QString itemName);

private:

    /**
     * @brief Method to connect CIntrospectionEventProvider signals to slots
     * @param void
     * @return void
     */
    void connectSignals();

};

#endif // CINTROSPECTIONEVENTHANDLER_H
