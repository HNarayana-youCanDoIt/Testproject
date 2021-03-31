import QtQuick 2.7
import "../../../Common"
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0

Item {

    anchors.fill: parent

    /*
     * MediaOff Button onRelease of this HMI has to come out from MediaOff.
     */
    GenericButton {
        id: idSourceInfoButton

        width: parent.width
        height: parent.height

       anchors{
           left: parent.left
           leftMargin: 20
       }

       contentItem:  Item {

           anchors.fill: parent

           HBText{
               id: idTapOnText

               width: 63
               height: 30

               anchors{
                   left: parent.left
                   verticalCenter: parent.verticalCenter
               }

               text: qsTr("Press") + cppThemeMgr.languageChanged

               fontType: enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
           }

           Image{
               id: idMediaOffIcon

               anchors{
                   left: idTapOnText.right
                   verticalCenter: parent.verticalCenter
               }

               source: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Ico_RotaryVolume_7in_n-assets/Drw_Ico_RotaryVolume_7in_nd.png"
           }

           HBText{

               width: 290
               height: 30

               anchors{
                   left: idMediaOffIcon.right
                   leftMargin: 5
                   verticalCenter: parent.verticalCenter
               }

               text: qsTr("to Resume Media Playback.") + cppThemeMgr.languageChanged

               fontType: enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
           }
       }

        onReleased: {
            // Do nothing.
        }
    }

    Component.onCompleted: {
        cppDrawersApp.qmlLog("QadMediaOffComponent.qml: Component.onCompleted.")
    }

}
