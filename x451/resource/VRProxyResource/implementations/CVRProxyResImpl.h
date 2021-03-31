/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
***************************************************************
*/
/**
* @file         CVRProxyResImpl.h
* @ingroup      HMIComponent
* @author       Rahul Singh Parihar
* @brief        CVRProxyResImpl will be an interface to communicate to VR service
* and to pass on the information to upper layers.
*/

#ifndef CVRPROXYRESIMPL_H
#define CVRPROXYRESIMPL_H

#include <capi/CAPIClientAbstraction.hpp>
#include "interfaces/IVRProxyResource.h"
#include "CVRProxyEventProvider.h"

/*!
 * @class CVRProxyResImpl - Derived from IVRProxyResource interface
 */
class CVRProxyResImpl: public IVRProxyResource
{
public:

    /**
     * @brief   getVRProxyEventProvider - Method to get the instance of CVRProxyEventProvider class.
     * @param   void.
     * @return  pointer to the object of CVRProxyEventProvider class.
     */
    CVRProxyEventProvider* getVRProxyEventProvider();

private:
    /*!
     * @brief Adding ResourceFactory class as friend class so that
     * ResourceFactory shall be able to create the instance of this class.
     */
    friend class ResourceFactory;

    /**
     * @brief CVRProxyResImpl - Constructor of CVRProxyResImpl class
     */
    CVRProxyResImpl();

    /**
     * @brief ~CVRProxyResImpl - Destructor of CVRProxyResImpl class
     */
    virtual ~CVRProxyResImpl();

    /******************************************************//**
     * @category CALLBACK
     *******************************************************/
    /**
     * @brief   onVRProxyStatusCb - Callback to get notified about the avalability status of the UISpeechIntfProxy.
     * @param   eAvailabilityStatus - status of UISpeechIntfProxy whether available or not.
     * @return  void.
     */
    void onVRProxyStatusCb(AvailabilityStatus eAvailabilityStatus);

    /**
     * @brief   onVRStateAttributeCb - Callback to get notified about the VR state change.
     * @param   eVRState - state of voice recognition.
     * @return  void.
     */
    void onVRStateAttributeCb(UISSTypes::eVRStateEnum eVRState) override;

    /**
     * @brief   onVRDialogStateAttributeCb - Callback to get notified about the VR dialog state change.
     * @param   eVRState - state of voice recognition dialog whether active or inactive.
     * @return  void.
     */
    void onVRDialogStateAttributeCb(UISSTypes::eVRDialogActive eVRDialogState) override;

    /**
     * @brief   onVRAvailableStateAttributeCb - Callback to get notified about the VR availability state change.
     * @param   objVRAvailableState - availability state of voice recognition whether available or not.
     * @return  void.
     */
    void onVRAvailableStateAttributeCb(UISSTypes::sVRAvailable objVRAvailableState) override;

    /******************************************************//**
     * @category INTERNAL METHODS
     *******************************************************/
    /**
     * @brief   subscribeVRProxyCb - Internal method to subscribe all the callback methods.
     * @param   void.
     * @return  void.
     */
    void subscribeVRProxyCb();


/******************************************************//**
 * @category PROPERTIES
 *******************************************************/
private:
    /**
     * @brief Instance of BtManagerExtProxy class to communicate with
     * bt press plugin layer.
     */
    CAPIClientAbstraction<UISpeechIntfProxy>    m_objVRProxy;
    /**
     * @brief Pointer of CVRProxyEventProvider class to
     * emit signals to the VR adaptor layer.
     */
    CVRProxyEventProvider*                      m_pVRProxyEventProvider;
    //! Flag to maintain VR proxy availability status
    bool                                        m_bIsVRProxyAvailable;
    //! Enum to hold current VR state
    UISSTypes::eVRStateEnum                     m_eVRState;
    //! Enum to hold VR dialog state
    UISSTypes::eVRDialogActive                  m_eVRDialogState;
};

#endif // CVRPROXYRESIMPL_H
