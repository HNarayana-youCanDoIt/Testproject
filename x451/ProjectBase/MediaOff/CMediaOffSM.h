/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CMediaOffSM.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CMediaOffSM, a State machine handler for Media Off module,
 * CMediaOffSM inherits SCI_MediaOff_OCB to handle statemachine events.
 */

#ifndef CMEDIAOFFSM_H
#define CMEDIAOFFSM_H

#include "StateMachine_TML_HMI_SM.h"

class CMediaOffApplication;
class CMediaOffAdaptor;
class CMediaOffEventHandler;

/**
 * @brief CMediaOffSM, a State machine handler for Media Off module,
 * It inherits SCI_MediaOff_OCB to handle statemachine events.
 */
class CMediaOffSM : public TML_HMI_SM::SCI_MediaOff_OCB
{
public:
    //________________________________________________________________________________________________
    /**
    * @brief	CMediaOffSM::CMediaOffSM constructor for state machine class CMediaOffSM.
    * @param	QObject.
    * @return	NA.
    **/
    CMediaOffSM(CMediaOffApplication& mediaOffApp);
    /**
    * @brief	CMediaOffSM::~CMediaOffSM is destructor of state machine class CMediaOffSM
    * @param	NA.
    * @return	NA.
    **/
    ~CMediaOffSM();
    //________________________________________________________________________________________________
    // SCI_MediaOff_OCB interface
public:
    /**
    * @brief	CMediaOffSM::enterMediaOff is state machine class callback function inherited from SCI_MediaOff_OCB
    * callback function from statemachine for entering MediaOff module
    * @param	void.
    * @return	void.
    **/
    void enterMediaOff() override;
    /**
    * @brief	CMediaOffSM::exitMediaOff is state machine class callback function inherited from SCI_MediaOff_OCB
    * callback function from statemachine for exiting MediaOff module
    * @param	void.
    * @return	void.
    **/
    void exitMediaOff() override;

    /**
    * @brief	CMediaOffSM::enterMediaOffScreen is state machine class callback function inherited from SCI_MediaOff_OCB
    * callback function from statemachine for entering MediaOff screen
    * @param	void.
    * @return	void.
    **/
    void enterMediaOffScreen() override;
    /**
    * @brief	CMediaOffSM::exitMediaOffScreen is state machine class callback function inherited from SCI_MediaOff_OCB
    * callback function from statemachine for exiting MediaOff screen
    * @param	void.
    * @return	void.
    **/
    void exitMediaOffScreen() override;

    /**
    * @brief	CMediaOffSM::enterMediaOffSetDateScreen is state machine class callback function inherited from SCI_MediaOff_OCB
    * callback function from statemachine for entering MediaOff Set Date screen
    * @param	void.
    * @return	void.
    **/
    void enterMediaOffSetDateScreen() override;
    /**
    * @brief	CMediaOffSM::exitMediaOffSetDateScreen is state machine class callback function inherited from SCI_MediaOff_OCB
    * callback function from statemachine for exiting MediaOff Set Date screen
    * @param	void.
    * @return	void.
    **/
    void exitMediaOffSetDateScreen() override;
    //________________________________________________________________________________________________
private:
    // Parent class pointer
    CMediaOffApplication& mMediaOffApp; // reference for Media Off application class object
};

#endif // CMEDIAOFFSM_H
