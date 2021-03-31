/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CDisplayManagerEventProvider.h
 * @ingroup       HMIComponent
 * @author        Vishal Chaudhary
 * @brief         This file contains CDisplayManagerEventProvider class that
 *                shall publish events whenever HMI DisplayManagerResource layer
 *                receive some response or callbacks from DisplayManagerResource
 *                proxy.
 */

#ifndef CDISPLAYMANAGEREVENTPROVIDER_H
#define CDISPLAYMANAGEREVENTPROVIDER_H

#include <QObject>

using namespace std;

/*!
 * @class CDisplayManagerDataEventProvider
 * @brief This class shall publish events whenever HMI DisplayManagerResource layer receive
 * some response or callbacks from BtResource proxy.
 */
class CDisplayManagerEventProvider: public QObject
{
    Q_OBJECT

public:
    CDisplayManagerEventProvider(QObject* pParent = 0);
    ~CDisplayManagerEventProvider();

signals:
    /******************************************************//**
     * @category SIGNALS
     * @brief Signals that shall be emitted to the application layer
     *******************************************************/

    /**
     * @brief   sigBrightnessLevelRespRecv: signal to update the
     *          setBrightnessLevelAsuncReq() response.
     * @param   void
     * @return  void
     */
    void sigBrightnessLevelRespRecv();

    /**
     * @brief   sigButtonPanelBrightnessLevelRespRecv: signal to update the
     *          setButtonPanelBrightnessLevelAsyncReq() response.
     * @param   void
     * @return  void
     */
    void sigButtonPanelBrightnessLevelRespRecv();

    /**
     * @brief   sigUpdateBrightnessLevel: signal to update the
     *          brightness level.
     * @param   iBrightnessLevel: brightness level.
     * @return  void
     */
    void sigUpdateBrightnessLevel(short iBrightnessLevel);

    /**
     * @brief   sigUpdateButtonPanelBrightnessLevel: signal to update the
     *          brightness level.
     * @param   iBrightnessLevel: brightness level.
     * @return  void
     */
    void sigUpdateButtonPanelBrightnessLevel(short iBrightnessLevel);

    /**
     * @brief   sigUpdateDisplayOnOffFeatureStatus: signal to update the
     *          display OnOff feature status.
     * @param   iDisplayOnOffFeatureStatus: DisplayOnOffFeatureStatus 1 if
     *          enabled, else 0.
     * @return  void
     */
    void sigUpdateDisplayOnOffFeatureStatus(qint32 iDisplayOnOffFeatureStatus);

    /**
     * @brief   sigUpdateNightModeStatus: signal to update the
     *          DayNight status.
     * @param   iNightModeStatus: night mode status 0 - disabled , 1 -
     *          enabled
     * @return  void
     */
    void sigUpdateNightModeStatus(qint32 iNightModeStatus);

public:
    /************************************************************************//**
     * @category    METHODS
     * @brief       Methods that would be used by the DisplayManagerResource
     * layer to indirectly emit signals to the DisplayManager application layer
     ************************************************************************/

    /**
     *  @brief   updateBrightnessLevelResponse: Method to update the response
     *          of setBrightnessLevelAsuncReq(), the value is used for debouncing
     *          logic.
     *  @param  void.
     *  @return void.
     */
    void updateBrightnessLevelResponse();

    /**
     *  @brief   updateButtonPanelBrightnessLevelResponse: Method to update the response
     *          of setButtonPanelBrightnessLevelAsyncReq(), the value is used for debouncing
     *          logic.
     *  @param  void.
     *  @return void.
     */
    void updateButtonPanelBrightnessLevelResponse();

    /**
     *  @brief   updateBrightnessLevel: Method to update the brightness level.
     *  @param   iBrightnessLevel: Brightness level.
     *  @return  void.
     */
    void updateBrightnessLevel(short iBrightnessLevel);

    /**
     *  @brief   updateButtonPanelBrightnessLevel: Method to update the brightness level.
     *  @param   iBrightnessLevel: Brightness level.
     *  @return  void.
     */
    void updateButtonPanelBrightnessLevel(short iBrightnessLevel);

    /**
     *  @brief   updateDisplayOnOffFeatureStatus: Method to update the display
     *           on/off feature status.
     *  @param   iDisplayOnOffFeatureStatus: Display on/off feature status 1 if
     *           enabled, else 0.
     *  @return  void.
     */
    void updateDisplayOnOffFeatureStatus(qint32 iDisplayOnOffFeatureStatus);

    /**
     *  @brief   updateNightModeStatus: Method to update the NightMode
     *           status.
     *  @param   iNightModeStatus: night mode status 0 - disabled , 1 -
     *           enabled
     *  @return  void.
     */
    void updateNightModeStatus(qint32 iNightModeStatus);

};

#endif // CDISPLAYMANAGEREVENTPROVIDER_H
