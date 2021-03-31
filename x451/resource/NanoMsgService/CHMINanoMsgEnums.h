/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CHMINanoMsgEnums.h
* @ingroup      HMIComponent
* @author       Mohit Rajani
* CHVACEnum     Class that would contain all the Enums related to NANO message communication
*/

#ifndef CHMINANOMSGENUMS_H
#define CHMINANOMSGENUMS_H

const char RVCAPP_SOCKET_ADDR[]= {"ipc:///tmp/rvcapp.ipc"};

/**
     * @enum ENanoMsgId
     * @brief Enum for NANO message communication
     */
enum ENanoMsgId
{
    ENANOMSG_INVALID = -1,
    ENANOMSG_HMI_READY_NOTIFICATION = 11,       // Message to be sent
    ENANOMSG_HMI_READY_NOTIFICATION_ACK = 18,   //Expected reply

    ENANOMSG_RVC_HMI_STATUS = 28,               //Message to be sent
    ENANOMSG_REV_ENGAGE = 19,                   // Expected reply if reverse gear engaged
    ENANOMSG_REV_ENGAGE_ACK = 44,               // Expected reply if reverse gear engaged acknowledge
    ENANOMSG_REV_DISENGAGE = 20,                //Expected reply if reverse gear disengaged
    ENANOMSG_REV_DISENGAGE_ACK = 45,                //Expected reply if reverse gear disengaged acknowledge

    ENANOMSG_PARK_VARIANT_INFO = 31,            //Message to be sent
    ENANOMSG_PDC_VARIANT = 32,                  // Expected reply if variant is only PDC
    ENANOMSG_PDC_RVC_VARIANT = 33,              // Expected reply if variant is PDC_RVC
    ENANOMSG_RVC_VARIANT = 34,                  // Expected reply if variant is only RVC

    ENANOMSG_HMI_HANDSHAKING = 42,              // Message sent during nano msg handshaking between hmi and rvcapp
    ENANOMSG_HMI_HANDSHAKING_ACK = 43,          // Message sent during nano msg handshaking between hmi and rvcapp


    ENANOMSG_HMI_ANMIATION_STARTED = 46,        // Message to inform startup animation started / progress
    ENANOMSG_HMI_ANMIATION_STARTED_ACK = 47,        // Message to inform startup animation started / progress acknowledge

    ENANOMSG_HMI_ANMIATION_STOPPED = 48,        // Message to inform startup animation stopped / completed
    ENANOMSG_HMI_ANMIATION_STOPPED_ACK = 49,        // Message to inform startup animation stopped / completed acknowledge
};

#endif // CHMINANOMSGENUMS_H
