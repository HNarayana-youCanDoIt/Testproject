/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         WaylandIVIController.cpp
* @ingroup      HMI Framework
* @author       Mohit Rajani
* @brief class acts as the wrapper ontop of the layer manager ilm calls. The class creates the ilm surfaces for
* the main hmi and notification windows
*/

#include "WaylandIVIController.h"
#include <QGuiApplication>
#include <QtDebug>
#include <logging.h>

/**
 * @brief The various layer and surface Id' that would be used by the HMI for the layer management
 */
t_ilm_surface ILM_SURFACEID_MAIN = 20;
t_ilm_surface ILM_SURFACEID_NOTIFICATION = 21;

/**
 * @brief The various ILM scene that defined within the HMI, and the surfaces within each scene
 */

template <int N>
struct ILMScene {
    static const int surfaceCount = N;
    t_ilm_surface surfaces[N];
};

ILMScene<1> SCENE_NATIVE_HMI = {{
    ILM_SURFACEID_MAIN
}};

t_ilm_surface* surfaces;
int surfaceCount;
int x;
int y;
int w;
int h;


WaylandIVIController::WaylandIVIController()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s", __FUNCTION__);
    native = QGuiApplication::platformNativeInterface();
    wlDisplay = (struct wl_display *)native->nativeResourceForWindow("display", NULL);
    ilmClient_init((t_ilm_nativedisplay)wlDisplay);
    x = 0;
    y = 0;
    w = 0;
    h = 0;

    surfaces = SCENE_NATIVE_HMI.surfaces;
    surfaceCount = SCENE_NATIVE_HMI.surfaceCount;
}


void WaylandIVIController::waylandLayerSetup(QWindow *window, t_ilm_surface surfaceId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s, surfaceId: %d",__FUNCTION__, surfaceId);
    ilmErrorTypes result;

    x = window->x();
    y = window->y();
    w = window->width();
    h = window->height();

    // Needs to be done for each window created
    struct wl_surface *surface = static_cast<struct wl_surface *>
            (native->nativeResourceForWindow("surface", window));

    result = ilm_surfaceCreate((t_ilm_nativehandle)surface,
                               w,
                               h,
                               ILM_PIXELFORMAT_RGBA_8888,
                               &surfaceId);
    if(result != ILM_SUCCESS)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"ilm_surfaceCreate Failed for HMI Main: %d, layer Id: %d",result, surfaceId );
    }

    ilm_commitChanges();
}
