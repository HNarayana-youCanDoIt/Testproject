#include "CSkeletonResourceImpl.h"
#include <ResourceMaster.h>
#include "logging.h"

CSkeletonResourceImpl::CSkeletonResourceImpl():
    mpSkeletonDataEventProvider(new CSkeletonDataEventProvider()),
    mType(-1)
{
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,__FUNCTION__);
}

CSkeletonResourceImpl::~CSkeletonResourceImpl()
{
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,__FUNCTION__);
    if (mpSkeletonDataEventProvider)
        delete mpSkeletonDataEventProvider;
}

CSkeletonDataEventProvider* CSkeletonResourceImpl::getSkeletonDataEventProvider()
{
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,__FUNCTION__);
    return mpSkeletonDataEventProvider;
}

void CSkeletonResourceImpl::exampleReq()
{
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,__FUNCTION__);
    // make call to PresCtrl or Service Proxy
    if (-1 == mType )
        mType = 0;
    else
        mType = -1;
    //Simulating the Cb this would not be required when working with the actual presCtrl or proxy
    exmapleReqCb();
}

void CSkeletonResourceImpl::exmapleReqCb()
{
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,__FUNCTION__);
    // Propagate the information to the upper layers
    if (mpSkeletonDataEventProvider)
        mpSkeletonDataEventProvider->updateDataType(mType);
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_MAIN,"SkeletonDataEventProvider is null");
}

void CSkeletonResourceImpl::exampleEventCb()
{
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,__FUNCTION__);
    if (mpSkeletonDataEventProvider)
        mpSkeletonDataEventProvider->hardkeyEvent(1);
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_MAIN,"SkeletonDataEventProvider is null");
}
