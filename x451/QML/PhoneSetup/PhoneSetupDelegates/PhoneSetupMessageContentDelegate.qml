import QtQuick 2.7
import com.harman.qml.thememanager 1.0
import "../../Common"


/** Label with Edit Button Delegate ***
  * Delegate containing Label and Button Delegate.
  */
Item {
    id: idMessageContent

    height: (idMessageText.height + idEditBtn.height + 20)

    /* Message content text gets displayed using this alias */
    property alias prText: idMessageText.text

    /* This property is used to override the HBText if necessary*/
    property alias prHBText: idMessageText

    /* This property is used to get the height of message text */
    property int prMessageTextHeight: idMessageText.height

    /* Edit button visiblility status  handled using this property */
    property bool prEditBtnVisibilityStatus: true

    /* To find out the clicked edit button index */
    property int prEditBtnIndex: -1

    /* On click of edit button, this signal gets emitted */
    signal sigEditBtnClicked()

    /* HBText used to display the SMS content */
    HBText {
        id: idMessageText
        width: (parent.width - (anchors.leftMargin + 10))
        anchors {
            top: (prEditBtnVisibilityStatus ? parent.top : undefined)
            topMargin: (prEditBtnVisibilityStatus ? 10 : 0)
            left: parent.left
            leftMargin: 10
            verticalCenter: (prEditBtnVisibilityStatus ? undefined : parent.verticalCenter)
        }
        text: ""
        wrapMode: Text.Wrap
        fontType: ThemeMgr.FONTTYPE_T35_C3

    }

    /* Edit button, which triggers to keypad for writing custom message */
    GenericButton {
        id: idEditBtn
        height: (visible ? 40 : 0)

        anchors {
            bottom: idMessageContent.bottom
            bottomMargin: 5
            horizontalCenter: parent.horizontalCenter
        }
        text: qsTr("Edit") + cppThemeMgr.languageChanged
        visible: prEditBtnVisibilityStatus

        background: Image
        {
            id: idButtonBackground
            height: 40

            anchors.fill: parent
            visible: (source !== "")
            source: (parent.enabled)? ((parent.pressed)? (parent.pressedImageURL): (parent.defaultImageURL)): (parent.disabledImageURL)

        }

        defaultImageURL: "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_nd.png"
        pressedImageURL: "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_n.png"
        disabledImageURL: "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_nd.png"

        textFontType : ThemeMgr.FONTTYPE_T35_C3

        onReleased: {
            sigEditBtnClicked()
        }
    }
}

