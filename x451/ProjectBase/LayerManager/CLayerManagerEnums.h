/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CLayerManagerEnums.h
* @ingroup      HMIComponent
* @author       Mohit Rajani
* CLayerManagerEnum     Class that would contain all the Enums related to LayerManager
*               that would also be registered as a QML type so that these can be used in QML too
*/

#ifndef CLAYERMANAGERENUM_H
#define CLAYERMANAGERENUM_H

#include <QObject>
#include <QtQml>

/**
 * @class CLayerManagerEnums
 * @brief Class that would contain all the Enums related to LayerManager
 *        that would also be registered as a QML type so that these can be used in QML too
 */
class CLayerManagerEnums : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief The ESurfaceType enum
     * enums for the various surfaces supported by the system
     */
    enum ESurfaceType
    {
        SURFACE_INVALID = -1,
        SURFACE_HMI = 0,
        SURFACE_ANDROIDAUTO,
        SURFACE_CARPLAY,
        SURFACE_HVAC_NOTIFICATIONS,
        SURFACE_VOL_NOTIFICATION,
        SURFACE_VIDEO
    };
    Q_ENUM(ESurfaceType)

    /**
     * @brief registerLayerManagerEnumsToQML Method to register CLayerManagerEnum as a QML type
     */
    static void registerLayerManagerEnumsToQML()
    {
        qmlRegisterType<CLayerManagerEnums>("com.harman.qml.layermanagerenums",1,0,"LayerManagerEnums");
    }
};
Q_DECLARE_METATYPE(CLayerManagerEnums::ESurfaceType)

#endif // CLAYERMANAGERENUM_H
