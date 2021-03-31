/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/
#ifndef V0_COM_HARMAN_HMI_hmi_VR_STUB_DEFAULT_HPP_
#define V0_COM_HARMAN_HMI_hmi_VR_STUB_DEFAULT_HPP_


#include <v0/com/harman/hmi/hmiVRStub.hpp>
#include <sstream>

namespace v0 {
namespace com {
namespace harman {
namespace hmi {

/**
 * Provides a default implementation for hmiVRStubRemoteEvent and
 * hmiVRStub. Method callbacks have an empty implementation,
 * remote set calls on attributes will always change the value of the attribute
 * to the one received.
 *
 * Override this stub if you only want to provide a subset of the functionality
 * that would be defined for this service, and/or if you do not need any non-default
 * behaviour.
 */
class hmiVRStubDefault
    : public virtual hmiVRStub {
public:
    hmiVRStubDefault();

    hmiVRStubRemoteEvent* initStubAdapter(const std::shared_ptr<hmiVRStubAdapter> &_adapter);

    const CommonAPI::Version& getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> _client);


    /**
     * description: Method to be invoked to display teleprompter list in HMI.
     */
    virtual void showTelePrompterList(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector<std::string> _strAryTelePrompterlist, showTelePrompterListReply_t _reply);
    /**
     * description: Method to be invoked to display picklist in HMI.
     */
    virtual void showPickList(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector<std::string> _strAryPicklist, std::string _strContextTitle, showPickListReply_t _reply);
    /**
     * description: Method to be invoked to display picklist in HMI.
     */
    virtual void showPickList(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector<std::string> _strAryPicklist, showPickList1Reply_t _reply);
    /**
     * description: Method to be invoked to remove the picklist from HMI.
     */
    virtual void hidePickList(const std::shared_ptr<CommonAPI::ClientId> _client, hidePickListReply_t _reply);
    /**
     * description: Method to be invoked to select an item from the pick list.
     */
    virtual void setFocusedItem(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _iLineNo, setFocusedItemReply_t _reply);
    /**
     * description: Method to be invoked to switch to the required HMI screen.
     */
    virtual void setScreen(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _strScreenName, setScreenReply_t _reply);
    /**
     * description: Method to be invoked to switch to different categories during media browse.
     */
    virtual void mediaFilterListShow(const std::shared_ptr<CommonAPI::ClientId> _client, ::v0::com::harman::hmi::hmiVRTypes::EFilterIDType _eFilterType, int64_t _iFilterId, mediaFilterListShowReply_t _reply);
    /**
     * description: Method to be invoked to display contact details of the particular contact.
     */
    virtual void showContact(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _strDatabaseType, int32_t _iContactId, showContactReply_t _reply);
    /**
     * description: Method to be invoked to set the focus on a particular category.
     */
    virtual void focusSelectedCategory(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _strCategory, focusSelectedCategoryReply_t _reply);

/**
 * description: Signal shall be broadcast to activate VR.
 */
virtual void fireActivateVREvent(const ::v0::com::harman::hmi::hmiVRTypes::EKeyState &_eKeyState, const ::v0::com::harman::hmi::hmiVRTypes::EScreenName &_eScreenName);
/**
 * description: Signal shall be broadcast to activate VR.
 */
virtual void fireActivateVREvent(const ::v0::com::harman::hmi::hmiVRTypes::EKeyState &_eKeyState);
/**
 * description: Signal shall be broadcast to de-activate VR.
 */
virtual void fireCancelVREvent();
/**
 * description: Signal shall be broadcast when ever any pick list item is selected from HMI.
 */
virtual void fireListItemTouchEvent(const int32_t &_iFocusedItem);


protected:
    class RemoteEventHandler: public virtual hmiVRStubRemoteEvent {
    public:
        RemoteEventHandler(hmiVRStubDefault *_defaultStub);


    private:
        hmiVRStubDefault *defaultStub_;
    };
private:
    hmiVRStubDefault::RemoteEventHandler remoteEventHandler_;


    CommonAPI::Version interfaceVersion_;
};

} // namespace hmi
} // namespace harman
} // namespace com
} // namespace v0


// Compatibility
namespace v0_1 = v0;

#endif // V0_COM_HARMAN_HMI_hmi_VR_STUB_DEFAULT
