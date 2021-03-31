/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CRCAApplication.h
 * @ingroup         HMIComponent
 * @author          Nishant Khandagale
 * CRCAApplication, an Application for RCA module,
 * CRCAApplication act as creator calls for the adaptor and event handler
 */

#ifndef CRCAAPPLICATION_H
#define CRCAAPPLICATION_H

#include <QObject>
#include "HMIIncludes.h"

class CRCAAdaptor;
class CRCAEventHandler;

/**
 * @brief The CRCAApplication CRCAApplication, an Application for RCA module,
 * CRCAApplication act as creator calls for the adaptor and event handler
 */
class CRCAApplication : public QObject
{
public:

    /**
     * @brief CRCAApplication: constructor
     * @param pParent: parent object instance
     * @return void
     */
    CRCAApplication(QObject* pParent = nullptr);

    /**
     * @brief CRCAApplication: destructor
     * @param void
     * @return void
     */
    ~CRCAApplication();

private:

    /**
     * @brief m_pRCAAdaptor: Stores the RCA adaptor object instance
     */
    CRCAAdaptor* m_pRCAAdaptor;

    /**
     * @brief m_pRCAEventHandler: Stores the event handler object instance
     */
    CRCAEventHandler* m_pRCAEventHandler;
};

#endif // CRCAAPPLICATION_H
