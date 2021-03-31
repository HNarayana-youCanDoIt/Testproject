/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CW3WAdaptor.h
 * @ingroup         HMIComponent
 * @author          Nishant Khandagale
 * CW3WAdaptor, an Adaptor for W3W module,
 * CW3WAdaptor is class used to communicate with qml, resources of W3W module.
 */

#ifndef CW3WADAPTOR_H
#define CW3WADAPTOR_H

#include <QObject>
#include <QString>
#include "logging.h"
#include "CFramework.h"
#include "CW3WEnum.h"
#include "CW3WSetupListModel.h"
#include "CW3WAboutListModel.h"
#include "CW3WAutoSuggestionListModel.h"
#include "CW3WFavoriteListModel.h"
#include "CW3WRecentListModel.h"
#include "CW3WData.h"
#include "CPopupEnum.h"

//! @category FORWARD DECLERATIONS
class CW3WResourceImpl;

/**
 * @brief CW3WAdaptor, an Adaptor for W3W module,
 * It is class used to communicate with qml, resources of W3W module.
 */
class CW3WAdaptor : public QObject
{
    Q_OBJECT

    // Properties

    // property for qml to get W3W Setup list model
    Q_PROPERTY(QAbstractListModel* w3wSetupListModel    READ w3wSetupListModel  CONSTANT)

    // property for qml to get W3W About list model
    Q_PROPERTY(QAbstractListModel* w3wAboutListModel    READ w3wAboutListModel  CONSTANT)

    // property for qml to get W3W Auto Suggestion list model
    Q_PROPERTY(QAbstractListModel* w3wAutoSuggestionListModel    READ w3wAutoSuggestionListModel  CONSTANT)

    // property for qml to get W3W Favorite list model
    Q_PROPERTY(QAbstractListModel* w3wFavoriteListModel    READ w3wFavoriteListModel  CONSTANT)

    // property for qml to get W3W Recent list model
    Q_PROPERTY(QAbstractListModel* w3wRecentListModel    READ w3wRecentListModel  CONSTANT)

    // property for qml which holds the typed W3W Address input text entered in W3W Address Suggestion screen
    Q_PROPERTY(QString w3wAddressInputText  READ w3wAddressInputText   WRITE setW3WAddressInputText)

    // property for qml which holds whether Auto Suggestion is received or not
    Q_PROPERTY(bool autoSuggestionRecievedStatus  READ autoSuggestionRecievedStatus WRITE setAutoSuggestionRecievedStatus NOTIFY sigAutoSuggestionRecievedStatusChanged)

    // property for qml which holds the selected W3W Address from W3W Address Suggestion / Favorites / Recent screens
    Q_PROPERTY(QString selectedW3WAddress  READ selectedW3WAddress   WRITE setSelectedW3WAddress NOTIFY sigSelectedW3WAddressChanged)

    // property for qml which holds the selected W3W Address Label from W3W Address Suggestion / Favorites / Recent screens
    Q_PROPERTY(QString selectedW3WAddressLabel  READ selectedW3WAddressLabel   WRITE setSelectedW3WAddressLabel NOTIFY sigSelectedW3WAddressLabelChanged)

    // property for qml which holds the selected W3W Address For Favorite
    Q_PROPERTY(QString selectedW3WAddressForFavorite  READ selectedW3WAddressForFavorite   WRITE setSelectedW3WAddressForFavorite NOTIFY sigSelectedW3WAddressForFavoriteChanged)

    // property for qml which holds the selected W3W Address Label For Favorite
    Q_PROPERTY(QString selectedW3WAddressLabelForFavorite  READ selectedW3WAddressLabelForFavorite   WRITE setSelectedW3WAddressLabelForFavorite NOTIFY sigSelectedW3WAddressLabelForFavoriteChanged)

    // property for qml which holds the selected W3W Address For Delete
    Q_PROPERTY(QString selectedW3WAddressForDelete  READ selectedW3WAddressForDelete   WRITE setSelectedW3WAddressForDelete NOTIFY sigSelectedW3WAddressForDeleteChanged)

    // property for qml which holds the selected W3W Address Label For Delete
    Q_PROPERTY(QString selectedW3WAddressLabelForDelete  READ selectedW3WAddressLabelForDelete   WRITE setSelectedW3WAddressLabelForDelete NOTIFY sigSelectedW3WAddressLabelForDeleteChanged)

    // property for qml which holds the last navigated address's latitude
    Q_PROPERTY(double lastNavigatedLatitude  READ lastNavigatedLatitude   WRITE setLastNavigatedLatitude NOTIFY sigLastNavigatedLatitudeChanged)

    // property for qml which holds the last navigated address's longitude
    Q_PROPERTY(double lastNavigatedLongitude  READ lastNavigatedLongitude   WRITE setLastNavigatedLongitude NOTIFY sigLastNavigatedLongitudeChanged)

public:
    /**
    * @brief	CW3WAdaptor::CW3WAdaptor constructor for class CW3WAdaptor.
    * @param	QObject.
    * @return	NA.
    **/
    CW3WAdaptor(QObject *parent = nullptr);

    /**
    * @brief	CW3WAdaptor::~CW3WAdaptor is destructor of class CW3WAdaptor
    * @param	NA.
    * @return	NA.
    **/
    ~CW3WAdaptor();

    /**
     * @brief   w3wFeatureSupportStatus: Method to get whether W3W feature is supported or not
     *          EOL for W3W should be enabled And either Carplay or AA EOL should be enabled.
     * @param   void.
     * @return  TRUE if W3W feature is supported, FALSE otherwise.
     */
    bool w3wFeatureSupportStatus();

    /**
     * @brief   Method to create W3W related Setup List data models.
     * @param   void.
     * @return  void.
     */
    void createW3WSetupListModel();

    /**
     * @brief   Method to delete W3W related Setup List data models.
     * @param   void.
     * @return  void.
     */
    void deleteW3WSetupListModel();

    /**
     * @brief   Method to create W3W related About List data models.
     * @param   void.
     * @return  void.
     */
    void createW3WAboutListModel();

    /**
     * @brief   Method to delete W3W related About List data models.
     * @param   void.
     * @return  void.
     */
    void deleteW3WAboutListModel();

    /**
     * @brief   Method to create W3W related Auto Suggestion List data models.
     * @param   void.
     * @return  void.
     */
    void createW3WAutoSuggestionListModel();

    /**
     * @brief   Method to delete W3W related Auto Suggestion List data models.
     * @param   void.
     * @return  void.
     */
    void deleteW3WAutoSuggestionListModel();

    /**
     * @brief   Method to create W3W related Favorite List data models.
     * @param   void.
     * @return  void.
     */
    void createW3WFavoriteListModel();

    /**
     * @brief   Method to delete W3W related Favorite List data models.
     * @param   void.
     * @return  void.
     */
    void deleteW3WFavoriteListModel();

    /**
     * @brief   Method to create W3W related Recent List data models.
     * @param   void.
     * @return  void.
     */
    void createW3WRecentListModel();

    /**
     * @brief   Method to delete W3W related Recent List data models.
     * @param   void.
     * @return  void.
     */
    void deleteW3WRecentListModel();

    /**
     * @brief   Method to get W3W setup list model.
     * @param   void.
     * @return  pointer to the object of class CW3WSetupListModel
     */
    QAbstractListModel* w3wSetupListModel(){ return m_pW3WSetupListModel; }

    /**
     * @brief   Method to get W3W About list model.
     * @param   void.
     * @return  pointer to the object of class CW3WAboutListModel
     */
    QAbstractListModel* w3wAboutListModel(){ return m_pW3WAboutListModel; }

    /**
     * @brief   Method to get W3W Auto Suggestion list model.
     * @param   void.
     * @return  pointer to the object of class CW3WAutoSuggestionListModel
     */
    QAbstractListModel* w3wAutoSuggestionListModel(){ return m_pW3WAutoSuggestionListModel; }

    /**
     * @brief   Method to get W3W Favorite list model.
     * @param   void.
     * @return  pointer to the object of class CW3WFavoriteListModel
     */
    QAbstractListModel* w3wFavoriteListModel(){ return m_pW3WFavoriteListModel; }

    /**
     * @brief   Method to get W3W Recent list model.
     * @param   void.
     * @return  pointer to the object of class CW3WRecentListModel
     */
    QAbstractListModel* w3wRecentListModel(){ return m_pW3WRecentListModel; }

    /**
     * @brief   updateSetupListModel: Method to update the Setup List model.
     * @param   void.
     * @return  void.
     */
    void updateSetupListModel();

    /**
     * @brief   Method to update the Checkbox Menu setting in Persistency.
     * @param   iItemId , This parameter contains the selected Item Id.
     * @param   bIsChecked , This parameter contains whether the selected Item is checked or not.
     * @return  void.
     */
    Q_INVOKABLE void invUpdateCheckboxSetting(int iItemId, bool bIsChecked);

    /**
     * @brief   invSetAutoLaunchPermissionStatusForAA: Method to set whether Auto Launch Permission is provided for
     *          Android Auto or not.
     * @param   autoLaunchPermission : auto launch permission for Android Auto.
     * @return  void.
     */
    Q_INVOKABLE void invSetAutoLaunchPermissionStatusForAA(bool autoLaunchPermission);

    /**
     * @brief   autoLaunchPermissionStatusForAA: Method to get whether Auto Launch Permission is provided for
     *          Android Auto or not.
     * @param   void.
     * @return  TRUE if Auto Launch Permission is provided for Android Auto, FALSE otherwise.
     */
    bool autoLaunchPermissionStatusForAA();

    /**
     * @brief   invSetAutoLaunchPermissionStatusForCP: Method to set whether Auto Launch Permission is provided for
     *          Apple CarPlay or not.
     * @param   autoLaunchPermission : auto launch permission for Apple CarPlay.
     * @return  void.
     */
    Q_INVOKABLE void invSetAutoLaunchPermissionStatusForCP(bool autoLaunchPermission);

    /**
     * @brief   autoLaunchPermissionStatusForCP: Method to get whether Auto Launch Permission is provided for
     *          Apple CarPlay or not.
     * @param   void.
     * @return  TRUE if Auto Launch Permission is provided for Apple CarPlay, FALSE otherwise.
     */
    bool autoLaunchPermissionStatusForCP();

    /**
     * @brief   invSetStartupWalkthroughStatus: Method to set whether Walkthrough on Startup to be displayed or not.
     * @param   startupWalkthroughStatus : whether Walkthrough on Startup to be displayed or not.
     * @return  void.
     */
    Q_INVOKABLE void invSetStartupWalkthroughStatus(bool startupWalkthroughStatus);

    /**
     * @brief   startupWalkthroughStatus: Method to get whether Walkthrough on Startup status.
     * @param   void.
     * @return  TRUE if Walkthrough on Startup is enabled, FALSE otherwise.
     */
    bool startupWalkthroughStatus();

    /**
     * @brief	getKeyButtonDefaultImage: This function returns the path of default state images.
     * @param	iKeyIndex: Received from qml, based on index corresponding image path is returned.
     * @return	QString: Path of the image.
     */
    Q_INVOKABLE QString getKeyButtonDefaultImage(int iKeyIndex);

    /**
     * @brief	getKeyButtonPressedImage: This function returns the path of pressed state images.
     * @param	iKeyIndex: Received from qml, based on index corresponding image path is returned.
     * @return	QString: Path of the image.
     */
    Q_INVOKABLE QString getKeyButtonPressedImage(int iKeyIndex);

    /**
     * @brief	getKeyButtonDisabledImage: This function returns the path of disabled state images.
     * @param	iKeyIndex: Received from qml, based on index corresponding image path is returned.
     * @return	QString: Path of the image.
     */
    Q_INVOKABLE QString getKeyButtonDisabledImage(int iKeyIndex);

    /**
     * @brief getClickedCharacter: Gets the input character for W3W Address Edit box based on the index passed
     * @param iCharIndex - clicked character index - passed from qml
     * @return QChar: character which is clicked
     */
    Q_INVOKABLE QChar getClickedCharacter(int iCharIndex);

    /**
     * @brief getFlagIconURLForCountryCode: Gets the Flag icon URL for the specified Country code.
     * @param countryCode - Country code for which the Flag icon is required.
     * @return QString: Flag icon URL for the specified Country code, return "" if country code is not present in Map.
     */
    Q_INVOKABLE QString getFlagIconURLForCountryCode(QString countryCode);

    /**
     * @brief   Method to set the W3W Address Input text entered in W3W Address Suggestion screen.
     * @param   strInputText , This parameter contains the input text entered in W3W Address Suggestion screen.
     * @return  void.
     */
    Q_INVOKABLE void setW3WAddressInputText(const QString &strInputText);

    /**
     * @brief Method to get the W3W Address Input text entered in W3W Address Suggestion screen.
     * @param void.
     * @return QString: W3W Address Input text entered in W3W Address Suggestion screen.
     */
    Q_INVOKABLE QString w3wAddressInputText();

    /**
     * @brief Method to set the auto suggestion recieved status.
     * @param bAutoSuggestionRecivedStatus:  W3W Address Auto suggestion recieved status.
     * @return void.
     */
    Q_INVOKABLE void setAutoSuggestionRecievedStatus(bool bAutoSuggestionRecivedStatus);

    /**
     * @brief Method to get the auto suggestion recieved status.
     * @param void.
     * @return bool: W3W Address Auto suggestion recieved status.
     */
    Q_INVOKABLE bool autoSuggestionRecievedStatus();

    /**
     * @brief Method to select the W3W Address item from Auto Suggestion / Favorite Addresses / Recent Addresses screen.
     * @param  addressType : Type of W3W address (Auto Suggestion / Favourite / Recent).
     *         itemId : Item id of the selected W3W Address.
     * @return void
     */
    Q_INVOKABLE void invSelectW3WAddressItem(CW3WEnum::EW3WAddressType addressType, int itemId);

    /**
     * @brief Method to set the selected W3W address item from either of Address Suggestion /
     *        Favorite Addresses / Recent Addresses screens.
     * @param selectedW3WAddressItem: Selected W3W Address item.
     * @return void
     */
    void setSelectedW3WAddressItem(const CW3WData::SW3WAddressData selectedW3WAddressItem);

    /**
     * @brief Method to get the Selected W3W address item.
     * @param void.
     * @return CW3WData::SW3WAddressData&: Selected W3W Address.
     */
    CW3WData::SW3WAddressData& selectedW3WAddressItem();

    /**
     * @brief Method to set the selected W3W address.
     * @param strSelectedAddress: Selected W3W Address.
     * @return void
     */
    Q_INVOKABLE void setSelectedW3WAddress(const QString strSelectedAddress);

    /**
     * @brief Method to get the Selected W3W Address.
     * @param void.
     * @return QString: Selected W3W Address.
     */
    Q_INVOKABLE QString selectedW3WAddress();

    /**
     * @brief Method to set the selected W3W address Label.
     * @param strSelectedAddressLabel: Selected W3W Address Label.
     * @return void
     */
    Q_INVOKABLE void setSelectedW3WAddressLabel(const QString strSelectedAddressLabel);

    /**
     * @brief Method to get the Selected W3W Address Label.
     * @param void.
     * @return QString: Selected W3W Address Label.
     */
    Q_INVOKABLE QString selectedW3WAddressLabel();

    /**
     * @brief   Method to check whether favorite maximum limit is reached or not.
     * @param   void.
     * @return  bool: whether favorite maximum limit is reached or not.
     */
    Q_INVOKABLE bool invIsFavoriteMaxLimitReached();

    /**
     * @brief Method to add the selected W3W Address to favorite addresses.
     * @param  void
     * @return void
     */
    Q_INVOKABLE void invAddToFavorite();

    /**
     * @brief Method to edit the selected W3W Address from favorite addresses.
     * @param  void
     * @return void
     */
    Q_INVOKABLE void invEditFavorite();

    /**
     * @brief updateFavoriteSavedStatus: Updates the status of favorite addition or modification
     * @param favoriteSavedStatus (true : if favorite saved successfully, else false).
     * @return void.
     */
    void updateFavoriteSavedStatus(bool favoriteSavedStatus);

    /**
     * @brief Method to select the W3W Address item for favorite from Auto Suggestion / Favourite / Recent screens.
     * @param addressType : Type of W3W address (Auto Suggestion / Favorite / Recent)
     *        favoriteOperation : Operation to be performed on Favorite (Add or Edit)
     *        itemId : Item id of the selected W3W Address from Favorite / Recent list,
     *        default argument is -1. So no need to pass for adding favorite from W3W main screen.
     * @return void
     */
    Q_INVOKABLE void invSelectW3WAddressForFavorite(CW3WEnum::EW3WAddressType addressType, CW3WEnum::EW3WFavoriteOperation favoriteOperation,
                                                    int itemId = -1);

    /**
     * @brief Method to set the selected W3W address item for Favorite from W3W Main /
     *        Favorite Addresses or Recent Addresses screens.
     * @param selectedW3WAddressItemForFavorite: Selected W3W Address item for Favorite.
     * @return void
     */
    void setSelectedW3WAddressItemForFavorite(const CW3WData::SW3WAddressData selectedW3WAddressItemForFavorite);

    /**
     * @brief Method to set the selected W3W address For Favorite.
     * @param strSelectedAddressForFavorite: Selected W3W Address For Favorite.
     * @return void
     */
    Q_INVOKABLE void setSelectedW3WAddressForFavorite(const QString strSelectedAddressForFavorite);

    /**
     * @brief Method to get the Selected W3W Address For Favorite.
     * @param void.
     * @return QString: Selected W3W Address For Favorite.
     */
    Q_INVOKABLE QString selectedW3WAddressForFavorite();

    /**
     * @brief Method to set the selected W3W address Label For Favorite.
     * @param strSelectedAddressLabel: Selected W3W Address Label For Favorite.
     * @return void
     */
    Q_INVOKABLE void setSelectedW3WAddressLabelForFavorite(const QString strSelectedAddressLabelForFavorite);

    /**
     * @brief Method to get the Selected W3W Address Label For Favorite.
     * @param void.
     * @return QString: Selected W3W Address Label For Favorite.
     */
    Q_INVOKABLE QString selectedW3WAddressLabelForFavorite();

    /**
     * @brief Method to delete the selected W3W Address from Favorite Addresses or Recent addresses based on specified type.
     * @param  addressType : Address type to be deleted (Favorite/Recent)
     * @return void
     */
    Q_INVOKABLE void invDeleteW3WAddress(CW3WEnum::EW3WAddressType addressType);

    /**
     * @brief updateAddressDeletedStatus: Updates the status of W3W address deletion
     * @param addressDeletedStatus (true : if deleted successfully, else false).
     * @return void.
     */
    void updateAddressDeletedStatus(bool addressDeletedStatus);

    /**
     * @brief Method to select the W3W Address item from Recent Addresses list.
     * @param addressType : Type of W3W address (Auto Suggestion / Favourite / Recent)
     *        itemId : Item id of the selected W3W Address.
     * @return void
     */
    Q_INVOKABLE void invSelectW3WAddressForDelete(CW3WEnum::EW3WAddressType addressType, int itemId);

    /**
     * @brief Method to set the selected W3W address item for Delete from
     *        Favorite Addresses or Recent Addresses screens.
     * @param selectedW3WAddressItemForDelete: Selected W3W Address item for Delete.
     * @return void
     */
    void setSelectedW3WAddressItemForDelete(const CW3WData::SW3WAddressData selectedW3WAddressItemForDelete);

    /**
     * @brief Method to set the selected W3W address For Delete.
     * @param strSelectedAddressForDelete: Selected W3W Address For Delete.
     * @return void
     */
    Q_INVOKABLE void setSelectedW3WAddressForDelete(const QString strSelectedAddressForDelete);

    /**
     * @brief Method to get the Selected W3W Address For Delete.
     * @param void.
     * @return QString: Selected W3W Address For Delete.
     */
    Q_INVOKABLE QString selectedW3WAddressForDelete();

    /**
     * @brief Method to set the selected W3W address Label For Delete.
     * @param strSelectedAddressLabel: Selected W3W Address Label For Delete.
     * @return void
     */
    Q_INVOKABLE void setSelectedW3WAddressLabelForDelete(const QString strSelectedAddressLabelForDelete);

    /**
     * @brief Method to get the Selected W3W Address Label For Delete.
     * @param void.
     * @return QString: Selected W3W Address Label For Delete.
     */
    Q_INVOKABLE QString selectedW3WAddressLabelForDelete();

    /**
     * @brief Method to initiate Navigation using specified W3W Address.
     * @param strInputText : Input Text containing W3W word for initiating the Navigation.
     * @return void.
     */
    Q_INVOKABLE void invInitiateNavigation(const QString &strInputText);

    /**
     * @brief Method to initiate Navigation using selected W3W Address item.
     * @param void.
     * @return void.
     */
    Q_INVOKABLE void invInitiateNavigation();

    /**
     * @brief updateNavigationStatus update the navigation status provided by the below layers
     * @param navigationStatus navigation status ( true if navigation is success, else false )
     * @return void
     */
    void updateNavigationStatus(bool navigationStatus);

    /**
	 * @brief Method to activate VR for W3W.
     * @param void.
     * @return void.
     */
    Q_INVOKABLE void invActivateVRForW3W();

    /**
     * @brief   Method to check whether the provided text is in W3W Address format.
     * @param   strInputText: entered text in W3W Address suggestion screen.
     * @return  bool: whether the specified text is in W3W Address format.
     */
    Q_INVOKABLE bool isTextInW3WAddressFormat(const QString &strInputText);

    /**
     * @brief updateOnCoreProxyAvailability: Updates the current available status of the w3w core Proxy whether available or not
     * @param bW3WCoreProxyStatus: w3w core Proxy Status.
     * @return void.
     */
    void updateOnCoreProxyAvailability(bool bW3WCoreProxyStatus);

    /**
     * @brief updateOnPluginProxyAvailability: Updates the current available status of the w3w plugin Proxy whether available or not
     * @param bW3WPluginProxyStatus: w3w core Proxy Status.
     * @return void.
     */
    void updateOnPluginProxyAvailability(bool bW3WPluginProxyStatus);

    /**
     * @brief updateAutoSuggestionList gets the auto suggestion list and updates the model
     * @param void
     * @return void
     */
    void updateAutoSuggestionList();

    /**
     * @brief   Method to get the W3W Favorite or Recent Addresses.
     * @param   addressType , This parameter contains the type of W3W address (Favorite or Recent).
     * @return  void.
     */
    Q_INVOKABLE void invGetW3WAddresses(CW3WEnum::EW3WAddressType addressType);

    /**
     * @brief   Method to get both the favorite and recent addresses.
     * @param   void.
     * @return  void.
     */
    void getFavoriteAndRecentAddresses();

    /**
     * @brief updateFavoriteAddressList gets the favorite address list and updates the model
     * @param void
     * @return void
     */
    void updateFavoriteAddressList();

    /**
     * @brief updateRecentAddressList gets the recent address list and updates the model
     * @param void
     * @return void
     */
    void updateRecentAddressList();

    /**
     * @brief   Method to update the Country Preference for the selected option into persistency.
     * @param   iItemId , This parameter contains the selected Item Id.
     * @return  void.
     */
    Q_INVOKABLE void invUpdateCountryPreference(int iItemId);

    /**
     * @brief CW3WAdaptor::updateCurrentCountryCode update the country code provided by the below layers
     * @param countryCode country code
     * @return void
     */
    void updateCurrentCountryCode(const QString &countryCode);

    /**
     * @brief CW3WAdaptor::getCurrentCountryCode gets the current country code provided by the below layers
     * @param void
     * @return countryCode country code
     */
    QString getCurrentCountryCode();

    /**
     * @brief updateMapsLaunchStatus update the maps launch status provided by the below layers
     * @param mapsLaunchStatus maps launch status success/failure
     * @return void
     */
    void updateMapsLaunchStatus(int mapsLaunchStatus);

    /**
     * @brief updateConnNextStatus update the connnext connection status provided by the below layers
     * @param connNextStatus connnext connection status suucess/failure
     * @return void
     */
    void updateConnNextStatus(int connNextStatus);

    /**
     * @brief updateW3WCoordinates update the w3w coordinates for the provided address
     * @param lat latitude value
     * @param lng longitude value
     * @return void
     */
    void updateW3WCoordinates(double lat, double lng);

    /**
     * @brief Method to get the latitude of last navigated W3W Address.
     * @param void.
     * @return double: latitude of last navigated W3W Address.
     */
    Q_INVOKABLE double lastNavigatedLatitude();

    /**
     * @brief Method to set the Latitude of last Navigated W3W Address.
     * @param lastNavigatedLatitude: Latitude of last Navigated W3W Address.
     * @return void
     */
    Q_INVOKABLE void setLastNavigatedLatitude(double lastNavigatedLatitude);

    /**
     * @brief Method to get the longitude of last navigated W3W Address.
     * @param void.
     * @return double: longitude of last navigated W3W Address.
     */
    Q_INVOKABLE double lastNavigatedLongitude();

    /**
     * @brief Method to set the Longitude of last Navigated W3W Address.
     * @param lastNavigatedLongitude: Longitude of last Navigated W3W Address.
     * @return void
     */
    Q_INVOKABLE void setLastNavigatedLongitude(double lastNavigatedLongitude);

    /**
     * @brief updateW3WAddressOffCoord update the w3w address for the provided coordinates
     * @param w3wAddress
     */
    void updateW3WAddress(QString w3wAddress);

    /*!
     * @brief   Method to send the W3W Address to the specified number.
     * @param   number : The number to which the W3W Address is to be sent.
     *          W3WAddress : W3W Address to be sent.
     * @return  void.
     */
    Q_INVOKABLE void invShareW3WAddressViaSMS(const QString number, const QString W3WAddress);

    /**
     * @brief editLabelSaveButtonClicked: Method gets called on Save button click, to update the keypad text as a label for W3W Address
     * @param const labelName - Label name in the text input field
     * @return void
     */
    Q_INVOKABLE void editLabelSaveButtonClicked(const QString &labelName);

signals:

    /**
     * @brief sigW3WCoreProxyAvailability provides proxy availability status for w3w core proxy
     * @param status true / false
     * @return void
     */
    void sigW3WCoreProxyAvailability(bool status);

    /**
     * @brief   Signal emits whenever W3W Address auto suggestion is recieved status gets changed.
     * @param   void.
     * @return  void.
     */
    void sigAutoSuggestionRecievedStatusChanged();

    /**
     * @brief   Signal emits whenever selected W3W Address gets changed.
     * @param   void.
     * @return  void.
     */
    void sigSelectedW3WAddressChanged();

    /**
     * @brief   Signal emits whenever selected W3W Address Label gets changed.
     * @param   void.
     * @return  void.
     */
    void sigSelectedW3WAddressLabelChanged();

    /**
     * @brief   Signal emits whenever selected W3W Address For Favorite gets changed.
     * @param   void.
     * @return  void.
     */
    void sigSelectedW3WAddressForFavoriteChanged();

    /**
     * @brief   Signal emits whenever selected W3W Address Label For Favorite gets changed.
     * @param   void.
     * @return  void.
     */
    void sigSelectedW3WAddressLabelForFavoriteChanged();

    /**
     * @brief   Signal emits whenever selected W3W Address For Delete gets changed.
     * @param   void.
     * @return  void.
     */
    void sigSelectedW3WAddressForDeleteChanged();

    /**
     * @brief   Signal emits whenever selected W3W Address Label For Delete gets changed.
     * @param   void.
     * @return  void.
     */
    void sigSelectedW3WAddressLabelForDeleteChanged();

    /**
     * @brief   Signal emits whenever Latitude of last navigated W3W address gets changed.
     * @param   void.
     * @return  void.
     */
    void sigLastNavigatedLatitudeChanged();

    /**
     * @brief   Signal emits whenever Longitude of last navigated W3W address gets changed.
     * @param   void.
     * @return  void.
     */
    void sigLastNavigatedLongitudeChanged();

public slots:

    /**
     * @brief   sltPopupResult: Slot to be connected to PopupManager's signal sigPopupResult to handle
     *          Popup events
     * @param   popupId - Id of the Popup
     * @param   popupResult - Result of the Popup(Displayed, Closed or Ignored)
     * @param   additionalInfo - Additional info (based on reason on which popup is closed)
     * @return  void.
     */
    void sltPopupResult(CPopupEnum::EPopupID popupId, CPopupEnum::EPopupResult popupResult, QString additionalInfo);

private:

    /**
     * @brief   Method to fill the keypad button data in a Map for W3W Address Suggestion keyboard.
     * @param   void.
     * @return  void.
     */
    void fillKeypadButtonDataMap();

    /**
     * @brief   Method to fill the Flags icon URL in a Map for respective country code.
     *          The country code will be the key, and Flag icon URL will be the value for this map pair.
     * @param   void.
     * @return  void.
     */
    void fillFlagsDataMap();

    /**
     * @brief   Method to check whether the entered text in W3W Address suggestion screen is ready to be sent to W3W Service for auto suggestion.
     * @param   strInputText: entered text in W3W Address suggestion screen.
     * @return  bool: whether the text entered in W3W Address suggestion screen is ready to be sent to W3W Service for auto suggestion.
     */
    bool isTextReadyForAutoSuggestion(const QString &strInputText);

    /**
     * @brief   Method to check whether specified w3w address is already saved in favorites or not.
     * @param   selectedW3WAddressItemForFavorite: selected w3w address to be saved to favorites.
     * @return  bool: whether specified w3w address is already saved in favorites or not.
     */
    bool isFavoriteAlreadySaved(CW3WData::SW3WAddressData selectedW3WAddressItemForFavorite);

private:

    /* MAX_LIMIT_FOR_FAVORITES: Maximum limit for favorites */
    const static int MAX_LIMIT_FOR_FAVORITES = 10;

    /* KEYPAD_CHAR_ARRAY_COLUMNS: Total Number of Characters in the W3W Address Suggestion keyboard */
    const static int KEYPAD_CHAR_ARRAY_COUNT = 30;

    /* Match the input text with the below regular expression to know whether the text is in W3W address format or not */
    const QString m_strW3WAddressRegularExpression ="[^0-9`~!@#$%^&*()+\\-_=\\[{\\}\\\\|'<,.>?/\";:£§º©®\\s]{1,}[・.。]"
                                                    "[^0-9`~!@#$%^&*()+\\-_=\\[{\\}\\\\|'<,.>?/\";:£§º©®\\s]{1,}[・.。]"
                                                    "[^0-9`~!@#$%^&*()+\\-_=\\[{\\}\\\\|'<,.>?/\";:£§º©®\\s]{1,}";

    /* This map holds the indexe's & corresponding keypad data for W3W Address suggestion keyboard */
    QMap<int, CW3WData::SW3WAddressSuggestionKeypadData> m_mapKeypadButtonData;

    /* This map holds the Flag icon URL for respective country code */
    QMap<QString, QString> m_mapFlagsData;

    /* Pointer of CW3WSetupListModel class used to load the list items for W3W Setup screen */
    CW3WSetupListModel*                   m_pW3WSetupListModel;

    /* Pointer of CW3WSetupListModel class used to load the list items for W3W About screen */
    CW3WAboutListModel*                   m_pW3WAboutListModel;

    /* Pointer of CW3WAutoSuggestionListModel class used to load the auto suggestion list items for W3W Address Suggestion screen */
    CW3WAutoSuggestionListModel*          m_pW3WAutoSuggestionListModel;

    /* Pointer of CW3WFavoriteListModel class used to load the list items for W3W Favorite screen */
    CW3WFavoriteListModel*                   m_pW3WFavoriteListModel;

    /* Pointer of CW3WRecentListModel class used to load the list items for W3W Recent screen */
    CW3WRecentListModel*                   m_pW3WRecentListModel;

    /* String to hold typed input text in W3W Address Suggestion screen */
    QString m_strW3WAddressInputText;

    /* Boolean whether Auto Suggestion list is recieved or not, based on that UI will change in W3W Address Suggestion screen */
    bool  m_bAutoSuggestionReceivedStatus;

    /* Selected W3W Address item in any of Address Suggestion / Favorite Addresses / Recent Addresses screen */
    CW3WData::SW3WAddressData m_SelectedW3WAddressItem;

    /* Selected W3W Address item for Deletion in Favorite Addresses or Recent Addresses screen */
    CW3WData::SW3WAddressData m_SelectedW3WAddressItemForDelete;

    /* Selected W3W Address item to Add or Edit Favorite in Favorite Addresses or Recent Addresses screen */
    CW3WData::SW3WAddressData m_SelectedW3WAddressItemForFavorite;

    /* Holds the current W3W Address type (Favorite/Recent) on which the Add/Edit/Delete operation is performed */
    CW3WEnum::EW3WAddressType m_CurrentW3WAddressType;

    /* To distinguish whether favorite is being getting added or edited */
    CW3WEnum::EW3WFavoriteOperation m_FavoriteOperation;

    /* boolean store the w3w core proxy status. available/unavailable */
    bool m_bW3WCoreProxyStatus;

    /* boolean store the w3w plugin proxy status. available/unavailable */
    bool m_bW3WPluginProxyStatus;

    /* pointer to store the w3w resource object */
    CW3WResourceImpl* m_pW3WResource;

    /* string to store the w3w country code set by the user */
    QString m_CurrentCountryCode;

    /* stores the connNext connection status (0 : Connected, 1 : Not connected) */
    int m_connNextConnStatus;

    /* stores the last navigated w3w address */
    QString m_LastNavigatedW3WAddress;

    /* stores the w3w coordinates for an address */
    CW3WData::Coordinates m_W3WCoordinates;

    /* stores the w3w address for the provided coordinates */
    QString m_W3WAddress;

};

#endif // CW3WADAPTOR_H
