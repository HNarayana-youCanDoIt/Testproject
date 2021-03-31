import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3


/*
 * the main UI window screen which houses the other qmls
 * It will have the Loader to load the qml files in the main area
 * Also the drawer instances required on all the screen
 */
Item {
    id: idAppMainWindow
    objectName: "AppMainWindow"
    anchors.fill: parent
    property var _screenName: null
    property var _drawerScreenName: null
    property var _popupScreenName: null
    property var _overlayScreenName: null
    property var _drawersSourceComponent: null
    property var _popupSourceComponent: null
    property var _keypadOverlaySourceComponent: null
    property var _vrOverlaySourceComponent: null

    /*
     * Function is called from the CBaseApplication to load a particular QML component
     */
    function loadComponent(component, screenName) {
        cppUIBase.qmlLog("UI Main loadComponent, component: " + component + "screenName: " + screenName)
        _screenName = screenName
        idAppMainLoader.sourceComponent = component
    }

    /*
     * Function is called from the CBaseApplication to load Drawers QML component
     */
    function loadDrawersComponent(component, drawerScreenName) {
        cppUIBase.qmlLog("UI Main loadDrawersComponent, component: " + component)
        _drawerScreenName = drawerScreenName
        _drawersSourceComponent = component
    }

    /*
     * Method to be invoked to start screen timer of currently loaded screen
     */
    function startScreenTimer()
    {
        cppUIBase.qmlLog("UI Main startScreenTimer")
        idAppMainLoader.item.startScreenTimer()
    }

    /*
     * Loader to load the qml files in the main area
     */
    Loader {
        id: idAppMainLoader
        anchors.fill: parent
        asynchronous: true
        onStatusChanged: {
            if (idAppMainLoader.status === Loader.Ready) {

                //Set objectName
                idAppMainLoader.item.objectName = _screenName
                cppIntrospectionAdaptor.invSetScreenChanged(idAppMainLoader.item.objectName)
            }
        }
    }

    /*
     * Loader to load the Drawers
     */
    Loader {
        id: idDrawersLoader
        anchors.fill: parent
        asynchronous: true
        sourceComponent: _drawersSourceComponent
        onStatusChanged: {
            if (idDrawersLoader.status === Loader.Ready) {

                //Set objectName
                idDrawersLoader.item.objectName = _drawerScreenName
                cppIntrospectionAdaptor.invSetDrawerChanged(idDrawersLoader.item.objectName)
            }
        }
    }

    /*
     * Method to load keypad overlay
     */
    function loadKeypadOverlay(component, overlayScreenName)
    {
        _keypadOverlaySourceComponent = undefined
        cppUIBase.qmlLog("Load keypad overlay, component: " + component + "screen " + overlayScreenName)
        _overlayScreenName = overlayScreenName
        _keypadOverlaySourceComponent = component
        cppUIBase.qmlLog("Load keypad overlay, component: " + component + "_overlayScreenName " + _overlayScreenName)

    }

    /*
     * Method to unload keypad overlay
     */
    function unloadKeypadOverlay() {
        cppUIBase.qmlLog("Unload keypad overlay, component: " + _keypadOverlaySourceComponent)
        _keypadOverlaySourceComponent = undefined
    }

    /*
     * Loader to load the Keypad overlay
     */
    Loader{
        id:idKeypadOverlayLoader
        anchors.fill: parent
        sourceComponent: _keypadOverlaySourceComponent


        onStatusChanged: {

            if (idKeypadOverlayLoader.status === Loader.Ready) {

                //Set objectName

                idKeypadOverlayLoader.item.objectName = _overlayScreenName
                cppIntrospectionAdaptor.invSetScreenChanged(idKeypadOverlayLoader.item.objectName)

                cppUIBase.qmlLog("idKeypadOverlayLoader onStatusChanged, component: ")       
          }
            else
            {
                if(idKeypadOverlayLoader.status === Loader.Null && idKeypadOverlayLoader.source == "")
                {
                    cppIntrospectionAdaptor.invSetScreenChanged("PhoneSetup.qml")
                }
            }
        }
    }

    /*
     * Method to load VR overlay
     */
    function loadVROverlay(component)
    {
        _vrOverlaySourceComponent = undefined
        cppUIBase.qmlLog("Load VR overlay, component: " + component)
        _vrOverlaySourceComponent = component
    }

    /*
     * Method to unload VR overlay
     */
    function unloadVROverlay() {
        cppUIBase.qmlLog("Unload VR overlay, component: " + _vrOverlaySourceComponent)
        _vrOverlaySourceComponent = undefined
    }

    /*
     * Loader to load the VR overlay
     */
    Loader{
        id:idVROverlayLoader
        anchors.fill: parent
        sourceComponent: _vrOverlaySourceComponent
    }

    /*
     * Function is called from the CPopupManager to load a particular QML component
     */
    function loadPopup(component, popupScreenName) {
        _popupSourceComponent = null
        _popupScreenName = popupScreenName
        cppUIBase.qmlLog("Popup loadComponent, component: " + component)
        _popupSourceComponent = component
    }
    /*
     * Function is called from the CPopupManager to unload a particular QML component
     */
    function unloadPopup() {
        cppUIBase.qmlLog("Popup unLoad")
        idPopupLoader.item.close()
        idPopupLoader.item.objectName = ""
        cppIntrospectionAdaptor.invSetPopupChanged("No Popup")

        // _popupSourceComponent = null; // FixMe: [NK] [POPUP] temp code
    }
    /*
     * Loader to load the qml files in the main area
     */
    Loader {
        id: idPopupLoader
        objectName: "PopupLoader"
        anchors.fill: parent
        sourceComponent: _popupSourceComponent

        onSourceComponentChanged: {
            if (_popupSourceComponent !== null)
                idPopupLoader.item.open()

        }

        onStatusChanged: {
            if (idPopupLoader.status === Loader.Ready) {

                //Set objectName
                idPopupLoader.item.objectName = _popupScreenName
                cppUIBase.qmlLog("UI idPopupLoader")
                cppIntrospectionAdaptor.invSetPopupChanged(idPopupLoader.item.objectName)
            }
        }
    }
}
