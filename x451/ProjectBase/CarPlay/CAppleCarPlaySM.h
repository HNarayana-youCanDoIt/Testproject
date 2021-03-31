/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CAppleCarPlaySM.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* This file is having the definition for CAppleCarPlaySM class of AppleCarPlay.
* This file implements the TML_HMI_SM::SCI_AppleCarPlay_OCB interface generated
* by Yakindu State Chart tool.
*/

#ifndef CAPPLECARPLAYSM_H
#define CAPPLECARPLAYSM_H

#include "HMIIncludes.h"

/**
 *  @category: Forward_declaration
 */
class CAppleCarPlayApplication;

/**
 * @class CAppleCarPlaySM
 * @brief The CAppleCarPlaySM class implements the TML_HMI_SM::SCI_AppleCarPlay_OCB
 *        interface generated
 * by Yakindu State Chart tool.
 */
class CAppleCarPlaySM : public TML_HMI_SM::SCI_CarPlay_OCB
{
public:
    /**
    * @brief	CAppleCarPlaySM::CAppleCarPlaySM constructor for class
    *           CAppleCarPlaySM.
    * @param	CAppleCarPlayApplication pAppleCarPlayApp
    * @return	NA.
    **/
    CAppleCarPlaySM(const CAppleCarPlayApplication *pAppleCarPlayApp);

    /**
    * @brief	CAppleCarPlaySM::~CAppleCarPlaySM destructor for class
    *           CAppleCarPlaySM.
    * @param	CAppleCarPlayApplication& drawersApp
    * @return	NA.
    **/
    ~CAppleCarPlaySM();

    /**
    * @brief    CAppleCarPlaySM::enterCarPlay enter function for AppleCarPlay
    *           State in StateMachine. This function is called when state
    *           machine enters in AppleCarPlay State.
    * @param	void.
    * @return	void.
    **/
    void enterCarPlay() override;

    /**
    * @brief    CAppleCarPlaySM::exitCarPlay exit function for AppleCarPlay
    *           State in StateMachine. This function is called when state
    *           machine exits from AppleCarPlay State.
    * @param	void.
    * @return	void.
    **/
    void exitCarPlay() override;

private:
    /**
     * @brief m_pAppleCarPlayApp: CAppleCarPlayApplication class pointer which
     *        creates this class object.
     */
    const CAppleCarPlayApplication *m_pAppleCarPlayApp;
};

#endif // CAPPLECARPLAYSM_H
