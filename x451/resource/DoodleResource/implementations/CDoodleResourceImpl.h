/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CDoodleResourceImpl.h
 * @ingroup       HMIComponent
 * @author        Nandkishor Lokhande
 * CDoodleResourceImpl, Resource Implementation for Doodle.
 */
//________________________________________________________________________________________________
#ifndef CDOODLERESOURCEIMPL_H
#define CDOODLERESOURCEIMPL_H

#include <capi/CAPIClientAbstraction.hpp>
#include "interfaces/IDoodleResource.h"
#include "CDoodleEventProvider.h"

//________________________________________________________________________________________________
/*!
 * @class   CDoodleResourceImpl
 * @brief   This class provides methods to communicate with the Doodle proxy directly
 * which are inherited from IDoodleResource interface.
 */
class CDoodleResourceImpl : public IDoodleResource
{
public:
    //// Methods specific for IDoodleResource class

    /**
    * @brief    CDoodleResourceImpl: constructor for CDoodleResourceImpl.
    * @param    NA.
    * @return   NA.
    */
    CDoodleResourceImpl();

    /**
    * @brief    ~CDoodleResourceImpl: destructor for CDoodleResourceImpl.
    * @param    NA.
    * @return   NA.
    */
    virtual ~CDoodleResourceImpl();
    //________________________________________________________________________________________________
    /**
    * @brief    getEventProvider: getter method to get Doodle event provider object.
    * @param    void.
    * @return   CDoodleEventProvider object pointer.
    */
    CDoodleEventProvider *getEventProvider();
    //________________________________________________________________________________________________

public:
    //// Methods specific for IDoodleResource class

    /**
     * @brief   getProxyAvailabilityStatus: method to get Doodle proxy availability status
     * @param   void
     * @return  bool true when Doodle proxy available otherwise false
     */
    bool getProxyAvailabilityStatus() override;
    //________________________________________________________________________________________________

private:
    //// Call back methods specific for IDoodleResource class

    /**
     * @brief   doodleProxyStatusCb: CallBack method to get notified about the availability status of Doodle Proxy
     * @param   eStatus: status of Doodle proxy whether available or not
     * @return  void
     */
    void doodleProxyStatusCb(CommonAPI::AvailabilityStatus eStatus) override;
    //________________________________________________________________________________________________

private:
    //// Internal Methods specific for IDoodleResource class

    /**
     * @brief   subscribeDoodleProxy: method to subscribe Doodle proxy signals.
     * @param   void.
     * @return  void.
     */
    void subscribeDoodleProxy();
    //________________________________________________________________________________________________
    /**
     * @brief   unSubscribeDoodleProxy: method to un-subscribe Doodle proxy signals.
     * @param   void.
     * @return  void.
     */
    void unSubscribeDoodleProxy();
    //________________________________________________________________________________________________

private:

    /**
    * @brief ResourceFactory: Adding ResourceFactory class as friend class so that
    * ResourceFactory shall be able to create the instance of this class.
    */
    friend class ResourceFactory;
    //________________________________________________________________________________________________

    //// DoodleServiceProxy class object to call DriveNext proxy methods **/
    //CAPIClientAbstraction<doodleProxy> m_objDoodleProxy;

    //// m_pEventProvider: pointer to CDoodleEventProvider class instance.
    CDoodleEventProvider* m_pEventProvider;

    //// m_bProxyAvailability: bool veriable to hold Doodle porxy available status.
    bool m_bProxyAvailability;

    //________________________________________________________________________________________________
};

#endif // CDOODLERESOURCEIMPL_H
