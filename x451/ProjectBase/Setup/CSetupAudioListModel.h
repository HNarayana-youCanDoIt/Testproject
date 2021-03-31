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
 * @author        Harish Kunisetty
 * CSetupAudioListModel.h, audio setup list model class header file, responsible for creating audio setup static list model
 */
#ifndef CSETUPAUDIOLISTMODEL_H
#define CSETUPAUDIOLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "CSetupData.h"
#include "logging.h"

/**
 * @brief The CSetupAudioListModel class: Responsible for creating audio setup static list model
 */
class CSetupAudioListModel : public QAbstractListModel
{
    Q_OBJECT

public:

    /* Roles to get the CSetupAudioListModel data */
    enum EAudioSetupRoles {
        ListItemIndexRole = Qt::UserRole,
        ListItemNameRole,
        ListItemTypeRole
    };

    explicit CSetupAudioListModel(QObject *parent = nullptr);
    ~CSetupAudioListModel();

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

private:

    /* Audio setup screen items list container */
    QList<CSetupData*> m_AudioSetupDataList;
};

#endif // CSETUPAUDIOLISTMODEL_H
