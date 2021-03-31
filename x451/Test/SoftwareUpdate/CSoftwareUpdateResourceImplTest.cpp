#include "CSoftwareUpdateResourceImplTest.h"
#include "SoftwareUpdateResource/implementations/CSoftwareUpdateResourceImpl.h"
void CSoftwareUpdateResourceImplTest::SetUp()
{
    m_pSoftwareUpdateResourceImpl = new CSoftwareUpdateResourceImpl();
}

void CSoftwareUpdateResourceImplTest::TearDown()
{
    delete m_pSoftwareUpdateResourceImpl;
}

TEST_F(CSoftwareUpdateResourceImplTest, CheckSoftwareUpdateResourceImpInstanceIsNotNull)
{
    ASSERT_TRUE(m_pSoftwareUpdateResourceImpl != nullptr) << "CSoftwareUpdateResourceImplTest Constructor PASSED";
}

TEST_F(CSoftwareUpdateResourceImplTest, CheckSoftwareUpdateResourceImpInitializedVariables)
{
    EXPECT_TRUE((m_pSoftwareUpdateResourceImpl->m_bSoftwareUpdateAvailable) == false);
}

TEST_F(CSoftwareUpdateResourceImplTest, CheckForStatusEventListnerSoftwareUpdate)
{
    m_pSoftwareUpdateResourceImpl->statusEventListnerSoftwareUpdate(AvailabilityStatus::AVAILABLE);
    EXPECT_TRUE((m_pSoftwareUpdateResourceImpl->m_bSoftwareUpdateAvailable) == true);
}

TEST_F(CSoftwareUpdateResourceImplTest, CheckForOnSWAvailable)
{
    SoftwareUpdateTypes::tPackageDetails pkgDetails;
    pkgDetails.setSource(SoftwareUpdateTypes::eUpdateSource::UPDATE_SOURCE_MSD);
    pkgDetails.setPackageName("ABC");
    pkgDetails.setDescription("Desc");
    pkgDetails.setVersion("XYZ");
    pkgDetails.setPackageSize(9);
    pkgDetails.setEstimatedInstallTime(90);
    pkgDetails.setPackageLocation("/usr/bin");

    SoftwareUpdateTypes::tPackageList packageList;
    packageList.push_back(pkgDetails);

    m_pSoftwareUpdateResourceImpl->onSWAvailable(packageList);


    std::list<SUpdateSearchResult>tmpList = m_pSoftwareUpdateResourceImpl->getPackageDetails();
    for (std::list<SUpdateSearchResult>::iterator it = tmpList.begin(); it != tmpList.end(); ++it)
    {
        if((it->_packageDetails.strPackageName).c_str() == "ABC")
        {
            EXPECT_STREQ((it->_packageDetails.strPackageName).c_str(), "ABC");
            EXPECT_TRUE((it->_packageDetails.eSource) == ESoftwareUpdateSource::UPDATE_SOURCE_MSD);
            EXPECT_STREQ((it->_packageDetails.strVersion).c_str(), "XYZ");
            EXPECT_EQ((it->_packageDetails.uiPackageSize), 9);
        }

    }

    m_pSoftwareUpdateResourceImpl->mSWImageList = packageList;
    m_pSoftwareUpdateResourceImpl->m_bSoftwareUpdateAvailable = true;
    m_pSoftwareUpdateResourceImpl->requestSWUpdate(0);

    m_pSoftwareUpdateResourceImpl->requestSWUpdate(100);
    m_pSoftwareUpdateResourceImpl->m_bSoftwareUpdateAvailable = false;
    m_pSoftwareUpdateResourceImpl->requestSWUpdate(1);

    m_pSoftwareUpdateResourceImpl->onSWAvailable(packageList);

    m_pSoftwareUpdateResourceImpl->m_pSoftwareUpdateEventProvider = NULL;
    m_pSoftwareUpdateResourceImpl->onSWAvailable(packageList);
}

TEST_F(CSoftwareUpdateResourceImplTest, CodeCoverage)
{
    m_pSoftwareUpdateResourceImpl->statusEventListnerSoftwareUpdate(AvailabilityStatus::NOT_AVAILABLE);
    m_pSoftwareUpdateResourceImpl->m_bSoftwareUpdateAvailable = true;

    SoftwareUpdateTypes::tUpdateSearchResult updateResult;
    updateResult.setUpdateAvailability(SoftwareUpdateTypes::eUpdateAvailability::NO_UPDATE_AVAILABLE);
    m_pSoftwareUpdateResourceImpl->asyncCbCheckForUpdate(CommonAPI::CallStatus::SUCCESS, SoftwareUpdateTypes::eMethodResult::REQ_OK, updateResult);

    updateResult.setUpdateAvailability(SoftwareUpdateTypes::eUpdateAvailability::UPDATE_ALREADY_IN_PROGRESS);
    m_pSoftwareUpdateResourceImpl->asyncCbCheckForUpdate(CommonAPI::CallStatus::SUCCESS, SoftwareUpdateTypes::eMethodResult::REQ_OK, updateResult);

    updateResult.setUpdateAvailability(SoftwareUpdateTypes::eUpdateAvailability::NO_NETWORK_CONNECTIVITY);
    m_pSoftwareUpdateResourceImpl->asyncCbCheckForUpdate(CommonAPI::CallStatus::SUCCESS, SoftwareUpdateTypes::eMethodResult::REQ_OK, updateResult);

    updateResult.setUpdateAvailability(SoftwareUpdateTypes::eUpdateAvailability::NO_UPDATE_AVAILABLE);
    m_pSoftwareUpdateResourceImpl->asyncCbCheckForUpdate(CommonAPI::CallStatus::SUCCESS, SoftwareUpdateTypes::eMethodResult::REQ_FAILED, updateResult);
    m_pSoftwareUpdateResourceImpl->CancelUpdateAsyncCb(CallStatus::SUCCESS);


    m_pSoftwareUpdateResourceImpl->DeclineUpdateAsyncCb(CallStatus::SUCCESS);

    SoftwareUpdateTypes::tStatus status;
    status.setCurrentState(SoftwareUpdateTypes::eSwdlState::IDLE);

    SoftwareUpdateTypes::tErrorInfo  errorInfo;
    errorInfo.setErrorCode(SoftwareUpdateTypes::eErrorCode::PACKAGE_VALIDATION_FAILED);
    errorInfo.setErrorString("error");
    status.setErrorInfo(errorInfo);
    m_pSoftwareUpdateResourceImpl->onSoftwareUpdateStatus(status, SoftwareUpdateTypes::eUpdateSource::UPDATE_SOURCE_MSD);
    m_pSoftwareUpdateResourceImpl->InstallPackageVerMismatchAsyncCb(CommonAPI::CallStatus::REMOTE_ERROR);
    m_pSoftwareUpdateResourceImpl->asyncCbCheckForUpdate(CommonAPI::CallStatus::SUCCESS, SoftwareUpdateTypes::eMethodResult::REQ_OK, updateResult);
    m_pSoftwareUpdateResourceImpl->asyncCbCheckForUpdate(CommonAPI::CallStatus::SUCCESS, SoftwareUpdateTypes::eMethodResult::REQ_FAILED, updateResult);
    errorInfo.setErrorCode(SoftwareUpdateTypes::eErrorCode::MSD_DISCONNECTED);
    m_pSoftwareUpdateResourceImpl->onSoftwareUpdateStatus(status, SoftwareUpdateTypes::eUpdateSource::UPDATE_SOURCE_MSD);


}

TEST_F(CSoftwareUpdateResourceImplTest, CodeCoverage2)
{
    m_pSoftwareUpdateResourceImpl->m_bSoftwareUpdateAvailable = false;
    m_pSoftwareUpdateResourceImpl->checkForUpdate();
    m_pSoftwareUpdateResourceImpl->m_bSoftwareUpdateAvailable = true;
    m_pSoftwareUpdateResourceImpl->checkForUpdate();
    m_pSoftwareUpdateResourceImpl->CancelUpdateAsyncCb(CallStatus::NOT_AVAILABLE);
    m_pSoftwareUpdateResourceImpl->DeclineUpdateAsyncCb(CallStatus::NOT_AVAILABLE);
    m_pSoftwareUpdateResourceImpl->cancelUpdate(ESoftwareUpdateCancelType::CANCEL_INSTALL);
    m_pSoftwareUpdateResourceImpl->m_bSoftwareUpdateAvailable = true;
    m_pSoftwareUpdateResourceImpl->cancelUpdate(ESoftwareUpdateCancelType::CANCEL_INSTALL);
    m_pSoftwareUpdateResourceImpl->cancelUpdate(ESoftwareUpdateCancelType::DECLINE_INSTALL);
    m_pSoftwareUpdateResourceImpl->reqInstallVerMismatch(0);
    m_pSoftwareUpdateResourceImpl->reqInstallVerMismatch(1);
    m_pSoftwareUpdateResourceImpl->reqInstallVerMismatch(2);
    m_pSoftwareUpdateResourceImpl->reqInstallVerMismatch(3);
    m_pSoftwareUpdateResourceImpl->m_bSoftwareUpdateAvailable = false;
    m_pSoftwareUpdateResourceImpl->reqInstallVerMismatch(3);
    m_pSoftwareUpdateResourceImpl->InstallPackageVerMismatchAsyncCb(CommonAPI::CallStatus::SUCCESS);


}
