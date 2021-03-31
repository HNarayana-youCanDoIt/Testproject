/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CFramework.h
* @ingroup      HMI Framework
* @author       Mohit Rajani
* @brief Class provides a way to register context properties, start/restart screen timers. Create and handle the qml screen components
*/

#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <QQuickItem>
#include <QQmlApplicationEngine>
#include <CScreen.h>
#include <QObject>
#include <QTimer>
#include <QStack>

/**
 * @struct SScreenData
 * @brief Structure to hold the data for screen history stack.
 *        It will store the screen's name and it's top Index
 */
struct SScreenData{
    //Screen Name
    QString m_strScreenName;

    //Index of Item to be displayed on top(in case of a list)
    int m_iTopIndex;

    SScreenData()
    {
        m_strScreenName = "";
        m_iTopIndex = -1;
    }
};
/**
 * @brief Class provides a way to register context properties, start/restart screen timers. Create and handle the qml screen components
 */
class CFramework: public QObject
{
    Q_OBJECT
public :
    static CFramework& getFramework();
    ~CFramework();
    /**
     * @brief getQMLScreen - creates a QML object of the provided qml file
     * @param strQmlurl - Path of the qml.
     * @param pParent - Pointer to the dish root object holding the active dish
     * @return - qml object
     */
    CScreen* getQMLScreen(const QString &strQmlurl, QQuickItem* pParent);

    /**
     * @brief setContextProperty - To pass the cpp object or current module to qml.
     * @param strName - name of the object to be used in qml file
     *        for e.g. cppHomeAA, cppTunerApp etc.
     * @param pValue - Pointer of the object to be accessed in qml.
     * @return - void
     */
    void setContextProperty(const QString &strName, QObject *pValue);

    /**
     * @brief setContextProperty - To pass the cpp object or current module to qml.
     * @param name - - name of the object to be used in qml file
     *        for e.g. cppHomeAA, cppTunerApp etc
     * @param value - Pointer of the object to be accessed in qml.
     * @return void
     */
    void setContextProperty(const QString &name, const QVariant & value);

    /**
     * @brief setRootObject - set the root object to show the qml screens.
     * @param pRootObject - Pointer of the root object
     * @return - void
     */
    void setRootObject(QQuickItem* pRootObject);

    /**
     * @brief getRootObject - get the root object to show the qml screens.
     * @param - void
     * @return rootObject - Pointer of the root object
     */
    QQuickItem *getRootObject();

    /**
     * @brief setNotificationRootObject - set the root object to show the notification overlays.
     * @param rootObject - Pointer of the root object for the vol notification window
     * @return void
     */
    void setNotificationRootObject(QQuickItem* pRootObject);

    /**
     * @brief getNotificationRootObject - get the root object to show the notification screens.
     * @param void
     * @return rootObject - Pointer of the Volume notification window root object
     */
    QQuickItem* getNotificationRootObject();

    /**
     * @brief setVoiceAlertRootObject - set the root object to show the voice alert overlays.
     * @param pRootObject - Pointer of the root object for the vol notification window
     * @return void
     */
    void setVoiceAlertRootObject(QQuickItem* pRootObject);

    /**
     * @brief getVoiceAlertRootObject - get the root object to show the voice alert.
     * @param void
     * @return rootObject - Pointer of the voice window root object
     */
    QQuickItem* getVoiceAlertRootObject();

    /**
     * @brief   startScreenTimer: This method shall be invoked only on first time to start the
     *          screen timer when the screen is being loaded.
     * @param   strScreenName for which the timer is to be started
     * @return  void
     */
    void startScreenTimer(const QString &strScreenName);

    /**
     * @brief   startScreenTimer: Method to be invoked by other components(screen/popup)
     *          to start the screen timer. This function can be used to start the timer of
     *          the currently loaded screen.
     * @param   void
     * @return  void
     */
    void startScreenTimer();

    /**
     * @brief restartScreenTimer function to restart the current running timer
     * @param - void
     * @return - void
     */
    void restartScreenTimer();

    /**
     * @brief stopScreenTimer stop the screenTimeout timer
     * @param - void
     * @return - void
     */
    void stopScreenTimer();

    /**
     * @brief eventFilter event filter function to get all the events on the hmi application
     * @param object qt/qml object on which the event is to be filtered
     * @param event event on the application
     * @return returns the event has been consumed or not (true,false)
     */
    bool eventFilter(QObject *pQObject, QEvent *pQEvent);

    /**
     * @brief setBEnableUserInteractionDetection: setter function to set m_bEnableUserInteractionDetection
     * @param bEnableUserInteractionDetection : boolean to set m_bEnableUserInteractionDetection
     * @return void
     */
    void setBEnableUserInteractionDetection(bool bEnableUserInteractionDetection);

    /**
     * @brief monitorUserInteraction function to check the UserInteraction (i.e. Touch/HKs)
     *        currently being used by CarPlay module to check for any userinteraction after
     *        CP getting disconnected. Can also be used for other module if required
     * @param - void
     * @return - void
     */
    void monitorUserInteraction();

    /**
     * @brief addScreenToStack - Method to add the screen(object of SScreenData) to be loaded to the screen history stack
     *        This method is called from loadScreen method in BaseApplication
     * @param strScreenName - string value of screen name
     * @return void
     */
    void addScreenToStack(const QString &strScreenName);

    /**
     * @brief updateTopIndex - Method to update the top index of current screen.
     *        This method is called from GenericList.qml just before new screen is about to be loaded.
     * @param iTopIndex - Index of top item in the current list
     * @return void
     */
    void updateTopIndex(int iTopIndex);

    /**
     * @brief getListTopItemIndex - Method to get the index of item to be displayed on top.
     *        This method is called from GenericList.qml on Component.onCompleted to set the top index of the list
     * @param void
     * @return int - index of item to be loaded on top of the list
     */
    int getListTopItemIndex();

    /**
     * @brief setBackPressedStatus - Method to set the value of m_bIsBackPressed
     * @param bIsBackPressed - bool value that indicates if back button was pressed or not
     * @return void
     */
    void setBackPressedStatus(bool bIsBackPressed);

    /**
     * @brief getIsBackPressed - Method to get current status of m_bIsBackPressed
     * @param void
     * @return bool - current status of m_bIsBackPressed
     */
    bool getIsBackPressed() {return m_bIsBackPressed;}

    /**
     * @brief clearScreenHistoryStack - Method to clear the screen History stack.
     *        This method shall be called from all the exit methods of Main states in SCT
     *        which would make sure the stack contains the screens of current state only.
     * @param void
     * @return void
     */
    void clearScreenHistoryStack();

    /**
     * @brief doBack - Method to raise evBackPressed SCT event.
     * @param void
     * @return void
     */
    void doBack();

signals:

    /**
     * @brief   sigBroadcastUserInteractionDetected: This signal will be emitted when,
     *          m_bEnableUserInteractionDetection is enabled and any User Interaction happens.
     * @param   void.
     * @return  void.
     */
    void sigBroadcastUserInteractionDetected();

    /**
     * @brief sigBeginScreenLoading - This signal will be emitted from method addScreenToStack just before a new screen is added to the stack.
     *        Signal will be propagated to GenericList.qml which would call updateTopIndex method to set the top index of current list.
     * @param void
     * @return void
     */
    void sigBeginScreenLoading();

private slots:

    /**
     * @brief sltScreenTimeout function is called when the screen timer timeout's
     * @param - void
     * @return - void
     */
    void sltScreenTimeout();

private :
    CFramework(QObject *pParent = nullptr);
    CFramework(const CFramework &);
    CFramework& operator=(const CFramework &);

    /** static object of the CFramework class */
    static CFramework*      m_pFramework;

    /** Object of the QML engine used to create QML components and objects */
    QQmlEngine m_objEngine;

    /** stores the rootObject of the QQuickWindow */
    QQuickItem* m_pRootObject;

    /** Map of CScreen. Creates and maintains the url, component and object for a particular QML file */
    QMap<QString, CScreen*> m_mapScreens;

    /** CScreen timeout timer */
    QTimer m_objScreenTimer;

    /** Map of Screen. Creates and maintains the url, component and object for a particular QML file */
    QMap<QString, CScreen*>mScreenList;

    /** stores the volume/hvac overlay notification root Object of the QQuickWindow */
    QQuickItem* m_pNotificationRootObject;

    /** stores the Voice Alert overlay root Object of the QQuickWindow */
    QQuickItem* m_pVoiceAlertRootObject;

    /** store screen name for screen timeout handling*/
    QString m_strScreenName;

    /** boolean member to enable/disable User Interaction Detection (i.e. Touch/HKs) */
    bool m_bEnableUserInteractionDetection;

    /** Object of QStack of type SScreenData that would maintain history of screens*/
    QStack<SScreenData> m_screenHistoryStack;

    /** Flag that indicates if Back button was pressed or not */
    bool m_bIsBackPressed;

};

#endif // FRAMEWORK_H
