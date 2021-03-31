/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CW3WRecentListModel.h
 * @ingroup       HMIComponent
 * @author        Nishant Khandagale
 * @brief         This file contains CW3WRecentListModel class that shall implement the
 * W3W Recent list data model that shall be used to update the W3W Recent screen.
 */

#ifndef CW3WRECENTLISTMODEL_H
#define CW3WRECENTLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "CW3WData.h"

/*!
 * @class CW3WRecentListModel
 * @brief This class shall implement the W3W Recent list data model that shall be used to update
 * the W3W Recent qml screen.
 */
class CW3WRecentListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    /************************************************************************//**
     * @category    ENUMS
     ************************************************************************/

    /*!
     * @enum    EW3WRecentListRoles
     * @brief   This enum shall hold the values that shall be used by W3W Recent qml screen
     * to update the data in the view.
     */
    enum EW3WRecentListRoles
    {
        /* This role holds the Item Main text */
        W3W_RECENT_ITEM_ADDRESS_ROLE = Qt::UserRole + 1,
        /* This role holds the Item Enable/Disable state */
        W3W_RECENT_ITEM_LABEL_ROLE,
        /* This role holds the Item type of the list item */
        W3W_RECENT_ITEM_TYPE_ROLE,
        /* This role holds the Item id of the list item */
        W3W_RECENT_ITEM_ID_ROLE,
    };
public:
    /**
    * @brief	CW3WRecentListModel::CW3WRecentListModel constructor for W3W Recent model.
    * @param	QObject. The pointer of parent class.
    * @return	NA.
    **/
    CW3WRecentListModel(QObject* pParent = nullptr);

    /**
    * @brief	CW3WRecentListModel::CW3WRecentListModel destructor for W3W Recent model.
    * @param	NA.
    * @return	NA.
    **/
    ~CW3WRecentListModel();

    /**
    * @brief	CW3WRecentListModel::updateW3WRecentModel function initializes the W3W Recent Model
    * @param	recentListData recent list data.
    * @return	void.
    **/
    void updateW3WRecentModel(QList<CW3WData::SW3WAddressData> recentListData);

    /**
    * @brief	getRecentData function returns the W3W Address item from
    *           Recent Addresses list at specified index
    * @param	itemId: The id of the required recent w3w address.
    * @return	CW3WData::SW3WAddressData: W3W Address item structure at specified index.
    **/
    CW3WData::SW3WAddressData getRecentData(int itemId);

    /**
    * @brief	getRecentDataAtIndex function returns the W3W Address item from
    *           Recent Addresses list at specified index
    * @param	index: The index for which value has to be get.
    * @return	CW3WData::SW3WAddressData: W3W Address item structure at specified index.
    **/
    CW3WData::SW3WAddressData getRecentDataAtIndex(int index);

    /**
    * @brief	CW3WRecentListModel::updateW3WRecentModelAtIndex function updates the W3W Recent Model
    *           at specified index with recentData.
    * @param	row : Index at which recent list model has to be updated.
    * @param	w3wAddressDataItem recent w3w address data.
    * @return	void.
    **/
    void updateW3WRecentModelAtIndex(int row, const CW3WData::SW3WAddressData& w3wAddressDataItem);

    /************************************************************************//**
     * @category    OVERRIDEN METHODS of QAbstractListModel class
     ************************************************************************/

    /*!
    * @brief   appendRow: Method to append the w3w Address Data item in the recent list.
    * @param   w3wAddressDataItem - Recent w3w address data item.
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
    * @brief	CW3WRecentListModel::rowCount function inherited from QAbstractListModel,
    *           Used to get row count.
    * @param	QModelIndex : The index is used to locate an item in the model.
    * @return	int : holds row count.
    **/
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

    /**
    * @brief	CW3WRecentListModel::data function inherited from QAbstractListModel,
    *           Used to get data linked to given role and present at given index.
    * @param	(index)QModelIndex : The index is used to locate an item in the model.
    *           (role)int : holds the role name of data to be extract from QModelIndex item.
    * @return	QVariant : data stored under the given role for the item referred to by the index.
    **/
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

    /**
    * @brief	CW3WRecentListModel::roleNames function inherited from QAbstractListModel,
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
    * @brief List to hold the information of each item in W3W Recent screen.
    */
    QList<CW3WData::SW3WAddressData>    m_listW3WRecent;
};

#endif // CW3WRECENTLISTMODEL_H
