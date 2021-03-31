/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
* @file          CPhoneBrowseTabBarModel.h
* @ingroup       HMIComponent
* @author        Rahul Balyan
* CPhoneBrowseTabBarModel,  Model for phone browse tab bar
**/

#ifndef CPHONEBROWSETABBARMODEL_H
#define CPHONEBROWSETABBARMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "CPhoneData.h"

/**
 * @brief CPhoneBrowseTabBarModel, Abstract list model class for phone browse tab bar,
 * It inherits QAbstractListModel class used to assign model to pathview present in tab bar of phone browse.
 */
class CPhoneBrowseTabBarModel : public QAbstractListModel
{
    Q_OBJECT

    /**
    * @brief CPhoneBrowseTabBarModel::EPhoneBrowseTabBarRoles is enum used to refer model values from QML.
    **/
    enum EPhoneBrowseTabBarRoles
    {
        TAB_BAR_COMPONENT_NAME_ROLE = Qt::UserRole + 1,
        TAB_BAR_COMPONENT_LEFT_ICON_ROLE,
        TAB_BAR_COMPONENT_MID_ICON_ROLE,
        TAB_BAR_COMPONENT_RIGHT_ICON_ROLE,
        TAB_BAR_COMPONENT_BROWSE_TYPE
    };

public:
    /**
    * @brief	CPhoneBrowseTabBarModel::CPhoneBrowseTabBarModel constructor for phone browse tab bar model.
    * @param	QObject.
    * @return	NA.
    **/
    CPhoneBrowseTabBarModel(QObject* pParent = nullptr);

    /**
    * @brief	CPhoneBrowseTabBarModel::CPhoneBrowseTabBarModel destructor for phone browse tab bar model.
    * @param	NA.
    * @return	NA.
    **/
    ~CPhoneBrowseTabBarModel();

    /**
    * @brief	CPhoneBrowseTabBarModel::rowCount function inherited from QAbstractListModel,
    *           Used to get row count.
    * @param	QModelIndex : The index is used to locate an item in the model.
    * @return	int : holds row count.
    **/
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

    /**
    * @brief	CPhoneBrowseTabBarModel::data function inherited from QAbstractListModel,
    *           Used to get data linked to given role and present at given index.
    * @param	(index)QModelIndex : The index is used to locate an item in the model.
    *           (role)int : holds the role name of data to be extract from QModelIndex item.
    * @return	QVariant : data stored under the given role for the item referred to by the index.
    **/
    QVariant data(const QModelIndex &iIndex, int iRole = Qt::DisplayRole) const override;

    /**
    * @brief	CPhoneBrowseTabBarModel::roleNames function inherited from QAbstractListModel,
    *           Used to get role names
    * @param	void.
    * @return	QHash<int, QByteArray> : holds model's role names
    **/
    QHash<int, QByteArray> roleNames() const override;

    /**
    * @brief	getBrowseType: Method to get browse type of the tab bar item.
    * @param	iItemIndex: Tab bar item index.
    * @return	Browse type of the tab bar item.
    **/
    int getBrowseType(int iItemIndex);

    /**
    * @brief	getBrowseItemIndex: Method to get tab bar browse item index.
    * @param	ePhoneBrowseType: Tab bar item browse type.
    * @return	tab bar browse itme index.
    **/
    int getBrowseItemIndex(CPhoneEnum::EPhoneBrowseType ePhoneBrowseType);

private:

    //! Phone Browse TabBar items list container
    QList<CPhoneData::SPhoneTabBarInfo> m_liPhoneBrowseTabBarList;
};

#endif // CPHONEBROWSETABBARMODEL_H
