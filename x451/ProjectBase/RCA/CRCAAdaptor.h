/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CRCAAdaptor.h
 * @ingroup         HMIComponent
 * @author          Nishant Khandagale
 * CRCAAdaptor, an Adaptor for RCA module,
 * CRCAAdaptor used to communicate between QML and Resource Layer.
 */

#ifndef CRCAADAPTOR_H
#define CRCAADAPTOR_H

#include <QObject>
#include "CRCAEnums.h"
#include "Media/CMediaAdaptor.h"

class IRCAResource;
class CAudioAdaptor;

/**
 * @brief The CRCAAdaptor, an Adaptor for RCA module,
 * CRCAAdaptor used to communicate between QML and Resource Layer.
 */
class CRCAAdaptor : public QObject
{
    Q_OBJECT

    //Properties
    // to get current bass/Mid/Treble value
    Q_PROPERTY(int iBassMidTrebleValue     READ iBassMidTrebleValue    WRITE setBassMidTrebleValue    NOTIFY sigBassMidTrebleValueChanged)

    // to get current bass/Mid/Treble name
    Q_PROPERTY(QString strBassMidTrebleName     READ strBassMidTrebleName    WRITE setBassMidTrebleName   NOTIFY sigBassMidTrebleNameChanged)

    // to get current Aux gain text
    Q_PROPERTY(QString strAuxGainText     READ strAuxGainText    WRITE setAuxGainText   NOTIFY sigAuxGainTextChanged)

    // to get current audio preset text
    Q_PROPERTY(QString strAudioPresetText     READ strAudioPresetText    WRITE setAudioPresetText   NOTIFY sigAudioPresetTextChanged)

    // to get current audio preset text
    Q_PROPERTY(QString strBalanceFaderImageSource     READ strBalanceFaderImageSource    WRITE setBalanceFaderImageSource   NOTIFY sigBalanceFaderImageSourceChanged)


public:
    /**
     * @brief getInstance: provides the instance of the RCA adaptor
     * @return CRCAAdaptor: RCA adaptor object
     */
    static CRCAAdaptor* getInstance();

    /**
     * @brief CRCAAdaptor: destructor
     * @param void
     * @return void
     */
    ~CRCAAdaptor();


    // All the RCA property setters and getters

    /**
     * @brief setRCAActionsInitiated: setter for RCA Action Initiated
     * @param eRCAActionInitiated: RCA action initiated
     * @param uiIntInfo: int data to be passed
     * @return void
     */
    void setRCAActionsInitiated(CRCAEnums::ERCAActionInitiated eRCAActionInitiated, uint uiIntInfo);

    /**
     * @brief isRCAActionSet: gets whether the specified action is set or not
     * @param eRCAAction: RCA action initiated
     * @return bool : true if specified RCA action is set, else false
     */
    bool isRCAActionSet(CRCAEnums::ERCAActionInitiated eRCAAction);

    /**
     * @brief clearRCAAction: clears the specified RCA Action from m_iRCAActionsInitiated
     * @param eRCAAction: RCA action initiated
     * @return void
     */
    void clearRCAAction(CRCAEnums::ERCAActionInitiated eRCAAction);


    /**
    * @brief	iBassMidTrebleValue: This function will return bass/mid/treble changed value.
    * @param	void.
    * @return	int: bass/Mid/Treble Value
    */
    int iBassMidTrebleValue();

    /**
    * @brief	strBassMidTrebleName: This function will return bass/mid/treble changed name.
    * @param	void.
    * @return	QString: bass/mid/treble name
    */
    QString strBassMidTrebleName();

    /**
    * @brief	strAuxGainText: This function will return aux gain text.
    * @param	void.
    * @return	QString: Aux gain text
    */
    QString strAuxGainText();

    /**
    * @brief	strAudioPresetText: This function will return audio preset text.
    * @param	void.
    * @return	QString: Aux gain text
    */
    QString strAudioPresetText();

    /**
    * @brief	strBalanceFaderImageSource: This function will return Balance fader image source.
    * @param	void.
    * @return	QString: Aux gain text
    */
    QString strBalanceFaderImageSource();


    /**
    * @brief	setBassMidTrebleValue: This function will set bass/mid/treble changed value.
    * @param	int: bass/Mid/Treble Value
    * @return	void
    */
    void setBassMidTrebleValue(int iBassMidTrebleValue);

    /**
    * @brief	setBassMidTrebleName: This function will set bass/mid/treble changed name.
    * @param	QString: bass/mid/treble name
    * @return	void
    */
    void setBassMidTrebleName(const QString &strBassMidTrebleName);

    /**
    * @brief	setAuxGainText: This function will set Aux gain text.
    * @param	QString: Aux gain text
    * @return	void
    */
    void setAuxGainText(const QString &strAuxGainText);

    /**
    * @brief	setAudioPresetText: This function will set AudioPreset text.
    * @param	QString: Audio preset text
    * @return	void
    */
    void setAudioPresetText(const QString &strAudioPresetText);

    /**
    * @brief	setBalanceFaderImageSource: This function will set balance fader image source.
    * @param	QString: balance fader image source
    * @return	void
    */
    void setBalanceFaderImageSource(const QString &strBalanceFaderImageSource);

    /**
     * @brief setHMIMediaBrowseStatus: sets the HMI browse Status
     * @param bIsHMIInBrowseState: status of HMI media browse status
     *        (true : HMI is in media browse state, false : HMI is not in media browse state)
     * @return void
     */
    void setHMIMediaBrowseStatus(bool bIsHMIInBrowseState);

private:

    /**
    * @brief	showBassMidTreblePopup: This function will show bass/mid/treble popup.
    * @param	void
    * @return	void
    */
    void showBassMidTreblePopup();

    /**
     * @brief isAudioSetupStateActive: return sct audio setup state's active status
     * @param void
     * @return bool: audio setup state's active status
     */
    bool isAudioSetupStateActive();

signals:

    /**
    * @brief	sigBassMidTrebleValueChanged: This signal will emit bass/Mid/Treble value whenever bass/Mid/Treble gets changed.
    * @param	void.
    * @return	void
    */
    void sigBassMidTrebleValueChanged();

    /**
    * @brief	sigBassMidTrebleNameChanged: This signal will emit Bass/Mid/Treble Name whenever Bass/Mid/Treble gets changed.
    * @param	void.
    * @return	void
    */
    void sigBassMidTrebleNameChanged();

    /**
    * @brief	sigAuxGainTextChanged: This signal will emit Aux gain text whenever aux gain gets changed.
    * @param	void.
    * @return	void
    */
    void sigAuxGainTextChanged();

    /**
    * @brief	sigAuxGainTextChanged: This signal will emit Audio preset text whenever audio preset gets changed.
    * @param	void.
    * @return	void
    */
    void sigAudioPresetTextChanged();

    /**
    * @brief	sigBalanceFaderImageSourceChanged: This signal will emit Balance Fader Image Source whenever Balance Fader Image Source gets changed.
    * @param	void.
    * @return	void
    */
    void sigBalanceFaderImageSourceChanged();

public slots:

    /**
     * @brief sltBassChanged: Method gets invoked whenever there is a change in bass value
     * @param void
     * @return void
     */
    void sltBassChanged();

    /**
     * @brief sltBassChanged: Method gets invoked whenever there is a change in middle value
     * @param void
     * @return void
     */
    void sltMidChanged();

    /**
     * @brief sltTrebleChanged: Method gets invoked whenever there is a change in treble value
     * @param void
     * @return void
     */
    void sltTrebleChanged();

    /**
     * @brief sltAudioPresetChanged: Method gets invoked whenever there is a change in audio preset
     * @param void
     * @return void
     */
    void sltAudioPresetChanged();

    /**
     * @brief sltBalanceFaderChanged: Method gets invoked whenever there is a change in balance or fader
     * @param void
     * @return void
     */
    void sltBalanceFaderChanged();

    /**
    * @brief sltNowPlayingChanged: Slot for now playing (audio/video) change event
    * @param void
    * @return void
    */
    void sltNowPlayingChanged();

    /**
     * @brief sltAuxGainValueChanged: slot gets invoked whenever there is a change in Aux Gain
     * @param void
     * @return void
     */
    void sltAuxGainValueChanged();

    /**
     * @brief   sltPopupResult: Slot to be connected to PopupManager's signal sigPopupResult to handle
     *          Popup events
     * @param   ePopupId - Id of the Popup
     * @param   EPopupPriority - Result of the Popup(Displayed, Closed or Ignored)
     * @param   strAdditionalInfo - Additional info (based on reason on which popup is closed)
     * @return  void.
     */
    void sltPopupResult(CPopupEnum::EPopupID ePopupId, CPopupEnum::EPopupResult ePopupResult, QString strAdditionalInfo);

private:

    /**
     * @brief CRCAAdaptor: constructor
     * @param pParent: parent object instance
     * @return void
     */
    explicit CRCAAdaptor(QObject *pParent = nullptr);

    /**
    * @brief	connectSignals: This function will connect signals from other adaptor to the corresponding slots in RCA Adaptor
    * @param	void
    * @return	void
    **/
    void connectSignals();

    /**
     * @brief m_pRCAAdaptor: Instance of RCA Adaptor
     */
    static CRCAAdaptor* m_pRCAAdaptor;

    /**
     * @brief m_iRCAActionsInitiated: RCA Actions initiated
     */
    uint8_t m_iRCAActionsInitiated;

    /**
     * @brief m_strAuxGainText: This variable holds the Aux gain text
     */
    QString m_strAuxGainText;

    /**
     * @brief m_strAudioPresetText: This variable holds the Audio preset text
     */
    QString m_strAudioPresetText;

    /**
     * @brief m_iBassMidTrebleValue: This variable holds the bass/Mid/Treble value
     */
    int m_iBassMidTrebleValue;

    /**
     * @brief m_strBassMidTrebleName: This variable holds the bass/Mid/Treble Name
     */
    QString m_strBassMidTrebleName;

    /**
     * @brief m_strBalanceFaderImageSource: This variable holds the Balance Fader Image Source
     */
    QString m_strBalanceFaderImageSource;

    /**
     * @brief m_bIsHMIInBrowseState: bool whether HMI is in browse state
     */
    bool m_bIsHMIInBrowseState;

};

#endif // CRCAADAPTOR_H
