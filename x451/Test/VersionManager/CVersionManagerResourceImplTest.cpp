#include "CVersionManagerResourceImplTest.h"
#include "VersionManagerResource/implementations/CVersionManagerResourceImpl.h"
void CVersionManagerResourceImplTest::SetUp()
{
    m_pVersionManagerResourceImpl = new CVersionManagerResourceImpl();
}

void CVersionManagerResourceImplTest::TearDown()
{
    delete m_pVersionManagerResourceImpl;
}

TEST_F(CVersionManagerResourceImplTest, CheckVersionManagerResourceImpInstanceIsNotNull)
{
    ASSERT_TRUE(m_pVersionManagerResourceImpl != nullptr) << "CVersionManagerResourceImplTest Constructor PASSED";
}

TEST_F(CVersionManagerResourceImplTest, CheckForGetterOfVersionDetailsAsyncCb)
{
    versionmanagertypes_tata::versionInfo_t versionInfo;

    versionInfo.setS_versionName("SOC");
    versionInfo.setS_versionData("1.1");
    versionInfo.setS_versionReleasedDate("20-12-2019");
    versionInfo.setE_versionStatus(versionmanagertypes_tata::InformationStatus_e::STATUS_INFO_AVAILABLE);

    m_pVersionManagerResourceImpl->getVersionDetailsAsyncCb(CallStatus::SUCCESS, versionInfo);

    CVersionManagerEnums::SVersionInformation objVersionInformation = m_pVersionManagerResourceImpl->fetchVersionInfo();
    EXPECT_STREQ((objVersionInformation.versionReleasedDate).c_str(), "20-12-2019");
    EXPECT_STREQ((objVersionInformation.versionData).c_str(), "1.1");
    EXPECT_STREQ((objVersionInformation.versionName).c_str(), "SOC");



    versionInfo.setE_versionStatus(versionmanagertypes_tata::InformationStatus_e::STATUS_INFO_NOT_AVAILABLE);


    m_pVersionManagerResourceImpl->getVersionDetailsAsyncCb(CallStatus::SUCCESS, versionInfo);
    m_pVersionManagerResourceImpl->getVersionDetailsAsyncCb(CallStatus::REMOTE_ERROR, versionInfo);
    versionInfo.setE_versionStatus(versionmanagertypes_tata::InformationStatus_e::STATUS_INFO_AVAILABLE);
    m_pVersionManagerResourceImpl->m_pVersionManagerEventProvider = NULL;
    m_pVersionManagerResourceImpl->getVersionDetailsAsyncCb(CallStatus::SUCCESS, versionInfo);

}

TEST_F(CVersionManagerResourceImplTest, CheckVersionManagerResourceImpInitializedVariables)
{
    EXPECT_STREQ((m_pVersionManagerResourceImpl->VEHICLE_ID_NUMBER).c_str() , "VEHICLE_ID_NUMBER");
    EXPECT_STREQ((m_pVersionManagerResourceImpl->BUTTON_PANEL_16R_NUMBER_ECU_HW).c_str() , "BUTTON_PANEL_16R_NUMBER_ECU_HW");
    EXPECT_STREQ((m_pVersionManagerResourceImpl->DISPLAY_16R_NUMBER_ECU_HW).c_str() , "DISPLAY_16R_NUMBER_ECU_HW");
    EXPECT_STREQ((m_pVersionManagerResourceImpl->PARAMETERIZATION_PART_NUMBER).c_str() , "PARAMETERIZATION_PART_NUMBER");
    EXPECT_STREQ((m_pVersionManagerResourceImpl->SILVERBOX_HARDWARE_PART_NUMBER).c_str() , "SILVERBOX_HARDWARE_PART_NUMBER");
    EXPECT_STREQ((m_pVersionManagerResourceImpl->CONTAINER_PART_NUMBER).c_str() , "CONTAINER_PART_NUMBER");
    EXPECT_STREQ((m_pVersionManagerResourceImpl->SOC).c_str() , "SOC");
    EXPECT_STREQ((m_pVersionManagerResourceImpl->BUTTON_PANEL).c_str() , "BUTTON_PANEL");
    EXPECT_STREQ((m_pVersionManagerResourceImpl->DISPLAY).c_str() , "DISPLAY");
    EXPECT_STREQ((m_pVersionManagerResourceImpl->VEHICLE_CFG_INFO_NUMBER).c_str() , "VEHICLE_CFG_INFO");
}

TEST_F(CVersionManagerResourceImplTest, CheckForCodeCoverageWithOtherFunctions)
{
    m_pVersionManagerResourceImpl->versionManagerStatusCb(AvailabilityStatus::AVAILABLE);
    m_pVersionManagerResourceImpl->onVersionMismatchEventStatusCb(versionmanagertypes_tata::VersionMismatchDetails_e::BP_DM_VERSION_MISMATCH);

    versionmanagertypes_tata::_16RPartDetails_t _16Rdetails;
    _16Rdetails.setS_16RPartName("VEHICLE_ID_NUMBER");
    _16Rdetails.setS_16RPartData("123");
    _16Rdetails.setE_PartStatus(versionmanagertypes_tata::InformationStatus_e::STATUS_INFO_AVAILABLE);
    m_pVersionManagerResourceImpl->get16RPartNumberAsyncCb(CommonAPI::CallStatus::SUCCESS, _16Rdetails);

    _16Rdetails.setS_16RPartName("VEHICLE_CFG_INFO");
    m_pVersionManagerResourceImpl->get16RPartNumberAsyncCb(CommonAPI::CallStatus::SUCCESS, _16Rdetails);

    _16Rdetails.setS_16RPartName("BUTTON_PANEL_16R_NUMBER_ECU_HW");
    m_pVersionManagerResourceImpl->get16RPartNumberAsyncCb(CommonAPI::CallStatus::SUCCESS, _16Rdetails);

    _16Rdetails.setS_16RPartName("DISPLAY_16R_NUMBER_ECU_HW");
    m_pVersionManagerResourceImpl->get16RPartNumberAsyncCb(CommonAPI::CallStatus::SUCCESS, _16Rdetails);

    _16Rdetails.setS_16RPartName("PARAMETERIZATION_PART_NUMBER");
    m_pVersionManagerResourceImpl->get16RPartNumberAsyncCb(CommonAPI::CallStatus::SUCCESS, _16Rdetails);

    _16Rdetails.setS_16RPartName("SILVERBOX_HARDWARE_PART_NUMBER");
    m_pVersionManagerResourceImpl->get16RPartNumberAsyncCb(CommonAPI::CallStatus::SUCCESS, _16Rdetails);

    _16Rdetails.setS_16RPartName("CONTAINER_PART_NUMBER");
    m_pVersionManagerResourceImpl->get16RPartNumberAsyncCb(CommonAPI::CallStatus::SUCCESS, _16Rdetails);

    _16Rdetails.setS_16RPartName("VEHICLE_ID_R");
    m_pVersionManagerResourceImpl->get16RPartNumberAsyncCb(CommonAPI::CallStatus::SUCCESS, _16Rdetails);




    _16Rdetails.setS_16RPartName("VEHICLE_ID_NUMBER");
    m_pVersionManagerResourceImpl->get16RPartNumberAsyncCb(CommonAPI::CallStatus::REMOTE_ERROR, _16Rdetails);

    versionmanagertypes_tata::versionInfo_t versionInfo;
    versionInfo.setS_versionName("SOC");
    versionInfo.setS_versionData("123");
    versionInfo.setS_versionReleasedDate("101010");
    versionInfo.setE_versionStatus(versionmanagertypes_tata::InformationStatus_e::STATUS_INFO_AVAILABLE);
    m_pVersionManagerResourceImpl->getVersionDetailsAsyncCb(CommonAPI::CallStatus::SUCCESS, versionInfo);

    versionInfo.setS_versionName("BUTTON_PANEL");
    m_pVersionManagerResourceImpl->getVersionDetailsAsyncCb(CommonAPI::CallStatus::SUCCESS, versionInfo);

    versionInfo.setS_versionName("DISPLAY");
    m_pVersionManagerResourceImpl->getVersionDetailsAsyncCb(CommonAPI::CallStatus::SUCCESS, versionInfo);
    versionInfo.setS_versionName("NOT_VALID");
    m_pVersionManagerResourceImpl->getVersionDetailsAsyncCb(CommonAPI::CallStatus::SUCCESS, versionInfo);

    versionInfo.setS_versionName("DISPLAY");
    m_pVersionManagerResourceImpl->getVersionDetailsAsyncCb(CommonAPI::CallStatus::REMOTE_ERROR, versionInfo);

    m_pVersionManagerResourceImpl->m_pVersionManagerEventProvider = NULL;
    m_pVersionManagerResourceImpl->getVersionDetailsAsyncCb(CommonAPI::CallStatus::SUCCESS, versionInfo);

    m_pVersionManagerResourceImpl->m_pVersionManagerEventProvider = NULL;
    m_pVersionManagerResourceImpl->get16RPartNumberAsyncCb(CommonAPI::CallStatus::SUCCESS, _16Rdetails);

}

TEST_F(CVersionManagerResourceImplTest, CheckForCodeCoverageWithOtherFunctions2)
{
    m_pVersionManagerResourceImpl->versionManagerStatusCb(AvailabilityStatus::NOT_AVAILABLE);
    m_pVersionManagerResourceImpl->onVersionMismatchEventStatusCb(versionmanagertypes_tata::VersionMismatchDetails_e::NO_VERSION_MISMATCH);
    versionmanagertypes_tata::_16RPartDetails_t powermode;
    powermode.setE_PartStatus(versionmanagertypes_tata::InformationStatus_e::STATUS_INFO_AVAILABLE);
    powermode.setS_16RPartData("21");
    powermode.setS_16RPartName("powerModeCfgType");

    m_pVersionManagerResourceImpl->getPowerModeCfgTypeAsyncCb(CommonAPI::CallStatus::SUCCESS, powermode);
}
