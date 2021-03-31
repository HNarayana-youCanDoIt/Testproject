/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CFontType.h
* @ingroup      HMI Framework
* @author       Mohit Rajani
* CFontType, Font class for creating/storing details of Tata specific fonts for X0
*/

#ifndef CFONTTYPE_H
#define CFONTTYPE_H

#include <QObject>
#include "CThemeManagerEnums.h"

//FixMe these values are for X451, but needs to be modified to be handled by theme change events.
#define FontColorT45_C1 "#2b74c3"  //highlight color
#define FontColorT35_C2 "#2b74c3" //highlight color
#define FontColorT35_C3 "#cacaca"
#define FontColorT24_C2 "#ffffff"
#define FontColorT24_C3 "#2b74c3"  //highlight color
#define FontColor_Disabled "#b7b7b7" //"#6b6b6b"

// these values are for the font highlight color for each theme type in X451
const QString FontColorHighlight_1 = "#2b74c3";
const QString FontColorHighlight_2 = "#c32b2b";
//const QString FontColorHighlight_3 = "#2bc393"; As per TML, green colour theme should be removed
const QString FontColorHighlight_4 = "#f7913d";
const QString FontColorHighlight_5 = "#ac245e";

const QString FontColorWhite = "#ffffff";
const QString FontColorAmber = "#e68436";

/**
 * @brief CFontType, Font class for creating/storing details of Tata specific fonts for X451
 *
 */
class CFontType : public QObject
{
    Q_OBJECT

    /** Provides the font family name  */
    Q_PROPERTY(QString fontFamily READ fontFamily CONSTANT)

    /** Provides the font pixel size  */
    Q_PROPERTY(int fontPixelSize READ fontPixelSize CONSTANT)

    /** Provides the text color  */
    Q_PROPERTY(QString color READ color CONSTANT)

public:
    /**
     * @brief CFontType, contructor with default values for font type T20 and color C3
     * @param family - the font family to be used
     * @param fontPixelSize - the overall pixel size of the text
     * @param fontColor
     * @param isHighlightColor - font used is highlight color
     */
    CFontType(QString strFamily = "Noto Sans", int iFontPixelSize = 35, QString strFontColor = "#ffffff", bool bisHightlightColor = false);

    // getter functions for the various private members
    /**
     * @brief getter for the fontFamily
     * @return QString which is the fontFamily name
     */
    QString fontFamily(){ return m_sFamily; }

    /**
     * @brief getter for the fontPixelSize
     * @return int which is the pixel size set for the font
     */
    int fontPixelSize(){ return m_iFontPixelSize; }

    /**
     * @brief setColor set the color for the font type
     * @param color string which stored the hex value
     * @return void
     */
    void setColor(QString color) {m_sFontColor = color;}

    /**
     * @brief getter for text color
     * @return QString text color set for the custom font
     */
    QString color() { return m_sFontColor; }

    /**
     * @brief isHighlightColor - return the current state support for font highlight with color 
	 * @param void
     * @return true if highlight color is supported else false
     */
    bool isHighlightColor() {return m_bIsHighlightColor;}

private:
    /** Stores the font family name  */
    QString m_sFamily;

    /** Stores the font pixel size  */
    int m_iFontPixelSize;

    /** Stores the text color  */
    QString m_sFontColor;

    /** stores info whether the font used highlight color */
    bool m_bIsHighlightColor;

};

#endif // CFONTTYPE_H
