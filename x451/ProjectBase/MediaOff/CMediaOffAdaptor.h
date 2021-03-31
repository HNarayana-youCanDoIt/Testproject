/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CMediaOffAdaptor.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CMediaOffAdaptor, an Adaptor for Media Off module,
 * CMediaOffAdaptor is singleton class used to communicate with qml, resources of Media Off module.
 */

#ifndef CMEDIAOFFADAPTOR_H
#define CMEDIAOFFADAPTOR_H

#include <QObject>
#include <QString>
#include "logging.h"
#include "CFramework.h"

class CMediaOffApplication;
class CMediaOffEventHandler;
class CMediaOffSM;

/**
 * @brief CMediaOffAdaptor, an Adaptor for Home module,
 * It is singleton class used to communicate with qml, resources of Media Off module.
 */
class CMediaOffAdaptor : public QObject
{
    Q_OBJECT

    // Properties //
    // to get clock information from CDClockInformation
    Q_PROPERTY( QList<QObject*> clockInformationList READ clockInformationList NOTIFY sigClockInformationListChanged)

    // to get selected clock Id
    Q_PROPERTY(int selectedClockId READ selectedClockId WRITE setSelectedClockId NOTIFY sigSelectedClockIdChanged)

    //! property for qml to get whether Media Off screen is active or not
    Q_PROPERTY(bool mediaOffScreenStatus READ mediaOffScreenStatus NOTIFY sigMediaOffScreenStatusChanged)

public:
    /**
    * @brief	CMediaOffAdaptor::getInstance is static method used to get instance of singleton class CMediaOffAdaptor
    * @param	void.
    * @return	CMediaOffAdaptor.
    **/
    static CMediaOffAdaptor& getInstance();
    //________________________________________________________________________________________________
    /**
    * @brief	CMediaOffAdaptor::~CMediaOffAdaptor is destructor of singleton class CMediaOffAdaptor
    * @param	NA.
    * @return	NA.
    **/
    ~CMediaOffAdaptor();
    //________________________________________________________________________________________________
    /**
    * @brief	CMediaOffAdaptor::initAdaptorProperties is method used to inatialise adaptor properties.
    * @param	void.
    * @return	void.
    **/
    void initAdaptorProperties();
    //________________________________________________________________________________________________
    /**
    * @brief	CMediaOffAdaptor::clockInformationList is get method for "clockInformationList" qml property.
    * @param	void.
    * @return	QList<QObject*> : Clock information list.
    **/
    QList<QObject *> clockInformationList();
    //________________________________________________________________________________________________
    /**
    * @brief	CMediaOffAdaptor::clearClockInformationList is method to reset "clockInformationList" qml property.
    * @param	void.
    * @return	void.
    **/
    void clearClockInformationList();
    //________________________________________________________________________________________________
    /**
    * @brief	CMediaOffAdaptor::selectedClockId is get method for "selectedClockId" qml property.
    * @param	void.
    * @return	int.
    **/
    int selectedClockId();
    /**
    * @brief	CMediaOffAdaptor::setSelectedClockId is set method for "selectedClockId" qml property.
    * @param	_value.
    * @return	void.
    **/
    void setSelectedClockId(int _value);

    /**
     * @brief   mediaOffScreenStatus: Method to get whether Media Off screen is active or not.
     * @param   void.
     * @return  TRUE if Media Off screen is active, FALSE otherwise.
     */
    bool mediaOffScreenStatus();

    /**
     * @brief   setMediaOffScreenStatus: Method to set the Media Off screen status.
     * @param   TRUE if Media Off screen is active, FALSE otherwise.
     * @return  void.
     */
    void setMediaOffScreenStatus(bool bMediaOffScreenStatus);

    //________________________________________________________________________________________________

    /**
    * @brief	CMediaOffAdaptor::invSetDrawersVisibility is QML invokable method which sets the drawers visiblity.
    * @param	bool (bIsVisible Drawers visiblity)
    * @return	void.
    **/
    Q_INVOKABLE void invSetDrawersVisibility(bool bIsVisible);
    //________________________________________________________________________________________________
signals:
    /**
    * @brief	CHomeAdaptor::sigClockInformationListChanged is QML signal for "clockInformationList" property change event.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigClockInformationListChanged();

    /**
    * @brief	CMediaOffAdaptor::sigSelectedClockIdChanged is QML signal for "selectedClockId" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigSelectedClockIdChanged();

    /*!
     * @brief   sigMediaOffScreenStatusChanged: Signal emitted whenever MediaOffScreenStatus is changed.
     * @param   void.
     * @return  void.
     */
    void sigMediaOffScreenStatusChanged();

    //________________________________________________________________________________________________
public slots:

    //________________________________________________________________________________________________
protected:

    //________________________________________________________________________________________________
private:
    /**
    * @brief	CMediaOffAdaptor::CMediaOffAdaptor private constructor for singleton class CMediaOffAdaptor.
    * @param	QObject.
    * @return	NA.
    **/
    explicit CMediaOffAdaptor(QObject *parent = nullptr); // for singleton pattern class
    //________________________________________________________________________________________________
private:
    static CMediaOffAdaptor* mpMediaOffAdaptor; // for maintaining singleton class instance

    QList<QObject*> m_lCDClockInformations;     // member list contains clocks information and states
    int m_iSelectedClockId;                     // member variable to hold value for property "selectedClockId"
    /* Flag to maintain whether Media Off is active or not */
    bool m_bMediaOffScreenStatus;
};

#endif // CMEDIAOFFADAPTOR_H
