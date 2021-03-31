/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CVariantControlEventHandler.h
* @ingroup      HMIComponent
* @author       Manali Patil
* @class        CVariantControlEventHandler: Class has the slots for all the Signals sent by CVariantControlEventHandler
*                                   which informs VariantControl Adaptor about VariantControl Resource Events
*/

#ifndef CVARIANTCONTROLEVENTHANDLER_H
#define CVARIANTCONTROLEVENTHANDLER_H

#include <QObject>

class CVariantControlAdaptor;

/**
 * @brief The CVariantControlEventHandler class: This class is to handle VariantControl events.
 *          VariantControl resource event provider will emit signals and those will be handled here.
 */
class CVariantControlEventHandler : public QObject
{
    Q_OBJECT
public:

    /**
    * @brief	CVariantControlEventHandler - Constructor for event handler class CVariantControlEventHandler
    * @param	pParent: parent class pointer.
    * @return	void.
    **/
    explicit CVariantControlEventHandler(QObject *pParent = nullptr);

    /**
    * @brief	~CVariantControlEventHandler - Destructor for event handler class CVariantControlEventHandler
    * @param	void.
    * @return	void.
    **/
    ~CVariantControlEventHandler();

public slots:

    /**
    * @brief	sltAntennaTypeReceived: This method will inform Am/Fm Antenna type to Variant Control adaptor .
    * @param	iAntennaType: Antenna type status
    * @return	void
    */
    void sltAntennaTypeReceived(int iAntennaType);

    /**
    * @brief	sltEolAndroidAutoChangeReceived: This method will inform Changed eol value for AndroidAuto to Variant Control adaptor .
    * @param    bEolAndroidAutoStatus: status of Android Auto.
    * @return	void
    */
    void sltEolAndroidAutoChangeReceived(bool bEolAndroidAutoStatus);

    /**
    * @brief	sltEolAppleCarPlayChangeReceived: This method will inform Changed eol value for AppleCarPlay to Variant Control adaptor .
    * @param    bEolAppleCarPlayStatus: status of Apple carplay.
    * @return	void
    */
    void sltEolAppleCarPlayChangeReceived(bool bEolAppleCarPlayStatus);

    /**
    * @brief	sltEolDriveModeStatusReceived: This method will inform Changed eol value for drive mode status data to Variant Control adaptor .
    * @param    iEolDriveModeStatusOne: status of drive modes.
    * @return	void
    */
    void sltEolDriveModeStatusReceived(int iEolDriveModeStatus);

    /**
    * @brief	sltEolICCastEnabledStatusReceived: This method will inform Changed eol value for IC cast enabled status to Variant Control adaptor .
    * @param    iEolICCastEnabledStatus: enabled status of IC cast.
    * @return	void
    */
    void sltEolICCastEnabledStatusReceived(int iEolICCastEnabledStatus);
    
    /**
     * @brief sltEOLSensorCountUpdate: Slot to receive the updates in sensor count and to pass on this message to VariantControl adaptor.
     * @param iSensorCount: No. of PDC sensor available in the vehicle.
     * @return void
     */
    void sltEOLSensorCountUpdate(int iSensorCount);

    /**
     * @brief sltEOLVIP_DIDUpdate: Slot to receive the updates in VIP DID and to pass on this message to VariantControl adaptor.
     * @param iVIP_DID, vehicle infotaiment platform information
     * @return void
     */
    void sltEOLVIP_DIDUpdate(int iVIP_DID);

    /**
     * @brief sltEOLAppsDIDUpdate: Slot to receive the updates in Apps DID and to pass on this message to VariantControl adaptor.
     * @param iAppsDID, Apps / features disable enable information
     * @return void
     */
    void sltEOLAppsDIDUpdate(int iAppsDID);

private:
    /**
    * @brief	connectSignals: This function will connect signals and slots
    * @param	void
    * @return	void
    */
    void connectSignals();
};

#endif // CVARIANTCONTROLEVENTHANDLER_H
