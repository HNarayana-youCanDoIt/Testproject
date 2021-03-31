import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0
import "../Common/"

BaseUI {
    id: idGeneralSetup

    /* TitleLabel of General setup screen */
    HBTitleWithBackButton {
        prTitle: qsTr("TEXT_SETTINGS_GENERAL_SETUP") + cppThemeMgr.languageChanged
    }

    /* General setup screen delegate, this component contains label and a listItemSeparator image */
    Component {
        id: idLabelDelegate

        Column {
            enabled: listItemEnableRole
            HBButtonListItem {
                id          : idGeneralSetupListComp
                height      : idGeneralSetupList.prItemHeight - idSeparator.height
                width       : idGeneralSetupList.idList.width
                text        : listItemNameRole
                onReleased  :{
                    cppSetupApp.qmlLog("GeneralSetupScreen.qml,  GeneralSetupItem: onReleased: model index: "+ index)
                    cppSetupApp.raiseSMEvent("GeneralSetup", index)
                }
            }

            Connections
            {
                target: cppHardkeyAdaptor

                onSigRotaryPressed :
                {
                    if((HardkeyEnum.KEYCODEHK_MENUROTARY === iKeyCode) &&
                            (HardkeyEnum.HKEY_STATE_RELEASED === iKeyState ||
                             HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState))
                    {
                        if(idGeneralSetupList.idList.currentIndex === index)
                        {
                           /**
                            * raiseSMEvent function from the SetupApplication takes the id of the list item
                            * and carries it forward to the next state (if present)according to the model of the screen
                            **/
                            cppSetupApp.qmlLog("GeneralSetupScreen.qml,  GeneralSetupItem: onSigRotaryPressed : model index: "+ index)
                            cppSetupApp.raiseSMEvent("GeneralSetup", index)
                        }

                    }

                }
            }
            ListItemSeparator {
                id:idSeparator
            }
        }

    }

    /* General setup screen list is populated using GenericList and GeneralSetupModel */
    GenericList {
        id: idGeneralSetupList
        idList.model: cppSetupAdaptor.currentModel
        idList.delegate: idLabelDelegate
    }
}
