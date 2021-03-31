/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         IRCAResource.h
* @ingroup      HMIComponent
* @author       Nishant Khandagale
* IRCAResource, an interface for the RCA Resource Implementaion in HMI.
*/

#ifndef IRCARESOURCE_H
#define IRCARESOURCE_H

#include <QVariant>
#include <string>
#include <QString>
#include <QObject>

#include "v1/com/harman/dcif/RCAServiceTypes.hpp"
#include <capi/CAPIClientAbstraction.hpp>

using namespace std;
using namespace v1::com::harman::dcif;

/**
 * @interface IRCAResource
 * @brief     This interface provides functionality that would be implemented to interact
 *            with RCA service and also to provide data to RCA Adaptor Layer
 */
class IRCAResource
{
public:
    virtual ~IRCAResource(){}

    /*****  Request METHODS  ****************************/

    /**
     * @brief setHMIMediaBrowseStatusAsyncReq: Request method to set the HMI media browse status
     * @param bIsHMIInBrowseState: status of HMI media browse status
     *        (true : HMI is in media browse state, false : HMI is not in media browse state)
     * @return void
     */
    virtual void setHMIMediaBrowseStatusAsyncReq(bool bIsHMIInBrowseState) = 0;

    /*****  CALL BACK METHODS  ****************************/

    /**
     * @brief rcaProxyStatusCb: CallBack method to get notified about the availability status of RCA Proxy
     * @param eStatus: status of RCA proxy whether available or not
     * @return void
     */
    virtual void rcaProxyStatusCb(CommonAPI::AvailabilityStatus eStatus) = 0;

    /**
     * @brief onRCAActionInitiatedCb: this subscribe callback is invoked when any of the RCA action has initiated
     * @param eRCAActionInitiated: enum that provides the initiated RCA action
     * @param uiIntInfo: int data (used only for PV right now)
     * @return void
     */
    virtual void onRCAActionInitiatedCb(const RCAServiceTypes::eActionInitiated eRCAActionInitiated, uint16_t uiIntInfo) = 0;

    /**
     * @brief setHMIMediaBrowseStatusAsyncCb: Callback to get notified about setHMIMediaBrowseStatusAsync method response
     * @param eCallStatus: call status of the setHMIMediaBrowseStatusAsync method, whether success or not
     * @return void
     */
    virtual void setHMIMediaBrowseStatusAsyncCb(const CommonAPI::CallStatus& eCallStatus) = 0;
};

#endif // IRCARESOURCE_H



