/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CRCAEventHandler.h
* @ingroup      HMIComponent
* @author       Nishant Khandagale
* @class        CRCAEventHandler: Class acts as the event handler for all the signals/events sent by CRCAEventHandler
* which informs RCA Adaptor about RCA resource events
*/

#ifndef CRCAEVENTHANDLER_H
#define CRCAEVENTHANDLER_H

#include <QObject>

/**
 * @brief The CRCAEventHandler Class acts as the event handler for all the signals/events sent by CRCAEventHandler
 * which informs RCA Adaptor about RCA resource events
 */
class CRCAEventHandler : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief CRCAEventHandler: constructor
     * @param pParent: parent object instance
     * @return void
     */
    explicit CRCAEventHandler(QObject *pParent = nullptr);

    /**
     * @brief CRCAEventHandler: destructor
     * @param void
     * @return void
     */
    ~CRCAEventHandler();

public slots:

    /**
     * @brief sltRCAActionUpdate: Method to inform RCA adaptor that a parituclar RCA action has been initiated
     * @param iRCAActionInitiated: action that has been initiated by RCA
     * @param uiIntInfo: int data to be passed
     */
    void sltRCAActionUpdate(int iRCAActionInitiated, uint uiIntInfo);

private:
    /**
     * @brief connectSignals: Method to connect CRCAEventProvider signals to slots
     * @param void
     * @return void
     */
    void connectSignals();

private:

};

#endif // CRCAEVENTHANDLER_H
