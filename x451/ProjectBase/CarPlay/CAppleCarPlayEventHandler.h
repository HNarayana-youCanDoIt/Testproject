/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CAppleCarPlayEventHandler.h
 * @ingroup       HMIComponent
 * @author        Vishal Chaudhary
 * @brief         This file contains CAppleCarPlayEventHandler class that
 *                implements the slot for the signals emited by AppleCarPlay
 *                resource layer to inform AppleCarPlay adaptor regarding the
 *                updates in AppleCarPlay resource layer.
 */

#ifndef CAPPLECARPLAYEVENTHANDLER_H
#define CAPPLECARPLAYEVENTHANDLER_H

#include <QObject>
#include <string>

using namespace std;

/*!
 * @class CAppleCarPlayEventHandler
 * @brief This class implements the slot for the signals emited by AppleCarPlay
 *        resource layer to inform AppleCarPlay adaptor regarding the updates
 *        in AppleCarPlay resource layer.
 */
class CAppleCarPlayEventHandler: public QObject
{
    Q_OBJECT
public:
    /*!
     * @brief   Constructor of CAppleCarPlayEventHandler
     * @param   pParent: parent class pointer.
     * @return  void.
     */
    CAppleCarPlayEventHandler(QObject* pParent = 0);

    /*!
     * @brief   Destructor of CAppleCarPlayEventHandler
     * @param   void.
     * @return  void.
     */
    ~CAppleCarPlayEventHandler();

signals:

    /**
     * @brief   sigUpdateCPMediaNowPlayingInfo: This signal will be emitted when,
     *          CarPlay Media NowPlaying Info gets changed.
     * @param   void.
     * @return  void.
     */
    void sigUpdateCPMediaNowPlayingInfo();

private slots:
    /********************************************************************//**
     * @category    ANDROID AUTO EVENT HANDLER SLOTS
     * @brief       Slots for the signals emitted by AppleCarPlay resource
     *********************************************************************/

    /*!
     * @brief   Method to notify AppleCarPlay adaptor regarding update of
     *          AppleCarPlay Connection status.
     * @param   bAppleCarPlayConnectionStatus: true if connected else false.
     * @return  void.
     */
    void sltUpdateAppleCarPlayConnectionStatus(bool bAppleCarPlayConnectionStatus);

    /*!
     * @brief   Method to notify AppleCarPlay adaptor regarding update of
     *          AppleCarPlay Projection status.
     * @param   bAppleCarPlayProjectionStatus: true if projected else false.
     * @return  void.
     */
    void sltUpdateAppleCarPlayProjectionStatus(bool bAppleCarPlayProjectionStatus);

    /*!
     * @brief   Method to notify AppleCarPlay adaptor regarding update of
     *          AppleCarPlay Phone status.
     * @param   bAppleCarPlayPhoneStatus: true if phone(active call/incoming call)
     *          active else false.
     * @return  void.
     */
    void sltUpdateAppleCarPlayPhoneStatus(bool bAppleCarPlayPhoneStatus);

    /*!
     * @brief   Method to notify AppleCarPlay adaptor regarding update of
     *          CarPlay Siri status.
     * @param   bCarPlaySiriStatus: true if Siri is active else false.
     * @return  void.
     */
    void sltUpdateCarPlaySiriStatus(bool bCarPlaySiriStatus);

    /*!
     * @brief   Method to notify AppleCarPlay adaptor regarding update of
     *          AppleCarPlay DeviceName.
     * @param   strAppleCarPlayDeviceName: Connected AppleCarPlayDevice Name.
     * @return  void.
     */
    void sltUpdateAppleCarPlayDeviceName(const QString & strAppleCarPlayDeviceName);

    /*!
     * @brief   sltUpdateAppleCarPlayRemoteUIStatus: Method to notify AppleCarPlay adaptor
     *          regarding update of AppleCarPlay Remote UI status.
     * @param   bAppleCarPlayRemoteUIStatus: true if CP is going to auto launch, false otherwise
     * @return  void.
     */
    void sltUpdateAppleCarPlayRemoteUIStatus(bool bAppleCarPlayRemoteUIStatus);

    /**
     * @brief   sltUpdateCPMediaNowPlayingInfo: The slot for sigUpdateCPMediaNowPlayingInfo,
     *          to update CP media nowplaying in CarPlay Adaptor.
     * @param   void.
     * @return  void.
     */
    void sltUpdateCPMediaNowPlayingInfo();

    /**
     * @brief sltUpdateSmartFanState: This slot updates smart fan call status to upper layer.
     * @param bValue: Smart fan state, value holds the Enable state of Fan, like If smart Fan is enabled then true else false.
     * @return void.
     */
    void sltUpdateSmartFanState(bool bValue);

    /**
     * @brief sltUpdateCPProxyStatus: This slot updates CP proxy status to upper layer.
     * @param bCPProxyStatus: CP proxy status, true - available, false - not available.
     * @return void.
     */
    void sltUpdateCPProxyStatus(bool bCPProxyStatus);

private:
    /******************************************************//**
     * @category    INTERNAL METHODS
     *******************************************************/

    /*!
     * @brief   Method to connect signals provided by CAppleCarPlayEventProvider
     *          class with the internal slots.
     * @param   void.
     * @return  void.
     */
    void connectAppleCarPlayEventProviderSignals();

    /*!
     * @brief   Method to disconnect signals provided by
     *          CAppleCarPlayEventProvider class with the internal slots.
     * @param   void.
     * @return  void.
     */
    void disconnectAppleCarPlayEventProviderSignals();

private:

};

#endif // CAPPLECARPLAYEVENTHANDLER_H
