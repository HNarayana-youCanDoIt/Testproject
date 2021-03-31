/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CICCastAdaptor.h
 * @ingroup         HMIComponent
 * @author          Rajat Gupta
 * CICCastAdaptor,  an adaptor for IC cast module,
 * CICCastAdaptor is singleton class used to communicate with qml,resources of IC cast module.
 */

#ifndef CICCASTADAPTOR_H
#define CICCASTADAPTOR_H

#include <QObject>
#include <QString>
#include "CICCastEnums.h"
#include "interfaces/IICCastResource.h"

class CICCastEventHandler;


class CICCastAdaptor : public QObject
{
    Q_OBJECT

    // Properties //

    //Property to set the main IC Cast status
    Q_PROPERTY(bool icCastStatus READ icCastStatus NOTIFY sigICCastStatusChanged)

    //Property to set the main IC Cast enable status
    Q_PROPERTY(bool icCastEnableStatus READ icCastEnableStatus NOTIFY sigICCastEnableStatusChanged)


public:
    /**
    * @brief	CICCastAdaptor constructor for singleton class CICCastAdaptor.
    * @param	pParent: parent class pointer.
    * @return	void.
    **/
    explicit CICCastAdaptor(QObject *pParent = nullptr);
    //________________________________________________________________________________________________

    /**
    * @brief	~CICCastAdaptor is destructor of singleton class CICCastAdaptor
    * @param	void.
    * @return	void.
    **/
    ~CICCastAdaptor();
    //________________________________________________________________________________________________

    /**
    * @brief	getInstance is static method used to get instance of singleton class CICCastAdaptor
    * @param	void.
    * @return	returns the cuurent instance of the CICCastAdaptor.
    **/
    static CICCastAdaptor* getInstance();
    //________________________________________________________________________________________________
    /**
    * @brief  icCastStatus: getter function which returns the status of ic cast.
    * @param  void.
    * @return m_bICCastStatus: Returns the status of ic cast. TRUE if ic cast is enabled, FALSE otherwise.
    **/

    bool icCastStatus() { return m_bICCastStatus; }

    //________________________________________________________________________________________________
    /**
    * @brief  icCastEnableStatus: getter function which returns the enable status of ic cast option.
    * @param  void.
    * @return m_bICCastEnableStatus: Returns the status of ic cast. TRUE if ic cast is enabled, FALSE otherwise.
    **/

    bool icCastEnableStatus() { return m_bICCastEnableStatus; }

    //________________________________________________________________________________________________
    /**
     * @brief setICCastStatus: setter for the ic cast status.
     * @param bICCastStatus: holds the ic cast value that needs to be updated
     * @return void.
     */

    void setICCastStatus(bool bICCastStatus);
    //________________________________________________________________________________________________

    /**
     * @brief setICCastEnableStatus: setter for the ic cast option enable status.
     * @param bICCastEnableStatus: holds the ic cast callback status that needs to be updated
     * @return void.
     */

    void setICCastEnableStatus(bool bICCastEnableStatus);
    //________________________________________________________________________________________________
    /**
     * @brief updateICCastStatus: update the ic cast as per the respose callback.
     * @param iCallbackStatus: holds the ic cast callback status that needs to be updated
     * @return void.
     */

    void updateICCastStatus(int iCallbackStatus);
    //________________________________________________________________________________________________

    /**
     * @brief sendICCastStatus: setter function which will send the ic cast status to the resource layer.
     * @param iCallbackStatus: holds the ic cast callback status that needs to be updated
     * @return void.
     */

    Q_INVOKABLE void sendICCastStatus(bool bICCastStatus);
    //________________________________________________________________________________________________

    /**
     * @brief updateOnProxyAvailability: Updates the current available status of the IC Proxy whether available or not
     * @param bICCastProxyStatus: IC cast Proxy Status.
     * @return void.
     */

    void updateOnProxyAvailability(bool bICCastProxyStatus);
    //________________________________________________________________________________________________

private:

    /**
     * @brief updateOnThemeChanged: function will update the ic cast functionality based on Theme Change.
     * @param void.
     * @return void.
     */
    void updateOnThemeChanged();

    //________________________________________________________________________________________________

    /**
     * @brief mapIcCastThemeValue: function to map the theme value from HMI to Ic cast service side value.
     * @param iIcCastTheme   - value for Ic Cast theme.
     * @return  value after mapping as per Ic cast service side value.
     */
    int mapIcCastThemeValue(int iIcCastTheme);


signals:
    /**
    * @brief	sigICCastStatusChanged : signal gets emitted when ic cast status gets changed
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigICCastStatusChanged();
    //________________________________________________________________________________________________
    /**
    * @brief	sigICCastEnableStatusChanged : signal gets emitted when ic cast enable status gets changed.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigICCastEnableStatusChanged();
    //________________________________________________________________________________________________
private slots:

    /**
     * @brief sltCurrentThemeChangedForICCast Method gets invoked whenever there  is a change in theme type
     * @param   void
     * @return  void
     */
    void sltCurrentThemeChangedForICCast();

private:

    /**
     * @brief m_bICCastStatus: holds the IC cast status
     */
    bool m_bICCastStatus;

    /**
     * @brief m_pICCastAdaptor: for maintaining singleton class instance
     */
    static CICCastAdaptor* m_pICCastAdaptor;

    /**
     * @brief m_bICCastEnableStatus: holds the ic cast option enable status.
     */
    bool m_bICCastEnableStatus;

    /**
     * @brief m_pICCastResource: Pointer for the ICCastResource
     */
    IICCastResource* m_pICCastResource;

    /**
     * @brief m_bICCastValueToBeUpdated: Value which user has requested and will be assigned when the response will be success.
     */
    bool m_bICCastValueToBeUpdated;

    /**
     * @brief m_pICCastEventHandler: Instance of CICCastEventHandler class
     */
    CICCastEventHandler *m_pICCastEventHandler;

};

#endif // CICCASTADAPTOR_H
