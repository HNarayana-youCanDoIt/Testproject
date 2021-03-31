import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.popupenums 1.0
import QtGraphicalEffects 1.0
import "../Common"

//Theme for incoming call popup
BasePopup{

    Connections
    {
        target: PopupManager
        onSigProcessHKOnPopup: {
            cppUIBase.qmlLog("onSigProcessHKOnPopup : slot called")
            cppPhoneAdaptor.invHandleHardKeys(iKey, iKeyState)
        }
    }

    //This property holds the height of content item
    contentHeight: 432

    //This property holds the width of content item
    contentWidth: 648

    //Padding is used to set the co-orinates of Content Item
    topPadding: 24
    leftPadding: 76

    contentItem: Item{
        id: idPopupContent

        /**
         * Mouse area to prevent Popup to close when Content Item of the Popup is Touched
         */
        MouseArea{
            anchors.fill: parent
            onPressed: {
                cppUIBase.qmlLog("IncomingCallPopup.qml: Popup Content Item Touched")
                //do nothing
            }
        }

        height: 432
        width: 648
        anchors
        {
            left: parent.left
            leftMargin: 76
            top: parent.top
            topMargin:  24

        }

        Image
        {
            id: idPopupBackgroundColorPatch
            anchors.fill: parent
            source: "qrc:/image/PhoneCall/incomingCallPopup/incomingCallPopupBackGrd/Gen_Gfx_PhonePopupBgColourPatch_7in_n.png"
            ColorOverlay {
                id: idPopupBgColorOverlay
                anchors.fill: parent
                source: parent
                color:  cppThemeMgr.currentThemeColor
            }
        }

        Image
        {
            id: idPopupBackgroundOverlay
            anchors.fill: parent
            source: "qrc:/image/PhoneCall/incomingCallPopup/incomingCallPopupBackGrd/Gen_Gfx_PhonePopupBgOverlay_7in_n.png"
        }

        Image
        {
            id: idCallerImage
            width: 109
            height: 105
            anchors
            {
                left: parent.left
                leftMargin: 100
                top: parent.top
                topMargin: 121
            }
            source: cppPhoneAdaptor.incomingCallInfo.callerProfileImage

            HBText
            {
                anchors.fill: parent
                visible: (cppPhoneAdaptor.incomingCallInfo.callerProfileName !== "")
                text: cppPhoneAdaptor.incomingCallInfo.callerProfileName
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                fontType: ThemeMgr.FONTTYPE_T45_C1
            }
        }

        /**
          * HBText to hold incoming call popup title to be displayed
          **/
        HBText
        {
            id: idPopupTitle
            width: 330
            height: 25
            anchors
            {
                top: parent.top
                left: parent.left
                topMargin: 37
                leftMargin: 145
            }
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            fontType: ThemeMgr.FONTTYPE_T35_C3
            //TODO: Popup string id should be added instead of static text.
            text:qsTr("TEXT_PHONE_INCOMING_CALL") + cppThemeMgr.languageChanged
        }

        /**
          * HBText to hold text to be displayed on popup
          **/
        HBText
        {
            id: idCallerName
            width: 301
            height: 25
            anchors
            {
                top: parent.top
                left: parent.left
                topMargin: 131
                leftMargin: 228
            }
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignLeft
            fontType: ThemeMgr.FONTTYPE_T35_BK_C2
            text: (cppPhoneAdaptor.incomingCallInfo.callerName !== "") ? cppPhoneAdaptor.incomingCallInfo.callerName : cppPhoneAdaptor.incomingCallInfo.callerNumber
        }

        /**
          * HBText to hold text to be displayed on popup
          **/
        HBText
        {
            id: idCallerNumber
            width: 203
            height: 25
            anchors
            {
                top: parent.top
                left: parent.left
                topMargin: 192
                leftMargin: 228
            }
            visible: (cppPhoneAdaptor.incomingCallInfo.callerName !== "")
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignLeft
            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
            text: cppPhoneAdaptor.incomingCallInfo.callerNumber
        }

        RREHelper
        {
            id: idRREHelper
            isPopup: true
            Component.onCompleted:
            {
                cppPhoneApp.qmlLog("RreFocus.qml Component onCompleted")
            }
        }

        /**
          * First GenericButton for popup
          **/
        GenericButton
        {
            id: idFirstBtn
            contentItem: HBText
            {
                id: idFirstBtnText
                anchors
                {
                    bottom: parent.bottom
                    horizontalCenter: parent.horizontalCenter
                }
                visible: (text !== "")

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignBottom
                fontType: parent.enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
                text: qsTr(parent.text)
                elide: Text.ElideNone
            }
            prRREImageSrc: "qrc:/Assets/RREFocus/Popup_Ico_RRE_Btn_7in_np.png"
            prRREImageVerticalOffset: -10

            /*
             * Image for shortcut
             */
            background: Image
            {
                visible: (source !== "")
                anchors
                {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                    verticalCenterOffset: -10
                }
                source: parent.enabled ? (parent.pressed ? parent.pressedImageURL : parent.defaultImageURL) : parent.disabledImageURL
            }

            defaultImageURL :  "qrc:/image/PhoneCall/phoneCallMainPopup/Ph_Btn_IncomingCall_7in_n-assets/Ph_Ico_IncomingCall_n.png"
            pressedImageURL :  "qrc:/image/PhoneCall/phoneCallMainPopup/Ph_Btn_IncomingCall_7in_n-assets/Ph_Ico_IncomingCall_nf.png"
            disabledImageURL: "qrc:/image/PhoneCall/phoneCallMainPopup/Ph_Btn_IncomingCall_7in_n-assets/Ph_Ico_IncomingCall_nd.png"

            text: qsTr("TEXT_PHONE_ACCEPT_CALL") + cppThemeMgr.languageChanged

            enabled: !(cppPhoneAdaptor.rejectCallReqStatus || cppPhoneAdaptor.acceptCallReqStatus)

            width: 76
            height: 76
            anchors
            {
                top: parent.top
                left: parent.left
                topMargin: 318
                leftMargin: 70
            }

            onPressed: {
                idRREHelper.setCurrentRreIndex(-1)
            }

            onReleased:
            {
                PopupManager.ePopupResult = PopupEnum.EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS
                cppPhoneAdaptor.invAcceptIncomingCall()
            }

        }

        /**
          * Second GenericButton for popup
          **/
        GenericButton
        {
            id: idSecondBtn
            contentItem: HBText
            {
                id:idSecondBtnText
                visible: (text !== "")
                anchors
                {
                    bottom: parent.bottom
                    horizontalCenter: parent.horizontalCenter
                }
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignBottom
                fontType: parent.enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
                text: qsTr(parent.text)
                elide: Text.ElideNone
            }

            prRREImageSrc: "qrc:/Assets/RREFocus/Popup_Ico_RRE_Btn_7in_np.png"
            prRREImageVerticalOffset: -10

            /*
             * Image for shortcut
             */
            background: Image
            {
                visible: (source !== "")
                anchors
                {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                    verticalCenterOffset: -10
                }
                source: parent.enabled ? (parent.pressed ? parent.pressedImageURL : parent.defaultImageURL) : parent.disabledImageURL
            }


            defaultImageURL: "qrc:/image/PhoneCall/incomingCallPopup/Ph_Btn_EndCallMessage_7in_n-assets/Ph_Btn_EndCallMessage_n.png"
            pressedImageURL: "qrc:/image/PhoneCall/incomingCallPopup/Ph_Btn_EndCallMessage_7in_n-assets/Ph_Btn_EndCallMessage_nf.png"
            disabledImageURL: "qrc:/image/PhoneCall/incomingCallPopup/Ph_Btn_EndCallMessage_7in_n-assets/Ph_Btn_EndCallMessage_nd.png"


            enabled: (cppPhoneAdaptor.isSendingSMSAllowed &&
                      !(cppPhoneAdaptor.rejectCallReqStatus || cppPhoneAdaptor.sendSMSReqStatus || cppPhoneAdaptor.acceptCallReqStatus))
            //TODO: Popup string id should be added instead of static text.
            text: qsTr("TEXT_PHONE_REJECT_CALL_WITH_SMS") + cppThemeMgr.languageChanged

            width: 76
            height: 76
            anchors
            {
                top: parent.top
                left: parent.left
                topMargin: 318
                leftMargin: 285
            }


            onPressed: {
                idRREHelper.setCurrentRreIndex(-1)
            }

            onReleased:
            {
                PopupManager.ePopupResult = PopupEnum.EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS
                cppPhoneAdaptor.invRejectIncomingCallWithSMS()
            }
        }

        /**
          * Third GenericButton for popup
          **/
        GenericButton
        {
            id: idThirdBtn
            contentItem: HBText
            {
                id: idText
                visible: (text !== "")
                anchors
                {
                    bottom: parent.bottom
                    horizontalCenter: parent.horizontalCenter
                }
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignBottom
                fontType: parent.enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
                text: qsTr(parent.text)
                elide: Text.ElideNone
            }

            prRREImageSrc: "qrc:/Assets/RREFocus/Popup_Ico_RRE_Btn_7in_np.png"
            prRREImageVerticalOffset: -10

            /*
             * Image for shortcut
             */
            background: Image
            {
                visible: (source !== "")
                anchors
                {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                    verticalCenterOffset: -10
                }
                source: parent.enabled ? (parent.pressed ? parent.pressedImageURL : parent.defaultImageURL) : parent.disabledImageURL
            }

            defaultImageURL : "qrc:/image/PhoneCall/phoneCallMainPopup/Ph_Btn_EndCallSmall_7in_n-assets/Ph_Btn_EndCallSmall_n.png"
            pressedImageURL : "qrc:/image/PhoneCall/phoneCallMainPopup/Ph_Btn_EndCallSmall_7in_n-assets/Ph_Btn_EndCallSmall_nf.png"
            disabledImageURL: "qrc:/image/PhoneCall/phoneCallMainPopup/Ph_Btn_EndCallSmall_7in_n-assets/Ph_Btn_EndCallSmall_nd.png"

            text: qsTr("TEXT_PHONE_REJECT_CALL") + cppThemeMgr.languageChanged
            width: 76
            height: 76
            enabled: !(cppPhoneAdaptor.rejectCallReqStatus || cppPhoneAdaptor.acceptCallReqStatus)

            anchors
            {
                top: parent.top
                left: parent.left
                topMargin: 318
                leftMargin: 500
            }

            onPressed: {
                idRREHelper.setCurrentRreIndex(-1)
            }

            onReleased:
            {
                PopupManager.ePopupResult = PopupEnum.EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS
                cppPhoneAdaptor.invRejectIncomingCall()
            }
        }
    }

    Component.onCompleted:
    {
        cppPhoneApp.qmlLog("IncomingCallPopup.qml : Component.onCompleted")
        updateBtnList()
    }

    function updateBtnList()
    {
        cppPhoneApp.qmlLog("updateBtnList idRREHelper" + idRREHelper.prCurrentRREIndex)

        idRREHelper.resetItemList();
        var btnList = [idFirstBtn, idSecondBtn, idThirdBtn]
        idRREHelper.setItemList(btnList);
    }
}
