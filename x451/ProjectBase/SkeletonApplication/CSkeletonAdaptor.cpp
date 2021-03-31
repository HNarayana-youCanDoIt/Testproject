#include "CSkeletonAdaptor.h"
#include "ResourceFactory.hpp"

CSkeletonAdaptor* CSkeletonAdaptor::mpSkeletonAdaptor = nullptr;

CSkeletonAdaptor::CSkeletonAdaptor(QObject *parent) : QObject(parent),
    mType(CSkeletonEnums::TYPE_INVALID),
    mfw(CFramework::getFramework()),
    mSkeletonResource(ResourceFactory::getSkeletonResource())
{
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,__FUNCTION__);
    CSkeletonEnums::registerSkeletonEnumsToQML();
    mfw.setContextProperty("SkeletonAdaptor",this);
}

CSkeletonAdaptor::~CSkeletonAdaptor()
{
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,__FUNCTION__);

}

CSkeletonAdaptor& CSkeletonAdaptor::getInstance()
{
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,__FUNCTION__);
    if (nullptr == mpSkeletonAdaptor)
    {
        mpSkeletonAdaptor = new CSkeletonAdaptor();
    }
    return *mpSkeletonAdaptor;
}

/////////////////////////////
// Property related functions
/////////////////////////////

CSkeletonEnums::ESkeletonType CSkeletonAdaptor::type()
{
    return mType;
}

void CSkeletonAdaptor::setType(CSkeletonEnums::ESkeletonType type)
{
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,__FUNCTION__);
    if (type != mType)
    {
        mType = type;
        emit sigTypeChanged();
    }
}

// End Property related functions

//////////////////////////////////////////////////////////////////
// Functions to propogate calls to resource layer and statemachine

void CSkeletonAdaptor::exampleReq()
{
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,__FUNCTION__);

    //Todo: Call to resource layer, if required propogate call to SM
    if (mSkeletonResource)
        mSkeletonResource->exampleReq();
}

// End Functions to propogate calls to resource layer and statemachine
