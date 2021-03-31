/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CPopupPropertyHandler.h
* @ingroup      HMIComponent
* @author       Rahul Madan
* CPopupPropertyHandler Class definition which shall contain all the basic info
*                       about all the popups with their properties
*                       and create a map with Popup Ids as keys and Properties as value
*/

#ifndef CPOPUPPROPERTYHANDLER_H
#define CPOPUPPROPERTYHANDLER_H

#include <QObject>
#include <QMap>
#include <QVector>
#include "logging.h"
#include "CPopupEnum.h"

/**
 * @class CPopupPropertyHandler
 * @brief Class definition which shall contain all the basic info
 *        about all the popups with their properties
 *        and create a map with Popup Ids as keys and Properties as value
 */
class CPopupPropertyHandler : public QObject
{
    Q_OBJECT

public:
    /**
    * A class which acts as a container for all the common properties of a popup
    */
    class CPopupProperties{
    public:
        CPopupEnum::EPopupID m_eId;         //Enum value of the ID of Popup
        QString  m_sQmlFilePath;            //QML file path for respective popup
        CPopupEnum::EPopupPriority m_ePriority;  //Priority of the Popup
        bool m_bCloseOnTouch;               //Boolean value which decides whether to close popup on touch
        bool m_bCloseOnHK;                  //Boolean value which decides whether to close on hard Key Press
        bool m_bCloseOnSupersede;           //Boolean value which decides whether to close on Supersede
        bool m_bEnqueue;                    //Boolean value which decides whether popup should be enqueued or not
        CPopupEnum::EPopupZone m_ePopupZone;  // Popup display zone for respective popup
        int  m_iMinTimeout;                 // Integer value of Minimum Timeout of the Popup
        int  m_iMaxTimeout;                 // Integer value of Maximum Timeout of the Popup
        bool m_bResetPopupTimer;            //Boolean value which decides whether to reset popup timer or not on show popup call.
        QVector<CPopupEnum::EPopupApplicableContext>  m_vecApplicableContext; //Array of all states(context) in which the popup can be displayed
    public:
        /**
         * Default constructor initializing all the default values of properties
         */
        CPopupProperties();


        //Todo[RM] : QString parameter(sQmlFilePath) in below method should be const reference
        /**
         * @brief CPopupProperties
         * @param eId
         * @param sQmlFilePath
         * @param ePriority
         * @param ePopupZone
         * @param bCloseOnHK
         * @param bCloseOnSupersede
         * @param bCloseOnTouch
         * @param bEnqueue
         * @param iMinTimeout
         * @param iMaxTimeout
         * @param vecApplicableContext
         * @param bResetPopupTimer
         */
        CPopupProperties(CPopupEnum::EPopupID eId, const QString &sQmlFilePath, CPopupEnum::EPopupPriority ePriority, CPopupEnum::EPopupZone ePopupZone, bool bCloseOnSupersede, bool bCloseOnTouch, bool bCloseOnHK, int iMinTimeout, int iMaxTimeout, const QVector<CPopupEnum::EPopupApplicableContext> &vecApplicableContext, bool bEnqueue, bool bResetPopupTimer);
        /**
         * @brief Method to reset the values of all the properties to default
         * @param void
         * @return void
         */
        void reset();

        //Todo[RM] : QString parameter(sQmlFilePath) in below method should be const reference
        //TODO: Will be implementing for all the properties in future changes
        //ToDo: need make minTimeOut default as 2sec
        /**
         * @brief Method to set the Popup Properties to the values passed as arguments
         * @param CPopupEnum::EPopupID eId : CPopupEnum::EN_POPUPID_UNKNOWN - Enum value of the ID of the Popup
         * @param QString sQmlFilePath : "" - Path to the QML file of the Popup
         * @param CPopupEnum::EPopupPriority ePriority : CPopupEnum::EN_POPUP_PRIORITY_NONE - Priority of the popup
         * @param CPopupEnum::EPopupZone ePopupZone : false - Popup display zone
         * @param bool bCloseOnHK : false - close on HK property for popup
         * @param bool bCloseOnSupersede : false - close on supersede property for popup
         * @param bCloseOnTouch : false - close on touch property for popup
         * @param bool bEnqueue : false - enqueue property for popup
         * @param int iMinTimeout : 0 - popup min timeout
         * @param int iMaxTimeout : 0 - popup max timeout
         * @param QVector<CPopupEnum::EPopupApplicableContext> vecApplicableContext : m_vecCommonContext - applicable context for popup
         * @param bool bResetPopupTimer : Boolean value which decides whether to reset popup timer or not on show popup call.
         * @return void
         */
        void setProperties(CPopupEnum::EPopupID eId, const QString &sQmlFilePath, CPopupEnum::EPopupPriority ePriority, CPopupEnum::EPopupZone ePopupZone,bool bCloseOnSupersede, bool bCloseOnTouch, bool bCloseOnHK, int iMinTimeout, int iMaxTimeout, const QVector<CPopupEnum::EPopupApplicableContext> &vecApplicableContext = m_vecCommonContext, bool bEnqueue = false, bool bResetPopupTimer = false);

        /**
         * @brief Overlaoding operator == for Class CPopupProperties
         * @param CPopupProperties
         * @return bool
         */
        bool operator == (const CPopupProperties &rhs)
        {
            return (rhs.m_eId == m_eId);
        }

        /**
         * @brief m_vecCommonContext Array of States - Home,Media,Setup,Tuner,Phone,Engg. Menu,MediaOff,VR help, VR picklist
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecCommonContext;

        /**
         * @brief m_vecCommonContextWithCall Array of States - Home,Media,Setup,Tuner,Phone,Engg. Menu,MediaOff,VR help, VR picklist,Call
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecCommonContextWithCall;

        /**
         * @brief m_vecVRContext Array of States - Home,Media,Setup,Tuner,Phone,Engg. Menu,VR help
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecVRContext;

        /**
         * @brief m_vecDisplayOffPopupContext Array of States - Home,Media,Setup,Tuner,Phone,Engg. Menu
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecDisplayOffPopupContext;

        /**
         * @brief m_vecIncomingCallPopupContext Array of States - Context for incoming call popup
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecIncomingCallPopupContext;

        /**
         * @brief m_vecHomeContext Array of States - Home
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecHomeContext;

        /**
         * @brief m_vecSetupContext Array of States - Setup
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecSetupContext;

        /**
         * @brief m_vecTunerContext Array of States - Tuner
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecTunerContext;

        /**
         * @brief m_vecMediaContext Array of States - Media
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecMediaContext;

        /**
         * @brief m_vecPhoneContext Array of States - Phone
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecPhoneContext;

        /**
         * @brief m_vecPhoneCallContext Array of States - Phone call
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecPhoneCallContext;

        /**
         * @brief m_vecMediaOffContext Array of States - MediaOff
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecMediaOffContext;

        /**
         * @brief m_vecSoftwareUpdateContext Array of States - software update
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecSoftwareUpdateContext;

        /**
         * @brief m_vecEnggMenuContext Array of States - Engg. Menu
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecEnggMenuContext;

        /**
         * @brief m_vecSetupAndHomeContext Array of States - home and setup
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecSetupAndHomeContext;

        /**
         * @brief m_vecPDCRVCContext Array of States - PDC + RVC
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecPDCRVCContext;

        /**
         * @brief m_vecInvalidContext Context in which popup should not get displayed(SAL, Early wakeup, Startup Animation)
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecInvalidContext;

        /**
         * @brief m_vecVoiceAlertPopupContext vector of Contexts in which voice Alert popup should get displayed.
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecVoiceAlertPopupContext;

        /**
         * @brief m_vecDriveNextContext Array of States - DriveNext
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecDriveNextContext;

        /**
         * @brief m_vecDriveNextSetupContext Array of States - DriveNext Setup
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecDriveNextSetupContext;

        /**
         * @brief m_vecPhoneSetupContext Array of States - Phone Setup.
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecPhoneSetupContext;

        /**
         * @brief m_vecW3WContext Array of States - W3W.
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecW3WContext;

        /**
         * @brief m_vecDoodleStickerContext Array of States - Doodle Sticker.
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecDoodleStickerContext;

        /**
         * @brief m_vecDoodleSetupContext Array of States - Doodle Setup.
         */
        static const QVector<CPopupEnum::EPopupApplicableContext> m_vecDoodleSetupContext;

    };
    virtual ~CPopupPropertyHandler();
    /**
     * @brief Method to get m_mapPopupGroup
     * @param void
     * @return QMap<int, CPopupProperties>
     */
    QMap<int, CPopupProperties> getPopupMap();

    CPopupPropertyHandler();
private:
    /**
     * @brief Method to create a map of all the popups with their basic properties
     * @param void
     * @return void
     */
    void createPopupPropertyMap();

    // todo[RM] : Second parameter in below method should be const reference

    /**
     * @brief Method called from createPopupPropertyMap with popup proerties as arguments which are stored in the map
     * @param CPopupEnum::ePopupID eID   Enum value of the ID of the Popup
     * @param CPopupProperties pProp Object of CPopupProperties containing properties related to popup with id(eID)
     * @return void
     */
    void fillPopupInfo(CPopupEnum::EPopupID eID, CPopupProperties pProp);
private:

    /**
     * @brief m_mapPopupGroup Map to store all the popup properties(Value) against their Popup IDs(key)
     */
    QMap<int, CPopupProperties> m_mapPopupGroup;

};

#endif // CPOPUPPROPERTYHANDLER_H
