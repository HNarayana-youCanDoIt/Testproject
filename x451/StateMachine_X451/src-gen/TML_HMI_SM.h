
#ifndef TML_HMI_SM_H_
#define TML_HMI_SM_H_

#include <deque>
#include "../src/sc_types.h"
#include "../src/StatemachineInterface.h"
#include "../src/TimedStatemachineInterface.h"

/*! \file Header of the state machine 'TML_HMI_SM'.
*/


#ifndef SCT_EVENTS_TML_HMI_SM_H
#define SCT_EVENTS_TML_HMI_SM_H

namespace tml_hmi_sm_events
{
typedef enum  {
	InternalSCI_evCloseDrawer,
	InternalSCI_evHideVolOverlay,
	InternalSCI_evHideHvacOverlay,
	InternalSCI_evClosePopupInternal,
	InternalSCI_evCloseNotificationInternal,
	InternalSCI_evClosePopupOnMinTimeout,
	InternalSCI_evCloseNotificationOnMinTimeout,
	TimeEvent
} TML_HMI_SMEventName;

class SctEvent
{
	public:
		SctEvent(TML_HMI_SMEventName name) : name(name){}
		virtual ~SctEvent(){}
		const TML_HMI_SMEventName name;
		
};
		
template <typename T>
class TypedSctEvent : public SctEvent
{
	public:
		TypedSctEvent(TML_HMI_SMEventName name, T value) :
			SctEvent(name),
			value(value)
			{}
		virtual ~TypedSctEvent(){}
		const T value;
};

class SctEvent_InternalSCI_evCloseDrawer : public SctEvent
{
	public:
		SctEvent_InternalSCI_evCloseDrawer(TML_HMI_SMEventName name) : SctEvent(name){};
};
class SctEvent_InternalSCI_evHideVolOverlay : public SctEvent
{
	public:
		SctEvent_InternalSCI_evHideVolOverlay(TML_HMI_SMEventName name) : SctEvent(name){};
};
class SctEvent_InternalSCI_evHideHvacOverlay : public SctEvent
{
	public:
		SctEvent_InternalSCI_evHideHvacOverlay(TML_HMI_SMEventName name) : SctEvent(name){};
};
class SctEvent_InternalSCI_evClosePopupInternal : public SctEvent
{
	public:
		SctEvent_InternalSCI_evClosePopupInternal(TML_HMI_SMEventName name) : SctEvent(name){};
};
class SctEvent_InternalSCI_evCloseNotificationInternal : public SctEvent
{
	public:
		SctEvent_InternalSCI_evCloseNotificationInternal(TML_HMI_SMEventName name) : SctEvent(name){};
};
class SctEvent_InternalSCI_evClosePopupOnMinTimeout : public SctEvent
{
	public:
		SctEvent_InternalSCI_evClosePopupOnMinTimeout(TML_HMI_SMEventName name) : SctEvent(name){};
};
class SctEvent_InternalSCI_evCloseNotificationOnMinTimeout : public SctEvent
{
	public:
		SctEvent_InternalSCI_evCloseNotificationOnMinTimeout(TML_HMI_SMEventName name) : SctEvent(name){};
};

}
#endif /* SCT_EVENTS_TML_HMI_SM_H */

/*! Define indices of states in the StateConfVector */
#define SCVI_STARTUP_REGION_EARLYWAKEUP 0
#define SCVI_STARTUP_REGION_UI 0
#define SCVI_STARTUP_REGION_UI_HOME_PDC 0
#define SCVI_STARTUP_REGION_UI_HOME_PDC_ACTIVE_PDC_REGION_UI_PDC 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_HOME 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_HOME_HOME_HOMESCREENMAIN 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_HOME_HOME_HOMESCREENUPDATESHORTCUTS 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_HOME_HOME_CONFIGUREFAVHK 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_POWERMODE 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_POWERMODE_POWERMODES_MEDIAOFF 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_SETUPMAIN 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_VEHICLESETUP 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_PARKASSIST 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_MOODLIGHTING 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_BLUETOOTHSETUP 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_EDITSMSLIGHTBOX 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_VOLUMESETUP 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_AUXINGAIN 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_GENERALSETUP 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_SETDATE 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_SETTIME 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_SOFTWAREDETAILS 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_DISPLAYSETUP 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_VOICEALERTS 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_PAIREDDEVICES 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_PAIRNEWDEVICE 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_DELETEDEVICE 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_LIGHTINGSETUP 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_ABOUT 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_AUDIOSETUP 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_AUDIOSETUP_AUDIOSETUP_REGION_AUDIOPRESETS 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_AUDIOSETUP_AUDIOSETUP_REGION_BALANCEFADER 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ENGGMENU 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ENGGMENU_ENGG_REGION_ENGGMENUMAIN 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ENGGMENU_ENGG_REGION_TESTMODE 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ENGGMENU_ENGG_REGION_ILLUMINATION 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ENGGMENU_ENGG_REGION_ILLUMINATION_TESTMODE_ILLUMINATIONSCREENMAIN 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ENGGMENU_ENGG_REGION_ILLUMINATION_TESTMODE_DISPLAYILLUMINATION 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ENGGMENU_ENGG_REGION_ILLUMINATION_TESTMODE_BUTTONPANELILLUMINATION 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ENGGMENU_ENGG_REGION_BUTTONPANEL 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ENGGMENU_ENGG_REGION_DEBUGLOG 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ENGGMENU_ENGG_REGION_SYSTEMCONFIG 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ENGGMENU_ENGG_REGION_SYSTEMCONFIG_SYSTEMCONFIGURATION_SYSTEMCONFIGURATION 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ENGGMENU_ENGG_REGION_SYSTEMCONFIG_SYSTEMCONFIGURATION_VIN 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ENGGMENU_ENGG_REGION_SYSTEMCONFIG_SYSTEMCONFIGURATION__16RPART 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ENGGMENU_ENGG_REGION_SYSTEMCONFIG_SYSTEMCONFIGURATION__16RPART__16RPARTNO__16RPARTNOSCREENMAIN 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ENGGMENU_ENGG_REGION_SYSTEMCONFIG_SYSTEMCONFIGURATION__16RPART__16RPARTNO_PARAMETERPARTNO 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ENGGMENU_ENGG_REGION_SYSTEMCONFIG_SYSTEMCONFIGURATION__16RPART__16RPARTNO_SOFTWAREPARTNO 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ENGGMENU_ENGG_REGION_SYSTEMCONFIG_SYSTEMCONFIGURATION__16RPART__16RPARTNO_BUTTONPANELPARTNO 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ENGGMENU_ENGG_REGION_SYSTEMCONFIG_SYSTEMCONFIGURATION__16RPART__16RPARTNO_CONTAINERPARTNO 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ENGGMENU_ENGG_REGION_SYSTEMCONFIG_SYSTEMCONFIGURATION__16RPART__16RPARTNO_SILVERBOXPARTNO 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ENGGMENU_ENGG_REGION_SYSTEMCONFIG_SYSTEMCONFIGURATION__16RPART__16RPARTNO_DISPLAYHWPARTNO 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ENGGMENU_ENGG_REGION_SYSTEMCONFIG_SYSTEMCONFIGURATION_GPSCOORDINATE 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ENGGMENU_ENGG_REGION_PICTUREVIEWER 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ANDROIDAUTO 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ANDROIDAUTO_AA_REGION_AAMAIN 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_CARPLAY 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_CARPLAY_CARPLAY_REGION_CARPLAYMAIN 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SAL 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SAL_SAL_REGION_SMARTLINKMAIN 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SOFTWAREUPDATE 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SOFTWAREUPDATE_SWUPDATE_REGION_SOFTWAREUPDATEMAIN 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SOFTWAREUPDATE_SWUPDATE_REGION_SOFTWARESELECTSCREEN 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_PHONE 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_PHONE_PHONEBROWSE_REGION_FAVORITES 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_PHONE_PHONEBROWSE_REGION_CONTACTS 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_PHONE_PHONEBROWSE_REGION_NUMPAD 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_PHONE_PHONEBROWSE_REGION_CALLLOGS 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_PHONE_PHONEBROWSE_REGION_CONTACTDETAILS 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ACTIVEAUDIO 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ACTIVEAUDIO_ACTIVEAUDIO_MEDIA 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ACTIVEAUDIO_ACTIVEAUDIO_MEDIA_MEDIA_REGION_MEDIALOADING_ 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ACTIVEAUDIO_ACTIVEAUDIO_MEDIA_MEDIA_REGION_MEDIAMAIN 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ACTIVEAUDIO_ACTIVEAUDIO_MEDIA_MEDIA_REGION_MEDIAPICTURE 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ACTIVEAUDIO_ACTIVEAUDIO_MEDIA_MEDIA_REGION_MEDIAVIDEO 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ACTIVEAUDIO_ACTIVEAUDIO_MEDIA_MEDIA_REGION_MEDIAAUX 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ACTIVEAUDIO_ACTIVEAUDIO_MEDIA_MEDIA_REGION_AUXINGAIN 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ACTIVEAUDIO_ACTIVEAUDIO_MEDIA_MEDIA_REGION_MEDIABROWSEMAIN 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ACTIVEAUDIO_ACTIVEAUDIO_MEDIA_MEDIA_REGION_MEDIABROWSEMAIN_MEDIABROWSEMAIN_MEDIABROWSECATEGORY 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ACTIVEAUDIO_ACTIVEAUDIO_MEDIA_MEDIA_REGION_MEDIABROWSEMAIN_MEDIABROWSEMAIN_MEDIABROWSE 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ACTIVEAUDIO_ACTIVEAUDIO_TUNER 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ACTIVEAUDIO_ACTIVEAUDIO_TUNER_TUNER_REGION_TUNERMAIN 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ACTIVEAUDIO_ACTIVEAUDIO_TUNER_TUNER_REGION_TUNERMAIN_TUNER_MAIN_TUNERDEFAULT 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ACTIVEAUDIO_ACTIVEAUDIO_TUNER_TUNER_REGION_TUNERMAIN_TUNER_MAIN_TUNERAUTOSEEKUP 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ACTIVEAUDIO_ACTIVEAUDIO_TUNER_TUNER_REGION_TUNERMAIN_TUNER_MAIN_TUNERAUTOSTORE 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ACTIVEAUDIO_ACTIVEAUDIO_TUNER_TUNER_REGION_TUNERMAIN_TUNER_MAIN_TUNERSCAN 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ACTIVEAUDIO_ACTIVEAUDIO_TUNER_TUNER_REGION_TUNERMAIN_TUNER_MAIN_TUNERAUTOSEEKDOWN 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_ACTIVEAUDIO_ACTIVEAUDIO_TUNER_TUNER_REGION_TUNEROPTION 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_VRHELP 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_VRHELP_VR_REGION_VRHELPMAIN 0
#define SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_VRHELP_VR_REGION_VRHELPDETAIL 0
#define SCVI_STARTUP_REGION_UI_HOME_PHONECALL 0
#define SCVI_STARTUP_REGION_UI_HOME_PHONECALL_PHONE_CALL_REGION_PHONECALLSCREEN 0
#define SCVI_STARTUP_REGION_UI_HOME_PHONECALL_PHONE_CALL_REGION_PARTICIPANTSCREEN 0
#define SCVI_STARTUP_REGION_UI_HOME_PHONECALL_PHONE_CALL_REGION_PHONECALLBROWSE 0
#define SCVI_STARTUP_REGION_UI_HOME_PHONECALL_PHONE_CALL_REGION_PHONECALLBROWSE_PHONEBROWSE_REGION_FAVORITES 0
#define SCVI_STARTUP_REGION_UI_HOME_PHONECALL_PHONE_CALL_REGION_PHONECALLBROWSE_PHONEBROWSE_REGION_CONTACTS 0
#define SCVI_STARTUP_REGION_UI_HOME_PHONECALL_PHONE_CALL_REGION_PHONECALLBROWSE_PHONEBROWSE_REGION_NUMPAD 0
#define SCVI_STARTUP_REGION_UI_HOME_PHONECALL_PHONE_CALL_REGION_PHONECALLBROWSE_PHONEBROWSE_REGION_CALLLOGS 0
#define SCVI_STARTUP_REGION_UI_HOME_PHONECALL_PHONE_CALL_REGION_PHONECALLBROWSE_PHONEBROWSE_REGION_CONTACTDETAILS 0
#define SCVI_STARTUP_REGION_UI_HOME_VR 0
#define SCVI_STARTUP_REGION_UI_POPUP_POPUPMANAGER 1
#define SCVI_STARTUP_REGION_UI_POPUP_POPUPMANAGER_ZONE2_NONOTIFICATION 1
#define SCVI_STARTUP_REGION_UI_POPUP_POPUPMANAGER_ZONE2_NOTIFICATIONACTIVE 1
#define SCVI_STARTUP_REGION_UI_POPUP_POPUPMANAGER_ZONE2_NOTIFICATIONACTIVE_NOTIFICATION_TIMER_REGION_NOTIFICATIONTIMERSTATE 1
#define SCVI_STARTUP_REGION_UI_POPUP_POPUPMANAGER_ZONE4_NOPOPUP 2
#define SCVI_STARTUP_REGION_UI_POPUP_POPUPMANAGER_ZONE4_POPUPACTIVE 2
#define SCVI_STARTUP_REGION_UI_POPUP_POPUPMANAGER_ZONE4_POPUPACTIVE_POPUP_TIMER_REGION_POPUPTIMERSTATE 2
#define SCVI_STARTUP_REGION_UI_DRAWER_DRAWERMANAGER 3
#define SCVI_STARTUP_REGION_UI_DRAWER_DRAWERMANAGER_DRAWERS_MAIN_REGION_DRAWERSVISIBLESTATE 3
#define SCVI_STARTUP_REGION_UI_DRAWER_DRAWERMANAGER_DRAWERS_MAIN_REGION_DRAWERSVISIBLESTATE_SHORTCUT_DRAWER_REGION_SHORTCUTDRAWERMINIMIZEDSTATE 3
#define SCVI_STARTUP_REGION_UI_DRAWER_DRAWERMANAGER_DRAWERS_MAIN_REGION_DRAWERSVISIBLESTATE_SHORTCUT_DRAWER_REGION_SOURCEDRAWERMAXIMIZEDSTATE 3
#define SCVI_STARTUP_REGION_UI_DRAWER_DRAWERMANAGER_DRAWERS_MAIN_REGION_DRAWERSVISIBLESTATE_SHORTCUT_DRAWER_REGION_SOURCEDRAWERMAXIMIZEDSTATE_SOURCE_DRAWER_MAXIMIZED_REGION_SOURCEDRAWERTIMERSTATE 3
#define SCVI_STARTUP_REGION_UI_DRAWER_DRAWERMANAGER_DRAWERS_MAIN_REGION_DRAWERSVISIBLESTATE_SHORTCUT_DRAWER_REGION_HVACDRAWERMAXIMIZEDSTATE 3
#define SCVI_STARTUP_REGION_UI_DRAWER_DRAWERMANAGER_DRAWERS_MAIN_REGION_DRAWERSVISIBLESTATE_SHORTCUT_DRAWER_REGION_HVACDRAWERMAXIMIZEDSTATE_HVAC_DRAWER_MAXIMIZED_REGION_HVACDRAWERTIMERSTATE 3
#define SCVI_STARTUP_REGION_UI_DRAWER_DRAWERMANAGER_DRAWERS_MAIN_REGION_DRAWERSVISIBLESTATE_QAD_DRAWER_VISIBLE_REGION_QUICKACCESSDRAWERMINIMIZEDSTATE 4
#define SCVI_STARTUP_REGION_UI_DRAWER_DRAWERMANAGER_DRAWERS_MAIN_REGION_DRAWERSVISIBLESTATE_QAD_DRAWER_VISIBLE_REGION_QUICKACCESSDRAWERMAXIMIZEDSTATE 4
#define SCVI_STARTUP_REGION_UI_DRAWER_DRAWERMANAGER_DRAWERS_MAIN_REGION_DRAWERSVISIBLESTATE_QAD_DRAWER_VISIBLE_REGION_QUICKACCESSDRAWERMAXIMIZEDSTATE_QAD_DRAWER_MAXIMIZED_REGION_QADTIMERSTATE 4
#define SCVI_STARTUP_REGION_UI_DRAWER_DRAWERMANAGER_DRAWERS_MAIN_REGION_DRAWERSVISIBLESTATE_STATUS_BAR_REGION_STATUSBARSTATE 5
#define SCVI_STARTUP_REGION_UI_DRAWER_DRAWERMANAGER_DRAWERS_MAIN_REGION_DRAWERSHIDDENSTATE 3
#define SCVI_STARTUP_REGION_UI_DRAWER_DRAWERMANAGER_VOLUME_OVERLAY_REGION_VOLUMEOVERLAY 6
#define SCVI_STARTUP_REGION_UI_DRAWER_DRAWERMANAGER_VOLUME_OVERLAY_REGION_VOLUMEOVERLAY_VOL_OVERLAY_REGION_HIDEVOLUMEOVERLAY 6
#define SCVI_STARTUP_REGION_UI_DRAWER_DRAWERMANAGER_VOLUME_OVERLAY_REGION_VOLUMEOVERLAY_VOL_OVERLAY_REGION_SHOWVOLUMEOVERLAY 6
#define SCVI_STARTUP_REGION_UI_DRAWER_DRAWERMANAGER_VOLUME_OVERLAY_REGION_VOLUMEOVERLAY_VOL_OVERLAY_REGION_SHOWVOLUMEOVERLAY_VOLUME_OVERLAY_SHOW_REGION_VOLOVERLAYTIMERSTATE 6
#define SCVI_STARTUP_REGION_UI_DRAWER_DRAWERMANAGER_HVAC_OVERLAY_REGION_HVACOVERLAY 7
#define SCVI_STARTUP_REGION_UI_DRAWER_DRAWERMANAGER_HVAC_OVERLAY_REGION_HVACOVERLAY_HVAC_OVERLAY_REGION_HIDEHVACOVERLAY 7
#define SCVI_STARTUP_REGION_UI_DRAWER_DRAWERMANAGER_HVAC_OVERLAY_REGION_HVACOVERLAY_HVAC_OVERLAY_REGION_SHOWHVACOVERLAY 7
#define SCVI_STARTUP_REGION_UI_DRAWER_DRAWERMANAGER_HVAC_OVERLAY_REGION_HVACOVERLAY_HVAC_OVERLAY_REGION_SHOWHVACOVERLAY_HVAC_SHOW_OVERLAY_REGIOIN_HVACOVERLAYTIMERSTATE 7
#define SCVI_STARTUP_REGION_STARTUPANIMATION 0

class TML_HMI_SM : public TimedStatemachineInterface, public StatemachineInterface
{
	public:
		
		TML_HMI_SM();
		
		~TML_HMI_SM();
		
		/*! Enumeration of all states */ 
		typedef enum
		{
			TML_HMI_SM_last_state,
			startup_region_EarlyWakeup,
			startup_region_Ui,
			startup_region_Ui_home_PDC,
			startup_region_Ui_home_PDC_active_pdc_region_UI_PDC,
			startup_region_Ui_home_Main,
			startup_region_Ui_home_Main_main_Home,
			startup_region_Ui_home_Main_main_Home_home_HomeScreenMain,
			startup_region_Ui_home_Main_main_Home_home_HomeScreenUpdateShortcuts,
			startup_region_Ui_home_Main_main_Home_home_ConfigureFavHK,
			startup_region_Ui_home_Main_main_PowerMode,
			startup_region_Ui_home_Main_main_PowerMode_Powermodes_MediaOff,
			startup_region_Ui_home_Main_main_Setup,
			startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain,
			startup_region_Ui_home_Main_main_Setup_setup_region_VehicleSetup,
			startup_region_Ui_home_Main_main_Setup_setup_region_ParkAssist,
			startup_region_Ui_home_Main_main_Setup_setup_region_MoodLighting,
			startup_region_Ui_home_Main_main_Setup_setup_region_BluetoothSetup,
			startup_region_Ui_home_Main_main_Setup_setup_region_EditSMSLightbox,
			startup_region_Ui_home_Main_main_Setup_setup_region_VolumeSetup,
			startup_region_Ui_home_Main_main_Setup_setup_region_AUXInGain,
			startup_region_Ui_home_Main_main_Setup_setup_region_GeneralSetup,
			startup_region_Ui_home_Main_main_Setup_setup_region_SetDate,
			startup_region_Ui_home_Main_main_Setup_setup_region_SetTime,
			startup_region_Ui_home_Main_main_Setup_setup_region_SoftwareDetails,
			startup_region_Ui_home_Main_main_Setup_setup_region_DisplaySetup,
			startup_region_Ui_home_Main_main_Setup_setup_region_VoiceAlerts,
			startup_region_Ui_home_Main_main_Setup_setup_region_PairedDevices,
			startup_region_Ui_home_Main_main_Setup_setup_region_PairNewDevice,
			startup_region_Ui_home_Main_main_Setup_setup_region_DeleteDevice,
			startup_region_Ui_home_Main_main_Setup_setup_region_LightingSetup,
			startup_region_Ui_home_Main_main_Setup_setup_region_About,
			startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup,
			startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup_audioSetup_region_AudioPresets,
			startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup_audioSetup_region_BalanceFader,
			startup_region_Ui_home_Main_main_EnggMenu,
			startup_region_Ui_home_Main_main_EnggMenu_engg_region_EnggMenuMain,
			startup_region_Ui_home_Main_main_EnggMenu_engg_region_TestMode,
			startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination,
			startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_IlluminationScreenMain,
			startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_DisplayIllumination,
			startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_ButtonPanelIllumination,
			startup_region_Ui_home_Main_main_EnggMenu_engg_region_ButtonPanel,
			startup_region_Ui_home_Main_main_EnggMenu_engg_region_DebugLog,
			startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig,
			startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_SystemConfiguration,
			startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_VIN,
			startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart,
			startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo__16RPartNoScreenMain,
			startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ParameterPartNo,
			startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_SoftwarePartNo,
			startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ButtonPanelPartNo,
			startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ContainerPartNo,
			startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_SilverBoxPartNo,
			startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_DisplayHWPartNo,
			startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_GPSCoordinate,
			startup_region_Ui_home_Main_main_EnggMenu_engg_region_PictureViewer,
			startup_region_Ui_home_Main_main_AndroidAuto,
			startup_region_Ui_home_Main_main_AndroidAuto_aa_region_AAMain,
			startup_region_Ui_home_Main_main_CarPlay,
			startup_region_Ui_home_Main_main_CarPlay_carplay_region_CarPlayMain,
			startup_region_Ui_home_Main_main_SAL,
			startup_region_Ui_home_Main_main_SAL_sal_region_SmartlinkMain,
			startup_region_Ui_home_Main_main_SoftwareUpdate,
			startup_region_Ui_home_Main_main_SoftwareUpdate_swupdate_region_SoftwareUpdateMain,
			startup_region_Ui_home_Main_main_SoftwareUpdate_swupdate_region_SoftwareSelectScreen,
			startup_region_Ui_home_Main_main_Phone,
			startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Favorites,
			startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Contacts,
			startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_NumPad,
			startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_CallLogs,
			startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_ContactDetails,
			startup_region_Ui_home_Main_main_ActiveAudio,
			startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media,
			startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaLoading_,
			startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaMain,
			startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaPicture,
			startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaVideo,
			startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaAux,
			startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_AUXInGain,
			startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain,
			startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowseCategory,
			startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowse,
			startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner,
			startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain,
			startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerDefault,
			startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutoseekUp,
			startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutostore,
			startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerScan,
			startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutoseekDown,
			startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerOption,
			startup_region_Ui_home_Main_main_VRHelp,
			startup_region_Ui_home_Main_main_VRHelp_vr_region_VRHelpMain,
			startup_region_Ui_home_Main_main_VRHelp_vr_region_VRHelpDetail,
			startup_region_Ui_home_PhoneCall,
			startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallScreen,
			startup_region_Ui_home_PhoneCall_phone_call_region_ParticipantScreen,
			startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse,
			startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Favorites,
			startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Contacts,
			startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_NumPad,
			startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_CallLogs,
			startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_ContactDetails,
			startup_region_Ui_home_VR,
			startup_region_Ui_popup_PopupManager,
			startup_region_Ui_popup_PopupManager_Zone2_NoNotification,
			startup_region_Ui_popup_PopupManager_Zone2_NotificationActive,
			startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_notification_timer_region_NotificationTimerState,
			startup_region_Ui_popup_PopupManager_Zone4_NoPopup,
			startup_region_Ui_popup_PopupManager_Zone4_PopupActive,
			startup_region_Ui_popup_PopupManager_Zone4_PopupActive_popup_timer_region_PopupTimerState,
			startup_region_Ui_drawer_DrawerManager,
			startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState,
			startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_ShortcutDrawerMinimizedState,
			startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_SourceDrawerMaximizedState,
			startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_SourceDrawerMaximizedState_source_drawer_maximized_region_SourceDrawerTimerState,
			startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState,
			startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState_hvac_drawer_maximized_region_HVACDrawerTimerState,
			startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMinimizedState,
			startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMaximizedState,
			startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMaximizedState_qad_drawer_maximized_region_QADTimerState,
			startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_status_bar_region_StatusBarState,
			startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersHiddenState,
			startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay,
			startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_HideVolumeOverlay,
			startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_ShowVolumeOverlay,
			startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_ShowVolumeOverlay_volume_overlay_show_region_VolOverlayTimerState,
			startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay,
			startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_HideHvacOverlay,
			startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_ShowHvacOverlay,
			startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_ShowHvacOverlay_hvac_show_overlay_regioin_HvacOverlayTimerState,
			startup_region_StartupAnimation
		} TML_HMI_SMStates;
		
		//! Inner class for default interface scope.
		class DefaultSCI
		{
			
			public:
				DefaultSCI(TML_HMI_SM * parent): 
				evBackPressed_raised(false),
				evBrowse_raised(false),
				evHomeActivated_raised(false),
				evPdcActivated_raised(false),
				evPdcDeactivated_raised(false),
				evMediaActivated_raised(false),
				evTunerActivated_raised(false),
				evPhoneBrowseActivated_raised(false),
				evPhoneBrowseActivated_value(),
				evPhoneCallActivated_raised(false),
				evPhoneCallDeactivated_raised(false),
				evMedOffActivated_raised(false),
				evSetupActivated_raised(false),
				evEnggMenuActivated_raised(false),
				evAndroidAutoActivated_raised(false),
				evCarPlayProjectionStatusChanged_raised(false),
				evSALActivated_raised(false),
				evSoftwareUpdateActivated_raised(false),
				evVRHelpActivated_raised(false),
				evTest_raised(false),
				parent(parent)
				{}
				/*! Gets the value of the variable 'iCurrentHMIContext' that is defined in the default interface scope. */
				sc_integer get_iCurrentHMIContext() const;
				
				/*! Sets the value of the variable 'iCurrentHMIContext' that is defined in the default interface scope. */
				void set_iCurrentHMIContext(sc_integer value);
				
				/*! Gets the value of the variable 'HMI_INVALID_CONTEXT' that is defined in the default interface scope. */
				sc_integer get_hMI_INVALID_CONTEXT() const;
				
				/*! Gets the value of the variable 'HMI_MEDIA_CONTEXT' that is defined in the default interface scope. */
				sc_integer get_hMI_MEDIA_CONTEXT() const;
				
				/*! Gets the value of the variable 'HMI_TUNER_CONTEXT' that is defined in the default interface scope. */
				sc_integer get_hMI_TUNER_CONTEXT() const;
				
				/*! Gets the value of the variable 'HMI_PHONE_CONTEXT' that is defined in the default interface scope. */
				sc_integer get_hMI_PHONE_CONTEXT() const;
				
				/*! Gets the value of the variable 'HMI_PHONE_CALL_CONTEXT' that is defined in the default interface scope. */
				sc_integer get_hMI_PHONE_CALL_CONTEXT() const;
				
				/*! Gets the value of the variable 'HMI_SETUP_CONTEXT' that is defined in the default interface scope. */
				sc_integer get_hMI_SETUP_CONTEXT() const;
				
				/*! Gets the value of the variable 'HMI_HOME_CONTEXT' that is defined in the default interface scope. */
				sc_integer get_hMI_HOME_CONTEXT() const;
				
				/*! Gets the value of the variable 'HMI_MEDIA_OFF_CONTEXT' that is defined in the default interface scope. */
				sc_integer get_hMI_MEDIA_OFF_CONTEXT() const;
				
				/*! Gets the value of the variable 'HMI_ENG_MENU_CONTEXT' that is defined in the default interface scope. */
				sc_integer get_hMI_ENG_MENU_CONTEXT() const;
				
				/*! Gets the value of the variable 'HMI_SOFTWARE_UPDATE_CONTEXT' that is defined in the default interface scope. */
				sc_integer get_hMI_SOFTWARE_UPDATE_CONTEXT() const;
				
				/*! Gets the value of the variable 'HMI_PDC_RVC_CONTEXT' that is defined in the default interface scope. */
				sc_integer get_hMI_PDC_RVC_CONTEXT() const;
				
				/*! Gets the value of the variable 'HMI_ANDROID_AUTO_CONTEXT' that is defined in the default interface scope. */
				sc_integer get_hMI_ANDROID_AUTO_CONTEXT() const;
				
				/*! Gets the value of the variable 'HMI_APPLE_CARPLAY_CONTEXT' that is defined in the default interface scope. */
				sc_integer get_hMI_APPLE_CARPLAY_CONTEXT() const;
				
				/*! Gets the value of the variable 'HMI_SAL_CONTEXT' that is defined in the default interface scope. */
				sc_integer get_hMI_SAL_CONTEXT() const;
				
				/*! Gets the value of the variable 'HMI_EARLY_WAKEUP_CONTEXT' that is defined in the default interface scope. */
				sc_integer get_hMI_EARLY_WAKEUP_CONTEXT() const;
				
				/*! Gets the value of the variable 'HMI_STARTUP_ANIM_CONTEXT' that is defined in the default interface scope. */
				sc_integer get_hMI_STARTUP_ANIM_CONTEXT() const;
				
				/*! Gets the value of the variable 'HMI_VR_PICKLIST_CONTEXT' that is defined in the default interface scope. */
				sc_integer get_hMI_VR_PICKLIST_CONTEXT() const;
				
				/*! Gets the value of the variable 'HMI_VR_HELP_CONTEXT' that is defined in the default interface scope. */
				sc_integer get_hMI_VR_HELP_CONTEXT() const;
				
				/*! Gets the value of the variable 'HMI_DRIVE_NEXT_CONTEXT' that is defined in the default interface scope. */
				sc_integer get_hMI_DRIVE_NEXT_CONTEXT() const;
				
				/*! Gets the value of the variable 'HMI_PHONE_SETUP_CONTEXT' that is defined in the default interface scope. */
				sc_integer get_hMI_PHONE_SETUP_CONTEXT() const;
				
				/*! Gets the value of the variable 'VPM_UNKNOWN' that is defined in the default interface scope. */
				sc_integer get_vPM_UNKNOWN() const;
				
				/*! Gets the value of the variable 'VPM_SWITCH_OFF' that is defined in the default interface scope. */
				sc_integer get_vPM_SWITCH_OFF() const;
				
				/*! Gets the value of the variable 'VPM_EARLY_WAKEUP' that is defined in the default interface scope. */
				sc_integer get_vPM_EARLY_WAKEUP() const;
				
				/*! Gets the value of the variable 'VPM_MEDIA_OFF' that is defined in the default interface scope. */
				sc_integer get_vPM_MEDIA_OFF() const;
				
				/*! Gets the value of the variable 'VPM_ACTIVE' that is defined in the default interface scope. */
				sc_integer get_vPM_ACTIVE() const;
				
				/*! Gets the value of the variable 'VPM_ONE_HOUR' that is defined in the default interface scope. */
				sc_integer get_vPM_ONE_HOUR() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_PARK_ASSIST' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_PARK_ASSIST() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_MOOD_LIGHTING' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_MOOD_LIGHTING() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_BALANCE_FADER' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_BALANCE_FADER() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_AUDIO_PRESETS' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_AUDIO_PRESETS() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_EDIT_SMS' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_EDIT_SMS() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_AUX_GAIN' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_AUX_GAIN() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_SET_DATE' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_SET_DATE() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_SET_TIME' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_SET_TIME() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_PAIRED_DEVICES' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_PAIRED_DEVICES() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_PAIR_NEW_DEVICE' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_PAIR_NEW_DEVICE() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_DELETE_DEVICE' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_DELETE_DEVICE() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_VEHICLE_NAMED_ENTRY' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_VEHICLE_NAMED_ENTRY() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_AUDIO_NAMED_ENTRY' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_AUDIO_NAMED_ENTRY() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_BT_NAMED_ENTRY' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_BT_NAMED_ENTRY() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_VOLUME_NAMED_ENTRY' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_VOLUME_NAMED_ENTRY() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_GENERAL_NAMED_ENTRY' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_GENERAL_NAMED_ENTRY() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_MOODLIGHT_NAMED_ENTRY' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_MOODLIGHT_NAMED_ENTRY() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_BMT_NAMED_ENTRY' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_BMT_NAMED_ENTRY() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_BAL_FAD_NAMED_ENTRY' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_BAL_FAD_NAMED_ENTRY() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_AUD_PRE_NAMED_ENTRY' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_AUD_PRE_NAMED_ENTRY() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_PAIRED_DEVICES_NAMED_ENTRY' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_PAIRED_DEVICES_NAMED_ENTRY() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_DISPLAY_SETUP_NAMED_ENTRY' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_DISPLAY_SETUP_NAMED_ENTRY() const;
				
				/*! Gets the value of the variable 'SETUP_SCR_LIGHTING_SETUP_NAMED_ENTRY' that is defined in the default interface scope. */
				sc_integer get_sETUP_SCR_LIGHTING_SETUP_NAMED_ENTRY() const;
				
				/*! Gets the value of the variable 'POPUP_ONE_HOUR' that is defined in the default interface scope. */
				sc_integer get_pOPUP_ONE_HOUR() const;
				
				/*! Raises the in event 'evBackPressed' that is defined in the default interface scope. */
				void raise_evBackPressed();
				
				/*! Raises the in event 'evBrowse' that is defined in the default interface scope. */
				void raise_evBrowse();
				
				/*! Raises the in event 'evHomeActivated' that is defined in the default interface scope. */
				void raise_evHomeActivated();
				
				/*! Raises the in event 'evPdcActivated' that is defined in the default interface scope. */
				void raise_evPdcActivated();
				
				/*! Raises the in event 'evPdcDeactivated' that is defined in the default interface scope. */
				void raise_evPdcDeactivated();
				
				/*! Raises the in event 'evMediaActivated' that is defined in the default interface scope. */
				void raise_evMediaActivated();
				
				/*! Raises the in event 'evTunerActivated' that is defined in the default interface scope. */
				void raise_evTunerActivated();
				
				/*! Raises the in event 'evPhoneBrowseActivated' that is defined in the default interface scope. */
				void raise_evPhoneBrowseActivated(sc_integer value);
				
				/*! Raises the in event 'evPhoneCallActivated' that is defined in the default interface scope. */
				void raise_evPhoneCallActivated();
				
				/*! Raises the in event 'evPhoneCallDeactivated' that is defined in the default interface scope. */
				void raise_evPhoneCallDeactivated();
				
				/*! Raises the in event 'evMedOffActivated' that is defined in the default interface scope. */
				void raise_evMedOffActivated();
				
				/*! Raises the in event 'evSetupActivated' that is defined in the default interface scope. */
				void raise_evSetupActivated();
				
				/*! Raises the in event 'evEnggMenuActivated' that is defined in the default interface scope. */
				void raise_evEnggMenuActivated();
				
				/*! Raises the in event 'evAndroidAutoActivated' that is defined in the default interface scope. */
				void raise_evAndroidAutoActivated();
				
				/*! Raises the in event 'evCarPlayProjectionStatusChanged' that is defined in the default interface scope. */
				void raise_evCarPlayProjectionStatusChanged();
				
				/*! Raises the in event 'evSALActivated' that is defined in the default interface scope. */
				void raise_evSALActivated();
				
				/*! Raises the in event 'evSoftwareUpdateActivated' that is defined in the default interface scope. */
				void raise_evSoftwareUpdateActivated();
				
				/*! Raises the in event 'evVRHelpActivated' that is defined in the default interface scope. */
				void raise_evVRHelpActivated();
				
				/*! Raises the in event 'evTest' that is defined in the default interface scope. */
				void raise_evTest();
				
				
			private:
				friend class TML_HMI_SM;
				sc_integer iCurrentHMIContext;
				sc_integer HMI_INVALID_CONTEXT;
				sc_integer HMI_MEDIA_CONTEXT;
				sc_integer HMI_TUNER_CONTEXT;
				sc_integer HMI_PHONE_CONTEXT;
				sc_integer HMI_PHONE_CALL_CONTEXT;
				sc_integer HMI_SETUP_CONTEXT;
				sc_integer HMI_HOME_CONTEXT;
				sc_integer HMI_MEDIA_OFF_CONTEXT;
				sc_integer HMI_ENG_MENU_CONTEXT;
				sc_integer HMI_SOFTWARE_UPDATE_CONTEXT;
				sc_integer HMI_PDC_RVC_CONTEXT;
				sc_integer HMI_ANDROID_AUTO_CONTEXT;
				sc_integer HMI_APPLE_CARPLAY_CONTEXT;
				sc_integer HMI_SAL_CONTEXT;
				sc_integer HMI_EARLY_WAKEUP_CONTEXT;
				sc_integer HMI_STARTUP_ANIM_CONTEXT;
				sc_integer HMI_VR_PICKLIST_CONTEXT;
				sc_integer HMI_VR_HELP_CONTEXT;
				sc_integer HMI_DRIVE_NEXT_CONTEXT;
				sc_integer HMI_PHONE_SETUP_CONTEXT;
				sc_integer VPM_UNKNOWN;
				sc_integer VPM_SWITCH_OFF;
				sc_integer VPM_EARLY_WAKEUP;
				sc_integer VPM_MEDIA_OFF;
				sc_integer VPM_ACTIVE;
				sc_integer VPM_ONE_HOUR;
				sc_integer SETUP_SCR_PARK_ASSIST;
				sc_integer SETUP_SCR_MOOD_LIGHTING;
				sc_integer SETUP_SCR_BALANCE_FADER;
				sc_integer SETUP_SCR_AUDIO_PRESETS;
				sc_integer SETUP_SCR_EDIT_SMS;
				sc_integer SETUP_SCR_AUX_GAIN;
				sc_integer SETUP_SCR_SET_DATE;
				sc_integer SETUP_SCR_SET_TIME;
				sc_integer SETUP_SCR_PAIRED_DEVICES;
				sc_integer SETUP_SCR_PAIR_NEW_DEVICE;
				sc_integer SETUP_SCR_DELETE_DEVICE;
				sc_integer SETUP_SCR_VEHICLE_NAMED_ENTRY;
				sc_integer SETUP_SCR_AUDIO_NAMED_ENTRY;
				sc_integer SETUP_SCR_BT_NAMED_ENTRY;
				sc_integer SETUP_SCR_VOLUME_NAMED_ENTRY;
				sc_integer SETUP_SCR_GENERAL_NAMED_ENTRY;
				sc_integer SETUP_SCR_MOODLIGHT_NAMED_ENTRY;
				sc_integer SETUP_SCR_BMT_NAMED_ENTRY;
				sc_integer SETUP_SCR_BAL_FAD_NAMED_ENTRY;
				sc_integer SETUP_SCR_AUD_PRE_NAMED_ENTRY;
				sc_integer SETUP_SCR_PAIRED_DEVICES_NAMED_ENTRY;
				sc_integer SETUP_SCR_DISPLAY_SETUP_NAMED_ENTRY;
				sc_integer SETUP_SCR_LIGHTING_SETUP_NAMED_ENTRY;
				sc_integer POPUP_ONE_HOUR;
				sc_boolean evBackPressed_raised;
				sc_boolean evBrowse_raised;
				sc_boolean evHomeActivated_raised;
				sc_boolean evPdcActivated_raised;
				sc_boolean evPdcDeactivated_raised;
				sc_boolean evMediaActivated_raised;
				sc_boolean evTunerActivated_raised;
				sc_boolean evPhoneBrowseActivated_raised;
				sc_integer evPhoneBrowseActivated_value;
				sc_boolean evPhoneCallActivated_raised;
				sc_boolean evPhoneCallDeactivated_raised;
				sc_boolean evMedOffActivated_raised;
				sc_boolean evSetupActivated_raised;
				sc_boolean evEnggMenuActivated_raised;
				sc_boolean evAndroidAutoActivated_raised;
				sc_boolean evCarPlayProjectionStatusChanged_raised;
				sc_boolean evSALActivated_raised;
				sc_boolean evSoftwareUpdateActivated_raised;
				sc_boolean evVRHelpActivated_raised;
				sc_boolean evTest_raised;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
		
		/*! Returns an instance of the interface class 'DefaultSCI'. */
		DefaultSCI* getDefaultSCI();
		
		/*! Gets the value of the variable 'iCurrentHMIContext' that is defined in the default interface scope. */
		sc_integer get_iCurrentHMIContext() const;
		
		/*! Sets the value of the variable 'iCurrentHMIContext' that is defined in the default interface scope. */
		void set_iCurrentHMIContext(sc_integer value);
		
		/*! Gets the value of the variable 'HMI_INVALID_CONTEXT' that is defined in the default interface scope. */
		sc_integer get_hMI_INVALID_CONTEXT() const;
		
		/*! Gets the value of the variable 'HMI_MEDIA_CONTEXT' that is defined in the default interface scope. */
		sc_integer get_hMI_MEDIA_CONTEXT() const;
		
		/*! Gets the value of the variable 'HMI_TUNER_CONTEXT' that is defined in the default interface scope. */
		sc_integer get_hMI_TUNER_CONTEXT() const;
		
		/*! Gets the value of the variable 'HMI_PHONE_CONTEXT' that is defined in the default interface scope. */
		sc_integer get_hMI_PHONE_CONTEXT() const;
		
		/*! Gets the value of the variable 'HMI_PHONE_CALL_CONTEXT' that is defined in the default interface scope. */
		sc_integer get_hMI_PHONE_CALL_CONTEXT() const;
		
		/*! Gets the value of the variable 'HMI_SETUP_CONTEXT' that is defined in the default interface scope. */
		sc_integer get_hMI_SETUP_CONTEXT() const;
		
		/*! Gets the value of the variable 'HMI_HOME_CONTEXT' that is defined in the default interface scope. */
		sc_integer get_hMI_HOME_CONTEXT() const;
		
		/*! Gets the value of the variable 'HMI_MEDIA_OFF_CONTEXT' that is defined in the default interface scope. */
		sc_integer get_hMI_MEDIA_OFF_CONTEXT() const;
		
		/*! Gets the value of the variable 'HMI_ENG_MENU_CONTEXT' that is defined in the default interface scope. */
		sc_integer get_hMI_ENG_MENU_CONTEXT() const;
		
		/*! Gets the value of the variable 'HMI_SOFTWARE_UPDATE_CONTEXT' that is defined in the default interface scope. */
		sc_integer get_hMI_SOFTWARE_UPDATE_CONTEXT() const;
		
		/*! Gets the value of the variable 'HMI_PDC_RVC_CONTEXT' that is defined in the default interface scope. */
		sc_integer get_hMI_PDC_RVC_CONTEXT() const;
		
		/*! Gets the value of the variable 'HMI_ANDROID_AUTO_CONTEXT' that is defined in the default interface scope. */
		sc_integer get_hMI_ANDROID_AUTO_CONTEXT() const;
		
		/*! Gets the value of the variable 'HMI_APPLE_CARPLAY_CONTEXT' that is defined in the default interface scope. */
		sc_integer get_hMI_APPLE_CARPLAY_CONTEXT() const;
		
		/*! Gets the value of the variable 'HMI_SAL_CONTEXT' that is defined in the default interface scope. */
		sc_integer get_hMI_SAL_CONTEXT() const;
		
		/*! Gets the value of the variable 'HMI_EARLY_WAKEUP_CONTEXT' that is defined in the default interface scope. */
		sc_integer get_hMI_EARLY_WAKEUP_CONTEXT() const;
		
		/*! Gets the value of the variable 'HMI_STARTUP_ANIM_CONTEXT' that is defined in the default interface scope. */
		sc_integer get_hMI_STARTUP_ANIM_CONTEXT() const;
		
		/*! Gets the value of the variable 'HMI_VR_PICKLIST_CONTEXT' that is defined in the default interface scope. */
		sc_integer get_hMI_VR_PICKLIST_CONTEXT() const;
		
		/*! Gets the value of the variable 'HMI_VR_HELP_CONTEXT' that is defined in the default interface scope. */
		sc_integer get_hMI_VR_HELP_CONTEXT() const;
		
		/*! Gets the value of the variable 'HMI_DRIVE_NEXT_CONTEXT' that is defined in the default interface scope. */
		sc_integer get_hMI_DRIVE_NEXT_CONTEXT() const;
		
		/*! Gets the value of the variable 'HMI_PHONE_SETUP_CONTEXT' that is defined in the default interface scope. */
		sc_integer get_hMI_PHONE_SETUP_CONTEXT() const;
		
		/*! Gets the value of the variable 'VPM_UNKNOWN' that is defined in the default interface scope. */
		sc_integer get_vPM_UNKNOWN() const;
		
		/*! Gets the value of the variable 'VPM_SWITCH_OFF' that is defined in the default interface scope. */
		sc_integer get_vPM_SWITCH_OFF() const;
		
		/*! Gets the value of the variable 'VPM_EARLY_WAKEUP' that is defined in the default interface scope. */
		sc_integer get_vPM_EARLY_WAKEUP() const;
		
		/*! Gets the value of the variable 'VPM_MEDIA_OFF' that is defined in the default interface scope. */
		sc_integer get_vPM_MEDIA_OFF() const;
		
		/*! Gets the value of the variable 'VPM_ACTIVE' that is defined in the default interface scope. */
		sc_integer get_vPM_ACTIVE() const;
		
		/*! Gets the value of the variable 'VPM_ONE_HOUR' that is defined in the default interface scope. */
		sc_integer get_vPM_ONE_HOUR() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_PARK_ASSIST' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_PARK_ASSIST() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_MOOD_LIGHTING' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_MOOD_LIGHTING() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_BALANCE_FADER' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_BALANCE_FADER() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_AUDIO_PRESETS' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_AUDIO_PRESETS() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_EDIT_SMS' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_EDIT_SMS() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_AUX_GAIN' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_AUX_GAIN() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_SET_DATE' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_SET_DATE() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_SET_TIME' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_SET_TIME() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_PAIRED_DEVICES' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_PAIRED_DEVICES() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_PAIR_NEW_DEVICE' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_PAIR_NEW_DEVICE() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_DELETE_DEVICE' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_DELETE_DEVICE() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_VEHICLE_NAMED_ENTRY' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_VEHICLE_NAMED_ENTRY() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_AUDIO_NAMED_ENTRY' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_AUDIO_NAMED_ENTRY() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_BT_NAMED_ENTRY' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_BT_NAMED_ENTRY() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_VOLUME_NAMED_ENTRY' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_VOLUME_NAMED_ENTRY() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_GENERAL_NAMED_ENTRY' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_GENERAL_NAMED_ENTRY() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_MOODLIGHT_NAMED_ENTRY' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_MOODLIGHT_NAMED_ENTRY() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_BMT_NAMED_ENTRY' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_BMT_NAMED_ENTRY() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_BAL_FAD_NAMED_ENTRY' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_BAL_FAD_NAMED_ENTRY() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_AUD_PRE_NAMED_ENTRY' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_AUD_PRE_NAMED_ENTRY() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_PAIRED_DEVICES_NAMED_ENTRY' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_PAIRED_DEVICES_NAMED_ENTRY() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_DISPLAY_SETUP_NAMED_ENTRY' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_DISPLAY_SETUP_NAMED_ENTRY() const;
		
		/*! Gets the value of the variable 'SETUP_SCR_LIGHTING_SETUP_NAMED_ENTRY' that is defined in the default interface scope. */
		sc_integer get_sETUP_SCR_LIGHTING_SETUP_NAMED_ENTRY() const;
		
		/*! Gets the value of the variable 'POPUP_ONE_HOUR' that is defined in the default interface scope. */
		sc_integer get_pOPUP_ONE_HOUR() const;
		
		/*! Raises the in event 'evBackPressed' that is defined in the default interface scope. */
		void raise_evBackPressed();
		
		/*! Raises the in event 'evBrowse' that is defined in the default interface scope. */
		void raise_evBrowse();
		
		/*! Raises the in event 'evHomeActivated' that is defined in the default interface scope. */
		void raise_evHomeActivated();
		
		/*! Raises the in event 'evPdcActivated' that is defined in the default interface scope. */
		void raise_evPdcActivated();
		
		/*! Raises the in event 'evPdcDeactivated' that is defined in the default interface scope. */
		void raise_evPdcDeactivated();
		
		/*! Raises the in event 'evMediaActivated' that is defined in the default interface scope. */
		void raise_evMediaActivated();
		
		/*! Raises the in event 'evTunerActivated' that is defined in the default interface scope. */
		void raise_evTunerActivated();
		
		/*! Raises the in event 'evPhoneBrowseActivated' that is defined in the default interface scope. */
		void raise_evPhoneBrowseActivated(sc_integer value);
		
		/*! Raises the in event 'evPhoneCallActivated' that is defined in the default interface scope. */
		void raise_evPhoneCallActivated();
		
		/*! Raises the in event 'evPhoneCallDeactivated' that is defined in the default interface scope. */
		void raise_evPhoneCallDeactivated();
		
		/*! Raises the in event 'evMedOffActivated' that is defined in the default interface scope. */
		void raise_evMedOffActivated();
		
		/*! Raises the in event 'evSetupActivated' that is defined in the default interface scope. */
		void raise_evSetupActivated();
		
		/*! Raises the in event 'evEnggMenuActivated' that is defined in the default interface scope. */
		void raise_evEnggMenuActivated();
		
		/*! Raises the in event 'evAndroidAutoActivated' that is defined in the default interface scope. */
		void raise_evAndroidAutoActivated();
		
		/*! Raises the in event 'evCarPlayProjectionStatusChanged' that is defined in the default interface scope. */
		void raise_evCarPlayProjectionStatusChanged();
		
		/*! Raises the in event 'evSALActivated' that is defined in the default interface scope. */
		void raise_evSALActivated();
		
		/*! Raises the in event 'evSoftwareUpdateActivated' that is defined in the default interface scope. */
		void raise_evSoftwareUpdateActivated();
		
		/*! Raises the in event 'evVRHelpActivated' that is defined in the default interface scope. */
		void raise_evVRHelpActivated();
		
		/*! Raises the in event 'evTest' that is defined in the default interface scope. */
		void raise_evTest();
		
		//! Inner class for Skeleton interface scope.
		class SCI_Skeleton
		{
			
			public:
				SCI_Skeleton(TML_HMI_SM * parent): 
				parent(parent)
				{}
				
			private:
				friend class TML_HMI_SM;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
				//! Inner class for Skeleton interface scope operation callbacks.
				class SCI_Skeleton_OCB
				{
					public:
						virtual ~SCI_Skeleton_OCB() = 0;
						
						virtual void enterState() = 0;
						
						virtual void exitState() = 0;
						
						virtual void exampleRequest() = 0;
				};
				
				/*! Set the working instance of the operation callback interface 'SCI_Skeleton_OCB'. */
				void setSCI_Skeleton_OCB(SCI_Skeleton_OCB* operationCallback);
		
		/*! Returns an instance of the interface class 'SCI_Skeleton'. */
		SCI_Skeleton* getSCI_Skeleton();
		
		//! Inner class for ui interface scope.
		class SCI_Ui
		{
			
			public:
				SCI_Ui(TML_HMI_SM * parent): 
				evAnimComplete_raised(false),
				parent(parent)
				{}
				/*! Raises the in event 'evAnimComplete' that is defined in the interface scope 'ui'. */
				void raise_evAnimComplete();
				
				
			private:
				friend class TML_HMI_SM;
				sc_boolean evAnimComplete_raised;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
				//! Inner class for ui interface scope operation callbacks.
				class SCI_Ui_OCB
				{
					public:
						virtual ~SCI_Ui_OCB() = 0;
						
						virtual void initHmi() = 0;
						
						virtual void initUI() = 0;
						
						virtual void initMediaOff() = 0;
						
						virtual void initStartup() = 0;
						
						virtual void initHome() = 0;
						
						virtual void initMedia() = 0;
						
						virtual void initTuner() = 0;
						
						virtual void initSetup() = 0;
						
						virtual void initPhone() = 0;
						
						virtual void initDrawers() = 0;
						
						virtual void initEnggMenu() = 0;
						
						virtual void initAndroidAuto() = 0;
						
						virtual void initCarPlay() = 0;
						
						virtual void initSAL() = 0;
						
						virtual void initSoftwareUpdate() = 0;
						
						virtual void exitUI() = 0;
				};
				
				/*! Set the working instance of the operation callback interface 'SCI_Ui_OCB'. */
				void setSCI_Ui_OCB(SCI_Ui_OCB* operationCallback);
		
		/*! Returns an instance of the interface class 'SCI_Ui'. */
		SCI_Ui* getSCI_Ui();
		
		//! Inner class for mediaOff interface scope.
		class SCI_MediaOff
		{
			
			public:
				SCI_MediaOff(TML_HMI_SM * parent): 
				parent(parent)
				{}
				
			private:
				friend class TML_HMI_SM;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
				//! Inner class for mediaOff interface scope operation callbacks.
				class SCI_MediaOff_OCB
				{
					public:
						virtual ~SCI_MediaOff_OCB() = 0;
						
						virtual void enterMediaOff() = 0;
						
						virtual void exitMediaOff() = 0;
				};
				
				/*! Set the working instance of the operation callback interface 'SCI_MediaOff_OCB'. */
				void setSCI_MediaOff_OCB(SCI_MediaOff_OCB* operationCallback);
		
		/*! Returns an instance of the interface class 'SCI_MediaOff'. */
		SCI_MediaOff* getSCI_MediaOff();
		
		//! Inner class for startup interface scope.
		class SCI_Startup
		{
			
			public:
				SCI_Startup(TML_HMI_SM * parent): 
				parent(parent)
				{}
				
			private:
				friend class TML_HMI_SM;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
				//! Inner class for startup interface scope operation callbacks.
				class SCI_Startup_OCB
				{
					public:
						virtual ~SCI_Startup_OCB() = 0;
						
						virtual void enterStartAnim() = 0;
						
						virtual void exitStartupAnim() = 0;
				};
				
				/*! Set the working instance of the operation callback interface 'SCI_Startup_OCB'. */
				void setSCI_Startup_OCB(SCI_Startup_OCB* operationCallback);
		
		/*! Returns an instance of the interface class 'SCI_Startup'. */
		SCI_Startup* getSCI_Startup();
		
		//! Inner class for home interface scope.
		class SCI_Home
		{
			
			public:
				SCI_Home(TML_HMI_SM * parent): 
				evHomeScreenUpdateShortcutsActivated_raised(false),
				parent(parent)
				{}
				/*! Raises the in event 'evHomeScreenUpdateShortcutsActivated' that is defined in the interface scope 'home'. */
				void raise_evHomeScreenUpdateShortcutsActivated();
				
				/*! Gets the value of the variable 'bIsConfigureFavHKSelection' that is defined in the interface scope 'home'. */
				sc_boolean get_bIsConfigureFavHKSelection() const;
				
				/*! Sets the value of the variable 'bIsConfigureFavHKSelection' that is defined in the interface scope 'home'. */
				void set_bIsConfigureFavHKSelection(sc_boolean value);
				
				
			private:
				friend class TML_HMI_SM;
				sc_boolean evHomeScreenUpdateShortcutsActivated_raised;
				sc_boolean bIsConfigureFavHKSelection;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
				//! Inner class for home interface scope operation callbacks.
				class SCI_Home_OCB
				{
					public:
						virtual ~SCI_Home_OCB() = 0;
						
						virtual void enterHome() = 0;
						
						virtual void exitHome() = 0;
						
						virtual void enterHomeScreenMain() = 0;
						
						virtual void exitHomeScreenMain() = 0;
						
						virtual void enterHomeScreenUpdateShortcuts() = 0;
						
						virtual void exitHomeScreenUpdateShortcuts() = 0;
						
						virtual void enterConfigureFavHK() = 0;
						
						virtual void exitConfigureFavHK() = 0;
				};
				
				/*! Set the working instance of the operation callback interface 'SCI_Home_OCB'. */
				void setSCI_Home_OCB(SCI_Home_OCB* operationCallback);
		
		/*! Returns an instance of the interface class 'SCI_Home'. */
		SCI_Home* getSCI_Home();
		
		//! Inner class for phone interface scope.
		class SCI_Phone
		{
			
			public:
				SCI_Phone(TML_HMI_SM * parent): 
				evPhoneCallParticipantScreen_raised(false),
				evHFPDisconnect_raised(false),
				parent(parent)
				{}
				/*! Gets the value of the variable 'bIsPhoneCallStateActivated' that is defined in the interface scope 'phone'. */
				sc_boolean get_bIsPhoneCallStateActivated() const;
				
				/*! Sets the value of the variable 'bIsPhoneCallStateActivated' that is defined in the interface scope 'phone'. */
				void set_bIsPhoneCallStateActivated(sc_boolean value);
				
				/*! Gets the value of the variable 'bIsPhoneConnectedInHFP' that is defined in the interface scope 'phone'. */
				sc_boolean get_bIsPhoneConnectedInHFP() const;
				
				/*! Sets the value of the variable 'bIsPhoneConnectedInHFP' that is defined in the interface scope 'phone'. */
				void set_bIsPhoneConnectedInHFP(sc_boolean value);
				
				/*! Gets the value of the variable 'bIsPhoneConnectedInA2DP' that is defined in the interface scope 'phone'. */
				sc_boolean get_bIsPhoneConnectedInA2DP() const;
				
				/*! Sets the value of the variable 'bIsPhoneConnectedInA2DP' that is defined in the interface scope 'phone'. */
				void set_bIsPhoneConnectedInA2DP(sc_boolean value);
				
				/*! Raises the in event 'evPhoneCallParticipantScreen' that is defined in the interface scope 'phone'. */
				void raise_evPhoneCallParticipantScreen();
				
				/*! Raises the in event 'evHFPDisconnect' that is defined in the interface scope 'phone'. */
				void raise_evHFPDisconnect();
				
				/*! Gets the value of the variable 'BROWSE_CALLLOGS' that is defined in the interface scope 'phone'. */
				sc_integer get_bROWSE_CALLLOGS() const;
				
				/*! Gets the value of the variable 'BROWSE_NUMPAD' that is defined in the interface scope 'phone'. */
				sc_integer get_bROWSE_NUMPAD() const;
				
				/*! Gets the value of the variable 'BROWSE_FAVORITES' that is defined in the interface scope 'phone'. */
				sc_integer get_bROWSE_FAVORITES() const;
				
				/*! Gets the value of the variable 'BROWSE_CONTACTS' that is defined in the interface scope 'phone'. */
				sc_integer get_bROWSE_CONTACTS() const;
				
				/*! Gets the value of the variable 'BROWSE_CONTACTDETAILS' that is defined in the interface scope 'phone'. */
				sc_integer get_bROWSE_CONTACTDETAILS() const;
				
				
			private:
				friend class TML_HMI_SM;
				sc_boolean bIsPhoneCallStateActivated;
				sc_boolean bIsPhoneConnectedInHFP;
				sc_boolean bIsPhoneConnectedInA2DP;
				sc_boolean evPhoneCallParticipantScreen_raised;
				sc_boolean evHFPDisconnect_raised;
				sc_integer BROWSE_CALLLOGS;
				sc_integer BROWSE_NUMPAD;
				sc_integer BROWSE_FAVORITES;
				sc_integer BROWSE_CONTACTS;
				sc_integer BROWSE_CONTACTDETAILS;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
				//! Inner class for phone interface scope operation callbacks.
				class SCI_Phone_OCB
				{
					public:
						virtual ~SCI_Phone_OCB() = 0;
						
						virtual void enterPhone() = 0;
						
						virtual void exitPhone() = 0;
						
						virtual void enterPhoneBrowse() = 0;
						
						virtual void exitPhoneBrowse() = 0;
						
						virtual void enterPhoneCall() = 0;
						
						virtual void exitPhoneCall() = 0;
						
						virtual void enterCallLogs() = 0;
						
						virtual void exitCallLogs() = 0;
						
						virtual void enterContacts() = 0;
						
						virtual void exitContacts() = 0;
						
						virtual void enterFavorites() = 0;
						
						virtual void exitFavorites() = 0;
						
						virtual void enterNumPad() = 0;
						
						virtual void exitNumPad() = 0;
						
						virtual void enterPhoneCallScreen() = 0;
						
						virtual void exitPhoneCallScreen() = 0;
						
						virtual void enterParticipantsScreen() = 0;
						
						virtual void exitParticipantsScreen() = 0;
						
						virtual void enterContactDetails() = 0;
						
						virtual void exitContactDetails() = 0;
				};
				
				/*! Set the working instance of the operation callback interface 'SCI_Phone_OCB'. */
				void setSCI_Phone_OCB(SCI_Phone_OCB* operationCallback);
		
		/*! Returns an instance of the interface class 'SCI_Phone'. */
		SCI_Phone* getSCI_Phone();
		
		//! Inner class for enggMenu interface scope.
		class SCI_EnggMenu
		{
			
			public:
				SCI_EnggMenu(TML_HMI_SM * parent): 
				evTestModeActivated_raised(false),
				evIlluminationActivated_raised(false),
				evButtonPanelActivated_raised(false),
				evDebugLogActivated_raised(false),
				evSystemConfigActivated_raised(false),
				evVINActivated_raised(false),
				ev16RPartActivated_raised(false),
				evDisplayIlluminationActivated_raised(false),
				evButtonPanelIlluminationActivated_raised(false),
				evContainerPartNoActivated_raised(false),
				evSilverBoxPartNoActivated_raised(false),
				evDisplayHWPartNoActivated_raised(false),
				evButtonPanelPartNoActivated_raised(false),
				evSoftwarePartNoActivated_raised(false),
				evParameterPartNoActivated_raised(false),
				evGPSCoordinate_raised(false),
				evPictureViewerActivated_raised(false),
				parent(parent)
				{}
				/*! Raises the in event 'evTestModeActivated' that is defined in the interface scope 'enggMenu'. */
				void raise_evTestModeActivated();
				
				/*! Raises the in event 'evIlluminationActivated' that is defined in the interface scope 'enggMenu'. */
				void raise_evIlluminationActivated();
				
				/*! Raises the in event 'evButtonPanelActivated' that is defined in the interface scope 'enggMenu'. */
				void raise_evButtonPanelActivated();
				
				/*! Raises the in event 'evDebugLogActivated' that is defined in the interface scope 'enggMenu'. */
				void raise_evDebugLogActivated();
				
				/*! Raises the in event 'evSystemConfigActivated' that is defined in the interface scope 'enggMenu'. */
				void raise_evSystemConfigActivated();
				
				/*! Raises the in event 'evVINActivated' that is defined in the interface scope 'enggMenu'. */
				void raise_evVINActivated();
				
				/*! Raises the in event 'ev16RPartActivated' that is defined in the interface scope 'enggMenu'. */
				void raise_ev16RPartActivated();
				
				/*! Raises the in event 'evDisplayIlluminationActivated' that is defined in the interface scope 'enggMenu'. */
				void raise_evDisplayIlluminationActivated();
				
				/*! Raises the in event 'evButtonPanelIlluminationActivated' that is defined in the interface scope 'enggMenu'. */
				void raise_evButtonPanelIlluminationActivated();
				
				/*! Raises the in event 'evContainerPartNoActivated' that is defined in the interface scope 'enggMenu'. */
				void raise_evContainerPartNoActivated();
				
				/*! Raises the in event 'evSilverBoxPartNoActivated' that is defined in the interface scope 'enggMenu'. */
				void raise_evSilverBoxPartNoActivated();
				
				/*! Raises the in event 'evDisplayHWPartNoActivated' that is defined in the interface scope 'enggMenu'. */
				void raise_evDisplayHWPartNoActivated();
				
				/*! Raises the in event 'evButtonPanelPartNoActivated' that is defined in the interface scope 'enggMenu'. */
				void raise_evButtonPanelPartNoActivated();
				
				/*! Raises the in event 'evSoftwarePartNoActivated' that is defined in the interface scope 'enggMenu'. */
				void raise_evSoftwarePartNoActivated();
				
				/*! Raises the in event 'evParameterPartNoActivated' that is defined in the interface scope 'enggMenu'. */
				void raise_evParameterPartNoActivated();
				
				/*! Raises the in event 'evGPSCoordinate' that is defined in the interface scope 'enggMenu'. */
				void raise_evGPSCoordinate();
				
				/*! Raises the in event 'evPictureViewerActivated' that is defined in the interface scope 'enggMenu'. */
				void raise_evPictureViewerActivated();
				
				
			private:
				friend class TML_HMI_SM;
				sc_boolean evTestModeActivated_raised;
				sc_boolean evIlluminationActivated_raised;
				sc_boolean evButtonPanelActivated_raised;
				sc_boolean evDebugLogActivated_raised;
				sc_boolean evSystemConfigActivated_raised;
				sc_boolean evVINActivated_raised;
				sc_boolean ev16RPartActivated_raised;
				sc_boolean evDisplayIlluminationActivated_raised;
				sc_boolean evButtonPanelIlluminationActivated_raised;
				sc_boolean evContainerPartNoActivated_raised;
				sc_boolean evSilverBoxPartNoActivated_raised;
				sc_boolean evDisplayHWPartNoActivated_raised;
				sc_boolean evButtonPanelPartNoActivated_raised;
				sc_boolean evSoftwarePartNoActivated_raised;
				sc_boolean evParameterPartNoActivated_raised;
				sc_boolean evGPSCoordinate_raised;
				sc_boolean evPictureViewerActivated_raised;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
				//! Inner class for enggMenu interface scope operation callbacks.
				class SCI_EnggMenu_OCB
				{
					public:
						virtual ~SCI_EnggMenu_OCB() = 0;
						
						virtual void enterEnggMenu() = 0;
						
						virtual void exitEnggMenu() = 0;
						
						virtual void enterEnggMenuMain() = 0;
						
						virtual void exitEnggMenuMain() = 0;
						
						virtual void enterTestMode() = 0;
						
						virtual void exitTestMode() = 0;
						
						virtual void enterIlluminationMode() = 0;
						
						virtual void exitIlluminationMode() = 0;
						
						virtual void enterDisplayIllumination() = 0;
						
						virtual void exitDisplayIllumination() = 0;
						
						virtual void enterButtonPanelIllumination() = 0;
						
						virtual void exitButtonPanelIllumination() = 0;
						
						virtual void enterButtonPanelMode() = 0;
						
						virtual void exitButtonPanelMode() = 0;
						
						virtual void enterDebugLogMode() = 0;
						
						virtual void exitDebugLogMode() = 0;
						
						virtual void enterSystemConfigMode() = 0;
						
						virtual void exitSystemConfigMode() = 0;
						
						virtual void enterVIN() = 0;
						
						virtual void exitVIN() = 0;
						
						virtual void enterGPSCoordinates() = 0;
						
						virtual void exitGPSCoordinates() = 0;
						
						virtual void enter16RPartNo() = 0;
						
						virtual void exit16RPartNo() = 0;
						
						virtual void enterDisplayHWPartNo() = 0;
						
						virtual void exitDisplayHWPartNo() = 0;
						
						virtual void enterButtonPanelPartNo() = 0;
						
						virtual void exitButtonPanelPartNo() = 0;
						
						virtual void enterSoftwarePartNo() = 0;
						
						virtual void exitSoftwarePartNo() = 0;
						
						virtual void enterParameterPartNo() = 0;
						
						virtual void exitParameterPartNo() = 0;
						
						virtual void enterContainerPartNo() = 0;
						
						virtual void exitContainerPartNo() = 0;
						
						virtual void enterSilverBoxPartNo() = 0;
						
						virtual void exitSilverBoxPartNo() = 0;
						
						virtual void handleButtonPanelHK() = 0;
						
						virtual void enterPictureViewerMode() = 0;
						
						virtual void exitPictureViewerMode() = 0;
				};
				
				/*! Set the working instance of the operation callback interface 'SCI_EnggMenu_OCB'. */
				void setSCI_EnggMenu_OCB(SCI_EnggMenu_OCB* operationCallback);
		
		/*! Returns an instance of the interface class 'SCI_EnggMenu'. */
		SCI_EnggMenu* getSCI_EnggMenu();
		
		//! Inner class for androidAuto interface scope.
		class SCI_AndroidAuto
		{
			
			public:
				SCI_AndroidAuto(TML_HMI_SM * parent): 
				parent(parent)
				{}
				/*! Gets the value of the variable 'bProjStatus' that is defined in the interface scope 'androidAuto'. */
				sc_boolean get_bProjStatus() const;
				
				/*! Sets the value of the variable 'bProjStatus' that is defined in the interface scope 'androidAuto'. */
				void set_bProjStatus(sc_boolean value);
				
				
			private:
				friend class TML_HMI_SM;
				sc_boolean bProjStatus;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
				//! Inner class for androidAuto interface scope operation callbacks.
				class SCI_AndroidAuto_OCB
				{
					public:
						virtual ~SCI_AndroidAuto_OCB() = 0;
						
						virtual void enterAndroidAuto() = 0;
						
						virtual void exitAndroidAuto() = 0;
				};
				
				/*! Set the working instance of the operation callback interface 'SCI_AndroidAuto_OCB'. */
				void setSCI_AndroidAuto_OCB(SCI_AndroidAuto_OCB* operationCallback);
		
		/*! Returns an instance of the interface class 'SCI_AndroidAuto'. */
		SCI_AndroidAuto* getSCI_AndroidAuto();
		
		//! Inner class for carPlay interface scope.
		class SCI_CarPlay
		{
			
			public:
				SCI_CarPlay(TML_HMI_SM * parent): 
				parent(parent)
				{}
				/*! Gets the value of the variable 'bAppleCarPlayProjStatus' that is defined in the interface scope 'carPlay'. */
				sc_boolean get_bAppleCarPlayProjStatus() const;
				
				/*! Sets the value of the variable 'bAppleCarPlayProjStatus' that is defined in the interface scope 'carPlay'. */
				void set_bAppleCarPlayProjStatus(sc_boolean value);
				
				
			private:
				friend class TML_HMI_SM;
				sc_boolean bAppleCarPlayProjStatus;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
				//! Inner class for carPlay interface scope operation callbacks.
				class SCI_CarPlay_OCB
				{
					public:
						virtual ~SCI_CarPlay_OCB() = 0;
						
						virtual void enterCarPlay() = 0;
						
						virtual void exitCarPlay() = 0;
				};
				
				/*! Set the working instance of the operation callback interface 'SCI_CarPlay_OCB'. */
				void setSCI_CarPlay_OCB(SCI_CarPlay_OCB* operationCallback);
		
		/*! Returns an instance of the interface class 'SCI_CarPlay'. */
		SCI_CarPlay* getSCI_CarPlay();
		
		//! Inner class for SAL interface scope.
		class SCI_SAL
		{
			
			public:
				SCI_SAL(TML_HMI_SM * parent): 
				parent(parent)
				{}
				
			private:
				friend class TML_HMI_SM;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
				//! Inner class for SAL interface scope operation callbacks.
				class SCI_SAL_OCB
				{
					public:
						virtual ~SCI_SAL_OCB() = 0;
						
						virtual void enterSAL() = 0;
						
						virtual void exitSAL() = 0;
				};
				
				/*! Set the working instance of the operation callback interface 'SCI_SAL_OCB'. */
				void setSCI_SAL_OCB(SCI_SAL_OCB* operationCallback);
		
		/*! Returns an instance of the interface class 'SCI_SAL'. */
		SCI_SAL* getSCI_SAL();
		
		//! Inner class for softwareUpdate interface scope.
		class SCI_SoftwareUpdate
		{
			
			public:
				SCI_SoftwareUpdate(TML_HMI_SM * parent): 
				evSoftwareSelectActivated_raised(false),
				parent(parent)
				{}
				/*! Raises the in event 'evSoftwareSelectActivated' that is defined in the interface scope 'softwareUpdate'. */
				void raise_evSoftwareSelectActivated();
				
				
			private:
				friend class TML_HMI_SM;
				sc_boolean evSoftwareSelectActivated_raised;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
				//! Inner class for softwareUpdate interface scope operation callbacks.
				class SCI_SoftwareUpdate_OCB
				{
					public:
						virtual ~SCI_SoftwareUpdate_OCB() = 0;
						
						virtual void enterSoftwareUpdateMain() = 0;
						
						virtual void exitSoftwareUpdateMain() = 0;
						
						virtual void enterSoftwareSelectMode() = 0;
						
						virtual void exitSoftwareSelectMode() = 0;
						
						virtual void enterSoftwareUpdate() = 0;
						
						virtual void exitSoftwareUpdate() = 0;
				};
				
				/*! Set the working instance of the operation callback interface 'SCI_SoftwareUpdate_OCB'. */
				void setSCI_SoftwareUpdate_OCB(SCI_SoftwareUpdate_OCB* operationCallback);
		
		/*! Returns an instance of the interface class 'SCI_SoftwareUpdate'. */
		SCI_SoftwareUpdate* getSCI_SoftwareUpdate();
		
		//! Inner class for setup interface scope.
		class SCI_Setup
		{
			
			public:
				SCI_Setup(TML_HMI_SM * parent): 
				evVehicleSetupActivated_raised(false),
				evVehicleSetupActivated_value(),
				evAudioSetupActivated_raised(false),
				evAudioSetupActivated_value(),
				evBluetoothSetupActivated_raised(false),
				evBluetoothSetupActivated_value(),
				evVolumeSetupActivated_raised(false),
				evVolumeSetupActivated_value(),
				evVoiceAlertsActivated_raised(false),
				evVoiceAlertsActivated_value(),
				evGeneralSetupActivated_raised(false),
				evGeneralSetupActivated_value(),
				evSoftwareDetailsActivated_raised(false),
				evSoftwareDetailsActivated_value(),
				evDisplaySetupActivated_raised(false),
				evDisplaySetupActivated_value(),
				evKeypadActivated_raised(false),
				evAboutMenuSetupActivated_raised(false),
				parent(parent)
				{}
				/*! Raises the in event 'evVehicleSetupActivated' that is defined in the interface scope 'setup'. */
				void raise_evVehicleSetupActivated(sc_integer value);
				
				/*! Raises the in event 'evAudioSetupActivated' that is defined in the interface scope 'setup'. */
				void raise_evAudioSetupActivated(sc_integer value);
				
				/*! Raises the in event 'evBluetoothSetupActivated' that is defined in the interface scope 'setup'. */
				void raise_evBluetoothSetupActivated(sc_integer value);
				
				/*! Raises the in event 'evVolumeSetupActivated' that is defined in the interface scope 'setup'. */
				void raise_evVolumeSetupActivated(sc_integer value);
				
				/*! Raises the in event 'evVoiceAlertsActivated' that is defined in the interface scope 'setup'. */
				void raise_evVoiceAlertsActivated(sc_integer value);
				
				/*! Raises the in event 'evGeneralSetupActivated' that is defined in the interface scope 'setup'. */
				void raise_evGeneralSetupActivated(sc_integer value);
				
				/*! Raises the in event 'evSoftwareDetailsActivated' that is defined in the interface scope 'setup'. */
				void raise_evSoftwareDetailsActivated(sc_integer value);
				
				/*! Raises the in event 'evDisplaySetupActivated' that is defined in the interface scope 'setup'. */
				void raise_evDisplaySetupActivated(sc_integer value);
				
				/*! Raises the in event 'evKeypadActivated' that is defined in the interface scope 'setup'. */
				void raise_evKeypadActivated();
				
				/*! Raises the in event 'evAboutMenuSetupActivated' that is defined in the interface scope 'setup'. */
				void raise_evAboutMenuSetupActivated();
				
				
			private:
				friend class TML_HMI_SM;
				sc_boolean evVehicleSetupActivated_raised;
				sc_integer evVehicleSetupActivated_value;
				sc_boolean evAudioSetupActivated_raised;
				sc_integer evAudioSetupActivated_value;
				sc_boolean evBluetoothSetupActivated_raised;
				sc_integer evBluetoothSetupActivated_value;
				sc_boolean evVolumeSetupActivated_raised;
				sc_integer evVolumeSetupActivated_value;
				sc_boolean evVoiceAlertsActivated_raised;
				sc_integer evVoiceAlertsActivated_value;
				sc_boolean evGeneralSetupActivated_raised;
				sc_integer evGeneralSetupActivated_value;
				sc_boolean evSoftwareDetailsActivated_raised;
				sc_integer evSoftwareDetailsActivated_value;
				sc_boolean evDisplaySetupActivated_raised;
				sc_integer evDisplaySetupActivated_value;
				sc_boolean evKeypadActivated_raised;
				sc_boolean evAboutMenuSetupActivated_raised;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
				//! Inner class for setup interface scope operation callbacks.
				class SCI_Setup_OCB
				{
					public:
						virtual ~SCI_Setup_OCB() = 0;
						
						virtual void enterSetup() = 0;
						
						virtual void enterVehicleSetup() = 0;
						
						virtual void enterAudioSetup() = 0;
						
						virtual void enterBluetoothSetup() = 0;
						
						virtual void enterVolumeSetup() = 0;
						
						virtual void enterVoiceAlerts() = 0;
						
						virtual void enterGeneralSetup() = 0;
						
						virtual void enterSoftwareDetails() = 0;
						
						virtual void enterDisplaySetup() = 0;
						
						virtual void enterParkAssist() = 0;
						
						virtual void enterMoodLighting() = 0;
						
						virtual void enterBalanceFader() = 0;
						
						virtual void enterAudioPresets() = 0;
						
						virtual void enterEditSMSLightbox() = 0;
						
						virtual void enterAUXInGain() = 0;
						
						virtual void enterSetDate() = 0;
						
						virtual void enterSetTime() = 0;
						
						virtual void enterPairedDevices() = 0;
						
						virtual void enterPairNewDevice() = 0;
						
						virtual void enterDeleteDevice() = 0;
						
						virtual void enterLighting() = 0;
						
						virtual void enterAboutMenu() = 0;
						
						virtual void exitSetup() = 0;
						
						virtual void exitVehicleSetup() = 0;
						
						virtual void exitAudioSetup() = 0;
						
						virtual void exitBluetoothSetup() = 0;
						
						virtual void exitVolumeSetup() = 0;
						
						virtual void exitVoiceAlerts() = 0;
						
						virtual void exitGeneralSetup() = 0;
						
						virtual void exitSoftwareDetails() = 0;
						
						virtual void exitDisplaySetup() = 0;
						
						virtual void exitParkAssist() = 0;
						
						virtual void exitMoodLighting() = 0;
						
						virtual void exitBalanceFader() = 0;
						
						virtual void exitAudioPresets() = 0;
						
						virtual void exitEditSMSLightbox() = 0;
						
						virtual void exitAUXInGain() = 0;
						
						virtual void exitSetDate() = 0;
						
						virtual void exitSetTime() = 0;
						
						virtual void exitPairedDevices() = 0;
						
						virtual void exitPairNewDevice() = 0;
						
						virtual void exitDeleteDevice() = 0;
						
						virtual void exitLighting() = 0;
						
						virtual void exitAboutMenu() = 0;
						
						virtual void exitSetupState() = 0;
				};
				
				/*! Set the working instance of the operation callback interface 'SCI_Setup_OCB'. */
				void setSCI_Setup_OCB(SCI_Setup_OCB* operationCallback);
		
		/*! Returns an instance of the interface class 'SCI_Setup'. */
		SCI_Setup* getSCI_Setup();
		
		//! Inner class for media interface scope.
		class SCI_Media
		{
			
			public:
				SCI_Media(TML_HMI_SM * parent): 
				evMediaBrowse_raised(false),
				evBrowseItemPressed_raised(false),
				evBrowseItemPressed_value(),
				evPictureViewer_raised(false),
				evVideoFullScreen_raised(false),
				evNowPlayingAvailable_raised(false),
				evContentTypeChanged_raised(false),
				evMediaTypeSelected_raised(false),
				evMediaTypeSelected_value(),
				evVideoNextPrev_raised(false),
				parent(parent)
				{}
				/*! Raises the in event 'evMediaBrowse' that is defined in the interface scope 'media'. */
				void raise_evMediaBrowse();
				
				/*! Raises the in event 'evBrowseItemPressed' that is defined in the interface scope 'media'. */
				void raise_evBrowseItemPressed(sc_integer value);
				
				/*! Raises the in event 'evPictureViewer' that is defined in the interface scope 'media'. */
				void raise_evPictureViewer();
				
				/*! Raises the in event 'evVideoFullScreen' that is defined in the interface scope 'media'. */
				void raise_evVideoFullScreen();
				
				/*! Raises the in event 'evNowPlayingAvailable' that is defined in the interface scope 'media'. */
				void raise_evNowPlayingAvailable();
				
				/*! Raises the in event 'evContentTypeChanged' that is defined in the interface scope 'media'. */
				void raise_evContentTypeChanged();
				
				/*! Raises the in event 'evMediaTypeSelected' that is defined in the interface scope 'media'. */
				void raise_evMediaTypeSelected(sc_integer value);
				
				/*! Raises the in event 'evVideoNextPrev' that is defined in the interface scope 'media'. */
				void raise_evVideoNextPrev();
				
				/*! Gets the value of the variable 'isNowPlayingAvailable' that is defined in the interface scope 'media'. */
				sc_boolean get_isNowPlayingAvailable() const;
				
				/*! Sets the value of the variable 'isNowPlayingAvailable' that is defined in the interface scope 'media'. */
				void set_isNowPlayingAvailable(sc_boolean value);
				
				/*! Gets the value of the variable 'isBrowseCategoryDirectEntry' that is defined in the interface scope 'media'. */
				sc_boolean get_isBrowseCategoryDirectEntry() const;
				
				/*! Sets the value of the variable 'isBrowseCategoryDirectEntry' that is defined in the interface scope 'media'. */
				void set_isBrowseCategoryDirectEntry(sc_boolean value);
				
				/*! Gets the value of the variable 'BROWSE_FOLDERS' that is defined in the interface scope 'media'. */
				sc_integer get_bROWSE_FOLDERS() const;
				
				/*! Gets the value of the variable 'BROWSE_SONGS' that is defined in the interface scope 'media'. */
				sc_integer get_bROWSE_SONGS() const;
				
				/*! Gets the value of the variable 'BROWSE_ALBUMS' that is defined in the interface scope 'media'. */
				sc_integer get_bROWSE_ALBUMS() const;
				
				/*! Gets the value of the variable 'BROWSE_ARTISTS' that is defined in the interface scope 'media'. */
				sc_integer get_bROWSE_ARTISTS() const;
				
				/*! Gets the value of the variable 'BROWSE_GENRE' that is defined in the interface scope 'media'. */
				sc_integer get_bROWSE_GENRE() const;
				
				/*! Gets the value of the variable 'BROWSE_PLAYLISTS' that is defined in the interface scope 'media'. */
				sc_integer get_bROWSE_PLAYLISTS() const;
				
				/*! Gets the value of the variable 'BROWSE_PICTURE' that is defined in the interface scope 'media'. */
				sc_integer get_bROWSE_PICTURE() const;
				
				/*! Gets the value of the variable 'BROWSE_VIDEOS' that is defined in the interface scope 'media'. */
				sc_integer get_bROWSE_VIDEOS() const;
				
				/*! Gets the value of the variable 'BROWSE_ITUNES_RADIO' that is defined in the interface scope 'media'. */
				sc_integer get_bROWSE_ITUNES_RADIO() const;
				
				/*! Gets the value of the variable 'MEDIA_DISPLAYSTATE_NONE' that is defined in the interface scope 'media'. */
				sc_integer get_mEDIA_DISPLAYSTATE_NONE() const;
				
				/*! Gets the value of the variable 'MEDIA_DISPLAYSTATE_MAIN' that is defined in the interface scope 'media'. */
				sc_integer get_mEDIA_DISPLAYSTATE_MAIN() const;
				
				/*! Gets the value of the variable 'MEDIA_DISPLAYSTATE_LOADING' that is defined in the interface scope 'media'. */
				sc_integer get_mEDIA_DISPLAYSTATE_LOADING() const;
				
				/*! Gets the value of the variable 'MEDIA_DISPLAYSTATE_BROWSE' that is defined in the interface scope 'media'. */
				sc_integer get_mEDIA_DISPLAYSTATE_BROWSE() const;
				
				/*! Gets the value of the variable 'MEDIA_DISPLAYSTATE_BROWSE_CATEGORY' that is defined in the interface scope 'media'. */
				sc_integer get_mEDIA_DISPLAYSTATE_BROWSE_CATEGORY() const;
				
				/*! Gets the value of the variable 'MEDIA_DISPLAYSTATE_PICTURES' that is defined in the interface scope 'media'. */
				sc_integer get_mEDIA_DISPLAYSTATE_PICTURES() const;
				
				/*! Gets the value of the variable 'MEDIA_DISPLAYSTATE_AUX' that is defined in the interface scope 'media'. */
				sc_integer get_mEDIA_DISPLAYSTATE_AUX() const;
				
				/*! Gets the value of the variable 'iMediaDisplayState' that is defined in the interface scope 'media'. */
				sc_integer get_iMediaDisplayState() const;
				
				/*! Sets the value of the variable 'iMediaDisplayState' that is defined in the interface scope 'media'. */
				void set_iMediaDisplayState(sc_integer value);
				
				/*! Gets the value of the variable 'MEDIA_OPERATIONSTATE_NONE' that is defined in the interface scope 'media'. */
				sc_integer get_mEDIA_OPERATIONSTATE_NONE() const;
				
				/*! Gets the value of the variable 'MEDIA_OPERATIONSTATE_AUDIO' that is defined in the interface scope 'media'. */
				sc_integer get_mEDIA_OPERATIONSTATE_AUDIO() const;
				
				/*! Gets the value of the variable 'MEDIA_OPERATIONSTATE_VIDEO' that is defined in the interface scope 'media'. */
				sc_integer get_mEDIA_OPERATIONSTATE_VIDEO() const;
				
				/*! Gets the value of the variable 'MEDIA_OPERATIONSTATE_NOSONGS' that is defined in the interface scope 'media'. */
				sc_integer get_mEDIA_OPERATIONSTATE_NOSONGS() const;
				
				/*! Gets the value of the variable 'MEDIA_OPERATIONSTATE_CORRUPTVIDEO' that is defined in the interface scope 'media'. */
				sc_integer get_mEDIA_OPERATIONSTATE_CORRUPTVIDEO() const;
				
				/*! Gets the value of the variable 'iMediaOperationState' that is defined in the interface scope 'media'. */
				sc_integer get_iMediaOperationState() const;
				
				/*! Sets the value of the variable 'iMediaOperationState' that is defined in the interface scope 'media'. */
				void set_iMediaOperationState(sc_integer value);
				
				/*! Gets the value of the variable 'iCurrentMediaType' that is defined in the interface scope 'media'. */
				sc_integer get_iCurrentMediaType() const;
				
				/*! Sets the value of the variable 'iCurrentMediaType' that is defined in the interface scope 'media'. */
				void set_iCurrentMediaType(sc_integer value);
				
				/*! Gets the value of the variable 'MEDIA_TYPE_SONGS' that is defined in the interface scope 'media'. */
				sc_integer get_mEDIA_TYPE_SONGS() const;
				
				/*! Gets the value of the variable 'MEDIA_TYPE_VIDEOS' that is defined in the interface scope 'media'. */
				sc_integer get_mEDIA_TYPE_VIDEOS() const;
				
				/*! Gets the value of the variable 'MEDIA_TYPE_IMAGES' that is defined in the interface scope 'media'. */
				sc_integer get_mEDIA_TYPE_IMAGES() const;
				
				/*! Gets the value of the variable 'iCurrentContentType' that is defined in the interface scope 'media'. */
				sc_integer get_iCurrentContentType() const;
				
				/*! Sets the value of the variable 'iCurrentContentType' that is defined in the interface scope 'media'. */
				void set_iCurrentContentType(sc_integer value);
				
				/*! Gets the value of the variable 'CONTENT_TYPE_E' that is defined in the interface scope 'media'. */
				sc_integer get_cONTENT_TYPE_E() const;
				
				/*! Gets the value of the variable 'CONTENT_TYPE_S' that is defined in the interface scope 'media'. */
				sc_integer get_cONTENT_TYPE_S() const;
				
				/*! Gets the value of the variable 'CONTENT_TYPE_V' that is defined in the interface scope 'media'. */
				sc_integer get_cONTENT_TYPE_V() const;
				
				/*! Gets the value of the variable 'CONTENT_TYPE_I' that is defined in the interface scope 'media'. */
				sc_integer get_cONTENT_TYPE_I() const;
				
				/*! Gets the value of the variable 'CONTENT_TYPE_SV' that is defined in the interface scope 'media'. */
				sc_integer get_cONTENT_TYPE_SV() const;
				
				/*! Gets the value of the variable 'CONTENT_TYPE_SI' that is defined in the interface scope 'media'. */
				sc_integer get_cONTENT_TYPE_SI() const;
				
				/*! Gets the value of the variable 'CONTENT_TYPE_VI' that is defined in the interface scope 'media'. */
				sc_integer get_cONTENT_TYPE_VI() const;
				
				/*! Gets the value of the variable 'CONTENT_TYPE_SVI' that is defined in the interface scope 'media'. */
				sc_integer get_cONTENT_TYPE_SVI() const;
				
				/*! Gets the value of the variable 'iCurrentBrowseLevel' that is defined in the interface scope 'media'. */
				sc_integer get_iCurrentBrowseLevel() const;
				
				/*! Sets the value of the variable 'iCurrentBrowseLevel' that is defined in the interface scope 'media'. */
				void set_iCurrentBrowseLevel(sc_integer value);
				
				/*! Gets the value of the variable 'BROWSE_LEVEL_1' that is defined in the interface scope 'media'. */
				sc_integer get_bROWSE_LEVEL_1() const;
				
				/*! Gets the value of the variable 'BROWSE_LEVEL_2' that is defined in the interface scope 'media'. */
				sc_integer get_bROWSE_LEVEL_2() const;
				
				/*! Gets the value of the variable 'BROWSE_LEVEL_3' that is defined in the interface scope 'media'. */
				sc_integer get_bROWSE_LEVEL_3() const;
				
				/*! Gets the value of the variable 'BROWSE_LEVEL_NESTED' that is defined in the interface scope 'media'. */
				sc_integer get_bROWSE_LEVEL_NESTED() const;
				
				
			private:
				friend class TML_HMI_SM;
				sc_boolean evMediaBrowse_raised;
				sc_boolean evBrowseItemPressed_raised;
				sc_integer evBrowseItemPressed_value;
				sc_boolean evPictureViewer_raised;
				sc_boolean evVideoFullScreen_raised;
				sc_boolean evNowPlayingAvailable_raised;
				sc_boolean evContentTypeChanged_raised;
				sc_boolean evMediaTypeSelected_raised;
				sc_integer evMediaTypeSelected_value;
				sc_boolean evVideoNextPrev_raised;
				sc_boolean isNowPlayingAvailable;
				sc_boolean isBrowseCategoryDirectEntry;
				sc_integer BROWSE_FOLDERS;
				sc_integer BROWSE_SONGS;
				sc_integer BROWSE_ALBUMS;
				sc_integer BROWSE_ARTISTS;
				sc_integer BROWSE_GENRE;
				sc_integer BROWSE_PLAYLISTS;
				sc_integer BROWSE_PICTURE;
				sc_integer BROWSE_VIDEOS;
				sc_integer BROWSE_ITUNES_RADIO;
				sc_integer MEDIA_DISPLAYSTATE_NONE;
				sc_integer MEDIA_DISPLAYSTATE_MAIN;
				sc_integer MEDIA_DISPLAYSTATE_LOADING;
				sc_integer MEDIA_DISPLAYSTATE_BROWSE;
				sc_integer MEDIA_DISPLAYSTATE_BROWSE_CATEGORY;
				sc_integer MEDIA_DISPLAYSTATE_PICTURES;
				sc_integer MEDIA_DISPLAYSTATE_AUX;
				sc_integer iMediaDisplayState;
				sc_integer MEDIA_OPERATIONSTATE_NONE;
				sc_integer MEDIA_OPERATIONSTATE_AUDIO;
				sc_integer MEDIA_OPERATIONSTATE_VIDEO;
				sc_integer MEDIA_OPERATIONSTATE_NOSONGS;
				sc_integer MEDIA_OPERATIONSTATE_CORRUPTVIDEO;
				sc_integer iMediaOperationState;
				sc_integer iCurrentMediaType;
				sc_integer MEDIA_TYPE_SONGS;
				sc_integer MEDIA_TYPE_VIDEOS;
				sc_integer MEDIA_TYPE_IMAGES;
				sc_integer iCurrentContentType;
				sc_integer CONTENT_TYPE_E;
				sc_integer CONTENT_TYPE_S;
				sc_integer CONTENT_TYPE_V;
				sc_integer CONTENT_TYPE_I;
				sc_integer CONTENT_TYPE_SV;
				sc_integer CONTENT_TYPE_SI;
				sc_integer CONTENT_TYPE_VI;
				sc_integer CONTENT_TYPE_SVI;
				sc_integer iCurrentBrowseLevel;
				sc_integer BROWSE_LEVEL_1;
				sc_integer BROWSE_LEVEL_2;
				sc_integer BROWSE_LEVEL_3;
				sc_integer BROWSE_LEVEL_NESTED;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
				//! Inner class for media interface scope operation callbacks.
				class SCI_Media_OCB
				{
					public:
						virtual ~SCI_Media_OCB() = 0;
						
						virtual void enterMedia() = 0;
						
						virtual void exitMedia() = 0;
						
						virtual void enterMediaLoadingScn() = 0;
						
						virtual void exitMediaLoadingScn() = 0;
						
						virtual void enterMediaMainScn() = 0;
						
						virtual void exitMediaMainScn() = 0;
						
						virtual void enterMediaVideoViewerScn() = 0;
						
						virtual void exitMediaVideoViewerScn() = 0;
						
						virtual void enterMediaBrowseMain() = 0;
						
						virtual void exitMediaBrowseMain() = 0;
						
						virtual void enterMediaBrowseScn() = 0;
						
						virtual void exitMediaBrowseScn() = 0;
						
						virtual void enterMediaBrowseCategoryScn() = 0;
						
						virtual void exitMediaBrowseCategoryScn() = 0;
						
						virtual void enterMediaPictureViewerScn() = 0;
						
						virtual void exitMediaPictureViewerScn() = 0;
						
						virtual void enterMediaAuxScn() = 0;
						
						virtual void exitMediaAuxScn() = 0;
						
						virtual void enterAUXInGainScn() = 0;
						
						virtual void exitAUXInGainScn() = 0;
				};
				
				/*! Set the working instance of the operation callback interface 'SCI_Media_OCB'. */
				void setSCI_Media_OCB(SCI_Media_OCB* operationCallback);
		
		/*! Returns an instance of the interface class 'SCI_Media'. */
		SCI_Media* getSCI_Media();
		
		//! Inner class for tuner interface scope.
		class SCI_Tuner
		{
			
			public:
				SCI_Tuner(TML_HMI_SM * parent): 
				evTunerStateUpdate_raised(false),
				evTunerOptionScreen_raised(false),
				parent(parent)
				{}
				/*! Gets the value of the variable 'iTunerState' that is defined in the interface scope 'tuner'. */
				sc_integer get_iTunerState() const;
				
				/*! Sets the value of the variable 'iTunerState' that is defined in the interface scope 'tuner'. */
				void set_iTunerState(sc_integer value);
				
				/*! Gets the value of the variable 'TUNER_STATE_DEFAULT' that is defined in the interface scope 'tuner'. */
				sc_integer get_tUNER_STATE_DEFAULT() const;
				
				/*! Gets the value of the variable 'TUNER_STATE_AUTOSEEK_UP' that is defined in the interface scope 'tuner'. */
				sc_integer get_tUNER_STATE_AUTOSEEK_UP() const;
				
				/*! Gets the value of the variable 'TUNER_STATE_AUTOSEEK_DOWN' that is defined in the interface scope 'tuner'. */
				sc_integer get_tUNER_STATE_AUTOSEEK_DOWN() const;
				
				/*! Gets the value of the variable 'TUNER_STATE_AUTOSTORE' that is defined in the interface scope 'tuner'. */
				sc_integer get_tUNER_STATE_AUTOSTORE() const;
				
				/*! Gets the value of the variable 'TUNER_STATE_SCAN' that is defined in the interface scope 'tuner'. */
				sc_integer get_tUNER_STATE_SCAN() const;
				
				/*! Raises the in event 'evTunerStateUpdate' that is defined in the interface scope 'tuner'. */
				void raise_evTunerStateUpdate();
				
				/*! Raises the in event 'evTunerOptionScreen' that is defined in the interface scope 'tuner'. */
				void raise_evTunerOptionScreen();
				
				
			private:
				friend class TML_HMI_SM;
				sc_integer iTunerState;
				sc_integer TUNER_STATE_DEFAULT;
				sc_integer TUNER_STATE_AUTOSEEK_UP;
				sc_integer TUNER_STATE_AUTOSEEK_DOWN;
				sc_integer TUNER_STATE_AUTOSTORE;
				sc_integer TUNER_STATE_SCAN;
				sc_boolean evTunerStateUpdate_raised;
				sc_boolean evTunerOptionScreen_raised;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
				//! Inner class for tuner interface scope operation callbacks.
				class SCI_Tuner_OCB
				{
					public:
						virtual ~SCI_Tuner_OCB() = 0;
						
						virtual void enterTuner() = 0;
						
						virtual void exitTuner() = 0;
						
						virtual void enterTunerMain() = 0;
						
						virtual void exitTunerMain() = 0;
						
						virtual void enterTunerDefault() = 0;
						
						virtual void exitTunerDefault() = 0;
						
						virtual void enterTunerOption() = 0;
						
						virtual void exitTunerOption() = 0;
						
						virtual void enterTunerScan() = 0;
						
						virtual void exitTunerScan() = 0;
						
						virtual void enterTunerAutoSeekUp() = 0;
						
						virtual void exitTunerAutoSeekUp() = 0;
						
						virtual void enterTunerAutoSeekDown() = 0;
						
						virtual void exitTunerAutoSeekDown() = 0;
						
						virtual void enterTunerAutoStore() = 0;
						
						virtual void exitTunerAutoStore() = 0;
				};
				
				/*! Set the working instance of the operation callback interface 'SCI_Tuner_OCB'. */
				void setSCI_Tuner_OCB(SCI_Tuner_OCB* operationCallback);
		
		/*! Returns an instance of the interface class 'SCI_Tuner'. */
		SCI_Tuner* getSCI_Tuner();
		
		//! Inner class for TunerService interface scope.
		class SCI_TunerService
		{
			
			public:
				SCI_TunerService(TML_HMI_SM * parent): 
				evtStationUpdate_raised(false),
				parent(parent)
				{}
				/*! Gets the value of the variable 'iFrequency' that is defined in the interface scope 'TunerService'. */
				sc_integer get_iFrequency() const;
				
				/*! Sets the value of the variable 'iFrequency' that is defined in the interface scope 'TunerService'. */
				void set_iFrequency(sc_integer value);
				
				/*! Gets the value of the variable 'strBand' that is defined in the interface scope 'TunerService'. */
				sc_integer get_strBand() const;
				
				/*! Sets the value of the variable 'strBand' that is defined in the interface scope 'TunerService'. */
				void set_strBand(sc_integer value);
				
				/*! Raises the in event 'evtStationUpdate' that is defined in the interface scope 'TunerService'. */
				void raise_evtStationUpdate();
				
				
			private:
				friend class TML_HMI_SM;
				sc_integer iFrequency;
				sc_integer strBand;
				sc_boolean evtStationUpdate_raised;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
				//! Inner class for TunerService interface scope operation callbacks.
				class SCI_TunerService_OCB
				{
					public:
						virtual ~SCI_TunerService_OCB() = 0;
						
						virtual void requestSeek(sc_integer iDirection) = 0;
						
						virtual void requestStartScan() = 0;
						
						virtual void requestStopScan() = 0;
						
						virtual void requestAutoStore() = 0;
				};
				
				/*! Set the working instance of the operation callback interface 'SCI_TunerService_OCB'. */
				void setSCI_TunerService_OCB(SCI_TunerService_OCB* operationCallback);
		
		/*! Returns an instance of the interface class 'SCI_TunerService'. */
		SCI_TunerService* getSCI_TunerService();
		
		//! Inner class for parkAssit interface scope.
		class SCI_ParkAssit
		{
			
			public:
				SCI_ParkAssit(TML_HMI_SM * parent): 
				parent(parent)
				{}
				
			private:
				friend class TML_HMI_SM;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
				//! Inner class for parkAssit interface scope operation callbacks.
				class SCI_ParkAssit_OCB
				{
					public:
						virtual ~SCI_ParkAssit_OCB() = 0;
						
						virtual void enterParkAssist() = 0;
						
						virtual void exitParkAssist() = 0;
						
						virtual void enterParkAssistMain() = 0;
						
						virtual void exitParkAssistMain() = 0;
				};
				
				/*! Set the working instance of the operation callback interface 'SCI_ParkAssit_OCB'. */
				void setSCI_ParkAssit_OCB(SCI_ParkAssit_OCB* operationCallback);
		
		/*! Returns an instance of the interface class 'SCI_ParkAssit'. */
		SCI_ParkAssit* getSCI_ParkAssit();
		
		//! Inner class for hardKey interface scope.
		class SCI_HardKey
		{
			
			public:
				SCI_HardKey(TML_HMI_SM * parent): 
				evHardKeyStateUpdate_raised(false),
				parent(parent)
				{}
				/*! Gets the value of the variable 'iKeyCode' that is defined in the interface scope 'hardKey'. */
				sc_integer get_iKeyCode() const;
				
				/*! Sets the value of the variable 'iKeyCode' that is defined in the interface scope 'hardKey'. */
				void set_iKeyCode(sc_integer value);
				
				/*! Gets the value of the variable 'iKeyState' that is defined in the interface scope 'hardKey'. */
				sc_integer get_iKeyState() const;
				
				/*! Sets the value of the variable 'iKeyState' that is defined in the interface scope 'hardKey'. */
				void set_iKeyState(sc_integer value);
				
				/*! Raises the in event 'evHardKeyStateUpdate' that is defined in the interface scope 'hardKey'. */
				void raise_evHardKeyStateUpdate();
				
				
			private:
				friend class TML_HMI_SM;
				sc_integer iKeyCode;
				sc_integer iKeyState;
				sc_boolean evHardKeyStateUpdate_raised;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
				//! Inner class for hardKey interface scope operation callbacks.
				class SCI_HardKey_OCB
				{
					public:
						virtual ~SCI_HardKey_OCB() = 0;
						
						virtual void handleHardkeys(sc_integer iKeyCode, sc_integer iKeyState) = 0;
				};
				
				/*! Set the working instance of the operation callback interface 'SCI_HardKey_OCB'. */
				void setSCI_HardKey_OCB(SCI_HardKey_OCB* operationCallback);
		
		/*! Returns an instance of the interface class 'SCI_HardKey'. */
		SCI_HardKey* getSCI_HardKey();
		
		//! Inner class for drawers interface scope.
		class SCI_Drawers
		{
			
			public:
				SCI_Drawers(TML_HMI_SM * parent): 
				evShowDrawers_raised(false),
				evHideDrawers_raised(false),
				evShowVolOverlay_raised(false),
				evShowHvacOverlay_raised(false),
				evHideVolOverlay_raised(false),
				evHideHvacOverlay_raised(false),
				evResetHvacOverlayHideTimer_raised(false),
				evMinimizeShortcutDrawer_raised(false),
				evResetCloseDrawerTimer_raised(false),
				evMaximizeSourceDrawer_raised(false),
				evMaximizeHVACDrawer_raised(false),
				evMaximizeQadDrawer_raised(false),
				evMinimizeQadDrawer_raised(false),
				evEnableQadDrawer_raised(false),
				evDisableQadDrawer_raised(false),
				evDisableShortcutDrawer_raised(false),
				evEnableShortcutDrawer_raised(false),
				parent(parent)
				{}
				/*! Gets the value of the variable 'ID_HVAC_DRAWER' that is defined in the interface scope 'drawers'. */
				sc_integer get_iD_HVAC_DRAWER() const;
				
				/*! Gets the value of the variable 'ID_SOURCE_DRAWER' that is defined in the interface scope 'drawers'. */
				sc_integer get_iD_SOURCE_DRAWER() const;
				
				/*! Gets the value of the variable 'ID_QAD_DRAWER' that is defined in the interface scope 'drawers'. */
				sc_integer get_iD_QAD_DRAWER() const;
				
				/*! Gets the value of the variable 'ID_SHORTCUT_DRAWER_HOME_BUTTON' that is defined in the interface scope 'drawers'. */
				sc_integer get_iD_SHORTCUT_DRAWER_HOME_BUTTON() const;
				
				/*! Gets the value of the variable 'slideBarTimeout' that is defined in the interface scope 'drawers'. */
				sc_integer get_slideBarTimeout() const;
				
				/*! Sets the value of the variable 'slideBarTimeout' that is defined in the interface scope 'drawers'. */
				void set_slideBarTimeout(sc_integer value);
				
				/*! Raises the in event 'evShowDrawers' that is defined in the interface scope 'drawers'. */
				void raise_evShowDrawers();
				
				/*! Raises the in event 'evHideDrawers' that is defined in the interface scope 'drawers'. */
				void raise_evHideDrawers();
				
				/*! Raises the in event 'evShowVolOverlay' that is defined in the interface scope 'drawers'. */
				void raise_evShowVolOverlay();
				
				/*! Raises the in event 'evShowHvacOverlay' that is defined in the interface scope 'drawers'. */
				void raise_evShowHvacOverlay();
				
				/*! Raises the in event 'evHideVolOverlay' that is defined in the interface scope 'drawers'. */
				void raise_evHideVolOverlay();
				
				/*! Raises the in event 'evHideHvacOverlay' that is defined in the interface scope 'drawers'. */
				void raise_evHideHvacOverlay();
				
				/*! Raises the in event 'evResetHvacOverlayHideTimer' that is defined in the interface scope 'drawers'. */
				void raise_evResetHvacOverlayHideTimer();
				
				/*! Raises the in event 'evMinimizeShortcutDrawer' that is defined in the interface scope 'drawers'. */
				void raise_evMinimizeShortcutDrawer();
				
				/*! Raises the in event 'evResetCloseDrawerTimer' that is defined in the interface scope 'drawers'. */
				void raise_evResetCloseDrawerTimer();
				
				/*! Raises the in event 'evMaximizeSourceDrawer' that is defined in the interface scope 'drawers'. */
				void raise_evMaximizeSourceDrawer();
				
				/*! Raises the in event 'evMaximizeHVACDrawer' that is defined in the interface scope 'drawers'. */
				void raise_evMaximizeHVACDrawer();
				
				/*! Raises the in event 'evMaximizeQadDrawer' that is defined in the interface scope 'drawers'. */
				void raise_evMaximizeQadDrawer();
				
				/*! Raises the in event 'evMinimizeQadDrawer' that is defined in the interface scope 'drawers'. */
				void raise_evMinimizeQadDrawer();
				
				/*! Raises the in event 'evEnableQadDrawer' that is defined in the interface scope 'drawers'. */
				void raise_evEnableQadDrawer();
				
				/*! Raises the in event 'evDisableQadDrawer' that is defined in the interface scope 'drawers'. */
				void raise_evDisableQadDrawer();
				
				/*! Raises the in event 'evDisableShortcutDrawer' that is defined in the interface scope 'drawers'. */
				void raise_evDisableShortcutDrawer();
				
				/*! Raises the in event 'evEnableShortcutDrawer' that is defined in the interface scope 'drawers'. */
				void raise_evEnableShortcutDrawer();
				
				
			private:
				friend class TML_HMI_SM;
				sc_integer ID_HVAC_DRAWER;
				sc_integer ID_SOURCE_DRAWER;
				sc_integer ID_QAD_DRAWER;
				sc_integer ID_SHORTCUT_DRAWER_HOME_BUTTON;
				sc_integer slideBarTimeout;
				sc_boolean evShowDrawers_raised;
				sc_boolean evHideDrawers_raised;
				sc_boolean evShowVolOverlay_raised;
				sc_boolean evShowHvacOverlay_raised;
				sc_boolean evHideVolOverlay_raised;
				sc_boolean evHideHvacOverlay_raised;
				sc_boolean evResetHvacOverlayHideTimer_raised;
				sc_boolean evMinimizeShortcutDrawer_raised;
				sc_boolean evResetCloseDrawerTimer_raised;
				sc_boolean evMaximizeSourceDrawer_raised;
				sc_boolean evMaximizeHVACDrawer_raised;
				sc_boolean evMaximizeQadDrawer_raised;
				sc_boolean evMinimizeQadDrawer_raised;
				sc_boolean evEnableQadDrawer_raised;
				sc_boolean evDisableQadDrawer_raised;
				sc_boolean evDisableShortcutDrawer_raised;
				sc_boolean evEnableShortcutDrawer_raised;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
				//! Inner class for drawers interface scope operation callbacks.
				class SCI_Drawers_OCB
				{
					public:
						virtual ~SCI_Drawers_OCB() = 0;
						
						virtual void enterDrawers() = 0;
						
						virtual void exitDrawers() = 0;
						
						virtual void enterQadDrawerMinimizedState() = 0;
						
						virtual void exitQadDrawerMinimizedState() = 0;
						
						virtual void enterQadDrawerMaximizedState() = 0;
						
						virtual void exitQadDrawerMaximizedState() = 0;
						
						virtual void enterDrawersHiddenState(sc_boolean bPlayAnimation) = 0;
						
						virtual void exitDrawersHiddenState() = 0;
						
						virtual void enterDrawersVisibleState(sc_boolean bPlayAnimation) = 0;
						
						virtual void exitDrawersVisibleState() = 0;
						
						virtual void enterShortcutDrawerMinimizedState() = 0;
						
						virtual void exitShortcutDrawerMinimizedState() = 0;
						
						virtual void enterHvacDrawerMaximizedState() = 0;
						
						virtual void exitHvacDrawerMaximizedState() = 0;
						
						virtual void enterSourceDrawerMaximizedState() = 0;
						
						virtual void exitSourceDrawerMaximizedState() = 0;
						
						virtual void enterStatusBarState() = 0;
						
						virtual void exitStatusBarState() = 0;
						
						virtual void disableShortcutDrawer() = 0;
						
						virtual void enableShortcutDrawer() = 0;
						
						virtual void disableQadDrawer() = 0;
						
						virtual void enableQadDrawer() = 0;
						
						virtual void enableShortcutDrawerButtons(sc_integer iButtonID, sc_boolean bEnable) = 0;
						
						virtual void enterVolOverlayShowState() = 0;
						
						virtual void exitVolOverlayShowState() = 0;
						
						virtual void enterVolOverlayHideState() = 0;
						
						virtual void exitVolOverlayHideState() = 0;
						
						virtual void enterHvacOverlayShowState() = 0;
						
						virtual void exitHvacOverlayShowState() = 0;
						
						virtual void enterHvacOverlayHideState() = 0;
						
						virtual void exitHvacOverlayHideState() = 0;
				};
				
				/*! Set the working instance of the operation callback interface 'SCI_Drawers_OCB'. */
				void setSCI_Drawers_OCB(SCI_Drawers_OCB* operationCallback);
		
		/*! Returns an instance of the interface class 'SCI_Drawers'. */
		SCI_Drawers* getSCI_Drawers();
		
		//! Inner class for Popup interface scope.
		class SCI_Popup
		{
			
			public:
				SCI_Popup(TML_HMI_SM * parent): 
				evShowPopup_raised(false),
				evClosePopup_raised(false),
				evShowNotification_raised(false),
				evCloseNotification_raised(false),
				evForceClosePopup_raised(false),
				evForceCloseNotification_raised(false),
				evResetPopupTimer_raised(false),
				evResetNotificationTimer_raised(false),
				parent(parent)
				{}
				/*! Gets the value of the variable 'isPopupDisplayed' that is defined in the interface scope 'Popup'. */
				sc_boolean get_isPopupDisplayed() const;
				
				/*! Sets the value of the variable 'isPopupDisplayed' that is defined in the interface scope 'Popup'. */
				void set_isPopupDisplayed(sc_boolean value);
				
				/*! Gets the value of the variable 'isNotificationDisplayed' that is defined in the interface scope 'Popup'. */
				sc_boolean get_isNotificationDisplayed() const;
				
				/*! Sets the value of the variable 'isNotificationDisplayed' that is defined in the interface scope 'Popup'. */
				void set_isNotificationDisplayed(sc_boolean value);
				
				/*! Gets the value of the variable 'isMaxPopupTimeoutOver' that is defined in the interface scope 'Popup'. */
				sc_boolean get_isMaxPopupTimeoutOver() const;
				
				/*! Sets the value of the variable 'isMaxPopupTimeoutOver' that is defined in the interface scope 'Popup'. */
				void set_isMaxPopupTimeoutOver(sc_boolean value);
				
				/*! Gets the value of the variable 'isMinPopupTimeoutOver' that is defined in the interface scope 'Popup'. */
				sc_boolean get_isMinPopupTimeoutOver() const;
				
				/*! Sets the value of the variable 'isMinPopupTimeoutOver' that is defined in the interface scope 'Popup'. */
				void set_isMinPopupTimeoutOver(sc_boolean value);
				
				/*! Gets the value of the variable 'maxPopupTimeout' that is defined in the interface scope 'Popup'. */
				sc_integer get_maxPopupTimeout() const;
				
				/*! Sets the value of the variable 'maxPopupTimeout' that is defined in the interface scope 'Popup'. */
				void set_maxPopupTimeout(sc_integer value);
				
				/*! Gets the value of the variable 'minPopupTimeout' that is defined in the interface scope 'Popup'. */
				sc_integer get_minPopupTimeout() const;
				
				/*! Sets the value of the variable 'minPopupTimeout' that is defined in the interface scope 'Popup'. */
				void set_minPopupTimeout(sc_integer value);
				
				/*! Gets the value of the variable 'isMaxNotificationTimeoutOver' that is defined in the interface scope 'Popup'. */
				sc_boolean get_isMaxNotificationTimeoutOver() const;
				
				/*! Sets the value of the variable 'isMaxNotificationTimeoutOver' that is defined in the interface scope 'Popup'. */
				void set_isMaxNotificationTimeoutOver(sc_boolean value);
				
				/*! Gets the value of the variable 'isMinNotificationTimeoutOver' that is defined in the interface scope 'Popup'. */
				sc_boolean get_isMinNotificationTimeoutOver() const;
				
				/*! Sets the value of the variable 'isMinNotificationTimeoutOver' that is defined in the interface scope 'Popup'. */
				void set_isMinNotificationTimeoutOver(sc_boolean value);
				
				/*! Gets the value of the variable 'maxNotificationTimeout' that is defined in the interface scope 'Popup'. */
				sc_integer get_maxNotificationTimeout() const;
				
				/*! Sets the value of the variable 'maxNotificationTimeout' that is defined in the interface scope 'Popup'. */
				void set_maxNotificationTimeout(sc_integer value);
				
				/*! Gets the value of the variable 'minNotificationTimeout' that is defined in the interface scope 'Popup'. */
				sc_integer get_minNotificationTimeout() const;
				
				/*! Sets the value of the variable 'minNotificationTimeout' that is defined in the interface scope 'Popup'. */
				void set_minNotificationTimeout(sc_integer value);
				
				/*! Gets the value of the variable 'isCloseOnMinTimeoutPopup' that is defined in the interface scope 'Popup'. */
				sc_boolean get_isCloseOnMinTimeoutPopup() const;
				
				/*! Sets the value of the variable 'isCloseOnMinTimeoutPopup' that is defined in the interface scope 'Popup'. */
				void set_isCloseOnMinTimeoutPopup(sc_boolean value);
				
				/*! Gets the value of the variable 'isCloseOnMinTimeoutNotification' that is defined in the interface scope 'Popup'. */
				sc_boolean get_isCloseOnMinTimeoutNotification() const;
				
				/*! Sets the value of the variable 'isCloseOnMinTimeoutNotification' that is defined in the interface scope 'Popup'. */
				void set_isCloseOnMinTimeoutNotification(sc_boolean value);
				
				/*! Raises the in event 'evShowPopup' that is defined in the interface scope 'Popup'. */
				void raise_evShowPopup();
				
				/*! Raises the in event 'evClosePopup' that is defined in the interface scope 'Popup'. */
				void raise_evClosePopup();
				
				/*! Raises the in event 'evShowNotification' that is defined in the interface scope 'Popup'. */
				void raise_evShowNotification();
				
				/*! Raises the in event 'evCloseNotification' that is defined in the interface scope 'Popup'. */
				void raise_evCloseNotification();
				
				/*! Raises the in event 'evForceClosePopup' that is defined in the interface scope 'Popup'. */
				void raise_evForceClosePopup();
				
				/*! Raises the in event 'evForceCloseNotification' that is defined in the interface scope 'Popup'. */
				void raise_evForceCloseNotification();
				
				/*! Raises the in event 'evResetPopupTimer' that is defined in the interface scope 'Popup'. */
				void raise_evResetPopupTimer();
				
				/*! Raises the in event 'evResetNotificationTimer' that is defined in the interface scope 'Popup'. */
				void raise_evResetNotificationTimer();
				
				
			private:
				friend class TML_HMI_SM;
				sc_boolean isPopupDisplayed;
				sc_boolean isNotificationDisplayed;
				sc_boolean isMaxPopupTimeoutOver;
				sc_boolean isMinPopupTimeoutOver;
				sc_integer maxPopupTimeout;
				sc_integer minPopupTimeout;
				sc_boolean isMaxNotificationTimeoutOver;
				sc_boolean isMinNotificationTimeoutOver;
				sc_integer maxNotificationTimeout;
				sc_integer minNotificationTimeout;
				sc_boolean isCloseOnMinTimeoutPopup;
				sc_boolean isCloseOnMinTimeoutNotification;
				sc_boolean evShowPopup_raised;
				sc_boolean evClosePopup_raised;
				sc_boolean evShowNotification_raised;
				sc_boolean evCloseNotification_raised;
				sc_boolean evForceClosePopup_raised;
				sc_boolean evForceCloseNotification_raised;
				sc_boolean evResetPopupTimer_raised;
				sc_boolean evResetNotificationTimer_raised;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
				//! Inner class for Popup interface scope operation callbacks.
				class SCI_Popup_OCB
				{
					public:
						virtual ~SCI_Popup_OCB() = 0;
						
						virtual sc_boolean isPopupAllowed() = 0;
						
						virtual sc_boolean isNotificationAllowed() = 0;
						
						virtual void checkPopupContext() = 0;
						
						virtual void enterNoPopup() = 0;
						
						virtual void exitNoPopup() = 0;
						
						virtual void enterPopupActive() = 0;
						
						virtual void exitPopupActive() = 0;
						
						virtual void handlePopupPriority() = 0;
						
						virtual void enterNoNotification() = 0;
						
						virtual void exitNoNotification() = 0;
						
						virtual void enterNotificationActive() = 0;
						
						virtual void exitNotificationActive() = 0;
						
						virtual void handleNotificationPriority() = 0;
				};
				
				/*! Set the working instance of the operation callback interface 'SCI_Popup_OCB'. */
				void setSCI_Popup_OCB(SCI_Popup_OCB* operationCallback);
		
		/*! Returns an instance of the interface class 'SCI_Popup'. */
		SCI_Popup* getSCI_Popup();
		
		//! Inner class for Audio interface scope.
		class SCI_Audio
		{
			
			public:
				SCI_Audio(TML_HMI_SM * parent): 
				evActiveSrcVolumeChanged_raised(false),
				parent(parent)
				{}
				/*! Gets the value of the variable 'SRC_ENT_UNKNOWN' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_ENT_UNKNOWN() const;
				
				/*! Gets the value of the variable 'SRC_TUNER_FM' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_TUNER_FM() const;
				
				/*! Gets the value of the variable 'SRC_TUNER_AM' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_TUNER_AM() const;
				
				/*! Gets the value of the variable 'SRC_TUNER_DAB' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_TUNER_DAB() const;
				
				/*! Gets the value of the variable 'SRC_TUNER_LW' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_TUNER_LW() const;
				
				/*! Gets the value of the variable 'SRC_TUNER_MW' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_TUNER_MW() const;
				
				/*! Gets the value of the variable 'SRC_TUNER_SW' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_TUNER_SW() const;
				
				/*! Gets the value of the variable 'SRC_TUNER_WB' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_TUNER_WB() const;
				
				/*! Gets the value of the variable 'SRC_TUNER_SDARS' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_TUNER_SDARS() const;
				
				/*! Gets the value of the variable 'SRC_CDA' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_CDA() const;
				
				/*! Gets the value of the variable 'SRC_DVDA' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_DVDA() const;
				
				/*! Gets the value of the variable 'SRC_DVDV' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_DVDV() const;
				
				/*! Gets the value of the variable 'SRC_USB1' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_USB1() const;
				
				/*! Gets the value of the variable 'SRC_USB2' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_USB2() const;
				
				/*! Gets the value of the variable 'SRC_SD_CARD' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_SD_CARD() const;
				
				/*! Gets the value of the variable 'SRC_AUDIO_AUX' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_AUDIO_AUX() const;
				
				/*! Gets the value of the variable 'SRC_BT_A2DP1' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_BT_A2DP1() const;
				
				/*! Gets the value of the variable 'SRC_BT_A2DP2' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_BT_A2DP2() const;
				
				/*! Gets the value of the variable 'SRC_CARPLAY_MEDIA' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_CARPLAY_MEDIA() const;
				
				/*! Gets the value of the variable 'SRC_GAL_MEDIA' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_GAL_MEDIA() const;
				
				/*! Gets the value of the variable 'SRC_CARLIFE_MEDIA' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_CARLIFE_MEDIA() const;
				
				/*! Gets the value of the variable 'SRC_MIRRORLINK_MEDIA' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_MIRRORLINK_MEDIA() const;
				
				/*! Gets the value of the variable 'SRC_IPOD' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_IPOD() const;
				
				/*! Gets the value of the variable 'SRC_APPLINK_MEDIA' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_APPLINK_MEDIA() const;
				
				/*! Gets the value of the variable 'SRC_AUDIO_OFF' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_AUDIO_OFF() const;
				
				/*! Gets the value of the variable 'SRC_TUNER_DRM' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_TUNER_DRM() const;
				
				/*! Gets the value of the variable 'SRC_SAL_MEDIA' that is defined in the interface scope 'Audio'. */
				sc_integer get_sRC_SAL_MEDIA() const;
				
				/*! Gets the value of the variable 'CATEGORY_TUNER' that is defined in the interface scope 'Audio'. */
				sc_integer get_cATEGORY_TUNER() const;
				
				/*! Gets the value of the variable 'CATEGORY_MEDIA' that is defined in the interface scope 'Audio'. */
				sc_integer get_cATEGORY_MEDIA() const;
				
				/*! Gets the value of the variable 'CATEGORY_INTERRUPT' that is defined in the interface scope 'Audio'. */
				sc_integer get_cATEGORY_INTERRUPT() const;
				
				/*! Gets the value of the variable 'currentActiveSrc' that is defined in the interface scope 'Audio'. */
				sc_integer get_currentActiveSrc() const;
				
				/*! Sets the value of the variable 'currentActiveSrc' that is defined in the interface scope 'Audio'. */
				void set_currentActiveSrc(sc_integer value);
				
				/*! Gets the value of the variable 'activeSrcCategory' that is defined in the interface scope 'Audio'. */
				sc_integer get_activeSrcCategory() const;
				
				/*! Sets the value of the variable 'activeSrcCategory' that is defined in the interface scope 'Audio'. */
				void set_activeSrcCategory(sc_integer value);
				
				/*! Raises the in event 'evActiveSrcVolumeChanged' that is defined in the interface scope 'Audio'. */
				void raise_evActiveSrcVolumeChanged();
				
				
			private:
				friend class TML_HMI_SM;
				sc_integer SRC_ENT_UNKNOWN;
				sc_integer SRC_TUNER_FM;
				sc_integer SRC_TUNER_AM;
				sc_integer SRC_TUNER_DAB;
				sc_integer SRC_TUNER_LW;
				sc_integer SRC_TUNER_MW;
				sc_integer SRC_TUNER_SW;
				sc_integer SRC_TUNER_WB;
				sc_integer SRC_TUNER_SDARS;
				sc_integer SRC_CDA;
				sc_integer SRC_DVDA;
				sc_integer SRC_DVDV;
				sc_integer SRC_USB1;
				sc_integer SRC_USB2;
				sc_integer SRC_SD_CARD;
				sc_integer SRC_AUDIO_AUX;
				sc_integer SRC_BT_A2DP1;
				sc_integer SRC_BT_A2DP2;
				sc_integer SRC_CARPLAY_MEDIA;
				sc_integer SRC_GAL_MEDIA;
				sc_integer SRC_CARLIFE_MEDIA;
				sc_integer SRC_MIRRORLINK_MEDIA;
				sc_integer SRC_IPOD;
				sc_integer SRC_APPLINK_MEDIA;
				sc_integer SRC_AUDIO_OFF;
				sc_integer SRC_TUNER_DRM;
				sc_integer SRC_SAL_MEDIA;
				sc_integer CATEGORY_TUNER;
				sc_integer CATEGORY_MEDIA;
				sc_integer CATEGORY_INTERRUPT;
				sc_integer currentActiveSrc;
				sc_integer activeSrcCategory;
				sc_boolean evActiveSrcVolumeChanged_raised;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
		
		/*! Returns an instance of the interface class 'SCI_Audio'. */
		SCI_Audio* getSCI_Audio();
		
		//! Inner class for nsm interface scope.
		class SCI_Nsm
		{
			
			public:
				SCI_Nsm(TML_HMI_SM * parent): 
				evPowerModeChanged_raised(false),
				evPowerModeChanged_value(),
				parent(parent)
				{}
				/*! Raises the in event 'evPowerModeChanged' that is defined in the interface scope 'nsm'. */
				void raise_evPowerModeChanged(sc_integer value);
				
				/*! Gets the value of the variable 'currentPowerMode' that is defined in the interface scope 'nsm'. */
				sc_integer get_currentPowerMode() const;
				
				/*! Sets the value of the variable 'currentPowerMode' that is defined in the interface scope 'nsm'. */
				void set_currentPowerMode(sc_integer value);
				
				
			private:
				friend class TML_HMI_SM;
				sc_boolean evPowerModeChanged_raised;
				sc_integer evPowerModeChanged_value;
				sc_integer currentPowerMode;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
		
		/*! Returns an instance of the interface class 'SCI_Nsm'. */
		SCI_Nsm* getSCI_Nsm();
		
		//! Inner class for vr interface scope.
		class SCI_Vr
		{
			
			public:
				SCI_Vr(TML_HMI_SM * parent): 
				evShowPicklist_raised(false),
				evHidePicklist_raised(false),
				evVRHelpDetail_raised(false),
				parent(parent)
				{}
				/*! Raises the in event 'evShowPicklist' that is defined in the interface scope 'vr'. */
				void raise_evShowPicklist();
				
				/*! Raises the in event 'evHidePicklist' that is defined in the interface scope 'vr'. */
				void raise_evHidePicklist();
				
				/*! Raises the in event 'evVRHelpDetail' that is defined in the interface scope 'vr'. */
				void raise_evVRHelpDetail();
				
				
			private:
				friend class TML_HMI_SM;
				sc_boolean evShowPicklist_raised;
				sc_boolean evHidePicklist_raised;
				sc_boolean evVRHelpDetail_raised;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
				//! Inner class for vr interface scope operation callbacks.
				class SCI_Vr_OCB
				{
					public:
						virtual ~SCI_Vr_OCB() = 0;
						
						virtual void enterVRPickList() = 0;
						
						virtual void exitVRPickList() = 0;
						
						virtual void enterVRHelp() = 0;
						
						virtual void exitVRHelp() = 0;
						
						virtual void enterVRHelpMain() = 0;
						
						virtual void exitVRHelpMain() = 0;
						
						virtual void enterVRHelpDetail() = 0;
						
						virtual void exitVRHelpDetail() = 0;
				};
				
				/*! Set the working instance of the operation callback interface 'SCI_Vr_OCB'. */
				void setSCI_Vr_OCB(SCI_Vr_OCB* operationCallback);
		
		/*! Returns an instance of the interface class 'SCI_Vr'. */
		SCI_Vr* getSCI_Vr();
		
		
		/*
		 * Functions inherited from StatemachineInterface
		 */
		virtual void init();
		
		virtual void enter();
		
		virtual void exit();
		
		virtual void runCycle();
		
		/*!
		* Checks if the state machine is active (until 2.4.1 this method was used for states).
		* A state machine is active if it has been entered. It is inactive if it has not been entered at all or if it has been exited.
		*/
		virtual sc_boolean isActive() const;
		
		
		/*!
		* Checks if all active states are final. 
		* If there are no active states then the state machine is considered being inactive. In this case this method returns false.
		*/
		virtual sc_boolean isFinal() const;
		
		/*
		 * Functions inherited from TimedStatemachineInterface
		 */
		virtual void setTimer(TimerInterface* timerInterface);
		
		virtual TimerInterface* getTimer();
		
		virtual void raiseTimeEvent(sc_eventid event);
		
		/*! Checks if the specified state is active (until 2.4.1 the used method for states was calles isActive()). */
		sc_boolean isStateActive(TML_HMI_SMStates state) const;
		
		//! number of time events used by the state machine.
		static const sc_integer timeEventsCount = 9;
		
		//! number of time events that can be active at once.
		static const sc_integer parallelTimeEventsCount = 8;
		
	private:
	
		TML_HMI_SM(const TML_HMI_SM &rhs);
		
		TML_HMI_SM& operator=(const TML_HMI_SM&);
	
		//! Inner class for internal interface scope.
		class InternalSCI
		{
			
			public:
				InternalSCI(TML_HMI_SM * parent): 
				evCloseDrawer_raised(false),
				evHideVolOverlay_raised(false),
				evHideHvacOverlay_raised(false),
				evClosePopupInternal_raised(false),
				evCloseNotificationInternal_raised(false),
				evClosePopupOnMinTimeout_raised(false),
				evCloseNotificationOnMinTimeout_raised(false),
				parent(parent)
				{}
				/*! Gets the value of the variable 'bHideDrawers' that is defined in the internal scope. */
				sc_boolean get_bHideDrawers() const;
				
				/*! Sets the value of the variable 'bHideDrawers' that is defined in the internal scope. */
				void set_bHideDrawers(sc_boolean value);
				
				/*! Gets the value of the variable 'bPlayDrawersAnimation' that is defined in the internal scope. */
				sc_boolean get_bPlayDrawersAnimation() const;
				
				/*! Sets the value of the variable 'bPlayDrawersAnimation' that is defined in the internal scope. */
				void set_bPlayDrawersAnimation(sc_boolean value);
				
				/*! Raises the in event 'evCloseDrawer' that is defined in the internal scope. */
				void raise_evCloseDrawer();
				
				/*! Checks if the out event 'evCloseDrawer' that is defined in the internal scope has been raised. */
				sc_boolean isRaised_evCloseDrawer() const;
				
				/*! Raises the in event 'evHideVolOverlay' that is defined in the internal scope. */
				void raise_evHideVolOverlay();
				
				/*! Checks if the out event 'evHideVolOverlay' that is defined in the internal scope has been raised. */
				sc_boolean isRaised_evHideVolOverlay() const;
				
				/*! Raises the in event 'evHideHvacOverlay' that is defined in the internal scope. */
				void raise_evHideHvacOverlay();
				
				/*! Checks if the out event 'evHideHvacOverlay' that is defined in the internal scope has been raised. */
				sc_boolean isRaised_evHideHvacOverlay() const;
				
				/*! Gets the value of the variable 'isPopupAllowed' that is defined in the internal scope. */
				sc_boolean get_isPopupAllowed() const;
				
				/*! Sets the value of the variable 'isPopupAllowed' that is defined in the internal scope. */
				void set_isPopupAllowed(sc_boolean value);
				
				/*! Raises the in event 'evClosePopupInternal' that is defined in the internal scope. */
				void raise_evClosePopupInternal();
				
				/*! Checks if the out event 'evClosePopupInternal' that is defined in the internal scope has been raised. */
				sc_boolean isRaised_evClosePopupInternal() const;
				
				/*! Raises the in event 'evCloseNotificationInternal' that is defined in the internal scope. */
				void raise_evCloseNotificationInternal();
				
				/*! Checks if the out event 'evCloseNotificationInternal' that is defined in the internal scope has been raised. */
				sc_boolean isRaised_evCloseNotificationInternal() const;
				
				/*! Raises the in event 'evClosePopupOnMinTimeout' that is defined in the internal scope. */
				void raise_evClosePopupOnMinTimeout();
				
				/*! Checks if the out event 'evClosePopupOnMinTimeout' that is defined in the internal scope has been raised. */
				sc_boolean isRaised_evClosePopupOnMinTimeout() const;
				
				/*! Raises the in event 'evCloseNotificationOnMinTimeout' that is defined in the internal scope. */
				void raise_evCloseNotificationOnMinTimeout();
				
				/*! Checks if the out event 'evCloseNotificationOnMinTimeout' that is defined in the internal scope has been raised. */
				sc_boolean isRaised_evCloseNotificationOnMinTimeout() const;
				
				
			private:
				friend class TML_HMI_SM;
				sc_boolean bHideDrawers;
				sc_boolean bPlayDrawersAnimation;
				/*! Raises the in event 'evCloseDrawer' that is defined in the internal scope. */
				void internal_raise_evCloseDrawer();
				sc_boolean evCloseDrawer_raised;
				/*! Raises the in event 'evHideVolOverlay' that is defined in the internal scope. */
				void internal_raise_evHideVolOverlay();
				sc_boolean evHideVolOverlay_raised;
				/*! Raises the in event 'evHideHvacOverlay' that is defined in the internal scope. */
				void internal_raise_evHideHvacOverlay();
				sc_boolean evHideHvacOverlay_raised;
				sc_boolean isPopupAllowed;
				/*! Raises the in event 'evClosePopupInternal' that is defined in the internal scope. */
				void internal_raise_evClosePopupInternal();
				sc_boolean evClosePopupInternal_raised;
				/*! Raises the in event 'evCloseNotificationInternal' that is defined in the internal scope. */
				void internal_raise_evCloseNotificationInternal();
				sc_boolean evCloseNotificationInternal_raised;
				/*! Raises the in event 'evClosePopupOnMinTimeout' that is defined in the internal scope. */
				void internal_raise_evClosePopupOnMinTimeout();
				sc_boolean evClosePopupOnMinTimeout_raised;
				/*! Raises the in event 'evCloseNotificationOnMinTimeout' that is defined in the internal scope. */
				void internal_raise_evCloseNotificationOnMinTimeout();
				sc_boolean evCloseNotificationOnMinTimeout_raised;
				TML_HMI_SM * parent;
				void dispatch_event(tml_hmi_sm_events::SctEvent * event);
				
		};
	
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc_integer maxOrthogonalStates = 8;
			//! dimension of the state configuration vector for history states
		static const sc_integer maxHistoryStates = 1;
		
		TimerInterface* timer;
		sc_boolean timeEvents[timeEventsCount];
		
		TML_HMI_SMStates stateConfVector[maxOrthogonalStates];
		
		TML_HMI_SMStates historyVector[maxHistoryStates];
		sc_ushort stateConfVectorPosition;
		
		InternalSCI ifaceInternalSCI;
		DefaultSCI iface;
		SCI_Skeleton ifaceSkeleton;
		SCI_Skeleton_OCB* ifaceSkeleton_OCB;
		SCI_Ui ifaceUi;
		SCI_Ui_OCB* ifaceUi_OCB;
		SCI_MediaOff ifaceMediaOff;
		SCI_MediaOff_OCB* ifaceMediaOff_OCB;
		SCI_Startup ifaceStartup;
		SCI_Startup_OCB* ifaceStartup_OCB;
		SCI_Home ifaceHome;
		SCI_Home_OCB* ifaceHome_OCB;
		SCI_Phone ifacePhone;
		SCI_Phone_OCB* ifacePhone_OCB;
		SCI_EnggMenu ifaceEnggMenu;
		SCI_EnggMenu_OCB* ifaceEnggMenu_OCB;
		SCI_AndroidAuto ifaceAndroidAuto;
		SCI_AndroidAuto_OCB* ifaceAndroidAuto_OCB;
		SCI_CarPlay ifaceCarPlay;
		SCI_CarPlay_OCB* ifaceCarPlay_OCB;
		SCI_SAL ifaceSAL;
		SCI_SAL_OCB* ifaceSAL_OCB;
		SCI_SoftwareUpdate ifaceSoftwareUpdate;
		SCI_SoftwareUpdate_OCB* ifaceSoftwareUpdate_OCB;
		SCI_Setup ifaceSetup;
		SCI_Setup_OCB* ifaceSetup_OCB;
		SCI_Media ifaceMedia;
		SCI_Media_OCB* ifaceMedia_OCB;
		SCI_Tuner ifaceTuner;
		SCI_Tuner_OCB* ifaceTuner_OCB;
		SCI_TunerService ifaceTunerService;
		SCI_TunerService_OCB* ifaceTunerService_OCB;
		SCI_ParkAssit ifaceParkAssit;
		SCI_ParkAssit_OCB* ifaceParkAssit_OCB;
		SCI_HardKey ifaceHardKey;
		SCI_HardKey_OCB* ifaceHardKey_OCB;
		SCI_Drawers ifaceDrawers;
		SCI_Drawers_OCB* ifaceDrawers_OCB;
		SCI_Popup ifacePopup;
		SCI_Popup_OCB* ifacePopup_OCB;
		SCI_Audio ifaceAudio;
		SCI_Nsm ifaceNsm;
		SCI_Vr ifaceVr;
		SCI_Vr_OCB* ifaceVr_OCB;
		
		// prototypes of all internal functions
		
		sc_boolean check_startup_region_EarlyWakeup_tr0_tr0();
		sc_boolean check_startup_region_EarlyWakeup_tr1_tr1();
		sc_boolean check_startup_region_Ui_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_PDC_lr1_lr1();
		sc_boolean check_startup_region_Ui_home_PDC_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_Main_tr4_tr4();
		sc_boolean check_startup_region_Ui_home_Main_tr5_tr5();
		sc_boolean check_startup_region_Ui_home_Main_tr6_tr6();
		sc_boolean check_startup_region_Ui_home_Main_tr7_tr7();
		sc_boolean check_startup_region_Ui_home_Main_tr8_tr8();
		sc_boolean check_startup_region_Ui_home_Main_tr9_tr9();
		sc_boolean check_startup_region_Ui_home_Main_tr10_tr10();
		sc_boolean check_startup_region_Ui_home_Main_tr11_tr11();
		sc_boolean check_startup_region_Ui_home_Main_tr12_tr12();
		sc_boolean check_startup_region_Ui_home_Main_tr13_tr13();
		sc_boolean check_startup_region_Ui_home_Main_tr14_tr14();
		sc_boolean check_startup_region_Ui_home_Main_tr15_tr15();
		sc_boolean check_startup_region_Ui_home_Main_tr16_tr16();
		sc_boolean check_startup_region_Ui_home_Main_main_Home_lr1_lr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Home_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Home_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Home_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_Home_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_Main_main_Home_tr4_tr4();
		sc_boolean check_startup_region_Ui_home_Main_main_Home_tr5_tr5();
		sc_boolean check_startup_region_Ui_home_Main_main_Home_tr6_tr6();
		sc_boolean check_startup_region_Ui_home_Main_main_Home_home_HomeScreenMain_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Home_home_HomeScreenMain_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Home_home_HomeScreenUpdateShortcuts_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Home_home_HomeScreenUpdateShortcuts_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Home_home_ConfigureFavHK_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Home_home_ConfigureFavHK_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_PowerMode_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_PowerMode_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_PowerMode_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_Main_main_PowerMode_tr4_tr4();
		sc_boolean check_startup_region_Ui_home_Main_main_PowerMode_tr5_tr5();
		sc_boolean check_startup_region_Ui_home_Main_main_PowerMode_Powermodes_MediaOff_lr1_lr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_lr1_lr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_tr4_tr4();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_tr5_tr5();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_tr6_tr6();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_tr7_tr7();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_tr8_tr8();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_tr9_tr9();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain_tr4_tr4();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain_tr5_tr5();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain_tr6_tr6();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain_tr7_tr7();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain_tr8_tr8();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_VehicleSetup_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_VehicleSetup_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_VehicleSetup_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_ParkAssist_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_MoodLighting_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_BluetoothSetup_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_BluetoothSetup_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_BluetoothSetup_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_BluetoothSetup_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_EditSMSLightbox_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_VolumeSetup_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_VolumeSetup_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_AUXInGain_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_GeneralSetup_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_GeneralSetup_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_GeneralSetup_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_SetDate_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_SetTime_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_SoftwareDetails_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_DisplaySetup_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_VoiceAlerts_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_PairedDevices_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_PairedDevices_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_PairNewDevice_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_DeleteDevice_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_LightingSetup_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_LightingSetup_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_About_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup_audioSetup_region_AudioPresets_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup_audioSetup_region_BalanceFader_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_tr4_tr4();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_tr5_tr5();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_tr6_tr6();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_tr7_tr7();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_EnggMenuMain_lr1_lr1();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_EnggMenuMain_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_EnggMenuMain_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_EnggMenuMain_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_EnggMenuMain_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_EnggMenuMain_tr4_tr4();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_EnggMenuMain_tr5_tr5();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_TestMode_lr1_lr1();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_TestMode_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_lr0_lr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_IlluminationScreenMain_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_IlluminationScreenMain_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_DisplayIllumination_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_ButtonPanelIllumination_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_ButtonPanel_lr1_lr1();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_ButtonPanel_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_DebugLog_lr1_lr1();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_DebugLog_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_lr0_lr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_SystemConfiguration_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_SystemConfiguration_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_SystemConfiguration_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_VIN_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo__16RPartNoScreenMain_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo__16RPartNoScreenMain_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo__16RPartNoScreenMain_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo__16RPartNoScreenMain_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo__16RPartNoScreenMain_tr4_tr4();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo__16RPartNoScreenMain_tr5_tr5();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ParameterPartNo_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_SoftwarePartNo_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ButtonPanelPartNo_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ContainerPartNo_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_SilverBoxPartNo_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_DisplayHWPartNo_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_GPSCoordinate_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_PictureViewer_lr1_lr1();
		sc_boolean check_startup_region_Ui_home_Main_main_EnggMenu_engg_region_PictureViewer_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_AndroidAuto_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_AndroidAuto_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_AndroidAuto_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_AndroidAuto_tr4_tr4();
		sc_boolean check_startup_region_Ui_home_Main_main_AndroidAuto_aa_region_AAMain_lr1_lr1();
		sc_boolean check_startup_region_Ui_home_Main_main_CarPlay_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_CarPlay_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_CarPlay_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_CarPlay_tr4_tr4();
		sc_boolean check_startup_region_Ui_home_Main_main_CarPlay_tr5_tr5();
		sc_boolean check_startup_region_Ui_home_Main_main_CarPlay_carplay_region_CarPlayMain_lr1_lr1();
		sc_boolean check_startup_region_Ui_home_Main_main_SAL_lr1_lr1();
		sc_boolean check_startup_region_Ui_home_Main_main_SAL_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_SAL_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_SoftwareUpdate_lr1_lr1();
		sc_boolean check_startup_region_Ui_home_Main_main_SoftwareUpdate_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_SoftwareUpdate_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_SoftwareUpdate_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_SoftwareUpdate_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_Main_main_SoftwareUpdate_tr4_tr4();
		sc_boolean check_startup_region_Ui_home_Main_main_SoftwareUpdate_tr5_tr5();
		sc_boolean check_startup_region_Ui_home_Main_main_SoftwareUpdate_tr6_tr6();
		sc_boolean check_startup_region_Ui_home_Main_main_SoftwareUpdate_tr7_tr7();
		sc_boolean check_startup_region_Ui_home_Main_main_SoftwareUpdate_tr8_tr8();
		sc_boolean check_startup_region_Ui_home_Main_main_SoftwareUpdate_swupdate_region_SoftwareUpdateMain_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_SoftwareUpdate_swupdate_region_SoftwareSelectScreen_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_lr1_lr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_tr4_tr4();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_tr5_tr5();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_tr6_tr6();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_tr7_tr7();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_tr8_tr8();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Favorites_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Favorites_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Favorites_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Favorites_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Contacts_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Contacts_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Contacts_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Contacts_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_NumPad_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_NumPad_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_NumPad_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_NumPad_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_CallLogs_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_CallLogs_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_CallLogs_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_CallLogs_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_ContactDetails_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_ContactDetails_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_ContactDetails_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_ContactDetails_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_ContactDetails_tr4_tr4();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_tr4_tr4();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_tr5_tr5();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_tr7_tr7();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_lr1_lr1();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaLoading__tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaLoading__tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaMain_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaMain_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaPicture_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaPicture_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaPicture_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaVideo_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaVideo_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaAux_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_AUXInGain_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowseCategory_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowseCategory_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowseCategory_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowseCategory_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowse_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowse_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowse_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_lr1_lr1();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerDefault_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerDefault_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerDefault_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerDefault_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutoseekUp_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutostore_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerScan_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutoseekDown_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerOption_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerOption_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_VRHelp_lr1_lr1();
		sc_boolean check_startup_region_Ui_home_Main_main_VRHelp_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_VRHelp_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_VRHelp_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_VRHelp_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_Main_main_VRHelp_tr4_tr4();
		sc_boolean check_startup_region_Ui_home_Main_main_VRHelp_tr5_tr5();
		sc_boolean check_startup_region_Ui_home_Main_main_VRHelp_tr6_tr6();
		sc_boolean check_startup_region_Ui_home_Main_main_VRHelp_tr7_tr7();
		sc_boolean check_startup_region_Ui_home_Main_main_VRHelp_tr8_tr8();
		sc_boolean check_startup_region_Ui_home_Main_main_VRHelp_tr9_tr9();
		sc_boolean check_startup_region_Ui_home_Main_main_VRHelp_vr_region_VRHelpMain_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_VRHelp_vr_region_VRHelpDetail_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_PhoneCall_lr1_lr1();
		sc_boolean check_startup_region_Ui_home_PhoneCall_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_PhoneCall_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_PhoneCall_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallScreen_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallScreen_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_ParticipantScreen_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Favorites_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Favorites_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Favorites_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Favorites_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Contacts_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Contacts_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Contacts_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Contacts_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_NumPad_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_NumPad_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_NumPad_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_NumPad_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_CallLogs_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_CallLogs_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_CallLogs_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_CallLogs_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_ContactDetails_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_ContactDetails_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_ContactDetails_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_ContactDetails_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_ContactDetails_tr4_tr4();
		sc_boolean check_startup_region_Ui_home_VR_lr1_lr1();
		sc_boolean check_startup_region_Ui_home_VR_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_VR_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_VR_tr2_tr2();
		sc_boolean check_startup_region_Ui_popup_PopupManager_Zone2_NoNotification_tr0_tr0();
		sc_boolean check_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_lr1_lr1();
		sc_boolean check_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_tr0_tr0();
		sc_boolean check_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_tr1_tr1();
		sc_boolean check_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_tr2_tr2();
		sc_boolean check_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_notification_timer_region_NotificationTimerState_lr0_lr0();
		sc_boolean check_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_notification_timer_region_NotificationTimerState_lr1_lr1();
		sc_boolean check_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_notification_timer_region_NotificationTimerState_tr0_tr0();
		sc_boolean check_startup_region_Ui_popup_PopupManager_Zone4_NoPopup_tr0_tr0();
		sc_boolean check_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_lr1_lr1();
		sc_boolean check_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_tr0_tr0();
		sc_boolean check_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_tr1_tr1();
		sc_boolean check_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_tr2_tr2();
		sc_boolean check_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_popup_timer_region_PopupTimerState_lr0_lr0();
		sc_boolean check_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_popup_timer_region_PopupTimerState_lr1_lr1();
		sc_boolean check_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_popup_timer_region_PopupTimerState_tr0_tr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_tr0_tr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_ShortcutDrawerMinimizedState_lr1_lr1();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_ShortcutDrawerMinimizedState_lr2_lr2();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_ShortcutDrawerMinimizedState_tr0_tr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_ShortcutDrawerMinimizedState_tr1_tr1();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_SourceDrawerMaximizedState_tr0_tr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_SourceDrawerMaximizedState_source_drawer_maximized_region_SourceDrawerTimerState_lr0_lr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_SourceDrawerMaximizedState_source_drawer_maximized_region_SourceDrawerTimerState_tr0_tr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState_tr0_tr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState_hvac_drawer_maximized_region_HVACDrawerTimerState_lr0_lr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState_hvac_drawer_maximized_region_HVACDrawerTimerState_tr0_tr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMinimizedState_lr1_lr1();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMinimizedState_lr2_lr2();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMinimizedState_tr0_tr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMaximizedState_tr0_tr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMaximizedState_qad_drawer_maximized_region_QADTimerState_lr0_lr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMaximizedState_qad_drawer_maximized_region_QADTimerState_tr0_tr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersHiddenState_tr0_tr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_HideVolumeOverlay_tr0_tr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_ShowVolumeOverlay_tr0_tr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_ShowVolumeOverlay_volume_overlay_show_region_VolOverlayTimerState_lr0_lr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_ShowVolumeOverlay_volume_overlay_show_region_VolOverlayTimerState_tr0_tr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_HideHvacOverlay_tr0_tr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_ShowHvacOverlay_tr0_tr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_ShowHvacOverlay_hvac_show_overlay_regioin_HvacOverlayTimerState_lr0_lr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_ShowHvacOverlay_hvac_show_overlay_regioin_HvacOverlayTimerState_tr0_tr0();
		sc_boolean check_startup_region_StartupAnimation_tr0_tr0();
		sc_boolean check_startup_region_StartupAnimation_tr1_tr1();
		sc_boolean check_startup_region_StartupAnimation_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_Home_home__choice_0_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Home_home__choice_0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_PowerMode_Powermodes__choice_0_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_PowerMode_Powermodes__choice_0_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_AndroidAuto_aa_region__choice_0_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_AndroidAuto_aa_region__choice_0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_CarPlay_carplay_region__choice_0_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_CarPlay_carplay_region__choice_0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region__choice_0_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region__choice_0_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region__choice_0_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region__choice_0_tr4_tr4();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region__choice_0_tr3();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region__choice_1_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region__choice_1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main__choice_0_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main__choice_0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region__choice_0_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region__choice_0_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region__choice_0_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region__choice_0_tr4_tr4();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region__choice_0_tr5_tr5();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region__choice_0_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain__choice_0_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain__choice_0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio__choice_0_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio__choice_0_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio__choice_0_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main__choice_0_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main__choice_0_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main__choice_0_tr3_tr3();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main__choice_0_tr4_tr4();
		sc_boolean check_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main__choice_0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main__choice_1_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main__choice_1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main__choice_2_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main__choice_2_tr0();
		sc_boolean check_startup_region_Ui_home_Main_main__choice_3_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_Main_main__choice_3_tr0();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region__choice_0_tr0_tr0();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region__choice_0_tr1_tr1();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region__choice_0_tr2_tr2();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region__choice_0_tr4_tr4();
		sc_boolean check_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region__choice_0_tr3();
		sc_boolean check_startup_region_Ui_home__choice_0_tr1_tr1();
		sc_boolean check_startup_region_Ui_home__choice_0_tr2_tr2();
		sc_boolean check_startup_region_Ui_home__choice_0_tr3_tr3();
		sc_boolean check_startup_region_Ui_home__choice_0_tr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_drawers_main_region__choice_0_tr0_tr0();
		sc_boolean check_startup_region_Ui_drawer_DrawerManager_drawers_main_region__choice_0_tr1();
		sc_boolean check_startup_region__choice_0_tr0_tr0();
		sc_boolean check_startup_region__choice_0_tr2_tr2();
		sc_boolean check_startup_region__choice_0_tr1();
		void effect_startup_region_EarlyWakeup_tr0();
		void effect_startup_region_EarlyWakeup_tr1();
		void effect_startup_region_Ui_tr0();
		void effect_startup_region_Ui_home_PDC_lr1_lr1();
		void effect_startup_region_Ui_home_PDC_tr0();
		void effect_startup_region_Ui_home_Main_tr0();
		void effect_startup_region_Ui_home_Main_tr1();
		void effect_startup_region_Ui_home_Main_tr2();
		void effect_startup_region_Ui_home_Main_tr3();
		void effect_startup_region_Ui_home_Main_tr4();
		void effect_startup_region_Ui_home_Main_tr5();
		void effect_startup_region_Ui_home_Main_tr6();
		void effect_startup_region_Ui_home_Main_tr7();
		void effect_startup_region_Ui_home_Main_tr8();
		void effect_startup_region_Ui_home_Main_tr9();
		void effect_startup_region_Ui_home_Main_tr10();
		void effect_startup_region_Ui_home_Main_tr11();
		void effect_startup_region_Ui_home_Main_tr12();
		void effect_startup_region_Ui_home_Main_tr13();
		void effect_startup_region_Ui_home_Main_tr14();
		void effect_startup_region_Ui_home_Main_tr15();
		void effect_startup_region_Ui_home_Main_tr16();
		void effect_startup_region_Ui_home_Main_main_Home_lr1_lr1();
		void effect_startup_region_Ui_home_Main_main_Home_tr0();
		void effect_startup_region_Ui_home_Main_main_Home_tr1();
		void effect_startup_region_Ui_home_Main_main_Home_tr2();
		void effect_startup_region_Ui_home_Main_main_Home_tr3();
		void effect_startup_region_Ui_home_Main_main_Home_tr4();
		void effect_startup_region_Ui_home_Main_main_Home_tr5();
		void effect_startup_region_Ui_home_Main_main_Home_tr6();
		void effect_startup_region_Ui_home_Main_main_Home_home_HomeScreenMain_tr0();
		void effect_startup_region_Ui_home_Main_main_Home_home_HomeScreenMain_tr1();
		void effect_startup_region_Ui_home_Main_main_Home_home_HomeScreenUpdateShortcuts_tr0();
		void effect_startup_region_Ui_home_Main_main_Home_home_HomeScreenUpdateShortcuts_tr1();
		void effect_startup_region_Ui_home_Main_main_Home_home_ConfigureFavHK_tr0();
		void effect_startup_region_Ui_home_Main_main_Home_home_ConfigureFavHK_tr1();
		void effect_startup_region_Ui_home_Main_main_PowerMode_tr0();
		void effect_startup_region_Ui_home_Main_main_PowerMode_tr1();
		void effect_startup_region_Ui_home_Main_main_PowerMode_tr2();
		void effect_startup_region_Ui_home_Main_main_PowerMode_tr3();
		void effect_startup_region_Ui_home_Main_main_PowerMode_tr4();
		void effect_startup_region_Ui_home_Main_main_PowerMode_tr5();
		void effect_startup_region_Ui_home_Main_main_PowerMode_Powermodes_MediaOff_lr1_lr1();
		void effect_startup_region_Ui_home_Main_main_Setup_lr1_lr1();
		void effect_startup_region_Ui_home_Main_main_Setup_tr0();
		void effect_startup_region_Ui_home_Main_main_Setup_tr1();
		void effect_startup_region_Ui_home_Main_main_Setup_tr2();
		void effect_startup_region_Ui_home_Main_main_Setup_tr3();
		void effect_startup_region_Ui_home_Main_main_Setup_tr4();
		void effect_startup_region_Ui_home_Main_main_Setup_tr5();
		void effect_startup_region_Ui_home_Main_main_Setup_tr6();
		void effect_startup_region_Ui_home_Main_main_Setup_tr7();
		void effect_startup_region_Ui_home_Main_main_Setup_tr8();
		void effect_startup_region_Ui_home_Main_main_Setup_tr9();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain_tr0();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain_tr1();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain_tr2();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain_tr3();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain_tr4();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain_tr5();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain_tr6();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain_tr7();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain_tr8();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_VehicleSetup_tr0();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_VehicleSetup_tr1();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_VehicleSetup_tr2();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_ParkAssist_tr0();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_MoodLighting_tr0();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_BluetoothSetup_tr0();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_BluetoothSetup_tr1();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_BluetoothSetup_tr2();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_BluetoothSetup_tr3();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_EditSMSLightbox_tr0();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_VolumeSetup_tr0();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_VolumeSetup_tr1();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_AUXInGain_tr0();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_GeneralSetup_tr0();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_GeneralSetup_tr1();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_GeneralSetup_tr2();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_SetDate_tr0();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_SetTime_tr0();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_SoftwareDetails_tr0();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_DisplaySetup_tr0();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_VoiceAlerts_tr0();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_PairedDevices_tr0();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_PairedDevices_tr1();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_PairNewDevice_tr0();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_DeleteDevice_tr0();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_LightingSetup_tr0();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_LightingSetup_tr1();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_About_tr0();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup_tr0();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup_audioSetup_region_AudioPresets_tr0();
		void effect_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup_audioSetup_region_BalanceFader_tr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_tr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_tr1();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_tr2();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_tr3();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_tr4();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_tr5();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_tr6();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_tr7();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_EnggMenuMain_lr1_lr1();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_EnggMenuMain_tr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_EnggMenuMain_tr1();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_EnggMenuMain_tr2();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_EnggMenuMain_tr3();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_EnggMenuMain_tr4();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_EnggMenuMain_tr5();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_TestMode_lr1_lr1();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_TestMode_tr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_lr0_lr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_tr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_IlluminationScreenMain_tr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_IlluminationScreenMain_tr1();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_DisplayIllumination_tr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_ButtonPanelIllumination_tr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_ButtonPanel_lr1_lr1();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_ButtonPanel_tr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_DebugLog_lr1_lr1();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_DebugLog_tr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_lr0_lr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_tr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_SystemConfiguration_tr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_SystemConfiguration_tr1();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_SystemConfiguration_tr2();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_VIN_tr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart_tr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo__16RPartNoScreenMain_tr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo__16RPartNoScreenMain_tr1();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo__16RPartNoScreenMain_tr2();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo__16RPartNoScreenMain_tr3();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo__16RPartNoScreenMain_tr4();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo__16RPartNoScreenMain_tr5();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ParameterPartNo_tr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_SoftwarePartNo_tr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ButtonPanelPartNo_tr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ContainerPartNo_tr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_SilverBoxPartNo_tr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_DisplayHWPartNo_tr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_GPSCoordinate_tr0();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_PictureViewer_lr1_lr1();
		void effect_startup_region_Ui_home_Main_main_EnggMenu_engg_region_PictureViewer_tr0();
		void effect_startup_region_Ui_home_Main_main_AndroidAuto_tr0();
		void effect_startup_region_Ui_home_Main_main_AndroidAuto_tr1();
		void effect_startup_region_Ui_home_Main_main_AndroidAuto_tr2();
		void effect_startup_region_Ui_home_Main_main_AndroidAuto_tr3();
		void effect_startup_region_Ui_home_Main_main_AndroidAuto_tr4();
		void effect_startup_region_Ui_home_Main_main_AndroidAuto_aa_region_AAMain_lr1_lr1();
		void effect_startup_region_Ui_home_Main_main_CarPlay_tr0();
		void effect_startup_region_Ui_home_Main_main_CarPlay_tr1();
		void effect_startup_region_Ui_home_Main_main_CarPlay_tr2();
		void effect_startup_region_Ui_home_Main_main_CarPlay_tr3();
		void effect_startup_region_Ui_home_Main_main_CarPlay_tr4();
		void effect_startup_region_Ui_home_Main_main_CarPlay_tr5();
		void effect_startup_region_Ui_home_Main_main_CarPlay_carplay_region_CarPlayMain_lr1_lr1();
		void effect_startup_region_Ui_home_Main_main_SAL_lr1_lr1();
		void effect_startup_region_Ui_home_Main_main_SAL_tr0();
		void effect_startup_region_Ui_home_Main_main_SAL_tr1();
		void effect_startup_region_Ui_home_Main_main_SoftwareUpdate_lr1_lr1();
		void effect_startup_region_Ui_home_Main_main_SoftwareUpdate_tr0();
		void effect_startup_region_Ui_home_Main_main_SoftwareUpdate_tr1();
		void effect_startup_region_Ui_home_Main_main_SoftwareUpdate_tr2();
		void effect_startup_region_Ui_home_Main_main_SoftwareUpdate_tr3();
		void effect_startup_region_Ui_home_Main_main_SoftwareUpdate_tr4();
		void effect_startup_region_Ui_home_Main_main_SoftwareUpdate_tr5();
		void effect_startup_region_Ui_home_Main_main_SoftwareUpdate_tr6();
		void effect_startup_region_Ui_home_Main_main_SoftwareUpdate_tr7();
		void effect_startup_region_Ui_home_Main_main_SoftwareUpdate_tr8();
		void effect_startup_region_Ui_home_Main_main_SoftwareUpdate_swupdate_region_SoftwareUpdateMain_tr0();
		void effect_startup_region_Ui_home_Main_main_SoftwareUpdate_swupdate_region_SoftwareSelectScreen_tr0();
		void effect_startup_region_Ui_home_Main_main_Phone_lr1_lr1();
		void effect_startup_region_Ui_home_Main_main_Phone_tr0();
		void effect_startup_region_Ui_home_Main_main_Phone_tr1();
		void effect_startup_region_Ui_home_Main_main_Phone_tr2();
		void effect_startup_region_Ui_home_Main_main_Phone_tr3();
		void effect_startup_region_Ui_home_Main_main_Phone_tr4();
		void effect_startup_region_Ui_home_Main_main_Phone_tr5();
		void effect_startup_region_Ui_home_Main_main_Phone_tr6();
		void effect_startup_region_Ui_home_Main_main_Phone_tr7();
		void effect_startup_region_Ui_home_Main_main_Phone_tr8();
		void effect_startup_region_Ui_home_Main_main_Phone_tr9();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Favorites_tr0();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Favorites_tr1();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Favorites_tr2();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Favorites_tr3();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Contacts_tr0();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Contacts_tr1();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Contacts_tr2();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Contacts_tr3();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_NumPad_tr0();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_NumPad_tr1();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_NumPad_tr2();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_NumPad_tr3();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_CallLogs_tr0();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_CallLogs_tr1();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_CallLogs_tr2();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_CallLogs_tr3();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_ContactDetails_tr0();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_ContactDetails_tr1();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_ContactDetails_tr2();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_ContactDetails_tr3();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_ContactDetails_tr4();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_tr0();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_tr1();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_tr2();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_tr3();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_tr4();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_tr5();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_tr6();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_tr7();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_lr1_lr1();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_tr0();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_tr1();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaLoading__tr0();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaLoading__tr1();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaMain_tr0();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaMain_tr1();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaPicture_tr0();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaPicture_tr1();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaPicture_tr2();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaVideo_tr0();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaVideo_tr1();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaAux_tr0();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_AUXInGain_tr0();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowseCategory_tr0();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowseCategory_tr1();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowseCategory_tr2();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowseCategory_tr3();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowse_tr0();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowse_tr1();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowse_tr2();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_lr1_lr1();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tr0();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tr1();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tr0();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerDefault_tr0();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerDefault_tr1();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerDefault_tr2();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerDefault_tr3();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutoseekUp_tr0();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutostore_tr0();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerScan_tr0();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutoseekDown_tr0();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerOption_tr0();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerOption_tr1();
		void effect_startup_region_Ui_home_Main_main_VRHelp_lr1_lr1();
		void effect_startup_region_Ui_home_Main_main_VRHelp_tr0();
		void effect_startup_region_Ui_home_Main_main_VRHelp_tr1();
		void effect_startup_region_Ui_home_Main_main_VRHelp_tr2();
		void effect_startup_region_Ui_home_Main_main_VRHelp_tr3();
		void effect_startup_region_Ui_home_Main_main_VRHelp_tr4();
		void effect_startup_region_Ui_home_Main_main_VRHelp_tr5();
		void effect_startup_region_Ui_home_Main_main_VRHelp_tr6();
		void effect_startup_region_Ui_home_Main_main_VRHelp_tr7();
		void effect_startup_region_Ui_home_Main_main_VRHelp_tr8();
		void effect_startup_region_Ui_home_Main_main_VRHelp_tr9();
		void effect_startup_region_Ui_home_Main_main_VRHelp_vr_region_VRHelpMain_tr0();
		void effect_startup_region_Ui_home_Main_main_VRHelp_vr_region_VRHelpDetail_tr0();
		void effect_startup_region_Ui_home_PhoneCall_lr1_lr1();
		void effect_startup_region_Ui_home_PhoneCall_tr0();
		void effect_startup_region_Ui_home_PhoneCall_tr1();
		void effect_startup_region_Ui_home_PhoneCall_tr2();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallScreen_tr0();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallScreen_tr1();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_ParticipantScreen_tr0();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_tr0();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Favorites_tr0();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Favorites_tr1();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Favorites_tr2();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Favorites_tr3();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Contacts_tr0();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Contacts_tr1();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Contacts_tr2();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Contacts_tr3();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_NumPad_tr0();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_NumPad_tr1();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_NumPad_tr2();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_NumPad_tr3();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_CallLogs_tr0();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_CallLogs_tr1();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_CallLogs_tr2();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_CallLogs_tr3();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_ContactDetails_tr0();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_ContactDetails_tr1();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_ContactDetails_tr2();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_ContactDetails_tr3();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_ContactDetails_tr4();
		void effect_startup_region_Ui_home_VR_lr1_lr1();
		void effect_startup_region_Ui_home_VR_tr0();
		void effect_startup_region_Ui_home_VR_tr1();
		void effect_startup_region_Ui_home_VR_tr2();
		void effect_startup_region_Ui_popup_PopupManager_Zone2_NoNotification_tr0();
		void effect_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_lr1_lr1();
		void effect_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_tr0();
		void effect_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_tr1();
		void effect_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_tr2();
		void effect_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_notification_timer_region_NotificationTimerState_lr0_lr0();
		void effect_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_notification_timer_region_NotificationTimerState_lr1_lr1();
		void effect_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_notification_timer_region_NotificationTimerState_tr0();
		void effect_startup_region_Ui_popup_PopupManager_Zone4_NoPopup_tr0();
		void effect_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_lr1_lr1();
		void effect_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_tr0();
		void effect_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_tr1();
		void effect_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_tr2();
		void effect_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_popup_timer_region_PopupTimerState_lr0_lr0();
		void effect_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_popup_timer_region_PopupTimerState_lr1_lr1();
		void effect_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_popup_timer_region_PopupTimerState_tr0();
		void effect_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_tr0();
		void effect_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_ShortcutDrawerMinimizedState_lr1_lr1();
		void effect_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_ShortcutDrawerMinimizedState_lr2_lr2();
		void effect_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_ShortcutDrawerMinimizedState_tr0();
		void effect_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_ShortcutDrawerMinimizedState_tr1();
		void effect_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_SourceDrawerMaximizedState_tr0();
		void effect_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_SourceDrawerMaximizedState_source_drawer_maximized_region_SourceDrawerTimerState_lr0_lr0();
		void effect_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_SourceDrawerMaximizedState_source_drawer_maximized_region_SourceDrawerTimerState_tr0();
		void effect_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState_tr0();
		void effect_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState_hvac_drawer_maximized_region_HVACDrawerTimerState_lr0_lr0();
		void effect_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState_hvac_drawer_maximized_region_HVACDrawerTimerState_tr0();
		void effect_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMinimizedState_lr1_lr1();
		void effect_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMinimizedState_lr2_lr2();
		void effect_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMinimizedState_tr0();
		void effect_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMaximizedState_tr0();
		void effect_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMaximizedState_qad_drawer_maximized_region_QADTimerState_lr0_lr0();
		void effect_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMaximizedState_qad_drawer_maximized_region_QADTimerState_tr0();
		void effect_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersHiddenState_tr0();
		void effect_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_HideVolumeOverlay_tr0();
		void effect_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_ShowVolumeOverlay_tr0();
		void effect_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_ShowVolumeOverlay_volume_overlay_show_region_VolOverlayTimerState_lr0_lr0();
		void effect_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_ShowVolumeOverlay_volume_overlay_show_region_VolOverlayTimerState_tr0();
		void effect_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_HideHvacOverlay_tr0();
		void effect_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_ShowHvacOverlay_tr0();
		void effect_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_ShowHvacOverlay_hvac_show_overlay_regioin_HvacOverlayTimerState_lr0_lr0();
		void effect_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_ShowHvacOverlay_hvac_show_overlay_regioin_HvacOverlayTimerState_tr0();
		void effect_startup_region_StartupAnimation_tr0();
		void effect_startup_region_StartupAnimation_tr1();
		void effect_startup_region_StartupAnimation_tr2();
		void effect_startup_region_Ui_home_Main_main_Home_home__choice_0_tr1();
		void effect_startup_region_Ui_home_Main_main_Home_home__choice_0_tr0();
		void effect_startup_region_Ui_home_Main_main_PowerMode_Powermodes__choice_0_tr0();
		void effect_startup_region_Ui_home_Main_main_PowerMode_Powermodes__choice_0_tr1();
		void effect_startup_region_Ui_home_Main_main_AndroidAuto_aa_region__choice_0_tr1();
		void effect_startup_region_Ui_home_Main_main_AndroidAuto_aa_region__choice_0_tr0();
		void effect_startup_region_Ui_home_Main_main_CarPlay_carplay_region__choice_0_tr1();
		void effect_startup_region_Ui_home_Main_main_CarPlay_carplay_region__choice_0_tr0();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region__choice_0_tr0();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region__choice_0_tr1();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region__choice_0_tr2();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region__choice_0_tr4();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region__choice_0_tr3();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region__choice_1_tr0();
		void effect_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region__choice_1_tr1();
		void effect_startup_region_Ui_home_Main_main__choice_0_tr1();
		void effect_startup_region_Ui_home_Main_main__choice_0_tr0();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region__choice_0_tr0();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region__choice_0_tr2();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region__choice_0_tr3();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region__choice_0_tr4();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region__choice_0_tr5();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region__choice_0_tr1();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain__choice_0_tr1();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain__choice_0_tr0();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio__choice_0_tr0();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio__choice_0_tr1();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio__choice_0_tr2();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main__choice_0_tr1();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main__choice_0_tr2();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main__choice_0_tr3();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main__choice_0_tr4();
		void effect_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main__choice_0_tr0();
		void effect_startup_region_Ui_home_Main_main__choice_1_tr0();
		void effect_startup_region_Ui_home_Main_main__choice_1_tr1();
		void effect_startup_region_Ui_home_Main_main__choice_2_tr1();
		void effect_startup_region_Ui_home_Main_main__choice_2_tr0();
		void effect_startup_region_Ui_home_Main_main__choice_3_tr1();
		void effect_startup_region_Ui_home_Main_main__choice_3_tr0();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region__choice_0_tr0();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region__choice_0_tr1();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region__choice_0_tr2();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region__choice_0_tr4();
		void effect_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region__choice_0_tr3();
		void effect_startup_region_Ui_home__choice_0_tr1();
		void effect_startup_region_Ui_home__choice_0_tr2();
		void effect_startup_region_Ui_home__choice_0_tr3();
		void effect_startup_region_Ui_home__choice_0_tr0();
		void effect_startup_region_Ui_drawer_DrawerManager_drawers_main_region__choice_0_tr0();
		void effect_startup_region_Ui_drawer_DrawerManager_drawers_main_region__choice_0_tr1();
		void effect_startup_region__choice_0_tr0();
		void effect_startup_region__choice_0_tr2();
		void effect_startup_region__choice_0_tr1();
		void enact_startup_region_EarlyWakeup();
		void enact_startup_region_Ui();
		void enact_startup_region_Ui_home_PDC();
		void enact_startup_region_Ui_home_PDC_active_pdc_region_UI_PDC();
		void enact_startup_region_Ui_home_Main_main_Home();
		void enact_startup_region_Ui_home_Main_main_Home_home_HomeScreenMain();
		void enact_startup_region_Ui_home_Main_main_Home_home_HomeScreenUpdateShortcuts();
		void enact_startup_region_Ui_home_Main_main_Home_home_ConfigureFavHK();
		void enact_startup_region_Ui_home_Main_main_PowerMode_Powermodes_MediaOff();
		void enact_startup_region_Ui_home_Main_main_Setup();
		void enact_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain();
		void enact_startup_region_Ui_home_Main_main_Setup_setup_region_VehicleSetup();
		void enact_startup_region_Ui_home_Main_main_Setup_setup_region_ParkAssist();
		void enact_startup_region_Ui_home_Main_main_Setup_setup_region_MoodLighting();
		void enact_startup_region_Ui_home_Main_main_Setup_setup_region_BluetoothSetup();
		void enact_startup_region_Ui_home_Main_main_Setup_setup_region_EditSMSLightbox();
		void enact_startup_region_Ui_home_Main_main_Setup_setup_region_VolumeSetup();
		void enact_startup_region_Ui_home_Main_main_Setup_setup_region_AUXInGain();
		void enact_startup_region_Ui_home_Main_main_Setup_setup_region_GeneralSetup();
		void enact_startup_region_Ui_home_Main_main_Setup_setup_region_SetDate();
		void enact_startup_region_Ui_home_Main_main_Setup_setup_region_SetTime();
		void enact_startup_region_Ui_home_Main_main_Setup_setup_region_SoftwareDetails();
		void enact_startup_region_Ui_home_Main_main_Setup_setup_region_DisplaySetup();
		void enact_startup_region_Ui_home_Main_main_Setup_setup_region_VoiceAlerts();
		void enact_startup_region_Ui_home_Main_main_Setup_setup_region_PairedDevices();
		void enact_startup_region_Ui_home_Main_main_Setup_setup_region_PairNewDevice();
		void enact_startup_region_Ui_home_Main_main_Setup_setup_region_DeleteDevice();
		void enact_startup_region_Ui_home_Main_main_Setup_setup_region_LightingSetup();
		void enact_startup_region_Ui_home_Main_main_Setup_setup_region_About();
		void enact_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup();
		void enact_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup_audioSetup_region_AudioPresets();
		void enact_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup_audioSetup_region_BalanceFader();
		void enact_startup_region_Ui_home_Main_main_EnggMenu();
		void enact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_EnggMenuMain();
		void enact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_TestMode();
		void enact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_IlluminationScreenMain();
		void enact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_DisplayIllumination();
		void enact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_ButtonPanelIllumination();
		void enact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_ButtonPanel();
		void enact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_DebugLog();
		void enact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_SystemConfiguration();
		void enact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_VIN();
		void enact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo__16RPartNoScreenMain();
		void enact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ParameterPartNo();
		void enact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_SoftwarePartNo();
		void enact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ButtonPanelPartNo();
		void enact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ContainerPartNo();
		void enact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_SilverBoxPartNo();
		void enact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_DisplayHWPartNo();
		void enact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_GPSCoordinate();
		void enact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_PictureViewer();
		void enact_startup_region_Ui_home_Main_main_AndroidAuto_aa_region_AAMain();
		void enact_startup_region_Ui_home_Main_main_CarPlay_carplay_region_CarPlayMain();
		void enact_startup_region_Ui_home_Main_main_SAL();
		void enact_startup_region_Ui_home_Main_main_SoftwareUpdate();
		void enact_startup_region_Ui_home_Main_main_SoftwareUpdate_swupdate_region_SoftwareUpdateMain();
		void enact_startup_region_Ui_home_Main_main_SoftwareUpdate_swupdate_region_SoftwareSelectScreen();
		void enact_startup_region_Ui_home_Main_main_Phone();
		void enact_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Favorites();
		void enact_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Contacts();
		void enact_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_NumPad();
		void enact_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_CallLogs();
		void enact_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_ContactDetails();
		void enact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media();
		void enact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaLoading_();
		void enact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaMain();
		void enact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaPicture();
		void enact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaVideo();
		void enact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaAux();
		void enact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_AUXInGain();
		void enact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain();
		void enact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowseCategory();
		void enact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowse();
		void enact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner();
		void enact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain();
		void enact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerDefault();
		void enact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutoseekUp();
		void enact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutostore();
		void enact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerScan();
		void enact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutoseekDown();
		void enact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerOption();
		void enact_startup_region_Ui_home_Main_main_VRHelp();
		void enact_startup_region_Ui_home_Main_main_VRHelp_vr_region_VRHelpMain();
		void enact_startup_region_Ui_home_Main_main_VRHelp_vr_region_VRHelpDetail();
		void enact_startup_region_Ui_home_PhoneCall();
		void enact_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallScreen();
		void enact_startup_region_Ui_home_PhoneCall_phone_call_region_ParticipantScreen();
		void enact_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse();
		void enact_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Favorites();
		void enact_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Contacts();
		void enact_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_NumPad();
		void enact_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_CallLogs();
		void enact_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_ContactDetails();
		void enact_startup_region_Ui_home_VR();
		void enact_startup_region_Ui_popup_PopupManager_Zone2_NoNotification();
		void enact_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive();
		void enact_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_notification_timer_region_NotificationTimerState();
		void enact_startup_region_Ui_popup_PopupManager_Zone4_NoPopup();
		void enact_startup_region_Ui_popup_PopupManager_Zone4_PopupActive();
		void enact_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_popup_timer_region_PopupTimerState();
		void enact_startup_region_Ui_drawer_DrawerManager();
		void enact_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState();
		void enact_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_ShortcutDrawerMinimizedState();
		void enact_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_SourceDrawerMaximizedState();
		void enact_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_SourceDrawerMaximizedState_source_drawer_maximized_region_SourceDrawerTimerState();
		void enact_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState();
		void enact_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState_hvac_drawer_maximized_region_HVACDrawerTimerState();
		void enact_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMinimizedState();
		void enact_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMaximizedState();
		void enact_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMaximizedState_qad_drawer_maximized_region_QADTimerState();
		void enact_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_status_bar_region_StatusBarState();
		void enact_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersHiddenState();
		void enact_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_HideVolumeOverlay();
		void enact_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_ShowVolumeOverlay();
		void enact_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_ShowVolumeOverlay_volume_overlay_show_region_VolOverlayTimerState();
		void enact_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_HideHvacOverlay();
		void enact_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_ShowHvacOverlay();
		void enact_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_ShowHvacOverlay_hvac_show_overlay_regioin_HvacOverlayTimerState();
		void enact_startup_region_StartupAnimation();
		void exact_startup_region_EarlyWakeup();
		void exact_startup_region_Ui();
		void exact_startup_region_Ui_home_PDC();
		void exact_startup_region_Ui_home_PDC_active_pdc_region_UI_PDC();
		void exact_startup_region_Ui_home_Main_main_Home();
		void exact_startup_region_Ui_home_Main_main_Home_home_HomeScreenMain();
		void exact_startup_region_Ui_home_Main_main_Home_home_HomeScreenUpdateShortcuts();
		void exact_startup_region_Ui_home_Main_main_Home_home_ConfigureFavHK();
		void exact_startup_region_Ui_home_Main_main_PowerMode_Powermodes_MediaOff();
		void exact_startup_region_Ui_home_Main_main_Setup();
		void exact_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain();
		void exact_startup_region_Ui_home_Main_main_Setup_setup_region_VehicleSetup();
		void exact_startup_region_Ui_home_Main_main_Setup_setup_region_ParkAssist();
		void exact_startup_region_Ui_home_Main_main_Setup_setup_region_MoodLighting();
		void exact_startup_region_Ui_home_Main_main_Setup_setup_region_BluetoothSetup();
		void exact_startup_region_Ui_home_Main_main_Setup_setup_region_EditSMSLightbox();
		void exact_startup_region_Ui_home_Main_main_Setup_setup_region_VolumeSetup();
		void exact_startup_region_Ui_home_Main_main_Setup_setup_region_AUXInGain();
		void exact_startup_region_Ui_home_Main_main_Setup_setup_region_GeneralSetup();
		void exact_startup_region_Ui_home_Main_main_Setup_setup_region_SetDate();
		void exact_startup_region_Ui_home_Main_main_Setup_setup_region_SetTime();
		void exact_startup_region_Ui_home_Main_main_Setup_setup_region_SoftwareDetails();
		void exact_startup_region_Ui_home_Main_main_Setup_setup_region_DisplaySetup();
		void exact_startup_region_Ui_home_Main_main_Setup_setup_region_VoiceAlerts();
		void exact_startup_region_Ui_home_Main_main_Setup_setup_region_PairedDevices();
		void exact_startup_region_Ui_home_Main_main_Setup_setup_region_PairNewDevice();
		void exact_startup_region_Ui_home_Main_main_Setup_setup_region_DeleteDevice();
		void exact_startup_region_Ui_home_Main_main_Setup_setup_region_LightingSetup();
		void exact_startup_region_Ui_home_Main_main_Setup_setup_region_About();
		void exact_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup();
		void exact_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup_audioSetup_region_AudioPresets();
		void exact_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup_audioSetup_region_BalanceFader();
		void exact_startup_region_Ui_home_Main_main_EnggMenu();
		void exact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_EnggMenuMain();
		void exact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_TestMode();
		void exact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_IlluminationScreenMain();
		void exact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_DisplayIllumination();
		void exact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_ButtonPanelIllumination();
		void exact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_ButtonPanel();
		void exact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_DebugLog();
		void exact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_SystemConfiguration();
		void exact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_VIN();
		void exact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo__16RPartNoScreenMain();
		void exact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ParameterPartNo();
		void exact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_SoftwarePartNo();
		void exact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ButtonPanelPartNo();
		void exact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ContainerPartNo();
		void exact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_SilverBoxPartNo();
		void exact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_DisplayHWPartNo();
		void exact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_GPSCoordinate();
		void exact_startup_region_Ui_home_Main_main_EnggMenu_engg_region_PictureViewer();
		void exact_startup_region_Ui_home_Main_main_AndroidAuto_aa_region_AAMain();
		void exact_startup_region_Ui_home_Main_main_CarPlay_carplay_region_CarPlayMain();
		void exact_startup_region_Ui_home_Main_main_SAL();
		void exact_startup_region_Ui_home_Main_main_SoftwareUpdate();
		void exact_startup_region_Ui_home_Main_main_SoftwareUpdate_swupdate_region_SoftwareUpdateMain();
		void exact_startup_region_Ui_home_Main_main_SoftwareUpdate_swupdate_region_SoftwareSelectScreen();
		void exact_startup_region_Ui_home_Main_main_Phone();
		void exact_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Favorites();
		void exact_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Contacts();
		void exact_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_NumPad();
		void exact_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_CallLogs();
		void exact_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_ContactDetails();
		void exact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media();
		void exact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaLoading_();
		void exact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaMain();
		void exact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaPicture();
		void exact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaVideo();
		void exact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaAux();
		void exact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_AUXInGain();
		void exact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain();
		void exact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowseCategory();
		void exact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowse();
		void exact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner();
		void exact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain();
		void exact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerDefault();
		void exact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutoseekUp();
		void exact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutostore();
		void exact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerScan();
		void exact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutoseekDown();
		void exact_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerOption();
		void exact_startup_region_Ui_home_Main_main_VRHelp();
		void exact_startup_region_Ui_home_Main_main_VRHelp_vr_region_VRHelpMain();
		void exact_startup_region_Ui_home_Main_main_VRHelp_vr_region_VRHelpDetail();
		void exact_startup_region_Ui_home_PhoneCall();
		void exact_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallScreen();
		void exact_startup_region_Ui_home_PhoneCall_phone_call_region_ParticipantScreen();
		void exact_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse();
		void exact_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Favorites();
		void exact_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Contacts();
		void exact_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_NumPad();
		void exact_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_CallLogs();
		void exact_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_ContactDetails();
		void exact_startup_region_Ui_home_VR();
		void exact_startup_region_Ui_popup_PopupManager_Zone2_NoNotification();
		void exact_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive();
		void exact_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_notification_timer_region_NotificationTimerState();
		void exact_startup_region_Ui_popup_PopupManager_Zone4_NoPopup();
		void exact_startup_region_Ui_popup_PopupManager_Zone4_PopupActive();
		void exact_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_popup_timer_region_PopupTimerState();
		void exact_startup_region_Ui_drawer_DrawerManager();
		void exact_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState();
		void exact_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_ShortcutDrawerMinimizedState();
		void exact_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_SourceDrawerMaximizedState();
		void exact_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_SourceDrawerMaximizedState_source_drawer_maximized_region_SourceDrawerTimerState();
		void exact_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState();
		void exact_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState_hvac_drawer_maximized_region_HVACDrawerTimerState();
		void exact_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMinimizedState();
		void exact_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMaximizedState();
		void exact_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMaximizedState_qad_drawer_maximized_region_QADTimerState();
		void exact_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_status_bar_region_StatusBarState();
		void exact_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersHiddenState();
		void exact_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_HideVolumeOverlay();
		void exact_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_ShowVolumeOverlay();
		void exact_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_ShowVolumeOverlay_volume_overlay_show_region_VolOverlayTimerState();
		void exact_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_HideHvacOverlay();
		void exact_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_ShowHvacOverlay();
		void exact_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_ShowHvacOverlay_hvac_show_overlay_regioin_HvacOverlayTimerState();
		void exact_startup_region_StartupAnimation();
		void enseq_startup_region_EarlyWakeup_default();
		void enseq_startup_region_Ui_home_PDC_default();
		void enseq_startup_region_Ui_home_PDC_active_pdc_region_UI_PDC_default();
		void enseq_startup_region_Ui_home_Main_default();
		void enseq_startup_region_Ui_home_Main_main_Home_default();
		void enseq_startup_region_Ui_home_Main_main_Home_home_HomeScreenMain_default();
		void enseq_startup_region_Ui_home_Main_main_Home_home_HomeScreenUpdateShortcuts_default();
		void enseq_startup_region_Ui_home_Main_main_Home_home_ConfigureFavHK_default();
		void enseq_startup_region_Ui_home_Main_main_PowerMode_default();
		void enseq_startup_region_Ui_home_Main_main_PowerMode_Powermodes_MediaOff_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_entry_AUD_PRE();
		void enseq_startup_region_Ui_home_Main_main_Setup_entry_AudioSetup();
		void enseq_startup_region_Ui_home_Main_main_Setup_entry_BAL_FAD();
		void enseq_startup_region_Ui_home_Main_main_Setup_entry_BMT();
		void enseq_startup_region_Ui_home_Main_main_Setup_entry_BTSetup();
		void enseq_startup_region_Ui_home_Main_main_Setup_entry_DisplaySetup();
		void enseq_startup_region_Ui_home_Main_main_Setup_entry_GeneralSetup();
		void enseq_startup_region_Ui_home_Main_main_Setup_entry_MoodLight();
		void enseq_startup_region_Ui_home_Main_main_Setup_entry_PairDevices();
		void enseq_startup_region_Ui_home_Main_main_Setup_entry_VehicleSetup();
		void enseq_startup_region_Ui_home_Main_main_Setup_entry_VolumeSetup();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_VehicleSetup_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_ParkAssist_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_MoodLighting_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_BluetoothSetup_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_EditSMSLightbox_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_VolumeSetup_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_AUXInGain_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_GeneralSetup_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_SetDate_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_SetTime_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_SoftwareDetails_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_DisplaySetup_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_VoiceAlerts_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_PairedDevices_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_PairNewDevice_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_DeleteDevice_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_LightingSetup_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_About_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup_audioSetup_region_AudioPresets_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup_audioSetup_region_BalanceFader_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_EnggMenuMain_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_TestMode_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_IlluminationScreenMain_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_DisplayIllumination_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_ButtonPanelIllumination_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_ButtonPanel_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_DebugLog_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_SystemConfiguration_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_VIN_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo__16RPartNoScreenMain_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ParameterPartNo_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_SoftwarePartNo_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ButtonPanelPartNo_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ContainerPartNo_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_SilverBoxPartNo_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_DisplayHWPartNo_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_GPSCoordinate_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_PictureViewer_default();
		void enseq_startup_region_Ui_home_Main_main_AndroidAuto_default();
		void enseq_startup_region_Ui_home_Main_main_AndroidAuto_aa_region_AAMain_default();
		void enseq_startup_region_Ui_home_Main_main_CarPlay_default();
		void enseq_startup_region_Ui_home_Main_main_CarPlay_carplay_region_CarPlayMain_default();
		void enseq_startup_region_Ui_home_Main_main_SAL_default();
		void enseq_startup_region_Ui_home_Main_main_SAL_sal_region_SmartlinkMain_default();
		void enseq_startup_region_Ui_home_Main_main_SoftwareUpdate_default();
		void enseq_startup_region_Ui_home_Main_main_SoftwareUpdate_swupdate_region_SoftwareUpdateMain_default();
		void enseq_startup_region_Ui_home_Main_main_SoftwareUpdate_swupdate_region_SoftwareSelectScreen_default();
		void enseq_startup_region_Ui_home_Main_main_Phone_default();
		void enseq_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Favorites_default();
		void enseq_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Contacts_default();
		void enseq_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_NumPad_default();
		void enseq_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_CallLogs_default();
		void enseq_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_ContactDetails_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaLoading__default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaMain_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaPicture_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaVideo_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaAux_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_AUXInGain_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowseCategory_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowse_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerDefault_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutoseekUp_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutostore_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerScan_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutoseekDown_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerOption_default();
		void enseq_startup_region_Ui_home_Main_main_VRHelp_default();
		void enseq_startup_region_Ui_home_Main_main_VRHelp_vr_region_VRHelpMain_default();
		void enseq_startup_region_Ui_home_Main_main_VRHelp_vr_region_VRHelpDetail_default();
		void enseq_startup_region_Ui_home_PhoneCall_default();
		void enseq_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallScreen_default();
		void enseq_startup_region_Ui_home_PhoneCall_phone_call_region_ParticipantScreen_default();
		void enseq_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_default();
		void enseq_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Favorites_default();
		void enseq_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Contacts_default();
		void enseq_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_NumPad_default();
		void enseq_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_CallLogs_default();
		void enseq_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_ContactDetails_default();
		void enseq_startup_region_Ui_home_VR_default();
		void enseq_startup_region_Ui_popup_PopupManager_default();
		void enseq_startup_region_Ui_popup_PopupManager_Zone2_NoNotification_default();
		void enseq_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_default();
		void enseq_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_notification_timer_region_NotificationTimerState_default();
		void enseq_startup_region_Ui_popup_PopupManager_Zone4_NoPopup_default();
		void enseq_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_default();
		void enseq_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_popup_timer_region_PopupTimerState_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_ShortcutDrawerMinimizedState_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_SourceDrawerMaximizedState_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_SourceDrawerMaximizedState_source_drawer_maximized_region_SourceDrawerTimerState_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState_hvac_drawer_maximized_region_HVACDrawerTimerState_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMinimizedState_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMaximizedState_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMaximizedState_qad_drawer_maximized_region_QADTimerState_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_status_bar_region_StatusBarState_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersHiddenState_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_HideVolumeOverlay_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_ShowVolumeOverlay_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_ShowVolumeOverlay_volume_overlay_show_region_VolOverlayTimerState_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_HideHvacOverlay_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_ShowHvacOverlay_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_ShowHvacOverlay_hvac_show_overlay_regioin_HvacOverlayTimerState_default();
		void enseq_startup_region_StartupAnimation_default();
		void enseq_startup_region_default();
		void enseq_startup_region_Ui_home_PDC_active_pdc_region_default();
		void enseq_startup_region_Ui_home_Main_main_default();
		void shenseq_startup_region_Ui_home_Main_main();
		void enseq_startup_region_Ui_home_Main_main_Home_home_default();
		void enseq_startup_region_Ui_home_Main_main_PowerMode_Powermodes_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_entry_VehicleSetup();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_default();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_entry_MoodLight();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_entry_BTSetup();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_entry_GeneralSetup();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_entry_VolumeSetup();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_entry_PairDevices();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_entry_DisplaySetup();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_entry_AudioSetup();
		void enseq_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup_audioSetup_region_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_default();
		void enseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_default();
		void enseq_startup_region_Ui_home_Main_main_AndroidAuto_aa_region_default();
		void enseq_startup_region_Ui_home_Main_main_CarPlay_carplay_region_default();
		void enseq_startup_region_Ui_home_Main_main_SAL_sal_region_default();
		void enseq_startup_region_Ui_home_Main_main_SoftwareUpdate_swupdate_region_default();
		void enseq_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_default();
		void enseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_default();
		void enseq_startup_region_Ui_home_Main_main_VRHelp_vr_region_default();
		void enseq_startup_region_Ui_home_PhoneCall_phone_call_region_default();
		void enseq_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_default();
		void enseq_startup_region_Ui_popup_default();
		void enseq_startup_region_Ui_popup_PopupManager_Zone2_default();
		void enseq_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_notification_timer_region_default();
		void enseq_startup_region_Ui_popup_PopupManager_Zone4_default();
		void enseq_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_popup_timer_region_default();
		void enseq_startup_region_Ui_drawer_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_SourceDrawerMaximizedState_source_drawer_maximized_region_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState_hvac_drawer_maximized_region_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMaximizedState_qad_drawer_maximized_region_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_status_bar_region_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_ShowVolumeOverlay_volume_overlay_show_region_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_default();
		void enseq_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_ShowHvacOverlay_hvac_show_overlay_regioin_default();
		void exseq_startup_region_EarlyWakeup();
		void exseq_startup_region_Ui();
		void exseq_startup_region_Ui_home_PDC();
		void exseq_startup_region_Ui_home_PDC_active_pdc_region_UI_PDC();
		void exseq_startup_region_Ui_home_Main();
		void exseq_startup_region_Ui_home_Main_main_Home();
		void exseq_startup_region_Ui_home_Main_main_Home_home_HomeScreenMain();
		void exseq_startup_region_Ui_home_Main_main_Home_home_HomeScreenUpdateShortcuts();
		void exseq_startup_region_Ui_home_Main_main_Home_home_ConfigureFavHK();
		void exseq_startup_region_Ui_home_Main_main_PowerMode();
		void exseq_startup_region_Ui_home_Main_main_PowerMode_Powermodes_MediaOff();
		void exseq_startup_region_Ui_home_Main_main_Setup();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_VehicleSetup();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_ParkAssist();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_MoodLighting();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_BluetoothSetup();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_EditSMSLightbox();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_VolumeSetup();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_AUXInGain();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_GeneralSetup();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_SetDate();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_SetTime();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_SoftwareDetails();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_DisplaySetup();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_VoiceAlerts();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_PairedDevices();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_PairNewDevice();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_DeleteDevice();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_LightingSetup();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_About();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup_audioSetup_region_AudioPresets();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup_audioSetup_region_BalanceFader();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_EnggMenuMain();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_TestMode();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_IlluminationScreenMain();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_DisplayIllumination();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_ButtonPanelIllumination();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_ButtonPanel();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_DebugLog();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_SystemConfiguration();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_VIN();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo__16RPartNoScreenMain();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ParameterPartNo();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_SoftwarePartNo();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ButtonPanelPartNo();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ContainerPartNo();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_SilverBoxPartNo();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_DisplayHWPartNo();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_GPSCoordinate();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_PictureViewer();
		void exseq_startup_region_Ui_home_Main_main_AndroidAuto();
		void exseq_startup_region_Ui_home_Main_main_AndroidAuto_aa_region_AAMain();
		void exseq_startup_region_Ui_home_Main_main_CarPlay();
		void exseq_startup_region_Ui_home_Main_main_CarPlay_carplay_region_CarPlayMain();
		void exseq_startup_region_Ui_home_Main_main_SAL();
		void exseq_startup_region_Ui_home_Main_main_SAL_sal_region_SmartlinkMain();
		void exseq_startup_region_Ui_home_Main_main_SoftwareUpdate();
		void exseq_startup_region_Ui_home_Main_main_SoftwareUpdate_swupdate_region_SoftwareUpdateMain();
		void exseq_startup_region_Ui_home_Main_main_SoftwareUpdate_swupdate_region_SoftwareSelectScreen();
		void exseq_startup_region_Ui_home_Main_main_Phone();
		void exseq_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Favorites();
		void exseq_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Contacts();
		void exseq_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_NumPad();
		void exseq_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_CallLogs();
		void exseq_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_ContactDetails();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaLoading_();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaMain();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaPicture();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaVideo();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaAux();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_AUXInGain();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowseCategory();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowse();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerDefault();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutoseekUp();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutostore();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerScan();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutoseekDown();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerOption();
		void exseq_startup_region_Ui_home_Main_main_VRHelp();
		void exseq_startup_region_Ui_home_Main_main_VRHelp_vr_region_VRHelpMain();
		void exseq_startup_region_Ui_home_Main_main_VRHelp_vr_region_VRHelpDetail();
		void exseq_startup_region_Ui_home_PhoneCall();
		void exseq_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallScreen();
		void exseq_startup_region_Ui_home_PhoneCall_phone_call_region_ParticipantScreen();
		void exseq_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse();
		void exseq_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Favorites();
		void exseq_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Contacts();
		void exseq_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_NumPad();
		void exseq_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_CallLogs();
		void exseq_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_ContactDetails();
		void exseq_startup_region_Ui_home_VR();
		void exseq_startup_region_Ui_popup_PopupManager_Zone2_NoNotification();
		void exseq_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive();
		void exseq_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_notification_timer_region_NotificationTimerState();
		void exseq_startup_region_Ui_popup_PopupManager_Zone4_NoPopup();
		void exseq_startup_region_Ui_popup_PopupManager_Zone4_PopupActive();
		void exseq_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_popup_timer_region_PopupTimerState();
		void exseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState();
		void exseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_ShortcutDrawerMinimizedState();
		void exseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_SourceDrawerMaximizedState();
		void exseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_SourceDrawerMaximizedState_source_drawer_maximized_region_SourceDrawerTimerState();
		void exseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState();
		void exseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState_hvac_drawer_maximized_region_HVACDrawerTimerState();
		void exseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMinimizedState();
		void exseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMaximizedState();
		void exseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMaximizedState_qad_drawer_maximized_region_QADTimerState();
		void exseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_status_bar_region_StatusBarState();
		void exseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersHiddenState();
		void exseq_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_HideVolumeOverlay();
		void exseq_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_ShowVolumeOverlay();
		void exseq_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_ShowVolumeOverlay_volume_overlay_show_region_VolOverlayTimerState();
		void exseq_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_HideHvacOverlay();
		void exseq_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_ShowHvacOverlay();
		void exseq_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_ShowHvacOverlay_hvac_show_overlay_regioin_HvacOverlayTimerState();
		void exseq_startup_region_StartupAnimation();
		void exseq_startup_region();
		void exseq_startup_region_Ui_home();
		void exseq_startup_region_Ui_home_PDC_active_pdc_region();
		void exseq_startup_region_Ui_home_Main_main();
		void exseq_startup_region_Ui_home_Main_main_Home_home();
		void exseq_startup_region_Ui_home_Main_main_PowerMode_Powermodes();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region();
		void exseq_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup_audioSetup_region();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration();
		void exseq_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo();
		void exseq_startup_region_Ui_home_Main_main_AndroidAuto_aa_region();
		void exseq_startup_region_Ui_home_Main_main_CarPlay_carplay_region();
		void exseq_startup_region_Ui_home_Main_main_SAL_sal_region();
		void exseq_startup_region_Ui_home_Main_main_SoftwareUpdate_swupdate_region();
		void exseq_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region();
		void exseq_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main();
		void exseq_startup_region_Ui_home_Main_main_VRHelp_vr_region();
		void exseq_startup_region_Ui_home_PhoneCall_phone_call_region();
		void exseq_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region();
		void exseq_startup_region_Ui_popup();
		void exseq_startup_region_Ui_popup_PopupManager_Zone2();
		void exseq_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_notification_timer_region();
		void exseq_startup_region_Ui_popup_PopupManager_Zone4();
		void exseq_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_popup_timer_region();
		void exseq_startup_region_Ui_drawer();
		void exseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region();
		void exseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region();
		void exseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_SourceDrawerMaximizedState_source_drawer_maximized_region();
		void exseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState_hvac_drawer_maximized_region();
		void exseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region();
		void exseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMaximizedState_qad_drawer_maximized_region();
		void exseq_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_status_bar_region();
		void exseq_startup_region_Ui_drawer_DrawerManager_volume_overlay_region();
		void exseq_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region();
		void exseq_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_ShowVolumeOverlay_volume_overlay_show_region();
		void exseq_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region();
		void exseq_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region();
		void exseq_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_ShowHvacOverlay_hvac_show_overlay_regioin();
		void react_startup_region_EarlyWakeup();
		void react_startup_region_Ui_home_PDC_active_pdc_region_UI_PDC();
		void react_startup_region_Ui_home_Main_main_Home_home_HomeScreenMain();
		void react_startup_region_Ui_home_Main_main_Home_home_HomeScreenUpdateShortcuts();
		void react_startup_region_Ui_home_Main_main_Home_home_ConfigureFavHK();
		void react_startup_region_Ui_home_Main_main_PowerMode_Powermodes_MediaOff();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_SetupMain();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_VehicleSetup();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_ParkAssist();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_MoodLighting();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_BluetoothSetup();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_EditSMSLightbox();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_VolumeSetup();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_AUXInGain();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_GeneralSetup();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_SetDate();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_SetTime();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_SoftwareDetails();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_DisplaySetup();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_VoiceAlerts();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_PairedDevices();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_PairNewDevice();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_DeleteDevice();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_LightingSetup();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_About();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup_audioSetup_region_AudioPresets();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup_audioSetup_region_BalanceFader();
		void react_startup_region_Ui_home_Main_main_EnggMenu_engg_region_EnggMenuMain();
		void react_startup_region_Ui_home_Main_main_EnggMenu_engg_region_TestMode();
		void react_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_IlluminationScreenMain();
		void react_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_DisplayIllumination();
		void react_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode_ButtonPanelIllumination();
		void react_startup_region_Ui_home_Main_main_EnggMenu_engg_region_ButtonPanel();
		void react_startup_region_Ui_home_Main_main_EnggMenu_engg_region_DebugLog();
		void react_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_SystemConfiguration();
		void react_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_VIN();
		void react_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo__16RPartNoScreenMain();
		void react_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ParameterPartNo();
		void react_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_SoftwarePartNo();
		void react_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ButtonPanelPartNo();
		void react_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_ContainerPartNo();
		void react_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_SilverBoxPartNo();
		void react_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo_DisplayHWPartNo();
		void react_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration_GPSCoordinate();
		void react_startup_region_Ui_home_Main_main_EnggMenu_engg_region_PictureViewer();
		void react_startup_region_Ui_home_Main_main_AndroidAuto_aa_region_AAMain();
		void react_startup_region_Ui_home_Main_main_CarPlay_carplay_region_CarPlayMain();
		void react_startup_region_Ui_home_Main_main_SAL_sal_region_SmartlinkMain();
		void react_startup_region_Ui_home_Main_main_SoftwareUpdate_swupdate_region_SoftwareUpdateMain();
		void react_startup_region_Ui_home_Main_main_SoftwareUpdate_swupdate_region_SoftwareSelectScreen();
		void react_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Favorites();
		void react_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_Contacts();
		void react_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_NumPad();
		void react_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_CallLogs();
		void react_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_ContactDetails();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaLoading_();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaMain();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaPicture();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaVideo();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaAux();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_AUXInGain();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowseCategory();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain_MediaBrowse();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerDefault();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutoseekUp();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutostore();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerScan();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main_TunerAutoseekDown();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerOption();
		void react_startup_region_Ui_home_Main_main_VRHelp_vr_region_VRHelpMain();
		void react_startup_region_Ui_home_Main_main_VRHelp_vr_region_VRHelpDetail();
		void react_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallScreen();
		void react_startup_region_Ui_home_PhoneCall_phone_call_region_ParticipantScreen();
		void react_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Favorites();
		void react_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_Contacts();
		void react_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_NumPad();
		void react_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_CallLogs();
		void react_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region_ContactDetails();
		void react_startup_region_Ui_home_VR();
		void react_startup_region_Ui_popup_PopupManager_Zone2_NoNotification();
		void react_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_notification_timer_region_NotificationTimerState();
		void react_startup_region_Ui_popup_PopupManager_Zone4_NoPopup();
		void react_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_popup_timer_region_PopupTimerState();
		void react_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_ShortcutDrawerMinimizedState();
		void react_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_SourceDrawerMaximizedState_source_drawer_maximized_region_SourceDrawerTimerState();
		void react_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState_hvac_drawer_maximized_region_HVACDrawerTimerState();
		void react_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMinimizedState();
		void react_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMaximizedState_qad_drawer_maximized_region_QADTimerState();
		void react_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_status_bar_region_StatusBarState();
		void react_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersHiddenState();
		void react_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_HideVolumeOverlay();
		void react_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_ShowVolumeOverlay_volume_overlay_show_region_VolOverlayTimerState();
		void react_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_HideHvacOverlay();
		void react_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_ShowHvacOverlay_hvac_show_overlay_regioin_HvacOverlayTimerState();
		void react_startup_region_StartupAnimation();
		void react_startup_region_Ui_home_Main_main_Home_home__choice_0();
		void react_startup_region_Ui_home_Main_main_PowerMode_Powermodes__choice_0();
		void react_startup_region_Ui_home_Main_main_AndroidAuto_aa_region__choice_0();
		void react_startup_region_Ui_home_Main_main_CarPlay_carplay_region__choice_0();
		void react_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region__choice_0();
		void react_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region__choice_1();
		void react_startup_region_Ui_home_Main_main__choice_0();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region__choice_0();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain__choice_0();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio__choice_0();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main__choice_0();
		void react_startup_region_Ui_home_Main_main__choice_1();
		void react_startup_region_Ui_home_Main_main__choice_2();
		void react_startup_region_Ui_home_Main_main__choice_3();
		void react_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region__choice_0();
		void react_startup_region_Ui_home__choice_0();
		void react_startup_region_Ui_drawer_DrawerManager_drawers_main_region__choice_0();
		void react_startup_region__choice_0();
		void react_startup_region_Ui_home_PDC_active_pdc_region__entry_Default();
		void react_startup_region_Ui_home_Main_main_Home_home__entry_Default();
		void react_startup_region_Ui_home_Main_main_PowerMode_Powermodes__entry_Default();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_entry_VehicleSetup();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region__entry_Default();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_entry_MoodLight();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_entry_BTSetup();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_entry_GeneralSetup();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_entry_VolumeSetup();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_entry_PairDevices();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_entry_DisplaySetup();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup_audioSetup_region__entry_Default();
		void react_startup_region_Ui_home_Main_main_Setup_setup_region_entry_AudioSetup();
		void react_startup_region_Ui_home_Main_main_EnggMenu_engg_region__entry_Default();
		void react_startup_region_Ui_home_Main_main_EnggMenu_engg_region_Illumination_TestMode__entry_Default();
		void react_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__entry_Default();
		void react_startup_region_Ui_home_Main_main_EnggMenu_engg_region_SystemConfig_SystemConfiguration__16RPart__16RPartNo__entry_Default();
		void react_startup_region_Ui_home_Main_main_AndroidAuto_aa_region__entry_Default();
		void react_startup_region_Ui_home_Main_main_CarPlay_carplay_region__entry_Default();
		void react_startup_region_Ui_home_Main_main_SAL_sal_region__entry_Default();
		void react_startup_region_Ui_home_Main_main_SoftwareUpdate_swupdate_region__entry_Default();
		void react_startup_region_Ui_home_Main_main__entry_Default();
		void react_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region__entry_Default();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region__entry_Default();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaBrowseMain_MediaBrowseMain__entry_Default();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio__entry_Default();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region__entry_Default();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Tuner_tuner_region_TunerMain_tuner_main__entry_Default();
		void react_startup_region_Ui_home_Main_main_VRHelp_vr_region__entry_Default();
		void react_startup_region_Ui_home__entry_Default();
		void react_startup_region_Ui_home_PhoneCall_phone_call_region__entry_Default();
		void react_startup_region_Ui_home_PhoneCall_phone_call_region_PhoneCallBrowse_phoneBrowse_region__entry_Default();
		void react_startup_region_Ui_popup__entry_Default();
		void react_startup_region_Ui_popup_PopupManager_Zone2__entry_Default();
		void react_startup_region_Ui_popup_PopupManager_Zone2_NotificationActive_notification_timer_region__entry_Default();
		void react_startup_region_Ui_popup_PopupManager_Zone4__entry_Default();
		void react_startup_region_Ui_popup_PopupManager_Zone4_PopupActive_popup_timer_region__entry_Default();
		void react_startup_region_Ui_drawer__entry_Default();
		void react_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region__entry_Default();
		void react_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_SourceDrawerMaximizedState_source_drawer_maximized_region__entry_Default();
		void react_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState_hvac_drawer_maximized_region__entry_Default();
		void react_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region__entry_Default();
		void react_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_qad_drawer_visible_region_QuickAccessDrawerMaximizedState_qad_drawer_maximized_region__entry_Default();
		void react_startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_status_bar_region__entry_Default();
		void react_startup_region_Ui_drawer_DrawerManager_drawers_main_region__entry_Default();
		void react_startup_region_Ui_drawer_DrawerManager_volume_overlay_region__entry_Default();
		void react_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region__entry_Default();
		void react_startup_region_Ui_drawer_DrawerManager_volume_overlay_region_VolumeOverlay_vol_overlay_region_ShowVolumeOverlay_volume_overlay_show_region__entry_Default();
		void react_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region__entry_Default();
		void react_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region__entry_Default();
		void react_startup_region_Ui_drawer_DrawerManager_hvac_overlay_region_HvacOverlay_hvac_overlay_region_ShowHvacOverlay_hvac_show_overlay_regioin__entry_Default();
		void react_startup_region__entry_Default();
		void react_startup_region_Ui_home_Main_main_PowerMode_Powermodes_exit_null1();
		void react_startup_region_Ui_home_Main_main_AndroidAuto_aa_region_exit_AAProjectionNotActive();
		void react_startup_region_Ui_home_Main_main_CarPlay_carplay_region_exit_CarPlayProjNotActive();
		void react_startup_region_Ui_home_Main_main_Phone_phoneBrowse_region_exit_null1();
		void react_startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_exit_null2();
		void clearInEvents();
		void clearOutEvents();
		
		
	private:
		std::deque<tml_hmi_sm_events::SctEvent*> internalEventQueue;
		
		tml_hmi_sm_events::SctEvent* getNextEvent();
		
		void dispatch_event(tml_hmi_sm_events::SctEvent * event);
};

inline TML_HMI_SM::SCI_Skeleton_OCB::~SCI_Skeleton_OCB() {}
inline TML_HMI_SM::SCI_Ui_OCB::~SCI_Ui_OCB() {}
inline TML_HMI_SM::SCI_MediaOff_OCB::~SCI_MediaOff_OCB() {}
inline TML_HMI_SM::SCI_Startup_OCB::~SCI_Startup_OCB() {}
inline TML_HMI_SM::SCI_Home_OCB::~SCI_Home_OCB() {}
inline TML_HMI_SM::SCI_Phone_OCB::~SCI_Phone_OCB() {}
inline TML_HMI_SM::SCI_EnggMenu_OCB::~SCI_EnggMenu_OCB() {}
inline TML_HMI_SM::SCI_AndroidAuto_OCB::~SCI_AndroidAuto_OCB() {}
inline TML_HMI_SM::SCI_CarPlay_OCB::~SCI_CarPlay_OCB() {}
inline TML_HMI_SM::SCI_SAL_OCB::~SCI_SAL_OCB() {}
inline TML_HMI_SM::SCI_SoftwareUpdate_OCB::~SCI_SoftwareUpdate_OCB() {}
inline TML_HMI_SM::SCI_Setup_OCB::~SCI_Setup_OCB() {}
inline TML_HMI_SM::SCI_Media_OCB::~SCI_Media_OCB() {}
inline TML_HMI_SM::SCI_Tuner_OCB::~SCI_Tuner_OCB() {}
inline TML_HMI_SM::SCI_TunerService_OCB::~SCI_TunerService_OCB() {}
inline TML_HMI_SM::SCI_ParkAssit_OCB::~SCI_ParkAssit_OCB() {}
inline TML_HMI_SM::SCI_HardKey_OCB::~SCI_HardKey_OCB() {}
inline TML_HMI_SM::SCI_Drawers_OCB::~SCI_Drawers_OCB() {}
inline TML_HMI_SM::SCI_Popup_OCB::~SCI_Popup_OCB() {}
inline TML_HMI_SM::SCI_Vr_OCB::~SCI_Vr_OCB() {}


#endif /* TML_HMI_SM_H_ */
