/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CAudioApplication.cpp
 * @ingroup         HMIComponent
 * @author          Mohit Rajani
 * CAudioApplication, an Application for Audio module,
 * CAudioApplication act as creator calls for the adaptor and event handler
 */

#include "CAudioApplication.h"
#include "CAudioAdaptor.h"
#include "CAudioEventHandler.h"

CAudioApplication::CAudioApplication(QObject* parent): QObject(parent)
  , m_pAudioAdaptor(CAudioAdaptor::getInstance())
  , m_pAudioEventHandler(new CAudioEventHandler)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s", __FUNCTION__);
}

CAudioApplication::~CAudioApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s", __FUNCTION__);
    if (m_pAudioEventHandler)
    {
        delete m_pAudioEventHandler;
    }
}
