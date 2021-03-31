/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          IParkAssistResource.h
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 *  IParkAssistResource, an interface for Park Assist Resource Implementaion in HMI.
 */

#ifndef IPARKASSISTRESOURCE_H
#define IPARKASSISTRESOURCE_H

#include "v0/com/harman/ParkAssist/PDCService.hpp"
#include "v0/com/harman/ParkAssist/PDCServiceProxy.hpp"
//#include "v0/com/harman/ParkAssist/VehInterface_types.hpp"
#include "v0/com/harman/ParkAssist/PDCServiceProxyBase.hpp"
#include "v1/com/harman/ParkAssist/ParkAssistBaseType.hpp"
#include <capi/CAPIClientAbstraction.hpp>
#include "ParkAssist/CParkAssistEnums.h"

using namespace std;
using namespace v0::com::harman::ParkAssist;
using namespace v1::com::harman::ParkAssist;

/*!
 * @interface IParkAssistResource
 * @brief This interfaces provides abstract methods to communicate with the
 * ParkAssistPresCtrl proxy directly which shall be implemented by resource
 * implementation class.
 */

class IParkAssistResource
{
public:
    virtual ~IParkAssistResource(){}

    /*****  Request METHODS  ****************************/

    /**
    * @brief	This pure virtual function is to set park assist delay timer, API call to be made with this method.
    * @param    iParkAssistDelayTimer: park assist delay timer is integer holding the park assist delay timer set from parkAssist adaptor.
    * @return	void.
    */
    virtual void setParkAssistDelayTimer(uint8_t iParkAssistDelayTimer) = 0;

    /**
    * @brief	This pure virtual function is to set park assist rear tone, API call to be made with this method.
    * @param    iPdcRearTone: park assist rear tone is integer holding the park assist rear tone set from parkAssist adaptor.
    * @return	void.
    */
    virtual void setParkAssistRearTone(CParkAssistEnum::EPDcRearTones iPdcRearTone) = 0;

    /**
     * @brief getRevGearStatus - Returns the current state of reverse gear activation
     * @param void
     * @return true if reverse gear activated else false
     */
    virtual bool getRevGearStatus() = 0;

    /**
     * @brief getActivationStatus - Returns the status of PDC/RVC is activated from HU
     * @param void
     * @return true if PDC/RVC is activated from HU else false
     */
    virtual bool getActivationStatus() = 0;

    /**
     * @brief getVariantType - Returns the current park assist variant.
     * @param void
     * @return 0 -default, 1- pdc, 2-rvc, 3-pdc/rvc
     */
    virtual int getVariantType() = 0;
    /*****  CALL BACK METHODS  ****************************/

    /**
    * @brief	This function is call back method to get park assist delay timer, response from pdcserviceproxy received here.
    * @param    iPdcDelayTimerVolume: iPdcDelayTimerVolume holding the park assist delay timer on response.
    * @return	void.
    */
    virtual void onParkAssistDelayTimerCb(uint8_t iPdcDelayTimerVolume) = 0;

    /**
    * @brief	This function is call back method to get park assist rear tone, response from pdcserviceproxy received here.
    * @param    iPdcRearTone: iPdcRearTone holding the park assist rear tone on response.
    * @return	void.
    */
    virtual void onParkAssistRearToneCb(uint8_t iPdcRearTone) = 0;

    /**
    * @brief	This function is call back method to get the Common API call status as Sucess or failure.
    * @param    status: callstatus will hold the event status on subscription.
    * @return	void.
    */
    virtual void setParkAssistRearToneAsyncCb(const CallStatus &status, ParkAssistBaseType::PDcRearToneReq_enum _ValueType) = 0;

    /**
    * @brief	This function is call back method to get the Common API call status as Sucess or failure.
    * @param    status: callstatus will hold the event status on subscription.
    * @return	void.
    */
    virtual void setParkAssistDelayTimerAsyncCb(const CallStatus &status, int _ValueType) = 0;

    /**
     * @brief	This method calls the API of PDCServiceProxy, to set the reverse gear status requested by user
     * @param   bool bReverseGearStatus: status of reverse gear, true - engaged or false - dis-engaged
     * @return	void
     */
    virtual void setReverseGearStatusAttribute(bool bReverseGearStatus) = 0;

    /**
     * @brief setHmiNotificationAttribute this method sets the HMI notification attribute which informs the RVC/PDC the HMI is up
     * and running
     * @param status informing the HMI is up and running, should be true always
     * @return void
     */
    virtual void setHmiNotificationAttribute(bool bHmiUpStatus) = 0;

 };

#endif // IVEHICLERESOURCE_H
