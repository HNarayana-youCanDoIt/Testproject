/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CW3WData.h
 * @ingroup       HMIComponent
 * @author        Nishant Khandagale
 * @brief         This file contains CW3WData class that contain all the structure data that
 * shall be used by W3W UI data models.
 */

#ifndef CW3WDATA_H
#define CW3WDATA_H

#include <QObject>
#include <QString>
#include "CW3WEnum.h"
#include "logging.h"

/*!
 * @class CW3WData
 * @brief This class contains all structure data that shall be used by W3W UI data models.
 */
class CW3WData
{

    /********************************************//**
     * @category CONSTANTS
     ************************************************/

public:


    /*!
     * @struct  SW3WSetupData
     * @brief   This structure shall hold information of the W3W setup screen
     */
    struct SW3WSetupData
    {
        SW3WSetupData()
            : m_strName(""),
              m_bIsEnabled(true),
              m_bIsChecked(false),
              m_eW3WItemType(CW3WEnum::ITEM_TYPE_LABEL),
              m_iItemId(-1)
        {
        }

        SW3WSetupData(const QString &strName, bool bIsEnabled, bool bIsChecked, CW3WEnum::EW3WItemType eW3WItemType,int iItemId = -1)
            : m_strName(strName),
              m_bIsEnabled(bIsEnabled),
              m_bIsChecked(bIsChecked),
              m_eW3WItemType(eW3WItemType),
              m_iItemId(iItemId)
        {
        }

        //! Data to hold the item name
        QString     m_strName;
        //! Flag to hold enable state of the item
        bool        m_bIsEnabled;
        //! Flag to hold the checked state of the item
        bool        m_bIsChecked;
        //! Data to hold the item type
        CW3WEnum::EW3WItemType  m_eW3WItemType;
        //! Used to hold dropdown index value
        int m_iItemId;
    };

    /*!
     * @struct  SW3WAddressSuggestionKeypadData
     * @brief   This structure shall hold information of the W3W Address Suggestion Keypad data
     */
    struct SW3WAddressSuggestionKeypadData
    {
        SW3WAddressSuggestionKeypadData()
            : m_strKeyButtonDefaultImage(""),
              m_strKeyButtonPressedImage(""),
              m_strKeyButtonDisabledImage(""),
              m_cKeyButtonInputChar(-1)
        {
        }

        SW3WAddressSuggestionKeypadData(const QString &strKeyButtonDefaultImage, const QString &strKeyButtonPressedImage, const QString &strKeyButtonDisabledImage,const QChar cKeyButtonInputChar = -1)
            : m_strKeyButtonDefaultImage(strKeyButtonDefaultImage),
              m_strKeyButtonPressedImage(strKeyButtonPressedImage),
              m_strKeyButtonDisabledImage(strKeyButtonDisabledImage),
              m_cKeyButtonInputChar(cKeyButtonInputChar)
        {
        }

        //! String to hold the Default image path for the Key button
        QString     m_strKeyButtonDefaultImage;
        //! String to hold the Pressed image path for the Key button
        QString     m_strKeyButtonPressedImage;
        //! String to hold the Disabled image path for the Key button
        QString     m_strKeyButtonDisabledImage;
        //! Input character for the Key button
        QChar       m_cKeyButtonInputChar;
    };

    /*!
     * @struct  SW3WAddressData
     * @brief   This structure shall hold information of the W3W address data for Auto Suggestion, Favorites and Recent Addresses
     */
    struct SW3WAddressData
    {
        SW3WAddressData()
            : m_W3WAddress(""),
              m_W3WLanguageCode(""),
              m_W3WCountryCode(""),
              m_W3WNearestPlace(""),
              m_W3WAddressLabel(""),
              m_W3WItemType(CW3WEnum::ITEM_TYPE_INVALID),
              m_ItemId(-1)
        {
        }

        SW3WAddressData(const QString &address, const QString &languageCode,
                        const QString &countryCode, const QString &nearestPlace, const QString &addressLabel,
                               CW3WEnum::EW3WItemType itemType,int itemId = -1)
            : m_W3WAddress(address),
              m_W3WLanguageCode(languageCode),
              m_W3WCountryCode(countryCode),
              m_W3WNearestPlace(nearestPlace),
              m_W3WAddressLabel(addressLabel),
              m_W3WItemType(itemType),
              m_ItemId(itemId)
        {
        }

        //! Data to hold the W3W address
        QString     m_W3WAddress;
        //! Data to hold the W3W address language code
        QString     m_W3WLanguageCode;
        //! Data to hold the W3W address country code
        QString     m_W3WCountryCode;
        //! Data to hold the W3W address nearest place
        QString     m_W3WNearestPlace;
        //! Data to hold the W3W address label
        QString     m_W3WAddressLabel;
        //! Data to hold the item type
        CW3WEnum::EW3WItemType  m_W3WItemType;
        //! Used to hold index value
        int m_ItemId;
    };

    /*!
     * @struct  Coordinates
     * @brief   This structure shall hold latitude and longitude coordinates for the W3W address
     */
    struct Coordinates
    {
        Coordinates(): lat(0.0), lng(0.0)
        {
        }

        //! Holds the latitude of the W3W address
        double lat;

        //! Holds the longitude of the W3W address
        double lng;
    };

};

#endif // CW3WDATA_H
