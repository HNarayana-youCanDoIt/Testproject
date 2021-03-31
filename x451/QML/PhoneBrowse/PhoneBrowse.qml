import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.phoneenum 1.0
import com.harman.qml.hardkeyenum 1.0
import "qrc:/QML/Common"

BaseUI{
    id: idPhoneBrowseScreen

    // Property for Current Phone Browse screen index (Contacts / Calllogs / Contact Details etc.) which needs to be displayed
    property int prCurrentPhoneBrowseScreen: cppPhoneAdaptor.eCurrentPhoneBrowseScreen

    // Property alias for PhoneBrowseScreen Loader Component
    property alias prPhoneBrowseScreenLoader: idPhoneBrowseScreenLoader

    // Property alias for PhoneBrowseScreen TabBar Component
    property alias prPhoneBrowseTabBar: idPhoneBrowseTabBar

    // Mouse area to deactivate VR session on background touch
    MouseArea{
        anchors.fill: parent
        onPressed: {
            cppVRApp.qmlLog("PhoneBrowse.qml : MouseArea: onPressed")
            // Deactivate VR session
            cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
        }
    }


    /////////////////////////////////////////////////////////////////////////////////
    Loader {
        id: idPhoneBrowseScreenLoader
        anchors.fill: parent
        source: ""
    }

    // Fuction return the path of QML to be loaded in loader
    function getLoaderSource()
    {
        switch(prCurrentPhoneBrowseScreen)
        {
        case PhoneEnum.PHONE_BROWSE_TYPE_CALL_LOGS:
            return "qrc:/QML/PhoneBrowse/PhoneCallLogScreen.qml"

        case PhoneEnum.PHONE_BROWSE_TYPE_CONTACTS:
            return "qrc:/QML/PhoneBrowse/PhoneContactsScreen.qml"

        case PhoneEnum.PHONE_BROWSE_TYPE_FAVORITES:
            return "qrc:/QML/PhoneBrowse/PhoneFavoritesScreen.qml"

        case PhoneEnum.PHONE_BROWSE_TYPE_DIALPAD:
            return "qrc:/QML/PhoneBrowse/PhoneDialpadScreen.qml"

        case PhoneEnum.PHONE_BROWSE_TYPE_CONTACT_DETAILS:
            return "qrc:/QML/PhoneBrowse/PhoneContactDetailsScreen.qml"

        case PhoneEnum.PHONE_BROWSE_TYPE_FREQUENTLY_DIALED:
            return "qrc:/QML/PhoneBrowse/PhoneFrequentlyDialedScreen.qml"

        default:
            return ""
        }
    }

    onPrCurrentPhoneBrowseScreenChanged: {
        cppPhoneApp.qmlLog("onPrCurrentPhoneBrowseScreenChanged : new one ************ %%%%%% " + prCurrentPhoneBrowseScreen)
        idPhoneBrowseScreenLoader.source = getLoaderSource()
        if(PhoneEnum.PHONE_BROWSE_TYPE_CONTACT_DETAILS !== prCurrentPhoneBrowseScreen)
        {
            idPhoneBrowseTabBar.prCurrIndex = cppPhoneAdaptor.invGetBrowseItemIndex(prCurrentPhoneBrowseScreen)
        }
        else
        {
            idPhoneBrowseTabBar.prCurrIndex = cppPhoneAdaptor.invGetBrowseItemIndex(PhoneEnum.PHONE_BROWSE_TYPE_CONTACTS)
        }
    }

    Component.onCompleted : {
        idPhoneBrowseScreenLoader.source = getLoaderSource()
    }

    HBTabBar{
        id: idPhoneBrowseTabBar
        anchors{
            top: parent.top
            topMargin: 54
            left: parent.left
            leftMargin: 166
        }
        visible: !cppPhoneAdaptor.isInDTMFNumberPad

        prCurrIndex: prCurrentPhoneBrowseScreen

        prTabViewModel: cppPhoneAdaptor.pPhoneBrowseTabBarModel

        onSigTabViewCurrentIndexChanged:
        {
            if(index !== cppPhoneAdaptor.invGetBrowseItemIndex(prCurrentPhoneBrowseScreen))
            {
                cppPhoneApp.raiseSMEvent("PhoneBrowse", cppPhoneAdaptor.invGetBrowseType(index))
            }
            else
            {
                if(!isMovementByDrag)
                {
                  setPositionView();
                }

                cppPhoneApp.qmlLog("PhoneBrowse.qml index already active")
            }
        }
    }

    /*
     * Text used to show title text for shortcuts home screen
     */
    HBTitleWithBackButton {
        prTitle: qsTr("TEXT_PHONE_BROWSE_KEYPAD") + cppThemeMgr.languageChanged
        visible: !idPhoneBrowseTabBar.visible
    }
}
