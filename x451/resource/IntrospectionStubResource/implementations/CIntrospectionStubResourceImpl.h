/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CIntrospectionStubResourceImpl.h
* @ingroup      HMIComponent
* @author       Gaurav Garg
* CIntrospectionStubResourceImpl, Stub Resource Implementation for the Introspection Service module.
*/

#ifndef CINTROSPECTIONSTUBRESOURCEIMPL_H
#define CINTROSPECTIONSTUBRESOURCEIMPL_H

//!Include the headers related to IntrospectionStub
#include "v0/com/harman/dcif/HMIIntrospectionStubDefault.hpp"
#include "CIntrospectionEventProvider.h"

using namespace v0::com::harman::dcif;
using namespace std;

class CIntrospectionStubResourceImpl : public HMIIntrospectionStubDefault
{
public:

    /**
     * @brief CIntrospectionStubResourceImpl Constructor
     * @param void
     * @return NA
     */
    CIntrospectionStubResourceImpl();

    /**
     * @brief ~CIntrospectionStubResourceImpl Destructor
     * @param void
     * @return NA
     */
    virtual ~CIntrospectionStubResourceImpl();

    /**
     * @brief getIntrospectionEventProvider Method to get the instance of the Introspection event provider
     * @param void
     * @return the pointer to the Introspection event provider
     */
    CIntrospectionEventProvider* getIntrospectionEventProvider();

    /**
     * @brief inspectScreen: Method to get the description of topmost screen depending on the screen type enum parameter
     * @param pClient: CommonAPI client
     * @param ScreenItemType: enum to specify the type of object to inspect
     * @param itemName: name of the item that needs to be inspected
     * @param  pReply : CommonAPI reply
     * @return void
     */
    virtual void inspectScreen(const std::shared_ptr<CommonAPI::ClientId> pClient, ::v0::com::harman::dcif::HMIIntrospectionTypes::ScreenItemType screenItemType, std::string itemName, inspectScreenReply_t pReply) override;

    //[ToDo: Failure response case to be handled later]
    /**
    * @brief sendScreenInfo Method to set the Inspect screen data from stub Resource
    * @param strScreenInfo: the information for the screen that needs to be inspected
    * @return void
    */
    void sendScreenInfo(const string& strScreenInfo);

private:

    /** Instance of CIntrospectionEventProvider to propogate events to the upper layer */
    CIntrospectionEventProvider* m_pIntroEventProvider;

    /**  Function pointer to reply call of inspectScreen method */
    inspectScreenReply_t m_pInspectReplyVar;
};

#endif // CINTROSPECTIONSTUBRESOURCEIMPL_H
