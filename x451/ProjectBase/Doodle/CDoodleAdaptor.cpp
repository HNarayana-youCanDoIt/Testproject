/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDoodleAdaptor.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDoodleAdaptor, an Adaptor for Doodle module,
 * CDoodleAdaptor is class used to communicate with qml, resources of Doodle module.
 */

#include "ResourceFactory.hpp"
#include "HMIIncludes.h"

#include <QGuiApplication>

#include "CDoodleApplication.h"
#include "CDoodleAdaptor.h"
#include "CDoodleSM.h"
#include "CDoodleEventHandler.h"
#include "CDoodleEnum.h"
#include "CPersistencyAdaptor.h"
#include "CAudioAdaptor.h"
#include "CAndroidAutoAdaptor.h"
#include "CAppleCarPlayAdaptor.h"
#include "CVariantControlAdaptor.h"

#include "implementations/CDoodleResourceImpl.h"

///////////////////////////////////////////////////////////////////////////////
// Adaptor related functions
///////////////////////////////////////////////////////////////////////////////
CDoodleAdaptor::CDoodleAdaptor(QObject *parent) :
    QObject(parent),
    m_bDoodleEOLPresence(false),
    m_bDoodleProxyPresence(false),
    m_bDoodleActivated(false),
    m_iDoodleDisplayWaitTime(0),
    m_bAllowDoodleOnScreen(false),
    m_bAllowDoodleOnDrawer(false),
    m_bDoodleAvailable(false),
    m_strDoodleImageURL("qrc:/image/Doodle/Gfx_doodle_stickerShapes_7in_n-assets/Gfx_doodle_Doodle_default_picture1.png"),
    m_strStartupImageURL("qrc:/image/Doodle/Gfx_doodle_stickerShapes_7in_n-assets/Gfx_doodle_default_picture_P1.png"),
    m_bForceShowDoodleOnScreen(false),
    m_pDoodleWaitTimer(nullptr),
    m_pDoodleSetupModel(nullptr),
    m_eDoodleSetupExpandedElement(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_UNKNOWN),
    m_pDoodleResource(dynamic_cast<CDoodleResourceImpl*>(ResourceFactory::getDoodleResource()))
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s", __FUNCTION__);
    CFramework::getFramework().setContextProperty("cppDoodleAdaptor",this);
    CDoodleEnum::registerDoodleEnumsToQML();

    m_pDoodleWaitTimer = new QTimer(this);

    connectSignals();
    initDoodleProperties();
    initDoodleData();
}
//____________________________________________________________________________
CDoodleAdaptor::~CDoodleAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);

    disconnectSignals();

    if (nullptr != m_pDoodleWaitTimer)
    {
        m_pDoodleWaitTimer->stop();

        delete m_pDoodleWaitTimer;
        m_pDoodleWaitTimer = nullptr;
    }
    else
    {
        //Do Nothing!
    }

    resetDoodleSetupList();
    resetDoodleData();
}
//____________________________________________________________________________
void CDoodleAdaptor::initDoodleProperties()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);

    sltDoodleEOLEnabled();
    updateDoodleProxyPresence();

    if(m_pDoodleResource)
    {
        //sync with Doodle Proxy
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s: Doodle resource object not created", __FUNCTION__);
    }

    setDoodleDisplayWaitTime(5);
    setDoodleSize(QPoint(300, 200));

    //Fix Me: Need to handle as per clear status
    setDoodleImageURL("file://opt/hmi/Gfx_doodle_Doodle Startup.png");
    setStartupImageURL("file://opt/hmi/Gfx_doodle_Startup_Image_default_P2.png");

    setDoodleActivated(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_DOODLE_STICKER_ACTIVATED));
    setForceShowDoodleOnScreen(false);

    //Please Note: Not using setDoodlePosition as it saves value to Persistency
    m_DoodlePosition = QPoint(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_DOODLE_STICKER_POS_X), CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_DOODLE_STICKER_POS_Y));

    sltDrawerStateChanged();
    resetDoodleSetupList();
}
//____________________________________________________________________________
void CDoodleAdaptor::initDoodleData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
}
//____________________________________________________________________________
void CDoodleAdaptor::resetDoodleData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
}
//____________________________________________________________________________
void CDoodleAdaptor::resetDoodleSetupElements()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);

    qDeleteAll(m_lDoodleSetupElementsData.begin(), m_lDoodleSetupElementsData.end());
    m_lDoodleSetupElementsData.clear();

    emit sigDoodleSetupElementsChanged();
}
//____________________________________________________________________________
void CDoodleAdaptor::initDoodleSetupElements()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);

    qDeleteAll(m_lDoodleSetupElementsData.begin(), m_lDoodleSetupElementsData.end());
    m_lDoodleSetupElementsData.clear();

    for (int i = 0; i < static_cast<int>(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_TOTAL_COUNT); i++)
    {
        m_lDoodleSetupElementsData.append(new CDoodleSetupListElement());
        ((CDoodleSetupListElement*)m_lDoodleSetupElementsData[i])->setType(static_cast<CDoodleEnum::EDoodleSetupElementTypes>(i));
    }

    ((CDoodleSetupListElement*)m_lDoodleSetupElementsData[CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER])->setName("*My Sticker");
    ((CDoodleSetupListElement*)m_lDoodleSetupElementsData[CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER_ACTIVATE])->setName("*Activate Sticker");
    ((CDoodleSetupListElement*)m_lDoodleSetupElementsData[CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER_PREVIEW])->setName("*Preview Sticker");
    ((CDoodleSetupListElement*)m_lDoodleSetupElementsData[CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER_CLEAR])->setName("*Clear Sticker");
    ((CDoodleSetupListElement*)m_lDoodleSetupElementsData[CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE])->setName("*Startup Image");
    ((CDoodleSetupListElement*)m_lDoodleSetupElementsData[CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE_ACTIVATE])->setName("*Activate Image");
    ((CDoodleSetupListElement*)m_lDoodleSetupElementsData[CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE_PREVIEW])->setName("*Preview Image");
    ((CDoodleSetupListElement*)m_lDoodleSetupElementsData[CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE_CLEAR])->setName("*Clear Image");

    ((CDoodleSetupListElement*)m_lDoodleSetupElementsData[CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER])->setEnabled(true);
    ((CDoodleSetupListElement*)m_lDoodleSetupElementsData[CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER_ACTIVATE])->setEnabled(true);
    ((CDoodleSetupListElement*)m_lDoodleSetupElementsData[CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER_PREVIEW])->setEnabled(true);
    ((CDoodleSetupListElement*)m_lDoodleSetupElementsData[CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER_CLEAR])->setEnabled(true);
    ((CDoodleSetupListElement*)m_lDoodleSetupElementsData[CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE])->setEnabled(true);
    ((CDoodleSetupListElement*)m_lDoodleSetupElementsData[CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE_ACTIVATE])->setEnabled(true);
    ((CDoodleSetupListElement*)m_lDoodleSetupElementsData[CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE_PREVIEW])->setEnabled(true);
    ((CDoodleSetupListElement*)m_lDoodleSetupElementsData[CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE_CLEAR])->setEnabled(true);

    ((CDoodleSetupListElement*)m_lDoodleSetupElementsData[CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER_ACTIVATE])->setToggleStatus(doodleActivated());
    ((CDoodleSetupListElement*)m_lDoodleSetupElementsData[CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE_ACTIVATE])->setToggleStatus(true);

    emit sigDoodleSetupElementsChanged();
}
//____________________________________________________________________________
void CDoodleAdaptor::initDoodleSetupList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);

    if(nullptr == m_pDoodleSetupModel)
    {
        m_pDoodleSetupModel = new CGenericListModel(this);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s reseting Old m_pDoodleSetupModel", __FUNCTION__);
        m_pDoodleSetupModel->resetListModel();
    }

    initDoodleSetupElements();

    m_pDoodleSetupModel->tryAddListElementTypeAtEnd(static_cast<int>(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER));
    m_pDoodleSetupModel->tryAddListElementTypeAtEnd(static_cast<int>(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE));

    setDoodleSetupExpandedElement(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_UNKNOWN);
}
//____________________________________________________________________________
void CDoodleAdaptor::resetDoodleSetupList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    setDoodleSetupExpandedElement(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_UNKNOWN);
    resetDoodleSetupElements();

    if(m_pDoodleSetupModel)
    {
        delete m_pDoodleSetupModel;
        m_pDoodleSetupModel = nullptr;
    }
    else
    {
        //Do Nothing!
    }

}
//____________________________________________________________________________
void CDoodleAdaptor::refreshDoodleSetupList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    switch (doodleSetupExpandedElement())
    {
    case CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER:
    {
        tryRemoveStartupImageGroupFromDoodleSetupList();
        tryAddStickerGroupInDoodleSetupList();
    }
        break;
    case CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE:
    {
        tryRemoveStickerGroupFromDoodleSetupList();
        tryAddStartupImageGroupInDoodleSetupList();
    }
        break;
    case CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER_ACTIVATE:
    case CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER_PREVIEW:
    case CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER_CLEAR:
    case CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE_ACTIVATE:
    case CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE_PREVIEW:
    case CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE_CLEAR:
    case CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_UNKNOWN:
    case CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_TOTAL_COUNT:
    default:
    {
        tryRemoveStickerGroupFromDoodleSetupList();
        tryRemoveStartupImageGroupFromDoodleSetupList();
    }
        break;
    }
}
//____________________________________________________________________________
bool CDoodleAdaptor::doodleEOLPresence()
{
    return m_bDoodleEOLPresence;
}
//____________________________________________________________________________
void CDoodleAdaptor::setDoodleEOLPresence(bool bValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, bValue=%d", __FUNCTION__, bValue);
    if(bValue != m_bDoodleEOLPresence)
    {
        m_bDoodleEOLPresence = bValue;
        updateDoodleAvailability();

        emit sigDoodleEOLPresenceChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, m_bDoodleEOLPresence not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
bool CDoodleAdaptor::doodleProxyPresence()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s m_bDoodleProxyPresence %d", __FUNCTION__, m_bDoodleProxyPresence);
    return m_bDoodleProxyPresence;
}
//____________________________________________________________________________
void CDoodleAdaptor::updateDoodleProxyPresence()
{
    bool bValue = true;//((m_pDoodleResource != nullptr) && (m_pDoodleResource->getProxyAvailabilityStatus()));
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, bValue=%d", __FUNCTION__, bValue);
    if(bValue != m_bDoodleProxyPresence)
    {
        m_bDoodleProxyPresence = bValue;
        if (m_bDoodleProxyPresence)
        {
            initDoodleProperties();
        }
        else
        {
            doodleWaitTimerStop();
            setForceShowDoodleOnScreen(false);
            tryHideDoodleFromScreen();
            if (CHMIMain::getSM()->isStateActive(CHMIMain::getSM()->startup_region_Ui_home_Main_main_DoodleSetup))
            {
                CHMIMain::getSM()->raise_evBackPressed();
            }
            else
            {
                //Do Nothing!
            }
        }
        updateDoodleAvailability();

        emit sigDoodleProxyPresenceChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, m_bDoodleProxyPresence not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
bool CDoodleAdaptor::doodleActivated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s m_bDoodleActivated %d", __FUNCTION__, m_bDoodleActivated);
    return m_bDoodleActivated;
}
//____________________________________________________________________________
void CDoodleAdaptor::setDoodleActivated(bool bValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, bValue=%d", __FUNCTION__, bValue);
    if(bValue != m_bDoodleActivated)
    {
        m_bDoodleActivated = bValue;

        if (m_lDoodleSetupElementsData.count() == CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_TOTAL_COUNT)
        {
            ((CDoodleSetupListElement*)m_lDoodleSetupElementsData[CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER_ACTIVATE])->setToggleStatus(doodleActivated());
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, m_lDoodleSetupElementsData not available", __FUNCTION__);
        }
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_DOODLE_STICKER_ACTIVATED, m_bDoodleActivated);
        updateDoodleAvailability();

        emit sigDoodleActivatedChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, m_bDoodleActivated not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
int CDoodleAdaptor::doodleDisplayWaitTime()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s m_iDoodleDisplayWaitTime %d", __FUNCTION__, m_iDoodleDisplayWaitTime);
    return m_iDoodleDisplayWaitTime;
}
//____________________________________________________________________________
void CDoodleAdaptor::setDoodleDisplayWaitTime(int iValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, iValue=%d", __FUNCTION__, iValue);
    if(iValue != m_iDoodleDisplayWaitTime)
    {
        m_iDoodleDisplayWaitTime = iValue;

        if (nullptr != m_pDoodleWaitTimer)
        {
            m_pDoodleWaitTimer->setInterval(m_iDoodleDisplayWaitTime*1000);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s m_pDoodleWaitTimer not created", __FUNCTION__);
        }

        emit sigDoodleDisplayWaitTimeChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, m_iDoodleDisplayWaitTime not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
bool CDoodleAdaptor::allowDoodleOnScreen()
{
    return m_bAllowDoodleOnScreen;
}
//____________________________________________________________________________
void CDoodleAdaptor::setAllowDoodleOnScreen(bool bValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, bValue=%d", __FUNCTION__, bValue);
    if(bValue != m_bAllowDoodleOnScreen)
    {
        m_bAllowDoodleOnScreen = bValue;
        emit sigAllowDoodleOnScreenChanged();

        updateDoodleAvailability();
        updateDoodlePermissions();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, m_bAllowDoodleOnScreen not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
bool CDoodleAdaptor::allowDoodleOnDrawer()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s m_bAllowDoodleOnDrawer:%d", __FUNCTION__, m_bAllowDoodleOnDrawer);
    return m_bAllowDoodleOnDrawer;
}
//____________________________________________________________________________
void CDoodleAdaptor::setAllowDoodleOnDrawer(bool bValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, bValue=%d", __FUNCTION__, bValue);
    if(bValue != m_bAllowDoodleOnDrawer)
    {
        m_bAllowDoodleOnDrawer = bValue;
        updateDoodlePermissions();

        emit sigAllowDoodleOnDrawerChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, m_bAllowDoodleOnDrawer not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
bool CDoodleAdaptor::doodleAvailable()
{
    return m_bDoodleAvailable;
}
//____________________________________________________________________________
void CDoodleAdaptor::updateDoodleAvailability()
{
    bool bValue = (doodleEOLPresence() && doodleProxyPresence() && doodleActivated() && allowDoodleOnScreen());
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, bValue=%d", __FUNCTION__, bValue);
    if(bValue != m_bDoodleAvailable)
    {
        m_bDoodleAvailable = bValue;
        emit sigDoodleAvailableChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, m_bDoodleAvailable not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
QPoint CDoodleAdaptor::doodlePosition()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s m_DoodlePosition (X:%d, Y:%d)", __FUNCTION__, m_DoodlePosition.x(), m_DoodlePosition.y());
    return m_DoodlePosition;
}
//____________________________________________________________________________
void CDoodleAdaptor::setDoodlePosition(QPoint position)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s position (X:%d, Y:%d)", __FUNCTION__, position.x(), position.y());
    if (position.x() != m_DoodlePosition.x())
    {
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_DOODLE_STICKER_POS_X, position.x());
    }
    else
    {
        //Do Nothing!
    }
    if (position.y() != m_DoodlePosition.y())
    {
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_DOODLE_STICKER_POS_Y, position.y());
    }
    else
    {
        //Do Nothing!
    }
    m_DoodlePosition = position;
    emit sigDoodlePositionChanged();
}
//____________________________________________________________________________
QString CDoodleAdaptor::doodleImageURL()
{
#if defined(PLATFORM_WIN32) || defined(PLATFORM_LINUX_X86)
    return "qrc:/image/Doodle/Gfx_doodle_stickerShapes_7in_n-assets/Gfx_doodle_Doodle_default_picture1.png";
#else
    return m_strDoodleImageURL;
#endif // defined(PLATFORM_WIN32) || defined(PLATFORM_LINUX_X86)
}
//____________________________________________________________________________
void CDoodleAdaptor::setDoodleImageURL(QString imageURL)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s imageURL:%s", __FUNCTION__, imageURL.toStdString().data());
    m_strDoodleImageURL = imageURL;
    emit sigDoodleImageURLChanged();
}
//____________________________________________________________________________
QString CDoodleAdaptor::startupImageURL()
{
#if defined(PLATFORM_WIN32) || defined(PLATFORM_LINUX_X86)
    return "qrc:/image/Doodle/Gfx_doodle_stickerShapes_7in_n-assets/Gfx_doodle_default_picture_P1.png";
#else
    return m_strStartupImageURL;
#endif // defined(PLATFORM_WIN32) || defined(PLATFORM_LINUX_X86)
}
//____________________________________________________________________________
void CDoodleAdaptor::setStartupImageURL(QString imageURL)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s imageURL:%s", __FUNCTION__, imageURL.toStdString().data());
    m_strStartupImageURL = imageURL;
    emit sigStartupImageURLChanged();
}
//____________________________________________________________________________
QPoint CDoodleAdaptor::doodleSize()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s m_DoodleSize (Width:%d, Height:%d)", __FUNCTION__, m_DoodleSize.x(), m_DoodleSize.y());
    return m_DoodleSize;
}
//____________________________________________________________________________
void CDoodleAdaptor::setDoodleSize(QPoint size)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s size (Width:%d, Height:%d)", __FUNCTION__, size.x(), size.y());
    m_DoodleSize = size;
    emit sigDoodleSizeChanged();
}
//____________________________________________________________________________
CDoodleEnum::EDoodleSetupElementTypes CDoodleAdaptor::doodleSetupExpandedElement()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s m_eDoodleSetupExpandedElement:%d", __FUNCTION__, static_cast<int>(m_eDoodleSetupExpandedElement));
    return m_eDoodleSetupExpandedElement;
}
//____________________________________________________________________________
void CDoodleAdaptor::setDoodleSetupExpandedElement(CDoodleEnum::EDoodleSetupElementTypes eDoodleSetupExpandedElement)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s eDoodleSetupExpandedElement:%d", __FUNCTION__, static_cast<int>(eDoodleSetupExpandedElement));
    if(eDoodleSetupExpandedElement != m_eDoodleSetupExpandedElement)
    {
        m_eDoodleSetupExpandedElement = eDoodleSetupExpandedElement;
        refreshDoodleSetupList();
        emit sigDoodleSetupExpandedElementChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, m_eDoodleSetupExpandedElement not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
QList<QObject *> CDoodleAdaptor::doodleSetupElements()
{
    return m_lDoodleSetupElementsData;
}
//____________________________________________________________________________
QAbstractListModel *CDoodleAdaptor::doodleSetupListModel()
{
    return m_pDoodleSetupModel;
}
//____________________________________________________________________________
bool CDoodleAdaptor::forceShowDoodleOnScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s m_bForceShowDoodleOnScreen %d", __FUNCTION__, m_bForceShowDoodleOnScreen);
    return m_bForceShowDoodleOnScreen;
}
//____________________________________________________________________________
void CDoodleAdaptor::setForceShowDoodleOnScreen(bool bValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, bValue=%d", __FUNCTION__, bValue);
    if(bValue != m_bForceShowDoodleOnScreen)
    {
        m_bForceShowDoodleOnScreen = bValue;
        if (m_bForceShowDoodleOnScreen)
        {
            tryShowDoodleOnScreen();
        }
        else
        {
            //Do Nothing!
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, m_bForceShowDoodleOnScreen not changed", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDoodleAdaptor::sltDoodleEOLEnabled()
{
    bool bStatus = CVariantControlAdaptor::getInstance()->eolHMIDoodleEnabled();
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, bStatus:%d", __FUNCTION__, bStatus);
    setDoodleEOLPresence(bStatus);
}
//____________________________________________________________________________
void CDoodleAdaptor::sltDoodleWaitTimeEnded()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    tryShowDoodleOnScreen();
}
//____________________________________________________________________________
void CDoodleAdaptor::sltPopupResult(CPopupEnum::EPopupID ePopupId, CPopupEnum::EPopupResult ePopupResult, QString strAdditionalInfo)
{
    Q_UNUSED(strAdditionalInfo);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s, ePopupId:%d, ePopupResult:%d", __FUNCTION__, static_cast<int>(ePopupId), static_cast<int>(ePopupResult));

    if (doodleAvailable())
    {
        switch (ePopupResult)
        {
        case CPopupEnum::EN_POPUP_RESULT_DISPLAYED:
        {
            doodleWaitTimerStop();
        }
            break;
        case CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_CONTEXT_CHANGE:
        case CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_TIMEOUT:
        case CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_TOUCH:
        case CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_HK:
        case CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_SUPERSEDE:
        case CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_CLOSE_REQUEST:
        case CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_FORCE_CLOSE_REQUEST:
        case CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS:
        case CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_CLOSE_ALL_POPUPS:
        {
            doodleWaitTimerRestart();
        }
            break;
        case CPopupEnum::EN_POPUP_RESULT_INVALID:
        case CPopupEnum::EN_POPUP_RESULT_IGNORED:
        default:
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s Unhandled ePopupResult:%d", __FUNCTION__, static_cast<int>(ePopupResult));
        }
            break;
        }
    }
    else
    {
        //Do Nothing!
    }
}
//____________________________________________________________________________
void CDoodleAdaptor::sltDrawerStateChanged()
{
    if (CDrawersAdaptor::getInstance()->qadDrawerState() == DRAWERS_STATE_MAXIMIZED_STRING)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s qad drawer maximized", __FUNCTION__);
        setForceShowDoodleOnScreen(false);
        setAllowDoodleOnDrawer(false);
    }
    else if (CDrawersAdaptor::getInstance()->shortcutDrawerState() == DRAWERS_STATE_MAXIMIZED_STRING)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s shortcut drawer maximized", __FUNCTION__);
        setForceShowDoodleOnScreen(false);
        setAllowDoodleOnDrawer(false);
    }
    else
    {
        setAllowDoodleOnDrawer(true);
    }
}
//____________________________________________________________________________
void CDoodleAdaptor::sltActiveChanged_AndroidAuto(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, bStatus : %d ", __FUNCTION__, bStatus);

    tryHideDoodleFromScreen();
    if (doodleAvailable())
    {
        doodleWaitTimerRestart();
    }
    else
    {
        //Do Nothing!
    }
}
//____________________________________________________________________________
void CDoodleAdaptor::sltActiveChanged_CarPlay(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, bStatus : %d ", __FUNCTION__, bStatus);

    tryHideDoodleFromScreen();
    if (doodleAvailable())
    {
        doodleWaitTimerRestart();
    }
    else
    {
        //Do Nothing!
    }
}
//____________________________________________________________________________
void CDoodleAdaptor::sltActiveChanged_USB()
{
    bool bStatus = CAudioAdaptor::getInstance()->usbSrcStatus();
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, bStatus : %d ", __FUNCTION__, bStatus);

    tryHideDoodleFromScreen();
    if (doodleAvailable())
    {
        doodleWaitTimerRestart();
    }
    else
    {
        //Do Nothing!
    }
}
//____________________________________________________________________________
void CDoodleAdaptor::sltAvailabilityChanged_AuxIn()
{
    bool bStatus = CAudioAdaptor::getInstance()->auxConnectionStatus();
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, eAuxConnectionStatus : %d ", __FUNCTION__, bStatus);

    tryHideDoodleFromScreen();
    if (doodleAvailable())
    {
        doodleWaitTimerRestart();
    }
    else
    {
        //Do Nothing!
    }
}
//____________________________________________________________________________
void CDoodleAdaptor::resetDoodle()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
}
//____________________________________________________________________________
void CDoodleAdaptor::openDoodleSetupFromDoodle()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    CHMIMain::getSM()->raise_evDoodleSetupActivated();
    setForceShowDoodleOnScreen(true);
}
//____________________________________________________________________________
bool CDoodleAdaptor::isDoodleStickerOnScreen()
{
    bool bStatus = false;
    if (CPopupManager::getInstance()->getCurrentDisplayedPopup() == CPopupEnum::EN_POPUPID_DOODLE_MYSTICKER_ICON)
    {
        bStatus = true;
    }
    else
    {
        //Do Nothing!
    }
    return bStatus;
}
//____________________________________________________________________________
void CDoodleAdaptor::tryShowDoodleOnScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    if (doodleAvailable())
    {
        if (!isDoodleStickerOnScreen())
        {
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_DOODLE_MYSTICKER_ICON);
            setForceShowDoodleOnScreen(false);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s doodle already displayed on screen", __FUNCTION__);
        }
        doodleWaitTimerStop();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s doodle not allowed to display on screen", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDoodleAdaptor::tryHideDoodleFromScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_DOODLE_MYSTICKER_ICON);
}
//____________________________________________________________________________
void CDoodleAdaptor::updateDoodleStickerPosition(int iPosX, int iPosY)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, iPosX:%d, iPosY:%d", __FUNCTION__, iPosX, iPosY);

    int iScreenWidth = CHMIMain::getInstance()->getScreenWidth();
    int iScreenHeight = CHMIMain::getInstance()->getScreenHeight();

    int iWidth = doodleSize().x();
    int iHeight = doodleSize().y();

    int iDeltaX = 0;
    int iDeltaY = 0;

    //Validate new position as inside screen
    if (iPosX > (iScreenWidth - iWidth/2))
    {
        iPosX = (iScreenWidth - iWidth/2);
    }
    else if (iPosX < iWidth/2)
    {
        iPosX = iWidth/2;
    }
    else
    {
        //iPosX is OK
    }

    if (iPosY > (iScreenHeight - iHeight/2))
    {
        iPosY = (iScreenHeight - iHeight/2);
    }
    else if (iPosY < iHeight/2)
    {
        iPosY = iHeight/2;
    }
    else
    {
        //iPosY is OK
    }

    //Calculate near final position
    if (iPosX == iScreenWidth/2)
    {
        iDeltaX = iScreenWidth/2;
        iDeltaY = iScreenHeight - iHeight/2;
    }
    else if (iPosX < iScreenWidth/2)
    {
        if (iPosX > (iScreenHeight - iPosY))
        {
            iDeltaX = iPosX;
            iDeltaY = iScreenHeight - iHeight/2;
        }
        else
        {
            iDeltaX = iWidth/2;
            iDeltaY = iPosY;
        }
    }
    else
    {
        iPosX = iScreenWidth - iPosX;
        if (iPosX > (iScreenHeight - iPosY))
        {
            iDeltaX = iScreenWidth - iPosX;
            iDeltaY = iScreenHeight - iHeight/2;
        }
        else
        {
            iDeltaX = iScreenWidth - iWidth/2;
            iDeltaY = iPosY;
        }
    }

    setDoodlePosition(QPoint(iDeltaX, iDeltaY));
}
//____________________________________________________________________________
void CDoodleAdaptor::handleDoodleSetupElementTouchEvent(CDoodleEnum::EDoodleSetupElementTypes eSetupElementType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, eSetupElementType:%d", __FUNCTION__, static_cast<int>(eSetupElementType));

    switch (eSetupElementType)
    {
    case CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER:
    {
        if (m_pDoodleSetupModel != nullptr)
        {
            if(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER != doodleSetupExpandedElement())
            {
                setDoodleSetupExpandedElement(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER);
            }
            else
            {
                setDoodleSetupExpandedElement(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_UNKNOWN);
            }
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s, m_pDoodleSetupModel not created", __FUNCTION__);
        }
    }
        break;

    case CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE:
    {
        if (m_pDoodleSetupModel != nullptr)
        {
            if(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE != doodleSetupExpandedElement())
            {
                setDoodleSetupExpandedElement(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE);
            }
            else
            {
                setDoodleSetupExpandedElement(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_UNKNOWN);
            }
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s, m_pDoodleSetupModel not created", __FUNCTION__);
        }
    }
        break;

    case CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER_ACTIVATE:
    {
        setForceShowDoodleOnScreen(false);
        setDoodleActivated(!doodleActivated());
        //Fix Me: Need to handle as per clear status
        setDoodleImageURL("file://opt/hmi/Gfx_doodle_Doodle Startup.png");
    }
        break;

    case CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER_PREVIEW:
    {
        setForceShowDoodleOnScreen(false);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_DOODLE_MYSTICKER_ICON_PREVIEW);
    }
        break;

    case CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER_CLEAR:
    {
        setForceShowDoodleOnScreen(false);
        //Fix Me: Need to handle as per clear status
        setDoodleImageURL("qrc:/image/Doodle/Gfx_doodle_stickerShapes_7in_n-assets/Gfx_doodle_Doodle_default_picture1.png");
    }
        break;

    case CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE_ACTIVATE:
    {
        setForceShowDoodleOnScreen(false);
        bool bToggleStatus = ((CDoodleSetupListElement*)m_lDoodleSetupElementsData[CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE_ACTIVATE])->toggleStatus();
        ((CDoodleSetupListElement*)m_lDoodleSetupElementsData[CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE_ACTIVATE])->setToggleStatus(!bToggleStatus);
        //Fix Me: Need to handle as per clear status
        setStartupImageURL("file://opt/hmi/Gfx_doodle_Startup_Image_default_P2.png");
    }
        break;

    case CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE_PREVIEW:
    {
        setForceShowDoodleOnScreen(false);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_DOODLE_STARTUP_IMAGE_PREVIEW);
    }
        break;

    case CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE_CLEAR:
    {
        setForceShowDoodleOnScreen(false);
        //Fix Me: Need to handle as per clear status
        setStartupImageURL("qrc:/image/Doodle/Gfx_doodle_stickerShapes_7in_n-assets/Gfx_doodle_default_picture_P1.png");
    }
        break;

    case CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_UNKNOWN:
    case CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_TOTAL_COUNT:
    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s, eSetupElementType:%d not handled", __FUNCTION__, static_cast<int>(eSetupElementType));
    }
        break;
    }
}
//____________________________________________________________________________
bool CDoodleAdaptor::eventFilter(QObject *pQObject, QEvent *pQEvent)
{
    if (doodleAvailable())
    {
        QEvent::Type eventType = pQEvent->type();
        if ((eventType == QEvent::TouchBegin) || (eventType == QEvent::TouchEnd) || (eventType == QEvent::TouchUpdate))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s Touch eventType:%d", __FUNCTION__, static_cast<int>(eventType));
            doodleWaitTimerRestart();
        }
        else if ((eventType == QEvent::MouseButtonPress) || (eventType == QEvent::MouseButtonRelease) || (eventType == QEvent::MouseButtonDblClick))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s Mouse eventType:%d", __FUNCTION__, static_cast<int>(eventType));
            doodleWaitTimerRestart();
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        //Do Nothing!
    }

    // standard event processing
    return QObject::eventFilter(pQObject, pQEvent);
}
//____________________________________________________________________________
void CDoodleAdaptor::handleHardKeys(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s: eKey:%d, eKeyState:%d", __FUNCTION__, static_cast<int>(eKey), static_cast<int>(eKeyState));

    switch (eKey)
    {
    case CHardKeyEnum::EHardKeys::KEYCODEHK_VOLROTARY:
    case CHardKeyEnum::EHardKeys::KEYCODEHK_VOLROTARY_KNOB:
    case CHardKeyEnum::EHardKeys::KEYCODEHK_SEEKDOWN:
    case CHardKeyEnum::EHardKeys::KEYCODEHK_SEEKUP:
    case CHardKeyEnum::EHardKeys::KEYCODESWC_REJECT_MUTE:
    case CHardKeyEnum::EHardKeys::KEYCODESWC_PREV:
    case CHardKeyEnum::EHardKeys::KEYCODESWC_NEXT:
    case CHardKeyEnum::EHardKeys::KEYCODESWC_UP:
    case CHardKeyEnum::EHardKeys::KEYCODESWC_DOWN:
    {
        // Do nothing!
    }
        break;
    default:
    {
        tryHideDoodleFromScreen();
    }
    }

    if (doodleAvailable())
    {
        switch (eKeyState)
        {
        case CHardKeyEnum::EHardKeyState::HKEY_STATE_PRESSED:
        case CHardKeyEnum::EHardKeyState::HKEY_STATE_LONGPRESSED:
        {
            doodleWaitTimerStop();
        }
            break;
        case CHardKeyEnum::EHardKeyState::HKEY_STATE_RELEASED:
        case CHardKeyEnum::EHardKeyState::HKEY_STATE_LONGRELEASED:
        case CHardKeyEnum::EHardKeyState::HKEY_STATE_ROTATE_LEFT:
        case CHardKeyEnum::EHardKeyState::HKEY_STATE_ROTATE_RIGHT:
        {
            doodleWaitTimerRestart();
        }
            break;
        case CHardKeyEnum::EHardKeyState::HKEY_STATE_INVALID:
        case CHardKeyEnum::EHardKeyState::HKEY_STATE_STUCK:
        default:
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s Unhandled key event", __FUNCTION__);
        }
            break;
        }
    }
    else
    {
        //Do Nothing!
    }
}
//____________________________________________________________________________
void CDoodleAdaptor::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);

    connect(CVariantControlAdaptor::getInstance(), SIGNAL(sigEOLHMIDoodleEnabledChanged()), this, SLOT(sltDoodleEOLEnabled()));
    connect(m_pDoodleWaitTimer, SIGNAL(timeout()), this, SLOT(sltDoodleWaitTimeEnded()));
    connect(CPopupManager::getInstance(),SIGNAL(sigPopupResult(CPopupEnum::EPopupID,CPopupEnum::EPopupResult, QString)),this,SLOT(sltPopupResult(CPopupEnum::EPopupID,CPopupEnum::EPopupResult, QString)));
    connect(CDrawersAdaptor::getInstance(), SIGNAL(sigQadDrawerStateChanged()), this, SLOT(sltDrawerStateChanged()));
    connect(CDrawersAdaptor::getInstance(), SIGNAL(sigShortcutDrawerStateChanged()), this, SLOT(sltDrawerStateChanged()));
    connect(CDrawersAdaptor::getInstance(), SIGNAL(sigShortcutDrawerStateChanged()), this, SLOT(sltDrawerStateChanged()));
    connect(CAndroidAutoAdaptor::getInstance(), SIGNAL(sigAndroidAutoConnectionStatusChanged(bool)), this, SLOT(sltActiveChanged_AndroidAuto(bool)));
    connect(CAppleCarPlayAdaptor::getInstance(), SIGNAL(sigAppleCarPlayConnectionStatusChanged(bool)), this, SLOT(sltActiveChanged_CarPlay(bool)));
    connect(CAudioAdaptor::getInstance(), SIGNAL(sigUSBSrcStatuschanged()), this, SLOT(sltActiveChanged_USB()));
    connect(CAudioAdaptor::getInstance(), SIGNAL(sigAUXConnectionStatuschanged()), this, SLOT(sltAvailabilityChanged_AuxIn()));
}
//____________________________________________________________________________
void CDoodleAdaptor::disconnectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);

    disconnect(CVariantControlAdaptor::getInstance(), SIGNAL(sigEOLHMIDoodleEnabledChanged()), this, SLOT(sltDoodleEOLEnabled()));
    disconnect(m_pDoodleWaitTimer, SIGNAL(timeout()), this, SLOT(sltDoodleWaitTimeEnded()));
    disconnect(CPopupManager::getInstance(),SIGNAL(sigPopupResult(CPopupEnum::EPopupID,CPopupEnum::EPopupResult, QString)),this,SLOT(sltPopupResult(CPopupEnum::EPopupID,CPopupEnum::EPopupResult, QString)));
    disconnect(CDrawersAdaptor::getInstance(), SIGNAL(sigQadDrawerStateChanged()), this, SLOT(sltDrawerStateChanged()));
    disconnect(CDrawersAdaptor::getInstance(), SIGNAL(sigShortcutDrawerStateChanged()), this, SLOT(sltDrawerStateChanged()));
    disconnect(CAndroidAutoAdaptor::getInstance(), SIGNAL(sigAndroidAutoConnectionStatusChanged(bool)), this, SLOT(sltActiveChanged_AndroidAuto(bool)));
    disconnect(CAppleCarPlayAdaptor::getInstance(), SIGNAL(sigAppleCarPlayConnectionStatusChanged(bool)), this, SLOT(sltActiveChanged_CarPlay(bool)));
    disconnect(CAudioAdaptor::getInstance(), SIGNAL(sigUSBSrcStatuschanged()), this, SLOT(sltActiveChanged_USB()));
    disconnect(CAudioAdaptor::getInstance(), SIGNAL(sigAUXConnectionStatuschanged()), this, SLOT(sltAvailabilityChanged_AuxIn()));
}
//____________________________________________________________________________
void CDoodleAdaptor::updateDoodlePermissions()
{
    if (doodleAvailable() && allowDoodleOnDrawer())
    {
        qGuiApp->installEventFilter(this);
        doodleWaitTimerStart();
        if (forceShowDoodleOnScreen())
        {
            tryShowDoodleOnScreen();
        }
        else
        {
            //Do Nothing!
        }
    }
    else
    {
        qGuiApp->removeEventFilter(this);
        tryHideDoodleFromScreen();
        doodleWaitTimerStop();
    }
}
//____________________________________________________________________________
bool CDoodleAdaptor::doodleWaitTimerRunning()
{
    bool bRunning = false;
    if (nullptr != m_pDoodleWaitTimer)
    {
        bRunning = m_pDoodleWaitTimer->isActive();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s m_pDoodleWaitTimer not created", __FUNCTION__);
    }
    return bRunning;
}
//____________________________________________________________________________
void CDoodleAdaptor::doodleWaitTimerStart()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);

    if (nullptr != m_pDoodleWaitTimer)
    {
        m_pDoodleWaitTimer->start();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s m_pDoodleWaitTimer not created", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDoodleAdaptor::doodleWaitTimerStop()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);

    if (nullptr != m_pDoodleWaitTimer)
    {
        m_pDoodleWaitTimer->stop();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s m_pDoodleWaitTimer not created", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDoodleAdaptor::doodleWaitTimerRestart()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);

    if (nullptr != m_pDoodleWaitTimer)
    {
        m_pDoodleWaitTimer->stop();
        m_pDoodleWaitTimer->start();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s m_pDoodleWaitTimer not created", __FUNCTION__);
    }
}
//____________________________________________________________________________
bool CDoodleAdaptor::tryAddStickerGroupInDoodleSetupList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    bool bStatus = false;

    if (m_pDoodleSetupModel != nullptr)
    {
        int iIndexClear =   m_pDoodleSetupModel->tryAddListElementTypeAfterElement(static_cast<int>(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER_CLEAR), static_cast<int>(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER));
        int iIndexPreview = m_pDoodleSetupModel->tryAddListElementTypeAfterElement(static_cast<int>(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER_PREVIEW), static_cast<int>(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER));
        int iIndexActive =  m_pDoodleSetupModel->tryAddListElementTypeAfterElement(static_cast<int>(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER_ACTIVATE), static_cast<int>(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER));

        LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s iIndexActive:%d, iIndexPreview:%d, iIndexClear:%d", __FUNCTION__, iIndexActive, iIndexPreview, iIndexClear);
        bStatus = !((iIndexClear < 0) || (iIndexPreview < 0) ||(iIndexActive < 0));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s, m_pDoodleSetupModel not created", __FUNCTION__);
    }

    return bStatus;
}
//____________________________________________________________________________
bool CDoodleAdaptor::tryRemoveStickerGroupFromDoodleSetupList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    bool bStatus = false;

    if (m_pDoodleSetupModel != nullptr)
    {
        bool bStatusActive =    m_pDoodleSetupModel->tryRemoveListElementType(static_cast<int>(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER_ACTIVATE));
        bool bStatusPreview =   m_pDoodleSetupModel->tryRemoveListElementType(static_cast<int>(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER_PREVIEW));
        bool bStatusClear =     m_pDoodleSetupModel->tryRemoveListElementType(static_cast<int>(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_MY_STICKER_CLEAR));

        LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s bStatusActive:%d, bStatusPreview:%d, bStatusClear:%d", __FUNCTION__, bStatusActive, bStatusPreview, bStatusClear);
        bStatus = (bStatusActive && bStatusPreview && bStatusClear);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s, m_pDoodleSetupModel not created", __FUNCTION__);
    }

    return bStatus;
}
//____________________________________________________________________________
bool CDoodleAdaptor::tryAddStartupImageGroupInDoodleSetupList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    bool bStatus = false;

    if (m_pDoodleSetupModel != nullptr)
    {
        int iIndexClear =   m_pDoodleSetupModel->tryAddListElementTypeAfterElement(static_cast<int>(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE_CLEAR), static_cast<int>(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE));
        int iIndexPreview = m_pDoodleSetupModel->tryAddListElementTypeAfterElement(static_cast<int>(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE_PREVIEW), static_cast<int>(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE));
        int iIndexActive =  m_pDoodleSetupModel->tryAddListElementTypeAfterElement(static_cast<int>(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE_ACTIVATE), static_cast<int>(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE));

        LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s iIndexActive:%d, iIndexPreview:%d, iIndexClear:%d", __FUNCTION__, iIndexActive, iIndexPreview, iIndexClear);
        bStatus = !((iIndexClear < 0) || (iIndexPreview < 0) ||(iIndexActive < 0));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s, m_pDoodleSetupModel not created", __FUNCTION__);
    }

    return bStatus;
}
//____________________________________________________________________________
bool CDoodleAdaptor::tryRemoveStartupImageGroupFromDoodleSetupList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    bool bStatus = false;

    if (m_pDoodleSetupModel != nullptr)
    {
        bool bStatusActive =    m_pDoodleSetupModel->tryRemoveListElementType(static_cast<int>(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE_ACTIVATE));
        bool bStatusPreview =   m_pDoodleSetupModel->tryRemoveListElementType(static_cast<int>(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE_PREVIEW));
        bool bStatusClear =     m_pDoodleSetupModel->tryRemoveListElementType(static_cast<int>(CDoodleEnum::EDoodleSetupElementTypes::DOODLE_SETUP_STARTUP_IMAGE_CLEAR));

        LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s bStatusActive:%d, bStatusPreview:%d, bStatusClear:%d", __FUNCTION__, bStatusActive, bStatusPreview, bStatusClear);
        bStatus = (bStatusActive && bStatusPreview && bStatusClear);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s, m_pDoodleSetupModel not created", __FUNCTION__);
    }

    return bStatus;
}
//____________________________________________________________________________
