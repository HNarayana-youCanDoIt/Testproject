/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CSetupApplication.h
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * CSetupApplication.h, setup module application header file, contains all the functionality related to setup module
 *          creates instances for CAudioEventHandler & CSetupSM and raises events SM
 */
#ifndef CSETUPAPPLICATION_H
#define CSETUPAPPLICATION_H

#include <QObject>
#include "CBaseApplication.h"
#include "StateMachine_TML_HMI_SM.h"
#include "CSetupEnums.h"
#include "CSetupAdaptor.h"

class CAudioAdaptor;
class CVehicleSettingsAdaptor;
class CVehicleSettingsEventHandler;
class CSetupSM;
class CDateAndTimeEventHandler;

/**
 * @brief The CSetupApplication class: This class contains all the functionality related to setup module
 *          creates instances for CAudioEventHandler & CSetupSM and raises events SM
 */
class CSetupApplication : public CBaseApplication
{
    Q_OBJECT
public:
    /**
    * @brief	CSetupApplication - Constructor for application class CSetupApplication.
    * @param	QQuickItem.
    * @return	NA.
    **/
    CSetupApplication(QQuickItem* parent = nullptr);

    /**
    * @brief	~CSetupApplication - Destructor for application class CSetupApplication.
    * @param	NA.
    * @return	NA.
    **/
    ~CSetupApplication();

    /**
    * @brief	onCreated - Method is called when the QML is loaded successfully, this is CBaseApplication method
    * @param	QQuickItem.
    * @return	void.
    **/
    virtual void onCreated(QQuickItem* rootObject);

    /**
     * @brief   raiseSMEvent - Method is called from the QML file to raise an event on the State machine, this is CBaseApplication method
     * @param   name & data
     * @return	void.
     */
    void raiseSMEvent(const QString & name,const QVariant & data);

    /**
     * @brief   loadScreen - Method is called to load the provide qml file onto the QQuickWindow, this is CBaseApplication method
     * @param   qmlFilePath - provide qml file path
     * @return	void.
     */
    void loadScreen(QString qmlFilePath);

    /**
     * @brief setCurrentListModel: To set the current active setup list model, called from enter methods of SM
     * @param screenId
     * @return	void.
     */
    Q_INVOKABLE void setCurrentListModel(int screenId);

    /**
     * @brief switchScreenToMainSetup: Method is called from qml file when power mode changed to one hour mode to switch screen to main setup
     * @param void
     * @return	void.
     */
    Q_INVOKABLE void switchScreenToMainSetup();

    /**
     * @brief switchScreenToVehicleSetup: Method is called from qml file to switch screen to vehicle setup.
     * @param void
     * @return	void.
     */
    Q_INVOKABLE void switchScreenToVehicleSetup();

    /**
     * @brief  jumpToPreviousScreen: This method is called from qml, it raises evBack to SM.
     * @param  void
     * @return void.
     */
    Q_INVOKABLE void jumpToPreviousScreen();

    /**
     * @brief switchScreenToThemeSetup: Method is called from drwawers to switch screen to theme setup on theme presets clicked.
     * @param void
     * @return	void.
     */
    Q_INVOKABLE void switchScreenToThemeSetup();

public slots:

private:
    //private methods to be declared here

    /**
     * @brief   raiseSMEventForMainSetup - This method is responsible for raising events to SM for main setup
     * @param   setupIndex - type of setup event to be raised
     * @return	void.
     */
    void raiseSMEventForMainSetup(CSetupEnums::ESetupScreens setupIndex);

    /**
     * @brief   raiseSMEventForAudioSetup - This method is responsible for raising events to SM for audio setup
     * @param   eAudioSetupPathViewIndex - type of audio setup event to be raised
     * @return	void.
     */
    void raiseSMEventForAudioSetup(CSetupEnums::EAudioSetupPathViewCurrIndex eAudioSetupPathViewIndex);

    /**
     * @brief   raiseSMEventForGeneralSetup - This method is responsible for raising events to SM for general setup
     * @param   eGeneralSetupItemIndex - type of general setup event to be raised
     * @return	void.
     */
    void raiseSMEventForGeneralSetup(CSetupEnums::EGeneralSetup eGeneralSetupItemIndex);

    /**
     * @brief   raiseSMEventForVehicleSetup - This method is responsible for raising events to SM for Vehicle setup
     * @param   vehicleSetupIndex - type of vehicle setup event to be raised
     * @return	void.
     */
    void raiseSMEventForVehicleSetup(int vehicleSetupIndex);

    /**
     * @brief raiseSMEventForLightingSetup - This method is responsible for raising events to SM for lighting setup
     * @param iLightingSetupIndex   - type of lighting setup event to be raised
     * @return  void.
     */
    void raiseSMEventForLightingSetup(int iLightingSetupIndex);

    /**
     * @brief raiseSMEventForDriveNextSetup - This method is responsible for raising events to SM for DriveNext setup
     * @param iDriveNextSetupIndex   - type of DriveNext setup event to be raised
     * @return  void.
     */
    void raiseSMEventForDriveNextSetup(int iDriveNextSetupIndex);

private:

    /* Instance of CAudioAdaptor class */
    CAudioAdaptor *m_pAudioAdaptor;

    /* Instance of CVehicleSettingsAdaptor class */
    CVehicleSettingsAdaptor *m_pVehicleAdaptor;

    /* Instance of CVehicleSettingsEventHandler class */
    CVehicleSettingsEventHandler *m_pVehicleEventHandler;

    /* Instance of CDateAndTimeEventHandler class */
    CDateAndTimeEventHandler *m_pDateAndTimeEventHandler;

    /* Instance of CSetupSM class */
    CSetupSM* m_pSetupSM;

    /* Instance of CSetupAdaptor class */
    CSetupAdaptor *m_pSetupAdaptor;

    /**
     * @brief CONST_STRING_KEYPAD: string to hold "Keypad" string value
     */
    const QString CONST_STRING_KEYPAD;
};



#endif // CSETUPAPPLICATION_H
