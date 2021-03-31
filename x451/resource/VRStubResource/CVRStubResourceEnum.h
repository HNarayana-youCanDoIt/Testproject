/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CVRStubResourceEnum.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain all the enums that shall be used by VR stub resource data structures
 * or by VR stub implementation class. These enums shall also be used by VR adaptor layer.
 */

#ifndef CVRSTUBRESOURCEENUM_H
#define CVRSTUBRESOURCEENUM_H

/**
 * @brief The EVRRequestState enum for different request state invoked by the client
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

/**
 * @brief The EVRScreenID enum for screen id which is activating the VR
 */
enum EVRScreenID
{
    EN_SCREEN_DEFAULT   = 0,
    EN_SCREEN_W3W       = 1,
    EN_SCREEN_MAX_COUNT
};

#endif // CVRSTUBRESOURCEENUM_H
