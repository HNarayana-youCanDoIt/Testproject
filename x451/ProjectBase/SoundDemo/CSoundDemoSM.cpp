#include "CSoundDemoSM.h"
#include "CSoundDemoAdaptor.h"
#include "CAudioAdaptor.h"


CSoundDemoSM::CSoundDemoSM(CSoundDemoApplication *app)
    :m_app(app)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__);
    CHMIMain::getSM()->setSCI_SoundDemo_OCB(this);
}

void CSoundDemoSM::enterSoundDemo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__)
    if(CAudioEnums::SRC_HDD == CAudioAdaptor::getInstance()->activeEntSrc())
    {
        m_app->loadScreen("qrc:/QML/SoundDemo/SoundDemo.qml");
        CSoundDemoAdaptor::getInstance()->setActiveAudioPreset(CAudioAdaptor::getInstance()->activeAudioPreset());
        CAudioAdaptor::getInstance()->setAudioPresetAttribute(static_cast<int>(CAudioEnums::AUDIO_PRESET_FLAT));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s: User should reach here only while the HDD source is active else return back to home.", __FUNCTION__)
        m_app->handleFailSafeScenario();
    }
}

void CSoundDemoSM::exitSoundDemo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__)
    CAudioAdaptor::getInstance()->setAudioPresetAttribute(static_cast<int>(CSoundDemoAdaptor::getInstance()->getActiveAudioPreset()));
    if(CAudioEnums::SRC_HDD == CAudioAdaptor::getInstance()->activeEntSrc())
    {
        CAudioAdaptor::getInstance()->switchToPreviousEntSource();
        CAudioAdaptor::getInstance()->setIsSourceChangeRequestedByUser(false);
    }/*else{//DO Nothing} */
}

