import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../../Common"
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.thememanager 1.0
import com.harman.qml.w3wenum 1.0
import com.harman.qml.popupenums 1.0


/**
 * idDelegate, This is delagate of the Favorite list
 */
Item {
    id: idFavoriteDelegate

    width: idFavoriteList.idList.width
    height: idFavoriteList.prItemHeight

    Column {
        W3WAddressListItem {

            width       : idFavoriteDelegate.width
            height      : idFavoriteDelegate.height - idListItemSepratorImg.height

            prW3WAddress: itemAddressRole
            prW3WAddressLabel: (itemLabelRole !== "") ? itemLabelRole :
                                                        qsTr("TEXT_W3W_ADD_LABEL") + cppThemeMgr.languageChanged

            prEditLabelButton {
                width: 76
                height: 76
                defaultImageURL: "qrc:/image/W3W/Gen_Ico_Edit_n-assets/Gen_Ico_Edit_n.png"
                pressedImageURL: "qrc:/image/W3W/Gen_Ico_Edit_n-assets/Gen_Ico_Edit_np.png"
                disabledImageURL: "qrc:/image/W3W/Gen_Ico_Edit_n-assets/Gen_Ico_Edit_nd.png"

                onReleased: {
                    cppW3WApplication.qmlLog("W3WFavoriteDelegate.qml: Edit Label button clicked")
                    /* Mark this as as Selected W3W Address item for Editing the Favorite */
                    cppW3WAdaptor.invSelectW3WAddressForFavorite(W3WEnum.W3W_ADDRESS_TYPE_FAVORITE,
                                                                 W3WEnum.W3W_FAVORITE_OPERATION_EDIT, itemId)
                    cppW3WApplication.raiseSMEvent("LaunchW3WEditLabelScreen", "")
                }
            }

            prDeleteButton {
                width: 70
                height: 70

                defaultImageURL: "qrc:/image/Set_Ico_Delete/Set_Ico_Delete_n.png"
                pressedImageURL: "qrc:/image/Set_Ico_Delete/Set_Ico_Delete_nf.png"
                disabledImageURL: "qrc:/image/Set_Ico_Delete/Set_Ico_Delete_nd.png"

                onReleased: {
                    cppW3WApplication.qmlLog("W3WFavoriteDelegate.qml: Delete button clicked")
                    /* Mark this as as Selected W3W Address item for Favorite */
                    cppW3WAdaptor.invSelectW3WAddressForDelete(W3WEnum.W3W_ADDRESS_TYPE_FAVORITE, itemId)
                    PopupManager.showPopup(PopupEnum.EN_POPUPID_W3W_DELETE_FAVORITE)
                }
            }

            onReleased: {
                cppW3WApplication.qmlLog("W3WAutoSuggestionDelegate.qml: onReleased: ")
                cppW3WAdaptor.invSelectW3WAddressItem(W3WEnum.W3W_ADDRESS_TYPE_FAVORITE, itemId)
                cppUIBase.raiseSMEvent("back", "")
            }
        }

        ListItemSeparator {
            id: idListItemSepratorImg
        }
    }

    Connections {
        target: cppHardkeyAdaptor
        onSigRotaryPressed: {
            cppW3WApplication.qmlLog("W3WAutoSuggestionDelegate.qml: onRotaryUpdate: "+iKeyState)
            if((HardkeyEnum.HKEY_STATE_RELEASED === iKeyState ||
                HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState))
            {
                if(idFavoriteList.idList.currentIndex === index)
                {
                    cppW3WAdaptor.invSelectW3WAddressItem(W3WEnum.W3W_ADDRESS_TYPE_FAVORITE, itemId)
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
