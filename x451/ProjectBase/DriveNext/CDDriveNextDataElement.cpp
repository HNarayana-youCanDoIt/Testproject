/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file            CDDriveNextDataElement.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDDriveNextDataElement, data class for DriveNext data element information.
 */

#include "logging.h"
#include "CDDriveNextDataElement.h"
#include "CDDriveNextSignalInformation.h"
#include "CDriveNextApplication.h"
#include "CDriveNextAdaptor.h"

std::map<CDriveNextEnum::EDNSigUnitType, double> CDDriveNextDataElement::s_mapScaleFactors;

CDDriveNextDataElement::CDDriveNextDataElement():
    m_eSignalType(EDriveNextSignalTypes::DRIVENEXT_SIG_UNKNOWN),
    m_bValueInitialized(false),
    m_dValue(0),
    m_strDnTitle(""),
    m_strDnValue(""),
    m_strDnSubValue(""),
    m_strDnUnit(""),
    m_strDnSubUnit(""),
    m_strEnggTitle(""),
    m_strEnggValue(""),
    m_strEnggSubValue(""),
    m_strEnggUnit(""),
    m_strEnggSubUnit("")
{
    //LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);removed unwanted logs
}

EDriveNextSignalTypes CDDriveNextDataElement::getSignalType()
{
    return m_eSignalType;
}

double CDDriveNextDataElement::value()
{
    return m_dValue;
}

CDriveNextEnum::EDNSignalErrorTypes CDDriveNextDataElement::errorType()
{
    return m_eErrorType;
}

QString CDDriveNextDataElement::dnTitle()
{
    return m_strDnTitle;
}

QString CDDriveNextDataElement::dnValue()
{
    return m_strDnValue;
}

QString CDDriveNextDataElement::dnSubValue()
{
    return m_strDnSubValue;
}

QString CDDriveNextDataElement::dnUnit()
{
    return m_strDnUnit;
}

QString CDDriveNextDataElement::dnSubUnit()
{
    return m_strDnSubUnit;
}

QString CDDriveNextDataElement::enggTitle()
{
    return m_strEnggTitle;
}

QString CDDriveNextDataElement::enggValue()
{
    return m_strEnggValue;
}

QString CDDriveNextDataElement::enggSubValue()
{
    return m_strEnggSubValue;
}

QString CDDriveNextDataElement::enggUnit()
{
    return m_strEnggUnit;
}

QString CDDriveNextDataElement::enggSubUnit()
{
    return m_strEnggSubUnit;
}

void CDDriveNextDataElement::setSignalData(double value, CDriveNextEnum::EDNSignalErrorTypes eErrorType)
{
    bool bChanged = false;

    if (m_eErrorType != eErrorType)
    {
        m_eErrorType = eErrorType;
        emit sigErrorTypeChanged();
        bChanged = true;
    }
    else
    {
        //Do nothing, As no change in eErrorType.
    }

    if ((m_dValue != value) || (!m_bValueInitialized))
    {
        m_bValueInitialized = true;
        m_dValue = value;
        emit sigValueChanged();
        bChanged = true;
    }
    else
    {
        //Do nothing, As no change in value.
    }

    if (bChanged)
    {
        updateUnitValuesForElement(*this);
    }
    else
    {
        //Do nothing, As no change in value and eErrorType.
    }
}

void CDDriveNextDataElement::setDnTitle(QString strTitle)
{
    if (m_strDnTitle != strTitle)
    {
        m_strDnTitle = strTitle;
        emit sigDnTitleChanged();
    }
    else
    {
        //Do nothing, As no change in strTitle.
    }
}

void CDDriveNextDataElement::setDnValue(QString strValue)
{
    if (m_strDnValue != strValue)
    {
        m_strDnValue = strValue;
        emit sigDnValueChanged();
    }
    else
    {
        //Do nothing, As no change in strValue.
    }
}

void CDDriveNextDataElement::setDnSubValue(QString strSubValue)
{
    if (m_strDnSubValue != strSubValue)
    {
        m_strDnSubValue = strSubValue;
        emit sigDnSubValueChanged();
    }
    else
    {
        //Do nothing, As no change in strSubValue.
    }
}

void CDDriveNextDataElement::setDnUnit(QString strUnit)
{
    if (m_strDnUnit != strUnit)
    {
        m_strDnUnit = strUnit;
        emit sigDnUnitChanged();
    }
    else
    {
        //Do nothing, As no change in strUnit.
    }
}

void CDDriveNextDataElement::setDnSubUnit(QString strSubUnit)
{
    if (m_strDnSubUnit != strSubUnit)
    {
        m_strDnSubUnit = strSubUnit;
        emit sigDnSubUnitChanged();
    }
    else
    {
        //Do nothing, As no change in strSubUnit.
    }
}

void CDDriveNextDataElement::setEnggTitle(QString strTitle)
{
    if (m_strEnggTitle != strTitle)
    {
        m_strEnggTitle = strTitle;
        emit sigEnggTitleChanged();
    }
    else
    {
        //Do nothing, As no change in strTitle.
    }
}

void CDDriveNextDataElement::setEnggValue(QString strValue)
{
    if (m_strEnggValue != strValue)
    {
        m_strEnggValue = strValue;
        emit sigEnggValueChanged();
    }
    else
    {
        //Do nothing, As no change in strValue.
    }
}

void CDDriveNextDataElement::setEnggSubValue(QString strSubValue)
{
    if (m_strEnggSubValue != strSubValue)
    {
        m_strEnggSubValue = strSubValue;
        emit sigEnggSubValueChanged();
    }
    else
    {
        //Do nothing, As no change in strSubValue.
    }
}

void CDDriveNextDataElement::setEnggUnit(QString strUnit)
{
    if (m_strEnggUnit != strUnit)
    {
        m_strEnggUnit = strUnit;
        emit sigEnggUnitChanged();
    }
    else
    {
        //Do nothing, As no change in strUnit.
    }
}

void CDDriveNextDataElement::setEnggSubUnit(QString strSubUnit)
{
    if (m_strEnggSubUnit != strSubUnit)
    {
        m_strEnggSubUnit = strSubUnit;
        emit sigEnggSubUnitChanged();
    }
    else
    {
        //Do nothing, As no change in strSubUnit.
    }
}

void CDDriveNextDataElement::setSignalType(EDriveNextSignalTypes eSignalType)
{
    //LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_eSignalType:%d, eSignalType:%d", __FUNCTION__, static_cast<int>(m_eSignalType), static_cast<int>(eSignalType));
    m_eSignalType = eSignalType;
}

void CDDriveNextDataElement::updateScaleFactor(CDriveNextEnum::EDNSigUnitType eUnitType, double dScaleFactor)
{
    //LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eUnitType:%d, dScaleFactor:%lf", __FUNCTION__, static_cast<int>(eUnitType), dScaleFactor);
    s_mapScaleFactors[eUnitType] = dScaleFactor;
}

void CDDriveNextDataElement::updateUnitValuesForElement(CDDriveNextDataElement &thisObj)
{
    //LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eSignalType:%d", __FUNCTION__, static_cast<int>(thisObj.m_eSignalType));
    updateValueFormatForDnElement(thisObj);
    updateValueFormatForEnggElement(thisObj);
}

void CDDriveNextDataElement::resetUnitScaleMap()
{
    s_mapScaleFactors.clear();

    s_mapScaleFactors[CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN] = 0;
    s_mapScaleFactors[CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE] = 1;
    s_mapScaleFactors[CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_MILI_LTR] = 1;
    s_mapScaleFactors[CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_RPM] = 1;
    s_mapScaleFactors[CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC] = 1;
    s_mapScaleFactors[CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_HRS] = 1;
    s_mapScaleFactors[CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_MTR_PER_SEC_SQR] = 0;
    s_mapScaleFactors[CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM] = 0;
    s_mapScaleFactors[CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM_PER_HR] = 0;
    s_mapScaleFactors[CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM_PER_LITRE] = 0;
    s_mapScaleFactors[CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE] = 0;
    s_mapScaleFactors[CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM_PER_LTR] = 0;
    s_mapScaleFactors[CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_TOTAL_COUNT] = 0;
}

void CDDriveNextDataElement::updateValueFormatForDnElement(CDDriveNextDataElement &thisObj)
{
    //LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eSignalType:%d", __FUNCTION__, static_cast<int>(thisObj.m_eSignalType));
    CDriveNextEnum::EDNSigFormatType eValueFormatType = CDDriveNextSignalInformation::getSignalData(static_cast<int>(thisObj.m_eSignalType)).m_DNInfo.m_eValueFormatType;
    switch (eValueFormatType)
    {
    case CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE:
    {
        setNumericFormatForDnElement(thisObj);
    }
        break;
    case CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT:
    {
        setValueUnitFormatForDnElement(thisObj);
    }
        break;
    case CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_TEXT_VAL:
    {
        setStringValueFormatForDnElement(thisObj);
    }
        break;
    case CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_HHHH_MM_SS:
    {
        setTimeStringFormatForDnElement(thisObj);
    }
        break;
    case CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_HHHH_MM:
    {
        setDurationStringFormatForDnElement(thisObj);
    }
        break;
    case CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_UNKNOWN:
    case CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_TOTAL_COUNT:
    {
        ////Do nothing Invalid enum value
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eSignalType:%d, eValueFormatType:%d", __FUNCTION__, static_cast<int>(thisObj.m_eSignalType), static_cast<int>(eValueFormatType));
    }
        break;
    default:
    {
        //Fix me unhandled format
    }
        break;
    }
}

void CDDriveNextDataElement::updateValueFormatForEnggElement(CDDriveNextDataElement &thisObj)
{
    //LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eSignalType:%d", __FUNCTION__, static_cast<int>(thisObj.m_eSignalType));
    CDriveNextEnum::EDNSigFormatType eValueFormatType = CDDriveNextSignalInformation::getSignalData(static_cast<int>(thisObj.m_eSignalType)).m_EnggInfo.m_eValueFormatType;
    switch (eValueFormatType)
    {
    case CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE:
    {
        setNumericFormatForEnggElement(thisObj);
    }
        break;
    case CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT:
    {
        setValueUnitFormatForEnggElement(thisObj);
    }
        break;
    case CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_TEXT_VAL:
    {
        setStringValueFormatForEnggElement(thisObj);
    }
        break;
    case CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_HHHH_MM_SS:
    {
        setTimeStringFormatForEnggElement(thisObj);
    }
        break;
    case CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_HHHH_MM:
    {
        setDurationStringFormatForEnggElement(thisObj);
    }
        break;
    case CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_UNKNOWN:
    case CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_TOTAL_COUNT:
    {
        ////Do nothing Invalid enum value
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eSignalType:%d, eValueFormatType:%d", __FUNCTION__, static_cast<int>(thisObj.m_eSignalType), static_cast<int>(eValueFormatType));
    }
        break;
    default:
    {
        //Fix me unhandled format
    }
        break;
    }
}

void CDDriveNextDataElement::setNumericFormatForDnElement(CDDriveNextDataElement &thisObj)
{
    //LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_eSignalType:%d, dValue:%lf", __FUNCTION__, static_cast<int>(thisObj.m_eSignalType), thisObj.m_dValue);

    QString strValue = "";
    QString strSubValue = "";
    QString strUnit = "";
    QString strSubUnit = "";

    if ((CDriveNextEnum::EDNSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_NOT_RUNNING != thisObj.m_eErrorType) &&
            (CDriveNextEnum::EDNSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_DISTANCE_THRESH != thisObj.m_eErrorType))
    {
        strValue = QString::number(CDDriveNextSignalInformation::roundDoubleWithDecimals(thisObj.m_dValue));
    }
    else
    {
        strValue = CDDriveNextDataElement::getDNErrTextFormat(thisObj.m_eErrorType);
    }

    thisObj.setDnValue(strValue);
    thisObj.setDnSubValue(strSubValue);
    thisObj.setDnUnit(strUnit);
    thisObj.setDnSubUnit(strSubUnit);
}

void CDDriveNextDataElement::setNumericFormatForEnggElement(CDDriveNextDataElement &thisObj)
{
    QString strValue = "";
    QString strSubValue = "";
    QString strUnit = "";
    QString strSubUnit = "";

    if ((CDriveNextEnum::EDNSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_NOT_RUNNING != thisObj.m_eErrorType) &&
            (CDriveNextEnum::EDNSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_DISTANCE_THRESH != thisObj.m_eErrorType))
    {
        strValue = QString::number(CDDriveNextSignalInformation::roundDoubleWithDecimals(thisObj.m_dValue));
    }
    else
    {
        strValue = CDDriveNextDataElement::getEnggErrTextFormat(thisObj.m_eErrorType);
    }

    thisObj.setEnggValue(strValue);
    thisObj.setEnggSubValue(strSubValue);
    thisObj.setEnggUnit(strUnit);
    thisObj.setEnggSubUnit(strSubUnit);
}

void CDDriveNextDataElement::setValueUnitFormatForDnElement(CDDriveNextDataElement &thisObj)
{
    CDriveNextEnum::EDNSigUnitType eUnitType = CDDriveNextSignalInformation::getSignalData(static_cast<int>(thisObj.m_eSignalType)).m_DNInfo.m_eUnitType;

    QString strValue = "";
    QString strSubValue = "";
    QString strUnit = "";
    QString strSubUnit = "";

    if ((s_mapScaleFactors.count(eUnitType) > 0) && (s_mapScaleFactors[eUnitType] > 0))
    {
        int roundOffByPlaces = 2;
        if (CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE == eUnitType)
        {
            roundOffByPlaces = 1;
        }
        else
        {
            //Do Nothing!
        }

        if ((CDriveNextEnum::EDNSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_NOT_RUNNING != thisObj.m_eErrorType) &&
                (CDriveNextEnum::EDNSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_DISTANCE_THRESH != thisObj.m_eErrorType))
        {
            strValue = QString::number(CDDriveNextSignalInformation::roundDoubleWithDecimals((thisObj.m_dValue * s_mapScaleFactors[eUnitType]), roundOffByPlaces));
            strUnit = getCustomUnitString(eUnitType);
        }
        else
        {
            strValue = CDDriveNextDataElement::getDNErrTextFormat(thisObj.m_eErrorType);
        }
    }
    else
    {
        strValue = CDDriveNextDataElement::getDNErrTextFormat(thisObj.m_eErrorType);
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eSignalType:%d, eUnitType:%d, Invalid Scale factor", __FUNCTION__, static_cast<int>(thisObj.m_eSignalType), static_cast<int>(eUnitType));
    }

    thisObj.setDnValue(strValue);
    thisObj.setDnSubValue(strSubValue);
    thisObj.setDnUnit(strUnit);
    thisObj.setDnSubUnit(strSubUnit);
}

void CDDriveNextDataElement::setValueUnitFormatForEnggElement(CDDriveNextDataElement &thisObj)
{
    CDriveNextEnum::EDNSigUnitType eUnitType = CDDriveNextSignalInformation::getSignalData(static_cast<int>(thisObj.m_eSignalType)).m_EnggInfo.m_eUnitType;

    QString strValue = "";
    QString strSubValue = "";
    QString strUnit = "";
    QString strSubUnit = "";

    if ((CDriveNextEnum::EDNSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_NOT_RUNNING != thisObj.m_eErrorType) &&
            (CDriveNextEnum::EDNSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_DISTANCE_THRESH != thisObj.m_eErrorType))
    {
        strValue = QString::number(CDDriveNextSignalInformation::roundDoubleWithDecimals(thisObj.m_dValue));
        strUnit = getUnitString(eUnitType);
    }
    else
    {
        strValue = CDDriveNextDataElement::getEnggErrTextFormat(thisObj.m_eErrorType);
    }

    thisObj.setEnggValue(strValue);
    thisObj.setEnggSubValue(strSubValue);
    thisObj.setEnggUnit(strUnit);
    thisObj.setEnggSubUnit(strSubUnit);
}

void CDDriveNextDataElement::setStringValueFormatForDnElement(CDDriveNextDataElement &thisObj)
{
    CDriveNextEnum::EDNSigStringType eStringType = CDDriveNextSignalInformation::getSignalData(static_cast<int>(thisObj.m_eSignalType)).m_DNInfo.m_eStringType;

    QString strValue = "";
    QString strSubValue = "";
    QString strUnit = "";
    QString strSubUnit = "";

    if ((CDriveNextEnum::EDNSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_NOT_RUNNING != thisObj.m_eErrorType) &&
            (CDriveNextEnum::EDNSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_DISTANCE_THRESH != thisObj.m_eErrorType))
    {
        EDriveNextSignalTypes eSignalType = CDDriveNextSignalInformation::getSignalData(static_cast<int>(thisObj.m_eSignalType)).m_eSignalType;

        if ((EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_MOSTTIMEGEAR == eSignalType) ||
                (EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_MOSTTIMEGEAR == eSignalType) ||
                (EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_MOSTTIMEGEAR == eSignalType) ||
                (EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_MOSTTIMEGEAR == eSignalType) ||
                (EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_MOSTTIMEGEAR == eSignalType) ||
                (EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_MOSTTIMEGEAR == eSignalType))
        {
            int iGear = CDDriveNextSignalInformation::roundDoubleWithDecimals(thisObj.m_dValue, 0);
            QString strGear =  QString::number(iGear);
            /*if (iGear > 0)
            {
                strGear = QString::number(iGear);
            }
            else if (iGear < 0)
            {
                strGear = "R";
            }
            else
            {
                strGear = "N";
            }*/
            strValue = getStrString(eStringType) + strGear;
        }
        else
        {
            strValue = getStrString(eStringType) + QString::number(CDDriveNextSignalInformation::roundDoubleWithDecimals(thisObj.m_dValue));
        }
    }
    else
    {
        strValue = CDDriveNextDataElement::getDNErrTextFormat(thisObj.m_eErrorType);
    }

    thisObj.setDnValue(strValue);
    thisObj.setDnSubValue(strSubValue);
    thisObj.setDnUnit(strUnit);
    thisObj.setDnSubUnit(strSubUnit);
}

void CDDriveNextDataElement::setStringValueFormatForEnggElement(CDDriveNextDataElement &thisObj)
{
    CDriveNextEnum::EDNSigStringType eStringType = CDDriveNextSignalInformation::getSignalData(static_cast<int>(thisObj.m_eSignalType)).m_EnggInfo.m_eStringType;

    QString strValue = "";
    QString strSubValue = "";
    QString strUnit = "";
    QString strSubUnit = "";

    if ((CDriveNextEnum::EDNSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_NOT_RUNNING != thisObj.m_eErrorType) &&
            (CDriveNextEnum::EDNSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_DISTANCE_THRESH != thisObj.m_eErrorType))
    {
        strValue = getStrString(eStringType) + QString::number(CDDriveNextSignalInformation::roundDoubleWithDecimals(thisObj.m_dValue));
    }
    else
    {
        strValue = CDDriveNextDataElement::getEnggErrTextFormat(thisObj.m_eErrorType);
    }

    thisObj.setEnggValue(strValue);
    thisObj.setEnggSubValue(strSubValue);
    thisObj.setEnggUnit(strUnit);
    thisObj.setEnggSubUnit(strSubUnit);
}

void CDDriveNextDataElement::setTimeStringFormatForDnElement(CDDriveNextDataElement &thisObj)
{
    int iHrs = thisObj.m_dValue/3600;
    int iMin = std::fmod(thisObj.m_dValue,3600)/60;
    int iSec = std::fmod(thisObj.m_dValue,60);

    QString strValue = "";
    QString strUnit = "";
    QString strSubValue = "";
    QString strSubUnit = "";

    if ((CDriveNextEnum::EDNSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_NOT_RUNNING != thisObj.m_eErrorType) &&
            (CDriveNextEnum::EDNSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_DISTANCE_THRESH != thisObj.m_eErrorType))
    {
        QString zeroHH = "";
        QString zeroMM = "";
        QString zeroSS = "";
        if (iHrs < 10) zeroHH = "0";
        if (iMin < 10) zeroMM = "0";
        if (iSec < 10) zeroSS = "0";

        strValue = zeroHH + QString::number(iHrs) + ":" + zeroMM + QString::number(iMin) + ":" + zeroSS + QString::number(iSec);
        strUnit = "s";
    }
    else
    {
        strValue = CDDriveNextDataElement::getDNErrTextFormat(thisObj.m_eErrorType);
    }

    thisObj.setDnValue(strValue);
    thisObj.setDnSubValue(strSubValue);
    thisObj.setDnUnit(strUnit);
    thisObj.setDnSubUnit(strSubUnit);
}

void CDDriveNextDataElement::setTimeStringFormatForEnggElement(CDDriveNextDataElement &thisObj)
{
    int iHrs = thisObj.m_dValue/3600;
    int iMin = std::fmod(thisObj.m_dValue,3600)/60;
    int iSec = std::fmod(thisObj.m_dValue,60);

    QString strValue = "";
    QString strUnit = "";
    QString strSubValue = "";
    QString strSubUnit = "";

    if ((CDriveNextEnum::EDNSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_NOT_RUNNING != thisObj.m_eErrorType) &&
            (CDriveNextEnum::EDNSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_DISTANCE_THRESH != thisObj.m_eErrorType))
    {
        strValue = QString::number(iHrs) + ":" + QString::number(iMin) + ":" + QString::number(iSec);
        strUnit = "s";
    }
    else
    {
        strValue = CDDriveNextDataElement::getEnggErrTextFormat(thisObj.m_eErrorType);
    }

    thisObj.setEnggValue(strValue);
    thisObj.setEnggSubValue(strSubValue);
    thisObj.setEnggUnit(strUnit);
    thisObj.setEnggSubUnit(strSubUnit);
}

void CDDriveNextDataElement::setDurationStringFormatForDnElement(CDDriveNextDataElement &thisObj)
{
    int iHrs = thisObj.m_dValue/3600;
    int iMin = std::fmod(thisObj.m_dValue,3600)/60;

    QString strValue = "";
    QString strSubValue = "";
    QString strUnit = "";
    QString strSubUnit = "";

    if ((CDriveNextEnum::EDNSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_NOT_RUNNING != thisObj.m_eErrorType) &&
            (CDriveNextEnum::EDNSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_DISTANCE_THRESH != thisObj.m_eErrorType))
    {
        strValue = QString::number(iMin);
        strUnit = "min";
        strSubValue = QString::number(iHrs);
        strSubUnit = "hr";
    }
    else
    {
        strValue = CDDriveNextDataElement::getDNErrTextFormat(thisObj.m_eErrorType);
    }

    thisObj.setDnValue(strValue);
    thisObj.setDnSubValue(strSubValue);
    thisObj.setDnUnit(strUnit);
    thisObj.setDnSubUnit(strSubUnit);
}

void CDDriveNextDataElement::setDurationStringFormatForEnggElement(CDDriveNextDataElement &thisObj)
{
    int iHrs = thisObj.m_dValue/3600;
    int iMin = std::fmod(thisObj.m_dValue,3600)/60;

    QString strValue = "";
    QString strSubValue = "";
    QString strUnit = "";
    QString strSubUnit = "";

    if ((CDriveNextEnum::EDNSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_NOT_RUNNING != thisObj.m_eErrorType) &&
            (CDriveNextEnum::EDNSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_DISTANCE_THRESH != thisObj.m_eErrorType))
    {
        strValue = QString::number(iMin);
        strUnit = "min";
        strSubValue = QString::number(iHrs);
        strSubUnit = "hr";
    }
    else
    {
        strValue = CDDriveNextDataElement::getEnggErrTextFormat(thisObj.m_eErrorType);
    }

    thisObj.setEnggValue(strValue);
    thisObj.setEnggSubValue(strSubValue);
    thisObj.setEnggUnit(strUnit);
    thisObj.setEnggSubUnit(strSubUnit);
}

QString CDDriveNextDataElement::getUnitString(CDriveNextEnum::EDNSigUnitType eUnitType)
{
    QString strUnit = "";
    switch (eUnitType)
    {
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE:
    {
        strUnit = "%";
    }
        break;
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_MILI_LTR:
    {
        strUnit = "ml";
    }
        break;
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_RPM:
    {
        strUnit = "rpm";
    }
        break;
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC:
    {
        strUnit = "sec";
    }
        break;
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_HRS:
    {
        strUnit = "hours";
    }
        break;
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_MTR_PER_SEC_SQR:
    {
        strUnit = "m/s²";
    }
        break;
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM:
    {
        strUnit = "km";
    }
        break;
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM_PER_HR:
    {
        strUnit = "km/h";
    }
        break;
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM_PER_LITRE:
    {
        strUnit = "km/ltr";
    }
        break;
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE:
    {
        strUnit = "/" + QString::number(CDriveNextApplication::getDriveNextAdaptor()->scoreProxyScale());
    }
        break;
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM_PER_LTR:
    {
        strUnit = "km/l";
    }
        break;
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN:
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_TOTAL_COUNT:
    default:
    {
        strUnit = "??";
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Unhandled eUnitType:%d", __FUNCTION__, static_cast<int>(eUnitType));
    }
        break;
    }
    return strUnit;
}

QString CDDriveNextDataElement::getCustomUnitString(CDriveNextEnum::EDNSigUnitType eUnitType)
{
    //Fix Me handle all custom unit formats here
    QString strUnit = "";
    switch (eUnitType)
    {
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE:
    {
        strUnit = "%";
    }
        break;
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_MILI_LTR:
    {
        //Fix Me need to handle changed units
        strUnit = "ml";
    }
        break;
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_RPM:
    {
        strUnit = "rpm";
    }
        break;
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC:
    {
        strUnit = "sec";
    }
        break;
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_HRS:
    {
        strUnit = "hours";
    }
        break;
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_MTR_PER_SEC_SQR:
    {
        //Fix Me need to handle changed units
        strUnit = "m/s²";
    }
        break;
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM:
    {
        //Fix Me need to handle changed units
        strUnit = "km";
    }
        break;
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM_PER_HR:
    {
        //Fix Me need to handle changed units
        strUnit = "km/h";
    }
        break;
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM_PER_LITRE:
    {
        //Fix Me need to handle changed units
        strUnit = "km/ltr";
    }
        break;
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE:
    {
        strUnit = "/" + QString::number(CDriveNextApplication::getDriveNextAdaptor()->getScoreRange());
    }
        break;
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM_PER_LTR:
    {
        //Fix Me need to handle changed units
        strUnit = "km/l";
    }
        break;
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN:
    case CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_TOTAL_COUNT:
    default:
    {
        strUnit = "??";
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Unhandled eUnitType:%d", __FUNCTION__, static_cast<int>(eUnitType));
    }
        break;
    }
    return strUnit;
}

QString CDDriveNextDataElement::getStrString(CDriveNextEnum::EDNSigStringType eStringType)
{
    QString strString = "";
    switch (eStringType)
    {
    case CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_GEAR:
    {
        strString = "Gear ";
    }
        break;
    case CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN:
    case CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_TOTAL_COUNT:
    default:
    {
        strString = "??";
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Unhandled eStringType:%d", __FUNCTION__, static_cast<int>(eStringType));
    }
        break;
    }
    return strString;
}

QString CDDriveNextDataElement::getDNErrTextFormat(CDriveNextEnum::EDNSignalErrorTypes eErrorType)
{
    CPP_UNUSED(eErrorType);
    return "-";
}

QString CDDriveNextDataElement::getEnggErrTextFormat(CDriveNextEnum::EDNSignalErrorTypes eErrorType)
{
    return "Err:" + QString::number(static_cast<int>(eErrorType));
}
