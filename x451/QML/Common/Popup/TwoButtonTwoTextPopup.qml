import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.popupenums 1.0
import com.harman.qml.hardkeyenum 1.0
import QtGraphicalEffects 1.0
import "../../Common"


/*
  Template for Popup with TITLE, TEXT and TWO BUTTONS
*/
BasePopup {

    // Property for title to be set in the popup
    property alias prPopupTitle: idPopupTitle.text

    // Property for text to be set in the popup
    property alias prPopupTextOne: idPopupTextOne.text

    // Property for text to be set in the popup
    property alias prPopupTextTwo: idPopupTextTwo.text

    // Property for text to be set in the first button
    property alias prFirstBtnText: idFirstBtn.text

    // Property for text to be set in the second button
    property alias prSecondBtnText: idSecondBtn.text

    // Property for button enabled
    property alias prFirstBtnEnable: idFirstBtn.enabled

    // Property for button enabled
    property alias prSecondBtnEnable: idSecondBtn.enabled

    // Property holds the current RRE index for the popup
    property int prCurrentRREIndex: -1

    // Signal to be emitted on btn release for btn id idFirstBtn
    signal sigFirstBtnReleased()

    // Signal to be emitted on btn release for btn id idSecondBtn
    signal sigSecondBtnReleased()

    // This property holds the height of content item
    contentHeight: 291

    // This property holds the width of content item
    contentWidth: 546

    // Padding is used to set the co-orinates of Content Item
    topPadding: 94
    leftPadding: 127

    contentItem: Item {
        id: idPopupContent

        /**
         * Mouse area to prevent Popup to close when Content Item of the Popup is Touched
         */
        MouseArea{
            anchors.fill: parent
            onPressed: {
                cppUIBase.qmlLog("TwoButtonTwoTextPopup.qml: Popup Content Item Touched")
                // Deactivate VR session
                cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
                // Deactivate phone bt vr
                cppPhoneAdaptor.invReqPhoneBtVrDeactivation()
            }
        }


        /**
          * popup background
          **/
        Image {
            id: idPopupBg
            source: (prPopupTitle === "") ? "qrc:/image/Popup/PopupBg/PopUp_Backgr_Two_btn/Gen_Gfx_TwoBtn_NoTitle_PopupBgColourPatch_n.png"
                                          : "qrc:/image/Popup/PopupBg/PopUp_Backgr_Two_btn/Gen_Gfx_TwoBtn_Title_PopupBgColourPatch_n.png"
            ColorOverlay {
                id: idPopupBgColorOverlay
                anchors.fill: parent
                source: parent
                color:  cppThemeMgr.currentThemeColor
            }
        }

        Image {
            id: idPopupBgOverlay
            source: (prPopupTitle === "") ? "qrc:/image/Popup/PopupBg/PopUp_Backgr_Two_btn/Gen_Gfx_TwoBtn_NoTitle_PopupBgOverlay_n.pngg"
                                          : "qrc:/image/Popup/PopupBg/PopUp_Backgr_Two_btn/Gen_Gfx_TwoBtn_Title_PopupBgOverlay_n.png"
        }

        /**
          * HBText to hold title to be displayed on popup
          **/
        HBText {
            id: idPopupTitle
            width: 422
            height: 25
            anchors {
                top: parent.top
                topMargin: 31
                left: parent.left
                leftMargin: 56
            }
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            fontType: ThemeMgr.FONTTYPE_T35_BK_C2
        }

        /**
          * HBText to hold Main text to be displayed on popup
          **/
        HBText {
            id: idPopupTextOne
            width: 428
            height: 18

            anchors {
                top: parent.top
                left: parent.left
                topMargin: 112
                leftMargin: 37
            }

            horizontalAlignment: Text.AlignHCenter
            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        }

        /**
          * HBText to hold Main text to be displayed on popup
          **/
        HBText {
            id: idPopupTextTwo
            width: 428
            height: 18

            anchors {
                top: parent.top
                left: parent.left
                topMargin: 157
                leftMargin: 37
            }
            wrapMode: Text.WordWrap

            horizontalAlignment: Text.AlignHCenter
            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        }

        /**
          * First GenericButton for popup
          **/
        GenericButton {
            id: idFirstBtn

            width: 169
            height: 50
            anchors {
                top: parent.top
                left: parent.left
                topMargin: (prPopupTitle === "") ? 211 : 225
                leftMargin: 93
            }

            defaultImageURL: (0 === prCurrentRREIndex) ? "qrc:/Assets/RREFocus/Popup_Button_Focus.png" : ""
            pressedImageURL: "qrc:/Assets/RREFocus/Popup_Button_Focus.png"

            textFontType: enabled ? ThemeMgr.FONTTYPE_T35_C3 : ThemeMgr.FONTTYPE_T35_C3_DISABLED

            onPressed: {
                cppUIBase.qmlLog("TwoButtonTwoTextPopup.qml, idFirstBtn: onPressed event received")
                // Deactivate VR session
                cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
                // Deactivate phone bt vr
                cppPhoneAdaptor.invReqPhoneBtVrDeactivation()
                prCurrentRREIndex = 0
            }

            onReleased: {
                PopupManager.ePopupResult = PopupEnum.EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS
                sigFirstBtnReleased()
            }
        }

        /**
          * Second GenericButton for popup
          **/
        GenericButton {
            id: idSecondBtn

            width: 169
            height: 50
            anchors {
                top: parent.top
                left: parent.left
                topMargin: (prPopupTitle === "") ? 211 : 225
                leftMargin: 285
            }

            defaultImageURL: (1 === prCurrentRREIndex) ? "qrc:/Assets/RREFocus/Popup_Button_Focus.png" : ""
            pressedImageURL: "qrc:/Assets/RREFocus/Popup_Button_Focus.png"

           textFontType: enabled ? ThemeMgr.FONTTYPE_T35_C3 : ThemeMgr.FONTTYPE_T35_C3_DISABLED

           onPressed: {
               cppUIBase.qmlLog("TwoButtonTwoTextPopup.qml, idSecondBtn: onPressed event received")
               // Deactivate VR session
               cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
               // Deactivate phone bt vr
               cppPhoneAdaptor.invReqPhoneBtVrDeactivation()
               prCurrentRREIndex = 1
           }

            onReleased: {
                PopupManager.ePopupResult = PopupEnum.EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS
                sigSecondBtnReleased()
            }
        }

        Connections{
            target: PopupManager
            onSigRotaryUpdatePopup:{
                cppUIBase.qmlLog("TwoButtonTwoTextPopup.qml: sigRotaryUpdate: iKeyState: "
                                 + iKeyState + " iKeyCode : " + iKey)

                PopupManager.invResetPopupTimer()

                if(HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState){
                    if(-1 === prCurrentRREIndex){
                        prCurrentRREIndex = 1
                    }
                    else if(1 === prCurrentRREIndex){
                        prCurrentRREIndex = 0
                    }
                    else{
                        // Do nothing
                    }
                }
                else if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState){
                    if(-1 === prCurrentRREIndex){
                        prCurrentRREIndex = 0
                    }
                    else if(0 === prCurrentRREIndex){
                        prCurrentRREIndex = 1
                    }
                    else{
                        // Do nothing
                    }
                }
            }

            onSigRotaryPressedPopup:{
                cppUIBase.qmlLog("TwoButtonTwoTextPopup.qml: onRotaryPressed: "+iKeyState)


                if(HardkeyEnum.HKEY_STATE_RELEASED === iKeyState ||
                   HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState){
                    if(0 === prCurrentRREIndex && idFirstBtn.enabled){
                        // Deactivate VR session
                        cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
                        // Deactivate phone bt vr
                        cppPhoneAdaptor.invReqPhoneBtVrDeactivation()
                        PopupManager.ePopupResult = PopupEnum.EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS
                        sigFirstBtnReleased()
                    }
                    else if(1 === prCurrentRREIndex && idSecondBtn.enabled){
                        // Deactivate VR session
                        cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
                        // Deactivate phone bt vr
                        cppPhoneAdaptor.invReqPhoneBtVrDeactivation()
                        PopupManager.ePopupResult = PopupEnum.EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS
                        sigSecondBtnReleased()
                    }
                }
            }
        }
    }
}
