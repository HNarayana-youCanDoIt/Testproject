/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CVRData.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CVRData class that contain all the structure data that
 * shall be used by VR UI data models.
 */

#ifndef CVRDATA_H
#define CVRDATA_H

#include <unordered_map>
#include <QStringList>
#include "CVREnum.h"

using namespace std;

/*!
 * @struct  SVRCommandCategory
 * @brief   This structure shall hold the all information of individual help command category
 */
struct SVRCommandCategory
{
    SVRCommandCategory()
    {
        m_listCommandText.clear();
        m_listCommandPrompt.clear();
    }

    //! List to hold text imformation of a particular help command category
    QStringList     m_listCommandText;
    //! List to hold prompt imformation of a particular help command category
    QStringList     m_listCommandPrompt;

    void clear()
    {
        m_listCommandText.clear();
        m_listCommandPrompt.clear();
    }
};

/*!
 * @struct  SVRHelpCommands
 * @brief   This structure shall hold the information of VR help commands
 */
struct SVRHelpCommands
{
    SVRHelpCommands()
    {
        m_mapVRHelpCommands.clear();
    }
    //! Unordered map of VR help command categories information
    unordered_map<CVREnum::EVRHelpCategoryType, SVRCommandCategory, std::hash<int>> m_mapVRHelpCommands;

    void clear()
    {
        m_mapVRHelpCommands.clear();
    }
};

#endif // CVRDATA_H
