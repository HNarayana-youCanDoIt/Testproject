import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.phoneenum 1.0

BaseUI {

    property string prDialNumberText: ""

    /*
     * Image used to show number input field background
     */
    Image {
        id: idDialpadBg
        anchors {
            top: parent.top
            topMargin: 138
            left: parent.left
            leftMargin: 85
        }
        width: 630
        height: 354
        source: "qrc:/image/PhoneBrowse/Dialpad/Ph_Gfx_Dailpad1_7in_n-assets/Ph_Gfx_Dailpad1_n.png"
    }

    /*
     * HBTextInput used to show dialed number
     */
    HBTextInput {

        id: idNumPadTextInputField
        width: 300
        //todo: height will be changed after FontType issue is resolved.
        height: 45
        /**
          * Do not fix any length limit when this numpad is used as a DTMF Number pad.
         **/
        maximumLength: (!cppPhoneAdaptor.isInDTMFNumberPad ? 20 : null)
        clip: true
        /**
          * This is used to avoid the cursor present in Textinput, Since our requirement needs no cursor in Phone DialPad
         **/
        activeFocusOnPress: false

        anchors {
            top: parent.top
            topMargin: 153
            left: parent.left
            leftMargin: 217
        }
        //[Todo: Needs to be updated.]
        prFontType: ThemeMgr.FONTTYPE_T45_C1_WHITE
        horizontalAlignment: HBText.AlignRight
        verticalAlignment: HBText.AlignVCenter
        text: prDialNumberText
    }

    /*
     * DialPad Delete number button
     */
    MouseArea {
        id:idDialpadDelButton

        anchors {
            top: parent.top
            topMargin: 146
            left: parent.left
            leftMargin: 570
        }

        width: 46
        height: 46

        enabled: ("" !== prDialNumberText) && (!cppPhoneAdaptor.isInDTMFNumberPad)

        property string prDefaultImageURL: "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_NumDelete_7in_n-assets/Ph_Btn_NumDelete_n.png"
        property string prPressedImageURL: "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_NumDelete_7in_n-assets/Ph_Btn_NumDelete_nf.png"
        property string prDisabledImageURL: "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_NumDelete_7in_n-assets/Ph_Btn_NumDelete_nd.png"
        property bool touchAndHold: false

        // Delete icon & it's states handled here
        Image {

            width: 46
            height: 46

            visible: (source !== "") && (!cppPhoneAdaptor.isInDTMFNumberPad)
            source: (parent.enabled) ? (parent.containsPress ? (parent.prPressedImageURL) : (parent.prDefaultImageURL)) : (parent.prDisabledImageURL)
        }

        onReleased: {
            cppPhoneApp.qmlLog("PhoneDialpadScreen.qml Browse button: onReleased")

            if(touchAndHold)
            {
                //Do nothing
            }
            else
            {
                deleteDialNumber()
            }
            touchAndHold = false
        }
        onPressAndHold: {
            touchAndHold = true
            cppPhoneApp.qmlLog("PhoneDialpadScreen.qml Browse button: onPressAndHoldContinue")
            deleteAllDialNumber()
        }
    }

    /*
     * GenericButton used for Call/EndCall button
     */
    GenericButton {
        anchors {
            top: parent.top
            topMargin: 215
            left: parent.left
            leftMargin: 522
        }
        width: 86
        height: 238

        enabled: (((!cppPhoneAdaptor.isInDTMFNumberPad)
                   && (!cppPhoneAdaptor.dialReqStatus))
                  || ((cppPhoneAdaptor.isInDTMFNumberPad)
                      && (!cppPhoneAdaptor.endCallReqStatus)))

        defaultImageURL: !cppPhoneAdaptor.isInDTMFNumberPad ? "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_CallDailpad2_n-assets/Ph_Btn_CallDailpad_n.png" : "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_EndCallDailpad2_n-assets/Ph_Btn_EndCallDailpad2_n.png"
        pressedImageURL: !cppPhoneAdaptor.isInDTMFNumberPad ? "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_CallDailpad2_n-assets/Ph_Btn_CallDailpad_nf.png" : "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_EndCallDailpad2_n-assets/Ph_Btn_EndCallDailpad2_np.png"
        disabledImageURL: !cppPhoneAdaptor.isInDTMFNumberPad ? "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_CallDailpad2_n-assets/Ph_Btn_CallDailpad2_nd.png" : "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_EndCallDailpad2_n-assets/Ph_Btn_EndCallDailpad2_n.png"

        contentItem: HBText{
            width: 86
            height: 30

            anchors{
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: 40
            }
            elide: HBText.ElideNone
            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
            horizontalAlignment: HBText.AlignHCenter
            verticalAlignment: HBText.AlignVCenter
            text: parent.text
        }

        onReleased: {
            if (cppPhoneAdaptor.isInDTMFNumberPad) {
                cppUIBase.qmlLog(
                            "PhoneDialpadScreen.qml End Call button: onReleased")
                cppPhoneAdaptor.invEndPhoneCall()
            }
            else
            {
                cppUIBase.qmlLog("PhoneDialpadScreen.qml Call button: onReleased")
                if(parent.prDialNumberText === "")
                {
                    parent.prDialNumberText = (cppPhoneAdaptor.invGetLastDialedNumber())
                    cppUIBase.qmlLog("PhoneDialpadScreen.qml Call button: prDialNumberText" + parent.prDialNumberText)

                }
                else
                {
                    cppPhoneAdaptor.invDial(parent.prDialNumberText)
                }

            }
        }
    }

    /*
     * Grid used allign dial pad number buttons
     */
    Grid {
        anchors {
            left: parent.left
            leftMargin: 208
            top: parent.top
            topMargin: 211
        }
        columnSpacing: 4
        rowSpacing: 2
        columns: 3

        /*
         * Repeater used add dial pad number button in grid
         */
        Repeater {
            model: 12
            GenericButton {
                width: 100
                height: 60
                defaultImageURL: getNumPadDefaultImageURL(index)
                pressedImageURL: getNumPadPressedImageURL(index)
                disabledImageURL: getNumPadDefaultImageURL(index)

                onReleased: {
                    cppUIBase.qmlLog(
                                "PhoneDialpadScreen.qml Dialpad  button: onReleased "
                                + touchAndHold)
                    var dialedNum = ""
                    if (index === 10) {
                        if (touchAndHold) {
                            dialedNum = "+"
                        } else {
                            dialedNum = "0"
                        }
                    } else if (index === 9) {
                        dialedNum = "*"
                    } else if (index === 11) {
                        dialedNum = "#"
                    } else {
                        dialedNum = (index + 1)
                    }

                    if (cppPhoneAdaptor.isInDTMFNumberPad) {
                        cppPhoneAdaptor.invSendDtmfTone(dialedNum)
                    }

                    addDialNumber(dialedNum)
                }
            }
        }
    }

    /*
     * function to add dialed digit
     */
    function addDialNumber(number) {
        /**
        * This condition is used to avoid the extension of prDialNumberText when user enteres more than maximum length.
       */
        if(prDialNumberText.length < (idNumPadTextInputField.maximumLength)){
            prDialNumberText = prDialNumberText + number
        }
    }

    /*
     * function to delete dialed last digit
     */
    function deleteDialNumber() {
        if (prDialNumberText.length > 1) {
            prDialNumberText = prDialNumberText.substring(
                        0, (prDialNumberText.length - 1))
        } else {
            prDialNumberText = ""
        }
    }

    /**
      * When user Touch and hold Delete button, the whole NUmber text should be replaced by empty string
      */
    function deleteAllDialNumber(){
        prDialNumberText = ""
    }

    /*
     * function to get dial pad number image according to its index on dial pad
     */
    function getNumPadDefaultImageURL(index) {
        cppUIBase.qmlLog(
                    "PhoneDialpadScreen.qml getNumPadDefaultImageURL " + index)
        var ImageURL = ""
        switch (index) {
        case 0:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_Numpad1_7in_n-assets/Ph_Btn_Numpad1_7in_n.png"
            break
        case 1:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_Numpad2_7in_n-assets/Ph_Btn_Numpad2_7in_n.png"
            break
        case 2:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_Numpad3_7in_n-assets/Ph_Btn_Numpad3_7in_n.png"
            break
        case 3:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_Numpad4_7in_n-assets/Ph_Btn_Numpad4_7in_n.png"
            break
        case 4:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_Numpad5_7in_n-assets/Ph_Btn_Numpad5_7in_n.png"
            break
        case 5:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_Numpad6_7in_n-assets/Ph_Btn_Numpad6_7in_n.png"
            break
        case 6:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_Numpad7_7in_n-assets/Ph_Btn_Numpad7_7in_n.png"
            break
        case 7:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_Numpad8_7in_n-assets/Ph_Btn_Numpad8_7in_n.png"
            break
        case 8:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_Numpad9_7in_n-assets/Ph_Btn_Numpad9_7in_n.png"
            break
        case 9:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_NumpadStar_7in_n-assets/Ph_Btn_NumpadStar_7in_n.png"
            break
        case 10:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_Numpad0_7in_n-assets/Ph_Btn_Numpad0_7in_n.png"
            break
        case 11:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_NumpadHash_7in_n-assets/Ph_Btn_NumHash_7in_n.png"
            break
        }
        return ImageURL
    }

    /*
     * function to get dial pad number image according to its index on dial pad
     */
    function getNumPadPressedImageURL(index) {
        cppUIBase.qmlLog(
                    "PhoneDialpadScreen.qml getNumPadPressedImageURL " + index)
        var ImageURL = ""
        switch (index) {
        case 0:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_Numpad1_7in_n-assets/Ph_Btn_Numpad1_7in_nf.png"
            break
        case 1:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_Numpad2_7in_n-assets/Ph_Btn_Numpad2_7in_nf.png"
            break
        case 2:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_Numpad3_7in_n-assets/Ph_Btn_Numpad3_7in_nf.png"
            break
        case 3:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_Numpad4_7in_n-assets/Ph_Btn_Numpad4_7in_nf.png"
            break
        case 4:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_Numpad5_7in_n-assets/Ph_Btn_Numpad5_7in_nf.png"
            break
        case 5:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_Numpad6_7in_n-assets/Ph_Btn_Numpad6_7in_nf.png"
            break
        case 6:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_Numpad7_7in_n-assets/Ph_Btn_Numpad7_7in_nf.png"
            break
        case 7:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_Numpad8_7in_n-assets/Ph_Btn_Numpad8_7in_nf.png"
            break
        case 8:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_Numpad9_7in_n-assets/Ph_Btn_Numpad9_7in_nf.png"
            break
            //[Todo]: Image need to be updated. This image is same as Normal Image.
        case 9:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_NumpadStar_7in_n-assets/Ph_Btn_NumpadStar_7in_nf.png"
            break
        case 10:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_Numpad0_7in_n-assets/Ph_Btn_Numpad0_7in_nf.png"
            break
            //[Todo]: Image need to be updated. This image is same as Normal Image.
        case 11:
            ImageURL = "qrc:/image/PhoneBrowse/Dialpad/Ph_Btn_NumpadHash_7in_n-assets/Ph_Btn_NumHash_7in_nf.png"
            break
        }
        return ImageURL
    }

}
