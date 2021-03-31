#ifndef CVERSIONMANAGERADAPTORTEST_H
#define CVERSIONMANAGERADAPTORTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include<gmock/gmock.h>
#include<iostream>
#include <QSignalSpy>
#include <QTest>
#include "logging.h"
using namespace std;
class CVersionManagerAdaptor;

class CVersionManagerAdaptorTest: /*public ::testing::Test*/public ::testing::TestWithParam<int>
{
public:

    virtual void SetUp();
    virtual void TearDown();

    CVersionManagerAdaptor* m_pVersionManagerAdaptor;

    const QString INVALID_DATA =  "INVALID_DATA";
    const QString POWER_MODE_PEPS =  "01";
    const QString POWER_MODE_IGN =  "00";
};


#endif // CVERSIONMANAGERADAPTORTEST_H
