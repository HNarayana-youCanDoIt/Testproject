/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CSetupBMTListModel.h
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * CSetupBMTListModel.h, BMT list model class header file, responsible for creating BMT static list model
 */
#ifndef CSETUPBMTLISTMODEL_H
#define CSETUPBMTLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "CSetupData.h"
#include "logging.h"
#include "CAudioAdaptor.h"
#include "CSetupEnums.h"

/**
 * @brief The CSetupBMTListModel class: Responsible for creating BMT static list model
 */
class CSetupBMTListModel : public QAbstractListModel
{
    Q_OBJECT

public:

    /* Roles to get the CSetupBMTListModel data */
    enum EBMTRoles {
        ListItemIndexRole = Qt::UserRole,
        ListItemNameRole,
        ListItemTypeRole,
        ListItemCheckedRole,
        ListItemValueRole
    };

    explicit CSetupBMTListModel(QObject *parent = nullptr);
    ~CSetupBMTListModel();

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

private slots:

    /**
     * @brief sltBassChanged: Method gets invoked whenever there is a change in bass value
     * @param void
     * @return void
     */
    void sltBassChanged();

    /**
     * @brief sltMidChanged: Method gets invoked whenever there is a change in middle value
     * @param void
     * @return void
     */
    void sltMidChanged();

    /**
     * @brief sltTrebleChanged: Method gets invoked whenever there is a change in treble value
     * @param void
     * @return void
     */
    void sltTrebleChanged();

private:

    /* BMT screen items list container */
    QList<CSetupData*> m_BMTSetupDataList;

    /* Instance of CAudioAdaptor class */
    CAudioAdaptor *m_pAudioAdaptor;

};

#endif // CSETUPBMTLISTMODEL_H
