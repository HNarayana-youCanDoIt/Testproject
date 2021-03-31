import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.setupenums 1.0
import com.harman.qml.hardkeyenum 1.0
import "../../Common/"

Item {

    id: idBtnListWithLabelDelegate

    width: idDriveNextSetupList.width
    height: idDriveNextSetupList.prItemHeight

    Column {
        HBButtonListItem {
            id: idLabelComp
            width: idDriveNextSetupList.idList.width
            height: idDriveNextSetupList.prItemHeight - idSeparator.height
            text: driveNextSetupModel.listItemNameRole

            onReleased: {
                cppSetupApp.qmlLog("DriveNextLabelDelegate.qml - index: "+ driveNextSetupModel.listItemIdRole)
                cppSetupApp.raiseSMEvent("DriveNextSetup", driveNextSetupModel.listItemIdRole)
            }
        }

        ListItemSeparator {
            id:idSeparator
        }
    }

    //Handling RRE HK for Dropdown Delegate
    Connections {
        target: cppHardkeyAdaptor
        onSigRotaryPressed: {
            if((iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED) || (iKeyState === HardkeyEnum.HKEY_STATE_RELEASED)) {
                if(idDriveNextSetupList.idList.currentIndex === index) {
                    cppSetupApp.raiseSMEvent("DriveNextSetup", driveNextSetupModel.listItemIdRole)
                } else {
                    //Do Nothing
                    cppSetupApp.qmlLog(" Invalid Option Selected ")
                }
            } else {
                //Do Nothing
                cppSetupApp.qmlLog("Not in Released/LongReleased HardKey State")
            }
        }
    }
}
