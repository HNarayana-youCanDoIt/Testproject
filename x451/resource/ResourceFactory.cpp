#include "ResourceFactory.hpp"
#include "logging.h"
#include "implementations/CMediaResourceImpl.h"

#include "implementations/CTunerResourceImpl.h"
#include "implementations/CHardkeyResourceImpl.h"
#include "implementations/CEnggMenuResourceImpl.h"
#include "implementations/CVehicleResourceImpl.h"
#include "implementations/CParkAssistResourceImpl.h"
#include "implementations/CAudioResourceImpl.h"
#include "SoftwareUpdateResource/implementations/CSoftwareUpdateResourceImpl.h"
#include "implementations/CPhoneConnectionManagerResourceImpl.h"
#include "implementations/CDeviceModeHandlerResourceImpl.h"
#include "implementations/CAndroidAutoResourceImpl.h"
#include "implementations/CPhoneCallManagerResourceImpl.h"
#include "PowerModeResource/implementations/CPowerModeResourceImpl.h"
#include "HVACResource/implementations/CHVACResourceImpl.h"
#include "implementations/CDisplayManagerResourceImpl.h"
#include "implementations/CAppleCarPlayResourceImpl.h"
#include "implementations/CPhonePIMDBResourceImpl.h"
#include "implementations/CVehicleResourceImpl.h"
#include "implementations/CVersionManagerResourceImpl.h"
#include "DateAndTimeResource/implementations/CDateAndTimeResourceImpl.h"
#include "implementations/CVoiceAlertsResImpl.h"
#include "implementations/CBtPluginResourceImpl.h"
#include "implementations/CDiagnosticResourceImpl.h"
#include "LayerManagerResource/implementations/CLayerManagerResourceImpl.h"
#include "implementations/CVRProxyResImpl.h"
#include "implementations/CVariantControlResourceImpl.h"
#include "RCAResource/implementations/CRCAResourceImpl.h"
#include "ICCastResource/implementations/CICCastResourceImpl.h"
#include "DriveNextResource/implementations/CDriveNextResourceImpl.h"
#include "W3WResource/implementations/CW3WResourceImpl.h"
#include "DoodleResource/implementations/CDoodleResourceImpl.h"

IAudioResource* ResourceFactory::m_pAudioResource = nullptr;
IMediaResource* ResourceFactory::m_pMediaResource = nullptr;
ITunerResource* ResourceFactory::m_pTuner = nullptr;
ISoftwareUpdateResource* ResourceFactory::m_pSoftwareUpdateResource = nullptr;
IHardkeyResource* ResourceFactory::m_pHardkeyResource = nullptr;
IEnggMenuResource* ResourceFactory::m_pEnggMenuResource= nullptr;
IPhoneConnectionManagerResource* ResourceFactory::m_pPhoneConnectionManagerResource = nullptr;
IDeviceModeHandlerResource* ResourceFactory::m_pDeviceModeHandlerResource = nullptr;
IAndroidAutoResource* ResourceFactory::m_pAndroidAutoResource = nullptr;
IPhoneCallManagerResource* ResourceFactory::m_pPhoneCallManagerResource = nullptr;
IPhonePIMDBResource* ResourceFactory::m_pPhonePimDbResource = nullptr;
IPowerModeResource* ResourceFactory::m_pPowerModeResource = nullptr;
IHVACResource* ResourceFactory::m_pHVACResource = nullptr;
IDisplayManagerResource* ResourceFactory::m_pDisplayManagerResource = nullptr;
IAppleCarPlayResource* ResourceFactory::m_pAppleCarPlayResource = nullptr;
IVehicleResource* ResourceFactory::m_pVehicleResource = nullptr;
IParkAssistResource* ResourceFactory::m_pParkAssistResource = nullptr;
IDateAndTimeResource* ResourceFactory::m_pDateAndTimeResource = nullptr;
IVersionManagerResource* ResourceFactory::m_pVersionManagerResource = nullptr;
IVoiceAlerts* ResourceFactory::m_pVoiceAlertsResource = nullptr;
CVRStubResource* ResourceFactory::m_pVRStubResource = nullptr;
IBtPluginResource* ResourceFactory::m_pBtPluginResource = nullptr;
CIntrospectionStubResource* ResourceFactory::m_pIntrospectionStubResource = nullptr;
IDiagnosticResource* ResourceFactory::m_pDiagnosticResource = nullptr;
ILayerManagerResource* ResourceFactory::m_pLayerManagerResource = nullptr;
IVRProxyResource* ResourceFactory::m_pVRProxyResource = nullptr;
IVariantControlResource* ResourceFactory::m_pVariantControlResource = nullptr;
IRCAResource* ResourceFactory::m_pRCAResource = nullptr;
IICCastResource* ResourceFactory::m_pICCastResource = nullptr;
IDriveNextResource* ResourceFactory::m_pDriveNextResource = nullptr;
IW3WResource* ResourceFactory::m_pW3WResource = nullptr;
IDoodleResource* ResourceFactory::m_pDoodleResource = nullptr;

void ResourceFactory::initTunerResource()
{
    if ( nullptr == m_pTuner )
    {
        m_pTuner = new CTunerResourceImpl();
    }
}

ITunerResource *ResourceFactory::getTunerResource()
{
    initTunerResource();
    return m_pTuner;
}

void ResourceFactory::deleteTunerRsource()
{
    if(m_pTuner)
    {
        delete m_pTuner;
        m_pTuner = nullptr;
    }
}

void ResourceFactory::initAudioResource()
{
    if(nullptr == m_pAudioResource)
    {
        m_pAudioResource = new CAudioResourceImpl();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioResource is null");
    }
}

IAudioResource *ResourceFactory::getAudioResource()
{
    initAudioResource();
    return m_pAudioResource;
}

void ResourceFactory::deleteAudioRsource()
{
    if(m_pAudioResource)
    {
        delete m_pAudioResource;
        m_pAudioResource = nullptr;
    }
}

void ResourceFactory::initMediaResource()
{
    if(!m_pMediaResource)
    {
        m_pMediaResource = new CMediaResourceImpl();
    }
}
void ResourceFactory::deleteMediaResource()
{
    if(m_pMediaResource)
    {
        delete m_pMediaResource;
        m_pMediaResource = NULL;
    }
}
IMediaResource* ResourceFactory::getMediaResource()
{
    initMediaResource();
    return m_pMediaResource;
}

void ResourceFactory::initHardkeyResource()
{
    if(nullptr == m_pHardkeyResource)
    {
        m_pHardkeyResource = new CHardkeyResourceImpl();
    }
}

IHardkeyResource *ResourceFactory::getHardkeyResource()
{
    initHardkeyResource();
    return m_pHardkeyResource;
}

void ResourceFactory::deleteHardkeyResource()
{
    if(m_pHardkeyResource)
    {
        delete m_pHardkeyResource;
        m_pHardkeyResource = nullptr;
    }
}

void ResourceFactory::initSoftwareUpdateResource()
{
    if(!m_pSoftwareUpdateResource)
    {
        m_pSoftwareUpdateResource = new CSoftwareUpdateResourceImpl();
    }
}

void ResourceFactory::deleteSoftwareUpdateResource()
{
    if(m_pSoftwareUpdateResource)
    {
        delete m_pSoftwareUpdateResource;
        m_pSoftwareUpdateResource = NULL;
    }
}

void ResourceFactory::initEnggMenuResource()
{
    if ( nullptr == m_pEnggMenuResource )
    {
        m_pEnggMenuResource = new CEnggMenuResourceImpl();
    }
}

IEnggMenuResource *ResourceFactory::getEnggMenuResource()
{
    initEnggMenuResource();
    return m_pEnggMenuResource;
}

void ResourceFactory::deleteEnggMenuResource()
{
    if(m_pEnggMenuResource)
    {
        delete m_pEnggMenuResource;
        m_pEnggMenuResource = nullptr;
    }
}

ISoftwareUpdateResource* ResourceFactory::getSoftwareUpdateResource()
{
    return m_pSoftwareUpdateResource;
}

void ResourceFactory::initPhoneConnectionManagerResource()
{
    if (!m_pPhoneConnectionManagerResource)
    {
        m_pPhoneConnectionManagerResource = new CPhoneConnectionManagerResourceImpl();
    }
}

void ResourceFactory::disposePhoneConnectionManagerResource()
{
    if(m_pPhoneConnectionManagerResource)
    {
        delete m_pPhoneConnectionManagerResource;
        m_pPhoneConnectionManagerResource = NULL;
    }
}

IPhoneConnectionManagerResource* ResourceFactory::getPhoneConnectionManagerResource()
{
    initPhoneConnectionManagerResource();
    return m_pPhoneConnectionManagerResource;
}

void ResourceFactory::initRCAResource()
{
    if(nullptr == m_pRCAResource)
    {
        m_pRCAResource = new CRCAResourceImpl();
    }
}

void ResourceFactory::deleteRCAResource()
{
    if(m_pRCAResource)
    {
        delete m_pRCAResource;
        m_pRCAResource = nullptr;
    }
}

IRCAResource* ResourceFactory::getRCAResource()
{
    initRCAResource();
    return m_pRCAResource;
}

void ResourceFactory::initICCastResource()
{
    if (!m_pICCastResource)
    {
        m_pICCastResource = new CICCastResourceImpl();
    }
}

void ResourceFactory::deleteICCastResource()
{
    if(m_pICCastResource)
    {
        delete m_pICCastResource;
        m_pICCastResource = nullptr;
    }
}

IICCastResource *ResourceFactory::getICCastResource()
{
    initICCastResource();
    return m_pICCastResource;
}

void ResourceFactory::initDriveNextResource()
{
    if (!m_pDriveNextResource)
    {
        m_pDriveNextResource = new CDriveNextResourceImpl();
    }
}

void ResourceFactory::deleteDriveNextResource()
{
    if(m_pDriveNextResource)
    {
        delete m_pDriveNextResource;
        m_pDriveNextResource = nullptr;
    }
}

IDriveNextResource *ResourceFactory::getDriveNextResource()
{
    initDriveNextResource();
    return m_pDriveNextResource;
}

void ResourceFactory::initDeviceModeHandlerResource()
{
    if (!m_pDeviceModeHandlerResource)
    {
        m_pDeviceModeHandlerResource = new CDeviceModeHandlerResourceImpl();
    }
}

void ResourceFactory::disposeDeviceModeHandlerResource()
{
    if(m_pDeviceModeHandlerResource)
    {
        delete m_pDeviceModeHandlerResource;
        m_pDeviceModeHandlerResource = NULL;
    }
}

IDeviceModeHandlerResource *ResourceFactory::getDeviceModeHandlerResource()
{
    initDeviceModeHandlerResource();
    return m_pDeviceModeHandlerResource;
}

void ResourceFactory::initAndroidAutoResource()
{
    if (!m_pAndroidAutoResource)
    {
        m_pAndroidAutoResource = new CAndroidAutoResourceImpl();
    }
}

void ResourceFactory::deleteAndroidAutoResource()
{
    if(m_pAndroidAutoResource)
    {
        delete m_pAndroidAutoResource;
        m_pAndroidAutoResource = NULL;
    }
}

IAndroidAutoResource *ResourceFactory::getAndroidAutoResource()
{
    initAndroidAutoResource();
    return m_pAndroidAutoResource;
}

void ResourceFactory::initPhoneCallManagerResource()
{
    if (!m_pPhoneCallManagerResource)
    {
        m_pPhoneCallManagerResource = new CPhoneCallManagerResourceImpl();
    }
}

void ResourceFactory::disposePhoneCallManagerResource()
{
    if(m_pPhoneCallManagerResource)
    {
        delete m_pPhoneCallManagerResource;
        m_pPhoneCallManagerResource = NULL;
    }
}

IPhoneCallManagerResource* ResourceFactory::getPhoneCallManagerResource()
{
    initPhoneCallManagerResource();
    return m_pPhoneCallManagerResource;
}

void ResourceFactory::initPhonePIMDBResource()
{
    if (!m_pPhonePimDbResource)
    {
        m_pPhonePimDbResource = new CPhonePIMDBResourceImpl();
    }
}

void ResourceFactory::disposePhonePIMDBResource()
{
    if(m_pPhonePimDbResource)
    {
        delete m_pPhonePimDbResource;
        m_pPhonePimDbResource = NULL;
    }
}

IPhonePIMDBResource *ResourceFactory::getPhonePIMDBResource()
{
    initPhonePIMDBResource();
    return m_pPhonePimDbResource;
}

void ResourceFactory::initPowerModeResource()
{
    if(!m_pPowerModeResource)
    {
        m_pPowerModeResource = new CPowerModeResourceImpl();
    }
}

void ResourceFactory::deletePowerModeResource()
{
    if(m_pPowerModeResource)
    {
        delete m_pPowerModeResource;
        m_pPowerModeResource = NULL;
    }
}

IPowerModeResource* ResourceFactory::getPowerModeResource()
{
    initPowerModeResource();
    return m_pPowerModeResource;
}

void ResourceFactory::initHVACResource()
{
    if(nullptr == m_pHVACResource)
    {
        m_pHVACResource = new CHVACResourceImpl();
    }
}

void ResourceFactory::deleteHVACResource()
{
    if(m_pHVACResource)
    {
        delete m_pHVACResource;
        m_pHVACResource = nullptr;
    }
}

IHVACResource* ResourceFactory::getHVACResource()
{
    initHVACResource();
    return m_pHVACResource;
}

void ResourceFactory::initDisplayManagerResource()
{
    if(nullptr == m_pDisplayManagerResource)
    {
        m_pDisplayManagerResource = new CDisplayManagerResourceImpl();
    }
}

void ResourceFactory::deleteDisplayManagerResource()
{
    if(m_pDisplayManagerResource)
    {
        delete m_pDisplayManagerResource;
        m_pDisplayManagerResource = nullptr;
    }
}

IDisplayManagerResource *ResourceFactory::getDisplayManagerResource()
{
    initDisplayManagerResource();
    return m_pDisplayManagerResource;
}

void ResourceFactory::initAppleCarPlayResource()
{
    if(nullptr == m_pAppleCarPlayResource)
    {
        m_pAppleCarPlayResource = new CAppleCarPlayResourceImpl();
    }
}

void ResourceFactory::deleteAppleCarPlayResource()
{
    if(m_pAppleCarPlayResource)
    {
        delete m_pAppleCarPlayResource;
        m_pAppleCarPlayResource = nullptr;
    }
}

IAppleCarPlayResource *ResourceFactory::getAppleCarPlayResource()
{
    initAppleCarPlayResource();
    return m_pAppleCarPlayResource;
}

void ResourceFactory::initVehicleResource()
{
    if(nullptr == m_pVehicleResource)
    {
        m_pVehicleResource = new CVehicleResourceImpl();
    }
}

IVehicleResource *ResourceFactory::getVehicleResource()
{
    initVehicleResource();
    return m_pVehicleResource;
}

void ResourceFactory::deleteVehicleResource()
{
    if(m_pVehicleResource)
    {
        delete m_pVehicleResource;
        m_pVehicleResource = nullptr;
    }
}

void ResourceFactory::initParkAssistResource()
{
    if(nullptr == m_pParkAssistResource)
    {
        m_pParkAssistResource = new CParkAssistResourceImpl();
    }
}

IParkAssistResource *ResourceFactory::getParkAssistResource()
{
    initParkAssistResource();
    return m_pParkAssistResource;
}

void ResourceFactory::deleteParkAssistResource()
{
    if(m_pParkAssistResource)
    {
        delete m_pParkAssistResource;
        m_pParkAssistResource = nullptr;
    }
}

void ResourceFactory::initDateAndTimeResource()
{
    if(nullptr == m_pDateAndTimeResource)
    {
        m_pDateAndTimeResource = new CDateAndTimeResourceImpl();
    }
}

void ResourceFactory::deleteDateAndTimeResource()
{
    if(m_pDateAndTimeResource)
    {
        delete m_pDateAndTimeResource;
        m_pDateAndTimeResource = nullptr;
    }
}

IDateAndTimeResource *ResourceFactory::getDateAndTimeResource()
{
    initDateAndTimeResource();
    return m_pDateAndTimeResource;
}

void ResourceFactory::initIntrospectionStubResource()
{
    if(!m_pIntrospectionStubResource)
    {
        m_pIntrospectionStubResource = new CIntrospectionStubResource();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION,"Introspection Resource is null");
    }
}

void ResourceFactory::disposeIntrospectionStubResource()
{
    if(m_pIntrospectionStubResource)
    {
        delete m_pIntrospectionStubResource;
        m_pIntrospectionStubResource = nullptr;
    }
}

CIntrospectionStubResource* ResourceFactory::getIntrospectionStubResource()
{
    if(NULL == m_pIntrospectionStubResource)
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MAIN,"%s Introspection resource is empty "
                                            "reinitializing...", __FUNCTION__);
        initIntrospectionStubResource();
    }
    return m_pIntrospectionStubResource;
}

void ResourceFactory::initVoiceAlertsResource()
{
    if(NULL == m_pVoiceAlertsResource)
    {
        m_pVoiceAlertsResource = new CVoiceAlertsResImpl();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MAIN,"%s VoiceAlerts reource is already created.", __FUNCTION__);
    }

}

void ResourceFactory::disposeVoiceAlertsResource()
{
    delete m_pVoiceAlertsResource;
    m_pVoiceAlertsResource = NULL;
}

IVoiceAlerts *ResourceFactory::getVoiceAlertResource()
{
    if(NULL == m_pVoiceAlertsResource)
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MAIN,"%s VoiceAlerts reource is empty "
                                            "reinitializing...", __FUNCTION__);
        initVoiceAlertsResource();
    }
    return m_pVoiceAlertsResource;
}


void ResourceFactory::initVersionManagerResource()
{
    if ( nullptr == m_pVersionManagerResource)
    {
        m_pVersionManagerResource = new CVersionManagerResourceImpl();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VERSION_MANAGER,"Version Manager Resource is null");
    }
}

IVersionManagerResource *ResourceFactory::getVersionManagerResource()
{
    initVersionManagerResource();
    return m_pVersionManagerResource;
}

void ResourceFactory::deleteVersionManagerResource()
{
    if(m_pVersionManagerResource)
    {
        delete m_pVersionManagerResource;
        m_pVersionManagerResource = nullptr;
    }
}

void ResourceFactory::initVRStubResource()
{
    if(!m_pVRStubResource)
    {
        m_pVRStubResource = new CVRStubResource();
    }
}

void ResourceFactory::disposeVRStubResource()
{
    if(m_pVRStubResource)
    {
        delete m_pVRStubResource;
        m_pVRStubResource = NULL;
    }
}

CVRStubResource* ResourceFactory::getVRStubResource()
{
    initVRStubResource();
    return m_pVRStubResource;
}

void ResourceFactory::initBtPluginResource()
{
    if(!m_pBtPluginResource)
    {
        m_pBtPluginResource = new CBtPluginResourceImpl();
    }
}

void ResourceFactory::disposeBtPluginResource()
{
    if(m_pBtPluginResource)
    {
        delete m_pBtPluginResource;
        m_pBtPluginResource = NULL;
    }
}

IBtPluginResource* ResourceFactory::getBtPluginResource()
{
    initBtPluginResource();
    return m_pBtPluginResource;
}

void ResourceFactory::initDiagnosticResource()
{
    if ( nullptr == m_pDiagnosticResource)
    {
        m_pDiagnosticResource = new CDiagnosticResourceImpl();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DIAGNOSTIC,"Diagnostic Resource is null");
    }
}

IDiagnosticResource *ResourceFactory::getDiagnosticResource()
{
    if(!m_pDiagnosticResource)
    {
        initDiagnosticResource();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DIAGNOSTIC,"Diagnostic Resource is already created.");
    }

    return m_pDiagnosticResource;
}

void ResourceFactory::deleteDiagnosticResource()
{
    if(m_pDiagnosticResource)
    {
        delete m_pDiagnosticResource;
        m_pDiagnosticResource = nullptr;
    }
}

void ResourceFactory::initLayerManagerResource()
{
    if(nullptr == m_pLayerManagerResource)
    {
        m_pLayerManagerResource = new CLayerManagerResourceImpl();
    }
}

void ResourceFactory::deleteLayerManagerResource()
{
    if(m_pLayerManagerResource)
    {
        delete m_pLayerManagerResource;
        m_pLayerManagerResource = nullptr;
    }
}

ILayerManagerResource* ResourceFactory::getLayerManagerResource()
{
    if(!m_pLayerManagerResource)
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MAIN,"%s LayerManager proxy reource is empty "
                                            "reinitializing...", __FUNCTION__);
        initLayerManagerResource();
    }
    return m_pLayerManagerResource;
}

void ResourceFactory::initVRProxyResource()
{
    if(!m_pVRProxyResource)
    {
        m_pVRProxyResource = new CVRProxyResImpl();
    }
}

void ResourceFactory::disposeVRProxyResource()
{
    if(m_pVRProxyResource)
    {
        delete m_pVRProxyResource;
        m_pVRProxyResource = nullptr;
    }
}

IVRProxyResource* ResourceFactory::getVRProxyResource()
{
    if(!m_pVRProxyResource)
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MAIN,"%s VR proxy reource is empty "
                                            "reinitializing...", __FUNCTION__);
        initVRProxyResource();
    }
    return m_pVRProxyResource;
}

void ResourceFactory::initVariantControlResource()
{
    if(!m_pVariantControlResource)
    {
        m_pVariantControlResource = new CVariantControlResourceImpl();
    }
}

void ResourceFactory::deleteVariantControlResource()
{
    if(m_pVariantControlResource)
    {
        delete m_pVariantControlResource;
        m_pVariantControlResource = nullptr;
    }
}

IVariantControlResource* ResourceFactory::getVariantControlResource()
{
    if(!m_pVariantControlResource)
    {
        initVariantControlResource();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VARIANT_CONTROL,"Variant Control Resource is already created.");
    }
    return m_pVariantControlResource;
}


void ResourceFactory::initW3WResource()
{
    if (!m_pW3WResource)
    {
        m_pW3WResource = new CW3WResourceImpl();
    }
}

void ResourceFactory::deleteW3WResource()
{
    if(m_pW3WResource)
    {
        delete m_pW3WResource;
        m_pW3WResource = nullptr;
    }
}

IW3WResource *ResourceFactory::getW3WResource()
{
    initW3WResource();
    return m_pW3WResource;
}

void ResourceFactory::initDoodleResource()
{
    if (!m_pDoodleResource)
    {
        m_pDoodleResource = new CDoodleResourceImpl();
    }
}

void ResourceFactory::deleteDoodleResource()
{
    if(m_pDoodleResource)
    {
        delete m_pDoodleResource;
        m_pDoodleResource = nullptr;
    }
}

IDoodleResource *ResourceFactory::getDoodleResource()
{
    initDoodleResource();
    return m_pDoodleResource;
}
