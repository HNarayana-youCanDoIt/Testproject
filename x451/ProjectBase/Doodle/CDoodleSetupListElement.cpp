/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file            CDoodleSetupListElement.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDoodleSetupListElement, class to hold doodle setup element data information
 */
//____________________________________________________________________________

#include "CDoodleSetupListElement.h"
#include "logging.h"

//____________________________________________________________________________
CDoodleSetupListElement::CDoodleSetupListElement(QObject *parent) :
    QObject(parent),
    m_eElementType(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_UNKNOWN),
    m_strName(""),
    m_bEnabled(false),
    m_bToggleStatus(false)
{
}
//____________________________________________________________________________
CDoodleSetupListElement::~CDoodleSetupListElement()
{
}
//____________________________________________________________________________
CDoodleEnum::EDoodleSetupElementTypes CDoodleSetupListElement::type()
{
    return m_eElementType;
}
//____________________________________________________________________________
void CDoodleSetupListElement::setType(CDoodleEnum::EDoodleSetupElementTypes eElementType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, eElementType:%d", __FUNCTION__, static_cast<int>(eElementType));
    if (eElementType != m_eElementType)
    {
        m_eElementType = eElementType;
        emit sigTypeChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, value not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
QString CDoodleSetupListElement::name()
{
    return m_strName;
}
//____________________________________________________________________________
void CDoodleSetupListElement::setName(QString strName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, strName:%s", __FUNCTION__, strName.toStdString().data());
    if (strName != m_strName)
    {
        m_strName = strName;
        emit sigNameChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, value not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
bool CDoodleSetupListElement::enabled()
{
    return m_bEnabled;
}
//____________________________________________________________________________
void CDoodleSetupListElement::setEnabled(bool bEnabled)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, bEnabled:%d", __FUNCTION__, bEnabled);
    if (bEnabled != m_bEnabled)
    {
        m_bEnabled = bEnabled;
        emit sigEnabledChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, value not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
bool CDoodleSetupListElement::toggleStatus()
{
    return m_bToggleStatus;
}
//____________________________________________________________________________
void CDoodleSetupListElement::setToggleStatus(bool bToggleStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, bToggleStatus:%d", __FUNCTION__, bToggleStatus);
    if (bToggleStatus != m_bToggleStatus)
    {
        m_bToggleStatus = bToggleStatus;
        emit sigToggleStatusChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, value not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
