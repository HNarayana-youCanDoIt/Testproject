/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CDateAndTimeResourceImpl.h
 * @ingroup       HMIComponent
 * @author        Rajat Gupta
 * CDateAndTimeResourceImpl, Resource Implementation for DateAndTime.
 */

#ifndef CDATEANDTIMERESOURCEIMPL_H
#define CDATEANDTIMERESOURCEIMPL_H

#include <capi/CAPIClientAbstraction.hpp>
#include "DateAndTimeResource/interfaces/IDateAndTimeResource.h"


using namespace std;
using namespace v1::com::harman::TimeManager;


class CDateAndTimeEventProvider;
/**
*   @brief The DateAndTimeResourceImpl class
*   This class implements the DateAndTimeResourceImpl interface.
*/

class CDateAndTimeResourceImpl: public IDateAndTimeResource
{
public:

    virtual ~CDateAndTimeResourceImpl();


    CDateAndTimeResourceImpl();


    CDateAndTimeEventProvider* getDateAndTimeEventProvider();


    /*****  Request METHODS  ****************************/
    /**
    * @brief	IDateAndTimeResource::setSystemTime,This function sets the date and time of the system.
    * @param	sSystemDateTime , this structure  provides the values like hour,minute,sec etc
    * @return	void
    **/

    void setSystemTime(const SSystemTimeData &sSystemDateTime) override;

    /**
     * @brief   setTimeFormat: This method sends request to time manager to set the time format.
     * @param   bIs24HrTimeFormat: contains time format, true - 24 hr, false - 12 hr.
     * @return	void.
     */
    void setTimeFormat(bool bIs24HrTimeFormat) override;



    /*********************************************************
                        CallBack Methods
     *********************************************************/
    /**
    * @brief	CDateAndTimeResourceImpl::timeManagerServiceStatusCb,This function ensures the availability of Time Manager service
    * @param	AvailabilityStatus eStatus, this provides the enum carrying the info whether the service is available,not known or unavailable.
    * @return	void
    **/
    void timeManagerServiceStatusCb( CommonAPI::AvailabilityStatus eStatus) override;

    /**
    * @brief	IDateAndTimeResource::getSystemTimeWithTz24HrAttributeCb,This function invokes whenever there is a change event from service side.
    * @param	sSystemTime , this structure  provides the values like hour,minute,sec etc
    * @return	void
    **/
     void getSystemTimeWithTz24HrAttributeCb(const timeManagerServiceTypes::systemTime &sSystemTime) override;


     /*********************************************************
                        Response CallBack Methods
      *********************************************************/

     /**
     * @brief	IDateAndTimeResource::setSystemTimeCb,This function is the callback of the setSystemTime.
     * @param	CallStatus , this gives info regarding CommonAPI status
     * @param	callBackStatus , this gives info regarding Callback status
     * @return	void
     **/
     void setSystemTimeCb(const CommonAPI::CallStatus& callStatus, const bool& callBackStatus) override;

     /**
      * @brief   onGetTimeFormatAttributeCb: This is a call back method to the attribute getTimeFormatAttribute.
      * @param   eTimeFormat: contains time format, 1: 12 hr, 2: 24 hr.
      * @return	void.
      */
     void onGetTimeFormatAttributeCb(timeManagerServiceTypes::TM_Format eTimeFormat);

     /**
      * @brief   setTimeFormatCb: This is a call back method to the setTimeFormatAsync.
      * @param   callStatus: status of the call, success or failure.
      * @param   callBackStatus: status of hmi request, success or failure.
      * @return	void.
      */
     void setTimeFormatCb(const CallStatus& callStatus, const bool& callBackStatus);



    /*********************************************************
                        Internal Methods
     *********************************************************/

     /*!
      * @brief   Method to get date and time information.
      * @param   void.
      * @return  const reference instance of SSystemTimeData structure.
      */
     const SSystemTimeData& getSystemTimeData(){ return m_objSystemTimeData; }

private:
    friend class CHMIMain;

    /**
    * @brief	This function is to subscribe the DateAndTime settings events
    *           provided by DateAndTimepresctrlsettings proxy.
    * @param    void.
    * @return	void.
    */
    void subscribeDateAndTimeProxy();


    /* Create an instance of the CDateAndTimeDataEventProvider to emit signals to the upper layer **/
    CDateAndTimeEventProvider* m_pDateAndTimeEventProvider;

    /* TimeManager presctrlcontrolsproxy class object to call DateAndTime proxy methods **/
    CAPIClientAbstraction<TimeManagerProxy> m_pDateAndTimeProxy;

    //boolean variable to check if the Date and Time service is available or not.
    bool m_bIsDateAndTimeServiceAvailable;

    // Object of the SSystemTimeData Structure.
    SSystemTimeData   m_objSystemTimeData;

};
#endif // CDateAndTimeResourceImpl_H
