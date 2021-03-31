import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0

Control {
    id: idControl
    width: 100          //set List Generic Button width using this property
    height: 50          //set List Generic Button height using this property

    hoverEnabled: false  // used to handle hover functionality

    //////////////////////////////////////////////////////////////////////////////////

    /*
     * set List Generic Button text using this property
     */
    property string text: ""
    /*
     * use to change default image of List Generic Button
     */
    property string defaultImageURL: ""

    /*
     * use to change pressed image of List Generic Button
     */
    property string pressedImageURL: ""

    /*
     * use to change disabled image of List Generic Button
     */
    property string disabledImageURL: ""

    /*
     * use as condition to handle touch and hold functionality List Generic Button
     */
    property bool touchAndHold: false

    /*
     *  This property is used to know that the button is pressed or not.
     */
    property bool prPressed: false

    /*
     *  This property holds the status of button released or not.
     */
    property bool prIsButtonReleased: true

    //////////////////////////////////////////////////////////////////////////////////

    /*
     * press event signal emitted by the mouseArea subcomponent
     */
    signal pressed()

    /*
     * pressAndHold event signal emitted by the mouseArea subcomponent
     */
    signal pressAndHold()

    /*
     * released event signal emitted by the mouseArea subcomponent
     */
    signal released()

    /*
     * canceled event signal emitted by the mouseArea subcomponent
     */
    signal canceled()

    /*
     * clicked event signal emitted by the mouseArea subcomponent
     */
    signal clicked()

    /*
     * exited event signal emitted by the mouseArea subcomponent
     */
    signal exited()

    /*
     * pressAndHoldContinue event signal emitted by the mouseArea subcomponent
     */
    signal pressAndHoldContinue(real counter, bool isInside)
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    /*
     * contentItem can be use to modify test format for List Generic Button
     */
    contentItem: HBText {
        fontType: (parent.enabled) ? ThemeMgr.FONTTYPE_T35_C3 : ThemeMgr.FONTTYPE_T35_C3_DISABLED
        anchors.fill: parent
        visible: (text !== "")
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        text: parent.text
    }

    /*
     * background can be use to modify image behaviour for List Generic Button
     */
    background: Image {
        id: idButtonBackground
        anchors.fill: parent
        visible: (source !== "")
        source: (parent.enabled)? (idMouseArea.containsPress && idMouseArea._pressThreshold ? (parent.pressedImageURL): (parent.defaultImageURL)): (parent.disabledImageURL)
    }
    //////////////////////////////////////////////////////////////////////////////////

    onEnabledChanged: {
        if (!enabled)
        {
            continuousPressTimer.stop()
        }
        else
        {
            //Do nothing.
        }
    }

    MouseArea {
        id: idMouseArea
        anchors.fill: parent
        // disabling drag functionality on the liste element
        drag.target: undefined
        drag.axis: Drag.None
        preventStealing: false
        // informs whether press event threshold has been reached
        property bool _pressThreshold: false
        // informs whether release event threshold has been reached
        property bool _releaseThreshold: false

        /*
        * Timer encapsulated to handle long press and hold functionality
        */
        Timer {
            id: idPressThresholdTimer
            interval: 49
            running: false
            onTriggered: {
                parent._pressThreshold = true
                //cppUIBase.qmlLog("ListGenericButton:: onTriggered _pressThreshold: " + parent._pressThreshold)
            }
        }

        Timer {
            id: idReleaseThresholdTimer
            interval: 50
            running: false
            onTriggered: {
                parent._releaseThreshold = true
                //cppUIBase.qmlLog("ListGenericButton:: onTriggered _releaseThreshold: " + parent._releaseThreshold)
            }
        }

        /*
         * Timer encapsulated to handle long press and hold functionality
         */
        Timer
        {
            id: continuousPressTimer
            interval: 250
            running: false
            repeat: true
            property int counter:0

            onTriggered:
            {
                counter = counter + 1;
                idControl.pressAndHoldContinue(counter, parent.hovered)
            }
            onRunningChanged:
            {
                counter = 0
            }
        }

        /*
        * onPressed List Generic Button signal handled here,
        * user can handle this signal to get pressed event.
        */
        onPressed: {
            prIsButtonReleased = false
            touchAndHold = false;
            prPressed = true
            idControl.pressed()
            idPressThresholdTimer.start()
            idReleaseThresholdTimer.start()
            //cppUIBase.qmlLog("ListGenericButton:: onPressed, containsPress: " + containsPress);
        }

        onExited: {
            //cppUIBase.qmlLog("ListGenericButton::OnExited, containsPress: " + containsPress);
            idPressThresholdTimer.stop()
            prPressed = false
            _pressThreshold = false
            idReleaseThresholdTimer.stop()
            _releaseThreshold = false
            if(!prIsButtonReleased)
            {
                idControl.exited()
            }
            continuousPressTimer.stop();
        }

        /*
        * onPressAndHold List Generic Button signal handled here
        * user can handle this signal to get press & hold event.
        */
        onPressAndHold: {
            touchAndHold = true;
            idControl.pressAndHold()
            continuousPressTimer.start();
            //cppUIBase.qmlLog("ListGenericButton:: onPressAndHold");
        }

        /*
        * onReleased List Generic Button signal handled here
        * user can handle this signal to get press released event,
        * by using touchAndHold property value user can handle short/long release
        */
        onReleased: {
            prPressed = false
            prIsButtonReleased = true
            if ((true === containsMouse) && (true === _releaseThreshold)) {
                idControl.released()
                idReleaseThresholdTimer.stop()
            }
            continuousPressTimer.stop();
            //cppUIBase.qmlLog("ListGenericButton:: onReleased: IsLong: " + touchAndHold + " containsMouse: " + containsMouse + " _releaseThreshold: " + _releaseThreshold);
        }

        /*
         * onCanceled List Generic Button signal handled here
         * user can handle this signal to get press canceled event,
         * by using touchAndHold property value user can handle short/long cancel
         */
        onCanceled: {
            prPressed = false
            idPressThresholdTimer.stop()
            _pressThreshold = false
            idReleaseThresholdTimer.stop()
            _releaseThreshold = false
            idControl.canceled()
            continuousPressTimer.stop();
            //cppUIBase.qmlLog("ListGenericButton:: onCanceled: containsPress: " + containsPress);
        }

        /*
         * onClicked List List Generic Button signal handled here
         * user can handle this signal to get click/short release event,
         */
        onClicked: {
            touchAndHold = false;
            idControl.clicked()
            //cppUIBase.qmlLog("ListGenericButton:: onClicked");
        }

    }
    //////////////////////////////////////////////////////////////////////////////////
}
