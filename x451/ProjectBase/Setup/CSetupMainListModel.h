/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CSetupMainListModel.h
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * CSetupMainListModel.h, setup main list model class header file, responsible for creating setup main static list model
 */
#ifndef CSETUPMAINLISTMODEL_H
#define CSETUPMAINLISTMODEL_H
#include <QAbstractListModel>
#include <QList>
#include "CSetupData.h"
#include "logging.h"


/**
 * @brief The CSetupMainListModel class: Responsible for creating setup main static list model
 */
class CSetupMainListModel : public QAbstractListModel
{
    Q_OBJECT
public:

    /* Roles to get the CSetupMainListModel data */
    enum EMainSetupRoles {
        ListItemIndexRole = Qt::UserRole,
        ListItemNameRole,
        ListItemTypeRole,
        ListItemCheckedRole,
        ListItemEnumsRole
    };

    explicit CSetupMainListModel(QObject *parent = nullptr);
    ~CSetupMainListModel();

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
     * @brief initMainSetupList: This method is to initilize main setup list
     * @param  : void
     * @return : void
     */
    void initMainSetupList();

private slots:

    /**
     * @brief sltHandleVehicleSetupPresence : This Method gets invoked when ever there is a change in BCM presence.
     * @param : void
     * @return : void
     */
    void sltHandleVehicleSetupPresence();

    /**
     * @brief  sltCPConnectionStatusUpdated: This slot gets invoked on CP device connection status update.
     * @param  bCPConnectionStatus: true - CP device  connected, false - not connected.
     * @return void.
     */
    void sltCPConnectionStatusUpdated(bool bCPConnectionStatus);

    /**
     * @brief  sltPowerModeChanged: This slot gets invoked on power mode change.
     * @param  void.
     * @return void.
     */
    void sltPowerModeChanged();

private:

    /* Main setup screen items list container */
    QList<CSetupData*> m_SetupDataList;
};

#endif // CSETUPMAINLISTMODEL_H
