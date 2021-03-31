#include "CSoftwareUpdateAdaptorTest.h"
#include "SoftwareUpdate/CSoftwareUpdateAdaptor.h"
#include "Audio/CAudioAdaptor.h"

/**
 * @brief CSoftwareUpdateAdaptorTest::SetUp
 * This will create the instance of CSoftwareAdaptor class to tests various scenarios for this class.
 */
void CSoftwareUpdateAdaptorTest::SetUp()
{
    cout << "CSoftwareUpdateAdaptorTest::SetUp"<<endl;
    m_pSoftwareUpdateAdaptor = CSoftwareUpdateAdaptor::getInstance();
}

/**
 * @brief CSoftwareUpdateAdaptorTest::TearDown
 * This will delete the instance of CSoftwareAdaptor class after each test execution.
 */
void CSoftwareUpdateAdaptorTest::TearDown()
{
    cout << "CSoftwareUpdateAdaptorTest::TearDown"<<endl;
    if ( m_pSoftwareUpdateAdaptor != nullptr )
    {
        CSoftwareUpdateAdaptor::releaseInstance();
        m_pSoftwareUpdateAdaptor = nullptr;
    }
}

/**
 * @brief CheckSoftwareUpdateAdaptorInstanceIsNotNull: This will Test if the Adaptor Instance is not NULL.
 */
TEST_F(CSoftwareUpdateAdaptorTest, CheckSoftwareUpdateAdaptorInstanceIsNotNull)
{
    ASSERT_TRUE(m_pSoftwareUpdateAdaptor != nullptr);
    cout<< "CSoftwareUpdateAdaptorTest Constructor PASSED"<<endl;
}

/**
 * @brief CheckIfSWAvailabilityVarIsInitializedToDefault: This will test if m_bSwUpdateAvailability
 * member variable is initialized with default value "false"
 */
TEST_F(CSoftwareUpdateAdaptorTest, CheckIfSWAvailabilityVarIsInitializedToDefault)
{
    EXPECT_EQ(m_pSoftwareUpdateAdaptor->m_bSwUpdateAvailability , false);
}

/**
 * @brief CheckSoftwareUpdateAdaptorInitializedVariables: This will Tests if all the
 * member variables of this class are initialized with default value as in the CSoftwareUpdateAdaptor Class.
 */
TEST_F(CSoftwareUpdateAdaptorTest, CheckSoftwareUpdateAdaptorInitializedVariables)
{
    EXPECT_STREQ((m_pSoftwareUpdateAdaptor->m_strSelectedISOName).toStdString().c_str() , "");
    EXPECT_EQ(m_pSoftwareUpdateAdaptor->m_iSelectedISOIndex , -1);
    EXPECT_EQ(m_pSoftwareUpdateAdaptor->m_bBusyIndicatorVisibility , false);
}

/**
* @brief TestForSameSWUpdateAvailabilityVar: This test will check
* if same SWUpdateAvailibilty var is set
*/
TEST_F(CSoftwareUpdateAdaptorTest, TestForSameSWUpdateAvailabilityVar)
{
    //Set m_bSwUpdateAvailability to same value. i.e false
    m_pSoftwareUpdateAdaptor->setSwUpdateAvailability(false);
    EXPECT_EQ((m_pSoftwareUpdateAdaptor->swUpdateAvailability()), false);
}

/**
* @brief TestForDiffSWUpdateAvailabilityVar: This test will check
* if SWUpdateAvailibilty is set to new value
*/
TEST_F(CSoftwareUpdateAdaptorTest, TestForDiffSWUpdateAvailabilityVar)
{
    //Set m_bSwUpdateAvailability to different value. i.e true
    m_pSoftwareUpdateAdaptor->setSwUpdateAvailability(true);
    EXPECT_EQ((m_pSoftwareUpdateAdaptor->swUpdateAvailability()), true);
}

/**
* @brief TestIfSWUpdateSignalEmittedToUILayer: This test will check
* if SWUpdate signal is emitted to UI Layer
*/
TEST_F(CSoftwareUpdateAdaptorTest, TestIfSWUpdateSignalEmittedToUILayer)
{
    QSignalSpy spy(m_pSoftwareUpdateAdaptor, SIGNAL(sigSwUpdateAvailabilityChanged()));
    m_pSoftwareUpdateAdaptor->setSwUpdateAvailability(true);
    //Check if the signal is emmited to UI layer if spy count is increased
    EXPECT_TRUE(spy.count() == 1);
}




TEST_F(CSoftwareUpdateAdaptorTest, CheckForSetterOfBusyIndicatorVisibility)
{
    QSignalSpy spy(m_pSoftwareUpdateAdaptor, SIGNAL(sigBusyIndicatorVisibilityChanged()));
    m_pSoftwareUpdateAdaptor->setBusyIndicatorVisibility(true);
    EXPECT_EQ((m_pSoftwareUpdateAdaptor->busyIndicatorVisibility()), true);
    EXPECT_TRUE(spy.isValid() == true);
    // To cover else part where the value is same as the old one.
    m_pSoftwareUpdateAdaptor->setBusyIndicatorVisibility(true);

}

TEST_F(CSoftwareUpdateAdaptorTest, CheckForSetterOfSWISOList)
{
    QSignalSpy spy(m_pSoftwareUpdateAdaptor, SIGNAL(sigSWISOListChanged()));
    QStringList val;
    val << "ABC" << "DEF";
    m_pSoftwareUpdateAdaptor->setSWISOList(val);
    QStringList SWISOList = m_pSoftwareUpdateAdaptor->swISOList();
    EXPECT_TRUE(SWISOList.at(0) == "ABC");
    EXPECT_TRUE(SWISOList.at(1) == "DEF");
    EXPECT_TRUE(spy.isValid() == true);
    // To cover else part where the value is same as the old one.
    m_pSoftwareUpdateAdaptor->setSWISOList(val);

}

TEST_F(CSoftwareUpdateAdaptorTest, CheckForSetterOfSelectedISOName)
{
    QSignalSpy spy(m_pSoftwareUpdateAdaptor, SIGNAL(sigISONameSelected()));
    m_pSoftwareUpdateAdaptor->setSelectedISOName(QString::fromStdString("ABC123NF"));
    EXPECT_STREQ((m_pSoftwareUpdateAdaptor->selectedISOName()).toStdString().c_str(), "ABC123NF");
    EXPECT_TRUE(spy.isValid() == true);
    // To cover else part where the value is same as the old one.
    m_pSoftwareUpdateAdaptor->setSelectedISOName(QString::fromStdString("ABC123NF"));

}

TEST_F(CSoftwareUpdateAdaptorTest, CheckForSetterOfSelectedISOIndex)
{
    QSignalSpy spy(m_pSoftwareUpdateAdaptor, SIGNAL(sigSelectedISOIndexChanged()));
    m_pSoftwareUpdateAdaptor->setSelectedISOIndex(2);
    EXPECT_EQ((m_pSoftwareUpdateAdaptor->selectedISOIndex()), 2);
    EXPECT_TRUE(spy.isValid() == true);
    // To cover else part where the value is same as the old one.
    m_pSoftwareUpdateAdaptor->setSelectedISOIndex(2);

}

TEST_F(CSoftwareUpdateAdaptorTest, CheckForShowISOFileConfirmPopup)
{
    CPowerModeAdaptor::getInstance().powerModeChanged(CPowerModeEnums::VPM_ONE_HOUR);
    CPowerModeAdaptor::getInstance().sltNSMNodeStateEvent(8);
    m_pSoftwareUpdateAdaptor->showISOFileConfirmPopup(1, QString::fromStdString("ABCDEF"));
    EXPECT_EQ((m_pSoftwareUpdateAdaptor->selectedISOIndex()), 1);
    EXPECT_STREQ((m_pSoftwareUpdateAdaptor->selectedISOName()).toStdString().c_str(), "ABCDEF");

}

TEST_F(CSoftwareUpdateAdaptorTest, CheckForInvokableErrorVerMismatchUpdate)
{
    CPowerModeAdaptor::getInstance().powerModeChanged(CPowerModeEnums::VPM_ACTIVE);
    int error = m_pSoftwareUpdateAdaptor->invErrorVerMismatchUpdate();
    EXPECT_EQ(error, 0);

}

TEST_F(CSoftwareUpdateAdaptorTest, CheckForInvokableErrorVerMismatchUpdate2)
{
    CPowerModeAdaptor::getInstance().powerModeChanged(CPowerModeEnums::VPM_ONE_HOUR);
    CPowerModeAdaptor::getInstance().sltNSMNodeStateEvent(9);
    int error = m_pSoftwareUpdateAdaptor->invErrorVerMismatchUpdate();
    EXPECT_EQ(error, 1);
    CPowerModeAdaptor::getInstance().powerModeChanged(CPowerModeEnums::VPM_ONE_HOUR);
    CPowerModeAdaptor::getInstance().sltNSMNodeStateEvent(8);
}

TEST_F(CSoftwareUpdateAdaptorTest, CheckForShowAvailabilityErrorMessage)
{
    m_pSoftwareUpdateAdaptor->setBusyIndicatorVisibility(true);
    m_pSoftwareUpdateAdaptor->showAvailabilityErrorMessage(ESoftwareUpdateAvailability::UPDATE_ALREADY_IN_PROGRESS);
    EXPECT_EQ((m_pSoftwareUpdateAdaptor->busyIndicatorVisibility()), false);
}

TEST_F(CSoftwareUpdateAdaptorTest, CheckForUpdateAttributeWhenUSBSrcIsTrue)
{
    CAudioAdaptor::getInstance()->updateUSBSrcStatus(true);
    CPowerModeAdaptor::getInstance().powerModeChanged(CPowerModeEnums::VPM_ACTIVE);
    m_pSoftwareUpdateAdaptor->checkForUpdateAttribute();

    CPowerModeAdaptor::getInstance().powerModeChanged(CPowerModeEnums::VPM_ONE_HOUR);
    CPowerModeAdaptor::getInstance().sltNSMNodeStateEvent(9);
    m_pSoftwareUpdateAdaptor->checkForUpdateAttribute();

    CPowerModeAdaptor::getInstance().powerModeChanged(CPowerModeEnums::VPM_ONE_HOUR);
    CPowerModeAdaptor::getInstance().sltNSMNodeStateEvent(8);
    m_pSoftwareUpdateAdaptor->checkForUpdateAttribute();
}

TEST_F(CSoftwareUpdateAdaptorTest, CheckForUpdateAttributeWhenUSBSrcIsFalse)
{
    CAudioAdaptor::getInstance()->updateUSBSrcStatus(false);
    CPowerModeAdaptor::getInstance().powerModeChanged(CPowerModeEnums::VPM_ACTIVE);
    m_pSoftwareUpdateAdaptor->checkForUpdateAttribute();

    CPowerModeAdaptor::getInstance().powerModeChanged(CPowerModeEnums::VPM_ONE_HOUR);
    CPowerModeAdaptor::getInstance().sltNSMNodeStateEvent(9);
    m_pSoftwareUpdateAdaptor->checkForUpdateAttribute();

    CPowerModeAdaptor::getInstance().powerModeChanged(CPowerModeEnums::VPM_ONE_HOUR);
    CPowerModeAdaptor::getInstance().sltNSMNodeStateEvent(8);
    m_pSoftwareUpdateAdaptor->checkForUpdateAttribute();
}

TEST_F(CSoftwareUpdateAdaptorTest, CheckForOtherFunctionCoverage)
{
    m_pSoftwareUpdateAdaptor->swISOListReceived();
    m_pSoftwareUpdateAdaptor->showAvailabilityErrorMessage(ESoftwareUpdateAvailability::UPDATE_ALREADY_IN_PROGRESS);
    EXPECT_EQ((m_pSoftwareUpdateAdaptor->busyIndicatorVisibility()), false);
    CPowerModeAdaptor::getInstance().powerModeChanged(CPowerModeEnums::VPM_ACTIVE);
    m_pSoftwareUpdateAdaptor->showISOFileConfirmPopup(1, QString::fromStdString("ABCDEF"));

    CPowerModeAdaptor::getInstance().powerModeChanged(CPowerModeEnums::VPM_ONE_HOUR);
    CPowerModeAdaptor::getInstance().sltNSMNodeStateEvent(9);
    m_pSoftwareUpdateAdaptor->showISOFileConfirmPopup(1, QString::fromStdString("ABCDEF"));

    CPowerModeAdaptor::getInstance().powerModeChanged(CPowerModeEnums::VPM_ONE_HOUR);
    CPowerModeAdaptor::getInstance().sltNSMNodeStateEvent(8);
    m_pSoftwareUpdateAdaptor->invErrorVerMismatchUpdate();


    m_pSoftwareUpdateAdaptor->cancelUpdateOnError(ESoftwareUpdateCancelType::CANCEL_INSTALL);
    m_pSoftwareUpdateAdaptor->cancelUpdateOnError(ESoftwareUpdateCancelType ::DECLINE_INSTALL);


    m_pSoftwareUpdateAdaptor->invShowErrorMessage(0);
    m_pSoftwareUpdateAdaptor->invShowErrorMessage(5);

    m_pSoftwareUpdateAdaptor->showAvailabilityErrorMessage(3);

    m_pSoftwareUpdateAdaptor->requestInstallPackageAttribute(1);
    m_pSoftwareUpdateAdaptor->requestInstallOnVerMismatch(2);

}

