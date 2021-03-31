/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CVRHelpCommandListModel.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CVRHelpCommandListModel class that shall implement the
 * VR help command list data model which shall be used to update the VR help screen.
 */

#ifndef CVRHELPCOMMANDLISTMODEL_H
#define CVRHELPCOMMANDLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "CVREnum.h"

class CVRHelpCommandListModel : public QAbstractListModel
{
    Q_OBJECT
private:
    /************************************************************************//**
     * @category    ENUMS
     ************************************************************************/

    /*!
     * @enum    EVRHelpListRoles
     * @brief   This enum shall hold the values that shall be used by VR help qml
     *          screen to update the data in the view.
     */
    enum EVRHelpListRoles
    {
        VR_HELP_LIST_ITEM_TEXT_ROLE = Qt::UserRole + 1
    };

public:
    /**
     * @brief   CVRHelpCommandListModel: Constructor of CVRHelpCommandListModel.
     * @param   pParent: QObject pointer of parent class.
     * @return  NA.
     */
    CVRHelpCommandListModel(QObject* pParent = nullptr);

    /**
     * @brief   ~CVRHelpCommandListModel: Destructor of CVRHelpCommandListModel
     * @param   NA.
     * @return  NA.
     */
    ~CVRHelpCommandListModel();

    /************************************************************************//**
     * @category    OVERRIDEN METHODS of QAbstractListModel class
     ************************************************************************/
    int rowCount(const QModelIndex & objParent = QModelIndex()) const override;
    QVariant data(const QModelIndex & objIndex, int iRole = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    /************************************************************************//**
     * @category    EXTERNAL METHODS
     ************************************************************************/

    /**
     * @brief   insertRows: Method to append the pick list item name in the list.
     * @param   listHelpCommand: picklist data.
     * @return  void.
     */
    void insertRows(const QStringList& listHelpCommand);

    /**
     * @brief   removeRows: Method to clear the pick list.
     * @param   void.
     * @return  void.
     */
    void removeRows();

private:
    /******************************************************//**
     * @category PROPERTIES
     *******************************************************/

    //! List to hold the help command text.
    QStringList   m_listHelpCommand;
};

#endif // CVRHELPCOMMANDLISTMODEL_H
