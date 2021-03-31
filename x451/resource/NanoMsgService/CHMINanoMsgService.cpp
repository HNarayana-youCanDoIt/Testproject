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

#include "CHMINanoMsgService.h"
#include "logging.h"
#include "NanoMsgService/NanoMsg.h"

int CHMINanoMsgService::m_iNanoMsgSocketId = -1;

CHMINanoMsgService::CHMINanoMsgService() :
    m_bThreadIsToExit(false)
{

}

CHMINanoMsgService::~CHMINanoMsgService()
{

}

void CHMINanoMsgService::setNanoMsgSocketID(int iSocketID)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s socketID: %d", __FUNCTION__, iSocketID);
    m_iNanoMsgSocketId = iSocketID;
}

int CHMINanoMsgService::getNanoMsgSocketID()
{
    return m_iNanoMsgSocketId;
}

void CHMINanoMsgService::run()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"CHMINanoMsgService::run");
    do
    {
        int iMessageType = 0;
        int iReturn = -1;
        if(-1 == m_iNanoMsgSocketId)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s, ConnectToNanoMsgHost socket not connected", __FUNCTION__);
            break;
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s, ConnectToNanoMsgHost socketId: %d ", __FUNCTION__, m_iNanoMsgSocketId);
        }

        //Make sure that connection with server is achieved
        iReturn = SendNanoMessage(m_iNanoMsgSocketId, ENANOMSG_HMI_HANDSHAKING);
        if(ENANOMSG_HMI_HANDSHAKING_ACK == iReturn)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s, NanoMsgHandShake Successful... ", __FUNCTION__);
        }

        if (m_iNanoMsgSocketId >= 0)
        {
            while(!m_bThreadIsToExit)
            {
                //Recv the msgs from rvcaapp
                iMessageType = RecvNanoMessage(m_iNanoMsgSocketId);
                if (iMessageType > 0)
                {
                    processNanoMsg(iMessageType);
                }
                else if( -1 == iMessageType )
                {
                    //Not recovered from error. Come out of loop
                    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s, Message type -1 received from server", __FUNCTION__);
                }
                else
                {
                    // Do nothing
                }
            }
        }
        CloseNanoMsgConnection(m_iNanoMsgSocketId);
    }while(0);
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"CHMINanoMsgService::run thread while loop ended");
}

void CHMINanoMsgService::processNanoMsg(const int& iNanoMsg)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s, %d emit nano message ", __FUNCTION__, iNanoMsg);
    emit sigProcessNanoMsg(iNanoMsg);
}
