/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CMaskedMouseArea.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* This file is having the definition of the Masked Mouse area component,
* Which can be used to create the mask mouse area for any image in qml, like the mouse
* event will be processed on image only not the extra transparent part of the image.
*/

#ifndef MASKEDMOUSEAREA_H
#define MASKEDMOUSEAREA_H

#include <QImage>
#include <QQuickItem>


/**
 * @brief The CMaskedMouseArea class: defines the Masked Mouse area component,
 * Which can be used to create the mask mouse area for any image in qml, like the mouse
 * event will be processed on image only not the extra transparent part of the image.
 */
class CMaskedMouseArea : public QQuickItem
{
    Q_OBJECT

    // property for pressed chnaged of mouse area.
    Q_PROPERTY(bool pressed READ isPressed NOTIFY pressedChanged)

    // property to know the area contains the mouse or not
    Q_PROPERTY(bool containsMouse READ containsMouse NOTIFY containsMouseChanged)

    // property to for mask source url.
    Q_PROPERTY(QUrl maskSource READ maskSource WRITE setMaskSource NOTIFY maskSourceChanged)

    // property to set alphaThreshold.
    Q_PROPERTY(qreal alphaThreshold READ alphaThreshold WRITE setAlphaThreshold NOTIFY alphaThresholdChanged)

public:
    CMaskedMouseArea(QQuickItem *pParent = 0);


    /**
     * @brief   contains: This function is used to know that the point is present
     *          in MouseArea or not. This is an overriden function.
     * @param   objPoint: point object which need to check.
     * @return  void.
     */
    bool contains(const QPointF &objPoint) const;


    /**
     * @brief   isPressed: Getter of property pressed.
     * @param   void.
     * @return  true if pressed, else false
     */
    bool isPressed() const { return m_bPressed; }

    /**
     * @brief   containsMouse: Getter of property containsMouse
     * @param   void.
     * @return  true if contains else false.
     */
    bool containsMouse() const { return m_bContainsMouse; }

    /**
     * @brief   maskSource: Getter of property maskSource.
     * @param   void.
     * @return  url of mask source.
     */
    QUrl maskSource() const { return m_objMaskSource; }

    /**
     * @brief   setMaskSource: setter of property maskSource.
     * @param   objQurl of mask source.
     * @return  void.
     */
    void setMaskSource(const QUrl &objQurl);

    /**
     * @brief   alphaThreshold: Getter of property alphaThreshold.
     * @param   void.
     * @return  alphaThreshold
     */
    qreal alphaThreshold() const { return m_dAlphaThreshold; }

    /**
     * @brief   setAlphaThreshold: Setter of property alphaThreshold.
     * @param   dThreshold.
     * @return  void.
     */
    void setAlphaThreshold(qreal dThreshold);

    /**
     * @brief   registerMaskedMouseAreaToQML: Method to regisetr Masked mouse area
     *          component to qml.
     * @param   void
     * @return  void
     */
    static void registerMaskedMouseAreaToQML()
    {
        qmlRegisterType<CMaskedMouseArea>("com.harman.qml.maskedMouseArea", 1, 0, "MaskedMouseArea");
    }

signals:
    /**
     * @brief   pressed: signal which is emitted when the mouse area is pressed.
     * @param   void.
     * @return  void.
     */
    void pressed();

    /**
     * @brief   released: signal which is emitted when the mouse area is released.
     * @param   void.
     * @return  void.
     */
    void released();

    /**
     * @brief   clicked: signal which is emitted when the mouse area is clicked.
     * @param   void.
     * @return  void.
     */
    void clicked();

    /**
     * @brief   canceled: signal which is emitted when the mouse area is canceled.
     * @param   void.
     * @return  void.
     */
    void canceled();

    /**
     * @brief   pressedChanged: signal which is emitted when the mouse area's pressed gets changed.
     * @param   void.
     * @return  void.
     */
    void pressedChanged();

    /**
     * @brief   maskSourceChanged: signal which is emitted when the mask source gets changed.
     * @param   void.
     * @return  void.
     */
    void maskSourceChanged();

    /**
     * @brief   containsMouseChanged: signal which is emitted when the contain mouse property
     *          gets changed.
     * @param   void.
     * @return  void.
     */
    void containsMouseChanged();

    /**
     * @brief   alphaThresholdChanged: signal which is emitted when the alphaThreshold property
     *          gets changed.
     * @param   void.
     * @return  void.
     */
    void alphaThresholdChanged();

protected:
    /**
     * @brief   setPressed: Setter for property pressed.
     * @param   bPressed: Value of pressed.
     * @return  void.
     */
    void setPressed(bool bPressed);

    /**
     * @brief   setContainsMouse: Setter for property containsMouse
     * @param   bContainsMouse: Value of containsMouse
     * @return  void.
     */
    void setContainsMouse(bool bContainsMouse);

    /**
     * @brief   mousePressEvent: This is the overidden function which is called
     *          when mouse press event occurs.
     * @param   pMouseEvent: Mouse event pointer.
     * @return  void.
     */
    void mousePressEvent(QMouseEvent *pMouseEvent);

    /**
     * @brief   mouseReleaseEvent: This is the overidden function which is called
     *          when mouse release event occurs.
     * @param   pMouseEvent: Mouse event.
     * @return  void.
     */
    void mouseReleaseEvent(QMouseEvent *pMouseEvent);

    /**
     * @brief   hoverEnterEvent: This is the overidden function which is called
     *          when mouse hover enter event occurs.
     * @param   pHoverEvent: Hover event.
     * @return  void.
     */
    void hoverEnterEvent(QHoverEvent *pHoverEvent);

    /**
     * @brief   hoverLeaveEvent: This is the overidden function which is called
     *          when mouse hover leave event occurs.
     * @param   pHoverEvent: Hover event.
     * @return  void.
     */
    void hoverLeaveEvent(QHoverEvent *pHoverEvent);

    /**
     * @brief   mouseUngrabEvent: This is the overidden function which is called
     *          when mouse ungrab event occurs.
     * @param   void.
     * @return  void.
     */
    void mouseUngrabEvent();

private:
    /**
     * @brief m_bPressed: Member variable to hold the status of Mouse Area pressed.
     */
    bool m_bPressed;

    /**
     * @brief m_objMaskSource: Member variable to hold the mask source.
     */
    QUrl m_objMaskSource;

    /**
     * @brief m_objMaskImage: Mask image object.
     */
    QImage m_objMaskImage;

    /**
     * @brief m_objPressPoint: Variable to hold the press point object.
     */
    QPointF m_objPressPoint;

    /**
     * @brief m_dAlphaThreshold: Variable to hold the value of alpha thres hold.
     */
    qreal m_dAlphaThreshold;

    /**
     * @brief m_bContainsMouse: Variable to hold the value of contins mouse.
     */
    bool m_bContainsMouse;
};

#endif
