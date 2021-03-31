/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CDiagnosticResourceImpl.h
* @ingroup      HMIComponent
* @author       Manali Patil
* CDiagnosticResourceImpl, Resource Implementation for Diagnostic
*/
#ifndef CDIAGNOSTICRESOURCEIMPL_H
#define CDIAGNOSTICRESOURCEIMPL_H

#include "resource/DiagnosticResource/interfaces/IDiagnosticResource.h"
#include "CDiagnosticEventProvider.h"

using namespace v0::com::harman::diagnosticservice;

/**
 * @brief The CDiagnosticResourceImpl class is Resource Implementation for Diagnostic Resource
 */
class CDiagnosticResourceImpl: public IDiagnosticResource
{
public:

    /**
    * @brief	Destructor
    * @param	void
    * @return	None
    */
    virtual ~CDiagnosticResourceImpl();

    /**
    * @brief	This function is returns the pointer to CDiagnosticEventProvider
    * @param    void
    * @return	CDiagnosticEventProvider* : Pointer to CDiagnosticEventProvider instance
    */
    CDiagnosticEventProvider* getDiagnosticEventProvider();

    /**
    * @brief	Constructor
    * @param	void
    * @return	None
    */
    CDiagnosticResourceImpl();

private:

    /**
    * @brief	diagnosticStatusCb: This is a callback method for Diagnostic proxy status event.
    * @param	eAvailabilityStatus: Diagnostic proxy status available or not
    * @return	void
    */
    void diagnosticStatusCb(CommonAPI::AvailabilityStatus eAvailabilityStatus) override;

    /**
     * @brief getDiagAmFmAntennaStatusCb() :  callback for Am/Fm antenna status.
     * @param - eAntennaConnectionState: Antenna connection state whether connected/disconnected/Not known
     * @return - void
     */
    void getDiagAmFmAntennaStatusCb(const diagTypedefs::eDiagConnectionState & eAntennaConnectionState) override;

    /**
     * @brief getDiagSWCStatusCb() :  callback for SWC status.
     * @param - eSWCConnectionState: SWC connection state whether connected/disconnected/Not known
     * @return - void
     */
    void getDiagSWCStatusCb(const diagTypedefs::eDiagConnectionState & eSWCConnectionState) override;

    /**
     * @brief getDiagMICStatusCb() :  callback for Mic status.
     * @param - eMicConnectionState: MIC connection state whether connected/disconnected/Not known
     * @return - void
     */
    void getDiagMICStatusCb(const diagTypedefs::eDiagConnectionState & eMicConnectionState) override;

    /**
     * @brief getDiagAmFmAntennaConnectionStatusValue: return the Am/Fm connection status value.
     * @param void.
     * @return m_iAmFmConnectionStatusValue: Am/Fm connection status value
     */
    int getDiagAmFmAntennaConnectionStatusValue() { return m_iAmFmConnectionStatusValue ; }

    /**
     * @brief getDiagSWCConnectionStatusValue: return the SWC connection status value.
     * @param void.
     * @return m_iSwcConnectionStatusValue: SWC connection status value
     */
    int getDiagSWCConnectionStatusValue() { return m_iSwcConnectionStatusValue ; }

    /**
     * @brief getDiagMICConnectionStatusValue: return the Mic connection status value
     * @param void.
     * @return m_iMicConnectionStatusValue : Mic connection status value
     */
    int getDiagMICConnectionStatusValue() { return m_iMicConnectionStatusValue ; }

private:

    friend class ResourceFactory;

    /**
    * @brief	subscribeDiagnosticProxy: This function subscribes to the service of Diagnostic service
    * @param    void
    * @return	void
    */
    void subscribeDiagnosticProxy();

    /* Instance of the CDiagnosticEventProvider to emit signals to the upper layer */
    CDiagnosticEventProvider* m_pDiagnosticEventProvider;

    /* DiagnosticProxy class object to call Diagnostic proxy methods */
    CAPIClientAbstraction<DiagnosticServiceProxy> m_DiagnosticProxy;

    /**
     * @brief m_iAmFmConnectionStatusValue
     */
    int m_iAmFmConnectionStatusValue;

    /**
     * @brief m_iSwcConnectionStatusValue
     */
    int m_iSwcConnectionStatusValue;

    /**
     * @brief m_iMicConnectionStatusValue
     */
    int m_iMicConnectionStatusValue;

};

#endif //CDIAGNOSTICRESOURCEIMPL_H
