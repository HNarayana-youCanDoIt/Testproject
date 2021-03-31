#include "CVersionManagerApplicationTest.h"
#include "VersionManager/CVersionManagerApplication.h"

void CVersionManagerApplicationTest::SetUp()
{
    m_pVersionManagerApplication = new CVersionManagerApplication();
}

void CVersionManagerApplicationTest::TearDown()
{
    delete m_pVersionManagerApplication;
}

TEST_F(CVersionManagerApplicationTest, CheckVersionManagerApplicationInstanceIsNotNull)
{
    ASSERT_TRUE(m_pVersionManagerApplication != nullptr) << "CVersionManagerApplicationTest Constructor PASSED";
}
