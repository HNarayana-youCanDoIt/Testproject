/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CPowerModeAdaptor.h
 * @ingroup         HMIComponent
 * @author          Prashantkumar Raut
 * CPowerModeAdaptor an adaptor for PowerMode module which is used
 * to communicate with the power mode resource layer, QML layer and state machine
 */

#ifndef CPOWERMODEADAPTOR_H
#define CPOWERMODEADAPTOR_H

#include <QObject>
#include <QString>
#include "logging.h"
#include "CFramework.h"
#include "CPowerModeEnums.h"

class CPowerModeEventHandler;

/**
 * @brief CPowerModeAdaptor, an Adaptor for Power System,
 * CPowerModeAdaptor is singleton class used to communicate with qml resources of Power System.
 */
class CPowerModeAdaptor : public QObject
{
    Q_OBJECT

    /*! Property to hold the current powerMode */
    Q_PROPERTY(CPowerModeEnums::eVehiclePowerModes powerMode READ getPowerModeStatus NOTIFY sigPowerModeChanged)

public:
    /**
    * @brief	CPowerModeAdaptor::getInstance is static method used to get instance of singleton class CPowerModeAdaptor
    * @param	void.
    * @return	CPowerModeAdaptor.
    **/
    static CPowerModeAdaptor &getInstance();

    /**
    * @brief	CPowerModeAdaptor::~CPowerModeAdaptor is destructor of singleton class CPowerModeAdaptor
    * @param	NA.
    * @return	NA.
    **/
    ~CPowerModeAdaptor();

    /**
    * @brief	CPowerModeAdaptor::powerModeChanged is a method for changing SM Power Modes according to
    * the corresponding Power modes received from service
    * @param	m_ePowerMode - Current power mode
    * @return	void.
    **/
    void powerModeChanged(CPowerModeEnums::eVehiclePowerModes ePowerMode);

    /**
    * @brief	CPowerModeAdaptor::getPowerModeStatus is a get method for the power mode status according to
    * the corresponding Power modes received from service
    * @param	void
    * @return	current power mode as per CPowerModeEnums
    **/
    CPowerModeEnums::eVehiclePowerModes getPowerModeStatus();

    /**
     * @brief getNSMNodeState method to get nsm node state according to the state received from the service
     * @param void
     * @return current nsm node state
     */
    CPowerModeEnums::eNSMNodeStates getNSMNodeState();

    /**
    * @brief	CPowerModeEventHandler::sltPowerModeEvent is slot to get Power event change call back from resource
    * @param	QString m_mode the updated power mode string
    * @return	void.
    **/
    void sltPowerModeEvent(QString m_mode);

    /**
     * @brief sltNSMNodeStateEvent, slot to get nsm node state change call back from resource
     * @param nsmNodeState
     * @return void
     */
    void sltNSMNodeStateEvent(int iNsmNodeState);

    /**
     * @brief updateOneHourExpiryState: This method checks the value of one hour expiry state,
     *          if true, display's the popup EN_POPUPID_POWERMODE_ONE_HOUR_MODE_EXPIRY.
     * @param bOneHourExpiryState: State of one hour expiry active or not.
     * @return void.
     */
    void updateOneHourExpiryState(bool bOneHourExpiryState);

    /**
     * @brief setOneHourExpiryStateInactive: This method is used to set the one hour expiry state in-active.
     * @param void.
     * @return void.
     */
    Q_INVOKABLE void setOneHourExpiryStateInactive();

signals:
    /**
     * @brief sigCurrentPowerModeChanged signal is emitted when the current power mode changes
     * @return
     */
    void sigPowerModeChanged();

private slots:
    /**
    * @brief	CPowerModeAdaptor::sltUpdatePowerMode is a method for changing SM Power Modes according to
    * the corresponding Power modes received from service
    * @param	void.
    * @return	void.
    **/
    void sltUpdatePowerMode();

private:
    /**
    * @brief	CPowerModeAdaptor::CPowerModeAdaptor private constructor for singleton class CPowerModeAdaptor.
    * @param	QObject.
    * @return	NA.
    **/
    explicit CPowerModeAdaptor(QObject *parent = nullptr); // for singleton pattern class

    /**
     * @brief convertPMStrToEnum function to convert powermode string into corresponding enumeration
     * @param m_mode power mode string
     * @return enumeration value for the provide mode string
     */
    CPowerModeEnums::eVehiclePowerModes convertPMStrToEnum(QString m_mode);

    /**
     * for maintaining singleton class instance
     */
    static CPowerModeAdaptor* m_pPowerModeAdaptor;

    /**
     * CPowerModeEventHandler instance
     */
    CPowerModeEventHandler* m_pPowerModeEventHandler;

    /**
     * member variable for storing the power mode value
     */
    CPowerModeEnums::eVehiclePowerModes m_ePowerModeStatus;

    /* member to store the nsm node state value */
    CPowerModeEnums::eNSMNodeStates m_eNSMNodeState;

    /** To store the status of one hour mode expiry */
    bool m_bOneHourModeExpiryState;

};
#endif // CPOWERMODEADAPTOR_H
