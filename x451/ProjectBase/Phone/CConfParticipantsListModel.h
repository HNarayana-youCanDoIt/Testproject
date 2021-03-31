/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CConfParticipantsListModel.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CConfParticipantsListModel class that shall implement the
 * conference participant list data model that shall be used to update the conference participant screen.
 */

#ifndef CCONFPARTICIPANTSLISTMODEL_H
#define CCONFPARTICIPANTSLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "CPhoneData.h"

/*!
 * @class CConfParticipantsListModel
 * @brief This implement the conference participant list data model that shall be used to
 * update the conference participant screen.
 */
class CConfParticipantsListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    /************************************************************************//**
     * @category    ENUMS
     ************************************************************************/

    /*!
     * @enum    EConfParticipantListRoles
     * @brief   This enum shall hold the values that shall be used by conference participant qml screen
     * to update the data in the view.
     */
    enum EConfParticipantListRoles
    {
        CONF_PARTICIPANT_NAME_ROLE = Qt::UserRole + 1,
        CALLER_ID_ROLE,
        END_PARTICIPANT_CALL_ROLE,
    };

public:
    CConfParticipantsListModel(QObject* pParent = nullptr);
    ~CConfParticipantsListModel();

    /************************************************************************//**
     * @category    OVERRIDEN METHODS of QAbstractListModel class
     ************************************************************************/
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    /************************************************************************//**
     * @category    EXTERNAL METHODS
     ************************************************************************/

    /*!
     * @brief   Method to append the participant info in the conference participant screen.
     * @param   objConfParticipantInfo   - participant info in conference call.
     * @return  void.
     */
    void insertRows(const CPhoneData::SConfParticipantInfo& objConfParticipantInfo);

    /*!
     * @brief   Method to clear the conference participant list.
     * @param   void.
     * @return  void.
     */
    void removeRows();

    /**
     * @brief   Method to update the individual role data of the item in conference participant
     *          list as per the list index passed.
     * @param   iListIndex  - index of the item for which the role data needs to be updated.
     * @param   objData     - data that needs to be updated of the item role.
     * @param   iRole       - role of the item for which the data needs to be updated.
     * @return  void.
     */
    void updateConfParticipantListItem(int iListIndex , const QVariant& objData, int iRole);

private:
    /******************************************************//**
     * @category PROPERTIES
     *******************************************************/

    //! List to hold the participant info in conference call.
    QList<CPhoneData::SConfParticipantInfo>    m_listConfParticipant;
};

#endif // CCONFPARTICIPANTSLISTMODEL_H
