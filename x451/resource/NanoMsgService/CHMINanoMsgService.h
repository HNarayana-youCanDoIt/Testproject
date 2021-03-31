/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CHMINanoMsgService.h
* @ingroup      HMI Component
* @author       Mohit Rajani
* @brief The class creates the NanoMsg socket and listens for messages on it. The class propogates the information to the hmi
*       and send the correct response to the client over the socket
*/

#ifndef CHMINANOMSGSERVICE_H
#define CHMINANOMSGSERVICE_H
#include <QThread>
#include "CHMINanoMsgEnums.h"

/**
 * @brief The CHMINanoMsgService class
 * The class creates the NanoMsg socket and listens for messages on it. The class propogates the information to the hmi
 *       and send the correct response to the client over the socket
 */
class CHMINanoMsgService: public QThread
{
    Q_OBJECT
public:
    /**
     * @brief CHMINanoMsgService Constructor
     * @param void
     * @return void
     */
    CHMINanoMsgService();

    /**
     * @brief ~CHMINanoMsgService Destructor
     * @param void
     * @return void
     */
    ~CHMINanoMsgService();

    /**
     * @brief setNanoMsgSocketID used to set the global nano msg socket id
     * @param iSocketID global nano msg socket id to be used for all the nano msg communication
     * @param void
     */
    static void setNanoMsgSocketID(int iSocketID);

    /**
     * @brief getNanoMsgSocketID provides the global nano msg socket id
     * @param void
     * @return the global nano msg socket id to be used for all the nano msg communication
     */
    static int getNanoMsgSocketID();

protected:
    /**
     * @brief run over write QThread Function which will create the socket and listens for nano messages
     * @param void
     * @return void
     */
    virtual void run() override;

private:
    /**
     * @brief processNanoMsg Function that handles the messages from the clients and propogates the information to the hmi
     * applications
     * @param iNanoMsg the message type sent by the client
     * @return void
     */
    void processNanoMsg(const int& iNanoMsg);

signals:

    /**
     * @brief sigProcessNanoMsg signal is emitted to provide the information received to the hmi applications
     * @param iNanoMsg the message type sent by the client
     * @return void
     */
    void sigProcessNanoMsg(const int iNanoMsg);

private:
    /** Nano msg socket id **/
    static int m_iNanoMsgSocketId;

    /** informs whether the thread is to exit **/
    bool m_bThreadIsToExit;


};

#endif // CHMINANOMSGSERVICE_H
