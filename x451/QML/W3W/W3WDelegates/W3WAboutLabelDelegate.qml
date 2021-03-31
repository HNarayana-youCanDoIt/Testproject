import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../../Common"
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.thememanager 1.0

/** Label Delegate ***
  * Delegate containing only Label.
  */

Item
{
    id: idLabelDelegate
    width: idGenericList.idList.width
    height: idAboutDescriptionText.height + idBtnListItemSeparator.height + 20

    HBText
    {
        id: idAboutDescriptionText

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
        width: parent.width - anchors.leftMargin
        anchors {
            left: parent.left
            leftMargin: 11
        }
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        text: itemTextRole
        wrapMode: Text.Wrap

        onEnabledChanged: {
            fontType = (enabled) ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
        }
    }

    ListItemSeparator
    {
        id: idBtnListItemSeparator
        anchors {
            top: idAboutDescriptionText.bottom
            topMargin: 20
        }
    }
}


