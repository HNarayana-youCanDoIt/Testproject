/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CVoiceAlertsAdaptor.cpp
 * @ingroup       HMIComponent
 * @author        Guru Alingal
 * CVoiceAlertsAdapter, Class to adapt the voice alert data and mceData into platform sepecific
 * changes and to handle voice alert related fetures.
 */

#include "CVoiceAlertsAdaptor.h"
#include "CPopupManager.h"
#include "CFramework.h"
#include "logging.h"
#include "CSetupAdaptor.h"
#include "CVariantControlAdaptor.h"
#include "ResourceFactory.hpp"

CVoiceAlertsAdaptor* CVoiceAlertsAdaptor::m_spInst = NULL;

CVoiceAlertsAdaptor::CVoiceAlertsAdaptor() :
    m_pVoiceAlertsResource(ResourceFactory::getVoiceAlertResource()),
    m_bVoiceAlertSelection(false),
    m_bVoiceAlertPresence(false)

{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s", __FUNCTION__);
    CFramework::getFramework().setContextProperty("cppVoiceAlertsAdaptor", this);

    initVoiceAlertsList();
    m_eCurrAlert = static_cast<CVoiceAlertsEnums::EVoiceAlerts>(ResourceFactory::getVoiceAlertResource()->getCurrentVoiceAlert());
    m_eCurrMceAlert = static_cast<CVoiceAlertsEnums::EMceVoiceAlerts>(ResourceFactory::getVoiceAlertResource()->getCurrentMceVoiceAlert());
    m_eCurrAlertState = static_cast<CVoiceAlertsEnums::EVoiceAlertsState>(ResourceFactory::getVoiceAlertResource()->getCurrentState());
}

void CVoiceAlertsAdaptor::initVoiceAlertsList()
{
    m_mapAvailVoiceAlerts.clear();
    m_mapAvailMceVoiceAlerts.clear();


    CDataVoiceAert data;
    CDataMceVoiceAert mceData;

    //// TATA_X104_High_VAVE specific code
    data.m_eId = CVoiceAlertsEnums::EN_VA_NOALERT									   ; data.m_strMsg = ""									;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_AUTO_MODE                                    ; data.m_strMsg = "Auto Drive Mode activated"		;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_COMFORT_MODE                                 ; data.m_strMsg = "Comfort Drive Mode activated"		;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_DYNAMIC_MODE                                 ; data.m_strMsg = "Dynamic Drive Mode activated"		;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_ROUGH_ROAD_MODE                              ; data.m_strMsg = "Rough Road Mode activated"		;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_CITY_MODE                                    ; data.m_strMsg = "City Drive Mode activated"		;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_SPORT_MODE                                   ; data.m_strMsg = "Sport Drive Mode activated"		;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_ECONOMY_MODE                                 ; data.m_strMsg = "Economy Drive Mode activated"		;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_DOOR_OPEN_GENERAL_WARNING                    ; data.m_strMsg = "One of the Doors open"			;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_DRIVER_DOOR_OPEN                             ; data.m_strMsg = "Driver Door open"					;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_CO_DRIVER_DOOR_OPEN                          ; data.m_strMsg = "Co-Driver Door open"				;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_REAR_RIGHT_DOOR_OPEN                         ; data.m_strMsg = "Right rear Door open"				;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_REAR_LEFT_DOOR_OPEN                          ; data.m_strMsg = "Left rear Door open"				;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_TAIL_GATE_OPEN                               ; data.m_strMsg = "Tail gate open"					;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_FASTEN_SEAT_BELT_DRIVER                      ; data.m_strMsg = "Fasten Driver seat belt"			;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_PARK_BRAKE_ENGAGED                           ; data.m_strMsg = "Park Brake Engaged"				;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_LOW_TIRE_PRESSURE_ALERT_FR                   ; data.m_strMsg = "Low Tyre Pressure"				;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_LOW_TIRE_PRESSURE_ALERT_FL                   ; data.m_strMsg = "Low Tyre Pressure"				;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_LOW_TIRE_PRESSURE_ALERT_RR                   ; data.m_strMsg = "Low Tyre Pressure"				;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_LOW_TIRE_PRESSURE_ALERT_RL                   ; data.m_strMsg = "Low Tyre Pressure"				;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_FUEL_LEVEL_LOW_STATE                         ; data.m_strMsg = "Low Fuel level"					;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_LOW_BRAKE_FLUID                              ; data.m_strMsg = "Low Brake Fluid"					;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_ENGINE_OIL_PRESSURE_LOW_STATE                ; data.m_strMsg = "Low Oil Pressure"					;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_WATER_IN_FUEL                                ; data.m_strMsg = "Water in Fuel"					;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_KEY_SERVICE_REMINDER                         ; data.m_strMsg = "Service Reminder"					;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_KEY_FOB_BATTERY_LOW                          ; data.m_strMsg = "Smart Key Battery Low"			;   m_mapAvailVoiceAlerts[data.m_eId] = data;
    data.m_eId = CVoiceAlertsEnums::EN_VA_SMART_KEY_OUT_OF_RANGE                       ; data.m_strMsg = "Smart key not in vehicle"			;   m_mapAvailVoiceAlerts[data.m_eId] = data;

    //// MCE specific code
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_NOALERT									  ; mceData.m_strMsg = ""                                                       ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_AUTO_MODE                                    ; mceData.m_strMsg = "Auto Drive Mode activated"                              ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_COMFORT_MODE                                 ; mceData.m_strMsg = "Comfort Drive Mode activated"                           ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_DYNAMIC_MODE                                 ; mceData.m_strMsg = "Dynamic Drive Mode activated"                           ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_ROUGH_ROAD_MODE                              ; mceData.m_strMsg = "Rough Road Mode activated"                              ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_CITY_MODE                                    ; mceData.m_strMsg = "City Drive Mode activated"                              ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_SPORT_MODE                                   ; mceData.m_strMsg = "Sport Drive Mode activated"                             ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_ECONOMY_MODE                                 ; mceData.m_strMsg = "Economy Drive Mode activated"                           ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_WET_MODE                                     ; mceData.m_strMsg = "Wet Mode activated"                                     ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_MUD                                          ; mceData.m_strMsg = "Mud Mode activated"                                     ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_SAND                                         ; mceData.m_strMsg = "Sand Mode activated"                                    ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_GRASS                                        ; mceData.m_strMsg = "Snow Mode activated"                                    ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_DOOR_OPEN_GENERAL_WARNING                    ; mceData.m_strMsg = "One of the Doors open"                                  ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_DRIVER_DOOR_OPEN                             ; mceData.m_strMsg = "Driver Door open"                                       ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_CO_DRIVER_DOOR_OPEN                          ; mceData.m_strMsg = "Co-Driver Door open"                                    ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_REAR_RIGHT_DOOR_OPEN                         ; mceData.m_strMsg = "Right rear Door open"                                   ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_REAR_LEFT_DOOR_OPEN                          ; mceData.m_strMsg = "Left rear Door open"                                    ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_TAIL_GATE_OPEN                               ; mceData.m_strMsg = "Tail gate open"                                         ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_FASTEN_SEAT_BELT_DRIVER                      ; mceData.m_strMsg = "Fasten Driver seat belt"                                ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_HDC_DEACTIVATION_DUE_TO_SPEED_ABOVE_SET_VALUE; mceData.m_strMsg = "Hill Descent Control Deactivated"                       ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_HDC_ACTIVATED                                ; mceData.m_strMsg = "Hill Descent Control Activated"                         ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_PARK_BRAKE_ENGAGED                           ; mceData.m_strMsg = "Park Brake Engaged"                                     ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_LOW_BRAKE_FLUID                              ; mceData.m_strMsg = "Low Brake Fluid"                                        ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_LOW_SOC_INDICATION                           ; mceData.m_strMsg = "Low Battery Charge"                                     ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_TPMS_GENERAL_WARNING                         ; mceData.m_strMsg = "TPMS System error"                                      ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_LOW_TIRE_PRESSURE_ALERT_FL                   ; mceData.m_strMsg = "Low Tyre Pressure"                                      ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_LOW_TIRE_PRESSURE_ALERT_FR                   ; mceData.m_strMsg = "Low Tyre Pressure"                                      ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_LOW_TIRE_PRESSURE_ALERT_RL                   ; mceData.m_strMsg = "Low Tyre Pressure"                                      ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_LOW_TIRE_PRESSURE_ALERT_RR                   ; mceData.m_strMsg = "Low Tyre Pressure"                                      ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_LOW_TIRE_PRESSURE_ALERT_SPARE                ; mceData.m_strMsg = "Low Tyre Pressure"                                      ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_HIGH_TIRE_PRESSURE_ALERT_FL                  ; mceData.m_strMsg = "High Tyre Pressure"                                     ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_HIGH_TIRE_PRESSURE_ALERT_FR                  ; mceData.m_strMsg = "High Tyre Pressure"                                     ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_HIGH_TIRE_PRESSURE_ALERT_RL                  ; mceData.m_strMsg = "High Tyre Pressure"                                     ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_HIGH_TIRE_PRESSURE_ALERT_RR_                 ; mceData.m_strMsg = "High Tyre Pressure"                                     ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_HIGH_TIRE_PRESSURE_ALERT_SPARE               ; mceData.m_strMsg = "High Tyre Pressure"                                     ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_HIGH_TIRE_TEMP_ALERT_FL                      ; mceData.m_strMsg = "High Tyre Temperature"                                  ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_HIGH_TIRE_TEMP_ALERT_FR                      ; mceData.m_strMsg = "High Tyre Temperature"                                  ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_HIGH_TIRE_TEMP_ALERT_RL                      ; mceData.m_strMsg = "High Tyre Temperature"                                  ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_HIGH_TIRE_TEMP_ALERT_RR                      ; mceData.m_strMsg = "High Tyre Temperature"                                  ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_HIGH_TIRE_TEMP_ALERT_SPARE                   ; mceData.m_strMsg = "High Tyre Temperature"                                  ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_PRESSURE_LEAKAGE_ALERT_FL                    ; mceData.m_strMsg = "Tyre Pressure Leak"                                     ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_PRESSURE_LEAKAGE_ALERT_FR                    ; mceData.m_strMsg = "Tyre Pressure Leak"                                     ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_PRESSURE_LEAKAGE_ALERT_RL                    ; mceData.m_strMsg = "Tyre Pressure Leak"                                     ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_PRESSURE_LEAKAGE_ALERT_RR                    ; mceData.m_strMsg = "Tyre Pressure Leak"                                     ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_PRESSURE_LEAKAGE_ALERT_SPARE_                ; mceData.m_strMsg = "Tyre Pressure Leak"                                     ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_FORWARD_COLLISION_WARNING_INDICATION         ; mceData.m_strMsg = "Object ahead, please brake"                             ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_CRUISE_ACTIVATED                             ; mceData.m_strMsg = "Cruise activated"                                       ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_SERVICE_REMINDER_DAYS                        ; mceData.m_strMsg = "Service Due"                                            ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_SERVICE_REMINDER_KMS                         ; mceData.m_strMsg = "Service Due"                                            ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_FUEL_FILTER_CLOGGING                         ; mceData.m_strMsg = "Fuel Filter Clogged"                                    ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_ENGINE_OIL_PRESSURE_LOW_STATE                ; mceData.m_strMsg = "Low Oil Pressure"                                       ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_FUEL_LEVEL_LOW_STATE                         ; mceData.m_strMsg = "Low Fuel level"                                         ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_DRIVE_ALERT1_TEA_BREAK                       ; mceData.m_strMsg = "Tea Break"                                              ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_WATER_IN_FUEL                                ; mceData.m_strMsg = "Water in Fuel"                                          ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_KEY_FOB_BATTERY_LOW                          ; mceData.m_strMsg = "Smart Key Battery Low"                                  ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_FASTEN_SEAT_BELT_CO_DRIVER                   ; mceData.m_strMsg = "Fasten Passenger seat belt"                             ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_CRUISE_ON                                    ; mceData.m_strMsg = "Cruise ON! Set the Speed"                               ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_KEY_NOT_FOUND                                ; mceData.m_strMsg = "Key Not Found"                                          ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_EXPRESS_COOLING_ON                           ; mceData.m_strMsg = "Express Cooling On"                                     ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_EXPRESS_COOLING_OFF                          ; mceData.m_strMsg = "Express Cooling Off"                                    ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_EXPRESS_COOLING_ON_WINDOWS_ROLL_DOWN         ; mceData.m_strMsg = "Express Cooling On windows may roll Down"               ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_EXPRESS_COOLING_OFF_WINDOWS_ROLL_UP          ; mceData.m_strMsg = "Express Cooling Off windows may roll Up if Down"        ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_ROLL_UP_WINDOWS                              ; mceData.m_strMsg = "Roll Up the windows if Down"                            ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;
    mceData.m_eId = CVoiceAlertsEnums::EN_MCE_VA_LOW_AMBIENT_TEMPERATURE                      ; mceData.m_strMsg = "Low Ambient Temperature. It’s Already Cold Outside"     ;   m_mapAvailMceVoiceAlerts[mceData.m_eId] = mceData;

    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS,"%s: no. of voice alerts: %zd, no. of mce voice alerts: %zd",
             __FUNCTION__, m_mapAvailVoiceAlerts.size(), m_mapAvailMceVoiceAlerts.size());

}

CVoiceAlertsEnums::EVoiceAlerts CVoiceAlertsAdaptor::getECurrAlert() const
{
    return m_eCurrAlert;
}

void CVoiceAlertsAdaptor::setECurrAlert(int iCurrAlert)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s - Voice Alert Received: %d", __FUNCTION__, m_eCurrAlert);
    CVoiceAlertsEnums::EVoiceAlerts eCurrAlert = static_cast<CVoiceAlertsEnums::EVoiceAlerts>(iCurrAlert);
    if((eCurrAlert > CVoiceAlertsEnums::EN_VA_NOALERT) && (eCurrAlert <= m_mapAvailVoiceAlerts.size() - 1))
    {
        //Voice alert shall be displayed when status is set to 'In-Process'
        m_eCurrAlert = eCurrAlert;
    }
    else
    {
        m_eCurrAlert = CVoiceAlertsEnums::EN_VA_NOALERT;
    }
}

CVoiceAlertsEnums::EMceVoiceAlerts CVoiceAlertsAdaptor::getEMceCurrAlert() const
{
    return m_eCurrMceAlert;
}

void CVoiceAlertsAdaptor::setECurrMceAlert(int iCurrMceAlert)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s - Mce Voice Alert Received: %d", __FUNCTION__, m_eCurrMceAlert);
    CVoiceAlertsEnums::EMceVoiceAlerts eCurrMceAlert = static_cast<CVoiceAlertsEnums::EMceVoiceAlerts>(iCurrMceAlert);
    if((eCurrMceAlert > CVoiceAlertsEnums::EN_MCE_VA_NOALERT) && (eCurrMceAlert <= m_mapAvailMceVoiceAlerts.size() - 1))
    {
        //Voice alert shall be displayed when status is set to 'In-Process'
        m_eCurrMceAlert = eCurrMceAlert;
    }
    else
    {
        m_eCurrMceAlert = CVoiceAlertsEnums::EN_MCE_VA_NOALERT;
    }
}

void CVoiceAlertsAdaptor::setVoiceAlertSelection(bool bVoiceAlertSelection)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS,"%s Voice alert selection :%d", __FUNCTION__, bVoiceAlertSelection);
    if(bVoiceAlertSelection != m_bVoiceAlertSelection)
    {
        m_bVoiceAlertSelection = bVoiceAlertSelection;
        emit sigVoiceAlertSelectionChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s - Values are same: ", __FUNCTION__);
    }
}

void CVoiceAlertsAdaptor::driveModeUpdate(CVoiceAlertsEnums::EDriveModes eDriveMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s drive mode :%d", __FUNCTION__, eDriveMode);
    int iDriveModeStatus = CVariantControlAdaptor::getInstance()->eolDriveModeStatusData();
    if((iDriveModeStatus & CVoiceAlertsEnums::DRIVE_MODE_ENABLE_STATE) == CVoiceAlertsEnums::DRIVE_MODE_ENABLE_STATE)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s, drive mode available, iDriveModeStatus :%d", __FUNCTION__, iDriveModeStatus);

        CVoiceAlertsEnums::EDriveModesStates eDriveModeState = CVoiceAlertsEnums::DRIVE_MODE_STATE_INVALID;
        CSetupEnums::EDriveModes eCurrDriveMode = CSetupEnums::DRIVE_MODE_INVALID;

        switch(eDriveMode)
        {
        case CVoiceAlertsEnums::DRIVE_MODE_CITY_MANUAL:
            eCurrDriveMode = CSetupEnums::DRIVE_MODE_CITY;
            eDriveModeState = CVoiceAlertsEnums::DRIVE_MODE_CITY_MANUAL_STATE;
            break;
        case CVoiceAlertsEnums::DRIVE_MODE_SPORT_MANUAL:
            eCurrDriveMode = CSetupEnums::DRIVE_MODE_SPORT;
            eDriveModeState = CVoiceAlertsEnums::DRIVE_MODE_SPORT_MANUAL_STATE;
            break;
        case CVoiceAlertsEnums::DRIVE_MODE_ECONOMY_MANUAL:
            eCurrDriveMode = CSetupEnums::DRIVE_MODE_ECO;
            eDriveModeState = CVoiceAlertsEnums::DRIVE_MODE_ECONOMY_MANUAL_STATE;
            break;
        case CVoiceAlertsEnums::DRIVE_MODE_CITY_AUTO:
            eCurrDriveMode = CSetupEnums::DRIVE_MODE_CITY;
            eDriveModeState = CVoiceAlertsEnums::DRIVE_MODE_CITY_AUTO_STATE;
            break;
        case CVoiceAlertsEnums::DRIVE_MODE_SPORT_AUTO:
            eCurrDriveMode = CSetupEnums::DRIVE_MODE_SPORT;
            eDriveModeState = CVoiceAlertsEnums::DRIVE_MODE_SPORT_AUTO_STATE;
            break;
        case CVoiceAlertsEnums::DRIVE_MODE_ECONOMY_AUTO:
            eCurrDriveMode = CSetupEnums::DRIVE_MODE_ECO;
            eDriveModeState = CVoiceAlertsEnums::DRIVE_MODE_ECONOMY_AUTO_STATE;
            break;
        case CVoiceAlertsEnums::DRIVE_MODE_CITY_TIPTRONIC:
            eCurrDriveMode =CSetupEnums::DRIVE_MODE_CITY;
            eDriveModeState = CVoiceAlertsEnums::DRIVE_MODE_CITY_TIPTRONIC_STATE;
            break;
        case CVoiceAlertsEnums::DRIVE_MODE_SPORT_TIPTRONIC:
            eCurrDriveMode = CSetupEnums::DRIVE_MODE_SPORT;
            eDriveModeState = CVoiceAlertsEnums::DRIVE_MODE_SPORT_TIPTRONIC_STATE;
            break;
        case CVoiceAlertsEnums::DRIVE_MODE_ECONOMY_TIPTRONIC:
            eCurrDriveMode = CSetupEnums::DRIVE_MODE_ECO;
            eDriveModeState = CVoiceAlertsEnums::DRIVE_MODE_ECONOMY_TIPTRONIC_STATE;
            break;
        default:
            // do nothing
            break;
        }

        if((iDriveModeStatus & eDriveModeState) == eDriveModeState)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s setting drive mode eCurrDriveMode :%d", __FUNCTION__, eCurrDriveMode);
            CSetupAdaptor::getInstance()->setActiveDriveMode(eCurrDriveMode);
        }
    }
}

void CVoiceAlertsAdaptor::setVoiceAlertPresence(bool bVoiceAlertPresence)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS,"%s Voice alert Presence :%d", __FUNCTION__, bVoiceAlertPresence);
    if(bVoiceAlertPresence != m_bVoiceAlertPresence)
    {
        m_bVoiceAlertPresence = bVoiceAlertPresence;
        emit sigVoiceAlertPresenceChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s - Values are same: ", __FUNCTION__);
    }
}

void CVoiceAlertsAdaptor::setVoiceAlertSelectionAttribute(bool bVoiceAlertSelection)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS,"%s Set Voice alert selection :%d", __FUNCTION__, bVoiceAlertSelection);
    if(m_pVoiceAlertsResource)
    {
        m_pVoiceAlertsResource->setVoiceAlertSelection(bVoiceAlertSelection);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SETTINGS,"%s, Vehicle Resource is null", __FUNCTION__);
    }
}

CVoiceAlertsEnums::EVoiceAlertsState CVoiceAlertsAdaptor::getECurrAlertState() const
{
    return m_eCurrAlertState;
}

void CVoiceAlertsAdaptor::setECurrAlertState(const CVoiceAlertsEnums::EVoiceAlertsState &eCurrAlertState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s: eCurrAlertState: %d", __FUNCTION__, eCurrAlertState);
    m_eCurrAlertState = eCurrAlertState;
    processVoiceAlerts();
}

CVoiceAlertsAdaptor::~CVoiceAlertsAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s", __FUNCTION__);
}

CVoiceAlertsAdaptor& CVoiceAlertsAdaptor::getInstance()
{
    if(NULL == m_spInst)
    {
        m_spInst = new CVoiceAlertsAdaptor();
    }
    return *m_spInst;
}

void CVoiceAlertsAdaptor::processVoiceAlerts()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s: m_eCurrAlertState: %d", __FUNCTION__, m_eCurrAlertState);
    if(m_eCurrAlertState == CVoiceAlertsEnums::EN_VA_STATE_IN_PROCESS)
    {
        CVariantControlEnum::EVIP_DID eVIP_DID = CVariantControlAdaptor::getInstance()->eolVIP_DID();
        LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s: eVIP_DID: %d", __FUNCTION__, eVIP_DID);
        if(CVariantControlEnum::VIP_DID_HU_NEXON_LEVEL_B_VAVE == eVIP_DID)
        {
            if(CVoiceAlertsEnums::EN_VA_NOALERT != m_eCurrAlert)
            {
                displayVoiceAlert(m_eCurrAlert);
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s - No alert OR wrong alert received hence process req is ignored", __FUNCTION__);
            }
        }
        else
        {
            if(CVoiceAlertsEnums::EN_MCE_VA_NOALERT != m_eCurrMceAlert)
            {
                //This is the default handling for x445
                displayMceVoiceAlert(m_eCurrMceAlert);
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s - No Mce alert OR wrong Mce alert received hence process req is ignored", __FUNCTION__);
            }
        }
    }
    else
    {
        closeVoiceAlert();
    }
}


bool CVoiceAlertsAdaptor::displayVoiceAlert(CVoiceAlertsEnums::EVoiceAlerts eVoiceAlert)
{
    bool bRet = false;

    std::map<CVoiceAlertsEnums::EVoiceAlerts, CDataVoiceAert>::iterator it = m_mapAvailVoiceAlerts.find(eVoiceAlert);
    if((it != m_mapAvailVoiceAlerts.end()) &&
            ("" != it->second.m_strMsg))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, " %s Displaying voice alert %d ", __FUNCTION__, eVoiceAlert);
        updateVAMsg(it->second.m_strMsg);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_VOICE_ALERT_NOTIFICATION);
        bRet = true;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, " %s Invalid voice alert received %d ", __FUNCTION__, eVoiceAlert);
        //Do Nothing
    }

    return bRet;
}

bool CVoiceAlertsAdaptor::displayMceVoiceAlert(CVoiceAlertsEnums::EMceVoiceAlerts eMceVoiceAlert)
{
    bool bRet = false;

    std::map<CVoiceAlertsEnums::EMceVoiceAlerts, CDataMceVoiceAert>::iterator it = m_mapAvailMceVoiceAlerts.find(eMceVoiceAlert);
    if((it != m_mapAvailMceVoiceAlerts.end()) &&
            ("" != it->second.m_strMsg))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, " %s Displaying Mce voice alert %d ", __FUNCTION__, eMceVoiceAlert);
        updateVAMsg(it->second.m_strMsg);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_VOICE_ALERT_NOTIFICATION);
        bRet = true;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, " %s Invalid Mce voice alert received %d ", __FUNCTION__, eMceVoiceAlert);
        //Do Nothing
    }

    return bRet;
}

bool CVoiceAlertsAdaptor::closeVoiceAlert()
{
    CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_VOICE_ALERT_NOTIFICATION);
    return true;
}

QString CVoiceAlertsAdaptor::strVAMsg()
{
    return m_strVAMsg;
}

void CVoiceAlertsAdaptor::updateVAMsg(QString strMsg)
{
    if(m_strVAMsg != strMsg)
    {
        m_strVAMsg = strMsg;
        emit sigVAMsgChanged();
    }
}

