/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file            CDoodleSetupListElement.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDoodleSetupListElement, class to hold doodle setup element data information
 */
//________________________________________________________________________________________________

#ifndef CDOODLESETUPLISTELEMENT_H
#define CDOODLESETUPLISTELEMENT_H

#include <QObject>
#include <QString>

#include "CDoodleEnum.h"

/*!
 * @struct  CDoodleSetupListElement
 * @brief   This class shall hold element information for doodle setup list
 */
class CDoodleSetupListElement : public QObject
{
    Q_OBJECT
    //________________________________________________________________________________________________
    // Q Properties //

    //// To get the doodle setup element type.
    Q_PROPERTY(bool type READ type NOTIFY sigTypeChanged)

    //// To get the doodle setup element Name text.
    Q_PROPERTY(QString name READ name NOTIFY sigNameChanged)

    //// To get the doodle setup element enabled state.
    Q_PROPERTY(bool enabled READ enabled NOTIFY sigEnabledChanged)

    //// To get the doodle setup element toggle status.
    Q_PROPERTY(bool toggleStatus READ toggleStatus NOTIFY sigToggleStatusChanged)
    //________________________________________________________________________________________________

public:

    /**
    * @brief    CDoodleSetupListElement constructor for class CDoodleSetupListElement.
    * @param    QObject.
    * @return   NA.
    **/
    CDoodleSetupListElement(QObject *parent = nullptr);
    //________________________________________________________________________________________________
    /**
    * @brief    ~CDoodleSetupListElement is destructor of class CDoodleSetupListElement.
    * @param    NA.
    * @return   NA.
    **/
    ~CDoodleSetupListElement();
    //________________________________________________________________________________________________
    /**
    * @brief    type is get function for "type" property.
    * @param    void.
    * @return   CDoodleEnum::EDoodleSetupElementTypes element type.
    **/
    CDoodleEnum::EDoodleSetupElementTypes type();
    //________________________________________________________________________________________________
    /**
    * @brief    setType is set function for "type" property.
    * @param    CDoodleEnum::EDoodleSetupElementTypes element type.
    * @return   void.
    **/
    void setType(CDoodleEnum::EDoodleSetupElementTypes eElementType);
    //________________________________________________________________________________________________
    /**
    * @brief    name is get function for "name" property.
    * @param    void.
    * @return   QString name text.
    **/
    QString name();
    //________________________________________________________________________________________________
    /**
    * @brief    setName is set function for "name" property.
    * @param    QString name text.
    * @return   void.
    **/
    void setName(QString strName);
    //________________________________________________________________________________________________
    /**
    * @brief    enabled is get function for "enabled" property.
    * @param    void.
    * @return   bool Enabled status.
    **/
    bool enabled();
    //________________________________________________________________________________________________
    /**
    * @brief    setEnabled is set function for "enabled" property.
    * @param    bool Enabled status.
    * @return   void.
    **/
    void setEnabled(bool bEnabled);
    //________________________________________________________________________________________________
    /**
    * @brief    toggleStatus is get function for "toggleStatus" property.
    * @param    void.
    * @return   bool toogle status.
    **/
    bool toggleStatus();
    //________________________________________________________________________________________________
    /**
    * @brief    setToggleStatus is set function for "toggleStatus" property.
    * @param    bool toogle statust.
    * @return   void.
    **/
    void setToggleStatus(bool bToggleStatus);
    //________________________________________________________________________________________________

signals:

    /**
    * @brief    sigTypeChanged is QML signal for "type" property.
    * @param    void.
    * @return   void.
    **/
    Q_SIGNAL void sigTypeChanged();
    //________________________________________________________________________________________________
    /**
    * @brief    sigNameChanged is QML signal for "name" property.
    * @param    void.
    * @return   void.
    **/
    Q_SIGNAL void sigNameChanged();
    //________________________________________________________________________________________________
    /**
    * @brief    sigEnabledChanged is QML signal for "enabled" property.
    * @param    void.
    * @return   void.
    **/
    Q_SIGNAL void sigEnabledChanged();
    //________________________________________________________________________________________________
    /**
    * @brief    sigToggleStatusChanged is QML signal for "toggleStatus" property.
    * @param    void.
    * @return   void.
    **/
    Q_SIGNAL void sigToggleStatusChanged();
    //________________________________________________________________________________________________
private:

    //// Data veriable to hold the value for "type" property.
    CDoodleEnum::EDoodleSetupElementTypes  m_eElementType;

    //// Data veriable to hold the value for "name" property.
    QString m_strName;

    //// Data veriable to hold the value for "enabled" property.
    bool m_bEnabled;

    //// Data veriable to hold the value for "toggleStatus" property.
    bool m_bToggleStatus;
};

#endif // CDOODLESETUPLISTELEMENT_H
