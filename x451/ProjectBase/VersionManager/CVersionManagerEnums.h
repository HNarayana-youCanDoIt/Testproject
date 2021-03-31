#ifndef CVERSIONMANAGERENUMS_H
#define CVERSIONMANAGERENUMS_H

#include <QObject>
#include <QtQml>

using namespace std;

class CVersionManagerEnums: public QObject
{
    Q_OBJECT

public:

    /**
     * @brief The EPowerModeType enum, contains the power mode type
     */
    enum EPowerModeType
    {
        TYPE_POWER_MODE_INVALID = -1,
        TYPE_POWER_MODE_IGN_ON = 0,
        TYPE_POWER_MODE_PEPS = 1,
    };
    Q_ENUMS(EPowerModeType)


    struct SVersionInformation
    {
        string versionName;
        string versionReleasedDate;
        string versionData;
        SVersionInformation() : versionName("NA"), versionReleasedDate("NA"), versionData("NA")
        {}
    };

    static void registerSkeletonEnumsToQML()
    {
        qmlRegisterType<CVersionManagerEnums>("com.harman.qml.versionManagerenums",1,0,"VersionManagerEnums");
    }
};

Q_DECLARE_METATYPE(CVersionManagerEnums::EPowerModeType)

#endif // CVERSIONMANAGERENUMS_H
