import QtQuick 2.7
import com.harman.qml.phoneenum 1.0
import "../PhoneBrowse"

PhoneBrowse {

    // Fuction return the path of QML to be loaded in loader
    function getW3WPhoneBrowseLoaderSource()
    {
        cppW3WApplication.qmlLog("W3WPhoneBrowse.qml: getW3WPhoneBrowseLoaderSource: prCurrentPhoneBrowseScreen :" + prCurrentPhoneBrowseScreen)

        switch(prCurrentPhoneBrowseScreen)
        {
        case PhoneEnum.PHONE_BROWSE_TYPE_CONTACTS:
            return "qrc:/QML/W3W/W3WContactsScreen.qml"

        case PhoneEnum.PHONE_BROWSE_TYPE_CONTACT_DETAILS:
            return "qrc:/QML/W3W/W3WContactDetailsScreen.qml"

        default:
            return ""
        }
    }

    // Load the W3W Phone Browse Components
    prPhoneBrowseScreenLoader.source: getW3WPhoneBrowseLoaderSource()

    // Tab movement is disabled, as W3W Phone Browse needs only Contacts tab to be displayed
    prPhoneBrowseTabBar.prIsTabBarMovementEnabled: false

    onPrCurrentPhoneBrowseScreenChanged: {
        cppPhoneApp.qmlLog("W3WPhoneBrowse.qml onPrCurrentPhoneBrowseScreenChanged :" + prCurrentPhoneBrowseScreen)
        prPhoneBrowseScreenLoader.source = getW3WPhoneBrowseLoaderSource()
    }
}
