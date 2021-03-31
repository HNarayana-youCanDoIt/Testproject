import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.popupenums 1.0
import QtGraphicalEffects 1.0
import com.harman.qml.parkassistenum 1.0
import "../Common"

BasePopup {
    id:idLowPrioritySmsPopup

    width: 800
    height: 76

    //No Backgound image required
    prPopupBackground: ""

    //Setting animation duration to 0 as animation is not required
    prShowAnimationDuration: 0

    //Animation not required. hence setting the property to false
    prIsAnimationRequired: false

    /**
     * Need to allow press or release events through items below this popup and hence setting it to false.
     */
    modal: false

    /*
     *  Setting height and width of Content item to screen's height and width
     *  This is done to capture touch event on the whole screen.
     */
    contentWidth: 800
    contentHeight: 76

    background{
        //overriding this property as background touch is not need for this popup
    }

    /**
      * Property which holds the boolean value whether RVC is active or PDC
      **/

    property bool prIsRvcActive: (ParkAssistEnum.PARK_ASSIST_VARIANT_PDC_RVC === cppParkAssistAdaptor.parkAssistVariant)

    /* Message icon on park assist header for incoming SMS */
    property string prMessageIcon: (prIsRvcActive ? "qrc:/image/ParkAssist/RVC/Header/Nav_Ico_IncomingMsg_n.png" :
                                                    "qrc:/image/ParkAssist/Phone/Nav_Ico_IncomingMsg_n.png")

    /* Font as per screen type [PDC/RVC]*/
    property int prFontScreenSpecific: (prIsRvcActive ? ThemeMgr.FONTTYPE_RVC : ThemeMgr.FONTTYPE_PDC)


    Connections
    {
        target: PopupManager
        onSigProcessHKOnPopup: {
            cppUIBase.qmlLog("onSigProcessHKOnPopup: LowPrioritySmsPopup : slot called")
            PopupManager.invSetHKHandledStatus(cppPhoneAdaptor.invHandleHardKeys(iKey, iKeyState))
        }
    }

    contentItem: Item{
        anchors.fill: parent

        Image {
            id: idSmsIcon

            anchors{
                left: parent.left
                leftMargin: 18
                verticalCenter: parent.verticalCenter
            }
            source: prMessageIcon
        }

        HBText{
            id:idSenderName

            width: 565
            height: 23
            fontType: prFontScreenSpecific

            /**
          These properties will be set based on RVC presence. If RVC is active Variant then set these properties
          else they will set to default i.e in case of PDC
          **/
            font.letterSpacing: prIsRvcActive ? 2 : 0
            style: prIsRvcActive ? Text.Outline : Text.Normal
            styleColor: "gray"

            anchors{
                left: parent.left
                leftMargin: 75
                verticalCenter: parent.verticalCenter
            }

            //FixMe: the text shall be updated as per the sms received
            text: qsTr("TEXT_PHONE_LOW_PRIORITY_INCOMING_SMS") + cppPhoneAdaptor.smsSenderName + cppThemeMgr.languageChanged
        }
    }

    onAboutToShow: {
        cppPhoneApp.qmlLog("LowPrioritySmsPopup.qml : onAboutToShow")
        cppPhoneAdaptor.invSetLowPriorityPopupActiveStatus(true);
    }

    onClosed: {
        cppPhoneApp.qmlLog("LowPrioritySmsPopup.qml : onAboutToHide")
        cppPhoneAdaptor.invSetLowPriorityPopupActiveStatus(false);
    }
}
