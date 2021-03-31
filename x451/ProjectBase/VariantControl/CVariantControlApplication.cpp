/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CVariantControlApplication.cpp
 * @ingroup         HMIComponent
 * @author          Manali Patil
 * CVariantControlApplication, an Application for VariantControl module,
 * CVariantControlApplication act as mediator between QML and Statemachine.
 */

#include "CVariantControlApplication.h"
#include "CVariantControlAdaptor.h"
#include "CVariantControlEventHandler.h"

CVariantControlApplication::CVariantControlApplication(QObject* pParent): QObject(pParent)
    ,m_pVariantControlEventHandler(new CVariantControlEventHandler(this))
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s", __FUNCTION__);
    CVariantControlAdaptor::getInstance();
}

CVariantControlApplication::~CVariantControlApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s", __FUNCTION__);
    if (m_pVariantControlEventHandler)
    {
        delete m_pVariantControlEventHandler;
        m_pVariantControlEventHandler = nullptr;
    }
}
