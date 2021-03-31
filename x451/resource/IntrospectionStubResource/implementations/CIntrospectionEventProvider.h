/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CIntrospectionEventProvider.h
* @ingroup      HMIComponent
* @author       Gaurav Garg
* CIntrospectionEventProvider, class to propogate events from resource layer
*/


#ifndef CINTROSPECTIONEVENTPROVIDER_H
#define CINTROSPECTIONEVENTPROVIDER_H

#include <QObject>

/**
 * @brief CIntrospectionEventProvider, class to propogate events for resource layer to the Introspection Adaptor layer
*/
class CIntrospectionEventProvider : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief CIntrospectionEventProvider Constructor
     * @param parent object instance
     * @return NA
     */
    explicit CIntrospectionEventProvider(QObject *parent = nullptr);

    /**
     * @brief ~CIntrospectionEventProvider Destructor
     * @param NA
     * @return NA
     */
    ~CIntrospectionEventProvider();
signals:

    /**
     * @brief sigGetIntrospectionData: the signal is emitted when there is an update to the InspectScreen parameter
     * @param iItemType The type of item - screen, drawer, popup
     * @param itemName The name of item that needs to be inspected
     * @return void
     */
    void sigGetIntrospectionData(int iItemType, QString itemName);

public:

    /**
    * @brief getIntrospectionData: This method will emit the signal sigGetIntrospectionData for notification
    * @param iItemType The type of item - screen, drawer, popup
    * @param itemName The name of item that needs to be inspected
    * @return	void
    */
    void getIntrospectionData(int iItemType, std::string itemName);

};

#endif // CINTROSPECTIONEVENTPROVIDER_H
