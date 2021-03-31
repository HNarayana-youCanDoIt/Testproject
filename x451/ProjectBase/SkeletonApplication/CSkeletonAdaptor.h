#ifndef SKELETONADAPTOR_H
#define SKELETONADAPTOR_H

#include <QObject>
#include "logging.h"
#include "CSkeletonEnums.h"
#include <QString>
#include <CFramework.h>
#include "SkeletonResource/interfaces/ISkeletonResource.h"

class CSkeletonAdaptor : public QObject
{
    Q_OBJECT

    // Properties
    Q_PROPERTY(CSkeletonEnums::ESkeletonType type READ type WRITE setType NOTIFY sigTypeChanged)

public:

    // Get Adaptor instance
    ~CSkeletonAdaptor();
    static CSkeletonAdaptor& getInstance();

    CSkeletonEnums::ESkeletonType type();
    void setType(CSkeletonEnums::ESkeletonType type);

signals:
    void sigTypeChanged();

public slots:

protected:

    // API's called directly by the QML files, these need to be Q_INVOKABLE
    Q_INVOKABLE void exampleReq();


private:
    explicit CSkeletonAdaptor(QObject *parent = nullptr);
    static CSkeletonAdaptor* mpSkeletonAdaptor;

    CSkeletonEnums::ESkeletonType mType;

    // Framework reference
    CFramework& mfw;

    // Skeleton resource
    ISkeletonResource* mSkeletonResource;
};

#endif // SKELETONADAPTOR_H
