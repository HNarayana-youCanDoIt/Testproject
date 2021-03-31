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
                //FixME: Call service method to set
                cppSetupApp.qmlLog("lightingSetupScreen.qml - index: "+ lightingSetupModel.listItemIdRole)
                cppSetupApp.raiseSMEvent("LightingSetup", lightingSetupModel.listItemIdRole)
            }
        }

        //FixMe: Need to give proper list item separator image as per x451
        ListItemSeparator {
            id:idSeparator
        }
    }
}
