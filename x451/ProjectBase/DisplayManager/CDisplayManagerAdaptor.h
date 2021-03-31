/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CDisplayManagerAdaptor.h
 * @ingroup       HMIComponent
 * @author        Vishal Chaudhary
 * @brief         This file contains CDisplayManagerAdaptor class that stores
 *                all the data needed by QMl screens or other adaptor module.
 *                It also communicates with QML and Display Manager resource
 *                layer.
 */

#ifndef CDISPLAYMANAGERADAPTOR_H
#define CDISPLAYMANAGERADAPTOR_H

#include <QObject>
#include <QString>
#include "CFramework.h"

//! @category FORWARD DECLERATIONS
class CDisplayManagerResourceImpl;
class CDisplayManagerEventHandler;

/*!
 * @class CDisplayManagerAdaptor
 * @brief This is a singletone class that stores all the data needed by QMl
 *        screens or other adaptor module. It also communicates with QML and
 *        DisplayManager resource layer.
 */
class CDisplayManagerAdaptor: public QObject
{
    Q_OBJECT

    /**
      * @brief Property for DisplayFeature ON/OFF status.
      */
    Q_PROPERTY(bool displayOnOffFeatureStatus READ displayOnOffFeatureStatus NOTIFY sigDisplayOnOffFeatureStatusChanged)

    /**
      * @brief Property for nightModeStatus ON/OFF.
      */
    Q_PROPERTY(bool nightModeStatus READ nightModeStatus NOTIFY sigNightModeStatusChanged)

    /**
      * @brief Property for brightNessLevel.
      */
    Q_PROPERTY(short brightNessLevel READ brightNessLevel NOTIFY sigBrightnessLevelChanged)

    /**
      * @brief Property for Button Panel brightNessLevel.
      */
    Q_PROPERTY(short buttonPanelBrightnessLevel READ buttonPanelBrightnessLevel NOTIFY sigButtonPanelBrightnessLevelChanged)

public:
    ~CDisplayManagerAdaptor();

    /************************************************************************//**
     * @category    METHODS
     ************************************************************************/

    /*!
     * @brief   Method to create and get singleton instance of
     *          CDisplayManagerAdaptor class.
     * @param   void.
     * @return  pointer to the object of CDisplayManagerAdaptor class.
     */
    static CDisplayManagerAdaptor *getInstance();

    /**
     * @brief setBrightnessLevelRespRecv: Method to set the response of
     *        setDisplayBrightnessLevelAsyncReq() function. The value is used
     *        for debounce logic, When user made changes using slider, the
     *        resouce's api must only be called, if previous request resonsed
     *        recieved.
     */
    void setBrightnessLevelRespRecv();

    /**
     * @brief setButtonPanelBrightnessLevelRespRecv: Method to set the response of
     *        setButtonPanelBrightnessLevelAsyncReq() function. The value is used
     *        for debounce logic, When user made changes using slider, the
     *        resouce's api must only be called, if previous request resonsed
     *        recieved.
     * @param void.
     * @return void.
     */
    void setButtonPanelBrightnessLevelRespRecv();

    /*!
     * @brief   Method to set display status.
     * @param   bDisplayStatus - Display status.
     * @return  void.
     */
    void setBrightnessLevel(const short iBrightnessLevel);


    /*!
     * @brief   Method to set Button Panel Brightness level.
     * @param   iBrightnessLevel - ButtonPanel Brightness level.
     * @return  void.
     */
    void setButtonPanelBrightnessLevel(const short iBrightnessLevel);

    /*!
     * @brief   Method to set display status.
     * @param   bDisplayOnOffFeatureStatus - DisplayOnOff feature status,
     *          true if ON, else false.
     * @return  void.
     */
    void setDisplayOnOffFeatureStatus(const bool bDisplayOnOffFeatureStatus);

    /*!
     * @brief   Method to set NightMode status.
     * @param   bNightModeStatus - 0 - disbled, 1 - enabled.
     * @return  void.
     */
    void setNightModeStatus(const bool bNightModeStatus);

    /************************************************************************//**
     * @category    GETTERS
     ************************************************************************/


    /************************************************************************//**
     * @category    PROPERTY RELATED GETTERS
     ************************************************************************/

    /**
     * @brief displayOnOffFeatureStatus: Method to get the display status. This is a getter
     * method for displayOnOffFeatureStatus property.
     * @return Display status: true if ON else false.
     */
    bool displayOnOffFeatureStatus() const { return m_bDisplayOnOffFeatureStatus; }

    /**
     * @brief nightModeStatus: Method to get the dayNightMode status.
     *        This is a getter method for nightModeStatus property.
     * @return Display status: true if ON else false.
     */
    bool nightModeStatus() const { return m_bNightModeStatus; }

    /**
     * @brief brightNessLevel: Method to get the display status. This is a
     *        getter method for brightNessLevel property.
     * @return BrightnessLevel.
     */
    short brightNessLevel() const { return m_iBrightnessLevel; }

    /**
     * @brief buttonPanelBrightnessLevel: Method to get the button panel brightness level . This is a
     *        getter method for buttonPanelBrightnessLevel property.
     * @param void.
     * @return BrightnessLevel.
     */
    short buttonPanelBrightnessLevel() const { return m_iButtonPanelBrightnessLevel; }

    /************************************************************************//**
     * @category    RESOURCE LAYER METHODS
     * @brief       API's can be called directly from QML or from other
     *              Adaptor's
     ************************************************************************/

    /*!
     * @brief   Method to inform display manager resource to ON/OFF display.
     * @param   bDisplayOnOffFeatureStatus - Value can be true(ON) or false(OFF).
     * @return  void.
     */
    Q_INVOKABLE void reqDisplayOnOffFeature(bool bDisplayOnOffFeatureStatus);

    /*!
     * @brief   Method to call display manager resource's functon to set
     *          BrightnessLavel.
     * @param   iBrightnessLevel: Brightness level.
     * @param   bIsReleased: This is used to check that
     *          the slider's handle is released or not. HMI has to implement
     *          debounce logic, If slider is continuously changing, and HMI has
     *          to set the last value when user release the slider's handle.
     * @return  void.
     */
    Q_INVOKABLE void reqDisplayBrightnessLevel(short iBrightnessLevel, bool bIsReleased);

    /*!
     * @brief   Method to call button panel manager resource's functon to set
     *          BrightnessLavel.
     * @param   iBrightnessLevel: Brightness level.
     * @param   bIsReleased: This is used to check that
     *          the slider's handle is released or not. HMI has to implement
     *          debounce logic, If slider is continuously changing, and HMI has
     *          to set the last value when user release the slider's handle.
     * @return  void.
     */
    Q_INVOKABLE void reqButtonPanelBrightnessLevel(short iBrightnessLevel, bool bIsReleased);

signals:
    /************************************************************************//**
     * @category    PROPERTY RELATED SIGNALS
     ************************************************************************/

    /**
     * @brief sigDisplayOnOffFeatureStatusChanged: Notify signal for displayOnOffFeatureStatus property.
     */
    void sigDisplayOnOffFeatureStatusChanged();

    /**
     * @brief sigNightModeStatusChanged: Notify signal for nightModeStatus
     *        property.
     */
    void sigNightModeStatusChanged();

    /**
     * @brief sigBrightnessLevelChanged: Notify signal for brightNessLevel
     *        ♂property.
     */
    void sigBrightnessLevelChanged();

    /**
     * @brief sigButtonPanelBrightnessLevelChanged: Notify signal for buttonPanelBrightnessLevel
     *        property.
     */
    void sigButtonPanelBrightnessLevelChanged();


private:
    explicit CDisplayManagerAdaptor(QObject *pParent = nullptr);

    /**
     * @brief   isDisplayNeedstoBeOn: This function is used to know that Display
     *          must be on or not. Basically this function return true if HMI is in
     *          any such state, in which Display must be in ON state.
     * @param   void.
     * @return  true if display must be ON else false.
     */
    bool isDisplayNeedstoBeOn();

private slots:
    /**
     * @brief   sltReverseGearStatusChanged: This is the slot function which is called,
     *          When PDC/RVC state is cheanged. It checks the status of PDC/RVC, if it is
     *          enagaged, It calls DisplayManager function to ON the display.
     * @param   void.
     * @return  void.
     */
    void sltReverseGearStatusChanged();

private:

    /******************************************************//**
     * @category PROPERTIES
     *******************************************************/

    /**
     * @brief m_pDisplayManagerAdaptor: Pointer of CDisplayManagerAdaptor class
     *        for creating singleton instance.
     */
    static CDisplayManagerAdaptor*                   m_pDisplayManagerAdaptor;

    /**
     * @brief m_pDisplayManagerResource: Pointer of
     * CDisplayManagerManagerResourceImpl class to communicate with
     * display manager resource layer.
     */
    CDisplayManagerResourceImpl*    m_pDisplayManagerResource;

    /**
     * @brief m_pDisplayManagerEventHandler: Pointer of
     *        CDisplayManagerEventHandler.
     */
    CDisplayManagerEventHandler *m_pDisplayManagerEventHandler;

    /**
     * @brief m_bDisplayOnOffFeatureStatus: Variable to hold the status of
     *        Display ONOff feature  (true(ON))/ (false(OFF))
     */
    bool m_bDisplayOnOffFeatureStatus;

    /**
     * @brief m_bNightModeStatus: Variable to hold the status of DayNight
     *        Mode
     *        (true(ON))/ (false(OFF))
     */
    bool m_bNightModeStatus;

    /**
     * @brief m_iBrightnessLevel: Variable to hold the brightNess level.
     */
    short m_iBrightnessLevel;

    /**
     * @brief m_iButtonPanelBrightnessLevel: Variable to hold the Button panel brightNess level.
     */
    short m_iButtonPanelBrightnessLevel;

    /**
     * @brief m_bIsBrightnessLevelRespRecv: Variable to hold the status of
     *        brightNess level response recieved or not. When HMI calls
     *        resources api to set brightness level, the HMI restricts
     *        next change till the previous request response recieved.
     */
    bool m_bIsBrightnessLevelRespRecv;

    /**
     * @brief m_bIsButtonPanelBrightnessLevelRespRecv: Variable to hold the status of
     *        button panel brightNess level response recieved or not. When HMI calls
     *        resources api to set brightness level, the HMI restricts
     *        next change till the previous request response recieved.
     */
    bool m_bIsButtonPanelBrightnessLevelRespRecv;
};

#endif // CDISPLAYMANAGERADAPTOR_H
