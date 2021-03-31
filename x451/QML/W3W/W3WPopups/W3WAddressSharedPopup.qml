import QtQuick 2.7
import "../../Common/Popup"

NoButtonPopup
{
    prPopupTitle: qsTr("TEXT_W3W_POPUP_SHARED_SUCCESSFULLY") + cppThemeMgr.languageChanged
    prPopupText: "///" + cppUIBase.invTruncateText(cppW3WAdaptor.selectedW3WAddress, 30)
}
