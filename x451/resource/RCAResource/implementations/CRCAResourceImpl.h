/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CRCAResourceImpl.h
* @ingroup      HMIComponent
* @author       Nishant Khandagale
* CRCAResourceImpl, Resource Implementation for the RCA module. Implements the IRCAResource interface
*/

#ifndef CRCARESOURCEIMPL_H
#define CRCARESOURCEIMPL_H

#include "interfaces/IRCAResource.h"
#include "v1/com/harman/dcif/RCAServiceProxy.hpp"
#include "CRCAEventProvider.h"
#include <capi/CAPIClientAbstraction.hpp>

using namespace std;
using namespace v1::com::harman::dcif;

class CRCAEventProvider;

/**
 * @brief The CRCAResourceImpl, Resource Implementation for the RCA module. Implements the IRCAResource interface
 */
class CRCAResourceImpl: public IRCAResource
{
public:
    virtual ~CRCAResourceImpl();

    /**
     * @brief getRCAEventProvider: Method to get the instance of the RCA event provider
     * @param void
     * @return the pointer to the RCA event provider
     */
    CRCAEventProvider* getRCAEventProvider();

    /**
     * @brief rcaProxyStatusCb: CallBack method to get notified about the availability status of RCA Proxy
     * @param eStatus: status of RCA proxy whether available or not
     * @return void
     */
    void rcaProxyStatusCb(CommonAPI::AvailabilityStatus eStatus) override;

    /**
     * @brief onRCAActionInitiatedCb: this subscribe callback is invoked when any of the RCA action has initiated
     * @param eRCAActionInitiated: enum that provides the initiated RCA action
     * @param uiIntInfo: int data (used only for PV right now)
     * @return void
     */
    void onRCAActionInitiatedCb(const RCAServiceTypes::eActionInitiated eRCAActionInitiated, uint16_t uiIntInfo) override;

    /**
     * @brief setHMIMediaBrowseStatusAsyncCb: the async callback is invoked when HMI browse status is changed
     * @param eCallStatus: provides the status of the async call made
     * @return void
     */
    void setHMIMediaBrowseStatusAsyncCb(const CommonAPI::CallStatus& eCallStatus) override;

    /**
     * @brief setHMIMediaBrowseStatusAsyncReq: Request method to set the HMI media browse status
     * @param bIsHMIInBrowseState: status of HMI media browse status
     *        (true : HMI is in media browse state, false : HMI is not in media browse state)
     * @return void
     */
    void setHMIMediaBrowseStatusAsyncReq(bool bIsHMIInBrowseState) override;

private:
    CRCAResourceImpl();

    /**
     * @brief ResourceFactory: Adding ResourceFactory class as friend class so that
     * ResourceFactory shall be able to create the instance of this class.
     */
    friend class ResourceFactory;

    /**
     * @brief subscribeToCcmHuProxy: Method to subscribe CallBack methods to events provided by RCA proxy
     * @param void
     * @return void
     */
    void subscribeToRCAProxy();

    /**
     * @brief m_pRCAEventProvider: Instance of CRCAEventProvider to propogate events to RCA application layer
     */
    CRCAEventProvider* m_pRCAEventProvider;

    /**
     * @brief m_RCAProxy: RCAServiceProxy class object to call RCA layer Proxy methods
     */
    CAPIClientAbstraction<RCAServiceProxy> m_RCAProxy;

    /**
     * @brief m_bRCAProxyAvailable: provides information whether the RCA proxy is available or not
     */
    bool m_bRCAProxyAvailable;

};

#endif //CRCARESOURCEIMPL_H
