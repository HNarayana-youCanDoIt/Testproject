/**
 * @file            DnResetTripFailedPopup.qml
 * @ingroup         QmlPopup
 * @author          Nandkishor Lokhande
 * DnResetTripFailedPopup, a popup can use to show DriveNext trip reset failed starus,
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
    prPopupText: qsTr("TEXT_DN_POPUP_RESET_TRIP_FAILED") + cppThemeMgr.languageChanged
}
