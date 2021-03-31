import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.setupenums 1.0
import com.harman.qml.powerenums 1.0
import com.harman.qml.hardkeyenum 1.0
import "../../Common/"

Item {

    id: idLabelWithDropDownImageDelegate

    width: idLightingSetupList.width
    height: idLightingSetupList.prItemHeight

    Column {
        LabelWithClickableImage {
            id: idDropDown
            height      : idLightingSetupList.prItemHeight - idSeparator.height
            width       : idLightingSetupList.idList.width
            text        : lightingSetupModel.listItemNameRole
            prDefaultImage : (cppSetupAdaptor.expandedApproachLampsItemIndex === lightingSetupModel.index) ?
                                 "qrc:/image/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_n.png" :
                                 "qrc:/image/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_n.png"
            prPressedImage : (cppSetupAdaptor.expandedApproachLampsItemIndex === lightingSetupModel.index) ?
                                 "qrc:/image/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_nf.png" :
                                 "qrc:/image/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_nf.png"
            onSigImageClicked: {
                cppSetupAdaptor.toggleLightingSetupExpandState(lightingSetupModel.index, lightingSetupModel.listItemIdRole)
                idLightingSetupList.idList.positionViewAtIndex(lightingSetupModel.index, ListView.Beginning)
            }
            onReleased  : {
                cppSetupApp.qmlLog("idDelegateDropDown - index: "+ lightingSetupModel.index)
                cppSetupAdaptor.toggleLightingSetupExpandState(lightingSetupModel.index, lightingSetupModel.listItemIdRole)
                idLightingSetupList.idList.positionViewAtIndex(lightingSetupModel.index, ListView.Beginning)
            }
        }

        ListItemSeparator {
            id:idSeparator
        }
    }

    Connections {
        target: cppVehicleAdaptor

        /* If user is inside the lighting screen and the Bcm Ucs state is changed to false, then switch screen to vehicle setup */
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

        /* If user is inside the lighting screen and the approach lamps presence is changed to false, then switch screen to vehicle setup */
        onSigAppraochLampsPresenceChanged: {
            if( (false === cppVehicleAdaptor.appraochLampsPresence) )
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
            if(iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED || iKeyState === HardkeyEnum.HKEY_STATE_RELEASED)
            {
                if(idLightingSetupList.idList.currentIndex === index)
                {
                    cppSetupAdaptor.toggleLightingSetupExpandState(lightingSetupModel.index, lightingSetupModel.listItemIdRole)
                    idLightingSetupList.idList.positionViewAtIndex(lightingSetupModel.index, ListView.Beginning)
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
