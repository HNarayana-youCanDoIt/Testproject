/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CParkAssistResourceImpl.cpp
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * CParkAssistResourceImpl, Resource Implementation for Park Assist.
 */

#include "CParkAssistResourceImpl.h"
#include <ResourceMaster.h>
#include "logging.h"
#include "ResourceDeploymentConfig.h"


#if !defined(PLATFORM_WIN32) && !defined(PLATFORM_LINUX_X86)
#include "NanoMsgService/NanoMsg.h"
#include "NanoMsgService/CHMINanoMsgEnums.h"
#include "NanoMsgService/CHMINanoMsgService.h"
#endif

CParkAssistResourceImpl::CParkAssistResourceImpl():
    m_pParkAssistEventProvider(new CParkAssistEventProvider()),
    m_objPDCServiceProxy(ResourceDeploymentConfig::getConfig().m_PdcService_Proxy.domain, ResourceDeploymentConfig::getConfig().m_PdcService_Proxy.instance),
    m_iVariantType(CParkAssistEnum::PARK_ASSIST_VARIANT_DEFAULT),
    m_bPdcSettingAvailable(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,__FUNCTION__);
    SUBSCRIBE(m_objPDCServiceProxy,getProxyStatusEvent(),&CParkAssistResourceImpl::parkAssistSettingsSeriveStatusCb,_1);
    getEarlyParkAssistData();
}

void CParkAssistResourceImpl::subscribePdcSettingsProxy()
{

    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,__FUNCTION__);
    SUBSCRIBE(m_objPDCServiceProxy, getPDcOnDelayTimerAttribute().getChangedEvent(), &CParkAssistResourceImpl::onParkAssistDelayTimerCb, _1);
    SUBSCRIBE(m_objPDCServiceProxy, getPDcRearToneReq_enumAttribute().getChangedEvent(), &CParkAssistResourceImpl::onParkAssistRearToneCb, _1);

#if defined(PLATFORM_WIN32) || defined(PLATFORM_LINUX_X86)
    /** Reverse gear status */
    SUBSCRIBE(m_objPDCServiceProxy, getReverseGearStatusAttribute().getChangedEvent(), &CParkAssistResourceImpl::onReverseGearStatusAttributeCb, _1);
#endif
    /** PDC screen sensor state */
    SUBSCRIBE(m_objPDCServiceProxy, getPDcHuVisualZoneRearSensStateAttribute().getChangedEvent(), &CParkAssistResourceImpl::onPDcHuVisualZoneRearSensStateAttribute, _1);

    /** RVC screen sensor state */
    SUBSCRIBE(m_objPDCServiceProxy, getPDcHuProxRearSensStateAttribute().getChangedEvent(), &CParkAssistResourceImpl::onPDcHuProxRearSensStateAttribute, _1);

    /** PDC faults */
    SUBSCRIBE(m_objPDCServiceProxy, getPDcHuFaultState_enumAttribute().getChangedEvent(), &CParkAssistResourceImpl::onPDcHuFaultState_enumAttribute, _1);

    /** RVC faults */
    SUBSCRIBE(m_objPDCServiceProxy, getRvcFaultAttribute().getChangedEvent(), &CParkAssistResourceImpl::onRvcFaultAttribute, _1);

    /** PDC + RVC faults */
    SUBSCRIBE(m_objPDCServiceProxy, getPdc_rvcFaultAttribute().getChangedEvent(), &CParkAssistResourceImpl::onPdc_rvcFaultAttribute, _1);

    /** RVC overlay angle */
    SUBSCRIBE(m_objPDCServiceProxy, getSAsAngEPASAttribute().getChangedEvent(), &CParkAssistResourceImpl::onSAsAngEPASAttribute, _1);

    /** RVC overlay direction */
    SUBSCRIBE(m_objPDCServiceProxy, getSAsAngEPAsDir_enumAttribute().getChangedEvent(), &CParkAssistResourceImpl::onSAsAngEPAsDir_enumAttribute, _1);

    /** Pdc presence */
    SUBSCRIBE(m_objPDCServiceProxy, getPdcPresence_enAttribute().getChangedEvent(), &CParkAssistResourceImpl::onPdcPresence_enAttributeCb, _1);

    /** Pdc settings update */
    SUBSCRIBE(m_objPDCServiceProxy, getPdcsettingUpdateAttribute().getChangedEvent(), &CParkAssistResourceImpl::onPdcSettingUpdateAttributeCb, _1);
}

CParkAssistResourceImpl::~CParkAssistResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,__FUNCTION__);
}

CParkAssistEventProvider *CParkAssistResourceImpl::getParkAssistEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,__FUNCTION__);
    return m_pParkAssistEventProvider;
}

void CParkAssistResourceImpl::parkAssistSettingsSeriveStatusCb(CommonAPI::AvailabilityStatus eStatus)
{
    if(CommonAPI::AvailabilityStatus::AVAILABLE ==  eStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s, :true", __FUNCTION__);
        m_bPdcSettingAvailable = true;
        subscribePdcSettingsProxy();

        /** Getting the type of park assist variant */

#if defined(PLATFORM_WIN32) || defined(PLATFORM_LINUX_X86)
        getParkAssistVariantType();
#endif
        /** Getting the type of RVC overlay */
        getRvcOverlayType();

        /** Updating the park assist status to HMI */
        updateParkAssistStatusToHMI();

        /** Getting the pdc presence status*/
        getPdcPresence();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST,"%s, :false", __FUNCTION__);
        m_bPdcSettingAvailable = false;
    }
}

void CParkAssistResourceImpl::onParkAssistDelayTimerCb(uint8_t iPdcDelayTimer)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s, Pdc delay timer : %d ",__FUNCTION__, iPdcDelayTimer);
    if(m_pParkAssistEventProvider)
        m_pParkAssistEventProvider->updateParkAssistDelayTimer(iPdcDelayTimer);
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST,"ParkAssistEventProvider is null");
}

void CParkAssistResourceImpl::onParkAssistRearToneCb(uint8_t iPdcRearTone)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s, Pdc Rear Tone : %d ",__FUNCTION__, iPdcRearTone);
    if(m_pParkAssistEventProvider)
        m_pParkAssistEventProvider->updateParkAssistRearTone(iPdcRearTone);
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST,"ParkAssistEventProvider is null");
}

void CParkAssistResourceImpl::setParkAssistDelayTimer(uint8_t iParkAssistDelayTimer)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s, PDC Delay Timer : %d ",__FUNCTION__, iParkAssistDelayTimer);
    if(m_bPdcSettingAvailable)
    {
        m_objPDCServiceProxy->getPDcOnDelayTimerAttribute().setValueAsync(iParkAssistDelayTimer,std::bind(&CParkAssistResourceImpl::setParkAssistDelayTimerAsyncCb,this, _1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST,"%s, ParkAssist Proxy not available", __FUNCTION__);
    }
}

void CParkAssistResourceImpl::setParkAssistDelayTimerAsyncCb(const CallStatus &status, int _ValueType)
{
    CPP_UNUSED(_ValueType);
    if(CommonAPI::CallStatus::SUCCESS == status)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s, true", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s, false", __FUNCTION__);
    }
}

void CParkAssistResourceImpl::setParkAssistRearTone(CParkAssistEnum::EPDcRearTones ePdcRearTone)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s, PDC Tone Volume : %d ",__FUNCTION__, ePdcRearTone);
    ParkAssistBaseType::PDcRearToneReq_enum ePdcRearToneReq = static_cast<ParkAssistBaseType::PDcRearToneReq_enum::Literal>(ePdcRearTone);
    if(m_bPdcSettingAvailable)
    {
        m_objPDCServiceProxy->getPDcRearToneReq_enumAttribute().setValueAsync(ePdcRearToneReq,std::bind(&CParkAssistResourceImpl::setParkAssistRearToneAsyncCb,this, _1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST,"%s, ParkAssist Proxy not available", __FUNCTION__);
    }
}

void CParkAssistResourceImpl::setParkAssistRearToneAsyncCb(const CallStatus &status, ParkAssistBaseType::PDcRearToneReq_enum _ValueType)
{
    CPP_UNUSED(_ValueType);
    if(CommonAPI::CallStatus::SUCCESS == status)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s, true", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s, false", __FUNCTION__);
    }
}

void CParkAssistResourceImpl::onSetHmiNotificationCb(const CallStatus &callStatus, bool hmiNotification)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Call Status: %d, HMINotification Status: %d", __FUNCTION__, static_cast<int>(callStatus), hmiNotification);
}


/** *********************************PDC-RVC RELATED METHODS ********************************* */

void CParkAssistResourceImpl::updateParkAssistStatusToHMI()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, __FUNCTION__);

    if(m_pParkAssistEventProvider)
    {
        m_pParkAssistEventProvider->updateParkAssistStatusToHMI();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: ParkAssistEventProvider is null", __FUNCTION__);
    }
}

void CParkAssistResourceImpl::getEarlyParkAssistData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, __FUNCTION__);

#if defined(PLATFORM_WIN32) || defined(PLATFORM_LINUX_X86)
    /* This is done to get the reverse gear status and park assist variant status
     * as soon as HMI is up using nano message. All these information will be
     * fetched using dbus as well, hence this change is not required for simulation.
    */
#else
    int iSocketID = ConnectToNanoMsgHost(RVCAPP_SOCKET_ADDR);
    CHMINanoMsgService::setNanoMsgSocketID(iSocketID);

    /* Request Park Assist Variant Type */
    getParkAssistVariantInfo();

    /* Request Reverse Gear Status Type */
    int iRevGearStatus = NanoMsgHandShake(iSocketID, ENANOMSG_RVC_HMI_STATUS);
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Park assist Nano Msg hand shake completed. reverse gear state is: %d", __FUNCTION__, iRevGearStatus);

    ENanoMsgId eACKMsg = static_cast<ENanoMsgId>(updateReverseGearInfo(iRevGearStatus));
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: reverse gear state is: %d, ack: %d ", __FUNCTION__, iRevGearStatus, static_cast<int>(eACKMsg));

    if (ENANOMSG_INVALID != eACKMsg)
    {
        int iReturn = SendNanoMessage(iSocketID, eACKMsg);
        if (-1 == iReturn)
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Reverse gear status ack hand shake failed.", __FUNCTION__);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Reverse gear status ack shake successful, message sent",__FUNCTION__);
        }
    }
#endif
}
void CParkAssistResourceImpl::getParkAssistVariantInfo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s", __FUNCTION__);

#if defined(PLATFORM_WIN32) || defined(PLATFORM_LINUX_X86)
    //Park assist variant info getting through nano message is not required for simulation, required only for target.
#else
    int iSocketID = CHMINanoMsgService::getNanoMsgSocketID();
    int iVariantNanoMsg = NanoMsgHandShake(iSocketID, ENANOMSG_PARK_VARIANT_INFO);

    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Park assist Nano Msg hand shake completed. park assist variant is: %d", __FUNCTION__, iVariantNanoMsg);

    if ((ENANOMSG_PDC_VARIANT != iVariantNanoMsg) || (ENANOMSG_PDC_RVC_VARIANT != iVariantNanoMsg) || (ENANOMSG_RVC_VARIANT != iVariantNanoMsg))
    {
        iVariantNanoMsg = NanoMsgHandShake(iSocketID, ENANOMSG_PARK_VARIANT_INFO);
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Park assist Nano Msg hand shake completed. park assist variant is: %d", __FUNCTION__, iVariantNanoMsg);
    }
    switch(iVariantNanoMsg)
    {
    case EN_PDC_VARIANT:
        m_iVariantType = CParkAssistEnum::PARK_ASSIST_VARIANT_PDC;
        break;
    case EN_PDC_RVC_VARIANT:
        m_iVariantType = CParkAssistEnum::PARK_ASSIST_VARIANT_PDC_RVC;
        break;
    case EN_RVC_VARIANT:
        m_iVariantType = CParkAssistEnum::PARK_ASSIST_VARIANT_RVC;
        break;
    default:
        m_iVariantType = CParkAssistEnum::PARK_ASSIST_VARIANT_DEFAULT;
        break;
    }

    if(m_pParkAssistEventProvider)
    {
        m_pParkAssistEventProvider->updateParkAssistVariantType(m_iVariantType);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: ParkAssistEventProvider is null", __FUNCTION__);
    }

#endif
}

int CParkAssistResourceImpl::updateReverseGearInfo(int iRevGearStatus)
{
#if defined(PLATFORM_WIN32) || defined(PLATFORM_LINUX_X86)
    /* This is done to update the reverse gear status using nano message. All these information will be
     * fetched using dbus as well, hence this change is not required for simulation.
    */
    Q_UNUSED(iRevGearStatus)
    return -1;
#else
    if(CParkAssistEnum::PARK_ASSIST_VARIANT_DEFAULT == m_iVariantType)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Park assist variant info is not available in HMI: %d", __FUNCTION__, m_iVariantType);
        getParkAssistVariantInfo();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Park assist variant info is available in HMI: %d", __FUNCTION__, m_iVariantType);
    }

    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Reverse gear status: %d", __FUNCTION__, iRevGearStatus);
    ENanoMsgId eACKMsg = ENANOMSG_INVALID;
    bool bReverseGearStatus = false;
    if (ENANOMSG_REV_ENGAGE == iRevGearStatus)
    {
        eACKMsg = ENANOMSG_REV_ENGAGE_ACK;
        bReverseGearStatus = true;
    }
    else if (ENANOMSG_REV_DISENGAGE == iRevGearStatus)
    {
        eACKMsg = ENANOMSG_REV_DISENGAGE_ACK;
        bReverseGearStatus = false;
        /* Wherever we get disengage we need to set the activate from HMI false */
        m_sRevStatus.setBActivationStatus(false);
    }
    else
    {
        // Do Nothing
    }

    m_sRevStatus.setBReverseGearStatus(bReverseGearStatus);
    bool bActivationStatus = m_sRevStatus.getBActivationStatus();
    m_sRevStatus.setBActivationStatus(false);

    if(m_pParkAssistEventProvider)
    {
        m_pParkAssistEventProvider->updateScreenPDC_RVCStatus(bReverseGearStatus, bActivationStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: ParkAssistEventProvider is null", __FUNCTION__);
    }
    return eACKMsg;
#endif
}

void CParkAssistResourceImpl::setReverseGearStatusAttribute(bool bReverseGearStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Request - ReverseGearStatusAttribute : %d", __FUNCTION__, bReverseGearStatus);

    ParkAssistBaseType::HuPDcReqType_enum ePdcRvcRequestFromHMI;
    if(true == bReverseGearStatus)  /** Requested from HMI to show PDC-RVC */
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Park assist Activation requested", __FUNCTION__);
        ePdcRvcRequestFromHMI = ParkAssistBaseType::HuPDcReqType_enum::En_HU_PDC_Activate_Req;
        m_sRevStatus.setBActivationStatus(true);
    }
    else    /** Requested from HMI to hide PDC-RVC */
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Park assist De-activation requested", __FUNCTION__);
        ePdcRvcRequestFromHMI = ParkAssistBaseType::HuPDcReqType_enum::En_HU_PDC_Deactivate_Req;
        m_sRevStatus.setBActivationStatus(false);
    }

    if(m_bPdcSettingAvailable)
    {

        m_objPDCServiceProxy->getHuPDcReqType_enumAttribute().setValueAsync(ParkAssistBaseType::HuPDcReqType_enum::En_HU_PDC_Deactivate_Req, std::bind(&CParkAssistResourceImpl::setReverseGearStatusAttributeAsyncCb, this, _1, _2));
        m_objPDCServiceProxy->getHuPDcReqType_enumAttribute().setValueAsync(ePdcRvcRequestFromHMI, std::bind(&CParkAssistResourceImpl::setReverseGearStatusAttributeAsyncCb, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Park assist settings is not available.", __FUNCTION__);
    }
}

void CParkAssistResourceImpl::setReverseGearStatusAttributeAsyncCb(const CallStatus &status, int _ValueType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: CallStatus: %d, ValueType: %d", __FUNCTION__, static_cast<int>(status), _ValueType);
}

void CParkAssistResourceImpl::onReverseGearStatusAttributeCb(ParkAssistBaseType::reverseStatus sReverseGearStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Response - Reverse gear status: %d, Activation status from HMI: %d",
             __FUNCTION__, sReverseGearStatus.getBReverseGearStatus(), sReverseGearStatus.getBActivationStatus());

    if(m_pParkAssistEventProvider)
    {
        m_sRevStatus.setBActivationStatus(sReverseGearStatus.getBActivationStatus());
        m_sRevStatus.setBReverseGearStatus(sReverseGearStatus.getBReverseGearStatus());
        m_pParkAssistEventProvider->updateScreenPDC_RVCStatus(sReverseGearStatus.getBReverseGearStatus(), sReverseGearStatus.getBActivationStatus());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: ParkAssistEventProvider is null", __FUNCTION__);
    }
}

void CParkAssistResourceImpl::getParkAssistVariantType()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, __FUNCTION__);

    if(m_bPdcSettingAvailable)
    {
        m_objPDCServiceProxy->getParkAssistVariant_enumAttribute().getValueAsync(std::bind(&CParkAssistResourceImpl::onParkAssistVariant_enumAttributeCb, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Park assist settings is not available.", __FUNCTION__);
    }
}

void CParkAssistResourceImpl::onParkAssistVariant_enumAttributeCb(const CallStatus &status, ParkAssistBaseType::ParkAssistVariant_enum eParkAssistVariantType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Response - CallStatus: %d, ParkAssist Variant Type: %d", __FUNCTION__, static_cast<int>(status), eParkAssistVariantType.value_);

    if(m_pParkAssistEventProvider)
    {
        m_pParkAssistEventProvider->updateParkAssistVariantType(eParkAssistVariantType.value_);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: ParkAssistEventProvider is null", __FUNCTION__);
    }
}

void CParkAssistResourceImpl::onPDcHuVisualZoneRearSensStateAttribute(uint32_t uiPDCSensorState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s, Response - PDC Sensor state: %d", __FUNCTION__, uiPDCSensorState);

    if(m_pParkAssistEventProvider)
    {
        m_pParkAssistEventProvider->updatePdcScreenSensorState(uiPDCSensorState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: ParkAssistEventProvider is null", __FUNCTION__);
    }
}

void CParkAssistResourceImpl::onPDcHuProxRearSensStateAttribute(uint32_t uiRVCSensorState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Response - RVC Sensor state: %d", __FUNCTION__, uiRVCSensorState);

    if(m_pParkAssistEventProvider)
    {
        m_pParkAssistEventProvider->updateRvcScreenSensorState(uiRVCSensorState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: ParkAssistEventProvider is null", __FUNCTION__);
    }
}

void CParkAssistResourceImpl::onPDcHuFaultState_enumAttribute(ParkAssistBaseType::PDcHuFaultState_enum ePdcFault)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s: Response - PDC Fault: %d", __FUNCTION__, ePdcFault.value_);

    if(m_pParkAssistEventProvider)
    {
        m_pParkAssistEventProvider->updatePdcFault(ePdcFault.value_);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: ParkAssistEventProvider is null", __FUNCTION__);
    }
}

void CParkAssistResourceImpl::onRvcFaultAttribute(ParkAssistBaseType::RvcFault_enum eRvcFault)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Response - RVC Fault: %d", __FUNCTION__, eRvcFault.value_);

    if(m_pParkAssistEventProvider)
    {
        m_pParkAssistEventProvider->updateRvcFault(eRvcFault.value_);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: ParkAssistEventProvider is null", __FUNCTION__);
    }
}

void CParkAssistResourceImpl::onPdc_rvcFaultAttribute(ParkAssistBaseType::Pdc_RvcFault_enum ePdcRvcFault)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Response - PDC+RVC Fault: %d", __FUNCTION__, ePdcRvcFault.value_);

    if(m_pParkAssistEventProvider)
    {
        m_pParkAssistEventProvider->updatePdcRvcFault(ePdcRvcFault.value_);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: ParkAssistEventProvider is null", __FUNCTION__);
    }
}

void CParkAssistResourceImpl::getRvcOverlayType()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, __FUNCTION__);

    if(m_bPdcSettingAvailable)
    {
        m_objPDCServiceProxy->getRvcOverlayTypeAttribute().getValueAsync(std::bind(&CParkAssistResourceImpl::onRvcOverlayTypeAttributeCb, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Park assist settings is not available.", __FUNCTION__);
    }
}

void CParkAssistResourceImpl::onRvcOverlayTypeAttributeCb(const CallStatus &status, ParkAssistBaseType::RvcOverlayType_enum eRvcOverlayType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Response - CallStatus: %d, RVC Overlay Type: %d", __FUNCTION__, static_cast<int>(status), eRvcOverlayType.value_);

    if(m_pParkAssistEventProvider)
    {
        m_pParkAssistEventProvider->updateRvcOverlayType(eRvcOverlayType.value_);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: ParkAssistEventProvider is null", __FUNCTION__);
    }
}

void CParkAssistResourceImpl::onSAsAngEPAsDir_enumAttribute(ParkAssistBaseType::SAsAngEPAsDir_enum eOverlayDirection)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Response - Overlay direction: %d", __FUNCTION__, eOverlayDirection.value_);

    if(m_pParkAssistEventProvider)
    {
        m_pParkAssistEventProvider->updateRvcOverlayDirection(eOverlayDirection.value_);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: ParkAssistEventProvider is null", __FUNCTION__);
    }
}

void CParkAssistResourceImpl::onPdcPresence_enAttributeCb(ParkAssistBaseType::PDcPresence_enum ePdcPresence)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Response - Pdc presence %d", __FUNCTION__, ePdcPresence.value_);
    if(m_pParkAssistEventProvider)
    {
        m_pParkAssistEventProvider->updatePdcPresence(ePdcPresence.En_PDC_Present == ePdcPresence.value_);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: ParkAssistEventProvider is null", __FUNCTION__);
    }
}

void CParkAssistResourceImpl::onPdcSettingUpdateAttributeCb(ParkAssistBaseType::pdcsettingErrorUpdate objPdcSettingsErrorUpdate)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Response - Pdc Settings Error Status : %d, Pdc Settings Error Id : %d ",
             __FUNCTION__, objPdcSettingsErrorUpdate.getBErrorStatus(), objPdcSettingsErrorUpdate.getU8ErrorId());
    if(m_pParkAssistEventProvider)
    {
        m_pParkAssistEventProvider->updatePdcSettingsStatus(objPdcSettingsErrorUpdate.getBErrorStatus(), objPdcSettingsErrorUpdate.getU8ErrorId());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: ParkAssistEventProvider is null", __FUNCTION__);
    }
}

void CParkAssistResourceImpl::onSAsAngEPASAttribute(double dOverlayAngle)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Response - Overlay angle: %f", __FUNCTION__, dOverlayAngle);

    if(m_pParkAssistEventProvider)
    {
        m_pParkAssistEventProvider->updateRvcOverlayAngle(dOverlayAngle);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: ParkAssistEventProvider is null", __FUNCTION__);
    }
}

void CParkAssistResourceImpl::getPdcPresence()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s ",__FUNCTION__);

    if(m_bPdcSettingAvailable)
    {
        m_objPDCServiceProxy->getPdcPresence_enAttribute().getValueAsync(std::bind(&CParkAssistResourceImpl::onPdcPresenceAsyncCbResp, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST,"%s : Park assist settings is not available.", __FUNCTION__);
    }
}

void CParkAssistResourceImpl::onPdcPresenceAsyncCbResp(const CallStatus &status, ParkAssistBaseType::PDcPresence_enum ePdcPresence)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Response - CallStatus: %d, Pdc presence : %d", __FUNCTION__, static_cast<int>(status), ePdcPresence.value_);

    if(m_pParkAssistEventProvider)
    {
        m_pParkAssistEventProvider->updatePdcPresence(ePdcPresence.En_PDC_Present == ePdcPresence.value_);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: ParkAssistEventProvider is null", __FUNCTION__);
    }
}

void CParkAssistResourceImpl::setHmiNotificationAttribute(bool bHmiUpStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s status: %d",__FUNCTION__, static_cast<int>(bHmiUpStatus));

#if defined(PLATFORM_WIN32) || defined(PLATFORM_LINUX_X86)
    if(m_bPdcSettingAvailable)
    {
        m_objPDCServiceProxy->getHmiNotificationAttribute().setValueAsync(bHmiUpStatus, std::bind(&CParkAssistResourceImpl::onSetHmiNotificationCb, this, _1, _2));
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: getHMINotificationAttribute called", __FUNCTION__);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Park assist settings is not available.", __FUNCTION__);
    }
#else
    SendNanoMessage(CHMINanoMsgService::getNanoMsgSocketID(), ENANOMSG_HMI_READY_NOTIFICATION);
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Park assist HMI ready hand shake successful", __FUNCTION__);
#endif
}

/** *********************************PDC-RVC RELATED METHODS ********************************* */


bool CParkAssistResourceImpl::getRevGearStatus()
{
    return m_sRevStatus.getBReverseGearStatus();
}

bool CParkAssistResourceImpl::getActivationStatus()
{
    return m_sRevStatus.getBActivationStatus();
}

int CParkAssistResourceImpl::getVariantType()
{
    return m_iVariantType;
}
