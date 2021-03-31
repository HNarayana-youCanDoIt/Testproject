/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
***************************************************************
*/
/**
* @file         IVRProxyResource.h
* @ingroup      HMIComponent
* @author       Rahul Singh Parihar
* @brief        IVRProxyResource will have the declarations required for functions and attributes
* in VR service to communicate with HMI.
*/

#ifndef IVRPROXYRESOURCE_H
#define IVRPROXYRESOURCE_H

#include <v1/com/harman/UISpeechService/UISpeechIntfProxy.hpp>
#include <v1/com/harman/UISpeechService/UISSTypes.hpp>

using namespace std;
using namespace v1::com::harman::UISpeechService;

class IVRProxyResource
{
public:

    /** The base class of IVRProxyResource */
    virtual ~IVRProxyResource() {}

    /**
     * @brief   onVRStateAttributeCb - Callback to get notified about the VR state change.
     * @param   eVRState - state of voice recognition.
     * @return  void.
     */
    virtual void onVRStateAttributeCb(UISSTypes::eVRStateEnum eVRState) = 0;

    /**
     * @brief   onVRDialogStateAttributeCb - Callback to get notified about the VR dialog state change.
     * @param   eVRState - state of voice recognition dialog whether active or inactive.
     * @return  void.
     */
    virtual void onVRDialogStateAttributeCb(UISSTypes::eVRDialogActive eVRDialogState) = 0;

    /**
     * @brief   onVRAvailableStateAttributeCb - Callback to get notified about the VR availability state change.
     * @param   eVRState - availability state of voice recognition whether available or not.
     * @return  void.
     */
    virtual void onVRAvailableStateAttributeCb(UISSTypes::sVRAvailable objVRAvailableState) = 0;

};

#endif // IVRPROXYRESOURCE_H
