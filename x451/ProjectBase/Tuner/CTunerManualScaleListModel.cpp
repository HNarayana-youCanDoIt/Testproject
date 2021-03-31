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

#include "CTunerManualScaleListModel.h"
#include "logging.h"

CTunerManualScaleListModel::CTunerManualScaleListModel(QObject *pParent) :
    QAbstractListModel(pParent)
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    m_listTunerManualScale.clear();
    endRemoveRows();
}

CTunerManualScaleListModel::~CTunerManualScaleListModel()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    m_listTunerManualScale.clear();
    endRemoveRows();
}

QHash<int, QByteArray> CTunerManualScaleListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[SCALE_HAND_FREQ_ROLE] = "scaleHandFreqRole";
    roles[SCALE_HAND_HEIGHT_ROLE] = "scaleHandHeightRole";
    return roles;
}

QVariant CTunerManualScaleListModel::data(const QModelIndex &index, int role) const
{
    QVariant objDeviceName;
    if (index.row() >= 0 || index.row() < m_listTunerManualScale.count())
    {
        if(role == SCALE_HAND_FREQ_ROLE)
        {
            objDeviceName = m_listTunerManualScale[index.row()]->m_iScaleIndexFreqValue;
        }
        else if(role == SCALE_HAND_HEIGHT_ROLE)
        {
            objDeviceName = m_listTunerManualScale[index.row()]->m_iScaleIndexHeight;
        }
        else
        {}
    }
    else
    {}
    return objDeviceName;
}

int CTunerManualScaleListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listTunerManualScale.count();
}

void CTunerManualScaleListModel::removeRows()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    m_listTunerManualScale.clear();
    endRemoveRows();
}

void CTunerManualScaleListModel::insertRows(SManualTuningScaleData *pSManualTuningScaleData)
{
    beginInsertRows(QModelIndex() , m_listTunerManualScale.count(), m_listTunerManualScale.count());
    m_listTunerManualScale << pSManualTuningScaleData;
    endInsertRows();
}
