/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CSetupAdaptor.h
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * CSetupAdaptor.h, setup module adaptor header file, responsible for creating setup
 *                  list model class instances and contains current active model of setup
 */
#ifndef CSETUPADAPTOR_H
#define CSETUPADAPTOR_H

#include <QObject>
#include "logging.h"
#include "CFramework.h"
#include "CSetupEnums.h"
#include "CSetupMainListModel.h"
#include "CSetupAudioListModel.h"
#include "CSetupBMTListModel.h"
#include "CSetupAudioPresetListModel.h"
#include "CSetupGeneralListModel.h"
#include "CSetupVolumeSettingsListModel.h"
#include "EnggMenuResource/interfaces/IEnggMenuResource.h"
#include "EnggMenu/CEnggAdaptor.h"
#include "ResourceFactory.hpp"
#include "CPopupManager.h"
#include "CPowerModeAdaptor.h"
#include "CPowerModeEnums.h"
#include "CSetupListModel.h"
#include "CThemeSettingsModel.h"
#include "CAudioSettingsModel.h"
#include "CThemeElement.h"
#include "CThemeSetupWithDriveModeListModel.h"

/**
 * @brief The CSetupAdaptor class: Responsible for creating setup list model class instances and contains current active model of setup
 */
class CSetupAdaptor : public QObject
{
    Q_OBJECT

    /* To get current audio settings screen */
    Q_PROPERTY(CSetupEnums::EAudioSetupCurrentScreen eCurrentAudioSettingsScreen   READ eCurrentAudioSettingsScreen NOTIFY sigCurrentAudioSettingsScreenChanged)

    /* To get theme element list */
    Q_PROPERTY( QList<QObject*> themeElementsList READ themeElementsList NOTIFY sigThemeElementList)

    /* To get edit mode theme preset object */
    Q_PROPERTY(QObject* editModeThemeObject READ editModeThemeObject NOTIFY sigEditModeThemeObjectChanged)

    /* To get the current model of the setup */
    Q_PROPERTY(QAbstractListModel* currentModel READ currentModel NOTIFY sigCurrentModelChanged)

    /* To get the sub model of the delay timer */
    Q_PROPERTY(QAbstractListModel* parkAssistDelayTimerSubModel READ parkAssistDelayTimerSubModel NOTIFY sigParkAssistDelayTimerSubModelChanged)

    /* To get the sub model of the approach lamps */
    Q_PROPERTY(QAbstractListModel* approachLampsSubModel READ approachLampsSubModel NOTIFY sigApproachLampsSubModelChanged)

    /* To get the sub model of the park assist tone */
    Q_PROPERTY(QAbstractListModel* parkAssistToneSubModel READ parkAssistToneSubModel NOTIFY sigParkAssistToneSubModelChanged)

    /* To get the theme preset model */
    Q_PROPERTY(QAbstractListModel* themepresetModel READ themepresetModel CONSTANT)

    /* To get the Audio Settings model */
    Q_PROPERTY(QAbstractListModel* audioSettingsModel READ audioSettingsModel CONSTANT)

    /* To get edit mode flag value */
    Q_PROPERTY(bool editModeFlag READ editModeFlag WRITE setEditModeFlag NOTIFY sigEditModeFlagChanged)

    /* To get the theme preset selected value */
    Q_PROPERTY(int presetSelection READ presetSelection WRITE setPresetSelection NOTIFY sigPresetSelectionChanged)

    /* To get the current active theme preset value */
    Q_PROPERTY(int curActiveThemePreset READ curActiveThemePreset NOTIFY sigCurActiveThemePresetChanged)

    /* To get the current active theme preset icon */
    Q_PROPERTY(QString activeThemePresetIcon READ activeThemePresetIcon NOTIFY sigUpdateThemePresetInfo)

    /* To get the current active theme preset text */
    Q_PROPERTY(QString activeThemePresetText READ activeThemePresetText NOTIFY sigUpdateThemePresetInfo)

    /* To get the theme item index */
    Q_PROPERTY(int expandThemeItemIndex READ expandThemeItemIndex NOTIFY sigExpandedThemeItemIndexChanged)

    /* To get the park assist item index */
    Q_PROPERTY(int expandedParkAssistItemIndex READ expandedParkAssistItemIndex NOTIFY sigExpandedParkAssistItemIndexChanged)

    /* To get the approach lamp item index */
    Q_PROPERTY(int expandedApproachLampsItemIndex READ expandedApproachLampsItemIndex NOTIFY sigExpandedAppraochLampsItemIndexChanged)

    /* To get active theme preset changed */
    Q_PROPERTY(bool currentThemeModified READ currentThemeModified WRITE setCurrentThemeModified NOTIFY sigCurrentThemeModified)

    /* property for qml to get Theme setup with drive mode list model */
    Q_PROPERTY(QAbstractListModel* themeSetupWithDriveModeListModel READ themeSetupWithDriveModeListModel    CONSTANT)

public:
    explicit CSetupAdaptor(QObject *parent = nullptr);
    ~CSetupAdaptor();

    /**
    * @brief	getInstance : This function get the instance of setup adaptor class.
    * @param	void.
    * @return   Instance of CSetupAdaptor
    */
    static CSetupAdaptor* getInstance();

    /**
    * @brief	CSetupAdaptor::connectSignals is method used to link slots with respective module adaptor properties.
    * @param	void.
    * @return	void.
    **/
    void connectSignals();

    /**
     * @brief setCurrentAudioSetupScreen : This method is to set current active audio setup screen
     * @param eAudioSetupCurrentScreen : holds enum value for current audio setup screen
     * @return void.
     */
    void setCurrentAudioSetupScreen(CSetupEnums::EAudioSetupCurrentScreen eAudioSetupCurrentScreen);

    /**
     * @brief startFactoryResetProcess: is method which will take care whether factory reset is taking place while ignition is on.
    * if its not as per required then show a pop up to Turn On ignition else show a pop up to confirm
     * @param void
     * @return void
     */
    void startFactoryResetProcess();


    /**
     * @brief setCurrentListModel: Sets the current active model of setup based on screen transition
     * @param screenId.
     * @return void
     */
    void setCurrentListModel(int screenId);

    /**
     * @brief Method to get the audio preset name.
     * @param eAudioPresets : eAudioPresets value of audio preset list model.
     * @return  Return the audio preset name.
     */
    Q_INVOKABLE QString getAudioPresetName(CAudioEnums::EAudioPresets eAudioPresets);

    /**
     * @brief isVehicleSettingAvailable : Method to get vehicle settings available status.
     * @param void
     * @return bool : vehicle settings availability status
     */
    Q_INVOKABLE bool isVehicleSettingAvailable();


    /**
    * @brief	CSetupAdaptor::factoryResetConfirmClickProcess is method which will call the resource layer function to start factory reset
    * @return	void.
    **/
    Q_INVOKABLE void factoryResetConfirmClickProcess();

    /**
     * @brief   updateThemeSetupListModelData: To update the theme setup list model data.
     * @param   iRole: Role to be updated.
     * @param   iListItemIndex: Index to be updated.
     * @param   objValue: Value to be updated.
     * @param   pThemeSetupListModel: Pointer to CSetupListModel class object.
     * @param   eSetupListOption: Variable holds the setup list item index.
     * @return  void.
     */
    void updateThemeSetupListModelData(int iRole, int iListItemIndex, const QVariant& objValue, CSetupListModel *pThemeSetupListModel,
                                              CSetupEnums::ESetupScreens eSetupListOption = CSetupEnums::SETUP_SCREEN_INVALID);

    /**
     * @brief To update the setup model data
     * @param iRole: Role to be updated
     * @param iListItemIndex: Index to be updated
     * @param value: Value to be updated
     * @param CSetupEnums::ESetupScreens:eSetupListOption variable holds the setup list screens and setup list options
     * @return void
     */
    Q_INVOKABLE void updateSetupListModelData(int iRole, int iListItemIndex, const QVariant& value, QAbstractListModel *pCurrentListModel=nullptr,
                                              CSetupEnums::ESetupScreens eSetupListOption = CSetupEnums::SETUP_SCREEN_INVALID);

    /**
     * @brief To update the setup model data for Park Assist Volume in Vehicle Setup
     * @param iRole: Role to be updated
     * @param iListItemIndex: Index to be updated
     * @param value: Value to be updated
     * @param CSetupEnums::ESetupScreens:eSetupListOption variable holds the setup list screens and setup list options
     * @return void
     */
    void updateSetupListModelDataParkAssistVolume(int iRole, int iListItemIndex, const QVariant& value, QAbstractListModel *m_pCurrentListModel=nullptr,
                                                 CSetupEnums::ESetupScreens eSetupListOption = CSetupEnums::SETUP_SCREEN_INVALID);

    /**
    * @brief themeElementsList : This is get method for "ThemeElements" qml property.
    * @param	void.
    * @return	QList<QObject*> : will get theme element list instance.
    **/
    QList<QObject *> themeElementsList();

    /**
    * @brief editModeThemeObject : This method is to get the edit mode theme object.
    * @param	void.
    * @return	QList<QObject*> : will return edit mode theme element object.
    **/
    QObject *editModeThemeObject();

    /**
    * @brief editModeFlag : This method is to get the edit mode flag.
    * @param	void.
    * @return	editModeFlag will return true on change of edit mode flag else false.
    **/
    bool editModeFlag(){ return m_bEditModeFlag; }

    /**
    * @brief setEditModeFlag :	This is to set edit mode flag from qml when user changes the theme preset values like fanspeed, temperature, air flow distribution mode etc.
    * @param	bEditModeFlag : bEditModeFlag is true on change else false.
    * @return	void.
    **/
    Q_INVOKABLE void setEditModeFlag(bool bEditModeFlag);

    /**
    * @brief requestThemePresetValuesToService : This method is to request service methods on change of theme preset like fanspeed, temperature, air flow distribution mode etc.
    * @param	pThemeElement : Theme element object
    * @return	void.
    **/
    void requestThemePresetValuesToService(CThemeElement *pThemeElement);

    /**
    * @brief applyTheme : This method is to request service methods from qml on change of theme preset like fanspeed, temperature, air flow distribution mode etc.
    * @param	bEditModeFlag : bEditModeFlag is true on change else false.
    * @param    iCurrentIndex : current index of the theme preset.
    * @return	void.
    **/
    Q_INVOKABLE void applyTheme(bool bEditModeFlag, int iCurrentIndex);

    /**
     * @brief   themeSetupWithDriveModeListModel : Method to get theme setup with drive mode list model.
     * @param   void.
     * @return  pointer to the object of class CThemeSetupWithDriveModeListModel
     */
    QAbstractListModel* themeSetupWithDriveModeListModel(){ return m_pThemeSetupWithDriveModeListModel; }

    /**
    * @brief  invApplyThemeColor : This method is to set theme color as per the user request
    * @param  int : iThemeColor
    * @return  void.
    **/
    Q_INVOKABLE void invApplyThemeColor(int iThemeColor);

    /**
    * @brief  setChangeThemeWithDriveModeStatus : This method is to set change theme with drive mode status
    * @param  bool : bStatus
    * @return  void.
    **/
    void setChangeThemeWithDriveModeStatus(bool bStatus);

    /**
    * @brief  setActiveDriveMode : This method is to set active drive mode
    * @param  CSetupEnums::EDriveModes : eDriveMode
    * @return  void.
    **/
    void setActiveDriveMode(CSetupEnums::EDriveModes eDriveMode);

    /**
     * @brief  getActiveDriveMode: This method is to get active drive mode.
     * @param  void
     * @return  CSetupEnums::EDriveModes : m_eActiveDriveMode.
     */
    CSetupEnums::EDriveModes getActiveDriveMode(){return m_eActiveDriveMode;}

    /**
    * @brief  getChangeThemeWithDriveModeStatus : This method is to get Change Theme With Drive Mode status.
    * @param  void.
    * @return  bool : m_bChangeThemeWithDriveModeStatus.
    **/
    bool getChangeThemeWithDriveModeStatus() { return m_bChangeThemeWithDriveModeStatus; }

    /**
     * @brief  getCurrentTheme: This method is to get current theme color
     * @param  void
     * @return  CSetupEnums::EThemesItem : m_eCurrThemeColor.
     */
    CSetupEnums::EThemesItem getCurrentTheme(){return m_eCurrThemeColor;}

    /**
    * @brief copyCurrentThemePresetValues :	This method is to copy current theme preset values to edit mode theme object change of fanspeed, temperature, air flow distribution mode etc.
    * @param    iCurrentIndex : current index of the theme preset.
    * @return	void.
    **/
    Q_INVOKABLE void copyCurrentThemePresetValues(int iCurrentIndex);

    /**
    * @brief presetSelection :	This method is to get current preset theme on theme preset changed.
    * @param    void.
    * @return	presetSelection: current theme preset value.
    **/
    int presetSelection() { return m_iPresetSelected; }

    /**
    * @brief setPresetSelection : This method is to set current preset theme on theme preset changed.
    * @param    presetSelection: current theme preset value.
    * @return	void.
    **/
    Q_INVOKABLE void setPresetSelection(int iPresetSelected);

    /**
     * @brief curActiveThemePreset : This method is to get current active theme preset.
     * @param   void
     * @return  curActiveThemePreset: active theme preset value
     */
    int curActiveThemePreset() {return m_iCurActiveThemePreset;}

    /**
     * @brief setCurActiveThemePreset : This method is to set current active theme preset.
     * @param iCurActiveThemePreset : current active theme preset value.
     * @return  void.
     */
    void setCurActiveThemePreset(int iCurActiveThemePreset);

    /**
    * @brief updateThemeModelData : This method is to update theme model data.
    * @param    void.
    * @return	void.
    **/
    void updateThemeModelData(CThemeElement *pThemeElement);

    /**
     * @brief launchVehicleSettings : This method is used to launch vehicle settings on possible conditions
     * @param   void.
     * @return  void.
     */
    void launchVehicleSettings();

    /**
     * @brief launchThemeSettings : This method is used to launch theme settings on possible conditions
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void launchThemeSettings();

    /**
     * @brief launchAmbientLightSettings : This method is used to launch ambient light settings on possible conditions.
     * @param   void.
     * @return  void.
     */
    void launchAmbientLightSettings();

    /**
     * @brief themeLoadingStatus : This method is to get the theme loading status.
     * @param   void.
     * @return  themeLoadingStatus: theme loading status.
     */
    bool themeLoadingStatus() {return m_bThemeLoadingStatus;}

    /**
     * @brief themeLoadingChanged : This method is to set the theme loading status to false.
     * @param   void.
     * @return  void.
     */
    void themeLoadingChanged();

    /**
     * @brief updateCurActiveThemePreset : This method is used to update the current active theme preset info.
     * @param   void.
     * @return  void.
     */
    void updateCurActiveThemePreset();

    /**
     * @brief activeThemePresetIcon : This method is to get the theme preset icon
     * @param   void.
     * @return  activeThemePresetIcon : active theme preset icon.
     */
    QString activeThemePresetIcon() {return m_strActiveThemePresetIcon; }

    /**
     * @brief activeThemePresetText : This method is to get the theme preset text
     * @param   void.
     * @return  activeThemePresetText : active theme preset text.
     */
    QString activeThemePresetText() {return m_strActiveThemePresetText; }


    /**
     * @brief expandThemeItemIndex : This method is to get the theme subitem index
     * @param   void.
     * @return  expandThemeItemIndex : theme sub item index.
     */
    int expandThemeItemIndex() {return m_iExpandedThemeItemIndex; }

    /**
     * @brief setExpandedThemeItemIndex : This method is to set the theme subitem index
     * @param iExpandedThemeItemIndex : Expanded theme sub item index
     * @return  void.
     */
    void setExpandedThemeItemIndex(int iExpandedThemeItemIndex);

    /**
     * @brief expandedParkAssistItemIndex : This method is to get the park assist item index
     * @param void
     * @return  expandedParkAssistItemIndex : park assist item index.
     */
    int expandedParkAssistItemIndex() {return m_iExpandedParkAssistItemIndex; }

    /**
     * @brief setExpandedParkAssistItemIndex : This method is to set the park assist item index
     * @param iExpandedParkAssistItemIndex : Expanded park assist item index.
     * @return void.
     */
    void setExpandedParkAssistItemIndex(int iExpandedParkAssistItemIndex);

    /**
     * @brief expandedApproachLampsItemIndex : This method is to get the approach lamp item index
     * @param   void
     * @return expandedApproachLampsItemIndex : Appraoch lamps item index.
     */
    int expandedApproachLampsItemIndex() {return m_iExpandedApproachLampsItemIndex; }

    /**
     * @brief eCurrentAudioSettingsScreen : This method is to get the current audio setup screen
     * @param   void
     * @return m_eAudioSetupCurrentScreen : enum value for current audio setup sccreen
     */
    CSetupEnums::EAudioSetupCurrentScreen eCurrentAudioSettingsScreen() { return m_eAudioSetupCurrentScreen; }

    /**
     * @brief setExpandedApproachLampsItemIndex : This method is to set the approach lamps item index
     * @param iExpandedAppraochLampsItemIndex : Expanded appraoch lamps item index.
     * @return void.
     */
    void setExpandedApproachLampsItemIndex(int iExpandedAppraochLampsItemIndex);

    /**
     * @brief toggleExpandState : This method invoked from qml to toggle exapnd and collapse park assist item
     * @param iItemIndex : park assist item index.
     * @param iListItemType : park assist list item type
     * @return void.
     */
    Q_INVOKABLE void toggleExpandState(int iItemIndex, int iListItemType);

    /**
      * @brief expandParkAssistItem : Expand the park assist item
      * @param iItemIndex : park assist item index.
      * @param iListItemType : park assist list item type
      * @return void.
      */
    void expandParkAssistItem(int iItemIndex, int iListItemType);

    /**
      * @brief collapseParkAssistItem : Collapse the park assist item
      * @param iItemIndex : park assist item index.
      * @param iListItemType : park assist list item type
      * @param iNumItemsRemoved : number of items removed from the list
      * @return void.
      */
    void collapseParkAssistItem(int iItemIndex, int iListItemType, int &iNumItemsRemoved);

    /**
     * @brief expandThemeItem: Expand the theme subitem Dropdown.
     * @param iItemId : variable holds the list item type.
     * @return void.
     */
    Q_INVOKABLE void expandThemeItem(int iItemId);

    /**
     * @brief collapseThemeItem : Collapse the theme subitem Dropdown.
     * @param   iItemId : variable holds the list item type.
     * @return  void.
     */
    Q_INVOKABLE void collapseThemeItem(int iItemId);

    /**
     * @brief toggleLightingSetupExpandState : This method invoked from qml to toggle exapnd and collapse approach lamps item
     * @param iItemIndex : approach lamps item index.
     * @param iListItemType : approach lamps list item type
     * @return void.
     */
    Q_INVOKABLE void toggleLightingSetupExpandState(int iItemIndex, int iListItemType);

    /**
       * @brief expandLightingSetupItem : Expand the approach lamp item
       * @param iItemIndex : approach lamps item index.
       * @param iListItemType : approach lamps list item type
       * @return  void.
       */
    void expandLightingSetupItem(int iItemIndex, int iListItemType);

    /**
       * @brief collapseLightingSetupItem : Collapse the approach lamp item
       * @param iItemIndex : approach lamps item index.
       * @param iListItemType : approach lamps list item type
       * @return  void.
       */
    void collapseLightingSetupItem(int iItemIndex, int iListItemType);

    /**
       * @brief saveCustomThemeValToPersistency : This method is used to save custom theme preset values to persistency
       * @param void
       * @return  void.
       */
    void saveCustomThemeValToPersistency();

    /**
       * @brief initDriveNextListModel : To initialize the DriveNext setup list model
       * @return void
       * @param void
       */
    void initDriveNextListModel();

    /**
       * @brief resetDriveNextListModel : To reset the DriveNext setup list model
       * @return void
       * @param void
       */
    void resetDriveNextListModel();

    /**
       * @brief updateDriveNextListModel : To update the DriveNext setup list model
       * @return void
       * @param void
       */
    void updateDriveNextListModel();

signals:

    /*!
       * @brief   sigCurrentAudioSettingsScreenChanged Signal emitted whenever audio settings screen is updated.
       * @param   void.
       * @return  void.
       */
    void sigCurrentAudioSettingsScreenChanged();

    /**
     * @brief sigCurrentModelChanged: Signal gets emitted on model change
     * @param void
     * @return void
     */
    void sigCurrentModelChanged();

    /**
     * @brief sigDelayTimerSubModelChanged: Signal gets emitted on park assist delay timer model change
     * @param void
     * @return void
     */
    void sigParkAssistDelayTimerSubModelChanged();

    /**
     * @brief sigParkAssistToneSubModelChanged: Signal gets emitted on park assist tone model change
     * @param void
     * @return void
     */
    void sigParkAssistToneSubModelChanged();

    /**
     * @brief sigApproachLampsSubModelChanged: Signal gets emitted on approach lamps model change
     * @param void
     * @return void
     */
    void sigApproachLampsSubModelChanged();

    /**
     * @brief sigThemeElementList: Signal gets emitted on theme elements list gets changed.
     * @param void
     * @return void
     */
    void sigThemeElementList();

    /**
     * @brief sigEditModeFlagChanged: Signal gets emitted on edit mode flag gets changed.
     * @param void
     * @return void
     */
    void sigEditModeFlagChanged();

    /**
     * @brief sigEditModeThemeObjectChanged: Signal gets emitted on edit mode object gets changed.
     * @param void
     * @return void
     */
    void sigEditModeThemeObjectChanged();

    /**
     * @brief sigPresetSelectionChanged: Signal gets emitted on preset selected gets changed.
     * @param void
     * @return void
     */
    void sigPresetSelectionChanged();

    /**
     * @brief sigCurActiveThemePresetChanged : Signal gets emitted on current active theme preset gets changed.
     * @param   void.
     * @return  void.
     */
    void sigCurActiveThemePresetChanged();

    /**
     * @brief sigUpdateThemePresetInfo : Signal gets emitted when user changes the current active theme preset
     * @param   void
     * @return  void.
     */
    void sigUpdateThemePresetInfo();

    /**
     * @brief sigExpandedThemeItemIndexChanged : Signal gets emitted when theme sub item index gets changed.
     * @param   void.
     * @return  void.
     */
    void sigExpandedThemeItemIndexChanged();

    /**
     * @brief sigExpandedParkAssistItemIndexChanged : Signal gets emitted when park assist item index gets changed.
     * @param   void.
     * @return  void.
     */
    void sigExpandedParkAssistItemIndexChanged();

    /**
     * @brief sigExpandedAppraochLampsItemIndexChanged : Signal gets emitted when approach lamps item index gets changed.
     * @param   void.
     * @return  void.
     */
    void sigExpandedAppraochLampsItemIndexChanged();

    /**
     * @brief sigCurrentThemeModified : Signal gets emitted when active theme preset gets changed.
     * @param   void.
     * @return  void.
     */
    void sigCurrentThemeModified();

public slots:
    /**
    * @brief	CHomeAdaptor::slotFactoryResetWaitingStatusChanged is slot to catch Factory reset waiting status.
    * @param	bFactoryResetWaitingStatus, boolean value to state the factory reset waiting status.
    * @return	void.
    **/
    void slotFactoryResetWaitingStatusChanged(bool bFactoryResetWaitingStatus);

    /**
    * @brief	CHomeAdaptor::slotFactoryResetCompletionStatusChanged is slot to catch Factory reset completion status.
    * @param	bFactoryResetCompletionStatus, boolean value to state the factory reset completion status.
    * @return	void.
    **/
    void slotFactoryResetCompletionStatusChanged(bool bFactoryResetCompletionStatus);

    /**
     * @brief   sltCCMPresenceChanged: This method is a slot of sigCCMPresenceChanged which shall be invoked whenever
     *          CCm presence value is changed.
     * @param   void.
     * @return  void.
     */
    void sltCCMPresenceChanged();

    /**
     * @brief   sltVoiceAlertSelectionChanged is slot to update voice alert selection on signal changed
     * @param   void.
     * @return  void.
     */
    void sltVoiceAlertSelectionChanged();

    /**
     * @brief   sltThemeCannotBeUpdated is slot to update theme loading status on signal changed
     * @param   void.
     * @return  void.
     */
    void sltThemeCannotBeUpdated();

    /**
     * @brief sltBcmDrlSelectionStateChanged is slot to update the bcm drl selection state on signal changed
     * @param   void.
     * @return  void.
     */
    void sltBcmDrlSelectionStateChanged();

    /**
     * @brief   sltThemeCannotBeUpdated is slot to update ambient light illumination on signal changed
     * @param   void.
     * @return  void.
     */
    void sltAmbLightIllumLevelChanged();

    /**
     * @brief   sltThemeCannotBeUpdated is slot to update audio preset on signal changed
     * @param   void.
     * @return  void.
     */
    void sltActiveAudioPresetChanged();

    /**
     * @brief   sltVoiceAlertVolumeChanged is slot to update notification volume on signal changed
     * @param   void.
     * @return  void.
     */
    void sltVoiceAlertVolumeChanged();

    /**
     * @brief   sltNightModeStatusChanged is slot to update DRL state on signal changed
     * @param   void.
     * @return  void.
     */
    void sltNightModeStatusChanged();

    /**
     * @brief   initCustomThemeValues: To initialize the custom theme presets list. This method shall also be invoked
     *          from ThemeSetup screen whenever we enter into it.
     * @return  void
     * @param   void
     */
    Q_INVOKABLE void initCustomThemeValues();

private:

    /**
     * @brief currentModel: Returns current active model of setup
     * @return QAbstractListModel*
     * @param void
     */
    QAbstractListModel* currentModel();
    /**
     * @brief currentModel: Returns park assist delay timer sub model
     * @return QAbstractListModel*
     * @param void
     */
    QAbstractListModel* parkAssistDelayTimerSubModel();

    /**
     * @brief currentModel: Returns park assist tone sub model
     * @return QAbstractListModel*
     * @param void
     */
    QAbstractListModel* parkAssistToneSubModel();

    /**
     * @brief To initialize the setup list models
     * @return void
     * @param void
     */
    void initSetupListModels();

    /**
     * @brief To initialize the vehicle setup list model
     * @return void
     * @param void
     */
    void initVehicleSetupListModel();

    /**
     * @brief To initialize the park assist list model
     * @param   void.
     * @return  void.
     */
    void initParkAssistListModel();

    /**
     * @brief To initialize the theme setup list model
     * @return void
     * @param void
     */
    void initThemeSetupListModel();

    /**
     * @brief To initialize the theme presets list
     * @return void
     * @param void
     */
    void initThemeElementList();

    /**
     * @brief To initialize the lighting setup list model
     * @param   void
     * @return  void
     */
    void initLightingSetupListModel();

    /**
     * @brief currentModel: Returns approach lamps sub model
     * @return QAbstractListModel*
     * @param void
     */
    QAbstractListModel* approachLampsSubModel();

    /**
     * @brief currentModel: Returns theme presets model
     * @return QAbstractListModel*
     * @param void
     */
    QAbstractListModel* themepresetModel();

    /**
     * @brief audioSettingsModel: This function is to get audio setting model.
     * @return QAbstractListModel*
     * @param void
     */
    QAbstractListModel* audioSettingsModel()
    {
        return m_pAudioSettingsModel;
    }

    /**
     * @brief setCurrentThemeModified : This method is to set active theme preset status on changed
     * @param bcurrentThemeModified : holds true if active theme preset changed else false.
     * @return void.
     */
    void setCurrentThemeModified(bool bCurrentThemeModified);

    /**
     * @brief currentThemeModified : Will return active theme preset changed status
     * @param void.
     * @return  currentThemeModified: will return true if active theme preset gets changed else false.
     */
    bool currentThemeModified() {return m_bIsCurrentThemeModified; }

    /**
     * @brief validateClimateValues : This method is to validate climate values with active theme preset.
     * @param void.
     * @return validateClimateValues : will return true if fan speed or temperature gets changed else false
     */
    bool inline validateClimateValues();

    /**
     * @brief validateColorValues : This method is to validate color values with active theme preset.
     * @param void.
     * @return validateColorValues : will return true if theme color or brightness gets changed else false
     */
    bool inline validateColorValues();

    /**
     * @brief validateLightingValues : This method is to validate lighting values with active theme preset.
     * @param void.
     * @return validateLightingValues : will return true if ambient lighting gets changed else false
     */
    bool inline validateLightingValues();

    /**
     * @brief validateSoundValues : This method is to validate sound values with active theme preset.
     * @param void.
     * @return validateSoundValues : will return true if audio presets or notification volume gets changed else false
     */
    bool inline validateSoundValues();

    /**
     * @brief validateParkLamp : This method is to validate the ambient light feature availability and park lamp status.
     * @param void.
     * @return validateParkLamp : will return true if ambient light feature is available else false.
     */
    bool inline validateParkLamp();

    /**
     * @brief   This method is used to clear the request status.
     * @param   void.
     * @return  void.
     */
    void clearReqState();

    /**
     * @brief   This method is used to validate the request status.
     * @param   void.
     * @return  void.
     */
    void validateReq();

    /**
     * @brief   This method is used to get the count of the ocurrences.
     * @param   eReqState : passible request state.
     * @return  int : get the ocurrence of state.
     */
    int findOccurence(ERequestState eReqState);

    /**
     * @brief   This method is used to update the theme preset screen.
     * @param   bUserInitiated : holds true if apply theme is activated by user.
     * @return  void.
     */
    void updateThemesScreenParam(bool bUserInitiated = false);

    /**
     * @brief   This method is used to update vehicle setup list on signal changed.
     * @param   void.
     * @return  void.
     */
    void updateVehicleSetupListModel();

    /**
     * @brief   This method is used to update theme setup list on signal changed.
     * @param   void.
     * @return  void.
     */
    void updateThemeSetupListModel();

    /**
     * @brief   This method is used to update lighting setup list on signal changed
     * @param   void.
     * @return  void.
     */
    void updateLightingSetupListModel();

    /**
     * @brief updateReqState: Update the request state based on the match status.
     * @param eReqIndex: Request type to be updated.
     * @param bMatch: States wheter the value matches.
     */
    void updateReqState(ERequestIndex eReqIndex, bool bMatch);

private slots:

    /**
     * @brief Method gets invoked whenever there is a change in SDVC value
     * @param void
     * @return void
     */
    void sltPdcMixModeStatusChanged();

    /**
     * @brief Method gets invoked whenever there is a change in park assist volume
     * @param void
     * @return void
     */
    void sltParkAssistVolumeChanged();

    /**
     * @brief Method gets invoked whenever there is a change in park assist delay timer
     * @param void
     * @return void
     */
    void sltParkAssistDelayTimerChanged();

    /**
     * @brief Method gets invoked whenever there is a change in park assist tone
     * @param void
     * @return void
     */
    void sltParkAssistRearToneChanged();

    /**
     * @brief Method gets invoked whenever there is a change in approach lamps
     * @param void
     * @return void
     */
    void sltAppraochLampsChanged();

    /**
     * @brief Method gets invoked whenever there is a change in vehicle auto relock
     * @param void
     * @return void
     */
    void sltVehicleAutoRelockChanged();

    /**
     * @brief sltDriveNextElementsChanged: Slot to update DriveNext UI elements as per DriveNext elements status
     * @param void
     * @return void
     */
    void sltDriveNextElementsChanged();

    /**
     * @brief Method gets invoked whenever there is a change in fan speed
     * @param void
     * @return void
     */
    void sltFanSpeedChanged();

    /**
     * @brief Method gets invoked whenever there is a change in temperature
     * @param void
     * @return void
     */
    void sltTemperatureChanged();

    /**
     * @brief Method gets invoked whenever there is a change in air distribution mode
     * @param void
     * @return void
     */
    void sltDistributionModeChanged();

    /**
     * @brief sltCurrentThemeTypeChanged Method gets invoked whenever there  is a change in theme type
     * @param   void
     * @return  void
     */
    void sltCurrentThemeTypeChanged();

    /**
     * @brief  sltSmartFanStateChanged: This slot gets invoked on smart fan status change and updates the smart fan value to model.
     * @param  bSmartFanState: true - smart fan active, false - not active.
     * @return void.
     */
    void sltSmartFanStateChanged();

    /**
     * @brief  sltCPConnectionStatusUpdated: This slot gets invoked on CP device connection status update.
     * @param  bCPConnectionStatus: true - CP device  connected, false - not connected.
     * @return void.
     */
    void sltCPConnectionStatusUpdated(bool bCPConnectionStatus);

    /**
     * @brief sltErrorStatusChanged : This slot gets invoked on error status update.
     * @param   void.
     * @return  void.
     */
    void sltErrorStatusChanged();

    /**
     * @brief sltCtrlPanelModeChanged : This slot gets invoked on climate state update.
     * @param   void.
     * @return  void.
     */
    void sltCtrlPanelModeChanged();

    /**
     * @brief sltPowerModeChanged : This slot gets invoked on power mode state update.
     * @param   void.
     * @return  void.
     */
    void sltPowerModeChanged();

    /**
     * @brief sltParkLampStatusChanged : This slot gets invoked on park lamp state update.
     * @param   void.
     * @return  void.
     */
    void sltParkLampStatusChanged();

    /**
     * @brief sltPdcPresenceChanged : This slot gets invoked on pdc presence status update.
     * @param   void.
     * @return  void.
     */
    void sltPdcPresenceChanged();

    /**
     * @brief sltBcmUcsStateChanged : This slot gets invoked on bcmUcs status update.
     * @param   void.
     * @return  void.
     */
    void sltBcmUcsStateChanged();

    /**
     * @brief sltAppraochLampsPresenceChanged : This slot gets invoked on approach lamps presence status update.
     * @param   void.
     * @return  void.
     */
    void sltAppraochLampsPresenceChanged();

    /**
     * @brief sltAmbientLightModeIlluOnHuChanged : This slot gets invoked on ambient light presence status update.
     * @param   void.
     * @return  void.
     */
    void sltAmbientLightModeIlluOnHuChanged();

    /**
     * @brief sltBCMPresenceChanged : This slot gets invoked on bcm presence status update.
     * @param   void.
     * @return  void.
     */
    void sltBCMPresenceChanged();

    /**
     * @brief sltBcmDrlFeaturePresenceStatusChanged : This slot gets invoked on drl presence status update.
     * @param   void.
     * @return  void.
     */
    void sltBcmDrlFeaturePresenceStatusChanged();

    /**
     * @brief sltVoiceAlertPresenceChanged : This slot gets invoked on voice alert presence status update.
     * @param   void.
     * @return  void.
     */
    void sltVoiceAlertPresenceChanged();

    /**
     * @brief sltvehicleSetupElementsChanged : This slot gets invoked on any of the vehicle setup element gets changed.
     * @param   bStatus signal status value.
     * @return  void.
     */
    void sltVehicleSetupElementsChanged(bool bStatus);

    /**
     * @brief sltvehicleSetupElementsChanged : This slot gets invoked on any of the vehicle setup element gets changed.
     * @param   void.
     * @return  void.
     */
    void sltVehicleSetupElementsChanged();

private:

    static const short SETUP_INVALID_INDEX = -1;

private:

    /* Singleton instance of setup adaptor */
    static CSetupAdaptor* m_pSetupAdaptor;

    /* Instance of QAbstractListModel class, returns current active model of setup */
    QAbstractListModel *m_pCurrentModel;

    /* Instance of CSetupMainListModel class */
    CSetupMainListModel* m_pSetupMainListModel;

    /* Instance of CSetupAudioListModel class */
    CSetupAudioListModel* m_pSetupAudioListModel;

    /* Instance of CSetupBMTListModel class */
    CSetupBMTListModel* m_pSetupBMTListModel;

    /* Instance of CSetupAudioPresetListModel class */
    CSetupAudioPresetListModel* m_pSetupAudioPresetListModel;

    /* Instance of CSetupGeneralListModel class */
    CSetupGeneralListModel* m_pSetupGeneralListModel;

    /* Instance of CSetupVolumeSettingsListModel class */
    CSetupVolumeSettingsListModel* m_pSetupVolumeSettingsListModel;

    /* Instance of CSetupVehicleSettingsListModel class */
    CSetupListModel* m_pSetupVehicleSettingsListModel;

    /* Instance of CSetupListModel class, stores data of vehicle setup model */
    CSetupListModel *m_pSetupVehicleListModel;

    /* Instance of CSetupListModel class, stores data of park assist model */
    CSetupListModel *m_pSetupParkAssistListModel;

    /* Instance of CSetupListModel class, stores data of lighting setup model */
    CSetupListModel* m_pSetupLightingListModel;

    /* Instance of CSetupListModel class, stores data of DriveNext setup model */
    CSetupListModel* m_pSetupDriveNextListModel;

    /* Instance of CSetupListModel class, stores data of delay timer model */
    CSetupListModel *m_pSetupDelayTimerModel;

    /* Instance of CSetupListModel class, stores data of park assist tone model */
    CSetupListModel *m_pSetupParkAssistToneModel;

    /* Instance of CSetupListModel class, stores data of approach lamps model */
    CSetupListModel *m_pSetupAproachLampsModel;

    /* Instance of CSetupListModel class, stores data of theme setup model */
    CSetupListModel *m_pSetupThemeListModel;

    /* Instance of CSetupThemeSettingsListModel class */
    CThemeSettingsModel* m_pThemeSettingsModel;

    /**
     * @brief m_pAudioSettingsModel : Instance of CAudioSettingsModel class.
     */
    CAudioSettingsModel* m_pAudioSettingsModel;

    /* Instance to ThemeElements class*/
    QList<QObject*> m_lThemeElementsList;

    /* Editable theme preset list object*/
    CThemeElement  *m_pEditModeThemeElement;

    /* Instance of CThemeElement class, used to get the theme preset values*/
    CThemeElement* m_pThemeElement;

    /* Editable custom theme preset list object*/
    CThemeElement m_objCustomThemeElement;

    /*variable to set edit mode flag*/
    bool m_bEditModeFlag;

    /*variable to hold current preset selected*/
    int m_iPresetSelected;

    //! Pointer of CThemeSetupWithDriveModeListModel class
    CThemeSetupWithDriveModeListModel* m_pThemeSetupWithDriveModeListModel;

    /**
     * @brief m_bChangeThemeWithDriveModeStatus : This variable holds change theme with drive mode status.
     */
    bool m_bChangeThemeWithDriveModeStatus;

    /**
     * @brief m_eActiveDriveMode : This variable holds the active drive mode.
     */
    CSetupEnums::EDriveModes m_eActiveDriveMode;

    /**
     * @brief m_eCurrThemeColor : This variable holds the active theme color.
     */
    CSetupEnums::EThemesItem m_eCurrThemeColor;

    /**
     * @brief m_iCurActiveThemePreset : This variable holds the active theme preset.
     */
    int m_iCurActiveThemePreset;

    /**
     * @brief m_bThemeLoadingStatus : This variable holds the theme loading status.
     */
    bool m_bThemeLoadingStatus;

    /* Main setup screen items list container */
    QList<CSetupData*> m_SetupDataList;

    /** @brief m_mapThemePreset : This variable holds the active theme preset text */
    QString m_strActiveThemePresetText;

    /** @brief m_mapThemePreset : This variable holds the active theme preset icon */
    QString m_strActiveThemePresetIcon;

    /** @brief m_bIsThemeItemExpanded : This variable holds the theme item expanded status */
    bool m_bIsThemeItemExpanded;

    /** @brief m_iExpandedThemeItemIndex : This variable holds the theme item index */
    int m_iExpandedThemeItemIndex;

    /** @brief m_iExpandedThemeItemIndex : This variable holds the park assist item index */
    int m_iExpandedParkAssistItemIndex;

    /** @brief m_iExpandedApproachLampsItemIndex : This variable holds the approach lamps item index */
    int m_iExpandedApproachLampsItemIndex;

    /** @brief m_bIsCurrentThemeModified : This variable holds the active theme preset status */
    bool m_bIsCurrentThemeModified;

    /** @brief m_iApproachLampIndex : This variable holds the approach lamp position index*/
    int m_iApproachLampIndex;

    /** @brief m_eAudioSetupCurrentScreen : This variable holds current audio setup screen */
    CSetupEnums::EAudioSetupCurrentScreen m_eAudioSetupCurrentScreen;

    /** @brief m_iVoiceAlertIndex : This variable holds the voice alert position index*/
    int m_iVoiceAlertIndex;

    /** @brief m_iSmartFanIndex : This variable holds smart fan index in vehicle setup */
    int m_iSmartFanIndex;

    /** @brief m_iDriveNextIndex : This variable holds DriveNext index in vehicle setup */
    int m_iDriveNextIndex;

    /** @brief m_iBcmDrlIndex : This variable holds the drl position index*/
    int m_iBcmDrlIndex;

    /** @brief m_aryReqStatus : This variable holds the request status on change of the theme preset*/
    int m_aryReqStatus[6];

    /** @brief m_bIsClimatePopupShown : This variable holds the Climate Popup Shown status, TRUE if Climate popup has been shown
                                        else false.
    */
    bool m_bIsClimatePopupShown;
};

#endif // CSETUPADAPTOR_H
