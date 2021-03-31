/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CICCastEventProvider.h
* @ingroup      HMIComponent
* @author       Rahul Balyan
* CICastEventProvider, class to propogate events for resource layer to the ICCast Application layer
*/

#ifndef CICCASTEVENTPROVIDER_H
#define CICCASTEVENTPROVIDER_H

#include <QObject>

/**
 * @brief The CICCastEventProvider, class to propogate events for resource layer to the ICCast Application layer
 */
class CICCastEventProvider: public QObject
{
    Q_OBJECT

public:
    /**
     * @brief CICCastEventProvider: Constructor
     * @param pParent: parent object instance
     */
    CICCastEventProvider(QObject* pParent = 0);

    /**
     * @brief ~CICCastEventProvider: Destructor
     */
    ~CICCastEventProvider();

    /**
     * @brief updateIcRenderCastAsyncReqCb: Function which will send signal about the response callback status which the user has requested.
     * @param iICCastResponseCbValue: callback value for the request.
     * @return void.
     */
    void updateIcRenderCastAsyncReqCb(int iICCastResponseCbValue);

    /**
     * @brief updateIcProxyAvailability: Function which will send signal for the proxy availability status.
     * @param bIcProxyAvailability: proxy availability status.
     * @return void.
     */
    void updateIcProxyAvailability(bool bIcProxyAvailability);

    /**
     * @brief updateIcCastValue: Function which will send signal with the ic cast value to the application layer.
     * @param bIcCastValue: IC cast value
     * @return void.
     */
    void updateIcCastValue(bool bIcCastValue);

signals:

    /**
     * @brief sigUpdateIcRenderCastAsyncReqCb: Signal about the response callback status which the user has requested.
     * @param iICCastResponseCbValue: response callback status
     * @return void.
     */
    void sigUpdateIcRenderCastAsyncReqCb(int iICCastResponseCbValue);

    /**
     * @brief sigUpdateIcProxyAvailability: Signal for the proxy availability status.
     * @param bIcProxyAvailability: proxy availability status.
     * @return void.
     */
    void sigUpdateIcProxyAvailability(bool bIcProxyAvailability);

    /**
     * @brief sigUpdateIcCastValue: Signal for the ic cast value.
     * @param bIcCastValue: IC cast value
     * @return void.
     */
    void sigUpdateIcCastValue(bool bIcCastValue);


};

#endif // CICCASTEVENTPROVIDER_H
