#ifndef CSOFTWAREUPDATEADAPTORTEST_H
#define CSOFTWAREUPDATEADAPTORTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include<gmock/gmock.h>
#include<iostream>
#include "PowerMode/CPowerModeAdaptor.h"
#include <QSignalSpy>
#include <QTest>
#include "logging.h"
using namespace std;
class CSoftwareUpdateAdaptor;

class CSoftwareUpdateAdaptorTest: public ::testing::Test
{
public:

    virtual void SetUp();
    virtual void TearDown();

    CSoftwareUpdateAdaptor* m_pSoftwareUpdateAdaptor;
};


#endif // CVERSIONMANAGERADAPTORTEST_H
