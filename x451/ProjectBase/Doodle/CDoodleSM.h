/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDoodleSM.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDoodleSM, a State machine handler for Doodle module,
 * CDoodleSM inherits SCI_Doodle_OCB to handle state-machine events.
 */
//________________________________________________________________________________________________
#ifndef CDOODLESM_H
#define CDOODLESM_H

#include "StateMachine_TML_HMI_SM.h"

class CDoodleApplication;

//________________________________________________________________________________________________
/**
 * @brief CDoodleSM, a State machine handler for Doodle module,
 * It inherits SCI_Doodle_OCB to handle state machine events.
 */
class CDoodleSM : public TML_HMI_SM::SCI_DoodleSetup_OCB
{
public:

    /**
    * @brief    CDoodleSM::CDoodleSM constructor for state machine class CDoodleSM.
    * @param    QObject.
    * @return   NA.
    **/
    CDoodleSM(CDoodleApplication& DoodleApp);
    //________________________________________________________________________________________________
    /**
    * @brief    CDoodleSM::~CDoodleSM is destructor of state machine class CDoodleSM
    * @param    NA.
    * @return   NA.
    **/
    ~CDoodleSM();
    //________________________________________________________________________________________________
public:
    //// SCI_DoodleSetup_OCB interface

    /**
    * @brief    CDoodleSM::enterDoodleSetup is state machine class callback function inherited from SCI_DoodleSetup_OCB
    * callback function from state machine for entering Doodle module
    * @param    void.
    * @return   void.
    **/
    void enterDoodleSetup() override;
    //________________________________________________________________________________________________
    /**
    * @brief    CDoodleSM::exitDoodleSetup is state machine class callback function inherited from SCI_DoodleSetup_OCB
    * callback function from state machine for exiting Doodle module
    * @param    void.
    * @return   void.
    **/
    void exitDoodleSetup() override;
    //________________________________________________________________________________________________
    /**
    * @brief    CDoodleSM::enterDoodleSetupScreen is state machine class callback function inherited from SCI_DoodleSetup_OCB
    * callback function from state machine for entering Doodle module Setup Screen.
    * @param    void.
    * @return   void.
    **/
    void enterDoodleSetupScreen() override;
    //________________________________________________________________________________________________
    /**
    * @brief    CDoodleSM::exitDoodleSetupScreen is state machine class callback function inherited from SCI_DoodleSetup_OCB
    * callback function from state machine for exiting Doodle module Setup Screen.
    * @param    void.
    * @return   void.
    **/
    void exitDoodleSetupScreen() override;
    //________________________________________________________________________________________________
private:

    //// mDoodleApp: reference to CDoodleApplication class instance.
    CDoodleApplication& mDoodleApp;

    //________________________________________________________________________________________________
};

#endif // CDOODLESM_H
