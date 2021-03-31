/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CLayerManagerEventHandler.h
* @ingroup      HMIComponent
* @author       Mohit Rajani
* @class        CLayerManagerEventHandler: Class acts as the event handler for all the signals/events sent by CLayerManagerEventProvider
* which informs LayerManager Adaptor about LayerManager resource events
*/

#ifndef CLAYERMANAGEREVENTHANDLER_H
#define CLAYERMANAGEREVENTHANDLER_H

#include <QObject>

class CLayerManagerAdaptor;

/**
 * @brief The CLayerManagerEventHandler Class acts as the event handler for all the signals/events sent by CLayerManagerEventProvider
 * which informs LayerManager Adaptor about LayerManager resource events
 */
class CLayerManagerEventHandler : public QObject
{
    Q_OBJECT
public:
    explicit CLayerManagerEventHandler(QObject *parent = nullptr);
    ~CLayerManagerEventHandler();

public slots:

    /******* Notification start *********/
    /**
     * @brief sltShowNotificationSurfaceResult
     * @param result whether layer manager was able to show the surface or not, or there was an error
     * @return void
     */
    void sltShowNotificationSurfaceResult(int iResult);

    /**
     * @brief sltHideNotificationSurfaceResult
     * @param result whether layer manager was able to hide the surface or not, or there was an error
     * @return void
     */
    void sltHideNotificationSurfaceResult(int iResult);

    /**
     * @brief sltNotificationLayerVisibilityState
     * @param bVisibilityState the state whether visible or invisible
     * @return void
     */
    void sltNotificationLayerVisibilityState(bool bVisibilityState);

    /******* Notification end *********/


    /******* Surface start *********/
    /**
     * @brief sltShowSurfaceResult
     * @param result whether layer manager was able to show the surface or not, or there was an error
     * @return void
     */
    void sltShowSurfaceResult(int iResult);

    /**
     * @brief sltHideSurfaceResult
     * @param result whether layer manager was able to hide the surface or not, or there was an error
     * @return void
     */
    void sltHideSurfaceResult(int iResult);
    /******* Surface end *********/

private:
    /**
     * @brief Method to connect CLayerManagerEventProvider signals to slots
     * @param void
     * @return void
     */
    void connectSignals();
};

#endif // CLAYERMANAGEREVENTHANDLER_H
