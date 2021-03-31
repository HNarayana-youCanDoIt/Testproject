#ifndef CVERSIONMANAGERRESOURCEIMPLTEST_H
#define CVERSIONMANAGERRESOURCEIMPLTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include<gmock/gmock.h>

class CVersionManagerResourceImpl;
using namespace std;


class CVersionManagerResourceImplTest : public ::testing::Test
{
protected:
    CVersionManagerResourceImpl* m_pVersionManagerResourceImpl;

    virtual void SetUp();
    virtual void TearDown();
};

//class MockVersionManagerResource : public CVersionManagerResourceImpl {
//public:
//    MOCK_METHOD1(onVersionMismatchEventStatusCb, void(versionmanagertypes_tata::VersionMismatchDetails_e eMismatchType));
//    MOCK_METHOD1(versionManagerStatusCb, void(CommonAPI::AvailabilityStatus status));
//    MOCK_METHOD2(get16RPartNumberAsyncCb, void(const CommonAPI::CallStatus& status, const versionmanagertypes_tata::_16RPartDetails_t &t_16RpartInfo));
//    MOCK_METHOD2(getVersionDetailsAsyncCb, void(const CommonAPI::CallStatus& status, const versionmanagertypes_tata::versionInfo_t &t_versionInfo));
//    MOCK_METHOD2(getPowerModeCfgTypeAsyncCb, void(const CommonAPI::CallStatus& status, const versionmanagertypes_tata::_16RPartDetails_t& objPowerModeConfigInfo));

//};



#endif // CVERSIONMANAGERRESOURCEIMPLTEST_H
