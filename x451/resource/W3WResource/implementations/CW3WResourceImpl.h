/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2019
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CW3WResourceImpl.h
* @ingroup      HMIComponent
* @author       Mohit Rajani
* IW3WResource, Resource Implementation for the W3W module. Implements the IW3WResource interface
*/

#ifndef CW3WRESOURCEIMPL_H
#define CW3WRESOURCEIMPL_H

#include "interfaces/IW3WResource.h"
#include "CW3WEventProvider.h"


class CW3WResourceImpl: public IW3WResource
{
public:
    virtual ~CW3WResourceImpl();

    /**
     * @brief getW3WEventProvider: Method to get the instance of the W3W event provider
     * @param void
     * @return the pointer to the W3W event provider
     */
    CW3WEventProvider* getW3WEventProvider();

    /**
     * @brief W3WCoreProxyStatusCb: CallBack method to get notified about the availability status of W3W Core Proxy
     * @param eStatus: status of W3W Core proxy whether available or not
     * @return void
     */
    void W3WCoreProxyStatusCb(CommonAPI::AvailabilityStatus eStatus) override;

    /**
     * @brief W3WPluginProxyStatusCb: CallBack method to get notified about the availability status of W3W Plugin Proxy
     * @param eStatus: status of W3W plugin proxy whether available or not
     * @return void
     */
    void W3WPluginProxyStatusCb(CommonAPI::AvailabilityStatus eStatus) override;

    /**
     * @brief isW3WCoreProxyAvailable: returns the core proxy availability.
     * @param void.
     * @return bool: TRUE- IF proxy is available. FALSE- if proxy is absent.
     */
    bool isW3WCoreProxyAvailable() override { return m_bW3WCoreProxyAvailable; }

    /**
     * @brief isW3WPluginProxyAvailable: returns the plugin proxy availability.
     * @param void.
     * @return bool: TRUE- IF proxy is available. FALSE- if proxy is absent.
     */
    bool isW3WPluginProxyAvailable() override { return m_bW3WPluginProxyAvailable; }

    /**
     * @brief getAutoSuggestionsList
     * @return vector of type struct SSuggestion which has the w3w address suggestion along with metadata
     */
    vector<SSuggestion> getAutoSuggestionsList();

    /**
     * @brief getAutoSuggestions This method will provide three autosuggestion of words for a string input in w3w format
     * @param w3wAddress The three words address in W3W format
     * @return void
     */
    void getAutoSuggestions(string w3wAddress) override;

    /**
     * @brief asyncGetAutoSuggestionsCb callback for the getAutoSuggestions API
     * @param status - API call was successful or failure
     * @param apiStatus - W3W API call was successful or failure
     * @param arrAutoSuggestion for the provide W3W address
     * @return void
     */
    void asyncGetAutoSuggestionsCb(const CommonAPI::CallStatus& status, const w3wTypeCollection::retStatus& apiStatus, const w3wTypeCollection::arSuggtion& arrAutoSuggestion) override;

    /**
     * @brief addToFavoriteList
     * @param addressItem - Address item to be added to favorite list
     * @return void
     */
    void addToFavoriteList(SW3WAddressItem addressItem) override;

    /**
     * @brief editFromFavoriteList This method will edit the W3W address item from the favorite list
     * @param addressItem The W3W address item to be edited from the favorite list
     * @return void
     */
    void editFromFavoriteList(SW3WAddressItem addressItem) override;

    /**
     * @brief asyncFavoriteSavedCb callback for the addToFavoriteList/editFromFavoriteList APIs
     * @param status - API call was successful or failure
     * @param apiStatus - W3W API call was successful or failure
     * @return void
     */
    void asyncFavoriteSavedCb(const CommonAPI::CallStatus& status, const w3wpluginTypeCollection::retStatus& apiStatus) override;

    /**
     * @brief editFromRecentList This method will edit the W3W address item from the recent list
     * @param addressItem The W3W address item to be edited from the recent list
     * @return void
     */
    void editFromRecentList(SW3WAddressItem addressItem) override;

    /**
     * @brief asyncRecentUpdatedCb callback for the editFromRecentList APIs
     * @param status - API call was successful or failure
     * @param apiStatus - W3W API call was successful or failure
     * @return void
     */
    void asyncRecentUpdatedCb(const CommonAPI::CallStatus& status, const w3wpluginTypeCollection::retStatus& apiStatus) override;

    /**
     * @brief deleteFromFavoriteList This method will delete the W3W address item from the favorite list
     * @param addressItem The W3W address item to be deleted from the favorite list
     * @return void
     */
    void deleteFromFavoriteList(SW3WAddressItem addressItem) override;

    /**
     * @brief deleteFromRecentList This method will delete the W3W address item from the recent list
     * @param addressItem The W3W address item to be deleted from the recent list
     * @return void
     */
    void deleteFromRecentList(SW3WAddressItem addressItem) override;

    /**
     * @brief asyncDeleteAddressFromListCb callback for the deleteFromFavoriteList API
     * @param status - API call was successful or failure
     * @param apiStatus - W3W API call was successful or failure
     * @return void
     */
    void asyncDeleteAddressFromListCb(const CommonAPI::CallStatus& status, const w3wpluginTypeCollection::retStatus& apiStatus) override;

    /**
     * @brief getFavoriteAddressList
     * @return vector of type struct SW3WAddressItem which has the w3w favorite address along with metadata
     */
    vector<SW3WAddressItem> getFavoriteAddressList();

    /**
     * @brief getFavoriteAddresses This method will provide the Favorite Addresses
     * @param void
     * @return void
     */
    void getFavoriteAddresses() override;

    /**
     * @brief asyncFavoriteAddressesCb callback for the getFavoriteAddresses API
     * @param status - API call was successful or failure
     * @param apiStatus - W3W API call was successful or failure
     * @param arrFavoriteAddresses - Favorite address list
     * @return void
     */
    void asyncFavoriteAddressesCb(const CommonAPI::CallStatus& status, const w3wpluginTypeCollection::retStatus& apiStatus, const w3wpluginTypeCollection::arAddList& arrFavoriteAddresses) override;

    /**
     * @brief getRecentAddressList
     * @return vector of type struct SW3WAddressItem which has the w3w recent address along with metadata
     */
    vector<SW3WAddressItem> getRecentAddressList();

    /**
     * @brief getRecentAddresses This method will provide the Recent Addresses
     * @param void
     * @return void
     */
    void getRecentAddresses() override;

    /**
     * @brief asyncRecentAddressesCb callback for the getRecentAddresses API
     * @param status - API call was successful or failure
     * @param apiStatus - W3W API call was successful or failure
     * @param arrRecentAddresses - Recent address list
     * @return void
     */
    void asyncRecentAddressesCb(const CommonAPI::CallStatus& status, const w3wpluginTypeCollection::retStatus& apiStatus, const w3wpluginTypeCollection::arAddList& arrRecentAddresses) override;

    /**
     * @brief getLatLong This method will provide latitude and longitiude details of last navigated W3W address
     * @param w3wAddress The three words address in W3W format
     * @return void
     */
    void getLatLong(string w3wAddress) override;

    /**
     * @brief asyncGetLatLongCb callback for the getLatLong API
     * @param status - Comman API call was successful or failure
     * @param apiStatus - W3W API call was successful or failure
     * @param coord - coordinate of the provide W3W address
     * @return void
     */
    void asyncGetLatLongCb(const CommonAPI::CallStatus& status, const w3wTypeCollection::retStatus& apiStatus, const w3wTypeCollection::Coordinates& coord) override;

    /**
     * @brief getW3WAddress This method will provide W3W address for the passed latitude and longitude co-ordinates
     * @param latitude value
     * @param longitude value
     * @return void
     */
    void getW3WAddress(double latitude, double longitude) override;

    /**
     * @brief asyncGetW3WAddressCb callback for the getW3WAddress API
     * @param status - API call was successful or failure
     * @param apiStatus - W3W API call was successful or failure
     * @param w3wAddress - the W3W address for the provide coordinates
     * @return void
     */
    void asyncGetW3WAddressCb(const CommonAPI::CallStatus& status, const w3wTypeCollection::retStatus& apiStatus, const std::string& w3wAddress) override;

    // Interfaces for W3WPlugin
    /**
     * @brief navigateToAddress request w3w service to navigate to the provided w3w address
     * @param addressItem : w3w address item
     * @return void
     */
    void navigateToAddress(SW3WAddressItem addressItem) override;

    /**
     * @brief asyncNavigateToAddressCb callback for the navigateToAddress API
     * @param status - API call was successful or failure
     * @param apiStatus - W3W API call was successful or failure
     * @return void
     */
    void asyncNavigateToAddressCb(const CommonAPI::CallStatus& status, const w3wpluginTypeCollection::retStatus& apiStatus) override;

    /**
     * @brief getconnNextAppStatus getter method to know the status of connectnext app
     * @param void
     * @return void
     */
    void getconnNextAppStatus() override;

    /**
     * @brief asyncGetconnNextAppStatusCb callback for the getconnNextAppStatus API
     * @param status - API call was successful or failure
     * @param connStatus - success if ConnNext link is established, failure if not established
     */
    void asyncGetconnNextAppStatusCb(const CommonAPI::CallStatus& status, const w3wpluginTypeCollection::retStatus& connStatus) override;

    /**
     * @brief getCountryCode getter method to know the country code set by user
     * @param void
     * @return void
     */
    void getCountryCode() override;

    /**
     * @brief asyncGetCountryCodeCb callback for the getCountryCode API
     * @param status - API call was successful or failure
     * @param apiStatus - W3W API call was successful or failure
     * @param countryCode - returns country code set by user
     * @return void
     */
    void asyncGetCountryCodeCb(const CommonAPI::CallStatus& status, const w3wpluginTypeCollection::retStatus& apiStatus, const std::string& countryCode ) override;

    /**
     * @brief setCountryCode setter method for country code set by user
     * @param countryCode : Country code to be set ("IN" for India, "" for All)
     * @return void
     */
    void setCountryCode(const std::string& countryCode) override;

    /**
     * @brief asyncSetCountryCodeCb callback for the setCountryCode API
     * @param status - API call was successful or failure
     * @param countryCode - returns country code set by user
     * @return void
     */
    void asyncSetCountryCodeCb(const CommonAPI::CallStatus &callStatus, const std::string &countryCode ) override;

    /**
     * @brief onGetMapsLaunchStatusEvent method that will be called when the mapsLauchStatus broadcast message is sent by the service
     * @param mapsLaunchStatus - maps have been launched or not (success/failure)
     * @return void
     */
    void onGetMapsLaunchStatusEvent(w3wpluginTypeCollection::retStatus mapsLaunchStatus) override;

    /**
     * @brief asyncGetconnNextAppStatusEvent method that will be called when the connNextAppStatus broadcast message is sent by the service
     * @param connStatus - success if ConnNext link is established, failure if not established
     * @return void
     */
    void onGetconnNextAppStatusEvent(w3wpluginTypeCollection::retStatus connStatus) override;

    /**
     * @brief asyncGetCountryCodeCb method that will be called when the countryCode attribute update is sent by the service
     * @param countryCode - returns country code set by user
     * @return void
     */
    void onGetCountryCodeAttribute(std::string countryCode) override;

private:
    CW3WResourceImpl();

    /**
     * @brief ResourceFactory: Adding ResourceFactory class as friend class so that
     * ResourceFactory shall be able to create the instance of this class.
     */
    friend class ResourceFactory;

    /**
     * @brief m_pW3WEventProvider: Instance of CW3WEventProvider to propogate events to W3W application layer
     */
    CW3WEventProvider* m_pW3WEventProvider;

    /**
     * @brief m_W3WProxy: W3WServiceProxy class object to call W3W Core layer Proxy methods
     */
    CAPIClientAbstraction<what3wordscoreProxy> m_W3WCoreProxy;

    /**
     * @brief m_W3WProxy: W3WServiceProxy class object to call W3W Plugin layer Proxy methods
     */
    CAPIClientAbstraction<what3wordspluginProxy> m_W3WPluginProxy;

    /**
     * @brief m_bW3WProxyAvailable: provides information whether the W3W core proxy is available or not
     */
    bool m_bW3WCoreProxyAvailable;

    /**
     * @brief m_bW3WProxyAvailable: provides information whether the W3W plugin proxy is available or not
     */
    bool m_bW3WPluginProxyAvailable;

    /**
     * @brief m_AutoSuggestionList: stores the autoSuggestionList provided by the resource layer
     */
    vector<SSuggestion> m_AutoSuggestionList;

    /**
     * @brief m_FavoriteList: stores the Favorite Address List provided by the resource layer
     */
    vector<SW3WAddressItem> m_FavoriteAddressList;

    /**
     * @brief m_FavoriteList: stores the Recent Address List provided by the resource layer
     */
    vector<SW3WAddressItem> m_RecentAddressList;
};

#endif // CW3WRESOURCEIMPL_H
