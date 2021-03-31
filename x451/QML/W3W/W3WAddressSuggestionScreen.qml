import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import com.harman.qml.w3wenum 1.0
import com.harman.qml.thememanager 1.0
import "../Common"


BaseUI
{
    /* Property to hold index of Proceed Button */
    property int prIndexForDeleteButton: 11

    /* Property to hold index of Proceed Button */
    property int prIndexForHideKeypadButton: 21

    /* Property to hold index of Proceed Button */
    property int prIndexForProceedButton: 30

    /* Property to hold  Max no of characters that can be put in a Text Input Field */
    property int prMaxCharsInInputField: 120

    /* Property to disable & enable keypad buttons based on number of char's in the textinput field */
    property bool prCanAddNewChar: (idCustomText.length < prMaxCharsInInputField)

    /* Alias property to show or hide the keypad */
    property alias prKeypadVisibility: idKeypad.visible


    /* Function to delete characters */
    function fnDeleteChar() {
        if (idCustomText.text.length > 1)
        {
            idCustomText.remove(idCustomText.cursorPosition - 1,idCustomText.cursorPosition)
        }
        else
        {
            idCustomText.clear()
        }
    }

    /* function to clear all the characters in text input area */
    function fnClearAll() {
        idCustomText.clear()
        idCustomText.cursorPosition = 0
        idCustomText.focus = true
    }

    /* Function to handle the keypad input buttons */
    function handleKeypadInput(keyIndex) {

        if(prIndexForDeleteButton === keyIndex)
        {
            /* Clear single character in Text input on click of Delete button */
            fnDeleteChar()
        }
        else if(prIndexForHideKeypadButton === keyIndex)
        {
            /* Hide Keypad */
            prKeypadVisibility = false
        }
        else if(prIndexForProceedButton === keyIndex)
        {
            /* Handle Proceed button. Get the first item of Auto Suggestion data, and
             * set the selected W3W address with it
             */
            cppW3WAdaptor.invSelectW3WAddressItem(W3WEnum.W3W_ADDRESS_TYPE_AUTO_SUGGESTION, 0)
            /* Close the Address Suggestion screen and navigate to W3W main screen */
            cppUIBase.raiseSMEvent("back", "")
        }
        else
        {
            idCustomText.insert(idCustomText.cursorPosition, (cppW3WAdaptor.getClickedCharacter(keyIndex)))
        }

        idCustomText.focus = true;
    }

    /* Image for Keypad Background overlay */
    Image {
        source: "qrc:/image/Popup/PopupBg/Gen_Gfx_PopupOverlayBg_n.png"
    }

    /* Initial text to be displayed before displaying the auto suggestions */
    Item {

        id: idInitialTextComponent

        anchors.fill: parent

        visible: !cppW3WAdaptor.autoSuggestionRecievedStatus

        /* HBText to show "Search for any 3 word address" in this screen */
        HBText {

            anchors {
                top: parent.top
                topMargin: 88
                horizontalCenter: parent.horizontalCenter
            }
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            fontType: ThemeMgr.FONTTYPE_T22_LIGHT_C2

            text: qsTr("TEXT_W3W_SEARCH_3WORD_ADDRESS") + cppThemeMgr.languageChanged
        }

        /* HBText to show "For example:" in this screen */
        HBText {

            anchors {
                top: parent.top
                topMargin: 140
                horizontalCenter: parent.horizontalCenter
            }
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            fontType: ThemeMgr.FONTTYPE_T22_LIGHT_C2

            text: qsTr("TEXT_W3W_FOR_EXAMPLE") + cppThemeMgr.languageChanged
        }

        /* HBText to show "///masterpiece.above.names" in this screen */
        HBText {

            anchors {
                top: parent.top
                topMargin: 178
                horizontalCenter: parent.horizontalCenter
            }
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3

            text: qsTr("TEXT_W3W_3WORD_SAMPLE") + cppThemeMgr.languageChanged
        }

        /* HBText to show "Marks exact location to India Gate, Delhi" in this screen */
        HBText {

            anchors {
                top: parent.top
                topMargin: 215
                horizontalCenter: parent.horizontalCenter
            }
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            fontType: ThemeMgr.FONTTYPE_T22_LIGHT_C2

            /* Language.csv automatically adds "" for this text (TEXT_W3W_3WORD_SAMPLE_LOCATION), so using the text directly in code */
            text: qsTr("Marks exact location to India Gate, Delhi") + cppThemeMgr.languageChanged
        }

        /* HBText to show "Don't know one? Try finding it here" in this screen */
        HBText {

            anchors {
                top: parent.top
                topMargin: 285
                horizontalCenter: parent.horizontalCenter
            }
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            fontType: ThemeMgr.FONTTYPE_T22_LIGHT_C2

            text: qsTr("TEXT_W3W_DONT_KNOW_ONE") + cppThemeMgr.languageChanged
        }

        Image {
            source: "qrc:/image/W3W/Gen_Gfx_Barcodeurl/Gen_Gfx_Barcodeurl.png"
            anchors {
                top: parent.top
                topMargin: 329
                horizontalCenter: parent.horizontalCenter
            }
        }

        /* HBText to show "https://what3words.com" in this screen */
        HBText {

            anchors {
                top: parent.top
                topMargin: 435
                horizontalCenter: parent.horizontalCenter
            }
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            fontType: ThemeMgr.FONTTYPE_T22_LIGHT_C2

            text: qsTr("TEXT_W3W_URL") + cppThemeMgr.languageChanged
        }
    }

    /* Auto suggestion list component */
    GenericList {
        id: idAutoSuggestionList

        visible: cppW3WAdaptor.autoSuggestionRecievedStatus

        width: 488
        height: 240

        anchors{
            top: parent.top
            topMargin: 80
            left: parent.left
            leftMargin: 159
        }

        idList.model: cppW3WAdaptor.w3wAutoSuggestionListModel
        idList.cacheBuffer: 1000
        idList.delegate:
            Loader {
            source: "qrc:/QML/W3W/W3WDelegates/W3WAutoSuggestionDelegate.qml"
        }
    }

    /* Text input component */
    Item {

        id: idTextInputComponent

        width: 480
        height: 59

        anchors {
            top: parent.top
            topMargin: 20
            left: parent.left
            leftMargin: 160
        }

        Image {
            source: "qrc:/image/W3W/Set_Gfx_PasswordTextBg_n-assets/Set_Gfx_PasswordTextBg_n.png"
        }

        Image {
            id: idSlashImage
            anchors {
                left: parent.left
                leftMargin: 13
                verticalCenter: parent.verticalCenter
            }
            source: "qrc:/image/W3W/KeyPad/W3W_Marker_Logo-assets/W3W_Marker_Logo.png"
        }

        /* Text input used for to show typed characters  */
        HBTextInput {
            id: idCustomText

            width: parent.width - ( idSlashImage.width + 10 )
            height: 59

            anchors {
                top: parent.top
                left: idSlashImage.right
            }

            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter

            maximumLength: prMaxCharsInInputField
            prFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2

            selectByMouse: true
            cursorVisible: true
            clip: true

            onTextChanged: {
                cppW3WAdaptor.w3wAddressInputText = idCustomText.text
            }

            /**
              * When User tries to drag the cursor on the text in InputField or click at any place then the cursor shall follow the mouse.
              **/
            MouseArea {
                anchors.fill: parent
                onClicked:
                {
                    cppW3WApplication.qmlLog("W3WAddressSuggestionScreen.qml: Text Input clicked")
                    /* Show the hidden Keypad on click of Text Input */
                    prKeypadVisibility = true;
                    idCustomText.focus = true;
                    idCustomText.cursorPosition = idCustomText.positionAt(mouse.x)
                }
                onPositionChanged: idCustomText.cursorPosition = idCustomText.positionAt(mouse.x)
            }
        }

        /* Cancel button */
        GenericButton {
            id: idCancelButton

            width: 50
            height: 50

            anchors {
                top: parent.top
                left: parent.left
                leftMargin: 572
            }

            defaultImageURL : "qrc:/image/W3W/KeyPad/Gen_Ico_PopupCancel2_n-assets/Gen_Ico_PopupCancel2_n.png"
            pressedImageURL : "qrc:/image/W3W/KeyPad/Gen_Ico_PopupCancel2_n-assets/Gen_Ico_PopupCancel2_nf.png"

            onReleased: {
                cppW3WApplication.qmlLog("W3WAddressSuggestionScreen.qml: Cancel button clicked")
                cppUIBase.raiseSMEvent("back", "")
            }
        }
    }

    /* Keypad component */
    Item {

        id: idKeypad

        visible: true

        /* Keypad background image */
        Image {
            id:idColorPatch
            source: "qrc:/image/W3W/Gen_Gfx_W3W_KeypadSmallOverlayBg_7in_n/Gen_Gfx_W3W_KeypadSmallColorPatch_7in_n.png"
            ColorOverlay {
                id: idGenericButtonColorOverlay
                anchors.fill: parent
                source: parent
                color:  cppThemeMgr.currentThemeColor
            }
        }

        /* Keypad background overlay */
        Image {
            source: "qrc:/image/W3W/Gen_Gfx_W3W_KeypadSmallOverlayBg_7in_n/Gen_Gfx_W3W_KeypadSmallOverlayBg_7in_n.png"
        }

        /* First grid which contains 11 columns (qwertyuiop and Backspace button ) */
        Grid {
            columns: 11
            anchors {
                top: parent.top
                topMargin: 3 + 264
                left:parent.left
                leftMargin: 19
            }
            columnSpacing: 1
            Repeater {
                model: parent.columns
                KeypadButton{
                    prKeyButtonIndex: index + 1
                    /* Do not disable the Delete button */
                    /* Need to disable the Delete button if there are no characters inside Text input Component */
                    enabled: (prKeyButtonIndex != prIndexForDeleteButton) ? prCanAddNewChar :
                                                                            ((idCustomText.text.length == 0) ? false : true)
                    defaultImageURL: cppW3WAdaptor.getKeyButtonDefaultImage(prKeyButtonIndex)
                    pressedImageURL: cppW3WAdaptor.getKeyButtonPressedImage(prKeyButtonIndex)
                    disabledImageURL: cppW3WAdaptor.getKeyButtonDisabledImage(prKeyButtonIndex)

                    onReleased: {
                        cppW3WApplication.qmlLog("W3WAddressSuggestionScreen.qml: Pressed Key button index" + prKeyButtonIndex)
                        handleKeypadInput(prKeyButtonIndex)
                    }

                    onPressAndHold: {
                        if(prIndexForDeleteButton === prKeyButtonIndex)
                        {
                            cppW3WApplication.qmlLog("W3WAddressSuggestionScreen.qml: onPressAndHold Delete button")
                            /* Clear all characters in Text input on Press and Hold of Delete button */
                            fnClearAll()
                        }
                        else
                        {
                            //Do nothing
                        }
                    }
                }
            }
        }

        /* Second grid which contains 9 columns (asdfghjkl button ) */
        Grid {
            columns: 9
            anchors {
                top: parent.top
                topMargin: 74 + 264
                left:parent.left
                leftMargin: 83
            }
            columnSpacing: 1
            Repeater {
                model: parent.columns
                KeypadButton{
                    enabled: prCanAddNewChar
                    prKeyButtonIndex: index + 12
                    defaultImageURL: cppW3WAdaptor.getKeyButtonDefaultImage(prKeyButtonIndex)
                    pressedImageURL: cppW3WAdaptor.getKeyButtonPressedImage(prKeyButtonIndex)
                    disabledImageURL: cppW3WAdaptor.getKeyButtonDisabledImage(prKeyButtonIndex)

                    onReleased: {
                        cppW3WApplication.qmlLog("W3WAddressSuggestionScreen.qml: Pressed Key button index" + prKeyButtonIndex)
                        handleKeypadInput(prKeyButtonIndex)
                    }
                }
            }
        }

        /* Third grid which contains 10 columns (Hide button, zxcvbnm. buttons and Proceed button ) */
        Grid {
            columns: 10
            anchors {
                top: parent.top
                topMargin: 145 + 264
                left:parent.left
                leftMargin: 41
            }
            columnSpacing: 1
            Repeater {
                model: parent.columns
                KeypadButton{
                    prKeyButtonIndex: index + 21
                    /* Disable keypad buttons other than Hide Keypad and Proceed buttons if maximum characters reached.
                     * Also, disable Procced button till auto suggestion is recived. Hide keypad button will not be disabled.
                     */
                    enabled: ((prKeyButtonIndex != prIndexForHideKeypadButton) && (prKeyButtonIndex != prIndexForProceedButton)) ?
                                 prCanAddNewChar :
                                 (prKeyButtonIndex === prIndexForProceedButton) ?
                                    cppW3WAdaptor.autoSuggestionRecievedStatus : true

                    defaultImageURL: cppW3WAdaptor.getKeyButtonDefaultImage(prKeyButtonIndex)
                    pressedImageURL: cppW3WAdaptor.getKeyButtonPressedImage(prKeyButtonIndex)
                    disabledImageURL: cppW3WAdaptor.getKeyButtonDisabledImage(prKeyButtonIndex)

                    onReleased: {
                        cppW3WApplication.qmlLog("W3WAddressSuggestionScreen.qml: Pressed Key button index" + prKeyButtonIndex)
                        /* update text in input field according to index */
                        handleKeypadInput(prKeyButtonIndex)
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        idCustomText.forceActiveFocus()
    }
}
