/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          SoundDemoSM.h
 * @ingroup       HMIComponent
 * @author        Guru Alingal
 * @brief         Class to implement the SCI_SoundDemo_OCB interface from State Machine
 */

#ifndef SOUNDDEMOSM_H
#define SOUNDDEMOSM_H
#include "CSoundDemoApplication.h"
#include "StateMachine_TML_HMI_SM.h"

class CSoundDemoApplication;

class CSoundDemoSM : public TML_HMI_SM::SCI_SoundDemo_OCB
{
public:
    CSoundDemoSM(CSoundDemoApplication* app);

    // SCI_SoundDemo_OCB interface
    /**
     * @brief enterSoundDemo: Operations to be performed while entering to sound demo state.
     * @param void
     * @return void
     */
    virtual void enterSoundDemo() override;

    /**
     * @brief enterSoundDemo: Operations to be performed while exiting the sound demo state.
     * @param void
     * @return void
     */
    virtual void exitSoundDemo() override;

private:
    /**
     * @brief m_app: Sound demo application
     */
    CSoundDemoApplication* m_app;
};

#endif // SOUNDDEMOSM_H
