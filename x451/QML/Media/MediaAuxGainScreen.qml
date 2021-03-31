import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common/"
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0

BaseUI {
    id: idAuxInGain

    HBTitleWithBackButton{
        prTitle: qsTr("Aux Gain") + cppThemeMgr.languageChanged
    }

    /* Aux In Gain screen contains list of radio buttons,
        to achieve the radio button functionality(only one should be checked at a time) ButtonGroup is used */    
    ButtonGroup {
        id: idAuxInGainRadioButtonGroup
    }

    /* Aux In Gain screen delegate, this component contains label along with a radiobutton and a listItemSeparator image */
    Component {
        id: idDelegate

        Column {
            LabelWithRadioButton {
                id: idLabelWithRadio
                height: 68
                width: idAuxInGainList.idList.width
                radioButtonGroup: idAuxInGainRadioButtonGroup
                text: listItemNameRole
                radioButtonChecked : listItemCheckedRole
                onSigRadioBtnCheckedChanged: {
                    cppUIBase.qmlLog("AuXGainScreen.qml::onSigRadioBtnCheckedChanged - API Call, index: "+ index + listItemNameRole)
                    cppAudioAdaptor.setAuxInGainAttribute(index)
                }
            }

            Connections {
                target: cppHardkeyAdaptor
                onSigRotaryPressed: {
                    cppMediaApp.qmlLog("GenericList - MediaAuxGainScreen: onRotaryUpdate  iKeyState : " + iKeyState + " iKeyCode : " + iKeyCode)
                    if(HardkeyEnum.KEYCODEHK_MENUROTARY === iKeyCode)
                    {
                        if(HardkeyEnum.HKEY_STATE_RELEASED === iKeyState || HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState)
                        {
                            if(idAuxInGainList.idList.currentIndex === index)
                            {
                                cppUIBase.qmlLog("MediaAuxGainScreen::onRotaryUpdate - API Call, index: "+ index + listItemNameRole)
                                idLabelWithRadio.setRRESelection()
                            }
                        }
                        else
                        {
                            cppMediaApp.qmlLog("MediaAuxGainScreen::onRotaryUpdate - key state invalid, iKeyState : " + iKeyState)
                        }
                    }
                    else
                    {
                        cppMediaApp.qmlLog("MediaAuxGainScreen::onRotaryUpdate - key code invalid, iKeyCode : " + iKeyCode)
                    }
                }
            }

            ListItemSeparator
            {
                id: idSeparator
            }
        }
    }

    /* List of aux in gain options is populated using GenericList and AuxInGainModel */
    GenericList {
        id: idAuxInGainList
        idList.model: MediaAdaptor.mediaAuxInGainModel
        idList.delegate: idDelegate
    }
}
