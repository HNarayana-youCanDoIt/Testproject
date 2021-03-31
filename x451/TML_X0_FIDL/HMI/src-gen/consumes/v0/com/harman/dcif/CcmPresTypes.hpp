/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/
#ifndef V0_COM_HARMAN_DCIF_Ccm_Pres_Types_HPP_
#define V0_COM_HARMAN_DCIF_Ccm_Pres_Types_HPP_



#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Deployment.hpp>
#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <CommonAPI/Struct.hpp>
#include <CommonAPI/Types.hpp>
#include <cstdint>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v0 {
namespace com {
namespace harman {
namespace dcif {

struct CcmPresTypes {
    
    struct eHuCcmParam : CommonAPI::Enumeration<int32_t> {
        enum Literal : int32_t {
            HUCCM_AIRCON_CTRL = 1,
            HUCCM_ECON_MODE = 2,
            HUCCM_AUTO_MODE = 3,
            HUCCM_HVAC_CTRL = 4,
            HUCCM_MAX_DEFRST = 5,
            HUCCM_FRESHAIR_RECIRC = 6,
            HUCCM_DISTRIB_MODE = 7,
            HUCCM_TEMP_PASS = 8,
            HUCCM_TEMP_DRVR = 9,
            HUCCM_FAN_SPEED = 10,
            HUCCM_DUAL_MODE = 11,
            HUCCM_TEMP_CHANGE = 12,
            HUCCM_REAR_DEFOG = 13,
            CCM_ERR_STATUS = 14,
            CCM_VARIANT_TYPE = 15,
            CCM_PRESENCE = 16,
            CCM_SWITCH_STUCKWARN = 17,
            CCM_LOWFANSPD_CONFIG = 18,
            CCM_HIFANSPD_CONFIG = 19,
            CCM_LOWTEMP_CONFIG = 20,
            CCM_HITEMP_CONFIG = 21,
            CCM_ECON_CONFIG = 22,
            CCM_EXPCOOL_CONFIG = 23,
            HUCCM_EXPCOOL_STATUS = 24
        };
        
        eHuCcmParam() 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(Literal::HUCCM_AIRCON_CTRL)) {}
        eHuCcmParam(Literal _literal) 
            : CommonAPI::Enumeration<int32_t>(static_cast<int32_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast<int32_t>(Literal::HUCCM_AIRCON_CTRL):
                case static_cast<int32_t>(Literal::HUCCM_ECON_MODE):
                case static_cast<int32_t>(Literal::HUCCM_AUTO_MODE):
                case static_cast<int32_t>(Literal::HUCCM_HVAC_CTRL):
                case static_cast<int32_t>(Literal::HUCCM_MAX_DEFRST):
                case static_cast<int32_t>(Literal::HUCCM_FRESHAIR_RECIRC):
                case static_cast<int32_t>(Literal::HUCCM_DISTRIB_MODE):
                case static_cast<int32_t>(Literal::HUCCM_TEMP_PASS):
                case static_cast<int32_t>(Literal::HUCCM_TEMP_DRVR):
                case static_cast<int32_t>(Literal::HUCCM_FAN_SPEED):
                case static_cast<int32_t>(Literal::HUCCM_DUAL_MODE):
                case static_cast<int32_t>(Literal::HUCCM_TEMP_CHANGE):
                case static_cast<int32_t>(Literal::HUCCM_REAR_DEFOG):
                case static_cast<int32_t>(Literal::CCM_ERR_STATUS):
                case static_cast<int32_t>(Literal::CCM_VARIANT_TYPE):
                case static_cast<int32_t>(Literal::CCM_PRESENCE):
                case static_cast<int32_t>(Literal::CCM_SWITCH_STUCKWARN):
                case static_cast<int32_t>(Literal::CCM_LOWFANSPD_CONFIG):
                case static_cast<int32_t>(Literal::CCM_HIFANSPD_CONFIG):
                case static_cast<int32_t>(Literal::CCM_LOWTEMP_CONFIG):
                case static_cast<int32_t>(Literal::CCM_HITEMP_CONFIG):
                case static_cast<int32_t>(Literal::CCM_ECON_CONFIG):
                case static_cast<int32_t>(Literal::CCM_EXPCOOL_CONFIG):
                case static_cast<int32_t>(Literal::HUCCM_EXPCOOL_STATUS):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const eHuCcmParam &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const eHuCcmParam &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const eHuCcmParam &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const eHuCcmParam &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const eHuCcmParam &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const eHuCcmParam &_other) const { return (value_ > _other.value_); }
        
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast<int32_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast<int32_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast<int32_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast<int32_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast<int32_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast<int32_t>(_value)); }
    };
    struct tCcmHu : CommonAPI::Struct<eHuCcmParam, uint16_t> {
    	
    	tCcmHu() {
    	}
    	tCcmHu(const eHuCcmParam &_ccmHu_enum, const uint16_t &_CcmHu_value)
    	{
    		std::get<0>(values_) = _ccmHu_enum;
    		std::get<1>(values_) = _CcmHu_value;
    	}
    	inline const eHuCcmParam &getCcmHu_enum() const { return std::get<0>(values_); }
    	inline void setCcmHu_enum(const eHuCcmParam &_value) { std::get<0>(values_) = _value; }
    	inline const uint16_t &getCcmHu_value() const { return std::get<1>(values_); }
    	inline void setCcmHu_value(const uint16_t &_value) { std::get<1>(values_) = _value; }
    	inline bool operator==(const tCcmHu& _other) const {
                return (getCcmHu_enum() == _other.getCcmHu_enum() && getCcmHu_value() == _other.getCcmHu_value());
        }
    	inline bool operator!=(const tCcmHu &_other) const {
    		return !((*this) == _other);
    	}
    
    };
    struct CcmInfo : CommonAPI::Struct<bool, bool, bool, bool, bool, uint8_t, uint8_t, uint16_t, uint16_t, uint8_t, bool, uint16_t, bool, bool, uint8_t, bool, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, bool> {
    	
    	CcmInfo() {
    		std::get<0>(values_) = false;
    		std::get<1>(values_) = false;
    		std::get<2>(values_) = false;
    		std::get<3>(values_) = false;
    		std::get<4>(values_) = false;
    		std::get<10>(values_) = false;
    		std::get<12>(values_) = false;
    		std::get<13>(values_) = false;
    		std::get<15>(values_) = false;
    		std::get<23>(values_) = false;
    	}
    	CcmInfo(const bool &_ccmAirconCtrl, const bool &_ccmEconMode, const bool &_ccmAutoMode, const bool &_ccmHVACCtrl, const bool &_ccmMaxDefrst, const uint8_t &_ccmFreshairRecirc, const uint8_t &_ccmDistribMode, const uint16_t &_ccmTemPass, const uint16_t &_ccmTempDrvr, const uint8_t &_ccmFanSpeed, const bool &_ccmDualMode, const uint16_t &_ccmTempChange, const bool &_ccmRearDefog, const bool &_ccmErrStatus, const uint8_t &_ccmVariantType, const bool &_ccmPresence, const uint16_t &_ccmSwitchStuckwarn, const uint16_t &_ccmLowfanspdConfig, const uint16_t &_ccmHifanspdConfig, const uint16_t &_ccmLowtempConfig, const uint16_t &_ccmHitempConfig, const uint16_t &_ccmEconConfig, const uint16_t &_ccmExpCoolConfig, const bool &_ccmExpCoolSts)
    	{
    		std::get<0>(values_) = _ccmAirconCtrl;
    		std::get<1>(values_) = _ccmEconMode;
    		std::get<2>(values_) = _ccmAutoMode;
    		std::get<3>(values_) = _ccmHVACCtrl;
    		std::get<4>(values_) = _ccmMaxDefrst;
    		std::get<5>(values_) = _ccmFreshairRecirc;
    		std::get<6>(values_) = _ccmDistribMode;
    		std::get<7>(values_) = _ccmTemPass;
    		std::get<8>(values_) = _ccmTempDrvr;
    		std::get<9>(values_) = _ccmFanSpeed;
    		std::get<10>(values_) = _ccmDualMode;
    		std::get<11>(values_) = _ccmTempChange;
    		std::get<12>(values_) = _ccmRearDefog;
    		std::get<13>(values_) = _ccmErrStatus;
    		std::get<14>(values_) = _ccmVariantType;
    		std::get<15>(values_) = _ccmPresence;
    		std::get<16>(values_) = _ccmSwitchStuckwarn;
    		std::get<17>(values_) = _ccmLowfanspdConfig;
    		std::get<18>(values_) = _ccmHifanspdConfig;
    		std::get<19>(values_) = _ccmLowtempConfig;
    		std::get<20>(values_) = _ccmHitempConfig;
    		std::get<21>(values_) = _ccmEconConfig;
    		std::get<22>(values_) = _ccmExpCoolConfig;
    		std::get<23>(values_) = _ccmExpCoolSts;
    	}
    	inline const bool &getCcmAirconCtrl() const { return std::get<0>(values_); }
    	inline void setCcmAirconCtrl(const bool _value) { std::get<0>(values_) = _value; }
    	inline const bool &getCcmEconMode() const { return std::get<1>(values_); }
    	inline void setCcmEconMode(const bool _value) { std::get<1>(values_) = _value; }
    	inline const bool &getCcmAutoMode() const { return std::get<2>(values_); }
    	inline void setCcmAutoMode(const bool _value) { std::get<2>(values_) = _value; }
    	inline const bool &getCcmHVACCtrl() const { return std::get<3>(values_); }
    	inline void setCcmHVACCtrl(const bool _value) { std::get<3>(values_) = _value; }
    	inline const bool &getCcmMaxDefrst() const { return std::get<4>(values_); }
    	inline void setCcmMaxDefrst(const bool _value) { std::get<4>(values_) = _value; }
    	inline const uint8_t &getCcmFreshairRecirc() const { return std::get<5>(values_); }
    	inline void setCcmFreshairRecirc(const uint8_t &_value) { std::get<5>(values_) = _value; }
    	inline const uint8_t &getCcmDistribMode() const { return std::get<6>(values_); }
    	inline void setCcmDistribMode(const uint8_t &_value) { std::get<6>(values_) = _value; }
    	inline const uint16_t &getCcmTemPass() const { return std::get<7>(values_); }
    	inline void setCcmTemPass(const uint16_t &_value) { std::get<7>(values_) = _value; }
    	inline const uint16_t &getCcmTempDrvr() const { return std::get<8>(values_); }
    	inline void setCcmTempDrvr(const uint16_t &_value) { std::get<8>(values_) = _value; }
    	inline const uint8_t &getCcmFanSpeed() const { return std::get<9>(values_); }
    	inline void setCcmFanSpeed(const uint8_t &_value) { std::get<9>(values_) = _value; }
    	inline const bool &getCcmDualMode() const { return std::get<10>(values_); }
    	inline void setCcmDualMode(const bool _value) { std::get<10>(values_) = _value; }
    	inline const uint16_t &getCcmTempChange() const { return std::get<11>(values_); }
    	inline void setCcmTempChange(const uint16_t &_value) { std::get<11>(values_) = _value; }
    	inline const bool &getCcmRearDefog() const { return std::get<12>(values_); }
    	inline void setCcmRearDefog(const bool _value) { std::get<12>(values_) = _value; }
    	inline const bool &getCcmErrStatus() const { return std::get<13>(values_); }
    	inline void setCcmErrStatus(const bool _value) { std::get<13>(values_) = _value; }
    	inline const uint8_t &getCcmVariantType() const { return std::get<14>(values_); }
    	inline void setCcmVariantType(const uint8_t &_value) { std::get<14>(values_) = _value; }
    	inline const bool &getCcmPresence() const { return std::get<15>(values_); }
    	inline void setCcmPresence(const bool _value) { std::get<15>(values_) = _value; }
    	inline const uint16_t &getCcmSwitchStuckwarn() const { return std::get<16>(values_); }
    	inline void setCcmSwitchStuckwarn(const uint16_t &_value) { std::get<16>(values_) = _value; }
    	inline const uint16_t &getCcmLowfanspdConfig() const { return std::get<17>(values_); }
    	inline void setCcmLowfanspdConfig(const uint16_t &_value) { std::get<17>(values_) = _value; }
    	inline const uint16_t &getCcmHifanspdConfig() const { return std::get<18>(values_); }
    	inline void setCcmHifanspdConfig(const uint16_t &_value) { std::get<18>(values_) = _value; }
    	inline const uint16_t &getCcmLowtempConfig() const { return std::get<19>(values_); }
    	inline void setCcmLowtempConfig(const uint16_t &_value) { std::get<19>(values_) = _value; }
    	inline const uint16_t &getCcmHitempConfig() const { return std::get<20>(values_); }
    	inline void setCcmHitempConfig(const uint16_t &_value) { std::get<20>(values_) = _value; }
    	inline const uint16_t &getCcmEconConfig() const { return std::get<21>(values_); }
    	inline void setCcmEconConfig(const uint16_t &_value) { std::get<21>(values_) = _value; }
    	inline const uint16_t &getCcmExpCoolConfig() const { return std::get<22>(values_); }
    	inline void setCcmExpCoolConfig(const uint16_t &_value) { std::get<22>(values_) = _value; }
    	inline const bool &getCcmExpCoolSts() const { return std::get<23>(values_); }
    	inline void setCcmExpCoolSts(const bool _value) { std::get<23>(values_) = _value; }
    	inline bool operator==(const CcmInfo& _other) const {
                return (getCcmAirconCtrl() == _other.getCcmAirconCtrl() && getCcmEconMode() == _other.getCcmEconMode() && getCcmAutoMode() == _other.getCcmAutoMode() && getCcmHVACCtrl() == _other.getCcmHVACCtrl() && getCcmMaxDefrst() == _other.getCcmMaxDefrst() && getCcmFreshairRecirc() == _other.getCcmFreshairRecirc() && getCcmDistribMode() == _other.getCcmDistribMode() && getCcmTemPass() == _other.getCcmTemPass() && getCcmTempDrvr() == _other.getCcmTempDrvr() && getCcmFanSpeed() == _other.getCcmFanSpeed() && getCcmDualMode() == _other.getCcmDualMode() && getCcmTempChange() == _other.getCcmTempChange() && getCcmRearDefog() == _other.getCcmRearDefog() && getCcmErrStatus() == _other.getCcmErrStatus() && getCcmVariantType() == _other.getCcmVariantType() && getCcmPresence() == _other.getCcmPresence() && getCcmSwitchStuckwarn() == _other.getCcmSwitchStuckwarn() && getCcmLowfanspdConfig() == _other.getCcmLowfanspdConfig() && getCcmHifanspdConfig() == _other.getCcmHifanspdConfig() && getCcmLowtempConfig() == _other.getCcmLowtempConfig() && getCcmHitempConfig() == _other.getCcmHitempConfig() && getCcmEconConfig() == _other.getCcmEconConfig() && getCcmExpCoolConfig() == _other.getCcmExpCoolConfig() && getCcmExpCoolSts() == _other.getCcmExpCoolSts());
        }
    	inline bool operator!=(const CcmInfo &_other) const {
    		return !((*this) == _other);
    	}
    
    };



static inline const char* getTypeCollectionName() {
    static const char* typeCollectionName = "com.harman.dcif.CcmPresTypes";
    return typeCollectionName;
}

inline CommonAPI::Version getTypeCollectionVersion() {
    return CommonAPI::Version(0, 1);
}

}; // struct CcmPresTypes

} // namespace dcif
} // namespace harman
} // namespace com
} // namespace v0

namespace CommonAPI {
}


namespace std {
    //Hash for eHuCcmParam
    template<>
    struct hash<::v0::com::harman::dcif::CcmPresTypes::eHuCcmParam> {
        inline size_t operator()(const ::v0::com::harman::dcif::CcmPresTypes::eHuCcmParam& eHuCcmParam) const {
            return static_cast<int32_t>(eHuCcmParam);
        }
    };
}


// Compatibility
namespace v0_1 = v0;

#endif // V0_COM_HARMAN_DCIF_Ccm_Pres_Types_HPP_
