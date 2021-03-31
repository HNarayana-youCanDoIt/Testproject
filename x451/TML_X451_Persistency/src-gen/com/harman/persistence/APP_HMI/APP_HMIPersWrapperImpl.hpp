/**********************************************************************
 * Auto generated code on 2018-06-27 16:44:06
 * @ Author   COC_SWPF_DevTOOLS@harman.com
 * @ Version  1.5.5
 **********************************************************************/

#ifndef APP_HMI_PERSWRAPPERIMPL_HPP_
#define APP_HMI_PERSWRAPPERIMPL_HPP_


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <CCAPIMsgToCapiConverter.hpp>
#include <CommonAPI/CommonAPI.hpp>


namespace com {
	namespace harman {
		namespace persistence {

			class APP_HMIPersWrapperImpl
			{

				static APP_HMIPersWrapperImpl *m_instance;
				char mAppName[256];
				unsigned int mUserNo;
				unsigned int mSeatNo;

				APP_HMIPersWrapperImpl(unsigned int user_no, unsigned int seat_no);

				virtual ~APP_HMIPersWrapperImpl();
				
				//CCAPIMsgConverter object for null
				CommonAPI::CCAPI::CCAPIMsgToCapiConverter < CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>, CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>> obj_null;
				
				//CCAPIMsgConverter object for null
				CommonAPI::CCAPI::CCAPIMsgToCapiConverter < CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>, CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>> obj_null;
				
				//CCAPIMsgConverter object for null
				CommonAPI::CCAPI::CCAPIMsgToCapiConverter < CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>, CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>> obj_null;
				
				//CCAPIMsgConverter object for null
				CommonAPI::CCAPI::CCAPIMsgToCapiConverter < CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>, CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>> obj_null;
				
				//CCAPIMsgConverter object for null
				CommonAPI::CCAPI::CCAPIMsgToCapiConverter < CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>, CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>> obj_null;
				
				//CCAPIMsgConverter object for null
				CommonAPI::CCAPI::CCAPIMsgToCapiConverter < CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>, CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>> obj_null;
				
				//CCAPIMsgConverter object for null
				CommonAPI::CCAPI::CCAPIMsgToCapiConverter < CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>, CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>> obj_null;
				
				//CCAPIMsgConverter object for null
				CommonAPI::CCAPI::CCAPIMsgToCapiConverter < CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>, CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>> obj_null;
				
				//CCAPIMsgConverter object for null
				CommonAPI::CCAPI::CCAPIMsgToCapiConverter < CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>, CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>> obj_null;
				
				//CCAPIMsgConverter object for null
				CommonAPI::CCAPI::CCAPIMsgToCapiConverter < CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>, CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>> obj_null;
				
				//CCAPIMsgConverter object for 
				CommonAPI::CCAPI::CCAPIMsgToCapiConverter < CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<std::string, std::stringDeployment_t >>, CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<std::string, std::stringDeployment_t >>> obj_;
				
				//CCAPIMsgConverter object for 
				CommonAPI::CCAPI::CCAPIMsgToCapiConverter < CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<std::string, std::stringDeployment_t >>, CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<std::string, std::stringDeployment_t >>> obj_;
				
				//CCAPIMsgConverter object for 
				CommonAPI::CCAPI::CCAPIMsgToCapiConverter < CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<std::string, std::stringDeployment_t >>, CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<std::string, std::stringDeployment_t >>> obj_;
				
				//CCAPIMsgConverter object for 
				CommonAPI::CCAPI::CCAPIMsgToCapiConverter < CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<std::string, std::stringDeployment_t >>, CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<std::string, std::stringDeployment_t >>> obj_;
				
				//CCAPIMsgConverter object for 
				CommonAPI::CCAPI::CCAPIMsgToCapiConverter < CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<std::string, std::stringDeployment_t >>, CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<std::string, std::stringDeployment_t >>> obj_;
				
				//CCAPIMsgConverter object for 
				CommonAPI::CCAPI::CCAPIMsgToCapiConverter < CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<std::string, std::stringDeployment_t >>, CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<std::string, std::stringDeployment_t >>> obj_;
				
				//CCAPIMsgConverter object for 
				CommonAPI::CCAPI::CCAPIMsgToCapiConverter < CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<std::string, std::stringDeployment_t >>, CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<std::string, std::stringDeployment_t >>> obj_;
				
				//CCAPIMsgConverter object for null
				CommonAPI::CCAPI::CCAPIMsgToCapiConverter < CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>, CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>> obj_null;
				
				//CCAPIMsgConverter object for null
				CommonAPI::CCAPI::CCAPIMsgToCapiConverter < CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>, CommonAPI::CCAPI::CCAPIMsgSerializableArguments<
					CommonAPI::Deployable<int32_t, int32_tDeployment_t >>> obj_null;
				
			public:

				static APP_HMIPersWrapperImpl* getInstance(unsigned int user_no, unsigned int seat_no);

				static void destroyInstance();

				int config(void);

				int deinit(void);

				int setUserProfile(int user_no, int seat_no);

				
				//Key Value Based Resource API's
				virtual int pers_setHmiHomeSlot01(int32_t data);
				virtual int pers_getHmiHomeSlot01(int32_t *data,unsigned int size);
				
				//Key Value Based Resource API's
				virtual int pers_setHmiHomeSlot02(int32_t data);
				virtual int pers_getHmiHomeSlot02(int32_t *data,unsigned int size);
				
				//Key Value Based Resource API's
				virtual int pers_setHmiHomeSlot03(int32_t data);
				virtual int pers_getHmiHomeSlot03(int32_t *data,unsigned int size);
				
				//Key Value Based Resource API's
				virtual int pers_setHmiHomeSlot04(int32_t data);
				virtual int pers_getHmiHomeSlot04(int32_t *data,unsigned int size);
				
				//Key Value Based Resource API's
				virtual int pers_setHmiHomeSlot05(int32_t data);
				virtual int pers_getHmiHomeSlot05(int32_t *data,unsigned int size);
				
				//Key Value Based Resource API's
				virtual int pers_setHmiHomeSlot06(int32_t data);
				virtual int pers_getHmiHomeSlot06(int32_t *data,unsigned int size);
				
				//Key Value Based Resource API's
				virtual int pers_setHmiSetupSMSNotifyType(int32_t data);
				virtual int pers_getHmiSetupSMSNotifyType(int32_t *data,unsigned int size);
				
				//Key Value Based Resource API's
				virtual int pers_setHmiSetupSMSConfigSelection(int32_t data);
				virtual int pers_getHmiSetupSMSConfigSelection(int32_t *data,unsigned int size);
				
				//Key Value Based Resource API's
				virtual int pers_setHmiTestAutomation(int32_t data);
				virtual int pers_getHmiTestAutomation(int32_t *data,unsigned int size);
				
				//Key Value Based Resource API's
				virtual int pers_setHmiFavoriteScrOptionSelection(int32_t data);
				virtual int pers_getHmiFavoriteScrOptionSelection(int32_t *data,unsigned int size);
				
				//Key Value Based Resource API's
				virtual int pers_setHmiSetupCustomSMS01(std::string data);
				virtual int pers_getHmiSetupCustomSMS01(std::string *data,unsigned int size);
				
				//Key Value Based Resource API's
				virtual int pers_setHmiSetupCustomSMS02(std::string data);
				virtual int pers_getHmiSetupCustomSMS02(std::string *data,unsigned int size);
				
				//Key Value Based Resource API's
				virtual int pers_setHmiSetupCustomSMS03(std::string data);
				virtual int pers_getHmiSetupCustomSMS03(std::string *data,unsigned int size);
				
				//Key Value Based Resource API's
				virtual int pers_setHmiSetupCustomSMS04(std::string data);
				virtual int pers_getHmiSetupCustomSMS04(std::string *data,unsigned int size);
				
				//Key Value Based Resource API's
				virtual int pers_setHmiSetupCustomSMS05(std::string data);
				virtual int pers_getHmiSetupCustomSMS05(std::string *data,unsigned int size);
				
				//Key Value Based Resource API's
				virtual int pers_setHmiSetupCustomSMS06(std::string data);
				virtual int pers_getHmiSetupCustomSMS06(std::string *data,unsigned int size);
				
				//Key Value Based Resource API's
				virtual int pers_setHmiSetupCustomSMS07(std::string data);
				virtual int pers_getHmiSetupCustomSMS07(std::string *data,unsigned int size);
				
				//Key Value Based Resource API's
				virtual int pers_setHmiSetupThemePreset(int32_t data);
				virtual int pers_getHmiSetupThemePreset(int32_t *data,unsigned int size);
				
				//Key Value Based Resource API's
				virtual int pers_setHmiSetupAudioPreset(int32_t data);
				virtual int pers_getHmiSetupAudioPreset(int32_t *data,unsigned int size);
				

				//System settings E2P data
				void persistence_convert_resID(unsigned long index, char *charPtr);

				
			};

		} // namespace persistence
	} // namespace harman
} // namespace com

#endif APP_HMI_PERSWRAPPERIMPL_HPP_
