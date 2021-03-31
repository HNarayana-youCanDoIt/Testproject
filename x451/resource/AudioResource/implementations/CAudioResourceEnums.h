/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CAudioResourceEnums.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain all the enums that shall be used by Audio resource data structures
 * or by Audio resource implementation classes. These enums shall also be used by Audio application layer.
 */

#ifndef CAUDIORESOURCEENUMS_H
#define CAUDIORESOURCEENUMS_H

/**
  * @enum   EAudioSourceCategory
  * @brief  This enum shall hold the values supported for audio source category.
  */
enum EAudioSourceCategory
{
    SOURCE_CATEGORY_UNKNOWN = 0,
    SOURCE_CATEGORY_TUNER,
    SOURCE_CATEGORY_MEDIA,
    SOURCE_CATEGORY_AUX,
    SOURCE_CATEGORY_PROJECTION
};

#endif // CAUDIORESOURCEENUMS_H
