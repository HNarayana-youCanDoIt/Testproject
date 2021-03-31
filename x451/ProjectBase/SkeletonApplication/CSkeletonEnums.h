#ifndef CSKELETONENUMS_H
#define CSKELETONENUMS_H

#include <QObject>
#include <QtQml>

class CSkeletonEnums: public QObject
{
    Q_OBJECT
public:
    enum ESkeletonType
    {
        TYPE_INVALID = -1,
        TYPE_DEFAULT = 0
    };
    Q_ENUMS(ESkeletonType)

    static void registerSkeletonEnumsToQML()
    {
        qmlRegisterType<CSkeletonEnums>("com.harman.qml.skeletonenums",1,0,"SkeletonEnums");
    }
};

Q_DECLARE_METATYPE(CSkeletonEnums::ESkeletonType)

#endif // CSKELETONENUMS_H
