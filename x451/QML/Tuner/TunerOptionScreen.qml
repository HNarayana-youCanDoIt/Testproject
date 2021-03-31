import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.tunerenums 1.0
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0
import "qrc:/QML/Common"

BaseUI {
    id: idTunerOption
    anchors.fill: parent
    /* Text to hold Title of the screen */
    HBTitleWithBackButton {
        id: idTitle
        prTitle: qsTr("TEXT_TUNER_BROWSE") + cppThemeMgr.languageChanged
    }

    // ToDo : There is no need of list model and list veiw. We can create two static item for this.
    /* Tuner Option screen model data */
    ListModel {
        id: idTunerOptionModel
        ListElement {
            elementName: qsTr("TEXT_TUNER_BROWSE_AUTO_STORE")
            enableOption: true
        }
        ListElement {
            elementName: qsTr("TEXT_TUNER_BROWSE_SCAN")
            enableOption: true
        }
    }

    /* Tuner option screen delegate, this component contains label and a listItemSeparator image */
    Component {
        id: idDelegate
        Column {
            enabled: enableOption
            ListItemWithIconComp {
                id: idTunerOptionDelegate
                height: 68
                width: idTunerOptionList.idList.width
                prText: elementName
                prEnabledTextFontType: ThemeMgr.FONTTYPE_T35_C3
                prDisabledTextFontType: ThemeMgr.FONTTYPE_T35_C3_DISABLED
                prTextVerticalCenter: prIconVerticalCenter

                prDefaultIconImage: (index === TunerEnums.TUNER_OPTION_SCAN_INDEX) ? "qrc:/image/Tuner/Tun_Ico_Scanning_7in_n/Gen_Ico_RadioScan_n.png" : "qrc:/image/Tuner/Tun_Ico_AutoStore_7in_n/Gen_Ico_RadioAutoStore_n.png"
                prPressedIconImage: (index === TunerEnums.TUNER_OPTION_SCAN_INDEX) ? "qrc:/image/Tuner/Tun_Ico_Scanning_7in_n/Gen_Ico_RadioScan_n.png" : "qrc:/image/Tuner/Tun_Ico_AutoStore_7in_n/Gen_Ico_RadioAutoStore_n.png"
                prDisabledIconImage: (index === TunerEnums.TUNER_OPTION_SCAN_INDEX) ? "qrc:/image/Tuner/Tun_Ico_Scanning_7in_n/Gen_Ico_RadioScan_nd.png" : "qrc:/image/Tuner/Tun_Ico_AutoStore_7in_n/Gen_Ico_RadioAutoStore_nd.png"

                isIconOnLeft: true

                prIconLeftMargin: 0

                prTextWidth: 356
                prTextHeight: 25
                prTextLeftMargin: 0
                button.pressedImageURL: "qrc:/image/Gen_Gfx_ListCursor_7in_n-assets/Gen_Gfx_ListCursor_n.png"
                button.onReleased: {
                    cppTunerApp.qmlLog("tunerOptionScreen.qml, index: " + index)
                    if (TunerEnums.TUNER_OPTION_SCAN_INDEX === index) {
                        cppTunerAdaptor.requestScan()
                    } else if (TunerEnums.TUNER_OPTION_AUTOSTORE_INDEX === index) {
                        cppTunerAdaptor.requestAutostore()
                    } else {
                        cppTunerApp.qmlLog("tunerOptionScreen.qml, invalid index")
                    }
                }
            }
            ListItemSeparator {
            }
        }
    }
    /* Tuner option screen list is populated using GenericList and TunerOptionModel */
    GenericList {
        id: idTunerOptionList
        idList.model: idTunerOptionModel
        idList.delegate: idDelegate
    }

    Connections{
        target: cppHardkeyAdaptor
        onSigRotaryPressed: {
            cppTunerApp.qmlLog("TunerOptionScreen.qml : right rotary pressed")

            if(HardkeyEnum.KEYCODEHK_MENUROTARY === iKeyCode
               && (HardkeyEnum.HKEY_STATE_RELEASED === iKeyState
               || HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState)){
                if(idTunerOptionList.idList.currentIndex === TunerEnums.TUNER_OPTION_SCAN_INDEX){
                    cppTunerAdaptor.requestScan()
                }
                else if(idTunerOptionList.idList.currentIndex === TunerEnums.TUNER_OPTION_AUTOSTORE_INDEX){
                    cppTunerAdaptor.requestAutostore()
                }
            }
        }
    }
}
