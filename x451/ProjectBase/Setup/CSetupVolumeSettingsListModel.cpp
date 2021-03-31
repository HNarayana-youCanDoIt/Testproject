#include "CSetupVolumeSettingsListModel.h"

CSetupVolumeSettingsListModel::CSetupVolumeSettingsListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);

    m_pAudioAdaptor = CAudioAdaptor::getInstance();

    //FixMe: Change the model according to TATA, after finalised in service
    m_VolumeSetupDataList.clear();
    m_VolumeSetupDataList.append(new CSetupData(tr("TEXT_VOLUME_SETTING_SPEED_DEPENDENT_VOLUME"), CSetupEnums::SETUP_LIST_ITEM_CHECK_BOX/*"LabelwithCheckbox"*/, /*Checked/Unchecked*/false, 0, CSetupEnums::SETUP_SCREEN_INVALID));
    m_VolumeSetupDataList.append(new CSetupData(tr("TEXT_VOLUME_SETTING_START_UP"), "","",CSetupEnums::SETUP_LIST_ITEM_SLIDER /*"LabelwithSlider" */ , true, 0, false, -1, /*minValue*/ 5, /*maxValue*/ 20));
    m_VolumeSetupDataList.append(new CSetupData(tr("TEXT_VOLUME_SETTING_PHONE_CALL_VOLUME"), "qrc:/image/Setup/Sts_Ico_Volume_7in_n-assets/Set_Ico_CallVolume_7in_n-assets/Set_Ico_CallVolume_7in_n.png","",CSetupEnums::SETUP_LIST_ITEM_ICON_SLIDER/*"LabelwithSlider"*/  , true, 0, false, -1,  /*minValue*/ 0, /*maxValue*/ 30));
    m_VolumeSetupDataList.append(new CSetupData(tr("TEXT_VOLUME_SETTING_NOTIFICATION_VOLUME"), "qrc:/image/Setup/Sts_Ico_Volume_7in_n-assets/Set_Ico_NotificationVolume2_7in_n-assets/Set_Ico_NotificationVolume2_7in_n.png","",CSetupEnums::SETUP_LIST_ITEM_ICON_SLIDER /*"LabelwithSlider" */, true, 0, false, -1, /*minValue*/ 0, /*maxValue*/ 30));

    connect(m_pAudioAdaptor, SIGNAL(sigSpeedDependantVolumeChanged()), this, SLOT(sltSpeedDependantVolumeChanged()));
    connect(m_pAudioAdaptor, SIGNAL(sigStartUpVolumeChanged()), this, SLOT(sltStartUpVolumeChanged()));
    connect(m_pAudioAdaptor, SIGNAL(sigPhoneCallVolumeChanged()), this, SLOT(sltPhoneCallVolumeChanged()));
    connect(m_pAudioAdaptor, SIGNAL(sigVoiceAlertVolumeChanged()), this, SLOT(sltVoiceAlertVolumeChanged()));
}

CSetupVolumeSettingsListModel::~CSetupVolumeSettingsListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    qDeleteAll(m_VolumeSetupDataList.begin(), m_VolumeSetupDataList.end());
    m_VolumeSetupDataList.clear();
}

int CSetupVolumeSettingsListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "CSetupVolumeSettingsListModel::rowCount : %d ", m_VolumeSetupDataList.count());
    return m_VolumeSetupDataList.count();
}

QVariant CSetupVolumeSettingsListModel::data(const QModelIndex &index, int role) const
{
    QVariant data = QVariant();
    int row = index.row();
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: role: %d, row: %d", __FUNCTION__, role, row);
    if (row < 0 || row >= rowCount())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"CSetupVolumeSettingsListModel::data, invalid row: %d", row);
    }
    else
    {
        switch(role)
        {
        case ListItemIndexRole:
            data = m_VolumeSetupDataList[row]->m_eListItemIndex;
            break;
        case ListItemDefaultImageRole:
            data = m_VolumeSetupDataList[row]->m_sListItemDefaultImage;
            break;
        case ListItemNameRole:
            data = m_VolumeSetupDataList[row]->m_sListItemName;
            break;
        case ListItemTypeRole:
            data = m_VolumeSetupDataList[row]->m_sListItemType;
            break;
        case ListItemValueRole:
            data = m_VolumeSetupDataList[row]->m_iListItemValue;
            break;
        case ListItemCheckedRole:
            data = m_VolumeSetupDataList[row]->m_bListItemChecked;
            break;
         case ListItemMinValue:
            data = m_VolumeSetupDataList[row]->m_iListItemMinValue;
            break;
        case ListItemMaxValue:
            data = m_VolumeSetupDataList[row]->m_iListItemMaxValue;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"CSetupVolumeSettingsListModel::data, invalid role: %d", role);
            break;
        }
    }
    return data;

}

QHash<int, QByteArray> CSetupVolumeSettingsListModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[ListItemIndexRole] = "listItemIndexRole";
    roles[ListItemNameRole] = "listItemNameRole";
    roles[ListItemTypeRole] = "listItemTypeRole";
    roles[ListItemValueRole]   = "listItemValueRole";
    roles[ListItemCheckedRole] = "listItemCheckedRole";
    roles[ListItemMinValue] = "listItemMinValue";
    roles[ListItemMaxValue] = "listItemMaxValue";
    roles[ListItemDefaultImageRole] = "listItemDefaultImageRole";
    return roles;
}

void CSetupVolumeSettingsListModel::sltSpeedDependantVolumeChanged()
{
    bool speedDependentVolume = m_pAudioAdaptor->speedDependantVolume();
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Speed Dependant Volume :%d ", __FUNCTION__, speedDependentVolume );
    m_VolumeSetupDataList[CSetupEnums::VOLUME_SPEED_DEPENDENT]->m_bListItemChecked = speedDependentVolume;

    /* Refreshing the qml's data for the index which is changed */
    QModelIndex left = createIndex(CSetupEnums::VOLUME_SPEED_DEPENDENT, 0);
    QModelIndex right = createIndex(CSetupEnums::VOLUME_SPEED_DEPENDENT, 0);
    emit dataChanged(left, right);
}

void CSetupVolumeSettingsListModel::sltStartUpVolumeChanged()
{
    int startUpVolume = m_pAudioAdaptor->startUpVolume();
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "CSetupBMTListModel::sltStartUpVolumeChanged : %d ", startUpVolume );
    m_VolumeSetupDataList[CSetupEnums::VOLUME_START_UP]->m_iListItemValue = startUpVolume;
    m_VolumeSetupDataList[CSetupEnums::VOLUME_START_UP]->m_bListItemChecked = true;

    /* Refreshing the qml's data for the index which is changed */
    QModelIndex left = createIndex(CSetupEnums::VOLUME_START_UP, 0);
    QModelIndex right = createIndex(CSetupEnums::VOLUME_START_UP, 0);
    emit dataChanged(left, right);
}

void CSetupVolumeSettingsListModel::sltPhoneCallVolumeChanged()
{
    int phoneCallVolume = m_pAudioAdaptor->phoneCallVolume();
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Phone Call Volume: %d ",__FUNCTION__, phoneCallVolume );
    m_VolumeSetupDataList[CSetupEnums::VOLUME_PHONE_CALL]->m_iListItemValue = phoneCallVolume;
    m_VolumeSetupDataList[CSetupEnums::VOLUME_PHONE_CALL]->m_bListItemChecked = true;

    /* Refreshing the qml's data for the index which is changed */
    QModelIndex left = createIndex(CSetupEnums::VOLUME_PHONE_CALL, 0);
    QModelIndex right = createIndex(CSetupEnums::VOLUME_PHONE_CALL, 0);
    emit dataChanged(left, right);
}

void CSetupVolumeSettingsListModel::sltVoiceAlertVolumeChanged()
{
    int voiceAlertVolume = m_pAudioAdaptor->voiceAlertVolume();
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Phone Call Volume: %d ",__FUNCTION__, voiceAlertVolume );
    m_VolumeSetupDataList[CSetupEnums::VOLUME_VOICE_ALERTS]->m_iListItemValue = voiceAlertVolume;
    m_VolumeSetupDataList[CSetupEnums::VOLUME_VOICE_ALERTS]->m_bListItemChecked = true;

    /* Refreshing the qml's data for the index which is changed */
    QModelIndex left = createIndex(CSetupEnums::VOLUME_VOICE_ALERTS, 0);
    QModelIndex right = createIndex(CSetupEnums::VOLUME_VOICE_ALERTS, 0);
    emit dataChanged(left, right);
}
