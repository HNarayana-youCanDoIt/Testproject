/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2019
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CDynamicMaskedMouseArea.cpp
* @ingroup      HMIComponent
* @author       Nandkishor Lokhande
* This file is having the definition of the Dynamic Masked Mouse area component,
* Which can be used to create the mask mouse area for any image in qml, like the mouse
* event will be processed on image only not the extra transparent part of the image.
*/

#include "CDynamicMaskedMouseArea.h"

#include <QStyleHints>
#include <QGuiApplication>
#include <qqmlfile.h>

#include "logging.h"

CDynamicMaskedMouseArea::CDynamicMaskedMouseArea(QQuickItem *pParent)
    : QQuickItem(pParent),
      m_bPressed(false),
      m_dAlphaThreshold(0.0),
      m_bContainsMouse(false),
      m_bInvertArea(false)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
}

CDynamicMaskedMouseArea::~CDynamicMaskedMouseArea()
{
}

void CDynamicMaskedMouseArea::setPressed(bool bPressed)
{
    if (m_bPressed != bPressed)
    {
        m_bPressed = bPressed;
        emit pressedChanged();
    }
}

void CDynamicMaskedMouseArea::setContainsMouse(bool bContainsMouse)
{
    if (m_bContainsMouse != bContainsMouse)
    {
        m_bContainsMouse = bContainsMouse;
        emit containsMouseChanged();
    }
}

void CDynamicMaskedMouseArea::setMaskSource(const QUrl &objQurl)
{
    if (m_objMaskSource != objQurl)
    {
        m_objMaskSource = objQurl;
        m_objMaskImage = QImage(QQmlFile::urlToLocalFileOrQrc(objQurl));
        emit maskSourceChanged();
    }
}

void CDynamicMaskedMouseArea::setMaskPositionX(const int iX)
{
    m_objMaskPosition.setX(iX);
    emit maskPositionChanged();
}

void CDynamicMaskedMouseArea::setMaskPositionY(const int iY)
{
    m_objMaskPosition.setY(iY);
    emit maskPositionChanged();
}

void CDynamicMaskedMouseArea::setAlphaThreshold(qreal dThreshold)
{
    if (m_dAlphaThreshold != dThreshold)
    {
        m_dAlphaThreshold = dThreshold;
        emit alphaThresholdChanged();
    }
}

void CDynamicMaskedMouseArea::setInvertArea(bool bInvertArea)
{
    if (m_bInvertArea != bInvertArea)
    {
        m_bInvertArea = bInvertArea;
        emit invertAreaChanged();
    }
}

bool CDynamicMaskedMouseArea::contains(const QPointF &objPoint) const
{
    bool bValidTouchPosition = false;

    //Look if mask image in m_objMaskImage is available or not
    if(!m_objMaskImage.isNull())
    {
        //Look if QQuickItem contains given point inside it ot not
        if (QQuickItem::contains(objPoint))
        {
            //Convert given point to relative point inside mask
            QPoint objQPoint = objPoint.toPoint() - m_objMaskPosition;
            //Create alpha bonded value to handle touch for relative point.
            qreal dBoundedValue = qBound<int>(0, m_dAlphaThreshold * 255, 255);

            //Look if flow is in invert area or not
            if (invertArea())
            {
                //As flow is in invert area handle touch for relative point
                //look if point is inside image or not
                if ((objQPoint.x() >= 0) && (objQPoint.x() < m_objMaskImage.width()) && (objQPoint.y() >= 0) && (objQPoint.y() < m_objMaskImage.height()))
                {
                    //As point is inside of image
                    //look if point have alpha bonded value below difened range.
                    bValidTouchPosition = (qAlpha(m_objMaskImage.pixel(objQPoint)) < dBoundedValue);
                    //LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, Inside Mask Image Inverted %d", __FUNCTION__, bValidTouchPosition);
                }
                else
                {
                    //As point is outside of image
                    //Handle invert touch
                    bValidTouchPosition = true;
                    //LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, Outside Mask Image Inverted %d", __FUNCTION__, bValidTouchPosition);
                }
            }
            else
            {
                //As flow is not in invert area handle touch for relative point
                if ((objQPoint.x() >= 0) && (objQPoint.x() < m_objMaskImage.width()) && (objQPoint.y() >= 0) && (objQPoint.y() < m_objMaskImage.height()))
                {
                    //As point is inside of image
                    //look if point have alpha bonded value above difened range.
                    bValidTouchPosition = (qAlpha(m_objMaskImage.pixel(objQPoint)) > dBoundedValue);
                    //LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, Inside Mask Image %d", __FUNCTION__, bValidTouchPosition);
                }
                else
                {
                    //As point is outside of image
                    //ignore touch
                    //LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, Outside Mask Image %d", __FUNCTION__, bValidTouchPosition);
                }
            }
        }
        else
        {
            //LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, Outside Of Touch Area Defined %d", __FUNCTION__, bValidTouchPosition);
        }
    }
    else
    {
        //LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, No Mask Image Defined %d", __FUNCTION__, bValidTouchPosition);
    }

    //return touch status
    return bValidTouchPosition;
}

void CDynamicMaskedMouseArea::mousePressEvent(QMouseEvent *pMouseEvent)
{
    setPressed(true);
    m_objPressPoint = pMouseEvent->pos();
    emit pressed();
}

void CDynamicMaskedMouseArea::mouseReleaseEvent(QMouseEvent *pMouseEvent)
{
    setPressed(false);
    emit released();

    const int iThreshold = qApp->styleHints()->startDragDistance();
    const bool bIsClick = (iThreshold >= qAbs(pMouseEvent->x() - m_objPressPoint.x()) &&
                           iThreshold >= qAbs(pMouseEvent->y() - m_objPressPoint.y()));

    if (bIsClick)
    {
        emit clicked();
    }
}

void CDynamicMaskedMouseArea::mouseUngrabEvent()
{
    setPressed(false);
    emit canceled();
}

void CDynamicMaskedMouseArea::hoverEnterEvent(QHoverEvent *pHoverEvent)
{
    Q_UNUSED(pHoverEvent);
    setContainsMouse(true);
}

void CDynamicMaskedMouseArea::hoverLeaveEvent(QHoverEvent *pHoverEvent)
{
    Q_UNUSED(pHoverEvent);
    setContainsMouse(false);
}
