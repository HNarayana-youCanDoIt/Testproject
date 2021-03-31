
#include "CHMIApplicationSM.h"

CHMIApplicationSM::CHMIApplicationSM(CHMIApplication &parent)
    :rHMIAppMain(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, __FUNCTION__);
}

CHMIApplicationSM::~CHMIApplicationSM()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, __FUNCTION__);
}

void CHMIApplicationSM::initHmi()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CHMIApplicationSM::initHmi");
    rHMIAppMain.initHmi();
}

void CHMIApplicationSM::initUI()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CHMIApplicationSM::initUI");

}

void CHMIApplicationSM::initMediaOff()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CHMIApplicationSM::initMediaOff");
}

/* ToDo: These can be the points where we send signals to the UI.qml and handle the visibility of the loaders. If we decide
 * to make use of loaders for the various modules. Hope these functions are called only once
 */
void CHMIApplicationSM::initStartup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CHMIApplicationSM::initStartup");
    // Need to call the enter screen for that particular module
   //loadScreen("qrc:/QML/StartupAnim/StartupAnimMain.qml");
}

void CHMIApplicationSM::initMedia()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CHMIApplicationSM::initMedia");
    // Need to call the enter screen for that particular module
    // rHMIAppMain.loadScreen("qrc:/QML/Media/MediaScreen.qml");
}

void CHMIApplicationSM::initTuner()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CHMIApplicationSM::initTuner");
    // Need to call the enter screen for that particular module
    // rHMIAppMain.loadScreen("qrc:/QML/Tuner/TunerScreen.qml");
}

void CHMIApplicationSM::initHome()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CHMIApplicationSM::initHome");
    // Need to call the enter screen for that particular module
    // rHMIAppMain.loadScreen("qrc:/QML/Home/ScnHomeMain.qml");
}

void CHMIApplicationSM::initSetup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CHMIApplicationSM::initSetup");
    // Need to call the enter screen for that particular module
    // rHMIAppMain.loadScreen("qrc:/QML/Setup/SetupScreen.qml");
}

void CHMIApplicationSM::initPhone()
{
    // Need to call the enter screen for that particular module
}

void CHMIApplicationSM::initEnggMenu()
{
    // Need to call the enter screen for that particular module
}

void CHMIApplicationSM::initDrawers()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, __FUNCTION__);
    // Need to call the enter screen for that particular module
}

void CHMIApplicationSM::initAndroidAuto()
{
    // Need to call the enter screen for that particular module
}

void CHMIApplicationSM::initCarPlay()
{
    // Need to call the enter screen for that particular module
}

void CHMIApplicationSM::initSAL()
{
    // Need to call the enter screen for that particular module
}

void CHMIApplicationSM::initSoftwareUpdate()
{
    // Need to call the enter screen for that particular module
}

void CHMIApplicationSM::exitUI()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CHMIApplicationSM::exitUI");
    CDrawersAdaptor::getInstance()->setAllowStatusBarOnScreen(false);
}



