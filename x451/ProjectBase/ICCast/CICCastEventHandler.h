/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CICCastEventHandler.h
 * @ingroup         HMIComponent
 * @author          Rajat Gupta
 * CICCastEventHandler,  CICCastEventHandler for IC cast module,
 * CICCastEventHandler is a class used to communicate with the signals coming from resource layer and act accordingly.
 */
#ifndef CICCASTEVENTHANDLER_H
#define CICCASTEVENTHANDLER_H


#include <QObject>
#include <string>
#include "CICCastAdaptor.h"
using namespace std;

/**
 * @class CICCastEventHandler
 * @brief Class has the slots for all the Signals sent by CICCastEventProvider
 *        which informs IC Cast Adaptor about IC Cast Resource Events
 */
class CICCastEventHandler: public QObject
{
    Q_OBJECT

public:

    CICCastEventHandler(QObject* parent = 0);

    ~CICCastEventHandler();

public slots:

    /**
  * @brief sltUpdateIcRenderCastAsyncReqCb: Slot which will let us know the ic cast value which has been set is a success or failure.
  * @param iCallbackStatus: Status for the callback request.
  * @return void.
  */
 void sltUpdateIcRenderCastAsyncReqCb(int iCallbackStatus);

 /**
  * @brief sltUpdateIcProxyAvailability: This slots will help to enable/disable the ic cast button based on the proxy availability.
  * @param bIcProxyAvailability: IC Cast Proxy Status.
  * @return void.
  */
 void sltUpdateIcProxyAvailability(bool bIcProxyAvailability);

 /**
  * @brief sltUpdateIcCastValue: This slots will help to activate/deactivate the ic cast button based on the IC cast value from the service side.
  * @param bIcCastValue: IC Cast Proxy Status.
  * @return void.
  */
 void sltUpdateIcCastValue(bool bIcCastValue);

private:
    /**
     * @brief Method to connect CICCastEventProvider signals to slots
     * @param void
     * @return void
     */
    void connectSignals();
};

#endif // CICCASTEVENTHANDLER_H
