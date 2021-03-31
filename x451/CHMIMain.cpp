#include "HMIIncludes.h"
#include <Tuner/implementations/CTunerResourceImpl.h>
#include <HardkeyResource/implementations/CHardkeyResourceImpl.h>
#include <AudioResource/implementations/CAudioResourceImpl.h>
#include <EnggMenuResource/implementations/CEnggMenuResourceImpl.h>
#include <VehicleResource/implementations/CVehicleResourceImpl.h>
#include <ParkAssistResource/implementations/CParkAssistResourceImpl.h>
#include <ResourceFactory.hpp>
#include <capi/CAPIEngine.hpp>
#include "HMIApplication/CHMIApplication.h"
#include <QCursor>
#include "StateMachine_HBTimer.h"
#include <QStyleHints>


#define USE_RESOURCE_LAYER

TML_HMI_SM* CHMIMain::m_pStatemachine = NULL;
CHMIMain* CHMIMain::_instance = NULL;

CHMIMain::CHMIMain(QObject *pParent)
    : QObject(pParent),
      m_pHMIApplication(nullptr),
      m_pTMLTimer(nullptr)
{

    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s HMI startup", __FUNCTION__);

#ifdef USE_RESOURCE_LAYER
    CAPIEngine::getCAPIEngine();
#endif

#ifdef USE_RESOURCE_LAYER
    initResources();
#endif

    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CHMIMain::CHMIMain");
    m_pStatemachine = new TML_HMI_SM();

    // Create HMIApplication instance and call initHMIWindow to create the window
    m_pHMIApplication = new CHMIApplication(NULL);
    m_pHMIApplication->initHMIWindow();

    if(m_pStatemachine)
    {
        m_pTMLTimer = new HBTimer();
        if(m_pTMLTimer)
        {
            m_pStatemachine->setTimer(m_pTMLTimer);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s : m_pTMLTimer is NULL",__FUNCTION__);
        }
        m_pStatemachine->init();
        m_pStatemachine->enter();
        m_pStatemachine->runCycle();
    }
    else
    {
        qDebug() << " State Machine not initialized";
    }

    QGuiApplication::setOverrideCursor(QCursor(Qt::PointingHandCursor));

}

CHMIMain::~CHMIMain()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CHMIMain::~CHMIMain");
    if(m_pHMIApplication)
        delete m_pHMIApplication;

    ResourceFactory::deleteTunerRsource();
    ResourceFactory::deleteAudioRsource();
    ResourceFactory::deleteMediaResource();
    ResourceFactory::deleteHardkeyResource();
    ResourceFactory::deleteEnggMenuResource();
    ResourceFactory::deleteVehicleResource();
    ResourceFactory::deleteParkAssistResource();
    ResourceFactory::disposePhoneConnectionManagerResource();
    ResourceFactory::disposeDeviceModeHandlerResource();
    ResourceFactory::deleteAndroidAutoResource();
    ResourceFactory::disposePhoneCallManagerResource();
    ResourceFactory::disposePhonePIMDBResource();
    ResourceFactory::deletePowerModeResource();
    ResourceFactory::deleteHVACResource();
    ResourceFactory::deleteDisplayManagerResource();
    ResourceFactory::deleteAppleCarPlayResource();
    ResourceFactory::deleteDateAndTimeResource();
    ResourceFactory::deleteVersionManagerResource();
    ResourceFactory::disposeVoiceAlertsResource();
    ResourceFactory::disposeVRStubResource();
    ResourceFactory::disposeIntrospectionStubResource();
    ResourceFactory::disposeBtPluginResource();
    ResourceFactory::deleteDiagnosticResource();
    ResourceFactory::deleteLayerManagerResource();
    ResourceFactory::disposeVRProxyResource();
    ResourceFactory::deleteVariantControlResource();
    ResourceFactory::deleteRCAResource();
    ResourceFactory::deleteICCastResource();
    ResourceFactory::deleteDriveNextResource();
    ResourceFactory::deleteW3WResource();
    ResourceFactory::deleteDoodleResource();

    if(m_pTMLTimer)
    {
        delete m_pTMLTimer;
        m_pTMLTimer = nullptr;
    }
}

void CHMIMain::initResources()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CHMIMain::initResources");

    /** Create and init the Variant Control resource layer
     * This neeeds to be the first resource to be initialized since it read the eols and provides
     * info on which feature is to be enabled / disabled
    */
    ResourceFactory::initVariantControlResource();

    ResourceFactory::initParkAssistResource();
    ResourceFactory::initPowerModeResource();
    ResourceFactory::initAudioResource();
    ResourceFactory::initTunerResource();
    ResourceFactory::initHardkeyResource();
    ResourceFactory::initEnggMenuResource();
    ResourceFactory::initVehicleResource();
    ResourceFactory::initMediaResource();
    ResourceFactory::initSoftwareUpdateResource();
    ResourceFactory::initPhoneConnectionManagerResource();
    ResourceFactory::initPhoneCallManagerResource();
    ResourceFactory::initPhonePIMDBResource();
    ResourceFactory::initDeviceModeHandlerResource();
    ResourceFactory::initAndroidAutoResource();

    /** Create and init the HVAC resource layer */
    ResourceFactory::initHVACResource();

    /** Create and init the Display Manager resource layer */
    ResourceFactory::initDisplayManagerResource();

    /** Create and init the AppleCarPlay resource layer */
    ResourceFactory::initAppleCarPlayResource();

    /** Create and init the Time Manager resource layer */
    ResourceFactory::initDateAndTimeResource();


     /** Create and init the Introspection resource layer */
    ResourceFactory::initIntrospectionStubResource();

    /** Create and init the Version Manager resource layer */
    ResourceFactory::initVersionManagerResource();

    /**Create and init the voice alerts resource */
    ResourceFactory::initVoiceAlertsResource();

    ResourceFactory::initVRStubResource();

    /** Create and init the RCA resource layer */
    ResourceFactory::initRCAResource();

    ResourceFactory::initBtPluginResource();

    /** Create and init the Diagnostic resource layer */
    ResourceFactory::initDiagnosticResource();
    /** Create and init the Layer manager resource layer */
    ResourceFactory::initLayerManagerResource();

    ResourceFactory::initVRProxyResource();

    /** Create and init the Variant Control resource layer */
    ResourceFactory::initICCastResource();

    //Todo: Apps DID check
    /** Create and init the DriveNext resource layer */
    ResourceFactory::initDriveNextResource();

    /** Create and init the W3W resource layer */
    //Todo: Apps DID check
    ResourceFactory::initW3WResource();

    /** Create and init the Doodle resource layer */
    //Todo: Apps DID check
    ResourceFactory::initDoodleResource();
}

void CHMIMain::registerQMLEnums()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CHMIMain::registerQMLEnums");

}

void CHMIMain::startHMIApp()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "CHMIMain::startHMIApp");
    if(_instance == NULL)
    {
        _instance = new CHMIMain();
    }
}

CHMIMain* CHMIMain::getInstance()
{
    return _instance;
}

TML_HMI_SM* CHMIMain::getSM()
{
    return m_pStatemachine;
}

int CHMIMain::getScreenWidth()
{
    int iWidth = DEFAULT_SCREEN_WIDTH;
    if (m_pHMIApplication)
    {
        iWidth = m_pHMIApplication->getScreenWidth();
    }
    return iWidth;
}

int CHMIMain::getScreenHeight()
{
    int iHeight = DEFAULT_SCREEN_HEIGHT;
    if (m_pHMIApplication)
    {
        iHeight = m_pHMIApplication->getScreenHeight();
    }
    return iHeight;
}
