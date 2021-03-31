/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CMediaBrowseListModel.h
* @ingroup      HMIComponent
* @author       Rahul Madan
* @brief        This file contains CMediaBrowseListModel class that shall implement the
*               Media Browse list data model that shall be used to update the media browse screen for all the sources
*/
#ifndef CMEDIABROWSELISTMODEL_H
#define CMEDIABROWSELISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "CMediaData.h"

/**
 * @class CMediaBrowseListModel
 * @brief This class implements the Media Browse list data model that shall
 *        be used to update the media browse screen for all the sources
 */
class CMediaBrowseListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    /** *************************************************************
     * @category  ENUMS
     **************************************************************/
    /*!
     * @enum    EMediaBrowseListRoles
     * @brief   This enum shall hold the values that shall be used by Media Browse
     *          qml screen to update the data in the view.
     */
    enum EMediaBrowseListRoles
    {
        ITEM_IMAGE_ROLE = Qt::UserRole + 1,
        ITEM_NAME_ROLE,
        ITEM_METADATA_TYPE,
    };

    CMediaBrowseListModel(QObject *pParent = nullptr);
    ~CMediaBrowseListModel();

    /** *************************************************************
     * @category  OVERRIDEN METHODS of QAbstractListModel class
     **************************************************************/
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int,QByteArray> roleNames() const override;


    /** *************************************************************
     * @category  Internal Methods
     **************************************************************/
    /*!
     * @brief   Method to clear the media browse list.
     * @param   void.
     * @return  void.
     */
    void removeRows();

    /*!
     * @brief   Method to append the browse category items into the list.
     * @param   const QString &strItemText - Browse Item Text
     * @param   const QString &strItemImage - Browse Item Image
     * @return  void.
     */
    void insertRows(const QString &strItemText, const QString &strItemImage, const CMediaEnum::EMediaBrowseItem eMetadataType);

    /**
     * @brief getName   Method to get the value in name role
     * @param iIndex    index of the data
     * @return
     */
    QString getName(int iIndex);

private:

    /** *************************************************************
     * @category   PROPERTIES
     **************************************************************/
    /**
     * @list m_listBrowse
     * @brief List to hold the Media Browse Item Data
     */
    QList<SBrowseItemData> m_listBrowse;
};

#endif // CMEDIABROWSELISTMODEL_H
