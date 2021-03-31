/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CHomeUpdateShortcutModel.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CHomeUpdateShortcutModel, a model class for Update-Shortcut-List of Home module,
 * CHomeUpdateShortcutModel inherits QAbstractListModel class used to assign model to ListModel present in Update-Shortcut-List QML of Home module.
 */

#ifndef CHOMEUPDATESHORTCUTMODEL_H
#define CHOMEUPDATESHORTCUTMODEL_H

#include <QAbstractListModel>
#include <QList>

/**
 * @brief CHomeUpdateShortcutModel, a model class for Update-Shortcut-List of Home module,
 * It inherits QAbstractListModel class used to assign model to ListModel present in Update-Shortcut-List QML of Home module.
 */
class CHomeUpdateShortcutModel: public QAbstractListModel
{
    Q_OBJECT

public:
    //________________________________________________________________________________________________
    /**
    * @brief CHomeUpdateShortcutModel::ModelRoles is enum used to refer model values from QML.
    **/
    enum ModelRoles
    {
        shortcutIdRole = Qt::UserRole + 1,
    };
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeUpdateShortcutModel::CHomeUpdateShortcutModel constructor for Home Shortcut Model class CHomeUpdateShortcutModel.
    * @param	QObject.
    * @return	NA.
    **/
    CHomeUpdateShortcutModel(QObject *parent = nullptr);
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeUpdateShortcutModel::rowCount function inherited from QAbstractListModel,
    *           Used to get row count.
    * @param	QModelIndex.
    * @return	int.
    **/
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeUpdateShortcutModel::data function inherited from QAbstractListModel,
    *           Used to get data linked to given role and present at given index.
    * @param	QModelIndex, int.
    * @return	QVariant.
    **/
    QVariant data(const QModelIndex & objModelIndex, int iRole = Qt::DisplayRole) const;
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeUpdateShortcutModel::addItem function used to add row count.
    * @param	QModelIndex.
    * @return	void.
    **/
    void addItem(const int &iShortcutData);
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeUpdateShortcutModel::rowCount function used to clear model.
    * @param	void.
    * @return	void.
    **/
    void clearList();
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeUpdateShortcutModel::shortcutDataList function used to get model data list.
    * @param	void.
    * @return	QList<int>.
    **/
    QList<int> shortcutDataList() const;
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeUpdateShortcutModel::setModeDataList function used to set model data list.
    * @param	QList<int>.
    * @return	void.
    **/
    void setModeDataList(const QList<int> &ModeDataList);

protected:
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeUpdateShortcutModel::roleNames function inherited from QAbstractListModel,
    *           Used to get role names
    * @param	void.
    * @return	QHash<int, QByteArray>.
    **/
    QHash<int, QByteArray> roleNames() const;

private:
    QList<int> m_liShortcutIDList;  //  Model data list to hold shortcut data
};

#endif // CHOMEUPDATESHORTCUTMODEL_H
