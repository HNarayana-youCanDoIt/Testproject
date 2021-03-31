import QtQuick 2.7
import QtQuick.Controls 2.2

/*
 * Component for Each button in Keypad
 */
GenericButton {
    /*
     * This property stores index of each keypadbutton
     */
    property int prKeyButtonIndex: 0

    width: idImage.width
    height: idImage.height

    background: Image
    {
        id: idImage
        anchors.centerIn: parent
        visible: (source !== "")
        source: (parent.enabled) ? (parent.pressed ? (parent.pressedImageURL) : (parent.defaultImageURL)) : (parent.disabledImageURL)
    }
}
