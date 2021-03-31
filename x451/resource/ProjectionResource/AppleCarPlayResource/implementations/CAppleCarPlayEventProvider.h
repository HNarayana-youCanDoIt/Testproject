/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CAppleCarPlayEventProvider.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* CAppleCarPlayEventProvider, Class to send signals to AppleCarPlay Application
* layer on AppleCarPlay Resource events
*/

#ifndef CAPPLECARPLAYEVENTPROVIDER_H
#define CAPPLECARPLAYEVENTPROVIDER_H

#include <QObject>
#include <QString>

using namespace std;

/**
 * @class CAppleCarPlayEventProvider
 * @brief Class to send signals to AppleCarPlay Application layer on AppleCarPlay
 *        Resource events.
 */
class CAppleCarPlayEventProvider : public QObject
{
    Q_OBJECT

public:
    /**
    * @brief	CAppleCarPlayEventProvider::CAppleCarPlayEventProvider private
    *           constructor for class CAppleCarPlayEventProvider.
    * @param	pParent: parent class pointer.
    * @return	NA.
    **/
    CAppleCarPlayEventProvider(QObject* pParent = nullptr);

    /*!
     * @brief   Destructor of CAppleCarPlayEventProvider
     * @param   void.
     * @return  void.
     */
    ~CAppleCarPlayEventProvider();

    /**
     * @brief updateAppleCarPlayConnectionStatus: This function is used to update
     *        the AppleCarPlay connection status Status.
     * @param bAppleCarPlayConnectionStatus: true if AppleCarPlay connected, else false.
     * @return  void.
     */
    void updateAppleCarPlayConnectionStatus(bool bAppleCarPlayConnectionStatus);

    /**
     * @brief updateAppleCarPlayProjectionStatus: This function is used to update
     *        the AppleCarPlay projection status/Screen Status.
     * @param bAppleCarPlayProjectionStatus: true if AppleCarPlay projection is
     *        projected on HU, else false.
     * @return  void.
     */
    void updateAppleCarPlayProjectionStatus(bool bAppleCarPlayProjectionStatus);

    /**
     * @brief updateAppleCarPlayPhoneStatus: This function is used to update
     *        the AppleCarPlay phone status.
     * @param bAppleCarPlayPhoneStatus: true if AppleCarPlay phone(active call/incoming call) is
     *        projected on HU, else false.
     * @return  void.
     */
    void updateAppleCarPlayPhoneStatus(bool bAppleCarPlayPhoneStatus);

    /**
     * @brief updateCarPlaySiriStatus: This function is used to update
     *        the CarPlay Siri status.
     * @param bCarPlaySiriStatus: true if CarPlay Siri is
     *        active on HU, else false.
     * @return  void.
     */
    void updateCarPlaySiriStatus(bool bCarPlaySiriStatus);

    /**
     * @brief   updateAppleCarPlayDeviceName: This function is used to update
     *          the AppleCarPlay device name.
     * @param   strAppleCarPlayDeviceName: Device name of connected Apple CarPlay
     *          device.
     * @return  void.
     */
    void updateAppleCarPlayDeviceName(const string &strAppleCarPlayDeviceName);

    /**
     * @brief   updateAppleCarPlayRemoteUIStatus: This function is used to update
     *          the AppleCarPlay remote UI status
     * @param   bAppleCarPlayRemoteUIStatus: true if CarPlay is going to auto launch, false otherwise
     * @return  void.
     */
    void updateAppleCarPlayRemoteUIStatus(bool bAppleCarPlayRemoteUIStatus);

    /**
     * @brief   updateCPNowPlayingInfo: This function is called When
     *          CPNowPlayingInfo recieved by CarPlay pres.
     * @param   void.
     * @return  void.
     */
    void updateCPNowPlayingInfo();

    /**
     * @brief  updateSmartFanState: This method updates the smart fan call status to the upper layer.
     * @param  status: Status of the API call, true - success and false - fail.
     * @return void.
     */
    void updateSmartFanState(bool bValue);

    /**
     * @brief  updateCPProxyStatus: This method updates the CP proxy status to upper layer.
     * @param  bCPProxyStatus: CP proxy status, true - available, false - not available.
     * @return void.
     */
    void updateCPProxyStatus(bool bCPProxyStatus);

signals:
    /**
     * @brief   sigUpdateAppleCarPlayConnectionStatus: Signal to notify the Adaptor layer
     *          for the change of Apple CarPlay connection status.
     * @param   bCPConnectionStatus: Apple CarPlay connection status, true if
     *          AppleCarPlay is connected on HU, else false.
     * @return  void.
     */
    void sigUpdateAppleCarPlayConnectionStatus(bool bCPConnectionStatus);

    /**
     * @brief   sigUpdateCPConnectionStatus: Signal to notify the Adaptor layer
     *          for the change of Apple CarPlay projection status.
     * @param   bCPYProjectionStatus: Apple CarPlay projection status, true if
     *          AppleCarPlay projection is on foreground on HU, else false.
     * @return  void.
     */
    void sigUpdateAppleCarPlayProjectionStatus(bool bCPYProjectionStatus);

    /**
     * @brief   sigUpdateAppleCarPlayPhoneStatus: Signal to notify the Adaptor layer
     *          for the change of Apple CarPlay phone status.
     * @param   bAppleCarPlayPhoneStatus: Apple CarPlay phone status, true if
     *          AppleCarPlay phone (active call/incoming call) is on foreground on HU, else false.
     * @return  void.
     */
    void sigUpdateAppleCarPlayPhoneStatus(bool bAppleCarPlayPhoneStatus);

    /**
     * @brief   sigUpdateCarPlaySiriStatus: Signal to notify the Adaptor layer
     *          for the change of CarPlay Siri status.
     * @param   bCarPlaySiriStatus: CarPlay Siri status, true if
     *          CarPlay Siri is on foreground on HU, else false.
     * @return  void.
     */
    void sigUpdateCarPlaySiriStatus(bool bCarPlaySiriStatus);


    /**
     * @brief   sigUpdateAppleCarPlayDeviceName: Signal to notify the Adaptor
     *          layer for the change of AppleCarPlay device name.
     * @param   strAppleCarPlayDeviceName: Device name of connected Apple CarPlay
     *          device.
     * @return  void.
     */
    void sigUpdateAppleCarPlayDeviceName(const QString &strAppleCarPlayDeviceName);

    /**
     * @brief   sigUpdateAppleCarPlayRemoteUIStatus: Signal to notify the Adaptor
     *          layer for the change of AppleCarPlay remote UI status.
     * @param   bAppleCarPlayRemoteUIStatus: true if CarPlay is going to auto launch, false otherwise
     * @return  void.
     */
    void sigUpdateAppleCarPlayRemoteUIStatus(bool bAppleCarPlayRemoteUIStatus);

    /**
     * @brief   sigUpdateCPMediaNowPlayingInfo: This signal will be emitted when,
     *          CPMediaNowPlaying recieved from CP pres.
     * @param   void.
     * @return  void.
     */
    void sigUpdateCPMediaNowPlayingInfo();

    /**
     * @brief  sigUpdateSmartFanState: This signal notifies smart fan call status to upper layer.
     * @param  bCallStatus: Status of the API call, true - success and false - fail.
     * @return void.
     */
    void sigUpdateSmartFanState(bool bCallStatus);

    /**
     * @brief  sigUpdateCPProxyStatus: This signal notifies CP proxy availability status to upper layer.
     * @param  bCPProxyStatus: CP proxy status, true - available, false - not available.
     * @return void.
     */
    void sigUpdateCPProxyStatus(bool bCPProxyStatus);

};

#endif // CAPPLECARPLAYEVENTPROVIDER_H
