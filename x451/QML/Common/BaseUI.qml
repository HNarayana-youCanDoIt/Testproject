import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

/**
 *  Base container for every screen
 */
Item {
    id: idBaseUI
    width: 800
    height: 480

    /* background image for the HMI screens */
    property alias prBackGroundImage: idMainBackgroundImage.source

    /* signal is emitted when the screen looses focus */
    signal sigFocusLost

    /*
     * Commom background image for all the screens. The particular screen does not need to
     * set the background image
     */
    BorderImage {
        id: idMainBackgroundImage
        source: (cppThemeMgr.themeTypeFolderPath + (cppDisplayManagerAdaptor.nightModeStatus ? "" : "DayMode/") +"background.png")
        anchors.fill: parent
    }
}

/** how to use the focus property and signals

1. Use the property to get information when to get the focus information

2. Use the slots for screen specific handling
    onSigFocusGained: {
        cppUIBase.qmlLog("UI.qml:(" screen focus gained")
    }

    onSigFocusLost: {
        cppUIBase.qmlLog("UI.qml:(" screen focus lost")
    }
 **/
