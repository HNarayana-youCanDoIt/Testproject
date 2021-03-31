#ifndef CVERSIONMANAGEREVENTPROVIDERTEST_H
#define CVERSIONMANAGEREVENTPROVIDERTEST_H

#include "VersionManagerResource/implementations/CVersionManagerEventProvider.h"
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include<gmock/gmock.h>
#include<iostream>
#include <QSignalSpy>
#include <QTest>
#include "logging.h"

using namespace std;

class CVersionManagerEventProviderTest: public ::testing::Test
{
protected:

   CVersionManagerEventProvider* m_pVersionManagerEventProvider;

        virtual void SetUp();
        virtual void TearDown();
    };


#endif // CVERSIONMANAGEREVENTPROVIDERTEST_H
