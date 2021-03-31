import QtQuick 2.7
import com.harman.qml.thememanager 1.0
import com.harman.qml.Media 1.0
import com.harman.qml.mediaenum 1.0
import com.harman.qml.audioenums 1.0
import com.harman.qml.popupenums 1.0
import com.harman.qml.hardkeyenum 1.0
import "../Common"

BaseUI {

    function processBrowseCategoryRequest(itemMetadataType)
    {
        cppMediaApp.qmlLog("MediaBrowseCategory.qml - idBrowseCategoryItemDelegate - index: "+ itemMetadataType)

        if((MediaEnum.BROWSEITEM_PICTURE === itemMetadataType) && (cppVehicleAdaptor.speedLockOutStatus))
        {
            PopupManager.showPopup(PopupEnum.EN_POPUPID_USB_SPEED_LOCKOUT_IMAGES)
        }
        else
        {
            MediaAdaptor.processBrowseCategoryRequest(itemMetadataType)
        }
    }

    HBTitleWithBackButton{
        prTitle: qsTr("Browse") + cppThemeMgr.languageChanged
    }

    //Delegate
    Component{
        id: idBrowseCategoryItemDelegate

        Column{
            //This screen shall never be displayed for BT source, hence only checking for USB slot device
            enabled: MediaAdaptor.isUSBDeviceCategoryAvailable(itemMetadataType)
            ListItemWithIconComp {
                id: idBrowseListItem
                height: idMediaBrowseList.prItemHeight - idBrowseListSeperator.height
                width: idMediaBrowseList.idList.width
                prEnabledTextFontType: ThemeMgr.FONTTYPE_T35_C3
                prDisabledTextFontType: ThemeMgr.FONTTYPE_T35_C3_DISABLED
                prIconLeftMargin:0
                prTextLeftMargin: 0
                prTextWidth: 320
                prText: itemNameRole
                prDefaultIconImage : itemImageRole
                prPressedIconImage: itemImageRole
                prDisabledIconImage: MediaAdaptor.getBrowseCategoryImagePath(itemMetadataType, false)
                button.pressedImageURL: "qrc:/image/Gen_Gfx_ListCursor_7in_n-assets/Gen_Gfx_ListCursor_n.png"

                button.onReleased:
                {
                    processBrowseCategoryRequest(itemMetadataType)
                }
            }

            ListItemSeparator{
                id: idBrowseListSeperator
            }

            Connections{
                target: cppHardkeyAdaptor
                onSigRotaryPressed: {
                    cppMediaApp.qmlLog("MediaBrowseScreen.qml : right rotary pressed")

                    if(HardkeyEnum.KEYCODEHK_MENUROTARY === iKeyCode
                            && (HardkeyEnum.HKEY_STATE_RELEASED === iKeyState
                                || HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState))
                    {
                        if(idMediaBrowseList.idList.currentIndex === index)
                        {
                            //This screen shall never be displayed for BT hence only a check for USB category
                            if(MediaAdaptor.isUSBDeviceCategoryAvailable(itemMetadataType))
                            {
                                processBrowseCategoryRequest(itemMetadataType)
                            }
                        }
                    }
                }
            }
        }

    }

    GenericList{
        id: idMediaBrowseList

        idList.model: MediaAdaptor.mediaBrowseListModel
        idList.delegate: idBrowseCategoryItemDelegate

        idList.onModelChanged: {
            idList.currentIndex = -1
        }
    }
}
