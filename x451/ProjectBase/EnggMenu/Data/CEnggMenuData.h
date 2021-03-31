/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CEnggDataDebugLogs.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande, Rajat Gupta
 * CEnggMenuData, Data file which contains diff types of data used in a Model.
**/

#ifndef CENGGMENUDATA_H
#define CENGGMENUDATA_H
#include <QString>
#include <logging.h>
#include <CEnggMenuEnum.h>


class CEnggMenuData
{
public:
    CEnggMenuData()
    {

    }
    CEnggMenuData(int iListItemId ,const QString &strListItemMainText="",CEnggMenuEnum::EEnggMenuItemType iListItemType = CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_NONE ,const QString &strListItemSubText = "", bool bListItemStatus = false, bool bListItemEnableStatus = true):
        m_iEnggMenuItemId(iListItemId),
        m_strEnggMenuItemMainText(strListItemMainText),
        m_eEnggMenuItemType(iListItemType),
        m_bEnggMenuItemStatus(bListItemStatus),
        m_bEnggMenuItemEnableStatus(bListItemEnableStatus),
        m_strEnggMenuItemSubTitle(strListItemSubText)
    {

        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    }


public:
    /* Each item of the list will have unique id according to different screens which will be stored in this var */
    int m_iEnggMenuItemId;
    /* List item Title gets stored in this var */
    QString m_strEnggMenuItemMainText;
    /** m_eEnggMenuItemType variable is used to identify the type of delegate present in a
     *  list like label with checkbox or label with label etc
    **/
    CEnggMenuEnum::EEnggMenuItemType m_eEnggMenuItemType;

    /*List Item Checkbox status will be stored in this var*/
    bool m_bEnggMenuItemStatus;

    /*List Item Enable status will be stored in this var*/
    bool m_bEnggMenuItemEnableStatus;

    /*List Item Value will be stored in this var*/
    QString m_strEnggMenuItemSubTitle;
};

#endif // CENGGMENUDATA_H
