import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import "../Common"
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.thememanager 1.0
Item {

    id: idTumblerComponentWithBtns
    width: 76
    height: 271


    /* Tumbler width to be provided here */
    property int prTumblerWidth   : 90

    /* Tumbler buttons height to be provided here */
    property int prTumblerButtonsHeight        : 76

    /* Tumbler buttons width to be provided here */
    property int prTumblerButtonsWidth         : 76

    /* FixMe: Add default asset images once proper assets are received */
    /* tumbler increase button default image path to be provided */
    property string prArrowIncreaseNormalImage    :  "qrc:/image/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_n.png"

    /* tumbler increase button clicked image path to be provided */
    property string prArrowIncreasePressedImage   :  "qrc:/image/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_nf.png"

    /* tumbler decrease button default image path to be provided */
    property string prArrowDecreaseNormalImage    :  "qrc:/image/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_n.png"

    /* tumbler decrease button clicked image path to be provided */
    property string prArrowDecreasePressedImage   :  "qrc:/image/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_nf.png"

    /* tumbler cuurent item focus image path to be provided */
    property string prTumblerCurrentItemFocusImage :  "qrc:/image/Set_Gfx_Date&TimeBg_n.png/Set_Gfx_Date&TimeBg_3_n.png"

    /* whether the given model is numeric or not */
    property bool prIsModelNumeric   : true

    /* whether the user touched the tumbler */
    property bool prIsTouchOnTumbler   : false

    /* property to start with the given number */
    property int prStartingNumber   : 0

    /* This signal gets emitted with CurrentIndex and CurrentItem of Tumbler */
    signal sigTumblerCurrentItemChanged(int TumblerCurrentIndex , QtObject TumblerCurrentItem)

    property alias tumblerIncreaseBtn             : idTumblerIncreaseBtn
    property alias tumblerDecreaseBtn             : idTumblerDecreaseBtn
    property alias tumbler                        : idTumbler
    property alias tumblerCurrentItemFocusImage   : idTumblerCurrentItemFocusImage
    property alias tumblerHardKeyFocusImageSource   : idTumblerCurrentItemHardKeyFocusImage.source

    //It has to be an odd number count
    property alias prTumblerVisibleItemCount      : idTumbler.visibleItemCount

    /*Function to start the model from the given number i.e prStartingNumber */
    function formatNumText(count, modelData) {
        var data = modelData + prStartingNumber
        return data
    }


    /*It is used for Font of Tumbler component */
    FontMetrics {
        id: idFontMetrics
    }
    /* This button will increase the index on the button click of that particular tumbler attached to */
    ListGenericButton
    {
        id: idTumblerIncreaseBtn
        width: prTumblerButtonsWidth
        height: prTumblerButtonsHeight
        defaultImageURL: prArrowIncreaseNormalImage
        pressedImageURL: prArrowIncreasePressedImage
        anchors
        {
            top:parent.top
            horizontalCenter:idTumbler.horizontalCenter
        }
        onReleased: {

            tumbler.contentItem.incrementCurrentIndex()
            cppSetupApp.qmlLog("Item: " + idTumbler.currentItem.text + " CurrentIndex: " + (idTumbler.currentIndex))
            idTumblerComponentWithBtns.forceActiveFocus()
            prIsTouchOnTumbler = true

        }

        onPressAndHoldContinue:
        {
            tumbler.contentItem.incrementCurrentIndex()
            cppSetupApp.qmlLog("Item: " + idTumbler.currentItem.text + " CurrentIndex: " + (idTumbler.currentIndex))
        }
    }


    /* This button will decrease the index on the button click of that particular tumbler attached to */
    ListGenericButton
    {
        id: idTumblerDecreaseBtn
        width: prTumblerButtonsWidth
        height: prTumblerButtonsHeight
        defaultImageURL: prArrowDecreaseNormalImage
        pressedImageURL: prArrowDecreasePressedImage
        anchors {
            bottom: parent.bottom
            horizontalCenter:idTumbler.horizontalCenter
        }
        onReleased: {
            tumbler.contentItem.decrementCurrentIndex()
            cppSetupApp.qmlLog("Item: " + idTumbler.currentItem.text + " CurrentIndex: " + (idTumbler.currentIndex))
            idTumblerComponentWithBtns.forceActiveFocus()
            prIsTouchOnTumbler = true
        }
        onPressAndHoldContinue:
        {
            tumbler.contentItem.decrementCurrentIndex()
            cppSetupApp.qmlLog("Item: " + idTumbler.currentItem.text +" CurrentIndex: " + (idTumbler.currentIndex))
        }
    }

    Tumbler {
        id: idTumbler
        visibleItemCount: 3
        width: prTumblerWidth
        MouseArea{
            id: idMouseArea
            anchors.fill: parent

            /**
              * Since MouseArea is above tumbler so,On User Touch Mousearea need to pass the click event directly to tumbler,
              * for this we have to use propagateComposedEvents attribute
            */
            propagateComposedEvents: true
            onPressed:
            {
                idTumblerComponentWithBtns.forceActiveFocus()
                mouse.accepted = false
                /**
                  *  as the user tocuhes the tumbler after just opening the screen, we have to change the hardkey functionality to operate
                  * according to it.
                */
                prIsTouchOnTumbler = true
            }
        }


        anchors
        {
            top:idTumblerIncreaseBtn.bottom
            bottom:idTumblerDecreaseBtn.top
        }
        onCurrentIndexChanged: {
            sigTumblerCurrentItemChanged(currentIndex,currentItem)
        }


        contentItem:PathView {
            id: pathView
            model: tumbler.model
            delegate: idDelegateComponent
            clip: true
            pathItemCount: (tumbler.visibleItemCount + 1)
            preferredHighlightBegin: 0.5
            preferredHighlightEnd: 0.5
            dragMargin: (width / 2)

            path: Path {
                startX: (pathView.width / 2)
                startY:  -((pathView.delegateHeight / 2) + 10)
                PathLine {
                    x: (pathView.width / 2)
                    y: (( pathView.pathItemCount * pathView.delegateHeight) - (pathView.delegateHeight / 2) + 3)
                }
            }

            property real delegateHeight: ((tumbler.availableHeight / tumbler.visibleItemCount) + 2)
        }

    }


    /* This image will show on the background of current selected item in tumbler. */
    Image {
        id: idTumblerCurrentItemFocusImage

        anchors{
            top: idTumbler.top
            topMargin: ((idTumbler.height / 2) - (idTumblerCurrentItemFocusImage.height / 2))
        }
        source: prTumblerCurrentItemFocusImage
    }

    //[Todo:] This will be changed once assets are provided
    /* This image will show on the background of current selected item in tumbler. */
    Image {
        id: idTumblerCurrentItemHardKeyFocusImage

        anchors{
            top: idTumbler.top
            topMargin: ((idTumbler.height / 2) - (idTumblerCurrentItemFocusImage.height / 2))
        }
        visible: (idTumblerComponentWithBtns.focus || idTumblerIncreaseBtn.focus || idTumblerDecreaseBtn.focus)
        source: prTumblerCurrentItemFocusImage
    }

    Component {
        id: idDelegateComponent
        HBText {
            property real displacement: Math.abs(Tumbler.displacement)
            id: idTumblerDelegateText
            text: prIsModelNumeric ? formatNumText(Tumbler.tumbler.count, modelData) : modelData
            fontType: ((displacement >= 0) && (displacement <= 0.5)) ? ThemeMgr.FONTTYPE_T35_BK_C2 : ThemeMgr.FONTTYPE_T24_LIGHT_C2

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    Component.onCompleted: {
        focus = false
    }

}

/* EXAMPLE: How to use Tumbler component for 24 hrs format.

    TumblerWithButtonComponent{
        anchors
        {
            top:parent.top
            topMargin:100
            left:parent.left
            leftMargin:200
        }
        tumbler.model: 24
        prIsModelNumeric:true
        prStartingNumber: 0
        prTumblerVisibleItemCount: 3

        onSigTumblerCurrentItemChanged: {
            cppSetupApp.qmlLog("Item: " + idTumbler.currentItem.text +" CurrentIndex: " + (idTumbler.currentIndex))
        }
    }

*/

