/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CThemeSetupWithDriveModeListModel.h
 * @ingroup       HMIComponent
 * @author        Rahul Balyan
 * @brief         This file contains CThemeSetupWithDriveModeListModel class that shall implement
 * the Theme setup with drive mode list data model that shall be used to update the theme setup
 * with drive mode screen.
 */

#ifndef CTHEMESETUPWITHDRIVEMODELISTMODEL_H
#define CTHEMESETUPWITHDRIVEMODELISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "CSetupData.h"

/*!
 * @class CThemeSetupWithDriveModeListModel
 * @brief This class shall implement the theme setup with drive mode list data model that
 * shall be used to update the theme setup with drive mode qml screen.
 */
class CThemeSetupWithDriveModeListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    /************************************************************************//**
     * @category    ENUMS
     ************************************************************************/

    /*!
     * @enum    EThemeSetupWithDriveModeListRoles
     * @brief   This enum shall hold the values that shall be used by theme setup with drive mode qml screen
     * to update the data in the view.
     */
    enum EThemesSetupListRoles
    {
        // This role holds the Item Main text
        THEME_SETUP_ITEM_TEXT_ROLE = Qt::UserRole + 1,
        // This role holds the Item Enable/Disable state
        THEME_SETUP_ITEM_ENABLED_ROLE,
        // This role holds the Item Checked/Unchecked state
        THEME_SETUP_ITEM_CHECKED_ROLE,
        // This role holds the Item type of the list item.
        THEME_SETUP_ITEM_TYPE_ROLE,
        /**
         * This Role is used to identify the Item which is selected by user and which Item needs to expand on
         * drop-down click.
         */
        THEME_SETUP_ITEM_ID_ROLE,
    };
public:
    /**
    * @brief	CThemeSetupWithDriveModeListModel::CThemeSetupWithDriveModeListModel constructor for theme setup with drive mode model.
    * @param	QObject. The pointer of parent class.
    * @return	NA.
    **/
    CThemeSetupWithDriveModeListModel(QObject* pParent = nullptr);

    /**
    * @brief	CThemeSetupWithDriveModeListModel::CThemeSetupWithDriveModeListModel destructor for theme setup with drive mode model.
    * @param	NA.
    * @return	NA.
    **/
    ~CThemeSetupWithDriveModeListModel();

    /************************************************************************//**
     * @category    OVERRIDEN METHODS of QAbstractListModel class
     ************************************************************************/

    /**
    * @brief	CThemeSetupWithDriveModeListModel::rowCount function inherited from QAbstractListModel,
    *           Used to get row count.
    * @param	QModelIndex : The index is used to locate an item in the model.
    * @return	int : holds row count.
    **/
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

    /**
    * @brief	CThemeSetupWithDriveModeListModel::data function inherited from QAbstractListModel,
    *           Used to get data linked to given role and present at given index.
    * @param	(index)QModelIndex : The index is used to locate an item in the model.
    *           (role)int : holds the role name of data to be extract from QModelIndex item.
    * @return	QVariant : data stored under the given role for the item referred to by the index.
    **/
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

    /**
    * @brief	CThemeSetupWithDriveModeListModel::roleNames function inherited from QAbstractListModel,
    *           Used to get role names
    * @param	void.
    * @return	QHash<int, QByteArray> : holds model's role names
    **/
    QHash<int, QByteArray> roleNames() const override;

    /**
     * @brief CThemeSetupWithDriveModeListModel::setData Sets the role data for the item at index to value
     * @param index: The index for which value to be set
     * @param value: The value to be set for the role
     * @param role: The role data to be modified
     * @return: Returns true if successful; otherwise returns false.
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    /**
     * @brief CThemeSetupWithDriveModeListModel::invExpandThemesDropdown Expands themes Dropdown.
     * @param void.
     * @return void.
     */
    Q_INVOKABLE void invExpandThemesDropdown();

    /**
     * @brief CThemeSetupWithDriveModeListModel::invCollapseThemesDropdown collapse themes Dropdown.
     * @param void.
     * @return void.
     */
    Q_INVOKABLE void invCollapseThemesDropdown();

    /**
     * @brief CThemeSetupWithDriveModeListModel::invToggleChangeThemeWithDriveMode This method toggle change theme with drive mode status.
     * @param bool : bToggleBtnStatus.
     * @return void.
     */
    Q_INVOKABLE void invToggleChangeThemeWithDriveMode(bool bToggleBtnStatus);

    /**
    * @brief	CThemeSetupWithDriveModeListModel::initThemeSetupWithDriveModeMainModel function initializes the Main Theme Setup with drive mode Model
    * @param	void.
    * @return	void.
    **/
    void initThemeSetupWithDriveModeMainModel();

    /**
    * @brief	CThemeSetupWithDriveModeListModel::initThemesModel function initializes the theme list.
    * @param	void.
    * @return	void.
    **/
    void initThemesModel();

    /**
    * @brief	CThemeSetupWithDriveModeListModel::updateThemesList function updates the themes list
    * @param	void .
    * @return	void.
    **/
    void updateThemesList();

private:
    /******************************************************//**
     * @category PROPERTIES
     *******************************************************/

    /**
    * @brief List to hold the information of each item in theme setup with drive mode screen.
    */
    QList<CSetupData>    m_listThemeSetupWithDriveMode;

    /**
    * @brief List to hold the information of each item in themes option.
    */
    QList<CSetupData>      m_listThemes;


};

#endif // CTHEMESETUPWITHDRIVEMODELISTMODEL_H
