import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.mediaenum 1.0

BaseUI {

    id: idPictureViewer

    //In fullView, all controls shall be hidden to user
    property bool prIsFullView : false

    //In switch from full view, animation should be accessible for use
    property bool prIsInAnim : false

    function displayImage()
    {        
        idPictureTitle.text = MediaAdaptor.getImageTitle(MediaAdaptor.getPvCurrentImageIndex())
        cppMediaApp.qmlLog("MediaPictureViewerScreen.qml: Showing Image No. " + MediaAdaptor.getPvCurrentImageIndex()
                           + " :: Image Name. " + idPictureTitle.text)
        idPictureViewerPathView.positionViewAtIndex(MediaAdaptor.getPvCurrentImageIndex(), PathView.Center)        
    }

    Timer {
        id:idFullViewTimer

        interval: 5000
        onTriggered:
        {
            prIsFullView = true
        }
    }

    Timer {
        id:idAnimTimer

        interval: 300
        onTriggered:
        {
            prIsInAnim = false
        }
    }

    Image {
        id: idScreenBg
        source: "qrc:/image/Background/Gen_Gfx_BgLevel0_n.png"
    }

    PathView {
        id: idPictureViewerPathView
        anchors.fill: parent
        property int prCachecount: 4
        width: (parent.width * pathItemCount)

        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5


        currentIndex: 0
        interactive: (prIsInAnim || ((idPictureViewerPathView.count > 1) && prIsFullView))
        model: MediaAdaptor.imageDataModel

        pathItemCount: 3
        cacheItemCount: ((MediaAdaptor.imageDataModel.rowCount() > (pathItemCount + prCachecount)) ? prCachecount : undefined)
        snapMode: PathView.SnapOneItem

        path: Path {
            id:myPath
            startX: -800
            startY: 240
            PathLine {
                x: 1600
                y: 240
            }
        }

        onCurrentIndexChanged:{
            cppMediaApp.qmlLog("MediaPictureViewerScreen.qml: onCurrentIndexChanged: "+currentIndex)
            idPictureTitle.text = MediaAdaptor.getImageTitle(currentIndex)
            MediaAdaptor.setPvCurrentImageIndex(currentIndex)
        }

        onModelChanged:
        {
            cppMediaApp.qmlLog("MediaPictureViewerScreen.qml: onModelChanged : Model Count" + MediaAdaptor.totalImageCount)
            displayImage()
        }

        Component.onCompleted:
        {
            cppMediaApp.qmlLog("MediaPictureViewerScreen.qml: Component.onCompleted for PathView")
            displayImage()
        }

        delegate: Item{

            width: 800
            height: 480

            Image {
                property string strTemp:""
                id: idImage
                anchors.centerIn: parent
                source:  itemImageRole//MediaAdaptor.pvImageList[index]

                sourceSize.width: 800
                sourceSize.height: 480

                cache: false
                asynchronous: true

                onSourceChanged: {
                    cppMediaApp.qmlLog("MediaPictureViewerScreen.qml: onSourceChanged: "+itemImageRole+ " source: "+source)
                    idPictureTitle.text = MediaAdaptor.getImageTitle(idPictureViewerPathView.currentIndex)
                }

                onStatusChanged: {
                    cppMediaApp.qmlLog("MediaPictureViewerScreen.qml: onStatusChanged: idImage.status: " + idImage.status)

                    if(idImage.status === Image.Error)
                    {
                        idImage.source = "qrc:/image/Media/Media_Corrupt_Image/Gen_Gfx_Corrupted_Image.png"
                        idLoadingAnimation.visible = false
                    }

                    else if(idImage.status === Image.Null || idImage.status === Image.Loading)
                    {
                        idLoadingAnimation.visible = true
                    }

                    else if(idImage.status === Image.Ready)
                    {
                        idImage.visible = true
                        idLoadingAnimation.visible = false
                    }
                }
            }

            BusyIndicator{
                id: idLoadingAnimation
                visible: true

                anchors
                {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }
            }

            Component.onCompleted:
            {
                cppMediaApp.qmlLog("MediaPictureViewerScreen.qml: Delegate loading completed.")
            }
        }

        MouseArea{
            anchors.fill: parent

            onClicked:
            {
                cppMediaApp.qmlLog("MediaPictureViewerScreen.qml: MouseArea: OnClicked: currentIndex " + idPictureViewerPathView.currentIndex + "prIsFullView: "+prIsFullView                                   )

                idPictureViewerPathView.positionViewAtIndex((idPictureViewerPathView.currentIndex), PathView.Center)

                if(prIsFullView)
                {

                    prIsFullView = false
                    idFullViewTimer.restart()
                }
                else
                {
                    prIsFullView = true
                    idFullViewTimer.stop()
                }

                cppMediaApp.qmlLog("MediaPictureViewerScreen.qml: MouseArea: OnClicked " + prIsFullView)
            }

            Component.onCompleted: {
                cppMediaApp.qmlLog("MediaPictureViewerScreen.qml : Mouse area loading comlpeted")
            }
        }
    }


    Image {
        id: idDimBg
        source: "qrc:/image/Media/Med_Gfx_PictureViewerDimBg_7in_n-assets/Med_Gfx_PictureViewerDimBg_n.png"
        visible: !prIsFullView
    }

    //Picture Title
    HBText{
        id: idPictureTitle
        width: 419
        height: 31
        anchors{

            top: parent.top
            topMargin: 73
            horizontalCenter: parent.horizontalCenter
        }

        horizontalAlignment: Text.AlignHCenter
        fontType: ThemeMgr.FONTTYPE_T45_C1
        visible: !prIsFullView
    }

    //Browse Button
    GenericButton{
        id: idBrowseBtn
        width: 76
        height: 76

        anchors{

            left: parent.left
            leftMargin: 619
            top: parent.top
            topMargin: 50
        }

        defaultImageURL: "qrc:/image/Tuner/Gen_Ico_Browse/Gen_Ico_Browse_n.png"
        pressedImageURL: "qrc:/image/Tuner/Gen_Ico_Browse/Gen_Ico_Browse_nf.png"
        disabledImageURL: "qrc:/image/Tuner/Gen_Ico_Browse/Gen_Ico_Browse_nd.png"

        //If USB has only images, then disable browse button
        enabled: (MediaEnum.CONTENTTYPE_I !== MediaAdaptor.usbContentType)

        visible: !prIsFullView

        onReleased: {
            cppMediaApp.qmlLog("MediaPictureViewerScreen.qml: Media Browse Clicked!")
            //Go to Media Browse screen on Release of Browse Button
            cppMediaApp.raiseSMEvent("Media","Browse")
        }

        onPressAndHold: {
            //Restart the Full screen Mode Timer
            idFullViewTimer.restart()
        }

        onPressAndHoldContinue: {
            //Restart the Full screen Mode Timer
            idFullViewTimer.restart()
        }
    }

    //Back Button
    GenericButton{
        id: idBackButton
        width: 76
        height: 76
        anchors{
            left: parent.left
            leftMargin: 694
            top: parent.top
            topMargin: 50
        }

        defaultImageURL: "qrc:/image/Media/Media_Ico_Cancel2_7in_n-assets/Media_Ico_Cancel2_n.png"
        pressedImageURL: "qrc:/image/Media/Media_Ico_Cancel2_7in_n-assets/Media_Ico_Cancel2_nf.png"
        disabledImageURL: "qrc:/image/Media/Media_Ico_Cancel2_7in_n-assets/Media_Ico_Cancel2_nd.png"
        //Disabled image not required since this button shall never go to disabled state

        visible: !prIsFullView

        onReleased: {
            if(MediaEnum.CONTENTTYPE_I === MediaAdaptor.usbContentType)
            {
                cppMediaApp.qmlLog("MediaPictureViewerScreen.qml: PV - CONTENTTYPE_I - Back Button Clicked, switching to previous ENT source")
                MediaAdaptor.requestPreviousSource()
            }
            else if(MediaAdaptor.isNowPlayingDataAvail())
            {
                cppMediaApp.qmlLog("MediaPictureViewerScreen.qml: PV - nowPlaying available - Back Button Clicked, raise evBack")
                cppUIBase.raiseSMEvent("back", "")
            }
            else
            {
                cppMediaApp.qmlLog("MediaPictureViewerScreen.qml: PV - nowPlaying not available - Back Button Clicked, switching to previous ENT source")
                MediaAdaptor.requestPreviousSource()
            }
        }

        onPressAndHold: {
            //Restart the Full screen Mode Timer
            idFullViewTimer.restart()
        }

        onPressAndHoldContinue: {
            //Restart the Full screen Mode Timer
            idFullViewTimer.restart()
        }
    }

    /* Media Previous Image button */
    ListGenericButton {
        id: idMediaMainPrevBtn
        width: 76
        height: 76
        enabled: (idPictureViewerPathView.count > 1)

        anchors
        {
            left: parent.left
            top: parent.top
            leftMargin: 74
            topMargin: 202
        }

        defaultImageURL: "qrc:/image/Media/Med_Btn_FastRewind_7in_n-assets/Med_Btn_FastRewind_n.png"
        pressedImageURL: "qrc:/image/Media/Med_Btn_FastRewind_7in_n-assets/Med_Btn_FastRewind_nf.png"
        disabledImageURL: "qrc:/image/Media/Med_Btn_FastRewind_7in_n-assets/Med_Btn_FastRewind_nd.png"

        visible: !prIsFullView

        onReleased:
        {
            cppMediaApp.qmlLog("MediaPictureViewerScreen.qml: onReleased On PictureViewer Previous btn")

            idPictureViewerPathView.decrementCurrentIndex()
            idFullViewTimer.restart()
        }

        onPressAndHold: {
            //Restart the Full screen Mode Timer
            idFullViewTimer.restart()
        }

        onPressAndHoldContinue: {
            //Restart the Full screen Mode Timer
            idFullViewTimer.restart()
        }
    }

    /* Media Next Image button */
    ListGenericButton {
        id: idMediaMainNextBtn
        width: 76
        height: 76
        enabled: (idPictureViewerPathView.count > 1)

        anchors
        {
            left: parent.left
            top: parent.top
            leftMargin: 655
            topMargin: 202
        }

        defaultImageURL: "qrc:/image/Media/Med_Btn_FastForward_7in_n-assets/Med_Btn_FastForward_n.png"
        pressedImageURL: "qrc:/image/Media/Med_Btn_FastForward_7in_n-assets/Med_Btn_FastForward_nf.png"
        disabledImageURL: "qrc:/image/Media/Med_Btn_FastForward_7in_n-assets/Med_Btn_FastForward_nd.png"

        visible: !prIsFullView

        onReleased:
        {
            cppMediaApp.qmlLog("MediaPictureViewerScreen.qml: onReleased On PictureViewer Next btn")
            idPictureViewerPathView.incrementCurrentIndex()
            idFullViewTimer.restart()
        }

        onPressAndHold: {
            //Restart the Full screen Mode Timer
            idFullViewTimer.restart()
        }

        onPressAndHoldContinue: {
            //Restart the Full screen Mode Timer
            idFullViewTimer.restart()
        }
    }

    Slider
    {
        id: idPictureViewerSlider

        enabled: (idPictureViewerPathView.count > 1)

        anchors
        {
            top: parent.top
            topMargin: 417
            horizontalCenter: parent.horizontalCenter
        }

        width: idSliderImage.width
        height: idSliderImage.height

        from    : 1
        to      : idPictureViewerPathView.count
        stepSize: 1

        value: (idPictureViewerPathView.currentIndex + 1)

        visible: !prIsFullView

        snapMode: Slider.SnapOnRelease

        background: Image
        {
            id : idSliderImage

            width: 687
            height: 38
            source: "qrc:/image/Media/Med_Gfx_PictureViewerAlphaTrack_7in_n-assets/Med_Gfx_PictureViewerAlphaTrack_n.png"
            fillMode: Image.Pad
            anchors.horizontalCenter: parent.horizontalCenter
        }

        handle: Item {
            id: idSliderHandleItem
            anchors.top: parent.top
            anchors.verticalCenter: idSliderImage.verticalCenter
            x: (idPictureViewerSlider.leftPadding + (idPictureViewerSlider.visualPosition * (idPictureViewerSlider.availableWidth - width)))
            z: 1

            HBText {
                id: idCurrentPictureIndex
                anchors.centerIn: idSliderHandleItem
                text: Math.round(idPictureViewerSlider.value)
            }
        }

        onPressedChanged: {

            cppMediaApp.qmlLog("MediaPictureViewerScreen.qml: Slider pressed pos, requested image : " + Math.round(idPictureViewerSlider.value))

            if((idPictureViewerSlider.value > 0) && ((Math.round(idPictureViewerSlider.value)) <= (idPictureViewerPathView.count)))
            {
                idPictureViewerPathView.positionViewAtIndex((Math.round(idPictureViewerSlider.value) - 1), PathView.Center)
            }

            idFullViewTimer.restart()
        }
    }


    Connections{
        target: cppHardkeyAdaptor
        onSigRotaryUpdate :            
        {
            cppMediaApp.qmlLog("MediaPictureViewerScreen.qml: onSigRotaryUpdate:: iKeyCode"+ iKeyCode + "iKeyState: "+ iKeyState)

            if(HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState)
            {
                prIsInAnim = true
                idAnimTimer.restart()
                prIsFullView = false
                idFullViewTimer.restart()
                idPictureViewerPathView.decrementCurrentIndex()

                cppMediaApp.qmlLog("MediaPictureViewerScreen.qml: prIsFullView" + prIsFullView)
            }
            else if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState)
            {
                prIsInAnim = true
                idAnimTimer.restart()
                prIsFullView = false
                idFullViewTimer.restart()
                idPictureViewerPathView.incrementCurrentIndex()

                cppMediaApp.qmlLog("MediaPictureViewerScreen.qml: prIsFullView" + prIsFullView)
            }
            else
            {
                //Do nothing...invalid Rotary update event
            }
        }

        onSigRotaryPressed:
        {
            if((HardkeyEnum.KEYCODEHK_MENUROTARY === iKeyCode) && (HardkeyEnum.HKEY_STATE_RELEASED === iKeyState || HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState))
            {
                cppMediaApp.qmlLog("MediaPictureViewerScreen.qml : right rotary pressed")

                if(MediaEnum.CONTENTTYPE_I !== MediaAdaptor.usbContentType)
                {
                    MediaAdaptor.updateMediaBrowseList()
                    cppMediaApp.qmlLog("MediaPictureViewerScreen.qml : Media Browse Clicked!")
                    cppMediaApp.raiseSMEvent("Media","Browse")
                }
                else
                {
                    cppMediaApp.qmlLog("MediaPictureViewerScreen.qml : right rotary pressed ignored - USB without songs")
                }
            }
            else
            {
                //Do nothing
            }
        }
    }

    Connections{
        target: MediaAdaptor
        onSigImageIndexChanged:
        {
            cppMediaApp.qmlLog("MediaPictureViewerScreen.qml: onSigImageIndexChanged: " + MediaAdaptor.getPvCurrentImageIndex())
            idPictureViewerPathView.positionViewAtIndex(MediaAdaptor.getPvCurrentImageIndex(), PathView.Center)
            idPictureViewerPathView.currentIndex = MediaAdaptor.getPvCurrentImageIndex();
            idPictureTitle.text = MediaAdaptor.getImageTitle(MediaAdaptor.getPvCurrentImageIndex())
        }

        onSigPvImageListChanged:
        {
            cppMediaApp.qmlLog("MediaPictureViewerScreen.qml: onSigPvImageListChanged: " + MediaAdaptor.getPvCurrentImageIndex())
            idPictureViewerPathView.positionViewAtIndex(MediaAdaptor.getPvCurrentImageIndex(), PathView.Center)
            idPictureViewerPathView.currentIndex = MediaAdaptor.getPvCurrentImageIndex();
            idPictureTitle.text = MediaAdaptor.getImageTitle(MediaAdaptor.getPvCurrentImageIndex())
        }
    }

    Component.onCompleted: {
        cppMediaApp.qmlLog("MediaPictureViewerScreen.qml: Component.onCompleted")

        //Request to load the List with the images.
        MediaAdaptor.getCategoryRoot(MediaEnum.BROWSEITEM_PICTURE)
        idFullViewTimer.start()
    }
}
