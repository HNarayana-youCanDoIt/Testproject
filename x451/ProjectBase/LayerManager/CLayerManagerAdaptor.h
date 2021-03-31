/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CLayerManagerAdaptor.h
 * @ingroup         HMIComponent
 * @author          Mohit Rajani
 * CLayerManagerAdaptor, an Adaptor for LayerManager module,
 * CLayerManagerAdaptor used to communicate between QML and Resource Layer.
 */

#ifndef CLAYERMANAGERADAPTOR_H
#define CLAYERMANAGERADAPTOR_H

#include <QObject>
#include "CLayerManagerEnums.h"

class ILayerManagerResource;

/**
 * @brief The CLayerManagerAdaptor, an Adaptor for LayerManager module,
 * CLayerManagerAdaptor used to communicate between QML and Resource Layer.
 */
class CLayerManagerAdaptor : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief getInstance, provides the instance of the LayerManager adaptor
     * @param void
     * @return CLayerManagerAdaptor, LayerManager adaptor object
     */
    static CLayerManagerAdaptor* getInstance();

    /**
     * @brief destructor
     * param void
     * return void
     */
    ~CLayerManagerAdaptor();

    /**
     * @brief showScene based on the current state of the system make appropriate calls to show a surface
     * @param ESurfaceType surface that needs to be show
     * @return void
     */
    void showScene(CLayerManagerEnums::ESurfaceType eSurfaceType);

    /**
     * @brief hideScene function to ask layermanager to hide the video surface
     * @param ESurfaceType surface that needs to be show
     * @return void
     */
    void hideScene(CLayerManagerEnums::ESurfaceType eSurfaceType);

    /**
     * @brief onShowNotificationSurfaceResult method would be called on show notification surface callback on resource layer
     * @param result whether layer manager was able to show the surface or not, or there was an error
     * @return void
     */
    void onShowNotificationSurfaceResult(int iResult);

    /**
     * @brief onHideNotificationSurfaceResult method would be called on hide notification surface callback on resource layer
     * @param result whether layer manager was able to hide the surface or not, or there was an error
     * @return void
     */
    void onHideNotificationSurfaceResult(int iResult);

    /**
     * @brief onShowSurfaceResult method would be called on show generic surface callback on resource layer
     * @param result whether layer manager was able to show the surface or not, or there was an error
     * @return void
     */
    void onShowSurfaceResult(int iResult);

    /**
     * @brief onHideSurfaceResult method would be called on hide generic surface callback on resource layer
     * @param result whether layer manager was able to hide the surface or not, or there was an error
     * @return void
     */
    void onHideSurfaceResult(int iResult);

    /**
     * @brief onNotificationLayerVisibiltyState
     * @param bVisibilityState the state whether visible or invisible
     * @return void
     */
    void onNotificationLayerVisibiltyState(bool bVisibilityState);

    /**
     * @brief getNotificationLayerVisibiltyState get the current state of the notification layer visibility
     * @param void
     * @return visibility state
     */
    bool getNotificationLayerVisibiltyState();

private:

    /************* Notification Start *************/

    /**
     * @brief showVoiceAlertNotificationSurface function to ask layermanager to show
     *        the hvac notification surface.
     * @param void
     * @return void
     */
    void showVoiceAlertNotificationSurface();

    /**
     * @brief hideNotificationSurface function to ask layermanager to hide the
     *        hvac notification surface
     * @param void
     * @return void
     */
    void hideVoiceAlertNotificationSurface();

    /**
     * @brief showVolNotificationSurface function to ask layermanager to show the
     *        volume notification surface.
     * @param void
     * @return void
     */
    void showVolNotificationSurface();

    /**
     * @brief hideVolNotificationSurface function to ask layermanager to hide the volume notification surface
     * @param void
     * @return void
     */
    void hideVolNotificationSurface();

    /************* Notification End *************/

    /************* Surface Start *************/
    /**
    * @brief showSurface function to ask layermanager to show the specified surface
    * @param surfaceName name of the surface that needs to be shown
    * @return void
    */
    void showSurface(QString strSurfaceName);

    /**
    * @brief hideSurface function to ask layermanager to hide the specified surface
    * @param surfaceName name of the surface that needs to be hidden
    * @return void
    */
    void hideSurface(QString strSurfaceName);
    /************* Surface End *************/

private slots:

    /**
     * @brief sltProjectionOwnerChanged this slot is called when AA or CP projection owner status changes
     * @param void
     * @return void
     */
    void sltProjectionOwnerChanged();

signals:

    /**
     * @brief sigShowVideoSurfaceResult signal is emitted to inform clients of the show result
     * @param result whether layer manager was able to show the surface or not, or there was an error
     * @return void
     */
    void sigShowVideoSurfaceResult(int iResult);

    /**
     * @brief sigHideVideoSurfaceResult signal is emitted to inform clients of the hide result
     * @param result whether layer manager was able to hide the surface or not, or there was an error
     * @return void
     */
    void sigHideVideoSurfaceResult(int iResult);

    /**
     * @brief sigShowNotificationSurfaceResult signal is emitted to inform clients of the show result
     * @param result whether layer manager was able to show the surface or not, or there was an error
     * @return void
     */
    void sigShowNotificationSurfaceResult(int iResult);

    /**
     * @brief sigHideNotificationSurfaceResult signal is emitted to inform clients of the hide result
     * @param result whether layer manager was able to hide the surface or not, or there was an error
     * @return void
     */
    void sigHideNotificationSurfaceResult(int iResult);

    /**
     * @brief sigShowSurfaceResult signal is emitted to inform clients of the show result
     * @param result whether layer manager was able to show the surface or not, or there was an error
     * @return void
     */
    void sigShowSurfaceResult(int iResult);

    /**
     * @brief sigHideSurfaceResult signal is emitted to inform clients of the hide result
     * @param result whether layer manager was able to hide the surface or not, or there was an error
     * @return void
     */
    void sigHideSurfaceResult(int iResult);

    /**
     * @brief sigNotificationLayerVisibilityState signal emitted when property update is received
     * @param bVisibilityState the state whether visible or invisible
     * @return void
     */
    void sigNotificationLayerVisibilityState(bool bVisibilityState);

private:
    /**
     * @brief CLayerManagerAdaptor constructor
     * @param parent parent object instance
     * @return void
     */
    explicit CLayerManagerAdaptor(QObject *parent = nullptr);

private:
    /** Layer manager static object */
    static CLayerManagerAdaptor* m_pLayerManagerAdaptor;

    /** Instance of LayerManager resource */
    ILayerManagerResource* m_pLayerManagerResource;

    /** store the notification layer visibility state (true/false) */
    bool    m_bNotificationLayerVisibilityState;

};

#endif // CLAYERMANAGERADAPTOR_H
