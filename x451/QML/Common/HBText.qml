import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0

Text {
    id: _idText

    // The font type to be applied
    property int fontType: ThemeMgr.FONTTYPE_T35_C3

    // Holds the previous set font
    property int _prevFontType: fontType

    // get the custom font that is to be applied to the Text
    property CFontType customFont: cppThemeMgr.getFontType(fontType)

    function applyFont() {
        if (("undefined" !== customFont) && (null !== customFont)) {
            font.family = customFont.fontFamily
            font.pixelSize = customFont.fontPixelSize
            color = customFont.color
        }
    }

    //Todo: Remove once font pixel height part is aligned with TATA. For debugging purpose
    //    FontMetrics {
    //        id: idFontMetrics
    //        font.pixelSize: customFont.fontPixelSize
    //    }
    onFontTypeChanged: {
        if (_prevFontType !== fontType) {
            customFont = cppThemeMgr.getFontType(fontType)
            applyFont()
        }
    }

    Connections {
        target: cppThemeMgr
        onSigCurrentThemeTypeChanged: {
            customFont = cppThemeMgr.getFontType(fontType)
            applyFont()
        }
    }

    elide: Text.ElideRight
    verticalAlignment: Text.AlignVCenter

    Component.onCompleted: {
        applyFont()
        //Todo: Remove once font pixel height part is aligned with TATA. For debugging purpose
        //cppUIBase.qmlLog("FontMetrics: family: " + idFontMetrics.font.family)
        //cppUIBase.qmlLog("FontMetrics: font.pixelSize: " + idFontMetrics.font.pixelSize + ", height:" + idFontMetrics.height
        //                 + ",ascent: " + idFontMetrics.ascent + ",descent: " + idFontMetrics.descent)
    }
}
    /**
  How to use HBText
  1. Import below path
  import com.harman.qml.thememanager 1.0

  2. In place of Label/Text use HBText

  3. Set property fontType: ThemeMgr.FONTTYPE_T35_C3 based on the requirement.

  4. Do not set directly the font properties. The color for the text is internally set

  For handling Internationaliztion
  5. Along with providing the static text within qsTr we also need to ass cppThemeMgr.languageChanged
  E.g.

  HBText {
    fontType: ThemeMgr.FONTTYPE_T35_C3
    text: qsTr(LBL_XXX_ID) + cppThemeMgr.languageChanged
  }



  */
