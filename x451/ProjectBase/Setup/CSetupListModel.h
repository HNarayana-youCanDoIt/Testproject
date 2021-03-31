/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CSetupListModel.h
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * CSetupListModel.h, setup list model class header file, responsible for creating generic list of setup screen which has static model.
 */
#ifndef CSETUPLISTMODEL_H
#define CSETUPLISTMODEL_H
#include <QAbstractListModel>
#include <QList>
#include "CSetupData.h"
#include "logging.h"

/**
 * @brief The CSetupListModel class: Responsible for creating generic list of setup screen which has static model.
 */
class CSetupListModel : public QAbstractListModel
{
    Q_OBJECT
public:

    /* Roles to get the CSetupListModel data */
    enum ESetupRoles {
        ListItemIndexRole = Qt::UserRole,
        ListItemNameRole,
        ListItemDefaultImageRole,
        ListItemSelectedImageRole,
        ListItemTypeRole,
        ListItemEnabledRole,
        ListItemCollapsedRole,
        ListItemCheckedRole,
        ListItemValueRole,
        ListItemMinValue,
        ListItemMaxValue,
        ListItemDistributionModeImageRole,
        ListItemFanSpeedImageRole,
        ListItemFanSpeedValue,
        ListItemTemperatureValue,
        ListItemThemeLoadingStatus,
        ListItemClimateIconsVisibilityStatus,
        ListItemThemeColorVisibility,
        ListItemThemeSoundVisibility,
        ListItemIdRole,
    };

    explicit CSetupListModel(QObject *parent = nullptr);
    ~CSetupListModel();

    /**
     * @brief rowCount: When subclassing QAbstractListModel must provide implementation of the rowCount()
     * @param parent: When the parent is valid it means that rowCount is returning the number of children of parent.
     * @return Returns the number of rows in the model
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief data : When subclassing QAbstractListModel must provide implementation of the data()
     * @param index: The index whose data to be returned
     * @param role: The role whose data to be returned
     * @return Returns the data stored under the given role for the item referred to by the index
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * @brief roleNames: Defines rolenames that are to be used in qml
     * @param void
     * @return : Returns the model's role names
     */
    QHash<int, QByteArray> roleNames() const;

    /**
     * @brief setData: Sets the role data for the item at index to value
     * @param index: The index for which value to be set
     * @param value: The value to be set for the role
     * @param role: The role data to be modified
     * @return: Returns true if successful; otherwise returns false.
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    /**
     * @brief To add data to the setup list model
     * @param objSetupData: SetupData class obj, which is to be added to the list
     * @return: void
     */
    void addDataToModel(const CSetupData& objSetupData);

    /**
     * @brief   updateThemeSetupModelData: To update the theme setup model data.
     * @param   iRole: Role to be updated.
     * @param   iListItemIndex: Index to be updated.
     * @param   objValue: Value to be updated.
     * @param   eSetupListOption: Variable holds the setup list item index.
     * @return  void.
     */
    void updateThemeSetupModelData(int iRole, int iListItemIndex, const QVariant& objValue,
                                   CSetupEnums::ESetupScreens eSetupListOption = CSetupEnums::SETUP_SCREEN_INVALID);

    /**
     * @brief To update the theme setup model data
     * @param iRole: Role to be updated
     * @param iListItemIndex: Index to be updated
     * @param value: Value to be updated
     * @param CSetupEnums::ESetupScreens:eSetupListOption variable holds the setup list screens and setup list options
     * @return void
     */
    void updateSetupModelData(int iRole, int iListItemIndex, const QVariant& objValue,
                              CSetupEnums::ESetupScreens eSetupListOption = CSetupEnums::SETUP_SCREEN_INVALID);

    /**
     * @brief insertElementAt Function to insert rows from model
     * @param  iRow : iRow holds the data to inserted at particular row.
     * @param objSetupData : SetupData class obj, which is to be added to the list
     * @return : void
     */
    void insertElementAt(int iRow, const CSetupData &objSetupListModel);

    /**
     * @brief removeElementAt Function to remove element from model
     * @param  iRow : iRow holds the data to inserted at particular row.
     * @return : void
     */
    void removeElementAt(int iRow);

    /**
     * @brief insertRows Function to insert rows into the model.
     * @param objSetupListModel : SetupListModel class obj, which is to be added to the list
     * @return void.
     */
    void insertRows(const CSetupData &objSetupListModel);

    /**
    * @brief	removeRows function used to remove rows from model.
    * @param	void.
    * @return	void.
    **/
    void removeRows();

    /**
     * @brief elementAt Function returns the list element at index.
     * @param iIndex : holds the index of the list element
     * @return elementAt : returns the list element at index.
     */
    CSetupData elementAt(int iIndex);

    /**
     * @brief findIndexForRequiredRole: Function returns the index for required role and value.
     * @param iRole : holds the role for which we have to find the index.
     * @param value : value for which we have to find the index for the corresponding role.
     * @return index needed to update the model.
     */
    int findIndexForRequiredRole(int iRole, const QVariant &value);

    /**
     * @brief updateData: Function used to update data ofgiven element
     * @param iIndex : index to update.
     * @param value : value to update for the corresponding role.
     * @return ESetupRoles eRole : corresponding role to update.
     */
    void updateData(int iIndex, const QVariant &value, ESetupRoles eRole);

private:
    /**
     * @brief listChecked : To get the list item is checked or not
     * @return : bool
     * @param : void
     */
    bool listChecked();

    /**
     * @brief listItemValue : To get the list item value
     * @return : int
     * @param : void
     */
    int listItemValue();

    /**
     * @brief listItemDefaultImage : To get the list item default image path
     * @return : QString: Path of the default image
     * @param : void
     */
    QString listItemDefaultImage();

    /**
     * @brief listItemSelectedImage : To get the list item selected image path
     * @return : QString: Path of the selected image
     * @param : void
     */
    QString listItemSelectedImage();

    /**
     * @brief isCollapsed : To get the state of the list item, collapsed or expanded
     * @return : bool: collapsed or expanded
     * @param : void
     */
    bool isCollapsed();

    /**
     * @brief isListItemEnabled : To get the state of the list item, enabled or disabled
     * @return : bool: true or false
     * @param : void
     */
    bool isListItemEnabled();

    /**
     * @brief   updateThemeColor: To update the theme colour as per the selected theme.
     * @param   iListItemIndex: Index to be updated.
     * @param   objValue: Value to be updated.
     * @return  void.
     */
    void updateThemeColor(const QVariant& objValue, int& iListItemIndex);

public:

    /*  setup screen items list container */
    QList<CSetupData> m_SetupDataList;

    /* list item name gets stored in this var */
    QString m_sListItemName;

    /* list item type delegate stored in this var */
    CSetupEnums::ESetupListItemTypes m_sListItemType;

    /* list item is checked status stored in this var */
    bool m_bListItemChecked;

    /* list item value gets stored in this var */
    int m_iListItemValue;

    /* list item default image path gets stored in this var */
    QString m_sListItemDefaultImage;

    /* list item selected image path gets stored in this var */
    QString m_strListItemSelectedImage;

    /* list item collapsed status stored in this var */
    bool m_bIsListItemCollapsed;

    /* list item enabled / disabled status stored in this var */
    bool m_bIsListItemEnabled;
};

#endif // CSETUPLISTMODEL_H
