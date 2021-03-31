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
    contentHeight: idPopupBg.height

    // This property holds the width of content item
    contentWidth: idPopupBg.width

    // Padding is used to set the co-orinates of Content Item
    topPadding: ((parent.height - idPopupBg.height) / 2)
    leftPadding: ((parent.width - idPopupBg.width) / 2)

    // Property for Center Image source.
    property alias prImageSrc: idCenterImage.source

    contentItem: Item {
        id: idPopupContent

        /**
         * Mouse area to prevent Popup to close when Content Item of the Popup is Touched
         */
        MouseArea{
            anchors.fill: parent
            onPressed: {
                cppUIBase.qmlLog("NoButtonPopupWithImage.qml: Popup Content Item Touched")
                // Deactivate VR session
                cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
                // Deactivate phone bt vr
                cppPhoneAdaptor.invReqPhoneBtVrDeactivation()
            }
        }

        Image {
            id: idPopupBg
            source: "qrc:/image/Popup/PopupBg/Gen_Gfx_5thPopupBg_7in_n-assets/Gen_Gfx_5thPopupBgColourPatch_n.png"
            ColorOverlay {
                id: idPopupBgColorOverlay
                anchors.fill: parent
                source: parent
                color:  cppThemeMgr.currentThemeColor
            }
        }

        Image {
            id: idPopupBgOverlay
            source: "qrc:/image/Popup/PopupBg/Gen_Gfx_5thPopupBg_7in_n-assets/Gen_Gfx_5thPopupBgOverlay_n.png"
        }

        /**
          * HBText to hold title to be displayed on popup
          **/
        HBText {
            id: idPopupTitle
            width: 422
            height: 25

            anchors{
                horizontalCenter: idCenterImage.horizontalCenter
                top: parent.top
                topMargin: 30
            }
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            fontType: ThemeMgr.FONTTYPE_T35_BK_C2
        }

        /*
         * Image Needs to show on Popup between Title and Text
         */
        Image{
            id: idCenterImage

            anchors.centerIn: parent

            source: prImageSrc
        }

        /**
          * HBText one to hold text to be displayed on popup
          **/
        HBText {
            id: idPopupText

            width: 471
            height: 18

            anchors {
                top: idCenterImage.bottom
                topMargin: 30
                horizontalCenter: idCenterImage.horizontalCenter
            }

            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
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
