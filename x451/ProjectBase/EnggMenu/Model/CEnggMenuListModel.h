/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CEnggMenuListModel.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande, Rajat Gupta
 * CEnggMenuListModel, EnggMode list model class header file.
**/

#ifndef CENGGMENULISTMODEL_H
#define CENGGMENULISTMODEL_H
#include <QAbstractListModel>
#include <QList>
#include "Data/CEnggMenuData.h"

class CEnggMenuListModel: public QAbstractListModel
{
    Q_OBJECT

public:

    /**
     * @brief CEnggMenuListModel: constructor for class CEnggMenuListModel
     * @param NA.
     * @return NA.
     */
    CEnggMenuListModel(QObject *parent = nullptr);
    //________________________________________________________________________________________________

    /**
     * @brief CEnggMenuListModel: distructor for class CEnggMenuListModel
     * @param NA.
     * @return NA.
     */
    ~CEnggMenuListModel();
    //________________________________________________________________________________________________

    /**
     * @brief rowCount: When subclassing QAbstractListModel must provide implementation of the rowCount(). This function
     * returns the number if items present in a model.
     * @param parent: When the parent is valid it means that rowCount is returning the number of children of parent.
     * @return Returns the number of rows in the model
     */
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    //________________________________________________________________________________________________

    /**
     * @brief data : When subclassing QAbstractListModel must provide implementation of the data(). This function returns
     * the value of the corresponding role at a given index.
     * @param index: The index whose data to be returned
     * @param iRole: The iRole whose data to be returned
     * @return Returns the data stored under the given iRole for the item referred to by the index.
     */
    QVariant data(const QModelIndex & index, int iRole = Qt::DisplayRole) const;
    //________________________________________________________________________________________________

    /**
     * @brief updateEnggMenuModel :It will update the data for given model item
     * @param int iEnggMenuItemID: The index at which the data has to be changed
     * @param QVariant &value: The value that has to be updated
     * @param int role: The role for which the data has to be changed
     * @return :void.
     */
    void updateEnggMenuModel(int iEnggMenuItemID , const QVariant &value, int iRole);
    //________________________________________________________________________________________________

    /**
     * @brief addItem :It adds the item in Engineering Menu list model. /
     * @param CEnggMenuData &objEnggMenuModelData: the reference of the Data that has to be added in a particular model.
     * @return :void.
     */
    void addItem(const CEnggMenuData &objEnggMenuModelData);
    //________________________________________________________________________________________________

    /**
     * @brief resetList :It resets list model. /
     * @param :void
     * @return :void.
     */
    void resetList();
    //________________________________________________________________________________________________

protected:
    /**
     * @brief roleNames: Defines rolenames that are to be used in qml
     * @param void
     * @return : Returns the model's role names
     */
    QHash<int, QByteArray> roleNames() const;
    //________________________________________________________________________________________________

public:

    /**
     * @enum
     * @brief Roles to get the CEnggMenuListModel data
     */
    enum EEnggMenuDataRoles{
        //this role is for the main text of list item
        ENGG_MENU_ITEM_MAIN_TEXT_ROLE = Qt::UserRole + 1,
        //every list item has its own id that will be used through this role.
        ENGG_MENU_ITEM_ID_ROLE,

        //EnggMenu list contains different components like Text with Checkbox ,text with Text etc.This role will hold the Item type.
        ENGG_MENU_ITEM_TYPE_ROLE,

        //list item components like checkbox or radiobutton status will be taken through this role.
        ENGG_MENU_ITEM_STATUS_ROLE,

        //some list item contains sub text which will be taken thorough this role.
        ENGG_MENU_ITEM_SUB_TEXT_ROLE,

        //list item button enable status will be controlled by this role.
        ENGG_MENU_ITEM_ENABLE_STATUS_ROLE
    };

private:

    /* Screen items list container */
    QList<CEnggMenuData> m_listEnggMenuData;

    /* Screen items list element index, here key is list element id and value is position index in list*/
    QMap<int, int> m_mapEnggMenuDataElementIndex;
    //________________________________________________________________________________________________
};

#endif // CENGGMENULISTMODEL_H
