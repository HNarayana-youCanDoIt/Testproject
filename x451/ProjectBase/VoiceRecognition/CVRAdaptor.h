/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CVRAdaptor.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CVRAdaptor class that stores all the data needed by QMl screens or
 * other adaptor module. It also communicates with QML and VR Stub resource layer.
 */

#ifndef CVRADAPTOR_H
#define CVRADAPTOR_H

#include <QObject>
#include <QAbstractListModel>
#include "HMIIncludes.h"
#include "CVREnum.h"
#include "CVRData.h"
#include "model/CVRListModel.h"
#include "model/CVRHelpCommandListModel.h"
#include "CMediaEnum.h"
#include "CVRStubResourceEnum.h"

class CVRAdaptor : public QObject
{
    Q_OBJECT

    //! property for qml to get picklist model
    Q_PROPERTY(QAbstractListModel* pickListModel        READ pickListModel              CONSTANT)
    //! property for qml to get updated VR state
    Q_PROPERTY(CVREnum::EVRState vrState                READ vrState                    NOTIFY sigVRStateUpdated)
    //! property for qml to get main VR commands
    Q_PROPERTY(QStringList mainVRCommands               READ mainVRCommands             CONSTANT)
    //! property for qml to get VR help commands
    Q_PROPERTY(QAbstractListModel* vrHelpCommands       READ vrHelpCommands             NOTIFY sigVRHelpCommandsUpdated)
    //! property for qml to get VR help categories
    Q_PROPERTY(QAbstractListModel* vrHelpCategories     READ vrHelpCategories           CONSTANT)
    //! property for qml to get VR help category name
    Q_PROPERTY(QString vrHelpCategoryName               READ vrHelpCategoryName         NOTIFY sigVRHelpCommandsUpdated)
    //! property for qml to get whether to show teleprompter list data in VR animation popup or not
    Q_PROPERTY(bool teleprompterListStatus              READ teleprompterListStatus     WRITE setTeleprompterListStatus NOTIFY sigTeleprompterListStatusChanged)
    //! property for qml to get teleprompter list data
    Q_PROPERTY(QAbstractListModel* teleprompterList     READ teleprompterList           CONSTANT)

//!Set constants
private:
    const QString SET_SCREEN_PHONE          = "phone";
    const QString SET_SCREEN_PAIRED_PHONES  = "pairedPhones";
    const QString SET_SCREEN_CLIMATE        = "climate";
    const QString SET_SCREEN_MEDIA_FOLDERS  = "mediaFolders";
    const QString SET_SCREEN_MEDIA          = "media";
    const QString SET_SCREEN_TUNER          = "tuner";
    const QString CATEGORY_MOBILE           = "mobile";
    const QString CATEGORY_HOME             = "home";
    const QString CATEGORY_WORK             = "work";
    const QString CATEGORY_OTHER            = "other";

public:

    /**
     * @brief   ~CVRAdaptor: Destructor of CVRAdaptor
     * @param   NA.
     * @return  NA.
     */
    ~CVRAdaptor();

    /**
     * @brief   getInstance: Method to create and get singleton instance of CVRAdaptor class.
     * @param   void.
     * @return  pointer to the object of CVRAdaptor class.
     */
    static CVRAdaptor *getInstance();

    /**
     * @brief   showHideVROverlay: This function is used to show or hide the VR Overlay.
     * @param   bShowVROverLay: true if need to show the VR overlay, false to hide.
     * @return  void.
     */
    void showHideVROverlay(bool bShowVROverLay);

    /**
     * @brief   activateVRSession: Method to be invoked to activate VR session.
     * @param   eKeyState: state of the HK.
     *          eScreenID: Screen ID which is activating the VR
     * @return  void.
     */
    void activateVRSession(CHardKeyEnum::EHardKeyState eKeyState, EVRScreenID eScreenID = EN_SCREEN_DEFAULT);

    /**
     * @brief   invUpdateVRHelpCommandList: Method to be invoked to update command list as per
     *          the VR help category type received.
     * @param   iVRHelpCategoryType: category type for which the VR help command list
     *          needs to be updated.
     * @param   strVRHelpCategoryName: name of the selected VR help categoryfor which the VR help command list
     *          needs to be updated.
     * @return  void.
     */
    Q_INVOKABLE void invUpdateVRHelpCommandList(int iVRHelpCategoryType, QString strVRHelpCategoryName = "");

    /**
     * @brief   invDeactivateVRSession: method to be invoked to deactivate VR session.
     * @param   eKeyState: state of the HK. Default value is CHardKeyEnum::HKEY_STATE_RELEASED.
     * @return  TRUE, if deactivation is processed, FALSE otherwise.
     */
    Q_INVOKABLE bool invDeactivateVRSession(CHardKeyEnum::EHardKeyState eKeyState = CHardKeyEnum::HKEY_STATE_RELEASED);

    /**
     * @brief   invGetVRHelpFileReadStatus: method to be invoked to get help file read status whether the Help file
     *          was opened to be read or not.
     * @param   void.
     * @return  status of whether to open help file for reading. TRUE if the help file was successfully opened
     *          for reading, FALSE otherwise.
     */
    Q_INVOKABLE bool invGetVRHelpFileReadStatus() { return m_bVRHelpFileReadStatus; }

    /**
    * @brief    invHandleHardKeys: Method to take actions on hardkey as per VR specification.
    * @param    eKey        - key on which the action is triggered.
    * @param    eKeyState   - state of the key on which the action is triggered.
    * @return   true if the action was taken otherwise false.
    */
    Q_INVOKABLE bool invHandleHardKeys(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState);

    /**
     * @brief   invGetVRSessionStatus: Method to be invoked to get the current VR session whether active or not
     * @param   void.
     * @return  current session status of VR, whether activated or not
     */
    Q_INVOKABLE bool invGetVRSessionStatus() { return m_bVRSessionStatus; }

    /**
     * @brief   setScreen: Method to change the screen in HMI to the passed screen.
     * @param   strScreenName: Screen name that HMI requires to display(switch).
     * @return  void.
     */
    void setScreen(const QString& strScreenName);

    /**
     * @brief   showContact: Method to display the contact details of the particular contact.
     * @param   strDatabaseType: Phone database type.
     * @param   iContactId: Contact id of the contact.
     * @return  void.
     */
    void showContact(const QString& strDatabaseType, int iContactId);

    /**
     * @brief   showTeleprompterList: Method to display the teleprompter list data on VR animation
     *          popup if VR animation popup is displayed otherwise to show the teleprompter list popup.
     * @param   void.
     * @return  void.
     */
    void showTeleprompterList();

    /**
     * @brief   showPickList: Method to switch to VR state and display the picklist screen.
     * @param   void.
     * @return  void.
     */
    void showPickList();

    /**
     * @brief   hidePickList: Method to come out of VR state and hide the picklist screen.
     * @param   void.
     * @return  void.
     */
    void hidePickList();

    /**
     * @brief   setFocusedItem: Method to be invoked to select an item from the pick list.
     * @param   iLineNo: Line number to be highligted.
     * @return  void.
     */
    void setFocusedItem(int iLineNo);

    /**
     * @brief   focusSelectedCategory: Method to be invoked to set the focus on a
     *          particular category.
     * @param   strCategory: Category on which the focus has to be set.
     * @return  void.
     */
    void focusSelectedCategory(const QString& strCategory);

    /**
     * @brief   focusSelectedCategory: Method to be invoked to do media browsing based on category.
     * @param   iMediaFilterType: media browse category type to be browsed.
     * @param   iMediaFilterId: media browse category id to fetch data for a selected item.
     *          If -1 then show all the content of the media categroy otherwise show the content
     *          of the passed filterId.
     * @return  void.
     */
    void mediaFilterListShow(int32_t iMediaFilterType, int64_t iMediaFilterId);

    /**
     * @brief   onVRStateChange: Method to be invoked on VR state change.
     * @param   iVRState - current state of voice recognition.
     * @return  void.
     */
    void onVRStateChange(int iVRState);

    /**
     * @brief   mediaVRBrowseReqStatus: Method to be invoked to inform VR adaptor about success/failure of browse request.
     * @param   eMediaVRBrowseState - current state of VR browse request to Media.
     * @return  void.
     */
    void mediaVRBrowseReqStatus(CMediaEnum::EMediaVRBrowseState eMediaVRBrowseState);

    /**
     * @brief   onVRDialogStateChange: Method to be invoked on VR dialog state change.
     * @param   iVRDialogState - current dialog state of voice recognition.
     * @return  void.
     */
    void onVRDialogStateChange(int iVRDialogState);

    /**
     * @brief   onVRAvailableStatus: Method to be invoked on VR availibility status.
     * @param   bVRAvailabilityStatus - status of VR availibility, whether available or not.
     * @return  void.
     */
    void onVRAvailableStatus(bool bVRAvailabilityStatus );

    /**
     * @brief   onVRProxyAvailableStatus: Method to be invoked on VR proxy availibility status.
     * @param   bVRProxyAvailabilityStatus - status of VR proxy availibility, whether available or not.
     * @return  void.
     */
    void onVRProxyAvailableStatus(bool bVRProxyAvailabilityStatus );

    /**
     * @brief   invPickListItemSelected: Method to be invoked whenever picklist item is selected
     *          via touch or RRE.
     * @param   iLineNo: List index of the picklist item.
     * @return  void.
     */
    Q_INVOKABLE void invPickListItemSelected(int iLineNo);

    /**
     * @brief   invSendVRResponse: Method to be invoked to send the response of a request
     * @param   eResponseType: Response type of the request.
     * @return  void.
     */
    Q_INVOKABLE void invSendVRResponse(CVREnum::EResponseType eResponseType);

    /**
     * @brief   pickListModel: Method to get picklist list model.
     * @param   void.
     * @return  reference to the object of class CVRListModel
     */
    QAbstractListModel* pickListModel(){ return &m_objPickListModel; }

    /**
     * @brief   vrHelpCommands: Method to get VR help command list model.
     * @param   void.
     * @return  reference to the object of class CVRHelpCommandListModel to get
     *          VR help command list
     */
    QAbstractListModel* vrHelpCommands();

    /**
     * @brief   vrHelpCategories: Method to get VR help category list model.
     * @param   void.
     * @return  reference to the object of class CVRHelpCommandListModel to get
     *          VR help category list
     */
    QAbstractListModel* vrHelpCategories();

    /**
     * @brief   vrHelpCategoryName: Method to get VR help category name.
     * @param   void.
     * @return  name of the VR help category
     */
    QString vrHelpCategoryName(){ return m_strVRHelpCategoryName; }

    /**
     * @brief   mainVRCommands: Method to get list of main VR commands.
     * @param   void.
     * @return  list of main VR commands.
     */
    QStringList mainVRCommands();


    /**
     * @brief   Method to get current VR state.
     * @param   void.
     * @return  current VR state.
     */
    CVREnum::EVRState vrState() { return m_eVRState; }

    /**
     * @brief   teleprompterListStatus: Method to get teleprompter list status whether to show the list or not.
     * @param   void.
     * @return  TRUE if teleprompter list data has to be shown on VR animation popup, FALSE otherwise.
     */
    bool teleprompterListStatus() { return m_bTeleprompterListStatus; }

    /**
     * @brief   setTeleprompterListStatus: Method to set the teleprompter list status.
     * @param   TRUE if the list needs to be shown, FALSE otherwise.
     * @return  void.
     */
    void setTeleprompterListStatus(bool bTeleprompterListStatus);

    /**
     * @brief   vrHelpCategories: Method to get teleprompter list model.
     * @param   void.
     * @return  reference to the object of class CVRListModel to get
     *          VR help category list
     */
    QAbstractListModel* teleprompterList(){ return &m_objTeleprompterListModel; }

    /**
     * @brief   isVROverlayDisplaying: This function is used to know that the VR Overlay
     *          is currently displaying or not.
     * @param   void.
     * @return  bool: true if VR overlay is displaying, otherwise false
     */
    bool isVROverlayDisplaying() {return m_bIsVROverlayDisplaying;}

    /**
     * @brief   setHideVROverlayTimerStatus: Method to set the hide VR Overlay timer status.
     * @param   bool: TRUE if timer is needed to hide VR Overlay, FALSE otherwise.
     * @return  void.
     */
    void setHideVROverlayTimerStatus(bool bHideVROverlayTimerStatus);


    /**
    * @brief	hideVROverlayOnSessionEnd is a method to hide VR overlay on VR session end
    * @param	void.
    * @return	void.
    **/
    void hideVROverlayOnSessionEnd();

signals:

    /**
     * @brief   sigSetFocusedItem: Signal that shall be emitted to select an item from the pick list.
     * @param   iLineNo: Line number to be highligted.
     * @return  void.
     */
    void sigSetFocusedItem(int iLineNo);

    /*!
     * @brief   Signal emitted whenever vr state is changed.
     * @param   void.
     * @return  void.
     */
    void sigVRStateUpdated();

    /**
     * @brief   sigShowHideVROverlay: Signal emitted to show or hide VR overlay.
     * @param   bShowVROverLay: Flag which indicate whether to show or hide VR overlay
     *          TRUE - show VR overlay, FALSE - hide VR overlay.
     * @return  void.
     */
    void sigShowHideVROverlay(bool bShowVROverLay);

    /*!
     * @brief   Signal emitted whenever VR help command list is updated.
     * @param   void.
     * @return  void.
     */
    void sigVRHelpCommandsUpdated();

    /*!
     * @brief   sigTeleprompterListStatusChanged: Signal emitted whenever teleprompter list status is changed.
     * @param   void.
     * @return  void.
     */
    void sigTeleprompterListStatusChanged();

private slots:

    /**
     * @brief   sltSourceStateInfoUpdated - slot of the source state update received from audio adaptor
     * @param   iSourceId: source id for which the state has changed.
     * @param   iSourceState: current state of the source.
     * @return  void
     */
    void sltSourceStateInfoUpdated(int iSourceId, int iSourceState);

    /**
    * @brief	sltHideVROverlayOnSessionEnd is a method to hide VR overlay after timer expiry
    * after VR Session End in case Projection is active. This is to avoid the flicker of Home
    * screen in VR Overlay -> Projection screen transition.
    * @param	void.
    * @return	void.
    **/
    void sltHideVROverlayOnSessionEnd();

private:
    /**
     * @brief   CVRAdaptor: Constructor of CVRAdaptor.
     * @param   pParent: QObject pointer of parent class.
     * @return  NA.
     */
    explicit CVRAdaptor(QObject *pParent = nullptr);

    /**
     * @brief   initMainVRCommandsList: Method to add main VR commands in the list
     * @param   lstCommands - reference to store the list of command categories.
     * @param   objCommands - list of commands to be read from.
     * @return  void.
     */
    void initMainVRCommandsList(QStringList& lstCommands, SVRHelpCommands objCommands);

    /**
     * @brief   parseVRHelpCommands: Method to parse VR help commands from VRHelp xml file
     *          and add them in the list.
     * @param strFile - Path of the file to be parsed.
     * @param objCommandList - reference to store the list of command categories.
     * @param objCommands - reference to store the list of commands.
     */
    void parseVRHelpCommands(QString strFile, CVRHelpCommandListModel& objCommandList, SVRHelpCommands& objCommands);

    /**
     * @brief   parseCommands: Method to parse VR help commands from VRHelp xml file
     *          and add them in the list.
     * @param   objReader - QXmlStreamReader object to parse Help XML file.
     * @param   eCategoryType - Type of the VR help command category.
     * @param   objCommands - reference to store the list of commands.
     */
    void parseCommands(QXmlStreamReader &objReader, CVREnum::EVRHelpCategoryType eCategoryType,  SVRHelpCommands& objCommands);

    /**
     * @brief   setRequestState: Internal method to set VR request state.
     * @param   eVRRequestState: VR request state to be stored.
     * @return  void.
     */
    void setRequestState(CVREnum::EVRRequestState eVRRequestState);

    /**
     * @brief   requestVRBrowse: Internal method to request for VR browsing.
     * @param   void.
     * @return  void.
     */
    void requestVRBrowse();

    //! Pointer of CVRAdaptor class for creating singleton instance.
    static CVRAdaptor*          m_pVRAdaptor;
    //! Framework class's object reference.
    CFramework&                 m_objFramework;
    //! Object of CVRListModel class.
    CVRListModel                m_objPickListModel;
    //! Enum to hold current VR state.
    CVREnum::EVRState           m_eVRState;
    //! Flag to maintain VR session status, TRUE(active) FALSE(Inactive).
    bool                        m_bVRSessionStatus;
    //! String list to contain main VR commands.
    QStringList                 m_listMainVRCommands;

    //! String list to contain main VR commands for No FATC..
    QStringList                 m_listMainVRCommandsNoFATC;

    //! SVRHelpCommands structure's object to contain all the information of VR help commands
    SVRHelpCommands             m_objVRHelpCommands;

    //! SVRHelpCommands structure's object to contain all the information of VR help commands for No FATC.
    SVRHelpCommands             m_objVRHelpCommandsNoFATC;

    //! Object of CVRHelpCommandListModel class to hold VR help command list.
    CVRHelpCommandListModel     m_objVRHelpCommandListModel;

    //! Object of CVRHelpCommandListModel class to hold VR help command list for No FATC.
    CVRHelpCommandListModel     m_objVRHelpCommandListModelNoFATC;

    //! Object of CVRHelpCommandListModel class to hold VR help categories list.
    CVRHelpCommandListModel     m_objVRHelpCategoryListModel;

    //! Object of CVRHelpCommandListModel class to hold VR help categories list.
    CVRHelpCommandListModel     m_objVRHelpCategoryListModelNoFATC;

    //! Data to hold the VR help category name.
    QString                     m_strVRHelpCategoryName;
    //! Data to hold the read status of VR help file.
    bool                        m_bVRHelpFileReadStatus;
    //! Flag to maintain whether voice recognition is available or not.
    bool                        m_bIsVRAvailable;
    //! Flag to maintain whether to show teleprompter list on VR animation popup or not.
    bool                        m_bTeleprompterListStatus;
    //! String list to contain teleprompter list data.
    CVRListModel                m_objTeleprompterListModel;
    //! Data to hold the current request state
    CVREnum::EVRRequestState    m_eVRRequestState;
    //! Data to hold media browse category type to be browsed.
    int32_t                     m_iMediaFilterType;
    //! Data to hold media browse category id to fetch data for a selected item.
    int64_t                     m_iMediaFilterId;
    /**
     * @brief m_bIsVROverlayDisplayed: This variable holds the status of display of VR overlay.
     *                                 true if VR Overlay displayed else false.
     */
    bool m_bIsVROverlayDisplaying;
    //! Flag to maintain whether timer is needed to hide the VR overlay.
    bool m_bHideVROverlayTimerStatus;
};

#endif // CVRADAPTOR_H
