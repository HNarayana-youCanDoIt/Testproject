/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CPhoneSetupListModel.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar,Rajat Gupta
 * @brief         Contain implementation of all the methods declared in
 * CBtSetupListModel class
 */

#include "CPhoneSetupListModel.h"
#include "logging.h"
#include "CPhoneEnum.h"
#include "CPhoneAdaptor.h"
#include "CPersistencyAdaptor.h"

CPhoneSetupListModel::CPhoneSetupListModel(QObject *pParent) :
    QAbstractListModel(pParent),
    m_bIsSMSAlertItemExpanded(false),
    m_bIsConfigAutoSmsItemExpanded(false),
    m_bIsConfigAutoSmsEditItemExpanded(false),
    m_iConfigAutoSmsEditIndexExpanded(CPhoneEnum::PHONE_SETUP_CONFIGURE_AUTO_SMS + 1),
    SMS_ALERT_NOTIFICATION_ITEM_START_INDEX(4),
    SMS_ALERT_NOTIFICATION_ITEM_END_INDEX(6),
    CONFIG_SMS_ITEM_START_INDEX(5),
    CONFIG_SMS_ITEM_END_INDEX(15),
    CONFIG_AUTO_SMS_EDIT_ITEM_OFFSET_INDEX(6)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    m_listPhoneSetup.clear();
    m_listPhoneSMSAlert.clear();
    initPhoneSetupMainModel();
    initPhoneSetupSmsAlertList();
    initPhoneSetupConfigureSmsList();
    initPhoneSetupConfigureSmsEditList ();

}

CPhoneSetupListModel::~CPhoneSetupListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    m_listPhoneSetup.clear();
}

/************************************************************************//**
 * @category    OVERRIDEN METHODS of QAbstractListModel class
 ************************************************************************/
QHash<int, QByteArray> CPhoneSetupListModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[PHONE_SETUP_ITEM_TEXT_ROLE]           = "itemTextRole";
    roles[PHONE_SETUP_ITEM_ENABLED_ROLE]        = "itemEnabledRole";
    roles[PHONE_SETUP_ITEM_CHECKED_ROLE]        = "itemCheckedRole";
    roles[PHONE_SETUP_ITEM_TYPE_ROLE]           = "itemTypeRole";
    roles[PHONE_SETUP_ITEM_ID_ROLE]             = "itemId";
    roles[PHONE_SETUP_ITEM_EDIT_BUTTON_VISIBLE] = "itemEditBtnVisible";
    return roles;
}

QVariant CPhoneSetupListModel::data(const QModelIndex &index, int role) const
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    QVariant objRowData;
    int iRowIndex = index.row();
    if (index.isValid())
    {
        EPhoneSetupListRoles ePhoneSetupRole = static_cast<EPhoneSetupListRoles>(role);
        switch(ePhoneSetupRole)
        {
        case PHONE_SETUP_ITEM_TEXT_ROLE:
            objRowData = m_listPhoneSetup.at(iRowIndex).m_strName;
            break;
        case PHONE_SETUP_ITEM_ENABLED_ROLE:
            objRowData = m_listPhoneSetup.at(iRowIndex).m_bIsEnabled;
            break;
        case PHONE_SETUP_ITEM_CHECKED_ROLE:
            objRowData = m_listPhoneSetup.at(iRowIndex).m_bIsChecked;
            break;
        case PHONE_SETUP_ITEM_TYPE_ROLE:
            objRowData = m_listPhoneSetup.at(iRowIndex).m_ePhoneSetupItemType;
            break;
        case PHONE_SETUP_ITEM_ID_ROLE:
            objRowData = m_listPhoneSetup.at(iRowIndex).m_iItemId;
            break;
        case PHONE_SETUP_ITEM_EDIT_BUTTON_VISIBLE:
            objRowData = m_listPhoneSetup.at(iRowIndex).m_bEditBtnVisible;
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "invalid role received: %d", role);
            break;
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "model index out of scope: %d", iRowIndex);
    }
    return objRowData;
}

int CPhoneSetupListModel::rowCount(const QModelIndex &parent) const
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: rowCount: %d", __FUNCTION__, m_listPhoneSetup.count());
    Q_UNUSED(parent);
    return m_listPhoneSetup.count();
}

bool CPhoneSetupListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s : Role:%d, Index:%d ", __FUNCTION__, role, index.row());
    bool bReturnValue = false;
    if(index.isValid())
    {
        int iRowIndex = index.row();
        switch(role)
        {
        case PHONE_SETUP_ITEM_ENABLED_ROLE:
        {
            bool bIsPhoneItemEnabled = value.toBool();
            if(bIsPhoneItemEnabled != m_listPhoneSetup[iRowIndex].m_bIsEnabled)
            {
                m_listPhoneSetup[iRowIndex].m_bIsEnabled = bIsPhoneItemEnabled;
                bReturnValue = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Phone Setup Item enable state not changed");

            }
        }
            break;

        case PHONE_SETUP_ITEM_CHECKED_ROLE:
        {
            bool bIsPhoneSetupItemChecked = value.toBool ();
            if( m_listPhoneSetup[iRowIndex].m_bIsChecked  != bIsPhoneSetupItemChecked)
            {
                updateModelForCheckedRole (iRowIndex, bIsPhoneSetupItemChecked);
                bReturnValue  = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Phone Setup Item Checked status not changed");
            }
        }

            break;

        case PHONE_SETUP_ITEM_TEXT_ROLE:
        {
            const QString &strItemName = value.toString();
            if(strItemName.compare(m_listPhoneSetup[iRowIndex].m_strName) != 0)
            {
                m_listPhoneSetup[iRowIndex].m_strName = strItemName;
                bReturnValue = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Phone Setup Item name not changed");
            }
        }
            break;

        case PHONE_SETUP_ITEM_EDIT_BUTTON_VISIBLE:
        {

            bool bIsEditBtnVisible = value.toBool();
            if(bIsEditBtnVisible != m_listPhoneSetup[iRowIndex].m_bEditBtnVisible)
            {
                m_listPhoneSetup[iRowIndex].m_bEditBtnVisible = bIsEditBtnVisible;
                bReturnValue = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, " Phone Setup Item Edit Button Visiblity state not changed");

            }
        }
            break;

        case PHONE_SETUP_ITEM_ID_ROLE:
        {

            int iPhoneSetupDropDownId = value.toInt();
            if(iPhoneSetupDropDownId != m_listPhoneSetup[iRowIndex].m_iItemId)
            {
                m_listPhoneSetup[iRowIndex].m_iItemId = iPhoneSetupDropDownId;
                bReturnValue = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Phone Setup Item Dropdown Id not changed");

            }
        }

        default:
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s ,Default Case", __FUNCTION__);
            break;
        }
        if(bReturnValue)
        {
            QVector<int> vectRoles;
            vectRoles.push_back(role);
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Model Value Changed");
            emit dataChanged(index, index, vectRoles);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "item role data is not changed");
        }
    }

    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s ,Index Out of Scope!", __FUNCTION__);
    }
    return bReturnValue;

}


void CPhoneSetupListModel::expandSmsAlertNotification()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);

    if(!m_bIsSMSAlertItemExpanded)
    {
        /**
          * To check whether Configure Auto Sms Dropdown is expanded, if yes then collapse the dropdown.
          */
        if (m_bIsConfigAutoSmsItemExpanded)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s, deleting Configure Auto SMS Items", __FUNCTION__);
            collapseConfigAutoSms();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, Configure Auto Sms is in collapsed State", __FUNCTION__);
        }

        beginInsertRows(QModelIndex(), SMS_ALERT_NOTIFICATION_ITEM_START_INDEX,
                        (SMS_ALERT_NOTIFICATION_ITEM_START_INDEX + m_listPhoneSMSAlert.count() - 1));

        for (int i = 0; i < m_listPhoneSMSAlert.count(); i++)
        {
            m_listPhoneSetup.insert((SMS_ALERT_NOTIFICATION_ITEM_START_INDEX + i), m_listPhoneSMSAlert.at(i));
        }

        endInsertRows();
        m_bIsSMSAlertItemExpanded = true;
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, Insertion Successful", __FUNCTION__);
    }

    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, Sms Alert Notification is in Collapsed State", __FUNCTION__);
    }
}

void CPhoneSetupListModel::collapseSmsAlertNotification()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    if(m_bIsSMSAlertItemExpanded)
    {
        beginRemoveRows(QModelIndex(), SMS_ALERT_NOTIFICATION_ITEM_START_INDEX,
                        (SMS_ALERT_NOTIFICATION_ITEM_START_INDEX + m_listPhoneSMSAlert.count() - 1));

        for (int i = 0; i < m_listPhoneSMSAlert.count(); i++)
        {
            m_listPhoneSetup.removeAt(SMS_ALERT_NOTIFICATION_ITEM_START_INDEX);
        }

        endRemoveRows();
        m_bIsSMSAlertItemExpanded = false;
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s, Sms Alert Notification Items deletion Successful", __FUNCTION__);
    }

    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, Sms Alert Notification is in collapsed State", __FUNCTION__);
    }
}

void CPhoneSetupListModel::expandConfigAutoSms()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    if(!m_bIsConfigAutoSmsItemExpanded)
    {
        /**
          * To check whether Configure Sms Alert Notification Dropdown is expanded, if yes then collapse the dropdown.
          */
        if (m_bIsSMSAlertItemExpanded)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s, deleting Sms Alert Notification Expanded Items",__FUNCTION__);
            collapseSmsAlertNotification ();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, Sms Alert Notification is in collapsed State", __FUNCTION__);
        }

        beginInsertRows(QModelIndex(), CONFIG_SMS_ITEM_START_INDEX,
                        (CONFIG_SMS_ITEM_START_INDEX + m_listPhoneSMSConfig.count() - 1));

        for (int i = 0; i < m_listPhoneSMSConfig.count(); i++)
        {
            m_listPhoneSetup.insert((CONFIG_SMS_ITEM_START_INDEX + i),m_listPhoneSMSConfig.at(i));
        }

        endInsertRows();
        m_bIsConfigAutoSmsItemExpanded = true;
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s, Insertion Successful", __FUNCTION__);
    }

    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, Configure Auto Sms is in Collapsed state", __FUNCTION__);
    }
}

void CPhoneSetupListModel::collapseConfigAutoSms()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    if(m_bIsConfigAutoSmsItemExpanded)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, deletion Started", __FUNCTION__);
        /**
          * To check whether any Configure Sms Dropdown Edit Item is expanded, if yes then collapse the dropdown.
          */
        if(m_bIsConfigAutoSmsEditItemExpanded)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, deleting Configure Auto Sms Expanded Items", __FUNCTION__);
            collapseConfigAutoSmsEdit(m_iConfigAutoSmsEditIndexExpanded - CONFIG_AUTO_SMS_EDIT_ITEM_OFFSET_INDEX);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, Configure Auto Sms Edit Button is in collapsed state", __FUNCTION__);
        }

        beginRemoveRows(QModelIndex(), CONFIG_SMS_ITEM_START_INDEX,
                        (CONFIG_SMS_ITEM_START_INDEX + m_listPhoneSMSConfig.count() - 1));

        for (int i = 0; i < m_listPhoneSMSConfig.count(); i++)
        {
            m_listPhoneSetup.removeAt(CONFIG_SMS_ITEM_START_INDEX);
        }

        endRemoveRows();
        m_bIsConfigAutoSmsItemExpanded = false;
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s, deletion successful", __FUNCTION__);
    }

    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, ConfigAutoSmsItem is already in collapsed state", __FUNCTION__);
    }
}

void CPhoneSetupListModel::expandConfigAutoSmsEdit(int iItemId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);

    /**
      * Subtraction of CONFIG_AUTO_SMS_EDIT_ITEM_OFFSET_INDEX is done to equalize the PhoneSetup Index to Configure Sms Items Id which has a
      * range of 21-30
      */

    int iPhoneSetupIndex = (iItemId + CONFIG_AUTO_SMS_EDIT_ITEM_OFFSET_INDEX);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, iPhoneSetupIndex: %d", __FUNCTION__, iPhoneSetupIndex);
    if (m_bIsConfigAutoSmsEditItemExpanded)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, deleting Configure Auto Sms Expanded Items", __FUNCTION__);

        /**
          * Addtion of CONFIG_AUTO_SMS_EDIT_ITEM_OFFSET_INDEX is done to equalize the PhoneSetup Index to Configure Sms Items Id which has a
          * range of 21-30
          */
        collapseConfigAutoSmsEdit(m_iConfigAutoSmsEditIndexExpanded - CONFIG_AUTO_SMS_EDIT_ITEM_OFFSET_INDEX);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, ConfigAutoSmsItem Item is already in expanded state", __FUNCTION__);
    }

    beginInsertRows(QModelIndex(), iPhoneSetupIndex, iPhoneSetupIndex );

    m_listPhoneSetup.insert(iPhoneSetupIndex,m_listPhoneEditSMS.at(iItemId));
    endInsertRows();
    m_bIsConfigAutoSmsEditItemExpanded = true;
    m_iConfigAutoSmsEditIndexExpanded = iPhoneSetupIndex;
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, Insertion Successful", __FUNCTION__);
}

void CPhoneSetupListModel::collapseConfigAutoSmsEdit(int iItemId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    /**
      * To check whether any already Configure Sms edit item  Dropdown is expanded, if yes then collapse the dropdown.
      */

    if(m_bIsConfigAutoSmsEditItemExpanded)
    {
        /**
          * Subtraction of CONFIG_AUTO_SMS_EDIT_ITEM_OFFSET_INDEX is done to equalize the PhoneSetup Index to Configure Sms Items Id which has a
          * range of 21-30
          */

        int iPhoneSetupIndex = (iItemId + CONFIG_AUTO_SMS_EDIT_ITEM_OFFSET_INDEX);
        beginRemoveRows(QModelIndex(), iPhoneSetupIndex, iPhoneSetupIndex);
        m_listPhoneSetup.removeAt(iPhoneSetupIndex);
        endRemoveRows();
        m_bIsConfigAutoSmsEditItemExpanded = false;
        m_iConfigAutoSmsEditIndexExpanded = -1;
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, deletion Successful", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, ConfigAutoSmsItem Edit is already in collapsed state", __FUNCTION__);
    }
}


bool CPhoneSetupListModel::isItemEnabled(CPhoneEnum::EPhoneSetupItems eItemIndex)
{
    bool bEnabled = true;
    switch(eItemIndex)
    {
    case CPhoneEnum::PHONE_SETUP_PAIR_NEW_DEVICE:
    case CPhoneEnum::PHONE_SETUP_PAIRED_DEVICES:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: getProjPhConnectionStatus: %d, bluetoothStatus: %d"
                 , __FUNCTION__, CPhoneAdaptor::getInstance()->getProjPhConnectionStatus(), CPhoneAdaptor::getInstance()->bluetoothStatus());
        bEnabled = ((!CPhoneAdaptor::getInstance()->getProjPhConnectionStatus()) &&
                    (CPhoneAdaptor::getInstance()->bluetoothStatus()));
    }
        break;

    case CPhoneEnum::PHONE_SETUP_BLUETOOTH_VISIBILITY:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: getProjPhConnectionStatus: %d, bluetoothStatus: %d, btVisibilityReqStatus: %d"
                 , __FUNCTION__, CPhoneAdaptor::getInstance()->getProjPhConnectionStatus(), CPhoneAdaptor::getInstance()->bluetoothStatus()
                 , CPhoneAdaptor::getInstance()->btVisibilityReqStatus());
        bEnabled = ((!CPhoneAdaptor::getInstance()->getProjPhConnectionStatus()) &&
                    (CPhoneAdaptor::getInstance()->bluetoothStatus()) &&
                    (!CPhoneAdaptor::getInstance()->btVisibilityReqStatus()));
    }
        break;

    default:
        break;
    }
    return bEnabled;
}

void CPhoneSetupListModel::initPhoneSetupMainModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        m_listPhoneSetup.clear();

        m_listPhoneSetup.append(CPhoneData::SPhoneSetupInfo(tr("TEXT_SETTING_PAIR_NEW_DEVICE"), isItemEnabled(CPhoneEnum::PHONE_SETUP_PAIR_NEW_DEVICE), false,
                                                            CPhoneEnum::ITEM_TYPE_LABEL,CPhoneEnum::PHONE_SETUP_PAIR_NEW_DEVICE));

        m_listPhoneSetup.append(CPhoneData::SPhoneSetupInfo (tr("TEXT_SETTING_PAIRED_DEVICE_LIST"), isItemEnabled(CPhoneEnum::PHONE_SETUP_PAIRED_DEVICES), false,
                                                             CPhoneEnum::ITEM_TYPE_LABEL,CPhoneEnum::PHONE_SETUP_PAIRED_DEVICES));

        m_listPhoneSetup.append(CPhoneData::SPhoneSetupInfo (tr("TEXT_SETTING_BLUETOOTH_VISIBILITY"),
                                                             isItemEnabled(CPhoneEnum::PHONE_SETUP_BLUETOOTH_VISIBILITY),
                                                             CPhoneAdaptor::getInstance()->getHUDiscoverableStatus(),
                                                             CPhoneEnum::ITEM_TYPE_LABEL_WITH_CHECKBOX, CPhoneEnum::PHONE_SETUP_BLUETOOTH_VISIBILITY));

        m_listPhoneSetup.append(CPhoneData::SPhoneSetupInfo(tr("TEXT_SETUP_PHONE_SMS_ALERT_NOTIFICATION"), isItemEnabled(CPhoneEnum::PHONE_SETUP_SMS_ALERT_NOTIFICATION), false,
                                                            CPhoneEnum::ITEM_TYPE_LABEL_WITH_DROPDOWN,
                                                            CPhoneEnum::PHONE_SETUP_SMS_ALERT_NOTIFICATION));

        m_listPhoneSetup.append(CPhoneData::SPhoneSetupInfo(tr("TEXT_SETUP_PHONE_CONFIGURE_AUTO_SMS"), isItemEnabled(CPhoneEnum::PHONE_SETUP_CONFIGURE_AUTO_SMS), false,
                                                            CPhoneEnum::ITEM_TYPE_LABEL_WITH_DROPDOWN,
                                                            CPhoneEnum::PHONE_SETUP_CONFIGURE_AUTO_SMS));

    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "Phone adaptor object not created");
    }
}




void CPhoneSetupListModel::initPhoneSetupSmsAlertList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    int iSMSAlertSelectedIndex =
            CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_SETUP_SMS_NOTIFY_TYPE);

    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s , iSMSAlertSelectedIndex from persistency : %d", __FUNCTION__, iSMSAlertSelectedIndex);
    m_listPhoneSMSAlert.clear();

    m_listPhoneSMSAlert.append(CPhoneData::SPhoneSetupInfo (tr("TEXT_SETUP_PHONE_NOTIFY_POPUP_BEEP"), true
                                                            ,(CPhoneEnum::NOTIFY_WITH_BEEP_AND_POPUP_ID == iSMSAlertSelectedIndex)
                                                            ,CPhoneEnum::ITEM_TYPE_LABEL_WITH_RADIO_BUTTON
                                                            ,CPhoneEnum::NOTIFY_WITH_BEEP_AND_POPUP_ID));

    m_listPhoneSMSAlert.append(CPhoneData::SPhoneSetupInfo (tr("TEXT_SETUP_PHONE_NOTIFY_WITH_POPUP"), true
                                                            ,(CPhoneEnum::NOTIFY_WITH_ONLY_POPUP_ID == iSMSAlertSelectedIndex)
                                                            ,CPhoneEnum::ITEM_TYPE_LABEL_WITH_RADIO_BUTTON
                                                            ,CPhoneEnum::NOTIFY_WITH_ONLY_POPUP_ID));

    m_listPhoneSMSAlert.append(CPhoneData::SPhoneSetupInfo (tr("TEXT_SETUP_PHONE_NO_NOTIFICATION"), true,
                                                            (CPhoneEnum::NO_NOTIFICATION_ID == iSMSAlertSelectedIndex)
                                                            ,CPhoneEnum::ITEM_TYPE_LABEL_WITH_RADIO_BUTTON
                                                            ,CPhoneEnum::NO_NOTIFICATION_ID));

}


void CPhoneSetupListModel::initPhoneSetupConfigureSmsList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);

    int iConfigureAutoSmsIndex =
            CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_SETUP_SMS_CONFIGURE_SELECTION);

    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s , iConfigureAutoSmsIndex from persistency : %d", __FUNCTION__, iConfigureAutoSmsIndex);
    m_listPhoneSMSConfig.clear();

    m_listPhoneSMSConfig.append(CPhoneData::SPhoneSetupInfo(m_strArrFixedSMSs[0], true,
                                (CPhoneEnum::MESSAGE_1_ID == iConfigureAutoSmsIndex) ,
                                CPhoneEnum::ITEM_TYPE_LABEL_WITH_RADIO_BUTTON_AND_DROPDOWN,
                                CPhoneEnum::MESSAGE_1_ID));
    m_listPhoneSMSConfig.append(CPhoneData::SPhoneSetupInfo(m_strArrFixedSMSs[1], true,
                                (CPhoneEnum::MESSAGE_2_ID == iConfigureAutoSmsIndex),
                                CPhoneEnum::ITEM_TYPE_LABEL_WITH_RADIO_BUTTON_AND_DROPDOWN,
                                CPhoneEnum::MESSAGE_2_ID));

    m_listPhoneSMSConfig.append(CPhoneData::SPhoneSetupInfo(m_strArrFixedSMSs[2], true,
                                (CPhoneEnum::MESSAGE_3_ID == iConfigureAutoSmsIndex),
                                CPhoneEnum::ITEM_TYPE_LABEL_WITH_RADIO_BUTTON_AND_DROPDOWN,
                                CPhoneEnum::MESSAGE_3_ID));

    m_listPhoneSMSConfig.append(CPhoneData::SPhoneSetupInfo(CPersistencyAdaptor::getInstance().readStringData(EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_01),true,
                                                            (CPhoneEnum::MESSAGE_4_ID == iConfigureAutoSmsIndex),
                                                            CPhoneEnum::ITEM_TYPE_LABEL_WITH_RADIO_BUTTON_AND_DROPDOWN,
                                                            CPhoneEnum::MESSAGE_4_ID));

    m_listPhoneSMSConfig.append(CPhoneData::SPhoneSetupInfo(CPersistencyAdaptor::getInstance().readStringData(EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_02),true,
                                                            (CPhoneEnum::MESSAGE_5_ID == iConfigureAutoSmsIndex),
                                                            CPhoneEnum::ITEM_TYPE_LABEL_WITH_RADIO_BUTTON_AND_DROPDOWN,
                                                            CPhoneEnum::MESSAGE_5_ID));

    m_listPhoneSMSConfig.append(CPhoneData::SPhoneSetupInfo(CPersistencyAdaptor::getInstance().readStringData(EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_03),true,
                                                            (CPhoneEnum::MESSAGE_6_ID == iConfigureAutoSmsIndex),
                                                            CPhoneEnum::ITEM_TYPE_LABEL_WITH_RADIO_BUTTON_AND_DROPDOWN,
                                                            CPhoneEnum::MESSAGE_6_ID));

    m_listPhoneSMSConfig.append(CPhoneData::SPhoneSetupInfo(CPersistencyAdaptor::getInstance().readStringData(EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_04),true,
                                                            (CPhoneEnum::MESSAGE_7_ID == iConfigureAutoSmsIndex),
                                                            CPhoneEnum::ITEM_TYPE_LABEL_WITH_RADIO_BUTTON_AND_DROPDOWN,
                                                            CPhoneEnum::MESSAGE_7_ID));

    m_listPhoneSMSConfig.append(CPhoneData::SPhoneSetupInfo(CPersistencyAdaptor::getInstance().readStringData(EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_05),true,
                                                            (CPhoneEnum::MESSAGE_8_ID == iConfigureAutoSmsIndex),
                                                            CPhoneEnum::ITEM_TYPE_LABEL_WITH_RADIO_BUTTON_AND_DROPDOWN,
                                                            CPhoneEnum::MESSAGE_8_ID));

    m_listPhoneSMSConfig.append(CPhoneData::SPhoneSetupInfo(CPersistencyAdaptor::getInstance().readStringData(EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_06),true,
                                                            (CPhoneEnum::MESSAGE_9_ID == iConfigureAutoSmsIndex),
                                                            CPhoneEnum::ITEM_TYPE_LABEL_WITH_RADIO_BUTTON_AND_DROPDOWN,
                                                            CPhoneEnum::MESSAGE_9_ID));

    m_listPhoneSMSConfig.append(CPhoneData::SPhoneSetupInfo(CPersistencyAdaptor::getInstance().readStringData(EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_07),true,
                                                            (CPhoneEnum::MESSAGE_10_ID == iConfigureAutoSmsIndex),
                                                            CPhoneEnum::ITEM_TYPE_LABEL_WITH_RADIO_BUTTON_AND_DROPDOWN,
                                                            CPhoneEnum::MESSAGE_10_ID));

}



void CPhoneSetupListModel::initPhoneSetupConfigureSmsEditList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    m_listPhoneEditSMS.clear();

    m_listPhoneEditSMS.append(CPhoneData::SPhoneSetupInfo(m_strArrFixedSMSs[0],true,
                                                          false,CPhoneEnum::ITEM_TYPE_LABEL_WITH_EDIT_BUTTON,-1,false));

    m_listPhoneEditSMS.append(CPhoneData::SPhoneSetupInfo(m_strArrFixedSMSs[1],true,false,
                                                          CPhoneEnum::ITEM_TYPE_LABEL_WITH_EDIT_BUTTON,-1,false));

    m_listPhoneEditSMS.append(CPhoneData::SPhoneSetupInfo(m_strArrFixedSMSs[2], true,false,
                                                          CPhoneEnum::ITEM_TYPE_LABEL_WITH_EDIT_BUTTON,-1,false));

    m_listPhoneEditSMS.append(CPhoneData::SPhoneSetupInfo(CPersistencyAdaptor::getInstance().readStringData(EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_01),true,
                                                          false,CPhoneEnum::ITEM_TYPE_LABEL_WITH_EDIT_BUTTON));

    m_listPhoneEditSMS.append(CPhoneData::SPhoneSetupInfo(CPersistencyAdaptor::getInstance().readStringData(EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_02),true,
                                                          false,CPhoneEnum::ITEM_TYPE_LABEL_WITH_EDIT_BUTTON));

    m_listPhoneEditSMS.append(CPhoneData::SPhoneSetupInfo(CPersistencyAdaptor::getInstance().readStringData(EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_03),true,
                                                          false,CPhoneEnum::ITEM_TYPE_LABEL_WITH_EDIT_BUTTON));

    m_listPhoneEditSMS.append(CPhoneData::SPhoneSetupInfo(CPersistencyAdaptor::getInstance().readStringData(EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_04),true,
                                                          false,CPhoneEnum::ITEM_TYPE_LABEL_WITH_EDIT_BUTTON));

    m_listPhoneEditSMS.append(CPhoneData::SPhoneSetupInfo(CPersistencyAdaptor::getInstance().readStringData(EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_05),true,
                                                          false,CPhoneEnum::ITEM_TYPE_LABEL_WITH_EDIT_BUTTON));

    m_listPhoneEditSMS.append(CPhoneData::SPhoneSetupInfo(CPersistencyAdaptor::getInstance().readStringData(EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_06),true,
                                                          false,CPhoneEnum::ITEM_TYPE_LABEL_WITH_EDIT_BUTTON));

    m_listPhoneEditSMS.append(CPhoneData::SPhoneSetupInfo(CPersistencyAdaptor::getInstance().readStringData(EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_07),true,
                                                          false,CPhoneEnum::ITEM_TYPE_LABEL_WITH_EDIT_BUTTON));
}

void CPhoneSetupListModel::updateSmsAlertNotificationList()
{

    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    int iSMSAlertSelectedIndex =
            CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_SETUP_SMS_NOTIFY_TYPE);

    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s , iSMSAlertSelectedIndex from persistency : %d", __FUNCTION__, iSMSAlertSelectedIndex);
    for(int i = 0; i < m_listPhoneSMSAlert.count(); i++)
        m_listPhoneSMSAlert[i].m_bIsChecked = false;

    m_listPhoneSMSAlert[iSMSAlertSelectedIndex].m_bIsChecked = true;
}


void CPhoneSetupListModel::updateConfigAutoSmsList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    int iConfigAutoSmsSelectedIndex =
            CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_SETUP_SMS_CONFIGURE_SELECTION);

    for(int i = 0; i < m_listPhoneSMSConfig.count(); i++)
        m_listPhoneSMSConfig[i].m_bIsChecked = false;

    m_listPhoneSMSConfig[iConfigAutoSmsSelectedIndex].m_bIsChecked = true;
}



void CPhoneSetupListModel::updateModelForCheckedRole(int iPhoneSetupIndex, bool bCheckedStatus)
{
    if(iPhoneSetupIndex == CPhoneEnum::PHONE_SETUP_BLUETOOTH_VISIBILITY)
    {
        m_listPhoneSetup[iPhoneSetupIndex].m_bIsChecked = bCheckedStatus;
    }

    else if ((iPhoneSetupIndex >= SMS_ALERT_NOTIFICATION_ITEM_START_INDEX) &&
             (iPhoneSetupIndex <= SMS_ALERT_NOTIFICATION_ITEM_END_INDEX) && m_bIsSMSAlertItemExpanded)
    {
        for (int iIndex = SMS_ALERT_NOTIFICATION_ITEM_START_INDEX ; iIndex <= SMS_ALERT_NOTIFICATION_ITEM_END_INDEX ; ++iIndex)
        {
            m_listPhoneSetup[iIndex].m_bIsChecked = false;
        }

        m_listPhoneSetup[iPhoneSetupIndex].m_bIsChecked = bCheckedStatus;
    }
    else if ((iPhoneSetupIndex >= CONFIG_SMS_ITEM_START_INDEX)
             && (iPhoneSetupIndex <= (CONFIG_SMS_ITEM_END_INDEX + 1))
             && m_bIsConfigAutoSmsItemExpanded)
    {
        if(m_bIsConfigAutoSmsEditItemExpanded)
        {
            for (int iIndex = CONFIG_SMS_ITEM_START_INDEX ; iIndex < (CONFIG_SMS_ITEM_END_INDEX + 1) ; ++iIndex)
            {
                m_listPhoneSetup[iIndex].m_bIsChecked = false;
            }

            m_listPhoneSetup[iPhoneSetupIndex].m_bIsChecked = bCheckedStatus;
        }
        else
        {
            for (int iIndex = CONFIG_SMS_ITEM_START_INDEX ; iIndex < CONFIG_SMS_ITEM_END_INDEX  ; ++iIndex)
            {
                m_listPhoneSetup[iIndex].m_bIsChecked = false;
            }

            m_listPhoneSetup[iPhoneSetupIndex].m_bIsChecked = bCheckedStatus;
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Phone Setup Item checked state not changed");

    }
}

void CPhoneSetupListModel::updateConfigureMessageList(int iMessageIndex, const QString &strUpdatedMessage)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);

    if((iMessageIndex >= 0) && (iMessageIndex < m_listPhoneSetup.length()))
    {
        /** Updating the SMS content to persistence */
        CPersistencyAdaptor::getInstance().writeStringData((EPersistencyKeys)(EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_01 + ((iMessageIndex - CONFIG_AUTO_SMS_EDIT_ITEM_OFFSET_INDEX) - FIXED_SMS_COUNT)), strUpdatedMessage);

        m_listPhoneSMSConfig[iMessageIndex - CONFIG_AUTO_SMS_EDIT_ITEM_OFFSET_INDEX].m_strName = strUpdatedMessage;
        m_listPhoneEditSMS[iMessageIndex - CONFIG_AUTO_SMS_EDIT_ITEM_OFFSET_INDEX].m_strName = strUpdatedMessage;
        setData(index(iMessageIndex, 0), strUpdatedMessage, CPhoneSetupListModel::PHONE_SETUP_ITEM_TEXT_ROLE);
        setData(index(iMessageIndex - 1, 0), strUpdatedMessage, CPhoneSetupListModel::PHONE_SETUP_ITEM_TEXT_ROLE);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: Index is Out of Bound, iMessageIndex: %d ", __FUNCTION__, iMessageIndex);
    }
}

QString CPhoneSetupListModel::getConfiguredAutoSmsText()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    int iConfigureAutoSmsIndex = CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_SETUP_SMS_CONFIGURE_SELECTION);
    QString strAutoSmsText = "";

    if((iConfigureAutoSmsIndex >= 0) && (iConfigureAutoSmsIndex < m_listPhoneEditSMS.size()))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: configured auto sms text: %s", __FUNCTION__, strAutoSmsText.toStdString().c_str());
        strAutoSmsText = m_listPhoneEditSMS.at(iConfigureAutoSmsIndex).m_strName;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: iConfigureAutoSmsIndex out of scope", __FUNCTION__);
    }
    return strAutoSmsText;
}

int CPhoneSetupListModel::getSmsAlertType()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    return CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_SETUP_SMS_NOTIFY_TYPE);
}
