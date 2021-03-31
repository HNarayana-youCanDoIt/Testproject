#include "CDClockInformation.h"
#include "logging.h"

CDClockInformation::CDClockInformation(int _uId, CClockEnum::EClockLayoutTypes _layoutType, CClockEnum::EClockMotionTypes _motionType,
                                       QString _imageDial, QString _imageCenter, QString _imageCenterShadow,
                                       QString _imageHrHand, QString _imageHrHandShadow,
                                       QString _imageMinHand, QString _imageMinHandShadow,
                                       QString _imageSecHand, QString _imageSecHandShadow,
                                       QObject *parent) : QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s", __FUNCTION__);
    setUId(_uId);
    setLayoutType(_layoutType);
    setMotionType(_motionType);
    setImageDial(_imageDial);
    setImageCenter(_imageCenter);
    setImageCenterShadow(_imageCenterShadow);
    setImageHrHand(_imageHrHand);
    setImageHrHandShadow(_imageHrHandShadow);
    setImageMinHand(_imageMinHand);
    setImageMinHandShadow(_imageMinHandShadow);
    setImageSecHand(_imageSecHand);
    setImageSecHandShadow(_imageSecHandShadow);
}

CDClockInformation::~CDClockInformation()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s", __FUNCTION__);
}

int CDClockInformation::uId()
{
    return m_iUId;
}

void CDClockInformation::setUId(int _uid)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, %d", __FUNCTION__, _uid);
    if (_uid != m_iUId)
    {
        m_iUId = _uid;
        emit sigUIdChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, No change in value", __FUNCTION__);
    }
}

QString CDClockInformation::layout()
{
    QString strLayout = "";
    switch (m_eLayoutType)
    {
    case CClockEnum::LAYOUT_ANALOG:
    {
        strLayout = "qrc:/QML/MediaOff/X445/CmpClockAnalog.qml";
    }
        break;
    case CClockEnum::LAYOUT_DIGITAL:
    {
        strLayout = "qrc:/QML/MediaOff/X445/CmpClockDigital.qml";
    }
        break;
    default:
    {
        ////Do Nothing
    }
        break;
    }
    return strLayout;
}

int CDClockInformation::layoutType()
{
    return m_eLayoutType;
}

void CDClockInformation::setLayoutType(CClockEnum::EClockLayoutTypes _layoutType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, %d", __FUNCTION__, static_cast<int>(_layoutType));
    if (_layoutType != m_eLayoutType)
    {
        m_eLayoutType = _layoutType;
        emit sigLayoutTypeChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, No change in value", __FUNCTION__);
    }
}

int CDClockInformation::motionType()
{
    return m_eMotionType;
}

void CDClockInformation::setMotionType(CClockEnum::EClockMotionTypes _motionType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, %d", __FUNCTION__, static_cast<int>(_motionType));
    if (_motionType != m_eMotionType)
    {
        m_eMotionType = _motionType;
        emit sigMotionTypeChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, No change in value", __FUNCTION__);
    }
}

QString CDClockInformation::imageDial()
{
    return m_strImageDial;
}

void CDClockInformation::setImageDial(QString _imageDial)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, %s", __FUNCTION__, _imageDial.toStdString().data());
    if (_imageDial != m_strImageDial)
    {
        m_strImageDial = _imageDial;
        emit sigImageDialChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, No change in value", __FUNCTION__);
    }
}

QString CDClockInformation::imageCenter()
{
    return m_strImageCenter;
}

void CDClockInformation::setImageCenter(QString _imageCenter)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, %s", __FUNCTION__, _imageCenter.toStdString().data());
    if (_imageCenter != m_strImageCenter)
    {
        m_strImageCenter = _imageCenter;
        emit sigImageCenterChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, No change in value", __FUNCTION__);
    }
}

QString CDClockInformation::imageCenterShadow()
{
    return m_strImageCenterShadow;
}

void CDClockInformation::setImageCenterShadow(QString _imageCenterShadow)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, %s", __FUNCTION__, _imageCenterShadow.toStdString().data());
    if (_imageCenterShadow != m_strImageCenterShadow)
    {
        m_strImageCenterShadow = _imageCenterShadow;
        emit sigImageCenterShadowChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, No change in value", __FUNCTION__);
    }
}

QString CDClockInformation::imageHrHand()
{
    return m_strImageHrHand;
}

void CDClockInformation::setImageHrHand(QString _imageHrHand)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, %s", __FUNCTION__, _imageHrHand.toStdString().data());
    if (_imageHrHand != m_strImageHrHand)
    {
        m_strImageHrHand = _imageHrHand;
        emit sigImageHrHandChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, No change in value", __FUNCTION__);
    }
}

QString CDClockInformation::imageHrHandShadow()
{
    return m_strImageHrHandShadow;
}

void CDClockInformation::setImageHrHandShadow(QString _imageHrHandShadow)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, %s", __FUNCTION__, _imageHrHandShadow.toStdString().data());
    if (_imageHrHandShadow != m_strImageHrHandShadow)
    {
        m_strImageHrHandShadow = _imageHrHandShadow;
        emit sigImageHrHandShadowChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, No change in value", __FUNCTION__);
    }
}

QString CDClockInformation::imageMinHand()
{
    return m_strImageMinHand;
}

void CDClockInformation::setImageMinHand(QString _imageMinHand)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, %s", __FUNCTION__, _imageMinHand.toStdString().data());
    if (_imageMinHand != m_strImageMinHand)
    {
        m_strImageMinHand = _imageMinHand;
        emit sigImageMinHandChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, No change in value", __FUNCTION__);
    }
}

QString CDClockInformation::imageMinHandShadow()
{
    return m_strImageMinHandShadow;
}

void CDClockInformation::setImageMinHandShadow(QString _imageMinHandShadow)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, %s", __FUNCTION__, _imageMinHandShadow.toStdString().data());
    if (_imageMinHandShadow != m_strImageMinHandShadow)
    {
        m_strImageMinHandShadow = _imageMinHandShadow;
        emit sigImageMinHandShadowChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, No change in value", __FUNCTION__);
    }
}

QString CDClockInformation::imageSecHand()
{
    return m_strImageSecHand;
}

void CDClockInformation::setImageSecHand(QString _imageSecHand)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, %s", __FUNCTION__, _imageSecHand.toStdString().data());
    if (_imageSecHand != m_strImageSecHand)
    {
        m_strImageSecHand = _imageSecHand;
        emit sigImageSecHandChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, No change in value", __FUNCTION__);
    }
}

QString CDClockInformation::imageSecHandShadow()
{
    return m_strImageSecHandShadow;
}

void CDClockInformation::setImageSecHandShadow(QString _imageSecHandShadow)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, %s", __FUNCTION__, _imageSecHandShadow.toStdString().data());
    if (_imageSecHandShadow != m_strImageSecHandShadow)
    {
        m_strImageSecHandShadow = _imageSecHandShadow;
        emit sigImageSecHandShadowChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s, No change in value", __FUNCTION__);
    }
}
