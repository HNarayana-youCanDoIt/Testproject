/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CHVACResourceImpl.h
* @ingroup      HMIComponent
* @author       Mohit Rajani
* CHVACResourceImpl, Resource Implementation for the HVAC module. Implements the IHVACResource interface
*/

#ifndef CHVACRESOURCEIMPL_H
#define CHVACRESOURCEIMPL_H

#include "interfaces/IHVACResource.h"
#include "v0/com/harman/dcif/CcmHuProxy.hpp"
#include "v0/com/harman/dcif/CcmPresTypes.hpp"
#include "CHVACEventProvider.h"
#include <capi/CAPIClientAbstraction.hpp>
#include "CHVACData.h"

using namespace std;
using namespace v0::com::harman::dcif;

class CHVACEventProvider;

/**
 * @brief The * CHVACResourceImpl, Resource Implementation for the HVAC module. Implements the IHVACResource interface
 */
class CHVACResourceImpl: public IHVACResource
{
public:
    virtual ~CHVACResourceImpl();

    /**
     * @brief getHVACEventProvider Method to get the instance of the HVAC event provider
     * @param void
     * @return the pointer to the HVAC event provider
     */
    CHVACEventProvider* getHVACEventProvider();

    /**
     * @brief huCcm_req: Call the HVAC (ccm presCtrl) to set the value for a particular HVAC parameter
     * @param eCcmHuParam Enum that defines the HVAC parameter that needs to be set
     * @param uiValue provides the value that needs to be set for the provided HVAC parameter
     * @return void
     */
    void huCcm_req(CcmPresTypes::eHuCcmParam eCcmHuParam, const uint16_t uiValue) override;

    /**
     * @brief getCcmInfo: Call the HVAC (ccm presCtrl) get API to fetch all HVAC parameters
     * @param None
     * @return None
     */
     void getCcmInfo() override;
private:

    /**
     * @brief asyncCcmHuReqCb the async callback that will be invoked once huCcm_reqAsync is completed
     * @param callStatus provides the status of the async call made
     * @return void
     */
    void asyncCcmHuReqCb(const CommonAPI::CallStatus& callStatus) override;

    /**
     * @brief asyncCcmHuParameterCb the async callback is invoked when any of the HVAC parameters has an update in the value
     * @param ccmHuAttributeStruct struct that provides the HVAC parameter information and the update value of that parameter
     * @return void
     */
    void asyncCcmHuParameterCb(const CcmPresTypes::tCcmHu ccmHuAttributeStruct) override;

    /**
     * @brief CallBack method to get notified about the availability status of HVAC Proxy
     * @param status - status of HVAC proxy whether available or not
     * @return void
     */
    void ccmHuStatusEventCb(CommonAPI::AvailabilityStatus status) override;

    /**
     * @brief asyncGetCcmInfoCb the async callback is invoked to get all the values from service
     * @param callStatus provides the status of the async call made
     * @param struct that provides the HVAC parameter information and the corresponding values
     * @return void
     */
    void asyncGetCcmInfoCb(const CommonAPI::CallStatus&, const CcmPresTypes::CcmInfo&) override;

    /**
     * @brief   ccmHuUserInterventionFlagAttributeCb: Callback to be invoked when HU CCM value is changed through user
     *          intervention.
     * @param   ucHuCcmParam: The CCM parameter which has been changed.
     * @return  void.
     */
    void ccmHuUserInterventionFlagAttributeCb(uint8_t ucHuCcmParam) override;

    /**
     * @brief	fetchHVACInfo This method will return HVAC structure.
     * @param	void
     * @return	SHVACParamValues : structure which contains HVAC from CCM service.
     */
    SHVACParamValues fetchHVACInfo();


private:
    CHVACResourceImpl();

    /**
     * @brief Adding ResourceFactory class as friend class so that
     * ResourceFactory shall be able to create the instance of this class.
     */
    friend class ResourceFactory;

    /**
     * @brief subscribeToCcmHuProxy Method to subscribe CallBack methods to events provided by HVAC proxy
     * @param void
     * @return void
     */
    void subscribeToCcmHuProxy();

    /** Instance of CHVACEventProvider to propogate events to the upper layer */
    CHVACEventProvider* m_pHVACEventProvider;

    /** CcmHuProxy class object to call HVAC (Ccm) Player Proxy methods */
    CAPIClientAbstraction<CcmHuProxy> m_ccmHuProxy;

    /** provides information whether the HVAC proxy is available or not */
    bool m_bCcmHuAvailable;

    /** HVAC structure variable, which holds the HVAC info data */
    SHVACParamValues m_objSHVACParamValues;
};

#endif //CHVACRESOURCEIMPL_H
