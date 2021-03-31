#include "CVersionManagerAdaptorTest.h"
#include "VersionManager/CVersionManagerAdaptor.h"
#include "CVersionManagerParamTest.h"

void CVersionManagerAdaptorTest::SetUp()
{
    m_pVersionManagerAdaptor = CVersionManagerAdaptor::getInstance();
}

void CVersionManagerAdaptorTest::TearDown()
{
   // m_pVersionManagerAdaptor->~CVersionManagerAdaptor();
    if ( m_pVersionManagerAdaptor != nullptr )
    {
        CVersionManagerAdaptor::releaseInstance();
        m_pVersionManagerAdaptor = nullptr;
    }
}

//Test if CVersionManagerAdaptor instance is created and not Null 
TEST_F(CVersionManagerAdaptorTest, CheckVersionManagerAdaptorInstanceIsNotNull)
{
    ASSERT_TRUE(m_pVersionManagerAdaptor != nullptr)<< "CVersionManagerAdaptorTest Constructor PASSED"<<endl;
}

TEST_F(CVersionManagerAdaptorTest, CheckVersionManagerInitializedVariables)
{
    EXPECT_EQ(m_pVersionManagerAdaptor->m_strVIN , "");
    EXPECT_EQ(m_pVersionManagerAdaptor->m_strContainerPartNo , "");
    EXPECT_EQ(m_pVersionManagerAdaptor->m_strSilverBoxPartNo , "");
    EXPECT_EQ(m_pVersionManagerAdaptor->m_strDisplayHWPartNo , "");
    EXPECT_EQ(m_pVersionManagerAdaptor->m_strParameterizationPartNo , "");
    EXPECT_EQ(m_pVersionManagerAdaptor->m_strButtonPanelPartNo , "");
    EXPECT_EQ(m_pVersionManagerAdaptor->m_strBtnPanelSoftVersionNo , "");
    EXPECT_EQ(m_pVersionManagerAdaptor->m_strDisplayManagerVersionNo , "");
    EXPECT_EQ(m_pVersionManagerAdaptor->m_strSOCVersionNo , "");
    EXPECT_STRNE((m_pVersionManagerAdaptor->m_SwVersion).toStdString().c_str() , "");
    EXPECT_STRNE((m_pVersionManagerAdaptor->m_SwReleaseDate).toStdString().c_str() , "");
    EXPECT_EQ(m_pVersionManagerAdaptor->m_uiVersionMismatchValue , 0)<< "CVersionManagerAdaptorTest:: Variables Initialization Checked"<<endl;
}

TEST_F(CVersionManagerAdaptorTest, checkForSetVCInfoWithDiffValueString)
{
    m_pVersionManagerAdaptor->setVCInfo(QString::fromStdString(""));
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigVCInfoChanged()));
    m_pVersionManagerAdaptor->setVCInfo(QString::fromStdString("ABC123NF"));
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 1);
    EXPECT_STREQ((m_pVersionManagerAdaptor->vcInfo()).toStdString().c_str(), "ABC123NF");
}

TEST_F(CVersionManagerAdaptorTest, checkForSetVCInfoWithSameValueString)
{
    m_pVersionManagerAdaptor->setVCInfo(QString::fromStdString("ABC123NF"));
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigVCInfoChanged()));
    m_pVersionManagerAdaptor->setVCInfo(QString::fromStdString("ABC123NF"));
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 0);
    EXPECT_STREQ((m_pVersionManagerAdaptor->vcInfo()).toStdString().c_str(), "ABC123NF");
}

TEST_F(CVersionManagerAdaptorTest, CheckForSetterOfSwVersion)
{
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigSwVersionChanged()));
    m_pVersionManagerAdaptor->setSwVersion(QString::fromStdString("ABC123NF"));
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_STREQ((m_pVersionManagerAdaptor->swVersion()).toStdString().c_str(), "ABC123NF");
    //Check and coverage For Else Part when the values are same.
    m_pVersionManagerAdaptor->setSwVersion(QString::fromStdString("ABC123NF"));

}

TEST_F(CVersionManagerAdaptorTest, CheckForSetterOfSwReleaseDate)
{
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigSwReleaseDateChanged()));
    m_pVersionManagerAdaptor->setSwReleaseDate(QString::fromStdString("ABC123NF"));
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_STREQ((m_pVersionManagerAdaptor->swReleaseDate()).toStdString().c_str(), "ABC123NF");
    //Check and coverage For Else Part when the values are same.
    m_pVersionManagerAdaptor->setSwReleaseDate(QString::fromStdString("ABC123NF"));

}

TEST_F(CVersionManagerAdaptorTest, checkForSetVINInfoWithDiffValueString)
{
    m_pVersionManagerAdaptor->setVINInfo(QString::fromStdString(""));
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigVINInfoChanged()));
    m_pVersionManagerAdaptor->setVINInfo(QString::fromStdString("ABC123NF"));
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 1);
    EXPECT_STREQ((m_pVersionManagerAdaptor->vinInfo()).toStdString().c_str(), "ABC123NF");
}

TEST_F(CVersionManagerAdaptorTest, checkForSetVINInfoWithSameValueString)
{
    m_pVersionManagerAdaptor->setVCInfo(QString::fromStdString("ABC123NF"));
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigVCInfoChanged()));
    m_pVersionManagerAdaptor->setVCInfo(QString::fromStdString("ABC123NF"));
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 0);
    EXPECT_STREQ((m_pVersionManagerAdaptor->vcInfo()).toStdString().c_str(), "ABC123NF");
}

TEST_F(CVersionManagerAdaptorTest, checkForSetContainerPartNoWithDiffValueString)
{
    m_pVersionManagerAdaptor->setContainerPartNo(QString::fromStdString(""));
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigContainerPartNoChanged()));
    m_pVersionManagerAdaptor->setContainerPartNo(QString::fromStdString("ABC123NF"));
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 1);
    EXPECT_STREQ((m_pVersionManagerAdaptor->containerPartNo()).toStdString().c_str(), "ABC123NF");
}

TEST_F(CVersionManagerAdaptorTest, checkForSetContainerPartNoWithSameValueString)
{
    m_pVersionManagerAdaptor->setContainerPartNo(QString::fromStdString("ABC123NF"));
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigContainerPartNoChanged()));
    m_pVersionManagerAdaptor->setContainerPartNo(QString::fromStdString("ABC123NF"));
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 0);
    EXPECT_STREQ((m_pVersionManagerAdaptor->containerPartNo()).toStdString().c_str(), "ABC123NF");
}

TEST_F(CVersionManagerAdaptorTest, checkforSetSilverBoxPartNoWithDiffValueString)
{
    m_pVersionManagerAdaptor->setSilverBoxPartNo(QString::fromStdString(""));
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigSilverBoxPartChanged()));
    m_pVersionManagerAdaptor->setSilverBoxPartNo(QString::fromStdString("ABC123NF"));
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 1);
    EXPECT_STREQ((m_pVersionManagerAdaptor->silverBoxPartNo()).toStdString().c_str(), "ABC123NF");

}
TEST_F(CVersionManagerAdaptorTest, checkforSetSilverBoxPartNoWithSameValueString)
{
    m_pVersionManagerAdaptor->setSilverBoxPartNo(QString::fromStdString("ABC123NF"));
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigSilverBoxPartChanged()));
    m_pVersionManagerAdaptor->setSilverBoxPartNo(QString::fromStdString("ABC123NF"));
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 0);
    EXPECT_STREQ((m_pVersionManagerAdaptor->silverBoxPartNo()).toStdString().c_str(), "ABC123NF");

}

TEST_F(CVersionManagerAdaptorTest, checkforSetDisplayHWPartNoWithDiffValueString)
{
    m_pVersionManagerAdaptor->setDisplayHWPartNo(QString::fromStdString(""));
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigDisplayHWPartNoChanged()));
    m_pVersionManagerAdaptor->setDisplayHWPartNo(QString::fromStdString("ABC123NF"));
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 1);
    EXPECT_STREQ((m_pVersionManagerAdaptor->displayHWPartNo()).toStdString().c_str(), "ABC123NF");
}

TEST_F(CVersionManagerAdaptorTest, checkforSetDisplayHWPartNoWithSameValueString)
{
    m_pVersionManagerAdaptor->setDisplayHWPartNo(QString::fromStdString("ABC123NF"));
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigDisplayHWPartNoChanged()));
    m_pVersionManagerAdaptor->setDisplayHWPartNo(QString::fromStdString("ABC123NF"));
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 0);
    EXPECT_STREQ((m_pVersionManagerAdaptor->displayHWPartNo()).toStdString().c_str(), "ABC123NF");
}

TEST_F(CVersionManagerAdaptorTest, checkforSetParameterizationPartNoWithDiffValueString)
{
    m_pVersionManagerAdaptor->setParameterizationPartNo(QString::fromStdString(""));
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigParameterizationPartNoChanged()));
    m_pVersionManagerAdaptor->setParameterizationPartNo(QString::fromStdString("ABC123NF"));
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 1);
    EXPECT_STREQ((m_pVersionManagerAdaptor->parameterizationPartNo()).toStdString().c_str(), "ABC123NF");
}

TEST_F(CVersionManagerAdaptorTest, checkforSetParameterizationPartNoWithSameValueString)
{
    m_pVersionManagerAdaptor->setParameterizationPartNo(QString::fromStdString("ABC123NF"));
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigParameterizationPartNoChanged()));
    m_pVersionManagerAdaptor->setParameterizationPartNo(QString::fromStdString("ABC123NF"));
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 0);
    EXPECT_STREQ((m_pVersionManagerAdaptor->parameterizationPartNo()).toStdString().c_str(), "ABC123NF");
}

TEST_F(CVersionManagerAdaptorTest, checkforSetButtonPanelPartNoWithDiffValueString)
{
    m_pVersionManagerAdaptor->setButtonPanelPartNo(QString::fromStdString(""));
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigButtonPanelPartNoChanged()));
    m_pVersionManagerAdaptor->setButtonPanelPartNo(QString::fromStdString("ABC123NF"));
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 1);
    EXPECT_STREQ((m_pVersionManagerAdaptor->buttonPanelPartNo()).toStdString().c_str(), "ABC123NF");

}

TEST_F(CVersionManagerAdaptorTest, checkforSetButtonPanelPartNoWithSameValueString)
{
    m_pVersionManagerAdaptor->setButtonPanelPartNo(QString::fromStdString("ABC123NF"));
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigButtonPanelPartNoChanged()));
    m_pVersionManagerAdaptor->setButtonPanelPartNo(QString::fromStdString("ABC123NF"));
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 0);
    EXPECT_STREQ((m_pVersionManagerAdaptor->buttonPanelPartNo()).toStdString().c_str(), "ABC123NF");

}

TEST_F(CVersionManagerAdaptorTest, checkforSetBtnPanelSoftVersionNoWithDiffValueString)
{
    m_pVersionManagerAdaptor->setBtnPanelSoftVersionNo(QString::fromStdString(""));
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigBtnPanelSoftVersionNoChanged()));
    m_pVersionManagerAdaptor->setBtnPanelSoftVersionNo(QString::fromStdString("ABC123NF"));
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 1);
    EXPECT_STREQ((m_pVersionManagerAdaptor->btnPanelSoftVersionNo()).toStdString().c_str(), "ABC123NF");
}

TEST_F(CVersionManagerAdaptorTest, checkforSetBtnPanelSoftVersionNoWithSameValueString)
{
    m_pVersionManagerAdaptor->setBtnPanelSoftVersionNo(QString::fromStdString("ABC123NF"));
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigBtnPanelSoftVersionNoChanged()));
    m_pVersionManagerAdaptor->setBtnPanelSoftVersionNo(QString::fromStdString("ABC123NF"));
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 0);
    EXPECT_STREQ((m_pVersionManagerAdaptor->btnPanelSoftVersionNo()).toStdString().c_str(), "ABC123NF");
}

TEST_F(CVersionManagerAdaptorTest, checkforSetDisplayManagerSoftVersionNoWithDiffValueString)
{
    m_pVersionManagerAdaptor->setDisplayManagerSoftVersionNo(QString::fromStdString(""));
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigDisplayManagerSoftVersionNoChanged()));
    m_pVersionManagerAdaptor->setDisplayManagerSoftVersionNo(QString::fromStdString("ABC123NF"));
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 1);
    EXPECT_STREQ((m_pVersionManagerAdaptor->displayManagerSoftVersionNo()).toStdString().c_str(), "ABC123NF");

}
TEST_F(CVersionManagerAdaptorTest, checkforSetDisplayManagerSoftVersionNoWithSameValueString)
{
    m_pVersionManagerAdaptor->setDisplayManagerSoftVersionNo(QString::fromStdString("ABC123NF"));
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigDisplayManagerSoftVersionNoChanged()));
    m_pVersionManagerAdaptor->setDisplayManagerSoftVersionNo(QString::fromStdString("ABC123NF"));
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 0);
    EXPECT_STREQ((m_pVersionManagerAdaptor->displayManagerSoftVersionNo()).toStdString().c_str(), "ABC123NF");

}

TEST_F(CVersionManagerAdaptorTest, checkforSetSOCSoftVersionNoWithDiffValueString)
{
    m_pVersionManagerAdaptor->setSOCSoftVersionNo(QString::fromStdString(""));
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigSOCSoftVersionNoChanged()));
    m_pVersionManagerAdaptor->setSOCSoftVersionNo(QString::fromStdString("ABC123NF"));
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 1);
    EXPECT_STREQ((m_pVersionManagerAdaptor->socSoftVersionNo()).toStdString().c_str(), "ABC123NF");

}
TEST_F(CVersionManagerAdaptorTest, checkforSetSOCSoftVersionNoWithSameValueString)
{
    m_pVersionManagerAdaptor->setSOCSoftVersionNo(QString::fromStdString("ABC123NF"));
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigSOCSoftVersionNoChanged()));
    m_pVersionManagerAdaptor->setSOCSoftVersionNo(QString::fromStdString("ABC123NF"));
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 0);
    EXPECT_STREQ((m_pVersionManagerAdaptor->socSoftVersionNo()).toStdString().c_str(), "ABC123NF");

}
//ToDo: check for min max values and also which are out of bound.
//Use For Loop in these cases to shorten the code.
TEST_F(CVersionManagerAdaptorTest, checkforVersionMismatch)
{
    /**
      * 0 - No Version Mismatch
      * 1 - Display Version Mismatch
      * 2 - ButtonPanel Version Mismatch
      * 3 - BP_DM Version Mismatch.
    **/
    for(int versionMismatchCounter = 0;versionMismatchCounter < 4 ;versionMismatchCounter++)
    {
        m_pVersionManagerAdaptor->versionMisMatchValueReceived(versionMismatchCounter);
        EXPECT_TRUE(m_pVersionManagerAdaptor->m_uiVersionMismatchValue == versionMismatchCounter);
    }
}

TEST_F(CVersionManagerAdaptorTest, checkforSetPowerModePEPSMode)
{
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigPowerModeChanged()));
    m_pVersionManagerAdaptor->setPowerMode(POWER_MODE_PEPS);
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 1);
    EXPECT_TRUE(m_pVersionManagerAdaptor->m_ePowerModeType == 1);
    EXPECT_TRUE(m_pVersionManagerAdaptor->m_strPowerMode == POWER_MODE_PEPS);
    //To cover the else part when the values are same.
    m_pVersionManagerAdaptor->setPowerMode(POWER_MODE_PEPS);
}

TEST_F(CVersionManagerAdaptorTest, checkforSetPowerModeIgnOnMode)
{
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigPowerModeChanged()));
    m_pVersionManagerAdaptor->setPowerMode(POWER_MODE_IGN);
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 1);
    EXPECT_TRUE(m_pVersionManagerAdaptor->m_ePowerModeType == 0);
    EXPECT_TRUE(m_pVersionManagerAdaptor->m_strPowerMode == POWER_MODE_IGN);
    //To cover the else part when the values are same.
    m_pVersionManagerAdaptor->setPowerMode(POWER_MODE_IGN);
}

TEST_F(CVersionManagerAdaptorTest, checkforSetPowerModeInvalidData)
{
    QSignalSpy spy(m_pVersionManagerAdaptor, SIGNAL(sigPowerModeChanged()));
    m_pVersionManagerAdaptor->setPowerMode(INVALID_DATA);
    EXPECT_TRUE(spy.isValid() == true);
    EXPECT_TRUE(spy.count() == 1);
    EXPECT_FALSE(m_pVersionManagerAdaptor->m_ePowerModeType == 3);
    EXPECT_TRUE(m_pVersionManagerAdaptor->m_strPowerMode == INVALID_DATA);
    //To cover the else part when the values are same.
    m_pVersionManagerAdaptor->setPowerMode(INVALID_DATA);
}


TEST_F(CVersionManagerAdaptorTest, checkSWUpdateActionOnVersionMismatch)
{
    m_pVersionManagerAdaptor->m_uiVersionMismatchValue = 1;
    m_pVersionManagerAdaptor->callSwUpdateOnVerMismatch();
    //To cover the else part when the values are same.
    m_pVersionManagerAdaptor->m_uiVersionMismatchValue = 0;
    m_pVersionManagerAdaptor->callSwUpdateOnVerMismatch();
}

// Todo: [Recheck] This has been implemented in Both Classes i.e. for Adaptor and Param test Class.
INSTANTIATE_TEST_CASE_P(
        VersionMismatchTestCases,
        CVersionManagerAdaptorTest,
        ::testing::Values(
                0, 1, 2, 4, 5, 100
        ));

TEST_P(CVersionManagerAdaptorTest, checkForVersionMismatchParamTestCases) {
    int versionMismatchCounter = GetParam();
    m_pVersionManagerAdaptor->versionMisMatchValueReceived(versionMismatchCounter);
    EXPECT_TRUE(m_pVersionManagerAdaptor->m_uiVersionMismatchValue == versionMismatchCounter);
}

