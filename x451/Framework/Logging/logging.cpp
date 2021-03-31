#include <logging.h>

#ifdef PLATFORM_WIN32
#include <iostream>
#include <QDebug>
#include <QTime>
using namespace std;
#else
#include <dlt/dlt.h>
#endif

std::unordered_map <uint16_t, const char* > Log::mContextMap;

#ifndef PLATFORM_WIN32

struct t_DltData
{
    DltContext context;
    DltContextData contextdata;
};

t_DltData* DLT_DATA = nullptr;
#endif

void Log::initLogging(const char* AppName, const char* AppDesc, const std::unordered_map <uint16_t, const char* > & contextmap)
{
    mContextMap.insert(std::make_pair(0, "Core"));    
    auto it = contextmap.begin();

    while (it != contextmap.end())
    {
     mContextMap.insert(std::make_pair(it->first, it->second));
     it++;
    }

    size_t size = mContextMap.size();

#ifdef PLATFORM_WIN32
    CPP_UNUSED(AppName);
    CPP_UNUSED(AppDesc);
    CPP_UNUSED(size);
#else
        DLT_DATA = (t_DltData*)malloc(sizeof(t_DltData) * size );
    dlt_register_app(AppName,AppDesc);
    for (size_t i = 0; i < size; i++)
    {
        dlt_register_context(&DLT_DATA[i].context, Log::mContextMap[i], "Context");
    }
    dlt_verbose_mode();
#endif

}


void Log::log_message(uint16_t type, const char* str)
{
#ifdef PLATFORM_WIN32
    CPP_UNUSED(type);
    //std::cout << Log::mContextMap[type] << " " << str << std::endl;
    qDebug() <<QTime::currentTime() <<" : "<< str;
#else
    if (dlt_user_log_write_start(&DLT_DATA[type].context, &DLT_DATA[type].contextdata, DLT_LOG_WARN))
    {
        dlt_user_log_write_string(&DLT_DATA[type].contextdata, str);
        dlt_user_log_write_finish(&DLT_DATA[type].contextdata);
    }
#endif
}


