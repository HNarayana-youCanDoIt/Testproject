/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CW3WSM.h
 * @ingroup         HMIComponent
 * @author          Nishant Khandagale
 * CW3WSM, a State machine handler for W3W module,
 * CW3WSM inherits SCI_W3W_OCB to handle state-machine events.
 */

#ifndef CW3WSM_H
#define CW3WSM_H

#include "StateMachine_TML_HMI_SM.h"

class CW3WApplication;

/**
 * @brief CW3WSM, a State machine handler for W3W module,
 * It inherits SCI_W3w_OCB to handle statemachine events.
 */

class CW3WSM : public TML_HMI_SM::SCI_W3w_OCB
{
public:

    /**
    * @brief	CW3WSM::CW3WSM constructor for state machine class CW3WSM.
    * @param	QObject.
    * @return	NA.
    **/

    CW3WSM(CW3WApplication& W3WApp);
    /**
    * @brief	CW3WSM::~CW3WSM is destructor of state machine class CW3WSM
    * @param	NA.
    * @return	NA.
    **/
    ~CW3WSM();

    // SCI_W3W_OCB interface
public:
    /**
    * @brief	CW3WSM::enterW3W is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for entering W3W module
    * @param	void.
    * @return	void.
    **/
    void enterW3W() override;

    /**
    * @brief	CW3WSM::exitW3W is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for exiting W3W module
    * @param	void.
    * @return	void.
    **/
    void exitW3W() override;

    /**
    * @brief	CW3WSM::enterW3WStartupScreen is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for entering W3W Startup Screen.
    * @param	void.
    * @return	void.
    **/
    void enterW3WStartupScreen() override;

    /**
    * @brief	CW3WSM::exitW3WStartupScreen is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for exiting W3W Startup Screen.
    * @param	void.
    * @return	void.
    **/
    void exitW3WStartupScreen() override;

    /**
    * @brief	CW3WSM::enterW3WMainScreen is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for entering W3W Main Screen.
    * @param	void.
    * @return	void.
    **/
    void enterW3WMainScreen() override;

    /**
    * @brief	CW3WSM::exitW3WMainScreen is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for exiting W3W main Screen.
    * @param	void.
    * @return	void.
    **/
    void exitW3WMainScreen() override;

    /**
    * @brief	CW3WSM::enterW3WAddressSuggestionScreen is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for entering W3W address suggestion screen.
    * @param	void.
    * @return	void.
    **/
    void enterW3WAddressSuggestionScreen() override;

    /**
    * @brief	CW3WSM::exitW3WAddressSuggestionScreen is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for exiting W3W address suggestion screen.
    * @param	void.
    * @return	void.
    **/
    void exitW3WAddressSuggestionScreen() override;

    /**
    * @brief	CW3WSM::enterW3WPhoneBrowse is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for entering W3W Phone Browse screen.
    * @param	void.
    * @return	void.
    **/
    void enterW3WPhoneBrowse() override;

    /**
    * @brief	CW3WSM::exitW3WPhoneBrowse is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for exiting W3W Phone Browse screen.
    * @param	void.
    * @return	void.
    **/
    void exitW3WPhoneBrowse() override;

    /**
    * @brief	CW3WSM::enterContacts is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for entering W3W Contacts screen.
    * @param	void.
    * @return	void.
    **/
    void enterContacts() override;

    /**
    * @brief	CW3WSM::exitContacts is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for exiting W3W Contacts screen.
    * @param	void.
    * @return	void.
    **/
    void exitContacts() override;

    /**
    * @brief	CW3WSM::enterContactDetails is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for entering W3W Contact Details screen.
    * @param	void.
    * @return	void.
    **/
    void enterContactDetails() override;

    /**
    * @brief	CW3WSM::exitContactDetails is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for exiting W3W Contact Details screen.
    * @param	void.
    * @return	void.
    **/
    void exitContactDetails() override;

    /**
    * @brief	CW3WSM::enterW3WFavoritesScreen is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for entering W3W favorites screen.
    * @param	void.
    * @return	void.
    **/
    void enterW3WFavoritesScreen() override;

    /**
    * @brief	CW3WSM::exitW3WFavoritesScreen is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for exiting W3W favorites screen.
    * @param	void.
    * @return	void.
    **/
    void exitW3WFavoritesScreen() override;

    /**
    * @brief	CW3WSM::enterW3WRecentScreen is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for entering W3W recent addresses screen.
    * @param	void.
    * @return	void.
    **/
    void enterW3WRecentScreen() override;

    /**
    * @brief	CW3WSM::exitW3WRecentScreen is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for exiting W3W recent addresses screen.
    * @param	void.
    * @return	void.
    **/
    void exitW3WRecentScreen() override;

    /**
    * @brief	CW3WSM::enterW3WSetupScreen is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for entering W3W setup screen.
    * @param	void.
    * @return	void.
    **/
    void enterW3WSetupScreen() override;

    /**
    * @brief	CW3WSM::exitW3WSetupScreen is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for exiting W3W setup screen.
    * @param	void.
    * @return	void.
    **/
    void exitW3WSetupScreen() override;

    /**
    * @brief	CW3WSM::enterW3WAboutScreen is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for entering W3W about screen.
    * @param	void.
    * @return	void.
    **/
    void enterW3WAboutScreen() override;

    /**
    * @brief	CW3WSM::exitW3WAboutScreen is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for exiting W3W about screen.
    * @param	void.
    * @return	void.
    **/
    void exitW3WAboutScreen() override;

    /**
    * @brief	CW3WSM::enterW3WEditLabel is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for entering W3W Edit label screen.
    * @param	void.
    * @return	void.
    **/
    void enterW3WEditLabel() override;

    /**
    * @brief	CW3WSM::exitW3WEditLabel is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for exiting W3W Edit label screen.
    * @param	void.
    * @return	void.
    **/
    void exitW3WEditLabel() override;

    /**
    * @brief	CW3WSM::enterW3WVideoViewerScn is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for entering W3W Video Viewer screen.
    * @param	void.
    * @return	void.
    **/
    void enterW3WVideoViewerScn() override;

    /**
    * @brief	CW3WSM::exitW3WVideoViewerScn is state machine class callback function inherited from SCI_W3W_OCB
    * callback function from statemachine for exiting W3W Video Viewer screen.
    * @param	void.
    * @return	void.
    **/
    void exitW3WVideoViewerScn() override;

private:
    // Parent class pointer
    CW3WApplication& mW3WApp; // reference for W3W application class object

};

#endif // CW3WSM_H
