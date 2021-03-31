/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CScreen.h
* @ingroup      HMI Framework
* @author       Mohit Rajani
* @brief The Screen class used as a storage container for the qml component and corresponding object
*/

#ifndef CSCREEN_H
#define CSCREEN_H

#include <QObject>
#include <QQmlComponent>
#include <QQuickItem>

/**
 * @brief The Screen class used as a storage container for the qml component and corresponding object
 */

class CScreen: QObject
{
public:
    CScreen();
    ~CScreen();
    CScreen(const QString url, QQmlComponent* component = nullptr, QQuickItem* object = nullptr);

    /**
     * @brief url - provides te qml file url path
     * @param - void
     * @return - qml file url path
     */
    QString url();

    /**
     * @brief screenName provide the screen for the particular screen obejct
     * @param - void
     * @return screen name
     */
    QString& screenName();

    /**
     * @brief component - provides te qml component for the provide qml file
     * @param - void
     * @return - qml component
     */
    QQmlComponent* component();

    /**
     * @brief object - provides te qml object for the corresponding qml component
     * @param - void
     * @return - qml object
     */
    QQuickItem* object();

private:
    /** Stores the url path of the qml file */
    const QString m_strUrl;

    /** Stores the screen name for the given url path */
    QString m_strScreenName;

    /** Stores the qml component of the provided qml file */
    QQmlComponent* m_pComponent;

    /** Stores the qml object of the corresponding qml component */
    QQuickItem* m_pQmlObject;
};

#endif // SCREEN_H
