import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.popupenums 1.0
import QtGraphicalEffects 1.0
import "../../Common"


/*
  Template for Popup with TEXT and THREE BUTTON
*/
BasePopup {


    // Property for text to be set in the popup
    property alias prPopupTitle: idPopupTitle.text
    // Property for text to be set in the popup
    property alias prPopupTextOne: idPopupTextOne.text
    // Property for text to be set in the popup
    property alias prPopupTextTwo: idPopupTextTwo.text
    // Property for text to be set in the button
    property alias prFirstBtnText: idFirstBtn.text
    // Property for text to be set in the button
    property alias prSecondBtnText: idSecondBtn.text
    // Property for text to be set in the button
    property alias prThirdBtnText: idThirdBtn.text
    // Property for button enabled
    property alias prFirstBtnEnable: idFirstBtn.enabled
    // Property for button enabled
    property alias prSecondBtnEnable: idSecondBtn.enabled
    // Property for button enabled
    property alias prThirdBtnEnable: idThirdBtn.enabled

    // Property holds the current RRE index for the popup
    property int prCurrentRREIndex: -1

    // Signal to be emitted on btn release for btn id idFirstBtn
    signal firstBtnReleased

    // Signal to be emitted on btn release for btn id idSecondBtn
    signal secondBtnReleased

    // Signal to be emitted on btn release for btn id idThirdBtn
    signal thirdBtnReleased

    // This property holds the height of content item
    contentHeight: 314

    // This property holds the width of content item
    contentWidth: 637

    // Padding is used to set the co-orinates of Content Item
    topPadding: 83
    leftPadding: 81

    contentItem: Item {
        id: idPopupContent

        /**
         * Mouse area to prevent Popup to close when Content Item of the Popup is Touched
         */
        MouseArea{
            anchors.fill: parent
            onPressed: {
                cppUIBase.qmlLog("ThreeButtonTwoTextPopup.qml: Popup Content Item Touched")
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
            source: (prPopupTitle === "") ? "qrc:/image/Popup/PopupBg/PopUp_Backgr_three_btn/Gen_Gfx_ThreeBtn_NoTitle_PopupBgColourPatch_n.png"
                                          : "qrc:/image/Popup/PopupBg/PopUp_Backgr_three_btn/Gen_Gfx_ThreeBtn_Title_PopupBgColourPatch_n.png"
            ColorOverlay {
                id: idPopupBgColorOverlay
                anchors.fill: parent
                source: parent
                color:  cppThemeMgr.currentThemeColor
            }
        }

        Image {
            id: idPopupBgOverlay
            source: (prPopupTitle === "") ? "qrc:/image/Popup/PopupBg/PopUp_Backgr_three_btn/Gen_Gfx_ThreeBtn_NoTitle_PopupBgOverlay_n.png"
                                          : "qrc:/image/Popup/PopupBg/PopUp_Backgr_three_btn/Gen_Gfx_ThreeBtn_Title_PopupBgOverlay_n.png"
        }

        /**
          * HBText to hold title to be displayed on popup
          **/
        HBText {
            id: idPopupTitle
            width: 501
            height: 25

            anchors {
                top: parent.top
                left: parent.left
                topMargin: 41
                leftMargin: 62
            }
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            fontType: ThemeMgr.FONTTYPE_T35_BK_C2
        }

        /**
          * HBText to hold text to be displayed on popup
          **/
        HBText {
            id: idPopupTextOne
            width: 566
            height: 18

            anchors {
                top: parent.top
                left: parent.left
                topMargin: 123
                leftMargin: 35
            }

            horizontalAlignment: Text.AlignHCenter
            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        }

        /**
          * HBText to hold text to be displayed on popup
          **/
        HBText {
            id: idPopupTextTwo
            width: 566
            height: 18

            anchors {
                top: parent.top
                left: parent.left
                topMargin: 168
                leftMargin: 35
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

            textFontType: enabled ? ThemeMgr.FONTTYPE_T35_C3 : ThemeMgr.FONTTYPE_T35_C3_DISABLED
            width: 170
            height: 50
            anchors {
                top: parent.top
                left: parent.left
                topMargin: (prPopupTitle === "") ? 222 : 236
                leftMargin: 33
            }

            defaultImageURL: (0 === prCurrentRREIndex) ? "qrc:/Assets/RREFocus/Popup_Button_Focus.png" : ""
            pressedImageURL: "qrc:/Assets/RREFocus/Popup_Button_Focus.png"

            onPressed: {
                cppUIBase.qmlLog("ThreeButtonTwoTextPopup.qml, idFirstBtn: onPressed event received")
                // Deactivate VR session
                cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
                // Deactivate phone bt vr
                cppPhoneAdaptor.invReqPhoneBtVrDeactivation()
                prCurrentRREIndex = 0
            }

            onReleased: {
                PopupManager.ePopupResult = PopupEnum.EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS
                firstBtnReleased()
            }
        }

        /**
          * Second GenericButton for popup
          **/
        GenericButton {
            id: idSecondBtn

            textFontType: enabled ? ThemeMgr.FONTTYPE_T35_C3 : ThemeMgr.FONTTYPE_T35_C3_DISABLED
            width: 181
            height: 50
            anchors {
                top: parent.top
                left: parent.left
                topMargin: (prPopupTitle === "") ? 222 : 236
                leftMargin: 228
            }

            defaultImageURL: (1 === prCurrentRREIndex) ? "qrc:/Assets/RREFocus/Popup_Button_Focus.png" : ""
            pressedImageURL: "qrc:/Assets/RREFocus/Popup_Button_Focus.png"

            onPressed: {
                cppUIBase.qmlLog("ThreeButtonTwoTextPopup.qml, idSecondBtn: onPressed event received")
                // Deactivate VR session
                cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
                // Deactivate phone bt vr
                cppPhoneAdaptor.invReqPhoneBtVrDeactivation()
                prCurrentRREIndex = 1
            }

            onReleased: {
                PopupManager.ePopupResult = PopupEnum.EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS
                secondBtnReleased()
            }
        }

        /**
          * Third GenericButton for popup
          **/
        GenericButton {
            id: idThirdBtn

            width: 169
            height: 50
            anchors {
                top: parent.top
                left: parent.left
                topMargin: (prPopupTitle === "") ? 222 : 236
                leftMargin: 432
            }

            textFontType: enabled ? ThemeMgr.FONTTYPE_T35_C3 : ThemeMgr.FONTTYPE_T35_C3_DISABLED

            defaultImageURL: (2 === prCurrentRREIndex) ? "qrc:/Assets/RREFocus/Popup_Button_Focus.png" : ""
            pressedImageURL: "qrc:/Assets/RREFocus/Popup_Button_Focus.png"

            onPressed: {
                cppUIBase.qmlLog("ThreeButtonTwoTextPopup.qml, idThirdBtn: onPressed event received")
                // Deactivate VR session
                cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
                // Deactivate phone bt vr
                cppPhoneAdaptor.invReqPhoneBtVrDeactivation()
                prCurrentRREIndex = 2
            }

            onReleased: {
                PopupManager.ePopupResult = PopupEnum.EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS
                thirdBtnReleased()
            }
        }

        Connections{
            target: PopupManager
            onSigRotaryUpdatePopup:{
                cppUIBase.qmlLog("ThreeButtonTwoTextPopup.qml: sigRotaryUpdate: iKeyState: "
                                 + iKeyState + " iKeyCode : " + iKey)

                PopupManager.invResetPopupTimer()

                if(HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState){
                    if(-1 === prCurrentRREIndex){
                        prCurrentRREIndex = 2
                    }
                    else if(prCurrentRREIndex > 0){
                        prCurrentRREIndex--
                    }
                    else{
                        // Do nothing
                    }
                }
                else if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState){
                    if(-1 === prCurrentRREIndex){
                        prCurrentRREIndex = 0
                    }
                    else if(prCurrentRREIndex < 2){
                        prCurrentRREIndex++
                    }
                    else{
                        // Do nothing
                    }
                }
            }

            onSigRotaryPressedPopup:{
                cppUIBase.qmlLog("ThreeButtonTwoTextPopup.qml: onRotaryPressed: " + iKeyState)


                if(HardkeyEnum.HKEY_STATE_RELEASED === iKeyState ||
                   HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState){
                    if(0 === prCurrentRREIndex && idFirstBtn.enabled){
                        // Deactivate VR session
                        cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
                        // Deactivate phone bt vr
                        cppPhoneAdaptor.invReqPhoneBtVrDeactivation()
                        PopupManager.ePopupResult = PopupEnum.EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS
                        firstBtnReleased()
                    }
                    else if(1 === prCurrentRREIndex && idSecondBtn.enabled){
                        // Deactivate VR session
                        cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
                        // Deactivate phone bt vr
                        cppPhoneAdaptor.invReqPhoneBtVrDeactivation()
                        PopupManager.ePopupResult = PopupEnum.EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS
                        secondBtnReleased()
                    }
                    else if(2 === prCurrentRREIndex && idThirdBtn.enabled){
                        // Deactivate VR session
                        cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
                        // Deactivate phone bt vr
                        cppPhoneAdaptor.invReqPhoneBtVrDeactivation()
                        PopupManager.ePopupResult = PopupEnum.EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS
                        thirdBtnReleased()
                    }
                    else{
                        // do nothing
                    }
                }
            }
        }
    }
}
