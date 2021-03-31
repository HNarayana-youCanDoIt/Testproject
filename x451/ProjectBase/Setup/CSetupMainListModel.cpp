/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CSetupMainListModel.cpp
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * CSetupMainListModel.cpp, setup main list model class cpp file, responsible for creating setup main static list model
 */

#include "CSetupMainListModel.h"
#include "CVehicleSettingsAdaptor.h"
#include "CParkAssistAdaptor.h"
#include "CSetupAdaptor.h"
#include "CHVACAdaptor.h"
#include "CAppleCarPlayAdaptor.h"
#include "CVoiceAlertsAdaptor.h"

CSetupMainListModel::CSetupMainListModel(QObject *parent):
    QAbstractListModel(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    initMainSetupList();
    connect(CVehicleSettingsAdaptor::getInstance(), SIGNAL(sigBCMPresenceChanged()), this, SLOT(sltHandleVehicleSetupPresence()), Qt::QueuedConnection);
    connect(CVehicleSettingsAdaptor::getInstance(), SIGNAL(sigBcmUcsStateChanged()), this, SLOT(sltHandleVehicleSetupPresence()), Qt::QueuedConnection);
    connect(CParkAssistAdaptor::getInstance(), SIGNAL(sigPdcPresenceChanged()), this, SLOT(sltHandleVehicleSetupPresence()), Qt::QueuedConnection);
    connect(CHVACAdaptor::getInstance(), SIGNAL(sigCCMPresenceChanged()), this, SLOT(sltHandleVehicleSetupPresence()), Qt::QueuedConnection);
    connect(CAppleCarPlayAdaptor::getInstance(), SIGNAL(sigAppleCarPlayConnectionStatusChanged(bool)), this, SLOT(sltCPConnectionStatusUpdated(bool)), Qt::QueuedConnection);
    connect(&CVoiceAlertsAdaptor::getInstance(), SIGNAL(sigVoiceAlertPresenceChanged()), this, SLOT(sltHandleVehicleSetupPresence()), Qt::QueuedConnection);

    connect(&(CPowerModeAdaptor::getInstance()), SIGNAL(sigPowerModeChanged()), this, SLOT(sltPowerModeChanged()), Qt::QueuedConnection);

    sltHandleVehicleSetupPresence();
}

CSetupMainListModel::~CSetupMainListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    qDeleteAll(m_SetupDataList.begin(), m_SetupDataList.end());
    m_SetupDataList.clear();
}

int CSetupMainListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "CSetupMainListModel::rowCount : %d ", m_SetupDataList.count());
    return m_SetupDataList.count();
}

QVariant CSetupMainListModel::data(const QModelIndex &index, int role) const
{
    QVariant data = QVariant();
    int row = index.row();
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "CSetupMainListModel::data : %d %d ", row, rowCount());
    if (row < 0 || row >= rowCount())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"CSetupMainListModel::data, invalid row: %d", row);
    }
    else
    {
        switch(role)
        {
        case ListItemIndexRole:
            data = m_SetupDataList[row]->m_eListItemIndex;
            break;
        case ListItemNameRole:
            data = m_SetupDataList[row]->m_sListItemName;
            break;
        case ListItemTypeRole:
            data = m_SetupDataList[row]->m_sListItemType;
            break;
        case ListItemCheckedRole:
            data = m_SetupDataList[row]->m_bListItemChecked;
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"CSetupMainListModel::data, invalid role: %d", role);
            break;
        }
    }
    return data;
}

QHash<int, QByteArray> CSetupMainListModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[ListItemIndexRole] = "listItemIndexRole";
    roles[ListItemNameRole] = "listItemNameRole";
    roles[ListItemTypeRole] = "listItemTypeRole";
    roles[ListItemCheckedRole] = "listItemCheckedRole";
    roles[ListItemEnumsRole] = "listItemEnumRole";
    return roles;
}

void CSetupMainListModel::initMainSetupList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: bcm_presence: %d", __FUNCTION__, CVehicleSettingsAdaptor::getInstance()->bCmPresence());
    beginInsertRows(QModelIndex(), m_SetupDataList.count(), m_SetupDataList.count());
    m_SetupDataList.append(new CSetupData(tr("TEXT_SETTINGS_AUDIO_SETUP"), CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE, true, CSetupEnums::SETUP_AUDIO, CSetupEnums::SETUP_SCREEN_AUDIO ));
    m_SetupDataList.append(new CSetupData(tr("TEXT_SETTINGS_PHONE_SETUP"), CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE, true, CSetupEnums::SETUP_BLUETOOTH, CSetupEnums::SETUP_SCREEN_BLUETOOTH ));
    m_SetupDataList.append(new CSetupData(tr("TEXT_SETTINGS_VOLUME_SETUP"), CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE, true, CSetupEnums::SETUP_VOLUME, CSetupEnums::SETUP_SCREEN_VOLUME ));
    m_SetupDataList.append(new CSetupData(tr("TEXT_SETTINGS_GENERAL_SETUP"), CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE, true, CSetupEnums::SETUP_GENERAL, CSetupEnums::SETUP_SCREEN_GENERAL ));
    m_SetupDataList.append(new CSetupData(tr("TEXT_SETTINGS_THEMES"), CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE, true, CSetupEnums::SETUP_THEMES, CSetupEnums::SETUP_SCREEN_THEMES ));
    m_SetupDataList.append(new CSetupData(tr("TEXT_SETTINGS_SOFTWARE_DETAILS"), CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE, true, CSetupEnums::SETUP_SOFTWARE_DETAILS, CSetupEnums::SETUP_SCREEN_SOFTWARE_UPDATE));
    m_SetupDataList.append(new CSetupData(tr("TEXT_SETTINGS_ABOUT_MENU"), CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE, true, CSetupEnums::SETUP_ABOUT, CSetupEnums::SETUP_SCREEN_ABOUT_MENU));
    endInsertRows();
}


void CSetupMainListModel::sltHandleVehicleSetupPresence()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    /*
     * This logic is to check bcm presence and show vehicle setup in the main setup list, if it
     * is not available in list.
     * If bcm not present, then remove Vehicle Setup item from
     * Main setup list, if it is present in list.
     * Here we checking the list size empty and list size greater than or equal to 2 to avoid crash.
     * ToDo: There should be one more check for voice alert presence.
     */
    if (!m_SetupDataList.empty() && m_SetupDataList.size() >= 2)
    {
        //Here we are getting the vehicle setup item present at index 1
        CSetupData* pSetupData = m_SetupDataList.at(0);

        if(pSetupData)
        {
           if(CSetupAdaptor::getInstance()->isVehicleSettingAvailable())
           {
               /*
                * Insert Vehicle Setup Item in list.
                */
               if (CSetupEnums::SETUP_SCREEN_VEHICLE != pSetupData->m_eListItemIndex)
               {
                   beginInsertRows(QModelIndex(), 0, 0);
                   m_SetupDataList.insert(0, new CSetupData(tr("TEXT_SETTINGS_VEHICLE_SETUP")    ,CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE, true, CSetupEnums::SETUP_VEHICLE, CSetupEnums::SETUP_SCREEN_VEHICLE ));
                   endInsertRows();
               }
               else
               {
                   LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Vehicle Setup Item is already present in list.", __FUNCTION__);
               }
           }
           else
           {
               if(CSetupEnums::SETUP_SCREEN_VEHICLE == pSetupData->m_eListItemIndex)
               {
                   /*
                    * Remove Vehicle Setup Item from list.
                    */
                   beginRemoveRows(QModelIndex(), 0, 0);
                   m_SetupDataList.removeAt(0);
                   endRemoveRows();
               }
               else
               {
                   LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Vehicle setup item is not present in list ", __FUNCTION__);
               }
           }
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_SETTINGS,"%s pSetupData is Null ", __FUNCTION__);
        }
    }
    else
    {
         LOG_WARNING(Log::e_LOG_CONTEXT_SETTINGS,"%s Setup data list is empty ", __FUNCTION__);
    }
}

void CSetupMainListModel::sltCPConnectionStatusUpdated(bool bCPConnectionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: bCPConnectionStatus: %d", __FUNCTION__, bCPConnectionStatus);
    sltHandleVehicleSetupPresence();
}

void CSetupMainListModel::sltPowerModeChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);

    int iIndex = 0;
    /* Increament the iIndex if Vehicle Setup is displayed on first index to get the Audio Setup index */
    if( CSetupEnums::SETUP_VEHICLE == m_SetupDataList[iIndex]->m_iListItemValue )
    {
        iIndex++;
    }
    else
    {
        /* Do nothing */
    }

    /* Enable/Disable the Audio Setup menu based on power mode */
    if( (!m_SetupDataList.empty()) && (m_SetupDataList.size() >= iIndex) )
    {
        m_SetupDataList[iIndex]->m_bListItemChecked = (CPowerModeEnums::VPM_ACTIVE == CPowerModeAdaptor::getInstance().getPowerModeStatus()) ||
                (CPowerModeEnums::VPM_ONE_HOUR == CPowerModeAdaptor::getInstance().getPowerModeStatus());

        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "Audio Setup :m_bListItemChecked : %d", m_SetupDataList[iIndex]->m_bListItemChecked);

        /* Refreshing the qml's data for the index which is changed */
        QModelIndex left = createIndex(iIndex, 0);
        QModelIndex right = createIndex(iIndex, 0);
        emit dataChanged(left, right);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: Audio Setup Item Not Present in setup main list", __FUNCTION__);
    }
}
