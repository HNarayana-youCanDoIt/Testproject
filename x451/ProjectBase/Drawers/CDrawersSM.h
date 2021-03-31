/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CDrawersSM.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* This file is having the definition for CDrawersSM class of Drawers.
* This file implements the TML_HMI_SM::SCI_Drawers_OCB interface generated
* by Yakindu State Chart tool.
*/

#ifndef CDRAWERSSM_H
#define CDRAWERSSM_H

#include "CDrawersApplication.h"
#include "HMIIncludes.h"

/**
 * @class CDrawersSM
 * @brief The CDrawersSM class implements the TML_HMI_SM::SCI_Drawers_OCB
 *        interface generated
 * by Yakindu State Chart tool.
 */
class CDrawersSM : public TML_HMI_SM::SCI_Drawers_OCB
{
public:
    /**
    * @brief	CDrawersSM::CDrawersSM constructor for class CDrawersSM.
    * @param	CDrawersApplication& drawersApp
    * @return	NA.
    **/
    CDrawersSM(CDrawersApplication& drawersApp);

    /**
    * @brief	CDrawersSM::~CDrawersSM destructor for class CDrawersSM.
    * @param	CDrawersApplication& drawersApp
    * @return	NA.
    **/
    ~CDrawersSM();

    /**
    * @brief    CDrawersSM::enterDrawers enter function for Drawers State in
    *           StateMachine. This function is called when state machine enters
    *           in Drawers State.
    * @param	void.
    * @return	void.
    **/
    void enterDrawers() override;

    /**
    * @brief    CDrawersSM::exitDrawers exit function for Drawers State in
    *           StateMachine. This function is called when state machine exits
    *           from Drawers State.
    * @param	void.
    * @return	void.
    **/
    void exitDrawers() override;

    /**
    * @brief    CDrawersSM::enterDrawersHiddenState enter function for Drawers
    *           Hidden State in StateMachine. This function is called when state
    *           machine enters in Drawers Hidden State.
    * @param	sc_boolean bPlayAnimation: true if animation needs to play
    *           during hide of drawers, else false.
    * @return	void.
    **/
    void enterDrawersHiddenState(sc_boolean bPlayAnimation) override;

    /**
    * @brief    CDrawersSM::exitDrawersHiddenState: exit function for Drawers
    *           Hidden State in StateMachine. This function is called when state
    *           machine exits from Drawers Hidden State.
    * @param	void.
    * @return	void.
    **/
    void exitDrawersHiddenState() override;

    /**
    * @brief    CDrawersSM::enterDrawersVisibleState enter function for Drawers
    *           Visible State in StateMachine. This function is called when
    *           state machine enters in Drawers Visible State.
    * @param	sc_boolean bPlayAnimation: true if animation needs to play
    *           during show of drawers, else false.
    * @return	void.
    **/
    void enterDrawersVisibleState(sc_boolean bPlayAnimation) override;

    /**
    * @brief    CDrawersSM::exitDrawersVisibleState: exit function for Drawers
    *           Visible State in StateMachine. This function is called when
    *           state machine exits from Drawers Visible State.
    * @param	void.
    * @return	void.
    **/
    void exitDrawersVisibleState() override;

    /**
    * @brief    CDrawersSM::enterStatusBarState enter function for
    *           StatusBarState in StateMachine. This function is called when
    *           state machine enters in StatusBarState.
    * @param	void.
    * @return	void.
    **/
    void enterStatusBarState() override;

    /**
    * @brief    CDrawersSM::exitStatusBarState: exit function for
    *           exitStatusBarState in StateMachine. This function is called
    *           when state machine exits from exitStatusBarState.
    * @param	void.
    * @return	void.
    **/
    void exitStatusBarState() override;

    /**
    * @brief    CDrawersSM::enterShortcutDrawerMinimizedState enter function for
    *           ShortcutDrawerMinimizedState in StateMachine. This function is
    *           called when state machine enters in ShortcutDrawerMinimizedState.
    * @param	void.
    * @return	void.
    **/
    void enterShortcutDrawerMinimizedState() override;

    /**
    * @brief    CDrawersSM::exitShortcutDrawerMinimizedState: exit function for
    *           ShortcutDrawerMinimizedState in StateMachine. This function is
    *           called when state machine exits from
    *           ShortcutDrawerMinimizedState.
    * @param	void.
    * @return	void.
    **/
    void exitShortcutDrawerMinimizedState() override;

    /**
    * @brief    CDrawersSM::enterHvacDrawerMaximizedState enter function for
    *           HvacDrawerMaximized State in StateMachine. This function is
    *           called when state machine enters in HvacDrawerMaximized State.
    * @param	void.
    * @return	void.
    **/
    void enterHvacDrawerMaximizedState() override;

    /**
    * @brief    CDrawersSM::exitHvacDrawerMaximizedState exit function for
    *           HvacDrawerMaximized State in StateMachine. This function is
    *           called when state machine exits from HvacDrawerMaximized State.
    * @param	void.
    * @return	void.
    **/
    void exitHvacDrawerMaximizedState() override;

    /**
    * @brief    CDrawersSM::enterSourceDrawerMaximizedState enter function for
    *           SourceDrawerMaximized State in StateMachine. This function is
    *           called when state machine enters in SourceDrawerMaximized State.
    * @param	void.
    * @return	void.
    **/
    void enterSourceDrawerMaximizedState() override;

    /**
    * @brief    CDrawersSM::exitSourceDrawerMaximizedState exit function for
    *           SourceDrawerMaximized State in StateMachine. This function is
    *           called when state machine exits from SourceDrawerMaximized State.
    * @param	void.
    * @return	void.
    **/
    void exitSourceDrawerMaximizedState() override;

    /**
    * @brief    CDrawersSM::enterQadDrawerMaximizedState enter function for
    *           QadDrawerMaximized State in StateMachine. This function is
    *           called when state machine enters in QadDrawerMaximized State.
    * @param	void.
    * @return	void.
    **/
    void enterQadDrawerMaximizedState() override;

    /**
    * @brief    CDrawersSM::exitQadDrawerMaximizedState exit function for
    *           QadDrawerMaximized State in StateMachine. This function is
    *           called when state machine exits from QadDrawerMaximized State.
    * @param	void.
    * @return	void.
    **/
    void exitQadDrawerMaximizedState() override;

    /**
    * @brief    CDrawersSM::enterQadDrawerMinimizedState enter function for
    *           QadDrawerMinimized State in StateMachine. This function is
    *           called when state machine enters in QadDrawerMinimized State.
    * @param	void.
    * @return	void.
    **/
    void enterQadDrawerMinimizedState() override;

    /**
    * @brief    CDrawersSM::exitQadDrawerMinimizedState exit function for
    *           QadDrawerMinimized State in StateMachine. This function is
    *           called when state machine exits from QadDrawerMinimized State.
    * @param	void.
    * @return	void.
    **/
    void exitQadDrawerMinimizedState() override;

    /**
    * @brief    CDrawersSM::disableQadDrawer This function is called by state
    *           machine when QadDrawer needs to disable.
    * @param	void.
    * @return	void.
    **/
    void disableQadDrawer() override;

    /**
    * @brief    CDrawersSM::enableQadDrawer This function is called by state
    *           machine when QadDrawer needs to enable.
    * @param	void.
    * @return	void.
    **/
    void enableQadDrawer() override;

    /**
    * @brief    CDrawersSM::disableShortcutDrawer This function is called by
    *           state machine when ShortcutDrawer needs to disable.
    * @param	void.
    * @return	void.
    **/
    void disableShortcutDrawer() override;

    /**
    * @brief    CDrawersSM::enableShortcutDrawer This function is called by
    *           state machine when ShortcutDrawer needs to enable.
    * @param	void.
    * @return	void.
    **/
    void enableShortcutDrawer() override;

    /**
    * @brief    CDrawersSM::enableShortcutDrawerButtons: This function is called
    *           by state machine when any button of shortcut drawer needs to
    *           disable/enable.
    * @param    sc_integer iButtonID: Button ID to enable/disable
    * @param    sc_boolean bEnable: true if Enable else false.
    *
    * @return	void.
    **/
    void enableShortcutDrawerButtons(sc_integer iButtonID, sc_boolean bEnable) override;
	
    /**
     * @brief   enterVolOverlayShowState: entry function for state VolOverlayShowState.
     * @param   void.
     * @return  void.
     */
    void enterVolOverlayShowState() override;

    /**
     * @brief   exitVolOverlayShowState: exit function for state VolOverlayShowState.
     * @param   void.
     * @return  void.
     */
    void exitVolOverlayShowState() override;

    /**
     * @brief   enterVolOverlayHideState: entry function for state VolOverlayHideState.
     * @param   void.
     * @return  void.
     */
    void enterVolOverlayHideState() override;

    /**
     * @brief   exitVolOverlayHideState: exit function for state VolOverlayHideState.
     * @param   void.
     * @return  void.
     */
    void exitVolOverlayHideState() override;

    /**
     * @brief   enterHvacOverlayShowState: entry function for state HvacOverlayShowState.
     * @param   void.
     * @return  void.
     */
    void enterHvacOverlayShowState() override;

    /**
     * @brief   exitHvacOverlayShowState: exit function for state HvacOverlayShowState.
     * @param   void.
     * @return  void.
     */
    void exitHvacOverlayShowState() override;

    /**
     * @brief   enterHvacOverlayHideState: entry function for state HvacOverlayHideState.
     * @param   void.
     * @return  void.
     */
    void enterHvacOverlayHideState() override;

    /**
     * @brief   exitHvacOverlayHideState: exit function for state HvacOverlayHideState.
     * @param   void.
     * @return  void.
     */
    void exitHvacOverlayHideState() override;

private:
    // Parent class pointer
    CDrawersApplication &m_objDrawersApp;
};

#endif // CDRAWERSSM_H
