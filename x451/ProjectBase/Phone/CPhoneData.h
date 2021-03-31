/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CPhoneData.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CPhoneData class that contain all the structure data that
 * shall be used by phone UI data models.
 */

#ifndef CPHONEDATA_H
#define CPHONEDATA_H

#include <QObject>
#include <QString>
#include "CPhoneEnum.h"
#include "logging.h"

/*!
 * @class CPhoneData
 * @brief This class contains all structure data that shall be used by phone UI data models.
 */
class CPhoneData
{
    //const variable to specify path for default album art to be shown when song does not has any

    /********************************************//**
     * @category CONSTANTS
     ************************************************/
public:
    static const int MAX_DEVICE_PAIRING_COUNT       = 10;
    static const int8_t CONFERENCE_CALL_ID          = 17;
    static const int FAVORITE_CONTACTS_MAX_LIMIT    = 10;
    static const uint32_t SMS_READOUT_NON_MIX_MODE  = 0;
    static const uint32_t SMS_READOUT_MIX_MODE      = 1;

public:
    /*!
     * @struct  SPhoneData
     * @brief   This structure shall hold basic information of the phone data, all other structures
     * whom so ever need the information shall be derived from it.
     */
    struct SPhoneData
    {
        SPhoneData()
            : m_strName(""),
              m_bIsEnabled(true),
              m_bIsChecked(false)
        {

        }
        SPhoneData(const QString& strName, bool bIsEnabled, bool bIsChecked)
            : m_strName(strName),
              m_bIsEnabled(bIsEnabled),
              m_bIsChecked(bIsChecked)
        {}
        //! Data to hold the item name
        QString     m_strName;
        //! Flag to hold enable state of the item
        bool        m_bIsEnabled;
        //! Flag to hold the checked state of the item
        bool        m_bIsChecked;
    };
    /*!
     * @struct  SDeviceInfo
     * @brief   This structure shall hold device information
     */
    struct SDeviceInfo : public SPhoneData
    {
        SDeviceInfo()
            : m_strDeviceBtAddr("")
        {

        }
        //! Data to hold device bt address
        QString m_strDeviceBtAddr;
    };

    /*!
     * @struct  SPairedDeviceInfo
     * @brief   This structure shall hold information of the paired device that needs to be updated
     *          in paired device screen.
     */
    struct SPairedDeviceInfo : public SDeviceInfo
    {
        SPairedDeviceInfo()
            : m_bDeviceConnectionStatus(false),
              m_eItemType(CPhoneEnum::ITEM_TYPE_DEFAULT)
        {

        }
        //! Flag to hold connection status of the device
        bool                    m_bDeviceConnectionStatus;
        //! Data to hold the type of item to be shown
        CPhoneEnum::EItemType   m_eItemType;
    };

    /*!
     * @struct  SPhoneSetupInfo
     * @brief   This structure shall hold information of the phone setup screen
     */
    struct SPhoneSetupInfo : public SPhoneData
    {
        //TODO: Need to debug why param as QString& in constructor was giving compilation issues in linux
        SPhoneSetupInfo(const QString &strName, bool bIsEnabled, bool bIsChecked, CPhoneEnum::EItemType ePhoneSetupItemType,int iItemId = -1, bool bEditBtnVisible = true)
            : SPhoneData(strName, bIsEnabled, bIsChecked),
              m_ePhoneSetupItemType(ePhoneSetupItemType),
              m_iItemId(iItemId),
              m_bEditBtnVisible(bEditBtnVisible)
        {

        }
        //! Data to hold the item type
        CPhoneEnum::EItemType  m_ePhoneSetupItemType;

        //! Used to hold dropdown index value
        int m_iItemId;

        //! Used to hold edit button visibility
        bool m_bEditBtnVisible;
    };

    /*!
     * @struct  SConfParticipantInfo
     * @brief   This structure shall hold information of the conference participant that needs to be updated
     *          in conference participant screen.
     */
    struct SConfParticipantInfo : public SPhoneData
    {
        SConfParticipantInfo()
            : m_iCalldId(-1),
              m_bHangupEnhancedStatus(false)
        {

        }
        //! Data to hold call id of the participant
        int      m_iCalldId;
        //! Flag to hold hangup enhanced feature status
        bool     m_bHangupEnhancedStatus;

        //! Method to clear the stored data
        void clear()
        {
            m_iCalldId                 = -1;
            m_bHangupEnhancedStatus    = false;
        }
    };

    /*!
     * @struct  SContactDetailInfo
     * @brief   This structure shall hold information of the contact detail that needs to be updated
     *          in contact/details/favorite screen.
     */
    struct SContactDetailInfo
    {
        SContactDetailInfo()
            : m_iIndex(-1),
              m_iContactID(-1),
              m_strName(""),
              m_strNumber(""),
              m_iType(-1),
              m_bIsFavorite(false),
              m_iFavIndex(-1)
        {

        }
        //! Data to hold data index
        int m_iIndex;
        //! Data to hold contact id
        int m_iContactID;
        //! Data to hold contact name
        QString m_strName;
        //! Data to hold contact number
        QString m_strNumber;
        //! Data to hold contact type
        int m_iType;
        //! Data to hold contact is favorite or not
        bool m_bIsFavorite;
        //! Data to hold favorite index
        int m_iFavIndex;

        //! Method to clear the stored data
        void clear()
        {
            m_iIndex        = -1;
            m_iContactID    = -1;
            m_strName       = "";
            m_strNumber     = "";
            m_iType         = -1;
            m_bIsFavorite   = false;
            m_iFavIndex     = -1;
        }
    };

    /*!
     * @struct  SCallLogInfo
     * @brief   This structure shall hold information of the call log that needs to be updated
     *          in call logs screen.
     */
    struct SCallLogInfo
    {
        SCallLogInfo()
            : m_iIndex(-1),
              m_strName(""),
              m_strNumber(""),
              m_iCallType(-1),
              m_strTime(""),
              m_strDate("")
        {

        }

        //! Data to hold data index
        int m_iIndex;
        //! Data to hold call name
        QString m_strName;
        //! Data to hold call number
        QString m_strNumber;
        //! Data to hold call type
        int m_iCallType;
        //! Data to hold call time
        QString m_strTime;
        //! Data to hold call date
        QString m_strDate;

        //! Method to clear the stored data
        void clear()
        {
            m_iIndex = -1;
            m_strName = "";
            m_strNumber = "";
            m_iCallType = -1;
            m_strTime = "";
            m_strDate = "";
        }
    };

    /*!
     * @struct  SPhoneTabBarInfo
     * @brief   This structure shall hold information of the phone tab bar information need to be displayed
     *          in phone browse.
     */
    struct SPhoneTabBarInfo : public SPhoneData
    {
        SPhoneTabBarInfo(const QString &strName,
                         const QString &strLeftIcon,
                         const QString &strMidIcon,
                         const QString &strRightIcon,
                         CPhoneEnum::EPhoneBrowseType ePhoneBrowseType)
            : SPhoneData(strName, true, true),
              m_ePhoneBrowseType(ePhoneBrowseType),
              m_strMidIcon(strMidIcon),
              m_strLeftIcon(strLeftIcon),
              m_strRightIcon(strRightIcon)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);
        }

        //! hold browse type of the tab bar item
        CPhoneEnum::EPhoneBrowseType m_ePhoneBrowseType;
        //! list item name gets stored in this var */
        QString m_strMidIcon;
        //! list item type delegate stored in this var */
        QString m_strLeftIcon;
        //! list item type delegate stored in this var */
        QString m_strRightIcon;
    };

};

/*!
 * @class   CCallInfo
 * @brief   This structure shall hold basic call information
 */
class CCallInfo : public QObject
{
    Q_OBJECT
public:
    CCallInfo(QObject *pParent = nullptr)
        : QObject(pParent),
          m_iCallId(-1),
          m_strCallerName(""),
          m_strCallerNumber(""),
          m_strCallDuration(""),
          m_strCallerProfileImage("default"),
          m_eCallerState(CPhoneEnum::CALLER_UNAVAILABLE)
    {

    }

    /************************************************************************//**
     * @category   CONSTANTS
     ************************************************************************/
    const QString DEFAULT_CONTACT_TRANSPARENT_IMAGE_PATH = "qrc:/image/PhoneCall/callScreen/Ph_Gfx_ProfileImage_n/Ph_Gfx_ProfileImage_Transparent_n.png";
    const QString DEFAULT_CONTACT_OVERLAY_IMAGE_PATH     = "qrc:/image/PhoneCall/callScreen/Ph_Gfx_ProfileImage_n/Ph_Gfx_ProfileImage_Overlay_n.png";

    /************************************************************************//**
     * @category   BT CONNECTION RELATED Q_PROPERTY
     ************************************************************************/
    //! property for qml to get updated caller name
    Q_PROPERTY(QString callerName                       READ callerName         NOTIFY sigCallerNameUpdated)
    //! property for qml to get updated caller number
    Q_PROPERTY(QString callerNumber                     READ callerNumber       NOTIFY sigCallerNumberUpdated)
    //! property for qml to get updated call duration
    Q_PROPERTY(QString callDuration                     READ callDuration       NOTIFY sigCallDurationUpdated)
    //! property for qml to get updated caller profile image
    Q_PROPERTY(QString callerProfileImage               READ callerProfileImage NOTIFY sigCallerProfileImageUpdated)
    //! property for qml to get updated caller profile name
    Q_PROPERTY(QString callerProfileName                READ callerProfileName  NOTIFY sigCallerProfileImageUpdated)
    //! property for qml to get updated caller state
    Q_PROPERTY(CPhoneEnum::ECallerState callerState     READ callerState        NOTIFY sigCallerStateUpdated)

    /************************************************************************//**
     * @category    PROPERTY RELATED GETTERS
     ************************************************************************/

    /*!
     * @brief   Method to get the of the caller.
     * @param   void.
     * @return  name of the caller.
     */
    const QString callerName(){ return m_strCallerName; }

    /*!
     * @brief   Method to get the number of the caller.
     * @param   void.
     * @return  phone number of the caller.
     */
    const QString callerNumber(){ return m_strCallerNumber; }

    /*!
     * @brief   Method to get the call dutaion of the call if active.
     * @param   void.
     * @return  call duration of the call if active otherwise linguistic text for call state.
     */
    const QString callDuration()
    {
        QString strCallDurationToDisplay = "";

        switch (callerState())
        {
        case CPhoneEnum::CALLER_ACTIVE:
        {
            strCallDurationToDisplay = m_strCallDuration;
        }
            break;
        case CPhoneEnum::CALLER_INACTIVE:
        {
            //TODO: string id should be added instead of static text.
            strCallDurationToDisplay = tr("Calling...");
        }
            break;
        case CPhoneEnum::CALLER_ON_HOLD:
        {
            //TODO: string id should be added instead of static text.
            strCallDurationToDisplay = tr("On Hold");
        }
            break;
        default:
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, Unhandled callDuration for callerState:%d", __FUNCTION__, callerState());
        }
            break;
        }
        return strCallDurationToDisplay;
    }

    /*!
     * @brief   Method to get the profile image of the caller.
     * @param   void.
     * @return  profile image of the caller.
     */
    const QString callerProfileImage(){ return m_strCallerProfileImage; }

    /*!
     * @brief   callerProfileName: Method to get the profile
     *          name(first letter of firat name and last name) of the caller.
     * @param   void.
     * @return  profile name of the caller.
     */
    const QString callerProfileName(){ return m_strCallerProfileName; }

    /*!
     * @brief   Method to get status whether the caller is active or inactive.
     * @param   void.
     * @return  current state of the caller.
     */
    CPhoneEnum::ECallerState callerState(){ return m_eCallerState; }

signals:
    /************************************************************************//**
     * @category    PROPERTY RELATED SIGNALS
     ************************************************************************/
    /*!
     * @brief   Signal emitted whenever caller name is updated.
     * @param   void.
     * @return  void.
     */
    void sigCallerNameUpdated();

    /*!
     * @brief   Signal emitted whenever caller number is updated.
     * @param   void.
     * @return  void.
     */
    void sigCallerNumberUpdated();

    /*!
     * @brief   Signal emitted whenever call duration is updated.
     * @param   void.
     * @return  void.
     */
    void sigCallDurationUpdated();

    /*!
     * @brief   Signal emitted whenever caller profile image is updated.
     * @param   void.
     * @return  void.
     */
    void sigCallerProfileImageUpdated();

    /*!
     * @brief   Signal emitted whenever caller active state is updated.
     * @param   void.
     * @return  void.
     */
    void sigCallerStateUpdated();

public:

    /************************************************************************//**
     * @category    SETTERS
     ************************************************************************/

    /*!
     * @brief   Method to set caller name.
     * @param   strCallerName - caller name.
     * @return  void.
     */
    void setCallerName(const QString& strCallerName)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: caller name is: %s", __FUNCTION__, strCallerName.toStdString().c_str());
        m_strCallerName = strCallerName;
        emit sigCallerNameUpdated();
    }

    /*!
     * @brief   Method to set caller number.
     * @param   strCallerNumber - caller number.
     * @return  void.
     */
    void setCallerNumber(const QString& strCallerNumber)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: caller number is: %s", __FUNCTION__, strCallerNumber.toStdString().c_str());
        m_strCallerNumber = strCallerNumber;
        emit sigCallerNumberUpdated();
    }

    /*!
     * @brief   Method to set caller profile image.
     * @param   strCallerProfileImage - caller profile image.
     * @param   bShowOverlayImage - flag to check whether to show default overlay or default trasparent image.
     * @param   bIsActiveCallSingle - flag to check whether active call is single or not.
     * @return  void.
     */
    void setCallerProfileImage(const QString& strCallerProfileImage, bool bShowOverlayImage, bool bIsActiveCallSingle)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
        m_strCallerProfileName = "";
        if(bShowOverlayImage)
        {
            m_strCallerProfileImage = DEFAULT_CONTACT_OVERLAY_IMAGE_PATH;
        }
        else
        {
            if(bIsActiveCallSingle)
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, m_strCallerName:%s, strCallerProfileImage:%s", __FUNCTION__, m_strCallerName.toStdString().c_str(), strCallerProfileImage.toStdString().c_str());
                if("" == strCallerProfileImage)
                {
                    if(m_strCallerName != "")
                    {
                        QStringList listCallerName = m_strCallerName.split(" ", QString::SkipEmptyParts);
                        if(!listCallerName.isEmpty())
                        {
                            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: list of caller name is not empty", __FUNCTION__);
                            if(listCallerName.size() > 1)
                            {
                                QChar cFirstName    = QString(listCallerName.first()).at(0);
                                QChar cLastName     = QString(listCallerName.last()).at(0);
                                m_strCallerProfileName  = QString(cFirstName) + QString(cLastName);
                            }
                            else
                            {
                                m_strCallerProfileName = QString(QString(listCallerName.first()).at(0));
                            }
                            m_strCallerProfileName.toUpper();
                            m_strCallerProfileImage = DEFAULT_CONTACT_TRANSPARENT_IMAGE_PATH;
                        }
                        else
                        {
                            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: list of caller name is empty", __FUNCTION__);
                            m_strCallerProfileImage = DEFAULT_CONTACT_OVERLAY_IMAGE_PATH;
                        }
                    }
                    else
                    {
                        m_strCallerProfileImage = DEFAULT_CONTACT_OVERLAY_IMAGE_PATH;
                    }
                }
                else
                {
                #ifdef PLATFORM_WIN32
                    m_strCallerProfileImage = DEFAULT_CONTACT_OVERLAY_IMAGE_PATH;
                #else
                    m_strCallerProfileImage = "file://" + strCallerProfileImage;
                #endif
                }
            }
            else
            {
                m_strCallerProfileImage = DEFAULT_CONTACT_TRANSPARENT_IMAGE_PATH;
            }
        }

        emit sigCallerProfileImageUpdated();
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Caller profile image is: %s, Caller Profile Name is: %s", __FUNCTION__,
                 m_strCallerProfileImage.toStdString().c_str(), m_strCallerProfileName.toStdString().c_str());
    }

    /*!
     * @brief   Method to set call duration.
     * @param   strCallDuration - call duration.
     * @return  void.
     */
    void setCallDuration(const QString& strCallDuration)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
        if(m_strCallDuration.compare(strCallDuration) != 0)
        {
            m_strCallDuration = strCallDuration;
            emit sigCallDurationUpdated();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "call duration not changed");
        }
    }

    /*!
     * @brief   Method to set caller status whether active or inactive.
     * @param   eCallerState - caller current state.
     * @return  void.
     */
    void setCallerState(CPhoneEnum::ECallerState eCallerState)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
        if(m_eCallerState != eCallerState)
        {
            m_eCallerState = eCallerState;
            emit sigCallerStateUpdated();

            ////emit call duration signal as its value need to update as per call state
            emit sigCallDurationUpdated();
        }



        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "call state not changed");
        }
    }

    /*!
     * @brief   Method to clear the stored data.
     * @param   void.
     * @return  void.
     */
    void clear()
    {
        setCallerName("");
        setCallerNumber("");
        setCallDuration("");
        setCallerState(CPhoneEnum::CALLER_UNAVAILABLE);
        setCallId(-1);
        m_strCallerProfileImage = "default";
        m_strCallerProfileName  = "";
        emit sigCallerProfileImageUpdated();
    }

    /*!
     * @brief   Method to get the call id.
     * @param   void.
     * @return  call id.
     */
    Q_INVOKABLE int invGetCallId() { return m_iCallId; }

    /*!
     * @brief   Method to set the call id.
     * @param   iCallId - call id.
     * @return  void.
     */
    void setCallId(int iCallId)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
        m_iCallId = iCallId;
    }

private:
    //! Data to hold the call id of the call
    int                         m_iCallId;
    //! Data to hold caller name
    QString                     m_strCallerName;
    //! Data to hold caller number
    QString                     m_strCallerNumber;
    //! Data to hold call duration of the call
    QString                     m_strCallDuration;
    //! Data to hold profile image of the caller
    QString                     m_strCallerProfileImage;
    //! Data to hold first letter of first and last name
    QString                     m_strCallerProfileName;
    //! Data to hold caller current state
    CPhoneEnum::ECallerState    m_eCallerState;
};

#endif // CPHONEDATA_H
