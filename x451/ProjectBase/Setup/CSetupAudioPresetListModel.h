/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CSetupAudioPresetListModel.h
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * CSetupAudioPresetListModel.h, audio preset list model class header file, responsible for creating audio preset static list model
 */
#ifndef CSETUPAUDIOPRESETLISTMODEL_H
#define CSETUPAUDIOPRESETLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "CSetupData.h"
#include "logging.h"
#include "CAudioAdaptor.h"

//TODO: In this file that this class should be revisited and unwanted code and logic should be removed

/**
 * @brief The CSetupAudioPresetListModel class: Responsible for creating audio preset static list model
 */
class CSetupAudioPresetListModel : public QAbstractListModel
{
    Q_OBJECT

public:

    /* Roles to get the CSetupAudioPresetListModel data */
    enum EAudioPresetSetupRoles {
        ListItemIndexRole = Qt::UserRole,
        ListItemNameRole,
        ListItemTypeRole,
        ListItemCheckedRole
    };

    explicit CSetupAudioPresetListModel(QObject *parent = nullptr);
    ~CSetupAudioPresetListModel();

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
     * @brief Method is to get the audio preset name.
     * @param eAudioPresets: enum of the audio preset list
     * @return :m_sListItemName - returns the audio preset name.
     */
    const QString getAudioPresetName(CAudioEnums::EAudioPresets eAudioPresets);

private:

    /* Audio preset screen items list container */
    QList<CSetupData*> m_AudioPresetSetupDataList;

    /* Instance of CAudioAdaptor class */
    CAudioAdaptor *m_pAudioAdaptor;
};

#endif // CSETUPAUDIOPRESETLISTMODEL_H
