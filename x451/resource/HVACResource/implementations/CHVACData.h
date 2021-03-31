
/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CHVACData.h
* @ingroup      HMIComponent
* @author       Gaurav Garg
* CHVACDATA, Structure for CHVACDATA
*/

#ifndef CHVACDATA_H
#define CHVACDATA_H

/**
 * @brief SHVACParamValues Structure to store all the values related to HVAC received from service
 * @type struct
 */

struct SHVACParamValues
{
            bool bCcmAirconCtrl;
            bool bCcmEconMode;
            bool bCcmAutoMode;
            bool bCcmHVACCtrl;
            bool bCcmMaxDefrst;
            int  iCcmFreshairRecirc;
            int  iCcmDistribMode;
            int  iCcmTemPass;
            int  iCcmTempDrvr;
            int  iCcmFanSpeed;
            bool bCcmDualMode;
            int  iCcmTempChange;
            bool bCccmRearDefog;
            bool bCcmErrStatus;
            int  iCcmVariantType;
            bool bCcmPresence;
            int  iCcmPresence;
            int  iCcmSwitchStuckwarn;
            int  iCcmLowfanspdConfig;
            int  iCcmHifanspdConfig;
            int  iCcmLowtempConfig;
            int  iCcmHitempConfig;
            int  iCcmEconConfig;
            int  iCcmExpCoolConfig;
            bool bCcmExpCoolStatus;
            int  iCcmPassengerTemprature;
            int  iCcmDriverTemprature;
            int  iVariantType;
};


#endif // CHVACDATA_H



