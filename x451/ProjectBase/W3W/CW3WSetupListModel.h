/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CW3WSetupListModel.h
 * @ingroup       HMIComponent
 * @author        Nishant Khandagale
 * @brief         This file contains CW3WSetupListModel class that shall implement the
 * W3W setup list data model that shall be used to update the W3W setup screen.
 */

#ifndef CW3WSETUPLISTMODEL_H
#define CW3WSETUPLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "CW3WData.h"

/*!
 * @class CW3WSetupListModel
 * @brief This class shall implement the W3W setup list data model that shall be used to update
 * the W3W setup qml screen.
 */
class CW3WSetupListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    /************************************************************************//**
     * @category    ENUMS
     ************************************************************************/

    /*!
     * @enum    EW3WSetupListRoles
     * @brief   This enum shall hold the values that shall be used by W3W setup qml screen
     * to update the data in the view.
     */
    enum EW3WSetupListRoles
    {
        /* This role holds the Item Main text */
        W3W_SETUP_ITEM_TEXT_ROLE = Qt::UserRole + 1,
        /* This role holds the Item Enable/Disable state */
        W3W_SETUP_ITEM_ENABLED_ROLE,
        /* This role holds the Item Checked/Unchecked state */
        W3W_SETUP_ITEM_CHECKED_ROLE,
        /* This role holds the Item type of the list item */
        W3W_SETUP_ITEM_TYPE_ROLE,
        /**
         * This Role is used to identify the Item which is selected by user and which Item needs to expand on
         * drop-down click.
         */
        W3W_SETUP_ITEM_ID_ROLE,
    };
public:
    /**
    * @brief	CW3WSetupListModel::CW3WSetupListModel constructor for W3W setup model.
    * @param	QObject. The pointer of parent class.
    * @return	NA.
    **/
    CW3WSetupListModel(QObject* pParent = nullptr);

    /**
    * @brief	CW3WSetupListModel::CW3WSetupListModel destructor for W3W setup model.
    * @param	NA.
    * @return	NA.
    **/
    ~CW3WSetupListModel();

    /************************************************************************//**
     * @category    OVERRIDEN METHODS of QAbstractListModel class
     ************************************************************************/

    /**
    * @brief	CW3WSetupListModel::rowCount function inherited from QAbstractListModel,
    *           Used to get row count.
    * @param	QModelIndex : The index is used to locate an item in the model.
    * @return	int : holds row count.
    **/
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

    /**
    * @brief	CW3WSetupListModel::data function inherited from QAbstractListModel,
    *           Used to get data linked to given role and present at given index.
    * @param	(index)QModelIndex : The index is used to locate an item in the model.
    *           (role)int : holds the role name of data to be extract from QModelIndex item.
    * @return	QVariant : data stored under the given role for the item referred to by the index.
    **/
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

    /**
    * @brief	CW3WSetupListModel::roleNames function inherited from QAbstractListModel,
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
    * @brief	CW3WSetupListModel::initW3WSetupModel function initializes the W3W Setup Model
    * @param	void.
    * @return	void.
    **/
    void initW3WSetupModel();

    /**
    * @brief	CW3WSetupListModel::initW3WAutoLaunchPermissionModel function initializes the W3W Auto Launch Permission Model
    * @param	void.
    * @return	void.
    **/
    void initW3WAutoLaunchPermissionModel();

    /**
    * @brief	CW3WSetupListModel::initW3WCountryPreferenceModel function initializes the W3W Country Preference Model
    * @param	void.
    * @return	void.
    **/
    void initW3WCountryPreferenceModel();

    /**
     * @brief expandSetupDropDown: Expands the Setup Dropdown item.
     * @param iItemId : ID of the Item to be expanded.
     * @return void.
     */
    Q_INVOKABLE void expandSetupDropDown(int iItemId);

    /**
     * @brief collapseSetupDropDown: Collapse the Setup Dropdown item.
     * @param iItemId : ID of the Item to be collapsed.
     * @return void.
     */
    Q_INVOKABLE void collapseSetupDropDown(int iItemId);

    /**
     * @brief expandAutoLaunchPermission: Expands the Auto Launch Permission Dropdown.
     * @param void.
     * @return void.
     */
    Q_INVOKABLE void expandAutoLaunchPermission();

    /**
     * @brief collapseAutoLaunchPermission: Collapse the Auto Launch Permission Dropdown.
     * @param void.
     * @return void.
     */
    Q_INVOKABLE void collapseAutoLaunchPermission();

    /**
     * @brief expandCountryPreference: Expands the Country Preference Dropdown.
     * @param void.
     * @return void.
     */
    Q_INVOKABLE void expandCountryPreference();

    /**
     * @brief collapseCountryPreference: Collapse the Country Preference Dropdown.
     * @param void.
     * @return void.
     */
    Q_INVOKABLE void collapseCountryPreference();

    /**
    * @brief	CW3WSetupListModel::updateAutoLaunchPermissionList function updates the Auto Launch Permission list
    * @param	void.
    * @return	void.
    **/
    void updateAutoLaunchPermissionList();

    /**
    * @brief	CW3WSetupListModel::updateStartupWalkthroughMenu function updates the Walkthrough on Startup menu
    * @param	void.
    * @return	void.
    **/
    void updateStartupWalkthroughMenu();

    /**
    * @brief	CW3WSetupListModel::updateCountryPreferenceList function updates the Country Preference list
    * @param	void.
    * @return	void.
    **/
    void updateCountryPreferenceList();

    /**
    * @brief	CW3WSetupListModel::updateModelForCheckedRole function updates the model of W3W Setup for Checked Role.
    * @param	iW3WSetupIndex: Index of the selected item in a W3W setup model.
    * @param	bCheckedStaus: Contains the boolean value whether item is checked or unchecked.
    * @return   void.
    **/
    void updateModelForCheckedRole(int iW3WSetupIndex, bool bCheckedStatus);

    /**
    * @brief	isItemEnabled: Method to get whether the W3W setup item is enabld or not.
    * @param	eItemName: W3W setup item index.
    * @return   TRUE if the item is enabled, FALSE otherwise.
    **/
    bool isItemEnabled(CW3WEnum::EW3WSetupItems eItemIndex);

private:
    /******************************************************//**
     * @category PROPERTIES
     *******************************************************/

    /**
    * @brief List to hold the information of each item in W3W setup screen.
    */
    QList<CW3WData::SW3WSetupData>    m_listW3WSetup;

    /**
    * @brief List to hold the information of each item in Auto Launch Permission options.
    */
    QList<CW3WData::SW3WSetupData>      m_listW3WAutoLaunchPermission;

    /**
    * @brief List to hold the information of each item in Country Preference options.
    */
    QList<CW3WData::SW3WSetupData>      m_listW3WCountryPreference;

    /**
    * @brief boolean variable which holds the value whether Auto Launch Permission List Item is expanded/collapsed.
    */
    bool m_bIsAutoLaunchPermissionExpanded;

    /**
    * @brief boolean variable which holds the value whether Country Preference List Item is expanded/collapsed.
    */
    bool m_bIsCountryPreferenceExpanded;

    /* Setup items list element index, here key is list item id and value is the position in list*/
    QMap<int, int> m_mapSetupDataElementIndex;
};

#endif // CW3WSETUPLISTMODEL_H
