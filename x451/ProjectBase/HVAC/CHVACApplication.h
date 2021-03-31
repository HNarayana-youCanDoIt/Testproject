/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CHVACApplication.h
 * @ingroup         HMIComponent
 * @author          Mohit Rajani
 * CHVACApplication, an Application for HVAC (ccm) module,
 * CHVACApplication act as creator calls for the adaptor and event handler
 */

#ifndef CHVACAPPLICATION_H
#define CHVACAPPLICATION_H

#include <QObject>
#include "HMIIncludes.h"

class CHVACAdaptor;
class CHVACEventHandler;

/**
 * @brief The CHVACApplication CHVACApplication, an Application for HVAC (ccm) module,
 * CHVACApplication act as creator calls for the adaptor and event handler
 */
class CHVACApplication : public QObject
{
public:
    CHVACApplication(QObject* parent = nullptr);
    ~CHVACApplication();

private:
    /** Stores the HVAC adaptor object instance */
    CHVACAdaptor* m_pHVACAdaptor;

    /** Stores the event handler object instance */
    CHVACEventHandler* m_pHVACEventHandler;
};

#endif // CHVACAPPLICATION_H
