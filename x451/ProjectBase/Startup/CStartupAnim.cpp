#include "CStartupAnim.h"
#include "HMIIncludes.h"
#include <logging.h>
#include "CHomeAdaptor.h"
#include <Audio/CAudioAdaptor.h>
#include <ParkAssist/CParkAssistAdaptor.h>

CStartupAnim::CStartupAnim(QQuickItem* parent)
    :CBaseApplication(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CStartupAnim::CStartupAnim");
    CHMIMain::getSM()->setSCI_Startup_OCB(this);
    mfw.setContextProperty("cppStartupAnim",this);
}

CStartupAnim::~CStartupAnim()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CStartupAnim::~CStartupAnim");
}

void CStartupAnim::onCreated(QQuickItem *rootObject)
{
    Q_UNUSED(rootObject);
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CStartupAnim::onCreated");
}

void CStartupAnim::raiseSMEvent(const QString & name,const QVariant & data)
{
    Q_UNUSED(name);
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, __FUNCTION__);
    if(!(CParkAssistAdaptor::getInstance()->reverseGearStatus()) && (data == "HomeMain"))
    {
        CHomeAdaptor::getInstance().setCurrentPageIndex(0);
        CHMIMain::getSM()->getSCI_Ui()->raise_evAnimComplete();
    }
}

void CStartupAnim::enterStartAnim()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CStartupAnim::startAnim");

    loadScreen("qrc:/QML/StartupAnim/StartupAnimMain.qml");
}

void CStartupAnim::exitStartupAnim()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s", __FUNCTION__);
    CFramework::getFramework().clearScreenHistoryStack();
}
