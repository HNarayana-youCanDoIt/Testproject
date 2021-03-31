/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CDeviceSearchListModel.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CDeviceSearchListModel class that shall implement the
 * device search list data model that shall be used to update the pair new device UI screen.
 */

#ifndef CDEVICESEARCHLISTMODEL_H
#define CDEVICESEARCHLISTMODEL_H

#include <QObject>
#include <QString>
#include <QAbstractListModel>
#include "CPhoneData.h"

/*!
 * @class CDeviceSearchListModel
 * @brief This  class that shall implement the device search list data model that shall be used
 * to update the device search list UI screen.
 */
class CDeviceSearchListModel : public QAbstractListModel
{
    Q_OBJECT

private:
    /************************************************************************//**
     * @category    ENUMS
     ************************************************************************/

    /*!
     * @enum    EDeviceSearchListRoles
     * @brief   This enum shall hold the values that shall be used by pair new device qml screen
     * to update the data in the view.
     */
    enum EDeviceSearchListRoles
    {
        DEVICE_NAME_ROLE = Qt::UserRole + 1,
        DEVICE_ADDRESS_ROLE
    };

public:
    CDeviceSearchListModel(QObject* pParent = nullptr);
    ~CDeviceSearchListModel();

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
     * @brief   insertRows: Method to append the device info in the search device list.
     * @param   objDeviceInfo   - device information of the searched device.
     * @return  void.
     */
    void insertRows(const CPhoneData::SDeviceInfo& objDeviceInfo);

    /*!
     * @brief   removeRow: Method to delete single entry from list.
     * @param   iRow: element index to delete.
     * @return  void.
     */
    void removeRow(int iRow);

    /*!
     * @brief   removeRows: Method to clear the device search list.
     * @param   void.
     * @return  void.
     */
    void removeRows();

    /*!
     * @brief   getNameFromIndex: Method to get name value for index.
     * @param   iRowIndex: list index for list element
     * @return  name value for list element
     */
    Q_INVOKABLE QString getNameFromIndex(int iRowIndex);

    /*!
     * @brief   getAddrFromIndex: Method to get address value for index.
     * @param   iRowIndex: list index for list element
     * @return  address value for list element
     */
    Q_INVOKABLE QString getAddrFromIndex(int iRowIndex);

private:
    /******************************************************//**
     * @category PROPERTIES
     *******************************************************/

    //! List to hold the device info of the searched devices.
    QList<CPhoneData::SDeviceInfo>    m_listSearchDevices;
};

#endif // CDEVICESEARCHLISTMODEL_H
