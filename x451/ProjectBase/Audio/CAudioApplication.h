/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CAudioApplication.h
 * @ingroup         HMIComponent
 * @author          Mohit Rajani
 * CAudioApplication, an Application for Audio module,
 * CAudioApplication act as creator calls for the adaptor and event handler
 */

#ifndef CAUDIOAPPLICATION_H
#define CAUDIOAPPLICATION_H

#include <QObject>

class CAudioAdaptor;
class CAudioEventHandler;

/**
 * @brief The CAudioApplication CAudioApplication, an Application for Audio module,
 * CAudioApplication act as creator calls for the adaptor and event handler
 */
class CAudioApplication : public QObject
{
public:
    CAudioApplication(QObject* parent = nullptr);
    ~CAudioApplication();

private:
    /** Stores the Audio adaptor object instance */
    CAudioAdaptor* m_pAudioAdaptor;

    /** Stores the event handler object instance */
    CAudioEventHandler* m_pAudioEventHandler;
};

#endif // CAUDIOAPPLICATION_H
