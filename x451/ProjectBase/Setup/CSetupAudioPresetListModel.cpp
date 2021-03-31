/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CSetupAudioPresetListModel.cpp
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * CSetupAudioPresetListModel.cpp, audio preset list model class cpp file, responsible for creating audio preset static list model
 */

#include "CSetupAudioPresetListModel.h"

CSetupAudioPresetListModel::CSetupAudioPresetListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);

    m_pAudioAdaptor = CAudioAdaptor::getInstance();

    //FixMe: Change the model according to TATA, after finalised in service
    m_AudioPresetSetupDataList.clear();
    m_AudioPresetSetupDataList.append(new CSetupData(tr("TEXT_AUDIO_PRESET_FLAT"), CSetupEnums::SETUP_LIST_ITEM_LABEL, false, false, -1));
    m_AudioPresetSetupDataList.append(new CSetupData(tr("TEXT_AUDIO_PRESET_ROCK"), CSetupEnums::SETUP_LIST_ITEM_LABEL, false, false, -1));
    m_AudioPresetSetupDataList.append(new CSetupData(tr("TEXT_AUDIO_PRESET_POP"), CSetupEnums::SETUP_LIST_ITEM_LABEL, false, false, -1));
    m_AudioPresetSetupDataList.append(new CSetupData(tr("TEXT_AUDIO_PRESET_JAZZ"), CSetupEnums::SETUP_LIST_ITEM_LABEL, false, false, -1));
    m_AudioPresetSetupDataList.append(new CSetupData(tr("TEXT_AUDIO_PRESET_CLASSIC"), CSetupEnums::SETUP_LIST_ITEM_LABEL, false, false, -1));
    m_AudioPresetSetupDataList.append(new CSetupData(tr("TEXT_AUDIO_PRESET_SPEECH"), CSetupEnums::SETUP_LIST_ITEM_LABEL, false, false, -1));
    m_AudioPresetSetupDataList.append(new CSetupData(tr("TEXT_AUDIO_PRESET_USER"), CSetupEnums::SETUP_LIST_ITEM_LABEL, false, false, -1));
}

CSetupAudioPresetListModel::~CSetupAudioPresetListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    qDeleteAll(m_AudioPresetSetupDataList.begin(), m_AudioPresetSetupDataList.end());
    m_AudioPresetSetupDataList.clear();
}

int CSetupAudioPresetListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "CSetupAudioPresetListModel::rowCount : %d ", m_AudioPresetSetupDataList.count());
    return m_AudioPresetSetupDataList.count();
}

QVariant CSetupAudioPresetListModel::data(const QModelIndex &index, int role) const
{
    QVariant data = QVariant();
    int row = index.row();
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: role: %d, row: %d", __FUNCTION__, role, row);
    if (row < 0 || row >= rowCount())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"CSetupAudioPresetListModel::data, invalid row: %d", row);
    }
    else
    {
        switch(role)
        {
        case ListItemIndexRole:
            data = m_AudioPresetSetupDataList[row]->m_eListItemIndex;
            break;
        case ListItemNameRole:
            data = m_AudioPresetSetupDataList[row]->m_sListItemName;
            break;
        case ListItemTypeRole:
            data = m_AudioPresetSetupDataList[row]->m_sListItemType;
            break;
        case ListItemCheckedRole:
            data = m_AudioPresetSetupDataList[row]->m_bListItemChecked;
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"CSetupAudioPresetListModel::data, invalid role: %d", role);
            break;
        }
    }
    return data;
}

QHash<int, QByteArray> CSetupAudioPresetListModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[ListItemIndexRole] = "listItemIndexRole";
    roles[ListItemNameRole] = "listItemNameRole";
    roles[ListItemTypeRole] = "listItemTypeRole";
    roles[ListItemCheckedRole] = "listItemCheckedRole";
    return roles;
}

const QString CSetupAudioPresetListModel::getAudioPresetName(CAudioEnums::EAudioPresets eAudioPresets)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO," %s eAudioPresets is: %d",__FUNCTION__, eAudioPresets);
    QString strAudioPresetName = "";
    if((eAudioPresets >= 0) && (eAudioPresets < m_AudioPresetSetupDataList.size()))
    {
        strAudioPresetName =  m_AudioPresetSetupDataList.at(eAudioPresets)->m_sListItemName;
    }
    else
    {
        //do nothing
    }
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO," %s AudioPresetName: %s",__FUNCTION__, strAudioPresetName.toStdString().c_str());
    return strAudioPresetName;
}
