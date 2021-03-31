#include "CTunerResourceImpl.h"
#include "resource/ResourceDeploymentConfig.h"
#include <QDebug>
#include <QtCore/qmath.h>
#include <ResourceMaster.h>
#include "logging.h"

using namespace std::placeholders;

CTunerResourceImpl::CTunerResourceImpl()
    :m_pTunerEventProvider(new CTunerEventProvider()),
      m_Tuner_Proxy(ResourceDeploymentConfig::getConfig().m_Tuner_Proxy.domain,ResourceDeploymentConfig::getConfig().m_Tuner_Proxy.instance),
      m_Tuner_Introspection_Proxy(ResourceDeploymentConfig::getConfig().m_Tuner_Introspection_Proxy.domain,ResourceDeploymentConfig::getConfig().m_Tuner_Introspection_Proxy.instance),
      m_uiSeekType(0), m_iCurrentFrequency(-1), m_iLastPlayedFrequency(0), m_iBand(-1), m_iFieldStrength(-1), m_strStationName(""),
      m_uiTagId(0), m_ucMultipath(0), m_bIsTunerProxyAvailable(false), m_bIsTunerIntrospectionProxyAvailable(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    init();
}

void CTunerResourceImpl::init()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    SUBSCRIBE(m_Tuner_Introspection_Proxy,getProxyStatusEvent(),&CTunerResourceImpl::tunerIntrospectionProxyAvailabilityCb,_1 );
    SUBSCRIBE(m_Tuner_Proxy,getProxyStatusEvent(),&CTunerResourceImpl::tunerProxyAvailability,_1 );
    subscribeTunerProxyEvents();
    SUBSCRIBE(m_Tuner_Introspection_Proxy,getQualityMonitorEvent(), &CTunerResourceImpl::onQualityAmFmChangeCb,_1,_2,_3 );
}

CTunerResourceImpl::~CTunerResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s", __FUNCTION__);
    if (m_pTunerEventProvider)
    {
        delete m_pTunerEventProvider;
        m_pTunerEventProvider = nullptr;
    }
}

CTunerEventProvider* CTunerResourceImpl::getTunerDataEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    return m_pTunerEventProvider;
}


void CTunerResourceImpl::tunerProxyAvailability(CommonAPI::AvailabilityStatus status)
{
    if( CommonAPI::AvailabilityStatus::AVAILABLE== status )
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, :true", __FUNCTION__);
        m_bIsTunerProxyAvailable = true;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_TUNER,"%s, :false", __FUNCTION__);
        m_bIsTunerProxyAvailable = false;
    }

    // Propagate the information to the tuner adaptor layer
    if (m_pTunerEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"update tuner proxy status to upper layer");
        m_pTunerEventProvider->updateTunerStatus(m_bIsTunerProxyAvailable);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CTunerResourceImpl::tunerIntrospectionProxyAvailabilityCb(CommonAPI::AvailabilityStatus status)
{
    if( CommonAPI::AvailabilityStatus::AVAILABLE == status )
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, :true", __FUNCTION__);
        m_bIsTunerIntrospectionProxyAvailable = true;
        if(m_pTunerEventProvider)
        {
            m_pTunerEventProvider->introspectionProxyAvailable();
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_TUNER,"%s, :false", __FUNCTION__);
        m_bIsTunerIntrospectionProxyAvailable = false;
    }
}

void CTunerResourceImpl::subscribeTunerProxyEvents()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s", __FUNCTION__);
    SUBSCRIBE(m_Tuner_Proxy,getAudioCurrentStationAttribute().getChangedEvent(),&CTunerResourceImpl::onCurrentStation,_1 );
    SUBSCRIBE(m_Tuner_Proxy,getAudioPresetListAttribute().getChangedEvent(),&CTunerResourceImpl::onPresetListChange,_1 );
    SUBSCRIBE(m_Tuner_Proxy,getAudioStationListAttribute().getChangedEvent(),&CTunerResourceImpl::onReceiveStationList,_1 );
    m_Tuner_Proxy->forceBroadcastUpdateAsync(std::bind(&CTunerResourceImpl::asyncStationSelectStationcb,this, _1));
}

void CTunerResourceImpl::enableQualityMonitor(bool bMonitorFlag)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s ,reqMonitorDiagnostics: bMonitorFlag %d", __FUNCTION__, bMonitorFlag);
    if(m_bIsTunerIntrospectionProxyAvailable)
    {
        if (bMonitorFlag)
        {
            m_Tuner_Introspection_Proxy->controlQualityMonitorAsync(OrinocoTunerIntrospectionTypes::Device::DEV_AMFM, std::bind(&CTunerResourceImpl::asyncStationSelectStationcb, this, _1));
            bMonitorFlag = false;
        }
        else
        {
            m_Tuner_Introspection_Proxy->controlQualityMonitorAsync(OrinocoTunerIntrospectionTypes::Device::DEV_NONE, std::bind(&CTunerResourceImpl::asyncStationSelectStationcb, this, _1));
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_TUNER, "Tuner introspection proxy is not available");
    }
}
void CTunerResourceImpl::onQualityAmFmChangeCb(const OrinocoTunerIntrospectionTypes::QualityAmFms &qualityamfmlist, const OrinocoTunerIntrospectionTypes::QualityDabs &qualitydablist, const OrinocoTunerIntrospectionTypes::QualityDrms &qualitydrmlist)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, __FUNCTION__);
    CPP_UNUSED(qualitydablist);
    CPP_UNUSED(qualitydrmlist);

    if (qualityamfmlist.size() > 0)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "NotifyQualityMonitorInfo : AMFM list size : %llu", static_cast<long long unsigned int>(qualityamfmlist.size()));
        OrinocoTunerIntrospectionTypes::QualityAmFm qualityamfm = qualityamfmlist[0];
        uint8_t ucMultipath = qualityamfm.getMultipath();
        m_iFieldStrength = qualityamfm.getFieldStrength();
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, Multipath : %d, FieldStrength : %d", __FUNCTION__, ucMultipath, m_iFieldStrength);
        if(m_pTunerEventProvider)
        {
            m_pTunerEventProvider->updateMultipath(ucMultipath);
            m_pTunerEventProvider->updateFieldStrength(m_iFieldStrength);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_TUNER,"%s ,m_pTunerEventProvider is null", __FUNCTION__);
        }
    }
}

void CTunerResourceImpl::onReceiveStationList(const OrinocoTunerTypes::AudioStationList &audioStationList)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    std::vector<OrinocoTunerTypes::ListStation> sList = audioStationList.getStations().getStations();

    if((OrinocoTunerTypes::StationListType::LIST_AUTOSTORE == audioStationList.getStations().getListType()) && (OrinocoTunerTypes::StationSeekMode::SEEK_FULL_AUTOSTORE == m_uiSeekType))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s,list size after receive station %zu=", __FUNCTION__, sList.size());

        if(m_pTunerEventProvider)
        {
            if(sList.size()!= 0)
            {
                m_pTunerEventProvider->validStationFoundStatus(true);
            }
            else
            {
                m_pTunerEventProvider->validStationFoundStatus(false);
            }
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, List type is not correct", __FUNCTION__);
    }
}

void CTunerResourceImpl::storePresetList(std::vector<OrinocoTunerTypes::ListStation> sList)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, sList size %zu",__FUNCTION__, sList.size());
    if(!sList.empty())
    {
        mapPresetList.clear();

        for( size_t i=0; i < sList.size(); i++)
        {
            OrinocoTunerTypes::ListStation station = sList.at(i);
            int iSource = static_cast<int>(station.getSource());//cast the unsigned int to an int since it may store a -1 value
            if(iSource == m_iBand)
            {
                /**
                * Changing service preset index(1 to 20) to HMI preset index(0 to 19)
                */
                int presetindex = station.getSel().getPreset() - 1;
                mapPresetList[presetindex]= station.getSel().getFrequency();
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, band type for preset list is not correct %u", __FUNCTION__, station.getSource());
            }
        }

        if(m_pTunerEventProvider)
        {
            m_pTunerEventProvider->presetListResponseReceived();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, Provider not available", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, List is empty.", __FUNCTION__);
    }
}

void CTunerResourceImpl::onPresetListChange(const OrinocoTunerTypes::StationList &stationList)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);

    std::vector<OrinocoTunerTypes::ListStation> sList = stationList.getStations();

    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, sList size %zu",__FUNCTION__, sList.size());

    if(OrinocoTunerTypes::StationListType::LIST_PRESET == stationList.getListType())
    {
        storePresetList(sList);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, List type is not correct", __FUNCTION__);
    }
}

map<uint, uint> CTunerResourceImpl::getPresetList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    return mapPresetList;

}

void CTunerResourceImpl::onCurrentStation( const OrinocoTunerTypes::AudioCurrentStation & currStation)
{
    m_currStation = currStation.getStation().getSel();
    m_iBand = currStation.getStation().getSource();
    m_iCurrentFrequency = currStation.getStation().getSel().getFrequency();
    m_uiSeekType = currStation.getStation().getSel().getSeekMode();
    m_strStationName = currStation.getStation().getInfo().getName();
    m_uiTagId = currStation.getStation().getSel().getTag();

    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s,  currentsource:%u, currentfrequency:%d, seekmode:%d, m_strstationname:%s, m_uiTagId : %d",__FUNCTION__, m_iBand, m_iCurrentFrequency, m_uiSeekType,m_strStationName.c_str(), m_uiTagId);

    if(m_pTunerEventProvider)
    {
        m_pTunerEventProvider->updateSeekType(m_uiSeekType);
        m_pTunerEventProvider->updateBand(m_iBand);
        m_pTunerEventProvider->updateFrequency(m_iCurrentFrequency);
        m_pTunerEventProvider->activePresetResponseReceived();
        m_pTunerEventProvider->manualTuningStatus();
        m_pTunerEventProvider->updateStationName(m_strStationName);
        if(ITunerTypes::StationSeekMode::SEEK_SCAN_UP == m_uiSeekType)
        {
            m_pTunerEventProvider->updateTagId(m_uiTagId);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_TUNER, "m_pTunerEventProvider is null");
    }
}

void CTunerResourceImpl::startSeekUp()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    OrinocoTunerTypes::StationSelector selector;
    selector.setTag(0);
    selector.setFrequency(0);
    selector.setPreset(0);
    selector.setSeekMode(OrinocoTunerTypes::StationSeekMode::SEEK_AUTO_UP);

    callStationSelectStationAsync(selector, ITunerTypes::eHANDLE_SEEK_AUTO, std::bind(&CTunerResourceImpl::asyncStationSelectStationcb,this, _1));
}

void CTunerResourceImpl::startSeekDown()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    OrinocoTunerTypes::StationSelector selector;
    selector.setTag(0);
    selector.setFrequency(0);
    selector.setPreset(0);
    selector.setSeekMode(OrinocoTunerTypes::StationSeekMode::SEEK_AUTO_DOWN);

    callStationSelectStationAsync(selector, ITunerTypes::eHANDLE_SEEK_AUTO, std::bind(&CTunerResourceImpl::asyncStationSelectStationcb,this, _1));
}

void CTunerResourceImpl::startScan()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    OrinocoTunerTypes::StationSelector selector;
    m_iLastPlayedFrequency = m_iCurrentFrequency;
    selector.setTag(0);
    selector.setFrequency(0);
    selector.setPreset(0);
    selector.setSeekMode(OrinocoTunerTypes::StationSeekMode::SEEK_SCAN_UP);

    callStationSelectStationAsync(selector, ITunerTypes::eHANDLE_SCAN, std::bind(&CTunerResourceImpl::asyncStationSelectStationcb,this, _1));
}

void CTunerResourceImpl::startManualSeekUp()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    OrinocoTunerTypes::StationSelector selector;
    selector.setTag(0);
    selector.setFrequency(0);
    selector.setPreset(0);
    selector.setSeekMode(OrinocoTunerTypes::StationSeekMode::SEEK_MAN_UP);

    callStationSelectStationAsync(selector, ITunerTypes::eHANDLE_SEEK_STEP, std::bind(&CTunerResourceImpl::asyncStationSelectStationcb,this, _1));
}

void CTunerResourceImpl::startManualSeekDown()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    OrinocoTunerTypes::StationSelector selector;
    selector.setTag(0);
    selector.setFrequency(0);
    selector.setPreset(0);
    selector.setSeekMode(OrinocoTunerTypes::StationSeekMode::SEEK_MAN_DOWN);

    callStationSelectStationAsync(selector, ITunerTypes::eHANDLE_SEEK_STEP, std::bind(&CTunerResourceImpl::asyncStationSelectStationcb,this, _1));
}

void CTunerResourceImpl::startAutoStore()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    OrinocoTunerTypes::StationSelector selector;
    m_iLastPlayedFrequency = m_iCurrentFrequency;
    selector.setTag(0);
    selector.setFrequency(0);
    selector.setPreset(0);
    selector.setSeekMode(OrinocoTunerTypes::StationSeekMode::SEEK_FULL_AUTOSTORE);

    m_Tuner_Proxy->stationStorePresetAsync(selector,0,ITunerTypes::eHANDLE_STORE_PRESET,std::bind(&CTunerResourceImpl::asyncStationSelectStationcb,this, _1));
}

void CTunerResourceImpl::stopSeekOnScanAndAutostore()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    OrinocoTunerTypes::StationSelector selector;
    selector.setTag(0);
    /*After stop scan or autostore, the frequency is set to the value at which scan started*/
    selector.setFrequency(m_iLastPlayedFrequency);
    selector.setPreset(0);
    selector.setSeekMode(OrinocoTunerTypes::StationSeekMode::SEEK_OFF);

    callStationSelectStationAsync(selector, ITunerTypes::eHANDLE_SEEK_OFF, std::bind(&CTunerResourceImpl::asyncStationSelectStationcb,this, _1));
}

void CTunerResourceImpl::stopSeek()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    OrinocoTunerTypes::StationSelector selector;
    selector.setTag(0);
    selector.setFrequency(0);
    selector.setPreset(0);
    selector.setSeekMode(OrinocoTunerTypes::StationSeekMode::SEEK_OFF);

    callStationSelectStationAsync(selector, ITunerTypes::eHANDLE_SEEK_OFF, std::bind(&CTunerResourceImpl::asyncStationSelectStationcb,this, _1));
}

void CTunerResourceImpl::setFrequency(int iFrequency)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    OrinocoTunerTypes::StationSelector selector;
    selector.setTag(0);
    selector.setFrequency(iFrequency);
    selector.setPreset(0);
    selector.setSeekMode(OrinocoTunerTypes::StationSeekMode::SEEK_MAN_UP);

    callStationSelectStationAsync(selector, ITunerTypes::eHANDLE_SEEK_MANUAL, std::bind(&CTunerResourceImpl::asyncStationSelectStationcb,this, _1));
}

void CTunerResourceImpl::addToPreset(int preset)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, PresetNumber : %d", __FUNCTION__,(preset + 1));
    if(m_bIsTunerProxyAvailable)
    {
        OrinocoTunerTypes::StationSelector selector = m_currStation;
        selector.setSeekMode(OrinocoTunerTypes::StationSeekMode::SEEK_OFF);
        m_Tuner_Proxy->stationStorePresetAsync(selector,(preset + 1), ITunerTypes::eHANDLE_STORE_PRESET,std::bind(&CTunerResourceImpl::asyncStationSelectStationcb,this, _1));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_TUNER, "%s, Tuner proxy is not available", __FUNCTION__);
    }
}

void CTunerResourceImpl::selectPreset(int preset)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, PresetNumber : %d", __FUNCTION__,preset);
    OrinocoTunerTypes::StationSelector selector;
    selector.setPreset(preset + 1);
    selector.setSeekMode(OrinocoTunerTypes::StationSeekMode::SEEK_OFF);
    ITunerTypes::eRequestHandle handle = ITunerTypes::eRequestHandle::eHANDLE_SELECT_PRESET_MANUAL;
    callStationSelectStationAsync(selector, handle, std::bind(&CTunerResourceImpl::asyncStationSelectStationcb,this, _1));
}

void CTunerResourceImpl::asyncStationSelectStationcb(const CommonAPI::CallStatus& status)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, status : %d", __FUNCTION__, static_cast<int>(status));

}

void CTunerResourceImpl::disableQualityMonitor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s", __FUNCTION__);
    enableQualityMonitor(false);
}

void CTunerResourceImpl::callStationSelectStationAsync(const OrinocoTunerTypes::StationSelector &stationSelector, const uint32_t &handle, OrinocoTunerProxyBase::StationSelectStationAsyncCallback callback, const CommonAPI::CallInfo *info)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    if (m_bIsTunerProxyAvailable)
    {
        m_Tuner_Proxy->stationSelectStationAsync(stationSelector, handle, callback, info);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_TUNER, "Tuner proxy is not available");
    }
}
