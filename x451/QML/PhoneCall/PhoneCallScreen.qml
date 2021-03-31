import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.phoneenum 1.0
import com.harman.qml.hardkeyenum 1.0
import "qrc:/QML/Common"

BaseUI{
    id: idPhoneCallScreen

    /**
      * Property to hold current call state
      **/
    property int prPhoneCallState: cppPhoneAdaptor.phoneCallState
    property bool prHandsfreeModeStatus: cppPhoneAdaptor.handsFreeModeStatus

    /**
      * Text to hold Title of the screen
      **/
    HBText {
        id: idScreenTitle
        width: 324
        height: 32
        anchors {
            left: parent.left
            leftMargin: 238
            top: parent.top
            topMargin: 72
        }
        fontType: ThemeMgr.FONTTYPE_T45_C1
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    /* Text to hold first caller name */
    HBText {
        id: idFirstCallerName
        width: 322
        height: 25

        anchors {
            left: parent.left
            leftMargin: 306
            top: parent.top
            topMargin: 146
        }

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft

        fontType: enabled ? ThemeMgr.FONTTYPE_T35_BK_C2 : ThemeMgr.FONTTYPE_T35_BK_C2_DISABLED
        text: (cppPhoneAdaptor.firstCallerInfo.callerName === "") ? cppPhoneAdaptor.firstCallerInfo.callerNumber : cppPhoneAdaptor.firstCallerInfo.callerName
    }

    /* Text to hold first caller number */
    HBText {
        id: idFirstCallerNumber

        width: 322
        height: 18

        anchors {
            left: parent.left
            leftMargin: 306
            top: parent.top
            topMargin: 189
        }

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft

        fontType: enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C2 : ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED
        text: {
            if(cppPhoneAdaptor.secondCallerInfo.callerState === PhoneEnum.CALLER_UNAVAILABLE) {
                cppPhoneAdaptor.firstCallerInfo.callerNumber
            }
            else{
                cppPhoneAdaptor.firstCallerInfo.callDuration
            }
        }
    }

    /* Text to hold first call duration */
    HBText {
        id: idFirstCallDuration

        width: 322
        height: 18

        anchors {
            left: parent.left
            leftMargin: 306
            top: parent.top
            topMargin: 231
        }

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        text: cppPhoneAdaptor.firstCallerInfo.callDuration
    }

    /* Image for Second Caller Profile Image */
    Image {
        id: idSecondCallerProfileImage

        width: 109
        height: 105
        anchors{
            left: parent.left
            leftMargin: 155
            top: parent.top
            topMargin: 165
        }


        source: cppPhoneAdaptor.secondCallerInfo.callerProfileImage
    }

    /* Image for first Caller Profile Image */
    Image {
        id: idFirstCallerProfileImage

        width: 109
        height: 105
        anchors{
            left: parent.left
            leftMargin: 176
            top: parent.top
            topMargin: 145
        }
        source: cppPhoneAdaptor.firstCallerInfo.callerProfileImage

        HBText
        {
            anchors.fill: parent
            visible: (cppPhoneAdaptor.firstCallerInfo.callerProfileName !== "")
            text: cppPhoneAdaptor.firstCallerInfo.callerProfileName
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            fontType: ThemeMgr.FONTTYPE_T45_C1
        }
    }

    /* Text to hold second caller name */
    HBText {
        id: idSecondCallerName

        width: 322
        height: 25

        anchors {
            left: parent.left
            leftMargin: 306
            top: parent.top
            topMargin: 231
        }

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft

        fontType: (enabled) ? ThemeMgr.FONTTYPE_T35_BK_C2 : ThemeMgr.FONTTYPE_T35_BK_C2_DISABLED
        text: (cppPhoneAdaptor.secondCallerInfo.callerName === "") ? cppPhoneAdaptor.secondCallerInfo.callerNumber : cppPhoneAdaptor.secondCallerInfo.callerName
    }

    /* Text to hold second call duration */
    HBText {
        id: idSecondCallerDuration

        width: 100
        height: 18

        anchors {
            left: parent.left
            leftMargin: 306
            top: parent.top
            topMargin: 274
        }

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        text: cppPhoneAdaptor.secondCallerInfo.callDuration
    }

    RREHelper
    {
        id: idRREHelper
        Component.onCompleted:
        {
            cppPhoneApp.qmlLog("RreFocus.qml Component onCompleted")
        }
    }


    /* Button to switch phone call btw BT and handset */
    GenericButton {
        id: idHandSetBtn
        width: 76
        height: 76
        enabled: !(cppPhoneAdaptor.hfModeReqStatus)
        prRREImageSrc: "qrc:/Assets/RREFocus/Ph_Ico_RRE_Btn_7in_np.png"

        anchors{
            left: parent.left
            leftMargin: 120
            top: parent.top
            topMargin: 293
        }

        //ToDo : Need to disable handsfree button till the responce received
        defaultImageURL: prHandsfreeModeStatus ? "qrc:/image/PhoneCall/callScreen/Ph_Btn_Handset_7in_n/Ph_Btn_Handset_n.png" : "qrc:/image/PhoneCall/callScreen/Ph_Btn_Handsfree_7in_n-assets/Ph_Btn_Handsfree_n.png"
        pressedImageURL: prHandsfreeModeStatus ? "qrc:/image/PhoneCall/callScreen/Ph_Btn_Handset_7in_n/Ph_Btn_Handset_np.png" : "qrc:/image/PhoneCall/callScreen/Ph_Btn_Handsfree_7in_n-assets/Ph_Btn_Handsfree_nf.png"
        disabledImageURL: prHandsfreeModeStatus ? "qrc:/image/PhoneCall/callScreen/Ph_Btn_Handset_7in_n/Ph_Btn_Handset_nd.png" : "qrc:/image/PhoneCall/callScreen/Ph_Btn_Handsfree_7in_n-assets/Ph_Btn_Handsfree_nd.png"

        onPressed: {
            idRREHelper.setCurrentRreIndex(-1)
        }

        onReleased: {
            cppPhoneAdaptor.invSetHfMode(!prHandsfreeModeStatus)
        }
    }



    /* Button to open Number pad */
    GenericButton {
        id: idNumPadBtn

        width: 76
        height: 76
        visible: false
        prRREImageSrc: "qrc:/Assets/RREFocus/Ph_Ico_RRE_Btn_7in_np.png"

        anchors{
            left: parent.left
            leftMargin: 120
            top: parent.top
            topMargin: 384
        }

        defaultImageURL: "qrc:/image/PhoneCall/callScreen/Ph_Btn_Numpad_7in_n/Ph_Btn_Numpad_n.png"
        pressedImageURL: "qrc:/image/PhoneCall/callScreen/Ph_Btn_Numpad_7in_n/Ph_Btn_Numpad_np.png"
        disabledImageURL: "qrc:/image/PhoneCall/callScreen/Ph_Btn_Numpad_7in_n/Ph_Btn_Numpad_nd.png"

        onPressed: {
            idRREHelper.setCurrentRreIndex(-1)
        }

        onReleased: {
            cppPhoneApp.qmlLog("PhoneActiveCallScreen.qml : request numpad")
            cppPhoneAdaptor.invChangeDTMFNumberPadStatus(true)
            cppPhoneApp.raiseSMEvent("PhoneBrowse", PhoneEnum.PHONE_BROWSE_TYPE_DIALPAD)
        }
    }



    /* Button to switch phone call to hold */
    GenericButton {
        id: idHoldBtn

        width: 76
        height: 76
        prRREImageSrc: "qrc:/Assets/RREFocus/Ph_Ico_RRE_Btn_7in_np.png"

        enabled: !(cppPhoneAdaptor.holdCallReqStatus)
        anchors{
            left: parent.left
            leftMargin: 234
            top: parent.top
            topMargin: 384
        }

        defaultImageURL: "qrc:/image/PhoneCall/callScreen/Ph_Btn_OnHold_7in_n/Ph_Btn_OnHold_n.png"
        pressedImageURL: "qrc:/image/PhoneCall/callScreen/Ph_Btn_OnHold_7in_n/Ph_Btn_OnHold_np.png"
        disabledImageURL: "qrc:/image/PhoneCall/callScreen/Ph_Btn_OnHold_7in_n/Ph_Btn_OnHold_nd.png"

        onPressed: {
            idRREHelper.setCurrentRreIndex(-1)
        }

        onReleased: {
            cppPhoneAdaptor.invHoldActiveCall()
        }
    }



    /* Button to switch phone call to active */
    GenericButton {
        id: idResumeBtn
        width: 76
        height: 76
        prRREImageSrc: "qrc:/Assets/RREFocus/Ph_Ico_RRE_Btn_7in_np.png"

        enabled: !(cppPhoneAdaptor.resumeCallReqStatus)
        anchors{
            left: parent.left
            leftMargin: 234
            top: parent.top
            topMargin: 384
        }

        defaultImageURL: "qrc:/image/PhoneCall/callScreen/Ph_Btn_Resume_7in_n-assets/Ph_Btn_Resume_n.png"
        pressedImageURL: "qrc:/image/PhoneCall/callScreen/Ph_Btn_Resume_7in_n-assets/Ph_Btn_Resume_np.png"
        disabledImageURL: "qrc:/image/PhoneCall/callScreen/Ph_Btn_Resume_7in_n-assets/Ph_Btn_Resume_nd.png"

        onPressed: {
            idRREHelper.setCurrentRreIndex(-1)
        }

        onReleased:{
            cppPhoneAdaptor.invResumeHeldCall()
        }
    }



    /* Button to swap multiparty call */
    GenericButton {
        id: idSwapBtn
        width: 76
        height: 76
        prRREImageSrc: "qrc:/Assets/RREFocus/Ph_Ico_RRE_Btn_7in_np.png"

        enabled: !(cppPhoneAdaptor.swapCallsReqStatus)

        anchors{
            left: parent.left
            leftMargin: 234
            top: parent.top
            topMargin: 384
        }

        defaultImageURL: "qrc:/image/PhoneCall/callScreen/Ph_Btn_Swap_7in_n-assets/Ph_Btn_Swap_n.png"
        pressedImageURL: "qrc:/image/PhoneCall/callScreen/Ph_Btn_Swap_7in_n-assets/Ph_Btn_Swap_np.png"
        disabledImageURL: "qrc:/image/PhoneCall/callScreen/Ph_Btn_Swap_7in_n-assets/Ph_Btn_Swap_nd.png"

        onPressed: {
            idRREHelper.setCurrentRreIndex(-1)
        }

        onReleased:{

            cppPhoneAdaptor.invSwapCalls()
        }
    }



    /* Button terminate/end call */
    GenericButton {
        id: idEndBtn
        width: 96
        height: 96

        enabled: !(cppPhoneAdaptor.endCallReqStatus)

        anchors{
            left: parent.left
            leftMargin: 347
            top: parent.top
            topMargin: 374
        }

        defaultImageURL: "qrc:/image/PhoneCall/callScreen/Ph_Btn_EndCallLarge_7in_n/Ph_Btn_EndCallLarge_n.png"
        pressedImageURL: "qrc:/image/PhoneCall/callScreen/Ph_Btn_EndCallLarge_7in_n/Ph_Btn_EndCallLarge_np.png"
        disabledImageURL: "qrc:/image/PhoneCall/callScreen/Ph_Btn_EndCallLarge_7in_n/Ph_Btn_EndCallLarge_nd.png"

        onPressed: {
            idRREHelper.setCurrentRreIndex(-1)
        }

        onReleased:{
            cppPhoneApp.qmlLog("PhoneActiveCallScreen.qml : request end call")
            cppPhoneAdaptor.invEndPhoneCall()
        }
    }



    /* Button to add call */
    GenericButton {
        id: idAddCallBtn
        width: 76
        height: 76
        prRREImageSrc: "qrc:/Assets/RREFocus/Ph_Ico_RRE_Btn_7in_np.png"

        anchors{
            left: parent.left
            leftMargin: 481
            top: parent.top
            topMargin: 384
        }

        defaultImageURL: "qrc:/image/PhoneCall/callScreen/Ph_Btn_AddCall_7in_n/Ph_Btn_AddCall_n.png"
        pressedImageURL: "qrc:/image/PhoneCall/callScreen/Ph_Btn_AddCall_7in_n/Ph_Btn_AddCall_np.png"
        disabledImageURL: "qrc:/image/PhoneCall/callScreen/Ph_Btn_AddCall_7in_n/Ph_Btn_AddCall_nd.png"

        onPressed: {
            idRREHelper.setCurrentRreIndex(-1)
        }

        onReleased: {
            cppPhoneApp.qmlLog("PhoneActiveCallScreen.qml : request add call")
            cppPhoneApp.raiseSMEvent("PhoneBrowse", PhoneEnum.PHONE_BROWSE_TYPE_CALL_LOGS)
        }
    }




    /* Button to merge multiparty call */
    GenericButton {
        id: idMergeBtn
        width: 76
        height: 76
        prRREImageSrc: "qrc:/Assets/RREFocus/Ph_Ico_RRE_Btn_7in_np.png"

        enabled: !(cppPhoneAdaptor.mergeCallsReqStatus)

        anchors{
            left: parent.left
            leftMargin: 481
            top: parent.top
            topMargin: 384
        }

        defaultImageURL: "qrc:/image/PhoneCall/callScreen/Ph_Btn_Merge_7in_n-assets/Ph_Btn_Merge_n.png"
        pressedImageURL: "qrc:/image/PhoneCall/callScreen/Ph_Btn_Merge_7in_n-assets/Ph_Btn_Merge_np.png"
        disabledImageURL: "qrc:/image/PhoneCall/callScreen/Ph_Btn_Merge_7in_n-assets/Ph_Btn_Merge_nd.png"

        onPressed: {
            idRREHelper.setCurrentRreIndex(-1)
        }

        onReleased:{
            cppPhoneAdaptor.invConferenceCall()
        }
    }

    /* Button to mute the HU mic */
    GenericButton {
        id: idMuteBtn
        width: 76
        height: 76
        prRREImageSrc: "qrc:/Assets/RREFocus/Ph_Ico_RRE_Btn_7in_np.png"

        anchors{
            left: parent.left
            leftMargin: 594
            top: parent.top
            topMargin: 384
        }

        enabled: prHandsfreeModeStatus

        defaultImageURL: cppAudioAdaptor.micMuteStatus ?
                             "qrc:/image/PhoneCall/callScreen/Ph_Btn_UnMute_7in_n-assets/Ph_Btn_UnMute_n.png" :
                             "qrc:/image/PhoneCall/callScreen/Ph_Btn_Mute_7in_n/Ph_Ico_Mute_n.png"
        pressedImageURL: cppAudioAdaptor.micMuteStatus ?
                             "qrc:/image/PhoneCall/callScreen/Ph_Btn_UnMute_7in_n-assets/Ph_Btn_UnMute_nf.png" :
                             "qrc:/image/PhoneCall/callScreen/Ph_Btn_Mute_7in_n/Ph_Ico_Mute_np.png"
        disabledImageURL: cppAudioAdaptor.micMuteStatus ?
                              "qrc:/image/PhoneCall/callScreen/Ph_Btn_UnMute_7in_n-assets/Ph_Btn_UnMute_nd.png" :
                              "qrc:/image/PhoneCall/callScreen/Ph_Btn_Mute_7in_n/Ph_Ico_Mute_nd.png"

        onPressed: {
            idRREHelper.setCurrentRreIndex(-1)
        }

        onReleased: {
            cppPhoneApp.qmlLog("PhoneActiveCallScreen.qml : toggle mic mute")
            cppPhoneAdaptor.invToggleMicMute()
        }
    }

    /* Button to open participant's screen */
    GenericButton {
        id: idParticipantBtn
        width: 76
        height: 76
        prRREImageSrc: "qrc:/Assets/RREFocus/Ph_Ico_RRE_Btn_7in_np.png"

        anchors{
            left: parent.left
            leftMargin: 594
            top: parent.top
            topMargin: 293
        }

        defaultImageURL: "qrc:/image/PhoneCall/callScreen/Ph_btn_ShowParticipants_7in_n-assets/Ph_btn_Participants_n.png"
        pressedImageURL: "qrc:/image/PhoneCall/callScreen/Ph_btn_ShowParticipants_7in_n-assets/Ph_btn_Participants_np.png"
        disabledImageURL: "qrc:/image/PhoneCall/callScreen/Ph_btn_ShowParticipants_7in_n-assets/Ph_btn_Participants_nd.png"

        onPressed: {
            idRREHelper.setCurrentRreIndex(-1)
        }

        onReleased: {
            cppPhoneApp.qmlLog("PhoneActiveCallScreen.qml : request participant")
            cppPhoneApp.raiseSMEvent("ConferenceParticipant", "")
        }
    }



    Component.onCompleted: {
        cppPhoneApp.qmlLog("PhoneActiveCallScreen.qml : Component.onCompleted")
        updateUI()
        updateBtnList()
    }

    Connections
    {
        target: cppPhoneAdaptor
        onSigPhoneCallStateUpdated:
        {
            cppPhoneApp.qmlLog("PhoneActiveCallScreen.qml : onSigPhoneCallStateUpdated")
            updateUI()
        }
    }

    onPrHandsfreeModeStatusChanged:
    {
        switch(prPhoneCallState)
        {
        case PhoneEnum.PHONE_CALLSTATE_ACTIVE_CALL_AND_INCOMING_CALL:
        case PhoneEnum.PHONE_CALLSTATE_ACTIVE_CALL:
        case PhoneEnum.PHONE_CALLSTATE_HELD_CALL_AND_INCOMING_CALL:
        case PhoneEnum.PHONE_CALLSTATE_HELD_CALL:
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_INCOMING_CALL:
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE:
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_ONHOLD_AND_INCOMING_CALL:
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_ONHOLD:
        case PhoneEnum.PHONE_CALLSTATE_ACTIVE_CALL_AND_HELD_CALL:
        case PhoneEnum.PHONE_CALLSTATE_ACTIVE_CALL_AND_CONFERENCE_ONHOLD:
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_HELD_CALL:
            idMuteBtn.enabled = prHandsfreeModeStatus;
            break;
        default:
            //do nothing
            break;
        }
    }

    function updateBtnList()
    {
        cppPhoneApp.qmlLog("updateBtnList idRREHelper" + idRREHelper.prCurrentRREIndex)

        idRREHelper.resetItemList();
        var btnList = [idHandSetBtn, idNumPadBtn, idHoldBtn, idResumeBtn,idSwapBtn, idEndBtn, idAddCallBtn, idMergeBtn, idMuteBtn, idParticipantBtn]
        idRREHelper.setItemList(btnList);
    }

    function updateUI()
    {
        resetPhoneCallUI();
        idRREHelper.setCurrentRreIndex(-1);
        switch(prPhoneCallState)
        {
        case PhoneEnum.PHONE_CALLSTATE_ACTIVE_CALL_AND_INCOMING_CALL:
        case PhoneEnum.PHONE_CALLSTATE_ACTIVE_CALL:
            updateActiveCallUI();
            break;
        case PhoneEnum.PHONE_CALLSTATE_HELD_CALL_AND_INCOMING_CALL:
        case PhoneEnum.PHONE_CALLSTATE_HELD_CALL:
            updateHoldCallUI();
            break;
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_INCOMING_CALL:
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE:
            updateConferenceActiveCallUI();
            break;
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_ONHOLD_AND_INCOMING_CALL:
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_ONHOLD:
            updateConferenceHoldCallUI();
            break;
        case PhoneEnum.PHONE_CALLSTATE_ACTIVE_CALL_AND_HELD_CALL:
            updateActiveAndHoldCallUI();;
            break;
        case PhoneEnum.PHONE_CALLSTATE_ACTIVE_CALL_AND_CONFERENCE_ONHOLD:
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_HELD_CALL:
            updateConferenceActiveAndHoldCallUI();
            break;
        case PhoneEnum.PHONE_CALLSTATE_DIALING:
        case PhoneEnum.PHONE_CALLSTATE_ALERTING:
            updateOutGoingCallUI();
            break;
        case PhoneEnum.PHONE_CALLSTATE_ACTIVE_CALL_AND_DIALING:
        case PhoneEnum.PHONE_CALLSTATE_ACTIVE_CALL_AND_ALERTING:
            updateActiveAndOutgoingCallUI();
            break;
        case PhoneEnum.PHONE_CALLSTATE_HELD_CALL_AND_DIALING:
        case PhoneEnum.PHONE_CALLSTATE_HELD_CALL_AND_ALERTING:
            updateHoldAndOutgoingCallUI();
            break;
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_DIALING:
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_ALERTING:
            updateConferenceActiveAndOutgoingCallUI();
            break;
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_ONHOLD_AND_DIALING:
        case PhoneEnum.PHONE_CALLSTATE_CONFERENCE_ONHOLD_AND_ALERTING:
            updateConferenceHoldAndOutgoingCallUI();
            break;
        case PhoneEnum.PHONE_CALLSTATE_ALL_CALLS_TERMINATED:
            updateEndCallUI();
            break;
        default:
            break;
        }
    }

    function resetPhoneCallUI()
    {
        cppPhoneApp.qmlLog("updateUI resetPhoneCallUI")

        idFirstCallerProfileImage.visible = false;
        idSecondCallerProfileImage.visible = false;

        idFirstCallerName.visible = false;
        idFirstCallerNumber.visible = false;
        idFirstCallDuration.visible = false;
        idSecondCallerName.visible = false;
        idSecondCallerDuration.visible = false;

        idFirstCallerName.enabled = false;
        idFirstCallerNumber.enabled = false;
        idFirstCallDuration.enabled = false;
        idSecondCallerName.enabled = false;
        idSecondCallerDuration.enabled = false;

        idHandSetBtn.visible = false;
        idNumPadBtn.visible = false;
        idHoldBtn.visible = false;
        idEndBtn.visible = false;
        idAddCallBtn.visible = false;
        idMuteBtn.visible = false;
        idSwapBtn.visible = false;
        idMergeBtn.visible = false;
        idParticipantBtn.visible = false;
        idResumeBtn.visible = false;


        idHandSetBtn.enabled = false;
        idNumPadBtn.enabled = false;
        idHoldBtn.enabled = false;
        idEndBtn.enabled = false;
        idAddCallBtn.enabled = false;
        idMuteBtn.enabled = false;
        idSwapBtn.enabled = false;
        idMergeBtn.enabled = false;
        idParticipantBtn.enabled = false;
        idResumeBtn.enabled = false;
    }

    function updateActiveCallUI()
    {
        cppPhoneApp.qmlLog("updateUI updateActiveCallUI")

        idScreenTitle.text = qsTr("TEXT_PHONE_ACTIVE_CALL") + cppThemeMgr.languageChanged;
        idFirstCallerName.visible = true;
        idFirstCallerNumber.visible = (cppPhoneAdaptor.firstCallerInfo.callerName !== "");
        idFirstCallDuration.visible = true;

        idFirstCallerName.enabled = true;
        idFirstCallerNumber.enabled = true;
        idFirstCallDuration.enabled = true;

        idFirstCallerProfileImage.visible = true;

        idHandSetBtn.visible = true;
        idNumPadBtn.visible = true;
        idHoldBtn.visible = true;
        idEndBtn.visible = true;
        idAddCallBtn.visible = true;
        idMuteBtn.visible = true;
        idParticipantBtn.visible = true;

        idHandSetBtn.enabled = true;
        idNumPadBtn.enabled = true;
        idHoldBtn.enabled = true;
        idEndBtn.enabled = true;
        idAddCallBtn.enabled = true;
        idMuteBtn.enabled = prHandsfreeModeStatus;
        idParticipantBtn.enabled = false;

    }

    function updateHoldCallUI()
    {
        cppPhoneApp.qmlLog("updateUI updateHoldCallUI")

        idScreenTitle.text = qsTr("TEXT_PHONE_ACTIVE_CALL") + cppThemeMgr.languageChanged;

        idFirstCallerName.visible = true;
        idFirstCallerNumber.visible = (cppPhoneAdaptor.firstCallerInfo.callerName !== "");
        idFirstCallDuration.visible = true;

        idFirstCallerName.enabled = false;
        idFirstCallerNumber.enabled = false;
        idFirstCallDuration.enabled = true;

        idFirstCallerProfileImage.visible = true;

        idHandSetBtn.visible = true;
        idNumPadBtn.visible = true;
        idResumeBtn.visible = true;
        idEndBtn.visible = true;
        idAddCallBtn.visible = true;
        idMuteBtn.visible = true;
        idParticipantBtn.visible = true;

        idHandSetBtn.enabled = true;
        idNumPadBtn.enabled = true;
        idResumeBtn.enabled = true;
        idEndBtn.enabled = true;
        idAddCallBtn.enabled = true;
        idMuteBtn.enabled = prHandsfreeModeStatus;
        idParticipantBtn.enabled = false;
    }

    function updateEndCallUI()
    {
        cppPhoneApp.qmlLog("updateUI updateEndCallUI")

        idScreenTitle.text = qsTr("TEXT_PHONE_CALL_ENDED") + cppThemeMgr.languageChanged;

        idFirstCallerName.visible = true;
        idFirstCallerNumber.visible = (cppPhoneAdaptor.firstCallerInfo.callerName !== "");
        idFirstCallDuration.visible = true;

        idFirstCallerName.enabled = true;
        idFirstCallerNumber.enabled = true;
        idFirstCallDuration.enabled = true;

        idFirstCallerProfileImage.visible = true;
    }

    function updateOutGoingCallUI()
    {
        cppPhoneApp.qmlLog("updateUI updateOutGoingCallUI")

        idScreenTitle.text = qsTr("TEXT_PHONE_OUTGOING_CALL") + cppThemeMgr.languageChanged;

        idFirstCallerName.visible = true;
        idFirstCallerNumber.visible = (cppPhoneAdaptor.firstCallerInfo.callerName !== "");
        idFirstCallDuration.visible = true;

        idFirstCallerName.enabled = true;
        idFirstCallerNumber.enabled = true;
        idFirstCallDuration.enabled = true;

        idFirstCallerProfileImage.visible = true;

        idHandSetBtn.visible = true;
        idNumPadBtn.visible = true;
        idHoldBtn.visible = true;
        idEndBtn.visible = true;
        idAddCallBtn.visible = true;
        idMuteBtn.visible = true;
        idParticipantBtn.visible = true;

        idEndBtn.enabled = true;
        idHandSetBtn.enabled = true;
    }

    function updateConferenceActiveCallUI()
    {
        cppPhoneApp.qmlLog("updateUI updateConferenceActiveCallUI")

        idScreenTitle.text = qsTr("TEXT_PHONE_ACTIVE_CALL") + cppThemeMgr.languageChanged;

        idFirstCallerName.visible = true;
        idFirstCallerNumber.visible = true;
        idFirstCallDuration.visible = true;

        idFirstCallerName.enabled = true;
        idFirstCallerNumber.enabled = true;
        idFirstCallDuration.enabled = true;

        idFirstCallerProfileImage.visible = true;

        idHandSetBtn.visible = true;
        idNumPadBtn.visible = true;
        idHoldBtn.visible = true;
        idEndBtn.visible = true;
        idAddCallBtn.visible = true;
        idMuteBtn.visible = true;
        idParticipantBtn.visible = true;

        idHandSetBtn.enabled = true;
        idNumPadBtn.enabled = true;
        idHoldBtn.enabled = true;
        idEndBtn.enabled = true;
        idAddCallBtn.enabled = true;
        idMuteBtn.enabled = prHandsfreeModeStatus;
        idParticipantBtn.enabled = true;

    }

    function updateConferenceHoldCallUI()
    {
        cppPhoneApp.qmlLog("updateUI updateConferenceHoldCallUI")

        idScreenTitle.text = qsTr("TEXT_PHONE_ACTIVE_CALL") + cppThemeMgr.languageChanged;

        idFirstCallerName.visible = true;
        idFirstCallerNumber.visible = true;
        idFirstCallDuration.visible = true;

        idFirstCallerName.enabled = false;
        idFirstCallerNumber.enabled = false;
        idFirstCallDuration.enabled = true;

        idFirstCallerProfileImage.visible = true;

        idHandSetBtn.visible = true;
        idNumPadBtn.visible = true;
        idResumeBtn.visible = true;
        idEndBtn.visible = true;
        idAddCallBtn.visible = true;
        idMuteBtn.visible = true;
        idParticipantBtn.visible = true;

        idHandSetBtn.enabled = true;
        idNumPadBtn.enabled = true;
        idResumeBtn.enabled = true;
        idEndBtn.enabled = true;
        idAddCallBtn.enabled = true;
        idMuteBtn.enabled = prHandsfreeModeStatus;
        idParticipantBtn.enabled = true;
    }

    function updateActiveAndHoldCallUI()
    {
        cppPhoneApp.qmlLog("updateUI updateActiveAndHoldCallUI")

        idScreenTitle.text = qsTr("TEXT_PHONE_ACTIVE_CALL") + cppThemeMgr.languageChanged;

        idFirstCallerName.visible = true;
        idFirstCallerNumber.visible = true;
        idSecondCallerName.visible = true;
        idSecondCallerDuration.visible = true;

        idFirstCallerName.enabled = !(cppPhoneAdaptor.firstCallerInfo.callerState === PhoneEnum.CALLER_ON_HOLD);
        idFirstCallerNumber.enabled = true;

        idSecondCallerName.enabled = !(cppPhoneAdaptor.secondCallerInfo.callerState === PhoneEnum.CALLER_ON_HOLD);
        idSecondCallerDuration.enabled = true;

        idFirstCallerProfileImage.visible = true;
        idSecondCallerProfileImage.visible = true;

        idHandSetBtn.visible = true;
        idNumPadBtn.visible = true;
        idSwapBtn.visible = true;
        idEndBtn.visible = true;
        idMergeBtn.visible = true;
        idMuteBtn.visible = true;
        idParticipantBtn.visible = true;

        idHandSetBtn.enabled = true;
        idNumPadBtn.enabled = true;
        idSwapBtn.enabled = true;
        idEndBtn.enabled = true;
        idMergeBtn.enabled = true;
        idMuteBtn.enabled = prHandsfreeModeStatus;
        idParticipantBtn.enabled = false;
    }

    function updateActiveAndOutgoingCallUI()
    {
        cppPhoneApp.qmlLog("updateUI updateActiveAndOutgoingCallUI")

        idScreenTitle.text = qsTr("TEXT_PHONE_ACTIVE_CALL") + cppThemeMgr.languageChanged;

        idFirstCallerName.visible = true;
        idFirstCallerNumber.visible = true;
        idSecondCallerName.visible = true;
        idSecondCallerDuration.visible = true;

        idFirstCallerName.enabled = true;
        idFirstCallerNumber.enabled = true;
        idSecondCallerName.enabled = (cppPhoneAdaptor.secondCallerInfo.callerState === PhoneEnum.CALLER_ACTIVE);
        idSecondCallerDuration.enabled = true;

        idFirstCallerProfileImage.visible = true;
        idSecondCallerProfileImage.visible = true;

        idHandSetBtn.visible = true;
        idNumPadBtn.visible = true;
        idHoldBtn.visible = true;
        idEndBtn.visible = true;
        idAddCallBtn.visible = true;
        idMuteBtn.visible = true;
        idParticipantBtn.visible = true;


        idEndBtn.enabled = true;
        idHandSetBtn.enabled = true;
    }

    function updateHoldAndOutgoingCallUI()
    {
        cppPhoneApp.qmlLog("updateUI updateHoldAndOutgoingCallUI")

        idScreenTitle.text = qsTr("TEXT_PHONE_ACTIVE_CALL") + cppThemeMgr.languageChanged;

        idFirstCallerName.visible = true;
        idFirstCallerNumber.visible = true;
        idSecondCallerName.visible = true;
        idSecondCallerDuration.visible = true;

        idFirstCallerName.enabled = false;
        idFirstCallerNumber.enabled = true;
        idSecondCallerName.enabled = true;
        idSecondCallerDuration.enabled = true;

        idFirstCallerProfileImage.visible = true;
        idSecondCallerProfileImage.visible = true;

        idHandSetBtn.visible = true;
        idNumPadBtn.visible = true;
        idResumeBtn.visible = true;
        idEndBtn.visible = true;
        idAddCallBtn.visible = true;
        idMuteBtn.visible = true;
        idParticipantBtn.visible = true;


        idEndBtn.enabled = true;
        idHandSetBtn.enabled = true;
    }

    function updateConferenceActiveAndHoldCallUI()
    {
        cppPhoneApp.qmlLog("updateUI updateConferenceActiveAndHoldCallUI")

        idScreenTitle.text = qsTr("TEXT_PHONE_ACTIVE_CALL") + cppThemeMgr.languageChanged;

        idFirstCallerName.visible = true;
        idFirstCallerNumber.visible = true;
        idSecondCallerName.visible = true;
        idSecondCallerDuration.visible = true;

        idFirstCallerName.enabled = (cppPhoneAdaptor.firstCallerInfo.callerState === PhoneEnum.CALLER_ACTIVE);
        idFirstCallerNumber.enabled = true;
        idSecondCallerName.enabled = (cppPhoneAdaptor.secondCallerInfo.callerState === PhoneEnum.CALLER_ACTIVE);
        idSecondCallerDuration.enabled = true;

        idFirstCallerProfileImage.visible = true;
        idSecondCallerProfileImage.visible = true;

        idHandSetBtn.visible = true;
        idNumPadBtn.visible = true;
        idSwapBtn.visible = true;
        idEndBtn.visible = true;
        idMergeBtn.visible = true;
        idMuteBtn.visible = true;
        idParticipantBtn.visible = true;

        idHandSetBtn.enabled = true;
        idNumPadBtn.enabled = true;
        idSwapBtn.enabled = true;
        idEndBtn.enabled = true;
        idMergeBtn.enabled = true;
        idMuteBtn.enabled = prHandsfreeModeStatus;
        idParticipantBtn.enabled = true;
    }

    function updateConferenceActiveAndOutgoingCallUI()
    {
        cppPhoneApp.qmlLog("updateUI updateConferenceActiveAndOutgoingCallUI")

        idScreenTitle.text = qsTr("TEXT_PHONE_ACTIVE_CALL") + cppThemeMgr.languageChanged;

        idFirstCallerName.visible = true;
        idFirstCallerNumber.visible = true;
        idSecondCallerName.visible = true;
        idSecondCallerDuration.visible = true;

        idFirstCallerName.enabled = true;
        idFirstCallerNumber.enabled = true;
        idSecondCallerName.enabled = true;
        idSecondCallerDuration.enabled = true;

        idFirstCallerProfileImage.visible = true;
        idSecondCallerProfileImage.visible = true;

        idHandSetBtn.visible = true;
        idNumPadBtn.visible = true;
        idHoldBtn.visible = true;
        idEndBtn.visible = true;
        idAddCallBtn.visible = true;
        idMuteBtn.visible = true;
        idParticipantBtn.visible = true;

        idHandSetBtn.enabled = true;
        idEndBtn.enabled = true;
        idParticipantBtn.enabled = true;
    }

    function updateConferenceHoldAndOutgoingCallUI()
    {
        cppPhoneApp.qmlLog("updateUI updateConferenceHoldAndOutgoingCallUI")

        idFirstCallerName.visible = true;
        idFirstCallerNumber.visible = true;
        idSecondCallerName.visible = true;
        idSecondCallerDuration.visible = true;

        idFirstCallerName.enabled = false;
        idFirstCallerNumber.enabled = true;
        idSecondCallerName.enabled = true;
        idSecondCallerDuration.enabled = true;

        idFirstCallerProfileImage.visible = true;
        idSecondCallerProfileImage.visible = true;

        idHandSetBtn.visible = true;
        idNumPadBtn.visible = true;
        idResumeBtn.visible = true;
        idEndBtn.visible = true;
        idAddCallBtn.visible = true;
        idMuteBtn.visible = true;
        idParticipantBtn.visible = true;

        idHandSetBtn.enabled = true;
        idEndBtn.enabled = true;
        idParticipantBtn.enabled = true;
    }
}
