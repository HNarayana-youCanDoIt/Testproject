import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common"
import com.harman.qml.popupenums 1.0
import com.harman.qml.hardkeyenum 1.0

// TODO : Roatry and hardkey press handling for popup will be handled here Explained Below.
/**
 * We can change the button release/longrelease and RRE release/longrelease handling

 * We can create a generic signal in basePopup which shall have int as a param , something like buttonReleased(integer iIndex)
 * This shall be emited whenever button is release/longreleased via touch or via RRE
 * Create a slot in the popup which is currently shown. Write a switch case based upon the index received and handle it as per need
 * Kindly check where ever applicable
*/

/*
  Base Container for all the popups
*/
Popup {
    id: idBasePopup

    //Property holds whether the popup display animation is complited or not
    property bool prIsPopupAnimCompleted: false

    //Property holds the duration for Popup enter and exit Animation
    property int prShowAnimationDuration: 200

    //Property holds the duration for Popup enter and exit Animation
    property int prCloseAnimationDuration: (PopupManager.ePopupResult === PopupEnum.EN_POPUP_RESULT_CLOSED_ON_CONTEXT_CHANGE
                                            || PopupManager.ePopupResult === PopupEnum.EN_POPUP_RESULT_CLOSED_ON_CLOSE_ALL_POPUPS
                                            || PopupManager.ePopupResult === PopupEnum.EN_POPUP_RESULT_CLOSED_ON_FORCE_CLOSE_REQUEST)
                                            ? 0 : 100

    //Property holds the background source URL of Popup
    property alias prPopupBackground: idPopupBackground.source

    //Property to hold whether animation is required or not
    property bool prIsAnimationRequired: true

    //Signal to be emitted when popup closing animation completes and popup closed
    signal sigPopupClosed()

    width: 800
    height: 480

    /**
     * Modal popups often have a distinctive background dimming effect defined in overlay.modal,
     * and do not allow press or release events through to items beneath them.
     */
    modal: true

     //This property holds the width of content item
    contentWidth: 643
    // This property holds the height of content item
    contentHeight: 275
    // Padding is used to set the coorinates of Content Item
    topPadding: 83
    leftPadding: 81
    rightPadding : leftPadding
    bottomPadding : topPadding


    // This property holds the background item
    background: Item {
        id: idBackGroundItem

        clip: true

        Image {
            id: idPopupBackground
            source: "qrc:/image/Popup/PopupBg/Gen_Gfx_PopupOverlayBg_n.png"
        }

        /**
         * Mouse area to that calls closeOnTouch Method on a touch event over the background of the popup
         */
        MouseArea{
            anchors.fill: parent
            onPressed: {
                cppUIBase.qmlLog("BasePopup.qml : Popup Backround Touched")
                if(prIsPopupAnimCompleted){
                    PopupManager.closeOnTouch()
                    // Deactivate VR session
                    cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
                    // Deactivate phone bt vr
                    cppPhoneAdaptor.invReqPhoneBtVrDeactivation()
                }
            }
        }
    }
    contentItem: {
        //To be filled in Popup Templates
    }

    //This property holds the transition that is applied to the popup item when the popup is opened and enters the screen.
    enter: Transition {
        NumberAnimation {
            property: "opacity"
            from: (prIsAnimationRequired) ? 0 : 1
            to: 1
            duration: prShowAnimationDuration
        }

        ScaleAnimator {
            target: contentItem;
            from: (prIsAnimationRequired) ? 0 : 1
            to: 1
            duration: prShowAnimationDuration
            easing.type: Easing.OutBack
        }

        onRunningChanged: {
            if (!running){
                cppDrawersApp.qmlLog("base popup enter onRunningChanged end")
                prIsPopupAnimCompleted = true
            }
            else{
                cppDrawersApp.qmlLog("base popup enter onRunningChanged start")
                prIsPopupAnimCompleted = false
            }
        }
    }

    // This property holds the transition that is applied to the popup item when the popup is closed and exits the screen.
    exit: Transition {
        NumberAnimation {
            property: "opacity"
            from: 1
            to: (prIsAnimationRequired) ? .3 : 1
            duration: prCloseAnimationDuration
        }

        ScaleAnimator {
            target: contentItem;
            from: 1
            to: (prIsAnimationRequired) ? .3 : 1
            duration: prCloseAnimationDuration
            easing.type: Easing.Linear
        }

        onRunningChanged: {
            if (!running){
                cppDrawersApp.qmlLog("base popup exit onRunningChanged end")
                sigPopupClosed()
            }
            else{
                cppDrawersApp.qmlLog("base popup exit onRunningChanged start")
            }
        }
    }

//    onOpened: {
//        cppDrawersApp.qmlLog("base popup onOpened")
//    }

//    onClosed: {
//        cppDrawersApp.qmlLog("base popup onClosed")
//    }

//    Component.onCompleted: {
//        cppDrawersApp.qmlLog("base popup Component completed")
//    }

    //This property determines the circumstances under which the popup closes.
    //NoAutoClose : Indicates that the popup will only close when manually instructed to do so.
    closePolicy: Popup.NoAutoClose

}
