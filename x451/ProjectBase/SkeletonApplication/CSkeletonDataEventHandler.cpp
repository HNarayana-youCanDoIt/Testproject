#include "CSkeletonDataEventHandler.h"
#include <CHMIMain.h>
#include "CSkeletonAdaptor.h"
#include "SkeletonResource/implementations/CSkeletonResourceImpl.h"
#include <ResourceFactory.hpp>

CSkeletonDataEventHandler::CSkeletonDataEventHandler(QObject *parent):
    QObject(parent)
{
    connectSignals();
}

CSkeletonDataEventHandler::~CSkeletonDataEventHandler()
{

}

void CSkeletonDataEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,__FUNCTION__);
    CSkeletonResourceImpl* skeletonResource = dynamic_cast<CSkeletonResourceImpl*>(ResourceFactory::getSkeletonResource());
    if (skeletonResource)
    {
        // make the signal and slot connection
        CSkeletonDataEventProvider* skeletonDataEventProvider = skeletonResource->getSkeletonDataEventProvider();
        connect(skeletonDataEventProvider,SIGNAL(sigHardKeyEvent(int)),this,SLOT(sltHardKeyEvent(int)));
        connect(skeletonDataEventProvider,SIGNAL(sigUpdateDataType(int)),this,SLOT(sltUpdateDataType(int)));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MAIN,"Resource returns as null from ResourceFactory");
    }

}

void CSkeletonDataEventHandler::sltHardKeyEvent(int eventType)
{
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s: Hard key event type is: %d", __FUNCTION__, eventType);
    //CHMIMain::getSM()->getSCI_Tuner()->raise_evtStationUpdate();
}

void CSkeletonDataEventHandler::sltUpdateDataType(int type)
{
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s: Data type is: %d", __FUNCTION__, type);
    CSkeletonAdaptor::getInstance().setType(CSkeletonEnums::ESkeletonType(type));
}
