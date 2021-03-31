#ifndef CVERSIONMANAGEREVENTHANDLERTEST_H
#define CVERSIONMANAGEREVENTHANDLERTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include<gmock/gmock.h>
#include "VersionManager/CVersionManagerAdaptor.h"
#include "PowerMode/CPowerModeAdaptor.h"
#include<iostream>

using namespace std;
class CVersionManagerEventHandler;
//using ::testing::AtLeast;
//using ::testing::Return;
//using ::testing::_;
//using ::testing::NiceMock;

class CVersionManagerEventHandlerTest : public ::testing::Test {

public:
    virtual void SetUp();
    virtual void TearDown();

     CVersionManagerEventHandler* m_pVersionManagerEventHandler;

};

//class MockPowerModeAdaptor : public CPowerModeAdaptor {
//public:
//    MOCK_METHOD0(getPowerModeStatus, CPowerModeEnums::eVehiclePowerModes());
//};

#endif // CVERSIONMANAGEREVENTHANDLERTEST_H
