/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CAudioSettingsModel.h
 * @ingroup       HMIComponent
 * @author        Gaurav Garg
 * CAudioSettingsModel.h, audio settings list model file, Responsible for creating audio settings list model for HBTabBar
 */
#ifndef CAUDIOSETTINGSMODEL_H
#define CAUDIOSETTINGSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "CSetupData.h"

/**
 * @brief The CAudioSettingsModel class : Responsible for creating audio settings list model for HBTabBar
 */
class CAudioSettingsModel : public QAbstractListModel
{
    Q_OBJECT

    /**
    * @brief CAudioSettingsModel::EAudioSettingsTabBarRoles is enum used to refer model values from QML.
    **/
    enum EAudioSettingsTabBarRoles
    {
        TAB_BAR_COMPONENT_NAME_ROLE = Qt::UserRole + 1,
        TAB_BAR_COMPONENT_LEFT_ICON_ROLE,
        TAB_BAR_COMPONENT_MID_ICON_ROLE,
        TAB_BAR_COMPONENT_RIGHT_ICON_ROLE
    };

public:
    CAudioSettingsModel(QObject* pParent = nullptr);
    ~CAudioSettingsModel();

    /**
    * @brief	CAudioSettingsModel::rowCount function inherited from QAbstractListModel,
    *           Used to get row count.
    * @param	QModelIndex : The index is used to locate an item in the model.
    * @return	int : holds row count.
    **/
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

    /**
    * @brief	CAudioSettingsModel::data function inherited from QAbstractListModel,
    *           Used to get data linked to given role and present at given index.
    * @param	(index)QModelIndex : The index is used to locate an item in the model.
    *           (role)int : holds the role name of data to be extract from QModelIndex item.
    * @return	QVariant : data stored under the given role for the item referred to by the index.
    **/
    QVariant data(const QModelIndex &iIndex, int iRole = Qt::DisplayRole) const override;

    /**
    * @brief	CAudioSettingsModel::roleNames function inherited from QAbstractListModel,
    *           Used to get role names
    * @param	void.
    * @return	QHash<int, QByteArray> : holds model's role names
    **/
    QHash<int, QByteArray> roleNames() const override;

private:

    /**
     * @brief m_objAudioSetupDataList : Audio preset TabBar items list container
     */
    QList<CSetupData> m_objAudioSetupDataList;

};

#endif // CAUDIOSETTINGSMODEL_H
