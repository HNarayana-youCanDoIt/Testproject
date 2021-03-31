/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CVRStubEventProvider.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CVRStubEventProvider class that shall publish events
 * whenever HMI VRStubResource layer receive some request from VR proxy.
 */

#ifndef CVRSTUBEVENTPROVIDER_H
#define CVRSTUBEVENTPROVIDER_H

#include <QObject>
#include <QString>

using namespace std;

class CVRStubEventProvider : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief   CVRStubEventProvider: Constructor of CVRStubEventProvider.
     * @param   pParent: QObject pointer pointing to the parent class.
     * @return  NA.
     */
    explicit CVRStubEventProvider(QObject *pParent = nullptr);

    /**
     * @brief   ~CVRStubEventProvider: Destructor of CVRStubEventProvider.
     * @param   NA.
     * @return  NA.
     */
    ~CVRStubEventProvider();

    /************************************************************************//**
     * @category    METHODS
     * @brief       Methods that would be used by the VRStubResourceImpl
     * layer to indirectly emit signals to the VR adaptor layer
     ************************************************************************/

    /**
     * @brief   setScreenRequest: Method to be called by CVRStubResourceImpl class to
     *          inform VR adaptor layer to take action on setScreen method request.
     * @param   strScreenName: Screen name that HMI requires to display(switch).
     * @return  void.
     */
    void setScreenRequest(const string& strScreenName);

    /**
     * @brief   showContact: Method to be called by CVRStubResourceImpl class to
     *          inform VR adaptor layer to take action on showContact method request.
     * @param   strDatabaseType: Phone database type.
     * @param   iContactId: Contact id of the contact.
     * @return  void.
     */
    void showContact(const string& strDatabaseType, int iContactId);

    /**
     * @brief   showTeleprompterList: Method to be called by CVRStubResourceImpl class to
     *          inform VR adaptor layer to take action on showTeleprompterList method request.
     * @param   void.
     * @return  void.
     */
    void showTeleprompterList();

    /**
     * @brief   showPickList: Method to be called by CVRStubResourceImpl class to
     *          inform VR adaptor layer to take action on showPickList method request.
     * @param   void.
     * @return  void.
     */
    void showPickList();

    /**
     * @brief   hidePickList: Method to be called by CVRStubResourceImpl class to
     *          inform VR adaptor layer to take action on hidePickList method request.
     * @param   void.
     * @return  void.
     */
    void hidePickList();

    /**
     * @brief   setFocusedItem: Method to be called by CVRStubResourceImpl class to
     *          inform VR adaptor layer to take action on setFocusedItem method request.
     * @param   iLineNo: Line number to be highligted.
     * @return  void.
     */
    void setFocusedItem(int iLineNo);

    /**
     * @brief   focusSelectedCategory: Method to be called by CVRStubResourceImpl class to
     *          inform VR adaptor layer to take action on focusSelectedCategory method request.
     * @param   strCategory: Category on which the focus has to be set.
     * @return  void.
     */
    void focusSelectedCategory(const string& strCategory);

    /**
     * @brief   mediaFilterListShow: Method to be called by CVRStubResourceImpl class to
     *          inform VR adaptor layer to take action on mediaFilterListShow method request.
     * @param   iMediaFilterType: media browse category type to be browsed.
     * @param   iMediaFilterId: media browse category id to fetch data for a selected item.
     *          If -1 then show all the content of the media categroy otherwise show the content
     *          of the passed filterId.
     * @return  void.
     */
    void mediaFilterListShow(int32_t iMediaFilterType, int64_t iMediaFilterId);

signals:

    /******************************************************//**
     * @category    SIGNALS
     * @brief       Signals that shall be emitted to the VR
     * adaptor layer
     *******************************************************/

    /**
     * @brief   sigSetScreenRequest: Signal that shall be emitted to inform adaptor layer
     *          to take action on setScreen method request.
     * @param   strScreenName: Screen name that HMI requires to display(switch).
     * @return  void.
     */
    void sigSetScreenRequest(QString strScreenName);

    /**
     * @brief   sigShowContact: Signal that shall be emitted to inform adaptor layer
     *          to take action on showContact method request.
     * @param   strDatabaseType: Phone database type.
     * @param   iContactId: Contact id of the contact.
     * @return  void.
     */
    void sigShowContact(QString strDatabaseType, int iContactId);

    /**
     * @brief   sigShowTeleprompterList: Signal that shall be emitted to inform adaptor layer
     *          to take action on showTeleprompterList method request.
     * @param   void.
     * @return  void.
     */
    void sigShowTeleprompterList();

    /**
     * @brief   sigShowPickList: Signal that shall be emitted to inform adaptor layer
     *          to take action on showPickList method request.
     * @param   void.
     * @return  void.
     */
    void sigShowPickList();

    /**
     * @brief   sigHidePickList: Signal that shall be emitted to inform adaptor layer
     *          to take action on hidePickList method request.
     * @param   void.
     * @return  void.
     */
    void sigHidePickList();

    /**
     * @brief   sigSetFocusedItem: Signal that shall be emitted to inform adaptor layer
     *          to take action on setFocusedItem method request.
     * @param   iLineNo: Line number to be highligted.
     * @return  void.
     */
    void sigSetFocusedItem(int iLineNo);

    /**
     * @brief   sigFocusSelectedCategory: Signal that shall be emitted to inform adaptor layer
     *          to take action on focusSelectedCategory method request.
     * @param   strCategory: Category on which the focus has to be set.
     * @return  void.
     */
    void sigFocusSelectedCategory(QString strCategory);

    /**
     * @brief   sigMediaFilterListShow: Signal that shall be emitted to inform adaptor layer
     *          to take action on mediaFilterListShow method request.
     * @param   iMediaFilterType: media browse category type to be browsed.
     * @param   iMediaFilterId: media browse category id to fetch data for a selected item.
     *          If -1 then show all the content of the media categroy otherwise show the content
     *          of the passed filterId.
     * @return  void.
     */
    void sigMediaFilterListShow(qint32 iMediaFilterType, qint64 iMediaFilterId);

};

#endif // CVRSTUBEVENTPROVIDER_H
