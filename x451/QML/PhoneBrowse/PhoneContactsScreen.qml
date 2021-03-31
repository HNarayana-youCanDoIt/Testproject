import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.phoneenum 1.0
import com.harman.qml.hardkeyenum 1.0
import "../Common"

BaseUI {
    id: idPhoneContactsScreen

    /*
     * Component used to create List View item layout
     */
    Component {
        id: idListDelegate

        Column {
            property int prContactID: model.contactID
            HBButtonListItem {
                id: idListItem
                height: (idPhoneContactsList.height/4) - idListSeparator.height
                width: idPhoneContactsList.idList.width
                text: model.contactName

                onReleased: {
                    cppUIBase.qmlLog("PhoneContactsScreen.qml HBButtonListItem button: onReleased")
                    cppPhoneAdaptor.contactListCurrentTopIndex = (idPhoneContactsList.idList.indexAt(0, idPhoneContactsList.idList.contentY))
                    cppPhoneAdaptor.invGetContactDetails(prContactID)
                    cppPhoneApp.raiseSMEvent("PhoneBrowse", PhoneEnum.PHONE_BROWSE_TYPE_CONTACT_DETAILS)
                }
            }

            //Handling RRE HK for contacts items
            Connections
            {
                target: cppHardkeyAdaptor
                onSigRotaryPressed:
                {
                    cppPhoneApp.qmlLog("PhoneContactScreen: onRotaryUpdate: key state is: " + iKeyState)
                    if(iKeyState === HardkeyEnum.HKEY_STATE_RELEASED || iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED)
                    {
                        if(idPhoneContactsList.idList.currentIndex === index)
                        {
                            cppPhoneApp.qmlLog("PhoneContactScreen.qml - HBButtonListItem RRE release/longReleae event, itemIndex is: " + index)
                            cppPhoneAdaptor.contactListCurrentTopIndex = (idPhoneContactsList.idList.indexAt(0, idPhoneContactsList.idList.contentY))
                            cppPhoneAdaptor.invGetContactDetails(prContactID)
                            cppPhoneApp.raiseSMEvent("PhoneBrowse", PhoneEnum.PHONE_BROWSE_TYPE_CONTACT_DETAILS)
                        }
                    }
                }
            }

            ListItemSeparator {
                id: idListSeparator
            }
        }
    }

    /* Phone Contacts screen list */
    GenericList {
        id: idPhoneContactsList
        prSetTopIndexByScreen: true

        idList.model: cppPhoneAdaptor.contactListModel
        idList.delegate: idListDelegate

        visible: (((PhoneEnum.PHONE_DATA_READ_UPDATING === cppPhoneAdaptor.pimDbContactListSyncStatus)
                   || (PhoneEnum.PHONE_DATA_READ_DONE === cppPhoneAdaptor.pimDbContactListSyncStatus))
                  && (cppPhoneAdaptor.contactListModel.rowCount() > 0))
    }    

    Item {
        id: idWiatingAnim
        anchors
        {
            top: parent.top
            topMargin: 139
            left: parent.left
        }

        visible: ((PhoneEnum.PHONE_DATA_READ_READY === cppPhoneAdaptor.pimDbContactListSyncStatus)
                  || (PhoneEnum.PHONE_DATA_READING === cppPhoneAdaptor.pimDbContactListSyncStatus)
                  || (PhoneEnum.PHONE_DATA_READ_OFF === cppPhoneAdaptor.pimDbContactListSyncStatus)
                  || ((PhoneEnum.PHONE_DATA_READ_UPDATING === cppPhoneAdaptor.pimDbContactListSyncStatus)
                      && (cppPhoneAdaptor.contactListModel.rowCount() === 0)))

        BusyIndicator {
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
            text: qsTr("TEXT_PHONE_DOWNLOADING_PHONEBOOK") + cppThemeMgr.languageChanged
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
     * Phonebook Empty Text shows when Phonebook data synced and no contact found in database
     */
    HBText {
        id: idContactEmpty
        visible: ((PhoneEnum.PHONE_DATA_READ_DONE === cppPhoneAdaptor.pimDbContactListSyncStatus)
                  && (cppPhoneAdaptor.contactListModel.rowCount() === 0))
        text: qsTr("TEXT_PHONE_PHONEBOOK_EMPTY") + cppThemeMgr.languageChanged
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
     * Phonebook not available Text shows when Phonebook data not synced
     */
    HBText {
        id: idContactDownloadFailed
        visible: (cppPhoneAdaptor.pimDbContactListSyncStatus === PhoneEnum.PHONE_DATA_READ_FAIL)
        text: qsTr("TEXT_PHONE_BROWSE_PHONEBOOK_DOWNLOAD_FAILED") + cppThemeMgr.languageChanged
        width: 415
        height: 39 //------->> orig: 24
        anchors {
            left: parent.left
            leftMargin: 182
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
        cppPhoneApp.qmlLog("PhoneContactScreen.qml - top item index is: " + cppPhoneAdaptor.contactListCurrentTopIndex)
        idPhoneContactsList.idList.positionViewAtIndex(cppPhoneAdaptor.contactListCurrentTopIndex, ListView.Beginning)
    }
}
