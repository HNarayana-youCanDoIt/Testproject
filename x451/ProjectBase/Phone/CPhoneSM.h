/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CPhoneSM.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CPhoneSM class that is a state machine handler for Phone module to handle
 * state machine events.
 */

#ifndef CPHONESM_H
#define CPHONESM_H

#include "StateMachine_TML_HMI_SM.h"

//! @category FORWARD DECLERATIONS
class CPhoneApplication;

/*!
 * @class CPhoneSM
 * @brief This  class is a state machine handler for Phone module to handle
 * state machine events.
 */
class CPhoneSM: public TML_HMI_SM::SCI_Phone_OCB
{
public:
    CPhoneSM(CPhoneApplication& objPhoneApp);
    ~CPhoneSM();

    virtual void enterPhone() override;
    virtual void exitPhone() override;
    virtual void enterPhoneBrowse() override;
    virtual void exitPhoneBrowse() override;
    virtual void enterPhoneCall() override;
    virtual void exitPhoneCall() override;
    virtual void enterCallLogs() override;
    virtual void exitCallLogs() override;
    virtual void enterContacts() override;
    virtual void exitContacts() override;
    virtual void enterFavorites() override;
    virtual void exitFavorites() override;
    virtual void enterNumPad() override;
    virtual void exitNumPad() override;
    virtual void enterPhoneCallScreen() override;
    virtual void exitPhoneCallScreen() override;
    virtual void enterParticipantsScreen() override;
    virtual void exitParticipantsScreen() override;
    virtual void enterContactDetails() override;
    virtual void exitContactDetails() override;
    virtual void enterFrequentlyDialed() override;
    virtual void exitFrequentlyDialed() override;

private:
    CPhoneApplication&  m_objPhoneApp;
};

#endif // CPHONESM_H
