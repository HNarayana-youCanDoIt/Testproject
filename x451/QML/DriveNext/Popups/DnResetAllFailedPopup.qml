/**
 * @file            DnResetAllFailedPopup.qml
 * @ingroup         QmlPopup
 * @author          Nandkishor Lokhande
 * DnResetAllFailedPopup, a popup can use to show DriveNext reset All failed starus,
 * It has Title and Message field.
 */

import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.popupenums 1.0
import "../../Common/Popup"

NoButtonPopup
{
    /**
      * Title Text to be displayed on Popup
      */
    prPopupTitle: qsTr("TEXT_TITLE_ERROR") + cppThemeMgr.languageChanged

    /**
      * Message Text to be displayed on Popup
      */
    prPopupText: qsTr("TEXT_DN_POPUP_RESET_ALL_FAILED") + cppThemeMgr.languageChanged
}
