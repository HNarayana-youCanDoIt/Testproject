import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.setupenums 1.0
import "../../Common/"
import com.harman.qml.hardkeyenum 1.0

    /* Drop down delegate, this component contains label along with a clickable image, listItemSeparator image and Loader for loading SubItemModel's */
Item {

    id: idLabelWithDropDownImageDelegate
    width: idParkAssistList.width
    height: idParkAssistList.prItemHeight

    Column {
        LabelWithClickableImage {
            id: idDropDown

            height      : idParkAssistList.prItemHeight - idSeparator.height
            width       : idParkAssistList.idList.width

            text        : parkAssistModel.listItemNameRole

            prDefaultImage : (cppSetupAdaptor.expandedParkAssistItemIndex === parkAssistModel.listItemIdRole) ?
                                 "qrc:/image/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_n.png" :
                                 "qrc:/image/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_n.png"
            prPressedImage : (cppSetupAdaptor.expandedParkAssistItemIndex === parkAssistModel.listItemIdRole) ?
                                 "qrc:/image/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_nf.png" :
                                 "qrc:/image/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_nf.png"

            onSigImageClicked:{
                cppSetupAdaptor.toggleExpandState(parkAssistModel.index, parkAssistModel.listItemIdRole)
                idParkAssistList.idList.positionViewAtIndex(parkAssistModel.index, ListView.Beginning)
            }

            onReleased  : {
                cppSetupApp.qmlLog(" SetupLabelWithDropDownDelegate.qml - index: "+ parkAssistModel.index +
                                   "parkAssistModel.listItemIdRole" + parkAssistModel.listItemIdRole)
                cppSetupAdaptor.toggleExpandState(parkAssistModel.index, parkAssistModel.listItemIdRole)
                idParkAssistList.idList.positionViewAtIndex(parkAssistModel.index, ListView.Beginning)
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
            if(iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED || iKeyState === HardkeyEnum.HKEY_STATE_RELEASED)
            {
                if(idParkAssistList.idList.currentIndex === index)
                {
                    cppSetupAdaptor.toggleExpandState(parkAssistModel.index, parkAssistModel.listItemIdRole)
                    idParkAssistList.idList.positionViewAtIndex(parkAssistModel.index, ListView.Beginning)
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
