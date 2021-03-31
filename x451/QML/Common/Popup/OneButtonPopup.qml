import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0
import QtGraphicalEffects 1.0
import com.harman.qml.popupenums 1.0
import "../../Common"


/*
  Template for Popup with TEXT and ONE BUTTON
*/
BasePopup {

    // Property for text to be set in the popup title
    property alias prPopupTitle: idPopupTitle.text

    // Property for text to be set in the popup
    property alias prPopupText: idPopupText.text

    // Property for text to be set in the button
    property alias prBtnText: idOkBtn.text

    // Property for button to be enabled
    property alias prBtnEnable: idOkBtn.enabled

    // Property for button to be visible
    property alias prBtnVisible: idOkBtn.visible

    // Property holds the current RRE index for the popup
    property int prCurrentRREIndex: -1

    // Signal to be emitted onRelease of Button-idOkBtn
    signal btnReleased

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
        MouseArea {
            anchors.fill: parent
            onPressed: {
                cppUIBase.qmlLog(
                            "OneButtonPopup.qml: Popup Content Item Touched")
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
            source: "qrc:/image/Popup/PopupBg/PopUp_Backgr_one_btn/Gen_Gfx_OneBtn_PopupBgColourPatch_n.png"
            ColorOverlay {
                id: idPopupBgColorOverlay
                anchors.fill: parent
                source: parent
                color:  cppThemeMgr.currentThemeColor
            }
        }

        /**
          * popup background
          **/
        Image {
            id: idPopupBgOverlay
            source: "qrc:/image/Popup/PopupBg/PopUp_Backgr_one_btn/Gen_Gfx_OneBtn__PopupBgOverlay_n.png"
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
                left: parent.left
                topMargin: 30
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
            id: idPopupText
            width: 471
            height: 18

            anchors {
                top: parent.top
                left: parent.left
                topMargin: 132
                leftMargin: 37
            }
            wrapMode: Text.WordWrap
            elide: Text.ElideNone

            horizontalAlignment: Text.AlignHCenter
            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        }

        /**
          * GenericButton for user action on popup
          **/
        GenericButton {
            id: idOkBtn


            width: 205
            height: 50
            anchors {
                top: parent.top
                topMargin: 222
                horizontalCenter: parent.horizontalCenter
            }

            defaultImageURL: (0 === prCurrentRREIndex) ? "qrc:/Assets/RREFocus/Popup_Button_Focus.png" : ""
            pressedImageURL: "qrc:/Assets/RREFocus/Popup_Button_Focus.png"


            textFontType: enabled? ThemeMgr.FONTTYPE_T35_C3: ThemeMgr.FONTTYPE_T35_C3_DISABLED

            onPressed: {
                cppUIBase.qmlLog("OneButtonPopup.qml, idOkBtn: onPressed event received")
                // Deactivate VR session
                cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
                // Deactivate phone bt vr
                cppPhoneAdaptor.invReqPhoneBtVrDeactivation()
            }

            onReleased: {
                PopupManager.ePopupResult = PopupEnum.EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS
                btnReleased()
            }
        }

        Connections {
            target: PopupManager
            onSigRotaryUpdatePopup: {
                cppUIBase.qmlLog(
                            "OneButtonPopup.qml: sigRotaryUpdate: iKeyState: "
                            + iKeyState + " iKeyCode : " + iKey)
                PopupManager.invResetPopupTimer()

                if (HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState ||
                    HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState) {
                    if (-1 === prCurrentRREIndex) {
                        prCurrentRREIndex = 0
                    }
                }
            }

            onSigRotaryPressedPopup: {
                cppUIBase.qmlLog(
                            "OneButtonPopup.qml: onRotaryPressed: " + iKeyState)

                if(HardkeyEnum.HKEY_STATE_RELEASED === iKeyState ||
                   HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState){
                    if ((0 === prCurrentRREIndex) && idOkBtn.enabled) {
                        // Deactivate VR session
                        cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
                        // Deactivate phone bt vr
                        cppPhoneAdaptor.invReqPhoneBtVrDeactivation()
                        PopupManager.ePopupResult = PopupEnum.EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS
                        btnReleased()
                    }
                }
            }
        }
    }
}
