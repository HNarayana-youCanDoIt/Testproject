/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2019
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CSoundDemoAdaptor.cpp
* @ingroup      HMIComponent
* @author       Guru Alingal
* @brief        Adaptor class for sound demo.
*/

#include "CSoundDemoAdaptor.h"
#include "CSoundDemoData.h"
#include "HMIIncludes.h"
#include "CMediaAdaptor.h"

CSoundDemoAdaptor* CSoundDemoAdaptor::m_pInstance = nullptr;

CSoundDemoAdaptor::CSoundDemoAdaptor(QObject *pParent)
    :QObject(pParent),
      m_demoModel(this),
      m_iSelectedTrack(-1)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__)
    qmlRegisterUncreatableType<CSoundDemoModel>("com.harman.qml.SoundDemo", 1, 0, "CSoundDemoModel", "Cannot create instance of CSoundDemoModel in qml");

    m_bDemoAvailable = true;

    connect(CAudioAdaptor::getInstance(), SIGNAL(sigActiveEntSrcChanged()), this, SLOT(sltActiveEntSrcChanged()), Qt::QueuedConnection);
    connect(&CMediaAdaptor::getInstance(), SIGNAL(sigBrowseSessionCreated()), this, SLOT(sltBrowseSessionCreated()), Qt::AutoConnection);
    connect(&CMediaAdaptor::getInstance(), SIGNAL(sigUpdateNowPlayingPointer(int , int )), this, SLOT(sltUpdateNowPlayingPointer(int,int)), Qt::AutoConnection);
    connect(&CMediaAdaptor::getInstance(), SIGNAL(sigBrowseDataReceived(int)), this, SLOT(sltBrowseDataReceived(int)), Qt::AutoConnection);

    setActiveAudioPreset(CAudioAdaptor::getInstance()->activeAudioPreset());
}

void CSoundDemoAdaptor::initModel(CMediaBrowseCategoryListModel* pListModel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__)

    if(pListModel)
    {
        m_demoModel.removeRows();
        m_iSelectedTrack = -1;
        SSoundDemoData data;
        for(int i = 0; i< pListModel->rowCount(); i++)
        {
            data.m_strCaption = pListModel->getBrowseDataFromIndex(i).m_strCategoryItemText;
            data.m_strImagePath = (pListModel->getBrowseDataFromIndex(i).m_bIsActive) ? "qrc:/image/SoundDemo/SoundDemo_Btn_Play_n-assets/SoundDemo_Btn_Pause_n.png"
                                                                                      : "qrc:/image/SoundDemo/SoundDemo_Btn_Play_n-assets/SoundDemo_Btn_Play_n.png";
            data.m_iId = i;
            data.m_iTrackId = pListModel->getBrowseDataFromIndex(i).m_iCategoryItemId;
            data.m_iMinValue = 0;
            data.m_iMaxValue = 100;
            data.m_iCurrentValue = 0;
            data.m_bActive = true;
            data.m_bEnabled = true;
            data.m_bPgbVisibility = pListModel->getBrowseDataFromIndex(i).m_bIsActive;

            m_demoModel.insertRows(data);

            if(pListModel->getBrowseDataFromIndex(i).m_bIsActive)
            {
                m_iSelectedTrack = i;
            }
        }
    }

    emit demoModelChanged();
}

void CSoundDemoAdaptor::sltUpdateNowPlayingPointer(int iOldIndex, int iNewIndex)
{
    updateNowPlayingPointer(iOldIndex, iNewIndex);
}

void CSoundDemoAdaptor::sltBrowseDataReceived(int iCategory)
{
    if((CAudioEnums::SRC_HDD == CAudioAdaptor::getInstance()->activeEntSrc()) &&
            (iCategory == static_cast<int>(CMediaEnum::BROWSEITEM_SONGS)))
    {
        initModel(CMediaAdaptor::getInstance().mediaCategoryListModel());
        CHMIMain::getSM()->raise_evSoundDemoActivated();
    }
}

void CSoundDemoAdaptor::updateDemoModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__)
    emit demoModelChanged();
}

void CSoundDemoAdaptor::updatePlayStateData(int iIndex, bool bState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__);
    QString strImagePath = (bState) ? "qrc:/image/SoundDemo/SoundDemo_Btn_Play_n-assets/SoundDemo_Btn_Pause_n.png"
                                    : "qrc:/image/SoundDemo/SoundDemo_Btn_Play_n-assets/SoundDemo_Btn_Play_n.png";
    m_demoModel.updateRowData(iIndex, strImagePath, m_demoModel.ESoundDemoListRoles::ITEM_IMAGE_ROLE );
}

void CSoundDemoAdaptor::updateNowPlayingPointer(int iOldIndex, int iNewIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__)
    if((m_demoModel.rowCount() > 0) && (m_demoModel.rowCount() >= iOldIndex))
    {
        m_demoModel.updateRowData(iOldIndex, QVariant(false), m_demoModel.ESoundDemoListRoles::ITEM_PGBVISIBILITY_ROLE );
        updatePlayStateData(iOldIndex, false);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s incorrect old index %d", __FUNCTION__, iOldIndex)
    }

    if((m_demoModel.rowCount() > 0) && (m_demoModel.rowCount() >= iNewIndex))
    {
        m_demoModel.updateRowData(iNewIndex, QVariant(true), m_demoModel.ESoundDemoListRoles::ITEM_PGBVISIBILITY_ROLE );
        updatePlayStateData(iNewIndex, CMediaAdaptor::getInstance().isMediaAudioPlaying());
        m_iSelectedTrack = iNewIndex;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s incorrect new index %d", __FUNCTION__, iNewIndex)
    }
}

CSoundDemoAdaptor::~CSoundDemoAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__)
    m_bDemoAvailable = false;
    m_demoModel.removeRows();

    delete m_pInstance;
    m_pInstance = nullptr;
}

CSoundDemoModel *CSoundDemoAdaptor::demoModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__)
    return &m_demoModel;
}

bool CSoundDemoAdaptor::demoAvailable()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__)
    return m_bDemoAvailable;
}

void CSoundDemoAdaptor::setDemoAvailable(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__)
    if(m_bDemoAvailable != bStatus)
    {
        m_bDemoAvailable = bStatus;
        emit demoAvailableChanged();
    }
}

CSoundDemoAdaptor *CSoundDemoAdaptor::getInstance()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__)
    if(nullptr == m_pInstance)
    {
        m_pInstance = new CSoundDemoAdaptor();
    }

    return m_pInstance;
}

void CSoundDemoAdaptor::sltMediaPlayTime()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__);
    if(CAudioEnums::SRC_HDD == CAudioAdaptor::getInstance()->activeEntSrc())
    {
        m_demoModel.updateRowData(m_iSelectedTrack, QVariant(CMediaAdaptor::getInstance().totalDuration()), m_demoModel.ESoundDemoListRoles::ITEM_MAX_VAL_ROLE );
        m_demoModel.updateRowData(m_iSelectedTrack, QVariant(CMediaAdaptor::getInstance().playTime()), m_demoModel.ESoundDemoListRoles::ITEM_CURR_VAL_ROLE );
    }
}

void CSoundDemoAdaptor::sltMediaPlayState()
{
    updatePlayStateData(m_iSelectedTrack, CMediaAdaptor::getInstance().isMediaAudioPlaying());
}

void CSoundDemoAdaptor::sltActiveEntSrcChanged()
{
    if(CAudioEnums::SRC_HDD == CAudioAdaptor::getInstance()->activeEntSrc())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s connected to playstate and playtime", __FUNCTION__);
        CMediaAdaptor::getInstance().initBrowse(CMediaEnum::BROWSEITEM_SONGS);
        connect(&CMediaAdaptor::getInstance(), SIGNAL(sigPlayStateChanged()), this, SLOT(sltMediaPlayState()), Qt::QueuedConnection);
        connect(&CMediaAdaptor::getInstance(), SIGNAL(sigPlayTimeChanged()), this, SLOT(sltMediaPlayTime()), Qt::QueuedConnection);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s disconnected to playstate and playtime", __FUNCTION__);
        disconnect(&CMediaAdaptor::getInstance(), SIGNAL(sigPlayStateChanged()));
        disconnect(&CMediaAdaptor::getInstance(), SIGNAL(sigPlayTimeChanged()));
    }
}

void CSoundDemoAdaptor::sltBrowseSessionCreated()
{
    if(CAudioEnums::SRC_HDD == CAudioAdaptor::getInstance()->activeEntSrc())
    {
        CMediaAdaptor::getInstance().initBrowse(CMediaEnum::BROWSEITEM_SONGS);
    }
}

CAudioEnums::EAudioPresets CSoundDemoAdaptor::getActiveAudioPreset() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__);
    return m_activeAudioPreset;
}

void CSoundDemoAdaptor::setActiveAudioPreset(const CAudioEnums::EAudioPresets &activeAudioPreset)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__);
    m_activeAudioPreset = activeAudioPreset;
}

void CSoundDemoAdaptor::invSelectTrack(int iIndex, int iTrackId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s iIndex: %d iTrackId: %d m_iSelectedTrack: %d", __FUNCTION__, iIndex, iTrackId, m_iSelectedTrack);
    if(m_iSelectedTrack == iIndex)
    {
        CMediaAdaptor::getInstance().toggleResumePause(CMediaEnum::EN_BUTTON_STATE_RELEASED);
    }
    else if(-1 != iIndex)
    {
        updateNowPlayingPointer(m_iSelectedTrack, iIndex);
        m_iSelectedTrack = iIndex;
        CMediaAdaptor::getInstance().browseItemClicked(iTrackId, CMediaEnum::BROWSEITEM_SONGS, "", -1, iIndex);
    }/*else{//Do Nothing} */
}

