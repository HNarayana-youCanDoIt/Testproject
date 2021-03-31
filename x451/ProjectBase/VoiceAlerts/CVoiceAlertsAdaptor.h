/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CVoiceAlertsAdaptor.h
 * @ingroup       HMIComponent
 * @author        Guru Alingal
 * CVoiceAlertsAdapter, Class to adapt the voice alert data into platform sepecific
 * changes and to handle voice alert related fetures.
 */

#ifndef VOICEALERTSADAPTOR_H
#define VOICEALERTSADAPTOR_H

#include <QObject>
#include <VoiceAlertsData.h>
#include <CVoiceAlertsEventHandler.h>
#include "implementations/CVoiceAlertsResImpl.h"

class CVoiceAlertsResImpl;

class CVoiceAlertsAdaptor : public QObject
{
    Q_OBJECT

    /** Property to hold current voice alert text */
    Q_PROPERTY(QString strVAMsg READ strVAMsg NOTIFY sigVAMsgChanged)

    /** Property to hold current voice alert selection status*/
    Q_PROPERTY(bool voiceAlertSelection READ voiceAlertSelection NOTIFY sigVoiceAlertSelectionChanged)

    /** Property to hold current voice alert presence status*/
    Q_PROPERTY(bool voiceAlertPresence READ voiceAlertPresence NOTIFY sigVoiceAlertPresenceChanged)

public: //Member functions
    /**
     * @brief CVoiceAlertsAdaptor - Default destructor for CVoiceAlertsAdaptor
     * @param NA
     * @return NA
     */
    ~CVoiceAlertsAdaptor();

    /**
     * @brief getInstance - To return the instance CVoiceAlertsAdaptor
     * @param void
     * @return instance of CVoiceAlertsAdaptor
     */
    static CVoiceAlertsAdaptor& getInstance();

    /**
     * @brief displayVoiceAlert - To display the voice alert
     * @param eVoiceAlert -  voice alert to be displayed
     * @return true if processed successfully else false
     */
    bool displayVoiceAlert(CVoiceAlertsEnums::EVoiceAlerts eVoiceAlert);

    /**
     * @brief displayMceVoiceAlert - To display the Mce voice alert
     * @param eMceVoiceAlert -  voice alert to be displayed
     * @return true if processed successfully else false
     */
    bool displayMceVoiceAlert(CVoiceAlertsEnums::EMceVoiceAlerts eMceVoiceAlert);

    /**
     * @brief displayVoiceAlert - To close the voice alert
     * @param void.
     * @return true if processed successfully else false
     * */
    bool closeVoiceAlert();

    /**
     * @brief strVAMsg - To read the voice alert message
     * @param void.
     * @return voice alert message
     */
    QString strVAMsg();

    /**
     * @brief updateVAMsg - To update the voice alert message to be displayed
     * @param strMsg - New value to be added in strVAMsg
     * @return void.
     */
    void updateVAMsg(QString strMsg);

    /**
     * @brief getECurrAlertState - To get the current state of voice alert
     * @param void
     * @return current state of voice alert
     */
    CVoiceAlertsEnums::EVoiceAlertsState getECurrAlertState() const;

    /**
     * @brief setECurrAlertState - To set the current state of voice alert
     * @param eCurrAlertState - state of voice alert
     * @return void
     */
    void setECurrAlertState(const CVoiceAlertsEnums::EVoiceAlertsState &eCurrAlertState);

    /**
     * @brief getECurrAlert - To get curret active vocie alert
     * @param void
     * @return - current active voice alert
     */
    CVoiceAlertsEnums::EVoiceAlerts getECurrAlert() const;

    /**
     * @brief setECurrAlert - To set the current active voce alert
     * @param iCurrAlert - current active voice alert
     * @return void
     */
    void setECurrAlert(int iCurrAlert);

    /**
     * @brief getEMceCurrAlert - To get active vocie alert for Mce
     * @param void
     * @return - active voice alert for Mce
     */
    CVoiceAlertsEnums::EMceVoiceAlerts getEMceCurrAlert() const;

    /**
     * @brief setECurrMceAlert - To set the current active voce alert for Mce
     * @param iCurrMceAlert - current active voice alert for Mce
     * @return void
     */
    void setECurrMceAlert(int iCurrMceAlert);

    /**
     * @brief voiceAlertSelection - To get the current voice alert selection status
     * @param   void
     * @return - current voice alert selection
     */
    bool voiceAlertSelection() {return m_bVoiceAlertSelection;}
    /**
     * @brief setVoiceAlertSelection - To set the voice alert selection on HU
     * @param bVoiceAlertSelection - true if voice alert selection set enable, else false
     * @return - void.
     */
    void setVoiceAlertSelection(bool bVoiceAlertSelection);

    /**
     * @brief driveModeUpdate - Method will get invoked when drive mode changes and HMI recieves drive mode update.
     * @param eDriveMode - drive mode type
     * @return void.
     */
    void driveModeUpdate(CVoiceAlertsEnums::EDriveModes eDriveMode);

    /**
     * @brief voiceAlertPresence : To get the voice alert presence status.
     * @param   void.
     * @return true if voice alert is present else false
     */
    bool voiceAlertPresence() {return m_bVoiceAlertPresence;}

    /**
     * @brief setDriveModeStatusData : To set drive mode status data.
     * @param iDriveModeStatus: drive mode status data.
     * @return void
     */
    void setDriveModeStatusData(int iDriveModeStatus);
    /**
     * @brief setVoiceAlertPresence - To set the voice alert feature presence on HU
     * @param bVoiceAlertPresence  - true if voice alert feature present else false
     * @return - void.
     */
    void setVoiceAlertPresence(bool bVoiceAlertPresence);

    /**
    * @brief	This function is called from qml to set voice alert selection  value on HU.
    * @param	bVoiceAlertSelection: true if voice alert selection set enable, else false status which has set from qml.
    * @return	void
    */
    Q_INVOKABLE void setVoiceAlertSelectionAttribute(bool bVoiceAlertSelection);

signals:
    /**
     * @brief sigVAMsgChanged - Signal to indicate voice alert message update
     * @param void.
     * @return void.
     */
    void sigVAMsgChanged();

    /**
     * @brief sigVoiceAlertSelectionChanged - Signal to indicate voice alert selection on HU update
     * @param   void.
     * @return  void.
     */
    void sigVoiceAlertSelectionChanged();

    /**
     * @brief sigVoiceAlertPresenceChanged - Signal to indicate voice alert feature presence on HU.
     * @param   void.
     * @return  void.
     */
    void sigVoiceAlertPresenceChanged();

private: //Member Functions
    /**
     * @brief CVoiceAlertsAdaptor - Default constructor for CVoiceAlertsAdaptor
     * @param NA
     * @return NA
     */
    CVoiceAlertsAdaptor();

    /**
     * @brief initVoiceAlertsList - To add the available list of voice alerts in
     * the system to m_listAvailVoiceAlerts
     * @param - void
     * @return - void
     */
    void initVoiceAlertsList();

    /**
     * @brief processVoiceAlerts- To handle the  voice alerts based on the input
     * received from system.
     * @param void.
     * @return void.
     */
    void processVoiceAlerts();

private:  //Member Variables

    /* Instance of class Voice alert resource*/
    IVoiceAlerts* m_pVoiceAlertsResource;

    /**
     * @brief strVAMsg - Message to be displayed in voice alert notification.
     */
    QString m_strVAMsg;

    /** @brief m_eCurrAlert - To store the current active voice alert */
    CVoiceAlertsEnums::EVoiceAlerts m_eCurrAlert;

    /** @brief m_eCurrMceAlert - To store the current active voice alert for Mce */
    CVoiceAlertsEnums::EMceVoiceAlerts m_eCurrMceAlert;

    /** @brief m_eCurrAlert - To store the state of current active voice alert*/
    CVoiceAlertsEnums::EVoiceAlertsState m_eCurrAlertState;

    /** @brief m_spInst - Static instance of the CVoiceAlertsAdaptor class to be
     * returned as single instance of CVoiceAlertsAdaptor */
    static CVoiceAlertsAdaptor* m_spInst;

    /** @brief m_mapAvailVoiceAlerts - Map of available voice alerts*/
    std::map<CVoiceAlertsEnums::EVoiceAlerts, CDataVoiceAert> m_mapAvailVoiceAlerts;

    /** @brief m_mapAvailMceVoiceAlerts - Map of available voice alerts*/
    std::map<CVoiceAlertsEnums::EMceVoiceAlerts, CDataMceVoiceAert> m_mapAvailMceVoiceAlerts;

    /** @brief m_bVoiceAlertSelection - To store the voice alert selection*/
    bool m_bVoiceAlertSelection;

    /** @brief m_bVoiceAlertPresence - To store the voice alert presence*/
    bool m_bVoiceAlertPresence;

};

#endif // VOICEALERTSADAPTOR_H
