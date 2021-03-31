import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.setupenums 1.0
import com.harman.qml.powerenums 1.0
import com.harman.qml.hardkeyenum 1.0
import "../../Common/"

Item {

    id: idBtnListWithLabelDelegate

    width: idLightingSetupList.width
    height: idLightingSetupList.prItemHeight

    Column {        
        HBButtonListItem {
            id: idLabelComp
            width: idLightingSetupList.idList.width
            height: idLightingSetupList.prItemHeight - idSeparator.height
            text: lightingSetupModel.listItemNameRole

            onReleased:{
                cppSetupApp.qmlLog("lightingSetupScreen.qml - index: "+ lightingSetupModel.listItemIdRole)
                cppSetupApp.raiseSMEvent("LightingSetup", lightingSetupModel.listItemIdRole)
            }
        }

        ListItemSeparator {
            id:idSeparator
        }
    }

    Connections {
        target: cppVehicleAdaptor

        /* If user is inside the Lighting setup and the BCM presence is changed to false, then switch screen to main setup */
        onSigBCMPresenceChanged: {
            if( (false === cppVehicleAdaptor.bCmPresence) )
            {
                cppSetupApp.switchScreenToMainSetup()
            }
            else
            {
                //Do nothing
            }
        }

        /* If user is inside the lighting setup and the BCM presence is changed to false,
           ambient light presence is also false, then switch screen to main setup */
        onSigAmbientLightModeIlluOnHuChanged: {
            if( (false === cppVehicleAdaptor.bCmPresence) && (false === cppVehicleAdaptor.ambientLightModeIlluOnHu) )
            {
                cppSetupApp.switchScreenToMainSetup()
            }
            else if( (true === cppVehicleAdaptor.bCmPresence) && (false === cppParkAssistAdaptor.ambientLightModeIlluOnHu) )
            {
                cppSetupApp.jumpToPreviousScreen()
            }
            else
            {
                //Do nothing
            }
        }

        /* If user is inside the lighting setup and the BCM Ucs state is changed to false, then switch screen to vehicle setup */
        onSigBcmUcsStateChanged: {
            if( (false === cppVehicleAdaptor.bcmUcsState) )
            {
                cppSetupApp.switchScreenToVehicleSetup()
            }
            else
            {
                //Do nothing
            }
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
                    cppSetupApp.raiseSMEvent("LightingSetup", lightingSetupModel.listItemIdRole)
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

    Component.onCompleted: {
        console.log(" cppVehicleAdaptor.bcmPresence ", cppVehicleAdaptor.bCmPresence,
                    " cppVehicleAdaptor.ambientLightModeIlluOnHu ", cppVehicleAdaptor.ambientLightModeIlluOnHu,
                     " cppVehicleAdaptor.bcmUcsState ", cppVehicleAdaptor.bcmUcsState)
    }
}
