import QtQuick 2.7
import "../Common"

Keypad {

    /* Override the initial text to be displayed if there is no label/input provided */
    prInitialText: qsTr("TEXT_W3W_ENTER_LABEL_HERE") + cppThemeMgr.languageChanged

    /* Pass the old label text to Keypad component */
    prCustomText.text: cppW3WAdaptor.selectedW3WAddressLabelForFavorite

    prSaveBtn.onReleased: {
        /* Edit Label Save button handling: Closing keypad, moving to W3W app screen */
        cppW3WApplication.qmlLog("W3WEditLabelKeypad.qml: Save button clicked "+prCustomText.text)
        cppW3WAdaptor.editLabelSaveButtonClicked(prCustomText.text)
        cppW3WApplication.raiseSMEvent("Keypad", "Back")
    }

    Component.onCompleted: {

        if(prCustomText.text === "") {
            fnClearAll()
        }
        else {
            /* Do nothing */
        }
    }
}
