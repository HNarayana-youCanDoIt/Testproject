/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CThemeManager.h
* @ingroup      HMI Framework
* @author       Mohit Rajani
* CThemeManager, framework component to handle the theming for the HMI. Handling fonts, language, theme color etc
*/

#ifndef CTHEMEMANAGER_H
#define CTHEMEMANAGER_H

#include <QObject>
#include <QMap>
#include "CThemeManagerEnums.h"
#include "CFontType.h"
#include "CFramework.h"

/**
 * @brief CThemeManager, framework component to handle the theming for the HMI. Handling fonts, language, theme color etc
 */
class CThemeManager : public QObject
{
    Q_OBJECT

    /** dummy property to handle dynamic language change */
    Q_PROPERTY(QString languageChanged READ emptyString NOTIFY sigLanguageChanged)

    /** property provides the folder path to the various images which are dependent on the type of theme selected */
    Q_PROPERTY(QString themeTypeFolderPath READ themeTypeFolderPath NOTIFY sigThemeTypeFolderPathChanged)

    /** property provides the folder path to startup animation which are dependent on the type of theme selected */
    Q_PROPERTY(QString strStartupAnimPath READ strStartupAnimPath NOTIFY sigStrStartupAnimPathChanged)


    /** currently applied theme type */
    Q_PROPERTY(CThemeManagerEnums::EThemeTypes currentThemeType READ currentThemeType NOTIFY sigCurrentThemeTypeChanged)

    /** currently applied theme's color */
    Q_PROPERTY(QString currentThemeColor READ currentThemeColor NOTIFY sigCurrentThemeColorChanged)

public:
    /**
     * @brief getThemeManager, static function to get the ThemeManager instance
     * @return CThemeManager reference
     */
    static CThemeManager& getThemeManager();
    ~CThemeManager();

    /**
     * @brief getFontType, function to return Font class based on provide Font type enum. Function called from QML
     * @param, provide the FontType for which the font details are required
     * @return CFontType*, font class with font type specific properties
     */
    Q_INVOKABLE CFontType* getFontType(CThemeManagerEnums::EFontType);

    /**
     * @brief setLanguage, used to set the language for the system
     * @param language, the language to be set
     * @return void
     */
    Q_INVOKABLE void setLanguage(QString language);

    /**
     * @brief setThemeType function to set the theme type
     * @param eThemeType the enum value of the theme type that is to be set
     * @return void
     */
    void setThemeType(CThemeManagerEnums::EThemeTypes eThemeType);

    /**
     * @brief getCurrentLanguage, provides the current language of the system
     * @param void
     * @return QString, the current language string
     */
    QString getCurrentLanguage();

    /**
     * @brief getAllThemeColors- Provides all the supported theme colors
     * @param void
     * @return list of theme colors
     */
    Q_INVOKABLE QStringList getAllThemeColors(){return m_listFontHighlightColor;}
	
	/**
     * @brief currentThemeType: function provided the current set theme type
	 * @param void
     * @return enum provides the theme type of the current set theme
     */
    CThemeManagerEnums::EThemeTypes currentThemeType();

    /**
     * @brief writeThemeType : This method is used to write the current theme type at any path.
     * @param iThemeType : holds the current theme type.
     * @return void
     */
    void writeThemeType(int iThemeType);

    /**
     * @brief updateAnimConfig: Method to read the anim config and update it with the latest HMI theme type
     * @param void
     * @return true if updated false otherwise
     */
     bool updateAnimConfig();

signals:

    /**
     * @brief sigLanguageChanged: emitted when the language is changed and is handled within the QML to re-evaluate the qml binding and update the string
     * with the new language translation value
     * @param void
     * @return void
     */
    void sigLanguageChanged();

    /**
     * @brief sigThemeTypeFolderPathChanged: signal is emitted with the theme type path is changed. This can change when the theme type is changed by the user
     * @param void
     * @return void
     */
    void sigThemeTypeFolderPathChanged();

    /**
     * @brief sigThemeTypeFolderPathChanged: signal is emitted when startup animation path is changed. This can change when the theme type is changed by the user
     * @param void
     * @return void
     */
    void sigStrStartupAnimPathChanged();
    /**
     * @brief sigCurrentThemeTypeChanged: signal is emitted when the theme type is changed by the user
     * @param void
     * @return void
     */
    void sigCurrentThemeTypeChanged();

    /**
     * @brief sigCurrentThemeColorChanged: signal to update the change in theme color
     * @param void
     * @return void
     */
    void sigCurrentThemeColorChanged();

private:

    CThemeManager(QObject *parent = 0);
    CThemeManager(const CThemeManager &);
    CThemeManager& operator=(const CThemeManager &);

    /**
     * @brief Create the various font styles for TATA HMI and map it to EFontType
     */
    void initFontTypes();

    /**
     * @brief initLanguage, find and load the various language qm files and set the language based on locale
     */
    void initLanguage();

    /**
     * @brief emptyString, this is the getter for the languageChanged Q_PROPERTY. provides an empty string which is used within the qml to re-evaluate the binding
     * @return empty string
     */
    QString emptyString(){return ""; }

    /**
     * @brief themeTypeFolderPath function provides the current set theme types folder path
	 * @param void
     * @return QString return the current set themes folder path
     */
    QString themeTypeFolderPath();

    /**
     * @brief strStartupAnimPath function provides the path for startup animation as per current theme.
     * @param void
     * @return QString return the current startup animation path
     */
    QString strStartupAnimPath();

    /**
     * @brief setThemeTypeFolderPath set the folder path of the currently selected theme type
     * @param folderPath path to the theme folder (folder where images are stored)
	 * @return void
     */
    void setThemeTypeFolderPath(QString folderPath);

    /**
     * @brief setCurrentThemeType set the current theme type
     * @param themeType new theme type that is to be set
	 * @return void
     */
    void setCurrentThemeType(CThemeManagerEnums::EThemeTypes themeType);

    /**
     * @brief updateFontHighlightColor method to update the color for all the fonts which has isHighlightColor enabled
     * @param eThemeType based on the theme type select the highlight font color to set
	 * @return void
     */
    void updateFontHighlightColor(CThemeManagerEnums::EThemeTypes eThemeType);

    /**
     * @brief currentThemeColor, provides the current theme color
     * @param void
	 * @return current theme color as qstring
     */
    QString currentThemeColor();

    /**
     * @brief setCurrentThemeColor set the theme color for current theme
     * @param strColor theme color to set
	 * @return void
     */
    void setCurrentThemeColor(const QString &strColor);

    /** FONTTYPE map for the HMI to use */
    QMap<CThemeManagerEnums::EFontType, CFontType*> m_MapFontStyle;

    /** static object of the CThemeManager class */
    static CThemeManager* m_pThemeManager;

    /** Reference to the Framework */
    CFramework&  mfw;

    /** Stores the current language on the system **/
    QString m_strCurrentLanguage;

    /** Stores the current tranlator loaded in the application **/
    QTranslator m_Translator;

    /** Stores the current theme type */
    CThemeManagerEnums::EThemeTypes m_eCurrentThemeType;

    /** string list to store the various highlight color based on the theme type */
    QStringList m_listFontHighlightColor;

    /** Stores the current theme type folder path */
    QString m_strCurrThemeTypeFolderPath;

    /** Stores the current theme type folder path */
    QString m_strStartupAnimPath;

    /** List stores the theme folder path for a particular theme*/
    QStringList m_listThemefolderPath;

    /** Stores the current theme's theme color */
    QString m_strCurrentThemeColor;
};

#endif // CTHEMEMANAGER_H
