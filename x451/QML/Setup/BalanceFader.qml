import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.harman.qml.thememanager 1.0
import "../Common/"
import "qrc:/image/"

BaseUI {
    id: idBalFadScreen
    /* When we click on balance & fader mat we get the positions of x & y co-ordinates,
        by using those positions we calculate balance & fader valus and send those values to service.
        But in the case of Reset, Driver & Rear button click we wont get positions,
        so the below literals are used to send positions for the buttons */

    /*ToDo: Need to get the position of speaker when user pressed on driver,rear and reset based on values send by service.
            Not required the below values to be set, on requesting to set position of speaker */
    property int prBalancePosition: 102
    property int prResetBtnFaderPosition: 112
    property int prDriverBtnFaderPosition: 1
    property int prRearBtnFaderPosition: 231
    property int prDriverBtnBalPosition: 101

    /* Properties used to calculate  mouseX & mouseY values */
    property int prBalancePositionFromX   : -1
    property int prFaderPositionFromY     : -1

    /* Property used to increase the mouse area of balance & fader mat */
    property int prMatMouseAreaIncreased  : 55

    property alias balanceFaderMouseArea: idBalanceFaderMouseArea

    /**
     * Balance & Fader background image
     */
    Image {
        id: idBalFadBackgroundCarImage

        anchors {
            left: parent.left
            leftMargin: 323
            top: parent.top
            topMargin: 124
        }
        width: 308
        height: 308
        source: "qrc:/image/BalanceFader/Gen_Gfx_Balance&FaderCar_n/Gen_Gfx_Balance&FaderCar_n.png"

        Item {
            id: idCarMatRect

            width: 196
            height: 230
            anchors {
                left: parent.left
                leftMargin: 51
                top: parent.top
                topMargin: 35
            }

            /**
                  * Balance vertical line image
                **/
            Item {
                id: idBalFadVerticalLine
                x: cppAudioAdaptor.balancePos
                Image {
                    source: "qrc:/image/BalanceFader/Set_Gfx_BalanceFader_VerticalLine1_n/Set_Gfx_BalanceFader_VerticalLine1_n.png"
                }
            }

            /**
                 * Fader horizontal line image
                **/
            Item {
                id: idBalFadHorizontalLine
                y: cppAudioAdaptor.faderPos
                Image {
                    source: "qrc:/image/BalanceFader/Set_Gfx_BalanceFader_HorizontalLine2_n/Set_Gfx_BalanceFader_HorizontalLine2_n.png"
                }
            }

            /**
                     * Balance & Fader pointer image
                     */
            Item {
                id: idBalFadPointer
                x: cppAudioAdaptor.balancePos
                y: cppAudioAdaptor.faderPos
                Image {
                    anchors.centerIn: parent
                    source: "qrc:/image/BalanceFader/Set_Gfx_BalanceFader_Pointer_n/Set_Gfx_BalanceFader_Pointer_n.png"
                }
            }

            MouseArea {
                id: idBalanceFaderMouseArea

                anchors.centerIn: idCarMatRect
                width: idCarMatRect.width + prMatMouseAreaIncreased
                height: idCarMatRect.height + prMatMouseAreaIncreased

                /**
                     * Calculating balance value from x-coordinate
                     */
                onPositionChanged: {
                    console.log("BalanceFader -- Mouse dragged - MouseX: " + mouseX + " MouseY: " + mouseY)
                    updateBalanceFaderFromXY(mouseX, mouseY)
                    //Updating positions of balance & fader vertical, horizontal lines & pointer locally
                    cppAudioAdaptor.updateBalanceFaderPositions(prFaderPositionFromY, prBalancePositionFromX)
                }

                /**
                 * Calculating fader value from y-coordinate
                 */

                onReleased: {
                    console.log("BalanceFader -- Mouse Released - MouseX: " + mouseX + " MouseY: " + mouseY)
                    updateBalanceFaderFromXY(mouseX, mouseY)
                    //Updating positions of balance & fader vertical, horizontal lines & pointer on response
                    cppAudioAdaptor.calculateBalanceFader(prFaderPositionFromY, prBalancePositionFromX)
                }
            }
        }
    }
    function updateBalanceFaderFromXY(mouseX, mouseY) {
        //Calculating mouseX & mouseY based on original mat size
        mouseX = mouseX - (prMatMouseAreaIncreased/2)
        mouseY = mouseY - (prMatMouseAreaIncreased/2)

        if (mouseX < 0) {
            prBalancePositionFromX = 0
        }
        else if (mouseX > idCarMatRect.width) {
            prBalancePositionFromX = idCarMatRect.width
        }
        else {
            prBalancePositionFromX = mouseX
        }

        if (mouseY < 0) {
            prFaderPositionFromY = 0
        }
        else if (mouseY > idCarMatRect.height) {
            prFaderPositionFromY = idCarMatRect.height
        }
        else {
            prFaderPositionFromY = mouseY
        }
    }

    /**
     * Fader value label, where the value of fader is shown
     */

    HBText {
        id: idFaderValueLabel
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
        text: (cppAudioAdaptor.fader < 0) ? ("-0" + -cppAudioAdaptor.fader) : (cppAudioAdaptor.fader > 0) ? ("+0" + cppAudioAdaptor.fader) : ("0" + cppAudioAdaptor.fader)
        anchors {
            left: parent.left
            leftMargin: 595
            top: parent.top
            topMargin: 267
        }
    }

    /**
     * Balance value label, where the value of balance is shown
     */
    HBText {
        id: idBalanceValueLabel
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
        text: (cppAudioAdaptor.balance < 0) ? ("-0" + -cppAudioAdaptor.balance) : (cppAudioAdaptor.balance > 0) ? ("+0" + cppAudioAdaptor.balance) : ("0" + cppAudioAdaptor.balance)
        anchors {
            left: parent.left
            leftMargin: 510
            top: parent.top
            topMargin: 398
        }
    }

    /**
         * Fader label
         */
    HBText {
        id: idFaderLabel
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        text: qsTr("TEXT_AUDIO_SETTING_FADER") + cppThemeMgr.languageChanged
        anchors {
            top: parent.top
            topMargin: 243
            left: parent.left
            leftMargin: 580
        }
    }

    /**
     * Balance label
     */
    HBText {
        id: idBalanceLabel
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        text: qsTr("TEXT_AUDIO_SETTING_BALANCE") + cppThemeMgr.languageChanged
        anchors {
            left: parent.left
            leftMargin: 420
            top: parent.top
            topMargin: 398
        }
    }


    ColumnLayout {
        anchors {
            left: parent.left
            leftMargin: 220
            top: parent.top
            topMargin: 159
        }

        HBText {
            id: idBalanceFaderLabel
            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
            text: qsTr("TEXT_AUDIO_SETTING_BALANCE") + cppThemeMgr.languageChanged + "\n" + "& " + qsTr("TEXT_AUDIO_SETTING_FADER") + cppThemeMgr.languageChanged
            anchors {
                left: parent.left
                leftMargin: 20
            }
        }

            ColumnLayout {
            anchors.top: idBalanceFaderLabel.bottom
            anchors.topMargin: 23
     /**
     * Driver button, on clicking this balance & fader values gets set to driver (0,5)
     */
            GenericButton {
                id: idFrontBtn
                implicitWidth: 112
                implicitHeight: 47
                contentItem: HBText {
                        id: idFrontBtntext
                        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
                        text: qsTr("TEXT_SETUP_BUTTON_FRONT_LABEL") + cppThemeMgr.languageChanged
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                /* Note: Here  Set_GfxBtnBg_n.png is Selected image and Set_GfxBtnBg_nd.png is normal image */
                defaultImageURL: ((cppAudioAdaptor.balance == 0) && (cppAudioAdaptor.fader == 5)) ? "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_n.png" : "qrc:/image/BalanceFader/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_nd.png"
                pressedImageURL: "qrc:/image/BalanceFader/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_n.png"

                onReleased: {
                    cppAudioAdaptor.calculateBalanceFader(prDriverBtnFaderPosition, prDriverBtnBalPosition)
                }
            }

     /**
     * Rear button, on clicking this balance & fader values gets set to rear (0,-5)
     */
            GenericButton {
                id: idRearBtn
                implicitWidth: 112
                implicitHeight: 47
                contentItem:HBText {
                        id: idRearBtntext
                        fontType:ThemeMgr.FONTTYPE_T24_LIGHT_C2
                        text: qsTr("TEXT_SETUP_BUTTON_REAR_LABEL") + cppThemeMgr.languageChanged
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                /* Note: Here  Set_GfxBtnBg_n.png is Selected image and Set_GfxBtnBg_nd.png is normal image */
                defaultImageURL: ((cppAudioAdaptor.balance == 0) && (cppAudioAdaptor.fader == -5)) ? "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_n.png" : "qrc:/image/BalanceFader/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_nd.png"
                pressedImageURL: "qrc:/image/BalanceFader/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_n.png"

                onReleased: {
                    cppAudioAdaptor.calculateBalanceFader(prRearBtnFaderPosition, prBalancePosition)
                }
            }
            GenericButton {
                id: idResetBtn
                implicitWidth: 112
                implicitHeight: 47
                contentItem: HBText {
                        id:idResetBtnText
                        fontType:ThemeMgr.FONTTYPE_T24_LIGHT_C2
                        text: qsTr("TEXT_SETUP_BUTTON_RESET_LABEL") + cppThemeMgr.languageChanged
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                /* Note: Here  Set_GfxBtnBg_n.png is Selected image and Set_GfxBtnBg_nd.png is normal image */
                defaultImageURL: ((cppAudioAdaptor.balance == 0) && (cppAudioAdaptor.fader == 0)) ? "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_n.png" : "qrc:/image/BalanceFader/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_nd.png"
                pressedImageURL: "qrc:/image/BalanceFader/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_n.png"
                onReleased: {
                    cppAudioAdaptor.calculateBalanceFader(prResetBtnFaderPosition, prBalancePosition)
                }

            }
        }
    }
}
