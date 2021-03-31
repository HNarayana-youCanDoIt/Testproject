/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         ILayerManagerResource.h
* @ingroup      HMIComponent
* @author       Mohit Rajani
* ILayerManagerResource, an interface for Layer manager Resource Implementaion in HMI.
*/

#ifndef LAYERMANAGERRESOURCE_H
#define LAYERMANAGERRESOURCE_H

#include <string>
#include "v1/com/harman/layermanager/LayerManagerProxy.hpp"

using namespace std;
using namespace v1::com::harman::layermanager;

/**
 * @interface ILayerManagerResource
 * @brief     Interfaces for application layers to communicate with layermanager
 *            service
 */
class ILayerManagerResource
{
public:
    /**
     * @brief ~ILayerManagerResource virtual destructor
     * @param void
     * @return void
     */
    virtual ~ILayerManagerResource() {}

    /**
     * @brief showVoiceAlertNotificationSurface method to call layer manager to show
     *        the HVAC notification surface.
     * @param void
     * @return void
     */
    virtual void showVoiceAlertNotificationSurface() = 0;

    /**
     * @brief hideVoiceAlertNotificationSurface method to call layer manager to hide
     *        the HVAC notification surface.
     * @param void
     * @return void
     */
    virtual void hideVoiceAlertNotificationSurface() = 0;

    /**
     * @brief showVolNotificationSurface method to call layer manager to show
     *        the volume notification surface.
     * @param void
     * @return void
     */
    virtual void showVolNotificationSurface() = 0;

    /**
     * @brief hideVolNotificationSurface method to call layer manager to hide
     *        the volume notification surface.
     * @param void
     * @return void
     */
    virtual void hideVolNotificationSurface() = 0;

    /**
     * @brief showSurface method to call layer manager to show a particular surface
     * @param strSurfaceName name of the surface to be shown
     * @return void
     */
    virtual void showSurface(std::string strSurfaceName) = 0;

    /**
     * @brief hideSurface method to call layer manager to hide a particular surface
     * @param strSurfaceName name of the surface to be hidden
     * @return void
     */
    virtual void hideSurface(std::string strSurfaceName) = 0;

};

#endif // LAYERMANAGERRESOURCE_H
