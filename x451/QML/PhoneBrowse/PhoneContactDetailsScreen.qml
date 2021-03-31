import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0
import "../Common"

BaseUI {

    /* Property alias for Phone Contact Details list */
    property alias prPhoneContactDetailsList : idPhoneContactDetailsList

    Connections
    {
        target: cppPhoneAdaptor
        onSigHighlightContactCategory:
        {
            cppPhoneApp.qmlLog("onSigHighlightContactCategory : slot called")
            idPhoneContactDetailsList.idList.currentIndex = iLineNo
        }
    }

    //Handling RRE HK if VR session is active
    Connections
    {
        target: cppHardkeyAdaptor

        onSigPassHardkeyToOverlay:
        {
            cppVRApp.qmlLog("VRAnimPopup.qml: onSigPassHardkeyToOverlay: iKeyCode is: " + iKeyCode, " keystate is: ", iKeyState)
            if(cppVRAdaptor.invGetVRSessionStatus())
            {
                cppPhoneApp.qmlLog("VRAnimPopup.qml: onSigPassHardkeyToOverlay: VR session is active")
                //Inform VR adaptor to handle hardkey event
                cppHardkeyAdaptor.invSetHKHandledByOverlayStatus(cppVRAdaptor.invHandleHardKeys(iKeyCode, iKeyState))
            }
            else
            {
                cppPhoneApp.qmlLog("VRAnimPopup.qml: onSigPassHardkeyToOverlay: VR session is inactive")
            }
        }
    }

    /*
     * Component used to create List View item layout
     */
    Component {
        id: idContactDetailsListDelegate
        Column {

            enabled: idContactDetailListItem.enabled

            ContactDetailsListElement{
                id: idContactDetailListItem
                height: (idPhoneContactDetailsList.height/3) - idListSeparator.height
                width: idPhoneContactDetailsList.idList.width
                prContactNumber: contactNumber
                prContactType: cppPhoneAdaptor.invGetContactTypeText(contactType)
                prIsFavorite: contactIsFavorite
                onPressed:
                {
                    cppPhoneApp.qmlLog("PhoneContactDetailsScreen.qml: idContactDetailListItem: onPressed")
                    // Deactivate VR session
                    cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
                }

                onReleased: {
                    cppPhoneApp.qmlLog("PhoneContactDetailsScreen.qml: idContactDetailListItem: onReleased")
                    cppPhoneAdaptor.invDial(contactNumber, contactName)
                }

                onSigContactDetailCallPressed: {
                    cppPhoneApp.qmlLog("PhoneContactDetailsScreen.qml: idContactDetailListItem: onSigContactDetailCallPressed")
                    // Deactivate VR session
                    cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
                }

                onSigContactDetailCallReleased: {
                    cppPhoneApp.qmlLog("PhoneContactDetailsScreen.qml: idContactDetailListItem: onSigContactDetailCallReleased")
                    cppPhoneAdaptor.invDial(contactNumber, contactName)
                }

                onSigContactDetailFavPressed: {
                    cppPhoneApp.qmlLog("PhoneContactDetailsScreen.qml: idContactDetailListItem: onSigContactDetailFavPressed")
                    // Deactivate VR session
                    cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
                }

                onSigContactDetailFavReleased: {
                    cppPhoneApp.qmlLog("PhoneContactDetailsScreen.qml: idContactDetailListItem: onSigContactDetailFavReleased")
                    if(contactIsFavorite){
                        cppPhoneAdaptor.invRemoveContactFromFavorite(
                                    contactName, contactID, contactNumber, contactType,
                                    contactFavoriteIndex)
                    }
                    else{
                        cppPhoneAdaptor.invAddContactToFavorite(
                                    contactName, contactID, contactNumber, contactType,
                                    contactFavoriteIndex)
                    }
                }
            }

            //Handling RRE HK for contacts details items
            Connections
            {
                target: cppHardkeyAdaptor
                onSigRotaryPressed:
                {
                    cppPhoneApp.qmlLog("PhoneContactDetailsScreen: onRotaryUpdate: key state is: " + iKeyState)
                    if(iKeyState === HardkeyEnum.HKEY_STATE_RELEASED || iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED)
                    {
                        if(idPhoneContactDetailsList.idList.currentIndex === index)
                        {
                            cppPhoneApp.qmlLog("PhoneContactDetailsScreen.qml - HBButtonListItem RRE release/longReleae event, itemIndex is: " + index)
                            cppPhoneAdaptor.invDial(contactNumber, contactName)
                            // Deactivate VR session
                            cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
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
        id: idPhoneContactDetailsList

        anchors {
            top: parent.top
            topMargin: 216
        }
        rowShownPerPage: 3
        prScrollBarTopMargin: -prItemHeight
        height: 228
        idList.model: cppPhoneAdaptor.contactDetailListModel
        idList.delegate: idContactDetailsListDelegate
    }

    HBText {
        id: idContactNameText
        height: 25
        width: 469
        anchors{
            left: parent.left
            leftMargin: 147
            top: parent.top
            topMargin: 167
        }

        text: cppPhoneAdaptor.contactDetailListModel.getNameFromIndex(0)
    }

    ListItemSeparator {
        id: idListSeparator
        anchors{
            left: idPhoneContactDetailsList.left
            top: parent.top
            topMargin: 215
        }
    }
}
