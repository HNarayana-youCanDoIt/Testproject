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
            prDefaultImage : (idLightingSetup.prCurrentExpandedIndex === lightingSetupModel.index) ?
                                 "qrc:/image/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_n.png" :
                                 "qrc:/image/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_n.png"
            prPressedImage : (idLightingSetup.prCurrentExpandedIndex === lightingSetupModel.index) ?
                                 "qrc:/image/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_nf.png" :
                                 "qrc:/image/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_nf.png"
            onSigImageClicked: {
                cppSetupAdaptor.toggleApproachLampsExpandState(lightingSetupModel.index, lightingSetupModel.listItemIdRole)
                idLightingSetupList.idList.positionViewAtIndex(parkAssistModel.index, ListView.Beginning)
            }
            onReleased  : {
                cppSetupApp.qmlLog("idDelegateDropDown - index: "+ lightingSetupModel.index)
                cppSetupAdaptor.toggleApproachLampsExpandState(lightingSetupModel.index, lightingSetupModel.listItemIdRole)
                idLightingSetupList.idList.positionViewAtIndex(parkAssistModel.index, ListView.Beginning)
            }
        }

        ListItemSeparator {
            id:idSeparator
        }
    }
}
