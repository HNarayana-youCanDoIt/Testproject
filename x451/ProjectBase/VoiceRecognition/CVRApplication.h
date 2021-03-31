/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CVRApplication.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CVRApplication class that act as a mediator between QML and state machine.
 * It also load QML files related to VR module.
 */

#ifndef CVRAPPLICATION_H
#define CVRAPPLICATION_H

#include <QObject>
#include "HMIIncludes.h"

//! @category FORWARD DECLERATIONS
class CVRSM;
class CVRAdaptor;
class CVREventHandler;

class CVRApplication : public CBaseApplication
{
    Q_OBJECT
public:

    /**
     * @brief   CVRApplication: Constructor of CVRApplication.
     * @param   pParent: QObject pointer of parent class.
     * @return  NA.
     */
    explicit CVRApplication(QQuickItem* pParent = nullptr);

    /**
     * @brief   ~CVRApplication: Destructor of CVRApplication
     * @param   NA.
     * @return  NA.
     */
    ~CVRApplication();

    /***********************************************************//**
     * @category    METHODS
     ***********************************************************/
    void onCreated(QQuickItem* pRootObject) override;
    void loadScreen(QString strQmlFilePath) override;
    void raiseSMEvent(const QString& strName, const QVariant& objData) override;

public slots:
    /**
     * @brief   sltShowHideVROverlay: Slot to handle whether to show or hide VR overlay.
     * @param   bShowVROverLay: Flag which indicate whether to show or hide VR overlay
     *          TRUE - show VR overlay, FALSE - hide VR overlay.
     * @return  void.
     */
    void sltShowHideVROverlay(bool bShowVROverLay);

private:
    /******************************************************//**
     * @category PROPERTIES
     *******************************************************/
    //! Pointer of CVREventHandler type pointing to instance of CVREventHandler class
    CVREventHandler*    m_pVREventHandler;
    //! Pointer of CVRSM type pointing to instance of CVRSM class
    CVRSM*              m_pVRSm;
};

#endif // CVRAPPLICATION_H
