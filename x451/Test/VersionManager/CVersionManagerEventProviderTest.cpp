#include "CVersionManagerEventProviderTest.h"

void CVersionManagerEventProviderTest::SetUp()
{
    m_pVersionManagerEventProvider = new CVersionManagerEventProvider();
}

void CVersionManagerEventProviderTest::TearDown()
{
    delete m_pVersionManagerEventProvider; m_pVersionManagerEventProvider = NULL;
}

TEST_F(CVersionManagerEventProviderTest, CheckVersionManagerEventProviderInstanceIsNotNullr)
{
    ASSERT_TRUE(m_pVersionManagerEventProvider != nullptr);
    cout<< "CVersionManagerEventProviderTest Constructor PASSED"<<endl;
}

TEST_F(CVersionManagerEventProviderTest, CheckForSigVersionMismatchEventReceivedWithCorrectParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigVersionMismatchEventReceived(uint)));
    m_pVersionManagerEventProvider->versionMismatchEventReceived(5);
    EXPECT_EQ(spy1.count(), 1);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_TRUE(args.at(0).type() == QVariant::UInt);
    EXPECT_TRUE(args.at(0).toUInt() == 5);

}

TEST_F(CVersionManagerEventProviderTest, CheckForSigVersionMismatchEventReceivedWithWrongParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigVersionMismatchEventReceived(uint)));
    m_pVersionManagerEventProvider->versionMismatchEventReceived(5);
    EXPECT_NE(spy1.count(), 2);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_FALSE(args.at(0).type() == QVariant::String);
    EXPECT_FALSE(args.at(0).toUInt() == 3);

}

TEST_F(CVersionManagerEventProviderTest, CheckForSigPowerModeCfgTypeReceivedWithCorrectParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigPowerModeCfgTypeReceived(const QString&)));
    m_pVersionManagerEventProvider->powerModeCfgTypeReceived("0A123$");
    EXPECT_EQ(spy1.count(), 1);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_TRUE(args.at(0).type() == QVariant::String);
    EXPECT_TRUE(args.at(0).toString()== QString::fromStdString("0A123$"));
}

TEST_F(CVersionManagerEventProviderTest, CheckForSigPowerModeCfgTypeReceivedWithWrongParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigPowerModeCfgTypeReceived(const QString&)));
    m_pVersionManagerEventProvider->powerModeCfgTypeReceived("0A123$");
    EXPECT_NE(spy1.count(), 2);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_FALSE(args.at(0).type() == QVariant::UInt);
    EXPECT_FALSE(args.at(0).toString()== QString::fromStdString("0A00"));
}

TEST_F(CVersionManagerEventProviderTest, CheckForSigDisplayManagerSofVersionNoWithCorrectParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigDisplayManagerSofVersionNoUpdateReceived(const QString&)));
    m_pVersionManagerEventProvider->displayManagerSofVersionNoUpdateReceived(QString::fromStdString("0000"));
    EXPECT_EQ(spy1.count(), 1);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_TRUE(args.at(0).type() == QVariant::String);
    EXPECT_TRUE(args.at(0).toString()== QString::fromStdString("0000"));
}

TEST_F(CVersionManagerEventProviderTest, CheckForSigDisplayManagerSofVersionNoWithWrongParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigDisplayManagerSofVersionNoUpdateReceived(const QString&)));
    m_pVersionManagerEventProvider->displayManagerSofVersionNoUpdateReceived(QString::fromStdString("0000"));
    EXPECT_NE(spy1.count(), 2);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_FALSE(args.at(0).type() == QVariant::UInt);
    EXPECT_FALSE(args.at(0).toString()== QString::fromStdString("0"));
}


TEST_F(CVersionManagerEventProviderTest, CheckForSigButtonPanelSofVersionNoWithCorrectParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigButtonPanelSofVersionNoUpdateReceived(const QString&)));
    m_pVersionManagerEventProvider->buttonPanelSofVersionNoUpdateReceived(QString::fromStdString("0000"));
    EXPECT_EQ(spy1.count(), 1);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_TRUE(args.at(0).type() == QVariant::String);
    EXPECT_TRUE(args.at(0).toString()== QString::fromStdString("0000"));
}

TEST_F(CVersionManagerEventProviderTest, CheckForSigButtonPanelSofVersionNoWithWrongParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigButtonPanelSofVersionNoUpdateReceived(const QString&)));
    m_pVersionManagerEventProvider->buttonPanelSofVersionNoUpdateReceived(QString::fromStdString("0000"));
    EXPECT_NE(spy1.count(), 2);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_FALSE(args.at(0).type() == QVariant::UInt);
    EXPECT_FALSE(args.at(0).toString()== QString::fromStdString("1234"));
}

TEST_F(CVersionManagerEventProviderTest, CheckForSigSOCSofVersionNoWithCorrectParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigSOCSofVersionNoUpdateReceived(const QString&)));
    m_pVersionManagerEventProvider->socSofVersionNoUpdateReceived(QString::fromStdString("0000"));
    EXPECT_EQ(spy1.count(), 1);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_TRUE(args.at(0).type() == QVariant::String);
    EXPECT_TRUE(args.at(0).toString()== QString::fromStdString("0000"));
}

TEST_F(CVersionManagerEventProviderTest, CheckForSigSOCSofVersionNoWithWrongParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigSOCSofVersionNoUpdateReceived(const QString&)));
    m_pVersionManagerEventProvider->socSofVersionNoUpdateReceived(QString::fromStdString("0000"));
    EXPECT_NE(spy1.count(), 0);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_FALSE(args.at(0).type() == QVariant::UInt);
    EXPECT_FALSE(args.at(0).toString()== QString::fromStdString("1234"));
}

TEST_F(CVersionManagerEventProviderTest, CheckForSigButtonPanelPartNoWithCorrectParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigButtonPanelPartNoUpdateReceived(const QString&)));
    m_pVersionManagerEventProvider->buttonPanelPartNoReceived(QString::fromStdString("0000"));
    EXPECT_EQ(spy1.count(), 1);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_TRUE(args.at(0).type() == QVariant::String);
    EXPECT_TRUE(args.at(0).toString()== QString::fromStdString("0000"));
}

TEST_F(CVersionManagerEventProviderTest, CheckForSigButtonPanelPartNoWithWrongParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigButtonPanelPartNoUpdateReceived(const QString&)));
    m_pVersionManagerEventProvider->buttonPanelPartNoReceived(QString::fromStdString("0000"));
    EXPECT_NE(spy1.count(), 0);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_FALSE(args.at(0).type() == QVariant::UInt);
    EXPECT_FALSE(args.at(0).toString()== QString::fromStdString("1234"));
}

TEST_F(CVersionManagerEventProviderTest, CheckForSigParameterizationPartNoWithCorrectParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigParameterizationPartNoUpdateReceived(const QString&)));
    m_pVersionManagerEventProvider->parameterizationPartNoReceived(QString::fromStdString("0000"));
    EXPECT_EQ(spy1.count(), 1);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_TRUE(args.at(0).type() == QVariant::String);
    EXPECT_TRUE(args.at(0).toString()== QString::fromStdString("0000"));
}

TEST_F(CVersionManagerEventProviderTest, CheckForSigParameterizationPartNoWithWrongParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigParameterizationPartNoUpdateReceived(const QString&)));
    m_pVersionManagerEventProvider->parameterizationPartNoReceived(QString::fromStdString("0000"));
    EXPECT_NE(spy1.count(), 2);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_FALSE(args.at(0).type() == QVariant::UInt);
    EXPECT_FALSE(args.at(0).toString()== QString::fromStdString("1234"));
}

TEST_F(CVersionManagerEventProviderTest, CheckForSigDisplayHWPartNoWithCorrectParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigDisplayHWPartNoUpdateReceived(const QString&)));
    m_pVersionManagerEventProvider->displayHWPartNoReceived(QString::fromStdString("0000"));
    EXPECT_EQ(spy1.count(), 1);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_TRUE(args.at(0).type() == QVariant::String);
    EXPECT_TRUE(args.at(0).toString()== QString::fromStdString("0000"));
}

TEST_F(CVersionManagerEventProviderTest, CheckForSigDisplayHWPartNoWithWrongParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigDisplayHWPartNoUpdateReceived(const QString&)));
    m_pVersionManagerEventProvider->displayHWPartNoReceived(QString::fromStdString("0000"));
    EXPECT_NE(spy1.count(), 3);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_FALSE(args.at(0).type() == QVariant::UInt);
    EXPECT_FALSE(args.at(0).toString()== QString::fromStdString("1234"));
}

TEST_F(CVersionManagerEventProviderTest, CheckForSigSilverBoxPartNoWithCorrectParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigSilverBoxPartNoUpdateReceived(const QString&)));
    m_pVersionManagerEventProvider->silverBoxPartNoReceived(QString::fromStdString("0000"));
    EXPECT_EQ(spy1.count(), 1);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_TRUE(args.at(0).type() == QVariant::String);
    EXPECT_TRUE(args.at(0).toString()== QString::fromStdString("0000"));
}

TEST_F(CVersionManagerEventProviderTest, CheckForSigSilverBoxPartNoWithWrongParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigSilverBoxPartNoUpdateReceived(const QString&)));
    m_pVersionManagerEventProvider->silverBoxPartNoReceived(QString::fromStdString("0000"));
    EXPECT_NE(spy1.count(), 2);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_FALSE(args.at(0).type() == QVariant::UInt);
    EXPECT_FALSE(args.at(0).toString()== QString::fromStdString("1234"));
}

TEST_F(CVersionManagerEventProviderTest, CheckForSigContainerPartNoWithCorrectParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigContainerPartNoUpdateReceived(const QString&)));
    m_pVersionManagerEventProvider->containerPartNoReceived(QString::fromStdString("0000"));
    EXPECT_EQ(spy1.count(), 1);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_TRUE(args.at(0).type() == QVariant::String);
    EXPECT_TRUE(args.at(0).toString()== QString::fromStdString("0000"));
}

TEST_F(CVersionManagerEventProviderTest, CheckForSigContainerPartNoWithWrongParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigContainerPartNoUpdateReceived(const QString&)));
    m_pVersionManagerEventProvider->containerPartNoReceived(QString::fromStdString("0000"));
    EXPECT_NE(spy1.count(), 3);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_FALSE(args.at(0).type() == QVariant::UInt);
    EXPECT_FALSE(args.at(0).toString()== QString::fromStdString("1234"));
}

TEST_F(CVersionManagerEventProviderTest, CheckForSigVINInfoWithCorrectParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigVINInfoUpdateReceived(const QString&)));
    m_pVersionManagerEventProvider->vinPartNumberReceived(QString::fromStdString("0000"));
    EXPECT_EQ(spy1.count(), 1);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_TRUE(args.at(0).type() == QVariant::String);
    EXPECT_TRUE(args.at(0).toString()== QString::fromStdString("0000"));
}
TEST_F(CVersionManagerEventProviderTest, CheckForSigVINInfoWithWrongParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigVINInfoUpdateReceived(const QString&)));
    m_pVersionManagerEventProvider->vinPartNumberReceived(QString::fromStdString("0000"));
    EXPECT_NE(spy1.count(), 3);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_FALSE(args.at(0).type() == QVariant::UInt);
    EXPECT_FALSE(args.at(0).toString()== QString::fromStdString("1234"));
}

TEST_F(CVersionManagerEventProviderTest, CheckForSigVCInfoWithCorrectParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigVCInfoUpdateReceived(const QString&)));
    m_pVersionManagerEventProvider->vcInfoNumberReceived(QString::fromStdString("0000"));
    EXPECT_EQ(spy1.count(), 1);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_TRUE(args.at(0).type() == QVariant::String);
    EXPECT_TRUE(args.at(0).toString()== QString::fromStdString("0000"));
}

TEST_F(CVersionManagerEventProviderTest, CheckForSigVCInfoWithWrongParam)
{
    QSignalSpy spy1(m_pVersionManagerEventProvider, SIGNAL(sigVCInfoUpdateReceived(const QString&)));
    m_pVersionManagerEventProvider->vcInfoNumberReceived(QString::fromStdString("0000"));
    EXPECT_NE(spy1.count(), 3);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_FALSE(args.at(0).type() == QVariant::UInt);
    EXPECT_FALSE(args.at(0).toString()== QString::fromStdString("1234"));
}

