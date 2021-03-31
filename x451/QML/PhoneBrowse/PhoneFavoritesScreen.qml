import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.phoneenum 1.0
import com.harman.qml.hardkeyenum 1.0
import "../Common"

BaseUI {
    id: idPhoneFavoritesScreen

    /*
     * Component used to create List View item layout
     */
    Component {
        id: idListDelegate
        Column {
            FavoritesListElements {
                id: idListItem
                height      : (idPhoneFavoriteList.height/4) - idListSeparator.height
                width       : idPhoneFavoriteList.idList.width
                prContactType: cppPhoneAdaptor.invGetContactTypeText(contactType)
                prContactName: contactName
                prContactNumber: contactNumber
                prIsFavorite: contactIsFavorite

                onReleased: {
                    cppPhoneAdaptor.invDial(contactNumber, contactName)
                }

                onSigFavoriteBtnReleased: {
                    cppPhoneAdaptor.invRemoveContactFromFavorite(
                                contactName, contactID, contactNumber, contactType,
                                contactFavoriteIndex)
                }
            }

            //Handling RRE HK for favorite items
            Connections
            {
                target: cppHardkeyAdaptor
                onSigRotaryPressed:
                {
                    cppPhoneApp.qmlLog("PhoneFavoriteScreen: onRotaryUpdate: key state is: " + iKeyState)
                    if(iKeyState === HardkeyEnum.HKEY_STATE_RELEASED || iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED)
                    {
                        if(idPhoneFavoriteList.idList.currentIndex === index)
                        {
                            cppPhoneApp.qmlLog("PhoneFavoriteScreen.qml - HBButtonListItem RRE release/longReleae event, itemIndex is: " + index)
                            cppPhoneAdaptor.invDial(contactNumber, contactName)
                        }
                    }
                }
            }

            ListItemSeparator {
                id: idListSeparator
            }
        }
    }

    /* Phone favorite screen list */
    GenericList {
        id: idPhoneFavoriteList

        height: 284

        idList.model: cppPhoneAdaptor.favoriteContactListModel
        idList.delegate: idListDelegate

        visible: (((cppPhoneAdaptor.pimDbFavouriteListSyncStatus === PhoneEnum.PHONE_DATA_READ_UPDATING)
                   || (cppPhoneAdaptor.pimDbFavouriteListSyncStatus === PhoneEnum.PHONE_DATA_READ_DONE))
                  && (idPhoneFavoriteList.idList.count > 0))
    }

    Item {
        id: idWiatingAnim
        anchors
        {
            top: parent.top
            topMargin: 139
            left: parent.left
        }

        visible: ((cppPhoneAdaptor.pimDbFavouriteListSyncStatus === PhoneEnum.PHONE_DATA_READ_READY)
                  || (cppPhoneAdaptor.pimDbFavouriteListSyncStatus === PhoneEnum.PHONE_DATA_READING)
                  || (cppPhoneAdaptor.pimDbFavouriteListSyncStatus === PhoneEnum.PHONE_DATA_READ_OFF)
                  || (cppPhoneAdaptor.pimDbFavouriteListSyncStatus === PhoneEnum.PHONE_DATA_READ_UPDATING)
                  && (idPhoneFavoriteList.idList.count === 0))

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
            text: qsTr("TEXT_PHONE_BROWSE_DOWNLOADING_FAVOURITES") + cppThemeMgr.languageChanged
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
     * favorite empty Text shows when favorite data synced and no favorite found in database
     */
    HBText {
        id: idFavoritesEmpty
        visible: ((cppPhoneAdaptor.pimDbFavouriteListSyncStatus === PhoneEnum.PHONE_DATA_READ_DONE)
                  && (idPhoneFavoriteList.idList.count === 0))
        text: qsTr("TEXT_PHONE_BROWSE_NO_FAVOURITES_STORED") + cppThemeMgr.languageChanged
        width: 395
        height: 39 //------->> orig: 24

        anchors
        {
            left: parent.left
            leftMargin: 202
            top: parent.top
            topMargin: 244
        }

        fontType: ThemeMgr.FONTTYPE_T35_C3
        horizontalAlignment: HBText.AlignHCenter
        verticalAlignment: HBText.AlignVCenter
    }

    /*
     * Favourite not available Text shows when Favourite data not synced
     */
    HBText
    {
        id: idFavoritesNotAvailable
        visible: (cppPhoneAdaptor.pimDbFavouriteListSyncStatus === PhoneEnum.PHONE_DATA_READ_FAIL)
        text: qsTr("TEXT_PHONE_BROWSE_FAVOURITE_NOT_AVAILABLE") + cppThemeMgr.languageChanged
        width: 395
        height: 39 //------->> orig: 24

        anchors
        {
            left: parent.left
            leftMargin: 202
            top: parent.top
            topMargin: 244
        }

        fontType: ThemeMgr.FONTTYPE_T35_C3
        horizontalAlignment: HBText.AlignHCenter
        verticalAlignment: HBText.AlignVCenter
    }
}
