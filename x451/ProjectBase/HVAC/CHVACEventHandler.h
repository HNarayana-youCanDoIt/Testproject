/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CHVACEventHandler.h
* @ingroup      HMIComponent
* @author       Mohit Rajani
* @class        CHVACEventHandler: Class acts as the event handler for all the signals/events sent by CHVACEventHandler
* which informs HVAC Adaptor about HVAC resource events
*/

#ifndef CHVACEVENTHANDLER_H
#define CHVACEVENTHANDLER_H

#include <QObject>

class CHVACAdaptor;

/**
 * @brief The CHVACEventHandler Class acts as the event handler for all the signals/events sent by CHVACEventHandler
 * which informs HVAC Adaptor about HVAC resource events
 */
class CHVACEventHandler : public QObject
{
    Q_OBJECT
public:
    explicit CHVACEventHandler(QObject *parent = nullptr);
    ~CHVACEventHandler();

public slots:

    /**
     * @brief sltHVACParamUpdate Method to inform HVAC adaptor that a parituclar HVAC parameter has been updated
     * @param eParameterEnum the HVAC parameter that has been updated
     * @param uiValue the update value for the HVAC parameter
     */
    void sltHVACParamUpdate(int eParameterEnum , const uint16_t& uiValue);

    /**
     * @brief sltHVACInfoReceived Method to inform HVAC adaptor that a HVAC values has been received
     * @param void
     * @param void
     */
    void sltHVACInfoReceived();

    /**
     * @brief   sltCcmUserInterventionParamChanged: Slot to notify HVAC adaptor that CCM parameter is changed
     *          through user intervention.
     * @param   ucHuCcmParam: The CCM parameter which has been changed.
     * @return  void.
     */
    void sltCcmUserInterventionParamChanged(uint8_t ucHuCcmParam);


private:
    /**
     * @brief Method to connect CHVACEventProvider signals to slots
     * @param void
     * @return void
     */
    void connectSignals();

private:

    /** Pointer to hold the HVAC adaptor instance */
    CHVACAdaptor *m_pHVACAdaptor;
};

#endif // CHVACEVENTHANDLER_H
