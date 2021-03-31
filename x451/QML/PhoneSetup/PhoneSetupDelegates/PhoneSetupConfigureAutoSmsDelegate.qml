import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../../Common"
import com.harman.qml.hardkeyenum 1.0

/** Label with Radio Button and Dropdown Delegate ***
  * Delegate containing Label, dropdown icon and a radio button. This Delegate will be generally
  * used for Configure Auto SMS option in PhoneSetup.
  */

Item
{
    id: idConfigureAutoSmsDelegate
    width: idGenericList.width
    height: idGenericList.prItemHeight

    /*  Configure Auto SMS screen delegate, this component contains label along with a radiobutton and a
     *  listItemSeparator image
    */
    Column {
        LabelWithRadioButtonAndImage {
            id: idLabelWithRadioImageAndImage
            width: idGenericList.width
            height: idGenericList.prItemHeight - idCheckboxItemSeparator.height
            text:  itemTextRole
            radioButtonGroup: idSMSConfigureAutoRadioButtonGroup
            radioButtonChecked :   itemCheckedRole
            prDefaultImage : (idPhoneSetupMain.prConfigureSMSExpandedIndex === itemId)
                             ? "qrc:/image/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_n.png"
                             : "qrc:/image/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_n.png"
            prPressedImage : (idPhoneSetupMain.prConfigureSMSExpandedIndex === itemId)
                             ? "qrc:/image/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_nf.png"
                             : "qrc:/image/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_nf.png"
            onSigRadioBtnCheckedChanged: {
                cppPhoneApp.qmlLog("Configure Auto Sms - index: "+ itemId +" itemTextRole: " +
                                   itemTextRole + " itemCheckedRole: " + itemCheckedRole)
                cppPhoneAdaptor.invUpdateConfigureAutoSms(itemId)
                itemCheckedRole = true;
            }

            onSigImageClicked: toggleExpandState()

            function toggleExpandState() {
                cppPhoneApp.qmlLog("ConfigureAutoSMSScreen.qml : toggleExpandState - itemId: " + itemId)
                if (idPhoneSetupMain.prConfigureSMSExpandedIndex === itemId)
                {
                    idPhoneSetupMain.prConfigureSMSExpandedIndex = -1
                    cppPhoneAdaptor.phoneSetupListModel.collapseConfigAutoSmsEdit(itemId)
                }
                else
                {
                    idPhoneSetupMain.prConfigureSMSExpandedIndex = itemId
                    cppPhoneAdaptor.phoneSetupListModel.expandConfigAutoSmsEdit(itemId)
                    idGenericList.idList.positionViewAtIndex(index, ListView.Beginning)
                }
            }
        }


        ListItemSeparator
        {
            id: idCheckboxItemSeparator
        }
    }

    //Handling RRE HK for Configure Auto Sms items
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
                    idLabelWithRadioImageAndImage.radioButtonChecked = true
                }
                else
                {
                    //Do Nothing
                    cppPhoneApp.qmlLog("Invalid Index Selected")
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

