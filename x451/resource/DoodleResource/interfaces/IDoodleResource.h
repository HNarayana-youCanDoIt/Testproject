/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          IDoodleResource.h
 * @ingroup       HMIComponent
 * @author        Nandkishor Lokhande
 * CDoodleResourceImpl, an interface for Doodle Resource Implementation in HMI.
 */
//________________________________________________________________________________________________
#ifndef IDOODLERESOURCE_H
#define IDOODLERESOURCE_H

//#include "v0/com/harman/drivepro/doodleProxy.hpp"
#include "../implementations/CDoodleResourceData.h"

using namespace std;
//using namespace v0::com::harman::DoodlePresCtrl;
//________________________________________________________________________________________________
/*!
 * @interface   IDoodleResource
 * @brief       This interfaces provides abstract methods to communicate with the Doodle proxy directly
 *              which shall be implemented by resource implementation class.
 */
class IDoodleResource
{
public:

    /**
    * @brief    ~IDoodleResource: destructor for IDoodleResource.
    * @param    NA.
    * @return   NA.
    */
    virtual ~IDoodleResource(){}
    //________________________________________________________________________________________________

private:
    //// Methods specific for IDoodleResource class

    /**
     * @brief   getProxyAvailabilityStatus: method to get Doodle proxy availability status
     * @param   void
     * @return  bool true when Doodle proxy available otherwise false
     */
    virtual bool getProxyAvailabilityStatus() = 0;
    //________________________________________________________________________________________________

private:
    //// Call back methods specific for IDoodleResource class

    /**
     * @brief   DoodleProxyStatusCb: CallBack method to get notified about the availability status of Doodle Proxy
     * @param   eStatus: status of Doodle proxy whether available or not
     * @return  void
     */
    virtual void doodleProxyStatusCb(CommonAPI::AvailabilityStatus eStatus) = 0;
    //________________________________________________________________________________________________
};

#endif // IDOODLERESOURCE_H
