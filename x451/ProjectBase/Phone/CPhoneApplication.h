/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CPhoneApplication.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CPhoneApplication class that act as a mediator between QML and state machine.
 * It also load QML files related to Phone module.
 */

#ifndef CPHONEAPPLICATION_H
#define CPHONEAPPLICATION_H

#include <QObject>
#include "HMIIncludes.h"
#include "CPhoneEnum.h"

//! @category FORWARD DECLERATIONS
class CPhoneAdaptor;
class CPhoneSM;
class CPhoneEventHandler;

/*!
 * @class CPhoneApplication
 * @brief This class act as a mediator between QML and state machine.
 * It also load QML files related to Phone module.
 */
class CPhoneApplication : public CBaseApplication
{
    Q_OBJECT
public:
    explicit CPhoneApplication(QQuickItem* pParent = nullptr);
    ~CPhoneApplication();

    /***********************************************************//**
     * @category    METHODS
     ***********************************************************/
    void onCreated(QQuickItem* rootObject) override;
    void loadScreen(QString qmlFilePath) override;
    void raiseSMEvent(const QString& name, const QVariant& data) override;
    Q_INVOKABLE void qmlLog(QString strLog) override;

public slots:
    void sltPopupResult(CPopupEnum::EPopupID ePopupId, CPopupEnum::EPopupResult ePopupResult, QString strAdditionalInfo) override;
    /**
     * @brief   sltShowHidePhoneBtVROverlay: Slot to handle whether to show or hide Phone bt VR overlay.
     * @param   bShowPhoneBtVROverLay: Flag which indicate whether to show or hide phone bt VR overlay
     *          TRUE - show phone bt VR overlay, FALSE - hide phone bt VR overlay.
     * @return  void.
     */
    void sltShowHidePhoneBtVROverlay(bool bShowPhoneBtVROverLay);

private:
    /**
     * @brief   This method is responsible for raising events to SM for phone setup.
     * @param   ePhoneSetupIndex - type of bt setup event to be raised.
     * @return	void.
     */
    void raiseSMEventForPhoneSetup(CPhoneEnum::EPhoneSetupItems ePhoneSetupIndex);
    /**
     * @brief   This method is responsible for raising events to SM for phone browse.
     * @param   iPhoneBrowseType - type of bt setup event to be raised.
     * @return	void.
     */
    void raiseSMEventForPhoneBrowse(int iPhoneBrowseType);

    /**
     * @brief Method to connect signals
     * @param void
     * @return void
     */
    void connectSignals();

private:
    /******************************************************//**
     * @category PROPERTIES
     *******************************************************/

    //!Pointer to create instance of CPhoneAdaptor class.
    CPhoneAdaptor*          m_pPhoneAdaptor;
    //!Pointer to create instance of CPhoneSM class.
    CPhoneSM*               m_pPhoneSM;
    //!Pointer to create instance of CPhoneEventHandler class.
    CPhoneEventHandler*     m_pPhoneEventHandler;
};

#endif // CPHONEAPPLICATION_H
