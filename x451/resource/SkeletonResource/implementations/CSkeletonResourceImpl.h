#ifndef CSKELETONRESOURCEIMPL_H
#define CSKELETONRESOURCEIMPL_H

#include <QVariant>
#include <memory>


#include "../interfaces/ISkeletonResource.h"
#include "CSkeletonDataEventProvider.h"

//Include the headers related to PresCtrl

///
/// \brief The SkeletonResourceImpl class
/// This class implements the SkeletonResource interface.
///


class CSkeletonResourceImpl: public ISkeletonResource
{
public:

    virtual ~CSkeletonResourceImpl();


public:

    CSkeletonDataEventProvider* getSkeletonDataEventProvider();

    // Overide the SkeletonResource functions that are used by the upper layers to propagate the calls
    virtual void exampleReq() override;    

    /*****  CALL BACK METHODS  ****************************/
    virtual void exmapleReqCb() override;
    virtual void exampleEventCb() override;

private:
    friend class CHMIMain;
    CSkeletonResourceImpl();    

    //Create an instance of the CSkeletonDataEventProvider to emit signals to the upper layer
    CSkeletonDataEventProvider* mpSkeletonDataEventProvider;

    int mType;
};

#endif // CSKELETONRESOURCEIMPL_H
