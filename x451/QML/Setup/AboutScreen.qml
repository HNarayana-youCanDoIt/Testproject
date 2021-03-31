import QtQuick 2.7
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0
import "../Common"

BaseUI {
    id: idAboutScreen

    /* Title of About screen */
    HBTitleWithBackButton {
        prTitle: qsTr("TEXT_SETTINGS_ABOUT_MENU") + cppThemeMgr.languageChanged
    }


    HBText {
        text: qsTr("Open Source License Disclosure") + cppThemeMgr.languageChanged
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        anchors
        {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 120
        }
    }

    Component
    {
        id: idScrollableTextComponent
        Item
        {
            width: 488
            height: (idAboutText.contentHeight + 25)

            HBText {
                text: qsTr("Open source software components") + cppThemeMgr.languageChanged
                fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
            }

            /* License Information */
            HBText {
                id: idAboutText
                width: 488
                fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
                anchors {
                    top: parent.top
                    topMargin: 16
                }

                wrapMode: Text.Wrap
                text: qsTr("
Tata 7-inch touch screen radio software includes following components belonging to the following open source projects:
Google Noto Fonts https://www.google.com/get/noto/
Font Name: Noto Sans
Version: 1.04
Copyright information: Noto is a trademark of Google Inc.
All Noto fonts are published under the SIL Open Font License.
Language data and some sample texts are from the Unicode CLDR project.") + cppThemeMgr.languageChanged
            }
        }
    }


    /*
     * GenericList used to create Scrollable Text
     */
    GenericList {

        id:idGenericList

        idList.delegate: idScrollableTextComponent
        idList.model: 1
        prEnableAutoScroll: false
        prScrollBarTopMargin: -10

        prCurrentTopItemIndex: 0
        prRREIndex: 0
        idList.highlight: null //WE do not need any highlight here.

        anchors
        {
            top: parent.top
            topMargin: 160
        }
    }

    Connections {
        target: cppHardkeyAdaptor
        onSigRotaryUpdate: {
            cppPhoneApp.qmlLog("AboutScreen.qml: onRotaryUpdate: KeyState: " +iKeyState)

            if(HardkeyEnum.KEYCODEHK_MENUROTARY_KNOB === iKeyCode){
                if(HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState){
                    idGenericList.scrollbar.decrease()
                }
                else if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState){
                    idGenericList.scrollbar.increase()
                }
            }

        }
    }

}
