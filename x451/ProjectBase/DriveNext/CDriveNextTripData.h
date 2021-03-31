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

#ifndef CDRIVENEXTTRIPDATA_H
#define CDRIVENEXTTRIPDATA_H

#include <QObject>
#include "CDriveNextData.h"
#include "CDriveNextEnum.h"
#include "CDDriveNextDataElement.h"

class CDriveNextTripData : public QObject
{
    Q_OBJECT
    //// tripType is property To get trip Type value
    Q_PROPERTY(CDriveNextEnum::EDNTripType tripType READ tripType NOTIFY sigTripTypeChanged)

    //// tripName is property To get trip Name text
    Q_PROPERTY(QString tripName READ tripName NOTIFY sigTripNameChanged)

    //// tripSignals is property To get trip signals list
    Q_PROPERTY(QList<int> tripSignals READ tripSignals NOTIFY sigTripSignalsChanged)

public:
    /**
    * @brief	CDriveNextTripData::CDriveNextTripData constructor for class CDriveNextTripData.
    * @param	QObject.
    * @return	NA.
    **/
    CDriveNextTripData(QObject *parent = nullptr);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextTripData::CDriveNextTripData constructor for class CDriveNextTripData.
    * @param	CDriveNextEnum::EDNTripType trip type.
    * @param	QObject.
    * @return	NA.
    **/
    CDriveNextTripData(CDriveNextEnum::EDNTripType eValue, QObject *parent = nullptr);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextTripData::~CDriveNextTripData is destructor of class CDriveNextTripData
    * @param	NA.
    * @return	NA.
    **/
    ~CDriveNextTripData();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextTripData::tripType is getter function for property "tripType"
    * @param	void.
    * @return	CDriveNextEnum::EDNTripType : Trip Type.
    **/
    CDriveNextEnum::EDNTripType tripType();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextTripData::setTripType is setter function for property "tripType"
    * @param	CDriveNextEnum::EDNTripType : Trip Type.
    * @return	void.
    **/
    void setTripType(CDriveNextEnum::EDNTripType eValue);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextTripData::tripName is getter function for property "tripName"
    * @param	void.
    * @return	QString : Trip Name Text.
    **/
    QString tripName();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextTripData::setTripName is setter function for property "tripName"
    * @param	QString : Trip Name Text.
    * @return	void.
    **/
    void setTripName(QString strValue);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextTripData::tripSignals is getter function for property "tripSignals"
    * @param	void.
    * @return	QList<int> : Trip signals list.
    **/
    QList<int> tripSignals();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextTripData::setTripSignals is init function for property "tripSignals"
    * @param	void.
    * @return	void.
    **/
    void setTripSignals();
    //________________________________________________________________________________________________
signals:
    /**
    * @brief	CDriveNextTripData::sigTripTypeChanged is change in value signal for property "tripType"
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigTripTypeChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextTripData::sigTripNameChanged is change in value signal for property "tripName"
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigTripNameChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextTripData::sigHarshBrakeChanged is change in value signal for property "harshBrake"
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigHarshBrakeChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextTripData::sigTripSignalsChanged is change in value signal for property "tripSignals"
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigTripSignalsChanged();
    //________________________________________________________________________________________________
private:
    //// object to hold trip type
    CDriveNextEnum::EDNTripType m_eTripType;

    //// string to hold trip name text
    QString m_strTripName;

    //// list of signals used in trip details
    QList<int> m_listTripSignals;
};

#endif // CDRIVENEXTTRIPDATA_H
