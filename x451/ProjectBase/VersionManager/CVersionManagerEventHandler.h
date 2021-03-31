/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CVersionManagerEventHandler.h
* @ingroup      HMIComponent
* @author       Rajat Gupta
* @class        CVersionManagerEventHandler: Class has the slots for all the Signals sent by CVersionManagerEventHandler
*                                   which informs Version Manager Adaptor about Version Manager Resource Events
*/

#ifndef CVERSIONMANAGEREVENTHANDLER_H
#define CVERSIONMANAGEREVENTHANDLER_H

#include <QObject>
#include "Test/VersionManager/CVersionManagerEventHandlerTest.h"
class CVersionManagerAdaptor;

/**
 * @brief The CVersionManagerEventHandler class: This class is to handle Version Manager events.
 *          Version Manager resource event provider will emit signals and those will be handled here.
 */
class CVersionManagerEventHandler : public QObject
{
    Q_OBJECT
public:

    /**
    * @brief	CVersionManagerEventHandler - Constructor for event handler class CVersionManagerEventHandler
    * @param	QQuickItem
    * @return	void.
    **/
    explicit CVersionManagerEventHandler(QObject *parent = nullptr);

    /**
    * @brief	~CVersionManagerEventHandler - Destructor for event handler class CVersionManagerEventHandler
    * @param	QQuickItem
    * @return	void.
    **/
    ~CVersionManagerEventHandler();
    FRIEND_TEST(CVersionManagerEventHandlerTest, CheckSlotForPowerModeChanged);
    FRIEND_TEST(CVersionManagerEventHandlerTest, CheckVersionManagerEventHandlerInitializedVariables);
    FRIEND_TEST(CVersionManagerEventHandlerTest, CheckForOtherFunctionsCoverage);

public slots:


    /**
    * @brief	sltVCInfoUpdateReceived, This method will inform Version Manager adaptor to fetch 16Rpart number from resource layer.
    * @param	strVCInfo, this contains the VC info which was communicated with Version Manager Implementation class.
    * @return	void
    */
    void sltVCInfoUpdateReceived(const QString& strVCInfo);

    /**
    * @brief	sltVINInfoUpdateReceived, This method will inform Version Manager adaptor to fetch 16Rpart number from resource layer.
    * @param	strVinInfo, this contains the VIN info which was communicated with Version Manager Implementation class.
    * @return	void
    */
    void sltVINInfoUpdateReceived(const QString& strVinInfo);

    /**
    * @brief	sltContainerPartNoUpdateReceived, This method will inform Version Manager adaptor to fetch 16Rpart number from resource layer.
    * @param	strContainerPartNo, this contains the Container part  no which was communicated with Version Manager Implementation class.
    * @return	void
    */
    void sltContainerPartNoUpdateReceived(const QString& strContainerPartNo);

    /**
    * @brief	sltSilverBoxPartNoUpdateReceived, This method will inform Version Manager adaptor to fetch 16Rpart number from resource layer.
    * @param	strSilverBoxPartNo, this contains the Silver box part  no which was communicated with Version Manager Implementation class.
    * @return	void
    */
    void sltSilverBoxPartNoUpdateReceived(const QString& strSilverBoxPartNo);

    /**
    * @brief	sltDisplayHWPartNoUpdateReceived, This method will inform Version Manager adaptor to fetch software version number from resource layer.
    * @param	strDisplayHWPartNo, this contains the Display HW part no which was communicated with Version Manager Implementation class.
    * @return	void
    */
    void sltDisplayHWPartNoUpdateReceived(const QString& strDisplayHWPartNo);

    /**
    * @brief	sltParameterizationPartNoUpdateReceived, This method will inform Version Manager adaptor to fetch software version number from resource layer.
    * @param	strParameterizationPartNo, this contains the parameterization no which was communicated with Version Manager Implementation class.
    * @return	void
    */
    void sltParameterizationPartNoUpdateReceived(const QString& strParameterizationPartNo);

    /**
    * @brief	sltButtonPanelPartNoUpdateReceived, This method will inform Version Manager adaptor to fetch software version number from resource layer.
    * @param	strButtonPanelPartNo, this contains the Button panel part no which was communicated with Version Manager Implementation class.
    * @return	void
    */
    void sltButtonPanelPartNoUpdateReceived(const QString& strButtonPanelPartNo);


    /**
    * @brief	sltSOCSofVersionNoUpdateReceived, This method will inform Version Manager adaptor to fetch soc software version number from resource layer.
    * @param	strSOCSoftVersionNo, this contains the SOC soft version no which was communicated with Version Manager Implementation class.
    * @return	void
    */
    void sltSOCSofVersionNoUpdateReceived(const QString& strSOCSoftVersionNo);

    /**
    * @brief	sltButtonPanelSofVersionNoUpdateReceived, This method will inform Version Manager adaptor to fetch  btn panel software version number from resource layer.
    * @param	strBtnPanelSoftVersionNo, this contains the Button panel soft version no which was communicated with Version Manager Implementation class.
    * @return	void
    */
    void sltButtonPanelSofVersionNoUpdateReceived(const  QString& strBtnPanelSoftVersionNo);

    /**
    * @brief	sltDisplayManagerSofVersionNoUpdateReceived, This method will inform Version Manager adaptor to fetch display manager software version number from resource layer.
    * @param	strDisplayManagerSoftVersionNo, this contains the Display manager soft version no which was communicated with Version Manager Implementation class.
    * @return	void
    */
    void sltDisplayManagerSofVersionNoUpdateReceived(const QString& strDisplayManagerSoftVersionNo);

    /**
    * @brief	sltPowerModeCfgTypeReceived, This method will inform Version Manager adaptor to fetch power mode type from impl.
    * @param	strPowerMode, contains powerMode type
    * @return	void
    */
    void sltPowerModeCfgTypeReceived(const QString &strPowerMode);

    /**
    * @brief	sltVersionMismatchEventReceived, This method will inform Version Manager adaptor to fetch version mismatch value.
    * @param	uiVerMismatchValue, contains version mismatch type
    * @return	void
    */
    void sltVersionMismatchEventReceived(uint uiVerMismatchValue);

    /**
    * @brief Slot method that would be invoked whenever Power Mode changed signal is received
    * @param void
    * @param void
    */
    void sltPowerModeChanged();

private:

    /**
    * @brief	connectSignals, This function will connect signals and slots
    * @param	void
    * @return	void
    */
    void connectSignals();

    // It holds whether the last power state was in reduced CAN mode.
    bool m_bReducedCanStatus;
};

#endif // CVERSIONMANAGEREVENTHANDLER_H
