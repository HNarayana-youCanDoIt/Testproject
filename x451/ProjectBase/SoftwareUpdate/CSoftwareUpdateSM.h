/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CSoftwareUpdate.h
 * @ingroup         HMIComponent
 * @author          Gaurav Garg
 * CSoftwareUpdate, a State machine handler for Software Update module,
 * CSoftwareUpdateSM inherits SCI_SoftwareUpdate_OCB to handle statemachine events.
 */

#ifndef CSOFTWAREUPDATESM_H
#define CSOFTWAREUPDATESM_H

#include "CSoftwareUpdateApplication.h"
#include "StateMachine_TML_HMI_SM.h"


/**
 * @brief CSoftwareUpdateSM, a State machine handler for Software Update module,
 * It inherits SCI_SoftwareUpdate_OCB to handle statemachine events.
 */
class CSoftwareUpdateSM: public TML_HMI_SM::SCI_SoftwareUpdate_OCB
{
public:
    //________________________________________________________________________________________________
    /**
    * @brief	CSoftwareUpdateSM::CSoftwareUpdateSM constructor for state machine class CSoftwareUpdateSM.
    * @param	CSoftwareUpdateApplication.
    * @return	NA.
    **/
    CSoftwareUpdateSM(CSoftwareUpdateApplication& softwareUpdateApp);

    /**
    * @brief	CSoftwareUpdateSM::~CSoftwareUpdateSM is destructor of state machine class CSoftwareUpdateSM
    * @param	NA.
    * @return	NA.
    **/
    ~CSoftwareUpdateSM();
    //________________________________________________________________________________________________
    // SCI_SoftwareUpdate_OCB interface
public:
    /**
    * @brief	CSoftwareUpdateSM::enterSoftwareUpdate is state machine class callback function inherited from SCI_SoftwareUpdate_OCB
    * callback function from statemachine for entering SoftwareUpdate module
    * @param	void.
    * @return	void.
    **/
    void enterSoftwareUpdateMain() override;

    /**
    * @brief	CSoftwareUpdateSM::exitSoftwareUpdate is state machine class callback function inherited from SCI_SoftwareUpdate_OCB
    * callback function from statemachine for exiting SoftwareUpdate module
    * @param	void.
    * @return	void.
    **/
    void exitSoftwareUpdateMain() override;

    /**
    * @brief	CSoftwareUpdateSM::enterSoftwareUpdate is state machine class callback function inherited from SCI_SoftwareUpdate_OCB
    * callback function from statemachine for entering SoftwareUpdate module
    * @param	void.
    * @return	void.
    **/
    void enterSoftwareSelectMode() override;

    /**
    * @brief	CSoftwareUpdateSM::exitSoftwareUpdate is state machine class callback function inherited from SCI_SoftwareUpdate_OCB
    * callback function from statemachine for exiting SoftwareUpdate module
    * @param	void.
    * @return	void.
    **/
    void exitSoftwareSelectMode() override;

    /**
    * @brief	CSoftwareUpdateSM::enterSoftwareUpdate is state machine class callback function inherited from SCI_SoftwareUpdate_OCB
    * callback function from statemachine for entering SoftwareUpdate module
    * @param	void.
    * @return	void.
    **/
    void enterSoftwareUpdate() override;

    /**
    * @brief	CSoftwareUpdateSM::exitSoftwareUpdate is state machine class callback function inherited from SCI_SoftwareUpdate_OCB
    * callback function from statemachine for exiting SoftwareUpdate module
    * @param	void.
    * @return	void.
    **/
    void exitSoftwareUpdate() override;

private:

    /**
    * @brief	callDeclineOnSwUpdate This method will abort the software update process if update button is clicked and cancel operation is performed
    * @param	void.
    * @return	void.
    **/
    void callDeclineOnSwUpdate();

    /* Reference to CSoftwareUpdateApplication */
    CSoftwareUpdateApplication& mSoftwareUpdateApp;
};

#endif // CSOFTWAREUPDATESM_H
