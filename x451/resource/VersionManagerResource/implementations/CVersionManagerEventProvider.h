/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CVersionManagerEventProvider.h
 * @ingroup       HMIComponent
 * @author        Rajat Gupta
 * CVersionManagerEventProvider, Class to send signals to Version Manager Application layer on Version Manager Resource events
 */

#ifndef CVERSIONMANAGEREVENTPROVIDER_H
#define CVERSIONMANAGEREVENTPROVIDER_H

#include <QObject>
#include <string>
#include <QString>
using namespace std;

/**
 * @brief The CVersionManagerEventProvider class send signals to Version Manager Application layer on Version Manager Resource events
 */
class CVersionManagerEventProvider: public QObject
{
    Q_OBJECT

public:
    /**
    * @brief	CVersionManagerEventProvider, Constructor
    * @param	QObject*
    * @return	void
    */
    CVersionManagerEventProvider(QObject* parent = 0);

    /**
    * @brief	~CVersionManagerEventProvider, Destructor
    * @param	void
    * @return	None
    */
    ~CVersionManagerEventProvider();

signals:

    /**
     * @brief sigVCInfoUpdateReceived, Signal to notify VC info has been updated
     * @param strVCInfo, Current VC Number string that has to be updated
     * @return void
     */
    void sigVCInfoUpdateReceived(const QString& strVCInfo);

    /**
     * @brief sigVINInfoUpdateReceived, Signal to notify VIN info has been updated
     * @param strVinInfo, Current string that has to be updated
     * @return void
     */
    void sigVINInfoUpdateReceived(const QString& strVinInfo);

    /**
     * @brief sigContainerPartNoUpdateReceived, Signal to notify Container part number  has been updated
     * @param strContainerPartNo, Current string that has to be updated
     * @return void
     */
    void sigContainerPartNoUpdateReceived(const QString& strContainerPartNo);

    /**
     * @brief sigSilverBoxPartNoUpdateReceived, Signal to notify Silver box part Number has been updated
     * @param strSilverBoxPartNo, Current string that has to be updated
     * @return void
     */
    void sigSilverBoxPartNoUpdateReceived(const QString& strSilverBoxPartNo);

    /**
     * @brief sigDisplayHWPartNoUpdateReceived, Signal to notify Display HW Part Number has been updated
     * @param strDisplayHWPartNo, Current string that has to be updated
     * @return void
     */
    void sigDisplayHWPartNoUpdateReceived(const QString& strDisplayHWPartNo);

    /**
     * @brief sigParameterizationPartNoUpdateReceived, Signal to notify Parameterization part number has been updated
     * @param strParameterizationPartNo, Current string that has to be updated
     * @return void
     */
    void sigParameterizationPartNoUpdateReceived(const QString& strParameterizationPartNo);

    /**
     * @brief sigButtonPanelPartNoUpdateReceived, Signal to notify Button Panel part number has been updated
     * @param strButtonPanelPartNo, Current string that has to be updated
     * @return void
     */
    void sigButtonPanelPartNoUpdateReceived(const QString& strButtonPanelPartNo);


    /**
     * @brief sigSOCSofVersionNoUpdateReceived, Signal to notify SOC software version number details data has been updated
     * @param strSOCSoftVersionNo, Current string that has to be updated
     * @return void
     */
    void sigSOCSofVersionNoUpdateReceived(const QString& strSOCSoftVersionNo);

    /**
     * @brief sigButtonPanelSofVersionNoUpdateReceived, Signal to notify Btn panel software version number details data has been updated
     * @param strbuttonPanelSoftVersionNo, Current string that has to be updated
     * @return void
     */
    void sigButtonPanelSofVersionNoUpdateReceived(const QString& strbuttonPanelSoftVersionNo);

    /**
     * @brief sigDisplayManagerSofVersionNoUpdateReceived, Signal to notify Display manager software version number details data has been updated
     * @param strDisplayManagerSoftVersionNo, Current string that has to be updated
     * @return void
     */
    void sigDisplayManagerSofVersionNoUpdateReceived(const QString& strDisplayManagerSoftVersionNo);

    /**
     * @brief sigPowerModeCfgTypeReceived: Signal to notify power mode data has been updated
     * @param strPowerMode : information regarding power mode
     * @return void.
     */
    void sigPowerModeCfgTypeReceived(const QString& strPowerMode);

    /**
     * @brief sigVersionMismatchEventReceived: Signal to notify version mismatch data has been updated
     * @param uiMismacthValue : information regarding version mismatch
     * @return void.
     */
    void sigVersionMismatchEventReceived(uint uiMismacthValue);

public:


    /**
    * @brief	vcInfoNumberReceived, This method will inform version manager event handler, that VC Info number is received.
    * @param	strVCInfo,  string that has current info about VC info number.
    * @return	void
    */
    void vcInfoNumberReceived(const QString& strVCInfo);

    /**
    * @brief	vinPartNumberReceived, This method will inform version manager event handler, that vin part number info is received.
    * @param	strVinInfo,  string that has current info about part number.
    * @return	void
    */
    void vinPartNumberReceived(const QString& strVinInfo);

    /**
    * @brief	containerPartNoReceived, This method will inform version manager event handler, that container part number info is received.
    * @param	strContainerPartNo,  string that has current info about part number.
    * @return	void
    */
    void containerPartNoReceived(const QString& strContainerPartNo);

    /**
    * @brief	silverBoxPartNoReceived, This method will inform version manager event handler, that silver box  part number info is received.
    * @param	strSilverBoxPartNo,  string that has current info about part number.
    * @return	void
    */
    void silverBoxPartNoReceived(const QString& strSilverBoxPartNo);

    /**
    * @brief	displayHWPartNoReceived, This method will inform version manager event handler, that display hw part number info is received.
    * @param	strDisplayHWPartNo,  string that has current info about part number.
    * @return	void
    */
    void displayHWPartNoReceived(const QString& strDisplayHWPartNo);

    /**
    * @brief	parameterizationPartNoReceived, This method will inform version manager event handler, thatparameterization part number info is received.
    * @param	strParameterizationPartNo,  string that has current info about part number.
    * @return	void
    */
    void parameterizationPartNoReceived(const QString& strParameterizationPartNo);

    /**
    * @brief	buttonPanelPartNoReceived, This method will inform version manager event handler, that button panel part number info is received.
    * @param	strButtonPanelPartNo,  string that has current info about part number.
    * @return	void
    */
    void buttonPanelPartNoReceived(const QString& strButtonPanelPartNo);

    /**
    * @brief	socSofVersionNoUpdateReceived, This method will inform version manager event handler, that SOC soft version number info is received.
    * @param	strSOCSoftVersionNo,  string that has current info about part number.
    * @return	void
    */
    void socSofVersionNoUpdateReceived(const QString& strSOCSoftVersionNo);

    /**
    * @brief	buttonPanelSofVersionNoUpdateReceived, This method will inform version manager event handler, that btn panel soft version number info is received.
    * @param	strbuttonPanelSoftVersionNo,  string that has current info about part number.
    * @return	void
    */
    void buttonPanelSofVersionNoUpdateReceived(const QString& strbuttonPanelSoftVersionNo);

    /**
    * @brief	displayManagerSofVersionNoUpdateReceived, This method will inform version manager event handler, that display manager  soft version number info is received.
    * @param	strDisplayManagerSoftVersionNo,  string that has current info about part number.
    * @return	void
    */
    void displayManagerSofVersionNoUpdateReceived(const QString& strDisplayManagerSoftVersionNo);

    /**
     * @brief powerModeCfgTypeReceived: This method will inform version manager event handler, that power mode info is received.
     * @param strPowerMode, Contains info aboout power mode.
     * @return void.
     */
    void powerModeCfgTypeReceived(const string &strPowerMode);

    /**
     * @brief versionMismatchEventReceived: This method will inform version manager event handler, that version mismatch info is received.
     * @param uiMismacthValue, Contains info about version mismatch like BP, DM, or BP and DM mismatch
     * @return void.
     */
    void versionMismatchEventReceived(uint uiMismacthValue);

};


#endif // CVERSIONMANAGEREVENTPROVIDER_H
