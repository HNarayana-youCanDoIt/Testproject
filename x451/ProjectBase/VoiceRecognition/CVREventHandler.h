/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CVREventHandler.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CVREventHandler class that implements the slot for the signals
 * emited by VR stub resource layer to inform VR adaptor regarding the request sent by VR proxy.
 */

#ifndef CVREVENTHANDLER_H
#define CVREVENTHANDLER_H

#include <QObject>
#include <QString>

class CVREventHandler : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief   CVRStubEventProvider: Constructor of CVRStubEventProvider.
     * @param   pParent: QObject pointer pointing to the parent class.
     * @return  NA.
     */
    explicit CVREventHandler(QObject *pParent = nullptr);

    /**
     * @brief   ~CVRStubEventProvider: Destructor of CVRStubEventProvider.
     * @param   NA.
     * @return  NA.
     */
    ~CVREventHandler();

public slots:

    /******************************************************//**
     * @category SLOTS
     * @brief Slots connected with VRStub signals
     *******************************************************/
    /**
     * @brief   setScreenRequest: Method to notify VR adaptor layer to take action
     *          on setScreen method request.
     * @param   strScreenName: Screen name that HMI requires to display(switch).
     * @return  void.
     */
    void sltSetScreenRequest(QString strScreenName);

    /**
     * @brief   sltShowContact: Method to notify VR adaptor layer to take action
     *          on showContact method request.
     * @param   strDatabaseType: Phone database type.
     * @param   iContactId: Contact id of the contact.
     * @return  void.
     */
    void sltShowContact(QString strDatabaseType, int iContactId);

    /**
     * @brief   sltShowTeleprompterList: Method to notify VR adaptor layer to take action
     *          on showTeleprompterList method request.
     * @param   void.
     * @return  void.
     */
    void sltShowTeleprompterList();

    /**
     * @brief   sltShowPickList: Method to notify VR adaptor layer to take action
     *          on showPickList method request.
     * @param   void.
     * @return  void.
     */
    void sltShowPickList();

    /**
     * @brief   sltHidePickList: Method to notify VR adaptor layer to take action
     *          on hidePickList method request.
     * @param   void.
     * @return  void.
     */
    void sltHidePickList();

    /**
     * @brief   sltSetFocusedItem: Method to notify VR adaptor layer to take action
     *          on setFocusedItem method request.
     * @param   iLineNo: Line number to be highligted.
     * @return  void.
     */
    void sltSetFocusedItem(int iLineNo);

    /**
     * @brief   sltFocusSelectedCategory: Method to notify VR adaptor layer to take action
     *          on focusSelectedCategory method request.
     * @param   strCategory: Category on which the focus has to be set.
     * @return  void.
     */
    void sltFocusSelectedCategory(QString strCategory);

    /**
     * @brief   sltMediaFilterListShow: Method to notify VR adaptor layer to take action
     *          on mediaFilterListShow method request.
     * @param   iMediaFilterType: media browse category type to be browsed.
     * @param   iMediaFilterId: media browse category id to fetch data for a selected item.
     *          If -1 then show all the content of the media categroy otherwise show the content
     *          of the passed filterId.
     * @return  void.
     */
    void sltMediaFilterListShow(qint32 iMediaFilterType, qint64 iMediaFilterId);

    /******************************************************//**
     * @category SLOTS
     * @brief Slots connected with VRProxy signals
     *******************************************************/
    /**
     * @brief   sltVRStateChange: Method to notify VR adaptor layer to take action
     *          on VR state change.
     * @param   iVRState - current state of voice recognition.
     * @return  void.
     */
    void sltVRStateChange(int iVRState);

    /**
     * @brief   sltVRDialogStateChange: Method to notify VR adaptor layer to take action
     *          on VR dialog state change.
     * @param   iVRDialogState - current dialog state of voice recognition.
     * @return  void.
     */
    void sltVRDialogStateChange(int iVRDialogState);

    /**
     * @brief   sltVRAvailableStatus: Method to notify VR adaptor layer to take action
     *          on VR available status.
     * @param   bVRAvailableStatus - status of VR availibility, whether available or not.
     * @return  void.
     */
    void sltVRAvailableStatus(bool bVRAvailableStatus);

    /**
     * @brief   sltVRProxyAvailableStatus: Method to notify VR adaptor layer to take action
     *          on VR proxy available status.
     * @param   bVRProxyAvailableStatus - status of VR proxy availibility, whether available or not.
     * @return  void.
     */
    void sltVRProxyAvailableStatus(bool bVRProxyAvailableStatus);

private:
    /******************************************************//**
     * @category    INTERNAL METHODS
     *******************************************************/

    /*!
     * @brief   connectVRStubSignals: Method to connect signals provided by CVRStubEventProvider class
     *          with the internal slots.
     * @param   void.
     * @return  void.
     */
    void connectVRStubSignals();

    /*!
     * @brief   disconnectVRStubSignals: Method to disconnect signals provided by CVRStubEventProvider class
     *          with the internal slots.
     * @param   void.
     * @return  void.
     */
    void disconnectVRStubSignals();

    /*!
     * @brief   connectVRProxySignals: Method to connect signals provided by CVRProxyEventProvider class
     *          with the internal slots.
     * @param   void.
     * @return  void.
     */
    void connectVRProxySignals();

    /*!
     * @brief   disconnectVRProxySignals: Method to disconnect signals provided by CVRProxyEventProvider class
     *          with the internal slots.
     * @param   void.
     * @return  void.
     */
    void disconnectVRProxySignals();
};

#endif // CVREVENTHANDLER_H
