/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CVREnum.h
* @ingroup      HMIComponent
* @author       Rahul Singh Parihar
* This file is having the definition for Enum class of VR,
* This declares all the enums related to VR and register all enums to
* qt meta system to use in qml.
*/

#ifndef CVRENUM_H
#define CVRENUM_H

#include <QObject>
#include <QtQml>

/**
 * @class CVREnum
 * @brief The CVREnum class declares all the enums related to
 *        VR and register all enums to qt meta system to use in qml.
 */
class CVREnum: public QObject
{
    Q_OBJECT

public:

    /**
     * @brief The eResponseType enum for the type of the response to be sent for a method
     * request.
     */
    enum EResponseType
    {
        EN_RESPONSE_TYPE_SUCCESS,
        EN_RESPONSE_TYPE_FAILURE,
        EN_RESPONSE_TYPE_PROJECTION_MODE,
        EN_RESPONSE_TYPE_INVALID
    };
    Q_ENUM(EResponseType)

    /**
     * @brief The EVRState enum for the VR current state.
     */
    enum EVRState
    {
        EN_VR_STATE_INIT_BEGIN = 0,
        EN_VR_STATE_STANDBY,
        EN_VR_STATE_PROMPTING,
        EN_VR_STATE_LISTENING,
        EN_VR_STATE_ACCEPTING,
        EN_VR_STATE_PROCESSING,
        EN_VR_STATE_RECO_SUCCESS,
        EN_VR_STATE_RECO_FAILED,
        EN_VR_STATE_G2P_BEGIN,
        EN_VR_STATE_G2P_END,
        EN_VR_STATE_RECO_SUCCESS_BACKGROUND,
        EN_VR_STATE_INIT_END,
        EN_VR_STATE_SESSION_BEGIN,
        EN_VR_STATE_SESSION_END,
        EN_VR_STATE_LANGUAGE_LOAD_BEGIN,
        EN_VR_STATE_LANGUAGE_LOAD_END,
        EN_VR_STATE_LANGUAGE_WAITING_BEGIN,
        EN_VR_STATE_LANGUAGE_WAITING_END,
        EN_VR_STATE_TTS_LANGUAGE_LOAD_BEGIN,
        EN_VR_STATE_TTS_LANGUAGE_LOAD_END,
        EN_VR_STATE_TTS_LANGUAGE_WAITING_BEGIN,
        EN_VR_STATE_TTS_LANGUAGE_WAITING_END,
        EN_VR_STATE_NONE,
        EN_VR_STATE_INVALID
    };
    Q_ENUM(EVRState)

    /**
     * @brief The EVRDialogState enum for the VR current dialog state.
     */
    enum EVRDialogState
    {
        EN_VR_DIALOG_STATE_INACTIVE,
        EN_VR_DIALOG_STATE_ACTIVE
    };

    /**
     * @brief The EVRHelpCategoryType enum for the VR help category type.
     */
    enum EVRHelpCategoryType
    {
        EN_VR_MAIN_CATEGORY,
        EN_VR_PHONE_CATEGORY,
        EN_VR_MEDIA_CATEGORY,
        EN_VR_RADIO_CATEGORY,
        EN_VR_CLIMATE_CATEGORY
    };

    /**
     * @brief The EVRRequestState enum for different request state invoked
     */
    enum EVRRequestState
    {
        EN_NO_REQUEST,
        EN_REQUEST_SET_SCREEN,
        EN_REQUEST_SHOW_TELEPROMPTER_LIST,
        EN_REQUEST_SHOW_PICK_LIST,
        EN_REQUEST_HIDE_PICK_LIST,
        EN_REQUEST_SET_FOCUSED_ITEM,
        EN_REQUEST_SHOW_MEDIA_FILTER_LIST,
        EN_REQUEST_SHOW_CONTACT,
        EN_REQUEST_FOCUS_SELECTED_CATEGORY,
        EN_REQUEST_MEDIA_FILTER_LIST_SHOW,
    };

    /**
     * @brief registerVREnumsToQML: function to register enums to QML.
     */
    static void registerVREnumsToQML()
    {
        qmlRegisterType<CVREnum>("com.harman.qml.vrenum", 1, 0, "VREnum");
    }
};

Q_DECLARE_METATYPE(CVREnum::EResponseType)
Q_DECLARE_METATYPE(CVREnum::EVRState)
Q_DECLARE_METATYPE(CVREnum::EVRHelpCategoryType)
Q_DECLARE_METATYPE(CVREnum::EVRRequestState)

#endif // CVRENUM_H
