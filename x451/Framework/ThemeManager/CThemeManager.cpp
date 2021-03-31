/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CThemeManager.cpp
* @ingroup      HMI Framework
* @author       Mohit Rajani
* CThemeManager, framework component to handle the theming for the HMI. Handling fonts, language, theme color etc
*/

#include "CThemeManager.h"
#include <Framework/Logging/logging.h>
#include <QFontDatabase>
#include "CThemeManagerEnums.h"
#include <QGuiApplication>
#include <QFile>

CThemeManager* CThemeManager::m_pThemeManager = nullptr;

CThemeManager::CThemeManager(QObject *parent) : QObject(parent)
  , mfw(CFramework::getFramework())
  , m_strCurrentLanguage("")
  , m_eCurrentThemeType(CThemeManagerEnums::THEME_TYPE_1) // Todo: We should ideally get this from persistence
  , m_strCurrentThemeColor(FontColorHighlight_1)
{
    // populate the folder path for the various themes
    m_listThemefolderPath.clear();
    m_listThemefolderPath << "qrc:/image/Common/Theme/Theme1/"
                    << "qrc:/image/Common/Theme/Theme2/"
                    //<< "qrc:/image/Common/Theme/Theme3/" As per TML, green colour theme should be removed
                    << "qrc:/image/Common/Theme/Theme4/"
                    << "qrc:/image/Common/Theme/Theme5/";



    //Set the default path after initialization
    setThemeTypeFolderPath(m_listThemefolderPath.at(m_eCurrentThemeType));
    // Load all the tata specific font files
    initFontTypes();

    // Load all the language files and set currLanguage
    initLanguage();

    mfw.setContextProperty("cppThemeMgr",this);
}

CThemeManager::~CThemeManager()
{
    // Delete all the CFontType objects and then clear the list
    qDeleteAll(m_MapFontStyle.begin(),m_MapFontStyle.end());
    m_MapFontStyle.clear();
    if(m_pThemeManager)
        delete m_pThemeManager;
}

CThemeManager& CThemeManager::getThemeManager()
{
    if ( nullptr ==  m_pThemeManager )
    {
        m_pThemeManager = new CThemeManager();
    }
    return *m_pThemeManager;
}

void CThemeManager::initFontTypes()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, __FUNCTION__);

    //Register the font related enumerations
    CThemeManagerEnums::registerThemeManagerEnumsToQML();

    //register the class with qml for it to understand the object
    qmlRegisterUncreatableType<CFontType>("com.harman.qml.thememanager", 1, 0, "CFontType", "Cannot create instance of CFont in qml");

    //adding tata specific Fonts to QFontDatabase
//    QFontDatabase::addApplicationFont(":/Fonts/SlatePro.otf");
//    QFontDatabase::addApplicationFont(":/Fonts/SlatePro-Bk.otf");
//    QFontDatabase::addApplicationFont(":/Fonts/SlatePro-Light.otf");
      QFontDatabase::addApplicationFont(":/Fonts/NotoSans-Regular.ttf");


    // create font highlight color string list based on the theme type
    m_listFontHighlightColor.clear();
    m_listFontHighlightColor << FontColorHighlight_1
                             << FontColorHighlight_2
                             //<< FontColorHighlight_3  As per TML, green colour theme should be removed
                             << FontColorHighlight_4
                             << FontColorHighlight_5;

    QString strHighlightColor = m_listFontHighlightColor[m_eCurrentThemeType];
    /** Create the various font styles for TATA HMI (x451) and map it to an enumeration */
    // Type T45_C1
     m_MapFontStyle.insert(CThemeManagerEnums::FONTTYPE_T45_C1,new CFontType("Noto Sans",41,strHighlightColor, true));

     //Type T45_C1_WHITE
     m_MapFontStyle.insert(CThemeManagerEnums::FONTTYPE_T45_C1_WHITE, new CFontType("Noto Sans" , 41, FontColorWhite));

     // Type T45_C1_DISABLED
     m_MapFontStyle.insert(CThemeManagerEnums::FONTTYPE_T45_C1_DISABLED,new CFontType("Noto Sans",41,FontColor_Disabled));

     // Type T35_C3
     m_MapFontStyle.insert(CThemeManagerEnums::FONTTYPE_T35_C3,new CFontType("Noto Sans",31, FontColorWhite));

     // Type T35_C3_DISABLED
     m_MapFontStyle.insert(CThemeManagerEnums::FONTTYPE_T35_C3_DISABLED,new CFontType("Noto Sans",31,FontColor_Disabled));

     // Type T35_bk_C2
     m_MapFontStyle.insert(CThemeManagerEnums::FONTTYPE_T35_BK_C2,new CFontType("Noto Sans",31, FontColorWhite));

     // Type T35_BK_C2_DISABLED
     m_MapFontStyle.insert(CThemeManagerEnums::FONTTYPE_T35_BK_C2_DISABLED,new CFontType("Noto Sans",31,FontColor_Disabled));

     // Type T24_light_C2
     m_MapFontStyle.insert(CThemeManagerEnums::FONTTYPE_T24_LIGHT_C2,new CFontType("Noto Sans",22,FontColorWhite));

     // Type T24_LIGHT_C2_DISABLED
     m_MapFontStyle.insert(CThemeManagerEnums::FONTTYPE_T24_LIGHT_C2_DISABLED,new CFontType("Noto Sans",22,FontColor_Disabled));

     // Type T24_light_C3
     m_MapFontStyle.insert(CThemeManagerEnums::FONTTYPE_T24_LIGHT_C3,new CFontType("Noto Sans",22,FontColorWhite));

     // Type T24_LIGHT_C3_DISABLED
     m_MapFontStyle.insert(CThemeManagerEnums::FONTTYPE_T24_LIGHT_C3_DISABLED,new CFontType("Noto Sans",22,FontColor_Disabled));

     //[todo]: will be changed as per requirement.
     //RVC screen font
     m_MapFontStyle.insert(CThemeManagerEnums::FONTTYPE_RVC, new CFontType("Noto Sans", 28, FontColorWhite)); //White color

     //[todo]: will be changed as per requirement.
     // Type FONTTYPE_T22_BK_C2_AMBER
     m_MapFontStyle.insert(CThemeManagerEnums::FONTTYPE_T22_BK_C2_AMBER, new CFontType("Noto Sans",22, FontColorAmber)); //Amber color

     //[todo]: will be changed as per requirement.
     // Type FONTTYPE_PDC
     m_MapFontStyle.insert(CThemeManagerEnums::FONTTYPE_PDC, new CFontType("Noto Sans",23, FontColorWhite)); //White color

     // Type FONTTYPE_PDC
     m_MapFontStyle.insert(CThemeManagerEnums::FONTTYPE_T22_LIGHT_C2, new CFontType("Noto Sans",19,FontColorWhite)); //White color

     // Type FONTTYPE_T70_C2_WHITE
     m_MapFontStyle.insert(CThemeManagerEnums::FONTTYPE_T70_C2_WHITE, new CFontType("Noto Sans",70,FontColorWhite)); //White color

    // set default font for the application
    QFont defaultFont("Noto Sans");
    defaultFont.setPixelSize(31);
    qGuiApp->setFont(defaultFont);

}

CFontType* CThemeManager::getFontType(CThemeManagerEnums::EFontType fontType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, font type: %d", __FUNCTION__, fontType);
    CFontType* tmpFontType = m_MapFontStyle.value(CThemeManagerEnums::FONTTYPE_T35_C3);
    QMap<CThemeManagerEnums::EFontType, CFontType*>::const_iterator fontTypeIterator = m_MapFontStyle.find(fontType);
    if (fontTypeIterator != m_MapFontStyle.end())
    {
        tmpFontType = fontTypeIterator.value();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "font type not found. Setting t35_C3 as the default");
    }

    // Set the ownership to cpp so that the qml gc does not delete them at runtime
    qmlEngine(this)->setObjectOwnership(tmpFontType,QQmlEngine::CppOwnership);
    return tmpFontType;
}


void CThemeManager::initLanguage()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s", __FUNCTION__);
    /* To set the default locale to english india, since this was not being set
     * in target */
    QString curLocale = "en_IN";//QLocale::system().name(); // e.g. "en_IN"
    setLanguage(curLocale);
}

void CThemeManager::setLanguage(QString language)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, language: %s", __FUNCTION__,language.toStdString().data());

    if(m_strCurrentLanguage != language)
    {
        m_strCurrentLanguage = language;

        // remove the old translator
        if (!(m_Translator.isEmpty()))
        {
            qGuiApp->removeTranslator(&m_Translator);
        }

        // load the new translator
        QString qmLangQMPath = qGuiApp->applicationDirPath();
        qmLangQMPath.append("/languages/");
        QFile qmFile(QString("%1%2.qm").arg(qmLangQMPath).arg(language));
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, filename: %s", __FUNCTION__, qmFile.fileName().toStdString().data());
        if (qmFile.exists())
        {
            if(m_Translator.load(qmFile.fileName()))
            {
                qGuiApp->installTranslator(&m_Translator);
                // emit the signal to have all the qsTr related text re-evaluated
                emit sigLanguageChanged();
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_MAIN, "%s, translator for language: %s not installed", __FUNCTION__, language.toStdString().data());
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, file does not exists", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, trying to load the current language again", __FUNCTION__);
    }
}

QString CThemeManager::getCurrentLanguage()
{
    return m_strCurrentLanguage;
}

void CThemeManager::setThemeType(CThemeManagerEnums::EThemeTypes eThemeType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s theme: %d", __FUNCTION__, eThemeType);
    if ((m_eCurrentThemeType != eThemeType) &&
            ((eThemeType >= CThemeManagerEnums::EThemeTypes::THEME_TYPE_1) &&
             (eThemeType < CThemeManagerEnums::EThemeTypes::THEME_TYPE_MAX)))
    {
        // call function to update the hightlight color for the various font dependent on it
        updateFontHighlightColor(eThemeType);

        // call function to update the theme type path based on the theme type set
        setThemeTypeFolderPath(m_listThemefolderPath.at(eThemeType));

        // update the current theme type
        setCurrentThemeType(eThemeType);

        //Write theme type at any path
#if (!defined(PLATFORM_WIN32) && !defined(PLATFORM_LINUX_X86))
        writeThemeType(eThemeType);
#endif
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, trying to load the current theme again", __FUNCTION__);
    }
}

void CThemeManager::writeThemeType(int iThemeType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s themeType: %d", __FUNCTION__, iThemeType);

    if((iThemeType >= static_cast<int>(CThemeManagerEnums::EThemeTypes::THEME_TYPE_1)) &&
        (iThemeType < static_cast<int>(CThemeManagerEnums::EThemeTypes::THEME_TYPE_MAX)))
    {
        QString strFilePath = "/mnt/data/animConfig_X451.ini";
        QFile objfile(strFilePath);

        /**
         * HMI has removed green theme and updated values for pink and yellow theme, but the theme
         * values stored in PDC/RVC are old values. To map new values with old values, we have kept
         * an array holding previous values for new theme type to write it in animConfig_X451.ini file.
         */
        int aryThemeType[4] = {0, 1, 4, 3};

        if (!objfile.open(QIODevice::ReadWrite | QIODevice::Text)) {
            LOG_ERROR(Log::e_LOG_CONTEXT_MAIN, "%s, Could not Open File : %s ErrorMsg : %s",
                     __FUNCTION__, strFilePath.toStdString().c_str(), objfile.errorString().toStdString().c_str());
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, File Path :%s, Writing Theme Type: %d",
                     __FUNCTION__, strFilePath.toStdString().c_str(), iThemeType);
            QTextStream objStream(&objfile);
            objStream << "ThemeType = "<< aryThemeType[iThemeType] << endl;
            objfile.flush();
            objfile.close();
            system("sync");
        }
    }
    else
    {
        LOG_ERROR(Log::e_LOG_CONTEXT_MAIN, "%s, Inavlid theme type index", __FUNCTION__);
    }
}

bool CThemeManager::updateAnimConfig()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s themeType: ", __FUNCTION__);
    bool bResult = false;

    QString strFilePath = "/mnt/data/animConfig_X451.ini";
    QFile objFile(strFilePath);
    CThemeManagerEnums::EThemeTypes eVal = CThemeManagerEnums::EThemeTypes::THEME_TYPE_1;

    if(objFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       QTextStream inStream(&objFile);
       while(!inStream.atEnd())
       {
           QStringList strList = inStream.readLine().split(" ");
           eVal = static_cast<CThemeManagerEnums::EThemeTypes> (QString(strList.last()).toInt());
           LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s eVal: %d", __FUNCTION__, eVal);
           break;
       }

       if(currentThemeType() != eVal)
       {
           writeThemeType(currentThemeType());
           bResult = true;
       }
       else
       {
           LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s Value in %s is in sync.", __FUNCTION__, strFilePath.toStdString().c_str());
       }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s Could not open %s.", __FUNCTION__, strFilePath.toStdString().c_str());
    }
    return bResult;
}

QString CThemeManager::themeTypeFolderPath()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s", __FUNCTION__);
    return m_strCurrThemeTypeFolderPath;
}

QString CThemeManager::strStartupAnimPath()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s", __FUNCTION__);

#ifdef PLATFORM_WIN32
    QDir dir = QDir::current();
    m_strStartupAnimPath = "file:/" + dir.currentPath() + "/anim/Theme" + QString::number(m_eCurrentThemeType +1);
#else
    m_strStartupAnimPath = "file:/opt/hmi/anim/Theme" + QString::number(m_eCurrentThemeType +1);
#endif
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s", m_strStartupAnimPath.toStdString().data());
    return m_strStartupAnimPath;
}
void CThemeManager::setThemeTypeFolderPath(QString folderPath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, set path as %s", __FUNCTION__, folderPath.toStdString().data());
    if ( folderPath != m_strCurrThemeTypeFolderPath)
    {
        m_strCurrThemeTypeFolderPath = folderPath;
        emit sigThemeTypeFolderPathChanged();
    }
}

CThemeManagerEnums::EThemeTypes CThemeManager::currentThemeType()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s", __FUNCTION__);
    return m_eCurrentThemeType;
}

void CThemeManager::setCurrentThemeType(CThemeManagerEnums::EThemeTypes eThemeType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, set theme as %d", __FUNCTION__, eThemeType);
    if ( eThemeType != m_eCurrentThemeType)
    {
        m_eCurrentThemeType = eThemeType;
        emit sigCurrentThemeTypeChanged();
    }
}

QString CThemeManager::currentThemeColor()
{
    return m_strCurrentThemeColor;
}

void CThemeManager::setCurrentThemeColor(const QString& strColor)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, set theme color %s", __FUNCTION__, strColor.toStdString().c_str());
    if ( strColor != m_strCurrentThemeColor)
    {
        m_strCurrentThemeColor = strColor;
        emit sigCurrentThemeColorChanged();
    }
}

void CThemeManager::updateFontHighlightColor(CThemeManagerEnums::EThemeTypes eThemeType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, themeType: %d", __FUNCTION__, eThemeType);
    QMap<CThemeManagerEnums::EFontType, CFontType*>::const_iterator fontTypeIterator;
    for (fontTypeIterator = m_MapFontStyle.constBegin(); fontTypeIterator != m_MapFontStyle.constEnd(); ++fontTypeIterator)
    {
        CFontType* fontType = fontTypeIterator.value();
        if ((nullptr != fontType) && (true == fontType->isHighlightColor()))
        {
            if ((eThemeType >= CThemeManagerEnums::THEME_TYPE_1) && (eThemeType <= CThemeManagerEnums::THEME_TYPE_5))
            {
                LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "themeType: %d, highlight color: %s",eThemeType,m_listFontHighlightColor.at(eThemeType).toStdString().data());
                fontType->setColor(m_listFontHighlightColor.at(eThemeType));

                // update the current theme color
                setCurrentThemeColor(m_listFontHighlightColor.at(eThemeType));
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "themeType: %d out of range", eThemeType);
            }
        }
    }
}
