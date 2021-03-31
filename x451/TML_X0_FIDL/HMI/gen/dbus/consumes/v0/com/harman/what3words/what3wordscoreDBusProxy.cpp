/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/
#include <v0/com/harman/what3words/what3wordscoreDBusProxy.hpp>

namespace v0 {
namespace com {
namespace harman {
namespace what3words {

std::shared_ptr<CommonAPI::DBus::DBusProxy> createwhat3wordscoreDBusProxy(
	const CommonAPI::DBus::DBusAddress &_address,
	const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection) {
	return std::make_shared<what3wordscoreDBusProxy>(_address, _connection);
}

INITIALIZER(registerwhat3wordscoreDBusProxy) {
     CommonAPI::DBus::Factory::get()->registerProxyCreateMethod(
		what3wordscore::getInterface(),
		&createwhat3wordscoreDBusProxy);
}

what3wordscoreDBusProxy::what3wordscoreDBusProxy(
	const CommonAPI::DBus::DBusAddress &_address,
	const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection)
	:	CommonAPI::DBus::DBusProxy(_address, _connection)
{
}


    
    /**
     * description: This method will provide three autosuggestion of words for a string input in
     *   w3w format 		returns:      Vector for three word address, language code,
     *   nearest place, country code         status:       SUCCESS if no error, FAILURE
     *   on error.
     * param: w3waddress The three words address in W3W format
     */
    void what3wordscoreDBusProxy::getAutoSuggestions(const std::string &_w3waddress, CommonAPI::CallStatus &_internalCallStatus, ::v0::com::harman::what3words::w3wTypeCollection::retStatus &_status, ::v0::com::harman::what3words::w3wTypeCollection::arSuggtion &_wordSugg, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment> deploy_w3waddress(_w3waddress, static_cast<CommonAPI::DBus::StringDeployment*>(nullptr));
        CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::retStatus, CommonAPI::EmptyDeployment> deploy_status(static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::arSuggtion, ::v0::com::harman::what3words::w3wTypeCollection_::arSuggtionDeployment_t> deploy_wordSugg(static_cast<::v0::com::harman::what3words::w3wTypeCollection_::arSuggtionDeployment_t*>(nullptr));
        CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment >
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::retStatus,CommonAPI::EmptyDeployment>,
            CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::arSuggtion,::v0::com::harman::what3words::w3wTypeCollection_::arSuggtionDeployment_t>
            >
        	>::callMethodWithReply(
        *this,
        "getAutoSuggestions",
        "s",
(_info ? _info : &CommonAPI::DBus::defaultCallInfo),
deploy_w3waddress,
_internalCallStatus,
deploy_status, deploy_wordSugg);
_status = deploy_status.getValue();
_wordSugg = deploy_wordSugg.getValue();
}
    std::future<CommonAPI::CallStatus> what3wordscoreDBusProxy::getAutoSuggestionsAsync(const std::string &_w3waddress, GetAutoSuggestionsAsyncCallback _callback, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment> deploy_w3waddress(_w3waddress, static_cast<CommonAPI::DBus::StringDeployment*>(nullptr));
        CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::retStatus, CommonAPI::EmptyDeployment> deploy_status(static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::arSuggtion, ::v0::com::harman::what3words::w3wTypeCollection_::arSuggtionDeployment_t> deploy_wordSugg(static_cast<::v0::com::harman::what3words::w3wTypeCollection_::arSuggtionDeployment_t*>(nullptr));
        return CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment >
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::retStatus,CommonAPI::EmptyDeployment>,
            CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::arSuggtion,::v0::com::harman::what3words::w3wTypeCollection_::arSuggtionDeployment_t>
            >
        	>::callMethodAsync(
        *this,
        "getAutoSuggestions",
        "s",
        (_info ? _info : &CommonAPI::DBus::defaultCallInfo),
        deploy_w3waddress,
        [_callback] (CommonAPI::CallStatus _internalCallStatus, CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::retStatus, CommonAPI::EmptyDeployment> _status, CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::arSuggtion, ::v0::com::harman::what3words::w3wTypeCollection_::arSuggtionDeployment_t> _wordSugg) {
        	if (_callback)
        		_callback(_internalCallStatus, _status.getValue(), _wordSugg.getValue());
        },
        std::make_tuple(deploy_status, deploy_wordSugg));
    }
    /**
     * description: This method will provide latitude and longitiude details of last navigated W3W
     *   address 		returns:	  Latitude and longitude details of W3W address        
     *   status:       SUCCESS if no error, FAILURE on error.
     * param: w3waddress The three word address in W3W format
     */
    void what3wordscoreDBusProxy::getLatLong(const std::string &_w3waddress, CommonAPI::CallStatus &_internalCallStatus, ::v0::com::harman::what3words::w3wTypeCollection::retStatus &_status, ::v0::com::harman::what3words::w3wTypeCollection::Coordinates &_coord, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment> deploy_w3waddress(_w3waddress, static_cast<CommonAPI::DBus::StringDeployment*>(nullptr));
        CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::retStatus, CommonAPI::EmptyDeployment> deploy_status(static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::Coordinates, ::v0::com::harman::what3words::w3wTypeCollection_::CoordinatesDeployment_t> deploy_coord(static_cast<::v0::com::harman::what3words::w3wTypeCollection_::CoordinatesDeployment_t*>(nullptr));
        CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment >
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::retStatus,CommonAPI::EmptyDeployment>,
            CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::Coordinates,::v0::com::harman::what3words::w3wTypeCollection_::CoordinatesDeployment_t>
            >
        	>::callMethodWithReply(
        *this,
        "getLatLong",
        "s",
(_info ? _info : &CommonAPI::DBus::defaultCallInfo),
deploy_w3waddress,
_internalCallStatus,
deploy_status, deploy_coord);
_status = deploy_status.getValue();
_coord = deploy_coord.getValue();
}
    std::future<CommonAPI::CallStatus> what3wordscoreDBusProxy::getLatLongAsync(const std::string &_w3waddress, GetLatLongAsyncCallback _callback, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment> deploy_w3waddress(_w3waddress, static_cast<CommonAPI::DBus::StringDeployment*>(nullptr));
        CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::retStatus, CommonAPI::EmptyDeployment> deploy_status(static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::Coordinates, ::v0::com::harman::what3words::w3wTypeCollection_::CoordinatesDeployment_t> deploy_coord(static_cast<::v0::com::harman::what3words::w3wTypeCollection_::CoordinatesDeployment_t*>(nullptr));
        return CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment >
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::retStatus,CommonAPI::EmptyDeployment>,
            CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::Coordinates,::v0::com::harman::what3words::w3wTypeCollection_::CoordinatesDeployment_t>
            >
        	>::callMethodAsync(
        *this,
        "getLatLong",
        "s",
        (_info ? _info : &CommonAPI::DBus::defaultCallInfo),
        deploy_w3waddress,
        [_callback] (CommonAPI::CallStatus _internalCallStatus, CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::retStatus, CommonAPI::EmptyDeployment> _status, CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::Coordinates, ::v0::com::harman::what3words::w3wTypeCollection_::CoordinatesDeployment_t> _coord) {
        	if (_callback)
        		_callback(_internalCallStatus, _status.getValue(), _coord.getValue());
        },
        std::make_tuple(deploy_status, deploy_coord));
    }
    /**
     * description: This method will W3W address for the latitude and longitude co-ordinates
     *   		returns:	  W3W address         status:       SUCCESS if no error, FAILURE on
     *   error.
     * param: coord latitude and Longitude
     */
    void what3wordscoreDBusProxy::getW3WAddress(const ::v0::com::harman::what3words::w3wTypeCollection::Coordinates &_coord, CommonAPI::CallStatus &_internalCallStatus, ::v0::com::harman::what3words::w3wTypeCollection::retStatus &_status, std::string &_w3waddress, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::Coordinates, ::v0::com::harman::what3words::w3wTypeCollection_::CoordinatesDeployment_t> deploy_coord(_coord, static_cast<::v0::com::harman::what3words::w3wTypeCollection_::CoordinatesDeployment_t*>(nullptr));
        CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::retStatus, CommonAPI::EmptyDeployment> deploy_status(static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment> deploy_w3waddress(static_cast<CommonAPI::DBus::StringDeployment*>(nullptr));
        CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::Coordinates, ::v0::com::harman::what3words::w3wTypeCollection_::CoordinatesDeployment_t >
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::retStatus,CommonAPI::EmptyDeployment>,
            CommonAPI::Deployable<std::string,CommonAPI::DBus::StringDeployment>
            >
        	>::callMethodWithReply(
        *this,
        "getW3WAddress",
        "(dd)",
(_info ? _info : &CommonAPI::DBus::defaultCallInfo),
deploy_coord,
_internalCallStatus,
deploy_status, deploy_w3waddress);
_status = deploy_status.getValue();
_w3waddress = deploy_w3waddress.getValue();
}
    std::future<CommonAPI::CallStatus> what3wordscoreDBusProxy::getW3WAddressAsync(const ::v0::com::harman::what3words::w3wTypeCollection::Coordinates &_coord, GetW3WAddressAsyncCallback _callback, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::Coordinates, ::v0::com::harman::what3words::w3wTypeCollection_::CoordinatesDeployment_t> deploy_coord(_coord, static_cast<::v0::com::harman::what3words::w3wTypeCollection_::CoordinatesDeployment_t*>(nullptr));
        CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::retStatus, CommonAPI::EmptyDeployment> deploy_status(static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment> deploy_w3waddress(static_cast<CommonAPI::DBus::StringDeployment*>(nullptr));
        return CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::Coordinates, ::v0::com::harman::what3words::w3wTypeCollection_::CoordinatesDeployment_t >
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::retStatus,CommonAPI::EmptyDeployment>,
            CommonAPI::Deployable<std::string,CommonAPI::DBus::StringDeployment>
            >
        	>::callMethodAsync(
        *this,
        "getW3WAddress",
        "(dd)",
        (_info ? _info : &CommonAPI::DBus::defaultCallInfo),
        deploy_coord,
        [_callback] (CommonAPI::CallStatus _internalCallStatus, CommonAPI::Deployable<::v0::com::harman::what3words::w3wTypeCollection::retStatus, CommonAPI::EmptyDeployment> _status, CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment> _w3waddress) {
        	if (_callback)
        		_callback(_internalCallStatus, _status.getValue(), _w3waddress.getValue());
        },
        std::make_tuple(deploy_status, deploy_w3waddress));
    }


void what3wordscoreDBusProxy::getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const {
          ownVersionMajor = 0;
          ownVersionMinor = 1;
      }

      } // namespace what3words
      } // namespace harman
      } // namespace com
      } // namespace v0
