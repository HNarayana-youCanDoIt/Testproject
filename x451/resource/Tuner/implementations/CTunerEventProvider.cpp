#include "CTunerEventProvider.h"
#include "logging.h"

CTunerEventProvider::CTunerEventProvider(QObject *parent):
    QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
}

CTunerEventProvider::~CTunerEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
}


void CTunerEventProvider::updateSeekType(uint uiSeekType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    emit sigUpdateSeekType(uiSeekType);
}

void CTunerEventProvider::updateFrequency(uint uiFrequency)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    emit sigUpdateFrequency(uiFrequency);
}

void CTunerEventProvider::updateBand(int iBand)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    emit sigUpdateBand(iBand);
}

void CTunerEventProvider::manualTuningStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    emit sigManualSeekStatus();
}

void CTunerEventProvider::updateStationName(const string &objStrStationName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    emit sigUpdateStationName(objStrStationName);
}

void CTunerEventProvider::presetListResponseReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    emit sigPresetListResponseReceived();
}

void CTunerEventProvider::activePresetResponseReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    emit sigActivePresetResponseReceived();
}

void CTunerEventProvider::updateFieldStrength(int iFieldStrength)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    emit sigUpdateFieldStrength(iFieldStrength);
}

void CTunerEventProvider::updateTagId(uint uiTagId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    emit sigUpdateTagId(uiTagId);
}

void CTunerEventProvider::validStationFoundStatus(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    emit sigValidStationFoundUpdated(bStatus);
}

void CTunerEventProvider::updateMultipath(uint8_t ucMultipath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    unsigned char ucMultiPathValue = ucMultipath;
    emit sigUpdateMultipath(ucMultiPathValue);
}

void CTunerEventProvider::introspectionProxyAvailable()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    emit sigIntrospectionProxyAvailable();
}

void CTunerEventProvider::updateTunerStatus(bool bIsTunerAvailable)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    emit sigUpdateTunerStatus(bIsTunerAvailable);
}
