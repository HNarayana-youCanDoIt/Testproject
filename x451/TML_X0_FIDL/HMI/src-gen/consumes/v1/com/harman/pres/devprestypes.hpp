/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/
#ifndef V1_COM_HARMAN_PRES_devprestypes_HPP_
#define V1_COM_HARMAN_PRES_devprestypes_HPP_



#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Deployment.hpp>
#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <CommonAPI/Struct.hpp>
#include <CommonAPI/Types.hpp>
#include <cstdint>
#include <string>
#include <vector>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace com {
namespace harman {
namespace pres {

struct devprestypes {
    
    struct eModeName : CommonAPI::Enumeration<int32_t> {
        enum Literal : int32_t {
            USB_NONE = 0,
            USB_MSD = 1,
            USB_IPHONE_IPOD = 2,
            USB_IPHONE_CARPLAY = 3,
            USB_IPHONE_CARLIFE = 4,
            USB_IPHONE_SAL = 5,
            USB_ANDROID_MTP = 6,
            USB_ANDROID_ANDROIDAUTO = 7,
            USB_ANDROID_CARLIFE = 8,
            USB_ANDROID_SAL = 9,
            WIFI_IPHONE_CARPLAY = 10,
            WIFI_ANDROID_ANDROIDAUTO = 11
        };
        
        eModeName() 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(Literal::USB_NONE)) {}
        eModeName(Literal _literal) 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast<int32_t>(Literal::USB_NONE):
                case static_cast<int32_t>(Literal::USB_MSD):
                case static_cast<int32_t>(Literal::USB_IPHONE_IPOD):
                case static_cast<int32_t>(Literal::USB_IPHONE_CARPLAY):
                case static_cast<int32_t>(Literal::USB_IPHONE_CARLIFE):
                case static_cast<int32_t>(Literal::USB_IPHONE_SAL):
                case static_cast<int32_t>(Literal::USB_ANDROID_MTP):
                case static_cast<int32_t>(Literal::USB_ANDROID_ANDROIDAUTO):
                case static_cast<int32_t>(Literal::USB_ANDROID_CARLIFE):
                case static_cast<int32_t>(Literal::USB_ANDROID_SAL):
                case static_cast<int32_t>(Literal::WIFI_IPHONE_CARPLAY):
                case static_cast<int32_t>(Literal::WIFI_ANDROID_ANDROIDAUTO):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const eModeName &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const eModeName &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const eModeName &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const eModeName &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const eModeName &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const eModeName &_other) const { return (value_ > _other.value_); }
        
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast<int32_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast<int32_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast<int32_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast<int32_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast<int32_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast<int32_t>(_value)); }
    };
    
    struct eModeStatus : CommonAPI::Enumeration<int32_t> {
        enum Literal : int32_t {
            CAPABLE = 0,
            ACTIVATING = 1,
            ACTIVE = 2,
#ifdef PLATFORM_WIN32
            ERROR_1 = 3,
#else
            ERROR = 3,
#endif
            DEACTIVATING = 4
        };
        
        eModeStatus() 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(Literal::CAPABLE)) {}
        eModeStatus(Literal _literal) 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast<int32_t>(Literal::CAPABLE):
                case static_cast<int32_t>(Literal::ACTIVATING):
                case static_cast<int32_t>(Literal::ACTIVE):
# ifdef PLATFORM_WIN32
            case static_cast<int32_t>(Literal::ERROR_1):
#else
            case static_cast<int32_t>(Literal::ERROR):
#endif
                case static_cast<int32_t>(Literal::DEACTIVATING):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const eModeStatus &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const eModeStatus &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const eModeStatus &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const eModeStatus &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const eModeStatus &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const eModeStatus &_other) const { return (value_ > _other.value_); }
        
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast<int32_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast<int32_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast<int32_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast<int32_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast<int32_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast<int32_t>(_value)); }
    };
    
    struct eDeviceType : CommonAPI::Enumeration<int32_t> {
        enum Literal : int32_t {
            USB_MSD = 0,
            IPHONE = 1,
            ANDROID_PHONE = 2,
            UNKNOWN = 3
        };
        
        eDeviceType() 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(Literal::USB_MSD)) {}
        eDeviceType(Literal _literal) 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast<int32_t>(Literal::USB_MSD):
                case static_cast<int32_t>(Literal::IPHONE):
                case static_cast<int32_t>(Literal::ANDROID_PHONE):
                case static_cast<int32_t>(Literal::UNKNOWN):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const eDeviceType &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const eDeviceType &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const eDeviceType &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const eDeviceType &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const eDeviceType &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const eDeviceType &_other) const { return (value_ > _other.value_); }
        
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast<int32_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast<int32_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast<int32_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast<int32_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast<int32_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast<int32_t>(_value)); }
    };
    
    struct eAcknowledgement : CommonAPI::Enumeration<int32_t> {
        enum Literal : int32_t {
            VALID_INPUT = 0,
            INVALID_INPUT = 1
        };
        
        eAcknowledgement() 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(Literal::VALID_INPUT)) {}
        eAcknowledgement(Literal _literal) 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast<int32_t>(Literal::VALID_INPUT):
                case static_cast<int32_t>(Literal::INVALID_INPUT):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const eAcknowledgement &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const eAcknowledgement &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const eAcknowledgement &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const eAcknowledgement &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const eAcknowledgement &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const eAcknowledgement &_other) const { return (value_ > _other.value_); }
        
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast<int32_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast<int32_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast<int32_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast<int32_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast<int32_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast<int32_t>(_value)); }
    };
    
    struct eRequestStatus : CommonAPI::Enumeration<int32_t> {
        enum Literal : int32_t {
            REQUEST_SUCCESS = 0,
            REQUEST_FAILURE = 1
        };
        
        eRequestStatus() 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(Literal::REQUEST_SUCCESS)) {}
        eRequestStatus(Literal _literal) 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast<int32_t>(Literal::REQUEST_SUCCESS):
                case static_cast<int32_t>(Literal::REQUEST_FAILURE):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const eRequestStatus &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const eRequestStatus &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const eRequestStatus &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const eRequestStatus &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const eRequestStatus &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const eRequestStatus &_other) const { return (value_ > _other.value_); }
        
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast<int32_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast<int32_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast<int32_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast<int32_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast<int32_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast<int32_t>(_value)); }
    };
    
    struct eErrorStatus : CommonAPI::Enumeration<int32_t> {
        enum Literal : int32_t {
            UNKNOWN_ERROR = 0
        };
        
        eErrorStatus() 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(Literal::UNKNOWN_ERROR)) {}
        eErrorStatus(Literal _literal) 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast<int32_t>(Literal::UNKNOWN_ERROR):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const eErrorStatus &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const eErrorStatus &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const eErrorStatus &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const eErrorStatus &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const eErrorStatus &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const eErrorStatus &_other) const { return (value_ > _other.value_); }
        
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast<int32_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast<int32_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast<int32_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast<int32_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast<int32_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast<int32_t>(_value)); }
    };
    
    struct eDeviceFilter : CommonAPI::Enumeration<int32_t> {
        enum Literal : int32_t {
            ALL_DEVICES = 0,
            USB_DEVICES = 1,
            WIFI_CARPLAY = 2,
            WIFI_ANDROIDAUTO = 3
        };
        
        eDeviceFilter() 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(Literal::ALL_DEVICES)) {}
        eDeviceFilter(Literal _literal) 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast<int32_t>(Literal::ALL_DEVICES):
                case static_cast<int32_t>(Literal::USB_DEVICES):
                case static_cast<int32_t>(Literal::WIFI_CARPLAY):
                case static_cast<int32_t>(Literal::WIFI_ANDROIDAUTO):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const eDeviceFilter &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const eDeviceFilter &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const eDeviceFilter &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const eDeviceFilter &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const eDeviceFilter &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const eDeviceFilter &_other) const { return (value_ > _other.value_); }
        
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast<int32_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast<int32_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast<int32_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast<int32_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast<int32_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast<int32_t>(_value)); }
    };
    /**
     * description: When HMI invokes "startMode" method call and devPresCntrl responds with
     *   broadcast "modeStatus" and 		if "hasConflictModes" is set to TRUE, then refer
     *   this structure.
     */
    struct sConflictMode : CommonAPI::Struct<uint8_t, std::string, eModeName> {
    	
    	sConflictMode() {
    	}
    	sConflictMode(const uint8_t &_Id, const std::string &_deviceName, const eModeName &_modeName)
    	{
    		std::get<0>(values_) = _Id;
    		std::get<1>(values_) = _deviceName;
    		std::get<2>(values_) = _modeName;
    	}
    	inline const uint8_t &getId() const { return std::get<0>(values_); }
    	inline void setId(const uint8_t &_value) { std::get<0>(values_) = _value; }
    	inline const std::string &getDeviceName() const { return std::get<1>(values_); }
    	inline void setDeviceName(const std::string &_value) { std::get<1>(values_) = _value; }
    	inline const eModeName &getModeName() const { return std::get<2>(values_); }
    	inline void setModeName(const eModeName &_value) { std::get<2>(values_) = _value; }
    	inline bool operator==(const sConflictMode& _other) const {
                return (getId() == _other.getId() && getDeviceName() == _other.getDeviceName() && getModeName() == _other.getModeName());
        }
    	inline bool operator!=(const sConflictMode &_other) const {
    		return !((*this) == _other);
    	}
    
    };
    /**
     * description: If "modeStatus" is set to ERROR, only then refer "errorStatus" to get to know
     *   specific error.
     */
    struct sModeInfo : CommonAPI::Struct<eModeName, eModeStatus, eErrorStatus> {
    	
    	sModeInfo() {
    	}
    	sModeInfo(const eModeName &_modeName, const eModeStatus &_modeStatus, const eErrorStatus &_errorStatus)
    	{
    		std::get<0>(values_) = _modeName;
    		std::get<1>(values_) = _modeStatus;
    		std::get<2>(values_) = _errorStatus;
    	}
    	inline const eModeName &getModeName() const { return std::get<0>(values_); }
    	inline void setModeName(const eModeName &_value) { std::get<0>(values_) = _value; }
    	inline const eModeStatus &getModeStatus() const { return std::get<1>(values_); }
    	inline void setModeStatus(const eModeStatus &_value) { std::get<1>(values_) = _value; }
    	inline const eErrorStatus &getErrorStatus() const { return std::get<2>(values_); }
    	inline void setErrorStatus(const eErrorStatus &_value) { std::get<2>(values_) = _value; }
    	inline bool operator==(const sModeInfo& _other) const {
                return (getModeName() == _other.getModeName() && getModeStatus() == _other.getModeStatus() && getErrorStatus() == _other.getErrorStatus());
        }
    	inline bool operator!=(const sModeInfo &_other) const {
    		return !((*this) == _other);
    	}
    
    };
    /**
     * description: This gives details of device connected as follows: 		 		Id : It is unique id
     *   and to be passed in other method calls to devPresCntrl.			  		 		deviceName :
     *   Device name.  		 		hasUserPreference : It tells weather user has set
     *   preference for device connected. 							If YES, means devPresCntrl also starts
     *   mode without external trigger. 							If NO, means HMI to show pop up of HU
     *   supported modes and let user select one mode. 							 		devType : Device type.
     *    		modes : List of HU supported modes for the device connected.
     */
    struct sDeviceInfo : CommonAPI::Struct<uint8_t, std::string, bool, eDeviceType, std::vector<sModeInfo>> {
    	
    	sDeviceInfo() {
    		std::get<2>(values_) = false;
    	}
    	sDeviceInfo(const uint8_t &_Id, const std::string &_deviceName, const bool &_hasUserPreference, const eDeviceType &_devType, const std::vector<sModeInfo> &_HUSupportedModes)
    	{
    		std::get<0>(values_) = _Id;
    		std::get<1>(values_) = _deviceName;
    		std::get<2>(values_) = _hasUserPreference;
    		std::get<3>(values_) = _devType;
    		std::get<4>(values_) = _HUSupportedModes;
    	}
    	inline const uint8_t &getId() const { return std::get<0>(values_); }
    	inline void setId(const uint8_t &_value) { std::get<0>(values_) = _value; }
    	inline const std::string &getDeviceName() const { return std::get<1>(values_); }
    	inline void setDeviceName(const std::string &_value) { std::get<1>(values_) = _value; }
    	inline const bool &getHasUserPreference() const { return std::get<2>(values_); }
    	inline void setHasUserPreference(const bool _value) { std::get<2>(values_) = _value; }
    	inline const eDeviceType &getDevType() const { return std::get<3>(values_); }
    	inline void setDevType(const eDeviceType &_value) { std::get<3>(values_) = _value; }
    	inline const std::vector<sModeInfo> &getHUSupportedModes() const { return std::get<4>(values_); }
    	inline void setHUSupportedModes(const std::vector<sModeInfo> &_value) { std::get<4>(values_) = _value; }
    	inline bool operator==(const sDeviceInfo& _other) const {
                return (getId() == _other.getId() && getDeviceName() == _other.getDeviceName() && getHasUserPreference() == _other.getHasUserPreference() && getDevType() == _other.getDevType() && getHUSupportedModes() == _other.getHUSupportedModes());
        }
    	inline bool operator!=(const sDeviceInfo &_other) const {
    		return !((*this) == _other);
    	}
    
    };
    
    struct eIAP2Transport : CommonAPI::Enumeration<int32_t> {
        enum Literal : int32_t {
            USB_HOST = 0,
            USB_DEVICE = 1,
            BT = 2,
            WIFI = 3,
            NONE = 4
        };
        
        eIAP2Transport() 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(Literal::USB_HOST)) {}
        eIAP2Transport(Literal _literal) 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast<int32_t>(Literal::USB_HOST):
                case static_cast<int32_t>(Literal::USB_DEVICE):
                case static_cast<int32_t>(Literal::BT):
                case static_cast<int32_t>(Literal::WIFI):
                case static_cast<int32_t>(Literal::NONE):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const eIAP2Transport &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const eIAP2Transport &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const eIAP2Transport &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const eIAP2Transport &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const eIAP2Transport &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const eIAP2Transport &_other) const { return (value_ > _other.value_); }
        
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast<int32_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast<int32_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast<int32_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast<int32_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast<int32_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast<int32_t>(_value)); }
    };
    
    struct eIAP2Mode : CommonAPI::Enumeration<int32_t> {
        enum Literal : int32_t {
            IPOD_MODE = 0,
            CARPLAY_MODE = 1,
            CARLIFE_MODE = 2,
            SAL_MODE = 3,
            NO_MODE = 4
        };
        
        eIAP2Mode() 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(Literal::IPOD_MODE)) {}
        eIAP2Mode(Literal _literal) 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast<int32_t>(Literal::IPOD_MODE):
                case static_cast<int32_t>(Literal::CARPLAY_MODE):
                case static_cast<int32_t>(Literal::CARLIFE_MODE):
                case static_cast<int32_t>(Literal::SAL_MODE):
                case static_cast<int32_t>(Literal::NO_MODE):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const eIAP2Mode &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const eIAP2Mode &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const eIAP2Mode &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const eIAP2Mode &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const eIAP2Mode &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const eIAP2Mode &_other) const { return (value_ > _other.value_); }
        
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast<int32_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast<int32_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast<int32_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast<int32_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast<int32_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast<int32_t>(_value)); }
    };
    /**
     * description: User can store preference either by individual device (BY_DEVICE_NAME) 		OR
     *   group of devices by device type (BY_DEVICE_TYPE). 		 		NOTE: When user sets
     *   preference by device type, then it overwrites the prefernce set for individual
     *   device.
     */
    struct sPrefByDevType : CommonAPI::Struct<eDeviceType, eModeName> {
    	
    	sPrefByDevType() {
    	}
    	sPrefByDevType(const eDeviceType &_devType, const eModeName &_mode)
    	{
    		std::get<0>(values_) = _devType;
    		std::get<1>(values_) = _mode;
    	}
    	inline const eDeviceType &getDevType() const { return std::get<0>(values_); }
    	inline void setDevType(const eDeviceType &_value) { std::get<0>(values_) = _value; }
    	inline const eModeName &getMode() const { return std::get<1>(values_); }
    	inline void setMode(const eModeName &_value) { std::get<1>(values_) = _value; }
    	inline bool operator==(const sPrefByDevType& _other) const {
                return (getDevType() == _other.getDevType() && getMode() == _other.getMode());
        }
    	inline bool operator!=(const sPrefByDevType &_other) const {
    		return !((*this) == _other);
    	}
    
    };
    struct sPrefByDevName : CommonAPI::Struct<uint8_t, std::string, eModeName> {
    	
    	sPrefByDevName() {
    	}
    	sPrefByDevName(const uint8_t &_Id, const std::string &_deviceName, const eModeName &_mode)
    	{
    		std::get<0>(values_) = _Id;
    		std::get<1>(values_) = _deviceName;
    		std::get<2>(values_) = _mode;
    	}
    	inline const uint8_t &getId() const { return std::get<0>(values_); }
    	inline void setId(const uint8_t &_value) { std::get<0>(values_) = _value; }
    	inline const std::string &getDeviceName() const { return std::get<1>(values_); }
    	inline void setDeviceName(const std::string &_value) { std::get<1>(values_) = _value; }
    	inline const eModeName &getMode() const { return std::get<2>(values_); }
    	inline void setMode(const eModeName &_value) { std::get<2>(values_) = _value; }
    	inline bool operator==(const sPrefByDevName& _other) const {
                return (getId() == _other.getId() && getDeviceName() == _other.getDeviceName() && getMode() == _other.getMode());
        }
    	inline bool operator!=(const sPrefByDevName &_other) const {
    		return !((*this) == _other);
    	}
    
    };
    typedef std::vector<devprestypes::sDeviceInfo> vDeviceInfo;
    struct sIAP2Info : CommonAPI::Struct<eIAP2Transport, std::vector<eIAP2Mode>, std::string, uint8_t, std::string> {
    	
    	sIAP2Info() {
    	}
    	sIAP2Info(const eIAP2Transport &_transport, const std::vector<eIAP2Mode> &_modes, const std::string &_devicePath, const uint8_t &_deviceId, const std::string &_instanceName)
    	{
    		std::get<0>(values_) = _transport;
    		std::get<1>(values_) = _modes;
    		std::get<2>(values_) = _devicePath;
    		std::get<3>(values_) = _deviceId;
    		std::get<4>(values_) = _instanceName;
    	}
    	inline const eIAP2Transport &getTransport() const { return std::get<0>(values_); }
    	inline void setTransport(const eIAP2Transport &_value) { std::get<0>(values_) = _value; }
    	inline const std::vector<eIAP2Mode> &getModes() const { return std::get<1>(values_); }
    	inline void setModes(const std::vector<eIAP2Mode> &_value) { std::get<1>(values_) = _value; }
    	inline const std::string &getDevicePath() const { return std::get<2>(values_); }
    	inline void setDevicePath(const std::string &_value) { std::get<2>(values_) = _value; }
    	inline const uint8_t &getDeviceId() const { return std::get<3>(values_); }
    	inline void setDeviceId(const uint8_t &_value) { std::get<3>(values_) = _value; }
    	inline const std::string &getInstanceName() const { return std::get<4>(values_); }
    	inline void setInstanceName(const std::string &_value) { std::get<4>(values_) = _value; }
    	inline bool operator==(const sIAP2Info& _other) const {
                return (getTransport() == _other.getTransport() && getModes() == _other.getModes() && getDevicePath() == _other.getDevicePath() && getDeviceId() == _other.getDeviceId() && getInstanceName() == _other.getInstanceName());
        }
    	inline bool operator!=(const sIAP2Info &_other) const {
    		return !((*this) == _other);
    	}
    
    };
    typedef std::vector<devprestypes::sIAP2Info> vIAP2Info;



static inline const char* getTypeCollectionName() {
    static const char* typeCollectionName = "com.harman.pres.devprestypes";
    return typeCollectionName;
}

inline CommonAPI::Version getTypeCollectionVersion() {
    return CommonAPI::Version(1, 0);
}

}; // struct devprestypes

} // namespace pres
} // namespace harman
} // namespace com
} // namespace v1

namespace CommonAPI {
}


namespace std {
    //Hash for eModeName
    template<>
    struct hash<::v1::com::harman::pres::devprestypes::eModeName> {
        inline size_t operator()(const ::v1::com::harman::pres::devprestypes::eModeName& eModeName) const {
            return static_cast<int32_t>(eModeName);
        }
    };
    //Hash for eModeStatus
    template<>
    struct hash<::v1::com::harman::pres::devprestypes::eModeStatus> {
        inline size_t operator()(const ::v1::com::harman::pres::devprestypes::eModeStatus& eModeStatus) const {
            return static_cast<int32_t>(eModeStatus);
        }
    };
    //Hash for eDeviceType
    template<>
    struct hash<::v1::com::harman::pres::devprestypes::eDeviceType> {
        inline size_t operator()(const ::v1::com::harman::pres::devprestypes::eDeviceType& eDeviceType) const {
            return static_cast<int32_t>(eDeviceType);
        }
    };
    //Hash for eAcknowledgement
    template<>
    struct hash<::v1::com::harman::pres::devprestypes::eAcknowledgement> {
        inline size_t operator()(const ::v1::com::harman::pres::devprestypes::eAcknowledgement& eAcknowledgement) const {
            return static_cast<int32_t>(eAcknowledgement);
        }
    };
    //Hash for eRequestStatus
    template<>
    struct hash<::v1::com::harman::pres::devprestypes::eRequestStatus> {
        inline size_t operator()(const ::v1::com::harman::pres::devprestypes::eRequestStatus& eRequestStatus) const {
            return static_cast<int32_t>(eRequestStatus);
        }
    };
    //Hash for eErrorStatus
    template<>
    struct hash<::v1::com::harman::pres::devprestypes::eErrorStatus> {
        inline size_t operator()(const ::v1::com::harman::pres::devprestypes::eErrorStatus& eErrorStatus) const {
            return static_cast<int32_t>(eErrorStatus);
        }
    };
    //Hash for eDeviceFilter
    template<>
    struct hash<::v1::com::harman::pres::devprestypes::eDeviceFilter> {
        inline size_t operator()(const ::v1::com::harman::pres::devprestypes::eDeviceFilter& eDeviceFilter) const {
            return static_cast<int32_t>(eDeviceFilter);
        }
    };
    //Hash for eIAP2Transport
    template<>
    struct hash<::v1::com::harman::pres::devprestypes::eIAP2Transport> {
        inline size_t operator()(const ::v1::com::harman::pres::devprestypes::eIAP2Transport& eIAP2Transport) const {
            return static_cast<int32_t>(eIAP2Transport);
        }
    };
    //Hash for eIAP2Mode
    template<>
    struct hash<::v1::com::harman::pres::devprestypes::eIAP2Mode> {
        inline size_t operator()(const ::v1::com::harman::pres::devprestypes::eIAP2Mode& eIAP2Mode) const {
            return static_cast<int32_t>(eIAP2Mode);
        }
    };
}


// Compatibility
namespace v1_0 = v1;

#endif // V1_COM_HARMAN_PRES_devprestypes_HPP_
