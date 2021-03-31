#ifndef CSOFTWAREUPDATEEVENTPROVIDERTEST_H
#define CSOFTWAREUPDATEEVENTPROVIDERTEST_H

#include "SoftwareUpdateResource/implementations/CSoftwareUpdateEventProvider.h"
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include<gmock/gmock.h>
#include<iostream>
#include <QSignalSpy>
#include <QTest>
#include "logging.h"

using namespace std;

class CSoftwareUpdateEventProviderTest: public ::testing::Test
{
protected:

   CSoftwareUpdateEventProvider* m_pSoftwareUpdateEventProvider;

        virtual void SetUp();
        virtual void TearDown();
    };


#endif // CSOFTWAREUPDATEEVENTPROVIDERTEST_H
