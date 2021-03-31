/*********************************************************************
* Project         Presentation Control Core
* (c) copyright   2016
* Company         Harman International
*                 All rights reserved
*********************************************************************/
/**
* @file            logging.h
* @ingroup         presctrlcore
* @author          Ankur Tibrewal (ankur.tibrewal@harman.com)
* @brief           Logging abstraction. Ensures DLT is used on Linux, stdout on Windows.
*/

#ifndef LOGGING_H
#define LOGGING_H

#include <cstdio>
#include <iostream>
#include <stdint.h>
#include <unordered_map>

#define CPP_UNUSED(expr) (void)(expr)

#define LOG_INFO(A,B,...)            { char LogBuffer[1024];snprintf(LogBuffer,1024, B, ## __VA_ARGS__) ; Log::log_message(A,LogBuffer); }
#define LOG_DEBUG(A,B,...)           { char LogBuffer[1024];snprintf(LogBuffer,1024, B, ## __VA_ARGS__) ; Log::log_message(A,LogBuffer); }
#define LOG_WARNING(A,B,...)         { char LogBuffer[1024];snprintf(LogBuffer,1024, B, ## __VA_ARGS__) ; Log::log_message(A,LogBuffer); }
#define LOG_ERROR(A,B,...)           { char LogBuffer[1024];snprintf(LogBuffer,1024, B, ## __VA_ARGS__) ; Log::log_message(A,LogBuffer); }


class Log
{
public:
    enum eLogContextType
    {
        e_LOG_CONTEXT_MAIN = 1u,
        e_LOG_CONTEXT_PERSISTENCY,
        e_LOG_CONTEXT_MEDIA_OFF,
        e_LOG_CONTEXT_HOME,
        e_LOG_CONTEXT_ENGG_MENU,
        e_LOG_CONTEXT_TUNER,
        e_LOG_CONTEXT_AUDIO,
        e_LOG_CONTEXT_PROJECTION,
        e_LOG_CONTEXT_SETTINGS,
        e_LOG_CONTEXT_DRIVENEXT,
        e_LOG_CONTEXT_PHONE,
        e_LOG_CONTEXT_PHONE_BOOK,
        e_LOG_CONTEXT_MEDIA,
        e_LOG_CONTEXT_DRAWERS,
        e_LOG_CONTEXT_NAV_MAP,
        e_LOG_MODEMANAGER,
        e_LOG_CONTEXT_STATUSBAR,
        e_LOG_CONTEXT_SYSTEM,
        e_LOG_CONTEXT_POPUP,
        e_LOG_CONTEXT_NOTIFICATION,
        e_LOG_CONTEXT_WEIGHTINFO,
        e_LOG_CONTEXT_TIME_MANAGER,
        e_LOG_CONTEXT_AHA,
        e_LOG_CONTEXT_DISPLAY_CONTROL,
        e_LOG_CONTEXT_SECURITY_MANAGER,
        e_LOG_CONTEXT_LAYER_MANAGER,
        e_LOG_CONTEXT_HARDKEYS,
        e_LOG_CONTEXT_SOFTWARE_UPDATE,
        e_LOG_CONTEXT_POWER_MODE,
        e_LOG_CONTEXT_HVAC,
        e_LOG_CONTEXT_PARKASSIST,
        e_LOG_CONTEXT_VEHICLE,
        e_LOG_CONTEXT_VOICE_ALERTS,
        e_LOG_CONTEXT_VERSION_MANAGER,
        e_LOG_CONTEXT_DIAGNOSTIC,
        e_LOG_CONTEXT_VR,
        e_LOG_CONTEXT_VARIANT_CONTROL,
        e_LOG_CONTEXT_INTROSPECTION,
        e_LOG_CONTEXT_RCA,
        e_LOG_CONTEXT_ICCAST,
        e_LOG_CONTEXT_W3W,
        e_LOG_CONTEXT_DOODLE,
        e_LOG_CONTEXT_SOUNDDEMO,
        e_LOG_CONTEXT_INVALID
    };

    /**
    * Call this method once to initialize the logging related data structures.
    * 0 is reserved for Core in the Context map passed. User must use 1 as the starting point for Context ID.
    */
    static void initLogging(const char* AppName,const char* AppDesc,const std::unordered_map <uint16_t,const char* > & );

    /**
    * Can be called directly by the user with the log message, and the ID. But, use of logging macros is highly recommended.
    */
    static void log_message(uint16_t type,const char* str);

    static const uint16_t e_LOG_CONTEXT_CORE = 0u;

private :
    static std::unordered_map <uint16_t, const char* > mContextMap;



};

#endif // LOGGING_H
