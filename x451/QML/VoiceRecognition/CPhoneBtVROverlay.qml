import QtQuick 2.7
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.thememanager 1.0
import "qrc:/QML/Common"

Item
{
    id: idPhoneBtVROverlay

    width: 800
    height: 480

    //Handling HK for Phone Bt VR overlay
    Connections
    {
        target: cppHardkeyAdaptor
        onSigPassHardkeyToOverlay:
        {
            cppVRApp.qmlLog("CPhoneBtVROverlay.qml: onSigPassHardkeyToOverlay: iKeyCode is: " + iKeyCode, " keystate is: ", iKeyState)
            //Inform Phone adaptor to handle hardkey event
            cppHardkeyAdaptor.invSetHKHandledByOverlayStatus(cppPhoneAdaptor.invHandleHardKeys(iKeyCode, iKeyState))
        }
    }

    AnimatedImage
    {
        id: idAnimatedImage
        anchors.centerIn: parent
        source: "qrc:/image/BT_VR_Animartion/Bt_Vr_Listining_Anim.gif"
    }

    //Text for BT VR Listening state
    HBText
    {
        id:idVRText
        width: 500 //205
        height: 40
        anchors
        {
            left: parent.left
            leftMargin: 205
            top: parent.top
            topMargin: 156
        }
        text: qsTr("TEXT_PHONE_BT_VR_OVERLAY_TEXT") + cppThemeMgr.languageChanged
        fontType: ThemeMgr.FONTTYPE_T35_C3
        horizontalAlignment: HBText.AlignLeft
    }

    // Mouse area to deactivate VR session on background touch
    MouseArea
    {
        anchors.fill: parent
        onPressed:
        {
            cppVRApp.qmlLog("CPhoneBtVROverlay.qml : Phone BT BR overlay background touched")
            // Deactivate Phone BT VR session
            cppPhoneAdaptor.invReqPhoneBtVrDeactivation()
        }
    }
}
