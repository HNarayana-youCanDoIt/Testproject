/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2019
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CSoundDemoModel.h
* @ingroup      HMIComponent
* @author       Guru Alingal
* @brief        Model for sound demo list.
*/

#ifndef CSOUNDDEMOMODEL_H
#define CSOUNDDEMOMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "CSoundDemoData.h"

class CSoundDemoModel : public QAbstractListModel
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
    /**
     * @brief The ESoundDemoListRoles enum the
     */
    enum ESoundDemoListRoles
    {

        ITEM_ID_ROLE            = Qt::UserRole + 1,
        ITEM_TRACKID_ROLE       ,
        ITEM_CAPTION_ROLE       ,
        ITEM_IMAGE_ROLE         ,
        ITEM_MIN_VAL_ROLE       ,
        ITEM_CURR_VAL_ROLE      ,
        ITEM_MAX_VAL_ROLE       ,
        ITEM_ACTIVE_ROLE        ,
        ITEM_ENABLED_ROLE       ,
        ITEM_PGBVISIBILITY_ROLE ,
    };

    CSoundDemoModel(QObject *pParent = nullptr);
    ~CSoundDemoModel();

    /** *************************************************************
     * @category  OVERRIDEN METHODS of QAbstractListModel class
     **************************************************************/
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

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
    void insertRows(const SSoundDemoData &rowData);

    /**
     * @brief updateRowData Method to update the values of any role
     * @param index - Index of the data to be updated
     * @param value - New value to be set
     * @param role - Role that needs to be updated.
     * @return true if data updated else false
     */
    virtual bool updateRowData(int index, const QVariant &value, int role);

private:

    /** *************************************************************
     * @category   PROPERTIES
     **************************************************************/
    /**
     * @brief List to hold the Media Browse Item Data
     */
    QList<SSoundDemoData> m_listData;

};

#endif // CSOUNDDEMOMODEL_H
