#include "ResourceDeploymentConfig.h"


ResourceDeploymentConfig::ResourceDeploymentConfig()
    :
      #ifdef PLATFORM_WIN32
      m_Tuner_Proxy("local","OrinocoTuner/inst0"),
      m_Tuner_Introspection_Proxy("local","TunerIntrospection/inst0"),
      #else
      m_Tuner_Proxy("local","inst0"),
      m_Tuner_Introspection_Proxy("local","inst0"),
      #endif
      m_Audio_Control("local","AudioPresCtrl.controlsInst"),
      m_Audio_Settings("local", "AudioPresCtrl.settingsInst"),
      m_MediaPlayer_Proxy("local","mmpres.playengine"),
      m_Hardkey_Proxy("local","keypres.keysInst"),
      m_HardkeyPlugin_Proxy("local","keypresplugin.keypresplugin"),
      m_EnggMenu_Proxy("local","EnggMenuPresCtrlService.EnggServiceInstance"),
      m_SoftwareUpdate_Proxy("local", "SoftwareUpdate.swdl"),
      m_Media_Browser("local","mmpres.browser"),
      m_PhoneConnectionManager_Proxy("local","btpres.connectionManager"),
      m_DeviceModeHandler_Proxy("local","devpres.devModeHandlerInst"),
      m_AndroidAuto_Proxy("local","aapres.aaCtrlInst"),
      m_PhoneCallManager_Proxy("local","btpres.callManager"),
      m_Phone_PimDb_Proxy("local","btpres.pimManager"),
      m_PowerMode_Proxy("local","NodeStateManager.inst0"),
      m_CcmHu_Proxy("local","CCmPresCtrlService.CcmServiceInstance"),
      m_VersionManager_Proxy("local", "VersionManagerComponent.vmsInstance"),
      m_DisplayManager_Proxy("local", "CDisplayMgrPresCtrl.serverInstance"),
      m_Media_Manager("local","mmpres.mediamanager"),
      m_AndroidAutoPlugin_Proxy("local","TataAndroidAutoPresPlugin.TataPluginInstance"),
      m_Audio_Plugin("local", "TataAudioPresPlugin.audioPresPluginInst"),
      m_AppleCarPlay_Proxy("local","cppres.cpCtrlInst"),
      m_AppleCarPlayPlugin_Proxy("local","TataCarPlayPresPlugin.TataPluginInstance"),
      m_PdcService_Proxy("local","ParkAssist.PDCInstance"),
      m_VehicleSettingsService_Proxy("local", "VehicleSettingsPresCtrl.vehSettings"),
      m_MediaPlugin_Proxy("local", "mmpres.plugin"),
      m_TimeManager_Proxy("local","TimeManagerProvider.sysTimeMgr"),
      m_VoiceAlertProxy("local","VoiceAlert.VASInstance"),
      m_BtPressPlugin_Proxy("local", "TMLBtPresPlugin.btManagerExt"),
      m_Diagnostic_Proxy("local", "DiagnosticService.diagnosticServiceInst"),
      m_LayerManager_Proxy("local","layermanager.inst0"),
      m_VR_Proxy("local", "UISpeechService.UISpeechIntf"),
      m_RCA_Proxy("local","RCAService.rcasettings"),
      m_ICCast_Proxy("local", "IcRenderPres.icRenderServiceInstance"),
      m_DriveNext_Proxy("local", "DriveProPres.dppres"),
      m_W3WCore_Proxy("local", "w3w.w3wcore"),
      m_W3WPlugin_Proxy("local", "w3wplugin.w3wplugin")
{

}

ResourceDeploymentConfig& ResourceDeploymentConfig::getConfig()
{
    if ( nullptr == m_pSelf )
    {
        m_pSelf = new ResourceDeploymentConfig();
    }
    return *m_pSelf;
}

ResourceDeploymentConfig* ResourceDeploymentConfig::m_pSelf = nullptr;

