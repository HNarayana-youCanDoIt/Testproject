/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CParkAssistEventProvider.h
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * CParkAssistEventProvider, Class to send signals to Setup Application layer on Park Assist Resource events
 */

#ifndef CPARKASSISTEVENTPROVIDER_H
#define CPARKASSISTEVENTPROVIDER_H

#include <QObject>
#include <string>
using namespace std;

class CParkAssistEventProvider : public QObject
{
    Q_OBJECT
public:
    CParkAssistEventProvider(QObject* pParent = 0);
    ~CParkAssistEventProvider();

signals:
    /**
    * @brief	This function is called internally when pdc delay timer changed and
    *           consumed by the application layer.
    * @param	iPdcDelayTimer: pdc delay timer value.
    * @return	void.
    */
    void sigUpdateParkAssistDelayTimer(int iPdcDelayTimer);

    /**
    * @brief	This function is called internally when pdc rear tone changed and
    *           consumed by the application layer.
    * @param	iPdcRearTone: pdc rear tone value.
    * @return	void.
    */
    void sigUpdateParkAssistRearTone(int iPdcRearTone);

    /**
     * @brief	This signal gets emitted on reverse gear status change.
     * @param	bool bReverseGearStatus: status of reverse gear, engaged or dis-engaged
     * @param	bool bActivationStatus: true - show screen, false - hide screen
     * @return	void
     */
    void sigScreenPDC_RVCStatus(bool bReverseGearStatus, bool bActivationStatus);

    /**
     * @brief	This signal gets emitted on park assist variant change.
     * @param	int iParkAssistVariantType: Variant type, PDC, RVC or PDC+RVC
     * @return	void
     */
    void sigParkAssistVariantType(int iParkAssistVariantType);

    /**
     * @brief	This signal gets emitted on PDC screen sensor information change.
     * @param	int iPdcSensorState: Holds in which zone the obstacle is present
     * @return	void
     */
    void sigPdcScreenSensorState(int iPdcSensorState);

    /**
     * @brief	This signal gets emitted on RVC screen sensor information change.
     * @param	int iRvcSensorState: Holds in which zone the obstacle is present
     * @return	void
     */
    void sigRvcScreenSensorState(int iRvcSensorState);

    /**
     * @brief	This signal gets emitted on PDC fault state change.
     * @param	int iPdcFault: Holds the PDC fault index, based on which corresponding fault message gets displayed
     * @return	void
     */
    void sigPdcFault(int iPdcFault);

    /**
     * @brief	This signal gets emitted on RVC fault state change.
     * @param	int iRvcFault: Holds the RVC fault index, based on which corresponding fault message gets displayed
     * @return	void
     */
    void sigRvcFault(int iRvcFault);

    /**
     * @brief	This signal gets emitted on PDC+RVC fault state change.
     * @param	int iPdcRvcFault: Holds the PDC+RVC fault index, based on which corresponding fault message gets displayed
     * @return	void
     */
    void sigPdcRvcFault(int iPdcRvcFault);

    /**
     * @brief	This signal gets emitted on RVC overlay type change.
     * @param	int iRvcOverlayType: Current active overlay, Static / Dynamic
     * @return	void
     */
    void sigRvcOverlayType(int iRvcOverlayType);

    /**
     * @brief	This signal gets emitted on RVC overlay direction change.
     * @param	int iOverlayDirection: clockwise / counter-clockwise direction
     * @return	void
     */
    void sigRvcOverlayDirection(int iOverlayDirection);

    /**
     * @brief	This signal gets emitted on RVC overlay angle change.
     * @param	double dOverlayAngle: RVC overlay angle
     * @return	void
     */
    void sigRvcOverlayAngle(double dOverlayAngle);

    /**
     * @brief	This signal gets emitted on Park assist proxy status is received true.
     * @param	void
     * @return	void
     */
    void sigParkAssistStatusToHMI();

    /**
     * @brief   This signal gets emitted on PDc presence status is changed.
     * @param   bPdcPresence : Pdc presence status.
     * @return  void.
     */
    void sigPdcPresence(bool bPdcPresence);

    /**
     * @brief Signal shall be broadcasted whenever Park assist service is unable to change/update PDC settings requested by HMI
     * @param bErrorStatus : true if pdc settings cannot be updated as bcm is not ready, else false.
     * @param iErrorId : holds the error Id
     */
    void sigPdcSettingsStatus(bool bErrorStatus, int iErrorId);

public:
    /**
    * @brief	This function is called from resource layer when pdc delay timer has updated.
    * @param	iPdcDelayTimer: pdc delay timer value.
    * @return	void.
    */
    void updateParkAssistDelayTimer(int iPdcDelayTimer);

    /**
    * @brief	This function is called from resource layer when pdc tone data has updated.
    * @param	iPdcRearTone: pdc rear tone value.
    * @return	void.
    */
    void updateParkAssistRearTone(int iPdcRearTone);

    /**
     * @brief	This function is called from resource layer when status of reverse gear is updated.
     * @param	bool bReverseGearStatus: status of reverse gear, engaged or dis-engaged
     * @param	bool bActivationStatus: true - show screen, false - hide screen
     * @return	void
     */
    void updateScreenPDC_RVCStatus(bool bReverseGearStatus, bool bActivationStatus);

    /**
     * @brief	This function is called from resource layer when park assist variant is updated
     * @param	int iParkAssistVariantType: Variant type, PDC, RVC or PDC+RVC
     * @return	void
     */
    void updateParkAssistVariantType(int iParkAssistVariantType);

    /**
     * @brief	This function is called from resource layer when PDC screen sensor info is updated
     * @param	int iPdcSensorState: Holds in which zone the obstacle is present
     * @return	void
     */
    void updatePdcScreenSensorState(int iPdcSensorState);

    /**
     * @brief	This function is called from resource layer when RVC screen sensor info is updated
     * @param	int iRvcSensorState: Holds in which zone the obstacle is present
     * @return	void
     */
    void updateRvcScreenSensorState(int iRvcSensorState);

    /**
     * @brief	This function is called from resource layer when PDC fault info is updated
     * @param	int iPdcFault: Holds the PDC fault index, based on which corresponding fault message gets displayed
     * @return	void
     */
    void updatePdcFault(int iPdcFault);

    /**
     * @brief	This function is called from resource layer when RVC fault info is updated
     * @param	int iRvcFault: Holds the RVC fault index, based on which corresponding fault message gets displayed
     * @return	void
     */
    void updateRvcFault(int iRvcFault);

    /**
     * @brief	This function is called from resource layer when PDC+RVC fault info is updated
     * @param	int iPdcRvcFault: Holds the PDC+RVC fault index, based on which corresponding fault message gets displayed
     * @return	void
     */
    void updatePdcRvcFault(int iPdcRvcFault);

    /**
     * @brief	This function is called from resource layer when RVC overlay type is updated
     * @param	int iRvcOverlayType: Current active overlay, Static / Dynamic
     * @return	void.
     */
    void updateRvcOverlayType(int iRvcOverlayType);

    /**
     * @brief	This function is called from resource layer when RVC overlay direction is updated
     * @param	int iOverlayDirection: clockwise / counter-clockwise direction
     * @return	void.
     */
    void updateRvcOverlayDirection(int iOverlayDirection);

    /**
     * @brief	This function is called from resource layer when RVC overlay angle is updated
     * @param	double dOverlayAngle: RVC overlay angle
     * @return	void.
     */
    void updateRvcOverlayAngle(double dOverlayAngle);

    /**
     * @brief	This function is called from resource layer when park assist proxy status is received true
     * @param	void.
     * @return	void.
     */
    void updateParkAssistStatusToHMI();

    /**
     * @brief   This function is called from resource layer when pdc presence value is received true
     * @param   bPdcPresence : Pdc presence status.
     * @return  void.
     */
    void updatePdcPresence(bool bPdcPresence);

    /**
     * @brief Method to be invoked to notify adaptor regarding error in update of PDC settings
     *        requested by HMI by Park assist service
     * @param bErrorStatus : holds the error status
     * @param iErrorId : holds the errorId
     * @return  void.
     */
    void updatePdcSettingsStatus(bool bErrorStatus, int iErrorId);
};

#endif // CPARKASSISTEVENTPROVIDER_H
