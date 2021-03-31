/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CParkAssistHandler.h
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * This class is to handle park assist settings and park assist events.
 */

#ifndef CPARKASSISTEVENTHANDLER_H
#define CPARKASSISTEVENTHANDLER_H

#include <QObject>
#include "CParkAssistAdaptor.h"

/**
 * @brief The CParkAssistEventHandler class: This class is to handle Park Assist events.
 *          Park Assist resource event provider will emit signals and those will be handled here.
 */
class CParkAssistEventHandler : public QObject
{
    Q_OBJECT
public:
    CParkAssistEventHandler(QObject* parent = 0);
    ~CParkAssistEventHandler();

public slots:
    /**
    * @brief	This function will update pdc tone volume received from Pdc Resource layer.
    * @param	iParkAssistDelayTimer: park assist delay timer from pdcProxyService.
    * @return	void
    */
    void sltUpdateParkAssistDelayTimer(int iParkAssistDelayTimer);

    /**
    * @brief	This function will update pdc tone volume received from Pdc Resource layer.
    * @param	iParkAssistRearTone: park assist rear tone from pdcProxyService.
    * @return	void
    */
    void sltUpdateParkAssistRearTone(int iParkAssistRearTone);

    /**
    * @brief	This function will update reverse gear received from resource layer.
    * @param	bool bReverseGearStatus: true - engaged/ false - dis-engaged
    * @param	bool bActivationStatus: true - show screen, false - hide screen
    * @return	void
    */
    void sltUpdateScreenPDC_RVCStatus(bool bReverseGearStatus, bool bActivationStatus);

   /**
    * @brief	This function will update park assist variant received from resource layer.
    * @param	int iParkAssistVariantType: PDC, RVC, PDC-RVC
    * @return	void
    */
   void sltParkAssistVariantType(int iParkAssistVariantType);

   /**
    * @brief	This function will update PDC screen sensor info. received from resource layer.
    * @param	int iPdcSensorState: Distance fro obstacle
    * @return	void
    */
   void sltPdcScreenSensorState(int iPdcSensorState);

   /**
    * @brief	This function will update RVC screen sensor info. received from resource layer.
    * @param	int iRvcSensorState: Distance fro obstacle
    * @return	void
    */
   void sltRvcScreenSensorState(int iRvcSensorState);

   /**
    * @brief	This function will update PDC fault info received from resource layer.
    * @param	int iPdcFault: PDC fault message index
    * @return	void
    */
   void sltPdcFault(int iPdcFault);

   /**
    * @brief	This function will update RVC fault info received from resource layer.
    * @param	int iRvcFault: RVC fault message index
    * @return	void
    */
   void sltRvcFault(int iRvcFault);

   /**
    * @brief	This function will update PDC+RVC fault info received from resource layer.
    * @param	int iPdcRvcFault: PDC+RVC fault message index
    * @return	void
    */
   void sltPdcRvcFault(int iPdcRvcFault);

   /**
    * @brief	This function will update RVC overlay type received from resource layer.
    * @param	int iRvcOverlayType: static / dynamic overlay
    * @return	void
    */
   void sltRvcOverlayType(int iRvcOverlayType);

   /**
    * @brief	This function will update RVC overlay direction received from resource layer.
    * @param	int iOverlayDirection: clockwise / counter-clockwise
    * @return	void
    */
   void sltRvcOverlayDirection(int iOverlayDirection);

   /**
    * @brief	This function will update RVC overlay angle received from resource layer.
    * @param	int dOverlayAngle: Based on this angle steering wheel direction is shown
    * @return	void
    */
   void sltRvcOverlayAngle(double dOverlayAngle);

   /**
    * @brief	This function will update park assist proxy status received true from resource layer.
    * @param	void
    * @return	void
    */
   void sltParkAssistStatusToHMI();

   /**
    * @brief    This function will update pdc presence status received changed from resource layer.
    * @param    bPdcPresence : bPdcPresence state from pdcProxyService.
    * @return   void
    */
   void sltPdcPresence(bool bPdcPresence);

   /**
    * @brief This function will update the error status on changing pdc settings.
    * @param bErrorStatus : true if pdc settings cannot be updated as bcm is not ready, else false.
    * @param iErrorId : holds the pdc settings error id.
    * @return   void.
    */
   void sltPdcSettingsStatus(bool bErrorStatus, int iErrorId);

private:
    /**
    * @brief	This function will connect signals and slots.
    * @param	void
    * @return	void
    */
    void connectSignals();

    /* Instance of class IParkAssistAdaptor */
    CParkAssistAdaptor* m_pParkAssistAdaptor;

};

#endif // CPARKASSISTEVENTHANDLER_H
