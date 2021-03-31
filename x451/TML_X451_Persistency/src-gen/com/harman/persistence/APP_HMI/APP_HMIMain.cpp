/**********************************************************************
 * Auto generated code on 2018-06-27 16:44:06
 * @ Author   COC_SWPF_DevTOOLS@harman.com
 * @ Version  1.5.5
 **********************************************************************/

#include <iostream>
#include <string.h>
#include <stdio.h>
#include "APP_HMIPersWrapperImpl.hpp"

int main()
{
  
    std::cout << "Persistence APP_HMI ----------- " << std::endl;

	com::harman::persistence::APP_HMIPersWrapperImpl *pers;
    pers = com::harman::persistence::APP_HMIPersWrapperImpl::getInstance(1,1);

    pers->config();

	
	pers->deinit();	


	pers->destroyInstance();

    return 0;
}
