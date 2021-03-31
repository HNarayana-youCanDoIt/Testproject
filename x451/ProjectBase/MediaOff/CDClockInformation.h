/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDClockInformation.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDClockInformation is a Data class used to hold clock information.
 */

#ifndef CDCLOCKINFORMATION_H
#define CDCLOCKINFORMATION_H

#include <QObject>
#include <QString>

#include "CClockEnum.h"

class CDClockInformation: public QObject
{
    Q_OBJECT

    //Q Properties//
    //// QProperty to get clock Unique id
    Q_PROPERTY(int uId                        READ uId                  NOTIFY sigUIdChanged)

    //// QProperty to get clock layout
    Q_PROPERTY(QString layout                 READ layout               NOTIFY sigLayoutTypeChanged)

    //// QProperty to get clock layout type
    Q_PROPERTY(int layoutType                 READ layoutType           NOTIFY sigLayoutTypeChanged)

    //// QProperty to get clock motion type
    Q_PROPERTY(int motionType                 READ motionType           NOTIFY sigMotionTypeChanged)

    //// QProperty to get clock dial image path
    Q_PROPERTY(QString imageDial              READ imageDial            NOTIFY sigImageDialChanged)

    //// QProperty to get clock center image path
    Q_PROPERTY(QString imageCenter            READ imageCenter          NOTIFY sigImageCenterChanged)

    //// QProperty to get clock center shadow image path
    Q_PROPERTY(QString imageCenterShadow      READ imageCenterShadow    NOTIFY sigImageCenterShadowChanged)

    //// QProperty to get clock Hr hand image path
    Q_PROPERTY(QString imageHrHand            READ imageHrHand          NOTIFY sigImageHrHandChanged)

    //// QProperty to get clock Hr hand shadow image path
    Q_PROPERTY(QString imageHrHandShadow      READ imageHrHandShadow    NOTIFY sigImageHrHandShadowChanged)

    //// QProperty to get clock Min hand image path
    Q_PROPERTY(QString imageMinHand           READ imageMinHand         NOTIFY sigImageMinHandChanged)

    //// QProperty to get clock Min hand shadow image path
    Q_PROPERTY(QString imageMinHandShadow     READ imageMinHandShadow   NOTIFY sigImageMinHandShadowChanged)

    //// QProperty to get clock Sec hand image path
    Q_PROPERTY(QString imageSecHand           READ imageSecHand         NOTIFY sigImageSecHandChanged)

    //// QProperty to get clock Sec hand shadow image path
    Q_PROPERTY(QString imageSecHandShadow     READ imageSecHandShadow   NOTIFY sigImageSecHandShadowChanged)

    //________________________________________________________________________________________________
public:
    /**
    * @brief	CDClockInformation::CDClockInformation constructor for data class CDClockInformation.
    * @param	int : clock unique id,
    *           CClockEnum::EClockLayoutTypes : clock layout Type,
    *           CClockEnum::EClockMotionTypes : clock motion Type,
    *           QString : image for clock dial,       QString : image for clock center,
    *           QString : image for clock Hr Hand,    QString : image for clock Hr Hand Shadow,
    *           QString : image for clock Min Hand,   QString : image for clock Min Hand Shadow,
    *           QString : image for clock Sec Hand,   QString : image for clock Sec Hand Shadow,
    *           QObject : parent QObject.
    * @return	NA.
    **/
    CDClockInformation(int _uId, CClockEnum::EClockLayoutTypes _layoutType, CClockEnum::EClockMotionTypes _motionType = CClockEnum::MOTION_UNDEFINED,
                       QString _imageDial = "",     QString _imageCenter = "",      QString _imageCenterShadow = "",
                       QString _imageHrHand = "" ,  QString _imageHrHandShadow = "",
                       QString _imageMinHand = "",  QString _imageMinHandShadow = "",
                       QString _imageSecHand = "",  QString _imageSecHandShadow = "",
                       QObject *parent = nullptr);

    /**
    * @brief	CDClockInformation::~CDClockInformation is destructor of class CDClockInformation
    * @param	NA.
    * @return	NA.
    **/
    ~CDClockInformation();
    //________________________________________________________________________________________________
    /**
    * @brief	CDClockInformation::uId is get method for "uId" qml property.
    * @param	void.
    * @return	int.
    **/
    int uId();

    /**
    * @brief	CDClockInformation::setUId is set method for "uId" qml property.
    * @param	int : new value to set.
    * @return	void.
    **/
    void setUId(int _uId);

    /**
    * @brief	CDClockInformation::layout is get method for "layout" qml property.
    * @param	void.
    * @return	QString.
    **/
    QString layout();

    /**
    * @brief	CDClockInformation::layoutType is get method for "layoutType" qml property.
    * @param	void.
    * @return	int.
    **/
    int layoutType();

    /**
    * @brief	CDClockInformation::setLayoutType is set method for "layoutType" qml property.
    * @param	CClockEnum::EClockLayoutTypes : new value to set.
    * @return	void.
    **/
    void setLayoutType(CClockEnum::EClockLayoutTypes _layoutType);

    /**
    * @brief	CDClockInformation::motionType is get method for "motionType" qml property.
    * @param	void.
    * @return	int.
    **/
    int motionType();

    /**
    * @brief	CDClockInformation::setMotionType is set method for "motionType" qml property.
    * @param	CClockEnum::EClockMotionTypes : new value to set.
    * @return	void.
    **/
    void setMotionType(CClockEnum::EClockMotionTypes _motionType);

    /**
    * @brief	CDClockInformation::imageDial is get method for "imageDial" qml property.
    * @param	void.
    * @return	QString.
    **/
    QString imageDial();

    /**
    * @brief	CDClockInformation::setImageDial is set method for "imageDial" qml property.
    * @param	QString : new value to set.
    * @return	void.
    **/
    void setImageDial(QString _imageDial);

    /**
    * @brief	CDClockInformation::imageCenter is get method for "imageCenter" qml property.
    * @param	void.
    * @return	QString.
    **/
    QString imageCenter();

    /**
    * @brief	CDClockInformation::setImageCenter is set method for "imageCenter" qml property.
    * @param	QString : new value to set.
    * @return	void.
    **/
    void setImageCenter(QString _imageCenter);

    /**
    * @brief	CDClockInformation::imageCenterShadow is get method for "imageCenterShadow" qml property.
    * @param	void.
    * @return	QString.
    **/
    QString imageCenterShadow();

    /**
    * @brief	CDClockInformation::setImageCenterShadow is set method for "imageCenterShadow" qml property.
    * @param	QString : new value to set.
    * @return	void.
    **/
    void setImageCenterShadow(QString _imageCenterShadow);

    /**
    * @brief	CDClockInformation::imageHrHand is get method for "imageHrHand" qml property.
    * @param	void.
    * @return	QString.
    **/
    QString imageHrHand();

    /**
    * @brief	CDClockInformation::setImageHrHand is set method for "imageHrHand" qml property.
    * @param	QString : new value to set.
    * @return	void.
    **/
    void setImageHrHand(QString _imageHrHand);

    /**
    * @brief	CDClockInformation::imageHrHandShadow is get method for "imageHrHandShadow" qml property.
    * @param	void.
    * @return	QString.
    **/
    QString imageHrHandShadow();

    /**
    * @brief	CDClockInformation::setImageHrHandShadow is set method for "imageHrHandShadow" qml property.
    * @param	QString : new value to set.
    * @return	void.
    **/
    void setImageHrHandShadow(QString _imageHrHandShadow);

    /**
    * @brief	CDClockInformation::imageMinHand is get method for "imageMinHand" qml property.
    * @param	void.
    * @return	QString.
    **/
    QString imageMinHand();

    /**
    * @brief	CDClockInformation::setImageMinHand is set method for "imageMinHand" qml property.
    * @param	QString : new value to set.
    * @return	void.
    **/
    void setImageMinHand(QString _imageMinHand);

    /**
    * @brief	CDClockInformation::imageMinHandShadow is get method for "imageMinHandShadow" qml property.
    * @param	void.
    * @return	QString.
    **/
    QString imageMinHandShadow();

    /**
    * @brief	CDClockInformation::setImageMinHandShadow is set method for "imageMinHandShadow" qml property.
    * @param	QString : new value to set.
    * @return	void.
    **/
    void setImageMinHandShadow(QString _imageMinHandShadow);

    /**
    * @brief	CDClockInformation::imageSecHand is get method for "imageSecHand" qml property.
    * @param	void.
    * @return	QString.
    **/
    QString imageSecHand();

    /**
    * @brief	CDClockInformation::setImageSecHand is set method for "imageSecHand" qml property.
    * @param	QString : new value to set.
    * @return	void.
    **/
    void setImageSecHand(QString _imageSecHand);

    /**
    * @brief	CDClockInformation::imageSecHandShadow is get method for "imageSecHandShadow" qml property.
    * @param	void.
    * @return	QString.
    **/
    QString imageSecHandShadow();

    /**
    * @brief	CDClockInformation::setImageSecHandShadow is set method for "imageSecHandShadow" qml property.
    * @param	QString : new value to set.
    * @return	void.
    **/
    void setImageSecHandShadow(QString _imageSecHandShadow);

signals:
    /**
    * @brief	CDClockInformation::sigUIdChanged is QML signal for "uId" property change envnt.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigUIdChanged();

    /**
    * @brief	CDClockInformation::sigLayoutTypeChanged is QML signal for "layoutType" property change envnt.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigLayoutTypeChanged();

    /**
    * @brief	CDClockInformation::sigMotionTypeChanged is QML signal for "motionType" property change envnt.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigMotionTypeChanged();

    /**
    * @brief	CDClockInformation::sigImageDialChanged is QML signal for "imageDial" property change envnt.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigImageDialChanged();

    /**
    * @brief	CDClockInformation::sigImageCenterChanged is QML signal for "imageCenter" property change envnt.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigImageCenterChanged();

    /**
    * @brief	CDClockInformation::sigImageCenterChanged is QML signal for "imageCenterShadow" property change envnt.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigImageCenterShadowChanged();

    /**
    * @brief	CDClockInformation::sigImageHrHandChanged is QML signal for "imageHrHand" property change envnt.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigImageHrHandChanged();

    /**
    * @brief	CDClockInformation::sigImageHrHandShadowChanged is QML signal for "imageHrHandShadow" property change envnt.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigImageHrHandShadowChanged();

    /**
    * @brief	CDClockInformation::sigImageMinHandChanged is QML signal for "imageMinHand" property change envnt.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigImageMinHandChanged();

    /**
    * @brief	CDClockInformation::sigImageMinHandShadowChanged is QML signal for "imageMinHandShadow" property change envnt.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigImageMinHandShadowChanged();

    /**
    * @brief	CDClockInformation::sigImageSecHandChanged is QML signal for "imageSecHand" property change envnt.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigImageSecHandChanged();

    /**
    * @brief	CDClockInformation::sigImageSecHandShadowChanged is QML signal for "imageSecHandShadow" property change envnt.
    * @param	void.
    * @return	void.
    **/
    Q_SIGNAL void sigImageSecHandShadowChanged();

private:
    int m_iUId;                                     //// member veriable to hold value for "uId" property.
    CClockEnum::EClockLayoutTypes m_eLayoutType;    //// member veriable to hold value for "layoutType" property.
    CClockEnum::EClockMotionTypes m_eMotionType;    //// member veriable to hold value for "motionType" property.
    QString m_strImageDial;                         //// member veriable to hold value for "imageDial" property.
    QString m_strImageCenter;                       //// member veriable to hold value for "imageCenter" property.
    QString m_strImageCenterShadow;                 //// member veriable to hold value for "imageCenterShadow" property.
    QString m_strImageHrHand;                       //// member veriable to hold value for "imageHrHand" property.
    QString m_strImageHrHandShadow;                 //// member veriable to hold value for "imageHrHandShadow" property.
    QString m_strImageMinHand;                      //// member veriable to hold value for "imageMinHand" property.
    QString m_strImageMinHandShadow;                //// member veriable to hold value for "imageMinHandShadow" property.
    QString m_strImageSecHand;                      //// member veriable to hold value for "imageSecHand" property.
    QString m_strImageSecHandShadow;                //// member veriable to hold value for "imageSecHandShadow" property.
};

#endif // CDCLOCKINFORMATION_H
