import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.popupenums 1.0
import "../../Common/Popup"

NoButtonPopupWithIndicator
{

    /**
      * Text to be displayed on Popup
      */
    // TODO: Popup string id should be added instead of static text.
    prPopupText: qsTr("Resetting") + cppThemeMgr.languageChanged


}

