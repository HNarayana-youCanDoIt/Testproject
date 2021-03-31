/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CMediaOffAdaptor.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CMediaOffAdaptor, an Adaptor for Media Off module,
 * CMediaOffAdaptor is singleton class used to communicate with qml, resources of Media Off module.
 */

#include "ResourceFactory.hpp"
#include "HMIIncludes.h"

#include "CMediaOffApplication.h"
#include "CMediaOffAdaptor.h"
#include "CMediaOffSM.h"
#include "CMediaOffEventHandler.h"
#include "CClockEnum.h"
#include "CDClockInformation.h"
#include "CPersistencyAdaptor.h"

CMediaOffAdaptor* CMediaOffAdaptor::mpMediaOffAdaptor = nullptr;

///////////////////////////////////////////////////////////////////////////////
// Adaptor related functions
///////////////////////////////////////////////////////////////////////////////
CMediaOffAdaptor& CMediaOffAdaptor::getInstance()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF,__FUNCTION__);
    if (nullptr == mpMediaOffAdaptor)
    {
        mpMediaOffAdaptor = new CMediaOffAdaptor();
    }
    return *mpMediaOffAdaptor;
}
//____________________________________________________________________________
CMediaOffAdaptor::CMediaOffAdaptor(QObject *parent) : QObject(parent),
    m_bMediaOffScreenStatus(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF,__FUNCTION__);
    CFramework::getFramework().setContextProperty("cppMediaOffAdaptor",this);
    initAdaptorProperties();
}
//____________________________________________________________________________
CMediaOffAdaptor::~CMediaOffAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF,__FUNCTION__);
    clearClockInformationList();
    mpMediaOffAdaptor = nullptr;
}
//____________________________________________________________________________
void CMediaOffAdaptor::initAdaptorProperties()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF,__FUNCTION__);
    CClockEnum::registerClockEnumsToQML();
    clearClockInformationList();

    m_lCDClockInformations.append(new CDClockInformation(m_lCDClockInformations.count(), CClockEnum::LAYOUT_ANALOG, CClockEnum::MOTION_JUMP,
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_Classic_7in_n-assets/Classic_02_WithNumbers.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic2_White_7in_n-assets/Gen_Gxf_WatchHandRound_n.png",
                                                         "",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic2_White_7in_n-assets/Gen_Gfx_WatchHandHours_n.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic2_White_7in_n-assets/Gen_Gfx_WatchHandHours_n_shadow.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic2_White_7in_n-assets/Gen_Gxf_WatchHandMin_n.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic2_White_7in_n-assets/Gen_Gxf_WatchHandMin_n_shadow.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic2_White_7in_n-assets/Gen_Gxf_WatchHandSecond_n.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic2_White_7in_n-assets/Gen_Gxf_WatchHandSecond_n_shadow.png",
                                                         this));

    m_lCDClockInformations.append(new CDClockInformation(m_lCDClockInformations.count(), CClockEnum::LAYOUT_ANALOG, CClockEnum::MOTION_ELASTIC,
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_Classic_7in_n-assets/Classic_01_WithNumbers.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic1_Black_7in_n-assets/Gen_Gxf_WatchHandRound_n.png",
                                                         "",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic1_Black_7in_n-assets/Gen_Gfx_WatchHandHours_n.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic1_Black_7in_n-assets/Gen_Gfx_WatchHandHours_n_shadow.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic1_Black_7in_n-assets/Gen_Gxf_WatchHandMin_n.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic1_Black_7in_n-assets/Gen_Gxf_WatchHandMin_n_shadow.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic1_Black_7in_n-assets/Gen_Gxf_WatchHandSecond_n.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic1_Black_7in_n-assets/Gen_Gxf_WatchHandSecond_n_shadow.png",
                                                         this));

    m_lCDClockInformations.append(new CDClockInformation(m_lCDClockInformations.count(), CClockEnum::LAYOUT_ANALOG, CClockEnum::MOTION_SWITCH,
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_Minimal_7in_n-assets/Minimal_01.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Minimal1_7in_n-assets/Gen_Gxf_Minimal01_WatchHandRound_n.png",
                                                         "",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Minimal1_7in_n-assets/Gen_Gfx_Minimal01_WatchHandHours_n.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Minimal1_7in_n-assets/Gen_Gfx_Minimal01_WatchHandHours_n_shadow.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Minimal1_7in_n-assets/Gen_Gxf_Minimal01_WatchHandMin_n.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Minimal1_7in_n-assets/Gen_Gxf_Minimal01_WatchHandMin_n_shadow.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Minimal1_7in_n-assets/Gen_Gxf_Minimal01_WatchHandSec_n.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Minimal1_7in_n-assets/Gen_Gxf_Minimal01_WatchHandSec_n_shadow.png",
                                                         this));
    m_lCDClockInformations.append(new CDClockInformation(m_lCDClockInformations.count(), CClockEnum::LAYOUT_ANALOG, CClockEnum::MOTION_SMOOTH,
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_Minimal_7in_n-assets/Minimal_02.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Minimal2_7in_n-assets/Gen_Gxf_WatchHandRound_n.png",
                                                         "",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Minimal2_7in_n-assets/Gen_Gfx_WatchHandHours_n.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Minimal2_7in_n-assets/Gen_Gfx_WatchHandHours_n_shadow.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Minimal2_7in_n-assets/Gen_Gxf_WatchHandMin_n.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Minimal2_7in_n-assets/Gen_Gxf_WatchHandMin_n_shadow.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Minimal2_7in_n-assets/Gen_Gxf_WatchHandSec_n.png",
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Minimal2_7in_n-assets/Gen_Gxf_WatchHandSec_n_shadow.png",
                                                         this));
    m_lCDClockInformations.append(new CDClockInformation(m_lCDClockInformations.count(), CClockEnum::LAYOUT_DIGITAL, CClockEnum::MOTION_UNDEFINED,
                                                         "qrc:/Assets/MediaOff/Gen_Gfx_DigitalClock_Bg/Gen_Gfx_DigitalClock_Bg.png"));
    //m_lCDClockInformations.append(new CDClockInformation(m_lCDClockInformations.count(), CClockEnum::LAYOUT_ANALOG, CClockEnum::MOTION_SWITCH,
    //                                                     "qrc:/Assets/MediaOff/Gen_Gfx_Classic_7in_n-assets/Classic_01.png",
    //                                                     "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic1_Black_7in_n-assets/Gen_Gxf_WatchHandRound_n.png",
    //                                                     "",
    //                                                     "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic1_Black_7in_n-assets/Gen_Gfx_WatchHandHours_n.png",
    //                                                     "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic1_Black_7in_n-assets/Gen_Gfx_WatchHandHours_n_shadow.png",
    //                                                     "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic1_Black_7in_n-assets/Gen_Gxf_WatchHandMin_n.png",
    //                                                     "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic1_Black_7in_n-assets/Gen_Gxf_WatchHandMin_n_shadow.png",
    //                                                     "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic1_Black_7in_n-assets/Gen_Gxf_WatchHandSecond_n.png",
    //                                                     "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic1_Black_7in_n-assets/Gen_Gxf_WatchHandSecond_n_shadow.png",
    //                                                     this));
    //m_lCDClockInformations.append(new CDClockInformation(m_lCDClockInformations.count(), CClockEnum::LAYOUT_ANALOG, CClockEnum::MOTION_SMOOTH,
    //                                                     "qrc:/Assets/MediaOff/Gen_Gfx_Classic_7in_n-assets/Classic_02.png",
    //                                                     "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic2_White_7in_n-assets/Gen_Gxf_WatchHandRound_n.png",
    //                                                     "",
    //                                                     "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic2_White_7in_n-assets/Gen_Gfx_WatchHandHours_n.png",
    //                                                     "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic2_White_7in_n-assets/Gen_Gfx_WatchHandHours_n_shadow.png",
    //                                                     "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic2_White_7in_n-assets/Gen_Gxf_WatchHandMin_n.png",
    //                                                     "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic2_White_7in_n-assets/Gen_Gxf_WatchHandMin_n_shadow.png",
    //                                                     "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic2_White_7in_n-assets/Gen_Gxf_WatchHandSecond_n.png",
    //                                                     "qrc:/Assets/MediaOff/Gen_Gfx_WatchHand_Classic2_White_7in_n-assets/Gen_Gxf_WatchHandSecond_n_shadow.png",
    //                                                     this));
    emit sigClockInformationListChanged();
    int prevSelectedUId = CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_SELECTED_CLOCK_ID);

    //Validate previously selected clock UId
    if ((prevSelectedUId < 0) && (prevSelectedUId >= m_lCDClockInformations.count()))
    {
        prevSelectedUId = 0;
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_SELECTED_CLOCK_ID, prevSelectedUId);
    }
    setSelectedClockId(prevSelectedUId);
}
//____________________________________________________________________________
QList<QObject *> CMediaOffAdaptor::clockInformationList()
{
    return m_lCDClockInformations;
}
//____________________________________________________________________________
void CMediaOffAdaptor::clearClockInformationList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s", __FUNCTION__);
    qDeleteAll(m_lCDClockInformations.begin(), m_lCDClockInformations.end());
    m_lCDClockInformations.clear();
    emit sigClockInformationListChanged();
}

///////////////////////////////////////////////////////////////////////////////
// property related functions
///////////////////////////////////////////////////////////////////////////////
int CMediaOffAdaptor::selectedClockId()
{
    return m_iSelectedClockId;
}

void CMediaOffAdaptor::setSelectedClockId(int _value)
{
    if (m_iSelectedClockId != _value)
    {
        m_iSelectedClockId = _value;
        sigSelectedClockIdChanged();
    }
    else
    {
        //// No change in value
    }
}

bool CMediaOffAdaptor::mediaOffScreenStatus()
{
    return m_bMediaOffScreenStatus;
}

void CMediaOffAdaptor::setMediaOffScreenStatus(bool bMediaOffScreenStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s: bMediaOffScreenStatus : %d", __FUNCTION__, bMediaOffScreenStatus);
    if(m_bMediaOffScreenStatus != bMediaOffScreenStatus)
    {
        m_bMediaOffScreenStatus = bMediaOffScreenStatus;
        emit sigMediaOffScreenStatusChanged();
    }
}

///////////////////////////////////////////////////////////////////////////////
// QML related functions
///////////////////////////////////////////////////////////////////////////////
void CMediaOffAdaptor::invSetDrawersVisibility(bool bIsVisible)
{
    if(bIsVisible)
    {
        CHMIMain::getSM()->getSCI_Drawers()->raise_evShowDrawers();
    }
    else
    {
        CHMIMain::getSM()->getSCI_Drawers()->raise_evHideDrawers();
    }
}
//____________________________________________________________________________
