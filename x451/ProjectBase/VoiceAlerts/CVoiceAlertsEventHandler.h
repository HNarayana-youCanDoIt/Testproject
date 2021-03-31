/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
***************************************************************
*/
/**
* @file         CVoiceAlertsResImpl.h
* @ingroup       HMIComponent
* @author        Guru Alingal
* @brief CVoiceAlertsEventHandler class will be used to receive the data sent from voice
* alert resource layer and pass on the information to voice alert adaptor.
*/
#ifndef CVOICEALERTSEVENTHANDLER_H
#define CVOICEALERTSEVENTHANDLER_H

#include <QObject>
#include <VoiceAlertsEnum.h>
#include <CVoiceAlertsAdaptor.h>
#include <ResourceFactory.hpp>
#include <resource/VoiceAlerts/implementations/CVoiceAlertsResImpl.h>

class CVoiceAlertsEventHandler : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief CVoiceAlertsEventHandler -Constructor for voice alert event handler
     * @param parent
     */
    CVoiceAlertsEventHandler(QObject* parent = nullptr);

    ~CVoiceAlertsEventHandler();

    /**
     * @brief registerConnections - To regisetr connetctions of all the signals
     * to be emitted from event provider
     * @param void
     * @return void
     */
    void registerConnections();

private slots:

    /**
     * @brief sltVasStatus - Slot to handle the VAS status update
     * @param bStatus - Value of VAS state
     * @return void
     */
    void sltVASStatus(bool bStatus);

    /**
     * @brief sltHuAlertStatus - Slot to handle the status of voice alert
     * @param iAlertStaus - current status voice alert
     * @return void
     */
    void sltHuAlertStatus(int iAlertStaus);

    /**
     * @brief sltHuInfoFeaturePresence - Slot to handle the status of voice
     *        feature presence
     * @param iPresence - current value of feature presence
     * @return void
     */
    void sltHuInfoFeaturePresence(int iPresence);

    /**
     * @brief sltHuAlertHMISelection - Slot to handle the status update of
     *        HMISelection
     * @param iHMISelection - current value of HMI selection
     * @return void
     */
    void sltHuAlertHMISelection(int iHMISelection);

    /**
     * @brief sltCurDriveMode - Slot to handle update in drive mode
     * @param iDriveMode - Current drive mode
     * @return void
     */
    void sltCurDriveMode(int iDriveMode);

    /**
     * @brief sltHuAlertState - SLot to handle update in voice alert
     * @param iAlert - current voice alert
     * @return void
     */
    void sltHuAlertState(int iAlert);

    /**
     * @brief sltHuAlertMceState - SLot to handle update in voice alert for Mce state.
     * @param iMceAlert - current voice alert for Mce state.
     * @return void
     */
    void sltHuAlertMceState(int iMceAlert);

};

#endif
