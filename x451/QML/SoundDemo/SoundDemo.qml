import QtQuick 2.0
import QtQuick.Controls 2.1
import QtGraphicalEffects 1.0
import "../Common"
import com.harman.qml.SoundDemo 1.0
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.audioenums 1.0

BaseUI {
    id:idSoundDemo

    HBTitleWithBackButton {
        prTitle: qsTr("Sound Demo")+cppThemeMgr.languageChanged
    }

    /* Setup main screen delegate, this component contains label and a listItemSeparator image */
    Component {
        id: idDelegate

        Column {
            enabled: itemEnabledRole
            height: idSoundDemoList.prItemHeight
            ListItemWithIconComp
            {
                id: idListItem

                height: idProgress.visible ? (idSoundDemoList.prItemHeight - idProgress.height)
                                           : (idSoundDemoList.prItemHeight - idSeparator.height)
                width: idSoundDemoList.idList.width
                prEnabledTextFontType: ThemeMgr.FONTTYPE_T35_C3
                prDisabledTextFontType: ThemeMgr.FONTTYPE_T35_C3_DISABLED
                isIconOnLeft: false
                prIconRightMargin: -10
                prTextLeftMargin: 0
                prTextWidth: 360
                prText: itemCaptionRole
                prDefaultIconImage : itemImageRole
                prPressedIconImage: itemImageRole
                prDisabledIconImage: itemImageRole
                prTextVerticalCenter: prIconVerticalCenter
                button.pressedImageURL: "qrc:/image/Gen_Gfx_ListCursor_7in_n-assets/Gen_Gfx_ListCursor_n.png"

                button.onReleased:
                {
                    cppSoundDemoAdaptor.invSelectTrack(itemIdRole, itemTrackIdRole)
                }


                ProgressBar{
                    id: idProgress
                    width: idSoundDemoList.idList.width
                    height: 5
                    from: itemMinValRole
                    to: itemMaxValRole
                    value: itemCurrValRole
                    anchors.top: idListItem.bottom
                    visible: itemPgbVisibilityRole

                    background: Item{
                        Rectangle{
                            width:parent.width
                            height: parent.height
                            anchors.top: parent.top
                            color: "#5b5b5b"
                        }
                    }

                    contentItem: Item{
                        Rectangle{
                            width:idProgress.visualPosition * idProgress.width
                            height: parent.height
                            anchors.top: parent.top
                            color: cppThemeMgr.currentThemeColor
                        }
                    }
                }
            }

            Connections {
                target: cppHardkeyAdaptor
                onSigRotaryPressed: {
                    cppSoundDemoApp.qmlLog("GenericList: onRotaryUpdate: "+iKeyState)
                    if((HardkeyEnum.HKEY_STATE_RELEASED === iKeyState ||
                        HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState))
                    {
                        if(idSoundDemoList.idList.currentIndex === index)
                        {
                            cppSoundDemoApp.qmlLog("SoundDemo.qml - index: " + index)
                            cppSoundDemoAdaptor.invSelectTrack(itemIdRole)

                        }
                    }
                }
            }

            ListItemSeparator {
                id: idSeparator
                visible: !itemPgbVisibilityRole
            }
        }
    }
    /* Setup main list is populated using GenericList and SetupMainModel */
    GenericList {
        id: idSoundDemoList
        idList.model: cppSoundDemoAdaptor.demoModel
        idList.delegate: idDelegate
    }

    Connections{
        target: cppAudioAdaptor
        onSigActiveEntSrcChanged:
        {
            cppSoundDemoApp.qmlLog("SoundDemo.qml - Source change received.")
            if(AudioEnums.SRC_HDD !== cppAudioAdaptor.activeEntSrc)
            {
                cppUIBase.raiseSMEvent("back", "")
            }
        }
    }
}

