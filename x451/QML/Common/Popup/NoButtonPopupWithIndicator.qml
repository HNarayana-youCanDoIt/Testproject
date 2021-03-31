import QtQuick 2.7
import "../../Common"
import com.harman.qml.thememanager 1.0
import QtGraphicalEffects 1.0
import com.harman.qml.hardkeyenum 1.0

/*
  Template for Popup with Only TEXT and no BUTTONS
*/
BasePopup {

    // Property for text to be set in the popup
    property alias prPopupTitle: idPopupTitle.text

    // Property for text to be set in the popup
    property alias prPopupText: idPopupText.text

    // This property holds the height of content item
    contentHeight: 255

    // This property holds the width of content item
    contentWidth: 546

    // Padding is used to set the co-orinates of Content Item
    topPadding: 113
    leftPadding: 127

    contentItem: Item {
        id: idPopupContent

        /**
         * Mouse area to prevent Popup to close when Content Item of the Popup is Touched
         */
        MouseArea{
            anchors.fill: parent
            onPressed: {
                cppUIBase.qmlLog("NoButtonPopupWithIndicator.qml: Popup Content Item Touched")
                // Deactivate VR session
                cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
                // Deactivate phone bt vr
                cppPhoneAdaptor.invReqPhoneBtVrDeactivation()
            }
        }

        Image {
            id: idPopupBg
            source: "qrc:/image/Popup/PopupBg/PopUp_Backgr_No_btn/Gen_Gfx_4thPopupBgColourPatch_n.png"
            ColorOverlay {
                id: idPopupBgColorOverlay
                anchors.fill: parent
                source: parent
                color:  cppThemeMgr.currentThemeColor
            }
        }

        Image {
            id: idPopupBgOverlay
            source: (prPopupTitle === "") ? "qrc:/image/Popup/PopupBg/PopUp_Backgr_No_btn/Gen_Gfx_NoBtn_NoTitle_PopupBgOverlay_n.png"
                                          : "qrc:/image/Popup/PopupBg/PopUp_Backgr_No_btn/Gen_Gfx_NoBtn_TitlePopupBgOverlay_n.png"
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
                topMargin: 17
                leftMargin: 70
            }
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            fontType: ThemeMgr.FONTTYPE_T35_BK_C2
        }

        /**
          * HBText one to hold text to be displayed on popup
          **/
        HBText {
            id: idPopupText
            width: 471
            height: 18

            anchors {
                top: parent.top
                left: parent.left
                topMargin: 160
                leftMargin: 37
            }
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        }

        BusyIndicator {
            id:idBusyIndicator
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
            visible: true

        }

        Connections{
            target: PopupManager

            onSigRotaryPressedPopup:{
                cppUIBase.qmlLog("NoButtonPopup.qml: onRotaryPressed: " + iKeyState)


                if(HardkeyEnum.HKEY_STATE_RELEASED === iKeyState ||
                   HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState){
                   PopupManager.closeOnHardKey()
                }
            }
        }


    }
}
