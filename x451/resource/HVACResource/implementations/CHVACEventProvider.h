/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CHVACEventProvider.h
* @ingroup      HMIComponent
* @author       Mohit Rajani
* CHVACEventProvider, class to propogate events for resource layer to the HVAC Application layer
*/

#ifndef CHVACEVENTPROVIDER_H
#define CHVACEVENTPROVIDER_H

#include <QObject>
#include "v0/com/harman/dcif/CcmPresTypes.hpp"

using namespace v0::com::harman::dcif;

/**
 * @brief The CHVACEventProvider, class to propogate events for resource layer to the HVAC Application layer
 */
class CHVACEventProvider: public QObject
{
    Q_OBJECT

public:
    /**
     * @brief CHVACEventProvider Constructor
     * @param parent parent object instance
     */
    CHVACEventProvider(QObject* parent = 0);

    /**
     * @brief ~CHVACEventProvider Destructor
     */
    ~CHVACEventProvider();

signals:

    /**
     * @brief sigHVACParamUpdate, the signal is emitted when there is an update to the HVAC parameter
     * @param eParameterEnum the HVAC parameter that has been updated
     * @param uiValue the update value for the HVAC parameter
     * @return void
     */
    void sigHVACParamUpdate(int eParameterEnum , const uint16_t& uiValue);

    /**
     * @brief sigHVACInfoReceived Signal to notify HVAC details data has been received
     * @param void
     * @return void
     */
    void sigHVACInfoReceived();

    /**
     * @brief   sigCcmUserInterventionParamChanged: Signal to notify about CCM parameter is changed through user
     *          intervention to upper layer.
     * @param   ucHuCcmParam: The CCM parameter which has been changed.
     * @return  void.
     */
    void sigCcmUserInterventionParamChanged(uint8_t ucHuCcmParam);

public:

    /**
     * @brief HVACParamUpdate the function is called from the resource implementation to propogate update event to the above layers
     * @param eParameterEnum the HVAC parameter that has been updated
     * @param uiValue the update value for the HVAC parameter
     * @return void
     */
    void HVACParamUpdate(const CcmPresTypes::eHuCcmParam& eParameterEnum , const uint16_t& uiValue);

    /**
    * @brief	HVACInfoReceived This method will inform HVAC event handler, that HVAC info is received.
    * @param	void
    * @return	void
    */
    void HVACInfoReceived();

    /**
     * @brief   ccmUserInterventionParamChanged: Method to be called from resource layer to propogate CCM parameter changed event
     *          through user intervention to upper layer.
     * @param   ucHuCcmParam: The CCM parameter which has been changed.
     * @return  void.
     */
    void ccmUserInterventionParamChanged(uint8_t ucHuCcmParam);

};

#endif // CHVACEVENTPROVIDER_H
