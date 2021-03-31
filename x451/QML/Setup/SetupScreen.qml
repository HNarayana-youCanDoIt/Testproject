import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.hardkeyenum 1.0
import "../Common"

BaseUI {
    id: idSetupMain
    //To give focus to active qml
    focus: true

    /* TitleLabel of Setup screen */
    HBTitleWithBackButton {
        prTitle: qsTr("TEXT_SETTINGS_SETUP") + cppThemeMgr.languageChanged
    }

    /* Setup main screen delegate, this component contains label and a listItemSeparator image */
    Component {
        id: idDelegate

        Column {
            enabled: listItemCheckedRole
            HBButtonListItem {
                id: idSetupListComp
                height: idSetupMainList.prItemHeight - idSeparator.height
                width: idSetupMainList.idList.width
                text: listItemNameRole
                onReleased: {
                    cppSetupApp.qmlLog("SetupScreen.qml - index: " + index)
                    cppSetupApp.raiseSMEvent("Setup", listItemIndexRole)
                }
            }
                Connections {
                    target: cppHardkeyAdaptor
                    onSigRotaryPressed: {
                        cppSetupApp.qmlLog(
                                    "GenericList: onRotaryUpdate: "+iKeyState)
                        if((HardkeyEnum.HKEY_STATE_RELEASED === iKeyState ||
                            HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState))
                        {
                            if(idSetupMainList.idList.currentIndex === index)
                            {
                                cppSetupApp.qmlLog("SetupScreen.qml - index: " + index)
                                cppSetupApp.raiseSMEvent("Setup", listItemIndexRole)
                            }
                        }
                    }
                }

            ListItemSeparator {
                id: idSeparator
            }
        }
    }
    /* Setup main list is populated using GenericList and SetupMainModel */
    GenericList {
        id: idSetupMainList
        idList.model: cppSetupAdaptor.currentModel
        idList.delegate: idDelegate
    }
}
