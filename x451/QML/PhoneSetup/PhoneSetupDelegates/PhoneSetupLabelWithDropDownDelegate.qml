import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.harman.qml.phoneenum 1.0
import com.harman.qml.hardkeyenum 1.0
import "../../Common"

/** Label with Dropdown Image Delegate ***
  * Delegate containing Label and Dropdown image Delegate.
  */

Item
{
    id: idLabelWithDropDownImageDelegate
    width: idGenericList.width
    height: idGenericList.prItemHeight

    Column {
        LabelWithClickableImage {
            id: idDropDown
            width: idGenericList.width
            height: idGenericList.prItemHeight - idCheckboxItemSeparator.height

            prDefaultImage: (idPhoneSetupMain.prCurrentExpandedIndex === itemId)
                            ? "qrc:/image/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_n.png"
                            : "qrc:/image/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_n.png"

            prPressedImage: (idPhoneSetupMain.prCurrentExpandedIndex === itemId)
                            ? "qrc:/image/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_nf.png"
                            : "qrc:/image/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_nf.png"

            text        :  itemTextRole

            onSigImageClicked: toggleExpandState()

            onReleased:
            {
                cppPhoneApp.qmlLog("idLabelWithDropDownImageDelegate - index: " + index)
                toggleExpandState()
            }

            function toggleExpandState() {
                cppPhoneApp.qmlLog("toggleExpandState - index: "+ itemId)

                //Dropdown collapsed state
                if (idPhoneSetupMain.prCurrentExpandedIndex === itemId)
                {
                    idPhoneSetupMain.prCurrentExpandedIndex = -1

                    if(PhoneEnum.PHONE_SETUP_SMS_ALERT_NOTIFICATION === itemId)
                    {
                        cppPhoneAdaptor.phoneSetupListModel.collapseSmsAlertNotification()
                    }
                    else if(PhoneEnum.PHONE_SETUP_CONFIGURE_AUTO_SMS === itemId)
                    {
                        cppPhoneAdaptor.phoneSetupListModel.collapseConfigAutoSms()
                    }
                    else
                    {
                        //Do Nothing
                        cppPhoneApp.qmlLog("Invalid Option Selected")
                    }
                }

                //Dropdown expand state
                else
                {
                    idPhoneSetupMain.prCurrentExpandedIndex = itemId

                    idPhoneSetupMain.prConfigureSMSExpandedIndex = -1

                    if(PhoneEnum.PHONE_SETUP_SMS_ALERT_NOTIFICATION === itemId)
                    {
                        cppPhoneAdaptor.phoneSetupListModel.expandSmsAlertNotification()
                    }
                    else if(PhoneEnum.PHONE_SETUP_CONFIGURE_AUTO_SMS === itemId)
                    {
                        cppPhoneAdaptor.phoneSetupListModel.expandConfigAutoSms()

                    }
                    else
                    {
                        //Do Nothing
                        cppPhoneApp.qmlLog("Invalid option selected")
                    }

                    idGenericList.idList.positionViewAtIndex(index, ListView.Beginning)
                }
            }

        }


        ListItemSeparator
        {
            id: idCheckboxItemSeparator
        }

    }

    //Handling RRE HK for Dropdown Delegate
    Connections
    {
        target: cppHardkeyAdaptor
        onSigRotaryPressed:
        {
            if(iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED
                    || iKeyState === HardkeyEnum.HKEY_STATE_RELEASED)
            {
                if(idGenericList.idList.currentIndex === index)
                {
                    idDropDown.toggleExpandState()
                    /**
                          As per the last change we had to use rotary twice to go to the next item . 1st Rotary action will active the
                          RREIndex to the current Top Item and then 2nd rotary to move to the next Item. But now whenever the item will
                          expand, the RREIndex will still be on the currentIndex and in one rotary we will have next Item.
                     **/
                    idGenericList.prRREIndex = idGenericList.idList.currentIndex
                }
                else
                {
                    //Do Nothing
                    cppPhoneApp.qmlLog("Invalid option selected")
                }
            }
            else
            {
                //Do Nothing
                cppPhoneApp.qmlLog("Not in Released/LongReleased HardKey State")
            }
        }
    }
}
