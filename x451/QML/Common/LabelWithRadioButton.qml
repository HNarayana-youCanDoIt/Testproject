/* This component contains a label and radio button. */
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import com.harman.qml.thememanager 1.0


/* @FixMe: We are using generic button for accessing long press timers and other related activities,
           this can be removed once we implement some decorator.*/
/* Text label which is derived from generic button */
HBButtonListItem {


    /* Property holds duration for screen delay after radio button selection */
    property int prScreenHoldDelay: 50

    /* Right margin of radio button to be provided */
    property int prRadioRightMargin: 13

    /* property is true when user select radio button. */
    property bool prIsSelected: false

    /**
     * property holds whether the selection timer is needed for any action on timeout.
     * If true, will enable idScreenDelayTimer
     */
    property bool prActionOnTimeOut: false

    /* Width of radio button to be provided */
    property int prRadioBtnWidth: 76

    /* Height of radio button to be provided */
    property int prRadioBtnHeight: 76

    /* FixMe: Add default asset images once proper assets are received */
    /* Path of selected radio button image to be provided */
    property string prRadioBtnSelectedImage: "qrc:/image/Set_Ico_RadioButton_7in_n-assets/Set_Ico_RadioButton_7in_na.png"

    /* Path of non-selected/default radio button image to be provided */
    property string prRadioBtnDefaultImage: "qrc:/image/Set_Ico_RadioButton_7in_n-assets/Set_Ico_RadioButton_7in_n.png"

    /* Radio button group to be provided */
    property var radioButtonGroup: idRadioButton.ButtonGroup.group

    /* Alias provided for radio button control */
    property alias radioButtonChecked: idRadioButton.checked

    /* On click of radio button, this signal gets emitted */
    signal sigRadioBtnCheckedChanged()

    /*
     * Signal will get emitted when idScreenDelayTimer completed
     * This signal can be used by the screens or other components to take necessary action after user selection.
     * for e.g. closing the screen, displaying messages etc.
     */
    signal sigRadioBtnSelectionCompleted()

    /**
     * Method to set radio button state when user select radio button through RRE.
     */
    function setRRESelection(){
        prIsSelected = true
        radioButtonChecked = true
    }


    /**
     * Timer to hold screen after selection(when is screen should close after selection), so that user could
     * see the action taken on the screen. Timer will be get enabled when user set prActionOnTimeOut to true.
     */
    Timer {
        id: idScreenDelayTimer
        interval: prScreenHoldDelay
        onTriggered: {
            sigRadioBtnSelectionCompleted()
        }
    }

    contentItem:
        Item{

        width: parent.width
        height: parent.height
        anchors {
            left: parent.left
            leftMargin: 11
        }
        /* HBText used to display the label on the listitem */
        HBText {

            /**
                 * TODO: Currently the font used is not matching with the generic list screen
                 * layout as per provided by TML, need to check with TML to provide new FONT or
                 * change the existing FONT properties.
                 */
            id:idHBText

            width: 400
            height: 76

            anchors{
                left:parent.left
                top:parent.top
                verticalCenter: parent.verticalCenter
            }

            text: parent.parent.text

            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            //Todo: For Disable button font Type needs to be changed later.

            fontType: parent.parent.enabled ? ThemeMgr.FONTTYPE_T35_C3 : ThemeMgr.FONTTYPE_T35_C3
        }

        /* Radio button control, which provides default radio button functionality */
        RadioButton {
            id: idRadioButton

            height: prRadioBtnHeight
            width: prRadioBtnWidth

            ButtonGroup.group: radioButtonGroup

            anchors {
                right: parent.right
                rightMargin: prRadioRightMargin
                verticalCenter: parent.verticalCenter
            }

            /* Radio button control provides default image and that can be customized according to requirement.
                we can provide different our own custom images in indicator */
            indicator: Image {
                id: idRadioCustomImage
                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                }
                source: idRadioButton.checked ? prRadioBtnSelectedImage : prRadioBtnDefaultImage
            }

            /* On click of radio button, signal gets emitted with the corresponding index */
            onCheckedChanged: {
                if (checked && prIsSelected) {
                    sigRadioBtnCheckedChanged()
                    if(prActionOnTimeOut){
                        idScreenDelayTimer.start()
                    }
                    prIsSelected = false
                }
            }
            onPressed: {
                prIsSelected = true
            }
        }
    }


    onPressAndHold: {
        if (!idRadioButton.checked) {
            prIsSelected = true
            idRadioButton.checked = true
        }
    }

    onReleased: {
        if (!idRadioButton.checked && !touchAndHold) {
            prIsSelected = true
            idRadioButton.checked = true
        }
    }
    /*  EXAMPLE: Button group need to be added in the qml where all this component is used like given below,
    assign the group id to radioButtonGroup property
    ButtonGroup {
        id: idCustomRadioButtonGroup
    }

    prActionOnTimeOut: true (if user wants to hold screen for prScreenHoldDelay duration)

    radioButtonGroup: idCustomRadioButtonGroup

    onSigRadioBtnCheckedChanged: {
    }

    // will get emitted when prActionOnTimeOut set to true
    onSigRadioBtnSelectionCompleted: {
    }
*/
}
