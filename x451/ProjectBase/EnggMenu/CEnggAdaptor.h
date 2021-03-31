/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CEnggAdaptor.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande, Rajat Gupta
 * CEnggAdaptor, an adaptor for Engineering module,
 * CEnggAdaptor is singleton class used to communicate with qml,resources of Engg module.
 */

#ifndef CENGGADAPTOR_H
#define CENGGADAPTOR_H

#include <QObject>
#include <QString>
#include "logging.h"
#include "CFramework.h"
#include "CEnggMenuEnum.h"
#include "Model/CEnggMenuListModel.h"
#include "EnggMenuResource/interfaces/IEnggMenuResource.h"
#include "CTunerAdaptor.h"
#include "CAudioAdaptor.h"
#include "CMediaAdaptor.h"
#include "CAudioEnums.h"
#include "CVersionManagerAdaptor.h"
#include "CPowerModeAdaptor.h"
#include "CVehicleSettingsAdaptor.h"
#include "Diagnostic/CDiagnosticAdaptor.h"
#include "Diagnostic/CDiagnosticEnum.h"
#include "VariantControl/CVariantControlAdaptor.h"

class CEnggApplication;
class CEnggEventHandler;
class CEnggSM;

/**
 * @brief
 * CEnggAdaptor, an adaptor for Engineering module,
 * It is singleton class used to communicate with qml,resources of Engg module.
 */
class CEnggAdaptor : public QObject
{
    Q_OBJECT

    /**
     * Property to set the Enggg Menu List to the Current Model which is QAbstractListModel type
     */
    Q_PROPERTY(CEnggMenuListModel* enggMenuCurrentListModel READ enggMenuCurrentListModel NOTIFY sigEnggMenuCurrentListModelChanged)

    /**
     * Property to set the current screen
     */
    Q_PROPERTY(CEnggMenuEnum::EEnggMenuScreen enggMenuCurrentScreen READ enggMenuCurrentScreen NOTIFY sigEnggMenuCurrentScreenChanged)

    /**
     * Property to set the Title of Screen containing List.
     */
    Q_PROPERTY(QString enggMenuScreenTitle READ enggMenuScreenTitle NOTIFY sigEnggMenuScreenTitleChanged)

    /**
     * Property to set the persistency of test Automation in debug Logs.
     */
    Q_PROPERTY(bool enggMenuTestAutomationStatus READ enggMenuTestAutomationStatus NOTIFY sigEnggMenuTestAutomationStatusChanged)

    //Property to know the status of engg proxy availability.
    Q_PROPERTY(bool enggMenuProxyStatus READ enggMenuProxyStatus NOTIFY sigEnggMenuProxyStatusChanged)



private:
    /**
    * @brief	CEnggAdaptor::CEnggAdaptor: constructor for singleton class CEnggAdaptor.
    * @param	pParent: parent class pointer.
    * @return	void.
    **/
    // for singleton pattern class
    explicit CEnggAdaptor(QObject *pParent = nullptr);
    //________________________________________________________________________________________________
public:

    /**
    * @brief	CEnggAdaptor::~CEnggAdaptor is destructor of singleton class CEnggAdaptor
    * @param	void.
    * @return	void.
    **/
    ~CEnggAdaptor();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::getInstance: static method used to get instance of singleton class CEnggAdaptor
    * @param	void.
    * @return	CEnggAdaptor: instance of Engg Adaptor.
    **/
    static CEnggAdaptor* getInstance();
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggAdaptor::setAdaptorEnggMenuModel:  method used to set the model of the list
    * @param	CEnggMenuEnum::EEnggMenuScreen eEnggMenuScreen: Currently which model should be set to the list
    * @return	void.
    **/
    void setAdaptorEnggMenuModel(CEnggMenuEnum::EEnggMenuScreen eEnggMenuScreen);
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::initEnggMenuModels: method used to initialize all the models that will be used in a ListModel.
    * @param	void.
    * @return	void.
    **/
    void initEnggMenuListModels();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::initEnggMenuModelEnggMain: method used to initialize the EnggMenu Main Screen Model of EnggMenu.
    * @param	void.
    * @return	void.
    **/
    void initEnggMenuModelEnggMain();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::initEnggMenuModelDriveNextEfficiency: method used to initialize the DriveNext Efficiency Screen Model of EnggMenu.
    * @param	void.
    * @return	void.
    **/
    void initEnggMenuModelDriveNextEfficiency();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::resetEnggMenuModelDriveNextEfficiency: method used to reset the DriveNext Efficiency Screen Model of EnggMenu.
    * @param	void.
    * @return	void.
    **/
    void resetEnggMenuModelDriveNextEfficiency();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::initEnggMenuModelDriveNextBraking: method used to initialize the DriveNext Braking Screen Model of EnggMenu.
    * @param	void.
    * @return	void.
    **/
    void initEnggMenuModelDriveNextBraking();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::resetEnggMenuModelDriveNextBraking: method used to reset the DriveNext Braking Screen Model of EnggMenu.
    * @param	void.
    * @return	void.
    **/
    void resetEnggMenuModelDriveNextBraking();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::initEnggMenuModelDriveNextAcceleration: method used to initialize the DriveNext Acceleration Screen Model of EnggMenu.
    * @param	void.
    * @return	void.
    **/
    void initEnggMenuModelDriveNextAcceleration();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::resetEnggMenuModelDriveNextAcceleration: method used to reset the DriveNext Acceleration Screen Model of EnggMenu.
    * @param	void.
    * @return	void.
    **/
    void resetEnggMenuModelDriveNextAcceleration();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::initEnggMenuModelDriveNextGearShift: method used to initialize the DriveNext GearShift Screen Model of EnggMenu.
    * @param	void.
    * @return	void.
    **/
    void initEnggMenuModelDriveNextGearShift();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::resetEnggMenuModelDriveNextGearShift: method used to reset the DriveNext GearShift Screen Model of EnggMenu.
    * @param	void.
    * @return	void.
    **/
    void resetEnggMenuModelDriveNextGearShift();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::initEnggMenuModelDriveNextGeneric: method used to initialize the DriveNext Generic Screen Model of EnggMenu.
    * @param	void.
    * @return	void.
    **/
    void initEnggMenuModelDriveNextGeneric();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::resetEnggMenuModelDriveNextGeneric: method used to reset the DriveNext Generic Screen Model of EnggMenu.
    * @param	void.
    * @return	void.
    **/
    void resetEnggMenuModelDriveNextGeneric();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::initEnggMenuModelDriveNextSafety: method used to initialize the DriveNext Safety Screen Model of EnggMenu.
    * @param	void.
    * @return	void.
    **/
    void initEnggMenuModelDriveNextSafety();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::resetEnggMenuModelDriveNextSafety: method used to reset the DriveNext Safety Screen Model of EnggMenu.
    * @param	void.
    * @return	void.
    **/
    void resetEnggMenuModelDriveNextSafety();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::initEnggMenuModelDriveNextMainMenu: method used to initialize the DriveNext Screen Model of DriveNext main menu.
    * @param	void.
    * @return	void.
    **/
    void initEnggMenuModelDriveNextMainMenu();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::resetEnggMenuModelDriveNextMainMenu: method used to reset the DriveNext Screen Model of DriveNext main menu.
    * @param	void.
    * @return	void.
    **/
    void resetEnggMenuModelDriveNextMainMenu();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::initEnggMenuModelDriveNextDbgLevel: method used to initialize the DriveNext Screen Model of DriveNext log level.
    * @param	void.
    * @return	void.
    **/
    void initEnggMenuModelDriveNextDbgLevel();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::resetEnggMenuModelDriveNextDbgLevel: method used to reset the DriveNext Screen Model of DriveNext log level.
    * @param	void.
    * @return	void.
    **/
    void resetEnggMenuModelDriveNextDbgLevel();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::initEnggMenuModelDriveNextDbgLevel: method used to initialize the DriveNext Screen Model of DriveNext log trip selection.
    * @param	void.
    * @return	void.
    **/
    void initEnggMenuModelDriveNextDbgTrip();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::resetEnggMenuModelDriveNextDbgLevel: method used to reset the DriveNext Screen Model of DriveNext log trip selection.
    * @param	void.
    * @return	void.
    **/
    void resetEnggMenuModelDriveNextDbgTrip();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::initEnggMenuModelDriveNextDbgLocation: method used to initialize the DriveNext Screen Model of DriveNext Logging.
    * @param	void.
    * @return	void.
    **/
    void initEnggMenuModelDriveNextDbgLocation();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::resetEnggMenuModelDriveNextDbgLocation: method used to reset the DriveNext Screen Model of DriveNext Logging.
    * @param	void.
    * @return	void.
    **/
    void resetEnggMenuModelDriveNextDbgLocation();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::initEnggMenuModelDriveNextDetailList: method used to initialize the DriveNext Screen Model of DriveNext details.
    * @param	void.
    * @return	void.
    **/
    void initEnggMenuModelDriveNextDetailList();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::resetEnggMenuModelDriveNextDetailList: method used to reset the DriveNext Screen Model of DriveNext details.
    * @param	void.
    * @return	void.
    **/
    void resetEnggMenuModelDriveNextDetailList();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::initEnggMenuModelIllumination: method used to initialize the Illumination Screen Model of EnggMenu.
    * @param	void.
    * @return	void.
    **/
    void initEnggMenuModelIllumination();

    //________________________________________________________________________________________________
    /**
    * @brief	CEnggAdaptor::initEnggMenuModelSysConfig: method used to initialize the System Configuration Screen Model of EnggMenu.
    * @param	void.
    * @return	void.
    **/
    void initEnggMenuModelSysConfig();
    //________________________________________________________________________________________________


    /**
    * @brief	CEnggAdaptor::initEnggMenuModel16RPart: method used to initialize the 16R Part Number Screen Model of EnggMenu.
    * @param	void.
    * @return	void.
    **/
    void initEnggMenuModel16RPart();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::initEnggMenuModelTestModeTuner: method used to initialize the Test Mode Tuner Screen Model of EnggMenu.
    * @param	void.
    * @return	void.
    **/
    void initEnggMenuModelTestModeTuner();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::initEnggMenuModelTestModeAudioMediais method used to initialize the
    * Test Mode Audio Media Model of EnggMenu.
    * @param	void.
    * @return	void.
    **/
    void initEnggMenuModelTestModeAudioMedia();
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggAdaptor::initEnggMenuModelTestModeVideoMedia: method used to initialize the Test Mode Video Media Screen Model of EnggMenu.
    * @param	void.
    * @return	void.
    **/
    void initEnggMenuModelTestModeVideoMedia();
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggAdaptor::initEnggMenuModelDebugLogs: method used to initialize the DebugLogs Screen Model of EnggMenu.
    * @param	void.
    * @return	void.
    **/

    void initEnggMenuModelDebugLogs();

    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::enggMenuCurrentListModel: getter function which returns the current model which has to be shown on the screen.
    * @param	void.
    * @return	QAbstractListModel: returns the Model.
    **/

    CEnggMenuListModel *enggMenuCurrentListModel();

    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::enggMenuCurrentScreen: returns the current Screen assigned to the list
    * @param	void
    * @return	CEnggMenuEnum::EEnggMenuScreen :returns the currentScreen Index
    **/

    CEnggMenuEnum::EEnggMenuScreen enggMenuCurrentScreen();
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggAdaptor::enggMenuScreenTitle: return the current screen title.
    * @param	void
    * @return	QString : returns the string containing the title of current screen.
    **/

    QString enggMenuScreenTitle();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::enggMenuTestAutomationStatus: will return the status of Test Automation.
    * @param	void
    * @return	bool :returns the bool containing the status of Test Automation.
    **/

    bool enggMenuTestAutomationStatus();
    //________________________________________________________________________________________________
    /**
     * @brief enggMenuProxyStatus: This function will return the Engg Menu Proxy Current availability status.
     * @param : void.
     * @return bool: return the Engg Menu Proxy Current availability status.
     */
    bool enggMenuProxyStatus(){ return m_bIsEnggMenuProxyAvailable;}
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::setEnggMenuCurrentScreen: will set the current Screen according to the parameter
    * @param	screenIndex: contains the index of the current Screen
    * @return	void.
    **/

    void setEnggMenuCurrentScreen(CEnggMenuEnum::EEnggMenuScreen eEnggMenuCurrentScreenIndex);
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::setDebugsLogCheckStatus will set the status according to the parameter
    * @param	bDebugsLogStatus: contains the check/uncheck DebugsLog status
    * @return	void.
    **/
    void setDebugsLogCheckStatus(bool bDebugsLogStatus);

    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::setIpTypeStatus: will set the status according to the parameter
    * @param	iIpStatus: contains the status of Ip type
    * @param    iIpType :contains the type of Ip on which action has been taken
    * @return	void.
    **/
    void setIpTypeStatus(int iIpStatus, int iIpType);

    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::setEnggMenuTestAutomationStatus: will set the status of Test Automation.
    * @param	 iTestAutomationStatusCb, parameter contains the status of Test Automation
    * @param	 iTestAutomationStatusCb, parameter contains the value of Test Automation i.e Enable/Disable
    * @return	void.
    **/

    void setEnggMenuTestAutomationStatus(int iTestAutomationStatusCb, int iTestAutomationValueCb);
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::setFactoryResetWaitingStatus: will give info regarding waiting status.
    * @param	bool bFactoryResetWaitingStatus: parameter to set the status of Factory reset waiting.
    * @return	void.
    **/

    void setFactoryResetWaitingStatus(bool bFactoryResetWaitingStatus);
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggAdaptor::setFactoryResetCompletionStatus: will give info regarding completion status.
    * @param	bool bFactoryResetCompletionStatus: parameter to set the status of Factory reset completion.
    * @return	void.
    **/

    void setFactoryResetCompletionStatus(bool bFactoryResetCompletionStatus);
    //________________________________________________________________________________________________

    /**
     * @brief	updateDebugLogsStatusToService: This method reads the data from persistence and calls the API of engg menu service.
     * @param	void.
     * @return	void.
     **/
    void updateDebugLogsStatusToService();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::setDeviceModeStatus: give info regarding device mode status.
    * @param	iDeviceModeStatus: status of device mode callback
    * @param	iDeviceType: type of device mode
    * @return	void.
    **/

    void setDeviceModeStatus(int iDeviceModeStatus, int iDeviceType);
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::startFactoryResetProcess: it will start the factory reset process.
    * @param	void.
    * @return	void.
    **/
    void startFactoryResetProcess();

    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::buttonPanelHkHandling , This function will be called when user , being on button panel
    * screen will press/release any hardkey.
    * @param	void.
    * @return	void.
    **/
    void buttonPanelHkHandling();
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::setEnggMenuCurrentListModel: set the current changed model of enggMenu list.
    * @param	pEnggMenuCurrentListModel: Current Model that needs to be displayed now.S
    * @return	void.
    **/

    void setEnggMenuCurrentListModel(CEnggMenuListModel* pEnggMenuCurrentListModel);

    //________________________________________________________________________________________________

    /**
    * @brief	CEnggAdaptor::setEnggMenuCurrentScreenTitle: title of current Engg Menu Screen.
    * @param	strEnggMenuScreenTitle: Current Engg Menu Screen Title thats need to be displayed currently.
    * @return	void.
    **/

    void setEnggMenuCurrentScreenTitle(QString strEnggMenuScreenTitle);
    //________________________________________________________________________________________________

    /**
    * @brief updateSysConfigAntennaType: this will update the Am/FM Antenna type in System configuration.
    * @param void
    * @return void
    */
    void updateSysConfigAntennaType();
    //________________________________________________________________________________________________

    /**
    * @brief updateEnggMenuParametersOnProxyAvailability() - this will update the EnggMenu Parameters
    *        which are based on EnggMenu Proxy Availability.
    * @param bIsEnggMenuProxyAvailable: Engg Menu Proxy Availability.
    * @return void
    */
    void updateEnggMenuParametersOnProxyAvailability(bool bIsEnggMenuProxyAvailable);
    //________________________________________________________________________________________________
    
    /**
     * @brief startExtractingDebugsLogToUsb: this function will call to extract the logs from system to USB Connected.
     * @param void.
     * @return void.
     */
    void startExtractingDebugsLogToUsb();

    //________________________________________________________________________________________________
    /**
     * @brief	setExtractLogsStatus: This method updates the extract logs status.
     * @param   eExtractLogsProcessStatus: This will give the info regarding the extract Logs status(SUCCESS = 0,USB_NOT_CONNECTED = 1,
     *          LOGGING_NOT_ENABLED = 2,USB_DEVICE_FULL=3)
     * @return	void.
     **/
    void setExtractLogsStatus(CEnggMenuEnum::EEnggMenuExtractLogsStatus eExtractLogsProcessStatus);
    //________________________________________________________________________________________________
    /**
     * @brief   getInfotainmentPlatformName: This method gives current Infotainment Platform name.
     * @param   void.
     * @return  QString current Infotainment Platform name.
     **/
    QString getInfotainmentPlatformName();
    //________________________________________________________________________________________________
private slots:
    /**
     * @brief sltUpdateDriveNextElements: Slot to update DriveNext UI elements as per current system status
     * @param void
     * @return void
     */
    void sltUpdateDriveNextElements();
    //________________________________________________________________________________________________
    /**
     * @brief sltDriveNextPresenceChanged: Slot to update DriveNext UI elements as per DriveNext proxy status
     * @param void
     * @return void
     */
    void sltDriveNextPresenceChanged();
    //________________________________________________________________________________________________
    /**
     * @brief sltUpdateLoggingTripList: Slot to update DriveNext Logging Trip type
     * @param void
     * @return void
     */
    void sltUpdateLoggingTripList();
    //________________________________________________________________________________________________
    /**
     * @brief sltUpdateLoggingLevelList: Slot to update DriveNext Logging level type
     * @param void
     * @return void
     */
    void sltUpdateLoggingLevelList();
    //________________________________________________________________________________________________
    /**
     * @brief sltUpdateLoggingLocationList: Slot to update DriveNext Logging location type
     * @param void
     * @return void
     */
    void sltUpdateLoggingLocationList();
    //________________________________________________________________________________________________
    /**
     * @brief sltFrequencyChanged: Slot for frequency update signal
     * @param void
     * @return void
     */
    void sltFrequencyChanged();
    //________________________________________________________________________________________________
    /**
     * @brief sltUpdateStationName: Slot for station name update signal
     * @param void
     * @return void
     */
    void sltStationNameChanged();
    //________________________________________________________________________________________________
    /**
     * @brief sltUpdateStationName: Slot for field strength update signal
     * @param void
     * @return void
     */
    void sltFieldStrengthChanged();
    //________________________________________________________________________________________________
    /**
     * @brief sltActEntSourceVolumeChanged: Slot for active source volume update signal
     * @param void
     * @return void
     */
    void sltActEntSourceVolumeChanged();
    //________________________________________________________________________________________________
    /**
     * @brief sltActiveEntSrcChanged: Slot for active source update signal
     * @param void
     * @return void
     */
    void sltActiveEntSrcChanged();
    //________________________________________________________________________________________________
    /**
     * @brief sltSongTitleChanged: Slot for current track name
     * @param void
     * @return void
     */
    void sltSongTitleChanged();
    //________________________________________________________________________________________________
    /**
      * @brief sltMultipathChanged: Slot for multipath update signal
      * @param void
      * @return void
      */
    void sltMultipathChanged();
    //________________________________________________________________________________________________

    /**
     * @brief sltBitRateChanged: Slot for Audio bit rate change event
     * @param void
     * @return void
     */
    void sltBitRateChanged();
    //________________________________________________________________________________________________
    /**
     * @brief sltSamplingRateChanged: Slot for Audio sampling rate change event
     * @param void
     * @return void
     */
    void sltSamplingRateChanged();
    //________________________________________________________________________________________________

    /**
    * @brief sltVehicleSpeedChanged: Slot for vehicle speed change event
    * @param void
    * @return void
    */
    void sltVehicleSpeedChanged();
    //________________________________________________________________________________________________
    /**
    * @brief sltNowPlayingMetadataChanged: Slot for now playing metadata(audio/video) change event
    * @param void
    * @return void
    */
    void sltNowPlayingMetadataChanged();

    /**
      * @brief sltPowerModeChanged: Slot for Power Mode update signal
      * @param void
      * @return void
      */
    void sltPowerModeChanged();
    //________________________________________________________________________________________________
    /**
    * @brief sltSWCConnectionStatusChanged: Slot for SWC connection status change event
    * @param void
    * @return void
    */
    void sltSWCConnectionStatusChanged();
    //________________________________________________________________________________________________
    /**
    * @brief sltMICConnectionStatusChanged: Slot for MIC connection status change event
    * @param void
    * @return void
    */
    void sltMICConnectionStatusChanged();
    //________________________________________________________________________________________________

    /**
    * @brief sltVideoCodecChanged: Slot for video codec value change event
    * @param void
    * @return void
    */
    void sltVideoCodecChanged();
    //________________________________________________________________________________________________
    /**
    * @brief sltVideoFrameRateChanged: Slot for video frame rate change event
    * @param void
    * @return void
    */
    void sltVideoFrameRateChanged();
    //________________________________________________________________________________________________
    /**
    * @brief sltVideoResolutionChanged: Slot for video resolution change event
    * @param void
    * @return void
    */
    void sltVideoResolutionChanged();
    //________________________________________________________________________________________________
    /**
    * @brief sltMediaFormatChanged: Slot for Media format change event
    * @param void
    * @return void
    */
    void sltMediaFormatChanged();
    //________________________________________________________________________________________________
    /**
    * @brief sltAudioSamplingRateChanged: Slot for audio sampling rate change event
    * @param void
    * @return void
    */
    void sltAudioSamplingRateChanged();
    //________________________________________________________________________________________________
    /**
    * @brief sltAudioCodecChanged: Slot for MIC audio codec change event
    * @param void
    * @return void
    */
    void sltAudioCodecChanged();
    //________________________________________________________________________________________________

signals:
    /**
    * @brief	sigEnggMenuCurrentListModelChanged : signal emits when enggMenuCurrentListModel gets changed
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigEnggMenuCurrentListModelChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	sigEnggMenuScreenTitleChanged : signal emits when enggMenuScreenTitle gets changed
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigEnggMenuScreenTitleChanged();

    //________________________________________________________________________________________________

    /**
    * @brief	sigEnggMenuCurrentScreenChanged : signal emits when CurrentScreen gets changed
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigEnggMenuCurrentScreenChanged();

    //________________________________________________________________________________________________

    /**
    * @brief	sigEnggMenuTestAutomationStatusChanged : signal emits when Status of Test Automation gets changed
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigEnggMenuTestAutomationStatusChanged();

    /**
    * @brief	sigFactoryResetWaitingStatusChanged : signal emits when factory reset waiting status gets changed
    * @param	bool bFactoryrestWaitingStatus: contains status about factory reset waiting
    * @return	void.
    **/
    Q_SIGNAL void sigFactoryResetWaitingStatusChanged(bool bFactoryrestWaitingStatus);

    /**
    * @brief	sigFactoryResetCompletionStatusChanged : signal emits when factory reset waiting status gets changed
    * @param	bool bFactoryrestWaitingStatus: contains status about factory reset completion
    * @return	void.
    **/
    Q_SIGNAL void sigFactoryResetCompletionStatusChanged(bool bFactoryrestCompletionStatus);

    /**
    * @brief	sigButtonPanelHKPressedChanged : signal emits when Button Panel HardKey status gets changed
    * @param	int iKeyCode: contains the Code of The hardKey Pressed.
    * @param	int iKeyState: contains the state of The hardKey Pressed.
    * @return	void.
    **/
    void sigButtonPanelHKPressedChanged(int iKeyCode, int iKeyState);


    /**
    * @brief	sigEnggMenuProxyStatusChanged : signal emits when Engg Menu Proxy status gets changed
    * @param	void.
    * @return	void.
    **/
    void sigEnggMenuProxyStatusChanged();

    //________________________________________________________________________________________________
    
public slots:
    //________________________________________________________________________________________________
protected:

    /**
    * @brief	toggleEnggCheckbox : This function will call the service corresponding to the List Item clicked.
    * @param	bCheckboxStatus: contains the status of checkbox i.e checked or unchecked.
    * @param	iListItemId: contains the id of the list item
    * @return	void.
    **/
    Q_INVOKABLE void toggleEnggCheckbox(bool bCheckboxStatus,int iListItemId);

    /**
    * @brief	invToggleEnggRadioButton : This invocable function will call the service corresponding to the List Item clicked.
    * @param	bRadioButton: contains the status of Radio Button i.e checked or unchecked.
    * @param	iListItemId: contains the id of the list item
    * @return	void.
    **/
    Q_INVOKABLE void invToggleEnggRadioButton(bool bRadioButton,int iListItemId);

    /**
    * @brief	processEnggMenuItemClick : Whenever user clicks any item which does not use Raising Event, so we can process that here.
    * @param	iListItemId: contains the id of the list item
    * @return	void.
    **/
    Q_INVOKABLE void processEnggMenuItemClick(int iListItemId);
    //________________________________________________________________________________________________
private:
    /**
    * @brief	toggleEnggDebugCheckbox : This function will call the service of the item present in Debug Log.
    * @param	bCheckboxStatus: contains the status of checkbox i.e checked or unchecked.
    * @param	iListItemId: contains the id of the list item
    * @return	void.
    **/
    void toggleEnggDebugCheckbox(bool bCheckboxStatus,int iListItemId);

    /**
    * @brief	changeDriveNextDebugLevel : This function will call the service flow to change DriveNext debug level.
    * @param	iValue: contains new value to update
    * @return	void.
    **/
    void changeDriveNextDebugLevel(int iValue);

    /**
    * @brief	changeDriveNextLogType : This function will call the service flow to change DriveNext debug log trip.
    * @param	iValue: contains new value to update
    * @return	void.
    **/
    void changeDriveNextLogType(int iValue);

    /**
    * @brief	changeDriveNextLoggingLocation : This function will call the service flow to change DriveNext debug log location.
    * @param	iValue: contains new value to update
    * @return	void.
    **/
    void changeDriveNextLoggingLocation(int iValue);
    //________________________________________________________________________________________________
    /**
    * @brief	connectSignals: This function will connect signals from services to the corresponding slots in engineering menu
    * @param	void
    * @return	void
    **/
    void connectSignals();

    /**
      * @brief m_pEnggAdaptor: for maintaining singleton class instance
     */
    static CEnggAdaptor* m_pEnggAdaptor;

    /**
     * @brief m_pEnggMenuCurrentListModel: CEnggMenuListModel pointer which holds the currentModel of the list
     */
    CEnggMenuListModel *m_pEnggMenuCurrentListModel;

    /**
     * @brief m_eEnggMenuCurrentScreen: Enum that contains index of CurrentScreen
     */
    CEnggMenuEnum::EEnggMenuScreen m_eEnggMenuCurrentScreen;

    /**
     * @brief m_strEnggMenuScreenTitle: String that contains the Title of Current List Screen.
     */
    QString m_strEnggMenuScreenTitle;

    /**
    * @brief m_iActiveSource: contains the current active source.
    **/
    int m_iActiveSource;

    /**
    * @brief m_iCurrentTestMode: contains the current mode(audio/video)
    **/

    int m_iCurrentTestMode;

    /**
     * @brief m_bIsEnggMenuProxyAvailable: holds the status of EnggMenu Proxy Availability.
     */
    bool m_bIsEnggMenuProxyAvailable;

    /**
     * @brief :Pointers declaration to Different Models used in Engg Menu.
     */
    CEnggMenuListModel *m_pEnggModelEnggMain;
    CEnggMenuListModel *m_pEnggModelDebugLog;
    CEnggMenuListModel *m_pEnggModelIllumination;
    CEnggMenuListModel *m_pEnggModelSysConfig;
    CEnggMenuListModel *m_pEnggModelTestModeTuner;
    CEnggMenuListModel *m_pEnggModelTestModeAudioMedia;
    CEnggMenuListModel *m_pEnggModelTestModeVideoMedia;
    CEnggMenuListModel *m_pEnggModelSysConfig16RPart;

    CEnggMenuListModel *m_pEnggModelDriveNext;
    CEnggMenuListModel *m_pEnggModelDriveNextDebug;
    CEnggMenuListModel *m_pEnggModelDriveNextLog;
    CEnggMenuListModel *m_pEnggModelDriveNextLogging;
    CEnggMenuListModel *m_pEnggModelDriveNextDetails;
    CEnggMenuListModel *m_pEnggModelDriveNextDetailsEfficiency;
    CEnggMenuListModel *m_pEnggModelDriveNextDetailsBraking;
    CEnggMenuListModel *m_pEnggModelDriveNextDetailsAcceleration;
    CEnggMenuListModel *m_pEnggModelDriveNextDetailsGearShift;
    CEnggMenuListModel *m_pEnggModelDriveNextDetailsGeneric;
    CEnggMenuListModel *m_pEnggModelDriveNextDetailsSafety;


    /**
     * @brief m_pEnggMenuResource: pointer of EnggMenuResource class.
     */
    IEnggMenuResource *m_pEnggMenuResource;


};

#endif // CENGGADAPTOR_H
