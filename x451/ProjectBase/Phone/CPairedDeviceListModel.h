/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CPairedDeviceListModel.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CPairedDeviceListModel class that shall implement the
 * paired device list data model that shall be used to update the paired device and delete devices
 * UI screen.
 */

#ifndef CPAIREDDEVICELISTMODEL_H
#define CPAIREDDEVICELISTMODEL_H

#include <QObject>
#include <QString>
#include <QAbstractListModel>
#include "CPhoneData.h"

/*!
 * @class CPairedDeviceListModel
 * @brief This  class that shall implement the paired device list data model that shall be used to
 * update the paired device and delete devices UI screen.
 */

class CPairedDeviceListModel : public QAbstractListModel
{
    Q_OBJECT

private:
    /************************************************************************//**
     * @category    ENUMS
     ************************************************************************/

    /*!
     * @enum    EPairedDeviceListRoles
     * @brief   This enum shall hold the values that shall be used by paired devices and
     *          delete devices qml screen to update the data in the view.
     */
    enum EPairedDeviceListRoles
    {
        PAIRED_DEVICE_NAME_ROLE = Qt::UserRole + 1,
        PAIRED_DEVICE_ADDRESS_ROLE,
        PAIRED_DEVICE_CONNECTION_STATUS_ROLE,
        PAIRED_DEVICE_ITEM_TYPE_ROLE
    };

public:
    CPairedDeviceListModel(QObject* pParent = nullptr);
    ~CPairedDeviceListModel();

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
     * @brief   Method to append the paired device information in the paired device list.
     * @param   listPairedDevices - list of devices having information of the paired devices
     * @return  void.
     */
    void insertRows(const QList<CPhoneData::SPairedDeviceInfo>& listPairedDevices);

    /*!
     * @brief   Method to clear the paired device list.
     * @param   void.
     * @return  void.
     */
    void removeRows();

	 /**
     * @brief   isDeviceAlreadyPaired: This function is used to know that the
     *          the passed btAddress device already paired or not.
     * @param   strBtAddress: Bt Address of the device, which pairing status needs
     *          to check.
     * @return  true if device is already paired otherwise false.
     */
    bool isDeviceAlreadyPaired(const QString &strBtAddress);


private:
    /******************************************************//**
     * @category PROPERTIES
     *******************************************************/

    //! List to hold the paired device information of the searched devices.
    QList<CPhoneData::SPairedDeviceInfo>    m_listPairedDevices;
};

#endif // CPAIREDDEVICELISTMODEL_H
