import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.popupenums 1.0
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.dynamicMaskedMouseArea 1.0
import QtGraphicalEffects 1.0

import "../../Common"

//// Doodle My Sticker Icon Sub Element Layout
Item {
    anchors {
        fill: parent
    }

    //// property to handle popup ID
    property int prPopupID: PopupEnum.EN_POPUPID_UNKNOWN

    //// property to handle animation for Icon
    property alias prDoodleIconImage: idDoodleIconImage

    //// Doodle Layout with drop area and icon
    Item {
        anchors {
            fill: parent
        }

        //// DropArea for Doodle Icon
        DropArea {
            anchors {
                fill: parent
            }
        }

        //// Doodle Icon Layout
        Item {
            id: idDoodleIconLayuot

            x: cppDoodleAdaptor.doodlePosition.x - width/2
            y: cppDoodleAdaptor.doodlePosition.y - height/2

            width: cppDoodleAdaptor.doodleSize.x
            height: cppDoodleAdaptor.doodleSize.y

            Drag.active: idDoodleSetupButton.drag.active
            Drag.hotSpot.x: 10
            Drag.hotSpot.y: 10

            //// MouseArea used drag/drop icon or to open doodle setup screen
            MouseArea {
                id: idDoodleSetupButton
                anchors.fill: parent

                hoverEnabled: true

                //// Property to maintain touch and hold status used in drag/drop flow
                property bool touchAndHold: false

                //// Property to maintain touch and position status used in press/relase flow
                property bool touchInside: false

                ////Image used to show doodle icon
                Image {
                    id: idDoodleIconImage
                    anchors {
                        centerIn: parent
                    }

                    width: idDoodleIconLayuot.width * cppUIBase.screenAspectRatio * (idDoodleSetupButton.touchAndHold ? 1.05 : 1.00)
                    height: idDoodleIconLayuot.height * (idDoodleSetupButton.touchAndHold ? 1.05 : 1.00)

                    //// Behavior Animation used to show popup-stick effect for touch and hold
                    Behavior on width {
                        NumberAnimation {
                            duration: 100
                            easing.type: Easing.OutBack
                        }
                    }
                    Behavior on height {
                        NumberAnimation {
                            duration: 100
                            easing.type: Easing.OutBack
                        }
                    }

                    //Please Note: Update doodleSize porperty in CDoodleAdaptor as per source image size
                    source: cppDoodleAdaptor.doodleImageURL
                }

                //// function to handle flow on movement complete
                onPressed: {
                    cppUIBase.qmlLog("DoodleMyStickerIcon.qml: idDoodleSetupButton: onPressed")
                    drag.target = null
                    touchAndHold = false
                    touchInside = true
                }

                //// function to handle flow on press event
                onReleased: {
                    drag.target = null
                    if (touchAndHold) {
                        cppUIBase.qmlLog("DoodleMyStickerIcon.qml, idDoodleSetupButton: onReleased Long")
                        onMovementCompleted()
                    } else if (touchInside){
                        cppUIBase.qmlLog("DoodleMyStickerIcon.qml, idDoodleSetupButton: onReleased Short")
                        PopupManager.ePopupResult = PopupEnum.EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS
                        PopupManager.forceClosePopup(parent.parent.parent.prPopupID)
                        if (PopupEnum.EN_POPUPID_DOODLE_MYSTICKER_ICON === parent.parent.parent.prPopupID) {
                            cppDoodleAdaptor.openDoodleSetupFromDoodle()
                        }
                    } else {
                        cppUIBase.qmlLog("DoodleMyStickerIcon.qml, idDoodleSetupButton: onReleased outside")
                    }
                    touchAndHold = false
                    touchInside = false
                }

                //// function to handle flow on release event
                onCanceled: {
                    cppUIBase.qmlLog("DoodleMyStickerIcon.qml: idDoodleSetupButton: onCanceled")
                    drag.target = null
                    touchAndHold = false
                    touchInside = false
                }

                //// function to handle flow on press and hold event
                onPressAndHold: {
                    cppUIBase.qmlLog("DoodleMyStickerIcon.qml: idDoodleSetupButton: onPressAndHold")
                    if (touchInside) {
                        drag.target = parent
                        touchAndHold = true
                    }
                }

                //// function to handle touch released outside of button
                onExited: {
                    cppUIBase.qmlLog("DoodleMyStickerIcon.qml: idDoodleSetupButton: onExited")
                    touchInside = false
                }

                //// function to handle flow on movement complete
                function onMovementCompleted() {
                    cppUIBase.qmlLog("DoodleMyStickerIcon.qml, idDoodleSetupButton: onMovementCompleted")
                    cppDoodleAdaptor.updateDoodleStickerPosition(idDoodleIconLayuot.x + idDoodleIconLayuot.width/2, idDoodleIconLayuot.y + idDoodleIconLayuot.height/2)
                }
            }

            //// Behavior Animation used to show motion while shifting to final position
            Behavior on x {
                NumberAnimation {
                    duration: 150
                    easing.type: Easing.OutBack
                }
            }
            Behavior on y {
                NumberAnimation {
                    duration: 150
                    easing.type: Easing.OutBack
                }
            }
        }

        //// DynamicMaskedMouseArea used to hide doodle Icon
        DynamicMaskedMouseArea {
            anchors {
                fill: parent
            }

            alphaThreshold: 0.5
            maskSource: idDoodleIconImage.source
            maskPositionX: idDoodleIconLayuot.x
            maskPositionY: idDoodleIconLayuot.y

            invertArea: true

            onPressed: {
                cppUIBase.qmlLog("DoodleMyStickerIcon.qml, CancelButton: onPressed")
                // Deactivate VR session
                cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
                // Deactivate phone bt vr
                cppPhoneAdaptor.invReqPhoneBtVrDeactivation()
            }

            onReleased: {
                cppUIBase.qmlLog("DoodleMyStickerIcon.qml, CancelButton: onReleased")
                PopupManager.ePopupResult = PopupEnum.EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS
                PopupManager.forceClosePopup(parent.parent.prPopupID)
            }
        }
    }

    //// Connections to handle hard key events
    Connections {
        target: PopupManager
        onSigRotaryPressedPopup: {
            cppUIBase.qmlLog("DoodleMyStickerIcon.qml: onRotaryPressed: " + iKeyState)
            if((HardkeyEnum.HKEY_STATE_RELEASED === iKeyState) || (HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState)) {
                PopupManager.closeOnHardKey()
            }
        }
    }

    //// Connections to handle updated doodle layoit position
    Connections {
        target: cppDoodleAdaptor
        onSigDoodlePositionChanged: {
            cppUIBase.qmlLog("DoodleMyStickerIcon.qml: onSigDoodlePositionChanged: ")
            idDoodleIconLayuot.x = cppDoodleAdaptor.doodlePosition.x - idDoodleIconLayuot.width/2
            idDoodleIconLayuot.y = cppDoodleAdaptor.doodlePosition.y - idDoodleIconLayuot.height/2
        }
    }
}
