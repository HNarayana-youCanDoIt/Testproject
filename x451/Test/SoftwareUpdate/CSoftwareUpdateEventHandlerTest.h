#ifndef CSOFTWAREUPDATEEVENTHANDLERTEST_H
#define CSOFTWAREUPDATEEVENTHANDLERTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include<gmock/gmock.h>
#include "SoftwareUpdate/CSoftwareUpdateAdaptor.h"
#include "PowerMode/CPowerModeAdaptor.h"
#include<iostream>

using namespace std;
class CSoftwareUpdateEventHandler;


class CSoftwareUpdateEventHandlerTest : public ::testing::Test {

public:
    virtual void SetUp();
    virtual void TearDown();

     CSoftwareUpdateEventHandler* m_pSoftwareUpdateEventHandler;

};

#endif // CSOFTWAREUPDATEEVENTHANDLERTEST_H
