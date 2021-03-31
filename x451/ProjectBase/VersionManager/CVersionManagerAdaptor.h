/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CVersionManagerAdaptor.h
 * @ingroup         HMIComponent
 * @author          Rajat Gupta
 * CVersionManagerAdaptor, an Adaptor for Version Manager module,
 * CVersionManagerAdaptor used to communicate between QML and Resource Layer.
 */

#ifndef CVERSIONMANAGERADAPTOR_H
#define CVERSIONMANAGERADAPTOR_H

#include <QObject>
#include "CVersionManagerEnums.h"
#include "Test/VersionManager/CVersionManagerAdaptorTest.h"
#include "Test/VersionManager/CVersionManagerParamTest.h"
class IVersionManagerResource;

/**
 * @brief The CVersionManagerAdaptor class: This singleton class contains methods to handle Version Manager related functionality
 */

class CVersionManagerAdaptor : public QObject
{
    Q_OBJECT

    //Properties

    /* To get current Software Version */
    Q_PROPERTY(QString swVersion READ swVersion NOTIFY sigSwVersionChanged)

    /* To get current Software Release Date */
    Q_PROPERTY(QString swReleaseDate READ swReleaseDate NOTIFY sigSwReleaseDateChanged)

    /* Property for  VIN number information */
    Q_PROPERTY(QString vcInfo READ vcInfo NOTIFY sigVCInfoChanged)

    /* Property for  VIN number information */
    Q_PROPERTY(QString vinInfo READ vinInfo NOTIFY sigVINInfoChanged)

    /* Property for  container part number information */
    Q_PROPERTY(QString containerPartNo READ containerPartNo NOTIFY sigContainerPartNoChanged)

    /* Property for  silver box part number information */
    Q_PROPERTY(QString silverBoxPartNo READ silverBoxPartNo NOTIFY sigSilverBoxPartChanged)

    /* Property for  display HW part number information */
    Q_PROPERTY(QString displayHWPartNo READ displayHWPartNo NOTIFY sigDisplayHWPartNoChanged)

    /* Property for  parameterization part number information */
    Q_PROPERTY(QString parameterizationPartNo READ parameterizationPartNo NOTIFY sigParameterizationPartNoChanged)

    /* Property for  Button Panel part number information */
    Q_PROPERTY(QString buttonPanelPartNo READ buttonPanelPartNo NOTIFY sigButtonPanelPartNoChanged)

    /* Property for  Button panel Software version number information */
    Q_PROPERTY(QString btnPanelSoftVersionNo READ btnPanelSoftVersionNo NOTIFY sigBtnPanelSoftVersionNoChanged)

    /* Property for  Display Manager Software version number information */
    Q_PROPERTY(QString displayManagerSoftVersionNo READ displayManagerSoftVersionNo NOTIFY sigDisplayManagerSoftVersionNoChanged)

    /* Property for  SOC Software version number information */
    Q_PROPERTY(QString socSoftVersionNo READ socSoftVersionNo NOTIFY sigSOCSoftVersionNoChanged)

    /* To get power mode(IGN lock/PEPS) information */
    Q_PROPERTY(QString powerMode READ powerMode NOTIFY sigPowerModeChanged)


public:
    /**
    * @brief	This function get the instance of adaptor class.
    * @param	void
    * @return   pointer to CSoftwareUpdateAdaptor
    */
    static CVersionManagerAdaptor* getInstance();
	//Todo::Changed for Unit Test to keep the instance alive when it is destucted, then also
    static void releaseInstance();
    FRIEND_TEST(CVersionManagerAdaptorTest, CheckVersionManagerAdaptorInstanceIsNotNull);
    FRIEND_TEST(CVersionManagerAdaptorTest, CheckVersionManagerInitializedVariables);
    FRIEND_TEST(CVersionManagerAdaptorTest, checkforSetPowerModeIgnOnMode);
    FRIEND_TEST(CVersionManagerAdaptorTest, checkforSetPowerModePEPSMode);
    FRIEND_TEST(CVersionManagerAdaptorTest, checkSWUpdateActionOnVersionMismatch);
    FRIEND_TEST(CVersionManagerAdaptorTest, checkforVersionMismatch);
    //FRIEND_TEST(CVersionManagerParamTest,  CheckVersionManagerAdaptorParamInstanceIsNotNull);
    FRIEND_TEST(CVersionManagerParamTest,   checkForVersionMismatchParamTestCases);
    FRIEND_TEST(CVersionManagerAdaptorTest, checkForVersionMismatchParamTestCases);
    FRIEND_TEST(CVersionManagerAdaptorTest, checkforSetPowerModeInvalidData);
    FRIEND_TEST(CVersionManagerAdaptorTest, VersionMismatchTestCases2);
	
    /**
    * @brief	~CVersionManagerAdaptor, destructor of VersionManager Adaptor class.
    * @param	void.
    * @return   void.
    */
    ~CVersionManagerAdaptor();

    /**
     * @brief m_pVersionManagerAdaptor: Pointer of CVersionManagerAdaptor class
     *        for creating singleton instance.
     */
    static CVersionManagerAdaptor* m_pVersionManagerAdaptor;

    /**
    * @brief	This method will fetch version info from software update resource implementation.
    * @param	void
    * @return	void
    */
    void fetchVersionInfo();

    /**
    * @brief	This function will return current Software Version
    * @param	void
    * @return	QString: Software Version
    */
    QString swVersion();

    /**
    * @brief	This function will set current Software Version
    * @param	QString: current Software Version
    * @return	void
    */
    void setSwVersion(QString val);

    /**
    * @brief	This function will return current Software Release Date
    * @param	void
    * @return	QString: current Software Release Date
    */
    QString swReleaseDate();

    /**
    * @brief	This function will set current Software Release Date
    * @param	QString: current Software Release Date
    * @return	void
    */
    void setSwReleaseDate(QString val);

    /**
    * @brief	setVCInfo, This function will set current VC Info number
    * @param	strVCInfo: This string will hold the VC Info no.
    * @return	void
    */
    void setVCInfo(const QString& strVCInfo);

    /**
    * @brief	setVINInfo, This function will set current VIN number
    * @param	const QString& strVin, This string will hold the VIN no.
    * @return	void
    */
    void setVINInfo(const QString& strVin);

    /**
    * @brief	setContainerPartNo, This function will set current container part number
    * @param	const QString& strContainerPartNo, This string will hold the container part no.
    * @return	void
    */
    void setContainerPartNo(const QString& strContainerPartNo);

    /**
    * @brief	setSilverBoxPartNo, This function will set current silver box part number
    * @param	strSilverBoxPartNo, This string will hold the silver box part no.
    * @return	void
    */
    void setSilverBoxPartNo(const QString& strSilverBoxPartNo);

    /**
    * @brief	setDisplayHWPartNo, This function will set current display hardware part number
    * @param	strDisplayHWPartNo, This string will hold the display Hw part no.
    * @return	void
    */
    void setDisplayHWPartNo(const QString& strDisplayHWPartNo);

    /**
    * @brief	setParameterizationPartNo, This function will set current parameterization part number
    * @param	strParameterizationPartNo, This string will hold the parameterization no.
    * @return	void
    */
    void setParameterizationPartNo(const QString& strParameterizationPartNo);

    /**
    * @brief	setButtonPanelPartNo, This function will set current button panel part number
    * @param	strButtonPanelPartNo, This contains Button Panel Part no.
    * @return	void
    */
    void setButtonPanelPartNo(const QString& strButtonPanelPartNo);

    /**
    * @brief	setBtnPanelSoftVersionNo, This function will set Btn panel soft version no.
    * @param	strBtnPanelSoftVersionNo, This contains the btn panel soft version no.
    * @return	void
    */
    void setBtnPanelSoftVersionNo(const QString& strBtnPanelSoftVersionNo);

    /**
    * @brief	setDisplayManagerSoftVersionNo, This function will set current software part number
    * @param	strDisplayManagerSoftVersionNo, This contains the Display manager soft version no.
    * @return	void
    */
    void setDisplayManagerSoftVersionNo(const QString& strDisplayManagerSoftVersionNo);

    /**
    * @brief	setBtnPanelSoftVersionNo, This function will set current software part number
    * @param	strBtnPanelSoftVersionNo, This contains the SOC soft version no.
    * @return	void
    */
    void setSOCSoftVersionNo(const QString& strSOCSoftVersionNo);

    /**
    * @brief	versionMisMatchValueReceived, This function will set version mismatch value
    * @param	uiVerMismatchValue, This contains the version mismatch value
    * @return	void
    */
    void versionMisMatchValueReceived(uint uiVerMismatchValue);

    /**
    * @brief	versionMismatchEvent, This function will receive signal from qml to check if version mismatch exists or not
    * @param	void
    * @return	void
    */
    Q_INVOKABLE void versionMismatchEvent();

    /**
    * @brief	callSwUpdateOnVerMismatch, This function will call software update to update the software version
    * @param	void
    * @return	void
    */
    Q_INVOKABLE void callSwUpdateOnVerMismatch();

    /**
    * @brief	setPowerMode,This function will set current power mode type
    * @param	strPowerMode : IGN lock/ PEPS
    * @return	void
    */
    void setPowerMode(const QString& strPowerMode);

    /**
    * @brief	getPowerModeType. This function will return current power mode type
    * @param	void.
    * @return	m_ePowerModeType, return the  powerModeType
    */
    CVersionManagerEnums::EPowerModeType getPowerModeType() {  return m_ePowerModeType; }


    /**
    * @brief	vcInfo, This function will return VC Info number.
    * @param	void
    * @return	m_strVCInfo: returns the VC Info Number.
    */
    QString vcInfo() { return m_strVCInfo ; }

    /**
    * @brief	vinInfo, This function will return VIN number information
    * @param	void
    * @return	m_strVIN: Vehicle Identification Number
    */
    QString vinInfo() { return m_strVIN ; }

    /**
    * @brief	containerPartNo, This function will return container part number information
    * @param	void
    * @return	m_strContainerPartNo: Container part number
    */
    QString containerPartNo(){ return m_strContainerPartNo; }

    /**
    * @brief	silverBoxPartNo, This function will return silver box part number information
    * @param	void
    * @return	m_strSilverBoxPartNo: silver box part number
    */
    QString silverBoxPartNo(){ return m_strSilverBoxPartNo; }

    /**
    * @brief	displayHWPartNo, This function will return display HW part number information
    * @param	void
    * @return	m_strDisplayHWPartNo: Display HW part number
    */
    QString displayHWPartNo(){ return m_strDisplayHWPartNo; }

    /**
    * @brief	parameterizationPartNo, This function will return parameterization part number information
    * @param	void
    * @return	m_strParameterizationPartNo: Parameterization Part number
    */
    QString parameterizationPartNo(){ return m_strParameterizationPartNo; }

    /**
    * @brief	buttonPanelPartNo, This function will return buttonpanel part number information
    * @param	void
    * @return	m_strButtonPanelPartNo: Button Panel Part number
    */
    QString buttonPanelPartNo(){ return m_strButtonPanelPartNo ; }

    /**
    * @brief	btnPanelSoftVersionNo, This function will return SoftwarePartNo information
    * @param	void
    * @return	m_strBtnPanelSoftVersionNo: Button panel soft version number
    */
    QString btnPanelSoftVersionNo() { return m_strBtnPanelSoftVersionNo ; }

    /**
    * @brief	displayManagerSoftVersionNo, This function will return SoftwarePartNo information
    * @param	void
    * @return	m_strDisplayManagerVersionNo: display manager soft version number
    */
    QString displayManagerSoftVersionNo() { return m_strDisplayManagerVersionNo ; }

    /**
    * @brief	socSoftVersionNo, This function will return SOC soft version information
    * @param	void
    * @return	m_strSOCVersionNo: SOC soft version number
    */
    QString socSoftVersionNo() { return m_strSOCVersionNo ; }

    /**
    * @brief	This function will return power mode information
    * @param	void
    * @return	m_strPowerMode: Power mode(IGN lock/PEPS)
    */
    QString powerMode() { return m_strPowerMode ; }

signals:

    /**
    * @brief	This signal will emit Software Version on receiving Software Version
    * @param	void
    * @return	void
    */
    Q_SIGNAL void sigSwVersionChanged();

    /**
    * @brief	This signal will emit Software Release Date on receiving Software Release Date
    * @param	void
    * @return	void
    */
    Q_SIGNAL void sigSwReleaseDateChanged();

    /**
    * @brief	This signal will emit VC number information
    * @param	void
    * @return	void
    */
    void sigVCInfoChanged();

    /**
    * @brief	This signal will emit VIN number information
    * @param	void
    * @return	void
    */
    void sigVINInfoChanged();

    /**
    * @brief	This signal will emit container part number information
    * @param	void
    * @return	void
    */
    void sigContainerPartNoChanged();

    /**
    * @brief	This signal will emit silver box part number information
    * @param	void
    * @return	void
    */
    void sigSilverBoxPartChanged();

    /**
    * @brief	This signal will emit display hardware part number information
    * @param	void
    * @return	void
    */
    void sigDisplayHWPartNoChanged();

    /**
    * @brief	This signal will emit parameterization part number information
    * @param	void
    * @return	void
    */
    void sigParameterizationPartNoChanged();

    /**
    * @brief	This signal will be emitted when buttonPanel part number gets changed.
    * @param	void
    * @return	void
    */
    void sigButtonPanelPartNoChanged();

    /**
    * @brief	This signal will be emitted when Button panel soft version gets changed.
    * @param	void
    * @return	void
    */
    void sigBtnPanelSoftVersionNoChanged();

    /**
    * @brief	This signal will be emitted when display manager soft version gets changed.
    * @param	void
    * @return	void
    */
    void sigDisplayManagerSoftVersionNoChanged();

    /**
    * @brief	This signal will be emitted when SOC soft version gets changed.
    * @param	void
    * @return	void
    */
    void sigSOCSoftVersionNoChanged();

    /**
    * @brief	This signal will emit power mode(IGN lock/PEPS) information
    * @param	void
    * @return	void
    */
    void sigPowerModeChanged();


public slots:

private:
    /**
    * @brief	CVersionManagerAdaptor, Constructor
    * @param	QObject *parent : Parent class instance
    * @return   None
    */
    explicit CVersionManagerAdaptor(QObject *parent = nullptr);

    /**
     * @brief m_pVersionManagerResource, Pointer to IVersionManagerResource instance
    **/
    IVersionManagerResource* m_pVersionManagerResource;

    /**
     * @brief m_strVCInfo, This variable holds the VC Info number.
    **/
    QString m_strVCInfo;

    /**
     * @brief m_strVIN, This variable holds the VIN number details
    **/
    QString m_strVIN;

    /**
     * @brief m_strContainerPartNo ,This variable holds the container part number details
    **/
    QString m_strContainerPartNo;

    /**
     * @brief m_strSilverBoxPartNo, This variable holds the silver box part number details
     */
    QString m_strSilverBoxPartNo;

    /**
     * @brief m_strDisplayHWPartNo, This variable holds the display hardware part number details
     */
    QString m_strDisplayHWPartNo;

    /**
     * @brief m_strParameterizationPartNo, This variable holds the parameterization part number details
     */
    QString m_strParameterizationPartNo;

    /**
     * @brief m_strButtonPanelPartNo, This variable holds the button panel part number details
     */
    QString m_strButtonPanelPartNo;

    /**
     * @brief m_strBtnPanelSoftVersionNo, This variable holds the button panel soft version details
     */
    QString m_strBtnPanelSoftVersionNo;

    /**
     * @brief m_strDisplayManagerVersionNo, This variable holds the display manager soft version details
     */
    QString m_strDisplayManagerVersionNo;

    /**
     * @brief m_strSOCVersionNo, This variable holds the SOC soft version details
     */
    QString m_strSOCVersionNo;

    /**
     * @brief m_strPowerMode, This variable holds the power mode details
     */
    QString m_strPowerMode;

    /**
     * @brief m_ePowerModeType, This enum holds the power mode type
     */
    CVersionManagerEnums::EPowerModeType m_ePowerModeType;

    /**
     * @brief m_uiVersionMismatchValue , This variable holds the version mismatch type
     */
    uint m_uiVersionMismatchValue ;

    /* This variable holds the current Software Version */
    QString m_SwVersion;

    /* This variable holds the current Software Release Date */
    QString m_SwReleaseDate;
};

#endif // CVERSIONMANAGERADAPTOR_H
