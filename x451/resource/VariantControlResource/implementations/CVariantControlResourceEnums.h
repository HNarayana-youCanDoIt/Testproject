/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CVariantControlResourceEnums.h
 * @ingroup         HMIComponent
 * @author          Rajat Gupta
 * CVariantControlResourceEnum, file that contain enums that will be used in VariantControl.
 */

#ifndef CVARIANTCONTROLRESOURCEENUMS_H
#define CVARIANTCONTROLRESOURCEENUMS_H

/**
 * Enum for different vehicle infotainment platforms
 */
enum EVehicleInfotainmentPlatform
{
    VIP_DID_HU_LCIS = 0,
    VIP_DID_HU_TIAGO_7INCH = 1,
    VIP_DID_HU_HEXA_7_VAVE = 2,
    VIP_DID_HU_NEXON_EV_LEVEL_A_VAVE = 3,
    VIP_DID_HU_NEXON_LEVEL_B_VAVE = 4,
    VIP_DID_HU_MID_X451 = 5,
    VIP_DID_HU_HIGH_X451 = 6,
    VIP_DID_HU_MID_X445 = 7,
    VIP_DID_HU_HIGH_X445 = 8,
    VIP_DID_HU_NEXON_EV_MID = 9,
    VIP_DID_HU_NEXON_EV_HIGH = 10,
    VIP_DID_HU_TIGOR_7 = 11,
    VIP_DID_HU_NEXON_MCE = 12
};

#endif // CVARIANTCONTROLRESOURCEENUMS_H
