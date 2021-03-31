/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDoodleAdaptor.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDoodleAdaptor, an Adaptor for Doodle module,
 * Thisclass is used to communicate with qml, resources of Doodle module.
 */
//________________________________________________________________________________________________
#ifndef CDOODLEADAPTOR_H
#define CDOODLEADAPTOR_H

#include <QObject>
#include <QString>
#include <QTimer>

#include "logging.h"
#include "CFramework.h"
#include "CDoodleEnum.h"
#include "CHardKeyEnum.h"
#include "CPopupEnum.h"

#include "CGenericListModel.h"
#include "CDoodleSetupListElement.h"

//! @category FORWARD DECLERATIONS
class CDoodleResourceImpl;

//________________________________________________________________________________________________
/**
 * @brief CDoodleAdaptor, an Adaptor for Doodle module,
 * This class is used to communicate with qml, resources of Doodle module.
 */
class CDoodleAdaptor : public QObject
{
    Q_OBJECT
    //________________________________________________________________________________________________
    // Q Properties //

    //// To get the Doodle EOL presence status.
    Q_PROPERTY(bool doodleEOLPresence READ doodleEOLPresence NOTIFY sigDoodleEOLPresenceChanged)

    //// To get the Doodle proxy presence status.
    Q_PROPERTY(bool doodleProxyPresence READ doodleProxyPresence NOTIFY sigDoodleProxyPresenceChanged)

    //// To get the Doodle activate status.
    Q_PROPERTY(bool doodleActivated READ doodleActivated NOTIFY sigDoodleActivatedChanged)

    //// To get wait time in seconds after that doodle can be shown.
    Q_PROPERTY(int doodleDisplayWaitTime READ doodleDisplayWaitTime NOTIFY sigDoodleDisplayWaitTimeChanged)

    //// To get doodle show permission as per screen state.
    Q_PROPERTY(bool allowDoodleOnScreen READ allowDoodleOnScreen NOTIFY sigAllowDoodleOnScreenChanged)

    //// To get doodle show permission as per drawer state.
    Q_PROPERTY(bool allowDoodleOnDrawer READ allowDoodleOnDrawer NOTIFY sigAllowDoodleOnDrawerChanged)

    //// To get doodle available to show or not.
    Q_PROPERTY(bool doodleAvailable READ doodleAvailable NOTIFY sigDoodleAvailableChanged)

    //// To get doodle position on screen.
    Q_PROPERTY(QPoint doodlePosition READ doodlePosition NOTIFY sigDoodlePositionChanged)

    //// To get doodle Image URL.
    Q_PROPERTY(QString doodleImageURL READ doodleImageURL NOTIFY sigDoodleImageURLChanged)

    //// To get startup Image URL.
    Q_PROPERTY(QString startupImageURL READ startupImageURL NOTIFY sigStartupImageURLChanged)

    //// To get doodle size on screen.
    Q_PROPERTY(QPoint doodleSize READ doodleSize NOTIFY sigDoodleSizeChanged)

    //// To get doodle setup Expanded element type.
    Q_PROPERTY(CDoodleEnum::EDoodleSetupElementTypes doodleSetupExpandedElement READ doodleSetupExpandedElement NOTIFY sigDoodleSetupExpandedElementChanged)

    //// To get the doodle setup elements data
    Q_PROPERTY(QList<QObject *> doodleSetupElements READ doodleSetupElements NOTIFY sigDoodleSetupElementsChanged)

    //// property for qml to get doodle setup list model
    Q_PROPERTY(QAbstractListModel* doodleSetupListModel READ doodleSetupListModel CONSTANT)

    //________________________________________________________________________________________________

public:

    /**
    * @brief    CDoodleAdaptor constructor for class CDoodleAdaptor.
    * @param    QObject.
    * @return   NA.
    **/
    CDoodleAdaptor(QObject *parent = nullptr);
    //________________________________________________________________________________________________
    /**
    * @brief    ~CDoodleAdaptor is destructor of class CDoodleAdaptor.
    * @param    NA.
    * @return   NA.
    **/
    ~CDoodleAdaptor();
    //________________________________________________________________________________________________
    /**
    * @brief    initDoodleProperties is init function for CDoodleAdaptor Q properties.
    * @param    void.
    * @return   void.
    **/
    void initDoodleProperties();
    //________________________________________________________________________________________________
    /**
    * @brief    initDoodleData is init function for CDoodleAdaptor data.
    * @param    void.
    * @return   void.
    **/
    void initDoodleData();
    //________________________________________________________________________________________________
    /**
    * @brief    resetDoodleData is reset function for CDoodleAdaptor data.
    * @param    void.
    * @return   void.
    **/
    void resetDoodleData();
    //________________________________________________________________________________________________
    /**
    * @brief    initDoodleSetupElements is init function for doodle setup elements data.
    * @param    void.
    * @return   void.
    **/
    void initDoodleSetupElements();
    //________________________________________________________________________________________________
    /**
    * @brief    resetDoodleSetupElements is reset function for doodle setup elements data.
    * @param    void.
    * @return   void.
    **/
    void resetDoodleSetupElements();
    //________________________________________________________________________________________________
    /**
    * @brief    initDoodleSetupList is init function for doodle setup list.
    * @param    void.
    * @return   void.
    **/
    void initDoodleSetupList();
    //________________________________________________________________________________________________
    /**
    * @brief    resetDoodleSetupList is reset function for doodle setup list.
    * @param    void.
    * @return   void.
    **/
    void resetDoodleSetupList();
    //________________________________________________________________________________________________
    /**
    * @brief    refreshDoodleSetupList is a method to refresh DoodleSetupList.
    * @param    void.
    * @return   void.
    **/
    void refreshDoodleSetupList();
    //________________________________________________________________________________________________
    /**
    * @brief    doodleEOLPresence is method to get value for "doodleEOLPresence" property.
    * @param    void.
    * @return   bool TRUE if Doodle EOL is present, FALSE otherwise.
    **/
    bool doodleEOLPresence();
    //________________________________________________________________________________________________
    /**
    * @brief    setDoodleEOLPresence is a method to update "doodleEOLPresence" property.
    * @param    bool TRUE if Doodle EOL is present, FALSE otherwise.
    * @return   void.
    **/
    void setDoodleEOLPresence(bool bValue);
    //________________________________________________________________________________________________
    /**
    * @brief    doodleProxyPresence is method to get value for "doodleProxyPresence" property.
    * @param    void.
    * @return   bool TRUE if Doodle Proxy is present, FALSE otherwise.
    **/
    bool doodleProxyPresence();
    //________________________________________________________________________________________________
    /**
    * @brief    updateDoodleProxyPresence is a method to update "doodleProxyPresence" property.
    * @param    void.
    * @return   void.
    **/
    void updateDoodleProxyPresence();
    //________________________________________________________________________________________________
    /**
    * @brief    doodleActivated is method to get value for "doodleActivated" property.
    * @param    void.
    * @return   bool TRUE if Doodle is Activated, FALSE otherwise.
    **/
    bool doodleActivated();
    //________________________________________________________________________________________________
    /**
    * @brief    setDoodleActivated is a method to update "doodleActivated" property.
    * @param    bool TRUE if Doodle is Activated, FALSE otherwise.
    * @return   void.
    **/
    void setDoodleActivated(bool bValue);
    //________________________________________________________________________________________________
    /**
    * @brief    doodleDisplayWaitTime is method to get value for "doodleDisplayWaitTime" property.
    * @param    void.
    * @return   int wait time in seconds.
    **/
    int doodleDisplayWaitTime();
    //________________________________________________________________________________________________
    /**
    * @brief    setDoodleDisplayWaitTime is a method to update "doodleDisplayWaitTime" property.
    * @param    int wait time in seconds.
    * @return   void.
    **/
    void setDoodleDisplayWaitTime(int iValue);
    //________________________________________________________________________________________________
    /**
    * @brief    allowDoodleOnScreen is method to get value for "allowDoodleOnScreen" property.
    * @param    void.
    * @return   bool TRUE if Doodle allowed to show on screen, FALSE otherwise.
    **/
    bool allowDoodleOnScreen();
    //________________________________________________________________________________________________
    /**
    * @brief    setAllowDoodleOnScreen is a method to update "allowDoodleOnScreen" property.
    * @param    bool TRUE if Doodle allowed to show on screen, FALSE otherwise.
    * @return   void.
    **/
    void setAllowDoodleOnScreen(bool bValue);
    //________________________________________________________________________________________________
    /**
    * @brief    allowDoodleOnDrawer is method to get value for "allowDoodleOnDrawer" property.
    * @param    void.
    * @return   bool TRUE if Doodle allowed to show on screen, FALSE otherwise.
    **/
    bool allowDoodleOnDrawer();
    //________________________________________________________________________________________________
    /**
    * @brief    setAllowDoodleOnDrawer is a method to update "allowDoodleOnDrawer" property.
    * @param    bool TRUE if Doodle allowed to show on screen, FALSE otherwise.
    * @return   void.
    **/
    void setAllowDoodleOnDrawer(bool bValue);
    //________________________________________________________________________________________________
    /**
    * @brief    doodleAvailable is method to get value for "doodleAvailable" property.
    * @param    void.
    * @return   bool TRUE if Doodle allowed to show on screen, FALSE otherwise.
    **/
    bool doodleAvailable();
    //________________________________________________________________________________________________
    /**
    * @brief    updateDoodleAvailability is a method to update "doodleAvailable" property.
    * @param    void.
    * @return   void.
    **/
    void updateDoodleAvailability();
    //________________________________________________________________________________________________
    /**
    * @brief    doodlePosition is method to get value for "doodlePosition" property.
    * @param    void.
    * @return   QPoint doodle position.
    **/
    QPoint doodlePosition();
    //________________________________________________________________________________________________
    /**
    * @brief    setDoodlePosition is a method to update "doodlePosition" property.
    * @param    QPoint doodle position.
    * @return   void.
    **/
    void setDoodlePosition(QPoint position);
    //________________________________________________________________________________________________
    /**
    * @brief    doodleImageURL is method to get value for "doodleImageURL" property.
    * @param    void.
    * @return   QString doodle image URL.
    **/
    QString doodleImageURL();
    //________________________________________________________________________________________________
    /**
    * @brief    setDoodleImageURL is a method to update "doodleImageURL" property.
    * @param    QString doodle image URL.
    * @return   void.
    **/
    void setDoodleImageURL(QString imageURL);
    //________________________________________________________________________________________________
    /**
    * @brief    startupImageURL is method to get value for "startupImageURL" property.
    * @param    void.
    * @return   QString startup image URL.
    **/
    QString startupImageURL();
    //________________________________________________________________________________________________
    /**
    * @brief    setStartupImageURL is a method to update "startupImageURL" property.
    * @param    QString startup image URL.
    * @return   void.
    **/
    void setStartupImageURL(QString imageURL);
    //________________________________________________________________________________________________
    /**
    * @brief    doodleSize is method to get value for "doodleSize" property.
    * @param    void.
    * @return   QPoint doodle position.
    **/
    QPoint doodleSize();
    //________________________________________________________________________________________________
    /**
    * @brief    setDoodleSize is a method to update "doodleSize" property.
    * @param    QPoint doodle size.
    * @return   void.
    **/
    void setDoodleSize(QPoint size);
    //________________________________________________________________________________________________
    /**
    * @brief    doodleSetupExpandedElement is a method to get "doodleSetupExpandedElement" property.
    * @param    void.
    * @return   CDoodleEnum::EDoodleSetupElementTypes doodle setup expanded element type.
    **/
    CDoodleEnum::EDoodleSetupElementTypes doodleSetupExpandedElement();
    //________________________________________________________________________________________________
    /**
    * @brief    setDoodleSetupExpandedElement is a method to update "doodleSetupExpandedElement" property.
    * @param    CDoodleEnum::EDoodleSetupElementTypes doodle setup expanded element type.
    * @return   void.
    **/
    void setDoodleSetupExpandedElement(CDoodleEnum::EDoodleSetupElementTypes eDoodleSetupExpandedElement);
    //________________________________________________________________________________________________
    /**
    * @brief    doodleSetupElements is a method to update "doodleSetupElements" property.
    * @param    void.
    * @return   QList<QObject *> list for doodle setup elements.
    **/
    QList<QObject *> doodleSetupElements();
    //________________________________________________________________________________________________
    /**
    * @brief    doodleSetupListModel is a method to update "doodleSetupListModel" property.
    * @param    void.
    * @return   QAbstractListModel* pointer to doodle setup list model.
    **/
    QAbstractListModel *doodleSetupListModel();
    //________________________________________________________________________________________________
    /**
    * @brief    forceShowDoodleOnScreen is method to get value for force Show Doodle On Screen.
    * @param    void.
    * @return   bool TRUE if Doodle need to show on screen forcefully, FALSE otherwise.
    **/
    bool forceShowDoodleOnScreen();
    //________________________________________________________________________________________________
    /**
    * @brief    setForceShowDoodleOnScreen is a method to update value for force Show Doodle On Screen.
    * @param    bool TRUE if Doodle need to show on screen forcefully, FALSE otherwise.
    * @return   void.
    **/
    void setForceShowDoodleOnScreen(bool bValue);
    //________________________________________________________________________________________________

signals:

    /**
    * @brief    CDoodleAdaptor::sigDoodleEOLPresenceChanged is QML signal for "doodleEOLPresence" property.
    * @param    void.
    * @return   void.
    **/
    Q_SIGNAL void sigDoodleEOLPresenceChanged();
    //________________________________________________________________________________________________
    /**
    * @brief    CDoodleAdaptor::sigDoodleProxyPresenceChanged is QML signal for "doodleProxyPresence" property.
    * @param    void.
    * @return   void.
    **/
    Q_SIGNAL void sigDoodleProxyPresenceChanged();
    //________________________________________________________________________________________________
    /**
    * @brief    CDoodleAdaptor::sigDoodleActivatedChanged is QML signal for "doodleActivated" property.
    * @param    void.
    * @return   void.
    **/
    Q_SIGNAL void sigDoodleActivatedChanged();
    //________________________________________________________________________________________________
    /**
    * @brief    CDoodleAdaptor::sigDoodleDisplayWaitTimeChanged is QML signal for "doodleDisplayWaitTime" property.
    * @param    void.
    * @return   void.
    **/
    Q_SIGNAL void sigDoodleDisplayWaitTimeChanged();
    //________________________________________________________________________________________________
    /**
    * @brief    CDoodleAdaptor::sigAllowDoodleOnScreenChanged is QML signal for "allowDoodleOnScreen" property.
    * @param    void.
    * @return   void.
    **/
    Q_SIGNAL void sigAllowDoodleOnScreenChanged();
    //________________________________________________________________________________________________
    /**
    * @brief    CDoodleAdaptor::sigAllowDoodleOnDrawerChanged is QML signal for "allowDoodleOnDrawer" property.
    * @param    void.
    * @return   void.
    **/
    Q_SIGNAL void sigAllowDoodleOnDrawerChanged();
    //________________________________________________________________________________________________
    /**
    * @brief    CDoodleAdaptor::sigDoodleAvailableChanged is QML signal for "doodleAvailable" property.
    * @param    void.
    * @return   void.
    **/
    Q_SIGNAL void sigDoodleAvailableChanged();
    //________________________________________________________________________________________________
    /**
    * @brief    CDoodleAdaptor::sigDoodlePositionChanged is QML signal for "doodlePosition" property.
    * @param    void.
    * @return   void.
    **/
    Q_SIGNAL void sigDoodlePositionChanged();
    //________________________________________________________________________________________________
    /**
    * @brief    CDoodleAdaptor::sigDoodleImageURLChanged is QML signal for "doodleImageURL" property.
    * @param    void.
    * @return   void.
    **/
    Q_SIGNAL void sigDoodleImageURLChanged();
    //________________________________________________________________________________________________
    /**
    * @brief    CDoodleAdaptor::sigStartupImageURLChanged is QML signal for "startupImageURL" property.
    * @param    void.
    * @return   void.
    **/
    Q_SIGNAL void sigStartupImageURLChanged();
    //________________________________________________________________________________________________
    /**
    * @brief    CDoodleAdaptor::sigDoodleSizeChanged is QML signal for "doodleSize" property.
    * @param    void.
    * @return   void.
    **/
    Q_SIGNAL void sigDoodleSizeChanged();
    //________________________________________________________________________________________________
    /**
    * @brief    CDoodleAdaptor::sigDoodleSetupExpandedElementChanged is QML signal for "doodleSetupExpandedElement" property.
    * @param    void.
    * @return   void.
    **/
    Q_SIGNAL void sigDoodleSetupExpandedElementChanged();
    //________________________________________________________________________________________________
    /**
    * @brief    CDoodleAdaptor::sigDoodleSetupElementsChanged is QML signal for "doodleSetupElements" property.
    * @param    void.
    * @return   void.
    **/
    Q_SIGNAL void sigDoodleSetupElementsChanged();
    //________________________________________________________________________________________________

public slots:

    /**
    * @brief    sltDoodleEOLEnabled is a slot to get change for doodle EOL status.
    * @param    void.
    * @return   void.
    **/
    void sltDoodleEOLEnabled();
    //________________________________________________________________________________________________
    /**
    * @brief    sltDoodleWaitTimeEnded is a slot to get callback for doodle wait timer end.
    * @param    void.
    * @return   void.
    **/
    void sltDoodleWaitTimeEnded();
    //________________________________________________________________________________________________
    /**
     * @brief   sltPopupResult: Slot to be connected to PopupManager's signal sigPopupResult
     * used to handle Popup events
     * @param   ePopupId: Id of the Popup
     * @param   EPopupPriority: Result of the Popup(Displayed, Closed or Ignored)
     * @param   strAdditionalInfo: Additional info (based on reason on which popup is closed)
     * @return  void.
     */
    void sltPopupResult(CPopupEnum::EPopupID ePopupId, CPopupEnum::EPopupResult ePopupResult, QString strAdditionalInfo);
    //________________________________________________________________________________________________
    /**
     * @brief sltDrawerStateChanged: Slot to be connected to CDrawersAdaptor's signals sigQadDrawerStateChanged and sigShortcutDrawerStateChanged
     * Used to handle drawers states
     * @param void
     * @return void
     */
    void sltDrawerStateChanged();
    //________________________________________________________________________________________________
    /**
    * @brief    sltActiveChanged_AndroidAuto is slot to catch "AndroidAuto" active changes.
    * @param    bStatus : true if AndroidAuto is active
    * @return   void.
    **/
    void sltActiveChanged_AndroidAuto(bool bStatus);
    //________________________________________________________________________________________________
    /**
    * @brief    sltActiveChanged_CarPlay is slot to catch "CarPlay" active changes.
    * @param    bStatus : true if CarPlay is active
    * @return   void.
    **/
    void sltActiveChanged_CarPlay(bool bStatus);
    //________________________________________________________________________________________________
    /**
    * @brief    sltActiveChanged_USB is slot to catch "USB" active changes.
    * @param    void.
    * @return   void.
    **/
    void sltActiveChanged_USB();
    //________________________________________________________________________________________________
    /**
     * @brief   sltAvailabilityChanged_AuxIn: is slot catch "Aux" Connection status change
     * @param   void
     * @return  void
     */
    void sltAvailabilityChanged_AuxIn();
    //________________________________________________________________________________________________

public:

    /**
    * @brief    resetDoodle is a method to reset Doodle information,
    * It is Q_INVOKABLE to allow direct call from qml code.
    * @param    void.
    * @return   void.
    **/
    Q_INVOKABLE void resetDoodle();
    //________________________________________________________________________________________________
    /**
    * @brief    openDoodleSetupFromDoodle is a method to open doodle setup screen from doodle,
    * It is Q_INVOKABLE to allow direct call from qml code.
    * @param    void.
    * @return   void.
    **/
    Q_INVOKABLE void openDoodleSetupFromDoodle();
    //________________________________________________________________________________________________
    /**
    * @brief    isDoodleStickerOnScreen is a method to get doodle sticker display status,
    * It is Q_INVOKABLE to allow direct call from qml code.
    * @param    void.
    * @return   true when doodle sticker is displayed on screen, otherwise false.
    **/
    Q_INVOKABLE bool isDoodleStickerOnScreen();
    //________________________________________________________________________________________________
    /**
    * @brief    tryShowDoodleOnScreen is a method to trigger flow to show doodle on screen,
    * It is Q_INVOKABLE to allow direct call from qml code.
    * @param    void.
    * @return   void.
    **/
    Q_INVOKABLE void tryShowDoodleOnScreen();
    //________________________________________________________________________________________________
    /**
    * @brief    tryHideDoodleFromScreen is a method to trigger flow to hide doodle from screen,
    * It is Q_INVOKABLE to allow direct call from qml code.
    * @param    void.
    * @return   void.
    **/
    Q_INVOKABLE void tryHideDoodleFromScreen();
    //________________________________________________________________________________________________
    /**
    * @brief    updateDoodleStickerPosition is a method to update doodle sticker position after drag complete,
    * It is Q_INVOKABLE to allow direct call from qml code.
    * @param    int X position.
    * @param    int Y position.
    * @return   void.
    **/
    Q_INVOKABLE void updateDoodleStickerPosition(int iPosX, int iPosY);
    //________________________________________________________________________________________________
    /**
    * @brief    handleDoodleSetupElementTouchEvent is a method to handle doodle setup list element touch event,
    * It is Q_INVOKABLE to allow direct call from qml code.
    * @param    CDoodleEnum::EDoodleSetupElementTypes touch element type.
    * @return   void.
    **/
    Q_INVOKABLE void handleDoodleSetupElementTouchEvent(CDoodleEnum::EDoodleSetupElementTypes eSetupElementType);
    //________________________________________________________________________________________________
    /**
     * @brief   eventFilter event filter function to get all the events on the hmi application
     * @param   object qt/qml object on which the event is to be filtered
     * @param   event event on the application
     * @return  returns the event has been consumed or not (true,false)
     */
    bool eventFilter(QObject *pQObject, QEvent *pQEvent);
    //________________________________________________________________________________________________
    /**
    * @brief    handleHardKeys : Funtion to handle hardkey as per media specifications.
    * @param    eKey the key on which the action is triggered.
    * @param    eState state of the key on which the action is triggered.
    * @return   void.
    */
    void handleHardKeys(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState);
    //________________________________________________________________________________________________

private:

    /**
    * @brief    doodleWaitTimerStart is a method to start doodle wait timer.
    * @param    void.
    * @return   void.
    **/
    void connectSignals();
    //________________________________________________________________________________________________
    /**
    * @brief    doodleWaitTimerStart is a method to start doodle wait timer.
    * @param    void.
    * @return   void.
    **/
    void disconnectSignals();
    //________________________________________________________________________________________________
    /**
    * @brief    updateDoodlePermissions is a method to update doodle display permissions.
    * @param    void.
    * @return   void.
    **/
    void updateDoodlePermissions();
    //________________________________________________________________________________________________
    /**
    * @brief    doodleWaitTimerRunning is a method to get  doodle wait timer running state.
    * @param    void.
    * @return   bool TRUE when timer is running otherwise FALSE.
    **/
    bool doodleWaitTimerRunning();
    //________________________________________________________________________________________________
    /**
    * @brief    doodleWaitTimerStart is a method to start doodle wait timer.
    * @param    void.
    * @return   void.
    **/
    void doodleWaitTimerStart();
    //________________________________________________________________________________________________

    /**
    * @brief    doodleWaitTimerStop is a method to stop doodle wait timer.
    * @param    void.
    * @return   void.
    **/
    void doodleWaitTimerStop();
    //________________________________________________________________________________________________
    /**
    * @brief    doodleWaitTimerRestart is a method to restart doodle wait timer.
    * @param    void.
    * @return   void.
    **/
    void doodleWaitTimerRestart();
    //________________________________________________________________________________________________
    /**
    * @brief    tryAddStickerGroupInDoodleSetupList is a method to add Sticker group in DoodleSetupList.
    * @param    void.
    * @return   bool TRUE when group added successfully, otherwise FALSE.
    **/
    bool tryAddStickerGroupInDoodleSetupList();
    //________________________________________________________________________________________________
    /**
    * @brief    tryRemoveStickerGroupFromDoodleSetupList is a method to remove Sticker group from DoodleSetupList.
    * @param    void.
    * @return   bool TRUE when group removed successfully, otherwise FALSE.
    **/
    bool tryRemoveStickerGroupFromDoodleSetupList();
    //________________________________________________________________________________________________
    /**
    * @brief    tryAddStartupImageGroupInDoodleSetupList is a method to add StartupImage group in DoodleSetupList.
    * @param    void.
    * @return   bool TRUE when group added successfully, otherwise FALSE.
    **/
    bool tryAddStartupImageGroupInDoodleSetupList();
    //________________________________________________________________________________________________
    /**
    * @brief    tryRemoveStartupImageGroupFromDoodleSetupList is a method to remove StartupImage group from DoodleSetupList.
    * @param    void.
    * @return   bool TRUE when group removed successfully, otherwise false.
    **/
    bool tryRemoveStartupImageGroupFromDoodleSetupList();
    //________________________________________________________________________________________________
private:

    //// m_bDoodleEOLPresence: Variable to hold value for "doodleEOLPresence" property.
    bool m_bDoodleEOLPresence;

    //// m_bDoodleProxyPresence: Variable to hold value for "doodleProxyPresence" property.
    bool m_bDoodleProxyPresence;

    //// m_bDoodleActivated: Variable to hold value for "doodleActivated" property.
    bool m_bDoodleActivated;

    //// m_iDoodleDisplayWaitTime: Variable to hold value for "doodleDisplayWaitTime" property.
    int m_iDoodleDisplayWaitTime;

    //// m_bAllowDoodleOnScreen: Variable to hold value for "allowDoodleOnScreen" property.
    bool m_bAllowDoodleOnScreen;

    //// m_bAllowDoodleOnDrawer: Variable to hold value for "allowDoodleOnDrawer" property.
    bool m_bAllowDoodleOnDrawer;

    //// m_bDoodleAvailable: Variable to hold value for "doodleAvailable" property.
    bool m_bDoodleAvailable;

    //// m_DoodlePosition: Variable to hold value for "doodlePosition" property.
    QPoint m_DoodlePosition;

    //// m_strDoodleImageURL: Variable to hold value for "doodleImageURL" property.
    QString m_strDoodleImageURL;

    //// m_strStartupImageURL: Variable to hold value for "startupImageURL" property.
    QString m_strStartupImageURL;

    //// m_DoodleSize: Variable to hold value for "doodleSize" property.
    QPoint m_DoodleSize;

    //// m_bForceShowDoodleOnScreen: Variable to hold value for force Show Doodle On Screen.
    bool m_bForceShowDoodleOnScreen;

    //// m_pDoodleWaitTimer: QTimer pointer to hold Doodle wait timer object pointer.
    QTimer* m_pDoodleWaitTimer;

    //// m_pDoodleSetupModel: pointer to hold CGenericListModel object pointer.
    CGenericListModel* m_pDoodleSetupModel;

    //// m_lDoodleSetupElementsData : list of CDoodleSetupListElement class to hold different setup element data.
    QList<QObject *> m_lDoodleSetupElementsData;

    //// m_eDoodleSetupExpandedElement: used to hold current expanded element from doodle setup list
    CDoodleEnum::EDoodleSetupElementTypes m_eDoodleSetupExpandedElement;

    //// m_pDoodleResource: Pointer of CDoodleResourceImpl class, Used to communicate withDoodle resource layer.
    CDoodleResourceImpl* m_pDoodleResource;

    //________________________________________________________________________________________________
};

#endif // CDOODLEADAPTOR_H
