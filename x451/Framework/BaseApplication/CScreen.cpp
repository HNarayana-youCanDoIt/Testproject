/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CScreen.cpp
* @ingroup      HMI Framework
* @author       Mohit Rajani
* @brief The Screen class used as a storage container for the qml component and corresponding object
*/

#include "CScreen.h"
#include <QFileInfo>


CScreen::CScreen():
    m_strUrl(""),
    m_pComponent(nullptr),
    m_pQmlObject(nullptr)
{

}

CScreen::~CScreen()
{
    if (nullptr != m_pComponent)
        delete m_pComponent;

    if (nullptr != m_pQmlObject)
        delete m_pQmlObject;
}

CScreen::CScreen(const QString url, QQmlComponent *component, QQuickItem *object):
    m_strUrl(url),
    m_strScreenName(""),
    m_pComponent(component),
    m_pQmlObject(object)
{
    QFileInfo objScreenFileInfo(url);
    m_strScreenName = objScreenFileInfo.fileName();
}

QString CScreen::url()
{
    return m_strUrl;
}

QString &CScreen::screenName()
{
    return m_strScreenName;
}

QQmlComponent* CScreen::component()
{
    return m_pComponent;
}

QQuickItem* CScreen::object()
{
    return m_pQmlObject;
}
