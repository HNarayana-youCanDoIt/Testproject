/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CThemeSettingsModel.h
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * CThemeSettingsModel.h, theme settings list model file, responsible for creating theme preset static list model
 */
#ifndef CTHEMESETTINGSMODEL_H
#define CTHEMESETTINGSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "CSetupData.h"

/**
 * @brief The CThemeSettingsModel class : Responsible for creating theme preset static list model
 */
class CThemeSettingsModel : public QAbstractListModel
{
    Q_OBJECT

    /**
    * @brief CPhoneBrowseTabBarModel::EPhoneBrowseTabBarRoles is enum used to refer model values from QML.
    **/
    enum EThemePresetsTabBarRoles
    {
        TAB_BAR_COMPONENT_NAME_ROLE = Qt::UserRole + 1,
        TAB_BAR_COMPONENT_LEFT_ICON_ROLE,
        TAB_BAR_COMPONENT_MID_ICON_ROLE,
        TAB_BAR_COMPONENT_RIGHT_ICON_ROLE
    };

public:
    CThemeSettingsModel(QObject* pParent = nullptr);
    ~CThemeSettingsModel();

    /**
    * @brief	CPhoneBrowseTabBarModel::rowCount function inherited from QAbstractListModel,
    *           Used to get row count.
    * @param	QModelIndex : The index is used to locate an item in the model.
    * @return	int : holds row count.
    **/
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

    /**
    * @brief	CPhoneBrowseTabBarModel::data function inherited from QAbstractListModel,
    *           Used to get data linked to given role and present at given index.
    * @param	(index)QModelIndex : The index is used to locate an item in the model.
    *           (role)int : holds the role name of data to be extract from QModelIndex item.
    * @return	QVariant : data stored under the given role for the item referred to by the index.
    **/
    QVariant data(const QModelIndex &iIndex, int iRole = Qt::DisplayRole) const override;

    /**
    * @brief	CPhoneBrowseTabBarModel::roleNames function inherited from QAbstractListModel,
    *           Used to get role names
    * @param	void.
    * @return	QHash<int, QByteArray> : holds model's role names
    **/
    QHash<int, QByteArray> roleNames() const override;

    /**
     * @brief To update the theme tab bar model data
     * @param iIndex: holds the index of the list element
     * @param objThemeData: data stored under the given role for the item referred to by the index.
     * @return void
     */
    void updateModel(int iIndex, const CSetupData &objThemeData);

    /**
     * @brief To get the model data from the index.
     * @param iIndex: holds the index of the list element
     * @return getModelData : returns the model data
     */
    CSetupData getModelData(int iIndex);

private:

    /**
     * @brief m_pThemeSetupDataList : Theme preset TabBar items list container
     */
    QList<CSetupData> m_objThemeSetupDataList;

};

#endif // CTHEMESETTINGSMODEL_H
