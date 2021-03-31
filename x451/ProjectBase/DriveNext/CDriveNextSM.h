/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDriveNextSM.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDriveNextSM, a State machine handler for DriveNext module,
 * CDriveNextSM inherits SCI_DriveNext_OCB to handle state-machine events.
 */

#ifndef CDRIVENEXTSM_H
#define CDRIVENEXTSM_H

#include "StateMachine_TML_HMI_SM.h"

class CDriveNextApplication;

/**
 * @brief CDriveNextSM, a State machine handler for DriveNext module,
 * It inherits SCI_DriveNext_OCB to handle statemachine events.
 */

class CDriveNextSM : public TML_HMI_SM::SCI_DriveNext_OCB
{
public:
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextSM::CDriveNextSM constructor for state machine class CDriveNextSM.
    * @param	QObject.
    * @return	NA.
    **/

    CDriveNextSM(CDriveNextApplication& DriveNextApp);
    /**
    * @brief	CDriveNextSM::~CDriveNextSM is destructor of state machine class CDriveNextSM
    * @param	NA.
    * @return	NA.
    **/
    ~CDriveNextSM();
    //________________________________________________________________________________________________
    // SCI_DriveNext_OCB interface
public:
    /**
    * @brief	CDriveNextSM::enterDriveNext is state machine class callback function inherited from SCI_DriveNext_OCB
    * callback function from statemachine for entering DriveNext module
    * @param	void.
    * @return	void.
    **/
    void enterDriveNext() override;

    /**
    * @brief	CDriveNextSM::exitDriveNext is state machine class callback function inherited from SCI_DriveNext_OCB
    * callback function from statemachine for exiting DriveNext module
    * @param	void.
    * @return	void.
    **/
    void exitDriveNext() override;

    /**
    * @brief	CDriveNextSM::enterDriveNextTripsScreen is state machine class callback function inherited from SCI_DriveNext_OCB
    * callback function from statemachine for entering DriveNext module Trips Screen.
    * @param	void.
    * @return	void.
    **/
    void enterDriveNextTripsScreen() override;

    /**
    * @brief	CDriveNextSM::exitDriveNextTripsScreen is state machine class callback function inherited from SCI_DriveNext_OCB
    * callback function from statemachine for exiting DriveNext module Trips Screen.
    * @param	void.
    * @return	void.
    **/
    void exitDriveNextTripsScreen() override;

    /**
    * @brief	CDriveNextSM::enterDriveNextPerformanceBreakup is state machine class callback function inherited from SCI_DriveNext_OCB
    * callback function from statemachine for entering DriveNext module Performance Breakup screen.
    * @param	void.
    * @return	void.
    **/
    void enterDriveNextPerformanceBreakup() override;

    /**
    * @brief	CDriveNextSM::exitDriveNextPerformanceBreakup is state machine class callback function inherited from SCI_DriveNext_OCB
    * callback function from statemachine for exiting DriveNext module Performance Breakup screen.
    * @param	void.
    * @return	void.
    **/
    void exitDriveNextPerformanceBreakup() override;
    //________________________________________________________________________________________________
private:
    // Parent class pointer
    CDriveNextApplication& mDriveNextApp; // reference for DriveNext application class object

};

#endif // CDRIVENEXTSM_H
