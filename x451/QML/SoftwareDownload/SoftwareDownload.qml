import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../Common"
import com.harman.qml.thememanager 1.0

BaseUI {

    /////////////////////////////////////////////////////////////////////////////////
    //Property to take account of Number of press to open EnggMenu Screen.
    //Todo: It can be change as per requirement.
    property int counter: 0

    /**
     * Timer used to reset the counter after a particular time interval.
     */
    Timer {
        id: idClickTimer
        interval: 5000

        onTriggered: {
            cppUIBase.qmlLog("Timer Triggered")
            resetCounter()
        }
    }

    function resetCounter()
    {
        cppUIBase.qmlLog("Resetting Counter")
        counter = 0
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked:
        {
            resetCounter()
        }
    }

    MouseArea
    {
        id: idLeftClickableArea

        width: 150
        height: 120

        anchors
        {
            top: parent.top
            topMargin: 180
            left: parent.left
            leftMargin: 130
        }

        onClicked:
        {
            if(counter >= 4)
            {
                counter++
                cppUIBase.qmlLog("CounterLeft: " + counter)
                idClickTimer.start()
                if(8 === counter)
                {
                    cppSoftwareUpdateApp.raiseSMEvent("EnggMenu", "EnggMenu")
                    idClickTimer.stop()
                }
            }
            else
            {
                resetCounter()
            }
        }
    }

    MouseArea
    {
        id: idRightClickableArea

        width: 150
        height: 120

        anchors
        {
            top: parent.top
            topMargin: 180
            right: parent.right
            rightMargin: 130
        }

        onClicked:
        {
            counter++
            cppUIBase.qmlLog("CounterRight: " + counter)
            idClickTimer.start()
            if(counter > 4)
            {
                resetCounter()
            }
        }
    }

    ColumnLayout {
        id: idSoftwareReflashColumn

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
            text: qsTr("Software Version: ") + cppVersionManagerAdaptor.swVersion
                  + cppThemeMgr.languageChanged
            anchors.horizontalCenter: parent.horizontalCenter
            fontType: ThemeMgr.FONTTYPE_T35_C3
        }

        HBText {
            id: idSwReleaseDate
            text: qsTr("Release Date: ") + cppVersionManagerAdaptor.swReleaseDate
                  + cppThemeMgr.languageChanged
            anchors.horizontalCenter: parent.horizontalCenter
            fontType: ThemeMgr.FONTTYPE_T35_C3
        }
    }

    HBTitleWithBackButton{
        /**Using QProperty ,changing the title of the List Screen **/
        id: idMainTitle
        prTitle: qsTr("Software Reflash") + cppThemeMgr.languageChanged
    }

    GenericButton {
        id: idUpdateBtn

        width: 170
        height: 50

        anchors {
            top: idSoftwareReflashColumn.bottom
            topMargin: 90
            horizontalCenter: parent.horizontalCenter
        }

        defaultImageURL: "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_nd.png"
        pressedImageURL: "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_n.png"
        disabledImageURL: "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_nd.png"

        enabled: cppSoftwareUpdateAdaptor.swUpdateAvailability && (!cppSoftwareUpdateAdaptor.busyIndicatorVisibility)
        textFontType: enabled ? ThemeMgr.FONTTYPE_T35_C3 : ThemeMgr.FONTTYPE_T35_BK_C2_DISABLED

        text: qsTr("Update") + cppThemeMgr.languageChanged

        //[FixMe:: This is temporary implementation.]
        background: Image
        {
            id: idUpdateBtnBackground

            anchors.fill: parent
            visible: (source !== "")
            source: (parent.enabled)? ((parent.pressed)? (parent.pressedImageURL): (parent.defaultImageURL)): (parent.disabledImageURL)

        }

        onReleased: {
            cppSoftwareUpdateAdaptor.busyIndicatorVisibility = true
            cppSoftwareUpdateAdaptor.checkForUpdateAttribute()
        }

        Connections {
            target: cppHardkeyAdaptor
            onSigRotaryPressed: {
                cppUIBase.qmlLog(
                            "SoftwareDownload.qml: onRotaryUpdate: " + iKeyState)
                if ((iKeyState === 4 || iKeyState === 3)
                        && (idUpdateBtn.enabled)) {
                    cppSoftwareUpdateApp.qmlLog(
                                "SoftwareDownload.qml - SW update intiated via rotary")
                    cppSoftwareUpdateAdaptor.busyIndicatorVisibility = true
                    cppSoftwareUpdateAdaptor.checkForUpdateAttribute()
                }
            }
        }

        BusyIndicator {
            scale: 0.5
            visible: cppSoftwareUpdateAdaptor.busyIndicatorVisibility
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
        }

        Component.onCompleted: {
            cppSoftwareUpdateAdaptor.busyIndicatorVisibility = false
        }
    }

    Timer{
        id: idCancelFFwdTimer
        interval: 1500
        onTriggered: {
            cppSoftwareUpdateApp.qmlLog("SoftwareDownload.qml: cancelFastForward() invoked")
            MediaAdaptor.cancelFastForward()
        }
    }

    Component.onCompleted:
    {
        idCancelFFwdTimer.start()
    }
}
