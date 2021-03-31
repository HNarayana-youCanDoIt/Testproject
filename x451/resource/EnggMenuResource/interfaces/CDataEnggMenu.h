/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file   CDataEnggMenu.h
 * @ingroup       HMIComponent
 * @author        Rajat Gupta
 * CDataEnggMenu, This file contains all the other  Data Types that
 * wil be  used in ResourceLayer to store the diff type of data
**/

#ifndef CDATAENGGMENU_H
#define CDATAENGGMENU_H

/**
 * @enum EIpType
 * @brief Enum to check the type of IP
 */
enum EIpType
{
    IP_INVALID = -1,
    IP_STATIC = 1,
    IP_DYNAMIC = 2,
};

/**
 * @enum EResourceTestAutomationStatus
 * @brief Enum to check the status of test Automation i.e enable/disable
 */
enum EResourceTestAutomationStatus
{
    TEST_AUTOMATION_INVALID = -1,
    TEST_AUTOMATION_DISABLE,
    TEST_AUTOMATION_ENABLE,
};

/**
 * @enum EResourceLogType
 * @brief Enum to check the type of Log
 */
enum EResourceLogType
{
    INVALID_LOGS = -1,
    DBUS_LOGS = 0,
    DLT_LOGS = 1,
    CPU_MEASUREMENT_LOGS = 2,
    RAM_MEASUREMENT_LOGS = 3,
    MAX_DBUG_LOG_TYPE = 5
};
#endif // CDATAENGGMENU_H
