#ifndef CHMIAPPLICATIONENUMS_H
#define CHMIAPPLICATIONENUMS_H

#include <QObject>
#include <QtQml>

/*!
 * @class CHMIApplicationEnums
 * @brief This class contains HMI application UI module related enums.
 */
class CHMIApplicationEnums: public QObject
{
    Q_OBJECT
public:


    /**
     * @enum    EHMIProjectVarient
     * @brief   EHMIProjectVarient : enum for project varient type
     */
    enum EHMIProjectVarient
    {
        HMI_PROJECT_INVALID = -1,
        HMI_PROJECT_X451,
        HMI_PROJECT_X104_VAVE,
        HMI_PROJECT_X445,
    };
    Q_ENUM(EHMIProjectVarient)

    static void registerHMIApplicationEnumsToQML()
    {
        qmlRegisterType<CHMIApplicationEnums>("com.harman.qml.hmiapplicationenum", 1, 0, "HMIApplicationEnum");
    }
};

Q_DECLARE_METATYPE(CHMIApplicationEnums::EHMIProjectVarient)

#endif // CHMIAPPLICATIONENUMS_H
