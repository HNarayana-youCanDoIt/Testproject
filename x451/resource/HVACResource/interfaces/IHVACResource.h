/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         IHVACResource.h
* @ingroup      HMIComponent
* @author       Mohit Rajani
* IHVACResource, an interface for the HVAC (Ccm) Resource Implementaion in HMI.
*/

#ifndef IHVACRESOURCE_H
#define IHVACRESOURCE_H

#include <QVariant>
#include <string>
#include <QString>
#include <QObject>
#include "v0/com/harman/dcif/CcmHuProxy.hpp"
#include "v0/com/harman/dcif/CcmPresTypes.hpp"
#include <capi/CAPIClientAbstraction.hpp>
#include "implementations/CHVACData.h"

using namespace std;
using namespace v0::com::harman::dcif;

/**
 * @interface IHVACResource
 * @brief     This interface provides functionality that would be implemented to interact
 *            with HVAC presctrl and also to provide data to HVAC Adaptor Layer
 */
class IHVACResource
{
public:
    virtual ~IHVACResource(){}

    /*****  Request METHODS  ****************************/

    /**
     * @brief huCcm_req: Call the HVAC (ccm presCtrl) to set the value for a particular HVAC parameter
     * @param eCcmHuParam Enum that defines the HVAC parameter that needs to be set
     * @param uiValue provides the value that needs to be set for the provided HVAC parameter
     * @return None
     */
    virtual void huCcm_req(CcmPresTypes::eHuCcmParam eCcmHuParam, const uint16_t uiValue)= 0;

    /**
       * @brief getCcmInfo: Call the HVAC (ccm presCtrl) to get the value for all HVAC parameters
       * @param None
       * @return None
       */
      virtual void getCcmInfo()= 0;


      /**
      * @brief	This method will return HVAC structure reuested by adaptor.
      * @param	None
      * @return	SHVACParamValues : structure which contains HVAC information from CCM service.
      */
      virtual SHVACParamValues fetchHVACInfo() = 0;


    /*****  CALL BACK METHODS  ****************************/

    /**
     * @brief asyncCcmHuReqCb the async callback that will be invoked once huCcm_reqAsync is completed
     * @param callStatus provides the status of the async call made
     * @return void
     */
    virtual void asyncCcmHuReqCb(const CommonAPI::CallStatus& callStatus)=0;

    /**
     * @brief asyncCcmHuParameterCb the async callback is invoked when any of the HVAC parameters has an update in the value
     * @param ccmHuAttributeStruct struct that provides the HVAC parameter information and the update value of that parameter
     */
    virtual void asyncCcmHuParameterCb(const CcmPresTypes::tCcmHu ccmHuAttributeStruct)=0;

    /**
     * @brief asyncGetCcmInfoCb the async callback is invoked to get all the values from service
     * @param callStatus provides the status of the async call made
     * @param struct that provides the HVAC parameter information and the corresponding values
     */
      virtual void asyncGetCcmInfoCb(const CommonAPI::CallStatus&, const CcmPresTypes::CcmInfo&)=0;

    /**
     * @brief CallBack method to get notified about the availability status of HVAC Proxy
     * @param status - status of HVAC proxy whether available or not
     * @return void
     */
    virtual void ccmHuStatusEventCb(CommonAPI::AvailabilityStatus status) =0;

    /**
     * @brief   ccmHuUserInterventionFlagAttributeCb: Callback to be invoked when HU CCM value is changed through user
     *          intervention.
     * @param   ucHuCcmParam: The CCM parameter which has been changed.
     * @return  void.
     */
    virtual void ccmHuUserInterventionFlagAttributeCb(uint8_t ucHuCcmParam) = 0;

};

#endif // IHVACRESOURCE_H



