/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CLayerManagerApplication.h
 * @ingroup         HMIComponent
 * @author          Mohit Rajani
 * CLayerManagerApplication, an Application for LayerManager module,
 * CLayerManagerApplication act as creator calls for the adaptor and event handler
 */

#ifndef CLAYERMANAGERAPPLICATION_H
#define CLAYERMANAGERAPPLICATION_H

#include <QObject>
#include "HMIIncludes.h"

class CLayerManagerAdaptor;
class CLayerManagerEventHandler;

/**
 * @brief The CLayerManagerApplication CLayerManagerApplication, an Application for LayerManager module,
 * CLayerManagerApplication act as creator calls for the adaptor and event handler
 */
class CLayerManagerApplication : public QObject
{
public:
    CLayerManagerApplication(QObject* parent = nullptr);
    ~CLayerManagerApplication();

private:
    /** Stores the LayerManager adaptor object instance */
    CLayerManagerAdaptor* m_pLayerManagerAdaptor;

    /** Stores the event handler object instance */
    CLayerManagerEventHandler* m_pLayerManagerEventHandler;
};

#endif // CLAYERMANAGERAPPLICATION_H
