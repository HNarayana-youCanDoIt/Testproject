/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CTunerAdaptor.h
 * @ingroup       HMIComponent
 * @author        Rahul Balyan
 * CTunerAdaptor, an adaptor for tuner module which help tuner application layer
 *                to communicate with resource layer, QML layer and state machine
**/

#ifndef CTUNERADAPTOR_H
#define CTUNERADAPTOR_H

#include <QObject>
#include "logging.h"
#include <QString>
#include <CHMIMain.h>
#include "CTunerEnums.h"
#include "CFramework.h"
#include "Tuner/interfaces/ITunerResource.h"
#include "CTunerManualScaleListModel.h"
#include "CAudioAdaptor.h"
#include "CDiagnosticAdaptor.h"

/**
 * @brief The CTunerAdaptor class
 * The class will help tuner application layer to communicate with resource layer, QML layer and state machine
**/

class CTunerAdaptor : public QObject
{
    Q_OBJECT

    /** constant integer holds the AM frequency step size */
    const int AM_FREQ_STEP_SIZE;

    /** constant integer holds the FM frequency step size */
    const int FM_FREQ_STEP_SIZE;

    /** constant integer holds the no. of available AM frequency */
    const int AM_AVAIL_FREQ_COUNT;

    /** constant integer holds the no. of available FM frequency */
    const int FM_AVAIL_FREQ_COUNT;

    /** constant integer holds AM starting frequency */
    const int AM_STARTING_FREQ;

    /** constant integer holds FM starting frequency */
    const int FM_STARTING_FREQ;

    /** constant integer holds AM last frequency */
    const int AM_LAST_FREQ;

    /** constant integer holds FM last frequency */
    const int FM_LAST_FREQ;

    /** constant integer holds index divider for max tuner scale line */
    const int MAX_LINE_DIVIDER;

    /** constant integer holds index divider for mid tuner scale line */
    const int MID_LINE_DIVIDER;

    /** constant integer holds height for max line in tuner manual scale */
    const int MAX_LINE_HEIGHT;

    /** constant integer holds height for mid line in tuner manual scale */
    const int MID_LINE_HEIGHT;

    /** constant integer holds height for min line in tuner manual scale */
    const int MIN_LINE_HEIGHT;

    /** constant integer holds number of preset tiles per page */
    const int PRESET_TILES_PER_PAGE;

    /** constant integer holds value of invalid preset index */
    const int INVALID_PRESET_INDEX;

    /** constant integer holds maximum number of preset that can be stored in preset list */
    const int MAX_PRESETS;


    /** Properties */

    /** Property hold the current display tuner frequency */
    Q_PROPERTY(QString strFrequency READ strFrequency NOTIFY sigFrequencyChanged)

    /** Property hold the current band value in string */
    Q_PROPERTY(QString strBand READ strBand NOTIFY sigBandChanged)

    /** Property hold the current tuner frequency unit */
    Q_PROPERTY(QString strFrequencyUnit READ strFrequencyUnit NOTIFY sigFrequencyUnitChanged)

    /** Property hold the tuner seek type */
    Q_PROPERTY(CTunerEnums::ETunerSeekType eSeekType READ eSeekType NOTIFY sigSeekTypeChanged)

    /** Property hold the current tuner state and QML state will be updated using this property */
    Q_PROPERTY(QString strTunerState READ strTunerState WRITE setTunerState NOTIFY sigTunerStateChanged)

    /** Property hold the current band(AM, FM or DRM) for tuner */
    Q_PROPERTY(CTunerEnums::ETunerBand eBandType READ eBandType NOTIFY sigBandTypeChanged)

    /** Property hold the Manual scale index as per the current frequency */
    Q_PROPERTY(int iManualScaleIndex READ iManualScaleIndex NOTIFY sigManualScaleIndexChanged)

    /** Property to hold current station name */
    Q_PROPERTY(QString strStationName READ strStationName NOTIFY sigStationNameChanged)

    /** Property to hold Preset List */
    Q_PROPERTY(QList<QString> liPresetTilesList READ liPresetTilesList NOTIFY sigPresetTilesListChanged)

    /** Property hold the FM band manual scale model */
    Q_PROPERTY(CTunerManualScaleListModel* pTunerManualScaleListModel READ pTunerManualScaleListModel NOTIFY sigTunerManualScaleListModelChanged)

    /** Property to hold current active preset */
    Q_PROPERTY(int iActivePresetIndex READ iActivePresetIndex NOTIFY sigActivePresetIndexChanged)

    /** Property to hold current page index of preset list */
    Q_PROPERTY(int iPresetListPageIndex READ iPresetListPageIndex WRITE setPresetListPageIndex NOTIFY sigPresetListPageIndexChanged)

    /** Property to hold field strength of current station */
    Q_PROPERTY(int iFieldStrength READ iFieldStrength NOTIFY sigFieldStrengthChanged)

    /** Property to hold tagId of current station */
    Q_PROPERTY(uint uiTagId READ uiTagId NOTIFY sigTagIdChanged)

    /** Property to hold multipath of current station */
    Q_PROPERTY(unsigned char multiPath READ multiPath NOTIFY sigMultipathChanged)

    /** Property to hold tuner availability status */
    Q_PROPERTY(bool bTunerAvailabilityStatus READ bTunerAvailabilityStatus NOTIFY sigTunerAvailabilityStatusUpdated)

    /** Property to hold tuner UI data availability status */
    Q_PROPERTY(bool bTunerDataAvailableStatus READ bTunerDataAvailableStatus NOTIFY sigTunerDataAvailableStatusChanged)

public:

    // Get Adaptor instance
    ~CTunerAdaptor();
    static CTunerAdaptor *getInstance();

    /**
     * @brief strTunerState - Method to get current state of tuner screen qml
     * @param void
     * @return m_strTunerState - Value of current tuner operation state
     */
    QString strTunerState();

    /**
     * @brief strFrequency - Method to get the value of current frequency
     * @param void
     * @return m_strFrequency - Value of frequency
     */
    QString strFrequency();

    /**
     * @brief strBand - Method to get the value of current band in string
     * @param void
     * @return m_strBand - Band value
     */
    QString strBand();
    /**
     * @brief bTunerAvailabilityStatus - Method to get the value of m_bIsTunerEnabled
     * @param void
     * @return m_bIsTunerEnabled - Tuner availability status
     */
    bool bTunerAvailabilityStatus();

    /**
     * @brief bTunerDataAvailableStatus - Method to get tuner UI data availability status
     * @param void
     * @return m_bTunerDataAvailableStatus - Tuner UI data availability status
     */
    bool bTunerDataAvailableStatus();

    /**
     * @brief eSeekType - Method to get current tuner seek type
     * @param void
     * @return m_eSeekType - Value of seek type
     */

    CTunerEnums::ETunerSeekType eSeekType();

    /**
     * @brief eBandType - Method to get current band type
     * @param void
     * @return m_eBandType - Value of band type(AM,FM,DRM)
     */
    CTunerEnums::ETunerBand eBandType();

    /**
     * @brief iManualScaleIndex - Method to get current manual tuning scale index
     * @param void
     * @return m_iManualScaleIndex - Value of manual scale index
     */
    int iManualScaleIndex();

    /**
     * @brief uiTagId - Method to get tagId of current frequency
     * @param void
     * @return uiTagId - Value of tagId
     */
    uint uiTagId();

    /**
     * @brief strStationName - Method to get curent active station name
     * @param void
     * @return m_strStationName - Value of station name
     */
    QString strStationName();

    /**
     * @brief Method to get the value of m_iFieldStrength
     * @param void
     * @return m_iFieldStrength - Value of field strength of current station
     */
    int iFieldStrength();

    /**
     * @brief multiPath, returns the value of m_ucMultipath
     * @param void
     * @return m_ucMultipath -  multipath value of current station
     */
    unsigned char multiPath();
    /**
     * @brief Method to get the value of m_uiActivePreset
     * @brief iActivePresetIndex- Method to get the index of active preset
     * @param void
     * @return m_iActivePresetIndex - current active preset number
     */
    int iActivePresetIndex();

    /**
     * @brief iPresetListPageIndex - Method to get the index preset list's page
     * @param void
     * @return int : m_iPresetListPageIndex - current page index of preset list
     */
    int iPresetListPageIndex();

    /** TODO: use the actual class and not QObject **/
    /**
     * @brief Method to get the value of m_liTunerPresetList
     * @param void
     * @return m_liTunerPresetList - Value of preset list
     */
    QList<QString> liPresetTilesList();

    /**
     * @brief strFrequencyUnit - Method to get current frequency unit value
     * @param void
     * @return m_strFrequencyUnit - current frequency unit as per band
     */
    QString strFrequencyUnit();

    /**
     * @brief pTunerManualScaleListModel - Method to get tuner manual scale model for FM band pathview
     * @param void
     * @return CTunerManualScaleListModel : m_objTunerFMManualScaleListModel/m_objTunerAMManualScaleListModel
     * Manual scale Model for tuner based on type of band
     */
    CTunerManualScaleListModel* pTunerManualScaleListModel();

    /**
     * @brief setTunerState - Method to set current state of tuner screen qml.
     * @param strTunerState - Value of tuner state from tuner service
     * @return void
     */
    void setTunerState(const QString &strTunerState);

    /**
     * @brief setFrequency - Method to set the value of current frequency in UINT data type
     * @param uiFrequency - Value of frequency
     * @return void
     */
    void setFrequency(uint uiFrequency);

    /**
     * @brief setDisplayFrequency - Method to set the value of current display frequency in string
     * @param void
     * @return void
     */
    void setDisplayFrequency();

    /**
     * @brief setFrequencyUnit - Method to set the value of frequency unit
     * @param void
     * @return void
     */
    void setFrequencyUnit();

    /**
     * @brief setBand - Method to set the value of tuner band in string
     * @param void
     * @return void
     */
    void setBand();

    /*!
     * @brief setTunerAvailabilityStatus Method to set tuner availability status.
     * @param bTunerStatus - status of the tunerservice proxy whether available or not.
     * @return void.
     */
    void setTunerAvailabilityStatus(bool bTunerStatus);

    /*!
     * @brief setTunerDataAvailabilityStatus Method to set tuner data availability status.
     * @param bTunerDataStatus
     * @return void.
     */
    void setTunerDataAvailabilityStatus(bool bTunerDataStatus);

    /**
     * @brief setSeekType - Method to set the value of tuner seek type
     * @param eSeekType - Value of seek type from tuner service
     * @return void
     */
    void setSeekType(CTunerEnums::ETunerSeekType eSeekType);

    /**
     * @brief bandUpdate - Method will be called when handler receives band update
     * @param CTunerEnums::ETunerBand eBand - Value of Band Type from Tuner service
     * @return void
     */
    void bandUpdate(CTunerEnums::ETunerBand eBand);

    /**
     * @brief frequencyUpdate - Method will be called when handler receives frequency update
     * @param uiFrequency - Value of frequency from tuner service
     * @return void
     */
    void frequencyUpdate(uint uiFrequency);

    /**
     * @brief seekUpdate - Method will be called when handler receives seek update
     * @param eSeekType - Value of seek from tuner service
     * @return void
     */
    void seekUpdate(CTunerEnums::ETunerSeekType eSeekType);

    /**
     * @brief setBandType - Method to set the value of tuner band type
     * @param CTunerEnums::ETunerBand eBand - Value of Band Type from Tuner service
     * @return void
     */
    void setBandType(CTunerEnums::ETunerBand eBand);

    /**
     * @brief updateUIState - Method to emit signal for band, frequencyUnit and ManualScaleListModel update
     * @param void
     * @return void
     */
    void updateUIState();

    /**
     * @brief setManualScaleIndex - Method to set the value of manual scale index
     * @param iIndex - Value of manual scale index from Tuner service
     * @return void
     */
    void setManualScaleIndex(int iIndex);

    /**
     * @brief setTagId - Method to set the value of tuner band type
     * @param uint::tagId - Value of tagId of frequency
     * @return void
     */
    void setTagId(uint uiTagId);

    /**
     * @brief setStationName - Method to set the value of active station name
     * @param strStationName - Value of station name from Tuner service
     * @return void
     */
    void setStationName(const QString &objStrStationName);

    /**
     * @brief Method to set the value of active preset number
     * @param void
     * @return int : iActivePresetIndex
     */
    void setActivePresetIndex(int iActivePresetIndex);

    /**
     * @brief Method to set the value of field Strength(Signal Strength)
     * @param iFieldStrength - Value of field strength for current station
     * @return void
     */
    void setFieldStrength(int iFieldStrength);

    /**
     * @brief setPresetListPageIndex - Method to set the preset list page index
     * @param int : iPresetListPageIndex - preset list page's index
     * @return void
     */
    void setPresetListPageIndex(int iPresetListPageIndex);

    /**
     * @brief Method to emit signal for tuner manual scale list model
     * @param void
     * @return void
     */
    void setTunerManualScaleListModel();

    /**
     * @brief setPresetList - method to get the preset list from resource layer
     * @param void
     * @return void
     */
    void setPresetList();

    /**
     * @brief requestPresetPlayUp - method to play next preset
     * @param void
     * @return void
     */
    void requestPresetPlayUp();

    /**
     * @brief requestPresetPlayDown - method to play previous preset
     * @param void
     * @return void
     */
    void requestPresetPlayDown();

    // Public Methods
    /**
     * @brief getManualSeekStatus - method to get manual seek status
     * @param void
     * @return int : m_bManualSeekStatus
     */
    int getManualSeekStatus();

    /**
     * @brief setManualSeekStatus - method to set of status of Manual Seek.
     * @param bool : bStatus
     * @return void
     */
    void setManualSeekStatus(bool bStatus);

    /**
     * @brief initializeAMManualSeekListModel - method to initialize manual seek list model for AM band
     * @param void
     * @return void
     */
    void initializeAMManualSeekListModel();

    /**
     * @brief initializeFMManualSeekListModel - method to initialize manual seek list model for FM band
     * @param void
     * @return void
     */
    void initializeFMManualSeekListModel();

    /**
     * @brief setTunerManualScaleIndex - method to find current manual scale index
     * @param void
     * @return void
     */
    void setTunerManualScaleIndex();
    /**
     * @brief introspectionProxyAvailable - method to disbale  quality monitor
     * @param void
     * @return void
     */
    void introspectionProxyAvailable();

    /**
     * @brief isTunerAntennaConnected - Q_INVOKABLE method to check antenna connection status
     *        and to show antenna not connected popup if not connected
     * @param void
     * @return bool
     */
    Q_INVOKABLE bool isTunerAntennaConnected();

    /**
    * @brief handleHardKeys - Funtion to handle hardkey as per media specifications.
    * @param eKey the key on which the action is triggered.
    * @param eState state of the key on which the action is triggered.
    * @return  true is an action was taken false otherwise.
    */
    bool handleHardKeys(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState);

    /**
     * @brief Method to set the value of multipath of current station
     * @param unsigned char: multipath of current station
     * @return void
     */
    void setMultipath(unsigned char ucMultipath);

    // API's called directly by the QML files, these need to be Q_INVOKABLE
    /**
     * @brief requestAutoSeekUP - Q_INVOKABLE method to invoke start autoseek up API in resource layer
     * @param void
     * @return void
     */
    Q_INVOKABLE void requestAutoSeekUP();

    /**
     * @brief requestAutoSeekDown - Q_INVOKABLE method to invoke start autoseek down API in resource layer
     * @param void
     * @return void
     */
    Q_INVOKABLE void requestAutoSeekDown();

    /**
     * @brief requestScan - Q_INVOKABLE method to invoke start scan API in resource layer
     * @param void
     * @return void
     */
    Q_INVOKABLE void requestScan();

    /**
     * @brief requestAutostore - Q_INVOKABLE method to invoke start AutoStore API in resource layer
     * @param void
     * @return void
     */
    Q_INVOKABLE void requestAutostore();

    /**
     * @brief stopSeek - Q_INVOKABLE method to invoke stop Autoseek API in resource layer
     * @param void
     * @return void
     */
    Q_INVOKABLE void stopSeek();

    /**
     * @brief stopSeekOnScanAndAutostore - Q_INVOKABLE method to invoke stop seek when user scan and autostore is active
     * @param void
     * @return void
     */
    Q_INVOKABLE void stopSeekOnScanAndAutostore();

    /**
     * @brief startManualSeek - method to start manual seek
     * @param int - iManualFreq : frequency to set.
     * @return void
     */
    Q_INVOKABLE void startManualSeek(int iManualFreq);

    /**
     * @brief setFrequency - method to set tuner frequency
     * @param int - iFrequency : frequency to set.
     * @return void
     */
    Q_INVOKABLE void setTunerFrequency(int iFrequency);

    /**
     * @brief setFrequencyAfterAutostore - method to be invoked to set first preset frequency after autostore
     * @param
     * @return void
     */
    void setFrequencyAfterAutostore();

    /**
     * @brief storePreset - Q_INVOKABLE method to invoke store preset API in resource layer
     * @param int - Preset number in which current frequency is to be stored
     * @return void
     */
    Q_INVOKABLE void storePreset(int iPreset);

    /**
     * @brief selectPreset - Q_INVOKABLE method to invoke select preset API in resource layer
     * @param int - Preset number to be selected from the preset list
     * @return void
     */
    Q_INVOKABLE void selectPreset(int iPreset);

    /**
     * @brief setTunerQMLStatus - method to set tuner main screen QML status
     * @param bool bStatus : true(if loaded)
     * @return void
     */
    Q_INVOKABLE void setTunerQMLStatus(bool bStatus);

    /**
     * @brief enableQualityMonitor - method to control the quality monitor(on/off)
     * @param bMonitorFlag - true if quality monitor is to be enabled else false
     * @return void
     */
    void enableQualityMonitor(bool bMonitorFlag);

    /**
     * @brief launchTuner - method to be invoked when user select radio icon from home screen shortcut.
     * @param void
     * @return void
     */
    void launchTuner();

    /**
     * @brief handleStopSeek - method to handle stop seek as per the current seek mode.
     * @param void
     * @return void
     */
    void handleStopSeek();

    /**
     * @brief setAutoStoreCompleteSuccessStatus - Method to set autostore complete success status
     * @param bool : Auto Store Success status
     * @return void
     */
    void setAutoStoreCompleteSuccessStatus(bool bStatus);

    /**
     * @brief selectPresetListPageIndex - Method to select the preset list page index
     * @param void
     * @return void
     */
    void selectPresetListPageIndex();

    /**
     * @brief setManualSeekBlockStatus - method to set manual seek blocking status
     * @param bool bStatus : true(if blocked)
     * @return void
     */
    Q_INVOKABLE void setManualSeekBlockStatus(bool bStatus);


private:

    /**
     * TODO:
     * method is commented because there is some problem with stop seek API from service side
     * that's why we will not use this method for now.
     */
    /**
     * @brief stopOngoingSeek - Method to stop ongoing seek w.r.t current SCT state when user request for
     *                          some different seek.
     * @param CTunerEnums::ETunerSeekType - eSeekType: variable holds seek type to be started
     * @return bool : seek stop status
     */
    bool stopOnGoingSeek(CTunerEnums::ETunerSeekType eSeekType);

    /**
     * @brief setManualFrequency - method to invoke set manual frequency API in resource layer
     * @param void
     * @return void
     */
    void setManualFrequency();

    /**
     * @brief resetTunerData - method to reset tuner UI data
     * @param void
     * @return void
     */
    void resetTunerData();

    /**
     * @brief initPresetList - method to initialize the preset list with default values
     * @param void
     * @return void
     */
    void initPresetList();

    /**
     * @brief selectActivePreset - method to select active preset
     * @param void
     * @return void
     */
    void selectActivePreset();

    /**
     * @brief stopManualSeek - method to stop manual seek
     * @param void
     * @return void
     */
    void stopManualSeek();

signals:

    /**
    * @brief	CTunerAdaptor::sigFrequencyChanged is a notify signal to notify strFrequency property changes to qml
    * @param	void.
    * @return	void.
    **/
    void sigFrequencyChanged();

    /**
    * @brief	CTunerAdaptor::sigSeekTypeChanged is a notify signal to notify eSeekType property changes to qml
    * @param	void.
    * @return	void.
    **/
    void sigSeekTypeChanged();

    /**
    * @brief	CTunerAdaptor::sigBandTypeChanged is a notify signal to notify eBand property changes to qml
    * @param	void.
    * @return	void.
    **/
    void sigBandTypeChanged();

    /**
    * @brief	CTunerAdaptor::sigTunerStateChanged is a notify signal to notify strTunerState property changes to qml
    * @param	void.
    * @return	void.
    **/
    void sigTunerStateChanged();

    /**
    * @brief	CTunerAdaptor::sigManualScaleIndexChanged is a notify signal to notify iManualScaleIndex property changes to qml
    * @param	void.
    * @return	void.
    **/
    void sigManualScaleIndexChanged();

    /**
    * @brief	CTunerAdaptor::sigStationNameChanged is a notify signal to notify station name property changes to qml
    * @param	void.
    * @return	void.
    **/
    void sigStationNameChanged();

    /**
    * @brief	CTunerAdaptor::sigFrequencyUnitChanged is a notify signal to notify Frequency Unit property changes to qml
    * @param	void.
    * @return	void.
    **/
    void sigFrequencyUnitChanged();

    /**
    * @brief	CTunerAdaptor::sigBandChanged is a notify signal to notify Band value changes to qml
    * @param	void.
    * @return	void.
    **/
    void sigBandChanged();

    /**
    * @brief	CTunerAdaptor::sigTunerManualScaleListModelChanged is a notify signal to notify tuner Manual Scale List model change
    * @param	void.
    * @return	void.
    **/
    void sigTunerManualScaleListModelChanged();

    /**
     * @brief sigPresetTilesListChanged is a notify signal to notify whenever preset list is updated
     * @param void
     * @return void
     */
    void sigPresetTilesListChanged();

    /**
     * @brief sigActivePresetIndexChanged is a notify signal to notify whenever current active preset index is updated
     * @param void
     * @return void
     */
    void sigActivePresetIndexChanged();

    /**
     * @brief sigFieldStrengthChanged is a notify signal to notify whenever current field strength is updated
     * @param void
     * @return void
     */
    void sigFieldStrengthChanged();

    /**
     * @brief sigPresetListIndexPageChanged is a notify signal to notify whenever preset list page index changed
     * @param void
     * @return void
     */
    void sigPresetListPageIndexChanged();

    /**
    * @brief sigPresetListIndexPageChanged is a notify signal to notify whenever preset list page index changed
    * @param void
    * @return void
    */
    void sigTagIdChanged();

    /**
     * @brief sigMultipathChanged Signal to notify whenever multipath is updated
     * @param void
     * @return void
     */
    void sigMultipathChanged();

    /**
     * @brief sigTunerAvailabilityStatusUpdated is a notify signal to notify whenever tuner availability status is updated
     * @param void
     * @return void
     */
    void sigTunerAvailabilityStatusUpdated();

    /**
     * @brief sigTunerDataAvailableStatusChanged is a notify signal to notify whenever tuner data availability status is updated
     * @param void
     * @return void.
     */
    void sigTunerDataAvailableStatusChanged();


public slots:

    /**
     * @brief sltDrawerStateChanged - method to stop seek on drawer interaction
     * @param void
     * @return void
     */
    void sltDrawerStateChanged();

    /**
     * @brief sltTimerComplete - Method will get invoked when Qtimer completes.
     * @param void
     * @return void
     */
    void sltTimerComplete();

    /**
     * @brief sltActiveEntSrcUpdated - method to stop seek on Active Ent src changed
     * @param void
     * @return void
     */
    void sltActiveEntSrcUpdated();

    /**
     * @brief sltActiveInteruptSrcUpdated - method to stop seek on Active Interupt src changed
     * @param void
     * @return void
     */
    void sltActiveInteruptSrcUpdated();



protected:


private:
    explicit CTunerAdaptor(QObject *parent = nullptr);

    /**
     * @brief m_pTunerAdaptor : this static pointer variable of CTunerAdaptor class will
     *                          be used to access adaptor class from any class.
     */
    static CTunerAdaptor* m_pTunerAdaptor;

    /**
     * @brief m_objTunerFMManualScaleListModel : CTunerManualScaleListModel class object to store manual scale data.
     */
    CTunerManualScaleListModel m_objTunerFMManualScaleListModel;

    /**
     * @brief m_objTunerAMManualScaleListModel : CTunerManualScaleListModel class object to store manual scale data.
     */
    CTunerManualScaleListModel m_objTunerAMManualScaleListModel;

    /**
     * @brief m_liFMManualScaleFreq : Integer Qlist to store manual scale freq
     */
    QList<int> m_liFMManualScaleFreq;

    /**
     * @brief m_liAMManualScaleFreq : Integer Qlist to store manual scale freq
     */
    QList<int> m_liAMManualScaleFreq;

    /**
     * @brief m_uiFrequency : Variable to store frequency recieved from service side/resource layer
     */
    uint m_uiFrequency;

    /**
     * @brief m_uiAMFrequency : Variable to store FM frequency recieved from service side/resource layer
     */
    uint m_uiAMFrequency;

    /**
     * @brief m_uiFrequency : Variable to store AM frequency recieved from service side/resource layer
     */
    uint m_uiFMFrequency;

    /**
     * @brief m_uiCurrentResourceFrequency : method to hold current resource frequency.
     */
    uint m_uiCurrentResourceFrequency;

    /**
     * @brief m_strFrequency : Variable to store frequency to be display on tuner as well as in other modules
     */
    QString m_strFrequency;

    /**
     * @brief m_strFrequencyUnit : Variable to store frequency unit to be display on tuner as well as in other modules
     */
    QString m_strFrequencyUnit;

    /**
     * @brief m_strBand : Variable to store Tuner band value to be display on tuner as well as in other modules
     */
    QString m_strBand;

    /**
     * @brief m_eSeekType : Variable to store type of tuner seek(Autoseek/scan/autostore)
     */
    CTunerEnums::ETunerSeekType m_eSeekType;

    /**
     * @brief m_eBandType : Variable to store currently playing band
     */
    CTunerEnums::ETunerBand m_eBandType;

    /**
     * @brief m_strTunerState : Variable to store current tuner QML state
     */
    QString m_strTunerState;

    /**
     * @brief m_iManualScaleIndex : Variable to store current manual scale index
     */
    int m_iManualScaleIndex;

    /**
     * @brief m_bManualSeekStatus : boolean store manual seek status
     */
    bool m_bManualSeekStatus;

    /**
     * @brief m_strStationName : Variable to store current station name
     */
    QString m_strStationName;

    /**
     * @brief m_iFieldStrength : Variable to store current field strength
     */
    int m_iFieldStrength;

    /**
     * variable to store multipath value of current station
    */
    unsigned char m_ucMultipath;

    /**
     * @brief m_iActivePresetIndex : Variable to store current active preset
     */
    int m_iActivePresetIndex;

    /**
     * @brief m_uiSelectedPresetFrequency : Variable to store currently selected preset frequency
     */
    uint m_uiSelectedPresetFrequency;

    /**
     * @brief m_iSelectedPresetIndex : Variable to store user selected preset index
     */
    int m_iSelectedPresetIndex;

    /**
     * @brief m_uiTagId : Variable to store tagId of current frequency
     */
    uint m_uiTagId;

    /**
     * @brief m_iPresetListPageIndex : Variable to store Preset List Page Index
     */
    int m_iPresetListPageIndex;

    /**
     * @brief m_bPresetListEmptyStatus : Variable store thr preset list empty status : true if empty
     */
    bool m_bPresetListEmptyStatus;

    /**
     * @brief m_vecPresetList : Qvector for Preset list frequency data
     */
    QVector<int> m_vecPresetList;

    /**
     * @brief m_objTunerManualSeekTimer : QTimer for manual seek debouncing logic
     */
    QTimer m_objTunerManualSeekTimer;

    /**
     * @brief m_liTunerPresetList : QList to store the presets list display frequency
     */
    QList<QString>  m_liTunerPresetList;

    /**
     * @brief m_bIsTunerEnabled Flag to maintain whether tuner is enabled or not.
     */
    bool m_bIsTunerEnabled;

    /**
     * @brief m_bTunerDataAvailableStatus Flag to maintain tuner data availability status
     */
    bool m_bTunerDataAvailableStatus;

    /**
     * @brief m_bTunerMainScreenQMLStatus variable stores tuner screen status.
     *        True: if loaded, False: if not loaded
     */
    bool m_bTunerMainScreenQMLStatus;

    /**
     * @brief m_bAutoStoreSuccessStatus variable stores autostore completion success status.
     */
    bool m_bAutoStoreSuccessStatus;

    /**
     * @brief m_bBlockManualSeek variable stores manual seek blocking status.
     */
    bool m_bBlockManualSeek;

    /**
     * @brief m_pTunerResource : Tuner resource pointer
     */
    ITunerResource* m_pTunerResource;
};

#endif // TUNERADAPTOR_H
