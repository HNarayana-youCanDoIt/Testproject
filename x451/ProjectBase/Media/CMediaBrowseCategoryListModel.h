/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CMediaBrowseCategoryListModel.h
* @ingroup      HMIComponent
* @author       Rahul Madan
* @brief        This file contains CMediaBrowseCategoryListModel class that shall implement the
*               Media Browse Category list data model that shall be used to update all the Category screens in Media Browse
*/
#ifndef CMEDIABROWSECATEGORYLISTMODEL_H
#define CMEDIABROWSECATEGORYLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "CMediaData.h"
#include "CMediaEnum.h"

/**
 * @class CMediaBrowseCategoryListModel
 * @brief This class implements the Media Browse Category list data model
 *        that shall be used to update all the Category screens in Media Browse
 */
class CMediaBrowseCategoryListModel : public QAbstractListModel
{
    Q_OBJECT

private:

    /** *************************************************************
     * @category  ENUMS
     **************************************************************/
    /*!
     * @enum    EMediaBrowseCategoryListRoles
     * @brief   This enum shall hold the values that shall be used by Media Browse Category
     *          qml screen to update the data in the view.
     */
    enum EMediaBrowseCategoryListRoles
    {
        ITEM_IMAGE_ROLE = Qt::UserRole + 1,
        ITEM_NAME_ROLE,
        ITEM_ID_ROLE,
        ITEM_TYPE_ROLE,
        ITEM_ACTIVE_ROLE,
        ITEM_FSCONTENTTYPE_ROLE,
    };
public:
    CMediaBrowseCategoryListModel(QObject* pParent = nullptr);
    ~CMediaBrowseCategoryListModel();

    /** *************************************************************
     * @category  OVERRIDEN METHODS of QAbstractListModel class
     **************************************************************/
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int,QByteArray> roleNames() const override;


    /** *************************************************************
     * @category  Internal Methods
     **************************************************************/

    /*!
     * @brief   Method to clear the media browse list.
     * @param   void.
     * @return  void.
     */
    void removeRows();

    /*!
     * @brief   Method to append the browse category items into the list.
     * @param   objBrowseCategoryData - Browse Category Item Data
     * @return  void.
     */
    void insertRows(const SBrowseCategoryData &objBrowseCategoryData);

    /**
     * @brief Method to update the list item at iIndex
     * @param iIndex - Index of the item to be updated
     * @param objBrowseCategoryData - Browse Category Item data
     * @return void
     */
    void updateBrowseList(int iIndex,const SBrowseCategoryData &objBrowseCategoryData);

    /**
     * @brief Method to get SBrowseCategoryData object at a particular index
     * @param iIndex - Index for list item
     * @return SBrowseCategoryData - Struct object at index iIndex
     */
    SBrowseCategoryData getBrowseDataFromIndex(int iIndex);

private:

    /** *************************************************************
     * @category   PROPERTIES
     **************************************************************/
    /**
     * @list m_listBrowseCategory
     * @brief List to hold the Broswe Category Item Data
     */
    QList<SBrowseCategoryData> m_listBrowseCategory;
};

#endif // CMEDIABROWSECATEGORYLISTMODEL_H
