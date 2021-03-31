import QtQuick 2.7
import "../../../Common"
import com.harman.qml.thememanager 1.0

Item {
    id: idActiveCallComponent

    anchors.fill: parent

    /*
            * Label to show the Call in Progress.
            */
    HBText {
        id: idTxtCall

        width: 200
        height: 22

        anchors
        {
            fill: parent
            leftMargin: 25
        }

        text: qsTr("TEXT_QAD_LABEL_ACTIVE_CALL") + cppThemeMgr.languageChanged

        elide: Text.ElideRight
        fontType: enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
    }
}
