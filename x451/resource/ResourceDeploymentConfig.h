#ifndef RESOURCEDEPLOYMENTCONFIG_H
#define RESOURCEDEPLOYMENTCONFIG_H

#include <string>

class ResourceDeploymentConfig
{
private :

    ResourceDeploymentConfig();
    ResourceDeploymentConfig(const ResourceDeploymentConfig &);//Disable Copy
    ResourceDeploymentConfig& operator=(const ResourceDeploymentConfig&);//Disable Copy

public :

    static ResourceDeploymentConfig& getConfig();
    static ResourceDeploymentConfig* m_pSelf;

    struct CommonAPIClient
    {
    public :
        CommonAPIClient(const std::string & domain,const std::string & instance)
            :domain(domain)
            ,instance(instance)
        {

        }

        const std::string domain;
        const std::string instance;
    private :
        CommonAPIClient();
    };


    CommonAPIClient m_Tuner_Proxy;
    CommonAPIClient m_Tuner_Introspection_Proxy;
    CommonAPIClient m_Audio_Control;
    CommonAPIClient m_Audio_Settings;
    CommonAPIClient m_MediaPlayer_Proxy;
    CommonAPIClient m_Hardkey_Proxy;
    CommonAPIClient m_HardkeyPlugin_Proxy;
    CommonAPIClient m_EnggMenu_Proxy;
    CommonAPIClient m_SoftwareUpdate_Proxy;
    CommonAPIClient m_Media_Browser;
    CommonAPIClient m_PhoneConnectionManager_Proxy;
    CommonAPIClient m_DeviceModeHandler_Proxy;
    CommonAPIClient m_AndroidAuto_Proxy;
    CommonAPIClient m_PhoneCallManager_Proxy;
    CommonAPIClient m_Phone_PimDb_Proxy;
    CommonAPIClient m_PowerMode_Proxy;
    CommonAPIClient m_CcmHu_Proxy;
    CommonAPIClient m_VersionManager_Proxy;
    CommonAPIClient m_DisplayManager_Proxy;
    CommonAPIClient m_Media_Manager;
    CommonAPIClient m_AndroidAutoPlugin_Proxy;
    CommonAPIClient m_Audio_Plugin;
    CommonAPIClient m_AppleCarPlay_Proxy;
    CommonAPIClient m_AppleCarPlayPlugin_Proxy;
    CommonAPIClient m_PdcService_Proxy;
    CommonAPIClient m_VehicleSettingsService_Proxy;
    CommonAPIClient m_MediaPlugin_Proxy;
    CommonAPIClient m_TimeManager_Proxy;
    CommonAPIClient m_VoiceAlertProxy;
    CommonAPIClient m_BtPressPlugin_Proxy;
    CommonAPIClient m_Diagnostic_Proxy;
    CommonAPIClient m_LayerManager_Proxy;
    CommonAPIClient m_VR_Proxy;
    CommonAPIClient m_RCA_Proxy;
    CommonAPIClient m_ICCast_Proxy;
    CommonAPIClient m_DriveNext_Proxy;
    CommonAPIClient m_W3WCore_Proxy;
    CommonAPIClient m_W3WPlugin_Proxy;
};

#endif // RESOURCEDEPLOYMENTCONFIG_H
