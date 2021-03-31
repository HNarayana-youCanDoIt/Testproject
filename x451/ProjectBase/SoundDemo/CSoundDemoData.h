/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2019
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         SSoundDemoData.h
* @ingroup      HMIComponent
* @author       Guru Alingal
* @brief        Data type declarations to be used in sound demo feature.
*/
#ifndef CSOUNDDEMODATA_H
#define CSOUNDDEMODATA_H
#include<QString>

struct SSoundDemoData
{
    /** @brief m_strCaption: Caption to be displayed in the demo list */
    QString m_strCaption            ;
    /** @brief m_iId: A unique id for the list element */
    int     m_iId                   ;
    /** @brief m_iId: Trackid of the song*/
    int     m_iTrackId              ;
    /** @brief m_strImagePath: To store the path of image to be displayed in sound demo list item */
    QString m_strImagePath          ;
    /** @brief m_bActive: To determine if the current item is active */
    bool    m_bActive               ;
    /** @brief m_bEnabled: To determine if the current item is enabled */
    bool    m_bEnabled              ;
    /** @brief m_iMinValue: Minimum value of the progress bar to be displayed in the list item */
    int     m_iMinValue             ;
    /** @brief m_iCurrentValue: Store the current progress of the progress bar in the list item */
    int     m_iCurrentValue         ;
    /** @brief m_iMaxValue: Maximum value of the progress bar to be displayed in the list item */
    int     m_iMaxValue             ;
    /** @brief m_bProgressVisibility: Determines the visibility progress bar. */
    bool    m_bPgbVisibility        ;


    SSoundDemoData()
    {
        m_strCaption            = ""    ;
        m_strImagePath          = ""    ;
        m_iId                   = -1    ;
        m_iTrackId              = -1    ;
        m_bActive               = false ;
        m_bEnabled              = false ;
        m_iMinValue             = 0     ;
        m_iCurrentValue         = 0     ;
        m_iMaxValue             = 0     ;
        m_bPgbVisibility        = false ;
    }

};

#endif // CSOUNDDEMODATA_H
