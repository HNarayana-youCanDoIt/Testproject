import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0
import "../Common"

BaseUI {
    //id: idMainWindow
    width: 800
    height: 480
    /////////////////////////////////////////////////////////////////////////////////
    /*
     * Text used to show title text for shortcuts home screen
     */
    HBTitleWithBackButton {
        prTitle: qsTr("TEXT_HOME_SHORTCUT_HEADER") + cppThemeMgr.languageChanged
    }
    /////////////////////////////////////////////////////////////////////////////////
    /*
     * ButtonGroup used combine Shortcuts List View radio buttons in a group
     */
    ButtonGroup {
        id: idHomeRadioButtonGroup
    }

    /*
     * Component used to create Shortcuts List View item layout
     */
    Component {
        id: idUpdateShortcutsDelegate
        Column {
            LabelWithRadioButton {
                id: idLabelWithRadioButton
                width: idUpdateShortcutsListView.width
                text: cppHomeAdaptor.homeShortcutsList[model.shortcutIdRole].text
                height: idUpdateShortcutsListView.prItemHeight - idSeparator.height
                prActionOnTimeOut: true

                radioButtonGroup: idHomeRadioButtonGroup

                onSigRadioBtnCheckedChanged: {
                    cppHomeAdaptor.invUpdateShortcut(model.shortcutIdRole)
                }

                onSigRadioBtnSelectionCompleted: {
                    cppHomeApplication.raiseSMEvent("BackToHome", "")
                }
            }
            ListItemSeparator {
                id: idSeparator
            }

            Connections{
                target: cppHardkeyAdaptor
                onSigRotaryPressed: {
                    cppHomeApplication.qmlLog("ScnHomeUpdateShortcuts.qml : right rotary pressed")

                    if(HardkeyEnum.KEYCODEHK_MENUROTARY === iKeyCode
                       && (HardkeyEnum.HKEY_STATE_RELEASED === iKeyState
                       || HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState)){
                        if(idUpdateShortcutsListView.idList.currentIndex === index){
                            idLabelWithRadioButton.setRRESelection()
                        }
                    }
                }
            }
        }
    }

    /*
     * GenericList used to create Shortcuts List View
     */
    GenericList {
        id: idUpdateShortcutsListView
        idList.delegate: idUpdateShortcutsDelegate
        idList.model: cppHomeAdaptor.unusedShortcuts
    }
    /////////////////////////////////////////////////////////////////////////////////
}
