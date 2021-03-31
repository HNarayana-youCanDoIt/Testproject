
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0
import com.harman.qml.thememanager 1.0

Button
{
    text: ""            //set generic button text using this property
    width: 100          //set generic button width using this property
    height: 50          //set generic button height using this property

    hoverEnabled: true  // used to handle hover functionality
    //////////////////////////////////////////////////////////////////////////////////
    /*
     * use to change default image of Generic Button
     */
    property string defaultImageURL: ""

    /*
     * use to change pressed image of Generic Button
     */
    property string pressedImageURL: ""

    /*
     * use to change disabled image of Generic Button
     */
    property string disabledImageURL: ""

    /*
     * use as condition to handle touch and hold functionality Generic Button
     */
    property bool touchAndHold: false

    /*
     * property to enable colory overlay on the button background image. (Theme color to be overlayed on the icon
     */
    property alias prEnableColorOverlay: idGenericButtonColorOverlay.visible

    /*
     * use to Handle RRE index
     */
    property int prRREIndex: -1

    /*
     * use to update RRE visibility
     */
    property bool prRREVisible: false

    /*
     * use to update RRE image anchors
     */
    property int prRREImageVerticalOffset: 0

    /*
     * use to update RRE image
     */
    property alias prRREImageSrc: idRREImage.source

    /*
    * Property used to set fontType for HB text
    */
    property alias textFontType: idGenericBtnText.fontType
    //////////////////////////////////////////////////////////////////////////////////
    /*
     * use as a signal to get pressAndHoldContinue callback
     */
    signal pressAndHoldContinue(real counter, bool isInside)
    //////////////////////////////////////////////////////////////////////////////////
    /*
     * Timer encapsulated to handle long press and hold functionality
     */
    Timer
    {
        id:continuousPressTimer
        interval: 250
        running: false
        repeat: true
        property int counter:0

        onTriggered:
        {
            counter = counter + 1;
            parent.pressAndHoldContinue(counter, parent.hovered);
        }
        onRunningChanged:
        {
            counter = 0;
        }
    }
    //////////////////////////////////////////////////////////////////////////////////
    /*
     * contentItem can be use to modify test format for Generic Button
     */
    contentItem: HBText
    {
        id: idGenericBtnText
        fontType: (parent.enabled) ? ThemeMgr.FONTTYPE_T24_LIGHT_C2 : ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED
        anchors.fill: parent
        visible: (text !== "")
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        text: parent.text
    }

    /*
    * RRE focus image
    */

    Image
    {
        id: idRREImage

        anchors{
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
            verticalCenterOffset: prRREImageVerticalOffset
        }

        visible: prRREVisible
        source: "qrc:/image/Home/Home_Ico_RRE_Focus/Home_Ico_RRE_Focus.png"
    }


    /*
     * background can be use to modify image behaviour for Generic Button
     */
    background: Image
    {
        id: idButtonBackground
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        visible: (source !== "")
        source: (parent.enabled)? ((parent.pressed)? (parent.pressedImageURL): (parent.defaultImageURL)): (parent.disabledImageURL)
        ColorOverlay {
            id: idGenericButtonColorOverlay
            anchors.fill: idButtonBackground
            source: idButtonBackground
            color:  cppThemeMgr.currentThemeColor
            visible: false
        }
    }
    //////////////////////////////////////////////////////////////////////////////////

    /*
     * This is done here, because when user press button continously and go outside of that
     * button, and release after the button gets disabled, then the button does not get
     * canceled event, due to that the timer does not get stop and action happens continuously.
     * So stoping the timer if button gets disabled.
     */
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

    /*
     * onPressed Generic Button signal handled here,
     * user can handle this signal to get pressed event.
     */
    onPressed:
    {
        touchAndHold = false;
        //cppUIBase.qmlLog("GenericButton:: onPressed");
    }

    /*
     * onPressAndHold Generic Button signal handled here
     * user can handle this signal to get press & hold event.
     */
    onPressAndHold:
    {
        touchAndHold = true;
        continuousPressTimer.start();
        //cppUIBase.qmlLog("GenericButton:: onPressAndHold");
    }

    /*
     * onPressAndHoldContinue Generic Button signal handled here
     * user can handle this signal to get press & continus hlod event.
     */
    onPressAndHoldContinue:
    {
        //cppUIBase.qmlLog("GenericButton:: onPressAndHoldContinue: Count:" + counter + ", IsInsideButton:" + isInside);
    }

    /*
     * onReleased Generic Button signal handled here
     * user can handle this signal to get press released event,
     * by using touchAndHold property value user can handle short/long release
     */
    onReleased:
    {
        continuousPressTimer.stop();
        //cppUIBase.qmlLog("GenericButton:: onReleased: IsLong:" + touchAndHold);
    }

    /*
     * onCanceled Generic Button signal handled here
     * user can handle this signal to get press canceled event,
     * by using touchAndHold property value user can handle short/long cancel
     */
    onCanceled:
    {
        continuousPressTimer.stop();
        //cppUIBase.qmlLog("GenericButton:: onCanceled: IsLong:" + touchAndHold);
    }

    /*
     * onClicked Generic Button signal handled here
     * user can handle this signal to get click/short release event,
     */
    onClicked:
    {
        touchAndHold = false;
        //cppUIBase.qmlLog("GenericButton:: onClicked");
    }
    //////////////////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////////////////
/*
 * ┌───
 * ├──
 * └─── EXAMPLE: HOW TO USE
 */
/* GenericButton
{
    text:               cppHomeAdaptor.homeShortcutsList[1].text
    defaultImageURL:    cppHomeAdaptor.homeShortcutsList[1].iconNormal
    pressedImageURL:    cppHomeAdaptor.homeShortcutsList[1].iconPressed
    disabledImageURL:   cppHomeAdaptor.homeShortcutsList[1].iconInactive

    onPressed:
    {
        cppUIBase.qmlLog("GenericButton:: onPressed");
    }
    onPressAndHold:
    {
        cppUIBase.qmlLog("GenericButton:: onPressAndHold");
    }
    onPressAndHoldContinue:
    {
        cppUIBase.qmlLog("GenericButton:: onPressAndHoldContinue " + counter, " Inside " + isInside);
    }
    onReleased:
    {
        if(touchAndHold)
        {
            cppUIBase.qmlLog("GenericButton:: onLongReleased");
        }
        else
        {
            cppUIBase.qmlLog("GenericButton:: onReleased");
        }
    }
    onCanceled:
    {
        if(touchAndHold)
        {
            cppUIBase.qmlLog("GenericButton:: onLongCanceled");
        }
        else
        {
            cppUIBase.qmlLog("GenericButton:: onCanceled");
        }
    }
    onClicked:
    {
        cppUIBase.qmlLog("GenericButton:: onClicked");
    }
}*/
//////////////////////////////////////////////////////////////////////////////////////
////////////////
