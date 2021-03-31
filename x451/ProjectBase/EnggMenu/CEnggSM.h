/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CEnggSM.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande,Rajat Gupta
 * CEnggSM, a State machine handler for Engineering module,
 * CEnggSM inherits SCI_EnggMenu_OCB to handle statemachine events.
 */

#ifndef CENGGSM_H
#define CENGGSM_H

#include "CEnggMenuEnum.h"
#include "StateMachine_TML_HMI_SM.h"

class CEnggApplication;
class CEnggAdaptor;
class CEnggEventHandler;

/**
 * @brief CEnggSM, a State machine handler for Engineering module,
 * It inherits SCI_EnggMenu_OCB to handle statemachine events.
 */
class CEnggSM : public TML_HMI_SM::SCI_EnggMenu_OCB
{
public:
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggSM::CEnggSM constructor for state machine class CEnggSM.
    * @param	QObject.
    * @return	void.
    **/
    CEnggSM(CEnggApplication& enggApp);
    /**
    * @brief	CEnggSM::~CEnggSM is destructor of state machine class CEnggSM
    * @param	void.
    * @return	void.
    **/
    ~CEnggSM();
    //________________________________________________________________________________________________
    // SCI_EnggMenu_OCB interface
public:
    /**
    * @brief	CEnggSM::enterEnggMenu is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering EnggMenu module
    * @param	void.
    * @return	void.
    **/
    void enterEnggMenu() override;
    /**
    * @brief	CEnggSM::exitEnggMenu is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting EnggMenu module
    * @param	void.
    * @return	void.
    **/
    void exitEnggMenu() override;
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggSM::enterTestMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering TestMode module
    * @param	void.
    * @return	void.
    **/
    void enterTestMode() override;
    /**
    * @brief	CEnggSM::exitTestMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting TestMode module
    * @param	void.
    * @return	void.
    **/
    void exitTestMode() override;
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggSM::enterIlluminationMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering IlluminationMode module
    * @param	void.
    * @return	void.
    **/
    void enterIlluminationMode() override;
    /**
    * @brief	CEnggSM::exitIlluminationMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting IlluminationMode module
    * @param	void.
    * @return	void.
    **/
    void exitIlluminationMode() override;
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggSM::enterButtonPanelMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering ButtonPanelMode module
    * @param	void.
    * @return	void.
    **/
    void enterButtonPanelMode() override;
    /**
    * @brief	CEnggSM::exitButtonPanelMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting ButtonPanelMode module
    * @param	void.
    * @return	void.
    **/
    void exitButtonPanelMode() override;
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggSM::enterDebugLogMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering DebugLogMode module
    * @param	void.
    * @return	void.
    **/
    void enterDebugLogMode() override;
    /**
    * @brief	CEnggSM::exitDebugLogMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting DebugLogMode module
    * @param	void.
    * @return	void.
    **/
    void exitDebugLogMode() override;
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggSM::enterSystemConfigMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering SystemConfigMode module
    * @param	void.
    * @return	void.
    **/
    void enterSystemConfigMode() override;
    /**
    * @brief	CEnggSM::exitSystemConfigMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting SystemConfigMode module
    * @param	void.
    * @return	void.
    **/
    void exitSystemConfigMode() override;
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggSM::enterDisplayIllumination is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering DisplayIllumination module
    * @param	void.
    * @return	void.
    **/
    void enterDisplayIllumination() override;
    /**
    * @brief	CEnggSM::exitDisplayIllumination is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting DisplayIllumination module
    * @param	void.
    * @return	void.
    **/
    void exitDisplayIllumination() override;
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggSM::enterButtonPanelIllumination is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering ButtonPanelIllumination module
    * @param	void.
    * @return	void.
    **/
    void enterButtonPanelIllumination() override;
    /**
    * @brief	CEnggSM::exitButtonPanelIllumination is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting ButtonPanelIllumination module
    * @param	void.
    * @return	void.
    **/
    void exitButtonPanelIllumination() override;
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggSM::enterVIN is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering VIN module
    * @param	void.
    * @return	void.
    **/
    void enterVIN() override;
    /**
    * @brief	CEnggSM::exitVIN is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting VIN module
    * @param	void.
    * @return	void.
    **/
    void exitVIN() override;
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggSM::enter16RPartNo is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering 16RPartNo module
    * @param	void.
    * @return	void.
    **/
    void enter16RPartNo() override;
    /**
    * @brief	CEnggSM::exit16RPartNo is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting 16RPartNo module
    * @param	void.
    * @return	void.
    **/
    void exit16RPartNo() override;
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggSM::enterDisplayHWPartNo is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering DisplayHWPartNo module
    * @param	void.
    * @return	void.
    **/
    void enterDisplayHWPartNo() override;
    /**
    * @brief	CEnggSM::exitDisplayHWPartNo is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting DisplayHWPartNo module
    * @param	void.
    * @return	void.
    **/
    void exitDisplayHWPartNo() override;
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggSM::enterButtonPanelPartNo is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering ButtonPanelPartNo module
    * @param	void.
    * @return	void.
    **/
    void enterButtonPanelPartNo() override;
    /**
    * @brief	CEnggSM::exitButtonPanelPartNo is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting ButtonPanelPartNo module
    * @param	void.
    * @return	void.
    **/
    void exitButtonPanelPartNo() override;
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggSM::enterPictureViewerMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering Picure Viewer mode.
    * @param	void.
    * @return	void.
    **/
    void enterPictureViewerMode() override;
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggSM::exitPictureViewerMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting  Picure Viewer mode.
    * @param	void.
    * @return	void.
    **/
    void exitPictureViewerMode() override;
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggSM::enterSoftwarePartNo is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering SoftwarePartNo module
    * @param	void.
    * @return	void.
    **/
    void enterSoftwarePartNo() override;
    /**
    * @brief	CEnggSM::exitSoftwarePartNo is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting SoftwarePartNo module
    * @param	void.
    * @return	void.
    **/
    void exitSoftwarePartNo() override;
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggSM::enterParameterPartNo is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering ParameterPartNo module
    * @param	void.
    * @return	void.
    **/
    void enterParameterPartNo() override;
    /**
    * @brief	CEnggSM::exitParameterPartNo is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting ParameterPartNo module
    * @param	void.
    * @return	void.
    **/
    void exitParameterPartNo() override;
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggSM::enterContainerPartNo is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering ContainerPartNo module
    * @param	void.
    * @return	void.
    **/
    void enterContainerPartNo() override;
    /**
    * @brief	CEnggSM::exitContainerPartNo is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting ContainerPartNo module
    * @param	void.
    * @return	void.
    **/
    void exitContainerPartNo() override;
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggSM::enterSilverBoxPartNo is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering SilverBoxPartNo module
    * @param	void.
    * @return	void.
    **/
    void enterSilverBoxPartNo() override;
    /**
    * @brief	CEnggSM::exitSilverBoxPartNo is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting SilverBoxPartNo module
    * @param	void.
    * @return	void.
    **/
    void exitSilverBoxPartNo() override;
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggSM::enterGPSCoordinates is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering GPSCoordinates module
    * @param	void.
    * @return	void.
    **/
    void enterGPSCoordinates() override;
    /**
    * @brief	CEnggSM::exitGPSCoordinates is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting GPSCoordinates module
    * @param	void.
    * @return	void.
    **/
    void exitGPSCoordinates() override;
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggSM::enterEnggMenuMain is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering EnggMenuMain module
    * @param	void.
    * @return	void.
    **/
    void enterEnggMenuMain() override;
    /**
    * @brief	CEnggSM::exitEnggMenuMain is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting EnggMenuMain module
    * @param	void.
    * @return	void.
    **/
    void exitEnggMenuMain() override;
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggSM::enterEnggDriveNextMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering EnggMenu DriveNext Main module
    * @param	void.
    * @return	void.
    **/
    void enterEnggDriveNextMode() override;

    /**
    * @brief	CEnggSM::exitEnggDriveNextMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting EnggMenu DriveNext Main module
    * @param	void.
    * @return	void.
    **/
    void exitEnggDriveNextMode() override;

    /**
    * @brief	CEnggSM::enterEnggDriveNextLibUpdateMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering EnggMenu DriveNext Lib Update module
    * @param	void.
    * @return	void.
    **/
    void enterEnggDriveNextLibUpdateMode() override;

    /**
    * @brief	CEnggSM::exitEnggDriveNextLibUpdateMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting EnggMenu DriveNext Lib Update module
    * @param	void.
    * @return	void.
    **/
    void exitEnggDriveNextLibUpdateMode() override;

    /**
    * @brief	CEnggSM::enterEnggDriveNextConfigUpdateMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering EnggMenu DriveNext Config Update module
    * @param	void.
    * @return	void.
    **/
    void enterEnggDriveNextConfigUpdateMode() override;

    /**
    * @brief	CEnggSM::exitEnggDriveNextConfigUpdateMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting EnggMenu DriveNext Config Update module
    * @param	void.
    * @return	void.
    **/
    void exitEnggDriveNextConfigUpdateMode() override;

    /**
    * @brief	CEnggSM::enterEnggDriveNextDebugMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering EnggMenu DriveNext Debug module
    * @param	void.
    * @return	void.
    **/
    void enterEnggDriveNextDebugMode() override;

    /**
    * @brief	CEnggSM::exitEnggDriveNextDebugMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting EnggMenu DriveNext Debug module
    * @param	void.
    * @return	void.
    **/
    void exitEnggDriveNextDebugMode() override;

    /**
    * @brief	CEnggSM::enterEnggDriveNextLogMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering EnggMenu DriveNext Log module
    * @param	void.
    * @return	void.
    **/
    void enterEnggDriveNextLogMode() override;

    /**
    * @brief	CEnggSM::exitEnggDriveNextLogMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting EnggMenu DriveNext Log module
    * @param	void.
    * @return	void.
    **/
    void exitEnggDriveNextLogMode() override;

    /**
    * @brief	CEnggSM::enterEnggDriveNextLoggingMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering EnggMenu DriveNext Logging module
    * @param	void.
    * @return	void.
    **/
    void enterEnggDriveNextLoggingMode() override;

    /**
    * @brief	CEnggSM::exitEnggDriveNextLoggingMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting EnggMenu DriveNext Logging module
    * @param	void.
    * @return	void.
    **/
    void exitEnggDriveNextLoggingMode() override;

    /**
    * @brief	CEnggSM::enterEnggDriveNextTripMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering EnggMenu DriveNext Trip module
    * @param	void.
    * @return	void.
    **/
    void enterEnggDriveNextTripMode() override;

    /**
    * @brief	CEnggSM::exitEnggDriveNextTripMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting EnggMenu DriveNext Trip module
    * @param	void.
    * @return	void.
    **/
    void exitEnggDriveNextTripMode() override;

    /**
    * @brief	CEnggSM::enterEnggDriveNextTripDetailsMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering EnggMenu DriveNext Trip Details module
    * @param	void.
    * @return	void.
    **/
    void enterEnggDriveNextTripDetailsMode() override;

    /**
    * @brief	CEnggSM::exitEnggDriveNextTripDetailsMode is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting EnggMenu DriveNext Trip Details module
    * @param	void.
    * @return	void.
    **/
    void exitEnggDriveNextTripDetailsMode() override;
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggSM::enterW3WLastNavigated is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for entering W3W Last Navigated screen
    * @param	void.
    * @return	void.
    **/
    void enterW3WLastNavigated() override;
    /**
    * @brief	CEnggSM::exitW3WLastNavigated is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for exiting W3W Last Navigated screen
    * @param	void.
    * @return	void.
    **/
    void exitW3WLastNavigated() override;
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggSM::handleButtonPanelHK is state machine class callback function inherited from SCI_EnggMenu_OCB
    * callback function from statemachine for handling HardKey events under Button Panel State
    * @param	void.
    * @return	void.
    **/
    void handleButtonPanelHK() override;
    //________________________________________________________________________________________________
private:
    /**
     * @brief m_objEnggApp: Reference for engg application class object
     */
    CEnggApplication& m_objEnggApp; //
};

#endif // CENGGSM_H
