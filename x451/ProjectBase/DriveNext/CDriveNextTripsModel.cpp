/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file            CDriveNextTripsModel.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDriveNextTripsModel.h, DriveNext Trips model file, responsible for creating DriveNext trips static list model
 */

#include "CDriveNextTripsModel.h"
#include "logging.h"

CDriveNextTripsModel::CDriveNextTripsModel(QObject *pParent)
    :QAbstractListModel(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    m_objDataList.clear();
    m_objDataList.append(SDriveNextTripData(CDriveNextEnum::EDNTripType::DRIVENEXT_CURRENT_TRIP, tr("TEXT_DN_TRIP_CURRENT"),
                                            "qrc:/image/DriveNext/Gen_Ico_DriveProCurrent_7inch_n-assets/Gen_Ico_DriveProCurrent_7inch_n_LeftSide.png",
                                            "qrc:/image/DriveNext/Gen_Ico_DriveProCurrent_7inch_n-assets/Gen_Ico_DriveProCurrent_7inch_na.png",
                                            "qrc:/image/DriveNext/Gen_Ico_DriveProCurrent_7inch_n-assets/Gen_Ico_DriveProCurrent_7inch_n_RightSide.png" ));
    m_objDataList.append(SDriveNextTripData(CDriveNextEnum::EDNTripType::DRIVENEXT_TRIP_A, tr("TEXT_DN_TRIP_A"),
                                            "qrc:/image/DriveNext/Gen_Ico_DriveProTripA_7inch_n-assets/Gen_Ico_DriveProTripA_7inch_n_LeftSide.png",
                                            "qrc:/image/DriveNext/Gen_Ico_DriveProTripA_7inch_n-assets/Gen_Ico_DriveProTripA_7inch_na.png",
                                            "qrc:/image/DriveNext/Gen_Ico_DriveProTripA_7inch_n-assets/Gen_Ico_DriveProTripA_7inch_n_RightSide.png" ));
    m_objDataList.append(SDriveNextTripData(CDriveNextEnum::EDNTripType::DRIVENEXT_TRIP_B, tr("TEXT_DN_TRIP_B"),
                                            "qrc:/image/DriveNext/Gen_Ico_DriveProTripB_7inch_n-assets/Gen_Ico_DriveProTripB_7inch_n_LeftSide.png",
                                            "qrc:/image/DriveNext/Gen_Ico_DriveProTripB_7inch_n-assets/Gen_Ico_DriveProTripB_7inch_na.png",
                                            "qrc:/image/DriveNext/Gen_Ico_DriveProTripB_7inch_n-assets/Gen_Ico_DriveProTripB_7inch_n_RightSide.png" ));
    m_objDataList.append(SDriveNextTripData(CDriveNextEnum::EDNTripType::DRIVENEXT_OVERALL_TRIP, tr("TEXT_DN_TRIP_OVERALL"),
                                            "qrc:/image/DriveNext/Gen_Ico_DriveProOverall_7inch_n-assets/Gen_Ico_DriveProOverall_7inch_n_LeftSide.png",
                                            "qrc:/image/DriveNext/Gen_Ico_DriveProOverall_7inch_n-assets/Gen_Ico_DriveProOverall_7inch_na.png",
                                            "qrc:/image/DriveNext/Gen_Ico_DriveProOverall_7inch_n-assets/Gen_Ico_DriveProOverall_7inch_n_RightSide.png" ));
    m_objDataList.append(SDriveNextTripData(CDriveNextEnum::EDNTripType::DRIVENEXT_BEST_TRIP, tr("TEXT_DN_TRIP_BEST"),
                                            "qrc:/image/DriveNext/Gen_Ico_DriveProBestTrip_7inch_n-assets/Gen_Ico_DriveProBestTrip_n_LeftSide.png",
                                            "qrc:/image/DriveNext/Gen_Ico_DriveProBestTrip_7inch_n-assets/Gen_Ico_DriveProBestTrip_n_na.png",
                                            "qrc:/image/DriveNext/Gen_Ico_DriveProBestTrip_7inch_n-assets/Gen_Ico_DriveProBestTrip_n_RightSide.png" ));
    m_objDataList.append(SDriveNextTripData(CDriveNextEnum::EDNTripType::DRIVENEXT_LAST_TRIP,tr("TEXT_DN_TRIP_LAST"),
                                            "qrc:/image/DriveNext/Gen_Ico_DriveProLastTrip_7inch_n-assets/Gen_Ico_DriveProLastTrip_n_LeftSide.png",
                                            "qrc:/image/DriveNext/Gen_Ico_DriveProLastTrip_7inch_n-assets/Gen_Ico_DriveProLastTrip_n_na.png",
                                            "qrc:/image/DriveNext/Gen_Ico_DriveProLastTrip_7inch_n-assets/Gen_Ico_DriveProLastTrip_n_RightSide.png" ));
}

CDriveNextTripsModel::~CDriveNextTripsModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
}

int CDriveNextTripsModel::rowCount(const QModelIndex &parent) const
{
    //LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, rowCount : %d ",__FUNCTION__, m_objDataList.count());
    Q_UNUSED(parent)
    return m_objDataList.count();
}

QVariant CDriveNextTripsModel::data(const QModelIndex &iIndex, int iRole) const
{
    //LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    QVariant objData = QVariant();
    int iRow = iIndex.row();
    if (iRow < 0 || iRow >=  m_objDataList.count())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT,"%s, invalid row: %d",__FUNCTION__, iRow);
    }
    else
    {
        switch(iRole)
        {
        case TAB_BAR_COMPONENT_NAME_ROLE:
            objData = m_objDataList[iRow].m_strName;
            break;
        case TAB_BAR_COMPONENT_LEFT_ICON_ROLE:
            objData = m_objDataList[iRow].m_strLeftIcon;
            break;
        case TAB_BAR_COMPONENT_MID_ICON_ROLE:
            objData = m_objDataList[iRow].m_strMidIcon;
            break;
        case TAB_BAR_COMPONENT_RIGHT_ICON_ROLE:
            objData = m_objDataList[iRow].m_strRightIcon;
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT,"%s, invalid role: %d",__FUNCTION__, iRole);
            break;
        }
    }
    return objData;
}

QHash<int, QByteArray> CDriveNextTripsModel::roleNames() const
{
    //LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[TAB_BAR_COMPONENT_NAME_ROLE] = "name";
    roles[TAB_BAR_COMPONENT_LEFT_ICON_ROLE] = "leftIcon";
    roles[TAB_BAR_COMPONENT_MID_ICON_ROLE] = "midIcon";
    roles[TAB_BAR_COMPONENT_RIGHT_ICON_ROLE] = "rightIcon";
    return roles;
}

SDriveNextTripData CDriveNextTripsModel::getElementAt(int index)
{
    SDriveNextTripData obj;
    if (index >= 0 || index < m_objDataList.count())
    {
        obj = m_objDataList[index];
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT,"%s, invalid index: %d",__FUNCTION__, index);
    }
    return obj;
}
