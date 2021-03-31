/**********************************************************************
 * Auto generated code on 2018-03-09 15:45:19
 * @ Author   COC_SWPF_DevTOOLS@harman.com
 * @ Version  1.5.5
 **********************************************************************/

#include <iostream>
#include <string.h>
#include <stdio.h>
#include "HMI_TATAPersWrapperImpl.hpp"

int main()
{
  
    std::cout << "Persistence HMI_TATA ----------- " << std::endl;

	com::harman::persistence::HMI_TATAPersWrapperImpl *pers;
    pers = com::harman::persistence::HMI_TATAPersWrapperImpl::getInstance(1,1);

    pers->config();

	
	pers->deinit();	


	pers->destroyInstance();

    return 0;
}
