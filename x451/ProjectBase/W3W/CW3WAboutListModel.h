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
 * @brief         This file contains CW3WAboutListModel class that shall implement the
 * W3W About list data model that shall be used to update the W3W About screen.
 */

#ifndef CW3WABOUTLISTMODEL_H
#define CW3WABOUTLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "CW3WData.h"

/*!
 * @class CW3WAboutListModel
 * @brief This class shall implement the W3W About list data model that shall be used to update
 * the W3W About qml screen.
 */
class CW3WAboutListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    /************************************************************************//**
     * @category    ENUMS
     ************************************************************************/

    /*!
     * @enum    EW3WAboutListRoles
     * @brief   This enum shall hold the values that shall be used by W3W About qml screen
     * to update the data in the view.
     */
    enum EW3WAboutListRoles
    {
        /* This role holds the Item Main text */
        W3W_ABOUT_ITEM_TEXT_ROLE = Qt::UserRole + 1,
        /* This role holds the Item Enable/Disable state */
        W3W_ABOUT_ITEM_ENABLED_ROLE,
        /* This role holds the Item type of the list item */
        W3W_ABOUT_ITEM_TYPE_ROLE,
        /**
         * This Role is used to identify the Item which is selected by user and which Item needs to expand on
         * drop-down click.
         */
        W3W_ABOUT_ITEM_ID_ROLE,
    };
public:
    /**
    * @brief	CW3WAboutListModel::CW3WAboutListModel constructor for W3W About model.
    * @param	QObject. The pointer of parent class.
    * @return	NA.
    **/
    CW3WAboutListModel(QObject* pParent = nullptr);

    /**
    * @brief	CW3WAboutListModel::CW3WAboutListModel destructor for W3W About model.
    * @param	NA.
    * @return	NA.
    **/
    ~CW3WAboutListModel();

    /************************************************************************//**
     * @category    OVERRIDEN METHODS of QAbstractListModel class
     ************************************************************************/

    /**
    * @brief	CW3WAboutListModel::rowCount function inherited from QAbstractListModel,
    *           Used to get row count.
    * @param	QModelIndex : The index is used to locate an item in the model.
    * @return	int : holds row count.
    **/
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

    /**
    * @brief	CW3WAboutListModel::data function inherited from QAbstractListModel,
    *           Used to get data linked to given role and present at given index.
    * @param	(index)QModelIndex : The index is used to locate an item in the model.
    *           (role)int : holds the role name of data to be extract from QModelIndex item.
    * @return	QVariant : data stored under the given role for the item referred to by the index.
    **/
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

    /**
    * @brief	CW3WAboutListModel::roleNames function inherited from QAbstractListModel,
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
    * @brief	CW3WAboutListModel::initW3WAboutModel function initializes the W3W About Model
    * @param	void.
    * @return	void.
    **/
    void initW3WAboutModel();

    /**
    * @brief	CW3WAboutListModel::initW3WAboutDescriptionModel function initializes the W3W Description Model
    * @param	void.
    * @return	void.
    **/
    void initW3WAboutDescriptionModel();

    /**
     * @brief expandAboutItem: Expands the About Dropdown.
     * @param iItemIndex: W3W About item index to be expanded.
     * @return void.
     */
    Q_INVOKABLE void expandAboutItem(int iItemIndex);

    /**
     * @brief collapseAboutItem: Collapse the About Dropdown.
     * @param void.
     * @return void.
     */
    Q_INVOKABLE void collapseAboutItem();

    /**
    * @brief	isItemEnabled: Method to get whether the W3W About item is enabld or not.
    * @param	eItemName: W3W About item index.
    * @return   TRUE if the item is enabled, FALSE otherwise.
    **/
    bool isItemEnabled(CW3WEnum::EW3WAboutItems eItemIndex);

private:
    /******************************************************//**
     * @category PROPERTIES
     *******************************************************/

    /**
    * @brief List to hold the information of each item in W3W About screen.
    */
    QList<CW3WData::SW3WSetupData>    m_listW3WAbout;

    /**
    * @brief List to hold the information of each item for About Description options.
    */
    QList<CW3WData::SW3WSetupData>      m_listW3WAboutDescription;

    /**
    * @brief Integer variable which holds the value of the expanded About item index.
    */
    int m_iExpandedItemIndex;
};

#endif // CW3WABOUTLISTMODEL_H
