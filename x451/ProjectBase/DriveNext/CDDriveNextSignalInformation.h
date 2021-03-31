/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file            CDDriveNextSignalInformation.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDDriveNextSignalInformation, static data class for DriveNext signal data element information.
 */

#ifndef CDDRIVENEXTSIGNALINFORMATION_H
#define CDDRIVENEXTSIGNALINFORMATION_H

#include <QObject>
#include <QString>
#include "CFramework.h"
#include "CDriveNextEnum.h"
#include "CDriveNextData.h"

/**
 * @brief The CDDriveNextSignalInformation: Responsible holding DriveNext signal data information
 */
class CDDriveNextSignalInformation : public QObject
{
    Q_OBJECT
    //________________________________________________________________________________________________

public:
    //________________________________________________________________________________________________
    /**
    * @brief    initSignalsData: This function initialize signal data information
    * @param    void.
    * @return   void.
    */
    static void initSignalsData();
    //________________________________________________________________________________________________
    /**
    * @brief    resetSignalsData: This function reset signal data information
    * @param    void.
    * @return   void.
    */
    static void resetSignalsData();
    //________________________________________________________________________________________________
    /**
    * @brief    getSignalData: This function gives signal data information for provided signal type.
    * @param    int: signal type value.
    * @return   SDriveNextSignalInformation: signal data information.
    */
    static SDriveNextSignalInformation getSignalData(int index);
    //________________________________________________________________________________________________
    /**
    * @brief	roundDoubleWithDecimals is method to round off value with provided decimals places
    * @param	double value.
    * @param	uint decimals places, default value is 2 places.
    * @return	double rounded value.
    **/
    static double roundDoubleWithDecimals(double dValue, uint uiPlaces = 2);
    //________________________________________________________________________________________________

private:
    /**
    * @brief	CDDriveNextSignalInformation is constructor of class CDDriveNextSignalInformation,
    *			it is in private scope to restrict object creation
    * @param	QObject parent obj.
    * @return	NA.
    **/
    CDDriveNextSignalInformation (QObject *parent = nullptr);
    //________________________________________________________________________________________________

public:
    /**
     * @brief The int variable to hold trips count
     */
    static const int TRIPS_COUNT;

    /**
     * @brief The int variable to hold trips score range
     */
    static const int SCORE_RANGE;

    /**
     * @brief The int variable to hold signals count per trip
     */
    static const int SIGNALS_PER_TRIP_COUNT;

    /**
     * @brief list of signals used in trip details
     */
    static const int TRIP_SIGNAL_LIST[CDriveNextEnum::EDNTripElements::DN_TRIP_ELEMENT_TOTAL_COUNT];
    //________________________________________________________________________________________________

private:
    /**
     * @brief The array of SDriveNextSignalInformation struct: Responsible holding DriveNext signal information template
     */
    static const SDriveNextSignalInformation SIGNALS_DATA_INFO[];

    /**
     * @brief The array of CDDriveNextSignalInformation struct: Responsible holding all DriveNext signals information
     */

    static std::vector<SDriveNextSignalInformation> sm_vectSignalsInfo;
    //________________________________________________________________________________________________
};

#endif // CDDRIVENEXTSIGNALINFORMATION_H
