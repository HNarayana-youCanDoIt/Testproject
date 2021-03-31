#include "CVersionManagerParamTest.h"
#include "VersionManager/CVersionManagerAdaptor.h"

/**
 * @brief CVersionManagerAdaptor::SetUp
 * This will create the instance of CVersionManagerAdaptor class to tests parameterized Test case for this class.
 */
void CVersionManagerParamTest::SetUp()
{
    m_pVersionManagerAdaptor = CVersionManagerAdaptor::getInstance();
}

/**
 * @brief CVersionManagerAdaptor::TearDown
 * This will delete the instance of CVersionManagerAdaptor class after test execution.
 */
void CVersionManagerParamTest::TearDown()
{
    if ( m_pVersionManagerAdaptor != nullptr )
    {
        CVersionManagerAdaptor::releaseInstance();
        m_pVersionManagerAdaptor = nullptr;
    }
}

INSTANTIATE_TEST_CASE_P(
        VersionMismatchTestCases,
        CVersionManagerParamTest,
        ::testing::Values(
                -1000, -2, 0, 1, 2, 3, 4, 5, 100, 10000
        ));

/**
 * @brief checkForVersionMismatchParamTestCases: Parameterized test for versionMismatch function with various input data.
 */
TEST_P(CVersionManagerParamTest, checkForVersionMismatchParamTestCases) {
    int versionMismatchCounter = GetParam();
    m_pVersionManagerAdaptor->versionMisMatchValueReceived(versionMismatchCounter);
    EXPECT_TRUE(m_pVersionManagerAdaptor->m_uiVersionMismatchValue == versionMismatchCounter);
}

