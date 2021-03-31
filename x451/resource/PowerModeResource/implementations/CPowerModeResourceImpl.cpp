/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CPowerModeResourceImpl.h
* @ingroup      HMIComponent
* @author       Prashantkumar Raut
* CPowerModeResourceImpl, Resource Implementation for PowerMode using NSMPress.
*/

#include "CPowerModeResourceImpl.h"
#include <ResourceMaster.h>
#include "logging.h"
#include "ResourceDeploymentConfig.h"

CPowerModeResourceImpl::CPowerModeResourceImpl():
    m_pPowerModeEventProvider(new CPowerModeEventProvider()),
    m_bNSManagerAvailable(false),
    m_strPowerMode(""),
    m_eNSMNodeState(NodeStateTypes::NsmNodeState::NsmNodeState_NotSet)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,__FUNCTION__);
    subscribe();
}

CPowerModeResourceImpl::~CPowerModeResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,__FUNCTION__);
    if (m_pPowerModeEventProvider)
        delete m_pPowerModeEventProvider;
}

CPowerModeEventProvider* CPowerModeResourceImpl::getPowerModeEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,__FUNCTION__);
    return m_pPowerModeEventProvider;
}

void CPowerModeResourceImpl::statusEventListnerNSMManager(CommonAPI::AvailabilityStatus status)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,"%s %d", __FUNCTION__, static_cast<int>(status));

    if(status == CommonAPI::AvailabilityStatus::AVAILABLE )
    {
        if(m_pPowerMode_Proxy)
        {
            m_pPowerMode_Proxy->getVehiclePowerModeAttribute().getChangedEvent().subscribe(std::bind(&CPowerModeResourceImpl::onVehiclePowerMode,this,std::placeholders::_1));
            m_pPowerMode_Proxy->getNodeStateEvent().subscribe(std::bind(&CPowerModeResourceImpl::onGetNodeStateEvent,this,std::placeholders::_1));
            m_pPowerMode_Proxy->getSessionStateChangedEvent().subscribe
                    (std::bind(&CPowerModeResourceImpl::onGetSessionStateCb, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        }
        else
            LOG_WARNING(Log::e_LOG_CONTEXT_POWER_MODE,"m_pPowerMode_Proxy is NULL");
        m_bNSManagerAvailable = true;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,"NSMPressCtrl not available");
    }
}



void CPowerModeResourceImpl::subscribe()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,__FUNCTION__);
    CommonAPI::Runtime::setProperty("LogContext", "TML_HMI");
    CommonAPI::Runtime::setProperty("LibraryBase", "TML_HMI");

    /* create the runtime */
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    if(!runtime)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,"%s Error: could not load runtime", __FUNCTION__);
    }
    else
    {
        std::string domain = ResourceDeploymentConfig::getConfig().m_PowerMode_Proxy.domain;
        // create the Power mode proxy
        std::string connection = "dbusconnection";
        std::string instance = ResourceDeploymentConfig::getConfig().m_PowerMode_Proxy.instance;
        m_pPowerMode_Proxy = runtime->buildProxy<v2::org::genivi::NodeStateManager::ConsumerProxy>(domain, instance, connection);
        if(!m_pPowerMode_Proxy)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,"%s Error: could not create NSMPressCtrl proxy", __FUNCTION__);
        }
        else
        {
            m_pPowerMode_Proxy->getProxyStatusEvent().subscribe(std::bind(&CPowerModeResourceImpl::statusEventListnerNSMManager,this,std::placeholders::_1));
        }
    }
}


void CPowerModeResourceImpl::onVehiclePowerMode(std::string strMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,"%s, powerMode: %s",__FUNCTION__,strMode.c_str());

    if (m_pPowerModeEventProvider)
    {
        m_strPowerMode = strMode;
        m_pPowerModeEventProvider->updatePowerMode(strMode);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_POWER_MODE,"PowerModeEventProvider is null");
    }
}

void CPowerModeResourceImpl::onGetNodeStateEvent(NodeStateTypes::NsmNodeState eNsmNodeState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,"%s, nsmNodeState: %d",__FUNCTION__,static_cast<int>(eNsmNodeState));
    m_eNSMNodeState = eNsmNodeState;
    if (m_pPowerModeEventProvider)
        m_pPowerModeEventProvider->updateNSMNodeState(m_eNSMNodeState);
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_POWER_MODE,"PowerModeEventProvider is null");
    }
}

void CPowerModeResourceImpl::getNodeState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,"%s",__FUNCTION__);
    if(m_pPowerMode_Proxy)
    {
        m_pPowerMode_Proxy->GetNodeStateAsync(std::bind(&CPowerModeResourceImpl::asyncGetNodeStateCb,this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_POWER_MODE,"%s Error: NSMPressCtrl proxy is NULL", __FUNCTION__);
    }

}

void CPowerModeResourceImpl::asyncGetNodeStateCb(const CommonAPI::CallStatus& eStatus, const NodeStateTypes::NsmNodeState& eNsmNodeState, const NodeStateTypes::NsmErrorStatus& eErrorStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,"%s: status: %d, nsm node state: %d, errorStatus: %d", __FUNCTION__,
             static_cast<int>(eStatus), static_cast<int>(eNsmNodeState), static_cast<int>(eErrorStatus));

    if((CommonAPI::CallStatus::SUCCESS == eStatus) && (NodeStateTypes::NsmErrorStatus::NsmErrorStatus_Ok == eErrorStatus))
    {
        m_eNSMNodeState = eNsmNodeState;
        if (m_pPowerModeEventProvider)
            m_pPowerModeEventProvider->updateNSMNodeState(m_eNSMNodeState);
        else
            LOG_WARNING(Log::e_LOG_CONTEXT_POWER_MODE,"PowerModeEventProvider is null");
    }
}

std::string CPowerModeResourceImpl::getCurrentPowerMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,"%s, powerMode: %s",__FUNCTION__,m_strPowerMode.c_str());
    return m_strPowerMode;
}

int CPowerModeResourceImpl::getCurrentNSMNodeState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,"%s, nsm node state: %d",__FUNCTION__, static_cast<int>(m_eNSMNodeState));
    return static_cast<int>(m_eNSMNodeState);
}

void CPowerModeResourceImpl::onGetSessionStateCb(const string &Sessionname, const NodeStateTypes::NsmSeat& seat, const NodeStateTypes::NsmSessionState& sessionState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE, "%s: NSM Sessionname: %s, Seat: %d, SessionState: %d", __FUNCTION__, Sessionname.c_str(), seat.value_, sessionState.value_);

    if(ONE_HOUR_MODE_EXPIRY_SESSION == Sessionname.c_str())
    {
        if( (NodeStateTypes::NsmSessionState::NsmSessionState_Active == sessionState.value_) && (NodeStateTypes::NsmSeat::NsmSeat_Driver == seat.value_) )
        {
            if(m_pPowerModeEventProvider)
            {
                m_pPowerModeEventProvider->updateOneHourExpiryState(true);
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_POWER_MODE, "%s: PowerModeEventProvider is null", __FUNCTION__);
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE, "%s: In else, NSM SessionState: %d, Seat: %d", __FUNCTION__, sessionState.value_, seat.value_);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE, "%s: In else, NSM Sessionname: %s", __FUNCTION__, Sessionname.c_str());
    }
}

/*FixMe: This Method should not required to be called from HMI, this has to updated by service team.
 Need to remove once we get the proper fix from service team*/
void CPowerModeResourceImpl::setOneHourExpiryStateInactive()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE, "%s", __FUNCTION__);

    if(m_pPowerMode_Proxy)
    {
        m_pPowerMode_Proxy->SetSessionStateAsync(ONE_HOUR_MODE_EXPIRY_SESSION, NSM_SESSION_OWNER, NodeStateTypes::NsmSeat::NsmSeat_Driver,
                                                 NodeStateTypes::NsmSessionState::NsmSessionState_Inactive,
                                                 std::bind(&CPowerModeResourceImpl::onSetSessionStateAsyncCb, this, std::placeholders::_1, std::placeholders::_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_POWER_MODE, "%s: m_pPowerMode_Proxy is null", __FUNCTION__);
    }
}

void CPowerModeResourceImpl::onSetSessionStateAsyncCb(const CommonAPI::CallStatus& status, const NodeStateTypes::NsmErrorStatus& nsmErrorStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE, "%s: CallStatus: %d, NsmErrorStatus: %d", __FUNCTION__, static_cast<int>(status), nsmErrorStatus.value_);
}
