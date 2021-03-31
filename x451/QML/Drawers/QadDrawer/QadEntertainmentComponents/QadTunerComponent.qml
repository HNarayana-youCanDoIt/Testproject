import QtQuick 2.7
import "../../../Common"
import QtQuick.Layouts 1.3
import com.harman.qml.drawersenums 1.0
import com.harman.qml.thememanager 1.0

Item {
    id: idMediaComponent

    anchors.fill: parent

    /*
     * Tuner Info button, onclick of this HMI needs to
     * launch the tuner screen.
     */
    GenericButton {
        id: idSourceInfoButton

        anchors.fill: parent

        contentItem: Item {

            anchors.fill: parent
            /*
             * Image field to show Tuner source icon.
             */
            Image {
                id: idCurrentEntSourceIcon

                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                }

                source: enabled
                        ? "qrc:/image/Drawers/QAD/Maximized/Contents/Gen_Drawer_Ico_Radio_7in_n-assets/Gen_Drawer_Ico_Radio_n.png"
                        : "qrc:/image/Drawers/QAD/Maximized/Contents/Gen_Drawer_Ico_Radio_7in_n-assets/Gen_Drawer_Ico_Radio_nd.png"
            }

            /*
             * The column to show frequency label and station name label.
             */
            ColumnLayout {
                id: idSourceInfoTextColumn

                width: 181//163
                height: 48
                spacing: 10

                anchors {
                    left: idCurrentEntSourceIcon.right
                    verticalCenter: parent.verticalCenter
                }

                /*
                 * Label to show the current playing frequency text.
                 */
                HBText {
                    id: idFrequencyText

                    Layout.preferredWidth: parent.width
                    Layout.preferredHeight: 22

                    anchors.verticalCenter: (cppTunerAdaptor.strStationName === "") ? parent.verticalCenter : undefined

                    text: (cppTunerAdaptor.strFrequency + " " + (cppTunerAdaptor.strFrequencyUnit + cppThemeMgr.languageChanged))

                    elide: Text.ElideRight
                    fontType: enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
                }

                /*
                 * Label to show the current playing sstation name text.
                 */
                HBText {
                    id: idStationNameText

                    Layout.preferredWidth: parent.width
                    Layout.preferredHeight: 22

                    text: cppTunerAdaptor.strStationName

                    elide: Text.ElideRight
                    fontType: enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C2 : ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED
                }
            }
        }

        onReleased: {
            cppDrawersApp.qmlLog(
                        "QadTunerComponent.qml: SourceInfo button released.")
            maxDrawerClicked()
            cppAudioAdaptor.switchToActiveEntertainmentSourceScreen()
        }
    }

    /*
     * AutoSeekDown button for Tuner
     */
    GenericButton {
        id: idAutoSeekDownButton

        width: 76
        height: parent.height

        anchors {
            left: parent.left
            leftMargin: 279
            verticalCenter: parent.verticalCenter
        }

        defaultImageURL: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_FastRewind_7in_n-assets/Gen_Drawer_Button_Rewind_na.png"
        pressedImageURL: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_FastRewind_7in_n-assets/Gen_Drawer_Button_Rewind_nf.png"
        disabledImageURL: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_FastRewind_7in_n-assets/Gen_Drawer_Button_Rewind_nd.png"

        onReleased: {
            cppDrawersApp.qmlLog(
                        "QadTunerComponent.qml: AutoSeekDown released.")
             cppTunerAdaptor.requestAutoSeekDown()
             resetMaxDrawerCloseTimer()
        }
    }

    /*
     * AutoSeekUp button for Tuner
     */
    GenericButton {
        id: idAutoSeekUpButton

        width: 76
        height: parent.height

        anchors {
            left: parent.left
            leftMargin: 468
            verticalCenter: parent.verticalCenter
        }

        defaultImageURL: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_FastForward_7in_n-assets/Gen_Drawer_Button_Forward_na.png"
        pressedImageURL: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_FastForward_7in_n-assets/Gen_Drawer_Button_Forward_nf.png"
        disabledImageURL: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_FastForward_7in_n-assets/Gen_Drawer_Button_Forward_nd.png"

        onReleased: {
            cppDrawersApp.qmlLog(
                        "QadTunerComponent.qml: AutoSeekUp released.")
            cppTunerAdaptor.requestAutoSeekUP()
            resetMaxDrawerCloseTimer()
        }
    }
}
