#ifndef CVERSIONMANAGERPARAMTEST_H
#define CVERSIONMANAGERPARAMTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <iostream>
using namespace std;
class CVersionManagerAdaptor;

class CVersionManagerParamTest :public ::testing::TestWithParam<int>
{
protected:
    CVersionManagerAdaptor* m_pVersionManagerAdaptor;

    virtual void SetUp();
    virtual void TearDown();
};
#endif // CVERSIONMANAGERPARAMTEST_H
