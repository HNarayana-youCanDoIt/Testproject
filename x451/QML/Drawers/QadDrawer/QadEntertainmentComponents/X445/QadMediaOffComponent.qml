import QtQuick 2.7
import "../../../../Common"
import com.harman.qml.hardkeyenum 1.0
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
            leftMargin: 10
        }

        contentItem:  Item {

            anchors.fill: parent

            Image{
                id: idMediaOffIcon

                height: 76
                width: 76

                anchors{
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                }

                source: "qrc:/image/Drawers/QAD/Maximized/Contents/Gen_Drawer_Ico_MediaOff_7in_n-assets/Gen_Drawer_Ico_MediaOff_n.png"
            }

            HBText{

                anchors{
                    left: idMediaOffIcon.right
                    verticalCenter: parent.verticalCenter
                }

                text: qsTr("TEXT_MEDIA_OFF_TAP_RESUME_LABEL") + cppThemeMgr.languageChanged

                fontType: enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
            }
        }
        onCanceled: {
            cppDrawersApp.qmlLog("ShortcutDrawerContainerItem.qml: Media Off button onCanceled")
            cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_POWER, HardkeyEnum.HKEY_STATE_RELEASED)
        }

        onReleased: {
            cppDrawersApp.qmlLog("ShortcutDrawerContainerItem.qml: Media Off button onReleased")
            cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_POWER, HardkeyEnum.HKEY_STATE_RELEASED)
        }

        onPressed: {
            cppDrawersApp.qmlLog("ShortcutDrawerContainerItem.qml : Media Off button onPressed")
            // Deactivate VR session
            cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
            cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_POWER, HardkeyEnum.HKEY_STATE_PRESSED)
        }
    }

    Component.onCompleted: {
        cppDrawersApp.qmlLog("QadMediaOffComponent.qml: Component.onCompleted.")
    }

}
