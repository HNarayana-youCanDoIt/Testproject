/**
 * @file            DnCanNotResetPopup.qml
 * @ingroup         QmlPopup
 * @author          Nandkishor Lokhande
 * DnCanNotResetPopup, a popup can use to show DriveNext reset all option availability,
 * It has Message field.
 */

import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.popupenums 1.0
import "../../Common/Popup"

NoButtonPopup
{
    /**
      * Message Text to be displayed on Popup
      */
    prPopupText: qsTr("TEXT_DN_POPUP_TURN_OFF_ENGINE") + cppThemeMgr.languageChanged
}
