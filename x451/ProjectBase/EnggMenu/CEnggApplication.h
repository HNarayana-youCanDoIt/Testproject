/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CEnggApplication.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande, Rajat Gupta
 * CEnggApplication, an application for Engineering module,
 * CEnggApplication act as mediator between QML and Statemachine.
 */

#ifndef CENGGAPPLICATION_H
#define CENGGAPPLICATION_H

#include "CBaseApplication.h"
#include "CEnggMenuEnum.h"
#include "EnggDef.h"
#include <logging.h>
#include <CEnggMenuEnum.h>

class CEnggAdaptor;
class CEnggEventHandler;
class CEnggSM;

/**
 * @brief CEnggApplication, an application for Engineering module,
 * It act as mediator between QML and Statemachine.
 */
class CEnggApplication : public CBaseApplication
{
    Q_OBJECT
public:
    /**
    * @brief	CEnggApplication::CEnggApplication constructor for application class CEnggApplication.
    * @param	pParent: Pointer of parent class.
    * @return	void.
    **/
    CEnggApplication(QQuickItem* pParent = nullptr);
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggApplication::~CEnggApplication is destructor of application class CEnggApplication
    * @param	void.
    * @return	void.
    **/
    ~CEnggApplication();
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeAdaptor::initApplication: method used to initialise application properties.
    * @param	void.
    * @return	void.
    **/
    void initApplication();
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeAdaptor::resetApplication: method used to set the currentScreen to NULL
    * @param	void.
    * @return	void.
    **/
    void resetApplication();
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggApplication::onCreated: CBaseApplication method
    * @param	rootObject.
    * @return	void.
    **/
    virtual void onCreated(QQuickItem* rootObject);
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggApplication::raiseSMEvent is CBaseApplication method
    * @param	name: contains the name which can be used to switch the screen as per raised event.
    * @param    data: contains the data to raise SM event accordingly.
    * @return	void.
    **/
    void raiseSMEvent(const QString & name,const QVariant & data);
    //________________________________________________________________________________________________
    /**
    * @brief	setAppEnggMenuModel: function to change the Model of the List
    * @param	CEnggMenuEnum::EEnggMenuScreen eEnggMenuScreen: contains the model number which has to be set
    * @return	void.
    **/
    void setAppEnggMenuModel(CEnggMenuEnum::EEnggMenuScreen eEnggMenuScreen);
    //________________________________________________________________________________________________
    /**
    * @brief	loadEnggMenuScreen: used to load the required screen.
    * @param	eEnggMenuCurrentScreenIndex: contains the index of the screen which has to be set.
    * @return	void.
    **/
    void loadEnggMenuScreen(CEnggMenuEnum::EEnggMenuScreen eEnggMenuCurrentScreenIndex);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggMain: This method is responsible for raising events to SM for main EnggMenu Screen
     * @param   data: type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggMain(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggTestMode : This method is responsible for raising events to SM for
     *  Test Mode Screen
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggTestMode(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggDriveNext : This method is responsible for raising events to SM for
     *  DrveNext Main Screen
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggDriveNext(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggDriveNextLibUpdate : This method is responsible for raising events to SM for
     *  DrveNext Lib Update Screen
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggDriveNextLibUpdate(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggDriveNextConfigUpdate : This method is responsible for raising events to SM for
     *  DrveNext Config Update Screen
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggDriveNextConfigUpdate(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggDriveNextDebug : This method is responsible for raising events to SM for
     *  DrveNext Debug Log Trip Selection Screen
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggDriveNextDebug(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggDriveNextLog : This method is responsible for raising events to SM for
     *  DrveNext Debug Log Level Screen
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggDriveNextLog(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggDriveNextLogging : This method is responsible for raising events to SM for
     *  DrveNext Debug Logging Location Screen
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggDriveNextLogging(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggDriveNextDetails : This method is responsible for raising events to SM for
     *  DrveNext Details Screen
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggDriveNextDetails(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggButtonPanel : This method is responsible for raising events to SM for
     *  Button Panel Screen
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggButtonPanel(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggDbgLog : This method is responsible for raising events to SM for
     * debug Logs Screen
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggDbgLog(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggIllumination : This method is responsible for raising events to SM for
     *  Illumination Screen
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggIllumination(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggIllumButton : This method is responsible for raising events to SM for
     *  Button Illumination Screen
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggIllumButton(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggIllumDisplay : This method is responsible for raising events to SM for
     * Display Illumination Screen
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggIllumDisplay(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggSysConfig : This method is responsible for raising events to SM for
     * System Config Screen
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggSysConfig(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggSysConfigVIN : This method is responsible for raising events to SM for
     * VIN Screen
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggSysConfigVIN(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggSysConfigVC : This method is responsible for raising events to SM for
     * VC Screen
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggSysConfigVC(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggSysConfig16R : This method is responsible for raising events to SM for
     * 16R Screen
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggSysConfig16R(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggSysConfig16RBtn : This method is responsible for raising events to SM for
     * Button Panel Part No.
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggSysConfig16RBtn(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggSysConfig16RContain : This method is responsible for raising events to SM for
     * Container Part No.
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggSysConfig16RContain(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggSysConfig16RDisplay : This method is responsible for raising events to SM for
     * Display Part No
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggSysConfig16RDisplay(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggSysConfig16RParam : This method is responsible for raising events to SM for
     * Parameterization Part no
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggSysConfig16RParam(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggSysConfig16RSilver : This method is responsible for raising events to SM for
     * Silver part No.
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggSysConfig16RSilver(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggSysConfig16RSoftware : This method is responsible for raising events to SM for
     * Software Part No.
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggSysConfig16RSoftware(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggW3WLastNavigated : This method is responsible for raising events to SM for
     * W3W Last Navigated.
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggW3WLastNavigated(const QVariant & data);
    //________________________________________________________________________________________________
    /**
     * @brief   raiseSMEventScnEnggPictureViewer : This method is responsible for raising events to SM for
     * Picture Viewer.
     * @param   data:  type of event to be raised
     * @return	void.
     */
    void raiseSMEventScnEnggPictureViewer(const QVariant & data);
    //________________________________________________________________________________________________
private:

    /**
     * @brief m_pEnggAdaptor: reference of Engg adaptor instance.
     */
    CEnggAdaptor* m_pEnggAdaptor;

    /**
     * @brief m_pEnggDataEventHandler: pointer of CEnggEventHandler class.
     */
    CEnggEventHandler* m_pEnggDataEventHandler;

    /**
     * @brief m_pEnggSM: pointer to Engg state machine instance
     */
    CEnggSM* m_pEnggSM;

    /**
     * @brief m_aryEnggScreensInfo: Member Variable definition of Struct EnggScreenInfo which will have info of the current screen
     */
    EnggScreenInfo m_aryEnggScreensInfo[EnggScreenCount];

    /**
     * @brief m_eCurrentScreenType: holds the type of screen which has to be set in EnggMenu Module.
     */
    CEnggMenuEnum::EEnggScreenType m_eCurrentScreenType;
    //________________________________________________________________________________________________
};

#endif // CENGGAPPLICATION_H
