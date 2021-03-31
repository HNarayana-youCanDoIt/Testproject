import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../../Common"
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.setupenums 1.0

Item{
    width: idGenericList.width
    height: idGenericList.prItemHeight

    Column {
        LabelWithImageAndRadioButtonOnRight {
            id: idLabelWithRadioImageAndImage
            width: idGenericList.width
            height: idGenericList.prItemHeight - idCheckboxItemSeparator.height
            text:  itemTextRole
            radioButtonGroup: idThemesRadioButtonGroup
            radioButtonChecked : itemCheckedRole
            prEnableColorOverlayForLeftImage: true
            prOverlayColor: cppThemeMgr.getAllThemeColors()[itemId]
            enabled: itemEnabledRole


            onSigRadioBtnCheckedChanged: {
                cppSetupAdaptor.invApplyThemeColor(itemId)
            }

            onSigImageClicked: {
                cppSetupAdaptor.invApplyThemeColor(itemId)
            }
        }

        ListItemSeparator{
            id: idCheckboxItemSeparator
        }
    }

    Connections{
        target: cppHardkeyAdaptor
        onSigRotaryPressed: {
            cppSetupApp.qmlLog("ThemesRadioButtonDelegate.qml : right rotary pressed")

            if(HardkeyEnum.KEYCODEHK_MENUROTARY === iKeyCode
               && (HardkeyEnum.HKEY_STATE_RELEASED === iKeyState
               || HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState)){
                if(idGenericList.idList.currentIndex === index){
                    idLabelWithRadioImageAndImage.radioButtonChecked = true
                }
            }
        }
    }
}
