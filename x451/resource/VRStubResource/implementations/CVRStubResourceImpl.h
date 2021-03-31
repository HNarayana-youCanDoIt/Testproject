/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CVRStubResourceImpl.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CVRStubResourceImpl class that is derived from hmiVRStubDefault class
 * and which shall implement hmiVRStub request methods
 */

#ifndef CVRSTUBRESOURCEIMPL_H
#define CVRSTUBRESOURCEIMPL_H

//!Include the headers related to VRStub
#include "v0/com/harman/hmi/hmiVRStubDefault.hpp"
#include "implementations/CVRStubEventProvider.h"
#include "CVRStubResourceEnum.h"

using namespace v0::com::harman::hmi;
using namespace std;

/**
 * @class   CVRStubResourceImpl
 */
class CVRStubResourceImpl : public hmiVRStubDefault
{
public:
    /**
     * @brief    CVRStubResourceImpl: Constructor of CVRStubResourceImpl.
     * @param    NA.
     * @return   NA.
     */
    CVRStubResourceImpl();

    /**
     * @brief    ~CVRStubResourceImpl: Destructor of CVRStubResourceImpl.
     * @param    NA.
     * @return   NA.
     */
    virtual ~CVRStubResourceImpl();

    /*!
     * @brief   getVRStubEventProvider: Method to get the instance of CVRStubEventProvider class.
     * @param   void.
     * @return  pointer to the object of CVRStubEventProvider class.
     */
    CVRStubEventProvider* getVRStubEventProvider();

    /**
     * @brief   getPickList: Method to get picklist.
     * @param   void.
     * @return  list of pick list items.
     */
    const vector<string>& getPickList() { return m_vectPickList; }

    /**
     * @brief   getTeleprompterList: Method to get teleprompter list.
     * @param   void.
     * @return  list of teleprompter list items.
     */
    const vector<string>& getTeleprompterList() { return m_vectTeleprompterList; }

    /**
     * @brief   sendVRResponse: Method to be invoked to send the response back to the caller for a particular request
     * @param   eResponseType: Response type of the request.
     * @return  void.
     */
    void sendVRResponse(EResponseType eResponseType);

    /**
     * @brief   setScreen: Method to be invoked to switch to the required HMI screen.
     * @param   _client: It is used to identify the caller invoking this method within a stub.
     * @param   _strScreenName: Screen name that HMI requires to display(switch).
     * @param   _reply: Response whether the method call is successful or not.
     * @return  void.
     */
    void setScreen(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _strScreenName, setScreenReply_t _reply) override;

    /**
     * @brief   setScreen: Method to be invoked to display contact details of the particular contact.
     * @param   _client: It is used to identify the caller invoking this method within a stub.
     * @param   _strDatabaseType: Phone database type.
     * @param   _iContactId: Contact id of the contact for which contact details has to be displayed.
     * @param   _reply: Response whether the method call is successful or not.
     * @return  void.
     */
    void showContact(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _strDatabaseType, int32_t _iContactId, showContactReply_t _reply) override;

    /**
     * @brief   showTelePrompterList: Method to be invoked to display teleprompter list in HMI.
     * @param   _client: It is used to identify the caller invoking this method within a stub.
     * @param   _strAryTelePrompterlist: List of the items to be shown in teleprompter list.
     * @param   _reply: Response whether the method call is successful or not.
     * @return  void.
     */
    void showTelePrompterList(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector<std::string> _strAryTelePrompterlist, showTelePrompterListReply_t _reply) override;

    /**
     * @brief   showPickList: Method to be invoked to display picklist in HMI.
     * @param   _client: It is used to identify the caller invoking this method within a stub.
     * @param   _strAryPicklist: List of the items to be shown in picklist.
     * @param   _reply: Response whether the method call is successful or not.
     * @param   _strContextTitle: Context title for provided pick list
     * @return  void.
     */
    void showPickList(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector<std::string> _strAryPicklist, std::string _strContextTitle, showPickListReply_t _reply) override;

    /**
     * @brief   hidePickList: Method to be invoked to remove the picklist from HMI.
     * @param   _client: It is used to identify the caller invoking this method within a stub.
     * @param   _reply: Response whether the method call is successful or not.
     * @return  void.
     */
    void hidePickList(const std::shared_ptr<CommonAPI::ClientId> _client, hidePickListReply_t _reply) override;

    /**
     * @brief   setFocusedItem: Method to be invoked to select an item from the pick list.
     * @param   _client: It is used to identify the caller invoking this method within a stub.
     * @param   _iLineNo: Line number to be highligted.
     * @param   _reply: Response whether the method call is successful or not.
     * @return  void.
     */
    void setFocusedItem(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _iLineNo, setFocusedItemReply_t _reply) override;

    /**
     * @brief   focusSelectedCategory: Method to be invoked to set the focus on a particular category.
     * @param   _client: It is used to identify the caller invoking this method within a stub.
     * @param   _strCategory: Category on which the focus has to be set.
     * @param   _reply: Response whether the method call is successful or not.
     * @return  void.
     */
    void focusSelectedCategory(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _strCategory, focusSelectedCategoryReply_t _reply) override;

    /**
     * @brief   mediaFilterListShow: Method to be invoked to switch to different categories during media browse.
     * @param   _client: It is used to identify the caller invoking this method within a stub.
     * @param   _eFilterType: media browse category type to be browsed.
     * @param   _iFilterId: media browse category id to fetch data for a selected item. If -1 then show all the content
     *          of the media categroy otherwise show the content of the passed filterId.
     * @param   _reply: Response whether the method call is successful or not.
     * @return  void.
     */
    virtual void mediaFilterListShow(const std::shared_ptr<CommonAPI::ClientId> _client, hmiVRTypes::EFilterIDType _eFilterType, int64_t _iFilterId, mediaFilterListShowReply_t _reply) override;

private:

    /**
     * @brief   setRequestState: Internal method to set VR request state.
     * @param   eVRRequestState: VR request state to be stored.
     * @return  void.
     */
    void setRequestState(EVRRequestState eVRRequestState);

    /**
     * @brief   getResponseType: Internal method to get VR response type from the HMI response type
     * @param   eResponseType: HMI response type of the request
     * @return  VR response type to be send to the caller for a request
     */
    hmiVRTypes::EResponseType getResponseType(EResponseType eResponseType);

    //!Pointer of type CVRStubEventProvider to emit signals to the upper layer
    CVRStubEventProvider*           m_pVREventProvider;
    //! Data to hold address of setScreenReply method
    setScreenReply_t                m_objSetScreenReply;
    //! Data to hold address of showContactReply method
    showContactReply_t              m_objShowContactReply;
    //! Data to hold address of mediaFilterListShowReply method
    mediaFilterListShowReply_t      m_objMediaFilterListShowReply;
    //! Data to hold the current request state
    EVRRequestState                 m_eVRRequestState;
    //! List of items to be shown in picklist
    vector<string>                  m_vectPickList;
    //! List of items to be shown in teleprompter list
    vector<string>                  m_vectTeleprompterList;
};

#endif // CVRSTUBRESOURCEIMPL_H
