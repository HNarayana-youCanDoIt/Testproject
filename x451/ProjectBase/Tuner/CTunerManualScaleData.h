/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
* @file          CTunerManualScaleData.h.h
* @ingroup       HMIComponent
* @author        Rahul Balyan
* CTunerManualScaleData,  Data structure for CTunerManualScaleListModel
**/

#ifndef CTUNERMANUALSCALEDATA_H
#define CTUNERMANUALSCALEDATA_H

#include <QObject>

/**
 * @brief The SManualTuningScaleData structure
 * This structure is template to QList in CTunerManualScaleListModel.
**/
struct SManualTuningScaleData
{
    SManualTuningScaleData()
    {
        m_iScaleIndexHeight = 0;
        m_iScaleIndexFreqValue = -1;
    }
    int m_iScaleIndexHeight;
    int m_iScaleIndexFreqValue;
};

#endif // CTUNERMANUALSCALEDATA_H
