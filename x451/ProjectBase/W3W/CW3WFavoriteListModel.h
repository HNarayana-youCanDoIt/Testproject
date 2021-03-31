/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CW3WFavoriteListModel.h
 * @ingroup       HMIComponent
 * @author        Nishant Khandagale
 * @brief         This file contains CW3WFavoriteListModel class that shall implement the
 * W3W Favorite list data model that shall be used to update the W3W Favorite screen.
 */

#ifndef CW3WFAVORITELISTMODEL_H
#define CW3WFAVORITELISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "CW3WData.h"

/*!
 * @class CW3WFavoriteListModel
 * @brief This class shall implement the W3W Favorite list data model that shall be used to update
 * the W3W Favorite qml screen.
 */
class CW3WFavoriteListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    /************************************************************************//**
     * @category    ENUMS
     ************************************************************************/

    /*!
     * @enum    EW3WFavoriteListRoles
     * @brief   This enum shall hold the values that shall be used by W3W Favorite qml screen
     * to update the data in the view.
     */
    enum EW3WFavoriteListRoles
    {
        /* This role holds the Item Main text */
        W3W_FAVORITE_ITEM_ADDRESS_ROLE = Qt::UserRole + 1,
        /* This role holds the Item Enable/Disable state */
        W3W_FAVORITE_ITEM_LABEL_ROLE,
        /* This role holds the Item type of the list item */
        W3W_FAVORITE_ITEM_TYPE_ROLE,
        /* This role holds the Item id of the list item */
        W3W_FAVORITE_ITEM_ID_ROLE,
    };
public:
    /**
    * @brief	CW3WFavoriteListModel::CW3WFavoriteListModel constructor for W3W Favorite model.
    * @param	QObject. The pointer of parent class.
    * @return	NA.
    **/
    CW3WFavoriteListModel(QObject* pParent = nullptr);

    /**
    * @brief	CW3WFavoriteListModel::CW3WFavoriteListModel destructor for W3W Favorite model.
    * @param	NA.
    * @return	NA.
    **/
    ~CW3WFavoriteListModel();

    /**
    * @brief	getFavoriteData function returns the W3W Address item from
    *           Favorite Addresses list at specified index
    * @param	itemId: itemId of the required favorite w3w address.
    * @return	CW3WData::SW3WAddressData: W3W Address item structure at specified index.
    **/
    CW3WData::SW3WAddressData getFavoriteData(int itemId);

    /**
    * @brief	getFavoriteDataAtIndex function returns the W3W Address item from
    *           Favorite Addresses list at specified index
    * @param	index: The index for which value has to be get.
    * @return	CW3WData::SW3WAddressData: W3W Address item structure at specified index.
    **/
    CW3WData::SW3WAddressData getFavoriteDataAtIndex(int index);

    /**
    * @brief	CW3WFavoriteListModel::updateW3WFavoriteModelAtIndex function updates the W3W Favorite Model
    *           at specified index with favoriteData.
    * @param	row : Index at which favorite list model has to be updated.
    * @param	w3wAddressDataItem favorite w3w address data.
    * @return	void.
    **/
    void updateW3WFavoriteModelAtIndex(int row, const CW3WData::SW3WAddressData& w3wAddressDataItem);

    /************************************************************************//**
     * @category    OVERRIDEN METHODS of QAbstractListModel class
     ************************************************************************/

    /*!
     * @brief   appendRow: Method to append the w3w Address Data item in the favorites list.
     * @param   w3wAddressDataItem - Favorite w3w address data item.
     * @return  void.
     */
    void appendRow(const CW3WData::SW3WAddressData& w3wAddressDataItem);

    /*!
     * @brief   removeRow: Method to delete single entry from list.
     * @param   row: element index to delete.
     * @return  void.
     */
    void removeRow(int row);

    /**
    * @brief	CW3WFavoriteListModel::rowCount function inherited from QAbstractListModel,
    *           Used to get row count.
    * @param	QModelIndex : The index is used to locate an item in the model.
    * @return	int : holds row count.
    **/
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

    /**
    * @brief	CW3WFavoriteListModel::data function inherited from QAbstractListModel,
    *           Used to get data linked to given role and present at given index.
    * @param	(index)QModelIndex : The index is used to locate an item in the model.
    *           (role)int : holds the role name of data to be extract from QModelIndex item.
    * @return	QVariant : data stored under the given role for the item referred to by the index.
    **/
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

    /**
    * @brief	CW3WFavoriteListModel::roleNames function inherited from QAbstractListModel,
    *           Used to get role names
    * @param	void.
    * @return	QHash<int, QByteArray> : holds model's role names
    **/
    QHash<int, QByteArray> roleNames() const override;

    /**
     * @brief setData: Sets the role data for the item at index to value
     * @param index: The index for which value to be set
     * @param value: The value to be set for the role
     * @param role: The role data to be modified
     * @return: Returns true if successful; otherwise returns false.
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

private:
    /******************************************************//**
     * @category PROPERTIES
     *******************************************************/

    /**
    * @brief List to hold the information of each item in W3W Favorite screen.
    */
    QList<CW3WData::SW3WAddressData>    m_listW3WFavorite;
};

#endif // CW3WFAVORITELISTMODEL_H
