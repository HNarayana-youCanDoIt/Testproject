/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2019
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         IW3WResource.h
* @ingroup      HMIComponent
* @author       Mohit Rajani
* IW3WResource, an interface for the W3W Resource Implementaion in HMI.
*/

#ifndef IW3WRESOURCE_H
#define IW3WRESOURCE_H

#include <QObject>

#include "v0/com/harman/what3words/what3wordscoreProxy.hpp"
#include "v0/com/harman/what3words/what3wordspluginProxy.hpp"
#include <capi/CAPIClientAbstraction.hpp>

#include "implementations/CW3WResourceData.h"

using namespace std;
using namespace ::v0::com::harman::what3words;

/**
 * @interface IW3WResource
 * @brief     This interface provides functionality that would be implemented to interact
 *            with W3W service and also to provide data to W3W Adaptor Layer
 */
class IW3WResource
{
public:
    virtual ~IW3WResource(){}

    /*****  CALL BACK METHODS  ****************************/

    /**
     * @brief W3WCoreProxyStatusCb: CallBack method to get notified about the availability status of W3W Core Proxy
     * @param eStatus: status of W3W Core proxy whether available or not
     * @return void
     */
    virtual void W3WCoreProxyStatusCb(CommonAPI::AvailabilityStatus eStatus) = 0;

    /**
     * @brief W3WPluginProxyStatusCb: CallBack method to get notified about the availability status of W3W Plugin Proxy
     * @param eStatus: status of W3W plugin proxy whether available or not
     * @return void
     */
    virtual void W3WPluginProxyStatusCb(CommonAPI::AvailabilityStatus eStatus) = 0;

    /**
     * @brief isW3WCoreProxyAvailable: returns the core proxy availability.
     * @param void.
     * @return bool: TRUE- IF proxy is available. FALSE- if proxy is absent.
     */
    virtual bool isW3WCoreProxyAvailable() = 0;

    /**
     * @brief isW3WPluginProxyAvailable: returns the plugin proxy availability.
     * @param void.
     * @return bool: TRUE- IF proxy is available. FALSE- if proxy is absent.
     */
    virtual bool isW3WPluginProxyAvailable() = 0;

    /**
     * @brief getAutoSuggestions This method will provide three autosuggestion of words for a string input in w3w format
     * @param w3wAddress The three words address in W3W format
     * @return void
     */
    virtual void getAutoSuggestions(string w3wAddress) = 0;

    /**
     * @brief asyncGetAutoSuggestionsCb callback for the getAutoSuggestions API
     * @param status - API call was successful or failure
     * @param apiStatus - W3W API call was successful or failure
     * @param arrAutoSuggestion for the provide W3W address
     * @return void
     */
    virtual void asyncGetAutoSuggestionsCb(const CommonAPI::CallStatus& status, const w3wTypeCollection::retStatus& apiStatus, const w3wTypeCollection::arSuggtion& arrAutoSuggestion) = 0;

    /**
     * @brief addToFavoriteList This method will add the W3W address item to the favorite
     * @param addressItem The W3W address item to be added to the favorite list
     * @return void
     */
    virtual void addToFavoriteList(SW3WAddressItem addressItem) = 0;

    /**
     * @brief editFromFavoriteList This method will edit the W3W address item from the favorite list
     * @param addressItem The W3W address item to be edited from the favorite list
     * @return void
     */
    virtual void editFromFavoriteList(SW3WAddressItem addressItem) = 0;

    /**
     * @brief asyncFavoriteSavedCb callback for the addToFavoriteList/editFromFavoriteList APIs
     * @param status - API call was successful or failure
     * @param apiStatus - W3W API call was successful or failure
     * @return void
     */
    virtual void asyncFavoriteSavedCb(const CommonAPI::CallStatus& status, const w3wpluginTypeCollection::retStatus& apiStatus) = 0;

    /**
     * @brief editFromRecentList This method will edit the W3W address item from the recent list
     * @param addressItem The W3W address item to be edited from the recent list
     * @return void
     */
    virtual void editFromRecentList(SW3WAddressItem addressItem) = 0;

    /**
     * @brief asyncRecentUpdatedCb callback for the editFromRecentList APIs
     * @param status - API call was successful or failure
     * @param apiStatus - W3W API call was successful or failure
     * @return void
     */
    virtual void asyncRecentUpdatedCb(const CommonAPI::CallStatus& status, const w3wpluginTypeCollection::retStatus& apiStatus) = 0;

    /**
     * @brief deleteFromFavoriteList This method will delete the W3W address item from the favorite list
     * @param addressItem The W3W address item to be deleted from the favorite list
     * @return void
     */
    virtual void deleteFromFavoriteList(SW3WAddressItem addressItem) = 0;

    /**
     * @brief deleteFromRecentList This method will delete the W3W address item from the recent list
     * @param addressItem The W3W address item to be deleted from the recent list
     * @return void
     */
    virtual void deleteFromRecentList(SW3WAddressItem addressItem) = 0;

    /**
     * @brief asyncDeleteAddressFromListCb callback for the deleteFromFavoriteList/deleteFromRecentList API
     * @param status - API call was successful or failure
     * @param apiStatus - W3W API call was successful or failure
     * @return void
     */
    virtual void asyncDeleteAddressFromListCb(const CommonAPI::CallStatus& status, const w3wpluginTypeCollection::retStatus& apiStatus) = 0;

    /**
     * @brief getFavoriteAddresses This method will provide the Favorite Addresses
     * @param void
     * @return void
     */
    virtual void getFavoriteAddresses() = 0;

    /**
     * @brief asyncFavoriteAddressesCb callback for the getFavoriteAddresses API
     * @param status - API call was successful or failure
     * @param apiStatus - W3W API call was successful or failure
     * @param arrFavoriteAddresses - Favorite address list
     * @return void
     */
    virtual void asyncFavoriteAddressesCb(const CommonAPI::CallStatus& status, const w3wpluginTypeCollection::retStatus& apiStatus, const w3wpluginTypeCollection::arAddList& arrFavoriteAddresses) = 0;

    /**
     * @brief getRecentAddresses This method will provide the Recent Addresses
     * @param void
     * @return void
     */
    virtual void getRecentAddresses() = 0;

    /**
     * @brief asyncRecentAddressesCb callback for the getRecentAddresses API
     * @param status - API call was successful or failure
     * @param apiStatus - W3W API call was successful or failure
     * @param arrRecentAddresses - Recent address list
     * @return void
     */
    virtual void asyncRecentAddressesCb(const CommonAPI::CallStatus& status, const w3wpluginTypeCollection::retStatus& apiStatus, const w3wpluginTypeCollection::arAddList& arrRecentAddresses) = 0;


    /**
     * @brief getLatLong This method will provide latitude and longitiude details of last navigated W3W address
     * @param w3wAddress The three words address in W3W format
     * @return void
     */
    virtual void getLatLong(string w3wAddress) = 0;

    /**
     * @brief asyncGetLatLongCb callback for the getLatLong API
     * @param status - Comman API call was successful or failure
     * @param apiStatus - W3W API call was successful or failure
     * @param coord - coordinate of the provide W3W address
     * @return void
     */
    virtual void asyncGetLatLongCb(const CommonAPI::CallStatus& status, const w3wTypeCollection::retStatus& apiStatus, const w3wTypeCollection::Coordinates& coord) = 0;

    /**
     * @brief getW3WAddress This method will provide W3W address for the passed latitude and longitude co-ordinates
     * @param latitude value
     * @param longitude value
     * @return void
     */
    virtual void getW3WAddress(double latitude, double longitude) = 0;

    /**
     * @brief asyncGetW3WAddressCb callback for the getW3WAddress API
     * @param status - API call was successful or failure
     * @param apiStatus - W3W API call was successful or failure
     * @param w3wAddress - the W3W address for the provide coordinates
     * @return void
     */
    virtual void asyncGetW3WAddressCb(const CommonAPI::CallStatus& status, const w3wTypeCollection::retStatus& apiStatus, const std::string& w3wAddress) = 0;

    // Interfaces for W3WPlugin
    /**
     * @brief navigateToAddress request w3w service to navigate to the provided w3w address
     * @param addressItem : w3w address item
     * @return void
     */
    virtual void navigateToAddress(SW3WAddressItem addressItem) = 0;

    /**
     * @brief asyncNavigateToAddressCb callback for the navigateToAddress API
     * @param status - API call was successful or failure
     * @param apiStatus - W3W API call was successful or failure
     * @return void
     */
    virtual void asyncNavigateToAddressCb(const CommonAPI::CallStatus& status, const w3wpluginTypeCollection::retStatus& apiStatus) = 0;

    /**
     * @brief getconnNextAppStatus getter method to know the status of connectnext app
     * @param void
     * @return void
     */
    virtual void getconnNextAppStatus() = 0;

    /**
     * @brief asyncGetconnNextAppStatusCb callback for the getconnNextAppStatus API
     * @param status - API call was successful or failure
     * @param connStatus - success if ConnNext link is established, failure if not established
     * @return void
     */
    virtual void asyncGetconnNextAppStatusCb(const CommonAPI::CallStatus& status, const w3wpluginTypeCollection::retStatus& connStatus) = 0;

    /**
     * @brief getCountryCode getter method to know the country code set by user
     * @param void
     * @return void
     */
    virtual void getCountryCode() = 0;

    /**
     * @brief asyncGetCountryCodeCb callback for the getCountryCode API
     * @param status - API call was successful or failure
     * @param apiStatus - W3W API call was successful or failure
     * @param countryCode - returns country code set by user
     * @return void
     */
    virtual void asyncGetCountryCodeCb(const CommonAPI::CallStatus& status, const w3wpluginTypeCollection::retStatus& apiStatus, const std::string& countryCode ) = 0;

    /**
     * @brief setCountryCode setter method for country code set by user
     * @param countryCode : Country code to be set ("IN" for India, "" for All)
     * @return void
     */
    virtual void setCountryCode(const std::string& countryCode) = 0;

    /**
     * @brief asyncSetCountryCodeCb callback for the setCountryCode API
     * @param status - API call was successful or failure
     * @param countryCode - returns country code set by user
     * @return void
     */
    virtual void asyncSetCountryCodeCb(const CommonAPI::CallStatus &callStatus, const std::string &countryCode ) = 0;


    /**
     * @brief onGetMapsLaunchStatusEvent method that will be called when the mapsLauchStatus broadcast message is sent by the service
     * @param mapsLaunchStatus - maps have been launched or not (success/failure)
     * @return void
     */
    virtual void onGetMapsLaunchStatusEvent(w3wpluginTypeCollection::retStatus mapsLaunchStatus) = 0;

    /**
     * @brief asyncGetconnNextAppStatusEvent method that will be called when the connNextAppStatus broadcast message is sent by the service
     * @param connStatus - success if ConnNext link is established, failure if not established
     * @return void
     */
    virtual void onGetconnNextAppStatusEvent(w3wpluginTypeCollection::retStatus connStatus) = 0;

    /**
     * @brief asyncGetCountryCodeCb method that will be called when the countryCode attribute update is sent by the service
     * @param countryCode - returns country code set by user
     * @return void
     */
    virtual void onGetCountryCodeAttribute(std::string countryCode) = 0;

};

#endif // IW3WRESOURCE_H
