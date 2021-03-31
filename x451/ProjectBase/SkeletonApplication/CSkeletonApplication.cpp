#include "CSkeletonApplication.h"
#include "CSkeletonSM.h"
#include "CSkeletonDataEventHandler.h"
#include "CSkeletonAdaptor.h"

CSkelectonApplication::CSkelectonApplication(QQuickItem* parent)
    :CBaseApplication(parent),
      mSkeletonAdaptor(CSkeletonAdaptor::getInstance()),
      mpSkeletonSM(new CSkeletonSM(*this)),
      mpSkeletonDataEventHandler(new CSkeletonDataEventHandler())
{
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,__FUNCTION__);
    mfw.setContextProperty("cppSkeletonApp",this);
}

CSkelectonApplication::~CSkelectonApplication()
{
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,__FUNCTION__);
    if (mpSkeletonDataEventHandler)
        delete mpSkeletonDataEventHandler;
    if (mpSkeletonSM)
        delete mpSkeletonSM;
}

void CSkelectonApplication::onCreated(QQuickItem *rootObject)
{
    Q_UNUSED(rootObject);
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,__FUNCTION__);    
}

void CSkelectonApplication::loadScreen(QString qmlFilePath)
{
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,__FUNCTION__);
    CBaseApplication::loadScreen(qmlFilePath);
}

void CSkelectonApplication::raiseSMEvent(const QString & name,const QVariant & data)
{
    Q_UNUSED(name);
    //Replace the e_LOG_CONTEXT_MAIN with your modules
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,__FUNCTION__);
    if(data == "HomeMain")
    {
        loadScreen("qrc:/QML/Home/ScnHomeMain.qml");
        CHMIMain::getSM()->raise_evBackPressed();
    }
    else
    {
        //Replace the e_LOG_CONTEXT_MAIN with your modules
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s, requested update state no present",__FUNCTION__);
    }
}
