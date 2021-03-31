/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
* @file          CHomeConfigureFavHKModel.h
* @ingroup       HMIComponent
* @author        Rahul Balyan
* CHomeConfigureFavHKModel,  Model for configure fav HK screen
**/

#ifndef CHOMECONFIGUREFAVHKMODEL_H
#define CHOMECONFIGUREFAVHKMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "CHomeConfigureFavHKData.h"

/**
 * @brief CHomeConfigureFavHKModel, Abstract list model class for configure fav HK screen,
 * It inherits QAbstractListModel class used to assign model to list present in configure fav HK screen.
 */
class CHomeConfigureFavHKModel : public QAbstractListModel
{
    Q_OBJECT

    /**
    * @brief CHomeConfigureFavHKModel::EHomeConfigureFavHKRoles is enum used to refer model values from QML.
    **/
    enum EHomeConfigureFavHKRoles
    {
        FAV_HK_ID = Qt::UserRole + 1,
        FAV_HK_SHORTCUT_ID
    };

public:
    /**
    * @brief	CHomeConfigureFavHKModel::CHomeConfigureFavHKModel constructor for configure fav HK list model.
    * @param	QObject.
    * @return	NA.
    **/
    CHomeConfigureFavHKModel(QObject* pParent = nullptr);

    /**
    * @brief	CHomeConfigureFavHKModel::CHomeConfigureFavHKModel destructor for configure fav HK list model.
    * @param	NA.
    * @return	NA.
    **/
    ~CHomeConfigureFavHKModel();

    /**
    * @brief	CHomeConfigureFavHKModel::rowCount function inherited from QAbstractListModel,
    *           Used to get row count.
    * @param	QModelIndex : The index is used to locate an item in the model.
    * @return	int : holds row count.
    **/
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

    /**
    * @brief	CHomeConfigureFavHKModel::data function inherited from QAbstractListModel,
    *           Used to get data linked to given role and present at given index.
    * @param	(index)QModelIndex : The index is used to locate an item in the model.
    *           (role)int : holds the role name of data to be extract from QModelIndex item.
    * @return	QVariant : data stored under the given role for the item referred to by the index.
    **/
    QVariant data(const QModelIndex &iIndex, int iRole = Qt::DisplayRole) const override;

    /**
    * @brief	CHomeConfigureFavHKModel::roleNames function inherited from QAbstractListModel,
    *           Used to get role names
    * @param	void.
    * @return	QHash<int, QByteArray> : holds model's role names
    **/
    QHash<int, QByteArray> roleNames() const override;

    /**
    * @brief	CHomeConfigureFavHKModel::insertRows function used to insert row in model.
    * @param	iIndex(int) : index data to be added in model.
    *           iHeight(int) : height data to be added in model
    * @return	void.
    **/
    void insertRows(SConfigureFavHKData *pSConfigureFavHKData);

    /**
    * @brief	CHomeConfigureFavHKModel::removeRows function used to remove rows from model.
    * @param	void.
    * @return	void.
    **/
    void removeRows();

private:

    /* configure fav HK items list container */
    QList<SConfigureFavHKData*> m_liConfigureFavHKList;
};

#endif // CHOMECONFIGUREFAVHKMODEL_H
