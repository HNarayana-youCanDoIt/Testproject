/*********************************************************************
* Project: X451
* (c) copyright 2017
* Company: Harman International India
* All rights reserved
* Secrecy Level STRICTLY CONFIDENTIAL
*********************************************************************
* @file            Nanomsg.h
* @ingroup         ParkAsist
* @author          Atita Halemani, Ashwini Shamaprasad, Rana Singh (Atita.Halemani@harman.com, Ashwini.Shamaprasad@harman.com and Rana Singh)
* @brief		   Receiving nano msg over PAM and informing to rvcapp
*/
#ifndef __NANO_MESSAGE__
#define __NANO_MESSAGE__
/*---------------------------------------------------------------------------*/
/****************		Include files		**********************************/
/*---------------------------------------------------------------------------*/

#include <nanomsg/nn.h>
#include <nanomsg/bus.h>
#include <nanomsg/nn.h>
#include <nanomsg/pubsub.h>
#include<string.h>
#include <logging.h>

/*****************************************************************************
 * Function Name		: SendNanoMessage
 * Parameters			: @ int socket: pass the socket id for socket communication
 * 						  @ int message: send msg to another service
 * Return				: inline int
 * Function Description	: send a nano msg to another service and process
 *
 *
 * Miscellaneous 		: None
 *****************************************************************************/
inline int SendNanoMessage(int socket,int message)
{

    int Bytes_Sent = nn_send(socket, &message, sizeof(int), 0);
    return Bytes_Sent;
}

/*****************************************************************************
 * Function Name		: Function_Name
 * Parameters			: int socket: pass the socket number for handshaking
 * Return				: inline int
 * Function Description	: Initial handshake between PAM and rvc app App
 *
 *
 * Miscellaneous 		: None
 *****************************************************************************/
inline int NanoMsgHandShake(int socket, int iMsgType )
{
    int count = 0;
    int recv = 0;
    int iReturn = -1;
    int timeout = 100;
    char *buf = NULL;
    int MessageType =-1;
    //Making sure that connection is established with RVCApp without any issue
    nn_setsockopt (socket, NN_SOL_SOCKET, NN_RCVTIMEO, &timeout, sizeof (timeout)) ;
    while(count < 10)
    {
        //Sending message to rvc app
        SendNanoMessage(socket,iMsgType);

        recv = nn_recv (socket, &buf, NN_MSG, 0);
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s nn_recv receive count %d", __FUNCTION__, recv);
        if (recv > 0)
        {
            MessageType = *((int *)buf);
            nn_freemsg (buf);
            LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s count: %d response: %d", __FUNCTION__, count, MessageType);
            iReturn = MessageType;
            break;
        }

        count ++;
    }
    timeout = -1; //to make receive blocking Again
    nn_setsockopt (socket, NN_SOL_SOCKET, NN_RCVTIMEO, &timeout, sizeof (timeout)) ;
    return iReturn;
}

/*****************************************************************************
 * Function Name		: RecvNanoMessage
 * Parameters			: int socket: pass the socket number to receive msg
 * Return				: inline int
 * Function Description	: Receiving and Parsing Nano messages
 *
 *
 * Miscellaneous 		: None
 *****************************************************************************/
inline int RecvNanoMessage(int socket)
{
    void *buf = NULL;
    int MessageType =-1;
    int recv = nn_recv (socket, &buf, NN_MSG, 0);
    if (recv > 0)
    {
        MessageType = *((int *)buf);
        nn_freemsg (buf);
    }
    else if((errno== EBADF) || (errno== ENOTSUP ) || (errno== ETERM))
    {
        MessageType = recv;

    }
    return MessageType;
}

/*****************************************************************************
 * Function Name		: CloseNanoMsgConnection
 * Parameters			: int sock: pass the socket number to close the communication
 * Return				: inline void
 * Function Description	: Closing the connection
 *
 *
 * Miscellaneous 		: None
 *****************************************************************************/
inline void CloseNanoMsgConnection(int sock)
{
    nn_shutdown (sock, 0);
}

/*****************************************************************************
 * Function Name		: OpenNanoMsgHost
 * Parameters			: None
 * Return				: inline int
 * Function Description	: return socket handel for server
 *
 *
 * Miscellaneous 		: None
 *****************************************************************************/
inline int OpenNanoMsgHost()
{
    const char *Serverurl = "ipc:///tmp/rvcapp.ipc";
    int sock = -1 ;
    //Creating socket with type bus
    sock = nn_socket (AF_SP,NN_BUS);
    if (sock < 0)
    {
        return -1;
    }
    //Binding to rvcapp node for communication
    if ((nn_bind (sock, Serverurl)) < 0)
    {
        CloseNanoMsgConnection(sock);
        return -1;
    }
    return sock;
}

/*****************************************************************************
 * Function Name		: ConnectToNanoMsgHost
 * Parameters			: None
 * Return				: inline int
 * Function Description	: Opening server side socket and binding it
 *
 *
 * Miscellaneous 		: None
 *****************************************************************************/
inline int ConnectToNanoMsgHost(const char *Serverurl)
{
    int sock = -1;
    int result = 0;

    //Creating socket with bus type
    sock = nn_socket (AF_SP,NN_BUS);
    if (sock < 0)
    {
        return -1;
    }

    //Connecting to rvcapp for communication over bus
    result = nn_connect (sock, Serverurl);
    if (result < 0)
    {
        CloseNanoMsgConnection(sock);
        return -1;
    }
    return sock;
}

#endif
/*---------------------------------------------------------------------------*/
/****************		End Of File	   ***************************************/
/*---------------------------------------------------------------------------*/
