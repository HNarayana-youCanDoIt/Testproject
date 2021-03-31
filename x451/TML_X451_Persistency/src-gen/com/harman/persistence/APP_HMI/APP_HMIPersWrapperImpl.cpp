/**********************************************************************
 * Auto generated code on 2018-06-27 16:44:06
 * @ Author   COC_SWPF_DevTOOLS@harman.com
 * @ Version  1.5.5
 **********************************************************************/

#include "APP_HMIPersWrapperImpl.hpp"
#include <persistence_client_library_file.h>
#include <persistence_client_library_key.h>
#include <persistence_client_library.h>
#include <persistence_client_library_error_def.h>
#include <persistence_client_library_utils.h>

namespace com {
namespace harman {
namespace persistence {

APP_HMIPersWrapperImpl::APP_HMIPersWrapperImpl(unsigned int user_no, unsigned int seat_no)
{
	//Set AppName, user_no, seat_no
	memset(mAppName,'\0',256);
	memcpy(mAppName,"APP_HMI",256);
	mUserNo = user_no;
	mSeatNo = seat_no;

}

APP_HMIPersWrapperImpl::~APP_HMIPersWrapperImpl()
{

	printf("APP_HMIPersWrapperImpl::~APP_HMIPersWrapperImpl invoked \n");
	//DeInitialize PCL Library
	//pclDeinitLibrary();
}

APP_HMIPersWrapperImpl *APP_HMIPersWrapperImpl::m_instance = NULL;

APP_HMIPersWrapperImpl* APP_HMIPersWrapperImpl::getInstance(
		unsigned int user_no, unsigned int seat_no)
{
	if (!m_instance)
	{
		//Create the Persistency Wrapper Instance
		m_instance = new APP_HMIPersWrapperImpl(user_no, seat_no);
	}
	return m_instance;
}

void APP_HMIPersWrapperImpl::destroyInstance()
{
	if (m_instance)
		delete m_instance;
}

int APP_HMIPersWrapperImpl::config(void)
{
	//Initialize PCL Library
	return pclInitLibrary(mAppName, PCL_SHUTDOWN_TYPE_NORMAL);
}

int APP_HMIPersWrapperImpl::deinit(void)
{
	return pclDeinitLibrary();
}

int APP_HMIPersWrapperImpl::setUserProfile(int user_no, int seat_no)
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


int APP_HMIPersWrapperImpl::pers_setHmiHomeSlot01(Int32 data)
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

int APP_HMIPersWrapperImpl::pers_getHmiHomeSlot01(Int32 *data, unsigned int size)
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



int APP_HMIPersWrapperImpl::pers_setHmiHomeSlot02(Int32 data)
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

int APP_HMIPersWrapperImpl::pers_getHmiHomeSlot02(Int32 *data, unsigned int size)
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



int APP_HMIPersWrapperImpl::pers_setHmiHomeSlot03(Int32 data)
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

int APP_HMIPersWrapperImpl::pers_getHmiHomeSlot03(Int32 *data, unsigned int size)
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



int APP_HMIPersWrapperImpl::pers_setHmiHomeSlot04(Int32 data)
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

int APP_HMIPersWrapperImpl::pers_getHmiHomeSlot04(Int32 *data, unsigned int size)
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



int APP_HMIPersWrapperImpl::pers_setHmiHomeSlot05(Int32 data)
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

int APP_HMIPersWrapperImpl::pers_getHmiHomeSlot05(Int32 *data, unsigned int size)
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



int APP_HMIPersWrapperImpl::pers_setHmiHomeSlot06(Int32 data)
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

int APP_HMIPersWrapperImpl::pers_getHmiHomeSlot06(Int32 *data, unsigned int size)
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



int APP_HMIPersWrapperImpl::pers_setHmiSetupSMSNotifyType(Int32 data)
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

int APP_HMIPersWrapperImpl::pers_getHmiSetupSMSNotifyType(Int32 *data, unsigned int size)
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



int APP_HMIPersWrapperImpl::pers_setHmiSetupSMSConfigSelection(Int32 data)
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

int APP_HMIPersWrapperImpl::pers_getHmiSetupSMSConfigSelection(Int32 *data, unsigned int size)
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



int APP_HMIPersWrapperImpl::pers_setHmiTestAutomation(Int32 data)
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

int APP_HMIPersWrapperImpl::pers_getHmiTestAutomation(Int32 *data, unsigned int size)
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



int APP_HMIPersWrapperImpl::pers_setHmiFavoriteScrOptionSelection(Int32 data)
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

int APP_HMIPersWrapperImpl::pers_getHmiFavoriteScrOptionSelection(Int32 *data, unsigned int size)
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



int APP_HMIPersWrapperImpl::pers_setHmiSetupCustomSMS01(String data)
{
	int retVal = EPERS_COMMON;

	// Create the respective Deployable object for the data
	CommonAPI::Deployable<String,
			StringDeployment_t>
			deploy_(
				data,
				static_cast<StringDeployment_t*> (nullptr));

	// Serialize the Data using CCAPI Msg converter and then to string
	std::string str = obj_.fromCapi(deploy_);
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
			retVal = pclKeyWriteData(PCL_LDBID_LOCAL, "",mUserNo,mSeatNo,(unsigned char*)writeBuf, dataLen);
			delete writeBuf;
			writeBuf = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}

int APP_HMIPersWrapperImpl::pers_getHmiSetupCustomSMS01(String *data, unsigned int size)
{
	int retVal = EPERS_COMMON;

	//Read the size of the Data using pclKeyGetSize
	int dataLen = pclKeyGetSize(PCL_LDBID_LOCAL, "", mUserNo, mSeatNo);
	if (dataLen > 0)
	{
		char *recdata = new char[dataLen];
		if (NULL != recdata)
		{
			memset(recdata, '\0', dataLen);

			//PCL read data
			retVal = pclKeyReadData(PCL_LDBID_LOCAL,"",mUserNo,mSeatNo,(unsigned char*) recdata, dataLen);

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
				CommonAPI::Deployable<String,
					StringDeployment_t>
					deploy_(
					static_cast<StringDeployment_t*> (nullptr));

				//DeSerialize the Data using CCAPI Msg converter
				obj_.toCapi(buffer, deploy_);
				(*data) = deploy_.getValue();

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



int APP_HMIPersWrapperImpl::pers_setHmiSetupCustomSMS02(String data)
{
	int retVal = EPERS_COMMON;

	// Create the respective Deployable object for the data
	CommonAPI::Deployable<String,
			StringDeployment_t>
			deploy_(
				data,
				static_cast<StringDeployment_t*> (nullptr));

	// Serialize the Data using CCAPI Msg converter and then to string
	std::string str = obj_.fromCapi(deploy_);
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
			retVal = pclKeyWriteData(PCL_LDBID_LOCAL, "",mUserNo,mSeatNo,(unsigned char*)writeBuf, dataLen);
			delete writeBuf;
			writeBuf = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}

int APP_HMIPersWrapperImpl::pers_getHmiSetupCustomSMS02(String *data, unsigned int size)
{
	int retVal = EPERS_COMMON;

	//Read the size of the Data using pclKeyGetSize
	int dataLen = pclKeyGetSize(PCL_LDBID_LOCAL, "", mUserNo, mSeatNo);
	if (dataLen > 0)
	{
		char *recdata = new char[dataLen];
		if (NULL != recdata)
		{
			memset(recdata, '\0', dataLen);

			//PCL read data
			retVal = pclKeyReadData(PCL_LDBID_LOCAL,"",mUserNo,mSeatNo,(unsigned char*) recdata, dataLen);

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
				CommonAPI::Deployable<String,
					StringDeployment_t>
					deploy_(
					static_cast<StringDeployment_t*> (nullptr));

				//DeSerialize the Data using CCAPI Msg converter
				obj_.toCapi(buffer, deploy_);
				(*data) = deploy_.getValue();

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



int APP_HMIPersWrapperImpl::pers_setHmiSetupCustomSMS03(String data)
{
	int retVal = EPERS_COMMON;

	// Create the respective Deployable object for the data
	CommonAPI::Deployable<String,
			StringDeployment_t>
			deploy_(
				data,
				static_cast<StringDeployment_t*> (nullptr));

	// Serialize the Data using CCAPI Msg converter and then to string
	std::string str = obj_.fromCapi(deploy_);
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
			retVal = pclKeyWriteData(PCL_LDBID_LOCAL, "",mUserNo,mSeatNo,(unsigned char*)writeBuf, dataLen);
			delete writeBuf;
			writeBuf = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}

int APP_HMIPersWrapperImpl::pers_getHmiSetupCustomSMS03(String *data, unsigned int size)
{
	int retVal = EPERS_COMMON;

	//Read the size of the Data using pclKeyGetSize
	int dataLen = pclKeyGetSize(PCL_LDBID_LOCAL, "", mUserNo, mSeatNo);
	if (dataLen > 0)
	{
		char *recdata = new char[dataLen];
		if (NULL != recdata)
		{
			memset(recdata, '\0', dataLen);

			//PCL read data
			retVal = pclKeyReadData(PCL_LDBID_LOCAL,"",mUserNo,mSeatNo,(unsigned char*) recdata, dataLen);

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
				CommonAPI::Deployable<String,
					StringDeployment_t>
					deploy_(
					static_cast<StringDeployment_t*> (nullptr));

				//DeSerialize the Data using CCAPI Msg converter
				obj_.toCapi(buffer, deploy_);
				(*data) = deploy_.getValue();

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



int APP_HMIPersWrapperImpl::pers_setHmiSetupCustomSMS04(String data)
{
	int retVal = EPERS_COMMON;

	// Create the respective Deployable object for the data
	CommonAPI::Deployable<String,
			StringDeployment_t>
			deploy_(
				data,
				static_cast<StringDeployment_t*> (nullptr));

	// Serialize the Data using CCAPI Msg converter and then to string
	std::string str = obj_.fromCapi(deploy_);
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
			retVal = pclKeyWriteData(PCL_LDBID_LOCAL, "",mUserNo,mSeatNo,(unsigned char*)writeBuf, dataLen);
			delete writeBuf;
			writeBuf = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}

int APP_HMIPersWrapperImpl::pers_getHmiSetupCustomSMS04(String *data, unsigned int size)
{
	int retVal = EPERS_COMMON;

	//Read the size of the Data using pclKeyGetSize
	int dataLen = pclKeyGetSize(PCL_LDBID_LOCAL, "", mUserNo, mSeatNo);
	if (dataLen > 0)
	{
		char *recdata = new char[dataLen];
		if (NULL != recdata)
		{
			memset(recdata, '\0', dataLen);

			//PCL read data
			retVal = pclKeyReadData(PCL_LDBID_LOCAL,"",mUserNo,mSeatNo,(unsigned char*) recdata, dataLen);

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
				CommonAPI::Deployable<String,
					StringDeployment_t>
					deploy_(
					static_cast<StringDeployment_t*> (nullptr));

				//DeSerialize the Data using CCAPI Msg converter
				obj_.toCapi(buffer, deploy_);
				(*data) = deploy_.getValue();

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



int APP_HMIPersWrapperImpl::pers_setHmiSetupCustomSMS05(String data)
{
	int retVal = EPERS_COMMON;

	// Create the respective Deployable object for the data
	CommonAPI::Deployable<String,
			StringDeployment_t>
			deploy_(
				data,
				static_cast<StringDeployment_t*> (nullptr));

	// Serialize the Data using CCAPI Msg converter and then to string
	std::string str = obj_.fromCapi(deploy_);
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
			retVal = pclKeyWriteData(PCL_LDBID_LOCAL, "",mUserNo,mSeatNo,(unsigned char*)writeBuf, dataLen);
			delete writeBuf;
			writeBuf = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}

int APP_HMIPersWrapperImpl::pers_getHmiSetupCustomSMS05(String *data, unsigned int size)
{
	int retVal = EPERS_COMMON;

	//Read the size of the Data using pclKeyGetSize
	int dataLen = pclKeyGetSize(PCL_LDBID_LOCAL, "", mUserNo, mSeatNo);
	if (dataLen > 0)
	{
		char *recdata = new char[dataLen];
		if (NULL != recdata)
		{
			memset(recdata, '\0', dataLen);

			//PCL read data
			retVal = pclKeyReadData(PCL_LDBID_LOCAL,"",mUserNo,mSeatNo,(unsigned char*) recdata, dataLen);

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
				CommonAPI::Deployable<String,
					StringDeployment_t>
					deploy_(
					static_cast<StringDeployment_t*> (nullptr));

				//DeSerialize the Data using CCAPI Msg converter
				obj_.toCapi(buffer, deploy_);
				(*data) = deploy_.getValue();

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



int APP_HMIPersWrapperImpl::pers_setHmiSetupCustomSMS06(String data)
{
	int retVal = EPERS_COMMON;

	// Create the respective Deployable object for the data
	CommonAPI::Deployable<String,
			StringDeployment_t>
			deploy_(
				data,
				static_cast<StringDeployment_t*> (nullptr));

	// Serialize the Data using CCAPI Msg converter and then to string
	std::string str = obj_.fromCapi(deploy_);
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
			retVal = pclKeyWriteData(PCL_LDBID_LOCAL, "",mUserNo,mSeatNo,(unsigned char*)writeBuf, dataLen);
			delete writeBuf;
			writeBuf = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}

int APP_HMIPersWrapperImpl::pers_getHmiSetupCustomSMS06(String *data, unsigned int size)
{
	int retVal = EPERS_COMMON;

	//Read the size of the Data using pclKeyGetSize
	int dataLen = pclKeyGetSize(PCL_LDBID_LOCAL, "", mUserNo, mSeatNo);
	if (dataLen > 0)
	{
		char *recdata = new char[dataLen];
		if (NULL != recdata)
		{
			memset(recdata, '\0', dataLen);

			//PCL read data
			retVal = pclKeyReadData(PCL_LDBID_LOCAL,"",mUserNo,mSeatNo,(unsigned char*) recdata, dataLen);

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
				CommonAPI::Deployable<String,
					StringDeployment_t>
					deploy_(
					static_cast<StringDeployment_t*> (nullptr));

				//DeSerialize the Data using CCAPI Msg converter
				obj_.toCapi(buffer, deploy_);
				(*data) = deploy_.getValue();

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



int APP_HMIPersWrapperImpl::pers_setHmiSetupCustomSMS07(String data)
{
	int retVal = EPERS_COMMON;

	// Create the respective Deployable object for the data
	CommonAPI::Deployable<String,
			StringDeployment_t>
			deploy_(
				data,
				static_cast<StringDeployment_t*> (nullptr));

	// Serialize the Data using CCAPI Msg converter and then to string
	std::string str = obj_.fromCapi(deploy_);
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
			retVal = pclKeyWriteData(PCL_LDBID_LOCAL, "",mUserNo,mSeatNo,(unsigned char*)writeBuf, dataLen);
			delete writeBuf;
			writeBuf = NULL;
		} else {
			retVal = EPERS_DESER_ALLOCMEM;
		}
	}
	return retVal;
}

int APP_HMIPersWrapperImpl::pers_getHmiSetupCustomSMS07(String *data, unsigned int size)
{
	int retVal = EPERS_COMMON;

	//Read the size of the Data using pclKeyGetSize
	int dataLen = pclKeyGetSize(PCL_LDBID_LOCAL, "", mUserNo, mSeatNo);
	if (dataLen > 0)
	{
		char *recdata = new char[dataLen];
		if (NULL != recdata)
		{
			memset(recdata, '\0', dataLen);

			//PCL read data
			retVal = pclKeyReadData(PCL_LDBID_LOCAL,"",mUserNo,mSeatNo,(unsigned char*) recdata, dataLen);

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
				CommonAPI::Deployable<String,
					StringDeployment_t>
					deploy_(
					static_cast<StringDeployment_t*> (nullptr));

				//DeSerialize the Data using CCAPI Msg converter
				obj_.toCapi(buffer, deploy_);
				(*data) = deploy_.getValue();

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



int APP_HMIPersWrapperImpl::pers_setHmiSetupThemePreset(Int32 data)
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

int APP_HMIPersWrapperImpl::pers_getHmiSetupThemePreset(Int32 *data, unsigned int size)
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



int APP_HMIPersWrapperImpl::pers_setHmiSetupAudioPreset(Int32 data)
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

int APP_HMIPersWrapperImpl::pers_getHmiSetupAudioPreset(Int32 *data, unsigned int size)
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

