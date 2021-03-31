/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CMediaApplication.h
* @ingroup      HMIComponent
* @author       Rahul Madan
* CMediaApplication, Class to load Media QML files
*/
#ifndef CMEDIAAPPLICATION_H
#define CMEDIAAPPLICATION_H

#include <QObject>
#include "HMIIncludes.h"
#include "CFramework.h"

class CMediaAdaptor;
class CMediaSM;
class CMediaEventHandler;

/**
 * @class CMediaApplication
 * @brief Application class for Media Module, which acts as mediator between QML and statemachine
 *        This class loads Media QML files
 */
class CMediaApplication : public CBaseApplication
{
public:
    CMediaApplication(QQuickItem* parent = nullptr);

    ~CMediaApplication();

    virtual void onCreated(QQuickItem* rootObject);
    void raiseSMEvent(const QString & name,const QVariant & data);
    void loadScreen(QString qmlFilePath);

private:
    CMediaAdaptor& mMediaAdaptor;
    CMediaSM* m_pMediaSM;
    CMediaEventHandler* m_pMediaEventHandler;
};



#endif // CMEDIAAPPLICATION_H
