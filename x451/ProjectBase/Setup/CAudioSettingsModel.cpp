/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CAudioSettingsModel.h
 * @ingroup       HMIComponent
 * @author        Gaurav Garg
 * CAudioSettingsModel.h, audio settings list model file, responsible for creating audio settings static list model
 */
#include "CAudioSettingsModel.h"
#include "logging.h"

/* Here We have Used Duplicate Items in order to make the path circular in pathview used in AudioSettings.qml */

CAudioSettingsModel::CAudioSettingsModel(QObject *pParent)
     :QAbstractListModel(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);
    m_objAudioSetupDataList.clear();
    m_objAudioSetupDataList.append(CSetupData(tr("TEXT_AUDIO_SETTINGS_AUDIO_PRESETS"), "qrc:/image/Setup/Set_Ico_AudioPresets_7in_n-assets/Set_Ico_AudioPresets_LeftSide.png", "qrc:/image/Setup/Set_Ico_AudioPresets_7in_n-assets/Set_Ico_AudioPresets_na.png", "qrc:/image/Setup/Set_Ico_AudioPresets_7in_n-assets/Set_Ico_AudioPresets_n_RightSide.png" ));
    m_objAudioSetupDataList.append(CSetupData(tr("TEXT_AUDIO_SETTINGS_BALANCE_FADER"), "qrc:/image/Setup/Set_Ico_Balance_Fader_7in_n-assets/Set_Ico_Balance_Fader_LeftSide.png", "qrc:/image/Setup/Set_Ico_Balance_Fader_7in_n-assets/Set_Ico_Balance_Fader_na.png", "qrc:/image/Setup/Set_Ico_Balance_Fader_7in_n-assets/Set_Ico_Balance_Fader_n_RightSide.png"));
    m_objAudioSetupDataList.append(CSetupData(tr("TEXT_AUDIO_SETTINGS_AUDIO_PRESETS"), "qrc:/image/Setup/Set_Ico_AudioPresets_7in_n-assets/Set_Ico_AudioPresets_LeftSide.png", "qrc:/image/Setup/Set_Ico_AudioPresets_7in_n-assets/Set_Ico_AudioPresets_na.png", "qrc:/image/Setup/Set_Ico_AudioPresets_7in_n-assets/Set_Ico_AudioPresets_n_RightSide.png" ));
    m_objAudioSetupDataList.append(CSetupData(tr("TEXT_AUDIO_SETTINGS_BALANCE_FADER"), "qrc:/image/Setup/Set_Ico_Balance_Fader_7in_n-assets/Set_Ico_Balance_Fader_LeftSide.png", "qrc:/image/Setup/Set_Ico_Balance_Fader_7in_n-assets/Set_Ico_Balance_Fader_na.png", "qrc:/image/Setup/Set_Ico_Balance_Fader_7in_n-assets/Set_Ico_Balance_Fader_n_RightSide.png"));
}

CAudioSettingsModel::~CAudioSettingsModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);

}

int CAudioSettingsModel::rowCount(const QModelIndex &parent) const
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, rowCount : %d ",__FUNCTION__, m_objAudioSetupDataList.count());
    Q_UNUSED(parent)
    return m_objAudioSetupDataList.count();
}

QVariant CAudioSettingsModel::data(const QModelIndex &iIndex, int iRole) const
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    QVariant objData = QVariant();
    int iRow = iIndex.row();
    if (iRow < 0 || iRow >=  m_objAudioSetupDataList.count())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, invalid row: %d",__FUNCTION__, iRow);
    }
    else
    {
        switch(iRole)
        {
        case TAB_BAR_COMPONENT_NAME_ROLE:
            objData = m_objAudioSetupDataList[iRow].m_strName;
            break;
        case TAB_BAR_COMPONENT_LEFT_ICON_ROLE:
            objData = m_objAudioSetupDataList[iRow].m_strLeftIcon;
            break;
        case TAB_BAR_COMPONENT_MID_ICON_ROLE:
            objData = m_objAudioSetupDataList[iRow].m_strMidIcon;
            break;
        case TAB_BAR_COMPONENT_RIGHT_ICON_ROLE:
            objData = m_objAudioSetupDataList[iRow].m_strRightIcon;
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"CAudioSettingsModel::data, invalid role: %d", iRole);
            break;
        }
    }
    return objData;
}

QHash<int, QByteArray> CAudioSettingsModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[TAB_BAR_COMPONENT_NAME_ROLE] = "name";
    roles[TAB_BAR_COMPONENT_LEFT_ICON_ROLE] = "leftIcon";
    roles[TAB_BAR_COMPONENT_MID_ICON_ROLE] = "midIcon";
    roles[TAB_BAR_COMPONENT_RIGHT_ICON_ROLE] = "rightIcon";
    return roles;
}
