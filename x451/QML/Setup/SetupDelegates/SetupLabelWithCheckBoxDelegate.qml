import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.setupenums 1.0
import "../../Common/"
import com.harman.qml.hardkeyenum 1.0

    /* CheckBoxDelegate delegate, this component contains label, CheckBox and a listItemSeparator image */
Item {

    id: idLabelWithCheckBoxDelegate
    width: idParkAssistList.width
    height: idParkAssistList.prItemHeight

    Column {        
        LabelWithCheckBoxComp {
            id: idLabelWithCheckboxComp

            height               : idParkAssistList.prItemHeight - idSeparator.height
            width                : idParkAssistList.idList.width
            prCheckBoxRightMargin: 10

            text: parkAssistModel.listItemNameRole
            prCheckBoxChecked: parkAssistModel.listItemCheckedRole

            onReleased: {
                cppSetupApp.qmlLog("ParkAssistScreen.qml - Index: "+ parkAssistModel.index + "prCheckBoxChecked" + parkAssistModel.listItemCheckedRole)
                cppAudioAdaptor.setPdcMixModeStateAttribute(!prCheckBoxChecked)
            }
        }

        ListItemSeparator {
            id:idSeparator
        }
    }

    //Handling RRE HK for selecting or deselecting vehicle auto relock
    Connections
    {
        target: cppHardkeyAdaptor
        onSigRotaryPressed:
        {
            cppSetupApp.qmlLog("ParkAssistScreen.qml: onRotaryUpdate: key state is: " + iKeyState)
            if(iKeyState === HardkeyEnum.HKEY_STATE_RELEASED || iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED)
            {
                if(idParkAssistList.idList.currentIndex === parkAssistModel.index)
                {
                    cppSetupApp.qmlLog("ParkAssistScreen.qml - HBButtonListItem RRE release/longReleae event, itemIndex is: " + parkAssistModel.index)
                    cppAudioAdaptor.setPdcMixModeStateAttribute(!idLabelWithCheckboxComp.prCheckBoxChecked)
                }
            }
        }
    }
}
