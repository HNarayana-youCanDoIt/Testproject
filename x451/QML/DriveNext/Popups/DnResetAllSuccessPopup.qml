/**
 * @file            DnResetAllSuccessPopup.qml
 * @ingroup         QmlPopup
 * @author          Nandkishor Lokhande
 * DnResetAllSuccessPopup, a popup can use to show DriveNext reset All success starus,
 * It has Message field.
 */

import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.popupenums 1.0
import "../../Common/Popup"

NoButtonPopup
{
    /**
      * Message to be displayed on Popup
      */
    prPopupText: qsTr("TEXT_DN_POPUP_RESET_ALL_SUCCESS") + cppThemeMgr.languageChanged
}
