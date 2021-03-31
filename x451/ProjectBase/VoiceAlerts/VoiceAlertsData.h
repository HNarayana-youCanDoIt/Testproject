#ifndef VOICEALERTSDATA_H
#define VOICEALERTSDATA_H
#include "VoiceAlertsEnum.h"

#include <QObject>
#include <QtQml>

/**
 * @brief The CVoiceAlertsData class to store the data requried for displaying
 *        a voice alert.
 */
class CDataVoiceAert
{
public:
    /**Id of the voice alert **/
    CVoiceAlertsEnums::EVoiceAlerts m_eId;
    /**state of the voice alert **/
    CVoiceAlertsEnums::EVoiceAlertsState m_eState;
    /**Message to be displeyed during voice alert **/
    QString m_strMsg;
    
    CDataVoiceAert()
        :m_eId(CVoiceAlertsEnums::EN_VA_NOALERT),
          m_eState(CVoiceAlertsEnums::EN_VA_STATE_NO_ALERT),
          m_strMsg("")
    {

    }

    void reset()
    {
        m_eId = CVoiceAlertsEnums::EN_VA_NOALERT;
        m_eState = CVoiceAlertsEnums::EN_VA_STATE_NO_ALERT;
        m_strMsg = "";
    }
};

/**
 * @brief The CDataMceVoiceAert class to store the data requried for displaying
 *        a Mce voice alert.
 */
class CDataMceVoiceAert
{
public:
    /**Id of the voice alert **/
    CVoiceAlertsEnums::EMceVoiceAlerts m_eId;
    /**state of the voice alert **/
    CVoiceAlertsEnums::EVoiceAlertsState m_eState;
    /**Message to be displeyed during voice alert **/
    QString m_strMsg;

    CDataMceVoiceAert()
        :m_eId(CVoiceAlertsEnums::EN_MCE_VA_NOALERT),
          m_eState(CVoiceAlertsEnums::EN_VA_STATE_NO_ALERT),
          m_strMsg("")
    {

    }

    void reset()
    {
        m_eId = CVoiceAlertsEnums::EN_MCE_VA_NOALERT;
        m_eState = CVoiceAlertsEnums::EN_VA_STATE_NO_ALERT;
        m_strMsg = "";
    }
};

#endif // VOICEALERTSDATA_H
