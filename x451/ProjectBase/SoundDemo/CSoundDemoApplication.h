/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          SoundDemoApplication.h
 * @ingroup       HMIComponent
 * @author        Guru Alingal
 * @brief         This file contains SoundDemoApplication class that act as a mediator between QML and state machine.
 */


#ifndef SOUNDDEMOAPPLICATION_H
#define SOUNDDEMOAPPLICATION_H

#include <QObject>
#include "HMIIncludes.h"

 /***********************************************************//**
//! @category FORWARD DECLERATIONS
 ***********************************************************/
class CSoundDemoSM;


class CSoundDemoApplication : public CBaseApplication
{
    Q_OBJECT
public:

    /**
     * @brief   SoundDemoApplication: Constructor of SoundDemoApplication.
     * @param   pParent: QObject pointer of parent class.
     * @return  NA.
     */
    explicit CSoundDemoApplication(QQuickItem* pParent = nullptr);

    /**
     * @brief   ~SoundDemoApplication: Destructor of SoundDemoApplication
     * @param   NA.
     * @return  NA.
     */
    ~CSoundDemoApplication();

    /***********************************************************//**
     * @category    METHODS
     ***********************************************************/
    void qmlLog(QString strLog) override;
    void onCreated(QQuickItem* pRootObject) override;
    void loadScreen(QString strQmlFilePath) override;
    void raiseSMEvent(const QString& strName, const QVariant& objData) override;

    /**
     * @brief handleFailSafeScenario: Function to handle fail safe scenario and switch back to home screen.
     * @param void
     * @return void
     */
    void handleFailSafeScenario();

private slots:
    /**
     * @brief sltProcessAutoBack: SLot to handle single shot timer take user back to home
     *        screen on entering sound demo screen in invalid scenarios.
     * @param void
     * @return void
     */
    void sltProcessAutoBack();

private:
    /******************************************************//**
     * @category PROPERTIES
     *******************************************************/

    //! Pointer of SoundDemoSM type pointing to instance of SoundDemoSM class
    CSoundDemoSM*              m_pSoundDemoSM;

    // CBaseApplication interface

};


#endif // SOUNDDEMOAPPLICATION_H
