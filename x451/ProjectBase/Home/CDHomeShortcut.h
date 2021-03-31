/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDHomeShortcut.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDHomeShortcut, a Data structure for Home module,
 * CDHomeShortcut maintains home-shortcut-button data information.
 */

#ifndef CDHOMESHORTCUT_H
#define CDHOMESHORTCUT_H

#include <QObject>
#include <QString>
#include "CHomeEnum.h"
class CHomeAdaptor;

/**
 * @brief CDHomeShortcut, a Data structure for Home module,
 * It maintains home-shortcut-button data information.
 */
class CDHomeShortcut : public QObject
{
    Q_OBJECT

    // Properties //
    // to get home shortcut button Unique id
    Q_PROPERTY(int uId READ uId NOTIFY sigUIdChanged)

    // to get home shortcut button title text
    Q_PROPERTY(QString text READ text NOTIFY sigTextChanged)

    // to get home shortcut button normal icon
    Q_PROPERTY(QString iconNormal READ iconNormal NOTIFY sigIconNormalChanged)

    // to get home shortcut button pressed icon
    Q_PROPERTY(QString iconPressed READ iconPressed NOTIFY sigIconPressedChanged)

    // to get home shortcut button inactive icon
    Q_PROPERTY(QString iconInactive READ iconInactive NOTIFY sigIconInactiveChanged)

    // to get home shortcut button active state
    Q_PROPERTY(bool isActive READ isActive NOTIFY sigIsActiveChanged)

    // to get home shortcut button available state
    Q_PROPERTY(bool isAvailable READ isAvailable NOTIFY sigIsAvailableChanged)

public:
    /**
    * @brief	CDHomeShortcut::CDHomeShortcut constructor for data class CDHomeShortcut.
    * @param	unique id (int _uid) for shortcut, QObject.
    * @return	NA.
    **/
    explicit CDHomeShortcut(int _uid, QObject *parent = nullptr);
    //________________________________________________________________________________________________
    /**
    * @brief	CDHomeShortcut::~CDHomeShortcut is destructor of class CDHomeShortcut
    * @param	NA.
    * @return	NA.
    **/
    ~CDHomeShortcut();

    /** constant veriable to hold total count of shortcuts available per page **/
    static const int MAX_SHORTCUT_SLOTS_AVAILABLE_PER_PAGE = 6;

    /** Add shortcut details here by alphabet order of it's title text **/
    const static QString/*char **/ SHORTCUTS[CHomeEnum::MAX_SHORTCUTS_AVAILABLE][6];

    /** Add shortcut details here by alphabet order of it's title text **/
    //const static char * SHORTCUTS_Data[CHomeEnum::MAX_SHORTCUTS_AVAILABLE][6];

    /** total default shortcut info available **/
    static const int DEFAULT_SHORTCUTS_AVAILABLE = 8;

    /** Add default shortcut ID sequence **/
    static const int DEFAULT_SHORTCUT_IDS[CDHomeShortcut::DEFAULT_SHORTCUTS_AVAILABLE];

    //________________________________________________________________________________________________
    /**
    * @brief	CDHomeShortcut::uId is get method for "uId" qml property.
    * @param	void.
    * @return	int.
    **/
    int uId();
    /**
    * @brief	CDHomeShortcut::uId is set method for "uId" qml property.
    * @param	void.
    * @return	int.
    **/
    void setUId(int _uId);
    //________________________________________________________________________________________________
    /**
    * @brief	CDHomeShortcut::text is get method for "text" qml property.
    * @param	void.
    * @return	QString.
    **/
    QString text();
    /**
    * @brief	CDHomeShortcut::setText is set method for "text" qml property.
    * @param	QString.
    * @return	void.
    **/
    void setText(QString val);
    //________________________________________________________________________________________________
    /**
    * @brief	CDHomeShortcut::iconNormal is get method for "iconNormal" qml property.
    * @param	void.
    * @return	QString.
    **/
    QString iconNormal();
    /**
    * @brief	CDHomeShortcut::setIconNormal is set method for "iconNormal" qml property.
    * @param	QString.
    * @return	void.
    **/
    void setIconNormal(QString val);
    //________________________________________________________________________________________________
    /**
    * @brief	CDHomeShortcut::iconPressed is get method for "iconPressed" qml property.
    * @param	void.
    * @return	QString.
    **/
    QString iconPressed();
    /**
    * @brief	CDHomeShortcut::setIconPressed is set method for "iconPressed" qml property.
    * @param	QString.
    * @return	void.
    **/
    void setIconPressed(QString val);
    //________________________________________________________________________________________________
    /**
    * @brief	CDHomeShortcut::iconInactive is get method for "iconInactive" qml property.
    * @param	void.
    * @return	QString.
    **/
    QString iconInactive();
    /**
    * @brief	CDHomeShortcut::setIconInactive is set method for "iconInactive" qml property.
    * @param	QString.
    * @return	void.
    **/
    void setIconInactive(QString val);
    //________________________________________________________________________________________________
    /**
    * @brief	CDHomeShortcut::isActive is get method for "isActive" qml property.
    * @param	void.
    * @return	bool.
    **/
    bool isActive();
    /**
    * @brief	CDHomeShortcut::setIsActive is set method for "isActive" qml property.
    * @param	QString.
    * @return	void.
    **/
    void setIsActive(bool val);
    //________________________________________________________________________________________________
    /**
    * @brief	CDHomeShortcut::isAvailable is get method for "isAvailable" qml property.
    * @param	void.
    * @return	bool.
    **/
    bool isAvailable();
    /**
    * @brief	CDHomeShortcut::setIsAvailable is set method for "isAvailable" qml property.
    * @param	QString.
    * @return	void.
    **/
    void setIsAvailable(bool val);
    //________________________________________________________________________________________________
    /**
    * @brief	CDHomeShortcut::invShortcutClicked is QML invocable method which gives clicked callback.
    * @param	int (slotIndex).
    * @return	void.
    **/
    Q_INVOKABLE void invShortcutClicked(int _index);
    //________________________________________________________________________________________________
signals:
    /**
    * @brief	CDHomeShortcut::sigUIdChanged is QML signal for "uId" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigUIdChanged();
    /**
    * @brief	CDHomeShortcut::sigTextChanged is QML signal for "text" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigTextChanged();
    /**
    * @brief	CDHomeShortcut::sigIconNormalChanged is QML signal for "iconNormal" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigIconNormalChanged();
    /**
    * @brief	CDHomeShortcut::sigIconPressedChanged is QML signal for "iconPressed" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigIconPressedChanged();
    /**
    * @brief	CDHomeShortcut::sigIconInactiveChanged is QML signal for "iconInactive" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigIconInactiveChanged();
    /**
    * @brief	CDHomeShortcut::sigIsActiveChanged is QML signal for "isActive" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigIsActiveChanged();
    /**
    * @brief	CDHomeShortcut::sigIsAvailableChanged is QML signal for "isAvailable" property.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigIsAvailableChanged();
    //________________________________________________________________________________________________
public:
    /**
    * @brief	function pointer to handle shortcut specific flow, this will be linked to callback functions from CHomeAdaptor class
    * @param	slot index on which user clicked (int).
    * @return	void.
    **/
    void(CHomeAdaptor::*onButtonClickCBFunction)(int) = NULL;
    //________________________________________________________________________________________________
private:
    int m_UId;              // member veriable for property uId
    QString m_Text;         // member veriable for property text
    QString m_IconNormal;   // member veriable for property iconNormal
    QString m_IconPressed;  // member veriable for property iconPressed
    QString m_IconInactive; // member veriable for property iconInactive
    bool m_IsActive;        // member veriable for property isActive
    bool m_IsAvailable;     // member veriable for property isAvailable
    //________________________________________________________________________________________________
};

#endif // CDHOMESHORTCUT_H
