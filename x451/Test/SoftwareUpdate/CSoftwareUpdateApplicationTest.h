#ifndef CSOFTWAREUPDATEAPPLICATIONTEST_H
#define CSOFTWAREUPDATEAPPLICATIONTEST_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include<gmock/gmock.h>

class CSoftwareUpdateApplication;
using namespace std;

class CSoftwareUpdateApplicationTest: public ::testing::Test
{
protected:
    CSoftwareUpdateApplication* m_pSoftwareUpdateApplication;

    virtual void SetUp();
    virtual void TearDown();
};

#endif // CSOFTWAREUPDATEAPPLICATIONTEST_H
