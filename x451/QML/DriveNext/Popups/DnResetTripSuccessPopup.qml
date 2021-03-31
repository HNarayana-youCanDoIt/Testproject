/**
 * @file            DnResetTripSuccessPopup.qml
 * @ingroup         QmlPopup
 * @author          Nandkishor Lokhande
 * DnResetTripSuccessPopup, a popup can use to show DriveNext trip reset success starus,
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
    prPopupText: qsTr("TEXT_DN_POPUP_RESET_TRIP_SUCCESS") + cppThemeMgr.languageChanged
}
