#ifndef CSKELETONSM_H
#define CSKELETONSM_H

#include "SkeletonApplication/CSkeletonApplication.h"
#include <StateMachine/src-gen/TML_HMI_SM.h>

class CSkeletonSM: public TML_HMI_SM::SCI_Skeleton_OCB
{
public:
    CSkeletonSM(CSkelectonApplication& skeletonApp);
    ~CSkeletonSM();

    // Overide the functions of the SM interface for the particular application
public:

    virtual void enterState();
    virtual void exitState();
    virtual void exampleRequest();

private:
    // Parent class pointer
    CSkelectonApplication& mSkeletonApp;
};

#endif // CSKELETONSM_H
