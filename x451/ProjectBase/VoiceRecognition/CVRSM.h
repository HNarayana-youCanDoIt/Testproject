/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CVRSM.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CVRSM class that is a state machine handler for VR module to handle
 * state machine events.
 */


#ifndef CVRSM_H
#define CVRSM_H

#include "StateMachine_TML_HMI_SM.h"

//! @category FORWARD DECLERATIONS
class CVRApplication;

class CVRSM: public TML_HMI_SM::SCI_Vr_OCB
{

public:

    /**
     * @brief   CVRSM: Constructor of CVRSM.
     * @param   objVRApp: QObject of CVRApplication class.
     * @return  NA.
     */
    CVRSM(CVRApplication& objVRApp);

    /**
     * @brief   ~CVRSM: Destructor of CVRSM
     * @param   NA.
     * @return  NA.
     */
    ~CVRSM();

    /************************************************************************//**
     * @category    OVERRIDEN METHODS of TML_HMI_SM::SCI_Vr_OCB interface
     ************************************************************************/
    void enterVRPickList() override;

    void exitVRPickList() override;

    void enterVRHelp() override;

    void exitVRHelp() override;

    void enterVRHelpMain() override;

    void exitVRHelpMain() override;

    void enterVRHelpDetail() override;

    void exitVRHelpDetail() override;

private:
    //! refernce of CVRApplication class
    CVRApplication&     m_objVRApp;
};

#endif // CVRSM_H
