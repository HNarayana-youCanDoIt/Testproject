/**********************************************************************
 * Auto generated code on 2018-03-09 15:45:19
 * @ Author   COC_SWPF_DevTOOLS@harman.com
 * @ Version  1.5.5
 **********************************************************************/

#include "HMI_TATAPersWrapperImpl.hpp"
#include <persistence_client_library_file.h>
#include <persistence_client_library_key.h>
#include <persistence_client_library.h>
#include <persistence_client_library_error_def.h>
#include <persistence_client_library_utils.h>

namespace com {
namespace harman {
namespace persistence {

HMI_TATAPersWrapperImpl::HMI_TATAPersWrapperImpl(unsigned int user_no, unsigned int seat_no)
{
	//Set AppName, user_no, seat_no
	memset(mAppName,'\0',256);
	memcpy(mAppName,"HMI_TATA",256);
	mUserNo = user_no;
	mSeatNo = seat_no;

}

HMI_TATAPersWrapperImpl::~HMI_TATAPersWrapperImpl()
{

	printf("HMI_TATAPersWrapperImpl::~HMI_TATAPersWrapperImpl invoked \n");
	//DeInitialize PCL Library
	//pclDeinitLibrary();
}

HMI_TATAPersWrapperImpl *HMI_TATAPersWrapperImpl::m_instance = NULL;

HMI_TATAPersWrapperImpl* HMI_TATAPersWrapperImpl::getInstance(
		unsigned int user_no, unsigned int seat_no)
{
	if (!m_instance)
	{
		//Create the Persistency Wrapper Instance
		m_instance = new HMI_TATAPersWrapperImpl(user_no, seat_no);
	}
	return m_instance;
}

void HMI_TATAPersWrapperImpl::destroyInstance()
{
	if (m_instance)
		delete m_instance;
}

int HMI_TATAPersWrapperImpl::config(void)
{
	//Initialize PCL Library
	return pclInitLibrary(mAppName, PCL_SHUTDOWN_TYPE_NORMAL);
}

int HMI_TATAPersWrapperImpl::deinit(void)
{
	return pclDeinitLibrary();
}

int HMI_TATAPersWrapperImpl::setUserProfile(int user_no, int seat_no)
{
    int retVal = EPERS_COMMON;
    if (true == pclSetUserProfile(user_no, seat_no))
    {
        /* If everything goes well then update the user and seat no */
        mUserNo = user_no;
        mSeatNo = seat_no;
        retVal = EPERS_SUCCESS;
    }
    else
    {
        /* Do Nothing */
    }
    return retVal;
}


int HMI_TATAPersWrapperImpl::pers_setHmiHomeSlot01(Int32 data)
{
	int retVal = EPERS_COMMON;

	// Create the respective Deployable object for the data
	CommonAPI::Deployable<Int32,
			Int32Deployment_t>
			deploy_null(
				data,
				static_cast<Int32Deployment_t*> (nullptr));

	// Serialize the Data using CCAPI Msg converter and then to string
	std::string str = obj_null.fromCapi(deploy_null);
	std::cout << " Received fromCAPI:" << str.c_str() << std::endl;

	int dataLen = str.size();
	if (dataLen > 0)
	{
		char *writeBuf = new char[dataLen];
		if (NULL != writeBuf)
		{
			memset(writeBuf, '\0', dataLen);
			memcpy(writeBuf, str.c_str(), dataLen);

			for (int i = 0; i < dataLen; i++)
			{
				printf(" %02x", writeBuf[i]);
			}
			std::cout << std::endl;

			//PCL write Serialized Data
			retVal = pclKeyWriteData(PCL_LDBID_LOCAL, "null",mUserNo,mSeatNo,(unsigned char*)writeBuf, dataLen);
			delete writeBuf;
			writeBuf = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}

int HMI_TATAPersWrapperImpl::pers_getHmiHomeSlot01(Int32 *data, unsigned int size)
{
	int retVal = EPERS_COMMON;

	//Read the size of the Data using pclKeyGetSize
	int dataLen = pclKeyGetSize(PCL_LDBID_LOCAL, "null", mUserNo, mSeatNo);
	if (dataLen > 0)
	{
		char *recdata = new char[dataLen];
		if (NULL != recdata)
		{
			memset(recdata, '\0', dataLen);

			//PCL read data
			retVal = pclKeyReadData(PCL_LDBID_LOCAL,"null",mUserNo,mSeatNo,(unsigned char*) recdata, dataLen);

			std::cout << "ReadData : ";
			for (int i = 0; i < dataLen; i++) {
				printf(" %02x", recdata[i]);
			}
			std::cout << std::endl;

			std::cout << "Size of read bytes : " << retVal << std::endl;

			//check if the Size of the Data is equal to retVal (returned after PCL read)
			if(dataLen == retVal)
			{
				std::string buffer(recdata, recdata+dataLen);
				CommonAPI::Deployable<Int32,
					Int32Deployment_t>
					deploy_null(
					static_cast<Int32Deployment_t*> (nullptr));

				//DeSerialize the Data using CCAPI Msg converter
				obj_null.toCapi(buffer, deploy_null);
				(*data) = deploy_null.getValue();

			} else {
			//Do Nothing
			}
			delete recdata;
			recdata = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}



int HMI_TATAPersWrapperImpl::pers_setHmiHomeSlot02(Int32 data)
{
	int retVal = EPERS_COMMON;

	// Create the respective Deployable object for the data
	CommonAPI::Deployable<Int32,
			Int32Deployment_t>
			deploy_null(
				data,
				static_cast<Int32Deployment_t*> (nullptr));

	// Serialize the Data using CCAPI Msg converter and then to string
	std::string str = obj_null.fromCapi(deploy_null);
	std::cout << " Received fromCAPI:" << str.c_str() << std::endl;

	int dataLen = str.size();
	if (dataLen > 0)
	{
		char *writeBuf = new char[dataLen];
		if (NULL != writeBuf)
		{
			memset(writeBuf, '\0', dataLen);
			memcpy(writeBuf, str.c_str(), dataLen);

			for (int i = 0; i < dataLen; i++)
			{
				printf(" %02x", writeBuf[i]);
			}
			std::cout << std::endl;

			//PCL write Serialized Data
			retVal = pclKeyWriteData(PCL_LDBID_LOCAL, "null",mUserNo,mSeatNo,(unsigned char*)writeBuf, dataLen);
			delete writeBuf;
			writeBuf = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}

int HMI_TATAPersWrapperImpl::pers_getHmiHomeSlot02(Int32 *data, unsigned int size)
{
	int retVal = EPERS_COMMON;

	//Read the size of the Data using pclKeyGetSize
	int dataLen = pclKeyGetSize(PCL_LDBID_LOCAL, "null", mUserNo, mSeatNo);
	if (dataLen > 0)
	{
		char *recdata = new char[dataLen];
		if (NULL != recdata)
		{
			memset(recdata, '\0', dataLen);

			//PCL read data
			retVal = pclKeyReadData(PCL_LDBID_LOCAL,"null",mUserNo,mSeatNo,(unsigned char*) recdata, dataLen);

			std::cout << "ReadData : ";
			for (int i = 0; i < dataLen; i++) {
				printf(" %02x", recdata[i]);
			}
			std::cout << std::endl;

			std::cout << "Size of read bytes : " << retVal << std::endl;

			//check if the Size of the Data is equal to retVal (returned after PCL read)
			if(dataLen == retVal)
			{
				std::string buffer(recdata, recdata+dataLen);
				CommonAPI::Deployable<Int32,
					Int32Deployment_t>
					deploy_null(
					static_cast<Int32Deployment_t*> (nullptr));

				//DeSerialize the Data using CCAPI Msg converter
				obj_null.toCapi(buffer, deploy_null);
				(*data) = deploy_null.getValue();

			} else {
			//Do Nothing
			}
			delete recdata;
			recdata = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}



int HMI_TATAPersWrapperImpl::pers_setHmiHomeSlot03(Int32 data)
{
	int retVal = EPERS_COMMON;

	// Create the respective Deployable object for the data
	CommonAPI::Deployable<Int32,
			Int32Deployment_t>
			deploy_null(
				data,
				static_cast<Int32Deployment_t*> (nullptr));

	// Serialize the Data using CCAPI Msg converter and then to string
	std::string str = obj_null.fromCapi(deploy_null);
	std::cout << " Received fromCAPI:" << str.c_str() << std::endl;

	int dataLen = str.size();
	if (dataLen > 0)
	{
		char *writeBuf = new char[dataLen];
		if (NULL != writeBuf)
		{
			memset(writeBuf, '\0', dataLen);
			memcpy(writeBuf, str.c_str(), dataLen);

			for (int i = 0; i < dataLen; i++)
			{
				printf(" %02x", writeBuf[i]);
			}
			std::cout << std::endl;

			//PCL write Serialized Data
			retVal = pclKeyWriteData(PCL_LDBID_LOCAL, "null",mUserNo,mSeatNo,(unsigned char*)writeBuf, dataLen);
			delete writeBuf;
			writeBuf = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}

int HMI_TATAPersWrapperImpl::pers_getHmiHomeSlot03(Int32 *data, unsigned int size)
{
	int retVal = EPERS_COMMON;

	//Read the size of the Data using pclKeyGetSize
	int dataLen = pclKeyGetSize(PCL_LDBID_LOCAL, "null", mUserNo, mSeatNo);
	if (dataLen > 0)
	{
		char *recdata = new char[dataLen];
		if (NULL != recdata)
		{
			memset(recdata, '\0', dataLen);

			//PCL read data
			retVal = pclKeyReadData(PCL_LDBID_LOCAL,"null",mUserNo,mSeatNo,(unsigned char*) recdata, dataLen);

			std::cout << "ReadData : ";
			for (int i = 0; i < dataLen; i++) {
				printf(" %02x", recdata[i]);
			}
			std::cout << std::endl;

			std::cout << "Size of read bytes : " << retVal << std::endl;

			//check if the Size of the Data is equal to retVal (returned after PCL read)
			if(dataLen == retVal)
			{
				std::string buffer(recdata, recdata+dataLen);
				CommonAPI::Deployable<Int32,
					Int32Deployment_t>
					deploy_null(
					static_cast<Int32Deployment_t*> (nullptr));

				//DeSerialize the Data using CCAPI Msg converter
				obj_null.toCapi(buffer, deploy_null);
				(*data) = deploy_null.getValue();

			} else {
			//Do Nothing
			}
			delete recdata;
			recdata = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}



int HMI_TATAPersWrapperImpl::pers_setHmiHomeSlot04(Int32 data)
{
	int retVal = EPERS_COMMON;

	// Create the respective Deployable object for the data
	CommonAPI::Deployable<Int32,
			Int32Deployment_t>
			deploy_null(
				data,
				static_cast<Int32Deployment_t*> (nullptr));

	// Serialize the Data using CCAPI Msg converter and then to string
	std::string str = obj_null.fromCapi(deploy_null);
	std::cout << " Received fromCAPI:" << str.c_str() << std::endl;

	int dataLen = str.size();
	if (dataLen > 0)
	{
		char *writeBuf = new char[dataLen];
		if (NULL != writeBuf)
		{
			memset(writeBuf, '\0', dataLen);
			memcpy(writeBuf, str.c_str(), dataLen);

			for (int i = 0; i < dataLen; i++)
			{
				printf(" %02x", writeBuf[i]);
			}
			std::cout << std::endl;

			//PCL write Serialized Data
			retVal = pclKeyWriteData(PCL_LDBID_LOCAL, "null",mUserNo,mSeatNo,(unsigned char*)writeBuf, dataLen);
			delete writeBuf;
			writeBuf = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}

int HMI_TATAPersWrapperImpl::pers_getHmiHomeSlot04(Int32 *data, unsigned int size)
{
	int retVal = EPERS_COMMON;

	//Read the size of the Data using pclKeyGetSize
	int dataLen = pclKeyGetSize(PCL_LDBID_LOCAL, "null", mUserNo, mSeatNo);
	if (dataLen > 0)
	{
		char *recdata = new char[dataLen];
		if (NULL != recdata)
		{
			memset(recdata, '\0', dataLen);

			//PCL read data
			retVal = pclKeyReadData(PCL_LDBID_LOCAL,"null",mUserNo,mSeatNo,(unsigned char*) recdata, dataLen);

			std::cout << "ReadData : ";
			for (int i = 0; i < dataLen; i++) {
				printf(" %02x", recdata[i]);
			}
			std::cout << std::endl;

			std::cout << "Size of read bytes : " << retVal << std::endl;

			//check if the Size of the Data is equal to retVal (returned after PCL read)
			if(dataLen == retVal)
			{
				std::string buffer(recdata, recdata+dataLen);
				CommonAPI::Deployable<Int32,
					Int32Deployment_t>
					deploy_null(
					static_cast<Int32Deployment_t*> (nullptr));

				//DeSerialize the Data using CCAPI Msg converter
				obj_null.toCapi(buffer, deploy_null);
				(*data) = deploy_null.getValue();

			} else {
			//Do Nothing
			}
			delete recdata;
			recdata = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}



int HMI_TATAPersWrapperImpl::pers_setHmiHomeSlot05(Int32 data)
{
	int retVal = EPERS_COMMON;

	// Create the respective Deployable object for the data
	CommonAPI::Deployable<Int32,
			Int32Deployment_t>
			deploy_null(
				data,
				static_cast<Int32Deployment_t*> (nullptr));

	// Serialize the Data using CCAPI Msg converter and then to string
	std::string str = obj_null.fromCapi(deploy_null);
	std::cout << " Received fromCAPI:" << str.c_str() << std::endl;

	int dataLen = str.size();
	if (dataLen > 0)
	{
		char *writeBuf = new char[dataLen];
		if (NULL != writeBuf)
		{
			memset(writeBuf, '\0', dataLen);
			memcpy(writeBuf, str.c_str(), dataLen);

			for (int i = 0; i < dataLen; i++)
			{
				printf(" %02x", writeBuf[i]);
			}
			std::cout << std::endl;

			//PCL write Serialized Data
			retVal = pclKeyWriteData(PCL_LDBID_LOCAL, "null",mUserNo,mSeatNo,(unsigned char*)writeBuf, dataLen);
			delete writeBuf;
			writeBuf = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}

int HMI_TATAPersWrapperImpl::pers_getHmiHomeSlot05(Int32 *data, unsigned int size)
{
	int retVal = EPERS_COMMON;

	//Read the size of the Data using pclKeyGetSize
	int dataLen = pclKeyGetSize(PCL_LDBID_LOCAL, "null", mUserNo, mSeatNo);
	if (dataLen > 0)
	{
		char *recdata = new char[dataLen];
		if (NULL != recdata)
		{
			memset(recdata, '\0', dataLen);

			//PCL read data
			retVal = pclKeyReadData(PCL_LDBID_LOCAL,"null",mUserNo,mSeatNo,(unsigned char*) recdata, dataLen);

			std::cout << "ReadData : ";
			for (int i = 0; i < dataLen; i++) {
				printf(" %02x", recdata[i]);
			}
			std::cout << std::endl;

			std::cout << "Size of read bytes : " << retVal << std::endl;

			//check if the Size of the Data is equal to retVal (returned after PCL read)
			if(dataLen == retVal)
			{
				std::string buffer(recdata, recdata+dataLen);
				CommonAPI::Deployable<Int32,
					Int32Deployment_t>
					deploy_null(
					static_cast<Int32Deployment_t*> (nullptr));

				//DeSerialize the Data using CCAPI Msg converter
				obj_null.toCapi(buffer, deploy_null);
				(*data) = deploy_null.getValue();

			} else {
			//Do Nothing
			}
			delete recdata;
			recdata = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}



int HMI_TATAPersWrapperImpl::pers_setHmiHomeSlot06(Int32 data)
{
	int retVal = EPERS_COMMON;

	// Create the respective Deployable object for the data
	CommonAPI::Deployable<Int32,
			Int32Deployment_t>
			deploy_null(
				data,
				static_cast<Int32Deployment_t*> (nullptr));

	// Serialize the Data using CCAPI Msg converter and then to string
	std::string str = obj_null.fromCapi(deploy_null);
	std::cout << " Received fromCAPI:" << str.c_str() << std::endl;

	int dataLen = str.size();
	if (dataLen > 0)
	{
		char *writeBuf = new char[dataLen];
		if (NULL != writeBuf)
		{
			memset(writeBuf, '\0', dataLen);
			memcpy(writeBuf, str.c_str(), dataLen);

			for (int i = 0; i < dataLen; i++)
			{
				printf(" %02x", writeBuf[i]);
			}
			std::cout << std::endl;

			//PCL write Serialized Data
			retVal = pclKeyWriteData(PCL_LDBID_LOCAL, "null",mUserNo,mSeatNo,(unsigned char*)writeBuf, dataLen);
			delete writeBuf;
			writeBuf = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}

int HMI_TATAPersWrapperImpl::pers_getHmiHomeSlot06(Int32 *data, unsigned int size)
{
	int retVal = EPERS_COMMON;

	//Read the size of the Data using pclKeyGetSize
	int dataLen = pclKeyGetSize(PCL_LDBID_LOCAL, "null", mUserNo, mSeatNo);
	if (dataLen > 0)
	{
		char *recdata = new char[dataLen];
		if (NULL != recdata)
		{
			memset(recdata, '\0', dataLen);

			//PCL read data
			retVal = pclKeyReadData(PCL_LDBID_LOCAL,"null",mUserNo,mSeatNo,(unsigned char*) recdata, dataLen);

			std::cout << "ReadData : ";
			for (int i = 0; i < dataLen; i++) {
				printf(" %02x", recdata[i]);
			}
			std::cout << std::endl;

			std::cout << "Size of read bytes : " << retVal << std::endl;

			//check if the Size of the Data is equal to retVal (returned after PCL read)
			if(dataLen == retVal)
			{
				std::string buffer(recdata, recdata+dataLen);
				CommonAPI::Deployable<Int32,
					Int32Deployment_t>
					deploy_null(
					static_cast<Int32Deployment_t*> (nullptr));

				//DeSerialize the Data using CCAPI Msg converter
				obj_null.toCapi(buffer, deploy_null);
				(*data) = deploy_null.getValue();

			} else {
			//Do Nothing
			}
			delete recdata;
			recdata = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}



int HMI_TATAPersWrapperImpl::pers_setHmiTestAutomation(Int32 data)
{
	int retVal = EPERS_COMMON;

	// Create the respective Deployable object for the data
	CommonAPI::Deployable<Int32,
			Int32Deployment_t>
			deploy_null(
				data,
				static_cast<Int32Deployment_t*> (nullptr));

	// Serialize the Data using CCAPI Msg converter and then to string
	std::string str = obj_null.fromCapi(deploy_null);
	std::cout << " Received fromCAPI:" << str.c_str() << std::endl;

	int dataLen = str.size();
	if (dataLen > 0)
	{
		char *writeBuf = new char[dataLen];
		if (NULL != writeBuf)
		{
			memset(writeBuf, '\0', dataLen);
			memcpy(writeBuf, str.c_str(), dataLen);

			for (int i = 0; i < dataLen; i++)
			{
				printf(" %02x", writeBuf[i]);
			}
			std::cout << std::endl;

			//PCL write Serialized Data
			retVal = pclKeyWriteData(PCL_LDBID_LOCAL, "null",mUserNo,mSeatNo,(unsigned char*)writeBuf, dataLen);
			delete writeBuf;
			writeBuf = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}

int HMI_TATAPersWrapperImpl::pers_getHmiTestAutomation(Int32 *data, unsigned int size)
{
	int retVal = EPERS_COMMON;

	//Read the size of the Data using pclKeyGetSize
	int dataLen = pclKeyGetSize(PCL_LDBID_LOCAL, "null", mUserNo, mSeatNo);
	if (dataLen > 0)
	{
		char *recdata = new char[dataLen];
		if (NULL != recdata)
		{
			memset(recdata, '\0', dataLen);

			//PCL read data
			retVal = pclKeyReadData(PCL_LDBID_LOCAL,"null",mUserNo,mSeatNo,(unsigned char*) recdata, dataLen);

			std::cout << "ReadData : ";
			for (int i = 0; i < dataLen; i++) {
				printf(" %02x", recdata[i]);
			}
			std::cout << std::endl;

			std::cout << "Size of read bytes : " << retVal << std::endl;

			//check if the Size of the Data is equal to retVal (returned after PCL read)
			if(dataLen == retVal)
			{
				std::string buffer(recdata, recdata+dataLen);
				CommonAPI::Deployable<Int32,
					Int32Deployment_t>
					deploy_null(
					static_cast<Int32Deployment_t*> (nullptr));

				//DeSerialize the Data using CCAPI Msg converter
				obj_null.toCapi(buffer, deploy_null);
				(*data) = deploy_null.getValue();

			} else {
			//Do Nothing
			}
			delete recdata;
			recdata = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}



int HMI_TATAPersWrapperImpl::pers_setHmiSetupAudioPreset(Int32 data)
{
	int retVal = EPERS_COMMON;

	// Create the respective Deployable object for the data
	CommonAPI::Deployable<Int32,
			Int32Deployment_t>
			deploy_null(
				data,
				static_cast<Int32Deployment_t*> (nullptr));

	// Serialize the Data using CCAPI Msg converter and then to string
	std::string str = obj_null.fromCapi(deploy_null);
	std::cout << " Received fromCAPI:" << str.c_str() << std::endl;

	int dataLen = str.size();
	if (dataLen > 0)
	{
		char *writeBuf = new char[dataLen];
		if (NULL != writeBuf)
		{
			memset(writeBuf, '\0', dataLen);
			memcpy(writeBuf, str.c_str(), dataLen);

			for (int i = 0; i < dataLen; i++)
			{
				printf(" %02x", writeBuf[i]);
			}
			std::cout << std::endl;

			//PCL write Serialized Data
			retVal = pclKeyWriteData(PCL_LDBID_LOCAL, "null",mUserNo,mSeatNo,(unsigned char*)writeBuf, dataLen);
			delete writeBuf;
			writeBuf = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}

int HMI_TATAPersWrapperImpl::pers_getHmiSetupAudioPreset(Int32 *data, unsigned int size)
{
	int retVal = EPERS_COMMON;

	//Read the size of the Data using pclKeyGetSize
	int dataLen = pclKeyGetSize(PCL_LDBID_LOCAL, "null", mUserNo, mSeatNo);
	if (dataLen > 0)
	{
		char *recdata = new char[dataLen];
		if (NULL != recdata)
		{
			memset(recdata, '\0', dataLen);

			//PCL read data
			retVal = pclKeyReadData(PCL_LDBID_LOCAL,"null",mUserNo,mSeatNo,(unsigned char*) recdata, dataLen);

			std::cout << "ReadData : ";
			for (int i = 0; i < dataLen; i++) {
				printf(" %02x", recdata[i]);
			}
			std::cout << std::endl;

			std::cout << "Size of read bytes : " << retVal << std::endl;

			//check if the Size of the Data is equal to retVal (returned after PCL read)
			if(dataLen == retVal)
			{
				std::string buffer(recdata, recdata+dataLen);
				CommonAPI::Deployable<Int32,
					Int32Deployment_t>
					deploy_null(
					static_cast<Int32Deployment_t*> (nullptr));

				//DeSerialize the Data using CCAPI Msg converter
				obj_null.toCapi(buffer, deploy_null);
				(*data) = deploy_null.getValue();

			} else {
			//Do Nothing
			}
			delete recdata;
			recdata = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}



void persistence_convert_resID(unsigned long index, char *charPtr)
{
    char res_id[4];
    res_id[0] = (index >> 8) & 0xFF;
    res_id[1] = index & 0xFF;
    res_id[2] = 0x00;
    res_id[3] = 0x00;

    memset(charPtr, '\0', sizeof(res_id));
    memcpy(charPtr, res_id, sizeof(res_id));
}


} // namespace persistence
} // namespace harman
} // namespace com

