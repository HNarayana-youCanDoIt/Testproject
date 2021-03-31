import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.setupenums 1.0
import com.harman.qml.parkassistenum 1.0
import "../../Common/"
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0

Item {

    id: idPAToneDelegate
    width: idParkAssistList.width
    height: idParkAssistList.prItemHeight

    Column {
        LabelWithRadioButton {
            id: idLabelWithRadioButton
            height      : idParkAssistList.prItemHeight - idSeparator.height
            width       : idParkAssistList.idList.width

            text        : parkAssistModel.listItemNameRole
            radioButtonGroup: (SetupEnums.SETUP_OPTION_PARK_ASSIST_TONE_TYPE === parkAssistModel.listItemIndexRole)  ? idPAToneRadioBtnGroup : idPADelayTimerRadioBtnGroup
            radioButtonChecked : parkAssistModel.listItemCheckedRole

            onSigRadioBtnCheckedChanged  : {
                cppSetupApp.qmlLog(" idPAToneDelegate - listItemIdRole " + parkAssistModel.listItemIdRole + " listItemIndexRole " + parkAssistModel.listItemIndexRole)
                apiCall()
            }

            /*Note: Here we are calling this method to make call to service method to set park assist tone type or park assist delay timer */
            function apiCall()
            {
                cppSetupApp.qmlLog(" ApiCall : parkAssistModel.listItemIndexRole : " + parkAssistModel.listItemIndexRole + " parkAssistModel.listItemIdRole " + parkAssistModel.listItemIdRole )
                if(SetupEnums.SETUP_OPTION_PARK_ASSIST_TONE_TYPE === parkAssistModel.listItemIndexRole)
                {
                    cppParkAssistAdaptor.setParkAssistRearToneAttribute(parkAssistModel.listItemIdRole)
                }
                else if(SetupEnums.SETUP_OPTION_PARK_ASSIST_DELAY_TIMER === parkAssistModel.listItemIndexRole)
                {
                    cppParkAssistAdaptor.setParkAssistDelayTimerAttribute(parkAssistModel.listItemIdRole)
                }
                else
                {
                    cppSetupApp.qmlLog(" Invalid Index " + parkAssistModel.listItemIdRole )
                }
            }
        }

        ListItemSeparator {
            id:idSeparator
        }
    }

    Connections
    {
        target: cppHardkeyAdaptor
        onSigRotaryPressed:
        {
            if(iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED
                    || iKeyState === HardkeyEnum.HKEY_STATE_RELEASED)
            {
                if(idParkAssistList.idList.currentIndex === index)
                {
                    idLabelWithRadioButton.setRRESelection()
                }
            }

            else
            {
                //Do Nothing
                cppSetupApp.qmlLog("Not in Released/LongReleased HardKey State")
            }
        }
    }
}
