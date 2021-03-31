#include "HMIIncludes.h"
#include <QDebug>
#include <logging.h>
#include <QGuiApplication>


int main(int argc, char *argv[])
{
    std::unordered_map <uint16_t,const char* > mLog;
    mLog=
    {
        {Log::e_LOG_CONTEXT_MAIN,               "Main"              },
        {Log::e_LOG_CONTEXT_PERSISTENCY,        "Persistency"       },
        {Log::e_LOG_CONTEXT_MEDIA_OFF,          "MediaOff"          },
        {Log::e_LOG_CONTEXT_HOME,               "Home"              },
        {Log::e_LOG_CONTEXT_ENGG_MENU,          "EnggMenu"          },
        {Log::e_LOG_CONTEXT_TUNER,              "Tuner"             },
        {Log::e_LOG_CONTEXT_AUDIO,              "Audio"             },
        {Log::e_LOG_CONTEXT_PROJECTION,         "Projection"        },
        {Log::e_LOG_CONTEXT_SETTINGS,           "Settings"          },
        {Log::e_LOG_CONTEXT_DRIVENEXT,          "DriveNext"         },
        {Log::e_LOG_CONTEXT_PHONE,              "Phone"             },
        {Log::e_LOG_CONTEXT_PHONE_BOOK,         "PhoneBook"         },
        {Log::e_LOG_CONTEXT_MEDIA,              "Media"             },
        {Log::e_LOG_CONTEXT_DRAWERS,            "Drawers"           },
        {Log::e_LOG_CONTEXT_NAV_MAP,            "Navigation"        },
        {Log::e_LOG_MODEMANAGER,                "ModeManager"       },
        {Log::e_LOG_CONTEXT_STATUSBAR,          "Statusbar"         },
        {Log::e_LOG_CONTEXT_SYSTEM,             "System"            },
        {Log::e_LOG_CONTEXT_POPUP,              "Popup"             },
        {Log::e_LOG_CONTEXT_NOTIFICATION,       "Notification"      },
        {Log::e_LOG_CONTEXT_WEIGHTINFO,         "WeightInfo"        },
        {Log::e_LOG_CONTEXT_TIME_MANAGER,       "TimeInfo"          },
        {Log::e_LOG_CONTEXT_AHA,                "Aha"               },
        {Log::e_LOG_CONTEXT_DISPLAY_CONTROL,    "DisplayInfo"       },
        {Log::e_LOG_CONTEXT_SECURITY_MANAGER,   "TheftManagerinfo"  },
        {Log::e_LOG_CONTEXT_LAYER_MANAGER,      "LayerManager"      },
        {Log::e_LOG_CONTEXT_HARDKEYS,           "Hkey"              },
        {Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,    "SoftwareUpdate"    },
        {Log::e_LOG_CONTEXT_POWER_MODE,         "PMode"             },
        {Log::e_LOG_CONTEXT_HVAC,               "HVAC"              },
        {Log::e_LOG_CONTEXT_VEHICLE,            "Vehicle"           },
        {Log::e_LOG_CONTEXT_PARKASSIST,         "ParkAssist"        },
        {Log::e_LOG_CONTEXT_VOICE_ALERTS,       "VoiceAlerts"       },
        {Log::e_LOG_CONTEXT_VERSION_MANAGER,    "VersionManager"    },
        {Log::e_LOG_CONTEXT_VR,                 "VR"                },
        {Log::e_LOG_CONTEXT_INTROSPECTION,      "Introspection"     },
        {Log::e_LOG_CONTEXT_DIAGNOSTIC,         "Diagnostic"        },
        {Log::e_LOG_CONTEXT_VARIANT_CONTROL,    "VariantControl"    },
        {Log::e_LOG_CONTEXT_RCA,    		    "RCA"               },
        {Log::e_LOG_CONTEXT_ICCAST,             "ICCast"            },
        {Log::e_LOG_CONTEXT_W3W,                "W3W"               },
        {Log::e_LOG_CONTEXT_DOODLE,             "Doodle"            },
        {Log::e_LOG_CONTEXT_SOUNDDEMO,          "SDemo"             },
        {Log::e_LOG_CONTEXT_INVALID,            "INVA"              },
    };
    Log::initLogging("HMI","HMI app Log",mLog);
#ifdef PLATFORM_WIN32
    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
#endif
    QGuiApplication mApp(argc, argv);
    CHMIMain::startHMIApp();
    return mApp.exec();
}
