import QtQuick 2.7
import "../../Common/Popup"

NoButtonPopup{
    prPopupTitle: qsTr("Error");
    prPopupText:  MediaAdaptor.getStrUSBDeviceErrorPopupText();
}
