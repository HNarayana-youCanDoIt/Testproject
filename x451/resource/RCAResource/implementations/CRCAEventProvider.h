/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CRCAEventProvider.h
* @ingroup      HMIComponent
* @author       Nishant Khandagale
* CRCAEventProvider, class to propogate events for resource layer to the RCA Application layer
*/

#ifndef CRCAEVENTPROVIDER_H
#define CRCAEVENTPROVIDER_H

#include <QObject>
#include "v1/com/harman/dcif/RCAServiceTypes.hpp"

using namespace v1::com::harman::dcif;

/**
 * @brief The CRCAEventProvider, class to propogate events for resource layer to the RCA Application layer
 */
class CRCAEventProvider: public QObject
{
    Q_OBJECT

public:
    /**
     * @brief CRCAEventProvider: Constructor
     * @param pParent: parent object instance
     */
    CRCAEventProvider(QObject* pParent = 0);

    /**
     * @brief ~CRCAEventProvider: Destructor
     */
    ~CRCAEventProvider();

signals:

    /**
     * @brief sigRCAActionUpdate: the signal is emitted when there is an update from RCA
     * @param iRCAActionInitiated: action initiated by RCA
     * @param uiIntInfo: int data to be passed
     * @return void
     */
    void sigRCAActionUpdate(int iRCAActionInitiated, uint uiIntInfo);

public:

    /**
     * @brief rcaActionUpdate: the function is called from the resource implementation to propogate update event to the above layers
     * @param iRCAActionInitiated: action that has been initiated by RCA
     * @param uiIntInfo: int data to be passed
     * @return void
     */
    void rcaActionUpdate(int iRCAActionInitiated, uint uiIntInfo);

};

#endif // CRCAEVENTPROVIDER_H
