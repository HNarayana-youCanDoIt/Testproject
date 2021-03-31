#ifndef CICCASTENUM_H
#define CICCASTENUM_H

/**
 * @brief The EICRenderPhoneCallState enum: This enum contains all the possible phone call
 * states that shall be passed to IC render service
 */
enum EICRenderPhoneCallState
{
    EN_ICRENDER_STATE_NO_PHONE_CALL,
    EN_ICRENDER_STATE_INCOMING_CALL,
    EN_ICRENDER_STATE_OUTGOING_CALL,
    EN_ICRENDER_STATE_ACTIVE_CALL,
    EN_ICRENDER_STATE_ACTIVE_CONF_CALL,
    EN_ICRENDER_STATE_CALL_ONHOLD,
    EN_ICRENDER_STATE_CALL_ENDED,
    EN_ICRENDER_STATE_INVALID_CALL_STATE
};

/**
 * @enum EICCastFeature
 * @brief Enum for IC Cast Component that needs to be casted.
 */
enum EICCastFeature
{
    ICRENDER_CAST_MASTER = 1,
    ICRENDER_CAST_RADIO = 2,
    ICRENDER_CAST_MEDIA = 3,
};

#endif // CICCASTENUM_H
