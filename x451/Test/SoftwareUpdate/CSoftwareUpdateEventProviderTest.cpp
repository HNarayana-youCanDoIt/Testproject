#include "CSoftwareUpdateEventProviderTest.h"

void CSoftwareUpdateEventProviderTest::SetUp()
{
    m_pSoftwareUpdateEventProvider = new CSoftwareUpdateEventProvider();
}

void CSoftwareUpdateEventProviderTest::TearDown()
{
    delete m_pSoftwareUpdateEventProvider;
    m_pSoftwareUpdateEventProvider = NULL;
}
TEST_F(CSoftwareUpdateEventProviderTest, CheckSoftwareUpdateEventProviderInstanceIsNotNull)
{
    ASSERT_TRUE(m_pSoftwareUpdateEventProvider != nullptr);
    cout<< "CSoftwareUpdateEventProviderTest Constructor PASSED"<<endl;
}

TEST_F(CSoftwareUpdateEventProviderTest, CheckForSigSWUpdateAvailableWithCorrectInput)
{
    QSignalSpy spy1(m_pSoftwareUpdateEventProvider, SIGNAL(sigSWUpdateAvailable(bool)));
    m_pSoftwareUpdateEventProvider->updateSwAvailabilityStatus(true);
    EXPECT_EQ(spy1.count(), 1);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_TRUE(args.at(0).type() == QVariant::Bool);
    EXPECT_TRUE(args.at(0).toBool() == true);
}

TEST_F(CSoftwareUpdateEventProviderTest, CheckForSigSWUpdateAvailableWithWrongInput)
{
    QSignalSpy spy1(m_pSoftwareUpdateEventProvider, SIGNAL(sigSWUpdateAvailable(bool)));
    m_pSoftwareUpdateEventProvider->updateSwAvailabilityStatus(true);
    EXPECT_NE(spy1.count(), 0);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_FALSE(args.at(0).type() == QVariant::UInt);
    EXPECT_FALSE(args.at(0).toBool() == false);
}

TEST_F(CSoftwareUpdateEventProviderTest, CheckForSigUpdateSoftwareWithCorrectInput)
{
    QSignalSpy spy1(m_pSoftwareUpdateEventProvider, SIGNAL(sigUpdateSoftware()));
    m_pSoftwareUpdateEventProvider->updateSoftware();
    EXPECT_EQ(spy1.count(), 1);
}
TEST_F(CSoftwareUpdateEventProviderTest, CheckForSigUpdateSoftwareWithWrongInput)
{
    QSignalSpy spy1(m_pSoftwareUpdateEventProvider, SIGNAL(sigUpdateSoftware()));
    m_pSoftwareUpdateEventProvider->updateSoftware();
    EXPECT_NE(spy1.count(), 0);
}


TEST_F(CSoftwareUpdateEventProviderTest, CheckForSigUpdateErrorWithCorrectInput)
{
    QSignalSpy spy1(m_pSoftwareUpdateEventProvider, SIGNAL(sigUpdateError(uint)));
    m_pSoftwareUpdateEventProvider->updateError(1);
    EXPECT_EQ(spy1.count(), 1);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_TRUE(args.at(0).type() == QVariant::UInt);
    EXPECT_TRUE(args.at(0).toUInt() == 1);
}
TEST_F(CSoftwareUpdateEventProviderTest, CheckForSigUpdateErrorWithWrongInput)
{
    QSignalSpy spy1(m_pSoftwareUpdateEventProvider, SIGNAL(sigUpdateError(uint)));
    m_pSoftwareUpdateEventProvider->updateError(1);
    EXPECT_NE(spy1.count(), 3);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_FALSE(args.at(0).type() == QVariant::String);
    EXPECT_FALSE(args.at(0).toUInt() == 3);
}

TEST_F(CSoftwareUpdateEventProviderTest, CheckForSigUpdateSwAvailabilityWithCorrectInput)
{
    QSignalSpy spy1(m_pSoftwareUpdateEventProvider, SIGNAL(sigUpdateSwAvailability(uint)));
    m_pSoftwareUpdateEventProvider->updateSwAvailability(1);
    EXPECT_EQ(spy1.count(), 1);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_TRUE(args.at(0).type() == QVariant::UInt);
    EXPECT_TRUE(args.at(0).toUInt() == 1);
}
TEST_F(CSoftwareUpdateEventProviderTest, CheckForSigUpdateSwAvailabilityWithWrongInput)
{
    QSignalSpy spy1(m_pSoftwareUpdateEventProvider, SIGNAL(sigUpdateSwAvailability(uint)));
    m_pSoftwareUpdateEventProvider->updateSwAvailability(1);
    EXPECT_NE(spy1.count(), 2);
    QList<QVariant> args = spy1.takeFirst();
    EXPECT_FALSE(args.at(0).type() == QVariant::String);
    EXPECT_FALSE(args.at(0).toUInt() == 3);
}

