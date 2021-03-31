/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2019
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CW3WEventProvider.h
* @ingroup      HMIComponent
* @author       Mohit Rajani
* CW3WEventProvider, class to propogate events from resource layer to the W3W Application layer
*/

#ifndef CW3WEVENTPROVIDER_H
#define CW3WEVENTPROVIDER_H

#include <QObject>
#include <string.h>

using namespace std;

/**
 * @brief The CW3WEventProvider, class to propogate events for resource layer to the W3W Application layer
 */
class CW3WEventProvider: public QObject
{
    Q_OBJECT

public:
    /**
     * @brief CW3WEventProvider: Constructor
     * @param pParent: parent object instance
     */
    CW3WEventProvider(QObject* pParent = nullptr);

    /**
     * @brief ~CW3WEventProvider: Destructor
     */
    ~CW3WEventProvider();

    /**
     * @brief updateW3WCoreProxyAvailability: Function which will send signal for the w3w core proxy availability status
     * @param bW3WCoreProxyAvailability: w3w core proxy availability status
     * @return void
     */
    void updateW3WCoreProxyAvailability(bool bW3WCoreProxyAvailability);

    /**
     * @brief updateW3WPluginProxyAvailability: Function which will send signal for the w3w plugin proxy availability status
     * @param bW3WPluginProxyAvailability: plugin proxy availability status
     * @return void
     */
    void updateW3WPluginProxyAvailability(bool bW3WPluginProxyAvailability);

    /**
     * @brief updateAutoSuggetionList: Function which will send signal to application about update in auto suggestion list
     * @param void
     * @return void
     */
    void updateAutoSuggetionList();

    /**
     * @brief updateFavoriteSavedStatus: Function which will send signal to application about update in favorite item updation
     * @param favoriteSavedStatus (true : if favorite saved successfully, else false)
     * @return void
     */
    void updateFavoriteSavedStatus(bool favoriteSavedStatus);

    /**
     * @brief updateAddressDeletedStatus: Function which will send signal to application about update in favorite item deletion
     * @param addressDeletedStatus (true : if deleted successfully, else false)
     * @return void
     */
    void updateAddressDeletedStatus(bool addressDeletedStatus);

    /**
     * @brief updateFavoriteAddressList: Function which will send signal to application about update in favorite address list
     * @param void
     * @return void
     */
    void updateFavoriteAddressList();

    /**
     * @brief updateRecentAddressList: Function which will send signal to application about update in recent address list
     * @param void
     * @return void
     */
    void updateRecentAddressList();

    /**
     * @brief updateLatLng update lat lng coordinates
     * @param latittude lattitude value
     * @param longitude longitude value
     * @return void
     */
    void updateLatLng(double latittude, double longitude);

    /**
     * @brief updateW3wAddress update the w3w address
     * @param w3wAddress address provided by service
     * @return void
     */
    void updateW3WAddress(std::string w3wAddress);

    /**
     * @brief updateNavigationStatus update the Navigation status
     * @param status
     * @return void
     */
    void updateNavigationStatus(bool navigationStatus);

    /**
     * @brief updateConnNextStatus update the connnext connection status
     * @param status
     * @return void
     */
    void updateConnNextStatus(int connStatus);

    /**
     * @brief updateCountryCode update the country code
     * @param countryCode country code set by the user
     * @return void
     */
    void updateCountryCode(std::string countryCode);

    /**
     * @brief updateMapsLaunchStatus update the mapsLaunchStatus
     * @param mapsLaunchStatus maps launch status (success/failure)
     * @return void
     */
    void updateMapsLaunchStatus(int mapsLaunchStatus);

signals:

    /**
     * @brief sigUpdateW3WCoreProxyAvailability: Signal for the w3w core proxy availability status
     * @param bW3WCoreProxyAvailability: core proxy availability status
     * @return void
     */
    void sigUpdateW3WCoreProxyAvailability(bool bW3WCoreProxyAvailability);

    /**
     * @brief sigUpdateW3WPluginProxyAvailability: Signal for the w3w plugin proxy availability status
     * @param bW3WPluginProxyAvailability: plugin proxy availability status
     * @return void
     */
    void sigUpdateW3WPluginProxyAvailability(bool bW3WPluginProxyAvailability);

    /**
     * @brief sigUpdateAutoSuggestionList: Signal to inform upper layer there is an update in the auto suggestion list
     * @param void
     * @return void
     */
    void sigUpdateAutoSuggestionList();

    /**
     * @brief sigUpdateFavoriteSavedStatus: Signal to inform upper layer there is an update in the favorite saved status
     * @param favoriteSavedStatus (true : if favorite saved successfully, else false)
     * @return void
     */
    void sigUpdateFavoriteSavedStatus(bool favoriteSavedStatus);

    /**
     * @brief sigUpdateAddressDeletedStatus: Signal to inform upper layer there is an update in the address deleted status
     * @param addressDeletedStatus (true : if deleted successfully, else false)
     * @return void
     */
    void sigUpdateAddressDeletedStatus(bool addressDeletedStatus);

    /**
     * @brief sigUpdateFavoriteAddressList: Signal to inform upper layer there is an update in the favorite address list
     * @param void
     * @return void
     */
    void sigUpdateFavoriteAddressList();

    /**
     * @brief sigUpdateRecentAddressList: Signal to inform upper layer there is an update in the recent address list
     * @param void
     * @return void
     */
    void sigUpdateRecentAddressList();

    /**
     * @brief sigUpdateLatLng: Signal to inform upper layer there is an update lat lng coordinates
     * @param lat lattitude value
     * @param lng longitude value
     * @return void
     */
    void sigUpdateLatLng(double lat, double lng);

    /**
     * @brief sigUpdateW3WAddress: Signal to inform upper layer there is an update in the w3w address
     * @param w3wAddress address provided by service on getW3WAddress API call
     * @return void
     */
    void sigUpdateW3WAddress(QString w3wAddress);

    /**
     * @brief sigUpdateNavigationStatus: Signal to inform upper layer there is an update in the navigation status
     * @param navigationStatus: navigation Status (true: if navigation is successful, else false)
     * @return void
     */
    void sigUpdateNavigationStatus(bool navigationStatus);

    /**
     * @brief sigUpdateConnNextStatus: Signal to inform upper layer there is an update in the conn next connection status
     * @param connStatus conn next connection status
     * @return void
     */
    void sigUpdateConnNextStatus(int connStatus);

    /**
     * @brief sigUpdateCountryCode: Signal to inform upper layer there is an update in the country code
     * @param countryCode country code
     * @return void
     */
    void sigUpdateCountryCode(QString countryCode);

    /**
     * @brief sigUpdateMapsLaunchStatus: Signal to inform upper layer there is an update in maps launch status
     * @param mapsLaunchStatus maps launch status (success/failure)
     * @return void
     */
    void sigUpdateMapsLaunchStatus(int mapsLaunchStatus);

};

#endif // CW3WEVENTPROVIDER_H
