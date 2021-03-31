/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CParkAssistData.cpp
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * This class is to store the Park Assist data like fault messages & alert icons visibility.
 */

#include "CParkAssistData.h"

CParkAssistData::CParkAssistData() :
    m_bIsAlertIconAvailable(false),
    m_strPdcRvcFaultMessage("")
{

}

CParkAssistData::CParkAssistData(QString strPdcRvcFaultMessage, bool bAlertIconVisibility) :
    m_bIsAlertIconAvailable(bAlertIconVisibility),
    m_strPdcRvcFaultMessage(strPdcRvcFaultMessage)
{

}

CParkAssistData::~CParkAssistData()
{

}

bool CParkAssistData::isAlertIconAvailable()
{
    return m_bIsAlertIconAvailable;
}

QString CParkAssistData::pdcRvcFaultMessage()
{
    return m_strPdcRvcFaultMessage;
}
