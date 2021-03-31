#include "CSoftwareUpdateEventHandlerTest.h"
#include "SoftwareUpdate/CSoftwareUpdateEventHandler.h"


void CSoftwareUpdateEventHandlerTest::SetUp()
{
    m_pSoftwareUpdateEventHandler = new CSoftwareUpdateEventHandler();
}

void CSoftwareUpdateEventHandlerTest::TearDown()
{
    delete m_pSoftwareUpdateEventHandler;
    m_pSoftwareUpdateEventHandler = NULL;

}
TEST_F(CSoftwareUpdateEventHandlerTest, CheckSoftwareUpdateEventHandlerInstanceIsNotNull)
{
    ASSERT_TRUE(m_pSoftwareUpdateEventHandler != nullptr);
    cout<< "CSoftwareUpdateEventHandlerTest Constructor PASSED"<<endl;
}

TEST_F(CSoftwareUpdateEventHandlerTest, CheckForSlotsCoverage)
{
  m_pSoftwareUpdateEventHandler-> sltSWUpdateAvailable(true);
  m_pSoftwareUpdateEventHandler-> sltUpdateSoftware();
  m_pSoftwareUpdateEventHandler-> sltUpdateError(2);
  m_pSoftwareUpdateEventHandler-> sltUpdateSwAvailability(1);
}
