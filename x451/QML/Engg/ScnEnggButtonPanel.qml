import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common"
import com.harman.qml.thememanager 1.0
import QtQuick.Layouts 1.3
import com.harman.qml.hardkeyenum  1.0

BaseUI
{
    id: idButtonPanelScreen

    /**
     *Property to hold the HardKey Code pressed while on Button Panel Screen
     **/
    property int prSelectedKeyCode: HardkeyEnum.KEYCODEHK_INVALID

    /**
     *Property to hold the HardKey State pressed while on Button Panel Screen
     **/
    property int prSelectedKeyState: HardkeyEnum.HKEY_STATE_INVALID

    /**
     *Property to hold the Rotary HardKey Code pressed while on Button Panel Screen
     **/
    property int prSelectedRREKeyCode: HardkeyEnum.KEYCODEHK_INVALID

    /**
     *Property to hold the Rotary HardKey State pressed while on Button Panel Screen
     **/
    property int prSelectedRREKeyState: HardkeyEnum.HKEY_STATE_INVALID

    HBTitleWithBackButton
    {
        prTitle: qsTr(cppEnggAdaptor.enggMenuScreenTitle) + cppThemeMgr.languageChanged;
    }

    Image {
        id: idBackgrndBp

        source: "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Gfx_Background_7in_n-assets/BtnPanel_Gfx_Background_7in_n.png"
        anchors.centerIn: parent

        Image {
            id: idBtPanel

            source: "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Gfx_Icons_BG_7in_n-assets/BtnPanel_Gfx_Icons_BG_7in_n.png"

            anchors{
                left:parent.left
                leftMargin: 80
                top:parent.top
                topMargin: 175
            }
        }
    }

    Image{
        id: idVolumeHK

        anchors{
            left: parent.left
            leftMargin: 80
            top:parent.top
            topMargin: 220
        }

        source: !(prSelectedKeyCode === HardkeyEnum.KEYCODEHK_VOLROTARY)
                ? "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_RotaryVolume_7in_n-assets/BtnPanel_Ico_RotaryVolume_7in_n.png"
                : (prSelectedKeyState === HardkeyEnum.HKEY_STATE_STUCK) ? "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_RotaryVolume_7in_n-assets/BtnPanel_Ico_RotaryVolume_7in_nd.png"
                                                                    : "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_RotaryVolume_7in_n-assets/BtnPanel_Ico_RotaryVolume_7in_nf.png"
    }

    Image{
        id: idRotaryListHK

        anchors{
            left: parent.left
            leftMargin: 640
            top:parent.top
            topMargin: 220
        }

        source: !(prSelectedRREKeyCode === HardkeyEnum.KEYCODEHK_MENUROTARY)
                ? "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_RotaryListSelection_7in_n-assets/BtnPanel_Ico_RotaryListSelection_7in_n.png"
                : (prSelectedRREKeyState === HardkeyEnum.HKEY_STATE_STUCK) ? "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_RotaryListSelection_7in_n-assets/BtnPanel_Ico_RotaryListSelection_7in_nd.png"
                                                                    : "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_RotaryListSelection_7in_n-assets/BtnPanel_Ico_RotaryListSelection_7in_nf.png"
    }


    Image{
        id: idVolumeRotaryLeftKnob

        anchors{
            left: parent.left
            leftMargin: 60
            top: parent.top
            topMargin: 195
        }
        source: ((prSelectedKeyCode === HardkeyEnum.KEYCODEHK_VOLROTARY_KNOB)
                 && (prSelectedKeyState === HardkeyEnum.HKEY_STATE_ROTATE_LEFT))
                ? "qrc:/image/EnggMenu/ButtonPanel/Gen_Gfx_BtnPanelLeftArrow_7in_n-assets/Gen_Gfx_BtnPanelLeftArrow_n.png"
                : ""
    }

    Image{
        id: idVolumeRotaryRightKnob

        anchors{
            left: parent.left
            leftMargin: 110
            top: parent.top
            topMargin: 195
        }

        source: ((prSelectedKeyCode === HardkeyEnum.KEYCODEHK_VOLROTARY_KNOB)
                 && (prSelectedKeyState === HardkeyEnum.HKEY_STATE_ROTATE_RIGHT))
                ? "qrc:/image/EnggMenu/ButtonPanel/Gen_Gfx_BtnPanelRightArrow_7in_n-assets/Gen_Gfx_BtnPanelRightArrow_n.png"
                : ""
    }

    Image{
        id: idMenuRotaryLeftKnob

        anchors{
            left: parent.left
            leftMargin: 620
            top: parent.top
            topMargin: 195
        }
        source: ((prSelectedRREKeyCode === HardkeyEnum.KEYCODEHK_MENUROTARY_KNOB)
                 && (prSelectedRREKeyState === HardkeyEnum.HKEY_STATE_ROTATE_LEFT))
                ? "qrc:/image/EnggMenu/ButtonPanel/Gen_Gfx_BtnPanelLeftArrow_7in_n-assets/Gen_Gfx_BtnPanelLeftArrow_n.png"
                : ""
    }

    Image{
        id: idMenuRotaryRightKnob

        anchors{
            left: parent.left
            leftMargin: 672
            top: parent.top
            topMargin: 195
        }

        source: ((prSelectedRREKeyCode === HardkeyEnum.KEYCODEHK_MENUROTARY_KNOB)
                 && (prSelectedRREKeyState === HardkeyEnum.HKEY_STATE_ROTATE_RIGHT))
                ? "qrc:/image/EnggMenu/ButtonPanel/Gen_Gfx_BtnPanelRightArrow_7in_n-assets/Gen_Gfx_BtnPanelRightArrow_n.png"
                : ""
    }

    Timer {
        id:idRRETimer

        interval: 700
        onTriggered:
        {
            prSelectedRREKeyCode = HardkeyEnum.KEYCODEHK_INVALID
            prSelectedRREKeyState = HardkeyEnum.HKEY_STATE_INVALID
        }
    }

    Timer {
        id:idTimer
        interval: 700
        onTriggered:
        {
            prSelectedKeyCode = HardkeyEnum.KEYCODEHK_INVALID
            prSelectedKeyState = HardkeyEnum.HKEY_STATE_INVALID
        }
    }

    RowLayout
    {
        spacing: 2

        anchors{
            left: parent.left
            leftMargin: 175
            top:parent.top
            topMargin: 235
        }


        Image {
            id: idHomeHk

            source: !(prSelectedKeyCode === HardkeyEnum.KEYCODEHK_HOME)
                    ? "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_Home_7in_n-assets/BtnPanel_Ico_Home_7in_n.png"
                    : (prSelectedKeyState === HardkeyEnum.HKEY_STATE_STUCK) ? "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_Home_7in_n-assets/BtnPanel_Ico_Home_7in_nd.png"
                                                                        : "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_Home_7in_n-assets/BtnPanel_Ico_Home_7in_nf.png"
        }

        Image {
            id: idSeparator_1

            source: "qrc:/image/EnggMenu/ButtonPanel/Gen_gfx_divider_7in_n-assets/Gen_gfx_divider_7in_n.png"
        }

        Image {
            id: idSourceHk

            source: !(prSelectedKeyCode === HardkeyEnum.KEYCODEHK_FAVORITE)
                    ? "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_Favorite_7in_n-assets/BtnPanel_Ico_Favorite_7inch_n.png"
                    : (prSelectedKeyState === HardkeyEnum.HKEY_STATE_STUCK) ? "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_Favorite_7in_n-assets/BtnPanel_Ico_Favorite_7inch_nd.png"
                                                                        : "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_Favorite_7in_n-assets/BtnPanel_Ico_Favorite_7inch_nf.png"
        }

        Image {
            id: idSeparator_2

            source: "qrc:/image/EnggMenu/ButtonPanel/Gen_gfx_divider_7in_n-assets/Gen_gfx_divider_7in_n.png"
        }


        Image {
            id: idPreviousHk

            source: !(prSelectedKeyCode === HardkeyEnum.KEYCODEHK_SEEKDOWN)
                    ? "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_Prev_7in_n-assets/BtnPanel_Ico_Prev_7in_n.png"
                    : (prSelectedKeyState === HardkeyEnum.HKEY_STATE_STUCK) ? "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_Prev_7in_n-assets/BtnPanel_Ico_Prev_7in_nd.png"
                                                                        : "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_Prev_7in_n-assets/BtnPanel_Ico_Prev_7in_nf.png"
        }

        Image {
            id: idSeparator_3

            source: "qrc:/image/EnggMenu/ButtonPanel/Gen_gfx_divider_7in_n-assets/Gen_gfx_divider_7in_n.png"
        }

        Image {
            id: idNextHk

            source: !(prSelectedKeyCode === HardkeyEnum.KEYCODEHK_SEEKUP)
                    ? "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_Next_7in_n-assets/BtnPanel_Ico_Next_7in_n.png"
                    : (prSelectedKeyState === HardkeyEnum.HKEY_STATE_STUCK) ? "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_Next_7in_n-assets/BtnPanel_Ico_Next_7in_nd.png"
                                                                        : "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_Next_7in_n-assets/BtnPanel_Ico_Next_7in_nf.png"
        }

        Image {
            id: idSeparator_4

            source: "qrc:/image/EnggMenu/ButtonPanel/Gen_gfx_divider_7in_n-assets/Gen_gfx_divider_7in_n.png"
        }

        Image {
            id: idPhoneHk

            source: !(prSelectedKeyCode === HardkeyEnum.KEYCODEHK_PHONE)
                    ? "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_Phone_7in_n-assets/BtnPanel_Ico_Phone_7in_n.png"
                    : (prSelectedKeyState === HardkeyEnum.HKEY_STATE_STUCK) ? "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_Phone_7in_n-assets/BtnPanel_Ico_Phone_7in_nd.png"
                                                                        : "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_Phone_7in_n-assets/BtnPanel_Ico_Phone_7in_nf.png"

        }

        Image {
            id: idSeparator_5

            anchors{

            }
            source: "qrc:/image/EnggMenu/ButtonPanel/Gen_gfx_divider_7in_n-assets/Gen_gfx_divider_7in_n.png"
        }

        Image {
            id: idBackHk

            source: !(prSelectedKeyCode === HardkeyEnum.KEYCODEHK_BACK)
                    ? "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_Back_7in_n-assets/BtnPanel_Ico_Back_7in_n.png"
                    : ((prSelectedKeyState === HardkeyEnum.HKEY_STATE_STUCK) ? "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_Back_7in_n-assets/BtnPanel_Ico_Back_7in_nd.png"
                                                                        : "qrc:/image/EnggMenu/ButtonPanel/BtnPanel_Ico_Back_7in_n-assets/BtnPanel_Ico_Back_7in_nf.png")

        }

    }

    Connections
    {
        target: cppEnggAdaptor
        onSigButtonPanelHKPressedChanged :
        {
            console.log("onSigButtonPanelHKPressedChanged:: iKeyCode"+ iKeyCode)

            prSelectedRREKeyState = HardkeyEnum.KEYCODEHK_INVALID
            prSelectedRREKeyCode = HardkeyEnum.KEYCODEHK_INVALID

            if(iKeyState == HardkeyEnum.HKEY_STATE_PRESSED
                    || iKeyState == HardkeyEnum.HKEY_STATE_LONGPRESSED)
            {
                prSelectedKeyCode = iKeyCode
                prSelectedKeyState = HardkeyEnum.KEYCODEHK_INVALID
            }
            else if(iKeyState == HardkeyEnum.HKEY_STATE_STUCK)
            {
                prSelectedKeyCode = iKeyCode
                prSelectedKeyState = HardkeyEnum.HKEY_STATE_STUCK
            }
            else if(iKeyState == HardkeyEnum.HKEY_STATE_RELEASED
                    || iKeyState == HardkeyEnum.HKEY_STATE_LONGRELEASED)
            {
                if(HardkeyEnum.HKEY_STATE_STUCK !== prSelectedKeyState)
                    prSelectedKeyCode = HardkeyEnum.KEYCODEHK_INVALID
            }
            else if(iKeyState == HardkeyEnum.HKEY_STATE_ROTATE_LEFT
                    || iKeyState == HardkeyEnum.HKEY_STATE_ROTATE_RIGHT )
            {
                prSelectedKeyCode = iKeyCode
                prSelectedKeyState = iKeyState

                if(idTimer.running)
                    idTimer.restart()
                else
                    idTimer.start()
            }
            else
            {
                //Do nothing
            }
        }
    }

    Connections
    {
        target: cppHardkeyAdaptor

        onSigRotaryPressed :
        {
            idRRETimer.stop()
            console.log("onSigRotaryPressed:: iKeyCode "+ iKeyCode+ "iKeyState: "+ iKeyState)

            prSelectedKeyCode = HardkeyEnum.KEYCODEHK_INVALID
            prSelectedKeyState = HardkeyEnum.KEYCODEHK_INVALID

            if(iKeyState == HardkeyEnum.HKEY_STATE_RELEASED
                    || iKeyState == HardkeyEnum.HKEY_STATE_LONGRELEASED)
            {
                if(HardkeyEnum.HKEY_STATE_STUCK !== prSelectedRREKeyState)
                    prSelectedRREKeyCode = HardkeyEnum.KEYCODEHK_INVALID
            }
            else if(iKeyState == HardkeyEnum.HKEY_STATE_STUCK)
            {
                prSelectedRREKeyCode = iKeyCode
                prSelectedRREKeyState = HardkeyEnum.HKEY_STATE_STUCK
            }
            else if(iKeyState == HardkeyEnum.HKEY_STATE_PRESSED
                    || iKeyState == HardkeyEnum.HKEY_STATE_LONGPRESSED )
            {
                prSelectedRREKeyCode = iKeyCode
                prSelectedRREKeyState = HardkeyEnum.KEYCODEHK_INVALID
            }
            else
            {
                //Do nothing
            }
        }

        onSigRotaryUpdate :
        {
            console.log("onSigRotaryUpdate:: iKeyCode"+ iKeyCode + "iKeyState: "+ iKeyState)

            if(iKeyState == HardkeyEnum.HKEY_STATE_ROTATE_LEFT
                    || iKeyState == HardkeyEnum.HKEY_STATE_ROTATE_RIGHT )
            {
                prSelectedRREKeyCode = iKeyCode
                prSelectedRREKeyState = iKeyState

                if(idRRETimer.running)
                    idRRETimer.restart()
                else
                    idRRETimer.start()
            }

            else
            {
                //Do nothing
            }

        }
    }
}

