/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CIntrospectionAdaptor.h
* @ingroup      HMIComponent
* @author       Gaurav Garg
* CIntrospectionAdaptor used to communicate with the Resource Layer.
*/

#ifndef CINTROSPECTIONADAPTOR_H
#define CINTROSPECTIONADAPTOR_H

#include <QObject>
#include "logging.h"
#include "ResourceFactory.hpp"
#include "IntrospectionStubResource/CIntrospectionStubResource.h"
#include "HMIIncludes.h"
#include <CFramework.h>

class CFramework;

/**
 * @brief The CIntrospectionAdaptor, an Adaptor for Introspection module,
 * CIntrospectionAdaptor used to communicate with the Resource Layer.
 */
class CIntrospectionAdaptor: public QObject
{
    Q_OBJECT

public:

    /**
     * @brief CIntrospectionAdaptor destructor
     * param void
     * return void
     */
    virtual ~CIntrospectionAdaptor();

    /**
     * @brief getInstance, provides the instance of the Introspection adaptor
     * @param void
     * @return CIntrospectionAdaptor, Introspection adaptor object
     */
    static CIntrospectionAdaptor* getInstance();

    /**
     * @brief   invExtractFileName Method to get the fileName from the path
     * @param   strFilePath - file path name
     * @return  file name
     */
    Q_INVOKABLE QString invExtractFileName(QString strFilePath);

    /**
     * @brief   invSetScreenChanged Method to get the screen change information.
     * @param   screenName - changed screen Name.
     * @return  void
     */
    Q_INVOKABLE void invSetScreenChanged(QString strScreenName);

    /**
     * @brief   invSetDrawerChanged Method to get the drawer screen change information.
     * @param   screenName - changed screen Name.
     * @return  void
     */
    Q_INVOKABLE void invSetDrawerChanged(QString strScreenName);

    /**
     * @brief   invSetPopupChanged Method to get the popup screen change information.
     * @param   screenName - changed screen Name.
     * @return  void
     */
    Q_INVOKABLE void invSetPopupChanged(QString strScreenName);

    /**
     * @brief   invSetOverlayChanged Method to get the overlay screen change information.
     * @param   screenName - changed screen Name.
     * @return  void
     */
    Q_INVOKABLE void invSetOverlayChanged(QString strScreenName);

    /**
     * @brief   getIntrospectionData Method to get the screen information.
     * @param   iItemType The type of item - screen, drawer, popup
     * @param itemName The name of item that needs to be inspected
     * @return  void
     */
    void getIntrospectionData(int iItemType, QString itemName);

private:

    /**
     * @brief CIntrospectionAdaptor constructor
     * @param QObject type pointer pointing to parent class object
     * @return void
     */
    explicit CIntrospectionAdaptor(QObject* pParent = nullptr);

    /*!
     * @brief m_pIntroMainInstance Singleton Instance pointer for CIntrospectionAdaptor
     */
    static CIntrospectionAdaptor* m_pIntroMainInstance;

    /**
     * @brief fetchItemInfo Method to print the data of Inspect screen
     * param strTopScreen name of the screen to be inspected
     * param pItem Item object to be inspected
     * return string having inspection data
     */
    QString fetchItemInfo(const QString& strTopScreen, QQuickItem *pItem);

    /**
     * @brief fetchItemInfoForPopup Method to print the data of Inspect screen for popup
     * param strTopScreen name of the screen to be inspected
     * param pItem Item object to be inspected
     * return string having inspection data
     */
    QString fetchItemInfoForPopup(const QString& strTopScreen, QObject *pItem);

    /** Reference to the Framework */
    CFramework&  mfw;

    /**
     * @brief m_strScreenName:screen name of the top most screen
     */
    QString m_strScreenName;

    /**
     * @brief m_strDrawerScreenName:screen name of the top most drawer
     */
    QString m_strDrawerScreenName;

    /**
     * @brief m_strPopupScreenName:screen name of the top most popup
     */
    QString m_strPopupScreenName;

    /**
     * @brief m_strOverlayScreenName:screen name of the top most and recently updated overlay
     */
    QString m_strOverlayScreenName;

    /**
     * @brief m_iObjectIndex: marks the index of objects in introspection data
     */
    int m_iObjectIndex;

    /**
     * @brief m_iObjectIndexPopup: marks the index of objects in introspection data for popup
     */
    int m_iObjectIndexPopup;
};

#endif // CINTROSPECTIONADAPTOR_H
