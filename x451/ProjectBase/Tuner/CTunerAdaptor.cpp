/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CTunerAdaptor.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Balyan
 * CTunerAdaptor, an adaptor for tuner module which help tuner application layer
 *                to communicate with resource layer, QML layer and state machine
**/

#include "CTunerAdaptor.h"
#include "CHardkeyAdaptor.h"
#include "ResourceFactory.hpp"
#include "CPhoneAdaptor.h"
#include <QTimer>

CTunerAdaptor* CTunerAdaptor::m_pTunerAdaptor = nullptr;

CTunerAdaptor::CTunerAdaptor(QObject *parent) : QObject(parent),
    AM_FREQ_STEP_SIZE(9),
    FM_FREQ_STEP_SIZE(100),
    AM_AVAIL_FREQ_COUNT(120),
    FM_AVAIL_FREQ_COUNT(210),
    AM_STARTING_FREQ(531),
    FM_STARTING_FREQ(87500),
    AM_LAST_FREQ(1602),
    FM_LAST_FREQ(108000),
    MAX_LINE_DIVIDER(2),
    MID_LINE_DIVIDER(5),
    MAX_LINE_HEIGHT(96),
    MID_LINE_HEIGHT(73),
    MIN_LINE_HEIGHT(43),
    PRESET_TILES_PER_PAGE(5),
    INVALID_PRESET_INDEX(-1),
    MAX_PRESETS(20),
    m_uiFrequency(0),
    m_uiAMFrequency(0),
    m_uiFMFrequency(0),
    m_uiCurrentResourceFrequency(0),
    m_strFrequency(""),
    m_strFrequencyUnit(""),
    m_strBand(""),
    m_eSeekType(CTunerEnums::SEEK_INVALID),
    m_eBandType(CTunerEnums::BAND_INVALID),
    m_strTunerState(""),
    m_iManualScaleIndex(0),
    m_bManualSeekStatus(false),
    m_strStationName(""),
    m_iFieldStrength(-1),
    m_ucMultipath(0),
    m_iActivePresetIndex(-1),
    m_uiSelectedPresetFrequency(0),
    m_iSelectedPresetIndex(-1),
    m_uiTagId(0),
    m_iPresetListPageIndex(0),
    m_bPresetListEmptyStatus(true),
    m_bIsTunerEnabled(false),
    m_bTunerDataAvailableStatus(false),
    m_bTunerMainScreenQMLStatus(false),
    m_bAutoStoreSuccessStatus(false),
    m_bBlockManualSeek(false),
    m_pTunerResource(ResourceFactory::getTunerResource())
{
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"CTunerAdaptor::CTunerAdaptor");
    CTunerEnums::registerTunerEnumsToQML();
    CFramework::getFramework().setContextProperty("cppTunerAdaptor",this);
    m_liAMManualScaleFreq.clear();
    m_liFMManualScaleFreq.clear();
    m_liTunerPresetList.clear();
    initializeAMManualSeekListModel();
    initializeFMManualSeekListModel();
    setPresetList();
    connect(CDrawersAdaptor::getInstance(), SIGNAL(sigQadDrawerStateChanged()), this, SLOT(sltDrawerStateChanged()));
    connect(CDrawersAdaptor::getInstance(), SIGNAL(sigShortcutDrawerStateChanged()), this, SLOT(sltDrawerStateChanged()));
    connect(&m_objTunerManualSeekTimer, SIGNAL(timeout()), this, SLOT(sltTimerComplete()));
    connect(CAudioAdaptor::getInstance(), SIGNAL(sigActiveEntSrcChanged()), this, SLOT(sltActiveEntSrcUpdated()));
    connect(CAudioAdaptor::getInstance(), SIGNAL(sigActiveAudioSourceListUpdated()), this, SLOT(sltActiveInteruptSrcUpdated()));
}

CTunerAdaptor::~CTunerAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"CTunerAdaptor::~CTunerAdaptor");
    if(m_pTunerAdaptor)
    {
        delete m_pTunerAdaptor;
        m_pTunerAdaptor = nullptr;
    }

    m_liTunerPresetList.clear();
}

CTunerAdaptor* CTunerAdaptor::getInstance()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"CTunerAdaptor::getInstance");
    if (nullptr == m_pTunerAdaptor)
    {
        m_pTunerAdaptor = new CTunerAdaptor();
    }
    return m_pTunerAdaptor;
}

void CTunerAdaptor::initializeFMManualSeekListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    if(m_liFMManualScaleFreq.isEmpty())
    {
        int iFreq;
        int iFreqIndex = MID_LINE_DIVIDER;

        /*
        * For manual frequency scale we have to make frequency unit lines and
        * then need to arrange them as per the frequency unit index to form a scale.
        * Below logic is to fill m_objTunerManualScaleListModel with indexfrequency and height of the frequency unit lines.
        * Index will begin with the line with medium height of 63 pixels because starting freq for FM is 87.5
        * that's why iFreqIndex is started with 5 and then from iFreqIndex 6 to 9 frequency lines height
        * will be smallest which is 50 pixels and for index 10 it will be 80 pixels and this will continue
        * till iFreqIndex is smaller than FM_AVAIL_FREQ_COUNT + 5
        * iFreqIndex : starting freq for tuner will have MID_LINE_HEIGHT that's why starting index will be 5.
        **/
        for(int iIndex = 0; iIndex < FM_AVAIL_FREQ_COUNT; ++iIndex)
        {
            iFreq = FM_STARTING_FREQ + (FM_FREQ_STEP_SIZE * iIndex);
            m_liFMManualScaleFreq.append(iFreq);

            SManualTuningScaleData *pSManualTuningScaleData = new SManualTuningScaleData();
            pSManualTuningScaleData->m_iScaleIndexFreqValue = iFreq;

            if(0 == (iFreqIndex % MID_LINE_DIVIDER))
            {
                if(0 == (iFreqIndex % MAX_LINE_DIVIDER))
                {

                    pSManualTuningScaleData->m_iScaleIndexHeight = MAX_LINE_HEIGHT;
                }
                else
                {
                    pSManualTuningScaleData->m_iScaleIndexHeight = MID_LINE_HEIGHT;
                }
            }
            else
            {
                pSManualTuningScaleData->m_iScaleIndexHeight = MIN_LINE_HEIGHT;
            }

            m_objTunerFMManualScaleListModel.insertRows(pSManualTuningScaleData);
            ++iFreqIndex;
        }
    }
}

void CTunerAdaptor::initializeAMManualSeekListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    if(m_liAMManualScaleFreq.isEmpty())
    {
        int iFreq;
        int iFreqIndex = MID_LINE_DIVIDER;

        /*
        * For manual frequency scale we have to make frequency unit lines and
        * then need to arrange them as per the frequency unit index to form a scale.
        * Below logic is to fill m_objTunerManualScaleListModel with indexfrequency and height of the frequency unit lines.
        * Index will begin with the line with medium height of 63 pixels because starting freq for FM is 531
        * that's why iFreqIndex is started with 5 and then from iFreqIndex 6 to 9 frequency lines height
        * will be smallest which is 50 pixels and for index 10 it will be 80 pixels and this will continue
        * till iFreqIndex is smaller than AM_AVAIL_FREQ_COUNT + 5
        * iFreqIndex : starting freq for tuner will have MID_LINE_HEIGHT that's why starting index will be 5.
        **/
        for(int iIndex = 0; iIndex < AM_AVAIL_FREQ_COUNT; ++iIndex)
        {
            iFreq = AM_STARTING_FREQ + (AM_FREQ_STEP_SIZE * iIndex);
            m_liAMManualScaleFreq.append(iFreq);

            SManualTuningScaleData *pSManualTuningScaleData = new SManualTuningScaleData();
            pSManualTuningScaleData->m_iScaleIndexFreqValue = iFreq;

            if(0 == (iFreqIndex % MID_LINE_DIVIDER))
            {
                if(0 == (iFreqIndex % MAX_LINE_DIVIDER))
                {

                    pSManualTuningScaleData->m_iScaleIndexHeight = MAX_LINE_HEIGHT;
                }
                else
                {
                    pSManualTuningScaleData->m_iScaleIndexHeight = MID_LINE_HEIGHT;
                }
            }
            else
            {
                pSManualTuningScaleData->m_iScaleIndexHeight = MIN_LINE_HEIGHT;
            }

            m_objTunerAMManualScaleListModel.insertRows(pSManualTuningScaleData);
            ++iFreqIndex;
        }
    }
}

void CTunerAdaptor::setTunerManualScaleIndex()
{
    int index = (CTunerEnums::BAND_AM == eBandType()) ? m_liAMManualScaleFreq.indexOf(m_uiFrequency) : m_liFMManualScaleFreq.indexOf(m_uiFrequency);
    setManualScaleIndex(index);
}

void CTunerAdaptor::introspectionProxyAvailable()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s", __FUNCTION__);
    if(m_pTunerResource)
    {
        m_pTunerResource->enableQualityMonitor (true);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_TUNER,"m_pTunerResource is null");
    }
}

bool CTunerAdaptor::isTunerAntennaConnected()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, Tuner Antenna status : %d", __FUNCTION__, CDiagnosticAdaptor::getInstance()->antennaConnectionStatus());
    // Requirement to show antenna not connected popup has been removed from TML side
    // That's why not changing code, only returning true for tuner connection status(isTunerAntennaConnected).
    //    bool bRes = true;
    //    if(CDiagnosticEnum::CONNECTED != CDiagnosticAdaptor::getInstance()->antennaConnectionStatus())
    //    {
    //        CAudioAdaptor::getInstance()->playBeep(CAudioEnums::BEEP_TYPE_CONFIRM);
    //        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_TUNER_ANTENNA_NOT_CONNECTED_POPUP);
    //        bRes = false;
    //    }
    //    else
    //    {
    //        //do nothing
    //    }
    return true;
}

void CTunerAdaptor::initPresetList()
{
    m_liTunerPresetList.clear();
    m_vecPresetList.clear();
    for(int i = 0; i < MAX_PRESETS ; i++)
    {
        m_liTunerPresetList.append("");
        m_vecPresetList.append(0);
    }
    emit sigPresetTilesListChanged();
}

void CTunerAdaptor::setPresetList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);

    initPresetList();
    int iPresetFrequency;
    QString strPresetFrequency;
    m_bPresetListEmptyStatus = true;

    if (m_pTunerResource)
    {

        for (int iPresetIndex = 0; iPresetIndex < MAX_PRESETS ; iPresetIndex++)
        {
            iPresetFrequency = m_pTunerResource->getPresetList()[iPresetIndex];
            LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, m_iPresetFrequency : %d, m_iPresetindex : %d",__FUNCTION__, iPresetFrequency,iPresetIndex);

            if(iPresetFrequency != 0)
            {
                if(CTunerEnums::BAND_AM == m_eBandType)
                {
                    strPresetFrequency = QString::number(iPresetFrequency);
                }
                else if(CTunerEnums::BAND_FM == m_eBandType)
                {
                    strPresetFrequency =  QString::number(((double)iPresetFrequency/1000), 'f', 1);
                }
                else
                {
                    // do nothing
                }

                m_liTunerPresetList.replace(iPresetIndex, strPresetFrequency);
                m_vecPresetList.replace(iPresetIndex, iPresetFrequency);
                m_bPresetListEmptyStatus = false;
            }
        }

        selectActivePreset();

        emit sigPresetTilesListChanged();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_TUNER,"m_pTunerResource is null");
    }
}

void CTunerAdaptor::selectActivePreset()
{
    LOG_WARNING(Log::e_LOG_CONTEXT_TUNER,"%s", __FUNCTION__);

    if(!m_bPresetListEmptyStatus)
    {
        if(m_uiSelectedPresetFrequency != m_uiFrequency)
        {
            int iFrequency = static_cast<int>(m_uiFrequency);//cast the unsigned int to an int since it may store a -1 value
            if((INVALID_PRESET_INDEX != m_iSelectedPresetIndex) && (m_vecPresetList.at(m_iSelectedPresetIndex) == iFrequency))
            {
                setActivePresetIndex(m_iSelectedPresetIndex);
                m_uiSelectedPresetFrequency = m_uiFrequency;
            }
            else
            {
                setActivePresetIndex(m_vecPresetList.indexOf(iFrequency));
				m_uiSelectedPresetFrequency = m_uiFrequency;
            }

            if(INVALID_PRESET_INDEX != m_iActivePresetIndex)
            {
                selectPresetListPageIndex();
            }
            else
            {
                m_uiSelectedPresetFrequency = 0;
            }
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "Preset List is Empty");
    }
}

void CTunerAdaptor::selectPresetListPageIndex()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, CurrentActivePreset : %d", __FUNCTION__, m_iActivePresetIndex);
    int iPresetListPageIndex;
    if(INVALID_PRESET_INDEX != m_iActivePresetIndex)
    {
        iPresetListPageIndex = m_iActivePresetIndex / PRESET_TILES_PER_PAGE;
    }
    else
    {
        iPresetListPageIndex = 0;
    }
    setPresetListPageIndex(iPresetListPageIndex);
}

void CTunerAdaptor::setManualSeekBlockStatus(bool bStatus)
{
    if(bStatus != m_bBlockManualSeek)
    {
        m_bBlockManualSeek = bStatus;
    }
}

void CTunerAdaptor::setAutoStoreCompleteSuccessStatus(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, m_bAutoStoreSuccessStatus : %d", __FUNCTION__, m_bAutoStoreSuccessStatus);
    if(!bStatus)
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_NO_VALID_STATION_FOUND_POPUP);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, Valid stations found during autostore", __FUNCTION__);
    }
    m_bAutoStoreSuccessStatus = bStatus;
}

void CTunerAdaptor::requestPresetPlayDown()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s", __FUNCTION__);

    if(!m_bPresetListEmptyStatus)
    {
        int iIndex = m_iActivePresetIndex - 1;

        if(0 >= m_iActivePresetIndex)
        {
            iIndex = MAX_PRESETS - 1;
        }
        else
        {
            // Do nothing
        }

        for(int iCounter = 0; iCounter < MAX_PRESETS; iIndex--, iCounter++)
        {
            if(0 != m_vecPresetList.at(iIndex))
            {
                selectPreset(iIndex);
                setPresetListPageIndex(iIndex / PRESET_TILES_PER_PAGE);
                break;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "Preset frequency zero, Index : %d", iIndex)
            }

            if(0 == iIndex)
            {
                iIndex = MAX_PRESETS;
            }
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "Preset List is Empty");
    }
}

void CTunerAdaptor::requestPresetPlayUp()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s", __FUNCTION__);

    if(!m_bPresetListEmptyStatus)
    {
        int iIndex = m_iActivePresetIndex + 1;

        if((MAX_PRESETS - 1) == m_iActivePresetIndex)
        {
            iIndex = 0;
        }

        for(int iCounter = 0; iCounter < MAX_PRESETS; iIndex++, iCounter++)
        {
            if(0 != m_vecPresetList.at(iIndex))
            {
                selectPreset(iIndex);
                setPresetListPageIndex(iIndex / PRESET_TILES_PER_PAGE);
                break;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "Preset frequency zero, Index : %d", iIndex)
            }

            if((MAX_PRESETS - 1) == iIndex)
            {
                iIndex = -1;
            }
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "Preset List is Empty");
    }
}




/**
 * method is commented because there is some problem with stop seek API from service side
 */

////////////////////////////////////////////////////////////////////////
// This method is implemented to stop on going seek whenever user start any type of seek.
////////////////////////////////////////////////////////////////////////
bool CTunerAdaptor::stopOnGoingSeek(CTunerEnums::ETunerSeekType eSeekType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s ,eSeekType : %d",__FUNCTION__,eSeekType);

    bool bIsSeekStopped = false;
    m_uiSelectedPresetFrequency = 0;
    m_iSelectedPresetIndex = -1;

    if(m_eSeekType != eSeekType)
    {
        if(CTunerEnums::SEEK_NONE != m_eSeekType)
        {
            handleStopSeek();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s , seek is not active",__FUNCTION__);
        }
        bIsSeekStopped = true;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"Requested seek already active");
    }

    return bIsSeekStopped;
}

bool CTunerAdaptor::handleHardKeys(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    bool bRes = false;
    switch(eKey)
    {
    case CHardKeyEnum::KEYCODEHK_SEEKUP:
    {
        if((CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState) ||
                (CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState))
        {
            requestAutoSeekUP();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s , eKeyState not valid eKeyState : %d", __FUNCTION__, eKeyState);
        }
        bRes = true;
    }
        break;
    case CHardKeyEnum::KEYCODEHK_SEEKDOWN:
    {
        if((CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState) ||
                (CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState))
        {
            requestAutoSeekDown();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s , eKeyState not valid eKeyState : %d", __FUNCTION__, eKeyState);
        }
        bRes = true;
    }
        break;
    case CHardKeyEnum::KEYCODESWC_NEXT:
    {
        if(CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState)
        {
            requestPresetPlayUp();
        }
        else if(CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState)
        {
            requestAutoSeekUP();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s , eKeyState not valid eKeyState : %d", __FUNCTION__, eKeyState);
        }
        bRes = true;
    }
        break;
    case CHardKeyEnum::KEYCODESWC_PREV:
    {
        if(CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState)
        {
            requestPresetPlayDown();
        }
        else if(CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState)
        {
            requestAutoSeekDown();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s , eKeyState not valid eKeyState : %d", __FUNCTION__, eKeyState);
        }
        bRes = true;
    }
        break;
    case CHardKeyEnum::KEYCODEHK_BACK:
    {
        if((CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState) ||
                (CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState))
        {
            if(CTunerEnums::SEEK_NONE == m_eSeekType)
            {
                LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s , Seek is not active, Performing back operation", __FUNCTION__);
            }
            else
            {
                handleStopSeek();
                if(m_bTunerMainScreenQMLStatus)
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s , Main screen tuner, Seek is active, Stopping seek", __FUNCTION__);
                    bRes = true;
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s , Tuner is not main screen, Seek is active, Stopping seek and Performing back operation", __FUNCTION__);
                }
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s , eKeyState not valid eKeyState : %d", __FUNCTION__, eKeyState);
        }
    }
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s , Hardkey pressed eKey : %d", __FUNCTION__, eKey);
        handleStopSeek();
        break;
    }

    return bRes;
}


/////////////////////////////
// Property related functions
/////////////////////////////

QString CTunerAdaptor::strFrequency()
{
    return m_strFrequency;
}

QString CTunerAdaptor::strBand()
{
    return m_strBand;
}

CTunerEnums::ETunerSeekType CTunerAdaptor::eSeekType()
{
    return m_eSeekType;
}

QString CTunerAdaptor::strTunerState()
{
    return m_strTunerState;
}

CTunerEnums::ETunerBand CTunerAdaptor::eBandType()
{
    return m_eBandType;
}

int CTunerAdaptor::iManualScaleIndex()
{
    return m_iManualScaleIndex;
}

uint CTunerAdaptor::uiTagId()
{
    return m_uiTagId;
}

int CTunerAdaptor::iFieldStrength()
{
    return m_iFieldStrength;
}


QString CTunerAdaptor::strStationName()
{
    return m_strStationName;
}

bool CTunerAdaptor:: bTunerAvailabilityStatus()
{
    return m_bIsTunerEnabled;
}

bool CTunerAdaptor::bTunerDataAvailableStatus()
{
    return m_bTunerDataAvailableStatus;
}

int CTunerAdaptor::iActivePresetIndex()
{
    return m_iActivePresetIndex;
}

int CTunerAdaptor::iPresetListPageIndex()
{
    return m_iPresetListPageIndex;
}
unsigned char CTunerAdaptor::multiPath()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, __FUNCTION__);
    return m_ucMultipath;
}

QString CTunerAdaptor::strFrequencyUnit()
{
    return m_strFrequencyUnit;
}

QList<QString> CTunerAdaptor::liPresetTilesList()
{
    return m_liTunerPresetList;
}

CTunerManualScaleListModel* CTunerAdaptor::pTunerManualScaleListModel()
{
    CTunerManualScaleListModel *pTunerManualScaleListModel = nullptr;

    if(CTunerEnums::BAND_AM == m_eBandType)
    {
        pTunerManualScaleListModel = &m_objTunerAMManualScaleListModel;
    }
    else if(CTunerEnums::BAND_FM == m_eBandType)
    {
        pTunerManualScaleListModel = &m_objTunerFMManualScaleListModel;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s: Band type invalid.", __FUNCTION__);
    }

    return pTunerManualScaleListModel;
}

int CTunerAdaptor::getManualSeekStatus()
{
    return m_bManualSeekStatus;
}

void CTunerAdaptor::setTunerState(const QString &strTunerState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    if(strTunerState != m_strTunerState)
    {
        m_strTunerState = strTunerState;
        emit sigTunerStateChanged();
    }
}

void CTunerAdaptor::seekUpdate(CTunerEnums::ETunerSeekType eSeekType)
{
    CTunerEnums::ETunerSeekType ePreviousSeekType = m_eSeekType;
    setSeekType(eSeekType);
    bool bIsStateUpdated = false;
    int iTunerState = CHMIMain::getSM()->getSCI_Tuner()->get_iTunerState();


    switch(eSeekType)
    {
    case CTunerEnums::SEEK_AUTOSEEK_DOWN:
    {
        if(CHMIMain::getSM()->getSCI_Tuner()->get_tUNER_STATE_AUTOSEEK_DOWN() != iTunerState)
        {
            CHMIMain::getSM()->getSCI_Tuner()->set_iTunerState(CHMIMain::getSM()->getSCI_Tuner()->get_tUNER_STATE_AUTOSEEK_DOWN());
            bIsStateUpdated = true;
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"Current state is already eSeekType : %d", eSeekType);
        }
    }
        break;

    case CTunerEnums::SEEK_AUTOSEEK_UP:
    {
        if(CHMIMain::getSM()->getSCI_Tuner()->get_tUNER_STATE_AUTOSEEK_UP() != iTunerState)
        {
            CHMIMain::getSM()->getSCI_Tuner()->set_iTunerState(CHMIMain::getSM()->getSCI_Tuner()->get_tUNER_STATE_AUTOSEEK_UP());
            bIsStateUpdated = true;
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"Current state is already eSeekType : %d", eSeekType);
        }
    }
        break;

    case CTunerEnums::SEEK_SCAN_UP:
    {
        if(CHMIMain::getSM()->getSCI_Tuner()->get_tUNER_STATE_SCAN() != iTunerState)
        {
            CHMIMain::getSM()->getSCI_Tuner()->set_iTunerState(CHMIMain::getSM()->getSCI_Tuner()->get_tUNER_STATE_SCAN());
            bIsStateUpdated = true;
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"Current state is already eSeekType : %d", eSeekType);
        }
    }
        break;

    case CTunerEnums::SEEK_FULL_AUTOSTORE:
    {
        if(CHMIMain::getSM()->getSCI_Tuner()->get_tUNER_STATE_AUTOSTORE() != iTunerState)
        {
            CHMIMain::getSM()->getSCI_Tuner()->set_iTunerState(CHMIMain::getSM()->getSCI_Tuner()->get_tUNER_STATE_AUTOSTORE());
            bIsStateUpdated = true;
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"Current state is already eSeekType : %d", eSeekType);
        }

    }
        break;

    case CTunerEnums::SEEK_NONE:
    {
        if(CHMIMain::getSM()->getSCI_Tuner()->get_tUNER_STATE_DEFAULT() != iTunerState)
        {
            CHMIMain::getSM()->getSCI_Tuner()->set_iTunerState(CHMIMain::getSM()->getSCI_Tuner()->get_tUNER_STATE_DEFAULT());
            bIsStateUpdated = true;

            if((CTunerEnums::SEEK_FULL_AUTOSTORE == ePreviousSeekType) && m_bAutoStoreSuccessStatus)
            {
                CTunerAdaptor::getInstance()->setFrequencyAfterAutostore();
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "Current state is already eSeekType : %d", eSeekType);
        }
    }
        break;

    default:
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, seek type invalid", __FUNCTION__);
        break;
    }

    if(bIsStateUpdated)
    {
        CHMIMain::getSM()->getSCI_Tuner()->raise_evTunerStateUpdate();

        // Unmuting the system on seek, scan and autostore start
        if(CAudioAdaptor::getInstance()->muteActive() && CTunerEnums::SEEK_NONE != eSeekType)
        {
            CAudioAdaptor::getInstance()->toggleMute();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, system is already unmuted", __FUNCTION__);
        }
    }
}

void CTunerAdaptor::bandUpdate(CTunerEnums::ETunerBand eBand)
{
    if(eBand != m_eBandType && CTunerEnums::BAND_INVALID != eBand)
    {
        resetTunerData();
        setBandType(eBand);
        setFrequencyUnit();
        setBand();

        if(CTunerEnums::BAND_AM == m_eBandType)
        {
            setFrequency(m_uiAMFrequency);
        }
        else if(CTunerEnums::BAND_FM == m_eBandType)
        {
            setFrequency(m_uiFMFrequency);
        }
        else
        {
            // do noting
        }
        setTunerManualScaleListModel();
    }
}

void CTunerAdaptor::setBandType(CTunerEnums::ETunerBand eBand)
{
    if(eBand != m_eBandType)
    {
        m_eBandType = eBand;
    }
    emit sigBandTypeChanged();
}

void CTunerAdaptor::setFrequencyUnit()
{
    if(CTunerEnums::BAND_AM == m_eBandType)
    {
        m_strFrequencyUnit = tr("TEXT_TUNER_AM_FREQ_KHZ");
    }
    else if(CTunerEnums::BAND_FM == m_eBandType)
    {
        m_strFrequencyUnit = tr("TEXT_TUNER_FM_FREQ_MHZ");
    }
    else
    {
        m_strFrequencyUnit = "";
    }
    emit sigFrequencyUnitChanged();
}

void CTunerAdaptor::setBand()
{
    if(CTunerEnums::BAND_AM == m_eBandType)
    {
        m_strBand = tr("TEXT_TUNER_TITLE_AM");
    }
    else if(CTunerEnums::BAND_FM == m_eBandType)
    {
        m_strBand = tr("TEXT_TUNER_TITLE_FM");
    }
    else
    {
        m_strBand = "";
    }
    emit sigBandChanged();
}

void CTunerAdaptor::frequencyUpdate(uint uiFrequency)
{
    // We recieve duplicate frequencies from tuner service side for single set frequency call.
    // To block the duplicate frequencies, we added m_uiCurrentResourceFrequency check.
    if(uiFrequency != m_uiCurrentResourceFrequency)
    {
        m_uiCurrentResourceFrequency = uiFrequency;
        if(!getManualSeekStatus())
        {
            setFrequency(uiFrequency);
        }
        else
        {
            selectActivePreset();
        }
    }
}

void CTunerAdaptor::setFrequency(uint uiFrequency)
{
    if(uiFrequency != m_uiFrequency && uiFrequency != 0)
    {
        m_uiFrequency = uiFrequency;
        selectActivePreset();
        setDisplayFrequency();
        setTunerManualScaleIndex();
        setTunerDataAvailabilityStatus(true);

        if(CTunerEnums::BAND_AM == m_eBandType)
        {
            m_uiAMFrequency = m_uiFrequency;
        }
        else if(CTunerEnums::BAND_FM == m_eBandType)
        {
            m_uiFMFrequency = m_uiFrequency;
        }
        else
        {
            // do noting
        }
    }
}

void CTunerAdaptor::setDisplayFrequency()
{
    if(CTunerEnums::BAND_AM == m_eBandType)
    {
        m_strFrequency = QString::number(m_uiFrequency);
    }
    else if(CTunerEnums::BAND_FM == m_eBandType)
    {
        m_strFrequency = QString::number(((double)m_uiFrequency/1000), 'f', 1);
    }
    else
    {
        m_strFrequency = "";
    }
    emit sigFrequencyChanged();
}

void CTunerAdaptor::setTunerAvailabilityStatus(bool bTunerStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, tuner status is: %d", __FUNCTION__, bTunerStatus);
    if(bTunerStatus != m_bIsTunerEnabled)
    {
        m_bIsTunerEnabled = bTunerStatus;
        emit sigTunerAvailabilityStatusUpdated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s: tuner status not changed", __FUNCTION__);
    }
}

void CTunerAdaptor::setTunerDataAvailabilityStatus(bool bTunerDataStatus)
{
    if(bTunerDataStatus != m_bTunerDataAvailableStatus)
    {
        m_bTunerDataAvailableStatus = bTunerDataStatus;
        emit sigTunerDataAvailableStatusChanged();
    }
}

void CTunerAdaptor::setSeekType(CTunerEnums::ETunerSeekType eSeekType)
{
    if(eSeekType != m_eSeekType)
    {
        m_eSeekType = eSeekType;
        emit sigSeekTypeChanged();
    }
}

void CTunerAdaptor::updateUIState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
}


void CTunerAdaptor::setMultipath(unsigned char ucMultipath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, ucMultipath : %d", __FUNCTION__, ucMultipath);
    if(ucMultipath != m_ucMultipath)
    {
        m_ucMultipath = ucMultipath;
        emit sigMultipathChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, ucMultipath value not changed", __FUNCTION__);
    }
}

void CTunerAdaptor::setManualScaleIndex(int iIndex)
{
    if(iIndex != m_iManualScaleIndex)
    {
        m_iManualScaleIndex = iIndex;
        emit sigManualScaleIndexChanged();
    }
}

void CTunerAdaptor::setTagId(uint uiTagId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s and uiTagId is : %d", __FUNCTION__, uiTagId);
    if(uiTagId != m_uiTagId)
    {
        m_uiTagId = uiTagId;
        emit sigTagIdChanged();
    }
}

void CTunerAdaptor::setManualSeekStatus(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s and bStatus is : %d, m_bManualSeekStatus is : %d", __FUNCTION__, bStatus, m_bManualSeekStatus);
    m_bManualSeekStatus = bStatus;
}

void CTunerAdaptor::setStationName(const QString &objStrStationName)
{
    if(objStrStationName != m_strStationName)
    {
        m_strStationName = objStrStationName;
        emit sigStationNameChanged();
    }
}

void CTunerAdaptor::setActivePresetIndex(int iActivePresetIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s and index is : %d", __FUNCTION__, iActivePresetIndex);
    if(iActivePresetIndex != m_iActivePresetIndex)
    {
        m_iActivePresetIndex = iActivePresetIndex;
        emit sigActivePresetIndexChanged();
    }
}

void CTunerAdaptor::setPresetListPageIndex(int iPresetListPageIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s and iPresetListPageIndex is : %d", __FUNCTION__, iPresetListPageIndex);
    if(iPresetListPageIndex != m_iPresetListPageIndex)
    {
        m_iPresetListPageIndex = iPresetListPageIndex;
        emit sigPresetListPageIndexChanged();
    }
}

void CTunerAdaptor::setFieldStrength(int iFieldStrength)
{
    if(iFieldStrength != m_iFieldStrength)
    {
        m_iFieldStrength = iFieldStrength;
        emit sigFieldStrengthChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, iFieldStrength value is same.", __FUNCTION__);
    }
}

void CTunerAdaptor::setTunerManualScaleListModel()
{
    emit sigTunerManualScaleListModelChanged();
}

/** End Property related functions */

/********************************************************************/
/** Functions to propogate calls to resource layer and statemachine */

void CTunerAdaptor::requestAutoSeekUP()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);

    if(!isTunerAntennaConnected())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, Tuner antenna not connected", __FUNCTION__);
    }
    else
    {
        if(m_pTunerResource && stopOnGoingSeek(CTunerEnums::SEEK_AUTOSEEK_UP))
        {
            m_pTunerResource->startSeekUp();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_TUNER,"m_pTunerResource is null");
        }
    }
}

void CTunerAdaptor::requestAutoSeekDown()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);

    if(!isTunerAntennaConnected())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, Tuner antenna not connected", __FUNCTION__);
    }
    else
    {
        if(m_pTunerResource && stopOnGoingSeek(CTunerEnums::SEEK_AUTOSEEK_DOWN))
        {
            m_pTunerResource->startSeekDown();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_TUNER,"m_pTunerResource is null");
        }
    }
}

void CTunerAdaptor::requestScan()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);

    if(!isTunerAntennaConnected())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, Tuner antenna not connected", __FUNCTION__);
    }
    else
    {
        if(m_pTunerResource && stopOnGoingSeek(CTunerEnums::SEEK_SCAN_UP))
        {
            m_pTunerResource->startScan();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_TUNER,"m_pTunerResource is null");
        }
    }
}

void CTunerAdaptor::requestAutostore()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);

    if(!isTunerAntennaConnected())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, Tuner antenna not connected", __FUNCTION__);
    }
    else
    {
        if(m_pTunerResource && stopOnGoingSeek(CTunerEnums::SEEK_FULL_AUTOSTORE))
        {
            m_pTunerResource->startAutoStore();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_TUNER,"m_pTunerResource is null");
        }
    }
}

void CTunerAdaptor::stopSeek()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, m_eSeekType : %d", __FUNCTION__, m_eSeekType);

    if(m_pTunerResource && CTunerEnums::SEEK_NONE != m_eSeekType)
    {
        m_pTunerResource->stopSeek();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_TUNER,"m_pTunerResource is null");
    }
}

void CTunerAdaptor::stopSeekOnScanAndAutostore()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);

    if(m_pTunerResource)
    {
        m_pTunerResource->stopSeekOnScanAndAutostore();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_TUNER,"m_pTunerResource is null");
    }
}


void CTunerAdaptor::storePreset(int iPreset)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    m_uiSelectedPresetFrequency = m_uiCurrentResourceFrequency;
    m_iSelectedPresetIndex = iPreset;

    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, m_uiSelectedPresetFrequency : %d, m_iSelectedPresetIndex : %d", __FUNCTION__, m_uiSelectedPresetFrequency, m_iSelectedPresetIndex);
    setActivePresetIndex(iPreset);


    // Unmuting the system on manual seek start
    if(CAudioAdaptor::getInstance()->muteActive())
    {
        CAudioAdaptor::getInstance()->toggleMute();
    }

    if(m_pTunerResource)
    {
        CAudioAdaptor::getInstance()->playBeep(CAudioEnums::BEEP_TYPE_CONFIRM);
        m_pTunerResource->addToPreset(iPreset);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_TUNER,"m_pTunerResource is null");
    }
}

void CTunerAdaptor::selectPreset(int iPreset)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);

    if(0 != m_vecPresetList.at(iPreset))
    {
        if(!isTunerAntennaConnected())
        {
            LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, Tuner antenna not connected", __FUNCTION__);
        }
        else
        {
            stopManualSeek();
            m_uiSelectedPresetFrequency = m_vecPresetList.at(iPreset);
            m_iSelectedPresetIndex = iPreset;
            setActivePresetIndex(iPreset);

            // Unmuting the system on manual seek start
            if(CAudioAdaptor::getInstance()->muteActive())
            {
                CAudioAdaptor::getInstance()->toggleMute();
            }

            if(m_pTunerResource)
            {
                m_pTunerResource->selectPreset(iPreset);
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_TUNER,"m_pTunerResource is null");
            }
        }
    }
}

void CTunerAdaptor::setManualFrequency()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, m_uiFrequency: %d", __FUNCTION__, m_uiFrequency);
    if(m_pTunerResource)
    {
        m_pTunerResource->setFrequency(m_uiFrequency);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_TUNER,"m_pTunerResource is null");
    }
}

void CTunerAdaptor::resetTunerData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    initPresetList();
    setActivePresetIndex(-1);
    m_uiSelectedPresetFrequency = 0;
    m_iSelectedPresetIndex = -1;
    if(CTunerEnums::BAND_INVALID != m_eBandType)
    {
        setBandType(CTunerEnums::BAND_INVALID);
        m_uiFrequency = 0;
        setDisplayFrequency();
        setFrequencyUnit();
        setBand();
    }
    setTunerDataAvailabilityStatus(false);
}

void CTunerAdaptor::setTunerQMLStatus(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, tuner qml status, %d", __FUNCTION__, bStatus);
    m_bTunerMainScreenQMLStatus = bStatus;
}

void CTunerAdaptor::setTunerFrequency(int iFrequency)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    if(m_pTunerResource)
    {
        m_pTunerResource->setFrequency(iFrequency);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_TUNER,"m_pTunerResource is null");
    }
}

void CTunerAdaptor::setFrequencyAfterAutostore()
{
    if(!m_vecPresetList.isEmpty())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, frequency : %d", __FUNCTION__, m_vecPresetList.first());
        setTunerFrequency(m_vecPresetList.first());
        m_bAutoStoreSuccessStatus = false;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, preset list is empty", __FUNCTION__);
    }
}

void CTunerAdaptor::startManualSeek(int iManualFreq)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);

    if(!m_bBlockManualSeek)
    {
        stopOnGoingSeek(CTunerEnums::SEEK_MANUAL);
        m_bManualSeekStatus = true;

        /**
     * When user start manual seek we need to call setFrequency method of service for every frequency user
     * select during manual seek, which alot due which dbus will get floded with setFrequency call which
     * might affect system performance. So, to avoid this we have implemented debouncing logic.
     * Debouncing Logic :
     * We are starting timer of 400ms when user start manual seek and till the timer running we will update
     * current frequency variable m_uiFrequency and will not send any call to dbus. When timer completes
     * sltTimerComplete slot will get hit and we call setFrequency() with current frequency m_uiFrequency.
     */
        if(!m_objTunerManualSeekTimer.isActive())
        {
            LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s timer is started", __FUNCTION__);
            m_objTunerManualSeekTimer.setSingleShot(true);
            m_objTunerManualSeekTimer.setInterval(400);
            m_objTunerManualSeekTimer.start();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s timer is running", __FUNCTION__);
        }
        setFrequency(iManualFreq);

        // We have to update m_iManualScaleIndex variable with current manual scale pathveiw index
        // but we will not emit signal for the variable update that's why updating variable directly.
        m_iManualScaleIndex = (CTunerEnums::BAND_AM == eBandType()) ? m_liAMManualScaleFreq.indexOf(m_uiFrequency) : m_liFMManualScaleFreq.indexOf(iManualFreq);

        // Unmuting the system on manual seek start
        if(CAudioAdaptor::getInstance()->muteActive())
        {
            CAudioAdaptor::getInstance()->toggleMute();
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, ManualSeek is blocked due to preset selection", __FUNCTION__);
    }
}

void CTunerAdaptor::stopManualSeek()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s", __FUNCTION__);
    if(m_bManualSeekStatus)
    {
        setManualSeekBlockStatus(true);
        setManualSeekStatus(false);
        m_objTunerManualSeekTimer.stop();
    }
}

void CTunerAdaptor::sltTimerComplete()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, m_bBlockManualSeek : %d", __FUNCTION__, m_bBlockManualSeek);
    setManualFrequency();
}

void CTunerAdaptor::sltDrawerStateChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    if(CDrawersAdaptor::getInstance()->qadDrawerState() == DRAWERS_STATE_MAXIMIZED_STRING || CDrawersAdaptor::getInstance()->shortcutDrawerState() == DRAWERS_STATE_MAXIMIZED_STRING)
    {
        handleStopSeek();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, drawer is not in Maximized state",__FUNCTION__);
    }
}

void CTunerAdaptor::sltActiveEntSrcUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, Audio src change, stopping seek, %d", __FUNCTION__, CAudioAdaptor::getInstance()->activeEntSrc());
    handleStopSeek();
    if(CAudioEnums::SRC_TUNER_AM != CAudioAdaptor::getInstance()->activeEntSrc() && CAudioEnums::SRC_TUNER_FM != CAudioAdaptor::getInstance()->activeEntSrc())
    {
        resetTunerData();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, AM or FM is activated", __FUNCTION__);
    }
}

void CTunerAdaptor::sltActiveInteruptSrcUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, interupt src change", __FUNCTION__);
    CAudioAdaptor* m_pAudioAdaptor = CAudioAdaptor::getInstance();
    if(m_pAudioAdaptor->isAudioInterruptSourceActive(CAudioEnums::SRC_TEL_HANDSFREE)
            || m_pAudioAdaptor->isAudioInterruptSourceActive(CAudioEnums::SRC_TEL_RINGING)
            || m_pAudioAdaptor->isAudioInterruptSourceActive(CAudioEnums::SRC_TTS)
            || m_pAudioAdaptor->isAudioInterruptSourceActive(CAudioEnums::SRC_CARPLAY_PHONE)
            || m_pAudioAdaptor->isAudioInterruptSourceActive(CAudioEnums::SRC_CARPLAYPHONE_RINGING)
            || m_pAudioAdaptor->isAudioInterruptSourceActive(CAudioEnums::SRC_CARPLAY_SIRI)
            || m_pAudioAdaptor->isAudioInterruptSourceActive(CAudioEnums::SRC_CARPLAY_ALT)
            || m_pAudioAdaptor->isAudioInterruptSourceActive(CAudioEnums::SRC_GAL_VR)
            || m_pAudioAdaptor->isAudioInterruptSourceActive(CAudioEnums::SRC_GAL_VOICE))
    {
        handleStopSeek();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, Interupt source not active", __FUNCTION__);
    }
}

void CTunerAdaptor::enableQualityMonitor(bool bMonitorFlag)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, bMonitorFlag: %d", __FUNCTION__, bMonitorFlag);
    if (m_pTunerResource)
    {
        m_pTunerResource->enableQualityMonitor(bMonitorFlag);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_TUNER,"m_pTunerResource is null");
    }
}

void CTunerAdaptor::launchTuner()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    //Play the source from Tuner category and switch to Tuner screen
    CAudioAdaptor::getInstance()->playFromSourceGroup(CAudioEnums::EAudioSourceCategory::SOURCE_CATEGORY_TUNER, true);
}

void CTunerAdaptor::handleStopSeek()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    if(CTunerEnums::SEEK_AUTOSEEK_DOWN == m_eSeekType || CTunerEnums::SEEK_AUTOSEEK_UP == m_eSeekType)
    {
        stopSeek();
    }
    else if(CTunerEnums::SEEK_SCAN_UP == m_eSeekType || CTunerEnums::SEEK_FULL_AUTOSTORE == m_eSeekType)
    {
        stopSeekOnScanAndAutostore();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, Seek not active m_eSeekType : %d", __FUNCTION__, m_eSeekType);
    }
}

/** End Functions to propogate calls to resource layer and statemachine */
