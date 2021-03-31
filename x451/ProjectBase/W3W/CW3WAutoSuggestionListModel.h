/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CW3WAboutListModel.h
 * @ingroup       HMIComponent
 * @author        Nishant Khandagale
 * @brief         This file contains CW3WAutoSuggestionListModel class that shall implement the
 * W3W Auto Suggestion list data model that shall be used to update the W3W Address Suggestion screen.
 */

#ifndef CW3WAUTOSUGGESTIONLISTMODEL_H
#define CW3WAUTOSUGGESTIONLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "CW3WData.h"

/*!
 * @class CW3WAutoSuggestionListModel
 * @brief This class shall implement the W3W Auto Suggestion list data model that shall be used to update
 * the W3W Address Suggestion qml screen.
 */
class CW3WAutoSuggestionListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    /************************************************************************//**
     * @category    ENUMS
     ************************************************************************/

    /*!
     * @enum    EW3WAutoSuggestionListRoles
     * @brief   This enum shall hold the values that shall be used by W3W Auto Suggestion List qml
     * to update the data in the view.
     */
    enum EW3WAutoSuggestionListRoles
    {
        /* This role holds the Auto Suggestion Address text */
        W3W_SUGGESTION_ITEM_ADDRESS_ROLE = Qt::UserRole + 1,
        /* This role holds the Auto Suggestion Nearest Place text */
        W3W_SUGGESTION_ITEM_NEAREST_PLACE_ROLE,
        /* This role holds the Auto Suggestion Country Code text */
        W3W_SUGGESTION_ITEM_COUNTRY_CODE_ROLE,
        /* This role holds the Auto Suggestion list type */
        W3W_SUGGESTION_ITEM_TYPE_ROLE,
        /* This role holds the Auto Suggestion list id */
        W3W_SUGGESTION_ITEM_ID_ROLE,
    };
public:
    /**
    * @brief	CW3WAutoSuggestionListModel::CW3WAutoSuggestionListModel constructor for W3W Auto Suggestion model.
    * @param	QObject. The pointer of parent class.
    * @return	NA.
    **/
    CW3WAutoSuggestionListModel(QObject* pParent = nullptr);

    /**
    * @brief	CW3WAutoSuggestionListModel::CW3WAutoSuggestionListModel destructor for W3W Auto Suggestion model.
    * @param	NA.
    * @return	NA.
    **/
    ~CW3WAutoSuggestionListModel();

    /************************************************************************//**
     * @category    OVERRIDEN METHODS of QAbstractListModel class
     ************************************************************************/

    /**
    * @brief	CW3WAutoSuggestionListModel::rowCount function inherited from QAbstractListModel,
    *           Used to get row count.
    * @param	QModelIndex : The index is used to locate an item in the model.
    * @return	int : holds row count.
    **/
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

    /**
    * @brief	CW3WAutoSuggestionListModel::data function inherited from QAbstractListModel,
    *           Used to get data linked to given role and present at given index.
    * @param	(index)QModelIndex : The index is used to locate an item in the model.
    *           (role)int : holds the role name of data to be extract from QModelIndex item.
    * @return	QVariant : data stored under the given role for the item referred to by the index.
    **/
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

    /**
    * @brief	CW3WAutoSuggestionListModel::roleNames function inherited from QAbstractListModel,
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

    /**
    * @brief	CW3WAutoSuggestionListModel::updateW3WAutoSuggestionList function updates the W3W Auto Suggestion list Model
    * @param	autoSuggestionData auto suggestion data
    * @return	void.
    **/
    void updateW3WAutoSuggestionList(QList<CW3WData::SW3WAddressData> autoSuggestionData);

    /**
    * @brief	CW3WAutoSuggestionListModel::getAutoSuggestionData function returns the W3W Auto Suggestion list item
    *           having the specified itemID
    * @param	itemId: itemId of the required w3w address.
    * @return	CW3WData::SW3WAddressData: Auto Suggestion structure variable at specified index.
    **/
    CW3WData::SW3WAddressData getAutoSuggestionData(int itemId);

private:
    /******************************************************//**
     * @category PROPERTIES
     *******************************************************/

    /**
    * @brief List to hold the information of each item for W3W Auto Suggestion data.
    */
    QList<CW3WData::SW3WAddressData>    m_listW3WAutoSuggestion;
};

#endif // CW3WAUTOSUGGESTIONLISTMODEL_H
