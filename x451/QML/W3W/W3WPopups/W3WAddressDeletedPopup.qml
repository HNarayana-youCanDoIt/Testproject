import QtQuick 2.7
import "../../Common/Popup"

NoButtonPopup
{
    prPopupText: ( (cppW3WAdaptor.selectedW3WAddressLabelForDelete === "") ?
                     cppUIBase.invTruncateText(cppW3WAdaptor.selectedW3WAddressForDelete, 30) + qsTr("TEXT_W3W_POPUP_DELETED_SUCCESSFULLY") :
                     cppUIBase.invTruncateText(cppW3WAdaptor.selectedW3WAddressLabelForDelete, 30) + qsTr("TEXT_W3W_POPUP_DELETED_SUCCESSFULLY") ) + cppThemeMgr.languageChanged
}
