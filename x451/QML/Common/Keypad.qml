import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.phoneenum 1.0
import com.harman.qml.thememanager 1.0
import QtGraphicalEffects 1.0

Item {
    id: idKeypad

    /* Property to find the KeyPadState */
    property int prKeyPadState: PhoneEnum.KEYPAD_STATE_SMALL

    /* Property to find the KeyPadLastState */
    property int prKeyPadLastState: PhoneEnum.KEYPAD_STATE_SMALL

    /* Property to find the TextInputState */
    property int prTextInputState: PhoneEnum.TEXTINPUT_DEFAULT_TEXT

    /* Property to hold index of CapsLock Button */
    property int prIndexForCapsLockButton: 20

    /* Property to hold index of Space Button */
    property int prIndexForSpaceButton: 30

    /* Property to hold index of Numeric Button */
    property int prIndexForNumericToggleButton: 31

    /* Property to hold  Max no of characters that can be put in a Text Input Field */
    property int prMaxCharsInInputField: 120

    /* Property to disable & enable keypad buttons based on number of char's in the textinput field */
    property bool prCanAddNewChar: (idCustomText.length < prMaxCharsInInputField)

    /* Property for the initial text to be displayed if there is no input provided */
    property string prInitialText: qsTr("TEXT_GENERIC_ENTER_TEXT_HERE") + cppThemeMgr.languageChanged

    /* Property alias for Save Button */
    property alias prSaveBtn : idSaveBtn

    /* Property alias for Custom Text input */
    property alias prCustomText : idCustomText

    /* function to load keypad based on state & button index */
    function fnLoadKeyPadDefaultImage(keyPadState, buttonIndex)
    {
        var defaultImagePath = "";

        switch(keyPadState) {

        case PhoneEnum.KEYPAD_STATE_CAPITAL:
            defaultImagePath = cppPhoneAdaptor.getKeyButtonDefaultImageCapital(buttonIndex);
            break;

        case PhoneEnum.KEYPAD_STATE_SMALL:
            defaultImagePath =  cppPhoneAdaptor.getKeyButtonDefaultImageSmall(buttonIndex);
            break;

        case PhoneEnum.KEYPAD_STATE_NUMERIC:
            defaultImagePath =  cppPhoneAdaptor.getKeyButtonDefaultImageNumeric(buttonIndex);
            break;

        default:
            cppPhoneApp.qmlLog("Keypad.qml - fnLoadKeyPadDefaultImage default case: " + buttonIndex);
            defaultImagePath = "";
            break;
        }

        return defaultImagePath;
    }

    /* function to load disabled image keypad, based on state & button index */
    function fnLoadKeyPadDisabledImage(keyPadState, buttonIndex)
    {
        var disabledImagePath = "";

        switch(keyPadState) {

        case PhoneEnum.KEYPAD_STATE_CAPITAL:
            disabledImagePath = cppPhoneAdaptor.getKeyButtonDisabledImageCapital(buttonIndex);
            break;

        case PhoneEnum.KEYPAD_STATE_SMALL:
            disabledImagePath = cppPhoneAdaptor.getKeyButtonDisabledImageSmall(buttonIndex);
            break;

        case PhoneEnum.KEYPAD_STATE_NUMERIC:
            disabledImagePath =  cppPhoneAdaptor.getKeyButtonDisabledImageNumeric(buttonIndex);
            break;

        default:
            cppPhoneApp.qmlLog("Keypad.qml - fnLoadKeyPadDisabledImage default case: " + buttonIndex);
            disabledImagePath = "";
            break;
        }

        return  disabledImagePath;
    }

    /* function to load pressed image keypad, based on state & button index */
    function fnLoadKeyPadPressedImage(keyPadState, buttonIndex) {

        var pressedImagePath = "";

        switch(keyPadState) {

        case PhoneEnum.KEYPAD_STATE_CAPITAL:
            pressedImagePath = cppPhoneAdaptor.getKeyButtonPressedImageCapital(buttonIndex);
            break;

        case PhoneEnum.KEYPAD_STATE_SMALL:
            pressedImagePath = cppPhoneAdaptor.getKeyButtonPressedImageSmall(buttonIndex);
            break;

        case PhoneEnum.KEYPAD_STATE_NUMERIC:
            pressedImagePath = cppPhoneAdaptor.getKeyButtonPressedImageNumeric(buttonIndex);
            break;

        default:
            cppPhoneApp.qmlLog("Keypad.qml - fnLoadKeyPadPressedImage default case: " + buttonIndex);
            pressedImagePath = "";
            break;
        }

        return pressedImagePath;
    }

    /* function to delete characters */
    function fnDeleteChar() {
        if (idCustomText.text.length > 1)
        {
            idCustomText.remove(idCustomText.cursorPosition - 1,idCustomText.cursorPosition)
        }
        else
        {
            idCustomText.clear()
        }
        checkMessageStringForOnlySpaces(idCustomText.text)
    }

    /* function to clear all the characters in text input area */
    function fnClearAll() {

        idDeleteBtn.enabled = false
        idSaveBtn.enabled = false
        idCustomText.enabled = false

        idCustomText.clear()
        idCustomText.insert(idCustomText.cursorPosition, prInitialText)


        prKeyPadState = PhoneEnum.KEYPAD_STATE_CAPITAL
        prKeyPadLastState = PhoneEnum.KEYPAD_STATE_CAPITAL

        prTextInputState = PhoneEnum.TEXTINPUT_EMPTY_TEXT
        idCustomText.cursorPosition = 0
    }

    function updateTextInput(keyState, keyIndex)
    {
        if(PhoneEnum.TEXTINPUT_EMPTY_TEXT === prTextInputState)
        {
            prTextInputState = PhoneEnum.TEXTINPUT_TYPING_TEXT

            idCustomText.clear()
            idCustomText.insert(idCustomText.cursorPosition, (cppPhoneAdaptor.getClickedCharacter(prKeyPadState, (keyIndex - 1))))

            if(PhoneEnum.KEYPAD_STATE_CAPITAL === prKeyPadState)
            {
                prKeyPadState = PhoneEnum.KEYPAD_STATE_SMALL
                prKeyPadLastState = PhoneEnum.KEYPAD_STATE_SMALL
            }
        }
        else
        {
            idCustomText.insert(idCustomText.cursorPosition, (cppPhoneAdaptor.getClickedCharacter(prKeyPadState, (keyIndex - 1))))

        }

        if(!idDeleteBtn.enabled)
        {
            idDeleteBtn.enabled = true
        }
        if(!idCustomText.enabled) {

            idCustomText.enabled = true
        }
        checkMessageStringForOnlySpaces(idCustomText.text)
    }

    /**
      * Function to check whether the message string contains only spaces, If yes then Disable the Save Button else Enable the save button
      **/
    function checkMessageStringForOnlySpaces(messageString)
    {
        idSaveBtn.enabled = (/\S/.test(messageString));
    }

    /**
      * Image for Keypad Background covering other transparent area.
    **/
    Image {
        id: idKeypadBackground
        source: "qrc:/image/Popup/PopupBg/Gen_Gfx_PopupOverlayBg_n.png"
    }

    /**
      * Image for the Shodow as a background
     **/
    Image {
        id: idShadow
        source: "qrc:/image/KeyPad/Gfx_Set_Keypad_7in_Shadow.png"
    }

    /* Keypad background image */
    Image {
        id:idColorPatch
        source: "qrc:/image/KeyPad/Gfx_Set_Keypad_7in_Colorbg.png"
        ColorOverlay {
            id: idGenericButtonColorOverlay
            anchors.fill: parent
            source: parent
            color:  cppThemeMgr.currentThemeColor
        }

        MouseArea{
            anchors.fill: parent
        }
    }


    Image{
        source: "qrc:/image/KeyPad/Gfx_Set_Keypad_Overlay_7in_lyt-assets/Gfx_Set_Keypad_Overlay_lyt.png"

        MouseArea{
            anchors.fill: parent
        }
    }

    /* Delete button */
    MouseArea {
        id: idDeleteBtn
        anchors {
            top: parent.top
            topMargin: 43
            left: parent.left
            leftMargin: 703
        }
        width: 53
        height: 53

        property string prDefaultImageURL: "qrc:/image/KeyPad/Gen_Set_Ico_Delete_7in_n-assets/Gen_Set_Ico_Delete_7in_n.png"
        property string prPressedImageURL: "qrc:/image/KeyPad/Gen_Set_Ico_Delete_7in_n-assets/Gen_Set_Ico_Delete_7in_nf.png"
        property string prDisabledImageURL: "qrc:/image/KeyPad/Gen_Set_Ico_Delete_7in_n-assets/Gen_Set_Ico_Delete_7in_nd.png"
        property bool touchAndHold: false

        // short press handled here
        onReleased: {
            if(touchAndHold)
            {
                //Do nothing
            }
            else
            {
                if(true === containsMouse) {
                    fnDeleteChar()
                    if("" === idCustomText.text) {
                        fnClearAll()
                    }
                }
            }
            touchAndHold = false
        }

        // Delete icon & it's states handled here
        Image {
            visible: (source !== "")
            source: (parent.enabled) ? (parent.containsPress ? (parent.prPressedImageURL) : (parent.prDefaultImageURL)) : (parent.prDisabledImageURL)
        }


        onPressAndHold: {
            touchAndHold = true
            fnClearAll()
        }
    }

    /* Cancel button */
    GenericButton {
        id: idCancelBtn

        width: 120
        height: 49

        defaultImageURL : "qrc:/image/KeyPad/Set_Btn_KeyPad_Cancel_n-assets/Set_Btn_KeyPad_Cancel_n.png"
        pressedImageURL : "qrc:/image/KeyPad/Set_Btn_KeyPad_Cancel_n-assets/Set_Btn_KeyPad_Cancel_nf.png"
        disabledImageURL: "qrc:/image/KeyPad/Set_Btn_KeyPad_Cancel_n-assets/Set_Btn_KeyPad_Cancel_nd.png"

        anchors {
            top: parent.top
            topMargin: 379
            left: parent.left
            leftMargin: 281
        }

        //Cancel button handling: Closing keypad, moving to SETUP_SCREEN_CONFIGURE_AUTO_SMS screen
        onReleased: {
            cppSetupApp.raiseSMEvent("Keypad", "Back")
        }
    }

    /* Save button */
    GenericButton {
        id: idSaveBtn

        defaultImageURL : "qrc:/image/KeyPad/Set_Btn_KeyPad_Save_n-assets/Set_Btn_KeyPad_Save_n.png"
        pressedImageURL : "qrc:/image/KeyPad/Set_Btn_KeyPad_Save_n-assets/Set_Btn_KeyPad_Save_nf.png"
        disabledImageURL: "qrc:/image/KeyPad/Set_Btn_KeyPad_Save_n-assets/Set_Btn_KeyPad_Save_nd.png"

        width: 120
        height: 49

        anchors {
            top: parent.top
            topMargin: 379
            left: parent.left
            leftMargin: 402
        }

        onReleased: {
            //Save button handling: Closing keypad, moving to Phone Setup screen
            cppPhoneAdaptor.saveButtonClicked(idCustomText.text)
            cppSetupApp.raiseSMEvent("Keypad", "Back")
        }
    }

    /* Text input used for to show custom message typed */
    HBTextInput {
        id: idCustomText

        //[todo]: This has to be changed once assets are available
        width: 573
        height: 33

        anchors {
            top: parent.top
            topMargin: 57
            left: parent.left
            leftMargin: 45
        }

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter

        text: cppPhoneAdaptor.textInputMessage
        /**
          * Total length as per requirement is set to 120 characters.
          **/
        maximumLength: 120

        cursorDelegate: idCursor
        prFontType: (prTextInputState === PhoneEnum.TEXTINPUT_EMPTY_TEXT) ? ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED : ThemeMgr.FONTTYPE_T24_LIGHT_C3

        selectByMouse: true
        cursorVisible: true
        clip: true

        /**
          * When User tries to drag the cursor on the text in InputField or click at any place then the cursor shall follow the mouse.
          **/
        MouseArea {
            anchors.fill: parent
            onClicked:
            {
                idCustomText.focus = true;
                idCustomText.cursorPosition = idCustomText.positionAt(mouse.x)
            }
            onPositionChanged: idCustomText.cursorPosition = idCustomText.positionAt(mouse.x)
        }
    }

    /* Cursor image component */
    Component {
        id: idCursor
        Image {
            width: 1
            height: 32

            //FixMe: Replace with actual image
            source: "qrc:/image/KeyPad/Gfx_Set_Keypad_Cursor-assets/Cursor_Gfx.png"

            /* Cursor blink animation */
            PropertyAnimation on opacity {
                easing.type: Easing.OutSine
                loops: Animation.Infinite
                from: 0
                to: 1.0
                duration: 750
            }
        }
    }

    /* First grid which contains 10 columns (QWERTYUIOP) */
    Grid {
        columns: 10
        anchors {
            top: parent.top
            topMargin: 91
            left:parent.left
            leftMargin: 48
        }
        columnSpacing: 1
        Repeater {
            model: parent.columns
            KeypadButton{
                enabled: prCanAddNewChar
                prKeyButtonIndex: (index + 1)
                defaultImageURL: fnLoadKeyPadDefaultImage(prKeyPadState,prKeyButtonIndex)
                pressedImageURL: fnLoadKeyPadPressedImage(prKeyPadState,prKeyButtonIndex)
                disabledImageURL: fnLoadKeyPadDisabledImage(prKeyPadState,prKeyButtonIndex)

                onReleased: {
                    /* update text in input field according to the keypad state and index */
                    updateTextInput(prKeyPadState, prKeyButtonIndex)
                }
            }
        }
    }

    /* Second grid which contains 9 columns (ASDFGHJKL) */
    Grid {
        columns: 9
        anchors {
            top: parent.top
            topMargin: 162
            left:parent.left
            leftMargin: 83
        }
        columnSpacing: 1
        Repeater {
            model: parent.columns
            KeypadButton{
                enabled: prCanAddNewChar
                prKeyButtonIndex: (index + 11)
                defaultImageURL: fnLoadKeyPadDefaultImage(prKeyPadState,prKeyButtonIndex)
                pressedImageURL: fnLoadKeyPadPressedImage(prKeyPadState,prKeyButtonIndex)
                disabledImageURL: fnLoadKeyPadDisabledImage(prKeyPadState,prKeyButtonIndex)

                onReleased: {
                    /* update text in input field according to the keypad state and index */
                    updateTextInput(prKeyPadState, prKeyButtonIndex)
                }
            }
        }
    }

    /* Third grid which contains 8 columns (Capslock,ZXCVBNM) */
    Grid {
        columns: 8
        anchors {
            top: parent.top
            topMargin: 233
            left:parent.left
            leftMargin: 84
        }
        columnSpacing: 1
        Repeater {
            model: parent.columns
            KeypadButton{
                enabled: prCanAddNewChar
                prKeyButtonIndex: index + prIndexForCapsLockButton
                defaultImageURL: fnLoadKeyPadDefaultImage(prKeyPadState,prKeyButtonIndex)
                pressedImageURL: fnLoadKeyPadPressedImage(prKeyPadState,prKeyButtonIndex)
                disabledImageURL: fnLoadKeyPadDisabledImage(prKeyPadState,prKeyButtonIndex)

                onReleased: {
                    /* If key pressed is toggle between capital & small, toggle the keypad state */
                    if(prIndexForCapsLockButton === prKeyButtonIndex)
                    {
                        if(PhoneEnum.KEYPAD_STATE_CAPITAL === prKeyPadState)
                        {
                            prKeyPadState = PhoneEnum.KEYPAD_STATE_SMALL
                            prKeyPadLastState = PhoneEnum.KEYPAD_STATE_SMALL
                        }
                        else if(PhoneEnum.KEYPAD_STATE_SMALL === prKeyPadState)
                        {
                            prKeyPadState = PhoneEnum.KEYPAD_STATE_CAPITAL
                            prKeyPadLastState = PhoneEnum.KEYPAD_STATE_CAPITAL
                        }
                        else
                        {
                            cppPhoneApp.qmlLog("Grid4 - prKeyPadState: " + prKeyPadState + "prKeyPadLastState: " + prKeyPadLastState)
                        }
                    }
                    /* If key pressed is toggle between capital & small, don't fetch character */
                    else
                    {
                        /* update text in input field according to the keypad state and index */
                        updateTextInput(prKeyPadState, prKeyButtonIndex)
                    }
                }
            }
        }
    }

    /* Forth grid which contains 4 columns (,. space numpadKey) */
    Grid {
        columns: 4
        anchors {
            top: parent.top
            topMargin: 304
            left:parent.left
            leftMargin: 153
        }
        columnSpacing: 1
        Repeater {
            model: parent.columns
            KeypadButton{
                enabled: prCanAddNewChar
                prKeyButtonIndex: index + 28
                defaultImageURL: fnLoadKeyPadDefaultImage(prKeyPadState,prKeyButtonIndex)
                pressedImageURL: fnLoadKeyPadPressedImage(prKeyPadState,prKeyButtonIndex)
                disabledImageURL: fnLoadKeyPadDisabledImage(prKeyPadState,prKeyButtonIndex)

                onReleased: {
                    /* If key pressed is toggle between numeric & alphabetic, toggle the keypad state */
                    if(prIndexForNumericToggleButton === prKeyButtonIndex)
                    {
                        if((PhoneEnum.KEYPAD_STATE_CAPITAL === prKeyPadState) || (PhoneEnum.KEYPAD_STATE_SMALL === prKeyPadState))
                        {
                            prKeyPadState = PhoneEnum.KEYPAD_STATE_NUMERIC
                        }
                        else if(PhoneEnum.KEYPAD_STATE_CAPITAL === prKeyPadLastState)
                        {
                            prKeyPadState = PhoneEnum.KEYPAD_STATE_CAPITAL
                        }
                        else if(PhoneEnum.KEYPAD_STATE_SMALL === prKeyPadLastState)
                        {
                            prKeyPadState = PhoneEnum.KEYPAD_STATE_SMALL
                        }
                        else
                        {
                            cppPhoneApp.qmlLog("Grid4 - prKeyPadState: " + prKeyPadState + "prKeyPadLastState: " + prKeyPadLastState)
                        }
                    }
                    /* If key pressed is toggle between numeric & alphabetic, don't fetch character */
                    else
                    {
                        /* update text in input field according to the keypad state and index */
                        updateTextInput(prKeyPadState, prKeyButtonIndex)
                    }
                }
            }
        }
    }
}
