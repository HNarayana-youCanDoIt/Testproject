import QtQuick 2.7
import "../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.parkassistenum 1.0
import com.harman.qml.phoneenum 1.0

/**
 * This item contains components related to fault message.
 */
Item {
    id: idPAFaultMessageHeaderItem

    width: 800
    height: 72

    visible: ((!(cppPhoneAdaptor.lowPriorityPopupActive)) && (!(cppPhoneAdaptor.doesCallExist)))

    /**
      * Property which holds the boolean value whether RVC is active or PDC
      **/
    property bool prIsRvcActive: (ParkAssistEnum.PARK_ASSIST_VARIANT_PDC_RVC === cppParkAssistAdaptor.parkAssistVariant)

    /* Font as per screen type [PDC/RVC]*/
    property int prFontScreenSpecific: (prIsRvcActive ? ThemeMgr.FONTTYPE_RVC : ThemeMgr.FONTTYPE_PDC)

    /**
     * Alert image, shown at the time of fault message.
     */
    Image {
        id: idAlertIcon
        source: "qrc:/image/ParkAssist/RVC/Header/Gen_Ico_Alert_7in_n-assets/Gen_Ico_Alert_n.png"
        visible: cppParkAssistAdaptor.isAlertIconAvailable

        anchors {
            left: parent.left
            leftMargin: 9
            verticalCenter: parent.verticalCenter
        }
    }

    /**
     * HBText, used to display fault messages
     */
    HBText {
        id: idFaultMessage
        fontType: prFontScreenSpecific
        text: qsTr(cppParkAssistAdaptor.pdcRvcFaultMessage) + cppThemeMgr.languageChanged

        /**
          These properties will be set based on RVC presence. If RVC is active Variant then set these properties
          else they will set to default i.e in case of PDC
          **/
        font.letterSpacing: prIsRvcActive ? 2 : 0
        style: prIsRvcActive ? Text.Outline : Text.Normal
        styleColor: "gray"

        anchors {
            left: cppParkAssistAdaptor.isAlertIconAvailable ? idAlertIcon.right : parent.left
            leftMargin: cppParkAssistAdaptor.isAlertIconAvailable ? 3 : 30
            verticalCenter: parent.verticalCenter

        }
    }
}
