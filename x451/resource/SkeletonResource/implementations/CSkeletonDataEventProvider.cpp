#include "CSkeletonDataEventProvider.h"
#include "logging.h"

CSkeletonDataEventProvider::CSkeletonDataEventProvider(QObject *parent):
    QObject(parent)
{
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,__FUNCTION__);
}

CSkeletonDataEventProvider::~CSkeletonDataEventProvider()
{
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,__FUNCTION__);
}

void CSkeletonDataEventProvider::hardkeyEvent(int eventType)
{
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,__FUNCTION__);
    emit sigHardKeyEvent(eventType);
}

void CSkeletonDataEventProvider::updateDataType(int type)
{
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,__FUNCTION__);
    emit sigUpdateDataType(type);
}
