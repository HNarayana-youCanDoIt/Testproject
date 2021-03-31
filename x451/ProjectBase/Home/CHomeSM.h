/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CHomeSM.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CHomeSM, a State machine handler for Home module,
 * CHomeSM inherits SCI_EnggMenu_OCB to handle statemachine events.
 */

#ifndef CHOMESM_H
#define CHOMESM_H

#include "StateMachine_TML_HMI_SM.h"

class CHomeApplication;
class CHomeAdaptor;
class CHomeEventHandler;

/**
 * @brief CHomeSM, a State machine handler for Home module,
 * It inherits SCI_EnggMenu_OCB to handle statemachine events.
 */

class CHomeSM : public TML_HMI_SM::SCI_Home_OCB
{
public:
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeSM::CHomeSM constructor for state machine class CHomeSM.
    * @param	QObject.
    * @return	NA.
    **/
    CHomeSM(CHomeApplication& homeApp);
    /**
    * @brief	CHomeSM::~CHomeSM is destructor of state machine class CHomeSM
    * @param	NA.
    * @return	NA.
    **/
    ~CHomeSM();
    //________________________________________________________________________________________________
    // SCI_Home_OCB interface
public:
    /**
    * @brief	CHomeSM::enterHome is state machine class callback function inherited from SCI_Home_OCB
    * callback function from statemachine for entering home module
    * @param	void.
    * @return	void.
    **/
    void enterHome() override;
    /**
    * @brief	CHomeSM::exitHome is state machine class callback function inherited from SCI_Home_OCB
    * callback function from statemachine for exiting home module
    * @param	void.
    * @return	void.
    **/
    void exitHome() override;
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeSM::enterHomeScreenMain is state machine class callback function inherited from SCI_Home_OCB
    * callback function from statemachine for entering home main screen
    * @param	void.
    * @return	void.
    **/
    void enterHomeScreenMain() override;
    /**
    * @brief	CHomeSM::exitHomeScreenMain is state machine class callback function inherited from SCI_Home_OCB
    * callback function from statemachine for exiting home main screen
    * @param	void.
    * @return	void.
    **/
    void exitHomeScreenMain() override;
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeSM::enterHomeScreenUpdateShortcuts is state machine class callback function inherited from SCI_Home_OCB
    * callback function from statemachine for entering home update screen
    * @param	void.
    * @return	void.
    **/
    void enterHomeScreenUpdateShortcuts() override;
    /**
    * @brief	CHomeSM::exitHomeScreenUpdateShortcuts is state machine class callback function inherited from SCI_Home_OCB
    * callback function from statemachine for exiting home update screen
    * @param	void.
    * @return	void.
    **/
    void exitHomeScreenUpdateShortcuts() override;

    /**
    * @brief	CHomeSM::enterConfigureFavHK is state machine class callback function inherited from SCI_Home_OCB
    * callback function from statemachine for entering ConfigureFavHK screen
    * @param	void.
    * @return	void.
    **/
    virtual void enterConfigureFavHK() override;
    /**
    * @brief	CHomeSM::exitConfigureFavHK is state machine class callback function inherited from SCI_Home_OCB
    * callback function from statemachine for exiting ConfigureFavHK screen
    * @param	void.
    * @return	void.
    **/
    virtual void exitConfigureFavHK() override;
    //________________________________________________________________________________________________
private:
    // Parent class pointer
    CHomeApplication& mHomeApp; // reference for home application class object
};

#endif // CHOMESM_H
