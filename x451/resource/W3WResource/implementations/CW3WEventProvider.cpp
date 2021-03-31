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
* CICastEventProvider, class to propogate events from resource layer to the W3W Application layer
*/

#include "CW3WEventProvider.h"
#include "logging.h"

CW3WEventProvider::CW3WEventProvider(QObject *pParent):
    QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
}

CW3WEventProvider::~CW3WEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
}

void CW3WEventProvider::updateW3WCoreProxyAvailability(bool bW3WCoreProxyAvailability)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s: bW3WCoreProxyAvailability: %d", __FUNCTION__, bW3WCoreProxyAvailability);
    emit sigUpdateW3WCoreProxyAvailability(bW3WCoreProxyAvailability);
}

void CW3WEventProvider::updateW3WPluginProxyAvailability(bool bW3WPluginProxyAvailability)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s: bW3WPluginProxyAvailability: %d", __FUNCTION__, bW3WPluginProxyAvailability);
    emit sigUpdateW3WPluginProxyAvailability(bW3WPluginProxyAvailability);
}

void CW3WEventProvider::updateAutoSuggetionList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    emit sigUpdateAutoSuggestionList();
}

void CW3WEventProvider::updateFavoriteSavedStatus(bool favoriteSavedStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    emit sigUpdateFavoriteSavedStatus(favoriteSavedStatus);
}

void CW3WEventProvider::updateAddressDeletedStatus(bool addressDeletedStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    emit sigUpdateAddressDeletedStatus(addressDeletedStatus);
}

void CW3WEventProvider::updateFavoriteAddressList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    emit sigUpdateFavoriteAddressList();
}

void CW3WEventProvider::updateRecentAddressList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    emit sigUpdateRecentAddressList();
}

void CW3WEventProvider::updateLatLng(double latittude, double longitude)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s latitude is: %f, longitude is: %f", __FUNCTION__, latittude, longitude);
    emit sigUpdateLatLng(latittude, longitude);
}

void CW3WEventProvider::updateW3WAddress(std::string w3wAddress)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s w3wAddress: %s", __FUNCTION__, w3wAddress.c_str());
    emit sigUpdateW3WAddress(QString::fromStdString(w3wAddress));
}

void CW3WEventProvider::updateNavigationStatus(bool navigationStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s status: %d", __FUNCTION__, navigationStatus);
    emit sigUpdateNavigationStatus(navigationStatus);
}

void CW3WEventProvider::updateConnNextStatus(int connStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s status: %d", __FUNCTION__, connStatus);
    emit sigUpdateConnNextStatus(connStatus);
}

void CW3WEventProvider::updateCountryCode(std::string countryCode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s countryCode: %s", __FUNCTION__, countryCode.c_str());
    emit sigUpdateCountryCode(QString::fromStdString(countryCode));
}

void CW3WEventProvider::updateMapsLaunchStatus(int mapsLaunchStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s mapsLaunchStatus: %d", __FUNCTION__, mapsLaunchStatus);
    emit sigUpdateMapsLaunchStatus(mapsLaunchStatus);
}
