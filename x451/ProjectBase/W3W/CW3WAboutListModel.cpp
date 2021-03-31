/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CW3WAboutListModel.cpp
 * @ingroup       HMIComponent
 * @author        Nishant Khandagale
 * @brief         Contain implementation of all the methods declared in
 * CW3WAboutListModel class
 */

#include "CW3WAboutListModel.h"
#include "logging.h"
#include "CW3WEnum.h"
#include "CW3WAdaptor.h"
#include "CW3WApplication.h"

CW3WAboutListModel::CW3WAboutListModel(QObject *pParent) :
    QAbstractListModel(pParent),
    m_iExpandedItemIndex(CW3WEnum::W3W_ABOUT_INVALID)

{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    initW3WAboutModel();
    initW3WAboutDescriptionModel();
}

CW3WAboutListModel::~CW3WAboutListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    m_listW3WAbout.clear();
    m_listW3WAboutDescription.clear();
}

/************************************************************************//**
 * @category    OVERRIDEN METHODS of QAbstractListModel class
 ************************************************************************/
QHash<int, QByteArray> CW3WAboutListModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[W3W_ABOUT_ITEM_TEXT_ROLE]           = "itemTextRole";
    roles[W3W_ABOUT_ITEM_ENABLED_ROLE]        = "itemEnabledRole";
    roles[W3W_ABOUT_ITEM_TYPE_ROLE]           = "itemTypeRole";
    roles[W3W_ABOUT_ITEM_ID_ROLE]             = "itemId";
    return roles;
}

QVariant CW3WAboutListModel::data(const QModelIndex &index, int role) const
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    QVariant objRowData;
    int iRowIndex = index.row();
    if (index.isValid())
    {
        EW3WAboutListRoles eW3WAboutRole = static_cast<EW3WAboutListRoles>(role);
        switch(eW3WAboutRole)
        {
        case W3W_ABOUT_ITEM_TEXT_ROLE:
            objRowData = m_listW3WAbout.at(iRowIndex).m_strName;
            break;
        case W3W_ABOUT_ITEM_ENABLED_ROLE:
            objRowData = m_listW3WAbout.at(iRowIndex).m_bIsEnabled;
            break;
        case W3W_ABOUT_ITEM_TYPE_ROLE:
            objRowData = m_listW3WAbout.at(iRowIndex).m_eW3WItemType;
            break;
        case W3W_ABOUT_ITEM_ID_ROLE:
            objRowData = m_listW3WAbout.at(iRowIndex).m_iItemId;
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

int CW3WAboutListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listW3WAbout.count();
}

bool CW3WAboutListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s : Role:%d, Index:%d ", __FUNCTION__, role, index.row());
    bool bReturnValue = false;
    if(index.isValid())
    {
        int iRowIndex = index.row();
        switch(role)
        {
        case W3W_ABOUT_ITEM_ENABLED_ROLE:
        {
            bool bIsW3WItemEnabled = value.toBool();
            if(bIsW3WItemEnabled != m_listW3WAbout[iRowIndex].m_bIsEnabled)
            {
                m_listW3WAbout[iRowIndex].m_bIsEnabled = bIsW3WItemEnabled;
                bReturnValue = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_W3W, "W3W About Item enable state not changed");
            }
        }
            break;

        case W3W_ABOUT_ITEM_TEXT_ROLE:
        {
            const QString &strItemName = value.toString();
            if(strItemName.compare(m_listW3WAbout[iRowIndex].m_strName) != 0)
            {
                m_listW3WAbout[iRowIndex].m_strName = strItemName;
                bReturnValue = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_W3W, "W3W About Item name not changed");
            }
        }
            break;

        case W3W_ABOUT_ITEM_ID_ROLE:
        {

            int iW3WSetupDropDownId = value.toInt();
            if(iW3WSetupDropDownId != m_listW3WAbout[iRowIndex].m_iItemId)
            {
                m_listW3WAbout[iRowIndex].m_iItemId = iW3WSetupDropDownId;
                bReturnValue = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_W3W, "W3W About Item Dropdown Id not changed");

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

bool CW3WAboutListModel::isItemEnabled(CW3WEnum::EW3WAboutItems eItemIndex)
{
    bool bEnabled = false;
    switch(eItemIndex)
    {
    case CW3WEnum::W3W_ABOUT_ITEM_1:
    case CW3WEnum::W3W_ABOUT_ITEM_2:
        bEnabled = true;
        break;

    default:
        break;
    }
    return bEnabled;
}

void CW3WAboutListModel::initW3WAboutModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    m_listW3WAbout.clear();

    m_listW3WAbout.append(CW3WData::SW3WSetupData(tr("TEXT_W3W_ABOUT_ITEM1"),
                                                  isItemEnabled(CW3WEnum::W3W_ABOUT_ITEM_1), false,
                                                  CW3WEnum::ITEM_TYPE_LABEL_WITH_DROPDOWN, CW3WEnum::W3W_ABOUT_ITEM_1));

    m_listW3WAbout.append(CW3WData::SW3WSetupData (tr("TEXT_W3W_ABOUT_ITEM2"),
                                                   isItemEnabled(CW3WEnum::W3W_ABOUT_ITEM_2), false,
                                                   CW3WEnum::ITEM_TYPE_LABEL_WITH_DROPDOWN, CW3WEnum::W3W_ABOUT_ITEM_2));
}

void CW3WAboutListModel::initW3WAboutDescriptionModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);

    m_listW3WAboutDescription.clear();

    /* Language.csv automatically adds "" for this text (TEXT_W3W_ABOUT_ITEM1_DESCRIPTION), so using the text directly in code */
    m_listW3WAboutDescription.append(CW3WData::SW3WSetupData(
                                         tr("Tata with what3words makes navigation easier than ever before. what3words has assigned every 3m square in the world a unique 3 word address, which means you can drive to any precise location by simply saying three words.\nFor example ///masterpiece.above.names marks an exact entrance to India Gate, New Delhi."),
                                         true, false, CW3WEnum::ITEM_TYPE_LABEL, CW3WEnum::W3W_ABOUT_ITEM_1));

    /* Language.csv automatically adds "" for this text (TEXT_W3W_ABOUT_ITEM2_DESCRIPTION), so using the text directly in code */
    m_listW3WAboutDescription.append(CW3WData::SW3WSetupData(
                                         tr("Know the 3 word address for where you are going. Enter the 3 word address by voice or text. Pick the desired address from the suggestion list. Start navigating and arrive at your precise destination. Furthermore, you can Share the entered 3 word address via SMS or Save it as favorite too."),
                                            true, false, CW3WEnum::ITEM_TYPE_LABEL, CW3WEnum::W3W_ABOUT_ITEM_2));

}

void CW3WAboutListModel::expandAboutItem(int iItemIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);

    collapseAboutItem();

    if(m_iExpandedItemIndex != iItemIndex)
    {
        if( CW3WEnum::W3W_ABOUT_ITEM_1 <= iItemIndex &&
                m_listW3WAbout.count() > iItemIndex )
        {
            beginInsertRows(QModelIndex(), iItemIndex + 1, iItemIndex + 1);
            m_listW3WAbout.insert((iItemIndex + 1), m_listW3WAboutDescription.at(iItemIndex));
            endInsertRows();
            m_iExpandedItemIndex = iItemIndex;
            LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, Insertion Successful", __FUNCTION__);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Out of bound About Item (%d)", __FUNCTION__, iItemIndex);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, About (%d) is in Exapanded State", __FUNCTION__, iItemIndex);
    }
}

void CW3WAboutListModel::collapseAboutItem()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    if(CW3WEnum::W3W_ABOUT_INVALID != m_iExpandedItemIndex)
    {
        if( CW3WEnum::W3W_ABOUT_ITEM_1 <= m_iExpandedItemIndex &&
                m_listW3WAboutDescription.count() > m_iExpandedItemIndex )
        {
            beginRemoveRows(QModelIndex(), m_iExpandedItemIndex + 1, m_iExpandedItemIndex + 1);
            m_listW3WAbout.removeAt(m_iExpandedItemIndex + 1);
            endRemoveRows();
            m_iExpandedItemIndex = static_cast<int>(CW3WEnum::W3W_ABOUT_INVALID);
            LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, About Items deletion Successful", __FUNCTION__);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Out of bound About Item (%d)", __FUNCTION__, m_iExpandedItemIndex);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, About is in collapsed State", __FUNCTION__);
    }
}

