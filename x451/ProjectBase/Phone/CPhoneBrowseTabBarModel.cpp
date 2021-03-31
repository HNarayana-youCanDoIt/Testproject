#include "CPhoneBrowseTabBarModel.h"
#include "logging.h"

CPhoneBrowseTabBarModel::CPhoneBrowseTabBarModel(QObject *parent)
    : QAbstractListModel(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);

    m_liPhoneBrowseTabBarList.clear();
    m_liPhoneBrowseTabBarList.append(CPhoneData::SPhoneTabBarInfo(tr("TEXT_PHONE_BROWSE_CALL_LOG"),
                                                                  "qrc:/image/PhoneBrowse/Ph_Ico_CallLogs_7in_n/Ph_Ico_CallLogs_n_LeftSide.png",
                                                                  "qrc:/image/PhoneBrowse/Ph_Ico_CallLogs_7in_n/Ph_Ico_CallLogs_na.png",
                                                                  "qrc:/image/PhoneBrowse/Ph_Ico_CallLogs_7in_n/Ph_Ico_CallLogs_n_RightSide.png",
                                                                  CPhoneEnum::PHONE_BROWSE_TYPE_CALL_LOGS));
    m_liPhoneBrowseTabBarList.append(CPhoneData::SPhoneTabBarInfo(tr("TEXT_PHONE_BROWSE_CONTACT"),
                                                                  "qrc:/image/PhoneBrowse/Ph_Ico_Contacts_7in_n/Ph_Ico_Contacts_n_LeftSide.png",
                                                                  "qrc:/image/PhoneBrowse/Ph_Ico_Contacts_7in_n/Ph_Ico_Contacts_na.png",
                                                                  "qrc:/image/PhoneBrowse/Ph_Ico_Contacts_7in_n/Ph_Ico_Contacts_n_RightSide.png",
                                                                  CPhoneEnum::PHONE_BROWSE_TYPE_CONTACTS));
    m_liPhoneBrowseTabBarList.append(CPhoneData::SPhoneTabBarInfo(tr("TEXT_PHONE_BROWSE_KEYPAD"),
                                                                  "qrc:/image/PhoneBrowse/Ph_Ico_Dialpad_7in_n/Ph_Btn_Numpad_n_LeftSide.png",
                                                                  "qrc:/image/PhoneBrowse/Ph_Ico_Dialpad_7in_n/Ph_Btn_Numpad_na.png",
                                                                  "qrc:/image/PhoneBrowse/Ph_Ico_Dialpad_7in_n/Ph_Btn_Numpad_n_RightSide.png",
                                                                  CPhoneEnum::PHONE_BROWSE_TYPE_DIALPAD));
    m_liPhoneBrowseTabBarList.append(CPhoneData::SPhoneTabBarInfo(tr("TEXT_PHONE_BROWSE_FAVORITES"),
                                                                  "qrc:/image/PhoneBrowse/Ph_Ico_Favorites_7in_n/Ph_Ico_Favorites_n_LeftSide.png",
                                                                  "qrc:/image/PhoneBrowse/Ph_Ico_Favorites_7in_n/Ph_Ico_Favorites_na.png",
                                                                  "qrc:/image/PhoneBrowse/Ph_Ico_Favorites_7in_n/Ph_Ico_Favorites_n_RightSide.png",
                                                                  CPhoneEnum::PHONE_BROWSE_TYPE_FAVORITES));
    m_liPhoneBrowseTabBarList.append(CPhoneData::SPhoneTabBarInfo(tr("TEXT_PHONE_BROWSE_FREQUENTLY_DIALED"),
                                                                  "qrc:/image/PhoneBrowse/Ph_Ico_FrequentlyCalled_na-assets/Ph_Ico_FrequentlyCalled_LeftSide.png",
                                                                  "qrc:/image/PhoneBrowse/Ph_Ico_FrequentlyCalled_na-assets/Ph_Ico_FrequentlyCalled_na.png",
                                                                  "qrc:/image/PhoneBrowse/Ph_Ico_FrequentlyCalled_na-assets/Ph_Ico_FrequentlyCalled_RightSide.png",
                                                                  CPhoneEnum::PHONE_BROWSE_TYPE_FREQUENTLY_DIALED));
}

CPhoneBrowseTabBarModel::~CPhoneBrowseTabBarModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    m_liPhoneBrowseTabBarList.clear();
}

int CPhoneBrowseTabBarModel::rowCount(const QModelIndex &parent) const
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "CPhoneBrowseTabBarModel::rowCount : %d ", m_liPhoneBrowseTabBarList.count());
    Q_UNUSED(parent)
    return m_liPhoneBrowseTabBarList.count();
}

QVariant CPhoneBrowseTabBarModel::data(const QModelIndex &iIndex, int iRole) const
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    QVariant objData = QVariant();
    int iRow = iIndex.row();
    if (iRow < 0 || iRow >=  m_liPhoneBrowseTabBarList.count())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"CPhoneBrowseTabBarModel::data, invalid row: %d", iRow);
    }
    else
    {
        switch(iRole)
        {
        case TAB_BAR_COMPONENT_NAME_ROLE:
            objData = m_liPhoneBrowseTabBarList[iRow].m_strName;
            break;
        case TAB_BAR_COMPONENT_LEFT_ICON_ROLE:
            objData = m_liPhoneBrowseTabBarList[iRow].m_strLeftIcon;
            break;
        case TAB_BAR_COMPONENT_MID_ICON_ROLE:
            objData = m_liPhoneBrowseTabBarList[iRow].m_strMidIcon;
            break;
        case TAB_BAR_COMPONENT_RIGHT_ICON_ROLE:
            objData = m_liPhoneBrowseTabBarList[iRow].m_strRightIcon;
            break;
        case TAB_BAR_COMPONENT_BROWSE_TYPE:
            objData = m_liPhoneBrowseTabBarList[iRow].m_ePhoneBrowseType;
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"CPhoneBrowseTabBarModel::data, invalid role: %d", iRole);
            break;
        }
    }
    return objData;
}

QHash<int, QByteArray> CPhoneBrowseTabBarModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[TAB_BAR_COMPONENT_NAME_ROLE] = "name";
    roles[TAB_BAR_COMPONENT_LEFT_ICON_ROLE] = "leftIcon";
    roles[TAB_BAR_COMPONENT_MID_ICON_ROLE] = "midIcon";
    roles[TAB_BAR_COMPONENT_RIGHT_ICON_ROLE] = "rightIcon";
    roles[TAB_BAR_COMPONENT_BROWSE_TYPE] = "browseType";
    return roles;
}

int CPhoneBrowseTabBarModel::getBrowseType(int iItemIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: item index: %d", __FUNCTION__, iItemIndex);
    return m_liPhoneBrowseTabBarList[iItemIndex].m_ePhoneBrowseType;
}

int CPhoneBrowseTabBarModel::getBrowseItemIndex(CPhoneEnum::EPhoneBrowseType ePhoneBrowseType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: ePhoneBrowseType: %d", __FUNCTION__, ePhoneBrowseType);
    int iItemIndex = -1;
    for(int iIndex = 0; iIndex < rowCount(); iIndex++)
    {
        if(m_liPhoneBrowseTabBarList[iIndex].m_ePhoneBrowseType == ePhoneBrowseType)
        {
            iItemIndex = iIndex;
            break;
        }
        else
        {
            //do nothing
        }
    }
    return iItemIndex;
}


