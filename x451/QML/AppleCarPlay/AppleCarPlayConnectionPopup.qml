import QtQuick 2.7
import com.harman.qml.popupenums 1.0
import "../Common/Popup"

NoButtonPopup
{
    /**
      * Text to be displayed on Popup
      */
    // TODO: Popup string id should be added instead of static text.

    prPopupTitle: qsTr("Apple CarPlay") + cppThemeMgr.languageChanged

    /*
     * TODO: Need to prefix ellipsis if the string is not small enough to fit in
     * the space.
     */
    prPopupText: cppAppleCarPlayAdaptor.appleCarPlayDeviceName +  qsTr(" Connected.") + cppThemeMgr.languageChanged

    /*
     * AppleCarPlay Icon
     */
    Image{
        id: idAppleCarPlayIcon

        anchors {
            top: parent.top
            topMargin: 13
            left: parent.left
            leftMargin: 113
        }

        source: "qrc:/image/Drawers/QAD/Maximized/Contents/Gen_Drawer_Ico_Carplay_76x76_7in_n-assets/Gen_Drawer_Ico_Carplay_n.png"
    }

    MouseArea{
        //Mouse area to launch CarPlay if released
        anchors.fill: parent
        onReleased: {
            cppAppleCarPlayAdaptor.launchAppleCarPlay()
            PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_APPLE_CARPLAY_CONNECTION)
        }
    }
}

