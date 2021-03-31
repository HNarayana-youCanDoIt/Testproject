/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CW3WSetupListModel.cpp
 * @ingroup       HMIComponent
 * @author        Nishant Khandagale
 * @brief         Contain implementation of all the methods declared in
 * CW3WSetupListModel class
 */

#include "CW3WSetupListModel.h"
#include "logging.h"
#include "CW3WEnum.h"
#include "CW3WAdaptor.h"
#include "CW3WApplication.h"
#include "CVariantControlAdaptor.h"
#include "CPersistencyAdaptor.h"

CW3WSetupListModel::CW3WSetupListModel(QObject *pParent) :
    QAbstractListModel(pParent),
    m_bIsAutoLaunchPermissionExpanded(false),
    m_bIsCountryPreferenceExpanded(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    m_mapSetupDataElementIndex.clear();
    initW3WSetupModel();
    initW3WAutoLaunchPermissionModel();
    initW3WCountryPreferenceModel();
}

CW3WSetupListModel::~CW3WSetupListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    m_listW3WSetup.clear();
    m_listW3WAutoLaunchPermission.clear();
    m_listW3WCountryPreference.clear();
    m_mapSetupDataElementIndex.clear();
}

/************************************************************************//**
 * @category    OVERRIDEN METHODS of QAbstractListModel class
 ************************************************************************/
QHash<int, QByteArray> CW3WSetupListModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[W3W_SETUP_ITEM_TEXT_ROLE]           = "itemTextRole";
    roles[W3W_SETUP_ITEM_ENABLED_ROLE]        = "itemEnabledRole";
    roles[W3W_SETUP_ITEM_CHECKED_ROLE]        = "itemCheckedRole";
    roles[W3W_SETUP_ITEM_TYPE_ROLE]           = "itemTypeRole";
    roles[W3W_SETUP_ITEM_ID_ROLE]             = "itemId";
    return roles;
}

QVariant CW3WSetupListModel::data(const QModelIndex &index, int role) const
{
    QVariant objRowData;
    int iRowIndex = index.row();
    if (index.isValid())
    {
        EW3WSetupListRoles eW3WSetupRole = static_cast<EW3WSetupListRoles>(role);
        switch(eW3WSetupRole)
        {
        case W3W_SETUP_ITEM_TEXT_ROLE:
            objRowData = m_listW3WSetup.at(iRowIndex).m_strName;
            break;
        case W3W_SETUP_ITEM_ENABLED_ROLE:
            objRowData = m_listW3WSetup.at(iRowIndex).m_bIsEnabled;
            break;
        case W3W_SETUP_ITEM_CHECKED_ROLE:
            objRowData = m_listW3WSetup.at(iRowIndex).m_bIsChecked;
            break;
        case W3W_SETUP_ITEM_TYPE_ROLE:
            objRowData = m_listW3WSetup.at(iRowIndex).m_eW3WItemType;
            break;
        case W3W_SETUP_ITEM_ID_ROLE:
            objRowData = m_listW3WSetup.at(iRowIndex).m_iItemId;
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_W3W, "invalid role received: %d", role);
            break;
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "model index out of scope: %d", iRowIndex);
    }
    return objRowData;
}

int CW3WSetupListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listW3WSetup.count();
}

bool CW3WSetupListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s : Role:%d, Index:%d ", __FUNCTION__, role, index.row());
    bool bReturnValue = false;
    if(index.isValid())
    {
        int iRowIndex = index.row();
        switch(role)
        {
        case W3W_SETUP_ITEM_ENABLED_ROLE:
        {
            bool bIsW3WItemEnabled = value.toBool();
            if(bIsW3WItemEnabled != m_listW3WSetup[iRowIndex].m_bIsEnabled)
            {
                m_listW3WSetup[iRowIndex].m_bIsEnabled = bIsW3WItemEnabled;
                bReturnValue = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_W3W, "W3W Setup Item enable state not changed");
            }
        }
            break;

        case W3W_SETUP_ITEM_CHECKED_ROLE:
        {
            bool bIsW3WSetupItemChecked = value.toBool();
            if( m_listW3WSetup[iRowIndex].m_bIsChecked  != bIsW3WSetupItemChecked)
            {
                updateModelForCheckedRole (iRowIndex, bIsW3WSetupItemChecked);
                bReturnValue  = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_W3W, "W3W Setup Item Checked status not changed");
            }
        }

            break;

        case W3W_SETUP_ITEM_TEXT_ROLE:
        {
            const QString &strItemName = value.toString();
            if(strItemName.compare(m_listW3WSetup[iRowIndex].m_strName) != 0)
            {
                m_listW3WSetup[iRowIndex].m_strName = strItemName;
                bReturnValue = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_W3W, "W3W Setup Item name not changed");
            }
        }
            break;

        case W3W_SETUP_ITEM_ID_ROLE:
        {

            int iW3WSetupDropDownId = value.toInt();
            if(iW3WSetupDropDownId != m_listW3WSetup[iRowIndex].m_iItemId)
            {
                m_listW3WSetup[iRowIndex].m_iItemId = iW3WSetupDropDownId;
                bReturnValue = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_W3W, "W3W Setup Item Dropdown Id not changed");

            }
        }
            break;

        default:
            LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s ,Default Case", __FUNCTION__);
            break;
        }
        if(bReturnValue)
        {
            QVector<int> vectRoles;
            vectRoles.push_back(role);
            LOG_INFO(Log::e_LOG_CONTEXT_W3W, "Model Value Changed");
            emit dataChanged(index, index, vectRoles);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_W3W, "item role data is not changed");
        }
    }

    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s ,Index Out of Scope!", __FUNCTION__);
    }
    return bReturnValue;
}

bool CW3WSetupListModel::isItemEnabled(CW3WEnum::EW3WSetupItems eItemIndex)
{
    bool bEnabled = false;
    switch(eItemIndex)
    {
    case CW3WEnum::W3W_SETUP_AUTOLAUNCH_PERMISSIONS:
    case CW3WEnum::W3W_SETUP_COUNTRY_PREFERENCE:
    case CW3WEnum::W3W_SETUP_STARTUP_WALKTHROUGH:
        bEnabled = true;
        break;

    default:
        break;
    }
    return bEnabled;
}

void CW3WSetupListModel::initW3WSetupModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    m_listW3WSetup.clear();

    if( CVariantControlAdaptor::getInstance()->eolAndroidAutoEnabled() ||
            CVariantControlAdaptor::getInstance()->eolAppleCarPlayEnabled() )
    {
        m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_AUTOLAUNCH_PERMISSIONS] = m_listW3WSetup.count();
        m_listW3WSetup.append(CW3WData::SW3WSetupData (tr("TEXT_W3W_SETUP_AUTO_LAUNCH_PERMISSIONS"),
                                                   isItemEnabled(CW3WEnum::W3W_SETUP_AUTOLAUNCH_PERMISSIONS), false,
                                                   CW3WEnum::ITEM_TYPE_LABEL_WITH_DROPDOWN, CW3WEnum::W3W_SETUP_AUTOLAUNCH_PERMISSIONS));
    }

    m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_COUNTRY_PREFERENCE] = m_listW3WSetup.count();
    m_listW3WSetup.append(CW3WData::SW3WSetupData (tr("TEXT_W3W_SETUP_COUNTRY_PREFERENCE"),
                                                   isItemEnabled(CW3WEnum::W3W_SETUP_COUNTRY_PREFERENCE), false,
                                                   CW3WEnum::ITEM_TYPE_LABEL_WITH_DROPDOWN, CW3WEnum::W3W_SETUP_COUNTRY_PREFERENCE));

    m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_STARTUP_WALKTHROUGH] = m_listW3WSetup.count();
    m_listW3WSetup.append(CW3WData::SW3WSetupData (tr("TEXT_W3W_SETUP_STARTUP_WALKTHROUGH"),
                                                   isItemEnabled(CW3WEnum::W3W_SETUP_STARTUP_WALKTHROUGH), false,
                                                   CW3WEnum::ITEM_TYPE_LABEL_WITH_CHECKBOX, CW3WEnum::W3W_SETUP_STARTUP_WALKTHROUGH));

}

void CW3WSetupListModel::initW3WAutoLaunchPermissionModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);

    m_listW3WAutoLaunchPermission.clear();

    if(CVariantControlAdaptor::getInstance()->eolAndroidAutoEnabled())
    {
        m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_AUTOLAUNCH_PERMISSIONS_AA] = m_listW3WAutoLaunchPermission.count();
        m_listW3WAutoLaunchPermission.append(CW3WData::SW3WSetupData(tr("TEXT_W3W_SETUP_AUTO_LAUNCH_PERMISSIONS_AA"), true, false,
                                                  CW3WEnum::ITEM_TYPE_LABEL_WITH_CHECKBOX, CW3WEnum::W3W_SETUP_AUTOLAUNCH_PERMISSIONS_AA));
    }

    if(CVariantControlAdaptor::getInstance()->eolAppleCarPlayEnabled())
    {
        m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_AUTOLAUNCH_PERMISSIONS_CP] = m_listW3WAutoLaunchPermission.count();
        m_listW3WAutoLaunchPermission.append(CW3WData::SW3WSetupData (tr("TEXT_W3W_SETUP_AUTO_LAUNCH_PERMISSIONS_CP"), true, false,
                                                   CW3WEnum::ITEM_TYPE_LABEL_WITH_CHECKBOX, CW3WEnum::W3W_SETUP_AUTOLAUNCH_PERMISSIONS_CP));
    }
}

void CW3WSetupListModel::expandSetupDropDown(int iItemId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, iItemId: %d", __FUNCTION__, iItemId);

    if(CW3WEnum::W3W_SETUP_AUTOLAUNCH_PERMISSIONS == iItemId)
    {
        expandAutoLaunchPermission();
    }
    else if(CW3WEnum::W3W_SETUP_COUNTRY_PREFERENCE == iItemId)
    {
        expandCountryPreference();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, Invalid item: %d", __FUNCTION__, iItemId);
    }
}

void CW3WSetupListModel::collapseSetupDropDown(int iItemId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, iItemId: %d", __FUNCTION__, iItemId);

    if(CW3WEnum::W3W_SETUP_AUTOLAUNCH_PERMISSIONS == iItemId)
    {
        collapseAutoLaunchPermission();
    }
    else if(CW3WEnum::W3W_SETUP_COUNTRY_PREFERENCE == iItemId)
    {
        collapseCountryPreference();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, Invalid item : %d", __FUNCTION__, iItemId);
    }
}

void CW3WSetupListModel::expandAutoLaunchPermission()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);

    if(!m_bIsAutoLaunchPermissionExpanded)
    {
        // Collapse Country Preference Dropdown if it is expanded
        if(m_bIsCountryPreferenceExpanded)
        {
            collapseCountryPreference();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, Country Preference is in collapsed State", __FUNCTION__);
        }

        beginInsertRows(QModelIndex(), m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_AUTOLAUNCH_PERMISSIONS] + 1,
                        (m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_AUTOLAUNCH_PERMISSIONS] + m_listW3WAutoLaunchPermission.count()));

        for (int i = 0; i < m_listW3WAutoLaunchPermission.count(); i++)
        {
            m_listW3WSetup.insert(( (m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_AUTOLAUNCH_PERMISSIONS] + 1) + i), m_listW3WAutoLaunchPermission.at(i));
        }

        endInsertRows();
        m_bIsAutoLaunchPermissionExpanded = true;
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, Insertion Successful", __FUNCTION__);
    }

    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, Auto Launch Permission is in Expanded State", __FUNCTION__);
    }
}

void CW3WSetupListModel::collapseAutoLaunchPermission()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    if(m_bIsAutoLaunchPermissionExpanded)
    {
        beginRemoveRows(QModelIndex(), m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_AUTOLAUNCH_PERMISSIONS] + 1,
                        (m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_AUTOLAUNCH_PERMISSIONS] + m_listW3WAutoLaunchPermission.count() ));

        for (int i = 0; i < m_listW3WAutoLaunchPermission.count(); i++)
        {
            m_listW3WSetup.removeAt(m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_AUTOLAUNCH_PERMISSIONS] + 1);
        }

        endRemoveRows();
        m_bIsAutoLaunchPermissionExpanded = false;
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Auto Launch Permission Items deletion Successful", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, Auto Launch Permission is in collapsed State", __FUNCTION__);
    }
}

void CW3WSetupListModel::updateAutoLaunchPermissionList()
{
    /* No need to check EOL again, if the AA/CP is not supported, the list index item id will not be present */
    if (m_mapSetupDataElementIndex.contains(CW3WEnum::W3W_SETUP_AUTOLAUNCH_PERMISSIONS_AA))
    {
        bool bAutoLaunchPermissionForAA = CW3WApplication::getW3WAdaptor()->autoLaunchPermissionStatusForAA();
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s , bAutoLaunchPermissionForAA: %d ", __FUNCTION__, bAutoLaunchPermissionForAA);
        m_listW3WAutoLaunchPermission[m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_AUTOLAUNCH_PERMISSIONS_AA]].m_bIsChecked = bAutoLaunchPermissionForAA;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s , Android Auto not supported", __FUNCTION__);
    }

    if (m_mapSetupDataElementIndex.contains(CW3WEnum::W3W_SETUP_AUTOLAUNCH_PERMISSIONS_CP))
    {
        bool bAutoLaunchPermissionForCP = CW3WApplication::getW3WAdaptor()->autoLaunchPermissionStatusForCP();
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s , bAutoLaunchPermissionForCP: %d", __FUNCTION__, bAutoLaunchPermissionForCP);
        m_listW3WAutoLaunchPermission[m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_AUTOLAUNCH_PERMISSIONS_CP]].m_bIsChecked = bAutoLaunchPermissionForCP;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s , Carplay not supported", __FUNCTION__);
    }
}

void CW3WSetupListModel::updateStartupWalkthroughMenu()
{
    if((m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_STARTUP_WALKTHROUGH] >= 0) && (m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_STARTUP_WALKTHROUGH] < m_listW3WSetup.length()))
    {
        bool startupWalkthroughStatus = CW3WApplication::getW3WAdaptor()->startupWalkthroughStatus();
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s , startupWalkthroughStatus: %d ", __FUNCTION__, startupWalkthroughStatus);
        m_listW3WSetup[m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_STARTUP_WALKTHROUGH]].m_bIsChecked = startupWalkthroughStatus;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s , index out of bound", __FUNCTION__);
    }
}

void CW3WSetupListModel::initW3WCountryPreferenceModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);

    m_listW3WCountryPreference.clear();

    m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_COUNTRY_PREFERENCE_IN] = m_listW3WCountryPreference.count();
    m_listW3WCountryPreference.append(CW3WData::SW3WSetupData(tr("TEXT_W3W_SETUP_COUNTRY_PREFERENCE_INDIA"), true, false,
                                                  CW3WEnum::ITEM_TYPE_LABEL_WITH_RADIO_BUTTON, CW3WEnum::W3W_SETUP_COUNTRY_PREFERENCE_IN));

    m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_COUNTRY_PREFERENCE_ALL] = m_listW3WCountryPreference.count();
    m_listW3WCountryPreference.append(CW3WData::SW3WSetupData (tr("TEXT_W3W_SETUP_COUNTRY_PREFERENCE_ALL"), true, false,
                                                   CW3WEnum::ITEM_TYPE_LABEL_WITH_RADIO_BUTTON, CW3WEnum::W3W_SETUP_COUNTRY_PREFERENCE_ALL));
}

void CW3WSetupListModel::expandCountryPreference()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);

    if(!m_bIsCountryPreferenceExpanded)
    {
        // Collapse Auto Launch Permission Dropdown if it is expanded
        if(m_bIsAutoLaunchPermissionExpanded)
        {
            collapseAutoLaunchPermission();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, Auto Launch Permission is in collapsed State", __FUNCTION__);
        }

        beginInsertRows(QModelIndex(), m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_COUNTRY_PREFERENCE] + 1,
                        (m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_COUNTRY_PREFERENCE] + m_listW3WCountryPreference.count() ));

        for (int i = 0; i < m_listW3WCountryPreference.count(); i++)
        {
            m_listW3WSetup.insert(( (m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_COUNTRY_PREFERENCE] + 1) + i), m_listW3WCountryPreference.at(i));
        }

        endInsertRows();
        m_bIsCountryPreferenceExpanded = true;
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, Insertion Successful", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, Auto Launch Permission is in Expanded State", __FUNCTION__);
    }
}

void CW3WSetupListModel::collapseCountryPreference()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    if(m_bIsCountryPreferenceExpanded)
    {
        beginRemoveRows(QModelIndex(), m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_COUNTRY_PREFERENCE] + 1,
                        (m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_COUNTRY_PREFERENCE] + m_listW3WCountryPreference.count() ));

        for (int i = 0; i < m_listW3WCountryPreference.count(); i++)
        {
            m_listW3WSetup.removeAt(m_mapSetupDataElementIndex[CW3WEnum::W3W_SETUP_COUNTRY_PREFERENCE] + 1);
        }

        endRemoveRows();
        m_bIsCountryPreferenceExpanded = false;
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Country Preference Items deletion Successful", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, Country Preference is in collapsed State", __FUNCTION__);
    }
}

void CW3WSetupListModel::updateCountryPreferenceList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    CW3WEnum::EW3WSetupItems eCountryPreferenceIndex = CW3WEnum::W3W_SETUP_COUNTRY_PREFERENCE_IN;

    if(CW3WApplication::getW3WAdaptor()->getCurrentCountryCode() != "IN")
    {
        eCountryPreferenceIndex = CW3WEnum::W3W_SETUP_COUNTRY_PREFERENCE_ALL;
    }
    else
    {
        /* Do nothing */
    }

    for(int i = 0; i < m_listW3WCountryPreference.count(); i++)
    {
        m_listW3WCountryPreference[i].m_bIsChecked = false;
    }

    m_listW3WCountryPreference[m_mapSetupDataElementIndex[eCountryPreferenceIndex]].m_bIsChecked = true;
}

void CW3WSetupListModel::updateModelForCheckedRole(int iW3WSetupIndex, bool bCheckedStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s iW3WSetupIndex: %d bCheckedStatus: %d", __FUNCTION__, iW3WSetupIndex, bCheckedStatus);
    m_listW3WSetup[iW3WSetupIndex].m_bIsChecked = bCheckedStatus;
}
