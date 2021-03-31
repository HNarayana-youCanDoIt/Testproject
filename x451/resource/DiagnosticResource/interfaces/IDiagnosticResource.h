/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         IDiagnosticResource.h
* @ingroup      HMIComponent
* @author       Manali Patil
* IDiagnosticResource, an interface for Diagnostic Resource Implementaion in HMI
*/

#ifndef IDIAGNOSTICRESOURCE_H
#define IDIAGNOSTICRESOURCE_H

#include <string>
#include <capi/CAPIClientAbstraction.hpp>
#include "v0/com/harman/diagnosticservice/DiagnosticServiceProxy.hpp"

using namespace v0::com::harman::diagnosticservice;

/**
*   @brief The IDiagnosticResource class
*   This interface provides functionality which interacts with the below PresCtrl or Resource proxy directly.
*   It also provides functionality via which data can be provided to the upper layer.
*/
class IDiagnosticResource
{
public:
    virtual ~IDiagnosticResource(){}

    /*****  Request METHODS  ****************************/



//    /*****  CALL BACK METHODS  ****************************/

    /**
    * @brief	diagnosticStatusCb : This is a callback method for Diagnostic proxy status event.
    * @param	eAvailabilityStatus: Diagnostic proxy status available or not
    * @return	void
    */
    virtual void diagnosticStatusCb(CommonAPI::AvailabilityStatus eAvailabilityStatus ) = 0;

    /**
     * @brief getDiagAmFmAntennaStatusCb() : callback for Am/Fm antenna status.
     * @param - eAntennaConnectionState: Antenna connection state whether connected/disconnected/Not known
     * @return - void
     */
    virtual void getDiagAmFmAntennaStatusCb(const diagTypedefs::eDiagConnectionState & eAntennaConnectionState) = 0;

    /**
     * @brief getDiagSWCStatusCb() : callback for SWC status.
     * @param - eSWCConnectionState: SWC connection state whether connected/disconnected/Not known
     * @return - void
     */
    virtual void getDiagSWCStatusCb(const diagTypedefs::eDiagConnectionState & eSWCConnectionState) = 0;

    /**
     * @brief getDiagMICStatusCb() : callback for Mic status.
     * @param - eMicConnectionState: MIC connection state whether connected/disconnected/Not known
     * @return - void
     */
    virtual void getDiagMICStatusCb(const diagTypedefs::eDiagConnectionState & eMicConnectionState) = 0;

    /**
     * @brief getDiagAmFmAntennaConnectionStatusValue: return the Am/Fm connection status value.
     * @param void.
     * @return m_iAmFmConnectionStatusValue: Am/Fm connection status value
     */
    virtual int getDiagAmFmAntennaConnectionStatusValue() = 0;

    /**
     * @brief getDiagSWCConnectionStatusValue: return the SWC connection status value.
     * @param void.
     * @return m_iSwcConnectionStatusValue: SWC connection status value
     */
    virtual int getDiagSWCConnectionStatusValue() = 0;

    /**
     * @brief getDiagMICConnectionStatusValue: return the Mic connection status value
     * @param void.
     * @return m_iMicConnectionStatusValue : Mic connection status value
     */
    virtual int getDiagMICConnectionStatusValue() = 0;

};

#endif // IVERSIONMANAGERRESOURCE_H
