/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CParkAssistSM.h
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * CParkAssistSM.h, park assist module state machine header file, contains all the state machine callbacks of the module park assist.
 */

#ifndef CPARKASSISTSM_H
#define CPARKASSISTSM_H

#include <ParkAssist/CParkAssistApplication.h>
#include "StateMachine_TML_HMI_SM.h"
#include "HMIIncludes.h"
#include "logging.h"

/**
 * @brief The CParkAssistSM class: This class contains all the state machine callbacks of the module park assist.
 */
class CParkAssistSM : public TML_HMI_SM::SCI_ParkAssit_OCB
{

public:
    /**
    * @brief	CParkAssistSM - Constructor for SM class CParkAssistSM.
    * @param	CParkAssistApplication.
    * @return	NA.
    **/
    CParkAssistSM(CParkAssistApplication& parkAssistApp);

    /**
    * @brief	~CParkAssistSM - Destructor for SM class CParkAssistSM.
    * @param	NA.
    * @return	NA.
    **/
    ~CParkAssistSM();

public:

    // SCI_ParkAssit_OCB interface methods
    /**
     * @brief       Responsible for loading main park assist screen,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void enterParkAssist() override;

    /**
     * @brief       All the temporary data related to main park assist screen will be cleared,
     *              will be invoked from state machine...
     * @param       void.
     * @return      void.
     */
    void exitParkAssist() override;

    /*
     * FixME: Need to remove below methods from SCT as they are not used
    */
    void enterParkAssistMain() override;
    void exitParkAssistMain() override;

private:

    /** Reference to ParkAssist application class */
    CParkAssistApplication& mParkAssistApp;
};

#endif // CPARKASSISTSM_H
