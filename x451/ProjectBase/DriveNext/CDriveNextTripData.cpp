/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDriveNextTripData.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDriveNextTripData, a data class,
 * CDriveNextTripData is class used to hold DtiveNext Trip data.
 */

#include "CDriveNextTripData.h"
#include "CDDriveNextSignalInformation.h"
#include "implementations/CDriveNextResourceData.h"

CDriveNextTripData::CDriveNextTripData(QObject *parent) :
    QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    setTripType(CDriveNextEnum::EDNTripType::DRIVENEXT_TRIP_UNKNOWN);
}

CDriveNextTripData::CDriveNextTripData(CDriveNextEnum::EDNTripType eValue, QObject *parent) :
    QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eValue:%d", __FUNCTION__, static_cast<int>(eValue));
    setTripType(eValue);
}

CDriveNextTripData::~CDriveNextTripData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    m_listTripSignals.clear();
}

CDriveNextEnum::EDNTripType CDriveNextTripData::tripType()
{
    return m_eTripType;
}

void CDriveNextTripData::setTripType(CDriveNextEnum::EDNTripType eValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eValue:%d", __FUNCTION__, static_cast<int>(eValue));
    if (eValue != m_eTripType)
    {
        m_eTripType = eValue;
        emit sigTripTypeChanged();

        setTripSignals();
        switch (m_eTripType)
        {
        case CDriveNextEnum::EDNTripType::DRIVENEXT_CURRENT_TRIP :
        {
            setTripName(tr("TEXT_DN_TRIP_CURRENT"));
        }
            break;
        case CDriveNextEnum::EDNTripType::DRIVENEXT_TRIP_A :
        {
            setTripName(tr("TEXT_DN_TRIP_A"));
        }
            break;
        case CDriveNextEnum::EDNTripType::DRIVENEXT_TRIP_B :
        {
            setTripName(tr("TEXT_DN_TRIP_B"));
        }
            break;
        case CDriveNextEnum::EDNTripType::DRIVENEXT_OVERALL_TRIP :
        {
            setTripName(tr("TEXT_DN_TRIP_OVERALL"));
        }
            break;
        case CDriveNextEnum::EDNTripType::DRIVENEXT_BEST_TRIP :
        {
            setTripName(tr("TEXT_DN_TRIP_BEST"));
        }
            break;
        case CDriveNextEnum::EDNTripType::DRIVENEXT_LAST_TRIP :
        {
            setTripName(tr("TEXT_DN_TRIP_LAST"));
        }
            break;
        default:
        {
            setTripName("UNKNOWN");
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s trip name not defined", __FUNCTION__);
        }
            break;
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s no change in value", __FUNCTION__);
    }
}

QString CDriveNextTripData::tripName()
{
    return m_strTripName;
}

void CDriveNextTripData::setTripName(QString strValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s strValue:%s", __FUNCTION__, strValue.toStdString().data());
    if (strValue != m_strTripName)
    {
        m_strTripName = strValue;
        emit sigTripNameChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s no change in value", __FUNCTION__);
    }
}

QList<int> CDriveNextTripData::tripSignals()
{
    return m_listTripSignals;
}

void CDriveNextTripData::setTripSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_eTripType:%d", __FUNCTION__, static_cast<int>(m_eTripType));

    int iJumpIndex = -1;
    switch (m_eTripType)
    {
    case CDriveNextEnum::EDNTripType::DRIVENEXT_CURRENT_TRIP :
    {
        iJumpIndex = CDDriveNextSignalInformation::SIGNALS_PER_TRIP_COUNT*0;
    }
        break;
    case CDriveNextEnum::EDNTripType::DRIVENEXT_TRIP_A :
    {
        iJumpIndex = CDDriveNextSignalInformation::SIGNALS_PER_TRIP_COUNT*1;
    }
        break;
    case CDriveNextEnum::EDNTripType::DRIVENEXT_TRIP_B :
    {
        iJumpIndex = CDDriveNextSignalInformation::SIGNALS_PER_TRIP_COUNT*2;
    }
        break;
    case CDriveNextEnum::EDNTripType::DRIVENEXT_OVERALL_TRIP :
    {
        iJumpIndex = CDDriveNextSignalInformation::SIGNALS_PER_TRIP_COUNT*3;
    }
        break;
    case CDriveNextEnum::EDNTripType::DRIVENEXT_BEST_TRIP :
    {
        iJumpIndex = CDDriveNextSignalInformation::SIGNALS_PER_TRIP_COUNT*4;
    }
        break;
    case CDriveNextEnum::EDNTripType::DRIVENEXT_LAST_TRIP :
    {
        iJumpIndex = CDDriveNextSignalInformation::SIGNALS_PER_TRIP_COUNT*5;
    }
        break;
    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s trip type not handled", __FUNCTION__);
    }
        break;
    }

    if (iJumpIndex != -1)
    {
        m_listTripSignals.clear();
        for (int i = 0; i < CDriveNextEnum::EDNTripElements::DN_TRIP_ELEMENT_TOTAL_COUNT; i++)
        {
            m_listTripSignals.append((CDDriveNextSignalInformation::TRIP_SIGNAL_LIST[i] + iJumpIndex));
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s trip signals not defined", __FUNCTION__);
    }

    emit sigTripSignalsChanged();
}
