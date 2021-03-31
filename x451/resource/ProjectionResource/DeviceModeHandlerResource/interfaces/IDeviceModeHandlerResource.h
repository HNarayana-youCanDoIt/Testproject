/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         IDeviceModeHandlerResource.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* IDeviceModeHandlerResource, an interface for DeviceModeHandler Resource Implementaion in HMI.
*/

#ifndef IDEVICEMODEHANDLERRESOURCE_H
#define IDEVICEMODEHANDLERRESOURCE_H

#include <string>
#include "implementations/CDeviceModeHandlerResourceData.h"
//Header files related to PresCtrl
#include "v1/com/harman/pres/DeviceModeHandlerProxy.hpp"
#include "capi/CAPIClientAbstraction.hpp"

using namespace v1::com::harman::pres;
using namespace std;

/**
 * @interface IDeviceModeHandlerResource
 * @brief     This interface provides functionality that would be implemented to
 *            interact with DeviceModeHandler presctrl and also to provide data
 *            to DeviceModeHandler Adaptor Layer.
 */
class IDeviceModeHandlerResource
{
public:
    /*!
     * @brief   Destructor of IDeviceModeHandlerResource
     * @param   void.
     * @return  void.
     */
    virtual ~IDeviceModeHandlerResource() {}

    /*********************************************************//**
     * @category REQUEST METHODS
     *********************************************************/

private:

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
    virtual void deviceModeHandlerServiceStatusCb(CommonAPI::AvailabilityStatus eStatus) = 0;

    /*!
     * @brief   Callback to get notified about the device insertion.
     * @param   objDeviceInfo - sDeviceInfo object gives device details.
     * @return  void.
     */
    virtual void deviceInsertedCb(const devprestypes::sDeviceInfo &objDeviceInfo) = 0;

    /*!
     * @brief   Callback to get notified about the device removal.
     * @param   uint8_t - uiRemovalStatus device removal.
     * @return  void.
     */
    virtual void deviceRemovedCb(uint8_t uiRemovalStatus) = 0;

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
    virtual void modeStatusCb(uint8_t uiDeviceID, bool bReinsertedNeeded,
                      bool bHasConflictsMode,
                      const vector<devprestypes::sConflictMode> &vectSConflictMode,
                      const devprestypes::sModeInfo &objModeInfo) = 0;

    /*!
     * @brief startModeAsyncCb: Callback function of startMode api
     * @param eCallStatus: callStatus information.
     * @param eAcknowledgement: VALID_INPUT = 0, INVALID_INPUT = 1
     *
     */
    virtual void startModeAsyncCb(const CallStatus &eCallStatus, const devprestypes::eAcknowledgement &eAcknowledgement) = 0;

    /*!
     * @brief   getInsertedDeviceInfoAsyncCb: Callback to get notified about the
     *          device insertion.
     * @param   eCallStatus: Call status.
     * @param   objvDeviceInfo - vDeviceInfo object vector of sDeviceInfo structure
     *           which contains the device details.
     * @return  void.
     */
    virtual void getInsertedDeviceInfoAsyncCb(const CallStatus &eCallStatus, const devprestypes::vDeviceInfo &objvDeviceInfo) = 0;
};

#endif // IDEVICEMODEHANDLERRESOURCE_H
