
/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CIntrospectionAdaptor.cpp
* @ingroup      HMIComponent
* @author       Gaurav Garg
* CIntrospectionAdaptor used to communicate with the Resource Layer.
*/

#include "CIntrospectionAdaptor.h"
#include "CIntrospectionEnum.h"


CIntrospectionAdaptor* CIntrospectionAdaptor::m_pIntroMainInstance = nullptr;

CIntrospectionAdaptor::CIntrospectionAdaptor(QObject *pParent)
    :QObject(pParent)
    ,mfw(CFramework::getFramework())
    ,m_strScreenName("")
    ,m_iObjectIndex(0)
    ,m_iObjectIndexPopup(0)
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s",__FUNCTION__);
    mfw.setContextProperty("cppIntrospectionAdaptor", this);
}
CIntrospectionAdaptor::~CIntrospectionAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s",__FUNCTION__);

    if(m_pIntroMainInstance)
    {
        m_pIntroMainInstance = nullptr;
    }
}

CIntrospectionAdaptor* CIntrospectionAdaptor::getInstance()
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s",__FUNCTION__);
    if(nullptr == m_pIntroMainInstance )
    {
        m_pIntroMainInstance = new CIntrospectionAdaptor();
    }
    return m_pIntroMainInstance;
}

QString CIntrospectionAdaptor::invExtractFileName(QString strFilePath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s strFilePath %s ",__FUNCTION__, strFilePath.toStdString().c_str());
    vector<std::string> vecFilePathTokens;
    stringstream ssFilePath(strFilePath.toStdString());
    std::string strIntermediate;
    while(std::getline(ssFilePath, strIntermediate, '/'))
    {
        vecFilePathTokens.push_back(strIntermediate);
    }

    return QString::fromStdString(vecFilePathTokens.at(vecFilePathTokens.size() - 1));
}


QString CIntrospectionAdaptor::fetchItemInfo(const QString& strTopScreen, QQuickItem *pItem)
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s fetchItemInfo : %s", __FUNCTION__, strTopScreen.toStdString().c_str());
    QString strInspectInfoForOne = "";
    if(pItem)
    {
        QString strIsEnabled = (pItem->isEnabled())? "true" : "false";
        QString strIsVisible = (pItem->isVisible())? "true" : "false";
        QString strHasChild = (pItem->childItems().count() > 0) ? "true" : "false";
        QString strClassName = pItem->metaObject()->className();

        if(m_iObjectIndex>0)
        {
            strInspectInfoForOne.append(", \"obj");
            strInspectInfoForOne.append(QString::number(m_iObjectIndex++));
            strInspectInfoForOne.append("\": ");
        }
        else
        {
            m_iObjectIndex = 1;
        }

        strInspectInfoForOne += " {\"" + pItem->objectName() + "\":{\"className\" : \"" + strClassName + "\", \"parent\" : \""+ pItem->parentItem()->metaObject()->className()  + "\", \"hasChild\" : "+ strHasChild + ", \"childCount\" : " + QString::number(pItem->childItems().count()) +", \"height\" : "+ QString::number(pItem->height()) + ", \"width\" : "+  QString::number(pItem->width()) +", \"enabled\" : " +  strIsEnabled + ", \"visible\" : " + strIsVisible + ", \"x\" : " + QString::number(pItem->x()) + ", \"y\" : " + QString::number(pItem->y()) + ", \"z\" : " + QString::number(pItem->z());

        if(strClassName.endsWith("Image",Qt::CaseInsensitive) || strClassName.startsWith("HBText", Qt::CaseInsensitive) || strClassName.startsWith("GenericButton", Qt::CaseInsensitive))
        {
            const QMetaObject* metaObject = pItem->metaObject();
            QHash<QString, QVariant> list;
            QString strInspectAdditionalInfo = "";


            for(int i = 0 ; i < metaObject->propertyCount(); ++i)
            {
                QMetaProperty property = metaObject->property(i);
                const char* names = property.name();
                QVariant value = pItem->property(names);
                list[names] = value;
            }
            QHashIterator<QString, QVariant> i(list);
            while (i.hasNext())
            {
                i.next();
                int iCompareForText = QString::compare(i.key(), "text", Qt::CaseInsensitive);
                int iCompareForImgSource = QString::compare(i.key(), "source", Qt::CaseInsensitive);
                if(iCompareForText == 0 || iCompareForImgSource == 0)
                {
                    strInspectAdditionalInfo.append(", \"");
                    strInspectAdditionalInfo.append(i.key());
                    strInspectAdditionalInfo.append("\" : \"");
                    strInspectAdditionalInfo.append(i.value().toString());
                    strInspectAdditionalInfo.append("\"");
                }
            }

            strInspectInfoForOne.append(strInspectAdditionalInfo);
        }

        strInspectInfoForOne.append(" }");

        for(int iChildItemIndex = 0 ; iChildItemIndex < pItem->childItems().count(); iChildItemIndex++)
        {
            strInspectInfoForOne += fetchItemInfo(strTopScreen, pItem->childItems().at(iChildItemIndex));
        }
        strInspectInfoForOne.append("}");
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION," %s item is null", __FUNCTION__);
    }

    return strInspectInfoForOne;
}


QString CIntrospectionAdaptor::fetchItemInfoForPopup(const QString& strTopScreen, QObject *pItem)
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s fetchItemInfo : %s", __FUNCTION__, strTopScreen.toStdString().c_str());
    QString strInspectInfoForOne = "";
    if(pItem)
    {
        QString strHasChild = (pItem->children().count() > 0) ? "true" : "false";
        QString strClassName = pItem->metaObject()->className();

        if(m_iObjectIndexPopup>0)
        {
            strInspectInfoForOne.append(", \"obj");
            strInspectInfoForOne.append(QString::number(m_iObjectIndexPopup++));
            strInspectInfoForOne.append("\": ");
        }
        else
        {
            m_iObjectIndexPopup = 1;
        }

        strInspectInfoForOne += " {\"" + pItem->objectName() + "\":{\"className\" : \"" + strClassName + "\", \"parent\" : \""+ pItem->parent()->metaObject()->className() +"\", \"hasChild\" : " + strHasChild + ", \"childCount\" : " + QString::number(pItem->children().count());

        const QMetaObject* metaObject = pItem->metaObject();
        QHash<QString, QVariant> list;


            for(int i = 0 ; i < metaObject->propertyCount(); ++i)
            {
                QMetaProperty property = metaObject->property(i);
                const char* names = property.name();
                QVariant value = pItem->property(names);
                list[names] = value;
            }
            QHashIterator<QString, QVariant> i(list);
            while (i.hasNext())
            {
                i.next();
                int iCompareForHeight = QString::compare(i.key(), "height", Qt::CaseInsensitive);
                int iCompareForWidth = QString::compare(i.key(), "width", Qt::CaseInsensitive);
                int iCompareForEnabled = QString::compare(i.key(), "enabled", Qt::CaseInsensitive);
                int iCompareForVisible = QString::compare(i.key(), "visible", Qt::CaseInsensitive);
                int iCompareForX = QString::compare(i.key(), "x", Qt::CaseInsensitive);
                int iCompareForY = QString::compare(i.key(), "y", Qt::CaseInsensitive);
                int iCompareForZ = QString::compare(i.key(), "z", Qt::CaseInsensitive);
                int iCompareForText = QString::compare(i.key(), "text", Qt::CaseInsensitive);
                int iCompareForImgSource = QString::compare(i.key(), "source", Qt::CaseInsensitive);

                if( (iCompareForHeight == 0) || (iCompareForWidth == 0) || (iCompareForEnabled == 0) || (iCompareForVisible == 0) || (iCompareForX == 0) || (iCompareForY == 0) || (iCompareForZ == 0))
                {
                    strInspectInfoForOne.append(", \"");
                    strInspectInfoForOne.append(i.key());
                    strInspectInfoForOne.append("\" : ");
                    strInspectInfoForOne.append(i.value().toString());
                }
                else
                {
                    if((iCompareForText == 0) || (iCompareForImgSource == 0))
                    {
                        strInspectInfoForOne.append(", \"");
                        strInspectInfoForOne.append(i.key());
                        strInspectInfoForOne.append("\" : \"");
                        strInspectInfoForOne.append(i.value().toString());
                        strInspectInfoForOne.append("\"");
                    }
                }
            }

        strInspectInfoForOne.append(" }");

        for(int iChildItemIndex = 0 ; iChildItemIndex < pItem->children().count(); iChildItemIndex++)
        {
            strInspectInfoForOne += fetchItemInfoForPopup(strTopScreen, pItem->children().at(iChildItemIndex));
        }
        strInspectInfoForOne.append("}");
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION," %s item is null", __FUNCTION__);
    }

    return strInspectInfoForOne;
}

void CIntrospectionAdaptor::getIntrospectionData(int iItemType, QString itemName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s: Item type is: %d and the item name is %s",__FUNCTION__, iItemType, itemName.toStdString().c_str());

    EItemType eItemType = static_cast<EItemType>(iItemType);
    QString strScreenInfo = "";
    switch(eItemType)
    {
    case EItemType::EN_ITEM_TYPE_SCREEN:
    {
        if(itemName == m_strScreenName)
        {
            QQuickItem* pItem = mfw.getRootObject()->findChild<QQuickItem*>(m_strScreenName);
            strScreenInfo = fetchItemInfo(m_strScreenName, pItem);
            LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s strScreenInfo : %s",__FUNCTION__,strScreenInfo.toStdString().c_str());
            m_iObjectIndex = 0;
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION, "%s Inspection request for %s is not loaded in item type screen", __FUNCTION__, itemName.toStdString().c_str());
        }

        if(ResourceFactory::getIntrospectionStubResource())
        {
            ResourceFactory::getIntrospectionStubResource()->sendScreenInfo(strScreenInfo.toStdString());
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION, "%s IntroResource is null", __FUNCTION__);
        }
    }
        break;

    case EItemType::EN_ITEM_TYPE_DRAWER:
    {
        if(itemName == m_strDrawerScreenName)
        {
            QQuickItem* pItem = mfw.getRootObject()->findChild<QQuickItem*>(m_strDrawerScreenName);
            strScreenInfo = fetchItemInfo(m_strDrawerScreenName, pItem);
            LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s Drawer strScreenInfo : %s",__FUNCTION__,strScreenInfo.toStdString().c_str());
            m_iObjectIndex = 0;
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION, "%s Inspection request for %s is not loaded in item type drawer", __FUNCTION__, itemName.toStdString().c_str());
        }
        if(ResourceFactory::getIntrospectionStubResource())
        {
            ResourceFactory::getIntrospectionStubResource()->sendScreenInfo(strScreenInfo.toStdString());
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION, "%s IntroResource is null", __FUNCTION__);
        }
    }
        break;

    case EItemType::EN_ITEM_TYPE_POPUP:
    {
        if(itemName == m_strPopupScreenName)
        {
            QObject* pItem = mfw.getRootObject()->findChild<QObject*>(m_strPopupScreenName);
            strScreenInfo = fetchItemInfoForPopup(m_strPopupScreenName, pItem);
            LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s Popup strScreenInfo : %s",__FUNCTION__,strScreenInfo.toStdString().c_str());
            m_iObjectIndexPopup = 0;
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION, "%s Inspection request for %s is not loaded in item type popup", __FUNCTION__, itemName.toStdString().c_str());
        }
        if(ResourceFactory::getIntrospectionStubResource())
        {
            ResourceFactory::getIntrospectionStubResource()->sendScreenInfo(strScreenInfo.toStdString());
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION, "%s IntroResource is null", __FUNCTION__);
        }
    }

    case EItemType::EN_ITEM_TYPE_OVERLAYS:
    {
        if(itemName == m_strOverlayScreenName)
        {
            QQuickItem* pItem = mfw.getNotificationRootObject()->findChild<QQuickItem*>(itemName);
            strScreenInfo = fetchItemInfo(itemName, pItem);
            LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s Overlays strScreenInfo : %s",__FUNCTION__,strScreenInfo.toStdString().c_str());
            m_iObjectIndex = 0;
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION, "%s Inspection request for %s is not loaded in item type overlays", __FUNCTION__, itemName.toStdString().c_str());
        }

        if(ResourceFactory::getIntrospectionStubResource())
        {
            ResourceFactory::getIntrospectionStubResource()->sendScreenInfo(strScreenInfo.toStdString());
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION, "%s IntroResource is null", __FUNCTION__);
        }
    }
        break;

    default:
        LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION, "%s Invalid value received", __FUNCTION__);
        break;
    }
}

void CIntrospectionAdaptor:: invSetScreenChanged(QString strScreenName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s value : %s",__FUNCTION__,strScreenName.toStdString().c_str());
    m_strScreenName = strScreenName;
    if(ResourceFactory::getIntrospectionStubResource())
    {
       ResourceFactory::getIntrospectionStubResource()->setScreenChange(m_strScreenName.toStdString(), EItemType::EN_ITEM_TYPE_SCREEN);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION, "%s IntroResource is null", __FUNCTION__);
    }
}

void CIntrospectionAdaptor::invSetDrawerChanged(QString strScreenName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s value : %s",__FUNCTION__,strScreenName.toStdString().c_str());
    m_strDrawerScreenName = strScreenName;
    if(ResourceFactory::getIntrospectionStubResource())
    {
       ResourceFactory::getIntrospectionStubResource()->setScreenChange(m_strDrawerScreenName.toStdString(), EItemType::EN_ITEM_TYPE_DRAWER);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION, "%s IntroResource is null", __FUNCTION__);
    }
}


void CIntrospectionAdaptor::invSetPopupChanged(QString strScreenName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s value : %s",__FUNCTION__,strScreenName.toStdString().c_str());
    m_strPopupScreenName = strScreenName;
    if(ResourceFactory::getIntrospectionStubResource())
    {
       ResourceFactory::getIntrospectionStubResource()->setScreenChange(m_strPopupScreenName.toStdString(), EItemType::EN_ITEM_TYPE_POPUP);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION, "%s IntroResource is null", __FUNCTION__);
    }
}

void CIntrospectionAdaptor::invSetOverlayChanged(QString strScreenName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s value : %s",__FUNCTION__,strScreenName.toStdString().c_str());
    m_strOverlayScreenName = strScreenName;
    if(ResourceFactory::getIntrospectionStubResource())
    {
       ResourceFactory::getIntrospectionStubResource()->setScreenChange(m_strOverlayScreenName.toStdString(), EItemType::EN_ITEM_TYPE_OVERLAYS);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION, "%s IntroResource is null", __FUNCTION__);
    }
}
