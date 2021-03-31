import QtQuick 2.7
import com.harman.qml.vrenum 1.0
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.thememanager 1.0
import "qrc:/QML/Common"

Item
{
    id: idVRAnimationScreen

    //Property to hold VR current state
    property int prVRState: cppVRAdaptor.vrState
    //Property for VR main command list index
    property int prMainCommandIndex: -1
    //property to show teleprompter list or not
    property bool prTeleprompterListStaus: cppVRAdaptor.teleprompterListStatus
    //property to hold default value for timer interval
    property int prTimerDefaultInterval: 2000
    width: 800
    height: 480

    //Handling HK for VR animation overlay
    Connections
    {
        target: cppHardkeyAdaptor
        onSigPassHardkeyToOverlay:
        {
            cppVRApp.qmlLog("VRAnimPopup.qml: onSigPassHardkeyToOverlay: iKeyCode is: " + iKeyCode, " keystate is: ", iKeyState)
            //Inform VR adaptor to handle hardkey event
            cppHardkeyAdaptor.invSetHKHandledByOverlayStatus(cppVRAdaptor.invHandleHardKeys(iKeyCode, iKeyState))
        }
    }

    //Get animation source based upon VR current state
    function getAnimationSource(eVRState)
    {
        cppPhoneApp.qmlLog("getVRState: " + eVRState)
        switch (eVRState)
        {
        case VREnum.EN_VR_STATE_SESSION_BEGIN:
            return "qrc:/image/VR_Animation/01_Entry_Line_Wipe_Out_Ani.gif"
        case VREnum.EN_VR_STATE_LISTENING:
            return "qrc:/image/VR_Animation/02_WaitingForCommand_SCR_SRL_Ani.gif"
        case VREnum.EN_VR_STATE_ACCEPTING:
            return "qrc:/image/VR_Animation/03_Listening_Line_Flick_Ani.gif"
        case VREnum.EN_VR_STATE_PROCESSING:
        case VREnum.EN_VR_STATE_PROMPTING:
            //return "qrc:/image/VR_Animation/04_Processing_Mick_Speake_Ani_Apper.gif"
            return "qrc:/image/VR_Animation/04_Processing_Mick_Speake_Ani.gif"
        default:
            return ""
        }
    }

    AnimatedImage
    {
        id: idAnimatedImage
        anchors.centerIn: parent
        source: ""
        //        onCurrentFrameChanged:
        //        {
        //            if(((VREnum.EN_VR_STATE_PROCESSING === prVRState) || (VREnum.EN_VR_STATE_PROMPTING === prVRState)) &&
        //               (currentFrame === (frameCount - 1)))
        //            {
        //                cppStartupAnim.qmlLog("VRAnimation, Processing_Mick_Speake_Ani_Appe complete, current frame is: " + currentFrame + "framecount is" + frameCount)
        //                source = "qrc:/image/VR_Animation/04_Processing_Mick_Speake_Ani.gif"
        //            }
        //            else
        //            {
        //                //do not do anything
        //            }
        //        }
    }

    //Text for VR Listening state
    HBText
    {
        id:idVRListeningStateText
        anchors
        {
            top: parent.top
            topMargin: 180
            horizontalCenter: parent.horizontalCenter
        }
        //visible: (prVRState == VREnum.EN_VR_STATE_LISTENING)
        visible: !prTeleprompterListStaus
        text: qsTr("TEXT_VR_ANIMATION_OVERLAY_TEXT") + cppThemeMgr.languageChanged
        fontType: ThemeMgr.FONTTYPE_T35_C3
        horizontalAlignment: HBText.AlignLeft
    }

    //Text for VR Main command
    HBText
    {
        id:idVRMainCommandText
        width: 740
        height: 30
        anchors
        {
            left: parent.left
            leftMargin: 20
            top: parent.top
            topMargin: 235
        }
        //visible: (prVRState == VREnum.EN_VR_STATE_LISTENING)
        visible: !prTeleprompterListStaus
        text: ""
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
        horizontalAlignment: HBText.AlignHCenter
    }

    Component
    {
        id: idTeleprompterListItemDelegate
        Column
        {
            /* HBText used to show Contact Name*/
            HBText {
                id: idTeleprompterListItem

                height: idTeleprompterList.prItemHeight - idTeleprompterItemSeparator.height
                width: idTeleprompterList.width
                anchors
                {
                    left: parent.left
                    leftMargin: 8
                }
                text: vrListItemNameRole
                elide: Text.ElideNone
                wrapMode: Text.Wrap
                horizontalAlignment: HBText.AlignLeft
                verticalAlignment: HBText.AlignVCenter
                fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
            }

            ListItemSeparator
            {
                id: idTeleprompterItemSeparator
            }
        }
    }

    // teleprompter list.
    GenericList
    {
        id: idTeleprompterList
        rowShownPerPage: 2
        height: (idTeleprompterList.prItemHeight + 4) * rowShownPerPage
        anchors
        {
            top: parent.top
            topMargin: 160
            left: parent.left
            leftMargin: 165
        }
        visible: prTeleprompterListStaus
        idList.model: cppVRAdaptor.teleprompterList
        idList.delegate: idTeleprompterListItemDelegate
    }

    Timer
    {
        id: idTimer
        interval: prTimerDefaultInterval
        repeat: true
        running: true
        onTriggered:
        {
            cppVRApp.qmlLog("VRAnimPopup.qml: Main VR commands length " + cppVRAdaptor.mainVRCommands.length)
            if(prMainCommandIndex < (cppVRAdaptor.mainVRCommands.length - 1))
            {
                prMainCommandIndex++
            }
            else
            {
                prMainCommandIndex = 0
            }

            cppVRApp.qmlLog("VRAnimPopup.qml: Main VR command index" + prMainCommandIndex)

            if((prMainCommandIndex >= 0) && (prMainCommandIndex < cppVRAdaptor.mainVRCommands.length))
            {
                idVRMainCommandText.text = cppVRAdaptor.mainVRCommands[prMainCommandIndex]
                cppVRApp.qmlLog("VRAnimPopup.qml: Main VR command text" + idVRMainCommandText.text)
            }
            else
            {
                cppVRApp.qmlLog("VRAnimPopup.qml : VR main command index out of range ")
            }
        }
    }

    // Mouse area to deactivate VR session on background touch
    MouseArea
    {
        anchors.fill: parent
        onPressed: {
            cppVRApp.qmlLog("VRAnimPopup.qml : VR animation popup background touched")
            // Deactivate VR session
            cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
        }
    }

    //VR help button
    GenericButton
    {
        id: idVRHelpBtn
        width: 96
        height: 96
        anchors {
            top: parent.top
            left: parent.left
            topMargin: 315
            leftMargin: 352
        }
        enabled: true

        defaultImageURL:"qrc:/image/Home/NightMode/Hom_Ico_Help/Home_Ico_Help_n.png"
        pressedImageURL: "qrc:/image/Home/NightMode/Hom_Ico_Help/Home_Ico_Help_np.png"
        disabledImageURL: "qrc:/image/Home/NightMode/Hom_Ico_Help/Home_Ico_Help_nd.png"

        onReleased:
        {
            // Deactivate VR session
            cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
            if(cppVRAdaptor.invGetVRHelpFileReadStatus())
            {
                cppVRApp.raiseSMEvent("VRHelpCategory", "")
            }
        }
    }

    //VR teleprompter list status change handling
    onPrTeleprompterListStausChanged:
    {
        cppVRApp.qmlLog("VRAnimPopup.qml: Teleprompter list status " + prTeleprompterListStaus)
        if(prTeleprompterListStaus)
        {
            idTimer.stop()
        }
        else
        {
           //do nothing
        }
    }

    //VR state change handling
    onPrVRStateChanged:
    {
        idAnimatedImage.source = getAnimationSource(prVRState)
    }

    Component.onDestruction:
    {
        cppVRApp.qmlLog("VRAnimPopup.qml : onAboutToHide")
        // Stop the timer
        idTimer.running                     = false
        prVRState                           = VREnum.EN_VR_STATE_NONE;
        idAnimatedImage.source              = ""
        cppVRAdaptor.teleprompterListStatus = false
    }
}
