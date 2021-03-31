/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CThemeElement.h
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * CThemeElement.h, theme element file, responsible for creating theme presets
 *                  data model class instances and contains current active theme preset data
 */
#ifndef THEMEELEMENT_H
#define THEMEELEMENT_H

#include <QObject>
#include <QString>
#include "CAudioEnums.h"
#include "CThemeElement.h"

/**
 * @brief The CThemeElement class : Responsible for holding the current theme preset data like fan speed, temperature, distribution mode etc.,
 */
class CThemeElement : public QObject
{
    Q_OBJECT

    // Properties //

    // to get fanspeed value of respective theme preset
    Q_PROPERTY(int fanspeed READ fanspeed WRITE setFanSpeed NOTIFY sigFanSpeedChanged)

    // to get temperature value of respective theme preset
    Q_PROPERTY(float temperature READ temperature WRITE setTemperature NOTIFY sigTemperatureChanged)

    // to get air flow distribution mode value of respective theme preset
    Q_PROPERTY(int airFlowDistributionMode READ airFlowDistributionMode  NOTIFY sigAirFlowDistributionModeChanged)

    // to get color mode value of respective theme preset
    Q_PROPERTY(int themeColor READ themeColor WRITE setColorMode NOTIFY sigColorModeChanged)

    //to get theme display brightness of respective theme preset
    Q_PROPERTY(int themeDisplayBrightness READ themeDisplayBrightness WRITE setThemeDisplayBrightness NOTIFY sigThemeDisplayBrightnessChanged)

    //to get notification volume of respective theme preset
    Q_PROPERTY(int notificationVolume READ notificationVolume WRITE setNotificationVolume NOTIFY sigNotificationVolumeChanged)

    //to get audio preset of respective theme preset
    Q_PROPERTY(int audioPreset READ audioPreset WRITE setThemeAudioPreset NOTIFY sigThemeAudioPresetChanged)

    //to get bass value of respective theme preset
    Q_PROPERTY(int themeBass READ themeBass NOTIFY sigThemeBassValueChanged)

    //to get mid value of respective theme preset
    Q_PROPERTY(int themeMid READ themeMid NOTIFY sigThemeMidValueChanged)

    //to get mid value of respective theme preset
    Q_PROPERTY(int themeTreble READ themeTreble NOTIFY sigThemeTrebleValueChanged)

    //to get ambient light illumination level value of respective theme preset
    Q_PROPERTY(int themeAmbLightIlluLevel READ themeAmbLightIlluLevel WRITE setThemeAmbLightIlluLevel NOTIFY sigThemeAmbLightIlluLevelChanged)

public:
    explicit CThemeElement(int iFanSpeed, float fTemeperature, int iDistributionMode, int iColorMode, int iThemeDisplayBrightness,
                           int iNotificationVol, int iThemeAudioPreset, int iThemeBassValue, int iThemeMidValue,
                           int iThemeTrebleValue, int iThemeAmbLightIlluLevel, QObject *parent = nullptr);
    ~CThemeElement();

    /**
     * @brief getInstance, provides the instance of the CThemeElement
     * @return
     */
    static CThemeElement* getInstance();

    /**
    * @brief fanspeed : Method to get fan speed.
    * @param	void.
    * @return	fanspeed: fan speed value.
    **/
    int fanspeed() const { return m_iFanSpeed ;}

    /**
    * @brief setFanSpeed : Method to set fan speed.
    * @param   iFanSpeed : fan speed value of theme preset.
    * @return	void.
    **/
    Q_INVOKABLE void setFanSpeed(int iFanSpeed);

    /**
    * @brief temperature : Method to get temperature speed.
    * @param	void.
    * @return	temperature: temperature value.
    **/
    float temperature() const { return m_fTemperature ; }

    /**
    * @brief setTemperature : Method to set temperature.
    * @param	fTemperature : temperature value of theme preset.
    * @return	void.
    **/
    Q_INVOKABLE void setTemperature(float fTemperature);

    /**
    * @brief airFlowDistributionMode : Method to get air flow distribution mode.
    * @param	void.
    * @return	airFlowDistributionMode: airFlowDistributionMode value.
    **/
    int airFlowDistributionMode() { return m_iAirFlowDistributionMode; }

    /**
    * @brief setAirFlowDistributionMode : Method to set air Flow Distribution mode.
    * @param	iAirFlowDistributionMode : air flow mode value of theme preset.
    * @return	void.
    **/
    Q_INVOKABLE void setAirFlowDistributionMode(int iAirFlowDistributionMode);

    /**
    * @brief themeColor : Method to get color mode.
    * @param	void.
    * @return	colormode: theme color value.
    **/
    int themeColor() const {return m_iColorMode; }

    /**
    * @brief setColorMode :	Method to set color mode.
    * @param	iColorMode : color mode value of theme preset
    * @return	void.
    **/
    Q_INVOKABLE void setColorMode(int iColorMode);

    /**
     * @brief themeDisplayBrightness : Method to get theme display brightness value.
     * @param m_iThemeDisplayBrightness : theme display brightness value.
     * @return  void.
     */
    int themeDisplayBrightness() const {return m_iThemeDisplayBrightness; }

    /**
     * @brief setThemeDisplayBrightness : Method to set Display brightness
     * @param iThemeDisplayBrightness : display brightness of theme preset
     * @return  void.
     */
    Q_INVOKABLE void setThemeDisplayBrightness(int iThemeDisplayBrightness);

    /**
     * @brief notificationVolume : Method to get notification volume.
     * @param   void.
     * @return  notificationVolume : notification volume
     */
    int notificationVolume() const {return m_iNotificationVol; }

    /**
    * @brief setNotificationVolume :	Method to set notification volume.
    * @param	iNotifiactionVol : notification volume value.
    * @return	void.
    **/
    Q_INVOKABLE void setNotificationVolume(int iNotifiactionVol);

    /**
     * @brief audioPreset : Method to get audio preset.
     * @param   void.
     * @return  audioPreset : audioPreset value
     */
    int audioPreset() const {return m_iThemeAudioPreset ;}

    /**
    * @brief setThemeAudioPreset :	Method to set Audio preset.
    * @param	iAudioPreset : audio preset value.
    * @return	void.
    **/
    Q_INVOKABLE void setThemeAudioPreset(int iThemeAudioPreset);

    /**
    * @brief invGetThemeAudioPresetText :	Method to get theme Audio preset text.
    * @param	iThemeAudioPresetIndex : audio preset index.
    * @return	void.
    **/
    Q_INVOKABLE QString invGetThemeAudioPresetText(int iThemeAudioPresetIndex);

    /**
     * @brief themeBass : Method to get theme bass value
     * @param   void
     * @return themeBass : theme bass value
     */
    int themeBass() {return m_iThemeBass ;}

    /**
    * @brief setThemeBassValue :	Method to set theme bass.
    * @param	iThemeBass : theme bass value.
    * @return	void.
    **/
    Q_INVOKABLE void setThemeBassValue(int iThemeBass);

    /**
     * @brief themeMid : Method to get theme mid value
     * @param   void
     * @return themeMid : theme mid value
     */
    int themeMid() {return m_iThemeMid ;}

    /**
    * @brief setThemeMidValue :	Method to set theme mid.
    * @param	iThemeMid : theme mid value.
    * @return	void.
    **/
    Q_INVOKABLE void setThemeMidValue(int iThemeMid);

    /**
     * @brief themeTreble : Method to get theme treble.
     * @param  void.
     * @return themeTreble : theme treble value.
     */
    int themeTreble() {return m_iThemeTreble;}

    /**
     * @brief setThemeTrebleValue : Method to set theme treble value
     * @param iThemeTreble : theme treble value
     * @return void.
     */
    Q_INVOKABLE void setThemeTrebleValue(int iThemeTreble);

    /**
     * @brief themeAmbLightIlluLevel
     * @return
     */
    int themeAmbLightIlluLevel() const {return m_iThemeAmbLightIlluLevel;}
    /**
     * @brief setThemeAmbLightIlluLevel
     * @param iThemeAmbLightIlluLevel
     */
    Q_INVOKABLE void setThemeAmbLightIlluLevel(int iThemeAmbLightIlluLevel);
signals:
    /**
    * @brief sigFanSpeedChanged : This signal will emit fan speed value.
    * @param	void.
    * @return	void.
    **/
    void sigFanSpeedChanged();

    /**
    * @brief sigTemperatureChanged : This signal will emit temperature value.
    * @param	void.
    * @return	void.
    **/
    void sigTemperatureChanged();

    /**
    * @brief sigAirFlowDistributionModeChanged : This signal will emit air flow distribution mode value on changed.
    * @param	void.
    * @return	void.
    **/
    void sigAirFlowDistributionModeChanged();

    /**
    * @brief sigColorModeChanged : This signal will emit color mode value on changed.
    * @param	void.
    * @return	void.
    **/
    void sigColorModeChanged();

    /**
     * @brief sigThemeDisplayBrightnessChanged : This signal will emit theme display brightness value on changed.
     * @param   void.
     * @return  void.
     */
    void sigThemeDisplayBrightnessChanged();

    /**
     * @brief sigNotificationVolumeChanged : This signal will emit notification volume on changed
     * @param   void.
     * @return  void.
     */
    void sigNotificationVolumeChanged();

    /**
     * @brief sigThemeAudioPresetChanged : This signal will emit audio preset value on changed
     * @param   void.
     * @return  void.
     */
    void sigThemeAudioPresetChanged();

    /**
     * @brief sigThemeBassValueChanged : This signal will emit theme bass value on changed
     * @param   void.
     * @return  void.
     */
    void sigThemeBassValueChanged();

    /**
     * @brief sigThemeMidValueChanged : This signal will emit theme mid value on changed
     * @param   void.
     * @return  void.
     */
    void sigThemeMidValueChanged();

    /**
     * @brief sigThemeTrebleValueChanged : This signal will emit theme treble value on changed
     * @param   void.
     * @return  void.
     */
    void sigThemeTrebleValueChanged();

    /**
     * @brief sigThemeAmbLightIlluLevelChanged : This signal will emit theme ambient light illumination level on changed
     * @param   void.
     * @return  void.
     */
    void sigThemeAmbLightIlluLevelChanged();

private:

    /**
     * @brief mapThemeAudioPreset : This method is used to insert audio presets values in a map
     * @param   void.
     * @return  void.
     */
    void mapThemeAudioPreset();

public:

    /**
     * @brief CHVACAdaptor constructor
     * @param parent parent object instance
     * @return void
     */
    explicit CThemeElement(QObject *parent = nullptr);

    static CThemeElement* m_pThemeElement;

    /* This variable holds the fanspeed value*/
    int m_iFanSpeed;
    /* This variable holds the temperature value*/
    float m_fTemperature;
    /* This variable holds the air flow distribution mode */
    int m_iAirFlowDistributionMode;
    /* This variable holds the theme color value*/
    int m_iColorMode;
    /*This variable holds the notification volume value*/
    int m_iNotificationVol;
    /*This variable holds the audio preset value*/
    int m_iThemeAudioPreset;
    /* This variable holds the theme bass value */
    int m_iThemeBass;
    /* This variable holds the theme mid value */
    int m_iThemeMid;
    /* This variable holds the theme treble value */
    int m_iThemeTreble;
    /* This variable holds the theme ambient illumination level*/
    int m_iThemeAmbLightIlluLevel;

    /**
     * @brief m_iThemeDisplayBrightness : This variable holds the theme display brightness value
     */
    int m_iThemeDisplayBrightness;
    /* This variable holds the mapping of audio preset values */
    QMap<CAudioEnums::EAudioPresets,QString> m_mapAudioPresetTheme;
};

#endif // THEMEELEMENT_H
