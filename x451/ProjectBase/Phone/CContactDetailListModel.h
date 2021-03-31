/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CContactListModel.h
 * @ingroup       HMIComponent
 * @author        Nandkishor Lokhande
 * @brief         This file contains CContactListModel class that shall implement the
 * contact list data model that shall be  display on contact screen.
 */

#ifndef CCONTACTDETAILLISTMODEL_H
#define CCONTACTDETAILLISTMODEL_H

#include <QObject>
#include <QString>
#include <QAbstractListModel>
#include "CPhoneData.h"

/*!
 * @class CContactDetailListModel
 * @brief This  class that shall implement the contact detail list data model that shall be used
 * to update the contact/details/favorite list UI screen.
 */
class CContactDetailListModel : public QAbstractListModel
{
    Q_OBJECT

private:
    /**//** *****************************************************************
     * @category    ENUMS
     ************************************************************************/

    /*!
     * @enum    EContactDetailListRoles
     * @brief   This enum shall hold the values that shall be used by contact/details/favorite qml screen
     * to update the data in the view.
     */

    enum ECallLogListRoles
    {
        CONTACT_INDEX_ROLE = Qt::UserRole + 1,
        CONTACT_ID_ROLE,
        CONTACT_NAME_ROLE,
        CONTACT_NUMBER_ROLE,
        CONTACT_TYPE_ROLE,
        CONTACT_IS_FAVORITE_ROLE,
        CONTACT_FAVORITE_INDEX_ROLE,
    };

public:
    CContactDetailListModel(QObject* pParent = nullptr);
    ~CContactDetailListModel();

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
     * @brief   Method to append the contact detail information in the list.
     * @param   SContactDetailInfo - contact detail information.
     * @return  void.
     */
    void insertRows(const CPhoneData::SContactDetailInfo contactDetailInfo);

    /*!
     * @brief   Method to clear the contact detail list.
     * @param   void.
     * @return  void.
     */
    void removeRows();

    /*!
     * @brief   Method to get favorite index value for index.
     * @param   int. list index for list element
     * @return  int. favorite index value list element
     */
    int getFavoriteIndex(int iRowIndex);

    /*!
     * @brief   Method to set favorite index value for index.
     * @param   int. list index for list element
     * @param   int. favorite index value list element
     * @return  void
     */
    void setFavoriteIndex(int iRowIndex, int iFavIndex);

    /*!
     * @brief   Method to get name value for index.
     * @param   int. list index for list element
     * @return  QString. name value for list element
     */
    Q_INVOKABLE QString getNameFromIndex(int iRowIndex);

    /*!
     * @brief   Method to get number value for index.
     * @param   int. list index for list element
     * @return  QString. number value for list element
     */
    Q_INVOKABLE QString getNumberFromIndex(int iRowIndex);

    /*!
     * @brief   Method to get contact id value for index.
     * @param   int. list index for list element
     * @return  int. contact id value for list element
     */
    Q_INVOKABLE int getContactIdFromIndex(int iRowIndex);

    /*!
     * @brief   getContactTypeFromIndex - Method to get contact type value for index.
     * @param   iRowIndex - list index for list element
     * @return  contact type value for list element
     */
    Q_INVOKABLE int getContactTypeFromIndex(int iRowIndex);

private:
    /**//** *****************************************************************
     * @category PROPERTIES
     ************************************************************************/

    //! List to hold information of the contact details
    QList<CPhoneData::SContactDetailInfo>    m_list;
};

#endif // CCONTACTDETAILLISTMODEL_H
