#ifndef CSTARTUPANIM_H
#define CSTARTUPANIM_H

#include <QObject>
#include "CBaseApplication.h"
#include "StateMachine_TML_HMI_SM.h"

class CStartupAnim : public CBaseApplication, public TML_HMI_SM::SCI_Startup_OCB
{
public:
    CStartupAnim(QQuickItem* parent = nullptr);

    ~CStartupAnim();

    virtual void onCreated(QQuickItem* rootObject);
    void raiseSMEvent(const QString & name,const QVariant & data);

    // SCI_Startup_OCB interface
public:
    void enterStartAnim() override;
    void exitStartupAnim() override;
};

#endif // CSTARTUPANIM_H
