import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import com.harman.qml.w3wenum 1.0
import com.harman.qml.thememanager 1.0
import "../Common"

BaseUI
{
    /* Image for Keypad Background overlay */
    Image {
        source: "qrc:/image/Popup/PopupBg/Gen_Gfx_PopupOverlayBg_n.png"
    }

    /* Cancel button */
    GenericButton {

        width: 50
        height: 50

        anchors {
            top: parent.top
            topMargin: 29
            left: parent.left
            leftMargin: 732
        }

        defaultImageURL : "qrc:/image/W3W/KeyPad/Gen_Ico_PopupCancel2_n-assets/Gen_Ico_PopupCancel2_n.png"
        pressedImageURL : "qrc:/image/W3W/KeyPad/Gen_Ico_PopupCancel2_n-assets/Gen_Ico_PopupCancel2_nf.png"

        onReleased: {
            cppW3WApplication.qmlLog("W3WStartupScreen.qml: Cancel button clicked")
            cppUIBase.raiseSMEvent("back", "")
        }
    }

    /* Swipe view for showing different W3W startup pages */
    SwipeView {
        id: idSwipeView

        width: 588
        height: parent.height

        anchors {
            top: parent.top
            horizontalCenter: parent.horizontalCenter
        }

        clip: true
        currentIndex: idPageIndicator.currentIndex

        /* First Page of W3W Startup screen */
        W3WStartupFirstPage {
        }

        /* Second Page of W3W Startup screen */
        W3WStartupSecondPage {
        }

        /* Third Page of W3W Startup screen */
        W3WStartupThirdPage {
        }
    }

    /* Page indicator component */
    PageIndicator {
        id: idPageIndicator
        spacing: 12
        count: idSwipeView.count
        currentIndex: idSwipeView.currentIndex

        anchors {
            top: parent.top
            topMargin: 398
            horizontalCenter: parent.horizontalCenter
        }

        /* Delegate to show the pagination icon */
        delegate: Item {
            width: parent.spacing
            height: parent.spacing
            Image {
                anchors.centerIn: parent
                source: (index === idSwipeView.currentIndex) ?
                            "qrc:/image/Home/Home_Pagination/Home_pagination_4.png"
                          : "qrc:/image/Home/Home_Pagination/Home_pagination_3.png"
            }
        }

        onCurrentIndexChanged: {
            cppUIBase.qmlLog("W3WStartupScreen.qml onCurrentIndexChanged: currentIndex: " + currentIndex
                             + "pageAtCurrentIndex: " + idSwipeView.itemAt(currentIndex).objectName)
        }
    }

    /* Do not shown me again button */
    GenericButton {

        width: 173
        height: 19

        anchors {
            top: parent.top
            topMargin: 435
            horizontalCenter: parent.horizontalCenter
        }

        defaultImageURL : "qrc:/image/W3W/Gen_btn_Don't show me again_n-assets/Gen_btn_Don't show me again_n.png"
        pressedImageURL : "qrc:/image/W3W/Gen_btn_Don't show me again_n-assets/Gen_btn_Don't show me again_n.png"

        onReleased: {
            cppW3WApplication.qmlLog("W3WStartupScreen.qml: Do not show me again button clicked")
            cppW3WAdaptor.invSetStartupWalkthroughStatus(false)
            cppUIBase.raiseSMEvent("back", "")
        }
    }
}
