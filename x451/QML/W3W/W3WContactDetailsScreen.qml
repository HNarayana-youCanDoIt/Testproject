import QtQuick 2.7
import com.harman.qml.phoneenum 1.0
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0
import "../Common"
import "../PhoneBrowse"

PhoneContactDetailsScreen {


    prPhoneContactDetailsList.idList.delegate: idW3WContactDetailsListDelegate

    /*
     * Component used to create List View item layout
     */
    Component {
        id: idW3WContactDetailsListDelegate
        Column {

            enabled: idContactDetailListItem.enabled

            ContactDetailsListElement {
                id: idContactDetailListItem
                height: (prPhoneContactDetailsList.height/3) - idListSeparator.height
                width: prPhoneContactDetailsList.idList.width
                prContactNumber: contactNumber
                prContactType: cppPhoneAdaptor.invGetContactTypeText(contactType)

                /* Override below properties to show the Message icon */
                prFavoriteButton.defaultImageURL: "qrc:/image/W3W/Gen_Ico_SMS_7in_n-assets/Gen_Ico_SMS_7in_n.png"
                prFavoriteButton.pressedImageURL: "qrc:/image/W3W/Gen_Ico_SMS_7in_n-assets/Gen_Ico_SMS_7in_np.png"
                prFavoriteButton.disabledImageURL: "qrc:/image/W3W/Gen_Ico_SMS_7in_n-assets/Gen_Ico_SMS_7in_nd.png"

                /* Override below methods for W3W Contact Details screen related the behaviour */
                onPressed: {
                    cppPhoneApp.qmlLog("W3WContactDetailsScreen.qml: idContactDetailListItem: onPressed")
                }

                onReleased: {
                    cppPhoneApp.qmlLog("W3WContactDetailsScreen.qml: idContactDetailListItem: onReleased")
                    cppW3WAdaptor.invShareW3WAddressViaSMS(contactNumber, cppW3WAdaptor.selectedW3WAddress)
                }

                onSigContactDetailCallPressed: {
                    cppPhoneApp.qmlLog("W3WContactDetailsScreen.qml: idContactDetailListItem: onSigContactDetailCallPressed")
                }

                onSigContactDetailCallReleased: {
                    cppPhoneApp.qmlLog("W3WContactDetailsScreen.qml: idContactDetailListItem: onSigContactDetailCallReleased")
                    cppW3WAdaptor.invShareW3WAddressViaSMS(contactNumber, cppW3WAdaptor.selectedW3WAddress)
                }

                onSigContactDetailFavPressed: {
                    cppPhoneApp.qmlLog("W3WContactDetailsScreen.qml: idContactDetailListItem: onSigContactDetailFavPressed")
                }

                onSigContactDetailFavReleased: {
                    cppPhoneApp.qmlLog("W3WContactDetailsScreen.qml: idContactDetailListItem: onSigContactDetailFavReleased")
                    cppW3WAdaptor.invShareW3WAddressViaSMS(contactNumber, cppW3WAdaptor.selectedW3WAddress)
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
                        if(prPhoneContactDetailsList.idList.currentIndex === index)
                        {
                            cppPhoneApp.qmlLog("W3WContactDetailsScreen.qml - HBButtonListItem RRE release/longReleae event, itemIndex is: " + index)
                            cppW3WAdaptor.invShareW3WAddressViaSMS(contactNumber, cppW3WAdaptor.selectedW3WAddress)
                        }
                    }
                }
            }

            ListItemSeparator {
                id: idListSeparator
            }
        }
    }

}
