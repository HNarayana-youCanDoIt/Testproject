import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../../Common"
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.thememanager 1.0
import com.harman.qml.w3wenum 1.0


/**
 * idDelegate, This is delagate of the Auto Suggestion list
 */
Item {
    id: idAutoSuggestionDelegate

    width: 488
    height: 80

    Column {
        AutoSuggestionListItem {

            width       : idAutoSuggestionDelegate.width
            height      : idAutoSuggestionDelegate.height - idListItemSepratorImg.height

            prAddress: itemAddressRole
            prNearestPlace: itemNearestPlaceRole
            prFlagImage: cppW3WAdaptor.getFlagIconURLForCountryCode(itemCountryCodeRole);

            onReleased: {
                cppW3WApplication.qmlLog("W3WAutoSuggestionDelegate.qml: onReleased: ")
                cppW3WAdaptor.invSelectW3WAddressItem(W3WEnum.W3W_ADDRESS_TYPE_AUTO_SUGGESTION, itemId)
                cppUIBase.raiseSMEvent("back", "")
            }
        }

        /**
         * idListItemSepratorImg : Image source of the list item separator
         */
        Image {
            id: idListItemSepratorImg
            source: "qrc:/image/W3W/KeyPad/Gen_Gfx_ListSeparator_W3W_7in_n-assets/Gen_Gfx_ListSeparator_n.png"
            width: 488
            height: 1
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Connections {
        target: cppHardkeyAdaptor
        onSigRotaryPressed: {
            cppW3WApplication.qmlLog("W3WAutoSuggestionDelegate.qml: onRotaryUpdate: "+iKeyState)
            if((HardkeyEnum.HKEY_STATE_RELEASED === iKeyState ||
                HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState))
            {
                if(idAutoSuggestionList.idList.currentIndex === index)
                {
                    cppW3WAdaptor.invSelectW3WAddressItem(W3WEnum.W3W_ADDRESS_TYPE_AUTO_SUGGESTION, itemId)
                    cppUIBase.raiseSMEvent("back", "")
                }
                else
                {
                    //Do Nothing
                }
            }
            else
            {
                // Do Nothing
            }
        }
    }
}
