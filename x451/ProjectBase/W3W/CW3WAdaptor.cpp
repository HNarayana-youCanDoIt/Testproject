/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CW3WAdaptor.cpp
 * @ingroup         HMIComponent
 * @author          Nishant Khandagale
 * CW3WAdaptor, an Adaptor for W3W module,
 * CW3WAdaptor is class used to communicate with qml, resources of W3W module.
 */

#include "ResourceFactory.hpp"
#include "HMIIncludes.h"

#include "CW3WApplication.h"
#include "CW3WAdaptor.h"
#include "CW3WSM.h"
#include "CW3WEventHandler.h"
#include "CW3WEnum.h"
#include "CW3WSetupListModel.h"
#include "CVariantControlAdaptor.h"
#include "CPhoneAdaptor.h"
#include "CAudioAdaptor.h"
#include "CVRAdaptor.h"
#include "CPersistencyAdaptor.h"
#include "W3WResource/implementations/CW3WResourceImpl.h"

// files included for launching AA and CP
#include <AndroidAuto/CAndroidAutoAdaptor.h>
#include <CarPlay/CAppleCarPlayAdaptor.h>

CW3WAdaptor::CW3WAdaptor(QObject *parent) :
    QObject(parent),
    m_pW3WSetupListModel(nullptr),
    m_pW3WAboutListModel(nullptr),
    m_pW3WAutoSuggestionListModel(nullptr),
    m_pW3WFavoriteListModel(nullptr),
    m_pW3WRecentListModel(nullptr),
    m_strW3WAddressInputText(""),
    m_bAutoSuggestionReceivedStatus(false),
    m_SelectedW3WAddressItem(),
    m_SelectedW3WAddressItemForDelete(),
    m_SelectedW3WAddressItemForFavorite(),
    m_CurrentW3WAddressType(CW3WEnum::W3W_ADDRESS_TYPE_INVALID),
    m_FavoriteOperation(CW3WEnum::W3W_FAVORITE_OPERATION_INVALID),
    m_bW3WCoreProxyStatus(false),
    m_bW3WPluginProxyStatus(false),
    m_pW3WResource(dynamic_cast<CW3WResourceImpl*>(ResourceFactory::getW3WResource())),
    m_CurrentCountryCode(""),
    m_connNextConnStatus(1), //Failure
    m_LastNavigatedW3WAddress(""),
    m_W3WCoordinates(),
    m_W3WAddress("")
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    CFramework::getFramework().setContextProperty("cppW3WAdaptor",this);
    CW3WEnum::registerW3WEnumsToQML();

    connect(CPopupManager::getInstance(), SIGNAL(sigPopupResult(CPopupEnum::EPopupID, CPopupEnum::EPopupResult, QString)), this, SLOT(sltPopupResult(CPopupEnum::EPopupID, CPopupEnum::EPopupResult, QString)));

    fillKeypadButtonDataMap();
    fillFlagsDataMap();

    /* Setup Model needs to be created on startup, to listen to the settings on start up */
    createW3WSetupListModel();

    /* As there is state transition from Favorite/Recent to EditLabel screen, the model needs to be
     * alive when Favorite/Recent state is lauunched again from EditLabel screen */
    createW3WFavoriteListModel();
    createW3WRecentListModel();
}

CW3WAdaptor::~CW3WAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);

    disconnect(CPopupManager::getInstance(), SIGNAL(sigPopupResult(CPopupEnum::EPopupID, CPopupEnum::EPopupResult, QString)), this, SLOT(sltPopupResult(CPopupEnum::EPopupID, CPopupEnum::EPopupResult, QString)));

    deleteW3WSetupListModel();
    deleteW3WAboutListModel();
    deleteW3WAutoSuggestionListModel();

    deleteW3WFavoriteListModel();
    deleteW3WRecentListModel();
}

bool CW3WAdaptor::w3wFeatureSupportStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    return ( CVariantControlAdaptor::getInstance()->eolW3WEnabled() &&
            ( CVariantControlAdaptor::getInstance()->eolAndroidAutoEnabled() || CVariantControlAdaptor::getInstance()->eolAppleCarPlayEnabled()));
}

void CW3WAdaptor::createW3WSetupListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    m_pW3WSetupListModel = new CW3WSetupListModel(this);
}

void CW3WAdaptor::deleteW3WSetupListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    if(m_pW3WSetupListModel)
    {
        delete m_pW3WSetupListModel;
        m_pW3WSetupListModel = nullptr;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s: W3W setup list model instance already destroyed", __FUNCTION__);
    }
}

void CW3WAdaptor::createW3WAboutListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    m_pW3WAboutListModel = new CW3WAboutListModel(this);
}

void CW3WAdaptor::deleteW3WAboutListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    if(m_pW3WAboutListModel)
    {
        delete m_pW3WAboutListModel;
        m_pW3WAboutListModel = nullptr;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s: W3W about list model instance already destroyed", __FUNCTION__);
    }
}

void CW3WAdaptor::createW3WAutoSuggestionListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    m_pW3WAutoSuggestionListModel = new CW3WAutoSuggestionListModel(this);
}

void CW3WAdaptor::deleteW3WAutoSuggestionListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    if(m_pW3WAutoSuggestionListModel)
    {
        delete m_pW3WAutoSuggestionListModel;
        m_pW3WAutoSuggestionListModel = nullptr;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s: W3W auto suggestion list model instance already destroyed", __FUNCTION__);
    }
}

void CW3WAdaptor::createW3WFavoriteListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    m_pW3WFavoriteListModel = new CW3WFavoriteListModel(this);
}

void CW3WAdaptor::deleteW3WFavoriteListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    if(m_pW3WFavoriteListModel)
    {
        delete m_pW3WFavoriteListModel;
        m_pW3WFavoriteListModel = nullptr;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s: W3W Favorite list model instance already destroyed", __FUNCTION__);
    }
}

void CW3WAdaptor::createW3WRecentListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    m_pW3WRecentListModel = new CW3WRecentListModel(this);
}

void CW3WAdaptor::deleteW3WRecentListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    if(m_pW3WRecentListModel)
    {
        delete m_pW3WRecentListModel;
        m_pW3WRecentListModel = nullptr;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s: W3W Recent list model instance already destroyed", __FUNCTION__);
    }
}

void CW3WAdaptor::updateSetupListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    if(m_pW3WSetupListModel)
    {
        /* Update the Auto Launch Permission settings in Setup List model */
        m_pW3WSetupListModel->updateAutoLaunchPermissionList();
        /* Update the Walkthrough on Startup settings in Setup List model */
        m_pW3WSetupListModel->updateStartupWalkthroughMenu();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s: W3W setup list model is null", __FUNCTION__);
    }
}

void CW3WAdaptor::invUpdateCheckboxSetting(int iItemId, bool bIsChecked)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s: iItemId: %d bIsChecked: %d", __FUNCTION__, iItemId, bIsChecked);

    if(m_pW3WSetupListModel)
    {
        if(CW3WEnum::W3W_SETUP_AUTOLAUNCH_PERMISSIONS_AA == iItemId)
        {
            invSetAutoLaunchPermissionStatusForAA(bIsChecked);
            /* Update the Auto Launch Permission settings in Setup List model */
            m_pW3WSetupListModel->updateAutoLaunchPermissionList();
        }
        else if(CW3WEnum::W3W_SETUP_AUTOLAUNCH_PERMISSIONS_CP == iItemId)
        {
            invSetAutoLaunchPermissionStatusForCP(bIsChecked);
            /* Update the Auto Launch Permission settings in Setup List model */
            m_pW3WSetupListModel->updateAutoLaunchPermissionList();
        }
        else if(CW3WEnum::W3W_SETUP_STARTUP_WALKTHROUGH == iItemId)
        {
            invSetStartupWalkthroughStatus(bIsChecked);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s: Invalid iItemId: %d", __FUNCTION__, iItemId);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s: W3W setup list model is null", __FUNCTION__);
    }
}

void CW3WAdaptor::invSetAutoLaunchPermissionStatusForAA(bool autoLaunchPermission)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s autoLaunchPermission: %d", __FUNCTION__, autoLaunchPermission);
    CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_W3W_AUTOLAUNCH_ANDROID_AUTO, autoLaunchPermission);
}

bool CW3WAdaptor::autoLaunchPermissionStatusForAA()
{
    return CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_W3W_AUTOLAUNCH_ANDROID_AUTO);
}

void CW3WAdaptor::invSetAutoLaunchPermissionStatusForCP(bool autoLaunchPermission)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s autoLaunchPermission: %d", __FUNCTION__, autoLaunchPermission);
    CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_W3W_AUTOLAUNCH_APPLE_CARPLAY, autoLaunchPermission);
}

bool CW3WAdaptor::autoLaunchPermissionStatusForCP()
{
    return CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_W3W_AUTOLAUNCH_APPLE_CARPLAY);
}

void CW3WAdaptor::invSetStartupWalkthroughStatus(bool startupWalkthroughStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s autoLaunchPermission: %d", __FUNCTION__, startupWalkthroughStatus);
    CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_W3W_STARTUP_WALKTHROUGH, startupWalkthroughStatus);
}

bool CW3WAdaptor::startupWalkthroughStatus()
{
    return CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_W3W_STARTUP_WALKTHROUGH);
}

void CW3WAdaptor::fillKeypadButtonDataMap()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    int iIndex = 1;
    m_mapKeypadButtonData.clear();

    /* Insert SW3WAddressSuggestionKeypadData struct variable in map with Default Image, Pressed Image, Disabled Image path and
     * character to input for this keypad button in Edit box
     */
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallQ_7in_n-assets/Set_Btn_KeyPad_SmallQ_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallQ_7in_n-assets/Set_Btn_KeyPad_SmallQ_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallQ_7in_n-assets/Set_Btn_KeyPad_SmallQ_7in_nd.png",
                                     'q'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallW_7in_n-assets/Set_Btn_KeyPad_SmallW_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallW_7in_n-assets/Set_Btn_KeyPad_SmallW_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallW_7in_n-assets/Set_Btn_KeyPad_SmallW_7in_nd.png",
                                     'w'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallE_7in_n-assets/Set_Btn_KeyPad_SmallE_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallE_7in_n-assets/Set_Btn_KeyPad_SmallE_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallE_7in_n-assets/Set_Btn_KeyPad_SmallE_7in_nd.png",
                                     'e'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallR_7in_n-assets/Set_Btn_KeyPad_SmallR_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallR_7in_n-assets/Set_Btn_KeyPad_SmallR_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallR_7in_n-assets/Set_Btn_KeyPad_SmallR_7in_nd.png",
                                     'r'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallT_7in_n-assets/Set_Btn_KeyPad_SmallT_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallT_7in_n-assets/Set_Btn_KeyPad_SmallT_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallT_7in_n-assets/Set_Btn_KeyPad_SmallT_7in_nd.png",
                                     't'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallY_7in_n-assets/Set_Btn_KeyPad_SmallY_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallY_7in_n-assets/Set_Btn_KeyPad_SmallY_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallY_7in_n-assets/Set_Btn_KeyPad_SmallY_7in_nd.png",
                                     'y'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallU_7in_n-assets/Set_Btn_KeyPad_SmallU_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallU_7in_n-assets/Set_Btn_KeyPad_SmallU_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallU_7in_n-assets/Set_Btn_KeyPad_SmallU_7in_nd.png",
                                     'u'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallI_7in_n-assets/Set_Btn_KeyPad_SmallI_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallI_7in_n-assets/Set_Btn_KeyPad_SmallI_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallI_7in_n-assets/Set_Btn_KeyPad_SmallI_7in_nd.png",
                                     'i'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallO_7in_n-assets/Set_Btn_KeyPad_SmallO_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallO_7in_n-assets/Set_Btn_KeyPad_SmallO_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallO_7in_n-assets/Set_Btn_KeyPad_SmallO_7in_nd.png",
                                     'o'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallP_7in_n-assets/Set_Btn_KeyPad_SmallP_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallP_7in_n-assets/Set_Btn_KeyPad_SmallP_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallP_7in_n-assets/Set_Btn_KeyPad_SmallP_7in_nd.png",
                                     'p'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Gen_Set_Ico_Delete_7in_n-assets/Gen_Set_Ico_Delete_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Gen_Set_Ico_Delete_7in_n-assets/Gen_Set_Ico_Delete_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Gen_Set_Ico_Delete_7in_n-assets/Gen_Set_Ico_Delete_7in_nd.png"
                                     ));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallA_7in_n-assets/Set_Btn_KeyPad_SmallA_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallA_7in_n-assets/Set_Btn_KeyPad_SmallA_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallA_7in_n-assets/Set_Btn_KeyPad_SmallA_7in_nd.png",
                                     'a'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallS_7in_n-assets/Set_Btn_KeyPad_SmallS_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallS_7in_n-assets/Set_Btn_KeyPad_SmallS_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallS_7in_n-assets/Set_Btn_KeyPad_SmallS_7in_nd.png",
                                     's'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallD_7in_n-assets/Set_Btn_KeyPad_SmallD_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallD_7in_n-assets/Set_Btn_KeyPad_SmallD_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallD_7in_n-assets/Set_Btn_KeyPad_SmallD_7in_nd.png",
                                     'd'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallF_7in_n-assets/Set_Btn_KeyPad_SmallF_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallF_7in_n-assets/Set_Btn_KeyPad_SmallF_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallF_7in_n-assets/Set_Btn_KeyPad_SmallF_7in_nd.png",
                                     'f'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallG_7in_n-assets/Set_Btn_KeyPad_SmallG_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallG_7in_n-assets/Set_Btn_KeyPad_SmallG_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallG_7in_n-assets/Set_Btn_KeyPad_SmallG_7in_nd.png",
                                     'g'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallH_7in_n-assets/Set_Btn_KeyPad_SmallH_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallH_7in_n-assets/Set_Btn_KeyPad_SmallH_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallH_7in_n-assets/Set_Btn_KeyPad_SmallH_7in_nd.png",
                                     'h'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallJ_7in_n-assets/Set_Btn_KeyPad_SmallJ_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallJ_7in_n-assets/Set_Btn_KeyPad_SmallJ_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallJ_7in_n-assets/Set_Btn_KeyPad_SmallJ_7in_nd.png",
                                     'j'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallK_7in_n-assets/Set_Btn_KeyPad_SmallK_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallK_7in_n-assets/Set_Btn_KeyPad_SmallK_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallK_7in_n-assets/Set_Btn_KeyPad_SmallK_7in_nd.png",
                                     'k'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallL_7in_n-assets/Set_Btn_KeyPad_SmallL_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallL_7in_n-assets/Set_Btn_KeyPad_SmallL_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallL_7in_n-assets/Set_Btn_KeyPad_SmallL_7in_nd.png",
                                     'l'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_nd.png"
                                     ));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallZ_7in_n-assets/Set_Btn_KeyPad_SmallZ__7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallZ_7in_n-assets/Set_Btn_KeyPad_SmallZ__7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallZ_7in_n-assets/Set_Btn_KeyPad_SmallZ__7in_nd.png",
                                     'z'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallX_7in_n-assets/Set_Btn_KeyPad_SmallX_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallX_7in_n-assets/Set_Btn_KeyPad_SmallX_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallX_7in_n-assets/Set_Btn_KeyPad_SmallX_7in_nd.png",
                                     'x'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallC_7in_n-assets/Set_Btn_KeyPad_SmallC_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallC_7in_n-assets/Set_Btn_KeyPad_SmallC_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallC_7in_n-assets/Set_Btn_KeyPad_SmallC_7in_nd.png",
                                     'c'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallV_7in_n-assets/Set_Btn_KeyPad_SmallV_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallV_7in_n-assets/Set_Btn_KeyPad_SmallV_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallV_7in_n-assets/Set_Btn_KeyPad_SmallV_7in_nd.png",
                                     'v'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallB_7in_n-assets/Set_Btn_KeyPad_SmallB_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallB_7in_n-assets/Set_Btn_KeyPad_SmallB_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallB_7in_n-assets/Set_Btn_KeyPad_SmallB_7in_nd.png",
                                     'b'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallN_7in_n-assets/Set_Btn_KeyPad_SmallN_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallN_7in_n-assets/Set_Btn_KeyPad_SmallN_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallN_7in_n-assets/Set_Btn_KeyPad_SmallN_7in_nd.png",
                                     'n'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallM_7in_n-assets/Set_Btn_KeyPad_SmallM_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallM_7in_n-assets/Set_Btn_KeyPad_SmallM_7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_SmallM_7in_n-assets/Set_Btn_KeyPad_SmallM_7in_nd.png",
                                     'm'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_Capital._7in_n-assets/Set_Btn_Key_Cap._7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_Capital._7in_n-assets/Set_Btn_Key_Cap._7in_nf.png",
                                     "qrc:/image/W3W/KeyPad/Set_Btn_KeyPad_Capital._7in_n-assets/Set_Btn_Key_Cap._7in_nd.png",
                                     '.'));  iIndex++;
    m_mapKeypadButtonData.insert(iIndex, CW3WData::SW3WAddressSuggestionKeypadData(
                                     "qrc:/image/W3W/KeyPad/Gen_Ico_ArrowForward_7in_n-assets/Gen_Ico_SetArrowBottom_7in_n.png",
                                     "qrc:/image/W3W/KeyPad/Gen_Ico_ArrowForward_7in_n-assets/Gen_Ico_SetArrowBottom_7in_np.png",
                                     "qrc:/image/W3W/KeyPad/Gen_Ico_ArrowForward_7in_n-assets/Gen_Ico_SetArrowBottom_7in_nd.png"
                                     ));  iIndex++;
}

QString CW3WAdaptor::getKeyButtonDefaultImage(int iKeyIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s: iKeyIndex: %d", __FUNCTION__, iKeyIndex);

    QString strImagePath = "";
    if( (0 < iKeyIndex)  && (KEYPAD_CHAR_ARRAY_COUNT >= iKeyIndex) )
    {
        strImagePath = m_mapKeypadButtonData[iKeyIndex].m_strKeyButtonDefaultImage;
    }
    return strImagePath;
}

QString CW3WAdaptor::getKeyButtonPressedImage(int iKeyIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s: iKeyIndex: %d", __FUNCTION__, iKeyIndex);

    QString strImagePath = "";
    if( (0 < iKeyIndex)  && (KEYPAD_CHAR_ARRAY_COUNT >= iKeyIndex) )
    {
        strImagePath = m_mapKeypadButtonData[iKeyIndex].m_strKeyButtonPressedImage;
    }
    return strImagePath;
}

QString CW3WAdaptor::getKeyButtonDisabledImage(int iKeyIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s: iKeyIndex: %d", __FUNCTION__, iKeyIndex);

    QString strImagePath = "";
    if( (0 < iKeyIndex)  && (KEYPAD_CHAR_ARRAY_COUNT >= iKeyIndex) )
    {
        strImagePath = m_mapKeypadButtonData[iKeyIndex].m_strKeyButtonDisabledImage;
    }
    return strImagePath;
}

QChar CW3WAdaptor::getClickedCharacter(int iCharIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s: iCharIndex: %d", __FUNCTION__, iCharIndex);

    if( (0 < iCharIndex) && (KEYPAD_CHAR_ARRAY_COUNT > iCharIndex) )
    {
        return m_mapKeypadButtonData[iCharIndex].m_cKeyButtonInputChar;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s: Index of Out Bound ,iCharIndex: %d", __FUNCTION__, iCharIndex);
        return -1;
    }
}

void CW3WAdaptor::setW3WAddressInputText(const QString &strInputText)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s: strInputText: %s", __FUNCTION__, strInputText.toStdString().c_str());
    if(m_strW3WAddressInputText != strInputText)
    {
        m_strW3WAddressInputText = strInputText;

        if(isTextReadyForAutoSuggestion(m_strW3WAddressInputText))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Text ready for auto suggestion", m_strW3WAddressInputText.toStdString().c_str());
            if (nullptr != m_pW3WResource)
            {
                m_pW3WResource->getAutoSuggestions(m_strW3WAddressInputText.toStdString());
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, W3W resource is null", __FUNCTION__);
            }
        }
        else
        {
            //Do nothing
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Input text not changed", __FUNCTION__);
    }
}

QString CW3WAdaptor::w3wAddressInputText()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s", __FUNCTION__);
    return m_strW3WAddressInputText;
}

void CW3WAdaptor::setAutoSuggestionRecievedStatus(bool bAutoSuggestionRecivedStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s: bAutoSuggestionRecivedStatus: %d", __FUNCTION__, bAutoSuggestionRecivedStatus);

    if(m_bAutoSuggestionReceivedStatus != bAutoSuggestionRecivedStatus)
    {
        m_bAutoSuggestionReceivedStatus = bAutoSuggestionRecivedStatus;
        emit sigAutoSuggestionRecievedStatusChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Auto Suggestion Recived Status not changed", __FUNCTION__);
    }
}

bool CW3WAdaptor::autoSuggestionRecievedStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s", __FUNCTION__);
    return m_bAutoSuggestionReceivedStatus;
}

bool CW3WAdaptor::isTextReadyForAutoSuggestion(const QString &strInputText)
{
    /** Entered text shall have the first 2 words followed by "." and the first letter of the 3rd word
     *  to be ready for sending to W3W Service
     */
    if( (strInputText.count('.') >= 2) &&
            ( (strInputText.lastIndexOf('.') + 1) < strInputText.length() ) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CW3WAdaptor::invSelectW3WAddressItem(CW3WEnum::EW3WAddressType addressType, int itemId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, addressType: %d itemId:%d", __FUNCTION__, static_cast<int>(addressType), itemId);

    CW3WData::SW3WAddressData w3wAddressDataItem;

    if(CW3WEnum::W3W_ADDRESS_TYPE_AUTO_SUGGESTION == addressType)
    {
        w3wAddressDataItem = m_pW3WAutoSuggestionListModel->getAutoSuggestionData(itemId);
        setSelectedW3WAddressItem(w3wAddressDataItem);
    }
    else if(CW3WEnum::W3W_ADDRESS_TYPE_FAVORITE == addressType)
    {
        w3wAddressDataItem = m_pW3WFavoriteListModel->getFavoriteData(itemId);
        setSelectedW3WAddressItem(w3wAddressDataItem);
    }
    else if(CW3WEnum::W3W_ADDRESS_TYPE_RECENT == addressType)
    {
        w3wAddressDataItem = m_pW3WRecentListModel->getRecentData(itemId);
        setSelectedW3WAddressItem(w3wAddressDataItem);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Invalid addressType", __FUNCTION__);
    }
}

void CW3WAdaptor::setSelectedW3WAddressItem(const CW3WData::SW3WAddressData selectedW3WAddressItem)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, address : %s, languageCode : %s, countryCode : %s, nearestPlace : %s, addressLabel : %s, itemType: %d, itemId : %d",
             __FUNCTION__, selectedW3WAddressItem.m_W3WAddress.toStdString().c_str(), selectedW3WAddressItem.m_W3WLanguageCode.toStdString().c_str(),
             selectedW3WAddressItem.m_W3WCountryCode.toStdString().c_str(), selectedW3WAddressItem.m_W3WNearestPlace.toStdString().c_str(), selectedW3WAddressItem.m_W3WAddressLabel.toStdString().c_str(),
             selectedW3WAddressItem.m_W3WItemType, selectedW3WAddressItem.m_ItemId);

    if( (m_SelectedW3WAddressItem.m_ItemId != selectedW3WAddressItem.m_ItemId) ||
        (m_SelectedW3WAddressItem.m_W3WAddress != selectedW3WAddressItem.m_W3WAddress) ||
        (m_SelectedW3WAddressItem.m_W3WLanguageCode != selectedW3WAddressItem.m_W3WLanguageCode) ||
        (m_SelectedW3WAddressItem.m_W3WCountryCode != selectedW3WAddressItem.m_W3WCountryCode) ||
        (m_SelectedW3WAddressItem.m_W3WNearestPlace != selectedW3WAddressItem.m_W3WNearestPlace) ||
        (m_SelectedW3WAddressItem.m_W3WAddressLabel != selectedW3WAddressItem.m_W3WAddressLabel) ||
        (m_SelectedW3WAddressItem.m_W3WItemType != selectedW3WAddressItem.m_W3WItemType) )
    {
        setSelectedW3WAddress(selectedW3WAddressItem.m_W3WAddress);
        setSelectedW3WAddressLabel(selectedW3WAddressItem.m_W3WAddressLabel);
        m_SelectedW3WAddressItem.m_W3WLanguageCode = selectedW3WAddressItem.m_W3WLanguageCode;
        m_SelectedW3WAddressItem.m_W3WCountryCode = selectedW3WAddressItem.m_W3WCountryCode;
        m_SelectedW3WAddressItem.m_W3WNearestPlace = selectedW3WAddressItem.m_W3WNearestPlace;
        m_SelectedW3WAddressItem.m_W3WItemType = selectedW3WAddressItem.m_W3WItemType;
        m_SelectedW3WAddressItem.m_ItemId = selectedW3WAddressItem.m_ItemId;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Selected W3W Address item not changed", __FUNCTION__);
    }
}

CW3WData::SW3WAddressData& CW3WAdaptor::selectedW3WAddressItem()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    return m_SelectedW3WAddressItem;
}

void CW3WAdaptor::setSelectedW3WAddress(const QString strSelectedAddress)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s: strSelectedAddress: %s", __FUNCTION__, strSelectedAddress.toStdString().c_str());
    if(m_SelectedW3WAddressItem.m_W3WAddress != strSelectedAddress)
    {
        m_SelectedW3WAddressItem.m_W3WAddress = strSelectedAddress;
        emit sigSelectedW3WAddressChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Selected address not changed", __FUNCTION__);
    }
}

QString CW3WAdaptor::selectedW3WAddress()
{
    return m_SelectedW3WAddressItem.m_W3WAddress;
}

void CW3WAdaptor::setSelectedW3WAddressLabel(const QString strSelectedAddressLabel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s: strSelectedAddressLabel: %s", __FUNCTION__, strSelectedAddressLabel.toStdString().c_str());
    if(m_SelectedW3WAddressItem.m_W3WAddressLabel != strSelectedAddressLabel)
    {
        m_SelectedW3WAddressItem.m_W3WAddressLabel = strSelectedAddressLabel;
        emit sigSelectedW3WAddressLabelChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Selected address label not changed", __FUNCTION__);
    }
}

QString CW3WAdaptor::selectedW3WAddressLabel()
{
    return m_SelectedW3WAddressItem.m_W3WAddressLabel;
}

bool CW3WAdaptor::invIsFavoriteMaxLimitReached()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    if(MAX_LIMIT_FOR_FAVORITES <= m_pW3WFavoriteListModel->rowCount())
    {
        return true;
    }
    return false;
}

void CW3WAdaptor::editLabelSaveButtonClicked(const QString &labelName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s: labelName: %s", __FUNCTION__, labelName.toStdString().c_str());

    if("" != labelName)
    {
        CW3WData::SW3WAddressData w3wAddressItem = m_SelectedW3WAddressItemForFavorite;
        w3wAddressItem.m_W3WAddressLabel = labelName;
        setSelectedW3WAddressItemForFavorite(w3wAddressItem);

        if(CW3WEnum::W3W_FAVORITE_OPERATION_ADD == m_FavoriteOperation)
        {
            invAddToFavorite();
        }
        else if(CW3WEnum::W3W_FAVORITE_OPERATION_EDIT == m_FavoriteOperation)
        {
            invEditFavorite();
        }
        else
        {
            /* Do nothing */
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, Label name empty", __FUNCTION__);
    }
}

void CW3WAdaptor::invAddToFavorite()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);

    if (nullptr != m_pW3WResource)
    {
        if(isFavoriteAlreadySaved(m_SelectedW3WAddressItemForFavorite))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Favorite already exists", __FUNCTION__);
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_W3W_FAVORITE_ALREADY_SAVED);
        }
        else
        {
            /* Convertion to the resource layer structure */
            SW3WAddressItem w3wAddressItem((m_SelectedW3WAddressItemForFavorite.m_W3WAddress).toStdString(),
                                           (m_SelectedW3WAddressItemForFavorite.m_W3WLanguageCode).toStdString(),
                                           (m_SelectedW3WAddressItemForFavorite.m_W3WCountryCode).toStdString(),
                                           (m_SelectedW3WAddressItemForFavorite.m_W3WNearestPlace).toStdString(),
                                           (m_SelectedW3WAddressItemForFavorite.m_W3WAddressLabel).toStdString(),
                                           (m_SelectedW3WAddressItemForFavorite.m_ItemId));

            m_pW3WResource->addToFavoriteList(w3wAddressItem);

            /* If Favorite is added from Recent list, then update the Recent item as well */
            if(CW3WEnum::W3W_ADDRESS_TYPE_RECENT == m_CurrentW3WAddressType)
            {
                m_pW3WResource->editFromRecentList(w3wAddressItem);
            }
            else
            {
                /* Do nothing */
            }
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, W3W resource is null", __FUNCTION__);
    }
}

void CW3WAdaptor::invEditFavorite()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);

    if (nullptr != m_pW3WResource)
    {
        if(isFavoriteAlreadySaved(m_SelectedW3WAddressItemForFavorite))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Favorite already exists", __FUNCTION__);
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_W3W_FAVORITE_ALREADY_SAVED);
        }
        else
        {
            /* Convertion to the resource layer structure */
            SW3WAddressItem w3wAddressItem((m_SelectedW3WAddressItemForFavorite.m_W3WAddress).toStdString(),
                                           (m_SelectedW3WAddressItemForFavorite.m_W3WLanguageCode).toStdString(),
                                           (m_SelectedW3WAddressItemForFavorite.m_W3WCountryCode).toStdString(),
                                           (m_SelectedW3WAddressItemForFavorite.m_W3WNearestPlace).toStdString(),
                                           (m_SelectedW3WAddressItemForFavorite.m_W3WAddressLabel).toStdString(),
                                           (m_SelectedW3WAddressItemForFavorite.m_ItemId));

            m_pW3WResource->editFromFavoriteList(w3wAddressItem);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, W3W resource is null", __FUNCTION__);
    }
}

bool CW3WAdaptor::isFavoriteAlreadySaved(CW3WData::SW3WAddressData selectedW3WAddressItemForFavorite)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    CW3WData::SW3WAddressData w3wAddressData;
    for(int index = 0; index < m_pW3WFavoriteListModel->rowCount(); index++)
    {
        w3wAddressData = m_pW3WFavoriteListModel->getFavoriteDataAtIndex(index);

        if( (w3wAddressData.m_W3WAddress == selectedW3WAddressItemForFavorite.m_W3WAddress) &&
                (w3wAddressData.m_W3WAddressLabel == selectedW3WAddressItemForFavorite.m_W3WAddressLabel) )
        {
            return true;
        }
    }
    return false;
}

void CW3WAdaptor::updateFavoriteSavedStatus(bool favoriteSavedStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s: favoriteSavedStatus: %d", __FUNCTION__, favoriteSavedStatus);

    if(favoriteSavedStatus)
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_W3W_FAVORITE_SAVED);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Unable to save favorite", __FUNCTION__);
    }

    /* To get the updated Favorite and Recent addresses */
    getFavoriteAndRecentAddresses();
}

void CW3WAdaptor::invSelectW3WAddressForFavorite(CW3WEnum::EW3WAddressType addressType, CW3WEnum::EW3WFavoriteOperation favoriteOperation, int itemId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, addressType: %d favoriteOperation: %d itemIndex:%d", __FUNCTION__, static_cast<int>(addressType), static_cast<int>(favoriteOperation), itemId);

    CW3WData::SW3WAddressData w3wAddressDataItem;

    if(CW3WEnum::W3W_ADDRESS_TYPE_SELECTED == addressType)
    {
        w3wAddressDataItem = m_SelectedW3WAddressItem;
        setSelectedW3WAddressItemForFavorite(w3wAddressDataItem);
        m_FavoriteOperation = favoriteOperation;
    }
    else if(CW3WEnum::W3W_ADDRESS_TYPE_FAVORITE == addressType)
    {
        w3wAddressDataItem = m_pW3WFavoriteListModel->getFavoriteData(itemId);
        setSelectedW3WAddressItemForFavorite(w3wAddressDataItem);
        m_FavoriteOperation = favoriteOperation;
    }
    else if(CW3WEnum::W3W_ADDRESS_TYPE_RECENT == addressType)
    {
        w3wAddressDataItem = m_pW3WRecentListModel->getRecentData(itemId);
        setSelectedW3WAddressItemForFavorite(w3wAddressDataItem);
        m_FavoriteOperation = favoriteOperation;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Invalid addressType", __FUNCTION__);
    }
}

void CW3WAdaptor::setSelectedW3WAddressItemForFavorite(const CW3WData::SW3WAddressData selectedW3WAddressItemForFavorite)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, address : %s, languageCode : %s, countryCode : %s, nearestPlace : %s, addressLabel : %s, itemType: %d, itemId : %d",
             __FUNCTION__, selectedW3WAddressItemForFavorite.m_W3WAddress.toStdString().c_str(), selectedW3WAddressItemForFavorite.m_W3WLanguageCode.toStdString().c_str(),
             selectedW3WAddressItemForFavorite.m_W3WCountryCode.toStdString().c_str(), selectedW3WAddressItemForFavorite.m_W3WNearestPlace.toStdString().c_str(),
             selectedW3WAddressItemForFavorite.m_W3WAddressLabel.toStdString().c_str(), selectedW3WAddressItemForFavorite.m_W3WItemType,
             selectedW3WAddressItemForFavorite.m_ItemId);

    if( (m_SelectedW3WAddressItemForFavorite.m_ItemId != selectedW3WAddressItemForFavorite.m_ItemId) ||
        (m_SelectedW3WAddressItemForFavorite.m_W3WAddress != selectedW3WAddressItemForFavorite.m_W3WAddress) ||
        (m_SelectedW3WAddressItemForFavorite.m_W3WLanguageCode != selectedW3WAddressItemForFavorite.m_W3WLanguageCode) ||
        (m_SelectedW3WAddressItemForFavorite.m_W3WCountryCode != selectedW3WAddressItemForFavorite.m_W3WCountryCode) ||
        (m_SelectedW3WAddressItemForFavorite.m_W3WNearestPlace != selectedW3WAddressItemForFavorite.m_W3WNearestPlace) ||
        (m_SelectedW3WAddressItemForFavorite.m_W3WAddressLabel != selectedW3WAddressItemForFavorite.m_W3WAddressLabel) ||
        (m_SelectedW3WAddressItemForFavorite.m_W3WItemType != selectedW3WAddressItemForFavorite.m_W3WItemType) )
    {
        setSelectedW3WAddressForFavorite(selectedW3WAddressItemForFavorite.m_W3WAddress);
        setSelectedW3WAddressLabelForFavorite(selectedW3WAddressItemForFavorite.m_W3WAddressLabel);
        m_SelectedW3WAddressItemForFavorite.m_W3WLanguageCode = selectedW3WAddressItemForFavorite.m_W3WLanguageCode;
        m_SelectedW3WAddressItemForFavorite.m_W3WCountryCode = selectedW3WAddressItemForFavorite.m_W3WCountryCode;
        m_SelectedW3WAddressItemForFavorite.m_W3WNearestPlace = selectedW3WAddressItemForFavorite.m_W3WNearestPlace;
        m_SelectedW3WAddressItemForFavorite.m_W3WItemType = selectedW3WAddressItemForFavorite.m_W3WItemType;
        m_SelectedW3WAddressItemForFavorite.m_ItemId = selectedW3WAddressItemForFavorite.m_ItemId;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Selected W3W Address item For Favorite not changed", __FUNCTION__);
    }
}

void CW3WAdaptor::setSelectedW3WAddressForFavorite(const QString strSelectedAddressForFavorite)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s: strSelectedAddressForFavorite: %s", __FUNCTION__, strSelectedAddressForFavorite.toStdString().c_str());
    if(m_SelectedW3WAddressItemForFavorite.m_W3WAddress != strSelectedAddressForFavorite)
    {
        m_SelectedW3WAddressItemForFavorite.m_W3WAddress = strSelectedAddressForFavorite;
        emit sigSelectedW3WAddressForFavoriteChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Selected address for favorite not changed", __FUNCTION__);
    }
}

QString CW3WAdaptor::selectedW3WAddressForFavorite()
{
    return m_SelectedW3WAddressItemForFavorite.m_W3WAddress;
}

void CW3WAdaptor::setSelectedW3WAddressLabelForFavorite(const QString strSelectedAddressLabelForFavorite)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s: strSelectedAddressLabelForFavorite: %s", __FUNCTION__, strSelectedAddressLabelForFavorite.toStdString().c_str());
    if(m_SelectedW3WAddressItemForFavorite.m_W3WAddressLabel != strSelectedAddressLabelForFavorite)
    {
        m_SelectedW3WAddressItemForFavorite.m_W3WAddressLabel = strSelectedAddressLabelForFavorite;
        emit sigSelectedW3WAddressLabelForFavoriteChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Selected address label for favorite not changed", __FUNCTION__);
    }
}

QString CW3WAdaptor::selectedW3WAddressLabelForFavorite()
{
    return m_SelectedW3WAddressItemForFavorite.m_W3WAddressLabel;
}

void CW3WAdaptor::invDeleteW3WAddress(CW3WEnum::EW3WAddressType addressType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);

    if (nullptr != m_pW3WResource)
    {
        SW3WAddressItem w3wAddressItem((m_SelectedW3WAddressItemForDelete.m_W3WAddress).toStdString(),
                                       (m_SelectedW3WAddressItemForDelete.m_W3WLanguageCode).toStdString(),
                                       (m_SelectedW3WAddressItemForDelete.m_W3WCountryCode).toStdString(),
                                       (m_SelectedW3WAddressItemForDelete.m_W3WNearestPlace).toStdString(),
                                       (m_SelectedW3WAddressItemForDelete.m_W3WAddressLabel).toStdString(),
                                       (m_SelectedW3WAddressItemForDelete.m_ItemId));

        if(CW3WEnum::W3W_ADDRESS_TYPE_FAVORITE == addressType)
        {
            m_pW3WResource->deleteFromFavoriteList(w3wAddressItem);
        }
        else if(CW3WEnum::W3W_ADDRESS_TYPE_RECENT == addressType)
        {
            m_pW3WResource->deleteFromRecentList(w3wAddressItem);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Invalid addressType", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, W3W resource is null", __FUNCTION__);
    }
}

void CW3WAdaptor::updateAddressDeletedStatus(bool addressDeletedStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);

    if(addressDeletedStatus)
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_W3W_ADDRESS_DELETED);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Unable to delete", __FUNCTION__);
    }

    /* To get the updated Favorite and Recent addresses */
    getFavoriteAndRecentAddresses();
}

void CW3WAdaptor::invSelectW3WAddressForDelete(CW3WEnum::EW3WAddressType addressType, int itemId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, addressType: %d itemIndex:%d", __FUNCTION__, static_cast<int>(addressType), itemId);

    CW3WData::SW3WAddressData w3wAddressDataItem;

    if(CW3WEnum::W3W_ADDRESS_TYPE_FAVORITE == addressType)
    {
        w3wAddressDataItem = m_pW3WFavoriteListModel->getFavoriteData(itemId);
        setSelectedW3WAddressItemForDelete(w3wAddressDataItem);
    }
    else if(CW3WEnum::W3W_ADDRESS_TYPE_RECENT == addressType)
    {
        w3wAddressDataItem = m_pW3WRecentListModel->getRecentData(itemId);
        setSelectedW3WAddressItemForDelete(w3wAddressDataItem);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Invalid addressType", __FUNCTION__);
    }
}

void CW3WAdaptor::setSelectedW3WAddressItemForDelete(const CW3WData::SW3WAddressData selectedW3WAddressItemForDelete)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, address : %s, languageCode : %s, countryCode : %s, nearestPlace : %s, addressLabel : %s, itemType: %d, itemId : %d",
             __FUNCTION__, selectedW3WAddressItemForDelete.m_W3WAddress.toStdString().c_str(), selectedW3WAddressItemForDelete.m_W3WLanguageCode.toStdString().c_str(),
             selectedW3WAddressItemForDelete.m_W3WCountryCode.toStdString().c_str(), selectedW3WAddressItemForDelete.m_W3WNearestPlace.toStdString().c_str(),
             selectedW3WAddressItemForDelete.m_W3WAddressLabel.toStdString().c_str(), selectedW3WAddressItemForDelete.m_W3WItemType,
             selectedW3WAddressItemForDelete.m_ItemId);

    if( (m_SelectedW3WAddressItemForDelete.m_ItemId != selectedW3WAddressItemForDelete.m_ItemId) ||
        (m_SelectedW3WAddressItemForDelete.m_W3WAddress != selectedW3WAddressItemForDelete.m_W3WAddress) ||
        (m_SelectedW3WAddressItemForDelete.m_W3WLanguageCode != selectedW3WAddressItemForDelete.m_W3WLanguageCode) ||
        (m_SelectedW3WAddressItemForDelete.m_W3WCountryCode != selectedW3WAddressItemForDelete.m_W3WCountryCode) ||
        (m_SelectedW3WAddressItemForDelete.m_W3WNearestPlace != selectedW3WAddressItemForDelete.m_W3WNearestPlace) ||
        (m_SelectedW3WAddressItemForDelete.m_W3WAddressLabel != selectedW3WAddressItemForDelete.m_W3WAddressLabel) ||
        (m_SelectedW3WAddressItemForDelete.m_W3WItemType != selectedW3WAddressItemForDelete.m_W3WItemType) )
    {
        setSelectedW3WAddressForDelete(selectedW3WAddressItemForDelete.m_W3WAddress);
        setSelectedW3WAddressLabelForDelete(selectedW3WAddressItemForDelete.m_W3WAddressLabel);
        m_SelectedW3WAddressItemForDelete.m_W3WLanguageCode = selectedW3WAddressItemForDelete.m_W3WLanguageCode;
        m_SelectedW3WAddressItemForDelete.m_W3WCountryCode = selectedW3WAddressItemForDelete.m_W3WCountryCode;
        m_SelectedW3WAddressItemForDelete.m_W3WNearestPlace = selectedW3WAddressItemForDelete.m_W3WNearestPlace;
        m_SelectedW3WAddressItemForDelete.m_W3WItemType = selectedW3WAddressItemForDelete.m_W3WItemType;
        m_SelectedW3WAddressItemForDelete.m_ItemId = selectedW3WAddressItemForDelete.m_ItemId;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Selected W3W Address item For Delete not changed", __FUNCTION__);
    }
}

void CW3WAdaptor::setSelectedW3WAddressForDelete(const QString strSelectedAddressForDelete)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s: strSelectedAddressForDelete: %s", __FUNCTION__, strSelectedAddressForDelete.toStdString().c_str());
    if(m_SelectedW3WAddressItemForDelete.m_W3WAddress != strSelectedAddressForDelete)
    {
        m_SelectedW3WAddressItemForDelete.m_W3WAddress = strSelectedAddressForDelete;
        emit sigSelectedW3WAddressForDeleteChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Selected address for delete not changed", __FUNCTION__);
    }
}

QString CW3WAdaptor::selectedW3WAddressForDelete()
{
    return m_SelectedW3WAddressItemForDelete.m_W3WAddress;
}

void CW3WAdaptor::setSelectedW3WAddressLabelForDelete(const QString strSelectedAddressLabelForDelete)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s: strSelectedAddressLabelForDelete: %s", __FUNCTION__, strSelectedAddressLabelForDelete.toStdString().c_str());
    if(m_SelectedW3WAddressItemForDelete.m_W3WAddressLabel != strSelectedAddressLabelForDelete)
    {
        m_SelectedW3WAddressItemForDelete.m_W3WAddressLabel = strSelectedAddressLabelForDelete;
        emit sigSelectedW3WAddressLabelForDeleteChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Selected address label for delete not changed", __FUNCTION__);
    }
}

QString CW3WAdaptor::selectedW3WAddressLabelForDelete()
{
    return m_SelectedW3WAddressItemForDelete.m_W3WAddressLabel;
}

bool CW3WAdaptor::isTextInW3WAddressFormat(const QString &strInputText)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s,  strInputText: %s", __FUNCTION__, strInputText.toStdString().c_str());

    bool bIsTextInW3WAddressFormat = false;

    if( w3wFeatureSupportStatus() )
    {
        /* Match the input text with the regular expression to know whether the text is in W3W address format or not */
        QRegExp objW3WAddressRegularExpression(m_strW3WAddressRegularExpression);

        int iPosition = objW3WAddressRegularExpression.indexIn(strInputText);
        if( -1 < iPosition )
        {
            LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s,  W3W Address: %s", __FUNCTION__, objW3WAddressRegularExpression.cap(0).toStdString().c_str());

            bIsTextInW3WAddressFormat = true;
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, W3W feature not supported", __FUNCTION__);
    }

    return bIsTextInW3WAddressFormat;
}

void CW3WAdaptor::invInitiateNavigation(const QString &strInputText)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, strW3WAddress: %s", __FUNCTION__, strInputText.toStdString().c_str());

    if( w3wFeatureSupportStatus() )
    {
        /* Proceed if ConnectNext app is connected to HU */
        if(0 == m_connNextConnStatus)
        {
            if( (true == CAndroidAutoAdaptor::getInstance()->androidAutoConnectionStatus()) ||
                    (true == CAppleCarPlayAdaptor::getInstance()->appleCarPlayConnectionStatus()) )
            {
                /* Match the input text with the regular expression to know whether the text is in W3W address format or not */
                QRegExp objW3WAddressRegularExpression(m_strW3WAddressRegularExpression);

                int iPosition = objW3WAddressRegularExpression.indexIn(strInputText);
                if( -1 < iPosition )
                {
                    QString strW3WAddress = objW3WAddressRegularExpression.cap(0);
                    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s,  W3W Address: %s", __FUNCTION__, strW3WAddress.toStdString().c_str());
                    if (nullptr != m_pW3WResource)
                    {
                        /* Create structure of this address, and pass it to resource layer */
                        SW3WAddressItem w3wAddressItem(strW3WAddress.toStdString(), "", "", "", "");
                        m_pW3WResource->navigateToAddress(w3wAddressItem);

                        /* Store the last navigated address */
                        m_LastNavigatedW3WAddress = strW3WAddress;
                    }
                    else
                    {
                        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s W3W resource is NULL", __FUNCTION__);
                    }
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, W3W Address not found", __FUNCTION__);
                }
            }
            else
            {
                // Show W3W popup requesting user to connect a projection Device
                LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s AA / CP both not connected", __FUNCTION__);
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_W3W_AA_CP_NOT_CONNECTED);
            }
        }
        /* If ConnectNext app is not connected to HU, then show the popup */
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s ConnectNext not connected", __FUNCTION__);
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_W3W_CONNECTNEXT_NOT_CONNECTED);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, W3W feature not supported", __FUNCTION__);
    }
}

void CW3WAdaptor::invInitiateNavigation()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s", __FUNCTION__);

    /* Proceed if ConnectNext app is connected to HU */
    if(0 == m_connNextConnStatus)
    {
        if( (true == CAndroidAutoAdaptor::getInstance()->androidAutoConnectionStatus()) ||
                (true == CAppleCarPlayAdaptor::getInstance()->appleCarPlayConnectionStatus()) )
        {
            if (nullptr != m_pW3WResource)
            {
                /* Create structure of the selected w3w address item, and pass it to resource layer */
                SW3WAddressItem w3wAddressItem((m_SelectedW3WAddressItem.m_W3WAddress).toStdString(),
                                               (m_SelectedW3WAddressItem.m_W3WLanguageCode).toStdString(),
                                               (m_SelectedW3WAddressItem.m_W3WCountryCode).toStdString(),
                                               (m_SelectedW3WAddressItem.m_W3WNearestPlace).toStdString(),
                                               (m_SelectedW3WAddressItem.m_W3WAddressLabel).toStdString(),
                                               (m_SelectedW3WAddressItem.m_ItemId));

                m_pW3WResource->navigateToAddress(w3wAddressItem);

                /* Store the last navigated address */
                m_LastNavigatedW3WAddress = m_SelectedW3WAddressItem.m_W3WAddress;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s W3W resource is NULL", __FUNCTION__);
            }
        }
        else
        {
            // Show W3W popup requesting user to connect a projection Device
            LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s AA / CP both not connected", __FUNCTION__);
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_W3W_AA_CP_NOT_CONNECTED);
        }
    }
    /* If ConnectNext app is not connected to HU, then show the popup */
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s ConnectNext not connected", __FUNCTION__);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_W3W_CONNECTNEXT_NOT_CONNECTED);
    }
}

void CW3WAdaptor::updateNavigationStatus(bool navigationStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, navigationStatus: %d", __FUNCTION__, navigationStatus);
    if(navigationStatus)
    {
        if (nullptr != m_pW3WResource)
        {
            /* To update the co-ordinates of the last navigated */
            m_pW3WResource->getLatLong(m_LastNavigatedW3WAddress.toStdString());
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s W3W resource is NULL", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Unable to navigate due to invalid W3W address", __FUNCTION__);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_W3W_INVALID_ADDRESS);
    }
}

void CW3WAdaptor::invActivateVRForW3W()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s", __FUNCTION__);

    if(CVRAdaptor::getInstance())
    {
        CVRAdaptor::getInstance()->activateVRSession(CHardKeyEnum::HKEY_STATE_RELEASED, EN_SCREEN_W3W);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, VR Adaptor is null", __FUNCTION__);
    }
}

void CW3WAdaptor::updateOnCoreProxyAvailability(bool bW3WCoreProxyStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, bW3WCoreProxyStatus: %d", __FUNCTION__, bW3WCoreProxyStatus);

    if (bW3WCoreProxyStatus != m_bW3WCoreProxyStatus)
    {
        m_bW3WCoreProxyStatus = bW3WCoreProxyStatus;
        emit sigW3WCoreProxyAvailability(m_bW3WCoreProxyStatus);
    }
}

void CW3WAdaptor::updateOnPluginProxyAvailability(bool bW3WPluginProxyStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, bW3WPluginProxyStatus: %d", __FUNCTION__, bW3WPluginProxyStatus);
    m_bW3WPluginProxyStatus = bW3WPluginProxyStatus;

    if(m_bW3WPluginProxyStatus)
    {
        if (nullptr != m_pW3WResource)
        {
            /* Request Favorite and Recent addresses on plugin proxy availibility */
            getFavoriteAndRecentAddresses();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, W3W resource is null", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, W3WPluginProxy not available", __FUNCTION__);
    }
}

void CW3WAdaptor::updateAutoSuggestionList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    if (nullptr != m_pW3WResource)
    {
        QList<CW3WData::SW3WAddressData> suggestionList;
        suggestionList.clear();
        vector<SSuggestion> autoSuggestions = m_pW3WResource->getAutoSuggestionsList();
        SSuggestion suggestion;
        int itemId = 0;
        foreach (suggestion, autoSuggestions)
        {
            suggestionList.append(CW3WData::SW3WAddressData(QString::fromStdString(suggestion.m_w3wAddress),
                                                                   QString::fromStdString(suggestion.m_languageCode),
                                                                   QString::fromStdString(suggestion.m_countryCode),
                                                                   QString::fromStdString(suggestion.m_nearestPlace),
                                                                   "",
                                                                   CW3WEnum::ITEM_TYPE_AUTO_SUGGESTION,
                                                                   itemId++));
        }
        if (nullptr != m_pW3WAutoSuggestionListModel)
        {
            m_pW3WAutoSuggestionListModel->updateW3WAutoSuggestionList(suggestionList);
            setAutoSuggestionRecievedStatus(true);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s auto suggestion list not created", __FUNCTION__);
        }
    }
    else
    {
       LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s W3W resource is NULL", __FUNCTION__);
    }
}

void CW3WAdaptor::invGetW3WAddresses(CW3WEnum::EW3WAddressType addressType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s: addressType: %d", __FUNCTION__, static_cast<int>(addressType));

    if(m_bW3WPluginProxyStatus)
    {
        if (nullptr != m_pW3WResource)
        {
            if(CW3WEnum::W3W_ADDRESS_TYPE_FAVORITE == addressType)
            {
                m_CurrentW3WAddressType = addressType;
                m_pW3WResource->getFavoriteAddresses();
            }
            else if(CW3WEnum::W3W_ADDRESS_TYPE_RECENT == addressType)
            {
                m_CurrentW3WAddressType = addressType;
                m_pW3WResource->getRecentAddresses();
            }
            else
            {
                /* Do nothing */
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, W3W resource is null", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, W3WPluginProxy not available", __FUNCTION__);
    }
}

void CW3WAdaptor::getFavoriteAndRecentAddresses()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s", __FUNCTION__);

    if(m_bW3WPluginProxyStatus)
    {
        if (nullptr != m_pW3WResource)
        {
            m_pW3WResource->getFavoriteAddresses();
            m_pW3WResource->getRecentAddresses();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, W3W resource is null", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, W3WPluginProxy not available", __FUNCTION__);
    }
}

void CW3WAdaptor::updateFavoriteAddressList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);

    if (nullptr != m_pW3WResource)
    {
        if (nullptr != m_pW3WFavoriteListModel)
        {
            vector<SW3WAddressItem> newFavoriteAddresses = m_pW3WResource->getFavoriteAddressList();
            int newSize = static_cast<int> (newFavoriteAddresses.size());

            /* Add newly found addresses in the favorite list */
            for(int newIndex = 0; newIndex < newSize; newIndex++)
            {
                bool isNewAddressFound = true;

                /* Iterate through each element of new list */
                CW3WData::SW3WAddressData newFavorite(QString::fromStdString(newFavoriteAddresses.at(newIndex).m_w3wAddress),
                                                   QString::fromStdString(newFavoriteAddresses.at(newIndex).m_languageCode),
                                                   QString::fromStdString(newFavoriteAddresses.at(newIndex).m_countryCode),
                                                   QString::fromStdString(newFavoriteAddresses.at(newIndex).m_nearestPlace),
                                                   QString::fromStdString(newFavoriteAddresses.at(newIndex).m_w3wAddressLabel),
                                                   CW3WEnum::ITEM_TYPE_W3W_ADDRESS,
                                                   newFavoriteAddresses.at(newIndex).m_w3wAddressUID);

                /* Check whether new entry already exists in the existing model */
                for(int oldIndex = 0, oldSize = m_pW3WFavoriteListModel->rowCount(); oldIndex < oldSize; oldIndex++)
                {
                    CW3WData::SW3WAddressData existingFavorite = m_pW3WFavoriteListModel->getFavoriteDataAtIndex(oldIndex);

                    if( (existingFavorite.m_ItemId == newFavorite.m_ItemId) )
                    {
                        /* If any data is changed for this address item, then update that address item in model */
                        if( (existingFavorite.m_W3WAddress != newFavorite.m_W3WAddress) ||
                            (existingFavorite.m_W3WLanguageCode != newFavorite.m_W3WLanguageCode) || (existingFavorite.m_W3WCountryCode != newFavorite.m_W3WCountryCode) ||
                            (existingFavorite.m_W3WNearestPlace != newFavorite.m_W3WNearestPlace) || (existingFavorite.m_W3WAddressLabel != newFavorite.m_W3WAddressLabel) )
                        {
                            m_pW3WFavoriteListModel->updateW3WFavoriteModelAtIndex(oldIndex, newFavorite);
                        }

                        isNewAddressFound = false;
                        break;
                    }
                }

                /* Append newly found entry in the existing model */
                if(isNewAddressFound)
                {
                    m_pW3WFavoriteListModel->appendRow(newFavorite);
                    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s favorite item at %d added", __FUNCTION__, newIndex);
                }
            }

            /* Remove deleted addresses from the favorite list */
            for(int oldIndex = 0, oldSize = m_pW3WFavoriteListModel->rowCount(); oldIndex < oldSize; oldIndex++)
            {
                bool isOldAddressFound = false;

                /* Iterate through each element of old list */
                CW3WData::SW3WAddressData oldFavorite = m_pW3WFavoriteListModel->getFavoriteDataAtIndex(oldIndex);

                /* Check whether old entry exists in the new favorite list */
                for(int newIndex = 0; newIndex < newSize; newIndex++)
                {
                    /* Iterate through each element of new list */
                    CW3WData::SW3WAddressData newFavorite(QString::fromStdString(newFavoriteAddresses.at(newIndex).m_w3wAddress),
                                                       QString::fromStdString(newFavoriteAddresses.at(newIndex).m_languageCode),
                                                       QString::fromStdString(newFavoriteAddresses.at(newIndex).m_countryCode),
                                                       QString::fromStdString(newFavoriteAddresses.at(newIndex).m_nearestPlace),
                                                       QString::fromStdString(newFavoriteAddresses.at(newIndex).m_w3wAddressLabel),
                                                       CW3WEnum::ITEM_TYPE_W3W_ADDRESS,
                                                       newFavoriteAddresses.at(newIndex).m_w3wAddressUID);

                    if( oldFavorite.m_ItemId == newFavorite.m_ItemId )
                    {
                        isOldAddressFound = true;
                        break;
                    }
                }
                if(!isOldAddressFound)
                {
                    m_pW3WFavoriteListModel->removeRow(oldIndex);
                    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s favorite removed at %d", __FUNCTION__, oldIndex);
                }
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s favorite address list not created", __FUNCTION__);
        }
    }
    else
    {
       LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s W3W resource is NULL", __FUNCTION__);
    }
}

void CW3WAdaptor::updateRecentAddressList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);

    if (nullptr != m_pW3WResource)
    {
        if (nullptr != m_pW3WRecentListModel)
        {
            vector<SW3WAddressItem> newRecentAddresses = m_pW3WResource->getRecentAddressList();
            int newSize = static_cast<int> (newRecentAddresses.size());

            /* Add newly found addresses in the recent list */
            for(int newIndex = 0; newIndex < newSize; newIndex++)
            {
                bool isNewAddressFound = true;

                /* Iterate through each element of new list */
                CW3WData::SW3WAddressData newRecent(QString::fromStdString(newRecentAddresses.at(newIndex).m_w3wAddress),
                                                   QString::fromStdString(newRecentAddresses.at(newIndex).m_languageCode),
                                                   QString::fromStdString(newRecentAddresses.at(newIndex).m_countryCode),
                                                   QString::fromStdString(newRecentAddresses.at(newIndex).m_nearestPlace),
                                                   QString::fromStdString(newRecentAddresses.at(newIndex).m_w3wAddressLabel),
                                                   CW3WEnum::ITEM_TYPE_W3W_ADDRESS,
                                                   newRecentAddresses.at(newIndex).m_w3wAddressUID);

                /* Check whether new entry already exists in the existing model */
                for(int oldIndex = 0, oldSize = m_pW3WRecentListModel->rowCount(); oldIndex < oldSize; oldIndex++)
                {
                    CW3WData::SW3WAddressData existingRecent = m_pW3WRecentListModel->getRecentDataAtIndex(oldIndex);

                    if( (existingRecent.m_ItemId == newRecent.m_ItemId) )
                    {
                        /* If any data is changed for this address item, then update that address item in model */
                        if( (existingRecent.m_W3WAddress != newRecent.m_W3WAddress) ||
                            (existingRecent.m_W3WLanguageCode != newRecent.m_W3WLanguageCode) || (existingRecent.m_W3WCountryCode != newRecent.m_W3WCountryCode) ||
                            (existingRecent.m_W3WNearestPlace != newRecent.m_W3WNearestPlace) || (existingRecent.m_W3WAddressLabel != newRecent.m_W3WAddressLabel) )
                        {
                            m_pW3WRecentListModel->updateW3WRecentModelAtIndex(oldIndex, newRecent);
                        }

                        isNewAddressFound = false;
                        break;
                    }
                }

                /* Append newly found entry in the existing model */
                if(isNewAddressFound)
                {
                    m_pW3WRecentListModel->appendRow(newRecent);
                    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s recent item at %d added", __FUNCTION__, newIndex);
                }
            }

            /* Remove deleted addresses from the recent list */
            for(int oldIndex = 0, oldSize = m_pW3WRecentListModel->rowCount(); oldIndex < oldSize; oldIndex++)
            {
                bool isOldAddressFound = false;

                /* Iterate through each element of old list */
                CW3WData::SW3WAddressData oldRecent = m_pW3WRecentListModel->getRecentDataAtIndex(oldIndex);

                /* Check whether old entry exists in the new recent list */
                for(int newIndex = 0; newIndex < newSize; newIndex++)
                {
                    /* Iterate through each element of new list */
                    CW3WData::SW3WAddressData newRecent(QString::fromStdString(newRecentAddresses.at(newIndex).m_w3wAddress),
                                                       QString::fromStdString(newRecentAddresses.at(newIndex).m_languageCode),
                                                       QString::fromStdString(newRecentAddresses.at(newIndex).m_countryCode),
                                                       QString::fromStdString(newRecentAddresses.at(newIndex).m_nearestPlace),
                                                       QString::fromStdString(newRecentAddresses.at(newIndex).m_w3wAddressLabel),
                                                       CW3WEnum::ITEM_TYPE_W3W_ADDRESS,
                                                       newRecentAddresses.at(newIndex).m_w3wAddressUID);

                    if( oldRecent.m_ItemId == newRecent.m_ItemId )
                    {
                        isOldAddressFound = true;
                        break;
                    }
                }
                if(!isOldAddressFound)
                {
                    m_pW3WRecentListModel->removeRow(oldIndex);
                    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s recent removed at %d", __FUNCTION__, oldIndex);
                }
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s recent address list not created", __FUNCTION__);
        }
    }
    else
    {
       LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s W3W resource is NULL", __FUNCTION__);
    }
}


void CW3WAdaptor::invUpdateCountryPreference(int iItemId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s: iItemId: %d", __FUNCTION__, iItemId);

    if (nullptr != m_pW3WResource)
    {
        QString countryCode = "";
        if(CW3WEnum::W3W_SETUP_COUNTRY_PREFERENCE_IN == iItemId)
        {
            countryCode = "IN";
        }
        else
        {
            /* Do nothing */
        }
        m_pW3WResource->setCountryCode(countryCode.toStdString());
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, W3W resource is null", __FUNCTION__);
    }
}

void CW3WAdaptor::updateCurrentCountryCode(const QString &countryCode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    m_CurrentCountryCode = countryCode;

    if(m_pW3WSetupListModel)
    {
        /* Update the Setup model for Country Preference */
        m_pW3WSetupListModel->updateCountryPreferenceList();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s: W3W setup list model is null", __FUNCTION__);
    }
}

QString CW3WAdaptor::getCurrentCountryCode()
{
    return m_CurrentCountryCode;
}

void CW3WAdaptor::updateMapsLaunchStatus(int mapsLaunchStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s maps not launched, launch status: %d", __FUNCTION__, mapsLaunchStatus);

    /*
     * If maps launch status is sucess (0)
     * If AA is connected launch AA
     * If CP is connected launch CP
     * else show popup to connect a projection Device
     */
    if (0 == mapsLaunchStatus)
    {
        if (true == CAndroidAutoAdaptor::getInstance()->androidAutoConnectionStatus())
        {
            if(autoLaunchPermissionStatusForAA())
            {
                CAndroidAutoAdaptor::getInstance()->launchAndroidAuto();
            }
            else
            {
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_W3W_ALLOW_AUTOLAUNCH_AA);
            }
        }
        else if (true == CAppleCarPlayAdaptor::getInstance()->appleCarPlayConnectionStatus())
        {
            if(autoLaunchPermissionStatusForCP())
            {
                CAppleCarPlayAdaptor::getInstance()->launchAppleCarPlay();
            }
            else
            {
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_W3W_ALLOW_AUTOLAUNCH_CP);
            }
        }
        else
        {
            // Show W3W popup requesting user to connect a projection Device
            LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s AA / CP both not connected", __FUNCTION__);
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_W3W_AA_CP_NOT_CONNECTED);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s maps not launched, launch status: %d", __FUNCTION__, mapsLaunchStatus);
    }
}

void CW3WAdaptor::updateConnNextStatus(int connNextStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    m_connNextConnStatus = connNextStatus;
}

void CW3WAdaptor::updateW3WCoordinates(double lat, double lng)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    setLastNavigatedLatitude(lat);
    setLastNavigatedLongitude(lng);
}

void CW3WAdaptor::setLastNavigatedLatitude(double lastNavigatedLatitude)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s: lastNavigatedLatitude: %f", __FUNCTION__, lastNavigatedLatitude);
    if(m_W3WCoordinates.lat != lastNavigatedLatitude)
    {
        m_W3WCoordinates.lat = lastNavigatedLatitude;
        emit sigLastNavigatedLatitudeChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Last Navigated Latitude not changed", __FUNCTION__);
    }
}

double CW3WAdaptor::lastNavigatedLatitude()
{
    return m_W3WCoordinates.lat;
}

void CW3WAdaptor::setLastNavigatedLongitude(double lastNavigatedLongitude)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s: lastNavigatedLongitude: %f", __FUNCTION__, lastNavigatedLongitude);
    if(m_W3WCoordinates.lng != lastNavigatedLongitude)
    {
        m_W3WCoordinates.lng = lastNavigatedLongitude;
        emit sigLastNavigatedLongitudeChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, Last Navigated Longitude not changed", __FUNCTION__);
    }
}

double CW3WAdaptor::lastNavigatedLongitude()
{
    return m_W3WCoordinates.lng;
}

void CW3WAdaptor::updateW3WAddress(QString w3wAddress)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    m_W3WAddress = w3wAddress;
}

void CW3WAdaptor::invShareW3WAddressViaSMS(const QString number, const QString W3WAddress)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);

    QString w3wAddressWeblink = "https://w3w.co/";
    w3wAddressWeblink.append(W3WAddress);

    CAudioAdaptor::getInstance()->playBeep(CAudioEnums::BEEP_TYPE_CONFIRM);
    CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_W3W_ADDRESS_SHARED);
    CPhoneAdaptor::getInstance()->sendSMS(number, w3wAddressWeblink);
}

void CW3WAdaptor::sltPopupResult(CPopupEnum::EPopupID popupId, CPopupEnum::EPopupResult popupResult, QString additionalInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s: popupId: %d, popupResult: %d, additionalInfo: %s", __FUNCTION__, static_cast<int>(popupId), static_cast<int>(popupResult), additionalInfo.toStdString().c_str());

    switch(popupId)
    {
    case CPopupEnum::EPopupID::EN_POPUPID_W3W_ADDRESS_SHARED:
    {
        if (CPopupEnum::EN_POPUP_RESULT_DISPLAYED != popupResult)
        {
            /* Go back to W3W Main screen after W3W Address is shared */
            CHMIMain::getSM()->getSCI_W3w()->raise_evW3WAddressShared();
        }
        else
        {
            /* Do nothing */
        }
    }
        break;
    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W, "%s: In Default case.", __FUNCTION__);
    }
        break;
    }
}

void CW3WAdaptor::fillFlagsDataMap()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    m_mapFlagsData.clear();

    m_mapFlagsData.insert("AX", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Aland Islands.png");
    m_mapFlagsData.insert("AL", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Albania.png");
    m_mapFlagsData.insert("DZ", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Algeria.png");
    m_mapFlagsData.insert("AS", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/American Samoa.png");
    m_mapFlagsData.insert("AD", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Andorra.png");
    m_mapFlagsData.insert("AO", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Angola.png");
    m_mapFlagsData.insert("AI", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Anguilla.png");
    m_mapFlagsData.insert("AG", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Antigua and Barb.png");
    m_mapFlagsData.insert("AR", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Argentina.png");
    m_mapFlagsData.insert("AW", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Aruba.png");

    m_mapFlagsData.insert("SH", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Ascension and Tristan da Cunha.png");
    m_mapFlagsData.insert("AU", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Australia.png");
    m_mapFlagsData.insert("AT", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Austria.png");
    m_mapFlagsData.insert("AZ", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Azerbaijan.png");
    m_mapFlagsData.insert("BS", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Bahamas.png");
    m_mapFlagsData.insert("BH", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Bahrain.png");
    m_mapFlagsData.insert("BD", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Bangladesh.png");
    m_mapFlagsData.insert("BB", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Barbados.png");
    m_mapFlagsData.insert("BY", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Belarus.png");
    m_mapFlagsData.insert("BE", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Belgium.png");

    m_mapFlagsData.insert("BZ", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Belize.png");
    m_mapFlagsData.insert("BJ", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Benin.png");
    m_mapFlagsData.insert("BM", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Bermuda.png");
    m_mapFlagsData.insert("BT", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Bhutan.png");
    m_mapFlagsData.insert("BO", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Bolivia (Plurinatio.png");
    m_mapFlagsData.insert("BA", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Bosnia and Her.png");
    m_mapFlagsData.insert("BW", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Botswana.png");
    m_mapFlagsData.insert("BR", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Brazil.png");
    m_mapFlagsData.insert("IO", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/British Indian O.png");
    m_mapFlagsData.insert("BN", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Brunei Darussala.png");

    m_mapFlagsData.insert("BG", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Bulgaria.png");
    m_mapFlagsData.insert("BF", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Burkina Faso.png");
    m_mapFlagsData.insert("CV", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Cabo Verde.png");
    m_mapFlagsData.insert("KH", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Cambodia.png");
    m_mapFlagsData.insert("CM", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Cameroon.png");
    m_mapFlagsData.insert("CA", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Canada.png");
    m_mapFlagsData.insert("KY", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Cayman Islands.png");
    m_mapFlagsData.insert("CF", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Central African.png");
    m_mapFlagsData.insert("TD", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Chad.png");
    m_mapFlagsData.insert("CL", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Chile.png");

    m_mapFlagsData.insert("CN", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/China.png");
    m_mapFlagsData.insert("CX", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Christmas Island.png");
    m_mapFlagsData.insert("CC", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Cocos (Keeling) Is.png");
    m_mapFlagsData.insert("CO", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Colombia.png");
    m_mapFlagsData.insert("KM", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Comoros.png");
    m_mapFlagsData.insert("CK", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Cook Islands.png");
    m_mapFlagsData.insert("CR", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Costa Rica.png");
    m_mapFlagsData.insert("CI", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Cote d'Ivoire.png");
    m_mapFlagsData.insert("HR", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Croatia.png");
    m_mapFlagsData.insert("CU", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Cuba.png");

    m_mapFlagsData.insert("CW", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Curacao.png");
    m_mapFlagsData.insert("CY", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Cyprus.png");
    m_mapFlagsData.insert("CZ", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Czech Republic.png");
    m_mapFlagsData.insert("CD", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Democratic Republic of the Congo.png");
    m_mapFlagsData.insert("DK", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Denmark.png");
    m_mapFlagsData.insert("DJ", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Djibouti.png");
    m_mapFlagsData.insert("DM", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Dominica.png");
    m_mapFlagsData.insert("DO", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Dominican Republic.png");
    m_mapFlagsData.insert("EC", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Ecuador.png");
    m_mapFlagsData.insert("EG", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Egypt.png");

    m_mapFlagsData.insert("SV", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/El Salvador.png");
    m_mapFlagsData.insert("GQ", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Equatorial Guinea.png");
    m_mapFlagsData.insert("ER", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Eritrea.png");
    m_mapFlagsData.insert("FI", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Finland.png");
    m_mapFlagsData.insert("MK", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Former Yugoslav Republic of Macedonia.png");
    m_mapFlagsData.insert("FR", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/France.png");
    m_mapFlagsData.insert("GF", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/French Guiana.png");
    m_mapFlagsData.insert("PF", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/French Polynesia.png");
    m_mapFlagsData.insert("GA", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Gabon.png");
    m_mapFlagsData.insert("GM", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Gambia.png");

    m_mapFlagsData.insert("GE", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Georgia.png");
    m_mapFlagsData.insert("DE", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Germany.png");
    m_mapFlagsData.insert("GH", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Ghana.png");
    m_mapFlagsData.insert("GI", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Gibraltar.png");
    m_mapFlagsData.insert("GR", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Greece.png");
    m_mapFlagsData.insert("GL", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Greenland.png");
    m_mapFlagsData.insert("GD", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Grenada.png");
    m_mapFlagsData.insert("GP", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Guadeloupe.png");
    m_mapFlagsData.insert("GU", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Guam.png");
    m_mapFlagsData.insert("GT", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Guatemala.png");

    m_mapFlagsData.insert("GG", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Guernsey.png");
    m_mapFlagsData.insert("GN", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Guinea.png");
    m_mapFlagsData.insert("GW", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Guinea-Bissau.png");
    m_mapFlagsData.insert("GY", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Guyana.png");
    m_mapFlagsData.insert("HT", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Haiti.png");
    m_mapFlagsData.insert("VA", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Holy See.png");
    m_mapFlagsData.insert("HK", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Hong Kong.png");
    m_mapFlagsData.insert("IS", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Iceland.png");
    m_mapFlagsData.insert("IN", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/India.png");
    m_mapFlagsData.insert("ID", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Indonesia.png");

    m_mapFlagsData.insert("IR", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Iran (Islamic Republic of).png");
    m_mapFlagsData.insert("IQ", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Iraq.png");
    m_mapFlagsData.insert("IE", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Ireland.png");
    m_mapFlagsData.insert("IM", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Isle of Man.png");
    m_mapFlagsData.insert("IL", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Israel.png");
    m_mapFlagsData.insert("IT", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Italy.png");
    m_mapFlagsData.insert("JM", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Jamaica.png");
    m_mapFlagsData.insert("JP", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Japan.png");
    m_mapFlagsData.insert("JE", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Jersey.png");
    m_mapFlagsData.insert("KZ", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Kazakhstan.png");

    m_mapFlagsData.insert("KE", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Kenya.png");
    m_mapFlagsData.insert("KI", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Kiribati.png");
    m_mapFlagsData.insert("XK", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Kosovo.png");
    m_mapFlagsData.insert("KW", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Kuwait.png");
    m_mapFlagsData.insert("KG", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Kyrgyzstan.png");
    m_mapFlagsData.insert("LA", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Laos.png");
    m_mapFlagsData.insert("LV", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Latvia.png");
    m_mapFlagsData.insert("LB", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Lebanon.png");
    m_mapFlagsData.insert("LS", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Lesotho.png");
    m_mapFlagsData.insert("LR", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Liberia.png");

    m_mapFlagsData.insert("LY", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Libya.png");
    m_mapFlagsData.insert("LI", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Liechtenstein.png");
    m_mapFlagsData.insert("LT", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Lithuania.png");
    m_mapFlagsData.insert("LU", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Luxembourg.png");
    m_mapFlagsData.insert("MO", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Macau.png");
    m_mapFlagsData.insert("MG", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Madagascar.png");
    m_mapFlagsData.insert("MW", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Malawi.png");
    m_mapFlagsData.insert("MY", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Malaysia.png");
    m_mapFlagsData.insert("MV", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Maldives.png");
    m_mapFlagsData.insert("ML", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Mali.png");

    m_mapFlagsData.insert("MT", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Malta.png");
    m_mapFlagsData.insert("MH", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Marshall Islands.png");
    m_mapFlagsData.insert("MQ", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Martinique.png");
    m_mapFlagsData.insert("MR", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Mauritania.png");
    m_mapFlagsData.insert("MU", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Mauritius.png");
    m_mapFlagsData.insert("YT", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Mayotte.png");
    m_mapFlagsData.insert("MX", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Mexico.png");
    m_mapFlagsData.insert("MD", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Moldova.png");
    m_mapFlagsData.insert("MC", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Monaco.png");
    m_mapFlagsData.insert("MN", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Mongolia.png");

    m_mapFlagsData.insert("ME", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Montenegro.png");
    m_mapFlagsData.insert("MS", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Montserrat.png");
    m_mapFlagsData.insert("MA", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Morocco.png");
    m_mapFlagsData.insert("MZ", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Mozambique.png");
    m_mapFlagsData.insert("MM", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Myanmar.png");
    m_mapFlagsData.insert("NA", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Namibia.png");
    m_mapFlagsData.insert("NR", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Nauru.png");
    m_mapFlagsData.insert("NP", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Nepal.png");
    m_mapFlagsData.insert("NL", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Netherlands.png");
    m_mapFlagsData.insert("NC", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/New Caledonia.png");

    m_mapFlagsData.insert("NZ", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/New Zealand.png");
    m_mapFlagsData.insert("NI", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Nicaragua.png");
    m_mapFlagsData.insert("NE", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Niger.png");
    m_mapFlagsData.insert("NG", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Nigeria.png");
    m_mapFlagsData.insert("NU", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Niue.png");
    m_mapFlagsData.insert("NF", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Norfolk Island.png");
    m_mapFlagsData.insert("KP", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/North Korea.png");
    m_mapFlagsData.insert("MP", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Northern Mariana Islands.png");
    m_mapFlagsData.insert("NO", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Norway.png");
    m_mapFlagsData.insert("PK", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Pakistan.png");

    m_mapFlagsData.insert("PW", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Palau.png");
    m_mapFlagsData.insert("PA", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Panama.png");
    m_mapFlagsData.insert("PG", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Papua New Guinea.png");
    m_mapFlagsData.insert("PY", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Paraguay.png");
    m_mapFlagsData.insert("PE", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Peru.png");
    m_mapFlagsData.insert("PH", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Philippines.png");
    m_mapFlagsData.insert("PN", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Pitcairn.png");
    m_mapFlagsData.insert("PL", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Poland.png");
    m_mapFlagsData.insert("PT", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Portugal.png");
    m_mapFlagsData.insert("PR", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Puerto Rico.png");

    m_mapFlagsData.insert("CG", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Republic of the Congo.png");
    m_mapFlagsData.insert("RO", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Romania.png");
    m_mapFlagsData.insert("RU", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Russia.png");
    m_mapFlagsData.insert("RW", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Rwanda.png");
    m_mapFlagsData.insert("BL", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Saint Barthelemy.png");
    m_mapFlagsData.insert("KN", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Saint Kitts and Nevis.png");
    m_mapFlagsData.insert("LC", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Saint Lucia.png");
    m_mapFlagsData.insert("MF", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Saint Martin.png");
    m_mapFlagsData.insert("PM", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Saint Pierre and Miquelon.png");
    m_mapFlagsData.insert("VC", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Saint Vincent and the Grenadines.png");

    m_mapFlagsData.insert("WS", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Samoa.png");
    m_mapFlagsData.insert("SM", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/San Marino.png");
    m_mapFlagsData.insert("ST", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Sao Tome and Principe.png");
    m_mapFlagsData.insert("SA", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Saudi Arabia.png");
    m_mapFlagsData.insert("SN", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Senegal.png");
    m_mapFlagsData.insert("RS", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Serbia.png");
    m_mapFlagsData.insert("SC", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Seychelles.png");
    m_mapFlagsData.insert("SL", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Sierra Leone.png");
    m_mapFlagsData.insert("SG", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Singapore.png");
    m_mapFlagsData.insert("BQ", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Sint Eu.png");

    m_mapFlagsData.insert("SX", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Sint Maarten.png");
    m_mapFlagsData.insert("SK", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Slovakia.png");
    m_mapFlagsData.insert("SI", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Slovenia.png");
    m_mapFlagsData.insert("SB", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Solomon Islands.png");
    m_mapFlagsData.insert("SO", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Somalia.png");
    m_mapFlagsData.insert("ZA", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/South Africa.png");
    m_mapFlagsData.insert("GS", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/South Georgia and the South Sandwich Islands.png");
    m_mapFlagsData.insert("KR", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/South Korea.png");
    m_mapFlagsData.insert("SS", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/South Sudan.png");
    m_mapFlagsData.insert("ES", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Spain.png");

    m_mapFlagsData.insert("LK", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Sri Lanka.png");
    m_mapFlagsData.insert("PS", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/State of Palestine.png");
    m_mapFlagsData.insert("SD", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Sudan.png");
    m_mapFlagsData.insert("SR", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Suriname.png");
    m_mapFlagsData.insert("SJ", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Svalbard and Jan Mayen.png");
    m_mapFlagsData.insert("SZ", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Swaziland.png");
    m_mapFlagsData.insert("SE", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Sweden.png");
    m_mapFlagsData.insert("CH", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Switzerland.png");
    m_mapFlagsData.insert("TW", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Taiwan.png");
    m_mapFlagsData.insert("TJ", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Tajikistan.png");

    m_mapFlagsData.insert("TZ", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Tanzania.png");
    m_mapFlagsData.insert("TH", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Thailand.png");
    m_mapFlagsData.insert("TL", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Timor-Leste.png");
    m_mapFlagsData.insert("TG", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Togo.png");
    m_mapFlagsData.insert("TK", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Tokelau.png");
    m_mapFlagsData.insert("TO", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Tonga.png");
    m_mapFlagsData.insert("TT", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Trinidad and Tobago.png");
    m_mapFlagsData.insert("TN", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Tunisia.png");
    m_mapFlagsData.insert("TR", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Turkey.png");
    m_mapFlagsData.insert("TM", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Turkmenistan.png");

    m_mapFlagsData.insert("TV", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Tuvalu.png");
    m_mapFlagsData.insert("UG", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Uganda.png");
    m_mapFlagsData.insert("UA", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Ukraine.png");
    m_mapFlagsData.insert("AE", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/United Arab Emirates.png");
    m_mapFlagsData.insert("GB", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/United Kingdom.png");
    m_mapFlagsData.insert("UM", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/United States Minor Outlying Islands.png");
    m_mapFlagsData.insert("US", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/United States of America.png");
    m_mapFlagsData.insert("UY", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Uruguay.png");
    m_mapFlagsData.insert("UZ", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Uzbekistan.png");
    m_mapFlagsData.insert("VU", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Vanuatu.png");

    m_mapFlagsData.insert("VE", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Venezuela.png");
    m_mapFlagsData.insert("VN", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Vietnam.png");
    m_mapFlagsData.insert("VG", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Virgin Islands.png");
    m_mapFlagsData.insert("WF", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Wallis and Futuna.png");
    m_mapFlagsData.insert("EH", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Western Sahara.png");
    m_mapFlagsData.insert("YE", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Yemen.png");
    m_mapFlagsData.insert("ZM", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Zambia.png");
    m_mapFlagsData.insert("ZW", "qrc:/image/W3W/KeyPad/Gen_Gfx_Country Flag_n-assets/Zimbabwe.png");
}

QString CW3WAdaptor::getFlagIconURLForCountryCode(QString countryCode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s: countryCode: %s", __FUNCTION__, countryCode.toStdString().c_str());

    if( m_mapFlagsData.contains(countryCode) )
    {
        return m_mapFlagsData[countryCode];
    }
    else
    {
        return "";
    }
}
