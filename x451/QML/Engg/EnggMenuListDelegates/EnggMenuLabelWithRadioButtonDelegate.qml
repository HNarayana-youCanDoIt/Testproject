/* This component contains a label and radio button. */
import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.hardkeyenum 1.0
import "../../Common"

/** Delegate of Button List Item with Label and CheckBox  **/
Item {
    id: idEnggMenuLabelWithRadioButtonDelegate

    width: idGenericList.idList.width
    height: idGenericList.prItemHeight

    Column {
        /* Text label which is derived from generic button */
        LabelWithRadioButtonAsync {
            id: idLabelWithRadioButtonAsync

            width: idGenericList.idList.width
            height: (idGenericList.prItemHeight - idSeparator.height)

            text: enggMenuItemMainTextRole
            radioButtonChecked: enggMenuItemStatusRole

            radioButtonGroup: idEnggMenuRadioButtonGroup

            onSigRadioBtnCheckedChanged: {
                cppEnggApplication.qmlLog("sigRadioBtnCheckedChanged:: index "+ index)
                cppEnggAdaptor.invToggleEnggRadioButton(true, index)
            }
        }

        ListItemSeparator {
            id:idSeparator
        }
    }
}

/* USAGE EXAMPLE

 Create button group as below
 ButtonGroup {
     id: idEnggMenuRadioButtonGroup
 }

 Create scroll list delegate using EnggMenuLabelWithRadioButtonDelegate as component

 */
