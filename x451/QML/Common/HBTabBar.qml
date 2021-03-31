/*
 *  This is a Generic Component, Which provides the functionality related to
 *  tab view to all other modules. The following functionalities are provided by this
 *  component:
 *  1. It provides the tabView ==> The user of this component needs to assign
 *  a model and a delegate.
 *  2. It also have next and previous buttons implementation in it.
 */
import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0

Item {
    id: idTabBarItem

    height: 76
    width: 483

    /*
     * This property holds the alias of pathview, the pathview can be accessed using  this
     * property from outside of this qml
     */
    property alias prTabBarPathView: idPathView

    /*
     * This property holds the alias of pathview, the pathview can be accessed using  this
     * property from outside of this qml
     */
    property alias prTabViewModel: idPathView.model

    /*
     * This property holds movement status of TabBar
     * true : if movement is due to drag
     * false : if movement is not due to drag
     */
    property bool isMovementByDrag: false

    /*
     * This signal used to notify current index change
     */
    signal sigTabViewCurrentIndexChanged(int index)

    /*
     * This property holds status of movement by drag
     */
    property alias prCurrIndex: idPathView.currentIndex

    /*
     * This property holds whether Tab bar movement is enabled or not
     */
    property bool prIsTabBarMovementEnabled: true

    /* function to set the position view for pathview
      */
    function setPositionView()
    {
        idPathView.positionViewAtIndex(idPathView.currentIndex, PathView.Center)
    }

    /**
     * GenericButton is prevoius arrow button, used to swipe left
     */
    GenericButton {
        id:idPrevButton
        width: 76
        height: 76

        anchors{
            left: parent.left
            leftMargin: 21
            top: parent.top
            topMargin: -12
        }
        defaultImageURL: "qrc:/image/ZenPresets/Ph_Ico_BrowsePreviousArrow_7in_n-assets/Ph_Ico_BrowsePreviousArrow_na.png"
        pressedImageURL: "qrc:/image/ZenPresets/Ph_Ico_BrowsePreviousArrow_7in_n-assets/Ph_Ico_BrowsePreviousArrow_np.png"
        disabledImageURL: "qrc:/image/ZenPresets/Ph_Ico_BrowsePreviousArrow_7in_n-assets/Ph_Ico_BrowsePreviousArrow_nd.png"

        enabled: prIsTabBarMovementEnabled

        onPressed: {
            cppUIBase.qmlLog("HBTabBar.qml: idPrevButton: onPressed")
            // Deactivate VR session
            cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
        }

        /*
         * onReleased: Generic Button signal handled here,
         * user can handle this signal to get released event.
         */
        onReleased: {
            if(!touchAndHold)
            {
                idPathView.decrementCurrentIndex()
            }
        }

        /*
         * onPressAndHoldContinue Generic Button signal handled here,
         * user can handle this signal to get onPressAndHoldContinue event.
         */
        onPressAndHold: {
            idPathView.decrementCurrentIndex()
        }
    }

    /**
     * GenericButton is next arrow button, used to swipe right
     */
    GenericButton {
        id:idNextButton
        width: 76
        height: 76

        anchors{
            left: parent.left
            leftMargin: 353
            top: parent.top
            topMargin: -12
        }
        defaultImageURL: "qrc:/image/ZenPresets/Ph_Ico_BrowseNextArrow_7in_n-assets/Ph_Ico_BrowseNextArrow_na.png"
        pressedImageURL: "qrc:/image/ZenPresets/Ph_Ico_BrowseNextArrow_7in_n-assets/Ph_Ico_BrowseNextArrow_np.png"
        disabledImageURL: "qrc:/image/ZenPresets/Ph_Ico_BrowseNextArrow_7in_n-assets/Ph_Ico_BrowseNextArrow_nd.png"

        enabled: prIsTabBarMovementEnabled

        onPressed: {
            cppUIBase.qmlLog("HBTabBar.qml: idNextButton: onPressed")
            // Deactivate VR session
            cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
        }

        /*
         * onReleased: Generic Button signal handled here,
         * user can handle this signal to get released event.
         */
        onReleased: {
            if(!touchAndHold)
            {
                idPathView.incrementCurrentIndex()
            }
        }

        /*
         * onPressAndHoldContinue Generic Button signal handled here,
         * user can handle this signal to get onPressAndHoldContinue event.
         */
        onPressAndHold: {
            idPathView.incrementCurrentIndex()
        }
    }



    /*
     * This is delegate component which consists of generic button which consists of image and text
     */
    Component {
        id: idDelegate
        Item {
            anchors
            {
                top: parent.top
                topMargin: 7
            }

            width: idDelegateComp.width
            height: idDelegateComp.height

            /*
             * GenericButton is to select the list of items in the path view.
             */
            GenericButton {
                id: idDelegateComp

                /*
                 *This property holds the next index of pathview.
                 */
                property int prNextIndex: (((idPathView.currentIndex + 1) === idPathView.count) ? 0 : (idPathView.currentIndex + 1))
                property int prPrevIndex: ((0 === (idPathView.currentIndex)) ? (idPathView.count-1) : (idPathView.currentIndex - 1))

                anchors.centerIn: parent
                width: ((idImage.width) + idText.width)
                height: 58

                /*
                 * Image of the item in the pathview list.
                 * Image can be customized according to the respective screen
                 */
                Image {
                    id: idImage

                    height: 58
                    width: 58
                    visible: true

                    anchors{
                        left: parent.left
                        verticalCenter: parent.verticalCenter
                    }

                    source : getImgSource()

                    /* This function is for assigning the source of image in delegates */
                    function getImgSource()
                    {
                        if(idPathView.currentIndex === index)
                        {
                            return midIcon;
                        }
                        else if(idDelegateComp.prNextIndex === index)
                        {
                            return rightIcon;
                        }
                        else if(idDelegateComp.prPrevIndex === index)
                        {
                            return leftIcon;
                        }
                        else
                        {
                            // do nothing
                            return ""
                        }
                    }
                }

                /*
                 * text of the currently selected pathview item.
                 * Text can be customized according to the respective screen
                 */
                HBText{
                    id:idText
                    height: 16

                    text: ((idPathView.currentIndex === index) ? cppUIBase.invTruncateText(name, 10) : "")
                    fontType: (enabled) ? ThemeMgr.FONTTYPE_T24_LIGHT_C2 : ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    anchors{
                        left: idImage.right
                        verticalCenter: parent.verticalCenter
                    }
                    visible: (idDelegateComp.width === ((idImage.width) + width))
                }

                onPressed: {
                    cppUIBase.qmlLog("HBTabBar.qml: idDelegateComp: onPressed")
                    // Deactivate VR session
                    cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
                }

                /*
             * onReleased signal handled here,
             * user can handle this signal to get released event.
             */
                onReleased: {
                    idPathView.currentIndex = index
                }

                onPressAndHold: {
                    idPathView.currentIndex = index
                }
            }
        }
    }
    /*
 * Directions for Use: Uncomment the code below to trace the path for pathview generated.
 * This can be useful when creating appropriate paths.

    Canvas
    {
        id: canvas
        anchors.fill: parent
        antialiasing: true

        onPaint:
        {
            var context = canvas.getContext("2d")
            context.clearRect(10, 10, width, height)
            context.strokeStyle = "white"
            context.path = idPathView.path
            context.stroke()
        }
    }
*/



    /*
     * Pathview, pathview to scroll through the list of items
     */
    PathView {
        id:idPathView
        height: 58
        width: 288

        anchors {
            left: idTabBarItem.left
            leftMargin: 80
            top: idTabBarItem.top
            topMargin: -8
        }
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        highlightMoveDuration: 300
        delegate: idDelegate
        pathItemCount: 3
        clip: true

        enabled: prIsTabBarMovementEnabled

        path:
            Path{
            startX: -25; startY: 0;
            PathLine { x: idPathView.width + 25 ; y: 0}
        }

        /*
         * onMovementEnded pathview signal handled here,
         * user can handle this signal to get movementEnded event.
         */
        onMovementEnded: {
            if(isMovementByDrag){
                sigTabViewCurrentIndexChanged(idPathView.currentIndex)
            }
            isMovementByDrag = false
        }

        onMovementStarted: {
            isMovementByDrag = true
            // Deactivate VR session
            cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
        }

        onCurrentIndexChanged: {
            cppUIBase.qmlLog("curIndex: " + idPathView.currentIndex)
            if(!isMovementByDrag){
                sigTabViewCurrentIndexChanged(currentIndex)
            }
        }
    }

    /** Generic button to show back button with properties and implemetation as per X451 UI flow**/
    GenericButton {
        id: idBackButton
        width: 76
        height: 76

        anchors {
            left: parent.left
            leftMargin: 430
            top: parent.top
            topMargin: -4
        }

        defaultImageURL: "qrc:/image/Gen_Ico_Back_7in_n/Gen_Ico_Back_n.png"
        pressedImageURL: "qrc:/image/Gen_Ico_Back_7in_n/Gen_Ico_Back_np.png"
        disabledImageURL: "qrc:/image/Gen_Ico_Back_7in_n/Gen_Ico_Back_nd.png"

        onPressed: {
            cppUIBase.qmlLog("HBTabBar.qml: back button pressed.")
            // Deactivate VR session
            cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
        }

        onReleased: {
            cppUIBase.qmlLog("HBTabBar.qml: back button released.")
            cppUIBase.raiseSMEvent("back", "")
        }
    }

    /**
     * idListItemSepratorImg : Image source of the list item separator
     */
    Image {
        id: idListItemSepratorImg
        anchors{
            left: parent.left
            leftMargin: 55
            top:parent.top
            topMargin: 73
        }
        source: "qrc:/image/AudioPresets/AudioPresetsPopupBackground/Ph_Gfx_BrowsebottomSep_7in_n-assets/Ph_Gfx_BrowsebottomSep_n.png"
    }
}
