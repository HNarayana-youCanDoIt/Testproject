import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../../Common"
import com.harman.qml.setupenums 1.0

/** Label with Edit Button ***
  * Delegate for Configure Auto SMS items,when user clicks on dropdown of the given item. A Message and an Edit
  * (except first 3) button should be seen to the user.
  */

Item
{
    id: idDropDownContentDelegate
    width: idGenericList.idList.width
    height: (idMessageContentComponent.height + idListItemSeparator.height)

    /*
     *  Message content delegate, this component contains HBText and generic button for Editing the content of message
    */
    Column {

        PhoneSetupMessageContentDelegate{
            id:idMessageContentComponent

            width : idGenericList.idList.width
            prText : itemTextRole

            prEditBtnVisibilityStatus : itemEditBtnVisible
            prEditBtnIndex : index
            prHBText.onContentHeightChanged:
            {
                prHBText.height = ((Math.ceil(prHBText.contentHeight/idGenericList.prItemHeight) * idGenericList.prItemHeight))

            }

            onSigEditBtnClicked: {

                cppPhoneAdaptor.editButtonClicked(prText, prEditBtnIndex)
                /**
                 * Here it will trigger the Keypad.
                 */
                cppSetupApp.raiseSMEvent("Keypad", SetupEnums.SETUP_SCREEN_KEYBOARD)
            }
        }

        ListItemSeparator
        {
            id: idListItemSeparator
        }
    }
}


