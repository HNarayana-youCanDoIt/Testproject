/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CTunerSM.h
 * @ingroup       HMIComponent
 * @author        Rahul Balyan
 * CTunerSM, The class is child of state machine tuner module's class and will override all the parent class methods.
 * These method will get invoked when particular state gets activated.
 **/

#ifndef CTUNERSM_H
#define CTUNERSM_H

#include "CTunerApplication.h"
#include "CTunerAdaptor.h"
#include "StateMachine_TML_HMI_SM.h"

/**
 * brief The CTunerSM class
 * The class is child of state machine tuner module's class and will override all the parent class methods.
 * These method will get invoked when particular state gets activated.
**/

class CTunerSM: public TML_HMI_SM::SCI_Tuner_OCB
{
public:
    CTunerSM(CTunerApplication& tunerApp);
    ~CTunerSM();

    /** Methods overriden from Media SM interface */

    /**
     * @brief enterTuner - State machine call back method when tuner state gets activated
     * @param void
     * @return void
    **/
    virtual void enterTuner() override;

    /**
     * @brief exitTuner - State machine call back method when tuner state gets deactivated
     * @param void
     * @return void
    **/
    virtual void exitTuner() override;

    /**
     * @brief enterTunerMain - State machine call back method when tuner main state gets activated
     * @param void
     * @return void
    **/
    virtual void enterTunerMain() override;

    /**
     * @brief exitTunerMain - State machine call back method when tuner main state gets deactivated
     * @param void
     * @return void
    **/
    virtual void exitTunerMain() override;

    /**
     * @brief enterTunerDefault - State machine call back method when Tuner default state gets activated
     * @param void
     * @return void
    **/
    virtual void enterTunerDefault() override;

    /**
     * @brief exitTunerDefault - State machine call back method when Tuner default state gets deactivated
     * @param void
     * @return void
    **/
    virtual void exitTunerDefault() override;

    /**
     * @brief enterTunerOption - State machine call back method when tuner option screen state gets activated
     * @param void
     * @return void
    **/
    virtual void enterTunerOption() override;

    /**
     * @brief exitTunerOption - State machine call back method when tuner option screen state gets deactivated
     * @param void
     * @return void
    **/
    virtual void exitTunerOption() override;

    /**
     * @brief enterTunerScan - State machine call back method when tuner scan state gets activated
     * @param void
     * @return void
    **/
    virtual void enterTunerScan() override;

    /**
     * @brief exitTunerScan - State machine call back method when tuner scan state gets deactivated
     * @param void
     * @return void
    **/
    virtual void exitTunerScan() override;

    /**
     * @brief enterTunerAutoSeekUp - State machine call back method when tuner AutoSeekUp state gets activated
     * @param void
     * @return void
    **/
    virtual void enterTunerAutoSeekUp() override;

    /**
     * @brief exitTunerAutoSeekUp - State machine call back method when tuner AutoSeekUp state gets deactivated
     * @param void
     * @return void
    **/
    virtual void exitTunerAutoSeekUp() override;

    /**
     * @brief enterTunerAutoSeekDown - State machine call back method when tuner AutoSeekDown state gets activated
     * @param void
     * @return void
    **/
    virtual void enterTunerAutoSeekDown() override;

    /**
     * @brief exitTunerAutoSeekDown - State machine call back method when tuner AutoSeekDown state gets deactivated
     * @param void
     * @return void
    **/
    virtual void exitTunerAutoSeekDown() override;

    /**
     * @brief enterTunerAutoStore - State machine call back method when tuner AutoStore state gets activated
     * @param void
     * @return void
    **/
    virtual void enterTunerAutoStore() override;

    /**
     * @brief exitTunerAutoStore - State machine call back method when tuner AutoStore state gets deactivated
     * @param void
     * @return void
    **/
    virtual void exitTunerAutoStore() override;

public:

private:
    /** Parent class pointer */
    CTunerApplication& mTunerApp;

};
#endif // CTUNERSM_H
