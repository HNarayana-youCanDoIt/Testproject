#include "CVersionManagerEventHandlerTest.h"
#include "VersionManager/CVersionManagerEventHandler.h"


void CVersionManagerEventHandlerTest::SetUp()
{
    m_pVersionManagerEventHandler = new CVersionManagerEventHandler();
}

void CVersionManagerEventHandlerTest::TearDown()
{
    delete m_pVersionManagerEventHandler;
    m_pVersionManagerEventHandler = NULL;

}
TEST_F(CVersionManagerEventHandlerTest, CheckVersionManagerEventHandlerInstanceIsNotNull)
{
    ASSERT_TRUE(m_pVersionManagerEventHandler != nullptr);
    cout<< "CVersionManagerEventHandlerTest Constructor PASSED"<<endl;
}


TEST_F(CVersionManagerEventHandlerTest, CheckVersionManagerEventHandlerInitializedVariables)
{
    EXPECT_TRUE(m_pVersionManagerEventHandler->m_bReducedCanStatus == false);
}

TEST_F(CVersionManagerEventHandlerTest, CheckSlotForPowerModeChanged)
{
    CPowerModeAdaptor::getInstance().powerModeChanged(CPowerModeEnums::VPM_ACTIVE);
    m_pVersionManagerEventHandler->sltPowerModeChanged();
    EXPECT_FALSE((m_pVersionManagerEventHandler->m_bReducedCanStatus == true));
    CPowerModeAdaptor::getInstance().powerModeChanged(CPowerModeEnums::VPM_EARLY_WAKEUP);
    m_pVersionManagerEventHandler->sltPowerModeChanged();
    EXPECT_TRUE((m_pVersionManagerEventHandler->m_bReducedCanStatus == true));
}


TEST_F(CVersionManagerEventHandlerTest, CheckForOtherFunctionsCoverage)
{
  m_pVersionManagerEventHandler-> sltVCInfoUpdateReceived("ABC");
  m_pVersionManagerEventHandler-> sltVINInfoUpdateReceived("ABC");
  m_pVersionManagerEventHandler-> sltContainerPartNoUpdateReceived("ABC");
  m_pVersionManagerEventHandler-> sltSilverBoxPartNoUpdateReceived("ABC");
  m_pVersionManagerEventHandler-> sltDisplayHWPartNoUpdateReceived("ABC");
  m_pVersionManagerEventHandler-> sltParameterizationPartNoUpdateReceived("ABC");
  m_pVersionManagerEventHandler-> sltButtonPanelPartNoUpdateReceived("ABC");
  m_pVersionManagerEventHandler-> sltSOCSofVersionNoUpdateReceived("ABC");
  m_pVersionManagerEventHandler-> sltButtonPanelSofVersionNoUpdateReceived("ABC");
  m_pVersionManagerEventHandler-> sltDisplayManagerSofVersionNoUpdateReceived("ABC");
  m_pVersionManagerEventHandler-> sltPowerModeCfgTypeReceived("ABC");
  m_pVersionManagerEventHandler-> sltVersionMismatchEventReceived(1);

}





//TEST_F(CVersionManagerEventHandlerTest, TestPowerMode)
//{
////    MockPowerModeAdaptor mVM;

////    EXPECT_CALL(mVM, getPowerModeStatus())
////    .Times(2)
////    .WillOnce(Return(CPowerModeEnums::VPM_EARLY_WAKEUP))
////    .WillOnce(Return(CPowerModeEnums::VPM_ACTIVE));

//    //Arrange
//    CPowerModeAdaptor::getInstance().powerModeChanged(CPowerModeEnums::VPM_EARLY_WAKEUP);

//    //Action
//    m_pVersionManagerEventHandler->sltPowerModeChanged();


//    //Assert
//   // EXPECT_TRUE((m_pVersionManagerEventHandler->m_bReducedCanStatus == true));
//}

