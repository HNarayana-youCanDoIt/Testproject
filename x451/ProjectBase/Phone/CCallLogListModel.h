/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CCallLogListModel.h
 * @ingroup       HMIComponent
 * @author        Nandkishor Lokhande
 * @brief         This file contains CCallLogListModel class that shall implement the
 * call log list data model that shall be  display on call log screen.
 */

#ifndef CCALLLOGLISTMODEL_H
#define CCALLLOGLISTMODEL_H

#include <QObject>
#include <QString>
#include <QAbstractListModel>
#include "CPhoneData.h"

/*!
 * @class CDeviceSearchListModel
 * @brief This  class that shall implement the call log list data model that shall be used
 * to update the call log list UI screen.
 */
class CCallLogListModel : public QAbstractListModel
{
    Q_OBJECT

private:
    /**//** *****************************************************************
     * @category    ENUMS
     ************************************************************************/

    /*!
     * @enum    ECallLogListRoles
     * @brief   This enum shall hold the values that shall be used by call logs qml screen
     * to update the data in the view.
     */
    enum ECallLogListRoles
    {
        CALL_LOG_NAME_ROLE = Qt::UserRole + 1,
        CALL_LOG_NUMBER_ROLE,
        CALL_LOG_TYPE_ROLE,
        CALL_LOG_TIME_ROLE,
        CALL_LOG_DATE_ROLE,
    };

public:
    CCallLogListModel(QObject* pParent = nullptr);
    ~CCallLogListModel();

    /**//** *****************************************************************
     * @category    OVERRIDEN METHODS of QAbstractListModel class
     ************************************************************************/
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

    /**//** *****************************************************************
     * @category    EXTERNAL METHODS
     ************************************************************************/

    /*!
     * @brief   Method to append the call log information in the list.
     * @param   SCallLogInfo   - call details.
     * @return  void.
     */
    void insertRows(const CPhoneData::SCallLogInfo callDetailInfo);

    /*!
     * @brief   Method to clear the call log list.
     * @param   void.
     * @return  void.
     */
    void removeRows();
private:
    /**//** *****************************************************************
     * @category PROPERTIES
     ************************************************************************/

    //! List to hold information of the call logs
    QList<CPhoneData::SCallLogInfo>    m_list;
};

#endif // CCALLLOGLISTMODEL_H
