import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.phoneenum 1.0
import com.harman.qml.hardkeyenum 1.0
import "../Common"

BaseUI {
    id: idPhoneFrequentlyDialedScreen

    /*
     * Component used to create List View item layout
     */
    Component {
        id: idListDelegate
        Column {
            CallLogListElement {
                id: idListItem
                height      : (idFrequentlyDialedList.height/4) - idListSeparator.height
                width       : idFrequentlyDialedList.idList.width
                prCallType: callLogType
                prContactName: callLogName
                prCallTime: callLogTime
                prCallDate: callLogDate

                onReleased: {
                    cppPhoneApp.qmlLog(
                                "PhoneFrequentlyDialedScreen: idListItem: onReleased")
                    cppPhoneAdaptor.invDial(callLogNumber, callLogName)
                }
            }

            //Handling RRE HK for call logs items
            Connections
            {
                target: cppHardkeyAdaptor
                onSigRotaryPressed:
                {
                    cppPhoneApp.qmlLog("PhoneFrequentlyDialedScreen: onRotaryUpdate: key state is: " + iKeyState)
                    if(iKeyState === HardkeyEnum.HKEY_STATE_RELEASED || iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED)
                    {
                        if(idPhoneCallLogList.idList.currentIndex === index)
                        {
                            cppPhoneApp.qmlLog("PhoneFrequentlyDialedScreen - HBButtonListItem RRE release/longReleae event, itemIndex is: " + index)
                            cppPhoneAdaptor.invDial(callLogNumber, callLogName)
                        }
                    }
                }
            }

            ListItemSeparator {
                id: idListSeparator
            }
        }
    }

    /* Phone frequently dialed screen list */
    GenericList {
        id: idFrequentlyDialedList
        idList.model: cppPhoneAdaptor.frequentlyDialedListModel
        idList.delegate: idListDelegate

        visible: ((cppPhoneAdaptor.pimDbFrequentlyDialedListSyncStatus === PhoneEnum.PHONE_DATA_READ_DONE)
                  && (cppPhoneAdaptor.frequentlyDialedListModel.rowCount() > 0))
    }

    Item
    {
        id: idWiatingAnim
        anchors
        {
            top: parent.top
            topMargin: 139
            left: parent.left
        }

        visible: ((cppPhoneAdaptor.pimDbFrequentlyDialedListSyncStatus === PhoneEnum.PHONE_DATA_READ_READY)
                  || (cppPhoneAdaptor.pimDbFrequentlyDialedListSyncStatus === PhoneEnum.PHONE_DATA_READING)
                  || (cppPhoneAdaptor.pimDbFrequentlyDialedListSyncStatus === PhoneEnum.PHONE_DATA_READ_OFF))

        BusyIndicator
        {
            id: idBusyIndicator
            anchors
            {
                top: parent.top
                left: parent.left
                leftMargin: 350
            }
        }

        HBText {
            id: idWaitingText
            text: qsTr("TEXT_PHONE_FETCHING_FREQUENTLY_DIALED_NUMBERS") + cppThemeMgr.languageChanged
            width: 420
            height: 39
            anchors
            {
                left: parent.left
                leftMargin: 202
                top: parent.top
                topMargin: 105
            }

            fontType: ThemeMgr.FONTTYPE_T35_C3
            horizontalAlignment: HBText.AlignHCenter
            verticalAlignment: HBText.AlignVCenter
        }
    }

    /*
     * Frequently dialed list not available text shown on sync error
     */
    HBText {
        id: idFrequentlyDialedListNotAvailable
        visible: (cppPhoneAdaptor.pimDbFrequentlyDialedListSyncStatus === PhoneEnum.PHONE_DATA_READ_FAIL)
        text: qsTr("TEXT_PHONE_FREQUENTLY_DIALED_NUMBERS_NOT_AVAIL") + cppThemeMgr.languageChanged

        width: 420
        height: 39
        anchors {
            left: parent.left
            top: parent.top
            topMargin: 244
            horizontalCenter: parent.horizontalCenter
        }

        fontType: ThemeMgr.FONTTYPE_T35_C3
        horizontalAlignment: HBText.AlignHCenter
        verticalAlignment: HBText.AlignVCenter
    }

    /*
     * Frequently dialed list empty text shown on data empty
     */
    HBText {
        id: idCallLogsEmpty
        visible: ((cppPhoneAdaptor.pimDbFrequentlyDialedListSyncStatus === PhoneEnum.PHONE_DATA_READ_DONE)
                  && (cppPhoneAdaptor.frequentlyDialedListModel.rowCount() === 0))
        text: qsTr("TEXT_PHONE_EMPTY_FREQUENTLY_DIALED_LIST") + cppThemeMgr.languageChanged
        width: 420
        height: 39
        anchors {
            left: parent.left
            leftMargin: 202
            top: parent.top
            topMargin: 244
            horizontalCenter: parent.horizontalCenter
        }

        fontType: ThemeMgr.FONTTYPE_T35_C3
        horizontalAlignment: HBText.AlignHCenter
        verticalAlignment: HBText.AlignVCenter
    }
}
