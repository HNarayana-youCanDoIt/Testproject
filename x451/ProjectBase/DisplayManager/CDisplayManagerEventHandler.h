/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CDisplayManagerEventHandler.h
 * @ingroup       HMIComponent
 * @author        Vishal Chaudhary
 * @brief         This file contains CDisplayManagerEventHandler class that
 * implements the slot for the signals emited by Display Manager resource layer
 * to inform Display Manager adaptor regarding the updates in Display Manager
 * resource layer.
 */

#ifndef CDISPLAYMANAGEREVENTHANDLER_H
#define CDISPLAYMANAGEREVENTHANDLER_H

#include <QObject>

/*!
 * @class CDisplayManagerEventHandler
 * @brief This class implements the slot for the signals emited by phone resource
 * layer to inform Display Manager adaptor regarding the updates in Display
 * Manager resource layer.
 */
class CDisplayManagerEventHandler: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief CDisplayManagerEventHandler: Constructor
     * @param pParent: Parent object pointer.
     */
    CDisplayManagerEventHandler(QObject* pParent = 0);

    ~CDisplayManagerEventHandler();

private slots:
    /******************************************************//**
     * @category    DISPLAY MANAGER SLOTS
     * @brief       Slots for the signals emitted by Display Manager resource
     *******************************************************/

    /**
      * @brief sltBrightnessLevelRespRecv: Slot function for signal
      * sigBrightnessLevelRespRecv of CDisplayManagerEventProvider.
      */
     void sltBrightnessLevelRespRecv();

     /**
       * @brief sltButtonPanelBrightnessLevelRespRecv: Slot function for signal
       * sigButtonPanelBrightnessLevelRespRecv of CDisplayManagerEventProvider.
       */
      void sltButtonPanelBrightnessLevelRespRecv();

     /**
      * @brief sltUpdateBrightnessLevel: Slot function for signal
      * sigUpdateBrightnessLevel of CDisplayManagerEventProvider.
      * @param iBrightnessLevel: bright ness level
      */
     void sltUpdateBrightnessLevel(short iBrightnessLevel);

     /**
      * @brief sltUpdateButtonPanelBrightnessLevel: Slot function for signal
      * sigUpdateButtonPanelBrightnessLevel of CDisplayManagerEventProvider.
      * @param iBrightnessLevel: bright ness level
      */
     void sltUpdateButtonPanelBrightnessLevel(short iBrightnessLevel);

     /**
      * @brief sltUpdateDisplayOnOffFeatureStatus: Slot function for signal
      *        sigUpdateDisplayOnOffFeatureStatus of CDisplayManagerEventProvider.
      * @param iDisplayOnOffFeatureStatus: DisplayOnOffFeatureStatus 1
      *        if enabled, else 0.
      */
     void sltUpdateDisplayOnOffFeatureStatus(qint32 iDisplayOnOffFeatureStatus);

     /**
      * @brief sltUpdateDisplayStatus: Slot function for signal
      *         sigUpdateNightModeStatus of CDisplayManagerEventProvider.
      * @param iNightModeStatus: night mode status 0 - disabled , 1 -
     *         enabled
      */
     void sltUpdateNightModeStatus(qint32 iNightModeStatus);

private:
    /******************************************************//**
     * @category    INTERNAL METHODS
     *******************************************************/

    /*!
     * @brief   Method to connect signals provided by
     *          CDisplayManagerManagerEventProvider class
     *          with the internal slots.
     * @param   void.
     * @return  void.
     */
    void connectDisplayManagerSignals();

    /*!
     * @brief   Method to disconnect signals provided by
     *          CDisplayManagerManagerEventProvider class
     *          with the internal slots.
     * @param   void.
     * @return  void.
     */
    void disconnectDisplayManagerSignals();
};

#endif // CDISPLAYMANAGEREVENTHANDLER_H
