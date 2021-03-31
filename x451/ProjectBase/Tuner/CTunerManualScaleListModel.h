/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CTunerManualScaleListModel.h
 * @ingroup       HMIComponent
 * @author        Rahul Balyan
 * CTunerManualScaleListModel, Abstract list model class for tuner manual scale's pathview
**/

#ifndef CTUNERMANUALSCALELISTMODEL_H
#define CTUNERMANUALSCALELISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "CTunerManualScaleData.h"

/**
 * @brief CTunerManualScaleListModel, Abstract list model class for tuner manual scale's pathview,
 * It inherits QAbstractListModel class used to assign model to pathview present in manual seek bar QML of tuner module.
 */
class CTunerManualScaleListModel : public QAbstractListModel
{
    Q_OBJECT

    /**
    * @brief CTunerManualScaleListModel::ETunerManualScaleRoles is enum used to refer model values from QML.
    **/
    enum ETunerManualScaleRoles
    {
        SCALE_HAND_FREQ_ROLE = Qt::UserRole + 1,
        SCALE_HAND_HEIGHT_ROLE
    };

public:
    /**
    * @brief	CTunerManualScaleListModel::CTunerManualScaleListModel constructor for tuner manual scale list model class CTunerManualScaleListModel.
    * @param	QObject.
    * @return	NA.
    **/
    CTunerManualScaleListModel(QObject* pParent = nullptr);

    /**
    * @brief	CTunerManualScaleListModel::CTunerManualScaleListModel destructor for tuner manual scale list model class CTunerManualScaleListModel.
    * @param	NA.
    * @return	NA.
    **/
    ~CTunerManualScaleListModel();

    /**
    * @brief	CTunerManualScaleListModel::rowCount function inherited from QAbstractListModel,
    *           Used to get row count.
    * @param	QModelIndex : The index is used to locate an item in the model.
    * @return	int : holds row count.
    **/
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

    /**
    * @brief	CTunerManualScaleListModel::data function inherited from QAbstractListModel,
    *           Used to get data linked to given role and present at given index.
    * @param	(index)QModelIndex : The index is used to locate an item in the model.
    *           (role)int : holds the role name of data to be extract from QModelIndex item.
    * @return	QVariant : data stored under the given role for the item referred to by the index.
    **/
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
    * @brief	CTunerManualScaleListModel::roleNames function inherited from QAbstractListModel,
    *           Used to get role names
    * @param	void.
    * @return	QHash<int, QByteArray> : holds model's role names
    **/
    QHash<int, QByteArray> roleNames() const override;

    /**
    * @brief	CTunerManualScaleListModel::insertRows function used to insert row in model.
    * @param	iIndex(int) : index data to be added in model.
    *           iHeight(int) : height data to be added in model
    * @return	void.
    **/
    void insertRows(SManualTuningScaleData *pSManualTuningScaleData);

    /**
    * @brief	CTunerManualScaleListModel::removeRows function used to remove rows from model.
    * @param	void.
    * @return	void.
    **/
    void removeRows();

private:

    /**  Model data list to hold model data */
    QList<SManualTuningScaleData *>    m_listTunerManualScale;
};

#endif // CTUNERMANUALSCALELISTMODEL_H
