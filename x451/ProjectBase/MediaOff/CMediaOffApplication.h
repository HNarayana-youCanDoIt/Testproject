/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CMediaOffApplication.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CMediaOffApplication, an Application for Media Off module,
 * CMediaOffApplication act as mediator between QML and Statemachine.
 */

#ifndef CMEDIAOFFAPPLICATION_H
#define CMEDIAOFFAPPLICATION_H

class CMediaOffAdaptor;
class CMediaOffEventHandler;
class CMediaOffSM;

/**
 * @brief CMediaOffApplication, an Application for Media Off module,
 * It act as mediator between QML and Statemachine.
 */
class CMediaOffApplication : public CBaseApplication
{
public:
    /**
    * @brief	CMediaOffApplication::CMediaOffApplication constructor for application class CMediaOffApplication.
    * @param	QObject.
    * @return	NA.
    **/
    CMediaOffApplication(QQuickItem* parent = nullptr);
    //________________________________________________________________________________________________
    /**
    * @brief	CMediaOffApplication::~CMediaOffApplication is destructor of application class CMediaOffApplication
    * @param	NA.
    * @return	NA.
    **/
    ~CMediaOffApplication();
    //________________________________________________________________________________________________
    /**
    * @brief	CMediaOffApplication::onCreated is CBaseApplication method
    * @param	QQuickItem.
    * @return	void.
    **/
    virtual void onCreated(QQuickItem* rootObject);
    //________________________________________________________________________________________________
    /**
    * @brief	CMediaOffApplication::raiseSMEvent is CBaseApplication method
    * @param	QQuickItem, QVariant.
    * @return	void.
    **/
    void raiseSMEvent(const QString & name,const QVariant & data);
    //________________________________________________________________________________________________
private:
    CMediaOffAdaptor& mMediaOffAdaptor;             // refrence to MediaOff adaptor instance
    CMediaOffEventHandler* mpMediaOffEventHandler;  // pointer to MediaOff data handler instance
    CMediaOffSM* mpMediaOffSM;                      // pointer to MediaOff state machine instance
    //________________________________________________________________________________________________
};

#endif // CMEDIAOFFAPPLICATION_H