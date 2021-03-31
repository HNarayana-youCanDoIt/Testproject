/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CSetupSM.h
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * CSetupSM.h, setup module state machine header file, contains all the state machine callbacks of the module setup.
 */
#ifndef CSETUPSM_H
#define CSETUPSM_H

#include <Setup/CSetupApplication.h>
#include "StateMachine_TML_HMI_SM.h"
#include "HMIIncludes.h"
#include "logging.h"
#include "DateAndTime/CDateAndTimeAdaptor.h"

/**
 * @brief The CSetupSM class: This class contains all the state machine callbacks of the module setup.
 */
class CSetupSM : public TML_HMI_SM::SCI_Setup_OCB
{
public:
    /**
    * @brief	CSetupSM - Constructor for SM class CSetupSM.
    * @param	CSetupApplication.
    * @return	NA.
    **/
    CSetupSM(CSetupApplication& setupApp);

    /**
    * @brief	~CSetupSM - Destructor for SM class CSetupSM.
    * @param	NA.
    * @return	NA.
    **/
    ~CSetupSM();

public:
    // SCI_Setup_OCB interface methods
    /**
     * @brief       Responsible for loading main setup screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterSetup() override;

    /**
     * @brief       Responsible for loading Vehicle setup screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterVehicleSetup() override;

    /**
     * @brief       Responsible for loading Audio setup screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterAudioSetup() override;

    /**
     * @brief       Responsible for loading BT setup screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterBluetoothSetup() override;

    /**
     * @brief       Responsible for loading Volume setup screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterVolumeSetup() override;

    /**
     * @brief       Responsible for loading Voice alerts screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterVoiceAlerts() override;

    /**
     * @brief       Responsible for loading General setup screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterGeneralSetup() override;

    /**
     * @brief       Responsible for loading Software details screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterSoftwareDetails() override;

    /**
     * @brief       Responsible for loading Display setup screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterDisplaySetup() override;

    /**
     * @brief       Responsible for loading Park assist screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterParkAssist() override;

    /**
     * @brief       Responsible for loading Moodligting screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterMoodLighting() override;

    /**
     * @brief       Responsible for loading Balance & Fader screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterBalanceFader() override;

    /**
     * @brief       Responsible for loading Audio preset screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterAudioPresets() override;

    /**
     * @brief       Responsible for loading QWERTY keyboard screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterEditSMSLightbox() override;

    /**
     * @brief       Responsible for loading AUX gain screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterAUXInGain() override;

    /**
     * @brief       Responsible for loading Date setting screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterSetDate() override;

    /**
     * @brief       Responsible for loading Time setting screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterSetTime() override;

    /**
     * @brief       Responsible for loading Paired devices screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterPairedDevices() override;

    /**
     * @brief       Responsible for loading Pair new device screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterPairNewDevice() override;

    /**
     * @brief       Responsible for loading Delete device screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterDeleteDevice() override;

    /**
     * @brief       Responsible for loading Lighting screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterLighting() override;

    /**
     * @brief       enterAboutMenu: Responsible for loading About Menu Screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterAboutMenu() override;

    /**
     * @brief       All the temporary data related to main setup screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitSetup() override;

    /**
     * @brief       All the temporary data related to Vehicle setup screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitVehicleSetup() override;

    /**
     * @brief       All the temporary data related to Audio setup screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitAudioSetup() override;

    /**
     * @brief       All the temporary data related to BT setup screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitBluetoothSetup() override;

    /**
     * @brief       All the temporary data related to Volume setup screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitVolumeSetup() override;

    /**
     * @brief       All the temporary data related to Voice alerts screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitVoiceAlerts() override;

    /**
     * @brief       All the temporary data related to General setup screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitGeneralSetup() override;

    /**
     * @brief       All the temporary data related to Software details setup screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitSoftwareDetails() override;

    /**
     * @brief       All the temporary data related to Display setup screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitDisplaySetup() override;

    /**
     * @brief       All the temporary data related to Park assist screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitParkAssist() override;

    /**
     * @brief       All the temporary data related to Moodlighting screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitMoodLighting() override;

    /**
     * @brief       All the temporary data related to Balance & Fader screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitBalanceFader() override;

    /**
     * @brief       All the temporary data related to Audio preset screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitAudioPresets() override;

    /**
     * @brief       All the temporary data related to QWERTY keyboard screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitEditSMSLightbox() override;

    /**
     * @brief       All the temporary data related to AUX gain screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitAUXInGain() override;

    /**
     * @brief       All the temporary data related to Date setting screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitSetDate() override;

    /**
     * @brief       All the temporary data related to Time setting screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitSetTime() override;

    /**
     * @brief       All the temporary data related to Paired device screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitPairedDevices() override;

    /**
     * @brief       All the temporary data related to Pair new device screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitPairNewDevice() override;

    /**
     * @brief       All the temporary data related to Delete device screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitDeleteDevice() override;

    /**
     * @brief       All the temporary data related to lighting screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitLighting() override;

    /**
     * @brief       exitAboutMenu: All the temporary data related to About screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitAboutMenu() override;

    /**
     * @brief       All the temporary data related to Setup state will be cleared,
     *              will be invoked from state machine...
     *              This method is called on exit from Setup state
     * @param       void.
     * @return      void.
     */
    void exitSetupState() override;

    /**
     * @brief       enterDriveNextSetup: Responsible for loading DriveNext Setup screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterDriveNextSetup() override;

    /**
     * @brief       exitDriveNextSetup: All the temporary data related to DriveNextSetup screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitDriveNextSetup() override;

private:
    // Reference to Setup Application class
    CSetupApplication& mSetupApp;
};

#endif // CSETUPSM_H
