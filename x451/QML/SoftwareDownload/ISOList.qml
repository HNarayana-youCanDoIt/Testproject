import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../Common"
import com.harman.qml.thememanager 1.0

BaseUI {

    HBTitleWithBackButton {
        /**Using QProperty ,changing the title of the List Screen **/
        prTitle: qsTr("Software Files") + cppThemeMgr.languageChanged
    }
    Component {
        id: idSwUpdateListDelegate

        Column {
            HBButtonListItem {
                height: idSwUpdateISOList.prItemHeight - idSeparator.height
                width: idSwUpdateISOList.idList.width
                text: cppUIBase.invTruncateText(modelData,34)
                enabled: !cppSoftwareUpdateAdaptor.busyIndicatorVisibility
                onReleased: {
                    cppUIBase.qmlLog("ISOList.qml - index: " + index)
                    cppSoftwareUpdateAdaptor.showISOFileConfirmPopup(index,
                                                                     modelData)
                }

                BusyIndicator {
                    visible: (cppSoftwareUpdateAdaptor.busyIndicatorVisibility
                              && (index === cppSoftwareUpdateAdaptor.selectedISOIndex))
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                        verticalCenter: parent.verticalCenter
                    }
                }
            }

            Connections {
                target: cppHardkeyAdaptor
                onSigRotaryPressed: {
                    cppUIBase.qmlLog(
                                "GenericList: onRotaryUpdate: " + iKeyState)
                    if ((iKeyState === 4 || iKeyState === 3)
                            && (!cppSoftwareUpdateAdaptor.busyIndicatorVisibility)) {
                        cppUIBase.qmlLog(idSwUpdateISOList.idList.currentIndex
                                         + "ISOList.qml - index: " + index)
                        if (idSwUpdateISOList.idList.currentIndex === index) {
                            cppUIBase.qmlLog(
                                        "ISOList.qml - showISOFileConfirmPopup invoked")
                            cppSoftwareUpdateAdaptor.showISOFileConfirmPopup(
                                        index, modelData)
                        } else {


                            //Do nothing
                        }
                    }
                }
            }

            ListItemSeparator {
                id: idSeparator
            }
        }
    }

    GenericList {
        id: idSwUpdateISOList
        anchors.leftMargin: 100
        prScrollBarLeftMargin: 550
        width: (parent.width - anchors.leftMargin - 100)

        idList.model: cppSoftwareUpdateAdaptor.swISOList
        idList.delegate: idSwUpdateListDelegate
    }

    Component.onCompleted: {
        cppSoftwareUpdateAdaptor.busyIndicatorVisibility = false
    }
}
