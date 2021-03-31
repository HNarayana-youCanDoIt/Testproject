import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../../Common"
import com.harman.qml.hardkeyenum 1.0


Item
{
    id: idLabelWithRadioButtonComponent
    width: idGenericList.width
    height: idGenericList.prItemHeight

    Column{
        LabelWithRadioButton {
            id: idLabelWithRadioBtn
            width: idGenericList.width
            height: idGenericList.prItemHeight - idCheckboxItemSeparator.height
            text        :  itemTextRole
            radioButtonGroup: idSMSAlertRadioButtonGroup
            radioButtonChecked : itemCheckedRole
            onSigRadioBtnCheckedChanged: {
                cppPhoneApp.qmlLog("idSMSAlertInfoDelegate - itemId: "+ itemId +" itemTextRole: " + itemTextRole+"
                                                                    itemCheckedRole: " + itemCheckedRole)
                cppPhoneAdaptor.invUpdateSMSAlertNotification(itemId);
                itemCheckedRole = true
            }
        }
        ListItemSeparator
        {
            id: idCheckboxItemSeparator
        }
    }

    //Handling RRE HK for Sms Alert Notification items
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
                    idLabelWithRadioBtn.setRRESelection()
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
