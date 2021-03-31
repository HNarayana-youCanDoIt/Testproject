/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CPhoneSetupListModel.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar,Rajat Gupta
 * @brief         This file contains CBtSetupListModel class that shall implement the
 * bt setup list data model that shall be used to update the bt setup screen.
 */

#ifndef CBTSETUPLISTMODEL_H
#define CBTSETUPLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "CPhoneData.h"

/*!
 * @class CPhoneSetupListModel
 * @brief This class shall implement the bt setup list data model that shall be used to update
 * the bt setup qml screen.
 */
class CPhoneSetupListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    /************************************************************************//**
     * @category    ENUMS
     ************************************************************************/

    /*!
     * @enum    EPhoneSetupListRoles
     * @brief   This enum shall hold the values that shall be used by phone setup qml screen
     * to update the data in the view.
     */
    enum EPhoneSetupListRoles
    {
        // This role holds the Item Main text
        PHONE_SETUP_ITEM_TEXT_ROLE = Qt::UserRole + 1,
        // This role holds the Item Enable/Disable state
        PHONE_SETUP_ITEM_ENABLED_ROLE,
        // This role holds the Item Checked/Unchecked state
        PHONE_SETUP_ITEM_CHECKED_ROLE,
        // This role holds the Item type of the list item.
        PHONE_SETUP_ITEM_TYPE_ROLE,
        /**
         * This Role is used to identify the Item which is selected by user and which Item needs to expand on
         * drop-down click.
         */
        PHONE_SETUP_ITEM_ID_ROLE,
        // This role holds the visibility state of Edit Button used in Configure Auto Sms option.
        PHONE_SETUP_ITEM_EDIT_BUTTON_VISIBLE,
    };
public:
    /**
    * @brief	CPhoneSetupListModel::CPhoneSetupListModel constructor for Phone setup model.
    * @param	QObject. The pointer of parent class.
    * @return	NA.
    **/
    CPhoneSetupListModel(QObject* pParent = nullptr);

    /**
    * @brief	CPhoneSetupListModel::CPhoneSetupListModel destructor for Phone setup model.
    * @param	NA.
    * @return	NA.
    **/
    ~CPhoneSetupListModel();

    /************************************************************************//**
     * @category    OVERRIDEN METHODS of QAbstractListModel class
     ************************************************************************/

    /**
    * @brief	CPhoneSetupListModel::rowCount function inherited from QAbstractListModel,
    *           Used to get row count.
    * @param	QModelIndex : The index is used to locate an item in the model.
    * @return	int : holds row count.
    **/
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

    /**
    * @brief	CPhoneSetupListModel::data function inherited from QAbstractListModel,
    *           Used to get data linked to given role and present at given index.
    * @param	(index)QModelIndex : The index is used to locate an item in the model.
    *           (role)int : holds the role name of data to be extract from QModelIndex item.
    * @return	QVariant : data stored under the given role for the item referred to by the index.
    **/
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

    /**
    * @brief	CPhoneSetupListModel::roleNames function inherited from QAbstractListModel,
    *           Used to get role names
    * @param	void.
    * @return	QHash<int, QByteArray> : holds model's role names
    **/
    QHash<int, QByteArray> roleNames() const override;

    /**
     * @brief setData: Sets the role data for the item at index to value
     * @param index: The index for which value to be set
     * @param value: The value to be set for the role
     * @param role: The role data to be modified
     * @return: Returns true if successful; otherwise returns false.
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    /**
     * @brief expandSmsAlertNotification: Expands the Sms alert Notification Dropdown.
     * @param void.
     * @return void.
     */
    Q_INVOKABLE void expandSmsAlertNotification();

    /**
     * @brief collapseSmsAlertNotification: Collapse the Sms alert Notification Dropdown.
     * @param void.
     * @return void.
     */
    Q_INVOKABLE void collapseSmsAlertNotification();


    /**
     * @brief expandConfigAutoSms: Expands the Configure Auto Sms Dropdown.
     * @param void.
     * @return void.
     */
    Q_INVOKABLE void expandConfigAutoSms();

    /**
     * @brief expandConfigAutoSms: Collapse the Sms alert Notification Dropdown.
     * @param void.
     * @return void.
     */
    Q_INVOKABLE void collapseConfigAutoSms();


    /**
     * @brief expandConfigAutoSmsEdit: Expands the Configure Auto Sms Edit Items Dropdown.
     * @param iItemId : Id of the Selected Item which has to be expanded.
     * @return void.
     */
    Q_INVOKABLE void expandConfigAutoSmsEdit(int iItemId);

    /**
     * @brief collapseConfigAutoSmsEdit: Collapse the Configure Auto Sms Edit Items Dropdown.
     * @param iItemId : Id of the Selected Item which has to be collapsed.
     * @return void.
     */
    Q_INVOKABLE void collapseConfigAutoSmsEdit(int iItemId);

    /**
    * @brief	CPhoneSetupListModel::initPhoneSetupMainModel function initializes the Main Phone Setup Model
    * @param	void.
    * @return	void.
    **/
    void initPhoneSetupMainModel();

    /**
    * @brief	CPhoneSetupListModel::initPhoneSetupSmsAlertList function initializes the Sms Alert Notification list
    * items.
    * @param	void.
    * @return	void.
    **/
    void initPhoneSetupSmsAlertList();

    /**
    * @brief	CPhoneSetupListModel::initPhoneSetupConfigureSmsList function initializes the Configure Auto Sms list
    * items.
    * @param	void.
    * @return	void.
    **/
    void initPhoneSetupConfigureSmsList();

    /**
    * @brief	CPhoneSetupListModel::initPhoneSetupConfigureSmsEditList function initializes Configure Auto Sms list
    * items in expanded and edit state.
    * @param	void.
    * @return	void.
    **/
    void initPhoneSetupConfigureSmsEditList();

    /**
    * @brief	CPhoneSetupListModel::updateSmsAlertNotificationList function updates the Sms Alert Notification list
    * @param	void .
    * @return	void.
    **/
    void updateSmsAlertNotificationList();

    /**
    * @brief	CPhoneSetupListModel::updateConfigAutoSmsList function updates the Config Auto Sms list
    * @param	void .
    * @return	void.
    **/
    void updateConfigAutoSmsList();

    /**
    * @brief	CPhoneSetupListModel::updateModelForCheckedRole function updates the model of Phone Setup for Checked Role.
    * @param	iPhoneSetupIndex: Index of the selected item in a phone setup model.
    * @param	bCheckedStaus: Contains the boolean value whether item is checked or unchecked.
    * @return   void.
    **/
    void updateModelForCheckedRole(int iPhoneSetupIndex, bool bCheckedStatus);

    /**
    * @brief	CPhoneSetupListModel::updateConfigureMessageList function updates the Configure Sms related list with updated message.
    * @param	iMessageIndex: Index of the selected item in a phone setup model.
    * @param	strMessage: Contains the string value which is updated by user
    * @return   void.
    **/
    void updateConfigureMessageList(int iMessageIndex, const QString &strUpdatedMessage);

    /**
    * @brief	Method to get the configured sms text selected by user.
    * @param	void.
    * @return   configured auto sms text selected by user.
    **/
    QString getConfiguredAutoSmsText();

    /**
    * @brief	Method to get the sms alert type selected by user.
    * @param	void.
    * @return   configured sms alert type selected by user.
    **/
    int getSmsAlertType();

    /**
    * @brief	isItemEnabled: Method to get whether the phone setup item is enabld or not.
    * @param	eItemName: Phone setup item index.
    * @return   TRUE if the item is enabled, FALSE otherwise.
    **/
    bool isItemEnabled(CPhoneEnum::EPhoneSetupItems eItemIndex);

private:
    /******************************************************//**
     * @category PROPERTIES
     *******************************************************/

    /**
    * @brief List to hold the information of each item in phone setup screen.
    */
    QList<CPhoneData::SPhoneSetupInfo>    m_listPhoneSetup;

    /**
    * @brief List to hold the information of each item in Sms Alert Notification option.
    */
    QList<CPhoneData::SPhoneSetupInfo>      m_listPhoneSMSAlert;

    /**
    * @brief List to hold the information of each item in Configure Auto Sms option.
    */
    QList<CPhoneData::SPhoneSetupInfo>      m_listPhoneSMSConfig;

    /**
    * @brief List to hold the information of each item in Config Auto Sms option when its expanded.
    */
    QList<CPhoneData::SPhoneSetupInfo>      m_listPhoneEditSMS;

    /**
    * @brief boolean variable which holds the value whether Sms Alert notification List Item is expanded/collapsed.
    */
    bool m_bIsSMSAlertItemExpanded;

    /**
    * @brief boolean variable which holds the value whether Configure Auto Sms List Item is expanded/collapsed.
    */
    bool m_bIsConfigAutoSmsItemExpanded;

    /**
    * @brief boolean variable which holds the value whether Configure Auto Sms edit List Item is expanded/collapsed.
    */
    bool m_bIsConfigAutoSmsEditItemExpanded;

    /**
    * @brief This integer variable holds the index of the item in Configure Auto sms List Item which is currently
    * expanded.
    */
    int m_iConfigAutoSmsEditIndexExpanded;

    /**
     * @brief SMS_ALERT_NOTIFICATION_ITEM_START_INDEX: This integer constant holds the starting index for which the Sms Alert
     * Notification dropdown items will be inserted.
     */
    const int SMS_ALERT_NOTIFICATION_ITEM_START_INDEX ;
    /**
     * @brief SMS_ALERT_NOTIFICATION_ITEM_END_INDEX: This integer constant holds the ending index of the Sms Alert
     * Notification dropdown items.
     */
    const int SMS_ALERT_NOTIFICATION_ITEM_END_INDEX ;

    /**
    * @brief CONFIG_SMS_ITEM_START_INDEX: This integer constant holds the starting index for which the Configure Auto Sms dropdown items will be
    * inserted.
    */
    const int CONFIG_SMS_ITEM_START_INDEX ;

    /**
    * @brief CONFIG_SMS_ITEM_END_INDEX: This integer constant holds the ending index for  Configure Auto Sms dropdown items
    */
    const int CONFIG_SMS_ITEM_END_INDEX ;

    /**
    * @brief CONFIG_AUTO_SMS_EDIT_ITEM_OFFSET_INDEX: This integer constant holds the index offset to map the itemId to PhoneSetup List Index.
    */
    const int CONFIG_AUTO_SMS_EDIT_ITEM_OFFSET_INDEX;

    /**
     * @brief FIXED_SMS_COUNT: Total count for Static messages which will not be allowed to edit by end user.
     */
    static const int FIXED_SMS_COUNT = 3;

    /** This array contains SMS strings which cannot be edited */
    QString m_strArrFixedSMSs[3] = {"I am driving..... Sent from TATA ConnectNext.",
                                    "Stuck in Traffic, will be a bit late..... Sent from TATA ConnectNext.",
                                    "I am unable to take your call, Please message..... Sent from TATA ConnectNext."};




};

#endif // CBTSETUPLISTMODEL_H
