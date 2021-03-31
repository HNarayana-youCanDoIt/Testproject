/**********************************************************************
 * Auto generated code on 2018-03-09 15:45:19
 * @ Author   COC_SWPF_DevTOOLS@harman.com
 * @ Version  1.5.5
 **********************************************************************/

#ifndef HMI_TATA_PERSWRAPPERIMPL_HPP_
#define HMI_TATA_PERSWRAPPERIMPL_HPP_


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <CCAPIMsgToCapiConverter.hpp>
#include <CommonAPI/CommonAPI.hpp>


namespace com {
	namespace harman {
		namespace persistence {

			class HMI_TATAPersWrapperImpl
			{

				static HMI_TATAPersWrapperImpl *m_instance;
				char mAppName[256];
				unsigned int mUserNo;
				unsigned int mSeatNo;

				HMI_TATAPersWrapperImpl(unsigned int user_no, unsigned int seat_no);

				virtual ~HMI_TATAPersWrapperImpl();
				
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
				
			public:

				static HMI_TATAPersWrapperImpl* getInstance(unsigned int user_no, unsigned int seat_no);

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
				virtual int pers_setHmiTestAutomation(int32_t data);
				virtual int pers_getHmiTestAutomation(int32_t *data,unsigned int size);
				
				//Key Value Based Resource API's
				virtual int pers_setHmiSetupAudioPreset(int32_t data);
				virtual int pers_getHmiSetupAudioPreset(int32_t *data,unsigned int size);
				

				//System settings E2P data
				void persistence_convert_resID(unsigned long index, char *charPtr);

				
			};

		} // namespace persistence
	} // namespace harman
} // namespace com

#endif HMI_TATA_PERSWRAPPERIMPL_HPP_
