import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../Common"
import com.harman.qml.thememanager 1.0

BaseUI {
    id: idSoftwareDetailsScreen

    HBTitleWithBackButton{
            /**Using QProperty ,changing the title of the List Screen **/
            id: idMainTitle
            prTitle: qsTr("TEXT_SETTINGS_SOFTWARE_DETAILS") + cppThemeMgr.languageChanged
        }

    ColumnLayout {
        id:idSoftwareReflashColumn

        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 160
            left: parent.left
            leftMargin: 240
        }
        spacing: 10

        HBText {
            id: idSwVersionText
            text: qsTr("Software Version: ") + cppVersionManagerAdaptor.swVersion  + cppThemeMgr.languageChanged
            fontType: ThemeMgr.FONTTYPE_T35_C3
        }

        HBText {
            id: idSwReleaseDate
            text: qsTr("Release Date: ") + cppVersionManagerAdaptor.swReleaseDate + cppThemeMgr.languageChanged
            anchors.horizontalCenter: parent.horizontalCenter
            fontType: ThemeMgr.FONTTYPE_T35_C3
        }
    }
}
