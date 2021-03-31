/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CVoiceAlertsEventProvider.h
 * @ingroup       HMIComponent
 * @author        Guru Alingal
 * CVoiceAlertsEventProvider, Class to send signals to Application layer on
 * voice alert updates
 */

#ifndef CVOICEALERTSEVENTPROVIDER_H
#define CVOICEALERTSEVENTPROVIDER_H

#include <QObject>

using namespace std;

class CVoiceAlertsEventProvider :  public QObject
{
    Q_OBJECT
public:
    CVoiceAlertsEventProvider(QObject* pParent = 0);
    ~CVoiceAlertsEventProvider();

signals:

    /**
     * @brief sigVasStatus - Signal to notify VAS Status changes
     * @param bStatus - Value of VAS Status
     * @return void
     */
    void sigVASStatus(bool bStatus);

    /**
     * @brief sigHuAlertStatus - Signal to notify HUAlertStatus
     * @param iAlertStaus - Value of HUAlertStatus
     * @return void
     */
    void sigHuAlertStatus(int iAlertStaus);

    /**
     * @brief sigHuInfoFeaturePresence - Signal to notify feature presence state
     * @param iPresence - Value of HuInfoFeaturePresence attribute
     * @return void
     */
    void sigHuInfoFeaturePresence(int iPresence);

    /**
     * @brief sigHuAlertHMISelection - Signal to notify the status of HMI selection
     * @param iHMISelection - Value of HMI Selection
     * @return void
     */
    void sigHuAlertHMISelection(int iHMISelection);

    /**
     * @brief sigCurDriveMode - Signal to notify the updated CurDriveMode
     * @param iDriveMode - Value of drive mode
     * @return void
     */
    void sigCurDriveMode(int iDriveMode);

    /**
     * @brief sigHuAlertState - Signal to notify voice alert
     * @param iAlert - Value of voice alert
     * @return void
     */
    void sigHuAlertState(int iAlert);

    /**
     * @brief sigHuAlertMceState - Signal to notify voice alert for Mce state
     * @param iMceAlert - Value of voice alert for Mce state
     * @return void
     */
    void sigHuAlertMceState(int iMceAlert);

public:

    /**
     * @brief updateVasStatus - To get the updated value of vas status
     *        attribute and notify to adaptation layer
     * @param bStatus - value in vas status attribute
     * @return void
     */
    void updateVasStatus(bool bStatus);

    /**
     * @brief updateHuAlertStatus - To get the updated value of HUAlert
     *        status attribute and notify to adaptation layer
     * @param iAlertStaus - Value in HU Alert status attribute
     * @return void
     */
    void updateHuAlertStatus(int iAlertStaus);

    /**
     * @brief updateHuInfoFeaturePresence - To get the updated value of vas status
     *        attribute and notify to adaptation layer
     * @param iPresence - Feature is available or not
     * @return void
     */
    void updateHuInfoFeaturePresence(int iPresence);

    /**
     * @brief updateHuInfoFeaturePresence - To get the updated value of vas status
     *        attribute and notify to adaptation layer
     * @param iPresence - Feature is available or not
     * @return void
     */
    void updateHuAlertHMISelection(int iHMISelection);

    /**
     * @brief updateCurDriveMode- To get the updated value of drive mode and
     *        notify to adaptation layer
     * @param iDriveMode - Current drive mode
     * @return void
     */
    void updateCurDriveMode(int iDriveMode);

    /**
     * @brief updateHuAlertState - To get the latest voice alert and notify to
     *        adaptation layer.
     * @param iAlert
     * @return void
     */
    void updateHuAlertState(int iAlert);

    /**
     * @brief updateHuAlertMceState - To get the latest voice alert and notify to
     *        adaptation layer for Mce state.
     * @param iMceAlert: Voice Alert received from service for mce state.
     * @return void
     */
    void updateHuAlertMceState(int iMceAlert);
};

#endif // CVOICEALERTSEVENTPROVIDER_H
