/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CFontType.cpp
* @ingroup      HMI Framework
* @author       Mohit Rajani
* CFontType, Font class for creating Tata specific fonts
*/

#include "CFontType.h"

CFontType::CFontType(QString strFamily, int iFontPixelSize, QString strFontColor, bool bIsHightlightColor)
    : m_sFamily(strFamily),
      m_iFontPixelSize(iFontPixelSize),
      m_sFontColor(strFontColor),
      m_bIsHighlightColor(bIsHightlightColor)
{

}
