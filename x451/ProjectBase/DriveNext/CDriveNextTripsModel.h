/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file            CDriveNextTripsModel.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDriveNextTripsModel.h, DriveNext Trips model file, responsible for creating DriveNext trips static list model
 */

#ifndef CDRIVENEXTTRIPSMODEL_H
#define CDRIVENEXTTRIPSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "CDriveNextData.h"

/**
 * @brief The CDriveNextTripsModel class : Responsible for creating DriveNext trips list model for HBTabBar
 */
class CDriveNextTripsModel : public QAbstractListModel
{
    Q_OBJECT

    /**
    * @brief CDriveNextTripsModel::EDriveNextTripsTabBarRoles is enum used to refer model values from QML.
    **/
    enum EDriveNextTripsTabBarRoles
    {
        TAB_BAR_COMPONENT_NAME_ROLE = Qt::UserRole + 1,
        TAB_BAR_COMPONENT_LEFT_ICON_ROLE,
        TAB_BAR_COMPONENT_MID_ICON_ROLE,
        TAB_BAR_COMPONENT_RIGHT_ICON_ROLE
    };

public:
    CDriveNextTripsModel(QObject* pParent = nullptr);
    ~CDriveNextTripsModel();

    /**
    * @brief	CDriveNextTripsModel::rowCount function inherited from QAbstractListModel,
    *           Used to get row count.
    * @param	QModelIndex : The index is used to locate an item in the model.
    * @return	int : holds row count.
    **/
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

    /**
    * @brief	CDriveNextTripsModel::data function inherited from QAbstractListModel,
    *           Used to get data linked to given role and present at given index.
    * @param	(index)QModelIndex : The index is used to locate an item in the model.
    *           (role)int : holds the role name of data to be extract from QModelIndex item.
    * @return	QVariant : data stored under the given role for the item referred to by the index.
    **/
    QVariant data(const QModelIndex &iIndex, int iRole = Qt::DisplayRole) const override;

    /**
    * @brief	CDriveNextTripsModel::roleNames function inherited from QAbstractListModel,
    *           Used to get role names
    * @param	void.
    * @return	QHash<int, QByteArray> : holds model's role names
    **/
    QHash<int, QByteArray> roleNames() const override;

    /**
    * @brief	CDriveNextTripsModel::getElementAt function used to get element at provided index.
    * @param	int index
    * @return	SDriveNextTripData element object.
    **/
    SDriveNextTripData getElementAt(int index);

private:

    /**
     * @brief m_objDataList : Audio preset TabBar items list container
     */
    QList<SDriveNextTripData> m_objDataList;

};

#endif // CDRIVENEXTTRIPSMODEL_H
