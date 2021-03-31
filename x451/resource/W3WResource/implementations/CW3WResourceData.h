/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CW3WResourceData.h
 * @ingroup       HMIComponent
 * @author        Mohit Rajani
 * @brief         Contain all the structure data that shall be used by W3W resource implementation classes.
 */

#ifndef CW3WRESOURCEDATA_H
#define CW3WRESOURCEDATA_H

#include <string>

using namespace std;

struct SSuggestion
{
    SSuggestion()
        : m_w3wAddress(""),
          m_languageCode(""),
          m_countryCode(""),
          m_nearestPlace("")
    {
    }
    //! Data to hold w3w address
    string      m_w3wAddress;
    //! Data to hold language code
    string      m_languageCode;
    //! Data to hold country code
    string      m_countryCode;
    //! Data to hold nearest place
    string      m_nearestPlace;

    //! Method to clear the stored data
    void clear()
    {
        m_w3wAddress = "";
        m_languageCode = "";
        m_countryCode = "";
        m_nearestPlace = "";
    }
};

struct SW3WAddressItem
{
    SW3WAddressItem()
        : m_w3wAddress(""),
          m_languageCode(""),
          m_countryCode(""),
          m_nearestPlace(""),
          m_w3wAddressLabel(""),
          m_w3wAddressUID(-1)
    {
    }

    SW3WAddressItem(string w3wAddress, string languageCode, string countryCode,
                    string nearestPlace, string w3wAddressLabel, int w3wAddressUID =- 1)
        : m_w3wAddress(w3wAddress),
          m_languageCode(languageCode),
          m_countryCode(countryCode),
          m_nearestPlace(nearestPlace),
          m_w3wAddressLabel(w3wAddressLabel),
          m_w3wAddressUID(w3wAddressUID)
    {
    }

    //! Data to hold w3w address
    string      m_w3wAddress;
    //! Data to hold language code
    string      m_languageCode;
    //! Data to hold country code
    string      m_countryCode;
    //! Data to hold nearest place
    string      m_nearestPlace;
    //! Data to hold w3w address label
    string      m_w3wAddressLabel;
    //! Data to hold w3w address unique ID
    int         m_w3wAddressUID;

    //! Method to clear the stored data
    void clear()
    {
        m_w3wAddress = "";
        m_languageCode = "";
        m_countryCode = "";
        m_nearestPlace = "";
        m_w3wAddressLabel = "";
        m_w3wAddressUID = -1;
    }
};


#endif // CW3WRESOURCEDATA_H
