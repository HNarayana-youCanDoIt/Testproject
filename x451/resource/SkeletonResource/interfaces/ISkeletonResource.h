#ifndef SKELETONRESOURCE_H
#define SKELETONRESOURCE_H

#include <string>
#include <QString>
#include <QObject>
#include <QVariant>

///
/// \brief The ISkeletonResource class
/// This interfaces provides functionality which interacts with the below PresCtrl or Resource proxy directly.
/// It also provides functionality via which data can be provided to the upper layer.
/// It also propagates various events (Hard key, VR, etc) to the upper layers. This is done via Qt Signals
///

class ISkeletonResource
{

public:
    virtual ~ISkeletonResource(){}

    /*****  Request METHODS  ****************************/
    virtual void exampleReq() = 0;


    /*****  CALL BACK METHODS  ****************************/
    virtual void exmapleReqCb() = 0;
    virtual void exampleEventCb() = 0;

};

#endif // SKELETONRESOURCE_H
