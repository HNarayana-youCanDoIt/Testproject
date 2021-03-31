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

#include <CHMIMain.h>
#include <ResourceFactory.hpp>

#include "CW3WApplication.h"
#include "CW3WAdaptor.h"
#include "CW3WSM.h"
#include "CW3WEventHandler.h"
#include "resource/W3WResource/implementations/CW3WResourceImpl.h"

CW3WEventHandler::CW3WEventHandler(QObject *parent):
    QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    connectSignals();
}

CW3WEventHandler::~CW3WEventHandler()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    disconnectSignals();
}

void CW3WEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    CW3WResourceImpl* pW3WResource = dynamic_cast<CW3WResourceImpl*>(ResourceFactory::getW3WResource());

    if(pW3WResource)
    {
        CW3WEventProvider* pW3WEventProvider = pW3WResource->getW3WEventProvider();
        if(pW3WEventProvider)
        {
            connect(pW3WEventProvider, &CW3WEventProvider::sigUpdateW3WCoreProxyAvailability , this, &CW3WEventHandler::sltUpdateW3WCoreProxyAvailability, Qt::QueuedConnection);
            connect(pW3WEventProvider, &CW3WEventProvider::sigUpdateW3WPluginProxyAvailability , this, &CW3WEventHandler::sltUpdateW3WPluginProxyAvailability, Qt::QueuedConnection);
            connect(pW3WEventProvider, &CW3WEventProvider::sigUpdateAutoSuggestionList , this, &CW3WEventHandler::sltUpdateAutoSuggestionList,Qt::QueuedConnection);
            connect(pW3WEventProvider, &CW3WEventProvider::sigUpdateFavoriteSavedStatus , this, &CW3WEventHandler::sltUpdateFavoriteSavedStatus,Qt::QueuedConnection);
            connect(pW3WEventProvider, &CW3WEventProvider::sigUpdateAddressDeletedStatus , this, &CW3WEventHandler::sltUpdateAddressDeletedStatus,Qt::QueuedConnection);
            connect(pW3WEventProvider, &CW3WEventProvider::sigUpdateFavoriteAddressList , this, &CW3WEventHandler::sltUpdateFavoriteAddressList,Qt::QueuedConnection);
            connect(pW3WEventProvider, &CW3WEventProvider::sigUpdateRecentAddressList , this, &CW3WEventHandler::sltUpdateRecentAddressList,Qt::QueuedConnection);
            connect(pW3WEventProvider, &CW3WEventProvider::sigUpdateLatLng , this, &CW3WEventHandler::sltUpdateLatLng,Qt::QueuedConnection);
            connect(pW3WEventProvider, &CW3WEventProvider::sigUpdateW3WAddress , this, &CW3WEventHandler::sltUpdateW3WAddress,Qt::QueuedConnection);
            connect(pW3WEventProvider, &CW3WEventProvider::sigUpdateNavigationStatus , this, &CW3WEventHandler::sltUpdateNavigationStatus,Qt::QueuedConnection);
            connect(pW3WEventProvider, &CW3WEventProvider::sigUpdateConnNextStatus , this, &CW3WEventHandler::sltUpdateConnNextStatus,Qt::QueuedConnection);
            connect(pW3WEventProvider, &CW3WEventProvider::sigUpdateCountryCode ,this, &CW3WEventHandler::sltUpdateCountryCode,Qt::QueuedConnection);
            connect(pW3WEventProvider, &CW3WEventProvider::sigUpdateMapsLaunchStatus ,this, &CW3WEventHandler::sltUpdateMapsLaunchStatus,Qt::QueuedConnection);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, pW3WEventProvider is null", __FUNCTION__);
        }

    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W, "%s | W3W Resource is returned NULL from Resource Factory",__FUNCTION__);
    }
}

void CW3WEventHandler::disconnectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    CW3WResourceImpl* pW3WResource = dynamic_cast<CW3WResourceImpl*>(ResourceFactory::getW3WResource());

    if(pW3WResource)
    {
        CW3WEventProvider* pW3WEventProvider = pW3WResource->getW3WEventProvider();
        if(pW3WEventProvider)
        {
            disconnect(pW3WEventProvider, &CW3WEventProvider::sigUpdateW3WCoreProxyAvailability , this, &CW3WEventHandler::sltUpdateW3WCoreProxyAvailability);
            disconnect(pW3WEventProvider, &CW3WEventProvider::sigUpdateW3WPluginProxyAvailability , this, &CW3WEventHandler::sltUpdateW3WPluginProxyAvailability);
            disconnect(pW3WEventProvider, &CW3WEventProvider::sigUpdateAutoSuggestionList , this, &CW3WEventHandler::sltUpdateAutoSuggestionList);
            disconnect(pW3WEventProvider, &CW3WEventProvider::sigUpdateFavoriteSavedStatus , this, &CW3WEventHandler::sltUpdateFavoriteSavedStatus);
            disconnect(pW3WEventProvider, &CW3WEventProvider::sigUpdateAddressDeletedStatus , this, &CW3WEventHandler::sltUpdateAddressDeletedStatus);
            disconnect(pW3WEventProvider, &CW3WEventProvider::sigUpdateFavoriteAddressList , this, &CW3WEventHandler::sltUpdateFavoriteAddressList);
            disconnect(pW3WEventProvider, &CW3WEventProvider::sigUpdateRecentAddressList , this, &CW3WEventHandler::sltUpdateRecentAddressList);
            disconnect(pW3WEventProvider, &CW3WEventProvider::sigUpdateLatLng , this, &CW3WEventHandler::sltUpdateLatLng);
            disconnect(pW3WEventProvider, &CW3WEventProvider::sigUpdateW3WAddress , this, &CW3WEventHandler::sltUpdateW3WAddress);
            disconnect(pW3WEventProvider, &CW3WEventProvider::sigUpdateNavigationStatus , this, &CW3WEventHandler::sltUpdateNavigationStatus);
            disconnect(pW3WEventProvider, &CW3WEventProvider::sigUpdateConnNextStatus , this, &CW3WEventHandler::sltUpdateConnNextStatus);
            disconnect(pW3WEventProvider, &CW3WEventProvider::sigUpdateCountryCode ,this, &CW3WEventHandler::sltUpdateCountryCode);
            disconnect(pW3WEventProvider, &CW3WEventProvider::sigUpdateMapsLaunchStatus ,this, &CW3WEventHandler::sltUpdateMapsLaunchStatus);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, pW3WEventProvider is null", __FUNCTION__);
        }

    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W, "%s | W3W Resource is returned NULL from Resource Factory",__FUNCTION__);
    }
}

void CW3WEventHandler::sltUpdateW3WCoreProxyAvailability(bool w3wCoreProxyAvailability)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, w3wCoreProxyAvailability: %d", __FUNCTION__, w3wCoreProxyAvailability);
    CW3WApplication::getW3WAdaptor()->updateOnCoreProxyAvailability(w3wCoreProxyAvailability);
}

void CW3WEventHandler::sltUpdateW3WPluginProxyAvailability(bool w3wPluginProxyAvailability)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, w3wPluginProxyAvailability: %d", __FUNCTION__, w3wPluginProxyAvailability);
    CW3WApplication::getW3WAdaptor()->updateOnPluginProxyAvailability(w3wPluginProxyAvailability);
}

void CW3WEventHandler::sltUpdateAutoSuggestionList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s", __FUNCTION__);
    CW3WApplication::getW3WAdaptor()->updateAutoSuggestionList();
}

void CW3WEventHandler::sltUpdateFavoriteSavedStatus(bool favoriteSavedStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s", __FUNCTION__);
    CW3WApplication::getW3WAdaptor()->updateFavoriteSavedStatus(favoriteSavedStatus);
}

void CW3WEventHandler::sltUpdateAddressDeletedStatus(bool addressDeletedStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s", __FUNCTION__);
    CW3WApplication::getW3WAdaptor()->updateAddressDeletedStatus(addressDeletedStatus);
}

void CW3WEventHandler::sltUpdateFavoriteAddressList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s", __FUNCTION__);
    CW3WApplication::getW3WAdaptor()->updateFavoriteAddressList();
}

void CW3WEventHandler::sltUpdateRecentAddressList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s", __FUNCTION__);
    CW3WApplication::getW3WAdaptor()->updateRecentAddressList();
}

void CW3WEventHandler::sltUpdateLatLng(double lat, double lng)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s", __FUNCTION__);    
    CW3WApplication::getW3WAdaptor()->updateW3WCoordinates(lat, lng);
}

void CW3WEventHandler::sltUpdateW3WAddress(QString w3wAddress)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, w3w address: %s", __FUNCTION__, w3wAddress.toStdString().c_str());
    CW3WApplication::getW3WAdaptor()->updateW3WAddress(w3wAddress);
}

void CW3WEventHandler::sltUpdateNavigationStatus(bool navigationStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, navigationStatus: %d", __FUNCTION__, navigationStatus);
    CW3WApplication::getW3WAdaptor()->updateNavigationStatus(navigationStatus);
}

void CW3WEventHandler::sltUpdateConnNextStatus(int connStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, connStatus: %d", __FUNCTION__, connStatus);
    CW3WApplication::getW3WAdaptor()->updateConnNextStatus(connStatus);
}

void CW3WEventHandler::sltUpdateCountryCode(QString countryCode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s, country code: %s", __FUNCTION__, countryCode.toStdString().c_str());
    CW3WApplication::getW3WAdaptor()->updateCurrentCountryCode(countryCode);
}

void CW3WEventHandler::sltUpdateMapsLaunchStatus(int mapsLaunchStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s", __FUNCTION__);
    CW3WApplication::getW3WAdaptor()->updateMapsLaunchStatus(mapsLaunchStatus);
}
