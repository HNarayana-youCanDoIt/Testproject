/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file            CDDriveNextDataElement.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDDriveNextDataElement, data class for DriveNext data element information.
 */

#ifndef CDDRIVENEXTDATAELEMENT_H
#define CDDRIVENEXTDATAELEMENT_H

#include <QObject>
#include <QString>
#include "implementations/CDriveNextResourceData.h"
#include "CDriveNextEnum.h"

/**
 * @brief CDDriveNextDataElement, a Data structure for DriveNext Data Element,
 * It maintains data information.
 */
class CDDriveNextDataElement : public QObject
{
    Q_OBJECT

    //// Property to get value field
    Q_PROPERTY(double value READ value NOTIFY sigValueChanged)

    //// Property to get errorType field
    Q_PROPERTY(CDriveNextEnum::EDNSignalErrorTypes errorType READ errorType NOTIFY sigErrorTypeChanged)

    //// Property to get dnTitle text field
    Q_PROPERTY(QString dnTitle READ dnTitle NOTIFY sigDnTitleChanged)

    //// Property to get dnValue field
    Q_PROPERTY(QString dnValue READ dnValue NOTIFY sigDnValueChanged)

    //// Property to get dnSubValue field
    Q_PROPERTY(QString dnSubValue READ dnSubValue NOTIFY sigDnSubValueChanged)

    //// Property to get dnUnit field
    Q_PROPERTY(QString dnUnit READ dnUnit NOTIFY sigDnUnitChanged)

    //// Property to get dnSubUnit field
    Q_PROPERTY(QString dnSubUnit READ dnSubUnit NOTIFY sigDnSubUnitChanged)

    //// Property to get enggTitle text field
    Q_PROPERTY(QString enggTitle READ enggTitle NOTIFY sigEnggTitleChanged)

    //// Property to get enggValue field
    Q_PROPERTY(QString enggValue READ enggValue NOTIFY sigEnggValueChanged)

    //// Property to get enggSubValue field
    Q_PROPERTY(QString enggSubValue READ enggSubValue NOTIFY sigEnggSubValueChanged)

    //// Property to get enggUnit field
    Q_PROPERTY(QString enggUnit READ enggUnit NOTIFY sigEnggUnitChanged)

    //// Property to get enggSubUnit field
    Q_PROPERTY(QString enggSubUnit READ enggSubUnit NOTIFY sigEnggSubUnitChanged)

public:
    //// QObject related functions

    /**
    * @brief	CDDriveNextDataElement is constructor of class CDDriveNextDataElement
    * @param	NA.
    * @return	NA.
    **/
    CDDriveNextDataElement ();

    //// Data read functions
    /**
    * @brief	getSignalType is get method of signal type value
    * @param	void.
    * @return	EDriveNextSignalTypes signal type value.
    **/
    EDriveNextSignalTypes getSignalType ();

public:
    //// Q_PROPERTY getter functions

    /**
    * @brief	value is get method of "value" property
    * @param	void.
    * @return	double value.
    **/
    double value ();

    /**
    * @brief	errorType is get method of "errorType" property
    * @param	void.
    * @return	CDriveNextEnum::EDNSignalErrorTypes error type.
    **/
    CDriveNextEnum::EDNSignalErrorTypes errorType ();

    /**
    * @brief	dnTitle is get method of "dnTitle" property
    * @param	void.
    * @return	QString DriveNext title text.
    **/
    QString dnTitle ();

    /**
    * @brief	dnValue is get method of "dnValue" property
    * @param	void.
    * @return	QString DriveNext value text.
    **/
    QString dnValue ();

    /**
    * @brief	dnSubValue is get method of "dnSubValue" property
    * @param	void.
    * @return	QString DriveNext sub value text.
    **/
    QString dnSubValue ();

    /**
    * @brief	dnUnit is get method of "dnUnit" property
    * @param	void.
    * @return	QString DriveNext unit text.
    **/
    QString dnUnit ();

    /**
    * @brief	dnSubUnit is get method of "dnSubUnit" property
    * @param	void.
    * @return	QString DriveNext sub unit text.
    **/
    QString dnSubUnit ();

    /**
    * @brief	enggTitle is get method of "enggTitle" property
    * @param	void.
    * @return	QString Engg title text.
    **/
    QString enggTitle ();

    /**
    * @brief	enggValue is get method of "enggValue" property
    * @param	void.
    * @return	QString Engg value text.
    **/
    QString enggValue ();

    /**
    * @brief	enggSubValue is get method of "enggSubValue" property
    * @param	void.
    * @return	QString Engg sub value text.
    **/
    QString enggSubValue ();

    /**
    * @brief	enggUnit is get method of "enggUnit" property
    * @param	void.
    * @return	QString Engg unit text.
    **/
    QString enggUnit ();

    /**
    * @brief	enggSubUnit is get method of "enggSubUnit" property
    * @param	void.
    * @return	QString Engg sub unit text.
    **/
    QString enggSubUnit ();

signals:
    //// Q_PROPERTY signals

    /**
    * @brief	sigValueChanged is change in value signal for "value" property
    * @return	void.
    * @return	void.
    **/
    void sigValueChanged ();

    /**
    * @brief	sigErrorTypeChanged is change in value signal for "errorType" property
    * @return	void.
    * @return	void.
    **/
    void sigErrorTypeChanged ();

    /**
    * @brief	sigDnTitleChanged is change in value signal for "dnTitle" property
    * @return	void.
    * @return	void.
    **/
    void sigDnTitleChanged ();

    /**
    * @brief	sigDnValueChanged is change in value signal for "dnValue" property
    * @return	void.
    * @return	void.
    **/
    void sigDnValueChanged ();

    /**
    * @brief	sigDnSubValueChanged is change in value signal for "dnSubValue" property
    * @return	void.
    * @return	void.
    **/
    void sigDnSubValueChanged ();

    /**
    * @brief	sigDnUnitChanged is change in value signal for "dnUnit" property
    * @return	void.
    * @return	void.
    **/
    void sigDnUnitChanged ();

    /**
    * @brief	sigDnSubUnitChanged is change in value signal for "dnSubUnit" property
    * @return	void.
    * @return	void.
    **/
    void sigDnSubUnitChanged ();

    /**
    * @brief	sigEnggTitleChanged is change in value signal for "enggTitle" property
    * @return	void.
    * @return	void.
    **/
    void sigEnggTitleChanged ();

    /**
    * @brief	sigEnggValueChanged is change in value signal for "enggValue" property
    * @return	void.
    * @return	void.
    **/
    void sigEnggValueChanged ();

    /**
    * @brief	sigEnggSubValueChanged is change in value signal for "enggSubValue" property
    * @return	void.
    * @return	void.
    **/
    void sigEnggSubValueChanged ();

    /**
    * @brief	sigEnggUnitChanged is change in value signal for "enggUnit" property
    * @return	void.
    * @return	void.
    **/
    void sigEnggUnitChanged ();

    /**
    * @brief	sigEnggSubUnitChanged is change in value signal for "enggSubUnit" property
    * @return	void.
    * @return	void.
    **/
    void sigEnggSubUnitChanged ();

public:
    //// Q_PROPERTY setter functions

    /**
    * @brief	setSignalData is set method of "value", "errorType" properties
    * @param	double value.
    * @param	CDriveNextEnum::EDNSignalErrorTypes error type.
    * @return	void.
    **/
    void setSignalData (double value, CDriveNextEnum::EDNSignalErrorTypes eErrorType);

    /**
    * @brief	setDnTitle is set method of "dnTitle" property
    * @param	QString DriveNext title text.
    * @return	void.
    **/
    void setDnTitle (QString strTitle);

    /**
    * @brief	setEnggTitle is set method of "enggTitle" property
    * @param	QString setEngg title text.
    * @return	void.
    **/
    void setEnggTitle (QString strTitle);

private:
    //// Q_PROPERTY setter functions

    /**
    * @brief	setDnValue is set method of "dnValue" property
    * @param	QString DriveNext value text.
    * @return	void.
    **/
    void setDnValue (QString strValue);

    /**
    * @brief	setDnSubValue is set method of "dnSubValue" property
    * @param	QString DriveNext sub value text.
    * @return	void.
    **/
    void setDnSubValue (QString strSubValue);

    /**
    * @brief	setDnUnit is set method of "dnUnit" property
    * @param	QString DriveNext unit text.
    * @return	void.
    **/
    void setDnUnit (QString strUnit);

    /**
    * @brief	setDnSubUnit is set method of "dnSubUnit" property
    * @param	QString DriveNext sub unit text.
    * @return	void.
    **/
    void setDnSubUnit (QString strSubUnit);

    /**
    * @brief	setEnggValue is set method of "enggValue" property
    * @param	QString Engg value text.
    * @return	void.
    **/
    void setEnggValue (QString strValue);

    /**
    * @brief	setEnggSubValue is set method of "enggSubValue" property
    * @param	QString Engg sub value text.
    * @return	void.
    **/
    void setEnggSubValue (QString strSubValue);

    /**
    * @brief	setEnggUnit is set method of "enggUnit" property=
    * @param	QString Engg unit text.
    * @return	void.
    **/
    void setEnggUnit (QString strUnit);

    /**
    * @brief	setEnggSubUnit is set method of "enggSubUnit" property
    * @param	QString Engg sub unit text.
    * @return	void.
    **/
    void setEnggSubUnit (QString strSubUnit);

public:
    //// Data update functions

    /**
    * @brief	setSignalType is set method of signal type value
    * @param	EDriveNextSignalTypes signal type value.
    * @return	void.
    **/
    void setSignalType (EDriveNextSignalTypes eSignalType);

public:
    //// Data converter static functions

    /**
    * @brief	updateScaleFactor is set method of Scale Factor for given unit type.
    * @param	CDriveNextEnum::EDNSigUnitType unit type.
    * @param	double Scale Factor.
    * @return	void.
    **/
    static void updateScaleFactor(CDriveNextEnum::EDNSigUnitType eUnitType, double dScaleFactor);

    /**
    * @brief	updateUnitValuesForElement is static mathod to update value and units as per requirements.
    * @param	CDDriveNextDataElement element object to update value and units.
    * @return	void.
    **/
    static void updateUnitValuesForElement(CDDriveNextDataElement &thisObj);

    /**
    * @brief	resetUnitScaleMap is static mathod used to reset unit scale map with default values.
    * @param	void.
    * @return	void.
    **/
    static void resetUnitScaleMap();

private:
    //// Data converter static functions

    /**
    * @brief	updateValueFormatForDnElement is static mathod to update value format as per requirements.
    * @param	CDDriveNextDataElement element object to update.
    * @return	void.
    **/
    static void updateValueFormatForDnElement(CDDriveNextDataElement &thisObj);

    /**
    * @brief	updateValueFormatForEnggElement is static mathod to update VALUE format as per requirements.
    * @param	CDDriveNextDataElement element object to update.
    * @return	void.
    **/
    static void updateValueFormatForEnggElement(CDDriveNextDataElement &thisObj);

    /**
    * @brief	setNumericFormatForDnElement is static mathod to set NUMERIC VALUE format as per requirements.
    * @param	CDDriveNextDataElement element object to update.
    * @return	void.
    **/
    static void setNumericFormatForDnElement(CDDriveNextDataElement &thisObj);

    /**
    * @brief	setNumericFormatForEnggElement is static mathod to set NUMERIC VALUE format as per requirements.
    * @param	CDDriveNextDataElement element object to update.
    * @return	void.
    **/
    static void setNumericFormatForEnggElement(CDDriveNextDataElement &thisObj);

    /**
    * @brief	setValueUnitFormatForDnElement is static mathod to set VALUE UNIT format as per requirements.
    * @param	CDDriveNextDataElement element object to update.
    * @return	void.
    **/
    static void setValueUnitFormatForDnElement(CDDriveNextDataElement &thisObj);

    /**
    * @brief	setValueUnitFormatForEnggElement is static mathod to set VALUE UNIT format as per requirements.
    * @param	CDDriveNextDataElement element object to update.
    * @return	void.
    **/
    static void setValueUnitFormatForEnggElement(CDDriveNextDataElement &thisObj);

    /**
    * @brief	setStringValueFormatForDnElement is static mathod to set STRING VALUE format as per requirements.
    * @param	CDDriveNextDataElement element object to update.
    * @return	void.
    **/
    static void setStringValueFormatForDnElement(CDDriveNextDataElement &thisObj);

    /**
    * @brief	setStringValueFormatForEnggElement is static mathod to set STRING VALUE format as per requirements.
    * @param	CDDriveNextDataElement element object to update.
    * @return	void.
    **/
    static void setStringValueFormatForEnggElement(CDDriveNextDataElement &thisObj);

    /**
    * @brief	setTimeStringFormatForDnElement is static mathod to set TIME STRING format as per requirements.
    * @param	CDDriveNextDataElement element object to update.
    * @return	void.
    **/
    static void setTimeStringFormatForDnElement(CDDriveNextDataElement &thisObj);

    /**
    * @brief	setTimeStringFormatForEnggElement is static mathod to set TIME STRING format as per requirements.
    * @param	CDDriveNextDataElement element object to update.
    * @return	void.
    **/
    static void setTimeStringFormatForEnggElement(CDDriveNextDataElement &thisObj);

    /**
    * @brief	setDurationStringFormatForDnElement is static mathod to set DURATION STRING format as per requirements.
    * @param	CDDriveNextDataElement element object to update.
    * @return	void.
    **/
    static void setDurationStringFormatForDnElement(CDDriveNextDataElement &thisObj);

    /**
    * @brief	setDurationStringFormatForEnggElement is static mathod to set DURATION STRING format as per requirements.
    * @param	CDDriveNextDataElement element object to update.
    * @return	void.
    **/
    static void setDurationStringFormatForEnggElement(CDDriveNextDataElement &thisObj);

    /**
    * @brief	getUnitString is static mathod gives text string for unit type.
    * @param	CDriveNextEnum::EDNSigUnitType unit type.
    * @return	QString string format for unit type.
    **/
    static QString getUnitString(CDriveNextEnum::EDNSigUnitType eUnitType);

    /**
    * @brief	getCustomUnitString is static mathod gives text string for custom unit type.
    * @param	CDriveNextEnum::EDNSigUnitType unit type.
    * @return	QString string format for custom unit type.
    **/
    static QString getCustomUnitString(CDriveNextEnum::EDNSigUnitType eUnitType);

    /**
    * @brief	getStrString is static mathod gives text string for string type.
    * @param	CDriveNextEnum::EDNSigStringType string type.
    * @return	QString string format for string type.
    **/
    static QString getStrString(CDriveNextEnum::EDNSigStringType eStringType);

    /**
    * @brief	getDNErrTextFormat is static mathod to get error text format as per requirements for DriveNextMain screen.
    * @param	CDriveNextEnum::EDNSignalErrorTypes Error Type.
    * @return	QString error text format as per requirements for DriveNextMain screen.
    **/
    static QString getDNErrTextFormat(CDriveNextEnum::EDNSignalErrorTypes eErrorType);

    /**
    * @brief	getEnggErrTextFormat is static mathod to get error text format as per requirements for DriveNextEngg screen.
    * @param	CDriveNextEnum::EDNSignalErrorTypes Error Type.
    * @return	QString error text format as per requirements for DriveNextEngg screen.
    **/
    static QString getEnggErrTextFormat(CDriveNextEnum::EDNSignalErrorTypes eErrorType);

private:
    //// Data variables

    /// s_mapScaleFactors: static map to hold value for scale factors for different unit types
    static std::map<CDriveNextEnum::EDNSigUnitType, double> s_mapScaleFactors;

    /// m_eSignalType: variable to hold value for data signal type
    EDriveNextSignalTypes m_eSignalType;

    /// m_bValueInitialized: variable to hold status for value init
    bool m_bValueInitialized;

    //// m_dValue: variable to hold value for "value" property
    double m_dValue;

    //// m_eErrorType: variable to hold value for "errorType" property
    CDriveNextEnum::EDNSignalErrorTypes m_eErrorType;

    //// m_strDnTitle: variable to hold value for "dnTitle" property
    QString m_strDnTitle;

    //// m_strDnValue: variable to hold value for "dnValue" property
    QString m_strDnValue;

    //// m_strDnSubValue: variable to hold value for "dnSubValue" property
    QString m_strDnSubValue;

    //// m_strDnUnit: variable to hold value for "dnUnit" property
    QString m_strDnUnit;

    //// m_strDnSubUnit: variable to hold value for "dnSubUnit" property
    QString m_strDnSubUnit;

    //// m_strEnggTitle: variable to hold value for "enggTitle" property
    QString m_strEnggTitle;

    //// m_strEnggValue: variable to hold value for "enggValue" property
    QString m_strEnggValue;

    //// m_strEnggSubValue: variable to hold value for "enggSubValue" property
    QString m_strEnggSubValue;

    //// m_strEnggUnit: variable to hold value for "enggUnit" property
    QString m_strEnggUnit;

    //// m_strEnggSubUnit: variable to hold value for "enggSubUnit" property
    QString m_strEnggSubUnit;
};

#endif // CDDRIVENEXTDATAELEMENT_H
