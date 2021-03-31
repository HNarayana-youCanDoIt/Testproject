import QtQuick 2.7
import "../../Common/Popup"

NoButtonPopup
{
    prPopupText: ( (cppVariantControlAdaptor.eolAndroidAutoEnabled && cppVariantControlAdaptor.eolAppleCarPlayEnabled) ?
                        qsTr("TEXT_W3W_POPUP_AA_CP_NOT_CONNECTED") :
                    cppVariantControlAdaptor.eolAndroidAutoEnabled ?
                        qsTr("TEXT_W3W_POPUP_AA_NOT_CONNECTED") :
                    cppVariantControlAdaptor.eolAppleCarPlayEnabled ?
                        qsTr("TEXT_W3W_POPUP_CP_NOT_CONNECTED") :
                        "" ) + cppThemeMgr.languageChanged
}
