/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CSetupAudioListModel.h
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * CSetupAudioListModel.h, audio setup list model class header file, responsible for creating audio setup static list model
 */

#ifndef CSETUPVOLUMESETTINGSLISTMODEL_H
#define CSETUPVOLUMESETTINGSLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "CSetupData.h"
#include "logging.h"
#include "CAudioAdaptor.h"
#include "CSetupEnums.h"

class CSetupVolumeSettingsListModel : public QAbstractListModel
{
    Q_OBJECT

public:

    /* Roles to get the CSetupAudioListModel data */
    enum EVolumeSetupRoles {
        ListItemIndexRole = Qt::UserRole,
        ListItemDefaultImageRole,
        ListItemNameRole,
        ListItemTypeRole,
        ListItemCheckedRole,
        ListItemValueRole,
        ListItemMinValue,
        ListItemMaxValue
    };

    explicit CSetupVolumeSettingsListModel(QObject *parent = nullptr);
    ~CSetupVolumeSettingsListModel();

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

private slots:
    /**
     * @brief sltSpeedDependantVolumeChanged: Method gets invoked whenever there is a change in speed dependant volume.
     * @param void
     * @return void
     */
    void sltSpeedDependantVolumeChanged();

    /**
     * @brief sltStartUpVolumeChanged: Method gets invoked whenever there is a change in start up volume.
     * @param void
     * @return void
     */
    void sltStartUpVolumeChanged();

    /**
     * @brief sltPhoneCallVolumeChanged: Method gets invoked whenever there is a change in phone call volume.
     * @param void
     * @return void
     */
    void sltPhoneCallVolumeChanged();

    /**
     * @brief sltVoiceAlertVolumeChanged: Method gets invoked whenever there is a change in voice alert volume.
     * @param void
     * @return void
     */
    void sltVoiceAlertVolumeChanged();

private:

    /* Audio setup screen items list container */
    QList<CSetupData*> m_VolumeSetupDataList;

    /* Instance of CAudioAdaptor class */
    CAudioAdaptor *m_pAudioAdaptor;
};

#endif // CSETUPVOLUMESETTINGSLISTMODEL_H
