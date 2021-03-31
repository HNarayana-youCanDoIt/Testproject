/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CDeviceModeHandlerResourceImpl.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* CDeviceModeHandlerResourceImpl, Resource Implementation for DeviceModeHandler.
*/
#ifndef CDEVICEMODEHANDLERRESOURCEIMPL_H
#define CDEVICEMODEHANDLERRESOURCEIMPL_H

#include "interfaces/IDeviceModeHandlerResource.h"
#include "CDeviceModeHandlerEventProvider.h"
#include "CDeviceModeHandlerResourceData.h"

/**
 * @class CDeviceModeHandlerResourceImpl
 * @brief This class shall implement DeviceModeHandler Resource intreface
 */
class CDeviceModeHandlerResourceImpl: public IDeviceModeHandlerResource
{
public:
    virtual ~CDeviceModeHandlerResourceImpl();

    /**
     * @brief   Method to get the instance of CDeviceModeHandlerEventProvider
     * @param   void
     * @return  CDeviceModeHandlerEventProvider*: Pointer of
     *          CDeviceModeHandlerEventProvider
     */
    CDeviceModeHandlerEventProvider* getDeviceModeHandlerEventProvider();


    /*********************************************************
             Request Methods
     *********************************************************/

private:
    CDeviceModeHandlerResourceImpl();

    /*********************************************************
             Internal Methods
     *********************************************************/
    /**
     * @brief   Method to subscribe CallBack methods to events provided by
     *          DeviceModeHandlerPlayerProxy
     * @param   void
     * @return  void
     */
    void subscribe();


    /**
     * @brief   Method to get mapped enum of DeviceType, We have created our own
     *          enum for device type, this function accepts dev press's device
     *          type enum and return local mapped device type enum.
     * @param   const devprestypes::eDeviceType &: dev press's device type enum.
     * @return  EDeviceType: Local device type enum whihc is mapped with passed
     *          dev press's device type enum.
     */
    EDeviceType getDeviceTypeEnum(const devprestypes::eDeviceType &eDeviceTypeRcv);


    /**
     * @brief   Method to requext startMode for projection. This function calls
     *          the startModeAsync() of Dev press to start session of particular
     *          projection.
     * @param   const devprestypes::eModeName &eModeName: ModeName for which this
     *          function has to call startMode of devPress to start the session.
     * @param   uint8_t uiDeviceID: DeviceID for which startMode has to call.
     * @return  void.
     */
    void startModeReq(const devprestypes::eModeName &eModeName, uint8_t uiDeviceID);

    /*!
     * @brief   setProjectionConnectionStatus: This function is used to set the
     *          projection connection status, like AndroidAuto/Carplay
     *          connection status.
     * @param   objModeInfo: ModeInfo of connected device.
     * @return  void.
     */
    void setProjectionConnectionStatus(const devprestypes::sModeInfo &objModeInfo);

    /*********************************************************//**
     * @category CALLBACK METHODS
     *********************************************************/

    /*!
     * @brief   Callback to get notified about the avalability status of the
     *          DeviceModeHandler proxy.
     * @param   eStatus - status of DeviceModeHandler proxy whether available
     *          or not.
     * @return  void.
     */
    void deviceModeHandlerServiceStatusCb(CommonAPI::AvailabilityStatus eStatus) override;

    /*!
     * @brief   Callback to get notified about the device insertion.
     * @param   objDeviceInfo - sDeviceInfo object gives device details.
     * @return  void.
     */
    void deviceInsertedCb(const devprestypes::sDeviceInfo &objDeviceInfo) override;

    /*!
     * @brief   Callback to get notified about the device removal.
     * @param   objDeviceInfo - sDeviceInfo object gives device details.
     * @return  void.
     */
    void deviceRemovedCb(uint8_t uiRemovalStatus) override;

    /*!
     * @brief   CallBack to update status of method calls startMode &
     *          stopMode. This is the call back function which will be called
     *          to notify the Projection (AndroidAuto/SmartLink/CarPlay)
     *          connection status/information.
     * @param   uiDeviceID - device ID for which connection information reported.
     * @param   bHasConflictsMode: is set to TRUE if there is any conflicting
     *          mode available. and conflicting  mode details can be found
     *          with "details" parameter.
     * @param   vectSConflictMode: vector of sConflictMode: this contains the
     *          conflicting mode details if bHasConflictsMode is true.
     * @param   objModeInfo: This contains the details about the mode info for
     *          which we called startMode or stopMode, to start or stop mode
     *          session, Like AA session or CarPlay session, From this we can
     *          know that what is the projection mode(AA/CarPlay/SL) connection
     *          status? connected/disconnected.
     * @return  void.
     */
    void modeStatusCb(uint8_t uiDeviceID,
                      bool bReinsertedNeeded,
                      bool bHasConflictsMode,
                      const vector<devprestypes::sConflictMode> &vectSConflictMode,
                      const devprestypes::sModeInfo &objModeInfo) override;


    /********************************************//**
     * @category RESPONSE CALLBACK METHODS
     ************************************************/

    /*!
     * @brief startModeAsyncCb: Callback function of startMode api
     * @param eCallStatus: callStatus information.
     * @param eAcknowledgement: VALID_INPUT = 0, INVALID_INPUT = 1
     *
     */
     void startModeAsyncCb(const CallStatus &eCallStatus, const devprestypes::eAcknowledgement &eAcknowledgement) override;

     /*!
      * @brief   getInsertedDeviceInfoAsyncCb: Callback to get notified about the
      *          device insertion.
      * @param   eCallStatus: Call status.
      * @param   objvDeviceInfo - vDeviceInfo object vector of sDeviceInfo structure
      *           which contains the device details.
      * @return  void.
      */
     void getInsertedDeviceInfoAsyncCb(const CallStatus &eCallStatus, const devprestypes::vDeviceInfo &objvDeviceInfo) override;

private:
    /**
     * @brief Adding ResourceFactory class as friend class so that
     * ResourceFactory shall be able to create the instance of this class.
     */
    friend class ResourceFactory;

    /*********************************************************//**
     *      @category   PROPERTIES
     *********************************************************/

    /**
     * @brief: Instance of CDeviceModeHandlerEventProvider to emit signals to
     * the upper layer
     */
    CDeviceModeHandlerEventProvider* m_pDeviceModeHandlerEventProvider;

    /**
     * @brief: DeviceModeHandlerPlayerProxy class object to call
     * DeviceModeHandler Player Proxy methods
     */
    CAPIClientAbstraction<DeviceModeHandlerProxy> m_objDeviceModeHandlerProxy;

    /**
     * @brief: variable to store the availability status of
     * DeviceModeHandlerProxy.
     */
    bool m_bIsDeviceModeHandlerAvailable;

    /**
     * @brief: variable to store the Device informations.
     */
    SDeviceInformation m_objDeviceInfo;
};

#endif // CDEVICEMODEHANDLERRESOURCEIMPL_H
