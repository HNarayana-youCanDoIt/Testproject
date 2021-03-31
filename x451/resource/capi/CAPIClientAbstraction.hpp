#ifndef CAPICLIENTABSTRACTION_HPP
#define CAPICLIENTABSTRACTION_HPP

/*********************************************************************
* Project         Presentation Control Core
* (c) copyright   2016
* Company         Harman International
*                 All rights reserved
*********************************************************************/
/**
* @file            CommonAPIClientAbstraction.h
* @ingroup         presctrlcore
* @author          Ankur Tibrewal (ankur.tibrewal@harman.com)
* @brief           Simple wrapper over Common  API proxies.
*/

#include <CommonAPI/CommonAPI.hpp>
#include <string>
#include <functional>
#include <set>
#include <capi/CAPIEngine.hpp>



using namespace std::placeholders;


template <template<typename ...> class ProxyClass_>
class CAPIClientAbstraction
{
public :

    CAPIClientAbstraction(const std::string& domain,const std::string& instance)
        :m_pRuntime(nullptr)
        , m_pProxy(nullptr)
    {
        m_pRuntime = CommonAPI::Runtime::get();
        m_pProxy = m_pRuntime->buildProxy<ProxyClass_>(domain, instance, CAPIEngine::getMainLoop());
    }

    const std::string getStringAvailibility(const CommonAPI::AvailabilityStatus& avail)
    {
        return (CommonAPI::AvailabilityStatus::AVAILABLE == avail) ? std::string("available") : std::string("not available");
    }

    const std::string getStringCallStatus(const CommonAPI::CallStatus & stat)
    {
        return (CommonAPI::CallStatus::SUCCESS == stat) ? std::string("success") : std::string("failed");
    }

    std::shared_ptr<ProxyClass_<>> operator->()
    {
        return m_pProxy;
    }

private :
    std::shared_ptr<CommonAPI::Runtime> m_pRuntime;
    std::shared_ptr<ProxyClass_<>> m_pProxy;

};


#endif // CAPICLIENTABSTRACTION_HPP
