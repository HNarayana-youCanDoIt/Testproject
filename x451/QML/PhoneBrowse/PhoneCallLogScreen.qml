import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.phoneenum 1.0
import com.harman.qml.hardkeyenum 1.0
import "../Common"

BaseUI {
    id: idPhoneCallLogScreen



    /*
     * Component used to create List View item layout
     */
    Component {
        id: idListDelegate
        Column {
            CallLogListElement {
                id: idListItem
                height      : (idPhoneCallLogList.height/4) - idListSeparator.height
                width       : idPhoneCallLogList.idList.width
                prCallType: callLogType
                prContactName: callLogName
                prCallTime: callLogTime
                prCallDate: callLogDate

                onReleased: {
                    cppPhoneApp.qmlLog(
                                "PhoneCallLogsScreen.qml ListElementCallLog button: onReleased")
                    cppPhoneAdaptor.invDial(callLogNumber, callLogName)
                }
            }

            //Handling RRE HK for call logs items
            Connections
            {
                target: cppHardkeyAdaptor
                onSigRotaryPressed:
                {
                    cppPhoneApp.qmlLog("PhoneCallLogScreen: onRotaryUpdate: key state is: " + iKeyState)
                    if(iKeyState === HardkeyEnum.HKEY_STATE_RELEASED || iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED)
                    {
                        if(idPhoneCallLogList.idList.currentIndex === index)
                        {
                            cppPhoneApp.qmlLog("PhoneCallLogScreen.qml - HBButtonListItem RRE release/longReleae event, itemIndex is: " + index)
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

    /* Phone call logs screen list */
    GenericList {
        id: idPhoneCallLogList
        idList.model: cppPhoneAdaptor.callLogListModel
        idList.delegate: idListDelegate

        visible: (((cppPhoneAdaptor.pimDbCallListSyncStatus === PhoneEnum.PHONE_DATA_READ_UPDATING)
                   || (cppPhoneAdaptor.pimDbCallListSyncStatus === PhoneEnum.PHONE_DATA_READ_DONE))
                  && (cppPhoneAdaptor.callLogListModel.rowCount() > 0))
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

        visible: ((cppPhoneAdaptor.pimDbCallListSyncStatus === PhoneEnum.PHONE_DATA_READ_READY)
                  || (cppPhoneAdaptor.pimDbCallListSyncStatus === PhoneEnum.PHONE_DATA_READING)
                  || (cppPhoneAdaptor.pimDbCallListSyncStatus === PhoneEnum.PHONE_DATA_READ_OFF)
                  || ((cppPhoneAdaptor.pimDbCallListSyncStatus === PhoneEnum.PHONE_DATA_READ_UPDATING)
                      && (cppPhoneAdaptor.callLogListModel.rowCount() === 0)))

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
            text: qsTr("TEXT_PHONE_FETCHING_CALL_LOGS") + cppThemeMgr.languageChanged
            width: 395
            height: 39 //------->> orig: 24
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
     * Call Logs not available Text shows when call logs data not synced
     */
    HBText {
        id: idCallLogsNotAvailable
        visible: (cppPhoneAdaptor.pimDbCallListSyncStatus === PhoneEnum.PHONE_DATA_READ_FAIL)
        text: qsTr("TEXT_PHONE_CALL_LOGS_NOT_AVAIL") + cppThemeMgr.languageChanged

        width: 395
        height: 39 //------->> orig: 24
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



    /*
     * Call Logs Empty Text shows when call logs data synced and no logs found in database
     */
    HBText {
        id: idCallLogsEmpty
        visible: ((cppPhoneAdaptor.pimDbCallListSyncStatus === PhoneEnum.PHONE_DATA_READ_DONE)
                  && (cppPhoneAdaptor.callLogListModel.rowCount() === 0))
        text: qsTr("TEXT_PHONE_EMPTY_CALL_LOGS") + cppThemeMgr.languageChanged
        width: 395
        height: 39 //------->> orig: 24
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

    Component.onCompleted:
    {
        /* Clear the unread missed call count while entering into Calllogs screen */
        cppPhoneAdaptor.invResetUnreadMissedCallInfo();
    }
}
