import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.setupenums 1.0
import com.harman.qml.thememanager 1.0
import "../Common/"

BaseUI {
    id: idAudioPresets

    //This property holds the current audio setup screen information
    property int prCurrentAudioSettingsScreen: cppSetupAdaptor.eCurrentAudioSettingsScreen

    // Fuction return the path of QML to be loaded in loader
    function getLoaderSource()
    {
        switch(prCurrentAudioSettingsScreen)
        {
        case SetupEnums.AUDIOSETUP_BMT_AUDIO_PRESET_SCREEN:
            return "qrc:/QML/Setup/AudioPresets.qml"

        case SetupEnums.AUDIOSETUP_BALANCE_FADER_SCREEN:
            return "qrc:/QML/Setup/BalanceFader.qml"

        default:
            return ""
        }
    }

    Loader {
        id: idAudioSettingsLoader
        anchors.fill: parent
        source: ""
    }

    onPrCurrentAudioSettingsScreenChanged:
    {
        cppSetupApp.qmlLog("prCurrentAudioSettingsScreen: " + prCurrentAudioSettingsScreen)
        idAudioSettingsLoader.source = getLoaderSource()
    }

    HBTabBar{
        id:idAudioSettingsTabView

        anchors{
            top: parent.top
            topMargin: 54
            left: parent.left
            leftMargin: 166
        }
        prTabViewModel:cppSetupAdaptor.audioSettingsModel
        prCurrIndex: 0
        prTabBarPathView.pathItemCount: 4
        prTabBarPathView.preferredHighlightBegin: 0.25
        prTabBarPathView.preferredHighlightEnd: 0.25
        prTabBarPathView.path:
        Path{
            id: idTwoItemsPath
            startX: -40; startY: 0

            PathLine { x: idAudioSettingsTabView.prTabBarPathView.width + 250 ; y: 0}
        }
        onSigTabViewCurrentIndexChanged: {
                cppSetupApp.raiseSMEvent("AudioSetup", index)
        }
    }

    Component.onCompleted: {
        idAudioSettingsLoader.source = getLoaderSource()
    }
}
