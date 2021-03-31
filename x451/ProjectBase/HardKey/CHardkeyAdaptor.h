/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CHardkeyAdaptor.h
* @ingroup      HMIComponent
* @author       Prashantkumar Raut
* CHardkeyAdaptor Adaptor class for Hardkey - It is a singleton class used to communicate with qml and SM on HardKey events.
*/
#ifndef CHARDKEYADAPTOR_H
#define CHARDKEYADAPTOR_H

#include <QObject>
#include <QString>
#include "CFramework.h"
#include "interfaces/IHardkeyResource.h"
#include "CHardkeySM.h"
#include "CHardKeyEnum.h"

/**
 * @class CHardkeyAdaptor
 * @brief Adaptor class for Hardkey - It is a singleton class used to communicate with qml and SM on HardKey events.
 */
class CHardkeyAdaptor : public QObject
{
    Q_OBJECT

    //Define QProperties here

public:
    ~CHardkeyAdaptor();
    /**
     * @brief To get Instance of CHardkeyAdaptor
     * @param void
     * @return CHardkeyAdaptor*
     */
    static CHardkeyAdaptor* getInstance();

    /**
     * @brief Method to process triggerred hardkey
     * @param HardKeys - key code, KeyState - key state
     * @return void
     */
    void processHardKey(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState);

    /**
     * @brief   passHardkeyToOverlay - Method to be invoked to pass hardkey event to the overlay.
     * @param   eKeyCode - key code of the hard key
     * @param   eKeyState - state of the hard key
     * @return  return true if processed else false.
     */
    bool passHardkeyToOverlay(CHardKeyEnum::EHardKeys eKeyCode, CHardKeyEnum::EHardKeyState eKeyState);

    /**
     * @brief passRREToScreens - To Pass the Right rotary control to qml screens.
     * @param eKeyCode - key code of the hard key
     * @param eKeyState - state of the hard key
     * @return return trus if processed else false.
     */
    bool passRREToScreens(CHardKeyEnum::EHardKeys eKeyCode, CHardKeyEnum::EHardKeyState eKeyState);

    /**
     * @brief IsSWUpdateActive - To Pass the boolean value if SW update state is active
     * @param void
     * @return return true if SW update state is active, else false.
     */
    bool IsSWUpdateActive() { return m_bIsSWUpdateActive; }

    /**
     * @brief setSWUpdateActiveState - To set the boolean value if SW update state is active
     * @param bIsSWUpdateActive - true if the state is active, else false
     * @return void
     */
    void setSWUpdateActiveState(bool bIsSWUpdateActive) { m_bIsSWUpdateActive = bIsSWUpdateActive; }

    /**
     * @brief   invSetHKHandledByOverlayStatus: Method to set the status of HK handling by the overlay.
     *          This method shall be invoked by the overlay to indicate whether it has handled the HK completely
     *          or partial handling is done by the overlay and partial handling should be done by the popup/screen.
     * @param   bHKHandledStatus: TRUE if HK is completely handled by the overlay, FALSE if the partial handling
     *          is done by the overlay and popup/screen needs to do partial handling.
     * @return  void.
     */
    Q_INVOKABLE void invSetHKHandledByOverlayStatus(bool bHKHandledStatus) { m_bHardKeyHandledByOverlay = bHKHandledStatus; }

    /**
     * @brief   invsendKeyCodeEvent: Method to send a key code event to resource layer.
     * @param   hard key code
     * @param   hard key state
     * @return  void.
     */
    Q_INVOKABLE void invSendKeyCodeEvent(CHardKeyEnum::EHardKeys _eKeyCode, CHardKeyEnum::EHardKeyState _eKeyState);

    /**
     * @brief   invSendSliderStateEvent: Method to send a slider state event to resource layer.
     * @param   hard key code
     * @param   hard key state
     * @param   slider steps
     * @return  void.
     */
    Q_INVOKABLE void invSendSliderStateEvent(CHardKeyEnum::EHardKeys _eKeyCode, CHardKeyEnum::EHardKeyState _eKeyState, int _iSteps);

    /**
     * @brief   getKeyCodeForPlugin: Method to send a key code to Plugin key code.
     * @param   hard key code
     * @return  int Plugin key code.
     */
    int getKeyCodeForPlugin(CHardKeyEnum::EHardKeys _eKeyCode);

    /**
     * @brief   getKeyStateForPlugin: Method to convert a key state to Plugin key state.
     * @param   hard key state
     * @return  int Plugin key state.
     */
    int getKeyStateForPlugin(CHardKeyEnum::EHardKeyState _eKeyState);
signals:
    /**
     * @brief sigRotaryUpdate - This signal will emit the keycode and key state
     * @param iKeyCode - key code of the hard key
     * @param iKeyState - state of the hard key
     */
    void sigRotaryUpdate(int iKeyCode, int iKeyState);

    /**
     * @brief sigRotaryPressed - This signal will emit the keycode and key state
     * @param iKeyCode - key code of the hard key
     * @param iKeyState - state of the hard key
     */
    void sigRotaryPressed(int iKeyCode, int iKeyState);

    /**
     * @brief   sigPassHardkeyToOverlay - This signal shall emit to notify overlay regarding hardkey event.
     * @param   iKeyCode - key code of the hard key
     * @param   iKeyState - state of the hard key
     * @return  void.
     */
    void sigPassHardkeyToOverlay(int iKeyCode, int iKeyState);

public slots:

private:

    explicit CHardkeyAdaptor(QObject *pParent = nullptr);
    /**
     * Instance of class CHardkeyAdaptor
     */
    static CHardkeyAdaptor* m_pHardkeyAdaptor;

    /**
     * This will hold the current used hard key.
     */
    CHardKeyEnum::EHardKeys m_eCurrentHardkey;

    //FixMe: Need to remove this hot fix after HK service resolves its issue
    /**
     * This will hold true if current SM state is SW update
     */
    bool m_bIsSWUpdateActive;

    /**
     * @brief m_hardKeySM state machine object.
     */
    CHardkeySM m_hardKeySM;

    //! Flag to decide whether the HK is handled completely by the overlay or not.
    bool    m_bHardKeyHandledByOverlay;
};

#endif // CHARDKEYADAPTOR
