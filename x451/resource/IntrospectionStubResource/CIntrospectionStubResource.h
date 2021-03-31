/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CIntrospectionStubResource.h
* @ingroup      HMIComponent
* @author       Gaurav Garg
* CIntrospectionStubResource, Resource for the Introspection Service module that will be used to receive introspection related data from adaptor.
*/

#ifndef CINTROSPECTIONSTUBRESOURCE_H
#define CINTROSPECTIONSTUBRESOURCE_H

#if defined(PLATFORM_WIN32) || defined(PLATFORM_LINUX_X86)
#define USE_SIMULATION_INTROSPECTION
#endif // defined(PLATFORM_WIN32) || defined(PLATFORM_LINUX_X86)

#include "implementations/CIntrospectionStubResourceImpl.h"
#include "CIntrospectionEnum.h"

using namespace std;
class CIntrospectionStubResourceImpl;

class CIntrospectionStubResource
{
public:


    /**
     * @brief setScreenChange: Call the broadcast method for screenChange signal to send the changed screen name as signal information
     * @param strScreenName: string of last changed screen's object name
     * @param itemType: The type of item - screen, drawer, popup
     * @return void
     */
    void setScreenChange(const string& strScreenName, EItemType eItemType);

    /**
      * @brief sendScreenInfo: Call the method for the data containing information regarding the current screen
      * @param strScreenInfo: string of screen information
      * @return void
      */
    void sendScreenInfo(const string& strScreenInfo);

    /**
     * @brief getIntrospectionStubEventProvider: Method to get the instance of the Introspection event provider
     * @param void
     * @return the pointer to the Introspection event provider
     */
    CIntrospectionEventProvider* getIntrospectionStubEventProvider();

private:

    CIntrospectionStubResource();

    ~CIntrospectionStubResource();

    /**
     * @brief Adding ResourceFactory class as friend class so that
     * ResourceFactory shall be able to create the instance of this class.
     */
    friend class ResourceFactory;

    /** shared ptr for the stub impl file to start the introspection service */
    shared_ptr<CIntrospectionStubResourceImpl>  m_pIntrospectionStubResourceImpl;

};

#endif // CINTROSPECTIONSTUBRESOURCE_H
