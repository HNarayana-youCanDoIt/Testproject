/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/
#ifndef V1_COM_HARMAN_LAYERMANAGER_Layer_Manager_DBUS_PROXY_HPP_
#define V1_COM_HARMAN_LAYERMANAGER_Layer_Manager_DBUS_PROXY_HPP_

#include <v1/com/harman/layermanager/LayerManagerProxyBase.hpp>
#include "v1/com/harman/layermanager/LayerManagerDBusDeployment.hpp"

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/DBus/DBusAddress.hpp>
#include <CommonAPI/DBus/DBusFactory.hpp>
#include <CommonAPI/DBus/DBusProxy.hpp>
#include <CommonAPI/DBus/DBusAddressTranslator.hpp>
#include <CommonAPI/DBus/DBusEvent.hpp>
#include <CommonAPI/Types.hpp>
#include <CommonAPI/DBus/DBusSelectiveEvent.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

#include <string>

namespace v1 {
namespace com {
namespace harman {
namespace layermanager {

class LayerManagerDBusProxy
    : virtual public LayerManagerProxyBase, 
      virtual public CommonAPI::DBus::DBusProxy {
public:
    LayerManagerDBusProxy(
        const CommonAPI::DBus::DBusAddress &_address,
        const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection);

    virtual ~LayerManagerDBusProxy() { }


    virtual EventUpdateSelectiveEvent& getEventUpdateSelectiveEvent();
    virtual PropertyUpdateSelectiveEvent& getPropertyUpdateSelectiveEvent();

    /**
     * description: This is different from the Common API broadcast/attribute subscription. Client
     *   can subscribe to events like creation,destruction etc for a particular
     *   surface/layer/display. 					  The API will always be successfull, and will
     *   cause conditional broadcasts to be triggered to the registering clients.   
     *   					  Before calling this function ensure that you have subscribed to the
     *   propertyUpdate broadcast.
     * param: type: 		  The passed identifier is a surface/layer/display
     * param: name: 		  The string name for the desired object. The string name can be
     *   checked in LayerManager.conf
     * param: isSubscribe:    Whether this is a subscription or an unsubscription request.
     * param: eventFilter:	  Bitmask combination of events interested in (Look at tEventType)
     *                      returns:	  nothing
     */
    virtual void subscribeEvents(const ::v1::com::harman::layermanager::LayerManagerTypes::tObjectType &_type, const std::string &_name, const uint64_t &_eventFilter, const bool &_isSubscribe, CommonAPI::CallStatus &_internalCallStatus);
    virtual void setProperty(const std::vector<::v1::com::harman::layermanager::LayerManagerTypes::tProperty> &_property, CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::layermanager::LayerManagerTypes::tResult &_result, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> setPropertyAsync(const std::vector<::v1::com::harman::layermanager::LayerManagerTypes::tProperty> &_property, SetPropertyAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: This is different from the Common API broadcast/attribute subscription. Client
     *   can subscribe to events like creation,visibility change, resize etc for a
     *   particular surface/layer. 					  The API will always be successfull, and will
     *   cause conditional broadcasts to be triggered to the registering clients.   
     *   					  Before calling this function ensure that you have subscribed to the
     *   propertyUpdate broadcast.
     * param: type: 		  The passed identifier is a surface/layer/display
     * param: id: 			  The string identifier for the desired object. The string identifier
     *   can be checked in LayerManager.conf
     * param: isSubscribe:    Whether this is a subscription or an unsubscription request.
     * param: propFilter:	  Bitmask combination of properties interested in (Look at
     *   tPropertyType)                    returns:	  nothing
     */
    virtual void subscribeProps(const ::v1::com::harman::layermanager::LayerManagerTypes::tObjectType &_type, const std::string &_id, const uint64_t &_propFilter, const bool &_isSubscribe, CommonAPI::CallStatus &_internalCallStatus);
    /**
     * description: Removes all event / property subscription for a client.             returns:	 
     *   Nothing..
     */
    virtual void unsubscribeAll(CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> unsubscribeAllAsync(UnsubscribeAllAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Initiate a capture operation for the display,layer or surface. Will only return
     *   once the operation finished successfully/failed. 		Add periodic.
     * param: type: 		  The passed identifier is a surface/layer/display
     * param: name: 		  The string name for the desired object. The string identifier can be
     *   checked in LayerManager.conf                    returns:	  path: 		  If
     *   successfull, returns the path to the PNG file.           returns:    
     *   result:		  Status of operation.
     */
    virtual void screenshot(const ::v1::com::harman::layermanager::LayerManagerTypes::tObjectType &_type, const std::string &_name, CommonAPI::CallStatus &_internalCallStatus, std::string &_path, ::v1::com::harman::layermanager::LayerManagerTypes::tResult &_result, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> screenshotAsync(const ::v1::com::harman::layermanager::LayerManagerTypes::tObjectType &_type, const std::string &_name, ScreenshotAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: This API will set the visibility of a layer to true, if no higher priority
     *   layers are not currently visible.   				      There are no implicit z order /
     *   alpha changes.  				      Any layers at the same priority level will be hidden
     *   implicitly.  					  For more specific use cases, use the command API.
     * param: :layerID	Layer ID matching in layermanager.conf	       	 		returns:	  result :
     *   Check enumeration for more details.
     */
    virtual void showLayerSafe(const std::string &_layerID, CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::layermanager::LayerManagerTypes::tResult &_result, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> showLayerSafeAsync(const std::string &_layerID, ShowLayerSafeAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: This API will set the visibility of a layer to false. If any previous layer can
     *   be shown on screen, it is made visible.
     * param: :layerID	Layer ID matching in layermanager.conf 			returns:	  result : Check
     *   enumeration for more details.
     */
    virtual void hideLayerSafe(const std::string &_layerID, CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::layermanager::LayerManagerTypes::tResult &_result, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> hideLayerSafeAsync(const std::string &_layerID, HideLayerSafeAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: This API will set the visibility of a surface to true. The surface can be
     *   hidden again if desired through the hideSurface interface.
     * param: surfaceID: surface ID matching in layermanager.conf
     * param: bestGuessAttach: If set to true, this parameter causes the layer manager to
     *   find an appropriate "visible" layer to attach this surface to. (before being
     *   shown).  							The bestGuessSurface must be defined in the "supportedlayers"
     *   attribute in the layermanager config. The attach will always be done to the
     *   first visible layer found in the 							 "supportedlayers" list. If no visible
     *   Layer is found to which the surface can be attached, then the API will fail. 
     *   	       	 		returns:	  result : Check enumeration for more details.
     */
    virtual void showSurface(const std::string &_surfaceID, const bool &_bestGuessAttach, CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::layermanager::LayerManagerTypes::tResult &_result, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> showSurfaceAsync(const std::string &_surfaceID, const bool &_bestGuessAttach, ShowSurfaceAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: This API will set the visibility of a surface to false.
     * param: surfaceID: surface ID matching in layermanager.conf 			returns:	  result :
     *   Check enumeration for more details.
     */
    virtual void hideSurface(const std::string &_surfaceID, CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::layermanager::LayerManagerTypes::tResult &_result, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> hideSurfaceAsync(const std::string &_surfaceID, HideSurfaceAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Can be used to run any arbitrary command sequence. Command Sequences can be
     *   defined in LayerManagerCommands.ini file
     * param: :command	Cammand Sequence defined in LayerManagerCommands.ini 	       	
     *   		returns:	  result : Check enumeration for more details.
     */
    virtual void runCommand(const std::string &_command, CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::layermanager::LayerManagerTypes::tResult &_result, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> runCommandAsync(const std::string &_command, RunCommandAsyncCallback _callback, const CommonAPI::CallInfo *_info);


    virtual void getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const;

private:
   

    CommonAPI::DBus::DBusSelectiveEvent<EventUpdateSelectiveEvent, CommonAPI::Deployable<::v1::com::harman::layermanager::LayerManagerTypes::tEventType, CommonAPI::EmptyDeployment>, CommonAPI::Deployable<uint32_t, CommonAPI::EmptyDeployment>> eventUpdateSelective_;
    CommonAPI::DBus::DBusSelectiveEvent<PropertyUpdateSelectiveEvent, CommonAPI::Deployable<::v1::com::harman::layermanager::LayerManagerTypes::tProperty, ::v1::com::harman::layermanager::LayerManagerTypes_::tPropertyDeployment_t>> propertyUpdateSelective_;

};

} // namespace layermanager
} // namespace harman
} // namespace com
} // namespace v1

#endif // V1_COM_HARMAN_LAYERMANAGER_Layer_Manager_DBUS_PROXY_HPP_

