import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.popupenums 1.0
import "../Common/Popup"

NoButtonPopup
{
    /**
      * Title to be displayed on Popup
      */
    // TODO: Popup string id should be added instead of static text.
    prPopupTitle: qsTr("Pass Key:\"%1\"").arg(cppPhoneAdaptor.passKeyPin) + cppThemeMgr.languageChanged

    /**
      * Text to be displayed on Popup
      */
    prPopupText: qsTr("TEXT_PHONE_SETUP_HU_PAIRING").arg(cppPhoneAdaptor.passKeyPin).arg(cppUIBase.invTruncateText(cppPhoneAdaptor.selItemName,20)) + cppThemeMgr.languageChanged
}
