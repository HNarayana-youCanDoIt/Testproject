import QtQuick 2.7
import com.harman.qml.thememanager 1.0
import com.harman.qml.Media 1.0
import com.harman.qml.audioenums 1.0
import com.harman.qml.mediaenum 1.0
import com.harman.qml.hardkeyenum 1.0
import "../Common"

BaseUI{

    //Property for current top item's index in the list
    property int  prCurrentTopIndex: 0

    //Property for current top item's Text
    property string prCurrentTopIndexText: ""

    //Timer for Windowing Logic. It starts when CurrentTopItemIndex changes and After the timer is triggered requestPage API is called with prCurrentTopIndex as an argument
    Timer{
        id: idWindowingTimer
        interval: 200
        running: false
        onTriggered: {
            cppMediaApp.qmlLog("MediaBrowseCategory.qml: Windowing Timer up. CurrentTopIndex: "+prCurrentTopIndex)
            MediaAdaptor.requestPage(prCurrentTopIndex)
        }
    }

    //Timer to show Loading animation over the list when the visible part of list is empty
    Timer{
        id: idLoadingAnimTimer
        interval: 100
        running: false
        onTriggered: {
            cppMediaApp.qmlLog("MediaBrowseCategory.qml: idLoadingAnimTimer up ")
            if (prCurrentTopIndexText === "")
            {
                idLoadingAnim.visible = true
            }
        }
    }

    HBTitleWithBackButton{
        prTitle: MediaAdaptor.browseCategoryScreenTitle
    }

    HBText {
        id: idBrowseItemEmptyText
        text: MediaAdaptor.getEmptyCategoryText()
        fontType: ThemeMgr.FONTTYPE_T35_C3

        anchors {
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
        }

        visible: (MediaEnum.BROWSEDATA_STATE_EMPTY === MediaAdaptor.browseDataState)
    }

    //Delegate
    Component
    {
        id: idBrowseCategoryItemDelegate

        Column
        {
            id: idMediaBrowseCaqtgeoryCol
            Row
            {
                id: idMediaBrowseCaqtgeoryRow

                //This image shall point to the Media now playing item from the list i.e. current album, track, artist etc
                Image {
                    id: idNowPlayingImg
                    //Scrollbar issues are observed with height 76, hence setting height to 74
                    height: 74

                    source: "qrc:/image/Media/Med_Ico_NowPlaying_7in_n-assets/Med_Ico_NowPlaying_n.png"
                    visible: ((itemActiveRole) && (cppAudioAdaptor.activeEntSrc !== AudioEnums.SRC_BT_A2DP1))
                }

                ListItemWithIconComp
                {
                    id: idBrowseCategoryListItem

                    height: idBrowseCategoryList.prItemHeight - idBrowseCategoryListSeperator.height
                    width: idBrowseCategoryList.idList.width
                    prEnabledTextFontType: ThemeMgr.FONTTYPE_T35_C3
                    prDisabledTextFontType: ThemeMgr.FONTTYPE_T35_C3_DISABLED
                    prIconLeftMargin: ((idNowPlayingImg.visible) ? 0 : idNowPlayingImg.width)
                    prTextLeftMargin: 0
                    prTextWidth: 360
                    prText: itemNameRole
                    prDefaultIconImage : itemImageRole
                    prPressedIconImage: itemImageRole
                    prDisabledIconImage: itemImageRole
                    prTextVerticalCenter: prIconVerticalCenter
                    button.pressedImageURL: "qrc:/image/Gen_Gfx_ListCursor_7in_n-assets/Gen_Gfx_ListCursor_n.png"

                    button.onReleased:
                    {
                        MediaAdaptor.browseItemClicked(itemIdRole, itemTypeRole, itemNameRole, itemFSContentTypeRole, index)
                    }

                    onPrTextChanged: {
                        prCurrentTopIndexText = itemNameRole
                    }
                }
            }

            ListItemSeparator
            {
                id: idBrowseCategoryListSeperator
            }

            Connections{
                target: cppHardkeyAdaptor
                onSigRotaryPressed: {
                    cppMediaApp.qmlLog("MediaBrowseCategory.qml : right rotary pressed")

                    if(HardkeyEnum.KEYCODEHK_MENUROTARY === iKeyCode
                            && (HardkeyEnum.HKEY_STATE_RELEASED === iKeyState
                                || HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState))
                    {
                        if(idBrowseCategoryList.idList.currentIndex === index)
                        {
                            MediaAdaptor.browseItemClicked(itemIdRole, itemTypeRole, itemNameRole, itemFSContentTypeRole, index)
                        }
                    }
                }
            }
        }
    }

    GenericList{
        id: idBrowseCategoryList

        idList.model: MediaAdaptor.mediaCategoryListModel
        idList.delegate: idBrowseCategoryItemDelegate
        visible: (MediaEnum.BROWSEDATA_STATE_AVAILABLE === MediaAdaptor.browseDataState)
        idList.onModelChanged: {
            idList.currentIndex = -1
        }

        onVisibleChanged: {
            cppMediaApp.qmlLog("MediaBrowseCategory.qml: onVisibleChanged: visibility: " + visible)

            if(visible)
            {
                idLoadingAnim.visible = false
                idBrowseCategoryList.idList.positionViewAtIndex(cppUIBase.getListTopItemIndex(), ListView.Beginning)
            }
            else
            {
                idList.currentIndex = -1
                idBrowseCategoryList.prRREIndex = -1
            }
        }

        idList.onContentYChanged: {
            if (prCurrentTopIndexText === "")
            {
                if(!idLoadingAnimTimer.running)
                {
                    idLoadingAnimTimer.start()
                }
            }
            else
            {
                idLoadingAnim.visible = false
            }
        }

        onPrCurrentTopItemIndexChanged: {
            idWindowingTimer.restart()
            prCurrentTopIndex = prCurrentTopItemIndex
        }
    }

    onPrCurrentTopIndexTextChanged: {
        if(prCurrentTopIndexText === "")
        {
            idLoadingAnim.visible = true
        }
        else
        {
            idLoadingAnim.visible = false
        }
    }

    BusyIndicator{
        id: idLoadingAnim
        anchors{
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
        }

        visible: ((MediaEnum.BROWSEDATA_STATE_NONE === MediaAdaptor.browseDataState)
                  || (MediaEnum.BROWSEDATA_STATE_FETCHING === MediaAdaptor.browseDataState))
    }

    Connections{
        target: MediaAdaptor
        onSigBrowseDataStateUpdated: {
            if(MediaEnum.BROWSEDATA_STATE_EMPTY === MediaAdaptor.browseDataState)
            {
                idBrowseItemEmptyText.text = MediaAdaptor.getEmptyCategoryText()
            }
        }
    }
}
