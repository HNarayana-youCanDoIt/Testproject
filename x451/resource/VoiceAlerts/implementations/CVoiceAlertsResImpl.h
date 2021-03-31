    /*****************************************************************
    * Project        Harman Car Multimedia System
    * (c) copyright  2018
    * Company        Harman/Becker Automotive Systems GmbH
    *                All rights reserved
    * Secrecy Level  STRICTLY CONFIDENTIAL
    ***************************************************************
    */
    /**
    * @file         CVoiceAlertsResImpl.h
    * @ingroup       HMIComponent
    * @author        Guru Alingal
    * CVoiceAlertsResImpl will be an interface to communicate to voice alert service
    * and to pass on the information to upper layers.
    */

#ifndef CVOICEALERTSRESIMPL_H
#define CVOICEALERTSRESIMPL_H

#include <interfaces/IVoiceAlerts.h>
#include <v0/com/harman/VoiceAlert/VoiceAlertServiceProxy.hpp>
#include <v1/com/harman/VoiceAlert/VoiceAlertType.hpp>
#include <resource/ResourceDeploymentConfig.h>
#include <capi/CAPIClientAbstraction.hpp>
#include <implementations/CVoiceAlertsEventProvider.h>
#include "logging.h"

class CVoiceAlertsResImpl : public IVoiceAlerts
{
public:
    CVoiceAlertsResImpl();

    ~CVoiceAlertsResImpl();

    // IVoiceAlerts interface
    /**
     * @brief getEventProvider - Method to get the eventprovider object of voice alerts
     * @return pointer of voice alerts event provider.
     */
    CVoiceAlertsEventProvider* getEventProvider() const;


    /**
     * @brief setVoiceAlertSelection - Method to set the voice alert selection.
     *          which is going to call voiceAlertProxy(Service) API.
     * @param bVoiceAlertSelection - bVoiceAlertSelection is holding the voice alert value set from voice alert adaptor.
     * @return  void.
     */
    void setVoiceAlertSelection(bool bVoiceAlertSelection) override;

private: //Methods
    /**
    * @brief VAProxyAvailability - status for the availability change of voice alert proxy
    * @param status - AvailabilityStatus
    * @return - void
    */
    void VAProxyAvailabilityCb(CommonAPI::AvailabilityStatus eStatus);

    /**
     * @brief onVasStatusAttributeCb - To handle the updates in VasStatus
     *        attribute
     * @param bStatus - Value of attribute
     * @return void
     */
    void onVasStatusAttributeCb(bool bStatus);

    /**
     * @brief onHuAlertStatusAttributeCb - To handle attribute updates for
     *        HuAlertStatusAttribute
     * @param eAlertStaus - status of voice alert
     * @return void
     */
    void onHuAlertStatusAttributeCb(VoiceAlertType::HuAlertStatus_enum eAlertStaus);

    /**
     * @brief onGetHuAlertStateAttributeCb - To handle attribute updates for
     *        HuAlertState_enum
     * @param eAlert - active voice alert
     * @return void
     */
    void onGetHuAlertStateAttributeCb(VoiceAlertType::HuAlertState_enum eAlert);

    /**
     * @brief onGetHuAlertStateMceAttribute - To handle attribute updates for
     *        HuAlertStateMce_enum
     * @param eMceAlert - active voice alert
     * @return void
     */
    void onGetHuAlertStateMceAttribute(VoiceAlertType::HuAlertStateMce_enum eMceAlert);

    /**
     * @brief onHuInfoFeaturePresenceAttributeCb - To handle attribute updates for
     *        HuInfoFeaturePresence
     * @param ePresence - feature presence
     * @return void
     */
    void onHuInfoFeaturePresenceAttributeCb(VoiceAlertType::HuInfoFeaturePresence_enum ePresence);

    /**
     * @brief onHuAlertHMISelectionAttributeCb - To handle attribute updated for
     *        HuAlertHMISelectionAttribute
     * @param eHMISelection - state of HMI selection
     * @return void
     */
    void onHuAlertHMISelectionAttributeCb(VoiceAlertType::HuHMISelection_enum eHMISelection);

    /**
     * @brief onCurDriveModeSigAttributeCb - To handle attribute updates for
     *        CurDriveModeSigAttribute
     * @param eDriveMode - current drive mode
     * @return void
     */
    void onCurDriveModeSigAttributeCb(VoiceAlertType::CurDriveModeSig_enum eDriveMode);

    /**
     * @brief onHuHMISelectionAsyncCb - Call back method which gives the call status and voice alert selection status.
     * @param   status - call status returns true if sucess else false
     * @param   HuHMISelection_enum - state of Voice alert selection
     * @return  void
     */
    void onHuHMISelectionAsyncCb(const CallStatus &status, const VoiceAlertType::HuHMISelection_enum& );


private: //Members

    /** @brief To store the current status of voice alert feature availability*/
    VoiceAlertType::HuInfoFeaturePresence_enum m_ePresence;

    /** @brief To store the latest alert received from service*/
    VoiceAlertType::HuAlertState_enum m_eAlert;

    /** @brief To store the latest alert received from service for MCE*/
    VoiceAlertType::HuAlertStateMce_enum m_eMceAlert;

    /** @brief To store the status of current alert*/
    VoiceAlertType::HuAlertStatus_enum m_eAlertStatus;

    /** @brief To store the status of user selection of voice alert status*/
    VoiceAlertType::HuHMISelection_enum m_eHMISelection;

    /** @brief To store the current drive mode*/
    VoiceAlertType::CurDriveModeSig_enum m_eDriveMode;

    /** @brief m_VoiceAlertProxy Proxy for voice alert service */
    CAPIClientAbstraction<VoiceAlertServiceProxy> m_objVoiceAlertProxy;

    /** @brief m_eventProvider - Voice alerts event provider to be used to send
      * data to adaptor layer*/
    CVoiceAlertsEventProvider* m_pEventProvider;

    /** @brief m_bIsVoiceAlertAvailable - To check voice alert service available or not*/
    bool m_bIsVoiceAlertAvailable;

    // IVoiceAlerts interface
public:
    int getVoiceAlertPresence() override;
    int getCurrentVoiceAlert() override;
    int getCurrentMceVoiceAlert() override;
    int getCurrentState() override;
    int getHMISelectionState() override;
};

#endif
