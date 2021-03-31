import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.popupenums 1.0
import com.harman.qml.phoneenum 1.0
import com.harman.qml.parkassistenum 1.0
import QtGraphicalEffects 1.0
import "../Common"

BasePopup {
    id:idLowPriorityCallPopup

    width: 800
    height: 76

    //No Backgound image required
    prPopupBackground: ""

    //Setting animation duration to 0 as animation is not required
    prShowAnimationDuration: 0

    //Animation not required. hence setting the property to false
    prIsAnimationRequired: false

    /*
     *  Setting height and width of Content item to screen's height and width
     *  This is done to capture touch event on the whole screen.
     */
    contentWidth: 800
    contentHeight: 76

    /**
     * Need to allow press or release events through items below this popup and hence setting it to false.
     */
    modal: false

    background{
        //overriding this property as background touch is not need for this popup
    }

    /**
      * Property which holds the boolean value whether RVC is active or PDC
      **/

    property bool prIsRvcActive: (ParkAssistEnum.PARK_ASSIST_VARIANT_PDC_RVC === cppParkAssistAdaptor.parkAssistVariant)

    /**
      * Property to hold current call state
      **/
    property int prPhoneCallState: cppPhoneAdaptor.phoneCallState


    /* Font as per screen type [PDC/RVC]*/
    property int prFontScreenSpecific: (prIsRvcActive ? ThemeMgr.FONTTYPE_RVC : ThemeMgr.FONTTYPE_PDC)


    /* Phone icon for Low priority phone calls */
    property string prCallIcon: (prIsRvcActive ? "qrc:/image/ParkAssist/RVC/Header/Ph_Ico_Call/PDC_RVC_Ph_Call_Ico_na.png" :
                                                 "qrc:/image/PhoneCall/Ph_Ico_Low_Priority_Call_Icon/Ph_Ico_Low_Priority_Call_Icon.png")

    /* Endcall icon(default state) on park assist header for call */
    property string prEndCallDefaultIcon: (prIsRvcActive ? "qrc:/image/ParkAssist/RVC/Header/Ph_Ico_EndCall_n/Phone_Ico_EndCall_n.png" :
                                                           "qrc:/image/PhoneCall/incomingCallPopup/Ph_Btn_EndCallSmall_7in_n-assets/Ph_Btn_EndCallSmall_n.png")

    /* Endcall icon(pressed state) on park assist header for call */
    property string prEndCallPressedIcon: (prIsRvcActive ? "qrc:/image/ParkAssist/RVC/Header/Ph_Ico_EndCall_n/Phone_Ico_EndCall_np.png" :
                                                           "qrc:/image/PhoneCall/incomingCallPopup/Ph_Btn_EndCallSmall_7in_n-assets/Ph_Btn_EndCallSmall_nf.png")

    /* Endcall icon(disabled state) on park assist header for call */
    property string prEndCallDisabledIcon: (prIsRvcActive ? "qrc:/image/ParkAssist/RVC/Header/Ph_Ico_EndCall_n/Phone_Ico_EndCall_nd.png" :
                                                            "qrc:/image/PhoneCall/incomingCallPopup/Ph_Btn_EndCallSmall_7in_n-assets/Ph_Btn_EndCallSmall_nd.png")

    /* Mute icon(default state) on park assist header for call */
    property string prMuteDefaultIcon: (prIsRvcActive ?  "qrc:/image/ParkAssist/RVC/Header/Ph_Ico_Mute_n/Ph_Ico_Mute_n.png" :
                                                        "qrc:/image/PhoneCall/callScreen/Ph_Btn_Mute_7in_n/Ph_Ico_Mute_n.png")

    /* Mute icon(pressed state) on park assist header for call */
    property string prMutePressedIcon: (prIsRvcActive ? "qrc:/image/ParkAssist/RVC/Header/Ph_Ico_Mute_n/Ph_Ico_Mute_np.png" :
                                                        "qrc:/image/PhoneCall/callScreen/Ph_Btn_Mute_7in_n/Ph_Ico_Mute_np.png")

    /* Mute icon(disabled state) on park assist header for call */
    property string prMuteDisabledIcon: (prIsRvcActive ? "qrc:/image/ParkAssist/RVC/Header/Ph_Ico_Mute_n/Ph_Ico_Mute_nd.png" :
                                                         "qrc:/image/PhoneCall/callScreen/Ph_Btn_Mute_7in_n/Ph_Ico_Mute_nd.png")

    /* UnMute icon(default state) on park assist header for call */
    property string prUnMuteDefaultIcon: (prIsRvcActive ? "qrc:/image/ParkAssist/RVC/Header/Ph_Ico_UnMute_n/Ph_Ico_UnMute_n.png" :
                                                          "qrc:/image/PhoneCall/callScreen/Ph_Btn_UnMute_7in_n-assets/Ph_Btn_UnMute_n.png")

    /* UnMute icon(pressed state) on park assist header for call */
    property string prUnMutePressedIcon: (prIsRvcActive ? "qrc:/image/ParkAssist/RVC/Header/Ph_Ico_UnMute_n/Ph_Ico_UnMute_np.png" :
                                                          "qrc:/image/PhoneCall/callScreen/Ph_Btn_UnMute_7in_n-assets/Ph_Btn_UnMute_nf.png")

    /* UnMute icon(disabled state) on park assist header for call */
    property string prUnMuteDisabledIcon: (prIsRvcActive ? "qrc:/image/ParkAssist/RVC/Header/Ph_Ico_UnMute_n/Ph_Ico_UnMute_nd.png" :
                                                           "qrc:/image/PhoneCall/callScreen/Ph_Btn_UnMute_7in_n-assets/Ph_Btn_UnMute_nd.png")

    /* Accept call icon(default state) on park assist header for call */
    property string prAcceptCallDefaultIcon: (prIsRvcActive ? "qrc:/image/ParkAssist/RVC/Header/Ph_Ico_IncomingCall_n/Ph_Ico_IncomingCall_n.png" :
                                                              "qrc:/image/PhoneCall/incomingCallPopup/Ph_Btn_IncomingCall_7in_n-assets/Ph_Ico_IncomingCall_n.png")

    /* Accept call icon(pressed state) on park assist header for call */
    property string prAcceptCallPressedIcon: (prIsRvcActive ? "qrc:/image/ParkAssist/RVC/Header/Ph_Ico_IncomingCall_n/Ph_Ico_IncomingCall_np.png" :
                                                              "qrc:/image/PhoneCall/incomingCallPopup/Ph_Btn_IncomingCall_7in_n-assets/Ph_Ico_IncomingCall_nf.png")

    /* Accept call icon(disabled state) on park assist header for call */
    property string prAcceptCallDisabledIcon: (prIsRvcActive ? "qrc:/image/ParkAssist/RVC/Header/Ph_Ico_IncomingCall_n/Ph_Ico_IncomingCall_nd.png" :
                                                               "qrc:/image/PhoneCall/incomingCallPopup/Ph_Btn_IncomingCall_7in_n-assets/Ph_Ico_IncomingCall_nd.png")

    Connections
    {
        target: PopupManager
        onSigProcessHKOnPopup: {
            cppUIBase.qmlLog("onSigProcessHKOnPopup: LowPriorityCallPopup : slot called")
            PopupManager.invSetHKHandledStatus(cppPhoneAdaptor.invHandleHardKeys(iKey, iKeyState))
        }
    }

    contentItem: Item{
        anchors.fill: parent

        RREHelper
        {
            id: idRREHelper
            isPopup: true
            Component.onCompleted:
            {
                cppUIBase.qmlLog("LowPriorityCallPopup.qml: RREHelper:Component.onCompleted: ")
            }
        }

        Image {
            id: idCallIcon

            width: 76
            height: 76

            anchors{
                left: parent.left
                leftMargin: 0
                verticalCenter: parent.verticalCenter
            }

            source: prCallIcon
        }

        HBText{
            id: idCallerName

            width: 480
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

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }

        HBText{
            id: idCallStatus

            width: 150
            fontType: prFontScreenSpecific

            /**
          These properties will be set based on RVC presence. If RVC is active Variant then set these properties
          else they will set to default i.e in case of PDC
          **/
            font.letterSpacing: prIsRvcActive ? 2 : 0
            style: prIsRvcActive ? Text.Outline : Text.Normal
            styleColor: "gray"

            anchors{
                left: idCallerName.right
                /**
             * idCallerStatus text field should be always positioned 20pixel left to the content of idCallerName text field
             * So, Here we are calculating the left margin for idCallStatus text field as per the content width
             * of idCallerName text field.
             */
                leftMargin: (20 + ((idCallerName.contentWidth <= idCallerName.width) ? -(idCallerName.width - idCallerName.contentWidth) : 0))
                verticalCenter: parent.verticalCenter
            }
            visible: false

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft

        }

        GenericButton{
            id: idAcceptCall

            width: 76
            height: 76

            defaultImageURL : prAcceptCallDefaultIcon
            pressedImageURL : prAcceptCallPressedIcon
            disabledImageURL: prAcceptCallDisabledIcon
            prRREImageSrc   : (prIsRvcActive ? "qrc:/image/ParkAssist/RVC/Header/Ph_Ico_IncomingCall_n/Ph_Ico_IncomingCall_np.png"
                                             : "qrc:/image/Home/Home_Ico_RRE_Focus/Home_Ico_RRE_Focus.png")

            anchors{
                left: parent.left
                leftMargin: 640
                verticalCenter: parent.verticalCenter
            }
            visible: false

            onPressed: {
                idRREHelper.setCurrentRreIndex(-1)
            }
            onReleased:{
                cppPhoneApp.qmlLog("LowPriorityCallPopup : onReleased, acceptCall")
                cppPhoneAdaptor.invAcceptIncomingCall()
            }
        }

        GenericButton{
            id: idMuteCall

            width: 76
            height: 76

            defaultImageURL:  cppAudioAdaptor.micMuteStatus ? prUnMuteDefaultIcon  : prMuteDefaultIcon
            pressedImageURL:  cppAudioAdaptor.micMuteStatus ? prUnMutePressedIcon  : prMutePressedIcon
            disabledImageURL: cppAudioAdaptor.micMuteStatus ? prUnMuteDisabledIcon : prMuteDisabledIcon
            prRREImageSrc   : (cppAudioAdaptor.micMuteStatus ? (prIsRvcActive ? "qrc:/image/ParkAssist/RVC/Header/Ph_Ico_UnMute_n/Ph_Ico_UnMute_np.png"
                                                                              : "qrc:/image/Home/Home_Ico_RRE_Focus/Home_Ico_RRE_Focus.png")
                                                             : (prIsRvcActive ? "qrc:/image/ParkAssist/RVC/Header/Ph_Ico_Mute_n/Ph_Ico_Mute_np.png"
                                                                              : "qrc:/image/Home/Home_Ico_RRE_Focus/Home_Ico_RRE_Focus.png"))
            anchors{
                left: parent.left
                leftMargin: 640
                verticalCenter: parent.verticalCenter
            }
            visible: false

            onPressed: {
                idRREHelper.setCurrentRreIndex(-1)
            }
            onReleased: {
                cppPhoneApp.qmlLog("LowPriorityCallPopup : onReleased, toggle mic mute")
                cppPhoneAdaptor.invToggleMicMute()
            }
        }

        GenericButton{
            id: idRejectCall

            width: 76
            height: 76

            defaultImageURL : prEndCallDefaultIcon
            pressedImageURL : prEndCallPressedIcon
            disabledImageURL: prEndCallDisabledIcon
            prRREImageSrc   : (prIsRvcActive ? "qrc:/image/ParkAssist/RVC/Header/Ph_Ico_EndCall_n/Phone_Ico_EndCall_np.png"
                                             : "qrc:/image/Home/Home_Ico_RRE_Focus/Home_Ico_RRE_Focus.png")

            anchors{
                left: parent.left
                leftMargin: 724
                verticalCenter: parent.verticalCenter
            }
            visible: false

            onPressed: {
                idRREHelper.setCurrentRreIndex(-1)
            }
            onReleased:{
                cppPhoneApp.qmlLog("LowPriorityCallPopup : onReleased, idRejectCall")
                endCall()
            }
        }
    }

    onAboutToShow: {
        cppPhoneApp.qmlLog("LowPriorityCallPopup.qml.qml : Component.onAboutToShow" + prPhoneCallState)
        cppPhoneAdaptor.invSetLowPriorityPopupActiveStatus(true);
        updateUI()
        updateBtnList()
    }

    onClosed: {
        cppPhoneApp.qmlLog("LowPriorityCallPopup.qml : onAboutToHide")
        cppPhoneAdaptor.invSetLowPriorityPopupActiveStatus(false);
    }

    onPrPhoneCallStateChanged: {
        cppPhoneApp.qmlLog("LowPriorityCallPopup.qml.qml : onPrPhoneCallStateChanged state : " + prPhoneCallState)
        updateUI()
    }

    function updateBtnList()
    {
        cppPhoneApp.qmlLog("updateBtnList idRREHelper" + idRREHelper.prCurrentRREIndex)

        idRREHelper.resetItemList();
        var btnList = [idAcceptCall, idMuteCall,idRejectCall]
        idRREHelper.setItemList(btnList);
    }

    function updateUI(){
        idRREHelper.setCurrentRreIndex(-1)

        switch(prPhoneCallState)
        {
        case PhoneEnum.PHONE_CALLSTATE_ALL_CALLS_TERMINATED:
            endCallUIupdate()
            break;

        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_ONHOLD:
        case PhoneEnum.PHONE_CALLSTATE_HELD_CALL:
            holdCallUIupdate()
            break;

        case PhoneEnum.PHONE_CALLSTATE_ACTIVE_CALL:
        case PhoneEnum.PHONE_CALLSTATE_ACTIVE_CALL_AND_HELD_CALL:
        case PhoneEnum.PHONE_CALLSTATE_ACTIVE_CALL_AND_CONFERENCE_ONHOLD:
            activeCallUIupdate()
            break;

        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE:
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_HELD_CALL:
            conferenceActiveCallUIupdate()
            break;

        case PhoneEnum.PHONE_CALLSTATE_INCOMING_CALL:
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_INCOMING_CALL:
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_ONHOLD_AND_INCOMING_CALL:
        case PhoneEnum.PHONE_CALLSTATE_ACTIVE_CALL_AND_INCOMING_CALL:
        case PhoneEnum.PHONE_CALLSTATE_HELD_CALL_AND_INCOMING_CALL:
            incomingCallUIupdate()
            break;

        case PhoneEnum.PHONE_CALLSTATE_ACTIVE_CALL_AND_ALERTING:
        case PhoneEnum.PHONE_CALLSTATE_ACTIVE_CALL_AND_DIALING:
        case PhoneEnum.PHONE_CALLSTATE_ALERTING:
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_ALERTING:
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_DIALING:
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_ONHOLD_AND_ALERTING:
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_ONHOLD_AND_DIALING:
        case PhoneEnum.PHONE_CALLSTATE_DIALING:
        case PhoneEnum.PHONE_CALLSTATE_HELD_CALL_AND_ALERTING:
        case PhoneEnum.PHONE_CALLSTATE_HELD_CALL_AND_DIALING:
            outgoingCallUIupdate()
            break;
        default:
            cppPhoneApp.qmlLog("call state not handled : " + prPhoneCallState)
            break;
        }
    }

    function endCallUIupdate(){
        cppPhoneApp.qmlLog("LowPriorityCallPopup : endCallUIupdate")
        idCallerName.text = qsTr("TEXT_PHONE_CALL_ENDED") + cppThemeMgr.languageChanged
        idAcceptCall.visible = false
        idRejectCall.visible = false
        idMuteCall.visible = false
        idCallStatus.visible = false
    }

    function holdCallUIupdate(){
        cppPhoneApp.qmlLog("LowPriorityCallPopup : holdCallUIupdate")
        idCallerName.text = Qt.binding(function() { return ((cppPhoneAdaptor.firstCallerInfo.callerName === "")
                                                            ? cppPhoneAdaptor.firstCallerInfo.callerNumber + cppThemeMgr.languageChanged
                                                            : cppPhoneAdaptor.firstCallerInfo.callerName + cppThemeMgr.languageChanged) })
        idCallStatus.text = Qt.binding(function() { return (cppPhoneAdaptor.firstCallerInfo.callDuration + cppThemeMgr.languageChanged) })
        idAcceptCall.visible = false
        idMuteCall.visible = true
        idRejectCall.visible = true
        idCallStatus.visible = true
    }

    function activeCallUIupdate(){
        cppPhoneApp.qmlLog("LowPriorityCallPopup : activeCallUIupdate")
        idCallerName.text = Qt.binding(function() { return ((cppPhoneAdaptor.firstCallerInfo.callerState === PhoneEnum.CALLER_ACTIVE)
                                                            ? ((cppPhoneAdaptor.firstCallerInfo.callerName === "")
                                                               ? (cppPhoneAdaptor.firstCallerInfo.callerNumber + cppThemeMgr.languageChanged)
                                                               : (cppPhoneAdaptor.firstCallerInfo.callerName + cppThemeMgr.languageChanged))
                                                            : ((cppPhoneAdaptor.secondCallerInfo.callerName === "")
                                                               ? (cppPhoneAdaptor.secondCallerInfo.callerNumber + cppThemeMgr.languageChanged)
                                                               : (cppPhoneAdaptor.secondCallerInfo.callerName + cppThemeMgr.languageChanged))) })
        idCallStatus.text = Qt.binding(function() { return ((cppPhoneAdaptor.firstCallerInfo.callerState === PhoneEnum.CALLER_ACTIVE)
                                                            ? cppPhoneAdaptor.firstCallerInfo.callDuration + cppThemeMgr.languageChanged
                                                            : cppPhoneAdaptor.secondCallerInfo.callDuration + cppThemeMgr.languageChanged) })
        idAcceptCall.visible = false
        idMuteCall.visible = true
        idRejectCall.visible = true
        idCallStatus.visible = true
    }

    function conferenceActiveCallUIupdate(){
        cppPhoneApp.qmlLog("LowPriorityCallPopup : conferenceActiveCallUIupdate")
        idCallerName.text = Qt.binding(function() { return (qsTr("TEXT_PHONE_CALL_CONFERENCE") + cppThemeMgr.languageChanged) })
        idCallStatus.text = Qt.binding(function() { return ((cppPhoneAdaptor.firstCallerInfo.callerState === PhoneEnum.CALLER_ACTIVE)
                                                            ? cppPhoneAdaptor.firstCallerInfo.callDuration + cppThemeMgr.languageChanged
                                                            : cppPhoneAdaptor.secondCallerInfo.callDuration + cppThemeMgr.languageChanged) })
        idAcceptCall.visible = false
        idMuteCall.visible = true
        idRejectCall.visible = true
        idCallStatus.visible = true
    }

    function incomingCallUIupdate(){
        cppPhoneApp.qmlLog("LowPriorityCallPopup : incomingCallUIupdate")
        idCallerName.text = Qt.binding(function() { return ((cppPhoneAdaptor.incomingCallInfo.callerName !== "")
                                                            ? qsTr("TEXT_LOW_PRIORITY_INCOMING_CALL") + cppPhoneAdaptor.incomingCallInfo.callerName + cppThemeMgr.languageChanged
                                                            : qsTr("TEXT_LOW_PRIORITY_INCOMING_CALL") + cppPhoneAdaptor.incomingCallInfo.callerNumber + cppThemeMgr.languageChanged) })
        idAcceptCall.visible = true
        idMuteCall.visible = false
        idRejectCall.visible = true
        idCallStatus.visible = false
    }

    function outgoingCallUIupdate(){
        cppPhoneApp.qmlLog("LowPriorityCallPopup : outgoingCallUIupdate")
        idCallerName.text = Qt.binding(function() { return ((cppPhoneAdaptor.secondCallerInfo.callerState === PhoneEnum.CALLER_UNAVAILABLE)
                                                            ? ((cppPhoneAdaptor.firstCallerInfo.callerName === "")
                                                               ? (qsTr("TEXT_LOW_PRIORITY_OUTGOING_CALL") + cppPhoneAdaptor.firstCallerInfo.callerNumber + cppThemeMgr.languageChanged)
                                                               : (qsTr("TEXT_LOW_PRIORITY_OUTGOING_CALL") + cppPhoneAdaptor.firstCallerInfo.callerName + cppThemeMgr.languageChanged))
                                                            : ((cppPhoneAdaptor.secondCallerInfo.callerName === "")
                                                               ? (qsTr("TEXT_LOW_PRIORITY_OUTGOING_CALL") + cppPhoneAdaptor.secondCallerInfo.callerNumber + cppThemeMgr.languageChanged)
                                                               : (qsTr("TEXT_LOW_PRIORITY_OUTGOING_CALL") + cppPhoneAdaptor.secondCallerInfo.callerName + cppThemeMgr.languageChanged))) })
        idAcceptCall.visible = false
        idMuteCall.visible = false
        idRejectCall.visible = true
        idCallStatus.visible = false
    }

    function endCall(){
        switch(prPhoneCallState)
        {
        case PhoneEnum.PHONE_CALLSTATE_INCOMING_CALL:
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_INCOMING_CALL:
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_ONHOLD_AND_INCOMING_CALL:
        case PhoneEnum.PHONE_CALLSTATE_ACTIVE_CALL_AND_INCOMING_CALL:
        case PhoneEnum.PHONE_CALLSTATE_HELD_CALL_AND_INCOMING_CALL:
            cppPhoneAdaptor.invRejectIncomingCall()
            break;

        default:
            cppPhoneAdaptor.invEndPhoneCall()
            break;
        }
    }
}
