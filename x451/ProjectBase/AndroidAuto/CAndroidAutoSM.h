/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CAndroidAutoSM.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* This file is having the definition for CAndroidAutoSM class of AndroidAuto.
* This file implements the TML_HMI_SM::SCI_AndroidAuto_OCB interface generated
* by Yakindu State Chart tool.
*/

#ifndef CANDROIDAUTOSM_H
#define CANDROIDAUTOSM_H

#include "HMIIncludes.h"

/**
 *  @category: Forward_declaration
 */
class CAndroidAutoApplication;


/**
 * @class CAndroidAutoSM
 * @brief The CAndroidAutoSM class implements the TML_HMI_SM::SCI_AndroidAuto_OCB
 *        interface generated
 * by Yakindu State Chart tool.
 */
class CAndroidAutoSM : public TML_HMI_SM::SCI_AndroidAuto_OCB
{
public:
    /**
    * @brief	CAndroidAutoSM::CAndroidAutoSM constructor for class
    *           CAndroidAutoSM.
    * @param	CAndroidAutoApplication& drawersApp
    * @return	NA.
    **/
    CAndroidAutoSM(const CAndroidAutoApplication *pAndroidAutoApp);

    /**
    * @brief	CAndroidAutoSM::~CAndroidAutoSM destructor for class
    *           CAndroidAutoSM.
    * @param	CAndroidAutoApplication& drawersApp
    * @return	NA.
    **/
    ~CAndroidAutoSM();

    /**
    * @brief    CAndroidAutoSM::enterAndroidAuto enter function for AndroidAuto
    *           State in StateMachine. This function is called when state
    *           machine enters in AndroidAuto State.
    * @param	void.
    * @return	void.
    **/
    void enterAndroidAuto() override;

    /**
    * @brief    CAndroidAutoSM::exitAndroidAuto exit function for AndroidAuto
    *           State in StateMachine. This function is called when state
    *           machine exits from AndroidAuto State.
    * @param	void.
    * @return	void.
    **/
    void exitAndroidAuto() override;

private:
    // Parent class pointer
    const CAndroidAutoApplication *m_pAndroidAutoApp;
};

#endif // CANDROIDAUTOSM_H
