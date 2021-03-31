import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0

BaseUI {
    id: idScnConfigureFavKey
    anchors.fill: parent
    /* Text to hold Title of the screen */
    HBTitleWithBackButton {
        id: idTitle
        prTitle: qsTr("TEXT_CONFIGURE_FAVORITES_TITLE_LABEL") + cppThemeMgr.languageChanged
    }

    /////////////////////////////////////////////////////////////////////////////////
    /*
     * ButtonGroup used combine Shortcuts List View radio buttons in a group
     */
    ButtonGroup {
        id: idFavKeyRadioButtonGroup
    }

    /*
     * Component used to create Shortcuts List View item layout
     */
    Component {
        id: idFavKeyDelegate
        Column {
            LabelWithRadioButton {
                id: idLableWithRadioBtn
                width: idFavKeyListView.width
                height: idFavKeyListView.prItemHeight - idSeparator.height

                text: cppHomeAdaptor.homeShortcutsList[FavHKShortcutId].text
                prActionOnTimeOut: true

                radioButtonGroup: idFavKeyRadioButtonGroup
                radioButtonChecked: (FavHKId === cppHomeAdaptor.eCurrentFavKeyCode) ? true : false

                onSigRadioBtnCheckedChanged: {
                    cppHomeApplication.qmlLog("ScnConfigureFavKey.qml : index clicked : " + FavHKId)
                    cppHomeAdaptor.eCurrentFavKeyCode = FavHKId
                }
                onSigRadioBtnSelectionCompleted: {
                    cppHomeApplication.raiseSMEvent("BackToHome", "")
                }
            }

            Connections {
                target: cppHardkeyAdaptor
                onSigRotaryPressed: {
                    cppHomeApplication.qmlLog("ScnConfigureFavKey.qml: onRotaryUpdate  iKeyState : "
                                          + iKeyState + " iKeyCode : " + iKeyCode)
                    if(HardkeyEnum.KEYCODEHK_MENUROTARY === iKeyCode){
                        if(HardkeyEnum.HKEY_STATE_RELEASED === iKeyState
                                || HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState){
                            if(idFavKeyListView.idList.currentIndex === index){
                                cppHomeApplication.qmlLog("index clicked : " + FavHKId)
                                idLableWithRadioBtn.setRRESelection()
                            }
                        }
                        else{
                            cppHomeApplication.qmlLog("ScnConfigureFavKey.qml : key state invalid, iKeyState : " + iKeyState)
                        }
                    }
                    else{
                        cppHomeApplication.qmlLog("ScnConfigureFavKey.qml : key code invalid, iKeyCode : " + iKeyCode)
                    }
                }
            }
            ListItemSeparator {
                id: idSeparator
            }
        }
    }

    /*
     * GenericList used to create configure favorite hardkey List View
     */
    GenericList {
        id: idFavKeyListView
        idList.delegate: idFavKeyDelegate
        idList.model: cppHomeAdaptor.objFavKeyListModel
    }
}
