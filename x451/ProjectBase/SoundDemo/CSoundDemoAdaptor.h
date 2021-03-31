/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2019
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CSoundDemoAdaptor.h
* @ingroup      HMIComponent
* @author       Guru Alingal
* @brief        Adaptor class for sound demo.
*/

#ifndef CSOUNDDEMOADAPTOR_H
#define CSOUNDDEMOADAPTOR_H

#include <QObject>
#include<CSoundDemoModel.h>
#include <Audio/CAudioEnums.h>
#include <CMediaBrowseCategoryListModel.h>

class CSoundDemoAdaptor : public QObject
{
    Q_OBJECT

    /** PROPERTY to update the demo list model to qml */
    Q_PROPERTY(CSoundDemoModel* demoModel READ demoModel CONSTANT)

    /** PROPERTY to update the sound demo availability to qml */
    Q_PROPERTY(bool demoAvailable READ demoAvailable NOTIFY demoAvailableChanged)

    /** PROPERTY to update the sound demo availability to qml */
    Q_PROPERTY(int selectedTrackIndex READ selectedTrackIndex NOTIFY selectedTrackIndexChanged)

private:
    explicit CSoundDemoAdaptor(QObject* pParent = nullptr);

     /**
     * @brief updateDemoModel: To update the sound demo model with updates if any
     * @param void
     * @return void
     */
    void updateDemoModel();

    /**
     * @brief updatePlayStateData: To update media playstate data in the list item.
     * @param iIndex: List item index of the demo list to be updated with playstate.
     * @param bState: State of play state to be set.
     * @return void
     */
    void updatePlayStateData(int iIndex, bool bState);

    /**
     * @brief sltUpdateNowPlayingPointer: Signal to update the nowplaying pointer.
     * @param iOldIndex: list item index from where the highlight is to be removed.
     * @param iNewIndex: list item index to be highlighted.
     * @return void
     */
    void updateNowPlayingPointer(int iOldIndex, int iNewIndex);


public:
    ~CSoundDemoAdaptor();

    /**
     * @brief demoModel: Returns the sound demo model
     * @param void
     * @return demo sound model
     */
    CSoundDemoModel* demoModel();

    /**
     * @brief demoAvailable: Availability of sound demo feature
     * @param void
     * @return true if sound demo available else false
     */
    bool demoAvailable();

    /**
     * @brief setDemoAvailable: To update the status of sound demo availability status.
     * @param bStatus: Current status of sound demo feature
     * @return void
     */
    void setDemoAvailable(bool bStatus);

    /**
     * @brief getInstance: Returns the static instance of sound demo adapter.
     * @param void
     * @return pointer of CSoundDemoAdaptor
     */
    static CSoundDemoAdaptor *getInstance();

    /**
     * @brief getActiveAudioPreset: TO get the active audio preset stored before sound demo was activated.
     * @param void
     * @return preset active before sound demo
     */
    CAudioEnums::EAudioPresets getActiveAudioPreset() const;

    /**
     * @brief setActiveAudioPreset: To save the audio preset active in the system before activating sound demo.
     * @param activeAudioPreset: current active audio preset
     * @return void
     */
    void setActiveAudioPreset(const CAudioEnums::EAudioPresets &activeAudioPreset);

    /**
     * @brief invSelectTrack: To select a track for playback
     * @param iIndex: index of the track to be played.
     * @param iTrackId: Id of the track to be played.
     * @return void
     */
     Q_INVOKABLE void invSelectTrack(int iIndex, int iTrackId);

    /**
     * @brief selectedTrackIndex Return the current active demo track index
     * @return track index
     */
    int selectedTrackIndex() {return m_iSelectedTrack;}

    /**
     * @brief createDemoModel: This function will create the sound demo model and fill the model with data
     * @param void
     * @return void
     */
    void initModel(CMediaBrowseCategoryListModel* pListModel);

 signals:
    /**
     * @brief demoModelChanged: Signal to upadte the change in sound demo model
     * @param void
     * @return void
     */
    void demoModelChanged();

    /**
     * @brief demoAvailableChanged: Signal to update the change in availability status of sound demo feature
     * @param void
     * @return void
     */
    void demoAvailableChanged();

    /**
     * @brief selectedTrackIndexChanged: Signal to update the track index change
     * @param void
     * @return void
     */
    void selectedTrackIndexChanged();

private slots:

    /**
     * @brief sltMediaPlayTime: Slot to handle media playtime updates from media  adaptor
     * @param void
     * @return void
     */
    void sltMediaPlayTime();

    /**
     * @brief sltMediaPlayState: Slot to handle media playstate updates from media  adaptor
     * @param void
     * @return void
     */
    void sltMediaPlayState();

    /**
     * @brief sltActiveEntSrcChanged: SLot to handle entertainment source changes
     * @param void
     * @return void
     */
    void sltActiveEntSrcChanged();

    /**
     * @brief sltBrowseSessionCreated: Slot to handle browse session creation
     * @param void
     * @return void
     */
    void sltBrowseSessionCreated();

    /**
     * @brief sltUpdateNowPlayingPointer: Signal to update the nowplaying pointer.
     * @param iOldIndex: list item index from where the highlight is to be removed.
     * @param iNewIndex: list item index to be highlighted.
     * @return void
     */
    void sltUpdateNowPlayingPointer(int iOldIndex, int iNewIndex);

    /**
     * @brief sltBrowseDataReceived: TO handle browse data signal to display the sound demo
     * @param iCategory
     * @return void
     */
    void sltBrowseDataReceived(int iCategory);


private:

    /**
     * @brief m_pInstance: Static instance of this class
     */
    static CSoundDemoAdaptor* m_pInstance;

    /**
     * @brief m_demoModel: Sound demo model to store the demo list
     */
    CSoundDemoModel m_demoModel;

    /**
     * @brief m_activeAudioPreset: Stores the active audio preset before sound demo is activated
     */
    CAudioEnums::EAudioPresets m_activeAudioPreset;

    /**
     * @brief m_bDemoAvailable: To store the availability of sound demo
     */
    bool m_bDemoAvailable;

    /**
     * @brief m_iSelectedTrack: To store the current selected track
     */
    int m_iSelectedTrack;
};

#endif // CSOUNDDEMOADAPTOR_H
