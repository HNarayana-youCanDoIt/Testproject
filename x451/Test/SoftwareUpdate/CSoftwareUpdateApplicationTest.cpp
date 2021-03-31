#include "CSoftwareUpdateApplicationTest.h"
#include "SoftwareUpdate/CSoftwareUpdateApplication.h"

void CSoftwareUpdateApplicationTest::SetUp()
{
    m_pSoftwareUpdateApplication = new CSoftwareUpdateApplication();
}

void CSoftwareUpdateApplicationTest::TearDown()
{
    delete m_pSoftwareUpdateApplication;
}

TEST_F(CSoftwareUpdateApplicationTest, CheckSoftwareUpdateApplicationInstanceIsNotNull)
{
    ASSERT_TRUE(m_pSoftwareUpdateApplication != nullptr) << "CSoftwareUpdateApplicationTest Constructor PASSED";
}

TEST_F(CSoftwareUpdateApplicationTest, checkForOtherFunctionsCoverage)
{
    m_pSoftwareUpdateApplication->loadScreen("abs");
    m_pSoftwareUpdateApplication->raiseSMEvent("abs", "sa");
    m_pSoftwareUpdateApplication->raiseSMEvent("abs", "ISO");
    m_pSoftwareUpdateApplication->raiseSMEvent("abs", "Back");
    m_pSoftwareUpdateApplication->raiseSMEvent("abs", "Home");
    m_pSoftwareUpdateApplication->raiseSMEvent("abs", "EnggMenu");
    m_pSoftwareUpdateApplication->raiseSMEvent("abs", "usbDisconnect");
    m_pSoftwareUpdateApplication->raiseSMEvent("abs", "ABCD00+");
}
