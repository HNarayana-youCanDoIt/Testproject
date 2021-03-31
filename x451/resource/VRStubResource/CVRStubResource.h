/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CVRStubResource.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CVRStubResource class that shall create object of CVRStubResourceImpl
 * class and shall register it as a service. It shall also behave as a mediator between upper layer(VR adaptor)
 * and lower layer (VR Stub).
 */

#ifndef CVRSTUBRESOURCE_H
#define CVRSTUBRESOURCE_H

#include "implementations/CVRStubResourceImpl.h"
#include "implementations/CHardkeyEnums.h"

/**
 * @class   CVRStubResource
 */
class CVRStubResource
{
public:

    /**
     * @brief   getVRStubResourceImpl: Method to get raw pointer of type CVRStubResourceImpl pointing
     *          to the object of CVRStubResourceImpl class.
     * @param   void.
     * @return  raw pointer of type CVRStubResourceImpl.
     */
    CVRStubResourceImpl* getVRStubResourceImpl(){ return m_pVRStubResourceImpl.get(); }

    /**
     * @brief   activateVRSession: Method to be called to broadcast signal to activate VR session.
     * @param   iKeyState: state of the PTT key pressed.
     *          eScreenId: screen ID which is activating the VR (Default argument is EN_SCREEN_DEFAULT).
     * @return  void.
     */
    void activateVRSession(int iKeyState, EVRScreenID eScreenId = EVRScreenID::EN_SCREEN_DEFAULT);

    /**
     * @brief   deactivateVRSession: Method to be called to broadcast signal to deactivate VR session.
     * @param   void.
     * @return  void.
     */
    void deactivateVRSession();

    /**
     * @brief   listItemSelected: Method to be called to broadcast listItemTouch event whenever any list
     *          item is selected suring VR session and needs to be infor to VR service.
     * @param   iLineNo: List index of the item.
     * @return  void.
     */
    void listItemSelected(int32_t iLineNo);

    /**
     * @brief   sendVRResponse: Method to be invoked to send the response of a request
     * @param   eResponseType: Response type of the request.
     * @return  void.
     */
    void sendVRResponse(EResponseType eResponseType);    

private:

    /**
     * @brief CVRStubResource: Constructor of CVRStubResource.
     * @param void.
     * @return void.
     */
    CVRStubResource();

    /**
     * @brief ~CVRStubResource: Destructor of CVRStubResource.
     * @param void.
     * @return void.
     */
    ~CVRStubResource();

    /**
     * @brief getVRKeyState: Internal method to be called to get VR key state from EHardKeyState.
     * @param eKeyState: state of PTT key (short release or long press).
     * @return VR key state to be sent as a param while broadcasting signal to activate VR session.
     */
    hmiVRTypes::EKeyState getVRKeyState(EHardKeyState eKeyState);

    /**
     * @brief getVRScreenName: Internal method to be called to get VR Screen Name from EVRScreenID.
     * @param eScreenId: Screen ID.
     * @return VR Screen Name to be sent as a param while broadcasting signal to activate VR session.
     */
    hmiVRTypes::EScreenName getVRScreenName(EVRScreenID eScreenId);

/******************************************************//**
 * @category PROPERTIES
 *******************************************************/
private:

    /*!
     * @brief Adding ResourceFactory class as friend class so that
     * ResourceFactory shall be able to create the instance of this class.
     */
    friend class ResourceFactory;

    //!Shared pointer to store refernce count of CVRStubResourceImpl object
    shared_ptr<CVRStubResourceImpl> m_pVRStubResourceImpl;
};

#endif // CVRSTUBRESOURCE_H
