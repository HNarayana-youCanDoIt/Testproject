/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CParkAssistResourceImpl.h
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * CParkAssistResourceImpl, Resource Implementation for Park Assist.
 */

#ifndef CPARKASSISTRESOURCEIMPL_H
#define CPARKASSISTRESOURCEIMPL_H

#include "interfaces/IParkAssistResource.h"
#include "CParkAssistEventProvider.h"
#include "ParkAssist/CParkAssistEnums.h"

using namespace std;
using namespace v0::com::harman::ParkAssist;
using namespace v1::com::harman::ParkAssist;

/**
 * @brief The EParkAssistNanoMsg - Possible message types for park assist
 * nano messages
 */
enum EParkAssistNanoMsg
{
    EN_HMI_READY_NOTIFICATION = 11,     // Message to be sent
    EN_HMI_READY_NOTIFICATION_ACK = 18, //Expected reply

    EN_RVC_HMI_STATUS = 28,             //Message to be sent
    EN_REV_ENGAGE = 19,                 // Expected reply if reverse gear engaged.
    EN_REV_DISENGAGE = 20,              //Expected reply if reverse gear disengaged.

    EN_PARK_VARIANT_INFO = 31,          //Message to be sent
    EN_PDC_VARIANT = 32,                // Expected reply if variant is only PDC
    EN_PDC_RVC_VARIANT = 33,            // Expected reply if variant is PDC_RVC
    EN_RVC_VARIANT = 34,                // Expected reply if variant is only RVC
};

class CParkAssistResourceImpl : public IParkAssistResource
{
public:
    virtual ~CParkAssistResourceImpl();

public:
        CParkAssistEventProvider* getParkAssistEventProvider();
    /**
    * @brief	This function is to check the availability of audio settings proxy.
    * @param    eStatus: status will have API availability status.
    * @return	void.
    */
    void parkAssistSettingsSeriveStatusCb(CommonAPI::AvailabilityStatus eStatus);

    /*****  Request METHODS  ****************************/
    void setParkAssistDelayTimer(uint8_t iParkAssistDelayTimer) override;

    void setParkAssistRearTone(CParkAssistEnum::EPDcRearTones ePdcRearTone) override;

    void setReverseGearStatusAttribute(bool bReverseGearStatus) override;

    void setHmiNotificationAttribute(bool bHmiUpStatus) override;

    bool getRevGearStatus() override;

    bool getActivationStatus() override;

    int getVariantType() override;

    /*****  CALL BACK METHODS  ****************************/
    void onParkAssistDelayTimerCb(uint8_t iPdcDelayTimer) override;

    void onParkAssistRearToneCb(uint8_t iPdcRearTone) override;

    void setParkAssistDelayTimerAsyncCb(const CallStatus &status, int _ValueType) override;

    void setParkAssistRearToneAsyncCb(const CallStatus &status, ParkAssistBaseType::PDcRearToneReq_enum _ValueType) override;

    /**
     * @brief	This is a callback method to the getChangedEvent of getReverseGearStatusAttribute.
     * @param	ParkAssistBaseType::reverseStatus sReverseGearStatus: Park assist service sends a structure which contains,
     *          reverseGearStatus - Status of reverse gear, true - engaged, false - dis-engaged
     *          activationStatus - Activation status from HMI, true - show screen, false - hide screen
     * @return	void
     */
    void onReverseGearStatusAttributeCb(ParkAssistBaseType::reverseStatus sReverseGearStatus);

    /**
     * @brief	This is a callback method to the setValueAsync of getReverseGearStatusAttribute, which tells the status of call.
     * @param	const CallStatus &status: status will have API call status.
     * @param	int _ValueType: contains value of API call
     * @return	void
     */
    void setReverseGearStatusAttributeAsyncCb(const CallStatus &status, int _ValueType);

    /**
     * @brief	This method requests variant info, when proxy is available
     * @param	void
     * @return	void
     */
    void getParkAssistVariantType();

    /**
     * @brief	This is a callback method to the getValueAsync of getParkAssistVariant_enumAttribute
     * @param	const CallStatus &status: status will have API call status.
     * @param	ParkAssistBaseType::ParkAssistVariant_enum: contains park assist variant type
     * @return	void
     */
    void onParkAssistVariant_enumAttributeCb(const CallStatus &status, ParkAssistBaseType::ParkAssistVariant_enum eParkAssistVariantType);

    /**
     * @brief	This is a callback method to the getChangedEvent of getPDcHuVisualZoneRearSensStateAttribute.
     * @param	uint32_t uiPDCSensorState: Distance from obstacle, in which zone the obstacle is present
     * @return	void
     */
    void onPDcHuVisualZoneRearSensStateAttribute(uint32_t uiPDCSensorState);

    /**
     * @brief	This is a callback method to the getChangedEvent of getPDcHuProxRearSensStateAttribute.
     * @param	uint32_t uiRVCSensorState: Distance from obstacle, in which zone the obstacle is present
     * @return	void
     */
    void onPDcHuProxRearSensStateAttribute(uint32_t uiRVCSensorState);

    /**
     * @brief	This is a callback method to the getChangedEvent of getPDcHuFaultState_enumAttribute.
     * @param	ParkAssistBaseType::PDcHuFaultState_enum ePdcFault: PDC fault info message index is received
     * @return	void
     */
    void onPDcHuFaultState_enumAttribute(ParkAssistBaseType::PDcHuFaultState_enum ePdcFault);

    /**
     * @brief	This is a callback method to the getChangedEvent of getRvcFaultAttribute.
     * @param	ParkAssistBaseType::RvcFault_enum eRvcFault: RVC fault info message index is received
     * @return	void
     */
    void onRvcFaultAttribute(ParkAssistBaseType::RvcFault_enum eRvcFault);

    /**
     * @brief	This is a callback method to the getChangedEvent of getPdc_rvcFaultAttribute.
     * @param	ParkAssistBaseType::Pdc_RvcFault_enum ePdcRvcFault: PDC-RVC fault info message index is received
     * @return	void
     */
    void onPdc_rvcFaultAttribute(ParkAssistBaseType::Pdc_RvcFault_enum ePdcRvcFault);

    /**
     * @brief	This method requests RVC overlay type, when proxy is available
     * @param	void
     * @return	void
     */
    void getRvcOverlayType();

    /**
     * @brief	This is a callback method to the getValueAsync of getRvcOverlayTypeAttribute
     * @param	const CallStatus &status: status will have API call status.
     * @param	ParkAssistBaseType::RvcOverlayType_enum eRvcOverlayType: contains RVC overlay type static / dynamic
     * @return	void
     */
    void onRvcOverlayTypeAttributeCb(const CallStatus &status, ParkAssistBaseType::RvcOverlayType_enum eRvcOverlayType);

    /**
     * @brief	This is a callback method to the getChangedEvent of getSAsAngEPAsDir_enumAttribute.
     * @param	ParkAssistBaseType::SAsAngEPAsDir_enum eOverlayDirection: clockwise or counter-clockwise direction
     * @return	void
     */
    void onSAsAngEPAsDir_enumAttribute(ParkAssistBaseType::SAsAngEPAsDir_enum eOverlayDirection);

    /**
     * @brief updateReverseGearInfo update the reverse gear status (internal function)
     * @param iRevGearStatus current reverse gear status
     * @return provide the ACK value
     */

    int updateReverseGearInfo(int iRevGearStatus);

    /**
     * @brief getParkAssistVariantInfo: Requests park assist service for park assist variant info and updates the same to adaptor layer.
     * @param void.
     * @return void.
     */
    void getParkAssistVariantInfo();


    /**
     * @brief This is a callback method to the getChangedEvent of getPdcPresence_enAttribute.
     * @param   ParkAssistBaseType::PDcPresence_enum: pdc presence status
     * @return  void
     */
    void onPdcPresence_enAttributeCb(ParkAssistBaseType::PDcPresence_enum ePdcPresence);

    /**
     * @brief This is a callback method when park assist service notifies HMI that settings cannot be updated
     *          to show error popup on HMI.
     * @param   objPdcSettingsErrorUpdate : Park Assist service sends a structure which contains error status and error id.
     * @return  void.
     */
    void onPdcSettingUpdateAttributeCb(ParkAssistBaseType::pdcsettingErrorUpdate objPdcSettingsErrorUpdate);

    /**
     * @brief	This is a callback method to the getChangedEvent of getSAsAngEPASAttribute.
     * @param	double dOverlayAngle: steering wheel angle to be displayed on screen
     * @return	void
     */
    void onSAsAngEPASAttribute(double dOverlayAngle);

    /**
     * @brief getPdcPresence : This method requests pdc presence status, when proxy is available
     * @param   void.
     * @return  void.
     */
    void getPdcPresence();

    /**
     * @brief   This is a callback method to the getValueAsync of getPdcPresenceAttribute
     * @param	const CallStatus &status: status will have API call status.
     * @param	ParkAssistBaseType::PDcPresence_enum ePDcPresenc: contains pdc presence status
     * @return  void
     */
    void onPdcPresenceAsyncCbResp(const CallStatus &status, ParkAssistBaseType::PDcPresence_enum ePdcPresence);

private:

    /**
     * @brief Adding ResourceFactory class as friend class so that
     * ResourceFactory shall be able to create the instance of this class.
     */
    friend class ResourceFactory;

    CParkAssistResourceImpl();

    /**
    * @brief	This function is to subscribe the pdc settings events
    *           provided by PDCService proxy.
    * @param    void.
    * @return	void.
    */
    void subscribePdcSettingsProxy();

    /**
     * @brief onSetHmiNotificationCb - Call back to handle async update of HMINotfication attribute of parkassist service.
     * @param callStatus - Status of the api call
     * @param hmiNotification - updated value of hmiNotofication attribute.
     * @return void
     */
    void onSetHmiNotificationCb(const CallStatus &callStatus, bool hmiNotification );

    /**
     * @brief	This function is to update the park assist proxy status.
     * @param    void.
     * @return	void.
     */
    void updateParkAssistStatusToHMI();

    /**
     * @brief getEarlyParkAssistData - To fetch the early park assist data using nano message
     * @param void
     * @return void
     */
    void getEarlyParkAssistData();

    /* Create an instance of the CParkAssistEventProvider to emit signals to the upper layer **/
    CParkAssistEventProvider* m_pParkAssistEventProvider;

    /* PDCServiceProxy class object to call pdc proxy methods **/
    CAPIClientAbstraction<PDCServiceProxy> m_objPDCServiceProxy;

    /** To store the current state of reverse gear */
    ParkAssistBaseType::reverseStatus m_sRevStatus;

    /** To store the current park assist variant */
    int m_iVariantType;

    /* This variable holds the service availability status, TRUE if available else FALSE **/
    bool m_bPdcSettingAvailable;

};

#endif // CPARKASSISTRESOURCEIMPL_H
