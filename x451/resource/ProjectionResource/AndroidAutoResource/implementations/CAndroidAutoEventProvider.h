/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CAndroidAutoEventProvider.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* CAndroidAutoEventProvider, Class to send signals to AndroidAuto Application
* layer on AndroidAuto Resource events
*/

#ifndef CANDROIDAUTOEVENTPROVIDER_H
#define CANDROIDAUTOEVENTPROVIDER_H

#include <QObject>

/**
 * @class CAndroidAutoEventProvider
 * @brief Class to send signals to AndroidAuto Application layer on AndroidAuto
 *        Resource events.
 */
class CAndroidAutoEventProvider : public QObject
{
    Q_OBJECT

public:
    /**
    * @brief	CAndroidAutoEventProvider::CAndroidAutoEventProvider private
    *           constructor for class CAndroidAutoEventProvider.
    * @param	pParent: parent class pointer.
    * @return	NA.
    **/
    CAndroidAutoEventProvider(QObject* pParent = nullptr);

    /*!
     * @brief   Destructor of CAndroidAutoEventProvider
     * @param   void.
     * @return  void.
     */
    ~CAndroidAutoEventProvider();

signals:

    /**
     * @brief sigShowFirstRunPopup: This signal will be emitted when, Any
     *        AndroidAuto phone connected for first time to HU. on this signal
     *        HMI needs to show Android Auto first run message popup.
     */
    void sigShowFirstRunPopup();

    /**
     * @brief   sigUpdateAAMediaPlayState: This signal will be emitted when,
     *          AAMediaPlayState recieved from AA pres.
     * @param   usAAMediaPlayState: AAMediaPlayState.
     * @return  void.
     */
    void sigUpdateAAMediaPlayState(ushort usAAMediaPlayState);

    /**
     * @brief sigUpdateAAProjectionStatus: This signal will be emitted when,
     *        AAProjectionStatus recieved from AA pres.
     * @param bAAProjectionStatus: AAProjectionStatus, true if projected else
     *        false.
     * @return  void
     */
    void sigUpdateAAProjectionStatus(bool bAAProjectionStatus);

    /**
     * @brief   sigUpdateOKGoogleStatus: This signal will be emitted when,
     *          OKGoogleStatus recieved from AA press.
     * @param   bAAOKGoogleStatus: true if OKGoogle is active, else false
     * @return  void
     */
    void sigUpdateOKGoogleStatus(bool bAAOKGoogleStatus);

    /**
     * @brief   sigUpdateAANaviStatus: This signal will be emitted when,
     *          AndroidAuto Navigation status recieved from AA press.
     * @param   bAANaviStatus: true if AndroidAuto Navigation is active, else
     *          false.
     * @return  void.
     */
    void sigUpdateAANaviStatus(bool bAANaviStatus);

    /**
     * @brief   sigUpdateAAMediaMetaData: This signal will be emitted when,
     *          AndroidAuto Media Meta data gets changed.
     * @param   void.
     * @return  void.
     */
    void sigUpdateAAMediaMetaData();

    /**
     * @brief   sigUpdateAASessionDetails: This signal will be emitted when,
     *          AndroidAuto AA session details gets changed.
     * @param   void.
     * @return  void.
     */
    void sigUpdateAASessionDetails();

    /**
     * @brief   sigUpdateAANaviTurnEventDetails: This signal will be emitted when,
     *          AndroidAuto AA Navigation Turn Event details gets changed.
     * @param   void.
     * @return  void.
     */
    void sigUpdateAANaviTurnEventDetails();

    /**
     * @brief   sigUpdateAANaviDistanceDetails: This signal will be emitted when,
     *          AndroidAuto AA Navigation Distance details gets changed.
     * @param   void.
     * @return  void.
     */
    void sigUpdateAANaviDistanceDetails();

public:

    /**
     * @brief   updateAAFirstRunConnectionStatus: Method to update upper/AA
     *          adaptor whenever any AA auto phone is connected for the first
     *          time with HU.
     * @param   void
     * @return  void
     */
    void updateAAFirstRunConnectionStatus();

    /**
     * @brief   updateAAMediaPlayState: This function is called When
     *          AAMediaPlayState recieved by AndroidAuto pres.
     * @param   usAAMediaPlayState: AAMediaPlayState.
     * @return  void.
     */
    void updateAAMediaPlayState(ushort usAAMediaPlayState);

    /**
     * @brief updateAAProjectionStatus: This function is called When
     *        AAProjectionStatus is updated AndroidAuto pres.
     * @param bAAProjectionState: AndroidAuto projection status, true if
     *        projected, else false
     */
    void updateAAProjectionStatus(bool bAAProjectionState);

    /**
     * @brief   updateOKGoogleStatus: This function is called When
     *          OK Google status is updated in AndroidAuto pres, to update
     *          OK Google status to upper layer.
     * @param   bOKGoogleStatus: true if OKGoogle is active, else false
     * @return  void
     */
    void updateOKGoogleStatus(bool bOKGoogleStatus);

    /**
     * @brief   updateAANaviStatus: This function is called When
     *          Android Auto Navigation status is updated in AndroidAuto pres,
     *          to update Android Auto Navigation status to upper layer.
     * @param   bAANaviStatus: true if Android Auto Navigation is active, else
     *          false
     * @return  void
     */
    void updateAANaviStatus(bool bAANaviStatus);

    /**
     * @brief   updateAAMediaMetaData: This function is used to notify the updation
     *          of AA Media Meta data to Adaptor layer.
     * @param   void.
     * @return  void.
     */
    void updateAAMediaMetaData();

    /**
     * @brief   updateAASessionDetails: This function is used to notify the updation
     *          of AA session details to Adaptor layer.
     * @param   void.
     * @return  void.
     */
    void updateAASessionDetails();

    /**
     * @brief   updateAANaviTurnEventDetails: This function is used to notify the updation
     *          of AA Navigation Turn Event details to Adaptor layer.
     * @param   void.
     * @return  void.
     */
    void updateAANaviTurnEventDetails();

    /**
     * @brief updateAANaviTurnDistDetails: This function is used to notify the updation
     *          of AA Navigation Distance details to Adaptor layer.
     * @param   void.
     * @return  void.
     */
    void updateAANaviTurnDistanceDetails();

};

#endif // CANDROIDAUTOEVENTPROVIDER_H
