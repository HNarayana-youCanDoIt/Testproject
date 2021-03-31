/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CSetupGeneralListModel.h
 * @ingroup       HMIComponent
 * @author        Rajat Gupta
 * CSetupGeneralListModel.h, setup main list model class header file, responsible for creating setup General static list model
 */
#ifndef CSETUPGENERALLISTMODEL_H
#define CSETUPGENERALLISTMODEL_H
#include <QAbstractListModel>
#include <QList>
#include "CSetupData.h"
#include "logging.h"

/**
 * @brief The CSetupGeneralListModel class: Responsible for creating setup General static list model
 */
class CSetupGeneralListModel : public QAbstractListModel
{
    Q_OBJECT
public:

    /**
     * Roles to get the CSetupGeneralListModel data
    */
    enum EMainSetupRoles {
        ListItemIndexRole = Qt::UserRole,
        ListItemNameRole,
        ListItemTypeRole,
        ListItemEnableRole
    };

    explicit CSetupGeneralListModel(QObject *parent = nullptr);
    ~CSetupGeneralListModel();

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
    QVariant data(const QModelIndex &index, int iRole = Qt::DisplayRole) const override;

    /**
     * @brief roleNames: Defines rolenames that are to be used in qml
     * @param void
     * @return : Returns the model's role names
     */
    QHash<int, QByteArray> roleNames() const;

private slots:
    /**
     * @brief   sltEnggProxyStatusChanged: To update Factory reset List Item Enable/Disable based on Engg Menu proxy Status.
     * @param   void.
     * @return  void.
     */
    void sltEnggProxyStatusChanged();

private:

    /* General setup screen items list container */
    QList<CSetupData*> m_SetupGeneralDataList;
};

#endif // CSETUPGENERALLISTMODEL_H
