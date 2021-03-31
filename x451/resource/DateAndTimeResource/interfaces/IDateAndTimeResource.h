/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          IDateAndTimeResource.h
 * @ingroup       HMIComponent
 * @author        Rajat Gupta
 *  IDateAndTimeResource, an interface for Time manager Resource Implementaion in HMI.
 */


#ifndef IDATEANDTIMERESOURCE_H
#define IDATEANDTIMERESOURCE_H

#include <capi/CAPIClientAbstraction.hpp>
#include "resource/DateAndTimeResource/interfaces/CDataTimeManagerResource.h"

//Proxies to be used
#include "v1/com/harman/TimeManager/TimeManager.hpp"
#include "v1/com/harman/TimeManager/TimeManagerProxy.hpp"
#include "v0/com/harman/TimeManager/timeManagerServiceTypes.hpp"

using namespace std;
using namespace v0::com::harman::TimeManager;


/*!
 * @interface IDateAndTimeResource
 * @brief This interfaces provides abstract methods to communicate with the
 * TimeManager proxy directly which shall be implemented by resource
 * implementation class.
 */

class IDateAndTimeResource
{
public:
    virtual ~IDateAndTimeResource(){}

    /*****  Request METHODS  ****************************/
    /**
    * @brief	IDateAndTimeResource::setSystemTime,This function sets the date and time of the system.
    * @param	sSystemDateTime , this structure  provides the values like hour,minute,sec,day,month year.
    * @return	void
    **/
    virtual void setSystemTime(const SSystemTimeData &sSystemDateTime) = 0;

    /**
     * @brief   setTimeFormat: This method sends request to time manager to set the time format.
     * @param   bIs24HrTimeFormat: contains time format, true - 24 hr, false - 12 hr.
     * @return	void.
     */
    virtual void setTimeFormat(bool bIs24HrTimeFormat) = 0;

private:

    /*********************************************************
                        CallBack Methods
     *********************************************************/
    /**
    * @brief	IDateAndTimeResource::timeManagerServiceStatusCb,This function ensures the availability of Time Manager service
    * @param	AvailabilityStatus eStatus, this provides the enum carrying the info whether the service is available,not known or unavailable.
    * @return	void
    **/
    virtual void timeManagerServiceStatusCb( CommonAPI::AvailabilityStatus eStatus) = 0;
 public:

    /**
    * @brief	IDateAndTimeResource::getSystemTimeWithTz24HrAttributeCb,This function invokes whenever there is a change event from service side.
    * @param	sSystemTime , this structure  provides the values like hour,minute,sec etc
    * @return	void
    **/
    virtual void getSystemTimeWithTz24HrAttributeCb(const timeManagerServiceTypes::systemTime & sSystemTime) = 0;
    /*********************************************************
                       Response CallBack Methods
     *********************************************************/

    /**
    * @brief	IDateAndTimeResource::setSystemTimeCb,This function is the callback of the setSystemTime.
    * @param	CallStatus , this gives info regarding CommonAPI status
    * @param	callBackStatus , this gives info regarding Callback status
    * @return	void
    **/
    virtual void setSystemTimeCb(const CommonAPI::CallStatus& callStatus, const bool& callBackStatus) = 0;

};

#endif // IDATEANDTIMERESOURCE_H


