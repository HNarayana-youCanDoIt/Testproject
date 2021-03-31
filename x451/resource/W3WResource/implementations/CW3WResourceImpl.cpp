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

#include "CW3WResourceImpl.h"
#include <ResourceMaster.h>
#include "logging.h"
#include "ResourceDeploymentConfig.h"

CW3WResourceImpl::CW3WResourceImpl():
    m_pW3WEventProvider(new CW3WEventProvider())
  , m_W3WCoreProxy(ResourceDeploymentConfig::getConfig().m_W3WCore_Proxy.domain,ResourceDeploymentConfig::getConfig().m_W3WCore_Proxy.instance)
  , m_W3WPluginProxy(ResourceDeploymentConfig::getConfig().m_W3WPlugin_Proxy.domain,ResourceDeploymentConfig::getConfig().m_W3WPlugin_Proxy.instance)
  , m_bW3WCoreProxyAvailable(false)
  , m_bW3WPluginProxyAvailable(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    m_AutoSuggestionList.clear();
    m_FavoriteAddressList.clear();
    m_RecentAddressList.clear();

    // These SUBSCRIBE calls are not working properly on windows simulation
    SUBSCRIBE(m_W3WCoreProxy, getProxyStatusEvent(), &CW3WResourceImpl::W3WCoreProxyStatusCb, _1);
    SUBSCRIBE(m_W3WPluginProxy, getProxyStatusEvent(), &CW3WResourceImpl::W3WPluginProxyStatusCb, _1);

#ifndef PLATFORM_WIN32
    SUBSCRIBE(m_W3WPluginProxy, getMapsLaunchStatusEvent(), &CW3WResourceImpl::onGetMapsLaunchStatusEvent, _1);
    SUBSCRIBE(m_W3WPluginProxy, getConnNextAppStatusEvent(), &CW3WResourceImpl::onGetconnNextAppStatusEvent, _1);
#endif

    SUBSCRIBE(m_W3WPluginProxy, getCountryCodeAttribute().getChangedEvent(), &CW3WResourceImpl::onGetCountryCodeAttribute, _1);
}

CW3WResourceImpl::~CW3WResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);

    if (m_pW3WEventProvider)
    {
        delete m_pW3WEventProvider;
        m_pW3WEventProvider = nullptr;
    }
}

CW3WEventProvider* CW3WResourceImpl::getW3WEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    return m_pW3WEventProvider;
}

void CW3WResourceImpl::W3WCoreProxyStatusCb(AvailabilityStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, W3W proxy status : %d", __FUNCTION__, static_cast<int>(eStatus));

    if(CommonAPI::AvailabilityStatus::AVAILABLE == eStatus)
    {
        m_bW3WCoreProxyAvailable = true;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, W3W core service NOT AVAILABLE",__FUNCTION__);
        m_bW3WCoreProxyAvailable = false;
    }

    if(m_pW3WEventProvider)
    {
        m_pW3WEventProvider->updateW3WCoreProxyAvailability(m_bW3WCoreProxyAvailable);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, m_pW3WEventProvider not available", __FUNCTION__);
    }
}


void CW3WResourceImpl::W3WPluginProxyStatusCb(AvailabilityStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, W3W proxy status : %d", __FUNCTION__, static_cast<int>(eStatus));

    if(CommonAPI::AvailabilityStatus::AVAILABLE == eStatus)
    {
        m_bW3WPluginProxyAvailable = true;
        getconnNextAppStatus();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, W3W plugin service NOT AVAILABLE",__FUNCTION__);
        m_bW3WPluginProxyAvailable = false;
    }

    if(m_pW3WEventProvider)
    {
        m_pW3WEventProvider->updateW3WPluginProxyAvailability(m_bW3WPluginProxyAvailable);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, m_pW3WEventProvider not available", __FUNCTION__);
    }
}

vector<SSuggestion> CW3WResourceImpl::getAutoSuggestionsList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    return m_AutoSuggestionList;
}

void CW3WResourceImpl::getAutoSuggestions(string w3wAddress)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, w3wAddress: %s", __FUNCTION__, w3wAddress.c_str());

    if(m_bW3WCoreProxyAvailable)
    {
        m_W3WCoreProxy->getAutoSuggestionsAsync(w3wAddress, std::bind(&CW3WResourceImpl::asyncGetAutoSuggestionsCb,this, _1, _2, _3));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, W3W proxy not available", __FUNCTION__);
    }

}

void CW3WResourceImpl::asyncGetAutoSuggestionsCb(const CommonAPI::CallStatus& status, const w3wTypeCollection::retStatus& apiStatus, const w3wTypeCollection::arSuggtion& arrAutoSuggestion)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, status: %d, apiStatus: %d, arrAutoSuggestion.size:%zd", __FUNCTION__,
             static_cast<int>(status), static_cast<int>(apiStatus), arrAutoSuggestion.size());
    m_AutoSuggestionList.clear();

    w3wTypeCollection::Suggestion suggestion;
    foreach (suggestion, arrAutoSuggestion)
    {
        SSuggestion autoSuggestion;
        autoSuggestion.m_w3wAddress = suggestion.getThree_word_address();
        autoSuggestion.m_languageCode = suggestion.getLanguage_code();
        autoSuggestion.m_countryCode = suggestion.getCountry_code();
        autoSuggestion.m_nearestPlace = suggestion.getNearest_place();
        m_AutoSuggestionList.push_back(autoSuggestion);
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, w3wAddress: %s, languageCode: %s, countryCode: %s, nearestPlace: %s ", __FUNCTION__,
                 autoSuggestion.m_w3wAddress.c_str(), autoSuggestion.m_languageCode.c_str(),
                 autoSuggestion.m_countryCode.c_str(), autoSuggestion.m_nearestPlace.c_str());
    }

    if (nullptr != m_pW3WEventProvider)
    {
        m_pW3WEventProvider->updateAutoSuggetionList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, m_pW3WEventProvider not available", __FUNCTION__);
    }
}

void CW3WResourceImpl::addToFavoriteList(SW3WAddressItem addressItem)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s m_w3wAddress: %s m_languageCode: %s m_countryCode: %s m_nearestPlace: %s m_w3wAddressLabel: %s m_w3wAddressUID: %d",
             __FUNCTION__, addressItem.m_w3wAddress.c_str(), addressItem.m_languageCode.c_str(), addressItem.m_countryCode.c_str(),
             addressItem.m_nearestPlace.c_str(), addressItem.m_w3wAddressLabel.c_str(), addressItem.m_w3wAddressUID);

    if(m_bW3WPluginProxyAvailable)
    {
        w3wpluginTypeCollection::arAddList favoriteAddressList;
        w3wpluginTypeCollection::AddressList favoriteAddressItem;
        favoriteAddressItem.setThree_word_address(addressItem.m_w3wAddress);
        favoriteAddressItem.setLanguage_code(addressItem.m_languageCode);
        favoriteAddressItem.setCountry_code(addressItem.m_countryCode);
        favoriteAddressItem.setNearest_place(addressItem.m_nearestPlace);
        favoriteAddressItem.setLabel(addressItem.m_w3wAddressLabel);

        favoriteAddressList.clear();
        favoriteAddressList.push_back(favoriteAddressItem);

        m_W3WPluginProxy->addW3WAddressToListAsync( w3wpluginTypeCollection::listType::FAVOURITE, favoriteAddressList,
                                                    std::bind(&CW3WResourceImpl::asyncFavoriteSavedCb, this, _1, _2) );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, W3W proxy not available", __FUNCTION__);
    }
}

void CW3WResourceImpl::editFromFavoriteList(SW3WAddressItem addressItem)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s m_w3wAddress: %s m_languageCode: %s m_countryCode: %s m_nearestPlace: %s m_w3wAddressLabel: %s m_w3wAddressUID: %d",
             __FUNCTION__, addressItem.m_w3wAddress.c_str(), addressItem.m_languageCode.c_str(), addressItem.m_countryCode.c_str(),
             addressItem.m_nearestPlace.c_str(), addressItem.m_w3wAddressLabel.c_str(), addressItem.m_w3wAddressUID);

    if(m_bW3WPluginProxyAvailable)
    {
        w3wpluginTypeCollection::arAddList favoriteAddressList;
        w3wpluginTypeCollection::AddressList favoriteAddressItem;
        favoriteAddressItem.setUID(addressItem.m_w3wAddressUID);
        favoriteAddressItem.setThree_word_address(addressItem.m_w3wAddress);
        favoriteAddressItem.setLanguage_code(addressItem.m_languageCode);
        favoriteAddressItem.setCountry_code(addressItem.m_countryCode);
        favoriteAddressItem.setNearest_place(addressItem.m_nearestPlace);
        favoriteAddressItem.setLabel(addressItem.m_w3wAddressLabel);

        favoriteAddressList.clear();
        favoriteAddressList.push_back(favoriteAddressItem);

        m_W3WPluginProxy->editW3WAddressfromListAsync( w3wpluginTypeCollection::listType::FAVOURITE, favoriteAddressList,
                                                    std::bind(&CW3WResourceImpl::asyncFavoriteSavedCb, this, _1, _2) );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, W3W proxy not available", __FUNCTION__);
    }
}

void CW3WResourceImpl::asyncFavoriteSavedCb(const CommonAPI::CallStatus& status, const w3wpluginTypeCollection::retStatus& apiStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, status: %d, apiStatus: %d", __FUNCTION__,
             static_cast<int>(status), static_cast<int>(apiStatus));

    if (nullptr != m_pW3WEventProvider)
    {
        m_pW3WEventProvider->updateFavoriteSavedStatus(w3wpluginTypeCollection::retStatus::SUCCESS == apiStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, m_pW3WEventProvider not available", __FUNCTION__);
    }
}

void CW3WResourceImpl::editFromRecentList(SW3WAddressItem addressItem)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s m_w3wAddress: %s m_languageCode: %s m_countryCode: %s m_nearestPlace: %s m_w3wAddressLabel: %s m_w3wAddressUID: %d",
             __FUNCTION__, addressItem.m_w3wAddress.c_str(), addressItem.m_languageCode.c_str(), addressItem.m_countryCode.c_str(),
             addressItem.m_nearestPlace.c_str(), addressItem.m_w3wAddressLabel.c_str(), addressItem.m_w3wAddressUID);

    if(m_bW3WPluginProxyAvailable)
    {
        w3wpluginTypeCollection::arAddList recentAddressList;
        w3wpluginTypeCollection::AddressList recentAddressItem;
        recentAddressItem.setUID(addressItem.m_w3wAddressUID);
        recentAddressItem.setThree_word_address(addressItem.m_w3wAddress);
        recentAddressItem.setLanguage_code(addressItem.m_languageCode);
        recentAddressItem.setCountry_code(addressItem.m_countryCode);
        recentAddressItem.setNearest_place(addressItem.m_nearestPlace);
        recentAddressItem.setLabel(addressItem.m_w3wAddressLabel);

        recentAddressList.clear();
        recentAddressList.push_back(recentAddressItem);

        m_W3WPluginProxy->editW3WAddressfromListAsync( w3wpluginTypeCollection::listType::RECENT, recentAddressList,
                                                    std::bind(&CW3WResourceImpl::asyncRecentUpdatedCb, this, _1, _2) );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, W3W proxy not available", __FUNCTION__);
    }
}

void CW3WResourceImpl::asyncRecentUpdatedCb(const CommonAPI::CallStatus& status, const w3wpluginTypeCollection::retStatus& apiStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, status: %d, apiStatus: %d", __FUNCTION__,
             static_cast<int>(status), static_cast<int>(apiStatus));
}

void CW3WResourceImpl::deleteFromFavoriteList(SW3WAddressItem addressItem)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s m_w3wAddress: %s m_languageCode: %s m_countryCode: %s m_nearestPlace: %s m_w3wAddressLabel: %s m_w3wAddressUID: %d",
             __FUNCTION__, addressItem.m_w3wAddress.c_str(), addressItem.m_languageCode.c_str(), addressItem.m_countryCode.c_str(),
             addressItem.m_nearestPlace.c_str(), addressItem.m_w3wAddressLabel.c_str(), addressItem.m_w3wAddressUID);

    if(m_bW3WPluginProxyAvailable)
    {
        w3wpluginTypeCollection::arAddList favoriteAddressList;
        w3wpluginTypeCollection::AddressList favoriteAddressItem;
        favoriteAddressItem.setUID(addressItem.m_w3wAddressUID);
        favoriteAddressItem.setThree_word_address(addressItem.m_w3wAddress);
        favoriteAddressItem.setLanguage_code(addressItem.m_languageCode);
        favoriteAddressItem.setCountry_code(addressItem.m_countryCode);
        favoriteAddressItem.setNearest_place(addressItem.m_nearestPlace);
        favoriteAddressItem.setLabel(addressItem.m_w3wAddressLabel);

        favoriteAddressList.clear();
        favoriteAddressList.push_back(favoriteAddressItem);

        m_W3WPluginProxy->deleteW3WAddressfromListAsync( w3wpluginTypeCollection::listType::FAVOURITE, favoriteAddressList,
                                                    std::bind(&CW3WResourceImpl::asyncDeleteAddressFromListCb, this, _1, _2) );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, W3W proxy not available", __FUNCTION__);
    }
}

void CW3WResourceImpl::deleteFromRecentList(SW3WAddressItem addressItem)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s m_w3wAddress: %s m_languageCode: %s m_countryCode: %s m_nearestPlace: %s m_w3wAddressLabel: %s m_w3wAddressUID: %d",
             __FUNCTION__, addressItem.m_w3wAddress.c_str(), addressItem.m_languageCode.c_str(), addressItem.m_countryCode.c_str(),
             addressItem.m_nearestPlace.c_str(), addressItem.m_w3wAddressLabel.c_str(), addressItem.m_w3wAddressUID);

    if(m_bW3WPluginProxyAvailable)
    {
        w3wpluginTypeCollection::arAddList recentAddressList;
        w3wpluginTypeCollection::AddressList recentAddressItem;
        recentAddressItem.setUID(addressItem.m_w3wAddressUID);
        recentAddressItem.setThree_word_address(addressItem.m_w3wAddress);
        recentAddressItem.setLanguage_code(addressItem.m_languageCode);
        recentAddressItem.setCountry_code(addressItem.m_countryCode);
        recentAddressItem.setNearest_place(addressItem.m_nearestPlace);
        recentAddressItem.setLabel(addressItem.m_w3wAddressLabel);

        recentAddressList.clear();
        recentAddressList.push_back(recentAddressItem);

        m_W3WPluginProxy->deleteW3WAddressfromListAsync( w3wpluginTypeCollection::listType::RECENT, recentAddressList,
                                                    std::bind(&CW3WResourceImpl::asyncDeleteAddressFromListCb, this, _1, _2) );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, W3W proxy not available", __FUNCTION__);
    }
}

void CW3WResourceImpl::asyncDeleteAddressFromListCb(const CommonAPI::CallStatus& status, const w3wpluginTypeCollection::retStatus& apiStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, status: %d, apiStatus: %d", __FUNCTION__,
             static_cast<int>(status), static_cast<int>(apiStatus));

    if (nullptr != m_pW3WEventProvider)
    {
        m_pW3WEventProvider->updateAddressDeletedStatus(w3wpluginTypeCollection::retStatus::SUCCESS == apiStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, m_pW3WEventProvider not available", __FUNCTION__);
    }
}

vector<SW3WAddressItem> CW3WResourceImpl::getFavoriteAddressList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    return m_FavoriteAddressList;
}

void CW3WResourceImpl::getFavoriteAddresses()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);

    if(m_bW3WPluginProxyAvailable)
    {
        m_W3WPluginProxy->getW3WAddressListAsync( w3wpluginTypeCollection::listType::FAVOURITE, std::bind(&CW3WResourceImpl::asyncFavoriteAddressesCb, this, _1, _2, _3) );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, W3W proxy not available", __FUNCTION__);
    }
}

void CW3WResourceImpl::asyncFavoriteAddressesCb(const CommonAPI::CallStatus& status, const w3wpluginTypeCollection::retStatus& apiStatus, const w3wpluginTypeCollection::arAddList& arrFavoriteAddresses)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, status: %d, apiStatus: %d, arrFavoriteAddresses.size:%zd", __FUNCTION__,
             static_cast<int>(status), static_cast<int>(apiStatus), arrFavoriteAddresses.size());
    m_FavoriteAddressList.clear();

    w3wpluginTypeCollection::AddressList favoriteAddress;
    foreach (favoriteAddress, arrFavoriteAddresses)
    {
        SW3WAddressItem favoriteAddressItem;
        favoriteAddressItem.m_w3wAddress = favoriteAddress.getThree_word_address();
        favoriteAddressItem.m_languageCode = favoriteAddress.getLanguage_code();
        favoriteAddressItem.m_countryCode = favoriteAddress.getCountry_code();
        favoriteAddressItem.m_nearestPlace = favoriteAddress.getNearest_place();
        favoriteAddressItem.m_w3wAddressLabel = favoriteAddress.getLabel();
        favoriteAddressItem.m_w3wAddressUID = favoriteAddress.getUID();

        m_FavoriteAddressList.push_back(favoriteAddressItem);
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, w3wAddress: %s, languageCode: %s, countryCode: %s, nearestPlace: %s label: %s UID: %d", __FUNCTION__,
                 favoriteAddressItem.m_w3wAddress.c_str(), favoriteAddressItem.m_languageCode.c_str(), favoriteAddressItem.m_countryCode.c_str(),
                 favoriteAddressItem.m_nearestPlace.c_str(), favoriteAddressItem.m_w3wAddressLabel.c_str(), favoriteAddressItem.m_w3wAddressUID );
    }

    if (nullptr != m_pW3WEventProvider)
    {
        m_pW3WEventProvider->updateFavoriteAddressList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, m_pW3WEventProvider not available", __FUNCTION__);
    }
}

vector<SW3WAddressItem> CW3WResourceImpl::getRecentAddressList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    return m_RecentAddressList;
}

void CW3WResourceImpl::getRecentAddresses()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);

    if(m_bW3WPluginProxyAvailable)
    {
        m_W3WPluginProxy->getW3WAddressListAsync( w3wpluginTypeCollection::listType::RECENT, std::bind(&CW3WResourceImpl::asyncRecentAddressesCb, this, _1, _2, _3) );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, W3W proxy not available", __FUNCTION__);
    }
}

void CW3WResourceImpl::asyncRecentAddressesCb(const CommonAPI::CallStatus& status, const w3wpluginTypeCollection::retStatus& apiStatus, const w3wpluginTypeCollection::arAddList& arrRecentAddresses)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, status: %d, apiStatus: %d, arrRecentAddresses.size:%zd", __FUNCTION__,
             static_cast<int>(status), static_cast<int>(apiStatus), arrRecentAddresses.size());
    m_RecentAddressList.clear();

    w3wpluginTypeCollection::AddressList recentAddress;
    foreach (recentAddress, arrRecentAddresses)
    {
        SW3WAddressItem recentAddressItem;
        recentAddressItem.m_w3wAddress = recentAddress.getThree_word_address();
        recentAddressItem.m_languageCode = recentAddress.getLanguage_code();
        recentAddressItem.m_countryCode = recentAddress.getCountry_code();
        recentAddressItem.m_nearestPlace = recentAddress.getNearest_place();
        recentAddressItem.m_w3wAddressLabel = recentAddress.getLabel();
        recentAddressItem.m_w3wAddressUID = recentAddress.getUID();

        m_RecentAddressList.push_back(recentAddressItem);
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, w3wAddress: %s, languageCode: %s, countryCode: %s, nearestPlace: %s label: %s UID: %d", __FUNCTION__,
                 recentAddressItem.m_w3wAddress.c_str(), recentAddressItem.m_languageCode.c_str(), recentAddressItem.m_countryCode.c_str(),
                 recentAddressItem.m_nearestPlace.c_str(), recentAddressItem.m_w3wAddressLabel.c_str(), recentAddressItem.m_w3wAddressUID );
    }

    if (nullptr != m_pW3WEventProvider)
    {
        m_pW3WEventProvider->updateRecentAddressList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, m_pW3WEventProvider not available", __FUNCTION__);
    }
}

void CW3WResourceImpl::getLatLong(string w3wAddress)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, w3wAddress: %s", __FUNCTION__, w3wAddress.c_str());

    if(m_bW3WCoreProxyAvailable)
    {
        m_W3WCoreProxy->getLatLongAsync(w3wAddress, std::bind(&CW3WResourceImpl::asyncGetLatLongCb,this, _1, _2, _3));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, W3W proxy not available", __FUNCTION__);
    }

}

void CW3WResourceImpl::asyncGetLatLongCb(const CommonAPI::CallStatus& status, const w3wTypeCollection::retStatus& apiStatus, const w3wTypeCollection::Coordinates& coord)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, status: %d, apiStatus:: %d, latitude is: %f, longitude is: %f", __FUNCTION__,
             static_cast<int>(status), static_cast<int>(apiStatus), coord.getLat(), coord.getLng());
    if (nullptr != m_pW3WEventProvider)
    {
        m_pW3WEventProvider->updateLatLng(coord.getLat(), coord.getLng());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, m_pW3WEventProvider not available", __FUNCTION__);
    }
}

void CW3WResourceImpl::getW3WAddress(double latitude, double longitude)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, latitude is: %f, longitude is: %f", __FUNCTION__, latitude, longitude);

    if(m_bW3WCoreProxyAvailable)
    {
        w3wTypeCollection::Coordinates coord;
        coord.setLat(latitude);
        coord.setLng(longitude);
        m_W3WCoreProxy->getW3WAddressAsync(coord, std::bind(&CW3WResourceImpl::asyncGetW3WAddressCb,this, _1, _2, _3));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, W3W proxy not available", __FUNCTION__);
    }

}

void CW3WResourceImpl::asyncGetW3WAddressCb(const CommonAPI::CallStatus& status, const w3wTypeCollection::retStatus& apiStatus, const std::string& w3wAddress)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, status: %d, apiStatus:: %d, w3wAddress: %s", __FUNCTION__,
             static_cast<int>(status), static_cast<int>(apiStatus), w3wAddress.c_str());
    if (nullptr != m_pW3WEventProvider)
    {
        m_pW3WEventProvider->updateW3WAddress(w3wAddress.c_str());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, m_pW3WEventProvider not available", __FUNCTION__);
    }
}

void CW3WResourceImpl::navigateToAddress(SW3WAddressItem addressItem)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s m_w3wAddress: %s m_languageCode: %s m_countryCode: %s m_nearestPlace: %s m_w3wAddressLabel: %s m_w3wAddressUID: %d",
             __FUNCTION__, addressItem.m_w3wAddress.c_str(), addressItem.m_languageCode.c_str(), addressItem.m_countryCode.c_str(),
             addressItem.m_nearestPlace.c_str(), addressItem.m_w3wAddressLabel.c_str(), addressItem.m_w3wAddressUID);

    if(m_bW3WPluginProxyAvailable)
    {
        w3wpluginTypeCollection::arAddList w3wAddressList;
        w3wpluginTypeCollection::AddressList w3wAddressItem;
        w3wAddressItem.setUID(addressItem.m_w3wAddressUID);
        w3wAddressItem.setThree_word_address(addressItem.m_w3wAddress);
        w3wAddressItem.setLanguage_code(addressItem.m_languageCode);
        w3wAddressItem.setCountry_code(addressItem.m_countryCode);
        w3wAddressItem.setNearest_place(addressItem.m_nearestPlace);
        w3wAddressItem.setLabel(addressItem.m_w3wAddressLabel);

        w3wAddressList.clear();
        w3wAddressList.push_back(w3wAddressItem);

        m_W3WPluginProxy->navigateToAddressAsync(w3wAddressList, std::bind(&CW3WResourceImpl::asyncNavigateToAddressCb,this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, W3W proxy not available", __FUNCTION__);
    }
}

void CW3WResourceImpl::asyncNavigateToAddressCb(const CallStatus &status, const w3wpluginTypeCollection::retStatus &apiStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, status: %d, apiStatus:: %d", __FUNCTION__,
             static_cast<int>(status), static_cast<int>(apiStatus));

    if (nullptr != m_pW3WEventProvider)
    {
        m_pW3WEventProvider->updateNavigationStatus(w3wpluginTypeCollection::retStatus::SUCCESS == apiStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, m_pW3WEventProvider not available", __FUNCTION__);
    }
}

void CW3WResourceImpl::getconnNextAppStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);

    if(m_bW3WPluginProxyAvailable)
    {
        m_W3WPluginProxy->getconnNextAppStatusAsync(std::bind(&CW3WResourceImpl::asyncGetconnNextAppStatusCb,this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, W3W proxy not available", __FUNCTION__);
    }
}

void CW3WResourceImpl::asyncGetconnNextAppStatusCb(const CallStatus &status, const w3wpluginTypeCollection::retStatus &connStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, status: %d, connStatus:: %d", __FUNCTION__,
             static_cast<int>(status), static_cast<int>(connStatus));
    if (nullptr != m_pW3WEventProvider)
    {
        m_pW3WEventProvider->updateConnNextStatus(static_cast<int>(connStatus));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, m_pW3WEventProvider not available", __FUNCTION__);
    }
}

void CW3WResourceImpl::getCountryCode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);

    if(m_bW3WPluginProxyAvailable)
    {
        m_W3WPluginProxy->getCountryCodeAsync(std::bind(&CW3WResourceImpl::asyncGetCountryCodeCb,this, _1, _2, _3));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, W3W proxy not available", __FUNCTION__);
    }
}

void CW3WResourceImpl::asyncGetCountryCodeCb(const CallStatus &status, const w3wpluginTypeCollection::retStatus &apiStatus, const std::string &countryCode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, status: %d, apiStatus:: %d, countryCode: %s", __FUNCTION__,
             static_cast<int>(status), static_cast<int>(apiStatus), countryCode.c_str());
    if (nullptr != m_pW3WEventProvider)
    {
        m_pW3WEventProvider->updateCountryCode(countryCode);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, m_pW3WEventProvider not available", __FUNCTION__);
    }
}

void CW3WResourceImpl::setCountryCode(const std::string &countryCode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);

    if(m_bW3WPluginProxyAvailable)
    {
        m_W3WPluginProxy->getCountryCodeAttribute().setValueAsync(countryCode, std::bind(&CW3WResourceImpl::asyncSetCountryCodeCb, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, W3W proxy not available", __FUNCTION__);
    }
}

void CW3WResourceImpl::asyncSetCountryCodeCb(const CommonAPI::CallStatus &callStatus, const std::string &countryCode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, status: %d, countryCode: %s", __FUNCTION__,
             static_cast<int>(callStatus), countryCode.c_str());
}

void CW3WResourceImpl::onGetMapsLaunchStatusEvent(w3wpluginTypeCollection::retStatus mapsLaunchStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, mapsLaunchStatus:: %d", __FUNCTION__, static_cast<int>(mapsLaunchStatus));
    if (nullptr != m_pW3WEventProvider)
    {
        m_pW3WEventProvider->updateMapsLaunchStatus(static_cast<int>(mapsLaunchStatus));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, m_pW3WEventProvider not available", __FUNCTION__);
    }
}

void CW3WResourceImpl::onGetconnNextAppStatusEvent(w3wpluginTypeCollection::retStatus connStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, connStatus:: %d", __FUNCTION__, static_cast<int>(connStatus));
    if (nullptr != m_pW3WEventProvider)
    {
        m_pW3WEventProvider->updateConnNextStatus(static_cast<int>(connStatus));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, m_pW3WEventProvider not available", __FUNCTION__);
    }
}

void CW3WResourceImpl::onGetCountryCodeAttribute(std::string countryCode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, countryCode: %s", __FUNCTION__, countryCode.c_str());
    if (nullptr != m_pW3WEventProvider)
    {
        m_pW3WEventProvider->updateCountryCode(countryCode);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W,"%s, m_pW3WEventProvider not available", __FUNCTION__);
    }
}
