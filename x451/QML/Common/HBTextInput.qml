import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0

TextInput {
    id: idTextInput

    // The font type to be applied
    property int prFontType: ThemeMgr.FONTTYPE_T35_C3

    // Holds the previous set font
    property int prPrevFontType: prFontType

    // get the custom font that is to be applied to the Text
    property CFontType prCustomFont: cppThemeMgr.getFontType(prFontType)

    function applyFont() {
        if (("undefined" !== prCustomFont) && (null !== prCustomFont)) {
            font.family = prCustomFont.fontFamily
            font.pixelSize = prCustomFont.fontPixelSize
            color = prCustomFont.color
        }
    }

    onPrFontTypeChanged: {
        if (prPrevFontType !== prFontType) {
            prCustomFont = cppThemeMgr.getFontType(prFontType)
            applyFont()
        }
    }

    Component.onCompleted: {
        applyFont()
    }
}
/**
  How to use HBTextInput
  1. Import below path
  import com.harman.qml.thememanager 1.0

  2. In place of TextInput use HBTextInput

  3. Set property prFontType: ThemeMgr.FONTTYPE_T35_C3 based on the requirement.

  4. Do not set directly the font properties. The color for the text is internally set

  HBTextInput {
    prFontType: ThemeMgr.FONTTYPE_T35_C3
  }



  */
