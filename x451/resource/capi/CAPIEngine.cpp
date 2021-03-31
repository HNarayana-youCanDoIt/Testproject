#include "CAPIEngine.hpp"
#include "logging.h"

CAPIEngine* CAPIEngine::m_pSelf = nullptr;


CAPIEngine& CAPIEngine::getCAPIEngine()
{
    if ( nullptr == m_pSelf )
    {
        m_pSelf = new CAPIEngine;
    }
    return *m_pSelf;
}


std::shared_ptr<CommonAPI::MainLoopContext> CAPIEngine::getMainLoop()
{
    return m_pSelf->mainloopContext;
}

CAPIEngine::CAPIEngine()
{

    CommonAPI::Runtime::setProperty("LogContext", "TML_HMI");
    CommonAPI::Runtime::setProperty("LibraryBase", "TML_HMI");

    mainloopContext = std::make_shared<CommonAPI::MainLoopContext>("dbusconnection");

    QObject::connect(this, SIGNAL(onWatchAdded(Watch*)), this, SLOT(doWatchAdded(Watch*)), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(onWatchRemoved(Watch*)), this, SLOT(doWatchRemoved(Watch*)), Qt::QueuedConnection);

    if ( nullptr != mainloopContext )
    {
         mainloopContext->subscribeForWatches(std::bind(&CAPIEngine::regWatch,this, std::placeholders::_1, std::placeholders::_2),std::bind(&CAPIEngine::deregWatch,this, std::placeholders::_1));
    }

}

void CAPIEngine::onSocketDataAvailable(int fd)
{
    auto it = mWatchMap.find(fd);

    if (it != mWatchMap.end())
    {
//        LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "Socket returned data : %d", fd);
        it->second.mWatch->dispatch(POLLIN);
        const std::vector<CommonAPI::DispatchSource*>& dependentSources = it->second.mWatch->getDependentDispatchSources();
        for ( auto it = dependentSources.begin() ; it != dependentSources.end() ; it++ )
        {
            if (true == (*it)->check() )
            {
                while((*it)->dispatch()) {}
            }
        }
    }
    else
    {
        LOG_ERROR(Log::e_LOG_CONTEXT_MAIN, "Unknown socket data, ignoring : %d", fd);
    }
}

void CAPIEngine::doWatchAdded(Watch *watch)
{
    int fd = watch->getAssociatedFileDescriptor().fd;
    auto it = mWatchMap.find(fd);
    if (it == mWatchMap.end())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "Watch Registered : %d", fd);
        struct watchHandler wHdlr;
        wHdlr.mWatch = watch;
        wHdlr.mSn = new QSocketNotifier(fd,QSocketNotifier::Read);
        QObject::connect(wHdlr.mSn, SIGNAL(activated(int)), this, SLOT(onSocketDataAvailable(int)),Qt::AutoConnection);
        wHdlr.mSn->setEnabled(true);
        mWatchMap[fd] = wHdlr;
    }
    else
    {
        LOG_ERROR(Log::e_LOG_CONTEXT_MAIN, "Watch Already registered, ignoring : %d", fd);
    }
}

void CAPIEngine::doWatchRemoved(Watch *watch)
{
    int fd = watch->getAssociatedFileDescriptor().fd;
    auto it = mWatchMap.find(fd);
    if (it == mWatchMap.end())
    {
        LOG_ERROR(Log::e_LOG_CONTEXT_MAIN, "Watch Removed callback for unknown watch : %d", fd);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "Watch Removed : %d", fd);
        it->second.mSn->setEnabled(false);
        delete it->second.mSn;
        mWatchMap.erase(it);
    }

}

void CAPIEngine::regWatch( Watch* watch_, const DispatchPriority dispatchPriority)
{
   CPP_UNUSED(dispatchPriority);
   emit onWatchAdded(watch_);
}


void CAPIEngine::deregWatch( Watch* watch)
{
    emit onWatchRemoved(watch);
}
