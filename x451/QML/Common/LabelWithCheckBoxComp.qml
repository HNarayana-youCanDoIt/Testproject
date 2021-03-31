/* This component contains a label and CheckBox button. */
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

/* Text label which is derived from generic button */
HBButtonListItem {
    /* Right margin of CheckBox button to be provided */
    property int prCheckBoxRightMargin: 0

    /* property provided for checkbox button check control */
    property bool prCheckBoxChecked: false

    /* Path of selected CheckBox button image to be provided */
    property string prCheckBoxBtnCheckedImage: "qrc:/image/Set_Ico_Checkbox_7in_n-assets/Set_Checkbox_na.png"

    /* Path of non-selected/default CheckBox button image to be provided */
    property string prCheckBoxBtnUncheckedImage: "qrc:/image/Set_Ico_Checkbox_7in_n-assets/Set_Checkbox_n.png"

    /* Path of selected disable CheckBox button image to be provided */
    property string prCheckBoxBtnDisableCheckedImage: "qrc:/image/Set_Ico_Checkbox_7in_n-assets/Set_Ico_Checkbox_On_7in_nd.png"

    /* Path of non-selected/default disable CheckBox button image to be provided */
    property string prCheckBoxBtnDisableUncheckedImage: "qrc:/image/Set_Ico_Checkbox_7in_n-assets/Set_Ico_Checkbox_7in_nd.png"

    /* On click of radio button, this signal gets emitted with the corresponding index */
    signal sigCheckBoxCheckedChanged(bool checkBoxstatus)

    /* CheckBox button control, which provides default CheckBox button functionality */
    Image {
        anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
            rightMargin: prCheckBoxRightMargin
        }
        source: (parent.enabled ? (prCheckBoxChecked ? prCheckBoxBtnCheckedImage : prCheckBoxBtnUncheckedImage) : (prCheckBoxChecked ? prCheckBoxBtnDisableCheckedImage : prCheckBoxBtnDisableUncheckedImage))
    }
}

