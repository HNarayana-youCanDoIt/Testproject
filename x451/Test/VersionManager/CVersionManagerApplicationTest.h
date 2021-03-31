#ifndef CVERSIONMANAGERAPPLICATIONTEST_H
#define CVERSIONMANAGERAPPLICATIONTEST_H


#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include<gmock/gmock.h>

class CVersionManagerApplication;
using namespace std;


class CVersionManagerApplicationTest: public ::testing::Test
{

protected:
    CVersionManagerApplication* m_pVersionManagerApplication;

    virtual void SetUp();
    virtual void TearDown();
};

#endif // CVERSIONMANAGERAPPLICATIONTEST_H
