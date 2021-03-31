/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CHomeAdaptor.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CHomeAdaptor, an Adaptor for Home module,
 * CHomeAdaptor is singleton class used to communicate with qml,resources of Home module.
 */

#ifndef CHOMEADAPTOR_H
#define CHOMEADAPTOR_H

#include <QObject>
#include <QString>
#include "logging.h"
#include "CFramework.h"
#include "CHomeUpdateShortcutModel.h"
#include "CPersistencyAdaptor.h"
#include "CHardKeyEnum.h"
#include "CHomeConfigureFavHKModel.h"

class CHomeApplication;
class CHomeEventHandler;
class CHomeSM;
class CDHomeShortcut;

/**
 * @brief CHomeAdaptor, an Adaptor for Home module,
 * It is singleton class used to communicate with qml,resources of Home module.
 */
class CHomeAdaptor : public QObject
{
    Q_OBJECT

    // Properties //
    // to get home shortcut button information from CDHomeShortcut
    Q_PROPERTY( QList<QObject*> homeShortcutsList READ homeShortcutsList NOTIFY sigHomeShortcutsListChanged)

    // to get id of shortcut associated with particular shortcut slot on home screen
    Q_PROPERTY(QList<int> shortcutsId READ shortcutsId NOTIFY sigShortcutsIdChanged)

    // to get total pages need to show on home screen
    Q_PROPERTY(int shortcutPages READ shortcutPages NOTIFY sigShortcutPagesChanged)

    // to get set current visible page on home screen
    Q_PROPERTY(int currentPageIndex READ currentPageIndex WRITE setCurrentPageIndex NOTIFY sigCurrentPageIndexChanged)

    // to get total number of shortcuts slots including blank on home screen
    Q_PROPERTY(int shortcutsLength READ shortcutsLength NOTIFY sigShortcutsLengthChanged)

    // to get set shortcut which is selected to edit
    Q_PROPERTY(int shortcutToEdit READ shortcutToEdit NOTIFY sigShortcutToEditChanged)

    // to get set current favorite harkey code(selection)
    Q_PROPERTY(CHardKeyEnum::EFavKeyCode eCurrentFavKeyCode READ eCurrentFavKeyCode WRITE setCurrentFavKeyCode)

    // to get Unused shortcutId list used in update shortcut qml screen
    Q_PROPERTY(QAbstractListModel* unusedShortcuts READ unusedShortcuts NOTIFY sigUnusedShortcutsChanged)

    // to get model for configure favorite key screen list.
    Q_PROPERTY(QAbstractListModel* objFavKeyListModel READ objFavKeyListModel CONSTANT)

public:
    /**
    * @brief	CHomeAdaptor::getInstance is static method used to get instance of singleton class CHomeAdaptor
    * @param	void.
    * @return	CHomeAdaptor.
    **/
    static CHomeAdaptor& getInstance();
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeAdaptor::~CHomeAdaptor is destructor of singleton class CHomeAdaptor
    * @param	NA.
    * @return	NA.
    **/
    ~CHomeAdaptor();
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeAdaptor::initAdaptorProperties is method used to inatialise adaptor properties.
    * @param	void.
    * @return	void.
    **/
    void initAdaptorProperties();

    /**
    * @brief	CHomeAdaptor::isShortcutAvailable is method used check availability state for given shortcut ID.
    * @param	CHomeEnum::EHomeShortcutsUID shortcut id.
    * @return	bool: true if DID is available for ID given, otherwise false
    **/
    bool isShortcutAvailable(CHomeEnum::EHomeShortcutsUID eHomeShortcutsUID);

    /**
    * @brief	CHomeAdaptor::validateHomeSlotIndex is method used to validate Persistency Values for given home slot.
    * @param	EPersistencyKeys home slot number.
    * @return	bool : returns false if validation failed and data is reset to default else true
    **/
    bool validateHomeSlotIndex(EPersistencyKeys ePersistencyKey);

    /**
    * @brief	CHomeAdaptor::validateHomeWithEOLSettings is method used to validate EOL settings Values for home shortcuts.
    * @param	void.
    * @return	void.
    **/
    void validateHomeWithEOLSettings();

    /**
    * @brief	CHomeAdaptor::updateHomeScreenSlots is method used to update home screen slots.
    *           shall be called from
    *               init home module
    *               add/remove shortcut on home page
    *               DID changed for home shortcuts
    * @param	void.
    * @return	void.
    **/
    void updateHomeScreenSlots();

    /**
    * @brief	CHomeAdaptor::connectSignals is method used to link slots with respective module adaptor properties.
    * @param	void.
    * @return	void.
    **/
    void connectSignals();
    /**
    * @brief	CHomeAdaptor::linkShortcutCallbackFunctions is method used to link callback functions with adaptor properties.
    * @param	void.
    * @return	void.
    **/
    void linkShortcutCallbackFunctions();
    /**
    * @brief	CHomeAdaptor::initUnusedShortcutsList is method used to initialize unused shortcuts list.
    * @param	void.
    * @return	void.
    **/
    void initUnusedShortcutsList();
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeAdaptor::initFavKeyModel is method used to initialize favorite key list model.
    * @param	void.
    * @return	void.
    **/
    void initFavKeyModel();
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeAdaptor::addItemFavKeyModel is method used to add item in favHKModel after DID check.
    * @param	CHardKeyEnum::EFavKeyCode: Fav hardkey KeyCode.
    * @param    CHomeEnum::EHomeShortcutsUID shortcut ID of respective fav key.
    * @return	void.
    **/
    void addItemFavKeyModel(CHardKeyEnum::EFavKeyCode eFavHKId, CHomeEnum::EHomeShortcutsUID eShortcutId);
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeAdaptor::cbAddShortcutClicked is method used get callback for "Add Shortcut" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbAddShortcutClicked(int iShortcutIndex);

    /**
    * @brief	CHomeAdaptor::cbAndroidAutoClicked is method used get callback for "Android Auto" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbAndroidAutoClicked(int iShortcutIndex);
    /**
    * @brief	CHomeAdaptor::cbAuxInClicked is method used get callback for "Aux In" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbAuxInClicked(int iShortcutIndex);

    /**
    * @brief	CHomeAdaptor::cbBluetoothClicked is method used get callback for "Bluetooth" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbBluetoothClicked(int iShortcutIndex);

    /**
    * @brief	CHomeAdaptor::cbCarPlayClicked is method used get callback for "Apple Car Play" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbCarPlayClicked(int iShortcutIndex);

    /**
    * @brief	CHomeAdaptor::cbConnectNextClicked is method used get callback for "Connect Next" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbConnectNextClicked(int iShortcutIndex);

    /**
    * @brief	CHomeAdaptor::cbContactsClicked is method used get callback for "Contacts" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbContactsClicked(int iShortcutIndex);

    /**
    * @brief	CHomeAdaptor::cbDoodleClicked is method used get callback for "Doodle" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbDoodleClicked(int iShortcutIndex);

    /**
    * @brief	CHomeAdaptor::cbDriveNextClicked is method used get callback for "DriveNext" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbDriveNextClicked(int iShortcutIndex);

    /**
    * @brief	CHomeAdaptor::cbFavouriteClicked is method used get callback for "Favourite" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbFavouriteClicked(int iShortcutIndex);

    /**
    * @brief	CHomeAdaptor::cbHelpClicked is method used get callback for "Help" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbHelpClicked(int iShortcutIndex);

    /**
    * @brief	CHomeAdaptor::cbIpodClicked is method used get callback for "Ipod" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbIpodClicked(int iShortcutIndex);

    /**
    * @brief	CHomeAdaptor::cbAmbientLightClicked is method used get callback for "AmbientLight" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbAmbientLightClicked(int iShortcutIndex);

    /**
    * @brief	CHomeAdaptor::cbNavigationClicked is method used get callback for "Navigation" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbNavigationClicked(int iShortcutIndex);

    /**
    * @brief	CHomeAdaptor::cbParkAssistClicked is method used get callback for "Park Assist" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbParkAssistClicked(int iShortcutIndex);

    /**
    * @brief	CHomeAdaptor::cbPhoneClicked is method used get callback for "Phone" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbPhoneClicked(int iShortcutIndex);

    /**
    * @brief	CHomeAdaptor::cbPhoneClicked is method used get callback for "Phone" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbPhoneSetupClicked(int iShortcutIndex);

    /**
    * @brief	CHomeAdaptor::cbRadioClicked is method used get callback for "Radio" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbRadioClicked(int iShortcutIndex);
    /**
    * @brief	CHomeAdaptor::cbUSBClicked is method used get callback for "USB" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbUSBClicked(int iShortcutIndex);
    /**
    * @brief	CHomeAdaptor::cbVoiceCommandClicked is method used get callback for "Voice Command" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbVoiceCommandClicked(int iShortcutIndex);
    /**
    * @brief	CHomeAdaptor::cbAudioSettingClicked is method used get callback for "Audio Setting" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbAudioSettingClicked(int iShortcutIndex);
    /**
    * @brief	CHomeAdaptor::cbVehicleSettingClicked is method used get callback for "Vehicle setting" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbVehicleSettingClicked(int iShortcutIndex);
    /**
    * @brief	CHomeAdaptor::cbThemesClicked is method used get callback for "Themes" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbThemesClicked(int iShortcutIndex);
    /**
    * @brief	CHomeAdaptor::cbAudioPresetClicked is method used get callback for "Audio Preset" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbAudioPresetClicked(int iShortcutIndex);
    /**
     * @brief cbSettingsClicked is method used to get callback for "Settings" button
     * @param iShortcutIndex - slot index on which user clicked
     * @return void
     */
    void cbSettingsClicked(int iShortcutIndex);
    /**
     * @brief cbW3WClicked is method used to get callback for "W3W" button
     * @param iShortcutIndex - slot index on which user clicked
     * @return void
     */
    void cbW3WClicked(int iShortcutIndex);
        /**
    * @brief	CHomeAdaptor::cbDemoSoundClicked is method used get callback for "Sound Demo" button.
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void cbSoundDemoClicked(int iShortcutIndex);
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeAdaptor::homeShortcutsList is get method for "homeShortcutsList" qml property.
    * @param	void.
    * @return	QList<QObject*> : home shorcut list.
    **/
    QList<QObject*> homeShortcutsList();
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeAdaptor::shortcutsId is get method for "shortcutsId" qml property.
    * @param	void.
    * @return	QList<int> : home shortcut ID's list.
    **/
    QList<int> shortcutsId();
    /**
    * @brief	CHomeAdaptor::setShortcutsId is set method for "shortcutsId" qml property.
    * @param	liShortcutList : shortcut id list.
    * @return	void.
    **/
    void setShortcutsId(QList<int> liShortcutList);
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeAdaptor::eCurrentFavKeyCode is get method for current favorite hardkey selection.
    * @param	void.
    * @return	CHardKeyEnum::EFavKeyCode : fav HK key code.
    **/
    CHardKeyEnum::EFavKeyCode eCurrentFavKeyCode();
    /**
    * @brief	CHomeAdaptor::setCurrentFavKeyCode is set method for current favorite hardkey selection.
    * @param	CHardKeyEnum::EFavKeyCode : favorite HK key code.
    * @return	void.
    **/
    void setCurrentFavKeyCode(CHardKeyEnum::EFavKeyCode eFavKeyCode);
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeAdaptor::shortcutPages is get method for "shortcutPages" qml property.
    * @param	void.
    * @return	int : number of shortcut pages on home screen.
    **/
    int shortcutPages();
    /**
    * @brief	CHomeAdaptor::setShortcutPages is set method for "shortcutPages" qml property.
    * @param	int : no of shortcut pages.
    * @return	void.
    **/
    void setShortcutPages(int iPageCount);
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeAdaptor::currentPageIndex is get method for "currentPageIndex" qml property.
    * @param	void.
    * @return	int.
    **/
    int currentPageIndex();
    /**
    * @brief	CHomeAdaptor::setCurrentPageIndex is set method for "currentPageIndex" qml property.
    * @param	int : current page index.
    * @return	void.
    **/
    void setCurrentPageIndex(int iCurrentPageIndex);
    /**
    * @brief	CHomeAdaptor::updateHomeButtonEnableStatus is method to update home button enable status.
    * @param	void.
    * @return	void.
    **/
    void updateHomeButtonEnableStatus();
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeAdaptor::shortcutsLength is get method for "shortcutsLength" qml property.
    * @param	void.
    * @return	int : shortcut list length.
    **/
    int shortcutsLength();
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeAdaptor::shortcutToEdit is get method for "shortcutToEdit" qml property.
    * @param	void.
    * @return	int : shortcut Id of editable shortcut.
    **/
    int shortcutToEdit();
    /**
    * @brief	CHomeAdaptor::setShortcutToEdit is set method for "shortcutToEdit" qml property.
    * @param	int : Id of shortcut to edit.
    * @return	void.
    **/
    void setShortcutToEdit(int iShortcutId);
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeAdaptor::isOnHomeScreen used to get HMI is on home scren or not.
    * @param	void.
    * @return	bool TRUE when HMI is on home screen, otherwise FALSE.
    **/
    bool isOnHomeScreen();
    /**
    * @brief	CHomeAdaptor::setOnHomeScreen used to set HMI is on home scren or not.
    * @param	bool TRUE when HMI is on home screen, otherwise FALSE.
    * @return	void.
    **/
    void setOnHomeScreen(bool bStatus);
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeAdaptor::isShortcutOnDisplayScreen is method to check given shortcut is currently present on display screen or not.
    * @param	EHomeShortcutsUID, shortcut id enum.
    * @return	bool, true when shortcut is on display screen - false when shortcut is not on display screen
    **/
    bool isShortcutOnDisplayScreen(const CHomeEnum::EHomeShortcutsUID eShortcutId);
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeAdaptor::unusedShortcuts is get method for "unusedShortcuts" qml property.
    * @param	void.
    * @return	CHomeUpdateShortcutModel* : unsed shortcuts data model.
    **/
    CHomeUpdateShortcutModel* unusedShortcuts();
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeAdaptor::objFavKeyListModel is get method for "objFavKeyListModel" qml property.
    * @param	void.
    * @return	CHomeConfigureFavHKModel* : fav HK list model.
    **/
    Q_INVOKABLE CHomeConfigureFavHKModel *objFavKeyListModel();
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeAdaptor::invUpdateShortcut is QML invocable method which gives update shortcut callback.
    * @param	iShortcutIndex : shortcut slotIndex.
    * @param    iShortcutId : shortcut Unique Id
    * @return	void.
    **/
    Q_INVOKABLE void invUpdateShortcut(int iShortcutIndex, int iShortcutId = -1);
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeAdaptor::invShowUpdateHomeShortcutPopup is QML invokable method which call popup manager
    *           method to display remove/replace home shortcut popup.
    * @param	iSlotIndex : index on which shortcut icon shall get update
    * @return	void.
    **/
    Q_INVOKABLE void invShowUpdateHomeShortcutPopup(int iSlotIndex);
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeAdaptor::invShortcutToEditTitle is a method to get Title of shortcut to edit.
    * @param	void.
    * @return	QString : Title of the shortcut to be edit.
    **/
    Q_INVOKABLE QString invShortcutToEditTitle();
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeAdaptor::invIsFixShortcut is a method to get given shortcut is fix or not.
    * @param	CHomeEnum::EHomeShortcutsUID shortcut id to check.
    * @return	bool is given shortcut marked as fix.
    **/
    Q_INVOKABLE bool invIsFixedShortcut(CHomeEnum::EHomeShortcutsUID eShortcutID);
signals:
    /**
    * @brief	CHomeAdaptor::sigHomeShortcutsListChanged is QML signal for "currentPageIndex" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigHomeShortcutsListChanged();
    /**
    * @brief	CHomeAdaptor::sigShortcutsIdChanged is QML signal for "shortcutsId" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigShortcutsIdChanged();
    /**
    * @brief	CHomeAdaptor::sigShortcutPagesChanged is QML signal for "shortcutPages" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigShortcutPagesChanged();
    /**
    * @brief	CHomeAdaptor::sigCurrentPageIndexChanged is QML signal for "currentPageIndex" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigCurrentPageIndexChanged();
    /**
    * @brief	CHomeAdaptor::sigShortcutsLengthChanged is QML signal for "shortcutsLength" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigShortcutsLengthChanged();
    /**
    * @brief	CHomeAdaptor::sigShortcutToEditChanged is QML signal for "shortcutToEdit" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigShortcutToEditChanged();
    /**
    * @brief	CHomeAdaptor::sigUnusedShortcutsChanged is QML signal for "unusedShortcuts" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigUnusedShortcutsChanged();
    //________________________________________________________________________________________________
public slots:
    /**
    * @brief	CHomeAdaptor::slotEOLChanged is method used to handle updated EOL status.
    * @param	void.
    * @return	void.
    **/
    void slotEOLChanged();
    /**
    * @brief	CHomeAdaptor::slotActiveChanged_AndroidAuto is slot to catch "AndroidAuto" active changes.
    * @param	bActiveStatus : true if shortcut is active
    * @return	void.
    **/
    void slotActiveChanged_AndroidAuto(bool bActiveStatus);
    /**
    * @brief	CHomeAdaptor::slotActiveChanged_AuxIn is slot to catch "AuxIn" active changes.
    * @param	void.
    * @return	void.
    **/
    void slotActiveChanged_AuxIn();
    /**
    * @brief	CHomeAdaptor::slotActiveChanged_Bluetooth is slot to catch "Bluetooth" active changes.
    * @param	void.
    * @return	void.
    **/
    void slotActiveChanged_Bluetooth();
    /**
    * @brief	CHomeAdaptor::slotActiveChanged_CarPlay is slot to catch "CarPlay" active changes.
    * @param	bActiveStatus : true if shortcut is active
    * @return	void.
    **/
    void slotActiveChanged_CarPlay(bool bActiveStatus);
    /**
    * @brief	CHomeAdaptor::slotActiveChanged_ConnectNext is slot to catch "ConnectNext" active changes.
    * @param	bActiveStatus : true if shortcut is active
    * @return	void.
    **/
    void slotActiveChanged_ConnectNext(bool bActiveStatus);
    /**
    * @brief	CHomeAdaptor::slotActiveChanged_Contacts is slot to catch "Contacts" active changes.
    * @param	bActiveStatus : true if shortcut is active
    * @return	void.
    **/
    void slotActiveChanged_Contacts(bool bActiveStatus);
    /**
    * @brief	CHomeAdaptor::slotActiveChanged_Doodle is slot to catch "Doodle" active changes.
    * @param	void.
    * @return	void.
    **/
    void slotActiveChanged_Doodle();
    /**
    * @brief	CHomeAdaptor::slotActiveChanged_DriveNext is slot to catch "DriveNext" active changes.
    * @param	void.
    * @return	void.
    **/
    void slotActiveChanged_DriveNext();
    /**
    * @brief	CHomeAdaptor::slotActiveChanged_Favourite is slot to catch "Favourite" active changes.
    * @param	bActiveStatus : true if shortcut is active
    * @return	void.
    **/
    void slotActiveChanged_Favourite(bool bActiveStatus);
    /**
    * @brief	CHomeAdaptor::slotActiveChanged_Ipod is slot to catch "Ipod" active changes.
    * @param	bActiveStatus : true if shortcut is active
    * @return	void.
    **/
    void slotActiveChanged_Help(bool bActiveStatus);
    /**
    * @brief	CHomeAdaptor::slotActiveChanged_ XXX is slot to catch "XXX" active changes.
    * @param	void.
    * @return	void.
    **/
    void slotActiveChanged_Ipod();
    /**
    * @brief	CHomeAdaptor::slotActiveChanged_AmbientLight is slot to catch "AmbientLight" active changes.
    * @param	void.
    * @return	void.
    **/
    void slotActiveChanged_AmbientLight();
    /**
    * @brief	CHomeAdaptor::slotActiveChanged_Navigation is slot to catch "Navigation" active changes.
    * @param	bActiveStatus : true if shortcut is active
    * @return	void.
    **/
    void slotActiveChanged_Navigation(bool bActiveStatus);
    /**
    * @brief	CHomeAdaptor::slotActiveChanged_ParkAssist is slot to catch "ParkAssist" active changes.
    * @param	bActiveStatus : true if shortcut is active
    * @return	void.
    **/
    void slotActiveChanged_ParkAssist(bool bActiveStatus);
    /**
    * @brief	CHomeAdaptor::slotActiveChanged_Phone is slot to catch "Phone" active changes.
    * @param	bActiveStatus : true if shortcut is active
    * @return	void.
    **/
    void slotActiveChanged_Phone(bool bActiveStatus);
    /**
    * @brief	CHomeAdaptor::slotActiveChanged_Radio is slot to catch "Radio" active changes.
    * @param	void
    * @return	void.
    **/
    void slotActiveChanged_Radio();
    /**
    * @brief	CHomeAdaptor::slotActiveChanged_USB is slot to catch "USB" active changes.
    * @param	void.
    * @return	void.
    **/
    void slotActiveChanged_USB();
    /**
    * @brief	CHomeAdaptor::slotActiveChanged_VoiceCommand is slot to catch "VoiceCommand" active changes.
    * @param	bActiveStatus : true if shortcut is active
    * @return	void.
    **/
    void slotActiveChanged_VoiceCommand(bool bActiveStatus);
    /**
    * @brief	CHomeAdaptor::slotActiveChanged_AudioSetting is slot to catch "AudioSetting" active changes.
    * @param	bActiveStatus : true if shortcut is active
    * @return	void.
    **/
    void slotActiveChanged_AudioSetting(bool bActiveStatus);
    /**
    * @brief	CHomeAdaptor::slotActiveChanged_VehicleSetting is slot to catch "VehicleSetting" active changes.
    * @param	bActiveStatus : true if shortcut is active
    * @return	void.
    **/
    void slotActiveChanged_VehicleSetting(bool bActiveStatus);
    /**
    * @brief	CHomeAdaptor::slotActiveChanged_Themes is slot to catch "Themes" active changes.
    * @param	bActiveStatus : true if shortcut is active
    * @return	void.
    **/
    void slotActiveChanged_Themes(bool bActiveStatus);

    /**
     * @brief   slotAvailabilityChanged_AuxIn: is slot catch "Aux" Connection status change
     * @param   void
     * @return  void
     */
    void slotAvailabilityChanged_AuxIn();

    /**
     * @brief   sltPowerModeChanged: is slot for power mode status change
     * @param   void
     * @return  void
     */
    void sltPowerModeChanged();

    /**
     * @brief slotActiveChanged_W3W is slot for w3w status change
     * @param w3wCoreProxyStatus w3w core proxy status
     * @return void
     */
    void slotActiveChanged_W3W(bool w3wCoreProxyStatus);

    //________________________________________________________________________________________________
protected:

    //________________________________________________________________________________________________
private:
    /**
    * @brief	CHomeAdaptor::CHomeAdaptor private constructor for singleton class CHomeAdaptor.
    * @param	QObject.
    * @return	NA.
    **/
    explicit CHomeAdaptor(QObject *parent = nullptr); // for singleton pattern class
    //________________________________________________________________________________________________
private:
    static CHomeAdaptor* mpHomeAdaptor; // for maintaining singleton class instance

    QList<QObject*> m_lCDHomeShortcuts;     // member list contains shortcuts information and states
    QList<int> m_liShortcutsId;             // member variable for property shortcutsId
    QList<CHardKeyEnum::EFavKeyCode> m_liFavHK; // member variable list for fav hk available option

    CHardKeyEnum::EFavKeyCode m_eFavKeyCode;// member variable holds current favorite key action
    int m_iShortcutPages;                   // member variable for property shortcutPages
    int m_iCurrentPageIndex;                // member variable for property currentPageIndex
    int m_iShortcutToEdit;                  // member variable for property shortcutToEdit

    bool m_bOnHomeScreen;                   // member variable to hold HMI is on home screen or not
    /**
     * @brief m_bIsInitializationInProgress: member variable to maintain initialization progress status
     */
    bool m_bIsInitializationInProgress;

    CHomeUpdateShortcutModel *m_pHomeUpdateShortcutModel = nullptr;   // member variable for property unusedShortcuts

    CHomeConfigureFavHKModel m_objHomeFavKeyModel;   // member variable for property pHomefavKeyModel
};

#endif // CHOMEADAPTOR_H
