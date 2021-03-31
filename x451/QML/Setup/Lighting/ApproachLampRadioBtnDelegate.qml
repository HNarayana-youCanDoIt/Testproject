import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.setupenums 1.0
import com.harman.qml.powerenums 1.0
import com.harman.qml.hardkeyenum 1.0
import "../../Common/"

/* Approach lamps delegate, this component contains label along with a radiobutton and a listItemSeparator image */
Item {

    id: idApproachLampsDelegate
    width: idLightingSetupList.width
    height: idLightingSetupList.prItemHeight

    Column {        
        LabelWithRadioButton {
            id:idLabelWithRadioButton
            height      : idLightingSetupList.prItemHeight /*- idSeparator.height*/
            width       : idLightingSetupList.idList.width
            text        : listItemNameRole
            radioButtonGroup: idApproachLampsRadioButtonGroup
            radioButtonChecked : lightingSetupModel.listItemCheckedRole

            onSigRadioBtnCheckedChanged: {
                cppSetupApp.qmlLog("idApproachLampsDelegate - index: "+ lightingSetupModel.index +
                                   "listItemValueRole " + lightingSetupModel.listItemIdRole)
                //Call approach lamps API
                cppVehicleAdaptor.setApproachLampsAttribute(lightingSetupModel.listItemIdRole)
            }
        }

        ListItemSeparator {
            id:idSeparator
        }
    }

    //Handling RRE HK for Dropdown Delegate
    Connections
    {
        target: cppHardkeyAdaptor
        onSigRotaryPressed:
        {
            if((iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED) || (iKeyState === HardkeyEnum.HKEY_STATE_RELEASED))
            {
                if(idLightingSetupList.idList.currentIndex === index)
                {
                    idLabelWithRadioButton.setRRESelection()
                }
                else
                {
                    //Do Nothing
                    cppSetupApp.qmlLog(" Invalid Option Selected ")
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
