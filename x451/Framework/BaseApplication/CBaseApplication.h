/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CBaseApplication.h
* @ingroup      HMI Framework
* @author       Mohit Rajani
* @brief Main base class for all the HMI applications.
*/

#ifndef CBASEAPPLICATION_H
#define CBASEAPPLICATION_H

#include <QObject>
#include <QQuickItem>
#include "CFramework.h"
#include "CPopupEnum.h"

class CFramework;
class CThemeManager;

/**
 * @brief Main base class for all the HMI applications.
 */
class CBaseApplication :   public QObject
{
    Q_OBJECT

public :
    //TODO: This method need to be changed to abstract method for forcefull implementation
    /**
     * @brief qmlLog - Function that can be invoked from the QML world.
     * Enables logging from within the QML files
     * @param strLog - The information that is to be logged with the logging framework
     */
    Q_INVOKABLE virtual void qmlLog(QString strLog);

private :
    CBaseApplication();

public slots:
    /**
     * @brief Slot to be connected to PopupManager's signal sigPopupResult to handle Popup events
     * @param ePopupId - Id of the Popup
     * @param ePopupResult - Result of the Popup(Displayed, Closed or Ignored)
     * @param strAdditionalInfo - Additional info (based on reason on which popup is closed)
     */
    virtual void sltPopupResult(CPopupEnum::EPopupID ePopupId, CPopupEnum::EPopupResult ePopupResult, QString strAdditionalInfo);

public :

    CBaseApplication(QQuickItem* pParent = nullptr);

    /**
     * @brief onCreated - Function is called when the QML is loaded successfully
     * @param rootObject - provides the created qml object as the root Object
     */
    virtual void onCreated(QQuickItem* rootObject) = 0 ;

    /**
     * @brief loadScreen - Function is called to load the provide qml file onto the QQuickWindow
     * @param qmlFilePath - provide qml file path
     */
    virtual void loadScreen(QString qmlFilePath);

    /**
     * @brief loadDrawers - Function is called to load the Drawers qml file
     * @param strQmlFilePath - provide qml file path
     * @return void
     */
    virtual void loadDrawers(const QString &strQmlFilePath);

    /**
     * @brief   loadKeypadOverlay - Function to be invoked to load keypad overlay qml file.
     * @param   strQmlFilePath - overlay file path to be loaded.
     * @return  TRUE - if loadKeypadOverlay method is invoked, FALSE - unable to invoke loadKeypadOverlay method.
     */
    virtual bool loadKeypadOverlay(const QString &strQmlFilePath);

    /**
     * @brief   unloadKeypadOverlay - Function to be invoked to unload the keypad overlay.
     * @param   void.
     * @return  TRUE - if unloadKeypadOverlay method is invoked, FALSE - unable to invoke unloadKeypadOverlay method.
     */
    virtual bool unloadKeypadOverlay();

    /**
     * @brief   loadVROverlay - Function to be invoked to load VR overlay qml file.
     * @param   strQmlFilePath - overlay file path to be loaded.
     * @return  TRUE - if loadVROverlay method is invoked, FALSE - unable to invoke loadVROverlay method.
     */
    virtual bool loadVROverlay(const QString &strQmlFilePath);

    /**
     * @brief   unloadVROverlay - Function to be invoked to unload the VR overlay.
     * @param   void.
     * @return  TRUE - if unloadVROverlay method is invoked, FALSE - unable to invoke unloadVROverlay method.
     */
    virtual bool unloadVROverlay();

    /**
     * @brief loadMainAppScreen - Function is called to load the main UI window screen which houses the other qml
     * screens
     * @param qmlFilePath - provide qml file path
     */
    virtual void loadMainAppScreen(const QString &qmlFilePath);

    /**
     * @brief unloadScreen - Function is called to unload a particular qml
     * @param qmlFilePath - provide qml file path
     */
    virtual void unloadScreen(const QString &qmlFilePath);

	
    /**
     * @brief loadNotificationScreen - Function is called to load the
     *        notification window screen which houses the other notifications screens.
     * @param strQmlFilePath - provide qml file path
     * @return void
     */
    virtual void loadNotificationScreen(const QString &strQmlFilePath);

    /**
     * @brief loadVoiceAlertScreen - Function is called to load the
     *        Voice Alert window screen which houses the other Voice Alert screens.
     * @param strQmlFilePath - provide qml file path
     * @return void
     */
    virtual void loadVoiceAlertScreen(const QString &strQmlFilePath);

    /**
     * @brief raiseSMEvent - Function is called from the QML file to raise an event on the State machine
     * Based on which there might be a screen transition or internal state change
     * @param name - The name of the domain/module
     * @param data - The name of the event/state we want the SM to be transitioned into
     */
    // FixMe: The data can be a QString. No need for it to be a QVariant
    Q_INVOKABLE virtual void raiseSMEvent(const QString & name,const QVariant & data);

    /** Pointer to the parent object for the particular domain/module */
    QQuickItem* mParent;

    /** Reference to the Framework */
    CFramework&  mfw;

    /** Reference to the ThemeManager */
    CThemeManager& mThemeMgr;
};

#endif // CBASEAPPLICATION_H
