/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CLayerManagerResourceImpl.h
* @ingroup      HMIComponent
* @author       Mohit Rajani
* CLayerManagerResourceImpl, Resource Implementation for Layer manager.
*/

#ifndef CLAYERMANAGERRESOURCEIMPL_H
#define CLAYERMANAGERRESOURCEIMPL_H

#include "interfaces/ILayerManagerResource.h"
#include <capi/CAPIClientAbstraction.hpp>
#include "CLayerManagerEventProvider.h"

/**
 * @class CLayerManagerResourceImpl
 * @brief This class implements the LayerManager Resource intreface
 */
class CLayerManagerResourceImpl : public ILayerManagerResource
{
public:

    /**
     * @brief ~CLayerManagerResourceImpl Destructor
     * @param void
     * @return void
     */
    virtual ~CLayerManagerResourceImpl();

    /**
     * @brief getLayerManagerEventProvider Method to get the instance of CLayerManagerEventProvider
     * @param void
     * @return CLayerManagerEventProvider*
     */
    CLayerManagerEventProvider* getLayerManagerEventProvider() { return m_pLayerManagerEventProvider;}

    /*********************************************************
             Request Methods
     *********************************************************/

    /**
     * @brief showVoiceAlertNotificationSurface method to call layer manager to show
     *        the HVAC notification surface.
     * @param void
     * @return void
     */
    virtual void showVoiceAlertNotificationSurface() override;

    /**
     * @brief hideVoiceAlertNotificationSurface method to call layer manager to hide
     *        the HVAC notification surface.
     * @param void
     * @return void
     */
    virtual void hideVoiceAlertNotificationSurface() override;

    /**
     * @brief showVolNotificationSurface method to call layer manager to show
     *        the volume notification surface.
     * @param void
     * @return void
     */
    virtual void showVolNotificationSurface() override;

    /**
     * @brief hideVolNotificationSurface method to call layer manager to hide
     *        the volume notification surface.
     * @param void
     * @return void
     */
    virtual void hideVolNotificationSurface() override;

    /**
     * @brief onPropertyUpdateEventCb called when there is a property update for the subscribed property
     * @param property updated property data
     * @return void
     */
    void onPropertyUpdateEventCb(LayerManagerTypes::tProperty property);

    /**
     * @brief showSurface method to call layer manager to show a particular surface
     * @param strSurfaceName name of the surface to be shown
     * @return void
     */
    virtual void showSurface(std::string strSurfaceName) override;

    /**
     * @brief hideSurface method to call layer manager to hide a particular surface
     * @param strSurfaceName name of the surface to be hidden
     * @return void
     */
    virtual void hideSurface(std::string strSurfaceName) override;

private:
    CLayerManagerResourceImpl();

    /**
     * @brief subscribe Method to subscribe CallBack methods to events provided by LayerManagerProxy
     * @param void
     * @return void
     */
    void subscribe();

    /**
     * @brief layerManagerServiceStatusCb CallBack method to get notified about the availability status of Media Proxy
     * @param eStatus - status of Media proxy whether available or not
     * @return void
     */
    void layerManagerServiceStatusCb(CommonAPI::AvailabilityStatus eStatus );

    /**
     * @brief showHVACNotificationSurfaceAsyncCb CallBack to get notified about showSurface method response
     * @param eCallStatus - call status of the method, whether success or not.
     * @param eResult - type of the error received after invoking method.
     * @return void
     */
    void showHVACNotificationSurfaceAsyncCb(const CallStatus &eCallStatus, const LayerManagerTypes::tResult &eResult);

    /**
     * @brief hideHVACNotificationSurfaceAsyncCb Callback to get notified about hideSurface method response
     * @param status - call status of the method, whether success or not.
     * @param result - type of the error received after invoking method.
     * @return void
     */
    void hideHVACNotificationSurfaceAsyncCb(const CallStatus &eCallStatus, const LayerManagerTypes::tResult &eResult);

    /**
     * @brief showVolNotificationSurfaceAsyncCb CallBack to get notified about showSurface method response
     * @param eCallStatus - call status of the method, whether success or not.
     * @param eResult - type of the error received after invoking method.
     * @return void
     */
    void showVolNotificationSurfaceAsyncCb(const CallStatus &eCallStatus, const LayerManagerTypes::tResult &eResult);

    /**
     * @brief hideVolNotificationSurfaceAsyncCb Callback to get notified about hideSurface method response
     * @param eCallStatus - call status of the method, whether success or not.
     * @param eResult - type of the error received after invoking method.
     * @return void
     */
    void hideVolNotificationSurfaceAsyncCb(const CallStatus &eCallStatus, const LayerManagerTypes::tResult &eResult);

    /**
     * @brief showSurfaceAsyncCb CallBack to get notified about showSurface method response
     * @param eCallStatus - call status of the method, whether success or not.
     * @param eResult - type of the error received after invoking method.
     * @return void
     */
    void showSurfaceAsyncCb(const CallStatus &eCallStatus, const LayerManagerTypes::tResult &eResult);

    /**
     * @brief hideSurfaceAsyncCb Callback to get notified about hideSurface method response
     * @param eCallStatus - call status of the method, whether success or not.
     * @param eResult - type of the error received after invoking method.
     * @return void
     */
    void hideSurfaceAsyncCb(const CallStatus &eCallStatus, const LayerManagerTypes::tResult &eResult);

private:
    /**
     * @brief Adding ResourceFactory class as friend class so that
     * ResourceFactory shall be able to create the instance of this class.
     */
    friend class ResourceFactory;

    /** to check if Layer manager Service is available of not */
    bool    m_bLayerManagerAvailable;

    /** Instance of CLayerManagerEventProvider to emit signals to the upper layer */
    CLayerManagerEventProvider* m_pLayerManagerEventProvider;

    /** LayerManagerProxy class object to call layer manager Proxy methods */
    CAPIClientAbstraction<LayerManagerProxy> m_pLayerManagerProxy;

};

#endif // CLAYERMANAGERRESOURCEIMPL_H
