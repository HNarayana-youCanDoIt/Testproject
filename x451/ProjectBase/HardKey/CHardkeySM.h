/*****************************************************************
* Project        TATA X451
* (c) copyright  2018
* Company        Harman International India
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CHardKeySM.h
* @ingroup      HMIComponent
* @author       Guru Alingal
* CHardKeySM class implements TML_HMI_SM::SCI_HardKey_OCB. This class is used to handle hardkey operations.
* This class is responsible for passing on hard key events to respective modules.
*/
#ifndef CHARDKEYSM_H
#define CHARDKEYSM_H

#include <QObject>
#include "CFramework.h"
#include "CHardKeyEnum.h"
#include "StateMachine_TML_HMI_SM.h"
#include "CFunctor.h"


/**
 * @class CHardkeySM
 * @brief * CHardKeySM class used to handle hardkey operations.
 * This class is responsible for passing on hard key events to respective modules.
 */

class CHardkeySM: public QObject, public TML_HMI_SM::SCI_HardKey_OCB
{
    Q_OBJECT

    //Define QProperties here

public:
     CHardkeySM();
     ~CHardkeySM();

    // SCI_HardKey_OCB interface
     /**
     * @brief handleHomeHK To handle home hard key events and switch to home screen.
     * @param void
     * @return void
     */
    void handleHomeHK();

    /**
    * @brief handleFavHK To handle favourite hard key and process as per favourite configuration.
    * @param void
    * @return void
    */
    void handleFavHK();

    /**
    * @brief handleNextHK To handle next hard key and pass the control to respective modules.
    * @param void
    * @return void
    */
    void handleNextHK();

    /**
    * @brief handlePrevHK To handle prev hard key and pass the control to respective modules.
    * @param void
    * @return void
    */
    void handlePrevHK();

    /**
    * @brief handlePhoneHK To handle phone hard key.
    * @param void
    * @return void
    */
    void handlePhoneHK();

    /**
    * @brief handleBackHK To handle back hard key.
    * @param void
    * @return void
    */
    void handleBackHK();

     /**
     * @brief handleEnggMenuHK Process engg menu hard keys.
     * @param void
     * @return void
     */
    void handleEnggMenuHK();

    /**
     * @brief handleSwUpdate Process software update hard key. Switch to software update state.
     * @param void
     * @return void
     */
    void handleSwUpdateHK();

    /**
     * @brief handleVolRotaryHK: Process volume rotary hard key.
     * @param void
     * @return void
     */
    void handleVolRotaryHK();

    /**
     * @brief handleUpSWCK process up swc key.
     * @param void
     * @return void
     */
    void handleUpSWCK();

    /**
     * @brief handleDownSWCK process down swc key.
     * @param void
     * @return void
     */
    void handleDownSWCK();

    /**
     * @brief handleRejectMuteSWCK process Reject/Mute swc key.
     * @param void
     * @return void
     */
    void handleRejectMuteSWCK();

    /**
     * @brief handleAcceptVRSWCK process accept/VR swc key.
     * @param void
     * @return void
     */
    void handleAcceptVRSWCK();

    /**
     * @brief handleSrcSWCK process source swc key.
     * @param void
     * @return void
     */
    void handleSourceSWCK();

    /**
     * @brief handleHardkeys - Operation to handle any hard key state updates.
     *        This operation shall be triggered from the states which has hardkey actions defined.
     *        sigHardKeyStateUpdated will be emitted from this method.
     * @param iKeyCode
     * @param iKeyState
     */
    void handleHardkeys(int iKeyCode, int iKeyState) override;

    /**
     * @brief initKeyHandlerMap This will method will inintailize the map with key handlers.
     * @param void
     * @return void
     */
    void initKeyHandlerMap();

signals:

    /**
     * @brief hardKeyStateUpdated - Signal to indicate a hard key event.
     * @param iKeyCode
     * @param iKeyState
     * @return void
     */
    void sigHardKeyStateUpdated(int iKeyCode, int iKeyState);

public slots:

    /**
     * @brief onHardKeyStateUpdated Slot to handle hardKeyStateUpdated signal
     * @param iKeyCode
     * @param iKeyState
     * @return void
     */
    void sltOnHardKeyStateUpdated(int iKeyCode, int iKeyState);

private:

    /**
     * @brief   handleHardKeysInProjection: This function is a private function
     *          which is called for the hardKey, which needs to report to
     *          projection (AndroidAuto/AppleCarPlay) services. This function calls
     *          the corrosponding Adaptor's handleHardKey() function, for handling
     *          hardKeys, like: When AndroidAuto projection is active, then it
     *          calls AndroidAutoAdaptor's handleHardKeys() function.
     * @param   eHardKey: HardKey which needs to handle.
     * @param   eHardKeyState: HardKey's state
     * @return  true if hardkey reported to corresponding adapter is processed
     *          else false.
     */
    bool handleHardKeysInProjection(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState);

    /**
     * @brief   handleHardKeysInRadio: This function is a private function
     *          which is called for the hardKey, which needs to report to
     *          Radio adaptor to stop ongoing seek.
     * @param   eHardKey: HardKey which needs to handle.
     * @param   eHardKeyState: HardKey's state
     * @return  bool
     */
    bool handleHardKeysInRadio(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState);

    /**
     * @brief   handleHardKeysInParkAssist: This function is a private function
     *          which is called for the hardKey, which needs to report to
     *          ParkAssist adaptor to deactivate park assist.
     * @param   eHardKey: HardKey which needs to handle.
     * @param   eHardKeyState: HardKey's state
     * @return  bool
     */
    bool handleHardKeysInParkAssist(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState);

    /**
     * @brief m_mapHardKeyHandler Map to store the event handlers for each hard key.
     */
    QMap<CHardKeyEnum::EHardKeys, CFunctor<CHardkeySM>> m_mapHardKeyHandler;

    /**
     * @brief m_eKeyState variable to store key state of hard key.
     */
    CHardKeyEnum::EHardKeyState  m_eKeyState;

    /**
     * @brief m_eKeyCode variable to store key code of hard key.
     */
    CHardKeyEnum::EHardKeys  m_eKeyCode;


};

#endif // CHARDKEYSM_H
