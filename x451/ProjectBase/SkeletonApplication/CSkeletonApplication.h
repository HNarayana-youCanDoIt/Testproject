#ifndef CSKELETONAPPLICATION_H
#define CSKELETONAPPLICATION_H

#include "HMIIncludes.h"

class CSkeletonAdaptor;
class CSkeletonSM;
class CSkeletonDataEventHandler;

class CSkelectonApplication : public CBaseApplication
{
public:
    CSkelectonApplication(QQuickItem* parent = nullptr);

    ~CSkelectonApplication();

    void raiseSMEvent(const QString & name,const QVariant & data);
    virtual void onCreated(QQuickItem* rootObject);

    void loadScreen(QString qmlFilePath);

private:
    CSkeletonAdaptor& mSkeletonAdaptor;
    CSkeletonSM* mpSkeletonSM;
    CSkeletonDataEventHandler* mpSkeletonDataEventHandler;
};



#endif // CSKELETONAPPLICATION_H
