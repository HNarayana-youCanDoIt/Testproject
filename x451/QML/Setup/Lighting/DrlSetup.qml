import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.setupenums 1.0
import com.harman.qml.hardkeyenum 1.0
import "../../Common/"

Item {
    id: idDrlSetupDelegate
    width: idLightingSetupList.width
    height: idLightingSetupList.prItemHeight

    Column {
        LabelWithCheckBoxComp {
            id: idLabelWithCheckboxComp
            width: idLightingSetupList.idList.width
            height: (idLightingSetupList.prItemHeight - idSeparator.height)
            text: listItemNameRole
            prCheckBoxChecked: lightingSetupModel.listItemCheckedRole

            onReleased:
            {
                cppSetupApp.qmlLog("DrlSetup.qml - Index: "+ lightingSetupModel.listItemCheckedRole)
                cppVehicleAdaptor.setBcmDrlSelectionAttribute(!prCheckBoxChecked)
            }
        }

        //Handling RRE HK for selecting or deselecting bcm drl option
        Connections
        {
            target: cppHardkeyAdaptor
            onSigRotaryPressed:
            {
                if(iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED || iKeyState === HardkeyEnum.HKEY_STATE_RELEASED)
                {
                    if(idLightingSetupList.idList.currentIndex === index)
                    {
                        cppSetupApp.qmlLog("DrlSetup.qml: onRotaryUpdate: key state is: " + iKeyState)
                        cppVehicleAdaptor.setBcmDrlSelectionAttribute(!idLabelWithCheckboxComp.prCheckBoxChecked)
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

        ListItemSeparator {
            id:idSeparator
        }
    }
}
