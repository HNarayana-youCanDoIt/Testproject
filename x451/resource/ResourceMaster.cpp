#include "ResourceMaster.h"

ResourceMaster::ResourceMaster()
{
    runtimePtr = 0;
}

ResourceMaster* ResourceMaster::s_instance = nullptr;

ResourceMaster* ResourceMaster::getInstance()
{
   if (!s_instance)
     s_instance = new ResourceMaster();

   return s_instance;
}

std::shared_ptr<CommonAPI::Runtime>  ResourceMaster::getRuntime()
{
    if(runtimePtr == NULL)
    {

        runtimePtr = CommonAPI::Runtime::get();

    }
    return runtimePtr;
}
