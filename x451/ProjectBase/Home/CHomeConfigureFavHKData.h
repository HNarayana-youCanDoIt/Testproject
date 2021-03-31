/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
* @file          CHomeConfigureFavHKData.h
* @ingroup       HMIComponent
* @author        Rahul Balyan
* CHomeConfigureFavHKData,  Data structure for CHomeConfigureFavHKModel
**/

#ifndef CHOMECONFIGUREFAVHKDATA_H
#define CHOMECONFIGUREFAVHKDATA_H

#include <QObject>
#include "CHardKeyEnum.h"
#include "CHomeEnum.h"

/**
 * @brief The SConfigureFavHKData structure
 * This structure is template to QList in CHomeConfigureFavHKModel.
**/
struct SConfigureFavHKData
{
    SConfigureFavHKData()
    {
        m_eFavHKId = CHardKeyEnum::FAV_HK;
        m_eFavHKShortcutId = CHomeEnum::SHORTCUT_BLANK_ID;
    }
    SConfigureFavHKData(CHardKeyEnum::EFavKeyCode eFavHKId, CHomeEnum::EHomeShortcutsUID eFavHKShortcutId)
    {
        m_eFavHKId = eFavHKId;
        m_eFavHKShortcutId = eFavHKShortcutId;
    }

    /** Variable holds the favHK ID */
    CHardKeyEnum::EFavKeyCode m_eFavHKId;

    /** Variable holds home shortcutID for the respective favHK ID */
    CHomeEnum::EHomeShortcutsUID m_eFavHKShortcutId;
};

#endif // CHOMECONFIGUREFAVHKDATA_H
