/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2019
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CDynamicMaskedMouseArea.h
* @ingroup      HMIComponent
* @author       Nandkishor Lokhande
* This file is having the definition of the Dynamic Masked Mouse area component,
* Which can be used to create the mask mouse area for any image in qml, like the mouse
* event will be processed on image only not the extra transparent part of the image.
*/

#ifndef CDYNAMICMASKEDMOUSEAREA_H
#define CDYNAMICMASKEDMOUSEAREA_H

#include <QImage>
#include <QQuickItem>

/**
 * @brief The CDynamicMaskedMouseArea class: defines the Dynamic Masked Mouse area component,
 * Which can be used to create the mask mouse area for any image in qml, like the mouse
 * event will be processed on image only not the extra transparent part of the image.
 */
class CDynamicMaskedMouseArea : public QQuickItem
{
    Q_OBJECT

    // property for pressed chnaged of mouse area.
    Q_PROPERTY(bool pressed READ isPressed NOTIFY pressedChanged)

    // property to know the area contains the mouse or not
    Q_PROPERTY(bool containsMouse READ containsMouse NOTIFY containsMouseChanged)

    // property to for mask source url.
    Q_PROPERTY(QUrl maskSource READ maskSource WRITE setMaskSource NOTIFY maskSourceChanged)

    // property to for mask position.
    Q_PROPERTY(int maskPositionX READ maskPositionX WRITE setMaskPositionX NOTIFY maskPositionChanged)

    // property to for mask position.
    Q_PROPERTY(int maskPositionY READ maskPositionY WRITE setMaskPositionY NOTIFY maskPositionChanged)

    // property to set alphaThreshold.
    Q_PROPERTY(qreal alphaThreshold READ alphaThreshold WRITE setAlphaThreshold NOTIFY alphaThresholdChanged)

    // property to set invertArea touch handle.
    Q_PROPERTY(bool invertArea READ invertArea WRITE setInvertArea NOTIFY invertAreaChanged)

public:
    CDynamicMaskedMouseArea(QQuickItem *pParent = 0);
    ~CDynamicMaskedMouseArea();

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
     * @brief   maskPositionX: Getter of property maskPositionX.
     * @param   void.
     * @return  mask Position X.
     */
    int maskPositionX() const { return m_objMaskPosition.x(); }

    /**
     * @brief   setMaskPositionX: setter of property maskPositionX.
     * @param   mask Position X.
     * @return  void.
     */
    void setMaskPositionX(const int iX);

    /**
     * @brief   maskPositionY: Getter of property maskPositionY.
     * @param   void.
     * @return  mask Position Y.
     */
    int maskPositionY() const { return m_objMaskPosition.y(); }

    /**
     * @brief   setMaskPositionY: setter of property maskPositionY.
     * @param   mask Position Y.
     * @return  void.
     */
    void setMaskPositionY(const int iY);

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
     * @brief   invertArea: Getter of property invertArea.
     * @param   void.
     * @return  bool invertArea
     */
    bool invertArea() const { return m_bInvertArea; }

    /**
     * @brief   setInvertArea: Setter of property invertArea.
     * @param   bool bInvertArea.
     * @return  void.
     */
    void setInvertArea(bool bInvertArea);

    /**
     * @brief   registerDynamicMaskedMouseAreaToQML: Method to regisetr Masked mouse drag area
     *          component to qml.
     * @param   void
     * @return  void
     */
    static void registerDynamicMaskedMouseAreaToQML()
    {
        qmlRegisterType<CDynamicMaskedMouseArea>("com.harman.qml.dynamicMaskedMouseArea", 1, 0, "DynamicMaskedMouseArea");
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
     * @brief   maskPositionChanged: signal which is emitted when the mask Position gets changed.
     * @param   void.
     * @return  void.
     */
    void maskPositionChanged();

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

    /**
     * @brief   invertAreaChanged: signal which is emitted when the invertArea property
     *          gets changed.
     * @param   void.
     * @return  void.
     */
    void invertAreaChanged();

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
    void mousePressEvent(QMouseEvent *pMouseEvent) override;

    /**
     * @brief   mouseReleaseEvent: This is the overidden function which is called
     *          when mouse release event occurs.
     * @param   pMouseEvent: Mouse event.
     * @return  void.
     */
    void mouseReleaseEvent(QMouseEvent *pMouseEvent) override;

    /**
     * @brief   hoverEnterEvent: This is the overidden function which is called
     *          when mouse hover enter event occurs.
     * @param   pHoverEvent: Hover event.
     * @return  void.
     */
    void hoverEnterEvent(QHoverEvent *pHoverEvent) override;

    /**
     * @brief   hoverLeaveEvent: This is the overidden function which is called
     *          when mouse hover leave event occurs.
     * @param   pHoverEvent: Hover event.
     * @return  void.
     */
    void hoverLeaveEvent(QHoverEvent *pHoverEvent) override;

    /**
     * @brief   mouseUngrabEvent: This is the overidden function which is called
     *          when mouse ungrab event occurs.
     * @param   void.
     * @return  void.
     */
    void mouseUngrabEvent() override;

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
     * @brief m_objMaskPosition: Member variable to hold the mask Position.
     */
    QPoint m_objMaskPosition;

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

    /**
     * @brief m_bInvertArea: Variable to hold the value of invert area touch handle.
     */
    bool m_bInvertArea;
};

#endif // CDYNAMICMASKEDMOUSEAREA_H
