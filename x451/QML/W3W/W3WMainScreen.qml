import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.harman.qml.thememanager 1.0
import com.harman.qml.w3wenum 1.0
import com.harman.qml.popupenums 1.0
import "../Common"


BaseUI
{

    /* W3W Title with Setup button */
    RowLayout {

        anchors{
            top: parent.top
            topMargin: 50
        }

        /* HB text to show What 3 words? screen title */
        HBText {

            height: 76

            anchors{
                left: parent.left
                leftMargin: 149
            }

            fontType: ThemeMgr.FONTTYPE_T35_C3
            verticalAlignment: Text.AlignVCenter

            text: qsTr("TEXT_W3W_MAIN_TITLE") + cppThemeMgr.languageChanged
        }

        /* Generic button to show Info button */
        GenericButton {

            width: 76
            height: 76

            anchors{
                left: parent.left
                leftMargin: 477
            }

            defaultImageURL: "qrc:/image/W3W/Gen_Ico_Info_n-assets/Gen_Ico_Info_n.png"
            pressedImageURL: "qrc:/image/W3W/Gen_Ico_Info_n-assets/Gen_Ico_Info_nf.png"
            disabledImageURL: "qrc:/image/W3W/Gen_Ico_Info_n-assets/Gen_Ico_Info_nd.png"

            onReleased: {
                cppW3WApplication.qmlLog("W3WMainScreen.qml: Info button clicked")
                cppW3WApplication.raiseSMEvent("LaunchW3WAboutScreen", "")
            }
        }

        /* Generic button to show Setup button */
        GenericButton {

            width: 76
            height: 76

            anchors{
                left: parent.left
                leftMargin: 553
            }

            defaultImageURL: "qrc:/image/Tuner/Gen_Ico_Browse/Gen_Ico_Browse_n.png"
            pressedImageURL: "qrc:/image/Tuner/Gen_Ico_Browse/Gen_Ico_Browse_nf.png"
            disabledImageURL: "qrc:/image/Tuner/Gen_Ico_Browse/Gen_Ico_Browse_nd.png"

            onReleased: {
                cppW3WApplication.qmlLog("W3WMainScreen.qml: Setup button clicked")
                cppW3WApplication.raiseSMEvent("LaunchW3WSetupScreen", "")
            }
        }

    }

    /* W3W Address text placeholder with Mic button */
    Item {

        width: 480
        height: 59

        anchors{
            top: parent.top
            topMargin: 125
            left: parent.left
            leftMargin: 149
        }

        Image {

            source: "qrc:/image/W3W/Set_Gfx_PasswordTextBg_n-assets/Set_Gfx_PasswordTextBg_n.png"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    cppW3WApplication.raiseSMEvent("LaunchW3WAddressSuggestionScreen", "")
                }
            }
        }

        Image {
            id: idSlashImage

            anchors {
                left: parent.left
                leftMargin: 13
                verticalCenter: parent.verticalCenter
            }

            source: "qrc:/image/W3W/KeyPad/W3W_Marker_Logo-assets/W3W_Marker_Logo.png"
        }

        HBText {
            id: idW3WAddressPlaceholderText

            width: 405

            anchors {
                top: parent.top
                topMargin: 13
                left: idSlashImage.right
            }

            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter

            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
            text: ("" === cppW3WAdaptor.selectedW3WAddress) ? qsTr("TEXT_W3W_MAIN_PLACEHOLDER") + cppThemeMgr.languageChanged :
                                                              cppW3WAdaptor.selectedW3WAddress
        }

        /* Mic button */
        GenericButton {

            width: 55
            height: 55

            defaultImageURL : "qrc:/image/W3W/Gen_Ico_Mic_n-assets/Gen_Ico_Mic_n.png"
            pressedImageURL : "qrc:/image/W3W/Gen_Ico_Mic_n-assets/Gen_Ico_Mic_np.png"
            disabledImageURL: "qrc:/image/W3W/Gen_Ico_Mic_n-assets/Gen_Ico_Mic_nd.png"

            anchors {
                top: parent.top
                topMargin: 2
                left: parent.left
                leftMargin: 411
            }

            onReleased: {
                cppW3WApplication.qmlLog("W3WMainScreen.qml: Mic button clicked")
                cppW3WAdaptor.invActivateVRForW3W()
            }
        }
    }

    /* Row Layout for Share, Add Favorite and Navigate button */
    RowLayout {

        anchors {
            top: parent.top
            topMargin: 201
        }

        /* Share button */
        GenericButton {
            id: idShareButton

            width: 76
            height: 76

            anchors {
                left: parent.left
                leftMargin: 149
            }

            defaultImageURL : "qrc:/image/W3W/Gen_Ico_Share_n-assets/Gen_Ico_Share_n.png"
            pressedImageURL : "qrc:/image/W3W/Gen_Ico_Share_n-assets/Gen_Ico_Share_np.png"
            disabledImageURL: "qrc:/image/W3W/Gen_Ico_Share_n-assets/Gen_Ico_Share_nd.png"

            enabled: ("" !== cppW3WAdaptor.selectedW3WAddress)

            onReleased: {
                cppW3WApplication.qmlLog("W3WMainScreen.qml: Share button clicked")
                if(!cppPhoneAdaptor.hfpConnectionStatus) {
                    cppW3WApplication.qmlLog("W3WMainScreen.qml: HFP not connected")
                    PopupManager.showPopup(PopupEnum.EN_POPUPID_W3W_HFP_NOT_CONNECTED)
                }
                else if(!cppPhoneAdaptor.isSendingSMSAllowed) {
                    cppW3WApplication.qmlLog("W3WMainScreen.qml: SMS not supported")
                    PopupManager.showPopup(PopupEnum.EN_POPUPID_W3W_SMS_NOT_SUPPORTED)
                }
                else {
                    PopupManager.showPopup(PopupEnum.EN_POPUPID_W3W_SHARE_ADDRESS)
                }
            }
        }

        /* Add Favorite button */
        GenericButton {
            id: idAddFavoriteButton

            width: 76
            height: 76

            anchors {
                left: parent.left
                leftMargin: 345
            }

            defaultImageURL : "qrc:/image/W3W/Gen_Ico_AddFavourite_n-assets/Gen_Ico_AddFavourite_n.png"
            pressedImageURL : "qrc:/image/W3W/Gen_Ico_AddFavourite_n-assets/Gen_Ico_AddFavourite_np.png"
            disabledImageURL: "qrc:/image/W3W/Gen_Ico_AddFavourite_n-assets/Gen_Ico_AddFavourite_nd.png"

            enabled: ("" !== cppW3WAdaptor.selectedW3WAddress)

            onReleased: {
                cppW3WApplication.qmlLog("W3WMainScreen.qml: Add Favorite button clicked")

                if(cppW3WAdaptor.invIsFavoriteMaxLimitReached()) {
                    PopupManager.showPopup(PopupEnum.EN_POPUPID_W3W_FAVORITE_MAX_LIMIT)
                }
                else {
                    /* Mark this as as Selected W3W Address item for Favorite */
                    cppW3WAdaptor.invSelectW3WAddressForFavorite(W3WEnum.W3W_ADDRESS_TYPE_SELECTED,
                                                                 W3WEnum.W3W_FAVORITE_OPERATION_ADD)
                    cppW3WApplication.raiseSMEvent("LaunchW3WEditLabelScreen", "")
                }
            }
        }

        /* Navigate button */
        GenericButton {
            id: idNavigateButton

            width: 76
            height: 76

            anchors {
                left: parent.left
                leftMargin: 553
            }

            defaultImageURL : "qrc:/image/W3W/Gen_Ico_Navigate_n-assets/Gen_Ico_Navigate_n.png"
            pressedImageURL : "qrc:/image/W3W/Gen_Ico_Navigate_n-assets/Gen_Ico_Navigate_np.png"
            disabledImageURL: "qrc:/image/W3W/Gen_Ico_Navigate_n-assets/Gen_Ico_Navigate_nd.png"

            enabled: ("" !== cppW3WAdaptor.selectedW3WAddress)

            onReleased: {
                cppW3WApplication.qmlLog("W3WMainScreen.qml: Navigate button clicked")
                cppW3WAdaptor.invInitiateNavigation()
            }
        }
    }

    /* Row Layout for Favorite Addresses and Recent Addresses buttons */
    RowLayout {

        anchors{
            top: parent.top
            topMargin: 304
            left: parent.left
            leftMargin: 149
        }

        /* Favorite Addresses */
        Image {

            source: "qrc:/image/W3W/Set_Gfx_Addresses_Bg_n/Set_Gfx_Addresses_Bg_n.png"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    cppW3WApplication.qmlLog("W3WMainScreen.qml: Favorite button clicked")
                    cppW3WAdaptor.invGetW3WAddresses(W3WEnum.W3W_ADDRESS_TYPE_FAVORITE)
                    cppW3WApplication.raiseSMEvent("LaunchW3WFavoritesScreen", "")
                }
            }

            HBText {

                anchors {
                    top: parent.top
                    topMargin: 14
                    left: parent.left
                    leftMargin: 9
                }

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter

                fontType: ThemeMgr.FONTTYPE_T35_C3
                text: qsTr("TEXT_W3W_MAIN_FAVORITE_ADDRESSES") + cppThemeMgr.languageChanged
            }

            GenericButton {

                width: 76
                height: 76

                defaultImageURL : "qrc:/image/W3W/Gen_Ico_Favourite_n-assets/Gen_Ico_Favourite_n.png"
                pressedImageURL : "qrc:/image/W3W/Gen_Ico_Favourite_n-assets/Gen_Ico_Favourite_np.png"
                disabledImageURL: "qrc:/image/W3W/Gen_Ico_Favourite_n-assets/Gen_Ico_Favourite_nd.png"

                anchors {
                    top: parent.top
                    topMargin: 77
                    left: parent.left
                    leftMargin: 155
                }

                onReleased: {
                    cppW3WApplication.qmlLog("W3WMainScreen.qml: Favorite button clicked")
                    cppW3WAdaptor.invGetW3WAddresses(W3WEnum.W3W_ADDRESS_TYPE_FAVORITE)
                    cppW3WApplication.raiseSMEvent("LaunchW3WFavoritesScreen", "")
                }
            }
        }

        /* Recent Addresses */
        Image {

            anchors {
                left: parent.left
                leftMargin: 260
            }

            source: "qrc:/image/W3W/Set_Gfx_Addresses_Bg_n/Set_Gfx_Addresses_Bg_n.png"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    cppW3WApplication.qmlLog("W3WMainScreen.qml: Recent button clicked")
                    cppW3WAdaptor.invGetW3WAddresses(W3WEnum.W3W_ADDRESS_TYPE_RECENT)
                    cppW3WApplication.raiseSMEvent("LaunchW3WRecentScreen", "")
                }
            }

            HBText {

                anchors {
                    top: parent.top
                    topMargin: 14
                    left: parent.left
                    leftMargin: 9
                }

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter

                fontType: ThemeMgr.FONTTYPE_T35_C3
                text: qsTr("TEXT_W3W_MAIN_RECENT_ADDRESSES") + cppThemeMgr.languageChanged
            }

            GenericButton {

                width: 76
                height: 76

                defaultImageURL : "qrc:/image/W3W/Gen_Ico_Recent_n-assets/Gen_Ico_Recent_n.png"
                pressedImageURL : "qrc:/image/W3W/Gen_Ico_Recent_n-assets/Gen_Ico_Recent_np.png"
                disabledImageURL: "qrc:/image/W3W/Gen_Ico_Recent_n-assets/Gen_Ico_Recent_nd.png"

                anchors {
                    top: parent.top
                    topMargin: 77
                    left: parent.left
                    leftMargin: 155
                }

                onReleased: {
                    cppW3WApplication.qmlLog("W3WMainScreen.qml: Recent button clicked")
                    cppW3WAdaptor.invGetW3WAddresses(W3WEnum.W3W_ADDRESS_TYPE_RECENT)
                    cppW3WApplication.raiseSMEvent("LaunchW3WRecentScreen", "")
                }
            }
        }
    }
}
