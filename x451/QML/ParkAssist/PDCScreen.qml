import QtQuick 2.7
import "../Common"
import com.harman.qml.parkassistenum 1.0
import com.harman.qml.thememanager 1.0

BaseUI {
    id: id_PDC_Screen

    /**
     * Background image of PDC screen.
     */
    prBackGroundImage: "qrc:/image/ParkAssist/PDC/Gfx_PDC_Bg_n.png"

    /**
     * Gray color grid image of PDC.
     */
    Image {
        id: idPDCGrid
        x: 0
        y: 0
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_Large_Gray_Grid_7in_n.png"
    }

    /**
     * Green zone images.
     */
    Image {
        id: idGreenGridLeft_Level6
        x: 207
        y: 302
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_21_Green_X4in_n_LB.png"

        visible: ((cppParkAssistAdaptor.pdcScreenLeftSensorState != ParkAssistEnum.PDC_LEFT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenLeftSensorState <= ParkAssistEnum.PDC_LEFT_ZONE_GREEN_LEVEL_6))
    }

    Image {
        id: idGreenGridMidLeft_Level6
        x: 295
        y: 326
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_22_Green_X4in_n_LB.png"

        visible: ((cppParkAssistAdaptor.pdcScreenMidLeftSensorState != ParkAssistEnum.PDC_MID_LEFT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenMidLeftSensorState <= ParkAssistEnum.PDC_MID_LEFT_ZONE_GREEN_LEVEL_6))
    }

    Image {
        id: idGreenGridMidRight_Level6
        x: 406
        y: 321
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_23_Green_X4in_n_RB.png"

        visible: ((cppParkAssistAdaptor.pdcScreenMidRightSensorState != ParkAssistEnum.PDC_MID_RIGHT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenMidRightSensorState <= ParkAssistEnum.PDC_MID_RIGHT_ZONE_GREEN_LEVEL_6))
    }

    Image {
        id: idGreenGridRight_Level6
        x: 482
        y: 292
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_24_Green_X4in_n_RB.png"

        visible: ((cppParkAssistAdaptor.pdcScreenRightSensorState != ParkAssistEnum.PDC_RIGHT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenRightSensorState <= ParkAssistEnum.PDC_RIGHT_ZONE_GREEN_LEVEL_6))
    }

    Image {
        id: idGreenGridLeft_Level5
        x: 207
        y: 259
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_17_Green_X4in_n_LT.png"

        visible: ((cppParkAssistAdaptor.pdcScreenLeftSensorState != ParkAssistEnum.PDC_LEFT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenLeftSensorState <= ParkAssistEnum.PDC_LEFT_ZONE_GREEN_LEVEL_5))
    }

    Image {
        id: idGreenGridMidLeft_Level5
        x: 285
        y: 280
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_18_Green_X4in_n_LT.png"

        visible: ((cppParkAssistAdaptor.pdcScreenMidLeftSensorState != ParkAssistEnum.PDC_MID_LEFT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenMidLeftSensorState <= ParkAssistEnum.PDC_MID_LEFT_ZONE_GREEN_LEVEL_5))
    }

    Image {
        id: idGreenGridMidRight_Level5
        x: 396
        y: 280
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_19_Green_X4in_n_RT.png"

        visible: ((cppParkAssistAdaptor.pdcScreenMidRightSensorState != ParkAssistEnum.PDC_MID_RIGHT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenMidRightSensorState <= ParkAssistEnum.PDC_MID_RIGHT_ZONE_GREEN_LEVEL_5))
    }

    Image {
        id: idGreenGridRight_Level5
        x: 485
        y: 260
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_20_Green_X4in_n_RT.png"

        visible: ((cppParkAssistAdaptor.pdcScreenRightSensorState != ParkAssistEnum.PDC_RIGHT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenRightSensorState <= ParkAssistEnum.PDC_RIGHT_ZONE_GREEN_LEVEL_5))
    }

    /**
     * Yellow zone images.
     */
    Image {
        id: idYellowGridLeft_Level4
        x: 209
        y: 229
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_13_Yellow_X4in_n_LB.png"

        visible: ((cppParkAssistAdaptor.pdcScreenLeftSensorState != ParkAssistEnum.PDC_LEFT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenLeftSensorState <= ParkAssistEnum.PDC_LEFT_ZONE_YELLOW_LEVEL_4))
    }

    Image {
        id: idYellowGridMidLeft_Level4
        x: 285
        y: 243
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_14_Yellow_X4in_n_LB.png"

        visible: ((cppParkAssistAdaptor.pdcScreenMidLeftSensorState != ParkAssistEnum.PDC_MID_LEFT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenMidLeftSensorState <= ParkAssistEnum.PDC_MID_LEFT_ZONE_YELLOW_LEVEL_4))
    }

    Image {
        id: idYellowGridMidRight_Level4
        x: 396
        y: 243
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_15_Yellow_X4in_n_RB.png"

        visible: ((cppParkAssistAdaptor.pdcScreenMidRightSensorState != ParkAssistEnum.PDC_MID_RIGHT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenMidRightSensorState <= ParkAssistEnum.PDC_MID_RIGHT_ZONE_YELLOW_LEVEL_4))
    }

    Image {
        id: idYellowGridRight_Level4
        x: 486
        y: 222
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_16_Yellow_X4in_n_RB.png"

        visible: ((cppParkAssistAdaptor.pdcScreenRightSensorState != ParkAssistEnum.PDC_RIGHT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenRightSensorState <= ParkAssistEnum.PDC_RIGHT_ZONE_YELLOW_LEVEL_4))
    }

    Image {
        id: idYellowGridLeft_Level3
        x: 209
        y: 189
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_09_Yellow_X4in_n_LT.png"

        visible: ((cppParkAssistAdaptor.pdcScreenLeftSensorState != ParkAssistEnum.PDC_LEFT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenLeftSensorState <= ParkAssistEnum.PDC_LEFT_ZONE_YELLOW_LEVEL_3))
    }

    Image {
        id: idYellowGridMidLeft_Level3
        x: 294
        y: 216
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_10_Yellow_X4in_n_LT.png"

        visible: ((cppParkAssistAdaptor.pdcScreenMidLeftSensorState != ParkAssistEnum.PDC_MID_LEFT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenMidLeftSensorState <= ParkAssistEnum.PDC_MID_LEFT_ZONE_YELLOW_LEVEL_3))
    }

    Image {
        id: idYellowGridMidRight_Level3
        x: 397
        y: 207
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_11_Yellow_X4in_n_RT.png"

        visible: ((cppParkAssistAdaptor.pdcScreenMidRightSensorState != ParkAssistEnum.PDC_MID_RIGHT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenMidRightSensorState <= ParkAssistEnum.PDC_MID_RIGHT_ZONE_YELLOW_LEVEL_3))
    }

    Image {
        id: idYellowGridRight_Level3
        x: 488
        y: 193
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_12_Yellow_X4in_n_RT.png"

        visible: ((cppParkAssistAdaptor.pdcScreenRightSensorState != ParkAssistEnum.PDC_RIGHT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenRightSensorState <= ParkAssistEnum.PDC_RIGHT_ZONE_YELLOW_LEVEL_3))
    }

    /**
     * Red zone images.
     */
    Image {
        id: idRedGridLeft_Level2
        x: 204
        y: 144
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_05_Red_X4in_n_LB.png"

        visible: ((cppParkAssistAdaptor.pdcScreenLeftSensorState != ParkAssistEnum.PDC_LEFT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenLeftSensorState <= ParkAssistEnum.PDC_LEFT_ZONE_RED_LEVEL_2))
    }

    Image {
        id: idRedGridMidLeft_Level2
        x: 295
        y: 168
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_06_Red_X4in_n_LB.png"

        visible: ((cppParkAssistAdaptor.pdcScreenMidLeftSensorState != ParkAssistEnum.PDC_MID_LEFT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenMidLeftSensorState <= ParkAssistEnum.PDC_MID_LEFT_ZONE_RED_LEVEL_2))
    }

    Image {
        id: idRedGridMidRight_Level2
        x: 396
        y: 167
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_07_Red_X4in_n_RB.png"

        visible: ((cppParkAssistAdaptor.pdcScreenMidRightSensorState != ParkAssistEnum.PDC_MID_RIGHT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenMidRightSensorState <= ParkAssistEnum.PDC_MID_RIGHT_ZONE_RED_LEVEL_2))
    }

    Image {
        id: idRedGridRight_Level2
        x: 487
        y: 142
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_08_Red_X4in_n_RB.png"

        visible: ((cppParkAssistAdaptor.pdcScreenRightSensorState != ParkAssistEnum.PDC_RIGHT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenRightSensorState <= ParkAssistEnum.PDC_RIGHT_ZONE_RED_LEVEL_2))
    }

    Image {
        id: idRedGridLeft_Level1
        x: 216
        y: 134
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_01_Red_X4in_n_LT.png"

        visible: ((cppParkAssistAdaptor.pdcScreenLeftSensorState != ParkAssistEnum.PDC_LEFT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenLeftSensorState <= ParkAssistEnum.PDC_LEFT_ZONE_RED_LEVEL_1))
    }

    Image {
        id: idRedGridMidLeft_Level1
        x: 315
        y: 120
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_02_Red_X4in_n_LT.png"

        visible: ((cppParkAssistAdaptor.pdcScreenMidLeftSensorState != ParkAssistEnum.PDC_MID_LEFT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenMidLeftSensorState <= ParkAssistEnum.PDC_MID_LEFT_ZONE_RED_LEVEL_1))
    }

    Image {
        id: idRedGridMidRight_Level1
        x: 405
        y: 136
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_03_Red_X4in_n_RT.png"

        visible: ((cppParkAssistAdaptor.pdcScreenMidRightSensorState != ParkAssistEnum.PDC_MID_RIGHT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenMidRightSensorState <= ParkAssistEnum.PDC_MID_RIGHT_ZONE_RED_LEVEL_1))
    }

    Image {
        id: idRedGridRight_Level1
        x: 486
        y: 122
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_04_Red_X4in_n_RT.png"

        visible: ((cppParkAssistAdaptor.pdcScreenRightSensorState != ParkAssistEnum.PDC_RIGHT_ZONE_NO_OBSTACLE) &&
                  (cppParkAssistAdaptor.pdcScreenRightSensorState <= ParkAssistEnum.PDC_RIGHT_ZONE_RED_LEVEL_1))
    }

    /**
     * Mask image for PDC screen zones.
     */
    Image {
        id: idPDCMaskImage
        x: 0
        y: 0
        source: "qrc:/image/ParkAssist/PDC/Gfx_Large_GridOverlay_Bg_7in_n.png"
    }

    /**
     * Car back image.
     */
    Image {
        id: idCarBackImage
        source: "qrc:/image/ParkAssist/PDC/Gfx_PDC_CarLarge_n.png"
        anchors {
            left: parent.left
            leftMargin: 255
            top:parent.top
            topMargin: -12
        }
    }

    /**
     * Notification area for fault messages, call & SMS.
     */
    Image {
        id: idNotificationArea
        source: "qrc:/image/ParkAssist/Gen_Gfx_BgNotification_X07in_n.png"
    }

    /**
     * Cancel button - To close the RVC-Screen, if this screen is activated from HMI
     */
    GenericButton {
        id: idCancelBtn
        anchors {
            right: parent.right
            rightMargin: 8
            top:parent.top
            topMargin: 97
        }
        width: 112
        height: 80

        defaultImageURL: "qrc:/image/Tuner/Tun_Ico_Cancel/Tun_Ico_Cancel_n.png"
        pressedImageURL: "qrc:/image/Tuner/Tun_Ico_Cancel/Tun_Ico_Cancel_nf.png"
        visible: cppParkAssistAdaptor.isPdcRvcActivatedFromHmi

        onReleased: {
            cppParkAssistApp.qmlLog("PDC_Screen.qml - Cancel button clicked")
            cppParkAssistAdaptor.activatePdcRvc(false)
        }
    }

    /**
     * Loader used to load the corresponding header of park assist screen
     */
    Loader {
        id: idParkAssistHeaderLoader
        source: "ParkAssistFaultMessageHeader.qml"
    }

    state: cppParkAssistAdaptor.parkAssistHeaderState

    states: [
        State {
            name: "Fault_Message_Header"
            PropertyChanges {
                target: idParkAssistHeaderLoader
                source: "ParkAssistFaultMessageHeader.qml"
            }
        }
    ]

    Component.onCompleted: {
        cppParkAssistApp.qmlLog("PDC_Screen.qml - Component.onCompleted")
    }
}
