/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CVRListModel.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CVRListModel class that shall implement the
 * VR list data model which shall be used to either show picklist data or teleprompter list data.
 */

#ifndef CVRLISTMODEL_H
#define CVRLISTMODEL_H

#include <QObject>
#include <QString>
#include <QAbstractListModel>

class CVRListModel : public QAbstractListModel
{
    Q_OBJECT

private:
    /************************************************************************//**
     * @category    ENUMS
     ************************************************************************/

    /*!
     * @enum    EVRListRoles
     * @brief   This enum shall hold the values that shall be used to update either
     * pick list or teleprompter list data in the view.
     */
    enum EVRListRoles
    {
        VR_LIST_ITEM_NAME_ROLE = Qt::UserRole + 1
    };

public:
    /**
     * @brief   CVRListModel: Constructor of CVRListModel.
     * @param   pParent: QObject pointer of parent class.
     * @return  NA.
     */
    CVRListModel(QObject *pParent = nullptr);

    /**
     * @brief   ~CVRListModel: Destructor of CVRListModel
     * @param   NA.
     * @return  NA.
     */
    ~CVRListModel();

    /************************************************************************//**
     * @category    OVERRIDEN METHODS of QAbstractListModel class
     ************************************************************************/
    int rowCount(const QModelIndex & objParent = QModelIndex()) const override;
    QVariant data(const QModelIndex & objIndex, int iRole = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    /************************************************************************//**
     * @category    EXTERNAL METHODS
     ************************************************************************/

    /*!
     * @brief   insertRows: Method to append either picklist or teleprompter list
     *          item name in the list.
     * @param   m_vectVRList: either picklist or teleprompter list data.
     * @return  void.
     */
    void insertRows(const std::vector<std::string>& m_vectVRList);

    /*!
     * @brief   removeRows: Method to clear either picklist or teleprompter list.
     * @param   void.
     * @return  void.
     */
    void removeRows();

private:
    /******************************************************//**
     * @category PROPERTIES
     *******************************************************/

    //! List to hold either picklist or teleprompter list item name.
    QStringList   m_objVRList;
};

#endif // CVRLISTMODEL_H
