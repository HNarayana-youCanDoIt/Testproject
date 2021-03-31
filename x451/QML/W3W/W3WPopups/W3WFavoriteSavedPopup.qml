import QtQuick 2.7
import "../../Common/Popup"

NoButtonPopup
{
    prPopupTitle: qsTr("TEXT_W3W_POPUP_SAVED_SUCCESSFULLY") + cppThemeMgr.languageChanged
    prPopupText: (cppW3WAdaptor.selectedW3WAddressLabelForFavorite === "") ?
                     "///" + cppUIBase.invTruncateText(cppW3WAdaptor.selectedW3WAddressForFavorite, 30) :
                     "///" + cppUIBase.invTruncateText(cppW3WAdaptor.selectedW3WAddressForFavorite, 30) + "\nAs\n" + cppUIBase.invTruncateText(cppW3WAdaptor.selectedW3WAddressLabelForFavorite, 30)
}
