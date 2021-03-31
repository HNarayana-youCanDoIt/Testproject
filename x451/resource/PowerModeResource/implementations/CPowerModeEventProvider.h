/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CPowerModeEventProvider.h
 * @ingroup         HMIComponent
 * @author          Prashantkumar Raut
 * CPowerModeEventProvider - Class to send signals to PowerMode module on PowerMode Resource events
 */

#ifndef CPOWERMODEEVENTPROVIDER_H
#define CPOWERMODEEVENTPROVIDER_H

#include <QObject>

/**
 * @brief CPowerModeEventProvider - The class emits the signals to the CPowerModeEventHandler based on PowerMode resource events
 */
class CPowerModeEventProvider: public QObject
{
    Q_OBJECT

public:
    /**
    * @brief	CPowerModeEventProvider::CPowerModeEventProvider constructor for data handler class CPowerModeEventProvider.
    * @param	QObject.
    * @return	NA.
    **/
    CPowerModeEventProvider(QObject* parent = 0);

    /**
    * @brief	CPowerModeEventProvider::~CPowerModeEventProvider is destructor of data handler class CPowerModeEventProvider
    * @param	NA.
    * @return	NA.
    **/
    ~CPowerModeEventProvider();

signals:
    /**
    * @brief	This function is called internally when Power mode value is changed and
    *           consumed by the application layer.
    * @param	m_mode: Power mode string value.
    * @return	void.
    */
    void sigUpdatePowerMode(QString m_strMode);

    /**
     * @brief sigUpdateNSMNodeState, This signal is emitted when nsm node state is changed and
    *           consumed by the application layer.
     * @param nsmNodeState nsm node state value
     */
    void sigUpdateNSMNodeState(int iNsmNodeState);

    /**
     * @brief sigUpdateOneHourExpiryState: This signal is emitted when one hour expiry state is changed.
     * @param bOneHourExpiryState: State of one hour expiry active or not.
     * @return void.
     */
    void sigUpdateOneHourExpiryState(bool bOneHourExpiryState);

public:
    /**
    * @brief	This function is called from resource layer when Power mode data has updated.
    * @param	m_mode: Power mode string value.
    * @return	void.
    */
    void updatePowerMode(std::string  m_strMode);

    /**
     * @brief updateNSMNodeState, This function is called from resource layer when nsm node state has updated.
     * @param nsmNodeState, nsm node state value
     */
    void updateNSMNodeState(int iNsmNodeState);

    /**
     * @brief updateOneHourExpiryState: This function is called from resource layer when one hour expiry state is changed.
     * @param bOneHourExpiryState: State of one hour expiry active or not.
     * @return void.
     */
    void updateOneHourExpiryState(bool bOneHourExpiryState);
};

#endif // CPOWERMODEEVENTPROVIDER_H

