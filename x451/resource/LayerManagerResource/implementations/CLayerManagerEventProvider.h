/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CLayerManagerEventProvider.h
* @ingroup      HMIComponent
* @author       Mohit Rajani
* CLayerManagerEventProvider, propogates LayerManager service events to the upper layers
*/

#ifndef CLAYERMANAGEREVENTPROVIDER_H
#define CLAYERMANAGEREVENTPROVIDER_H

#include <QObject>

/**
 * @class CLayerManagerEventProvider
 * @brief This class propogates LayerManager service events to the upper layers
 */
class CLayerManagerEventProvider: public QObject
{
    Q_OBJECT

public:
    CLayerManagerEventProvider(QObject* parent = 0);
    ~CLayerManagerEventProvider();

signals:

    /**
     * @brief sigShowNotificationSurfaceResult Signal to notify CLayerManagerEventHandler about show notification layer result
     * @param result whether layer manager was able to show the surface or not, or there was an error
     * @return void
     */
    void sigShowNotificationSurfaceResult(int result);

    /**
     * @brief sigHideNotificationSurfaceResult Signal to notify CLayerManagerEventHandler about hide notification layer result
     * @param result whether layer manager was able to show the surface or not, or there was an error
     * @return void
     */
    void sigHideNotificationSurfaceResult(int result);

    /**
     * @brief sigNotificationLayerVisibilityState signal emitted when property update is received
     * @param bVisibilityState the state whether visible or invisible
     * @return void
     */
    void sigNotificationLayerVisibilityState(bool bVisibilityState);

    /**
     * @brief sigShowSurfaceResult Signal to notify CLayerManagerEventHandler about show notification layer result
     * @param result whether layer manager was able to show the surface or not, or there was an error
     * @return void
     */
    void sigShowSurfaceResult(int result);

    /**
     * @brief sigHideSurfaceResult Signal to notify CLayerManagerEventHandler about hide notification layer result
     * @param result whether layer manager was able to show the surface or not, or there was an error
     * @return void
     */
    void sigHideSurfaceResult(int result);

public:
    /** Declare the functions that would be used by the Resource layer to indirectly emit signals to the upper layers */

    /**
     * @brief onShowNotificationSurfaceResult provides the result of the request to layer manager to show notification surface
     * @param result whether layer manager was able to show the surface or not, or there was an error
     * @return void
     */
    void onShowNotificationSurfaceResult(int result);

    /**
     * @brief onHideNotificationSurfaceResult provides the result of the request to layer manager to hide notification surface
     * @param result whether layer manager was able to hide the surface or not, or there was an error
     * @return void
     */
    void onHideNotificationSurfaceResult(int result);

    /**
     * @brief onShowSurfaceResult provides the result of the request to layer manager to show notification surface
     * @param result whether layer manager was able to show the surface or not, or there was an error
     * @return void
     */
    void onShowSurfaceResult(int result);

    /**
     * @brief onHideSurfaceResult provides the result of the request to layer manager to hide notification surface
     * @param result whether layer manager was able to hide the surface or not, or there was an error
     * @return void
     */
    void onHideSurfaceResult(int result);

    /**
     * @brief onNotificationLayerVisibilityState
     * @param bVisibilityState the state whether visible or invisible
     * @return void
     */
    void onNotificationLayerVisibilityState(bool bVisibilityState);
};

#endif // CLAYERMANAGEREVENTPROVIDER_H
