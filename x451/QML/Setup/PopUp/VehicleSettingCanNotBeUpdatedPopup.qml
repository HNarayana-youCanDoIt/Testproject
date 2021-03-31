import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.popupenums 1.0
import "../../Common/Popup"
import com.harman.qml.powerenums 1.0

NoButtonPopup{

    /**
      * Title to be displayed on Popup
      */
    // TODO: Popup string id should be added instead of static text.
    prPopupTitle: qsTr("TEXT_SETUP_POPUP_TURN_ON_IGNITION_TITLE") + cppThemeMgr.languageChanged

    /**
      * Text to be displayed on Popup
      */
    // TODO: Popup string id should be added instead of static text.
    prPopupText: qsTr("TEXT_POPUP_POWER_MODE_SETTING_DISABLED") + cppThemeMgr.languageChanged

}
