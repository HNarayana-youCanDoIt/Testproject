/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         WaylandIVIController.h
* @ingroup      HMI Framework
* @author       Mohit Rajani
* @brief class acts as the wrapper ontop of the layer manager ilm calls. The class creates the ilm surfaces for
* the main hmi and notification windows
*/

#ifndef WAYLANDIVICONTROLLER_H
#define WAYLANDIVICONTROLLER_H

#include <wayland-client.h>
#include <ilm/ilm_control.h>
#include <ilm/ilm_client.h>
#include <ilm/ilm_input.h>
#include <ilm/ilm_types.h>
#include <QtGui/qpa/qplatformnativeinterface.h>
#include <QSharedPointer>
#include <QWindow>

/**
 * @brief The WaylandIVIController class, class acts as the wrapper ontop of the layer manager ilm calls. The class creates the ilm surfaces for
 * the main hmi and notification windows
 */
class WaylandIVIController
{
public:
    WaylandIVIController();

    /**
     * @brief Performs ILM layer setup for the specified window. This uses
     * hardcoded IDs for the application's layer and surface.
     * @param window
     * @param surface id of the surface to setup
     */
    void waylandLayerSetup(QWindow *window, t_ilm_surface surfaceId);

private:
    /** Wayland display struct */
    struct wl_display *wlDisplay;

    /** native interface pointer */
    QPlatformNativeInterface *native;
};

#endif // WAYLANDIVICONTROLLER_H
