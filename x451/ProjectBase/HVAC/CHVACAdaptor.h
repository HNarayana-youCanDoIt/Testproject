/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CHVACAdaptor.h
 * @ingroup         HMIComponent
 * @author          Mohit Rajani
 * CHVACAdaptor, an Adaptor for HVAC module,
 * CHVACAdaptor used to communicate between QML and Resource Layer.
 */

#ifndef CHVACADAPTOR_H
#define CHVACADAPTOR_H

#include <QObject>
#include "CHVACEnums.h"
#include <v0/com/harman/dcif/CcmPresTypes.hpp>
#include "implementations/CHVACData.h"

using namespace v0::com::harman::dcif;

class IHVACResource;

/**
 * @brief The CHVACAdaptor, an Adaptor for HVAC module,
 * CHVACAdaptor used to communicate between QML and Resource Layer.
 */
class CHVACAdaptor : public QObject
{
    Q_OBJECT

    //Properties
    /** AC mode on/off */
    Q_PROPERTY(quint16 acMode READ acMode WRITE setAcMode NOTIFY sigAcModeChanged)

    //! Xpress cool mode status
    Q_PROPERTY(bool xpressCoolMode READ xpressCoolMode NOTIFY sigXpressCoolModeChanged)

    /** Eco AC mode on/off */
    Q_PROPERTY(quint16 ecoAcMode READ ecoAcMode WRITE setEcoAcMode NOTIFY sigEcoAcModeChanged)

    /** Auto mode on/off */
    Q_PROPERTY(quint16 autoMode READ autoMode WRITE setAutoMode NOTIFY sigAutoModeChanged)

    /** control panel (Climate) on/off */
    Q_PROPERTY(quint16 ctrlPanelMode READ ctrlPanelMode WRITE setCtrlPanelMode NOTIFY sigCtrlPanelModeChanged)

    /** Max defrost on/off */
    Q_PROPERTY(quint16 maxDefrostMode READ maxDefrostMode WRITE setMaxDefrostMode NOTIFY sigMaxDefrostModeChanged)

    /** fresh air recirculation mode (0:Recirculation_ON, 2:Fresh_Air_ON) */
    Q_PROPERTY(CHVACEnums::EHVACAirCirculationModes airCirculationMode READ airCirculationMode WRITE setAirCirculationMode NOTIFY sigAirCirculationModeChanged)

    /** Distribution modes (1~5) */
    Q_PROPERTY(CHVACEnums::EHVACDistributionMode distributionMode READ distributionMode WRITE setDistributionMode NOTIFY sigDistributionModeChanged)

    /** fan speed (0~7) */
    Q_PROPERTY(quint16 fanSpeed READ fanSpeed WRITE setFanSpeed NOTIFY sigFanSpeedChanged)

    /** Dual Mode ON/OFF */
    Q_PROPERTY(bool dualMode READ dualMode WRITE setDualMode NOTIFY sigDualModeChanged)

    /** Temp (160~300) */
    Q_PROPERTY(float temperature READ temperature WRITE setTemperature NOTIFY sigTemperatureChanged)

    /** rear defog ON/OFF */
    Q_PROPERTY(quint16 rearDefog READ rearDefog WRITE setRearDefog NOTIFY sigRearDefogChanged)

    /** config : fan low speed limit (0~7) */
    Q_PROPERTY(quint16 fanSpeedLowLimit READ fanSpeedLowLimit NOTIFY sigFanSpeedLowLimitChanged)

    /** config : fan High speed limit (0~7) */
    Q_PROPERTY(quint16 fanSpeedHighLimit READ fanSpeedHighLimit NOTIFY sigFanSpeedHighLimitChanged)

    /** config : Temperature low limit */
    Q_PROPERTY(float temperatureLowLimit READ temperatureLowLimit NOTIFY sigTemperatureLowLimitChanged)

    /** config : Temperature high limit */
    Q_PROPERTY(float temperatureHighLimit READ temperatureHighLimit NOTIFY sigTemperatureHighLimitChanged)

    /** error status set/Unset */
    Q_PROPERTY(quint16 errorStatus READ errorStatus WRITE setErrorStatus NOTIFY sigErrorStatusChanged)

    /** CCM presence status */
    Q_PROPERTY(CHVACEnums::EHVACCCMPresence ccmPresence READ ccmPresence NOTIFY sigCCMPresenceChanged)
    
    /** property to hold hvac zone type */
    Q_PROPERTY(CHVACEnums::EHVACZoneType zoneType READ zoneType NOTIFY sigZoneTypeUpdated)

    /** property to hold hvac container type */
    Q_PROPERTY(CHVACEnums::EHVACContainerType hvacContainerType READ hvacContainerType NOTIFY sigHVACContainerTypeUpdated)
    
    /** property to hold air flow presence status */
    Q_PROPERTY(bool airFlowPresence READ airFlowPresence NOTIFY sigAirFlowPresenceUpdated)
    
    /** property to hold ac presence status */
    Q_PROPERTY(bool acPresence READ acPresence NOTIFY sigACPresenceUpdated)
    
    /** property to hold econ presence status */
    Q_PROPERTY(bool econPresence READ econPresence NOTIFY sigEconPresenceUpdated)
    
    /** property to hold temperature presence status */
    Q_PROPERTY(bool temperaturePresence READ temperaturePresence NOTIFY sigTemperaturePresenceUpdated)
    
    /** property to hold auto presence status */
    Q_PROPERTY(bool autoPresence READ autoPresence NOTIFY sigAutoPresenceUpdated)
    
    /** property to hold fan presence status */
    Q_PROPERTY(bool fanPresence READ fanPresence NOTIFY sigFanPresenceUpdated)
    
    /** property to hold fresh air presence status */
    Q_PROPERTY(bool freshAirPresence READ freshAirPresence NOTIFY sigFreshAirPresenceUpdated)
    
    /** property to hold xpress cooling presence status */
    Q_PROPERTY(bool xpressCoolingPresence READ xpressCoolingPresence NOTIFY sigXpressCoolingPresenceUpdated)

    /** property to hold defrost presence status */
    Q_PROPERTY(bool defrostPresence READ defrostPresence NOTIFY sigDefrostPresenceUpdated)

    /** property to hold passenger temperature */
    Q_PROPERTY(float passengerTemperature READ passengerTemperature NOTIFY sigPassengerTempChanged())

    /** property to hold driver temperature */
    Q_PROPERTY(float driverTemperature READ driverTemperature NOTIFY sigDriverTempChanged())

public:
    /**
     * @brief getInstance, provides the instance of the HVAC adaptor
     * @return CHVACAdaptor, HVAC adaptor object
     */
    static CHVACAdaptor* getInstance();

    /**
     * @brief destructor
     * param void
     * return void
     */
    ~CHVACAdaptor();

    /**
     * @brief setHVACParameter function called to the HVAC parameter values received from the lower layer
     * @param eHVACParam - the HVAC parameter enumeration that needs to be set
     * @param uiValue - value of the HVAC parameter that needs to be set
     * @return void
     */
    Q_INVOKABLE void setHVACParameter(CHVACEnums::EHVACParamEnums eHVACParam, quint16 uiValue);

    /**
     * @brief toggleAcMode function to toggle ac mode between on and off
     * @param void
     * @return void
     */
    Q_INVOKABLE void toggleAcMode();

    /**
     * @brief   invToggleXpressCoolMode: Method to toggle Xpress cool mode
     *          between on and off.
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void invToggleXpressCoolMode();

    /**
     * @brief   invToggleDualMode: Method to toggle Sync mode between on and off.
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void invToggleDualMode();

    /**
     * @brief   invDecreasePassengerTmp: Method to decrease the passenger temperature
     *          by the predefined step size (5).
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void invDecreasePassengerTmp();

    /**
     * @brief   invIncreasePassengerTmp: Method to increase the passenger temperature
     *          by the predefined step size (5).
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void invIncreasePassengerTmp();

    /**
     * @brief   invDecreaseDriverTmp: Method to decrease the driver temperature
     *          by the predefined step size (5).
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void invDecreaseDriverTmp();

    /**
     * @brief   invIncreaseDriverTmp: Method to increase the driver temperature
     *          by the predefined step size (5).
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void invIncreaseDriverTmp();

    /**
     * @brief toggleEcoAcMode function to toggle eco ac mode between on and off
     * @param void
     * @return void
     */
    Q_INVOKABLE void toggleEcoAcMode();

    /**
     * @brief decreaseTemperature method to decrease the temperature by the predefined step size (5)
     * @param void
     * @return void
     */
    Q_INVOKABLE void decreaseTemperature();

    /**
     * @brief increaseTemperature method to increase the temperature by the predefined step size (5)
     * @param void
     * @return void
     */
    Q_INVOKABLE void increaseTemperature();

    /**
     * @brief decreaseFanSpeed method to decrease the fan speed by the predefined step size (1)
     * @param void
     * @return void
     */
    Q_INVOKABLE void decreaseFanSpeed();

    /**
     * @brief increaseFanSpeed method to increase the fan speed by the predefined step size (1)
     * @param void
     * @return void
     */
    Q_INVOKABLE void increaseFanSpeed();

    /**
     * @brief increaseDistributionMode Change Air Vent Mode in the folowing sequence:
     * 1. Chest Mode 2. Chest+Leg Mode 3. Leg Mode
     * 4. Leg +Defrost Mode 5. Defrost Mode
     * and then Loop back to Chest Mode
     * @param void
     * @return void
     */
    Q_INVOKABLE void increaseDistributionMode();

    /**
     * @brief   invGetFanSpeedImage: Method to get fan speed image from the list as per the fan speed received.
     * @param   uiFanSpeed: current fan speed.
     * @return  Fan speed image as per the fan speed.
     */
    Q_INVOKABLE QString invGetFanSpeedImage(quint16 uiFanSpeed);

    /**
     * @brief toggleAirCirculationMode function to toggle air circulation mode between
     * (0:Recirculation_ON, 2:Fresh_Air_ON)
     */
    Q_INVOKABLE void toggleAirCirculationMode();

    /**
     * @brief   updateHVACContainerType: Method to update the hvac container based upon the
     *          zone and xpress cooling info.
     * @param   void.
     * @return  void.
     */
    void updateHVACContainerType();

    // All the HVAC property setters and getters

    /**
     * @brief acMode method to get the value of AC mode
     * @param void
     * @return current AC mode
     */
    quint16 acMode(){return m_uiACMode;}

    /**
     * @brief setAcMode setter for the AC mode property
     * @param acMode value that needs to be set
     * @return void
     */
    void setAcMode(quint16 uiAcMode);

    /**
     * @brief   xpressCoolMode: Method to get xpress cool mode status(ON/OFF).
     * @param   void.
     * @return  xpress cool mode status(ON/OFF).
     */
    bool xpressCoolMode(){ return m_bXpressCoolMode; }

    /**
     * @brief   setXpressCoolMode: Method to update xpress cool
     *          mode status received from service.
     * @param   bXpressCoolMode: Xpress cool mode whether ON/OFF
     * @return  void.
     */
    void setXpressCoolMode(bool bXpressCoolMode);

    /**
     * @brief ecoAcMode method to get the value of Eco AC mode
     * @param void
     * @return current Eco AC mode
     */
    quint16 ecoAcMode(){return m_uiEcoACMode;}

    /**
     * @brief setEcoAcMode setter for eco AC mode property
     * @param ecoAcMode value that needs to be set
     * @return void
     */
    void setEcoAcMode(quint16 uiEcoAcMode);

    /**
     * @brief autoMode method to get the value of auto mode
     * @param void
     * @return current auto mode
     */
    quint16 autoMode(){return m_uiAutoMode;}

    /**
     * @brief setAutoMode setter for auto mode property
     * @param autoMode value that needs to be set
     * @return void
     */
    void setAutoMode(quint16 uiAutoMode);

    /**
     * @brief ctrlPanelMode method to get the value of control panel mode (HVAC is on or off)
     * @param void
     * @return current control panel mode
     */
    quint16 ctrlPanelMode(){return m_uiCtrlPanelMode;}

    /**
     * @brief setCtrlPanelMode setter for control panel property
     * @param ctrlPanelMode value that needs to be set
     * @return void
     */
    void setCtrlPanelMode(quint16 uiCtrlPanelMode);

    /**
     * @brief maxDefrostMode method to get the value of max defrost mode
     * @param void
     * @return current max defrost mode
     */
    quint16 maxDefrostMode(){return m_uiMaxDefrostMode;}

    /**
     * @brief setMaxDefrostMode setter for max defrost mode property
     * @param maxDefrostMode value that needs to be set
     * @return void
     */
    void setMaxDefrostMode(quint16 uiMaxDefrostMode);

    /**
     * @brief airCirculationMode method to get the value of air circulation mode
     * @param void
     * @return current air circulation mode
     */
    CHVACEnums::EHVACAirCirculationModes airCirculationMode(){return m_eAirRecirculationMode;}


    /**
     * @brief setAirCirculationMode setter for air circulation mode property
     * @param airCirculationMode value that needs to be set
     * @return
     */
    void setAirCirculationMode(quint16 uiAirCirculationMode);

    /**
     * @brief distributionMode method to get the value of distribution mode
     * @param void
     * @return current distribution mode
     */
    CHVACEnums::EHVACDistributionMode distributionMode(){return m_eDistributionMode;}

    /**
     * @brief setDistributionMode setter for distribution mode property
     * @param distributionMode value that needs to be set
     * @return void
     */
    void setDistributionMode(quint16 uiDistributionMode);

    /**
     * @brief fanSpeed method of get the value of fan speed
     * @param void
     * @return current fan speed
     */
    quint16 fanSpeed(){return m_uiFanSpeed;}

    /**
     * @brief setFanSpeed setter for fan speed property
     * @param fanSpeed value that needs to be set
     * @return void
     */
    void setFanSpeed(quint16 uiFanSpeed);

    /**
     * @brief   dualMode: Method to get the dual mode status whether ON/OFF.
     * @param   void.
     * @return  Dual mode status whether ON/OFF.
     */
    bool dualMode(){return m_bDualMode;}

    /**
     * @brief   setDualMode: Method to set the dual mode status received from CCM service.
     * @param   bDualMode: Dual mode status whether ON/OFF.
     * @return  void.
     */
    void setDualMode(bool bDualMode);

    /**
     * @brief temperature method to get the value of temperature
     * @param void
     * @return current temperature
     */
    float temperature(){return m_fTemperature;}

    /**
     * @brief setTemperature setter for temperature property
     * @param temperature value that needs to be set
     * @return void
     */
    void setTemperature(float fTemperature);

    /**
     * @brief setTemperatureValue method called from the below layer to set temperature
     * @param void
     * @param temperature value that needs to be set
     */
    void setTemperatureValue(quint16 uiTemperature);

    /**
     * @brief rearDefog method to get the value for rear defog
     * @param void
     * @return current rear defog value
     */
    quint16 rearDefog(){return m_uiRearDefog;}

    /**
     * @brief setRearDefog setter for rear defog property
     * @param rearDefog value that needs to be set
     * @return void
     */
    void setRearDefog(quint16 uiRearDefog);

    /**
     * @brief fanSpeedLowLimit method to get fan speed lower limit
     * @param void
     * @return current lower limit for fan speed
     */
    quint16 fanSpeedLowLimit(){return m_uiFanSpeedLowLimit;}

    /**
     * @brief setFanSpeedLowLimit setter for fan speed low limit property
     * @param fanSpeedLowLimit value that needs to be set
     * @return void
     */
    void setFanSpeedLowLimit(quint16 uiFanSpeedLowLimit);

    /**
     * @brief fanSpeedHighLimit method to get fan speed upper limit
     * @param void
     * @return current high limit for fan speed
     */
    quint16 fanSpeedHighLimit(){return m_uiFanSpeedHighLimit;}

    /**
     * @brief setFanSpeedHighLimit setter for fan speed high limit property
     * @param fanSpeedHighLimit value that needs to be set
     * @return void
     */
    void setFanSpeedHighLimit(quint16 uiFanSpeedHighLimit);

    /**
     * @brief temperatureLowLimit method to get temperature lower limit
     * @param void
     * @return current lower limit for temperature
     */
    float temperatureLowLimit(){return m_fTemperatureLowLimit;}

    /**
     * @brief setTemepratureLowLimit setter for temperature low limit property
     * @param temperatureLowLimit value that needs to be set
     * @return void
     */
    void setTemepratureLowLimit(quint16 uiTemperatureLowLimit);

    /**
     * @brief temperatureHighLimit method to get temperature high limit
     * @param void
     * @return current high limit for temperature
     */
    float temperatureHighLimit(){return m_fTemperatureHighLimit;}

    /**
     * @brief setTemepratureHighLimit setter for temperature high limit property
     * @param temperatureHighLimit value that needs to be set
     * @return void
     */
    void setTemepratureHighLimit(quint16 uiTemperatureHighLimit);

    /**
     * @brief errorStatus method to get the value for error status
     * @param void
     * @return current error status value
     */
    quint16 errorStatus(){return m_uiErrorStatus;}

    /**
     * @brief setErrorStatus setter for error status property
     * @param errorStatus value that needs to be set
     * @return void
     */
    void setErrorStatus(quint16 uiErrorStatus);

    /**
    * @brief	fetchHVACvalues This method will fetch HVAC info from HVAC resource implementation.
    * @param	void
    * @return	void
    */
    void fetchHVACvalues();

    /**
     * @brief   ccmPresenceUpdate: Method to called from CHVACEventHandler when ccm Presence param is updated
     *                           If value of uiCCMPresenceStatus is 0, then HMI calls an API to get all HVAC parameters.
     * @param   uiCCMPresenceStatus: CCM presence status
     * @return  void
     */
    void setCCMPresenceStatus(quint16 uiCCMPresenceStatus);

    /**
    * @brief	setHvacZoneType: Method to be invoked to set the zone type whether single zone or dual zone.
    * @param	eZoneType: Single zone or Dual zone.
    * @return	void
    */
    void setHvacZoneType(CHVACEnums::EHVACZoneType eZoneType);

    /**
    * @brief	setAirFlowPresenceStatus: Method to be invoked to set the presence status of Air flow feature.
    * @param	bPresenceStatus: True if the feature is present, FALSE otherwise.
    * @return	void
    */
    void setAirFlowPresenceStatus(bool bPresenceStatus);

    /**
    * @brief	setACPresenceStatus: Method to be invoked to set the presence status of AC feature.
    * @param	bPresenceStatus: True if the feature is present, FALSE otherwise.
    * @return	void
    */
    void setACPresenceStatus(bool bPresenceStatus);

    /**
    * @brief	setEconPresenceStatus: Method to be invoked to set the presence status of ECON feature.
    * @param	bPresenceStatus: True if the feature is present, FALSE otherwise.
    * @return	void
    */
    void setEconPresenceStatus(bool bPresenceStatus);

    /**
    * @brief	setTemperaturePresnceStatus: Method to be invoked to set the presence status of Temperature feature.
    * @param	bPresenceStatus: True if the feature is present, FALSE otherwise.
    * @return	void
    */
    void setTemperaturePresnceStatus(bool bPresenceStatus);

    /**
    * @brief	setAutoPresenceStatus: Method to be invoked to set the presence status of Auto feature.
    * @param	bPresenceStatus: True if the feature is present, FALSE otherwise.
    * @return	void
    */
    void setAutoPresenceStatus(bool bPresenceStatus);

    /**
    * @brief	setAutoPresenceStatus: Method to be invoked to set the presence status of Fan feature.
    * @param	bPresenceStatus: True if the feature is present, FALSE otherwise.
    * @return	void
    */
    void setFanPresenceStatus(bool bPresenceStatus);

    /**
    * @brief	setFreshAirPresenceStatus: Method to be invoked to set the presence status of Fresh Air feature.
    * @param	bPresenceStatus: True if the feature is present, FALSE otherwise.
    * @return	void
    */
    void setFreshAirPresenceStatus(bool bPresenceStatus);

    /**
    * @brief	setXpressCoolingPresenceStatus: Method to be invoked to set the presence status of Xpress Cooling feature.
    * @param	bPresenceStatus: True if the feature is present, FALSE otherwise.
    * @return	void
    */
    void setXpressCoolingPresenceStatus(bool bPresenceStatus);

    /**
    * @brief	setDefrostPresenceStatus: Method to be invoked to set the presence status of Defrost feature.
    * @param	bPresenceStatus: True if the feature is present, FALSE otherwise.
    * @return	void
    */
    void setDefrostPresenceStatus(bool bPresenceStatus);

    /**
     * @brief  ccmPresence: Method to get the status of CCM presence.
     * @param  void.
     * @return CHVACEnums::EHVACCCMPresence: CCM presence status.
     */
    CHVACEnums::EHVACCCMPresence ccmPresence();

    /**
     * @brief  zoneType: Method to get the hvac zone type.
     * @param  void.
     * @return type of zone, single or dual.
     */
    CHVACEnums::EHVACZoneType zoneType();

    /**
     * @brief  hvacContainerType: Method to get the hvac container type.
     * @param  void.
     * @return type of container, single or single with xpress cooling or dual.
     */
    CHVACEnums::EHVACContainerType hvacContainerType();

    /**
     * @brief  airFlowPresence: Method to get the status of air flow presence.
     * @param  void.
     * @return TRUE if the feature is present, FALSE otherwise.
     */
    bool airFlowPresence();

    /**
     * @brief  acPresence: Method to get the status of ac presence.
     * @param  void.
     * @return TRUE if the feature is present, FALSE otherwise.
     */
    bool acPresence();

    /**
     * @brief  econPresence: Method to get the status of econ presence.
     * @param  void.
     * @return TRUE if the feature is present, FALSE otherwise.
     */
    bool econPresence();

    /**
     * @brief  temperaturePresence: Method to get the status of temperature presence.
     * @param  void.
     * @return TRUE if the feature is present, FALSE otherwise.
     */
    bool temperaturePresence();

    /**
     * @brief  autoPresence: Method to get the status of auto presence.
     * @param  void.
     * @return TRUE if the feature is present, FALSE otherwise.
     */
    bool autoPresence();

    /**
     * @brief  fanPresence: Method to get the status of fan presence.
     * @param  void.
     * @return TRUE if the feature is present, FALSE otherwise.
     */
    bool fanPresence();

    /**
     * @brief  freshAirPresence: Method to get the status of fresh air presence.
     * @param  void.
     * @return TRUE if the feature is present, FALSE otherwise.
     */
    bool freshAirPresence();

    /**
     * @brief  xpressCoolingPresence: Method to get the status of xpress cooling presence.
     * @param  void.
     * @return TRUE if the feature is present, FALSE otherwise.
     */
    bool xpressCoolingPresence();

    /**
     * @brief  defrostPresence: Method to get the status of defrost presence.
     * @param  void.
     * @return TRUE if the feature is present, FALSE otherwise.
     */
    bool defrostPresence();

    /**
     * @brief setCCMPresence:  Setter for the CCM presence property.
     * @param CHVACEnums::EHVACCCMPresence eCCMPresence: CCM presence value that needs to be set.
     * @return void.
     */
    void setCCMPresence(CHVACEnums::EHVACCCMPresence eCCMPresence);

    /**
     * @brief   ccmUserInterventionParamChanged: Method to be invoked when CCM parameter is changed through
     *          user intervention to upper layer.
     * @param   iHuCcmParam: The CCM parameter which has been changed.
     * @return  void.
     */
    void ccmUserInterventionParamChanged(int iHuCcmParam);

    /**
     * @brief   passengerTemperature: Method to get the passenger temperature value.
     * @param   void.
     * @return  Passenger temperature value.
     */
    float passengerTemperature() { return m_fPassengerTemperature; }

    /**
     * @brief   setPassengerTemperature: Method to set the passenger temperature value.
     * @param   iPassengerTemp: Passenger temperature value to be updated.
     * @return  void.
     */
    void setPassengerTemperature (int iPassengerTemp);

    /**
     * @brief   driverTemprature: Method to get the driver temperature value.
     * @param   void.
     * @return  Driver temperature value.
     */
    float driverTemperature() { return m_fDriverTemperature; }

    /**
     * @brief   setDriverTemperature: Method to set the driver temperature value.
     * @param   iDriverTemp: Driver temperature value to be updated.
     * @return  void.
     */
    void setDriverTemperature (int iDriverTemp);

signals:

    /**
     * @brief sigAcModeChanged signal emitted whenever ac mode updated
     * @param void
     * @return void
     */
    void sigAcModeChanged();

    /**
     * @brief   sigXpressCoolModeChanged: signal emitted whenever Xpress cool
     *          mode is updated.
     * @param   void.
     * @return  void.
     */
    void sigXpressCoolModeChanged();

    /**
     * @brief sigEcoAcModeChanged signal emitted whenever eco ac mode updated
     * @param void
     * @return void
     */
    void sigEcoAcModeChanged();

    /**
     * @brief sigAutoModeChanged signal emitted whenever auto mode updated
     * @param void
     * @return void
     */
    void sigAutoModeChanged();

    /**
     * @brief sigCtrlPanelModeChanged signal emitted whenever control panel mode updated
     * @param void
     * @return void
     */
    void sigCtrlPanelModeChanged();

    /**
     * @brief sigMaxDefrostModeChanged signal emitted whenever max defrost mode updated
     * @param void
     * @return void
     */
    void sigMaxDefrostModeChanged();

    /**
     * @brief sigAirCirculationModeChanged signal emitted whenever air circulation mode updated
     * @param void
     * @return void
     */
    void sigAirCirculationModeChanged();

    /**
     * @brief sigDistributionModeChanged signal emitted whenever distribution mode updated
     * @param void
     * @return void
     */
    void sigDistributionModeChanged();

    /**
     * @brief sigFanSpeedChanged signal emitted whenever fan speed updated
     * @param void
     * @return void
     */
    void sigFanSpeedChanged();

    /**
     * @brief sigDualModeChanged signal emitted whenever dual mode updated
     * @param void
     * @return void
     */
    void sigDualModeChanged();

    /**
     * @brief sigTemperatureChanged signal emitted whenever temperature updated
     * @param void
     * @return void
     */
    void sigTemperatureChanged();

    /**
     * @brief sigRearDefogChanged signal emitted whenever rear defog updated
     * @param void
     * @return void
     */
    void sigRearDefogChanged();

    /**
     * @brief sigFanSpeedLowLimitChanged signal emitted whenever fan speed low limit updated
     * @param void
     * @return void
     */
    void sigFanSpeedLowLimitChanged();

    /**
     * @brief sigFanSpeedHighLimitChanged signal emitted whenever fan speed high limit updated
     * @param void
     * @return void
     */
    void sigFanSpeedHighLimitChanged();

    /**
     * @brief sigTemperatureLowLimitChanged signal emitted whenever temperature low limit updated
     * @param void
     * @return void
     */
    void sigTemperatureLowLimitChanged();

    /**
     * @brief sigTemperatureHighLimitChanged signal emitted whenever temperature high limit updated
     * @param void
     * @return void
     */
    void sigTemperatureHighLimitChanged();

    /**
     * @brief sigErrorStatusChanged signal emitted whenever error status updated
     * @param void
     * @return void
     */
    void sigErrorStatusChanged();

    /**
     * @brief  sigCCMPresenceChanged: This signal gets emitted on CCM presence status update.
     * @param  void:
     * @return void:
     */
    void sigCCMPresenceChanged();

    /**
     * @brief  sigZoneTypeUpdated: This signal gets emitted on HVAC Zone type update.
     * @param  void.
     * @return void.
     */
    void sigZoneTypeUpdated();

    /**
     * @brief  sigHVACContainerTypeUpdated: This signal gets emitted on HVAC container type update.
     * @param  void.
     * @return void.
     */
    void sigHVACContainerTypeUpdated();

    /**
     * @brief  sigAirFlowPresenceUpdated: This signal gets emitted on Air Flow presence update.
     * @param  void.
     * @return void.
     */
    void sigAirFlowPresenceUpdated();

    /**
     * @brief  sigACPresenceUpdated: This signal gets emitted on AC presence update.
     * @param  void.
     * @return void.
     */
    void sigACPresenceUpdated();

    /**
     * @brief  sigEconPresenceUpdated: This signal gets emitted on Econ presence update.
     * @param  void.
     * @return void.
     */
    void sigEconPresenceUpdated();

    /**
     * @brief  sigTemperaturePresenceUpdated: This signal gets emitted on Temperature presence update.
     * @param  void.
     * @return void.
     */
    void sigTemperaturePresenceUpdated();

    /**
     * @brief  sigAutoPresenceUpdated: This signal gets emitted on Auto presence update.
     * @param  void.
     * @return void.
     */
    void sigAutoPresenceUpdated();

    /**
     * @brief  sigFanPresenceUpdated: This signal gets emitted on Fan presence update.
     * @param  void.
     * @return void.
     */
    void sigFanPresenceUpdated();

    /**
     * @brief  sigFreshAirPresenceUpdated: This signal gets emitted on Fresh Air presence update.
     * @param  void.
     * @return void.
     */
    void sigFreshAirPresenceUpdated();

    /**
     * @brief  sigXpressCoolingPresenceUpdated: This signal gets emitted on Xpress Cooling presence update.
     * @param  void.
     * @return void.
     */
    void sigXpressCoolingPresenceUpdated();

    /**
     * @brief  sigDefrostPresenceUpdated: This signal gets emitted on defrost presence update.
     * @param  void.
     * @return void.
     */
    void sigDefrostPresenceUpdated();

    /**
     * @brief   sigCcmUserInterventionParamChanged: Signal to notify about CCM parameter is changed through user
     *          intervention.
     * @param   iHuCcmParam: The CCM parameter which has been changed.
     * @return  void.
     */
    void sigCcmUserInterventionParamChanged(int iHuCcmParam);

    /**
     * @brief   sigPassengerTempChanged: Signal to notify about passenger temprature change.
     * @param   void.
     * @return  void.
     */
    void sigPassengerTempChanged();

    /**
     * @brief   sigDriverTempChanged: Signal to notify about driver temprature change.
     * @param   void.
     * @return  void.
     */
    void sigDriverTempChanged();

private:
    /**
     * @brief CHVACAdaptor constructor
     * @param parent parent object instance
     * @return void
     */
    explicit CHVACAdaptor(QObject *parent = nullptr);

    /**
     * @brief callToResourceLayer wrapper function to call resource layer to set HVAC parameters is provided values
     * @param eParameterEnum HVAC parameter that needs to be set/updated at resource layer
     * @param uiValue the value that needs to be set for that HVAC parameter
     * @return void
     */
    void callToResourceLayer(CHVACEnums::EHVACParamEnums eParameterEnum, quint16 uiValue);

    /**
     * @brief getTemperatureVal: Generic function which returns the calculated temperature as per the temprature received from CCM service.
     * @param iTemperature: Temperature received from CCM service that needs to be modified.
     * @return Modified temperature value for the given temp value
     */
    float getTemperatureVal(int iTemperature);

    /**
     * @brief   insertFanSpeedImages: Internal method to insert fan speed images in the list.
     * @param   void.
     * @return  void.
     */
    void insertFanSpeedImages();

    static CHVACAdaptor* m_pHVACAdaptor;

    /** Instance of HVAC resource */
    IHVACResource* m_pHVACResource;

    // HVAC parameters member variables
    /** AC mode on/off */
    quint16 m_uiACMode;

    //! Variable to hold Xpress cool mode status(ON/OFF)
    bool m_bXpressCoolMode;

    /** Eco AC mode on/off */
    quint16 m_uiEcoACMode;

    /** Auto mode on/off */
    quint16 m_uiAutoMode;

    /** control panel (Climate) on/off */
    quint16 m_uiCtrlPanelMode;

    /** Max defrost on/off */
    quint16 m_uiMaxDefrostMode;

    /** fresh air recirculation mode (0:Recirculation_ON, 2:Fresh_Air_ON) */
    CHVACEnums::EHVACAirCirculationModes m_eAirRecirculationMode;

    /** Distribution modes (1~5) */
    CHVACEnums::EHVACDistributionMode m_eDistributionMode;

    /** fan speed (0~7) */
    quint16 m_uiFanSpeed;

    /** Dual Mode ON/OFF */
    bool m_bDualMode;

    /** Temp (160~300) */
    float m_fTemperature;

    /** rear defog ON/OFF */
    quint16 m_uiRearDefog;

    /** Error Set/Unset */
    quint16 m_uiErrorStatus;

    /** config : fan low speed limit (0~7) */
    quint16 m_uiFanSpeedLowLimit;

    /** config : fan High speed limit (0~7) */
    quint16 m_uiFanSpeedHighLimit;

    /** config : Temperature low limit */
    float m_fTemperatureLowLimit;

    /** config : Temperature High limit */
    float m_fTemperatureHighLimit;

    /** CCM presence status */
    CHVACEnums::EHVACCCMPresence m_eCCMPresence;

    //! CCM zone type
    CHVACEnums::EHVACZoneType   m_eHvacZoneType;
    //! Air Flow presence status
    bool m_bAirFlowPresenceStatus;
    //! AC presenceStatus
    bool m_bACPresenceStatus;
    //! Econ presence status
    bool m_bEconPresenceStatus;
    //! Temperature presence status
    bool m_bTemperaturePresenceStatus;
    //! Auto presence status
    bool m_bAutoPresenceStatus;
    //! Fan presence status
    bool m_bFanPresenceStatus;
    //! Fresh Air presence status
    bool m_bFreshAirPresenceStatus;
    //! Xpress Cooling presence status
    bool m_bXpressCoolingPresenceStatus;
    //! Defrost presence status
    bool m_bDefrostPresenceStatus;
    //! HVAC container type
    CHVACEnums::EHVACContainerType m_eHvacContainerType;
    //! Driver temprature
    float m_fDriverTemperature;
    //! Passenger temprature
    float m_fPassengerTemperature;
    //! List of fan speed images
    QStringList m_listFanSpeedImages;
};

#endif // CHVACADAPTOR_H
