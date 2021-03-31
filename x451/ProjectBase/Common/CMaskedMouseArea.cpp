/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CMaskedMouseArea.cpp
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* This file is having the definition of the Masked Mouse area component,
* Which can be used to create the mask mouse area for any image in qml, like the mouse
* event will be processed on image only not the extra transparent part of the image.
*/

#include "CMaskedMouseArea.h"

#include <QStyleHints>
#include <QGuiApplication>
#include <qqmlfile.h>

CMaskedMouseArea::CMaskedMouseArea(QQuickItem *pParent)
    : QQuickItem(pParent),
      m_bPressed(false),
      m_dAlphaThreshold(0.0),
      m_bContainsMouse(false)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
}

void CMaskedMouseArea::setPressed(bool bPressed)
{
    if (m_bPressed != bPressed)
    {
        m_bPressed = bPressed;
        emit pressedChanged();
    }
}

void CMaskedMouseArea::setContainsMouse(bool bContainsMouse)
{
    if (m_bContainsMouse != bContainsMouse)
    {
        m_bContainsMouse = bContainsMouse;
        emit containsMouseChanged();
    }
}

void CMaskedMouseArea::setMaskSource(const QUrl &objQurl)
{
    if (m_objMaskSource != objQurl)
    {
        m_objMaskSource = objQurl;
        m_objMaskImage = QImage(QQmlFile::urlToLocalFileOrQrc(objQurl));
        emit maskSourceChanged();
    }
}

void CMaskedMouseArea::setAlphaThreshold(qreal dThreshold)
{
    if (m_dAlphaThreshold != dThreshold)
    {
        m_dAlphaThreshold = dThreshold;
        emit alphaThresholdChanged();
    }
}

bool CMaskedMouseArea::contains(const QPointF &objPoint) const
{
    if (!QQuickItem::contains(objPoint) || m_objMaskImage.isNull())
        return false;

    QPoint objQPoint = objPoint.toPoint();

    if (objQPoint.x() < 0 || objQPoint.x() >= m_objMaskImage.width() ||
            objQPoint.y() < 0 || objQPoint.y() >= m_objMaskImage.height())
        return false;

    qreal dBoundedValue = qBound<int>(0, m_dAlphaThreshold * 255, 255);
    return qAlpha(m_objMaskImage.pixel(objQPoint)) > dBoundedValue;
}

void CMaskedMouseArea::mousePressEvent(QMouseEvent *pMouseEvent)
{
    setPressed(true);
    m_objPressPoint = pMouseEvent->pos();
    emit pressed();
}

void CMaskedMouseArea::mouseReleaseEvent(QMouseEvent *pMouseEvent)
{
    setPressed(false);
    emit released();

    const int iThreshold = qApp->styleHints()->startDragDistance();
    const bool bIsClick = (iThreshold >= qAbs(pMouseEvent->x() - m_objPressPoint.x()) &&
                           iThreshold >= qAbs(pMouseEvent->y() - m_objPressPoint.y()));

    if (bIsClick)
        emit clicked();
}

void CMaskedMouseArea::mouseUngrabEvent()
{
    setPressed(false);
    emit canceled();
}

void CMaskedMouseArea::hoverEnterEvent(QHoverEvent *pHoverEvent)
{
    Q_UNUSED(pHoverEvent);
    setContainsMouse(true);
}

void CMaskedMouseArea::hoverLeaveEvent(QHoverEvent *pHoverEvent)
{
    Q_UNUSED(pHoverEvent);
    setContainsMouse(false);
}
