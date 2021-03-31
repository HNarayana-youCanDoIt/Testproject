#ifndef CSOFTWAREUPDATERESOURCEIMPLTEST_H
#define CSOFTWAREUPDATERESOURCEIMPLTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include<gmock/gmock.h>

class CSoftwareUpdateResourceImpl;
using namespace std;


class CSoftwareUpdateResourceImplTest : public ::testing::Test
{
protected:
    CSoftwareUpdateResourceImpl* m_pSoftwareUpdateResourceImpl;

    virtual void SetUp();
    virtual void TearDown();
};

#endif // CSOFTWAREUPDATERESOURCEIMPLTEST_H
