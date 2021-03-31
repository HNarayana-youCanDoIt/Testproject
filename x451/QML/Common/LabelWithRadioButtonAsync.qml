/* This component contains a label and radio button. */
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import com.harman.qml.hardkeyenum 1.0

/** Delegate of Button List Item with Label and Radio Button  **/

HBButtonListItem {
    /* Radio button group to be provided */
    property var radioButtonGroup: idRadioButton.ButtonGroup.group

    /* Alias provided for radio button control */
    property alias radioButtonChecked: idRadioButton.checked

    /* On click of radio button, this signal gets emitted */
    signal sigRadioBtnCheckedChanged()

    /* Radio button control, which provides default radio button functionality */
    RadioButton {
        id: idRadioButton
        height: 72
        width: 72
        ButtonGroup.group: radioButtonGroup
        enabled: false

        anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
            rightMargin: 30
        }

        indicator: Image {
            id: idRadioCustomImage
            anchors {
                left: parent.left
                verticalCenter: parent.verticalCenter
            }
            source: idRadioButton.checked ? "qrc:/image/Set_Ico_RadioButton_7in_n-assets/Set_Ico_RadioButton_7in_na.png" :
                                            "qrc:/image/Set_Ico_RadioButton_7in_n-assets/Set_Ico_RadioButton_7in_n.png"
        }
    }

    onPressAndHold: {
        if (!radioButtonChecked) {
            sigRadioBtnCheckedChanged()
        }
    }

    onReleased: {
        if (!radioButtonChecked) {
            sigRadioBtnCheckedChanged()
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
                cppEnggApplication.qmlLog("onSigRotaryPressed:: iKeyCode"+ iKeyCode)
                if(idGenericList.idList.currentIndex === index)
                {
                    if (!radioButtonChecked) {
                        sigRadioBtnCheckedChanged()
                    }
                }
            }
        }
    }
}
