/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CW3WEventHandler.h
 * @ingroup         HMIComponent
 * @author          Nishant Khandagale
 * CW3WEventHandler, a Resource handler for W3W module,
 * CW3WEventHandler act as mediator between adaptor and resource manager.
 * The class listens for the signals raised by the resource layer provider class.
 * It has the implementation of the corresponding slots.
 */

#ifndef CW3WEVENTHANDLER_H
#define CW3WEVENTHANDLER_H

#include <QObject>
#include <string.h>

using namespace std;

/**
 * @brief CW3WHandler, a Resource handler for W3W module,
 * It act as mediator between adaptor and resource manager,
 * This listens signals raised by the resource layer provider class,
 * It has the implementation of the corresponding slots.
 */
class CW3WEventHandler: public QObject
{
    Q_OBJECT
public:
    /**
    * @brief	CW3WEventHandler::CW3WEventHandler constructor for data handler class CW3WEventHandler.
    * @param	QObject.
    * @return	NA.
    **/
    CW3WEventHandler(QObject* parent = 0);

    /**
    * @brief	CW3WEventHandler::~CW3WEventHandler is destructor of data handler class CW3WEventHandler
    * @param	NA.
    * @return	NA.
    **/
    ~CW3WEventHandler();

public slots:

    /**
    * @brief sltUpdateW3WCoreProxyAvailability: informs whether the w3w core proxy is available
    * @param w3wCoreProxyAvailability: W3W core Proxy Status.
    * @return void.
    */
    void sltUpdateW3WCoreProxyAvailability(bool w3wCoreProxyAvailability);

    /**
    * @brief sltUpdateW3WPluginProxyAvailability: informs whether the w3w core proxy is available
    * @param w3wPluginProxyAvailability: W3W plugin Proxy Status.
    * @return void.
    */
    void sltUpdateW3WPluginProxyAvailability(bool w3wPluginProxyAvailability);

    /**
     * @brief sltUpdateAutoSuggestionList provides the auto suggestion list
     * @param void
     * @return void
     */
    void sltUpdateAutoSuggestionList();

    /**
     * @brief sltUpdateFavoriteSavedStatus provides the status of favourite saved status
     * @param favoriteSavedStatus (true : if favorite saved successfully, else false)
     * @return void
     */
    void sltUpdateFavoriteSavedStatus(bool favoriteSavedStatus);

    /**
     * @brief sltUpdateAddressDeletedStatus provides the status of address deleted status
     * @param addressDeletedStatus (true : if deleted successfully, else false)
     * @return void
     */
    void sltUpdateAddressDeletedStatus(bool addressDeletedStatus);

    /**
     * @brief sltUpdateFavoriteAddressList provides the favorite address list
     * @param void
     * @return void
     */
    void sltUpdateFavoriteAddressList();

    /**
     * @brief sltUpdateRecentAddressList provides the recent address list
     * @param void
     * @return void
     */
    void sltUpdateRecentAddressList();

    /**
     * @brief sltUpdateLatLng provides the latitude and longitude of the given w3w address
     * @param lat latitude value
     * @param lng longitude value
     * @void
     */
    void sltUpdateLatLng(double lat, double lng);

    /**
     * @brief sltUpdateW3WAddress provides the w3w address for the given latitude and longitude values
     * @param w3wAddress w3w address
     * @return void
     */
    void sltUpdateW3WAddress(QString w3wAddress);

    /**
     * @brief sltUpdateNavigationStatus inform the navigation status of the last navigate request
     * @param navigationStatus : navigation status of last navigate request (true if successful, else false)
     * @return void
     */
    void sltUpdateNavigationStatus(bool navigationStatus);

    /**
     * @brief sltUpdateConnNextStatus inform the connection state of the connext app
     * @param connStatus conn next connection status
     * @return void
     */
    void sltUpdateConnNextStatus(int connStatus);

    /**
     * @brief sltUpdateCountryCode provide the country code set by the user
     * @param countryCode country code string
     * @return void
     */
    void sltUpdateCountryCode(QString countryCode);

    /**
     * @brief sltUpdateMapsLaunchStatus informs whether the maps was launched by the connect next app
     * @param mapsLaunchStatus (success/failure)
     * @return void
     */
    void sltUpdateMapsLaunchStatus(int mapsLaunchStatus);

private:
    /**
    * @brief	CW3WEventHandler::connectSignals used to create connection for class CW3WEventHandler
    * @param	void.
    * @return	void.
    **/
    void connectSignals();

    /**
    * @brief	CW3WEventHandler::disconnectSignals used to release connection for class CW3WEventHandler
    * @param	void.
    * @return	void.
    **/
    void disconnectSignals();
};
#endif // CW3WEVENTHANDLER_H
